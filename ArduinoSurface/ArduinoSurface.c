/*
 LUFA Library
 Copyright (C) Dean Camera, 2012.
 
 dean [at] fourwalledcubicle [dot] com
 www.lufa-lib.org
 */

/*
 Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)
 
 Permission to use, copy, modify, distribute, and sell this
 software and its documentation for any purpose is hereby granted
 without fee, provided that the above copyright notice appear in
 all copies and that both that the copyright notice and this
 permission notice and warranty disclaimer appear in supporting
 documentation, and that the name of the author not be used in
 advertising or publicity pertaining to distribution of the
 software without specific, written prior permission.
 
 The author disclaims all warranties with regard to this
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
 *  Main source file for the Joystick demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#include "ArduinoSurface.h"

/** Circular buffer to hold data from the serial port before it is sent to the host. */
RingBuff_t USARTtoUSB_Buffer;

USB_SurfaceReport_Data_t surfaceReport = { 0, 0, 0,0,0,0,0,0,0,0,0,0 };
USB_SurfaceReport_Feature_t surfaceFeatureReport;

uint8_t PrevSurfaceHIDReportBuffer[sizeof(USB_SurfaceReport_Data_t)];

USB_ClassInfo_HID_Device_t Surface_HID_Interface = {
    .Config = {
	.InterfaceNumber              = 0,

	.ReportINEndpoint             =
		{
			.Address              = SURFACE_EPNUM,
			.Size                 = SURFACE_EPSIZE,
			.Banks                = 1,
		},

	.PrevReportINBuffer           = PrevSurfaceHIDReportBuffer,
	.PrevReportINBufferSize       = sizeof(PrevSurfaceHIDReportBuffer),
    },
};

#define LED_ON_TICKS 2000	/* Number of ticks to leave LEDs on */
volatile int led1_ticks = 0, led2_ticks = 0;

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
    SetupHardware();

    RingBuffer_InitBuffer(&USARTtoUSB_Buffer);

    sei();

    for (;;) 
    {
		HID_Device_USBTask(&Surface_HID_Interface);
		USB_USBTask();
	
		/* Turn off the Tx LED when the tick count reaches zero */
		if (led1_ticks) 
		{
			led1_ticks--;
			if (led1_ticks == 0) 
			{
				LEDs_TurnOffLEDs(LEDS_LED1);
			}
		}
		
		/* Turn off the Rx LED when the tick count reaches zero */
		if (led2_ticks) 
		{
			led2_ticks--;
			if (led2_ticks == 0) 
			{
				LEDs_TurnOffLEDs(LEDS_LED2);
			}
		}
    }
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Hardware Initialization */
    Serial_Init(115200, true);
    LEDs_Init();
    USB_Init();

    UCSR1B = ((1 << RXCIE1) | (1 << TXEN1) | (1 << RXEN1));
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	//LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
    HID_Device_ConfigureEndpoints(&Surface_HID_Interface);

    USB_Device_EnableSOFEvents();
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	HID_Device_ProcessControlRequest(&Surface_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
    HID_Device_MillisecondElapsed(&Surface_HID_Interface);
}

