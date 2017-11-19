#include "usb_desc.h"

const unsigned char usb_device_descriptor[SIZE_DEVICE_DESCRIPTOR]
= { 
	SIZE_DEVICE_DESCRIPTOR, // Size of the Descriptor in Bytes
	TYPE_DEVICE_DESCRIPTOR, // Device Descriptor (0x01)
	0x10, 
	0x01, // USB 1.1 = 0x0110ï¼?USB 1.0 = 0x0100
	0x00, // Class Code
	0x00, // Subclass Code
	0x00, // Protocol Code
	0x08, // Maximum Packet Size for Zero Endpoint
	0x83, // VID_L
	0x04, // VID_H
	0x50, // PID_L
	0x57, // PID_H
	0x00, /*bcdDevice rel. 2.00*/
	0x02,
	0x01, // Index of Manufacturer String Descriptor
	0x02, // Index of Product String Descriptor
	0x03, // Index of Serial Number String Descriptor
	0x01, // Number of Possible Configurations
};

const unsigned char usb_configuration_descriptor[SIZE_CONFIGURATION_DESCRIPTOR] = { 
	0x09, // Size of Descriptor in Bytes
	TYPE_CONFIG_DESCRIPTOR, // Configuration Descriptor (0x02)
	SIZE_CONFIGURATION_DESCRIPTOR,
	0x00, // Total length in bytes of data returned
	0x01, // Number of Interfaces
	0x01, // Value to use as an argument to select this configuration
	0x00, // Index of String Descriptor describing this configuration
	0xC0, // D7 Reserved, set to 1.(USB 1.0 Bus Powered),D6 Self Powered,D5 Remote Wakeup,D4..0 Reserved, set to 0.
	0x32,   // Maximum Power Consumption in 2mA units
	
	// interface descriptor
	0x09, // Size of Descriptor in Bytes (9 Bytes)
	TYPE_INTERFACE_DESCRIPTOR, // Interface Descriptor (0x04)
	0x00, // Number of Interface
	0x00, // Value used to select alternative setting
	0x02, // Number of Endpoints used for this interface
	0x03, // Class Code
	0x00, // Subclass Code
	0x00, // Protocol Code
	0x00, // Index of String Descriptor Describing this interface
	
	// HID descriptor
	0x09,    // Size of Descriptor in Bytes (9 Bytes)
	TYPE_HID_DESCRIPTOR, // HID descriptor (0x21)
	0x10, 
	0x01, // BCD representation of HID version
	0x00, // Target country code
	0x01, // Number of HID Report (or other HID class) Descriptor infos to follow */
	TYPE_REPORT_DESCRIPTOR, // Descriptor type: report
	SIZE_REPORT_DESCRIPTOR,
	0x00,  /* total length of report descriptor */
	
	// Endpoint descriptor
	0x07, // Size of Descriptor in Bytes (7 Bytes)
	TYPE_ENDPOINT_DESCRIPTOR, // Endpoint descriptor (0x05)
	0x81, // IN endpoint number 1 (0x81)
	0x03, // attrib: Interrupt endpoint
	0x04, // 
	0x00, // maximum packet size
	0x20,  // POLL INTERVAL (ms)
	
	0x07, // Size of Descriptor in Bytes (7 Bytes)
	TYPE_ENDPOINT_DESCRIPTOR, // Endpoint descriptor (0x05)
	0x01, // IN endpoint number 1 (0x81)
	0x03, // attrib: Interrupt endpoint
	0x04, // 
	0x00, // maximum packet size
	0x20  // POLL INTERVAL (ms)
};

/* HID dung cho mouse */
const unsigned char usb_report_descriptor[SIZE_REPORT_DESCRIPTOR] = {
	0x06,0xA0,0xFF, /* USAGE_PAGE (ST Page) */ 
	0x09, 0x01, /* USAGE (Demo Kit) */ 
	0xa1, 0x01, /* COLLECTION (Application) */ 
	
	// The Input report 
	0x09,0x03, // USAGE ID - Vendor defined 
	0x15, 0x80,//?????(0x80 or -128)
  0x25, 0x7F,//?????(0x7F or 127)
  0x35, 0x00,//?????(0)
  0x45,0xFF,//?????(255)
	0x75,0x08, // REPORT_SIZE (8bit) 
	0x95,4, // REPORT_COUNT (64Byte) 
	0x81,0x02, // INPUT (Data,Var,Abs) 

	// The Output report 
	0x09,0x04, // USAGE ID - Vendor defined 
	0x15, 0x80,//?????(0x80 or -128)
  0x25, 0x7F,//?????(0x7F or 127)
  0x35, 0x00,//?????(0)
  0x45,0xFF,//?????(255)
	0x75,0x08, // REPORT_SIZE (8bit) 
	0x95,4, // REPORT_COUNT (64Byte) 
	0x91,0x02, // OUTPUT (Data,Var,Abs) 

	0xc0 /* END_COLLECTION */ 
	//,0,0,0,0,0,0,0,0,0,0,0,0
};




const unsigned char String_LangID[SIZE_STRING_LANGID] = {
	SIZE_STRING_LANGID,
	TYPE_STRING_DESCRIPTOR,
	0x0409,	//En-US
};

const unsigned char String_Vendor[SIZE_STRING_VENDOR] =
{
    SIZE_STRING_VENDOR, /* Size of Vendor string */
    TYPE_STRING_DESCRIPTOR,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
    'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
    'c', 0, 's', 0
};

const unsigned char String_Product[SIZE_STRING_PRODUCT] =
{
    SIZE_STRING_PRODUCT,          /* bLength */
    TYPE_STRING_DESCRIPTOR,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '8', 0, ' ', 0, 'V', 0, 'U', 0,
    'S', 0, 'B', 0, ' ', 0, 'H', 0, 'I', 0, 'D', 0, ' ', 0,
    'd', 0,'e',0, 'm', 0, 'o', 0, ' ', 0, 'k', 0, 'i', 0, 't', 0 , ' ', 0
};

const unsigned char String_Serial[SIZE_STRING_SERIAL] =
{
    SIZE_STRING_SERIAL,           /* bLength */
    TYPE_STRING_DESCRIPTOR,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0,'3', 0,'2', 0
};

const unsigned char* USB_String_Descriptors[LENGTH_STRING_DESCRIPTOR] = {
	String_LangID,
	String_Vendor,
	String_Product,
	String_Serial
};

const unsigned char USB_String_Descriptors_Length[LENGTH_STRING_DESCRIPTOR] = {
	SIZE_STRING_LANGID,
	SIZE_STRING_VENDOR,
	SIZE_STRING_PRODUCT,
	SIZE_STRING_SERIAL
};