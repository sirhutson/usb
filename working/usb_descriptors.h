/*
 * Copyright (c) 2016, Alex Taradov <alex@taradov.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _USB_DESCRIPTORS_H_
#define _USB_DESCRIPTORS_H_

/*- Includes ----------------------------------------------------------------*/
#include "usb.h"

/*- Definitions -------------------------------------------------------------*/
enum
{
  USB_HID_DESCRIPTOR          = 0x21,
  USB_HID_REPORT_DESCRIPTOR   = 0x22,
  USB_HID_PHYSICAL_DESCRIPTOR = 0x23,
};

enum
{
	USB_CDC_DESCRIPTOR   =  0x24,
};

enum
{
  USB_STR_ZERO,
  USB_STR_MANUFACTURER,
  USB_STR_PRODUCT,
  USB_STR_SERIAL_NUMBER,
  USB_STR_CONFIGURATION,
  USB_STR_INTERFACE,
  USB_STR_COUNT,
};

/*- Types -------------------------------------------------------------------*/
typedef struct PACK
{
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  uint16_t  bcdHID;
  uint8_t   bCountryCode;
  uint8_t   bNumDescriptors;
  uint8_t   bDescriptorType1;
  uint16_t  wDescriptorLength;
} usb_hid_descriptor_t;

typedef struct PACK
{
	uint8_t     bLength;
	uint8_t     bDescriptortype;
	uint8_t     bDescriptorsubtype;
	uint8_t     bmCapabilities;
} usb_acm_t;

typedef struct PACK
{
	uint8_t    bLength;
	uint8_t    bDescriptortype;
	uint8_t    bDescriptorsubtype;
	uint16_t    bcdCDC;
} usb_headerfunction_t;

typedef struct PACK
{
	uint8_t     bLength;
	uint8_t     bDescriptortype;
	uint8_t     bEndpointAddress;
	uint8_t     bmAttributes;
	uint16_t    wMaxPacketSize;
	uint8_t     bInterval;
} usb_notification_t;


typedef struct PACK
{
	uint8_t    bLength;
	uint8_t    bDescriptortype;
	uint8_t    bDescriptorsubtype;
	uint8_t    bControlInterface;
	uint8_t    bSubordinateInterface0;
}usb_unionfunction_t;

typedef struct PACK
{
	uint8_t    bLength;
	uint8_t    bDescriptortype;
	uint8_t    bDescriptorsubtype;
	uint8_t    bmCapabilities;
	uint8_t    bDataInterface;
} usb_callmanagement_t; 


typedef struct PACK
{
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  uint8_t   bInterfaceNumber;
  uint8_t   bAlternateSetting;
  uint8_t   bNumEndpoints;
  uint8_t   bInterfaceClass;
  uint8_t   bInterfaceSubClass;
  uint8_t   bInterfaceProtocol;
  uint8_t   iInterface;
} usb_datainterface_descriptor_t;

typedef struct PACK
{
  usb_configuration_descriptor_t  configuration;
  usb_interface_descriptor_t      interface;
	usb_headerfunction_t            headerfunction;
	usb_acm_t                       acm;
	usb_unionfunction_t             unionfunction;
	usb_callmanagement_t            callmanagement;
	usb_notification_t              notification;
	usb_datainterface_descriptor_t  datainterface;
  usb_endpoint_descriptor_t       ep_in;
  usb_endpoint_descriptor_t       ep_out;
} usb_configuration_hierarchy_t;

//-----------------------------------------------------------------------------
extern usb_device_descriptor_t usb_device_descriptor;
extern usb_configuration_hierarchy_t usb_configuration_hierarchy;
extern uint8_t usb_hid_report_descriptor[33];
extern usb_string_descriptor_zero_t usb_string_descriptor_zero;
extern char *usb_strings[];
extern uint8_t usb_string_descriptor_buffer[64];

#endif // _USB_DESCRIPTORS_H_

