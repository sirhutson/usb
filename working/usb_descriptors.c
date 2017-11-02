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


/*- Includes ----------------------------------------------------------------*/
#include "usb.h"
#include "usb_descriptors.h"

/*- Variables ---------------------------------------------------------------*/
__attribute__((aligned (4))) usb_device_descriptor_t usb_device_descriptor =
{
  .bLength            = sizeof(usb_device_descriptor_t),
  .bDescriptorType    = USB_DEVICE_DESCRIPTOR,
  .bcdUSB             = 0x0200,
  .bDeviceClass       = 0x02,
  .bDeviceSubClass    = 0x00,
  .bDeviceProtocol    = 0x00, //was 0
  .bMaxPacketSize0    = 0x40,
  .idVendor           = 0x239a,
  .idProduct          = 0x000b,
  .bcdDevice          = 0x1000,
  .iManufacturer      = 0,
  .iProduct           = 0,
  .iSerialNumber      = 0,
  .bNumConfigurations = 0x01,
};

__attribute__((aligned (4))) usb_configuration_hierarchy_t usb_configuration_hierarchy =
{
  .configuration =
  {
    .bLength             = 0x09,
    .bDescriptorType     = USB_CONFIGURATION_DESCRIPTOR,
    .wTotalLength        = 0x43,
    .bNumInterfaces      = 0x02,
    .bConfigurationValue = 0x01,
    .iConfiguration      = 0x00,
    .bmAttributes        = 0x80,
    .bMaxPower           = 0x3B, // 400 mA
  },

  .interface =
  {
    .bLength             = 0x09,
    .bDescriptorType     = USB_INTERFACE_DESCRIPTOR,
    .bInterfaceNumber    = 0x00,
    .bAlternateSetting   = 0x00,
    .bNumEndpoints       = 0x01,
    .bInterfaceClass     = 0x02,
    .bInterfaceSubClass  = 0x02,
    .bInterfaceProtocol  = 0x01,
    .iInterface          = 0x00,
  },
  
	.headerfunction =
	{
		.bLength              = 0x05,
		.bDescriptortype      = 0x24,
		.bDescriptorsubtype   = 0x00,
		.bcdCDC               = 0x0110,
	},
	
	.acm =
	{
		.bLength              = 0x04,
		.bDescriptortype      = 0x24,
		.bDescriptorsubtype   = 0x02,
		.bmCapabilities       = 0x0F,	
	},
	
	.unionfunction =
	{
		.bLength              = 0x05,
		.bDescriptortype      = 0x24,
		.bDescriptorsubtype   = 0x06,
		.bControlInterface    = 0x00,
		.bSubordinateInterface0  = 0x01,
	},
	
	.callmanagement = 
	{
		.bLength              = 0x05,
		.bDescriptortype      = 0x24,
		.bDescriptorsubtype   = 0x01,
		.bmCapabilities       = 0x03,
		.bDataInterface       = 0x01,
	},
	
	.notification = 
	{
		.bLength                 = 0x07,
		.bDescriptortype         = USB_ENDPOINT_DESCRIPTOR,
	  .bEndpointAddress         = 0x80|3,
		.bmAttributes            = 0x03,
		.wMaxPacketSize          = 0x40,
		.bInterval               = 0xFF,
	},
	
  .datainterface =
  {
    .bLength             = sizeof(usb_datainterface_descriptor_t),
    .bDescriptorType     = 4,
		.bInterfaceNumber    = 0x01,
		.bAlternateSetting   = 0x00,
		.bNumEndpoints       = 0x02,
		.bInterfaceClass     = 0x0A,
    .bInterfaceSubClass  = 0x00,
    .bInterfaceProtocol  = 0xFE,
		.iInterface          = 0x00,
  },
	

  .ep_in =
  {
    .bLength             = 0x07,
    .bDescriptorType     = USB_ENDPOINT_DESCRIPTOR,
    .bEndpointAddress    = USB_IN_ENDPOINT|1,
    .bmAttributes        = 2,
    .wMaxPacketSize      = 0x40,
    .bInterval           = 0x01,
  },

  .ep_out =
  {
    .bLength             = 0x07,
    .bDescriptorType     = USB_ENDPOINT_DESCRIPTOR,
    .bEndpointAddress    = USB_OUT_ENDPOINT |2,
    .bmAttributes        = 2,
    .wMaxPacketSize      = 0x40,
    .bInterval           = 0,
  },
};

__attribute__((aligned (4))) uint8_t usb_hid_report_descriptor[33] =
{
  0x06, 0x00, 0xff,  // Usage Page (Vendor Defined 0xFF00)
  0x09, 0x01,        // Usage (0x01)
  0xa1, 0x01,        // Collection (Application)
  0x15, 0x00,        //   Logical Minimum (0)
  0x26, 0xff, 0x00,  //   Logical Maximum (255)
  0x75, 0x08,        //   Report Size (8)
  0x95, 0x40,        //   Report Count (64)
  0x09, 0x01,        //   Usage (0x01)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x95, 0x40,        //   Report Count (64)
  0x09, 0x01,        //   Usage (0x01)
  0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  0x95, 0x01,        //   Report Count (1)
  0x09, 0x01,        //   Usage (0x01)
  0xb1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  0xc0,              // End Collection
};

__attribute__((aligned (4))) usb_string_descriptor_zero_t usb_string_descriptor_zero =
{
  .bLength               = sizeof(usb_string_descriptor_zero_t),
  .bDescriptorType       = USB_STRING_DESCRIPTOR,
  .wLANGID               = 0x0409, // English (United States)
};

char *usb_strings[] =
{
  [USB_STR_MANUFACTURER]  = "RICH CHA$E",
  [USB_STR_PRODUCT]       = "Data Gateway",
  [USB_STR_SERIAL_NUMBER] = "DGW-123456",
  [USB_STR_CONFIGURATION] = "Main Configuration",
  [USB_STR_INTERFACE]     = "Main Interface",
};

__attribute__((aligned (4))) uint8_t usb_string_descriptor_buffer[64];