const uint8_t PROGMEM TouchBlob[] =
{
	0xfc, 0x28, 0xfe, 0x84, 0x40, 0xcb, 0x9a, 0x87, 0x0d, 0xbe, 0x57, 0x3c, 0xb6, 0x70, 0x09, 0x88, 0x07, 0x97, 0x2d, 0x2b, 0xe3, 0x38, 0x34, 0xb6, 0x6c, 0xed, 0xb0, 0xf7, 0xe5, 0x9c, 0xf6, 0xc2, 0x2e, 0x84, 0x1b, 0xe8, 0xb4, 0x51, 0x78, 0x43, 0x1f, 0x28, 0x4b, 0x7c, 0x2d, 0x53, 0xaf, 0xfc, 0x47, 0x70, 0x1b, 0x59, 0x6f, 0x74, 0x43, 0xc4, 0xf3, 0x47, 0x18, 0x53, 0x1a, 0xa2, 0xa1, 0x71, 0xc7, 0x95, 0x0e, 0x31, 0x55, 0x21, 0xd3, 0xb5, 0x1e, 0xe9, 0x0c, 0xba, 0xec, 0xb8, 0x89, 0x19, 0x3e, 0xb3, 0xaf, 0x75, 0x81, 0x9d, 0x53, 0xb9, 0x41, 0x57, 0xf4, 0x6d, 0x39, 0x25, 0x29, 0x7c, 0x87, 0xd9, 0xb4, 0x98, 0x45, 0x7d, 0xa7, 0x26, 0x9c, 0x65, 0x3b, 0x85, 0x68, 0x89, 0xd7, 0x3b, 0xbd, 0xff, 0x14, 0x67, 0xf2, 0x2b, 0xf0, 0x2a, 0x41, 0x54, 0xf0, 0xfd, 0x2c, 0x66, 0x7c, 0xf8, 0xc0, 0x8f, 0x33, 0x13, 0x03, 0xf1, 0xd3, 0xc1, 0x0b, 0x89, 0xd9, 0x1b, 0x62, 0xcd, 0x51, 0xb7, 0x80, 0xb8, 0xaf, 0x3a, 0x10, 0xc1, 0x8a, 0x5b, 0xe8, 0x8a, 0x56, 0xf0, 0x8c, 0xaa, 0xfa, 0x35, 0xe9, 0x42, 0xc4, 0xd8, 0x55, 0xc3, 0x38, 0xcc, 0x2b, 0x53, 0x5c, 0x69, 0x52, 0xd5, 0xc8, 0x73, 0x02, 0x38, 0x7c, 0x73, 0xb6, 0x41, 0xe7, 0xff, 0x05, 0xd8, 0x2b, 0x79, 0x9a, 0xe2, 0x34, 0x60, 0x8f, 0xa3, 0x32, 0x1f, 0x09, 0x78, 0x62, 0xbc, 0x80, 0xe3, 0x0f, 0xbd, 0x65, 0x20, 0x08, 0x13, 0xc1, 0xe2, 0xee, 0x53, 0x2d, 0x86, 0x7e, 0xa7, 0x5a, 0xc5, 0xd3, 0x7d, 0x98, 0xbe, 0x31, 0x48, 0x1f, 0xfb, 0xda, 0xaf, 0xa2, 0xa8, 0x6a, 0x89, 0xd6, 0xbf, 0xf2, 0xd3, 0x32, 0x2a, 0x9a, 0xe4, 0xcf, 0x17, 0xb7, 0xb8, 0xf4, 0xe1, 0x33, 0x08, 0x24, 0x8b, 0xc4, 0x43, 0xa5, 0xe5, 0x24, 0xc2
};

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either REPORT_ITEM_TYPE_In or REPORT_ITEM_TYPE_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent
 *
 *  \return Boolean true to force the sending of the report, false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(
    USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
    uint8_t* const ReportID,
    const uint8_t ReportType,
    void* ReportData,
    uint16_t* const ReportSize)
{
	if (ReportData != NULL && ReportSize != NULL)
	{
		if (ReportType == HID_REPORT_ITEM_Feature && *ReportID == 0x44)
		{
			uint8_t *reportp = ReportData;
			uint8_t id = *ReportID;

			*reportp++ = id;			

			memcpy(reportp, TouchBlob,
					       sizeof(TouchBlob));

			*ReportSize = sizeof(TouchBlob) + 1;
			return true;
		}
		else if (ReportType == HID_REPORT_ITEM_Feature)
		{
			USB_SurfaceReport_Feature_t *reportp = (USB_SurfaceReport_Feature_t*)ReportData;
			uint8_t maximumContactCount;
			maximumContactCount = 10;
			uint8_t id = *ReportID;

			reportp->ReportId = id;			
			reportp->MaximumContactCount = maximumContactCount;
			
			*ReportSize = sizeof(USB_SurfaceReport_Feature_t);
			return true;
		}
		else
		{
			USB_SurfaceReport_Data_t *reportp = (USB_SurfaceReport_Data_t*)ReportData;
		
			RingBuff_Count_t BufferCount = RingBuffer_GetCount(&USARTtoUSB_Buffer);
			uint8_t reportId = 1;		
			if (BufferCount >= SURFACE_REPORT_SIZE) 
			{
				uint8_t *ptr = ReportData;
				uint8_t TipSwitch = RingBuffer_Remove(&USARTtoUSB_Buffer);
				uint8_t ContactId = RingBuffer_Remove(&USARTtoUSB_Buffer);
				uint16_t  X = RingBuffer_Remove(&USARTtoUSB_Buffer) | (RingBuffer_Remove(&USARTtoUSB_Buffer) << 8);
				uint16_t  Y = RingBuffer_Remove(&USARTtoUSB_Buffer) | (RingBuffer_Remove(&USARTtoUSB_Buffer) << 8);
				uint16_t  ScanTime  = RingBuffer_Remove(&USARTtoUSB_Buffer) | (RingBuffer_Remove(&USARTtoUSB_Buffer) << 8);
				uint8_t ContactCount = RingBuffer_Remove(&USARTtoUSB_Buffer);
/*				
				*ptr++ = reportId;
				*ptr++ = TipSwitch;
				*ptr++ = ContactId;
				*ptr++ = (uint8_t)(X & 0xff);
				*ptr++ = (uint8_t)((X >> 8) & 0xff);
				*ptr++ = (uint8_t)(Y & 0xff);
				*ptr++ = (uint8_t)((Y >> 8) & 0xff);				
				*ptr++ = (uint8_t)(ScanTime & 0xff);
				*ptr++ = (uint8_t)((ScanTime >> 8) & 0xff);
				*ptr++ = ContactCount;
				
				*/
				reportp->ReportId = reportId;
				reportp->TipSwitch = (TipSwitch > 0) ? 0xff : 0 ;
				reportp->ContactId = ContactId;
				reportp->ScanTime = ScanTime;
				reportp->X = X;
				reportp->Y = Y;
				reportp->ContactCount = ContactCount;
				
				LEDs_TurnOnLEDs(LEDS_LED1);
				led1_ticks = LED_ON_TICKS;
			}
			else
			{
				
				reportp->ReportId = reportId;
				reportp->TipSwitch = 0;
				reportp->ContactId = 0;
				reportp->ScanTime = 0;
				reportp->X = 0;
				reportp->Y = 0;
				reportp->ContactCount = 0;
				
				*ReportSize = 0;
				return false;
			}
			*ReportSize = sizeof(USB_SurfaceReport_Data_t);
			return true;
		}
		*ReportSize = 0;
    }
    return false;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either REPORT_ITEM_TYPE_Out or REPORT_ITEM_TYPE_Feature
 *  \param[in] ReportData  Pointer to a buffer where the created report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
    /* Not used but must be present */
}

/** ISR to manage the reception of data from the serial port, placing received bytes into a circular buffer
 *  for later transmission to the host.
 */
ISR(USART1_RX_vect, ISR_BLOCK)
{
    uint8_t ReceivedByte = UDR1;

    if ((USB_DeviceState == DEVICE_STATE_Configured) &&
	    !RingBuffer_IsFull(&USARTtoUSB_Buffer)) {
	RingBuffer_Insert(&USARTtoUSB_Buffer, ReceivedByte);
    }
}
