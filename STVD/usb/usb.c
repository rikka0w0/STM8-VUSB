#include "main.h"
#include "usb_desc.h"



extern void usb_tx(void);

uint8_t data_sync;
uint8_t usb_rx_buffer[16];

uint8_t usb_Transaction;
uint8_t usb_EndPoint;

uint8_t * usb_tx_buffer_pointer;

uint8_t usb_tx_count;
uint8_t usb_rx_count;

volatile uint8_t usb_device_address;









struct usb_type
{
	volatile uint8_t state;
	volatile uint8_t event;

	uint8_t setup_address;

	uint8_t rx_buffer[16];
	uint8_t rx_lenght;

	uint8_t tx_buffer[16];
	uint8_t tx_lenght;
} usb;

void usb_init(void)
{
	usb.state = USB_STATE_IDLE;
	usb.event = USB_EVENT_NO;
	usb_device_address = 0;
	usb.setup_address  = 0;
}

void usb_send_nack(void)
{
	uint8_t data[2];

	GPIOC->ODR = 0x40;
	GPIOC->CR1 = 0xFF;
	GPIOC->CR2 = 0xFF;
	GPIOC->DDR = 0xFF;

	data[0] = 0x80;
	data[1] = USB_PID_NACK;

	usb_tx_count = 2;
	usb_tx_buffer_pointer = &data[0];

	usb_tx();

	nop();
	nop();
	nop();
	nop();
	nop();

	GPIOC->CR2 = 0x00;
	GPIOC->CR1 = 0x00;
	GPIOC->DDR = 0x3F;
}

@inline void usb_send_ack(void)
{
	uint8_t data[2];

	GPIOC->ODR = 0x40;
	GPIOC->CR1 = 0xFF;
	GPIOC->CR2 = 0xFF;
	GPIOC->DDR = 0xFF;
	
	data[0] = 0x80;
	data[1] = USB_PID_ACK;

	usb_tx_count = 2;
	usb_tx_buffer_pointer = &data[0];

	
	usb_tx();
	
	nop();
	nop();
	nop();
	nop();
	nop();

	GPIOC->CR2 = 0x00;
	GPIOC->CR1 = 0x00;
	GPIOC->DDR = 0x7F;
	GPIOC->DDR = 0x3F;
}

uint8_t count = 0;

@inline void usb_send_answer(void)
{
	GPIOC->ODR = 0x40;
	GPIOC->CR1 = 0xFF;
	GPIOC->CR2 = 0xFF;
	GPIOC->DDR = 0xFF;

	usb_tx_count = usb.tx_lenght;
	usb_tx_buffer_pointer = usb.tx_buffer;

	usb_tx();

	nop();
	nop();
	nop();
	nop();
	nop();

	GPIOC->CR2 = 0x00;
	GPIOC->CR1 = 0x00;
	GPIOC->DDR = 0x3F;
}

@inline void usb_copy_rx_buffer(void)
{
	uint8_t index = 0;

	for (index = 0; index < 16; index++)
		usb.rx_buffer[index] = usb_rx_buffer[index];
}

void usb_IN(void){
	if(usb.setup_address!=0)
		usb_device_address=usb.setup_address;


	if (usb.event == USB_EVENT_READY_DATA_IN)
	{
		usb_send_answer();
		usb.state = USB_STATE_IN;
		usb.event = USB_EVENT_WAIT_DATA_IN;
	}
	else
	{
		usb_send_nack();
	}
}

void usb_rx_ok(void)
{
	switch (usb_rx_buffer[1])
	{	
		case (USB_PID_OUT):
		{
			usb.state = USB_STATE_OUT;
			break;
		}
		
		case (USB_PID_DATA0):
		{
			if (usb_Transaction == USB_PID_SETUP)
			{
				usb_Transaction = USB_STATE_IDLE;
				usb_send_ack();
				usb_copy_rx_buffer();
				usb.event = USB_EVENT_RECEIVE_SETUP_DATA;
			}
			else if (usb.state == USB_STATE_OUT)
			{
				usb_send_ack();
				usb.event = USB_EVENT_NO;
			}
			break;
		}
		
		case (USB_PID_DATA1):
		{
			if (usb.state == USB_STATE_OUT)
			{
				usb_send_ack();
				usb.event = USB_EVENT_NO;
			}

			break;
		}
				
		default:
		{
			usb.state = USB_STATE_IDLE;
			break;
		}
	}
}

void USB_CRC16(uint8_t * buffer, uint8_t lenght)
{
	uint16_t crc = 0xFFFF;
	uint8_t index;
	uint8_t i;

	for (index = 0; index < lenght; index++)
	{
		crc ^= *buffer++;

		for (i = 8; i--;)
		{
			if ((crc & BIT(0)) != 0)
			{
				crc >>= 1;
				crc ^= 0xA001;
			}
			else
			{
				crc >>= 1;
			}
		}
	}

	crc = ~crc;

	*buffer++ = (uint8_t) crc;
	*buffer = (uint8_t) (crc >> 8);
}

