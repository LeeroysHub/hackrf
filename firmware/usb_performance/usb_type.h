#ifndef __USB_TYPE_H__
#define __USB_TYPE_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint8_t request_type;
	uint8_t request;
	uint8_t value_l;
	uint8_t value_h;
	uint8_t index_l;
	uint8_t index_h;
	uint8_t length_l;
	uint8_t length_h;
} usb_setup_t;

typedef enum {
	USB_STANDARD_REQUEST_GET_STATUS = 0,
	USB_STANDARD_REQUEST_CLEAR_FEATURE = 1,
	USB_STANDARD_REQUEST_SET_FEATURE = 3,
	USB_STANDARD_REQUEST_SET_ADDRESS = 5,
	USB_STANDARD_REQUEST_GET_DESCRIPTOR = 6,
	USB_STANDARD_REQUEST_SET_DESCRIPTOR = 7,
	USB_STANDARD_REQUEST_GET_CONFIGURATION = 8,
	USB_STANDARD_REQUEST_SET_CONFIGURATION = 9,
	USB_STANDARD_REQUEST_GET_INTERFACE = 10,
	USB_STANDARD_REQUEST_SET_INTERFACE = 11,
	USB_STANDARD_REQUEST_SYNCH_FRAME = 12,
} usb_standard_request_t;

typedef enum {
	USB_SETUP_REQUEST_TYPE_shift = 5,
	USB_SETUP_REQUEST_TYPE_mask = 3 << USB_SETUP_REQUEST_TYPE_shift,
	
	USB_SETUP_REQUEST_TYPE_STANDARD = 0 << USB_SETUP_REQUEST_TYPE_shift,
	USB_SETUP_REQUEST_TYPE_CLASS = 1 << USB_SETUP_REQUEST_TYPE_shift,
	USB_SETUP_REQUEST_TYPE_VENDOR = 2 << USB_SETUP_REQUEST_TYPE_shift,
	USB_SETUP_REQUEST_TYPE_RESERVED = 3 << USB_SETUP_REQUEST_TYPE_shift,
	
	USB_SETUP_REQUEST_TYPE_DATA_TRANSFER_DIRECTION_shift = 7,
	USB_SETUP_REQUEST_TYPE_DATA_TRANSFER_DIRECTION_mask = 1 << USB_SETUP_REQUEST_TYPE_DATA_TRANSFER_DIRECTION_shift,
	USB_SETUP_REQUEST_TYPE_DATA_TRANSFER_DIRECTION_HOST_TO_DEVICE = 0 << USB_SETUP_REQUEST_TYPE_DATA_TRANSFER_DIRECTION_shift,
	USB_SETUP_REQUEST_TYPE_DATA_TRANSFER_DIRECTION_DEVICE_TO_HOST = 1 << USB_SETUP_REQUEST_TYPE_DATA_TRANSFER_DIRECTION_shift,
} usb_setup_request_type_t;

typedef enum {
	USB_TRANSFER_DIRECTION_OUT = 0,
	USB_TRANSFER_DIRECTION_IN = 1,
} usb_transfer_direction_t;
	
typedef enum {
	USB_DESCRIPTOR_TYPE_DEVICE = 1,
	USB_DESCRIPTOR_TYPE_CONFIGURATION = 2,
	USB_DESCRIPTOR_TYPE_STRING = 3,
	USB_DESCRIPTOR_TYPE_INTERFACE = 4,
	USB_DESCRIPTOR_TYPE_ENDPOINT = 5,
	USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER = 6,
	USB_DESCRIPTOR_TYPE_OTHER_SPEED_CONFIGURATION = 7,
	USB_DESCRIPTOR_TYPE_INTERFACE_POWER = 8,
} usb_descriptor_type_t;

typedef enum {
	USB_TRANSFER_TYPE_CONTROL = 0,
	USB_TRANSFER_TYPE_ISOCHRONOUS = 1,
	USB_TRANSFER_TYPE_BULK = 2,
	USB_TRANSFER_TYPE_INTERRUPT = 3,
} usb_transfer_type_t;

typedef enum {
	USB_SPEED_LOW = 0,
	USB_SPEED_FULL = 1,
	USB_SPEED_HIGH = 2,
	USB_SPEED_SUPER = 3,
} usb_speed_t;

typedef struct {
	const uint8_t* const descriptor;
	const uint32_t number;
	const usb_speed_t speed;
} usb_configuration_t;

typedef struct {
	const uint8_t* const descriptor;
	usb_configuration_t* (*configurations)[];
	const usb_configuration_t* configuration;
} usb_device_t;

typedef struct usb_endpoint_t usb_endpoint_t;
struct usb_endpoint_t {
	usb_setup_t setup;
	uint8_t buffer[8];	// Buffer for use during IN stage.
	const uint_fast8_t address;
	usb_device_t* const device;
	usb_endpoint_t* const in;
	usb_endpoint_t* const out;
	void (*setup_complete)(usb_endpoint_t* const endpoint);
	void (*transfer_complete)(usb_endpoint_t* const endpoint);
};

#endif//__USB_TYPE_H__
