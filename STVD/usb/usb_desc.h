#ifndef USB_DESC_H_
#define USB_DESC_H_

#define ID_DEVICE_DESCRIPTOR 0x01
#define ID_CONFIG_DESCRIPTOR 0x02
#define ID_INTERFACE_DESCRIPTOR 0x04
#define ID_ENDPOINT_DESCRIPTOR 0x05
#define ID_HID_DESCRIPTOR 0x21
#define ID_REPORT_DESCRIPTOR 0x22

#define SIZE_DEVICE_DESCRIPTOR 0x12
#define SIZE_CONFIGURATION_DESCRIPTOR 41
#define SIZE_REPORT_DESCRIPTOR 40

extern const unsigned char usb_device_descriptor[SIZE_DEVICE_DESCRIPTOR];
extern const unsigned char usb_configuration_descriptor[SIZE_CONFIGURATION_DESCRIPTOR];
extern const unsigned char usb_report_descriptor[SIZE_REPORT_DESCRIPTOR];

#endif