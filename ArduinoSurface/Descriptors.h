/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this 
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in 
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting 
  documentation, and that the name of the author not be used in 
  advertising or publicity pertaining to distribution of the 
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for Descriptors.c.
 */
 
#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include "LUFA/Drivers/USB/USB.h"
		#include "LUFA/Drivers/USB/Class/HIDClass.h"

		#include <avr/pgmspace.h>

	/* Type Defines: */
	
		/** Type define for the surface HID report structure, for creating and sending HID reports to the host PC.
		 *  This mirrors the layout described to the host in the HID report descriptor, in Descriptors.c.
		 */
		typedef struct
		{
			uint8_t ReportId;
			uint8_t TipSwitch;
			uint8_t ContactId; 
			int16_t  X; /**< Current absolute touch X position, as a signed 16-bit integer */
			int16_t  Y; /**< Current absolute touch Y position, as a signed 16-bit integer */
			int16_t  ScanTime; 
			uint8_t ContactCount; 
		} ATTR_PACKED USB_SurfaceReport_Data_t;
		#define SURFACE_REPORT_SIZE 9		
		
		typedef struct
		{
			uint8_t ReportId; 
			uint8_t MaximumContactCount;
		} ATTR_PACKED USB_SurfaceReport_Feature_t;
		
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;
			USB_Descriptor_Interface_t            HID_Interface;
			USB_HID_Descriptor_HID_t              HID_SurfaceHID;
	        USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;
		} USB_Descriptor_Configuration_t;
					
	/* Macros: */
		/** Endpoint number of the Surface HID reporting IN endpoint. */
		#define SURFACE_EPNUM               (ENDPOINT_DIR_IN | 1)
		
		/** Size in bytes of the Surface HID reporting IN endpoint. */
		#define SURFACE_EPSIZE              sizeof(USB_SurfaceReport_Data_t)

        /** Descriptor header type value, to indicate a HID class HID Touch Quality Assurance Blob. */
        #define DTYPE_Touch_Blob              0xC5

#endif
