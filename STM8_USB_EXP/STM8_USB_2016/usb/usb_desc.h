#ifndef USB_DESC_H_
#define USB_DESC_H_

#define TYPE_DEVICE_DESCRIPTOR 0x01
#define TYPE_CONFIG_DESCRIPTOR 0x02
#define TYPE_STRING_DESCRIPTOR 0x03
#define TYPE_INTERFACE_DESCRIPTOR 0x04
#define TYPE_ENDPOINT_DESCRIPTOR 0x05
#define TYPE_HID_DESCRIPTOR 0x21
#define TYPE_REPORT_DESCRIPTOR 0x22

#define SIZE_DEVICE_DESCRIPTOR 0x12
#define SIZE_CONFIGURATION_DESCRIPTOR 41
#define SIZE_REPORT_DESCRIPTOR 40

#define LENGTH_STRING_DESCRIPTOR 4
#define SIZE_STRING_LANGID 4
#define SIZE_STRING_VENDOR             38
#define SIZE_STRING_PRODUCT            48
#define SIZE_STRING_SERIAL             26

extern const unsigned char usb_device_descriptor[SIZE_DEVICE_DESCRIPTOR];
extern const unsigned char usb_configuration_descriptor[SIZE_CONFIGURATION_DESCRIPTOR];
extern const unsigned char usb_report_descriptor[SIZE_REPORT_DESCRIPTOR];
extern const unsigned char* USB_String_Descriptors[LENGTH_STRING_DESCRIPTOR];
extern const unsigned char USB_String_Descriptors_Length[LENGTH_STRING_DESCRIPTOR];
#endif