void USB_Send_Data(uint8_t * buffer, uint8_t length, uint8_t mode)
{
	uint8_t index;
	
	if(mode)
		data_sync = USB_PID_DATA1;
		
	
	
	while (length > 0)
	{
		usb.tx_buffer[0] = 0x80;
		usb.tx_buffer[1] = data_sync;
		
		//Use variable mode as a flag
		if (length == 8)
			mode = 0x66;	//Requires an empty packet in the end
		
		if (length > 8)
		{
			usb.tx_lenght = 12;

			for (index = 2; index < 10; index++)
				usb.tx_buffer[index] = *buffer++;
			length -= 8;
		}
		else
		{
			usb.tx_lenght = (uint8_t) (4 + length);
			for (index = 2; index < 2 + length; index++)
				usb.tx_buffer[index] = *buffer++;
			length = 0;
		}

		// calculate CRC
		USB_CRC16(&usb.tx_buffer[2], (uint8_t) (usb.tx_lenght - 4));

		// toggle data0 data1
		if (data_sync == USB_PID_DATA1)
			data_sync = USB_PID_DATA0;
		else
			data_sync = USB_PID_DATA1;

		// data is available to send out 
		usb.event = USB_EVENT_READY_DATA_IN;
		
		// wait for transmission and then start the next
		while (usb.event == USB_EVENT_READY_DATA_IN)
		{
			if (usb.event == USB_EVENT_WAIT_DATA_IN)
				break;
		}
	}
	
	//If the length of last DATA packet is 8, then finialize the transcation by an empty packet
	if (mode == 0x66){
		usb.tx_lenght = 4;
		usb.tx_buffer[0] = 0x80;
		usb.tx_buffer[1] = data_sync;
		usb.tx_buffer[2] = 0;
		usb.tx_buffer[3] = 0;
	
		if (data_sync == USB_PID_DATA1)
			data_sync = USB_PID_DATA0;
		else
			data_sync = USB_PID_DATA1;
	
		usb.event = USB_EVENT_READY_DATA_IN;
	}
}


void USB_Send_Null_DATA1(void)
{
	usb.tx_lenght = 4;
	usb.tx_buffer[0] = 0x80;
	usb.tx_buffer[1] = USB_PID_DATA1;
	usb.tx_buffer[2] = 0;
	usb.tx_buffer[3] = 0;
	
	usb.event = USB_EVENT_READY_DATA_IN;
}

void USB_Send_Null_DATA0(void)
{
	usb.tx_lenght = 4;
	usb.tx_buffer[0] = 0x80;
	usb.tx_buffer[1] = USB_PID_DATA0;
	usb.tx_buffer[2] = 0;
	usb.tx_buffer[3] = 0;
	
	usb.event = USB_EVENT_READY_DATA_IN;
}

void usb_send_stall(void)
{
	usb.tx_lenght = 2;
	usb.tx_buffer[0] = 0x80;
	usb.tx_buffer[1] = USB_PID_STALL;
	
	usb.event = USB_EVENT_READY_DATA_IN;
}


void usb_process(void)
{

	if (usb.event == USB_EVENT_RECEIVE_SETUP_DATA)
	{
		switch (usb.rx_buffer[2])
		{
			case (USB_REQUEST_TYPE_FROM_DEVICE): //0x80
			{
				if (usb.rx_buffer[3] == USB_REQUEST_GET_DESCRIPTOR){ //0x06
						switch (usb.rx_buffer[5])
						{
							case (TYPE_DEVICE_DESCRIPTOR):
							{
								USB_Send_Data(usb_device_descriptor, usb.rx_buffer[8], 1);
								break;
							}
							case (TYPE_CONFIG_DESCRIPTOR):
							{
								USB_Send_Data(usb_configuration_descriptor,usb.rx_buffer[8], 1);
								break;
							}
							case (TYPE_STRING_DESCRIPTOR):
							{
								USB_Send_Data(USB_String_Descriptors[usb.rx_buffer[4]], USB_String_Descriptors_Length[usb.rx_buffer[4]], 1);
								break;
							}
						}
				}
				
				break;
			}
			
			case (USB_REQUEST_TYPE_FROM_INTERFACE):
			{
				switch (usb.rx_buffer[3])
				{
					case(USB_REQUEST_GET_DESCRIPTOR):
					{
						USB_Send_Data(usb_report_descriptor, SIZE_REPORT_DESCRIPTOR, 1);
						//usb_ready_reg=1;
						break;
					}
					default: 
						USB_Send_Null_DATA1();
						break;
				}
				break;
			}
			
			
			case (USB_REQUEST_TYPE_TO_DEVICE):	//0x00
			{
				switch (usb.rx_buffer[3])
				{
					case (USB_REQUEST_SET_ADDRESS):	//0x05
					{
						usb.setup_address = usb.rx_buffer[4];
						USB_Send_Null_DATA1();
						break;
					}
					case (USB_REQUEST_SET_CONFIGURATION):	//0x09
					{
						USB_Send_Null_DATA1();
						break;
					}
				}
				break;
			}

			case (0x21):
			{
				usb_send_stall();
				break;
			}
		}
	}
}
