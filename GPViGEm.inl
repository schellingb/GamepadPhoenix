/*
MIT License

Copyright (c) 2017-2023 Nefarius Software Solutions e.U. and Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//#define VIGEM_ASYNC_FUNCTIONS
//#define VIGEM_DS4

//
// WinAPI
// 
//#include <Windows.h>
#include <SetupAPI.h>
//#include <initguid.h>
//#include <strsafe.h>

//
// Driver shared
// 
#include <winioctl.h>

//
// STL
// 
//#include <cstdlib>
//#include <climits>
//#include <thread>
//#include <functional>
//#include <string>
//#include <iostream>

namespace GPViGEm {


namespace std { typedef size_t size; };


//
// Driver shared
// 
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//#include "ViGEm/Common.h"
/*
MIT License

Copyright (c) 2017-2023 Nefarius Software Solutions e.U. and Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#pragma once

//
// Represents the desired target type for the emulated device.
//  
typedef enum _VIGEM_TARGET_TYPE
{
    // 
    // Microsoft Xbox 360 Controller (wired)
    // 
    Xbox360Wired = 0,
#ifdef VIGEM_DS4
    //
    // Sony DualShock 4 (wired)
    // 
    DualShock4Wired = 2 // NOTE: 1 skipped on purpose to maintain compatibility
#endif // VIGEM_DS4

} VIGEM_TARGET_TYPE, *PVIGEM_TARGET_TYPE;

//
// Possible XUSB report buttons.
// 
typedef enum _XUSB_BUTTON
{
    XUSB_GAMEPAD_DPAD_UP            = 0x0001,
    XUSB_GAMEPAD_DPAD_DOWN          = 0x0002,
    XUSB_GAMEPAD_DPAD_LEFT          = 0x0004,
    XUSB_GAMEPAD_DPAD_RIGHT         = 0x0008,
    XUSB_GAMEPAD_START              = 0x0010,
    XUSB_GAMEPAD_BACK               = 0x0020,
    XUSB_GAMEPAD_LEFT_THUMB         = 0x0040,
    XUSB_GAMEPAD_RIGHT_THUMB        = 0x0080,
    XUSB_GAMEPAD_LEFT_SHOULDER      = 0x0100,
    XUSB_GAMEPAD_RIGHT_SHOULDER     = 0x0200,
    XUSB_GAMEPAD_GUIDE              = 0x0400,
    XUSB_GAMEPAD_A                  = 0x1000,
    XUSB_GAMEPAD_B                  = 0x2000,
    XUSB_GAMEPAD_X                  = 0x4000,
    XUSB_GAMEPAD_Y                  = 0x8000

} XUSB_BUTTON, *PXUSB_BUTTON;

//
// Represents an XINPUT_GAMEPAD-compatible report structure.
// 
typedef struct _XUSB_REPORT
{
    USHORT wButtons;
    BYTE bLeftTrigger;
    BYTE bRightTrigger;
    SHORT sThumbLX;
    SHORT sThumbLY;
    SHORT sThumbRX;
    SHORT sThumbRY;

} XUSB_REPORT, *PXUSB_REPORT;

//
// Initializes a _XUSB_REPORT structure.
// 
VOID FORCEINLINE XUSB_REPORT_INIT(
    _Out_ PXUSB_REPORT Report
)
{
    RtlZeroMemory(Report, sizeof(XUSB_REPORT));
}

//
// Values set by output reports on XINPUT_GAMEPAD
//
typedef struct _XUSB_OUTPUT_DATA
{
    UCHAR LargeMotor;
    UCHAR SmallMotor;
    UCHAR LedNumber;
} XUSB_OUTPUT_DATA, *PXUSB_OUTPUT_DATA;

#ifdef VIGEM_DS4
//
// The color value (RGB) of a DualShock 4 Lightbar
// 
typedef struct _DS4_LIGHTBAR_COLOR
{
    //
    // Red part of the Lightbar (0-255).
    //
    UCHAR Red;

    //
    // Green part of the Lightbar (0-255).
    //
    UCHAR Green;

    //
    // Blue part of the Lightbar (0-255).
    //
    UCHAR Blue;

} DS4_LIGHTBAR_COLOR, *PDS4_LIGHTBAR_COLOR;

//
// DualShock 4 digital buttons
// 
typedef enum _DS4_BUTTONS
{
    DS4_BUTTON_THUMB_RIGHT      = 1 << 15,
    DS4_BUTTON_THUMB_LEFT       = 1 << 14,
    DS4_BUTTON_OPTIONS          = 1 << 13,
    DS4_BUTTON_SHARE            = 1 << 12,
    DS4_BUTTON_TRIGGER_RIGHT    = 1 << 11,
    DS4_BUTTON_TRIGGER_LEFT     = 1 << 10,
    DS4_BUTTON_SHOULDER_RIGHT   = 1 << 9,
    DS4_BUTTON_SHOULDER_LEFT    = 1 << 8,
    DS4_BUTTON_TRIANGLE         = 1 << 7,
    DS4_BUTTON_CIRCLE           = 1 << 6,
    DS4_BUTTON_CROSS            = 1 << 5,
    DS4_BUTTON_SQUARE           = 1 << 4

} DS4_BUTTONS, *PDS4_BUTTONS;

//
// DualShock 4 special buttons
// 
typedef enum _DS4_SPECIAL_BUTTONS
{
    DS4_SPECIAL_BUTTON_PS           = 1 << 0,
    DS4_SPECIAL_BUTTON_TOUCHPAD     = 1 << 1

} DS4_SPECIAL_BUTTONS, *PDS4_SPECIAL_BUTTONS;

//
// DualShock 4 directional pad (HAT) values
// 
typedef enum _DS4_DPAD_DIRECTIONS
{
    DS4_BUTTON_DPAD_NONE        = 0x8,
    DS4_BUTTON_DPAD_NORTHWEST   = 0x7,
    DS4_BUTTON_DPAD_WEST        = 0x6,
    DS4_BUTTON_DPAD_SOUTHWEST   = 0x5,
    DS4_BUTTON_DPAD_SOUTH       = 0x4,
    DS4_BUTTON_DPAD_SOUTHEAST   = 0x3,
    DS4_BUTTON_DPAD_EAST        = 0x2,
    DS4_BUTTON_DPAD_NORTHEAST   = 0x1,
    DS4_BUTTON_DPAD_NORTH       = 0x0

} DS4_DPAD_DIRECTIONS, *PDS4_DPAD_DIRECTIONS;

//
// DualShock 4 HID Input report
// 
typedef struct _DS4_REPORT
{
    BYTE bThumbLX;
    BYTE bThumbLY;
    BYTE bThumbRX;
    BYTE bThumbRY;
    USHORT wButtons;
    BYTE bSpecial;
    BYTE bTriggerL;
    BYTE bTriggerR;

} DS4_REPORT, *PDS4_REPORT;

//
// Sets the current state of the D-PAD on a DualShock 4 report.
// 
VOID FORCEINLINE DS4_SET_DPAD(
    _Out_ PDS4_REPORT Report,
    _In_ DS4_DPAD_DIRECTIONS Dpad
)
{
    Report->wButtons &= ~0xF;
    Report->wButtons |= (USHORT)Dpad;
}

VOID FORCEINLINE DS4_REPORT_INIT(
    _Out_ PDS4_REPORT Report
)
{
    RtlZeroMemory(Report, sizeof(DS4_REPORT));

    Report->bThumbLX = 0x80;
    Report->bThumbLY = 0x80;
    Report->bThumbRX = 0x80;
    Report->bThumbRY = 0x80;

    DS4_SET_DPAD(Report, DS4_BUTTON_DPAD_NONE);
}

//
// Values set by output reports on DualShock 4
//
typedef struct _DS4_OUTPUT_DATA
{
    UCHAR LargeMotor;
    UCHAR SmallMotor;
    DS4_LIGHTBAR_COLOR LightbarColor;
} DS4_OUTPUT_DATA, *PDS4_OUTPUT_DATA;

#include <pshpack1.h> // pack structs tightly
//
// DualShock 4 HID Touchpad structure
//
typedef struct _DS4_TOUCH
{
    BYTE bPacketCounter;    // timestamp / packet counter associated with touch event
    BYTE bIsUpTrackingNum1; // 0 means down; active low
                            // unique to each finger down, so for a lift and repress the value is incremented
    BYTE bTouchData1[3];    // Two 12 bits values (for X and Y) 
                            // middle byte holds last 4 bits of X and the starting 4 bits of Y
    BYTE bIsUpTrackingNum2; // second touch data immediately follows data of first touch 
    BYTE bTouchData2[3];    // resolution is 1920x943
} DS4_TOUCH, * PDS4_TOUCH;

//
// DualShock 4 v1 complete HID Input report
//
typedef struct _DS4_REPORT_EX
{
	union
	{
		struct
		{
			BYTE bThumbLX;
			BYTE bThumbLY;
			BYTE bThumbRX;
			BYTE bThumbRY;
			USHORT wButtons;
			BYTE bSpecial;
			BYTE bTriggerL;
			BYTE bTriggerR;
			USHORT wTimestamp;
			BYTE bBatteryLvl;
			SHORT wGyroX;
			SHORT wGyroY;
			SHORT wGyroZ;
			SHORT wAccelX;
			SHORT wAccelY;
			SHORT wAccelZ;
			BYTE _bUnknown1[5];
			BYTE bBatteryLvlSpecial;
			// really should have a enum to show everything that this can represent (USB charging, battery level; EXT, headset, microphone connected)
			BYTE _bUnknown2[2];
			BYTE bTouchPacketsN; // 0x00 to 0x03 (USB max)
			DS4_TOUCH sCurrentTouch;
			DS4_TOUCH sPreviousTouch[2];
		} Report;

		UCHAR ReportBuffer[63];
	};
} DS4_REPORT_EX, *PDS4_REPORT_EX;

typedef struct _DS4_OUTPUT_BUFFER
{
	//
	// The output report buffer
	// 
	_Out_ UCHAR Buffer[64];
	
} DS4_OUTPUT_BUFFER, *PDS4_OUTPUT_BUFFER;

#include <poppack.h>
#endif // VIGEM_DS4

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//#include "ViGEm/km/BusShared.h"
/*
MIT License

Copyright (c) 2016-2019 Nefarius Software Solutions e.U. and Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


//
// GUID identifying the bus device. Used by client library to detect and communicate.
// 
// IMPORTANT: make sure to change this value if you fork it or introduce 
//				breaking changes!
// 
// {96E42B22-F5E9-42F8-B043-ED0F932F014F}
//DEFINE_GUID(GUID_DEVINTERFACE_BUSENUM_VIGEM,
//    0x96E42B22, 0xF5E9, 0x42F8, 0xB0, 0x43, 0xED, 0x0F, 0x93, 0x2F, 0x01, 0x4F);
const GUID /*DECLSPEC_SELECTANY*/ GUID_DEVINTERFACE_BUSENUM_VIGEM
                = { 0x96E42B22, 0xF5E9, 0x42F8, { 0xB0, 0x43, 0xED, 0x0F, 0x93, 0x2F, 0x01, 0x4F } };

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//#include "ViGEm/Common.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

//
// Common version for user-mode library and driver compatibility
// 
// On initialization, the user-mode library has this number embedded
// and sends it to the bus on its enumeration. The bus compares this
// number to the one it was compiled with. If they match, the bus
// access is permitted and success reported. If they mismatch, an
// error is reported and the user-mode library skips this instance.
// 
#define VIGEM_COMMON_VERSION            0x0001

#define FILE_DEVICE_BUSENUM             FILE_DEVICE_BUS_EXTENDER
#define BUSENUM_IOCTL(_index_)          CTL_CODE(FILE_DEVICE_BUSENUM, _index_, METHOD_BUFFERED, FILE_READ_DATA)
#define BUSENUM_W_IOCTL(_index_)        CTL_CODE(FILE_DEVICE_BUSENUM, _index_, METHOD_BUFFERED, FILE_WRITE_DATA)
#define BUSENUM_R_IOCTL(_index_)        CTL_CODE(FILE_DEVICE_BUSENUM, _index_, METHOD_BUFFERED, FILE_READ_DATA)
#define BUSENUM_RW_IOCTL(_index_)       CTL_CODE(FILE_DEVICE_BUSENUM, _index_, METHOD_BUFFERED, FILE_WRITE_DATA | FILE_READ_DATA)

#define IOCTL_VIGEM_BASE 0x801

// 
// IO control codes
// 
#define IOCTL_VIGEM_PLUGIN_TARGET           BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x000)
#define IOCTL_VIGEM_UNPLUG_TARGET           BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x001)
#define IOCTL_VIGEM_CHECK_VERSION           BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x002)
#define IOCTL_VIGEM_WAIT_DEVICE_READY       BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x003)

#define IOCTL_XUSB_REQUEST_NOTIFICATION     BUSENUM_RW_IOCTL(IOCTL_VIGEM_BASE + 0x200)
#define IOCTL_XUSB_SUBMIT_REPORT            BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x201)
#ifdef VIGEM_DS4
#define IOCTL_DS4_SUBMIT_REPORT             BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x202)
#define IOCTL_DS4_REQUEST_NOTIFICATION      BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x203)
#endif // VIGEM_DS4
//#define IOCTL_XGIP_SUBMIT_REPORT        BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x204)
//#define IOCTL_XGIP_SUBMIT_INTERRUPT     BUSENUM_W_IOCTL (IOCTL_VIGEM_BASE + 0x205)
#define IOCTL_XUSB_GET_USER_INDEX           BUSENUM_RW_IOCTL(IOCTL_VIGEM_BASE + 0x206)
#ifdef VIGEM_DS4
#define IOCTL_DS4_AWAIT_OUTPUT_AVAILABLE    BUSENUM_RW_IOCTL(IOCTL_VIGEM_BASE + 0x207)
#endif // VIGEM_DS4


//
//  Data structure used in PlugIn and UnPlug ioctls
//

#pragma region Plugin

//
// Data structure used in IOCTL_VIGEM_PLUGIN_TARGET requests.
// 
typedef struct _VIGEM_PLUGIN_TARGET
{
    //
    // sizeof (struct _BUSENUM_HARDWARE)
    //
    IN ULONG Size;

    //
    // Serial number of target device.
    // 
    IN ULONG SerialNo;

    // 
    // Type of the target device to emulate.
    // 
    VIGEM_TARGET_TYPE TargetType;

    //
    // If set, the vendor ID the emulated device is reporting
    // 
    USHORT VendorId;

    //
    // If set, the product ID the emulated device is reporting
    // 
    USHORT ProductId;

} VIGEM_PLUGIN_TARGET, *PVIGEM_PLUGIN_TARGET;

//
// Initializes a VIGEM_PLUGIN_TARGET structure.
// 
VOID FORCEINLINE VIGEM_PLUGIN_TARGET_INIT(
    _Out_ PVIGEM_PLUGIN_TARGET PlugIn,
          _In_ ULONG SerialNo,
          _In_ VIGEM_TARGET_TYPE TargetType
)
{
    RtlZeroMemory(PlugIn, sizeof(VIGEM_PLUGIN_TARGET));

    PlugIn->Size = sizeof(VIGEM_PLUGIN_TARGET);
    PlugIn->SerialNo = SerialNo;
    PlugIn->TargetType = TargetType;
}

#pragma endregion 

#pragma region Unplug

//
// Data structure used in IOCTL_VIGEM_UNPLUG_TARGET requests.
// 
typedef struct _VIGEM_UNPLUG_TARGET
{
    //
    // sizeof (struct _REMOVE_HARDWARE)
    //
    IN ULONG Size;

    //
    // Serial number of target device.
    // 
    ULONG SerialNo;

} VIGEM_UNPLUG_TARGET, *PVIGEM_UNPLUG_TARGET;

//
// Initializes a VIGEM_UNPLUG_TARGET structure.
// 
VOID FORCEINLINE VIGEM_UNPLUG_TARGET_INIT(
    _Out_ PVIGEM_UNPLUG_TARGET UnPlug,
          _In_ ULONG SerialNo
)
{
    RtlZeroMemory(UnPlug, sizeof(VIGEM_UNPLUG_TARGET));

    UnPlug->Size = sizeof(VIGEM_UNPLUG_TARGET);
    UnPlug->SerialNo = SerialNo;
}

#pragma endregion

#pragma region Check version

typedef struct _VIGEM_CHECK_VERSION
{
    IN ULONG Size;

    IN ULONG Version;

} VIGEM_CHECK_VERSION, *PVIGEM_CHECK_VERSION;

VOID FORCEINLINE VIGEM_CHECK_VERSION_INIT(
    _Out_ PVIGEM_CHECK_VERSION CheckVersion,
    _In_ ULONG Version
)
{
    RtlZeroMemory(CheckVersion, sizeof(VIGEM_CHECK_VERSION));

    CheckVersion->Size = sizeof(VIGEM_CHECK_VERSION);
    CheckVersion->Version = Version;
}

#pragma endregion

#pragma region Wait device ready

typedef struct _VIGEM_WAIT_DEVICE_READY
{
    IN ULONG Size;

    IN ULONG SerialNo;

} VIGEM_WAIT_DEVICE_READY, * PVIGEM_WAIT_DEVICE_READY;

VOID FORCEINLINE VIGEM_WAIT_DEVICE_READY_INIT(
    _Out_ PVIGEM_WAIT_DEVICE_READY WaitReady,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(WaitReady, sizeof(VIGEM_WAIT_DEVICE_READY));

    WaitReady->Size = sizeof(VIGEM_WAIT_DEVICE_READY);
    WaitReady->SerialNo = SerialNo;
}

#pragma endregion 

#pragma region XUSB (aka Xbox 360 device) section

//
// Data structure used in IOCTL_XUSB_REQUEST_NOTIFICATION requests.
// 
typedef struct _XUSB_REQUEST_NOTIFICATION
{
    //
    // sizeof(struct _XUSB_REQUEST_NOTIFICATION)
    // 
    ULONG Size;

    //
    // Serial number of target device.
    // 
    ULONG SerialNo;

    //
    // Vibration intensity value of the large motor (0-255).
    // 
    UCHAR LargeMotor;

    //
    // Vibration intensity value of the small motor (0-255).
    // 
    UCHAR SmallMotor;

    //
    // Index number of the slot/LED that XUSB.sys has assigned.
    // 
    UCHAR LedNumber;

} XUSB_REQUEST_NOTIFICATION, *PXUSB_REQUEST_NOTIFICATION;

//
// Initializes a XUSB_REQUEST_NOTIFICATION structure.
// 
VOID FORCEINLINE XUSB_REQUEST_NOTIFICATION_INIT(
    _Out_ PXUSB_REQUEST_NOTIFICATION Request,
          _In_ ULONG SerialNo
)
{
    RtlZeroMemory(Request, sizeof(XUSB_REQUEST_NOTIFICATION));

    Request->Size = sizeof(XUSB_REQUEST_NOTIFICATION);
    Request->SerialNo = SerialNo;
}

//
// Data structure used in IOCTL_XUSB_SUBMIT_REPORT requests.
// 
typedef struct _XUSB_SUBMIT_REPORT
{
    //
    // sizeof(struct _XUSB_SUBMIT_REPORT)
    // 
    ULONG Size;

    //
    // Serial number of target device.
    // 
    ULONG SerialNo;

    //
    // Report to submit to the target device.
    // 
    XUSB_REPORT Report;

} XUSB_SUBMIT_REPORT, *PXUSB_SUBMIT_REPORT;

//
// Initializes an XUSB report.
// 
VOID FORCEINLINE XUSB_SUBMIT_REPORT_INIT(
    _Out_ PXUSB_SUBMIT_REPORT Report,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(Report, sizeof(XUSB_SUBMIT_REPORT));

    Report->Size = sizeof(XUSB_SUBMIT_REPORT);
    Report->SerialNo = SerialNo;
}

typedef struct _XUSB_GET_USER_INDEX
{
    //
    // sizeof(struct _XUSB_GET_USER_INDEX)
    // 
    ULONG Size;

    //
    // Serial number of target device.
    // 
    ULONG SerialNo;

    //
    // User index of target device.
    // 
    OUT ULONG UserIndex;

} XUSB_GET_USER_INDEX, *PXUSB_GET_USER_INDEX;

//
// Initializes XUSB_GET_USER_INDEX structure.
// 
VOID FORCEINLINE XUSB_GET_USER_INDEX_INIT(
    _Out_ PXUSB_GET_USER_INDEX GetRequest,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(GetRequest, sizeof(XUSB_GET_USER_INDEX));

    GetRequest->Size = sizeof(XUSB_GET_USER_INDEX);
    GetRequest->SerialNo = SerialNo;
}

#pragma endregion

#ifdef VIGEM_DS4
#pragma region DualShock 4 section

typedef struct _DS4_OUTPUT_REPORT
{
    //
    // Vibration intensity value of the small motor (0-255).
    // 
    UCHAR SmallMotor;

    //
    // Vibration intensity value of the large motor (0-255).
    // 
    UCHAR LargeMotor;

    //
    // Color values of the Lightbar.
    //
    DS4_LIGHTBAR_COLOR LightbarColor;

} DS4_OUTPUT_REPORT, *PDS4_OUTPUT_REPORT;

//
// Data structure used in IOCTL_DS4_REQUEST_NOTIFICATION requests.
// 
typedef struct _DS4_REQUEST_NOTIFICATION
{
    //
    // sizeof(struct _XUSB_REQUEST_NOTIFICATION)
    // 
    ULONG Size;

    //
    // Serial number of target device.
    // 
    ULONG SerialNo;

    //
    // The HID output report
    // 
    DS4_OUTPUT_REPORT Report;

} DS4_REQUEST_NOTIFICATION, *PDS4_REQUEST_NOTIFICATION;

//
// Initializes a DS4_REQUEST_NOTIFICATION structure.
// 
VOID FORCEINLINE DS4_REQUEST_NOTIFICATION_INIT(
    _Out_ PDS4_REQUEST_NOTIFICATION Request,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(Request, sizeof(DS4_REQUEST_NOTIFICATION));

    Request->Size = sizeof(DS4_REQUEST_NOTIFICATION);
    Request->SerialNo = SerialNo;
}

//
// DualShock 4 request data
// 
typedef struct _DS4_SUBMIT_REPORT
{
    //
    // sizeof(struct _DS4_SUBMIT_REPORT)
    // 
    ULONG Size;

    //
    // Serial number of target device.
    // 
    ULONG SerialNo;

    //
    // HID Input report
    // 
    DS4_REPORT Report;

} DS4_SUBMIT_REPORT, *PDS4_SUBMIT_REPORT;

//
// Initializes a DualShock 4 report.
// 
VOID FORCEINLINE DS4_SUBMIT_REPORT_INIT(
    _Out_ PDS4_SUBMIT_REPORT Report,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(Report, sizeof(DS4_SUBMIT_REPORT));

    Report->Size = sizeof(DS4_SUBMIT_REPORT);
    Report->SerialNo = SerialNo;

    DS4_REPORT_INIT(&Report->Report);
}

#include <pshpack1.h>

//
// DualShock 4 extended report request
// 
typedef struct _DS4_SUBMIT_REPORT_EX
{
    //
     // sizeof(struct _DS4_SUBMIT_REPORT_EX)
     // 
    _In_ ULONG Size;

    //
    // Serial number of target device.
    // 
    _In_ ULONG SerialNo;

    //
    // Full size HID report excluding fixed Report ID.
    // 
    _In_ DS4_REPORT_EX Report;

} DS4_SUBMIT_REPORT_EX, * PDS4_SUBMIT_REPORT_EX;

#include <poppack.h>

//
// Initializes a DualShock 4 extended report.
// 
VOID FORCEINLINE DS4_SUBMIT_REPORT_EX_INIT(
    _Out_ PDS4_SUBMIT_REPORT_EX Report,
    _In_ ULONG SerialNo
)
{
    RtlZeroMemory(Report, sizeof(DS4_SUBMIT_REPORT_EX));

    Report->Size = sizeof(DS4_SUBMIT_REPORT_EX);
    Report->SerialNo = SerialNo;
}

#pragma endregion

#pragma region DS4 Await Output

#include <pshpack1.h>

typedef struct _DS4_AWAIT_OUTPUT
{
	//
	// sizeof(struct _DS4_AWAIT_OUTPUT)
	// 
	_In_ ULONG Size;

	//
	// Serial number of target device.
	// 
	_Inout_ ULONG SerialNo;

    //
    // The payload
    // 
    _Out_ DS4_OUTPUT_BUFFER Report;
    
} DS4_AWAIT_OUTPUT, * PDS4_AWAIT_OUTPUT;

#include <poppack.h>

VOID FORCEINLINE DS4_AWAIT_OUTPUT_INIT(
	_Out_ PDS4_AWAIT_OUTPUT Output,
    _In_ ULONG SerialNo
)
{
	RtlZeroMemory(Output, sizeof(DS4_AWAIT_OUTPUT));

	Output->Size = sizeof(DS4_AWAIT_OUTPUT);
    Output->SerialNo = SerialNo;
}

#pragma endregion
#endif // VIGEM_DS4

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//#include "ViGEm/Client.h"
/*
MIT License

Copyright (c) 2017-2023 Nefarius Software Solutions e.U. and Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#ifndef ViGEmClient_h__
#define ViGEmClient_h__

#ifdef __cplusplus
extern "C" {
#endif

//#include "ViGEm/Common.h"

#ifdef VIGEM_DYNAMIC
#ifdef VIGEM_EXPORTS
#define VIGEM_API __declspec(dllexport)
#else
#define VIGEM_API __declspec(dllimport)
#endif
#else
#define VIGEM_API
#endif

#if defined(_MSC_VER)
#define VIGEM_DEPRECATED __declspec(deprecated)
#elif defined(__GNUC__)
#define VIGEM_DEPRECATED __attribute__ ((deprecated))
#endif

	/** Values that represent ViGEm errors */
	typedef enum _VIGEM_ERRORS
	{
		//
		// API succeeded.
		// 
		VIGEM_ERROR_NONE = 0x20000000,
		//
		// A compatible bus driver wasn't found on the system.
		// 
		VIGEM_ERROR_BUS_NOT_FOUND = 0xE0000001,
		//
		// All device slots are occupied, no new device can be spawned.
		// 
		VIGEM_ERROR_NO_FREE_SLOT = 0xE0000002,
		VIGEM_ERROR_INVALID_TARGET = 0xE0000003,
		VIGEM_ERROR_REMOVAL_FAILED = 0xE0000004,
		//
		// An attempt has been made to plug in an already connected device.
		// 
		VIGEM_ERROR_ALREADY_CONNECTED = 0xE0000005,
		//
		// The target device is not initialized.
		// 
		VIGEM_ERROR_TARGET_UNINITIALIZED = 0xE0000006,
		//
		// The target device is not plugged in.
		// 
		VIGEM_ERROR_TARGET_NOT_PLUGGED_IN = 0xE0000007,
		//
		// It's been attempted to communicate with an incompatible driver version.
		// 
		VIGEM_ERROR_BUS_VERSION_MISMATCH = 0xE0000008,
		//
		// Bus driver found but failed to open a handle.
		// 
		VIGEM_ERROR_BUS_ACCESS_FAILED = 0xE0000009,
		VIGEM_ERROR_CALLBACK_ALREADY_REGISTERED = 0xE0000010,
		VIGEM_ERROR_CALLBACK_NOT_FOUND = 0xE0000011,
		VIGEM_ERROR_BUS_ALREADY_CONNECTED = 0xE0000012,
		VIGEM_ERROR_BUS_INVALID_HANDLE = 0xE0000013,
		VIGEM_ERROR_XUSB_USERINDEX_OUT_OF_RANGE = 0xE0000014,
		VIGEM_ERROR_INVALID_PARAMETER = 0xE0000015,
		//
		// The API is not supported by the driver.
		// 
		VIGEM_ERROR_NOT_SUPPORTED = 0xE0000016,
		//
		// An unexpected Win32 API error occurred. Call GetLastError() for details.
		// 
		VIGEM_ERROR_WINAPI = 0xE0000017,
		//
		// The specified timeout has been reached.
		// 
		VIGEM_ERROR_TIMED_OUT = 0xE0000018,
		VIGEM_ERROR_IS_DISPOSING = 0xE0000019,
	} VIGEM_ERROR;

	/**
	 * A macro that defines if the API succeeded
	 *
	 * @author	Benjamin "Nefarius" Höglinger-Stelzer
	 * @date	01.09.2020
	 *
	 * @param 	_val_	The error value.
	 */
#define VIGEM_SUCCESS(_val_) (_val_ == VIGEM_ERROR_NONE)

	 /** Defines an alias representing a driver connection object */
	typedef struct _VIGEM_CLIENT_T *PVIGEM_CLIENT;

	/** Defines an alias representing a target device object */
	typedef struct _VIGEM_TARGET_T *PVIGEM_TARGET;

	typedef _Function_class_(EVT_VIGEM_TARGET_ADD_RESULT)
		VOID CALLBACK
		EVT_VIGEM_TARGET_ADD_RESULT(
			PVIGEM_CLIENT Client,
			PVIGEM_TARGET Target,
			VIGEM_ERROR Result
		);

	typedef EVT_VIGEM_TARGET_ADD_RESULT *PFN_VIGEM_TARGET_ADD_RESULT;

	typedef _Function_class_(EVT_VIGEM_X360_NOTIFICATION)
		VOID CALLBACK
		EVT_VIGEM_X360_NOTIFICATION(
			PVIGEM_CLIENT Client,
			PVIGEM_TARGET Target,
			UCHAR LargeMotor,
			UCHAR SmallMotor,
			UCHAR LedNumber,
			LPVOID UserData
		);

	typedef EVT_VIGEM_X360_NOTIFICATION *PFN_VIGEM_X360_NOTIFICATION;

#ifdef VIGEM_DS4
	typedef _Function_class_(EVT_VIGEM_DS4_NOTIFICATION)
		VOID CALLBACK
		EVT_VIGEM_DS4_NOTIFICATION(
			PVIGEM_CLIENT Client,
			PVIGEM_TARGET Target,
			UCHAR LargeMotor,
			UCHAR SmallMotor,
			DS4_LIGHTBAR_COLOR LightbarColor,
			LPVOID UserData
		);

	typedef EVT_VIGEM_DS4_NOTIFICATION *PFN_VIGEM_DS4_NOTIFICATION;
#endif // VIGEM_DS4

	/**
	 *  Allocates an object representing a driver connection
	 *
	 * @author	Benjamin "Nefarius" Höglinger-Stelzer
	 * @date	28.08.2017
	 *
	 * @returns	A PVIGEM_CLIENT object.
	 */
	VIGEM_API PVIGEM_CLIENT vigem_alloc(void);

	/**
	 * Frees up memory used by the driver connection object
	 *
	 * @author	Benjamin "Nefarius" Höglinger-Stelzer
	 * @date	28.08.2017
	 *
	 * @param 	vigem	The PVIGEM_CLIENT object.
	 */
	VIGEM_API void vigem_free(
		PVIGEM_CLIENT vigem
	);

	/**
	 * Initializes the driver object and establishes a connection to the emulation bus
	 *          driver. Returns an error if no compatible bus device has been found.
	 *
	 * @author	Benjamin "Nefarius" Höglinger-Stelzer
	 * @date	28.08.2017
	 *
	 * @param 	vigem	The PVIGEM_CLIENT object.
	 *
	 * @returns	A VIGEM_ERROR.
	 */
	VIGEM_API VIGEM_ERROR vigem_connect(
		PVIGEM_CLIENT vigem
	);

	/**
	 * Disconnects from the bus device and resets the driver object state. The driver object
	 *           may be reused again after calling this function. When called, all targets which may
	 *           still be connected will be destroyed automatically. Be aware, that allocated target
	 *           objects won't be automatically freed, this has to be taken care of by the caller.
	 *
	 * @author	Benjamin "Nefarius" Höglinger-Stelzer
	 * @date	28.08.2017
	 *
	 * @param 	vigem	The PVIGEM_CLIENT object.
	 */
	VIGEM_API void vigem_disconnect(
		PVIGEM_CLIENT vigem
	);

	/**
	 * A useful utility function to check if pre 1.17 driver, meant to be replaced in the future by
	 *          more robust version checks, only able to be checked after at least one device has been
	 *          successfully plugged in.
	 *
	 * @author	Jason "megadrago88" Hart
	 * @date	17.08.2021
	 *
	 * @param   target  The PVIGEM_TARGET to check against.
	 *
	 * @returns	A BOOLEAN, true if the device wait ready ioctl is supported (1.17+) or false if not ( =< 1.16)
	 */
	VIGEM_API BOOLEAN vigem_target_is_waitable_add_supported(
		PVIGEM_TARGET target
	);

	/**
	 * Allocates an object representing an Xbox 360 Controller device.
	 *
	 * @author	Benjamin "Nefarius" Höglinger-Stelzer
	 * @date	28.08.2017
	 *
	 * @returns	A PVIGEM_TARGET representing an Xbox 360 Controller device.
	 */
	VIGEM_API PVIGEM_TARGET vigem_target_x360_alloc(void);

#ifdef VIGEM_DS4
	/**
	 * Allocates an object representing a DualShock 4 Controller device.
	 *
	 * @author	Benjamin "Nefarius" Höglinger-Stelzer
	 * @date	28.08.2017
	 *
	 * @returns	A PVIGEM_TARGET representing a DualShock 4 Controller device.
	 */
	VIGEM_API PVIGEM_TARGET vigem_target_ds4_alloc(void);
#endif // VIGEM_DS4

	/**
	 * Frees up memory used by the target device object. This does not automatically remove
	 *          the associated device from the bus, if present. If the target device doesn't get
	 *          removed before this call, the device becomes orphaned until the owning process is
	 *          terminated.
	 *
	 * @author	Benjamin "Nefarius" Höglinger-Stelzer
	 * @date	28.08.2017
	 *
	 * @param 	target	The target device object.
	 */
	VIGEM_API void vigem_target_free(
		PVIGEM_TARGET target
	);

	/**
	 * Adds a provided target device to the bus driver, which is equal to a device plug-in
	 *          event of a physical hardware device. This function blocks until the target device is
	 *          in full operational mode.
	 *
	 * @author	Benjamin "Nefarius" Höglinger-Stelzer
	 * @date	28.08.2017
	 *
	 * @param 	vigem 	The driver connection object.
	 * @param 	target	The target device object.
	 *
	 * @returns	A VIGEM_ERROR.
	 */
	VIGEM_API VIGEM_ERROR vigem_target_add(
		PVIGEM_CLIENT vigem,
		PVIGEM_TARGET target
	);

#ifdef VIGEM_ASYNC_FUNCTIONS
	/**
	 * Adds a provided target device to the bus driver, which is equal to a device plug-in
	 *          event of a physical hardware device. This function immediately returns. An optional
	 *          callback may be registered which gets called on error or if the target device has
	 *          become fully operational.
	 *
	 * @author	Benjamin "Nefarius" Höglinger-Stelzer
	 * @date	28.08.2017
	 *
	 * @param 	vigem 	The driver connection object.
	 * @param 	target	The target device object.
	 * @param 	result	An optional function getting called when the target device becomes available.
	 *
	 * @returns	A VIGEM_ERROR.
	 */
	VIGEM_API VIGEM_ERROR vigem_target_add_async(
		PVIGEM_CLIENT vigem,
		PVIGEM_TARGET target,
		PFN_VIGEM_TARGET_ADD_RESULT result
	);
#endif

	/**
	 * Removes a provided target device from the bus driver, which is equal to a device
	 *           unplug event of a physical hardware device. The target device object may be reused
	 *           after this function is called. If this function is never called on target device
	 *           objects, they will be removed from the bus when the owning process terminates.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	28.08.2017
	 *
	 * @param 	vigem 	The driver connection object.
	 * @param 	target	The target device object.
	 *
	 * @returns	A VIGEM_ERROR.
	 */
	VIGEM_API VIGEM_ERROR vigem_target_remove(
		PVIGEM_CLIENT vigem,
		PVIGEM_TARGET target
	);

#ifdef VIGEM_ASYNC_FUNCTIONS
	/**
	 * Registers a function which gets called, when LED index or vibration state changes
	 *                 occur on the provided target device. This function fails if the provided
	 *                 target device isn't fully operational or in an erroneous state.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	28.08.2017
	 *
	 * @param 	vigem			The driver connection object.
	 * @param 	target			The target device object.
	 * @param 	notification	The notification callback.
	 * @param 	userData		The user data passed to the notification callback.
	 *
	 * @returns	A VIGEM_ERROR.
	 */
	VIGEM_API VIGEM_ERROR vigem_target_x360_register_notification(
		PVIGEM_CLIENT vigem,
		PVIGEM_TARGET target,
		PFN_VIGEM_X360_NOTIFICATION notification,
		LPVOID userData
	);
#endif

#ifdef VIGEM_DS4
#ifdef VIGEM_ASYNC_FUNCTIONS
	/**
	 * This function is deprecated, use vigem_target_ds4_await_output_report or
	 * vigem_target_ds4_await_output_report_timeout instead. Registers a function which gets called,
	 * when LightBar or vibration state changes occur on the provided target device. This function
	 * fails if the provided target device isn't fully operational or in an erroneous state.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	28.08.2017
	 *
	 * @param 	vigem			The driver connection object.
	 * @param 	target			The target device object.
	 * @param 	notification	The notification callback.
	 * @param 	userData		The user data passed to the notification callback.
	 *
	 * @returns	A VIGEM_ERROR.
	 */
	VIGEM_API VIGEM_DEPRECATED VIGEM_ERROR vigem_target_ds4_register_notification(
		PVIGEM_CLIENT vigem,
		PVIGEM_TARGET target,
		PFN_VIGEM_DS4_NOTIFICATION notification,
		LPVOID userData
	);
#endif
#endif // VIGEM_DS4

	/**
	 * Removes a previously registered callback function from the provided target object.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	28.08.2017
	 *
	 * @param 	target	The target device object.
	 */
	VIGEM_API void vigem_target_x360_unregister_notification(
		PVIGEM_TARGET target
	);

#ifdef VIGEM_DS4
	/**
	 * Removes a previously registered callback function from the provided target object.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	28.08.2017
	 *
	 * @param 	target	The target device object.
	 */
	VIGEM_API VIGEM_DEPRECATED void vigem_target_ds4_unregister_notification(
		PVIGEM_TARGET target
	);
#endif // VIGEM_DS4

	/**
	 * Overrides the default Vendor ID value with the provided one.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	28.08.2017
	 *
	 * @param 	target	The target device object.
	 * @param 	vid   	The Vendor ID to set.
	 */
	VIGEM_API void vigem_target_set_vid(
		PVIGEM_TARGET target,
		USHORT vid
	);

	/**
	 * Overrides the default Product ID value with the provided one.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	28.08.2017
	 *
	 * @param 	target	The target device object.
	 * @param 	pid   	The Product ID to set.
	 */
	VIGEM_API void vigem_target_set_pid(
		PVIGEM_TARGET target,
		USHORT pid
	);

	/**
	 * Returns the Vendor ID of the provided target device object.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	28.08.2017
	 *
	 * @param 	target	The target device object.
	 *
	 * @returns	The Vendor ID.
	 */
	VIGEM_API USHORT vigem_target_get_vid(
		PVIGEM_TARGET target
	);

	/**
	 * Returns the Product ID of the provided target device object.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	28.08.2017
	 *
	 * @param 	target	The target device object.
	 *
	 * @returns	The Product ID.
	 */
	VIGEM_API USHORT vigem_target_get_pid(
		PVIGEM_TARGET target
	);

	/**
	 * Sends a state report to the provided target device.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	28.08.2017
	 *
	 * @param 	vigem 	The driver connection object.
	 * @param 	target	The target device object.
	 * @param 	report	The report to send to the target device.
	 *
	 * @returns	A VIGEM_ERROR.
	 */
	VIGEM_API VIGEM_ERROR vigem_target_x360_update(
		PVIGEM_CLIENT vigem,
		PVIGEM_TARGET target,
		XUSB_REPORT report
	);

#ifdef VIGEM_DS4
	/**
	 * DEPRECATED. Sends a state report to the provided target device. It's recommended to use
	 * vigem_target_ds4_update_ex instead to utilize all DS4 features like touch, gyro etc.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	28.08.2017
	 *
	 * @param 	vigem 	The driver connection object.
	 * @param 	target	The target device object.
	 * @param 	report	The report to send to the target device.
	 *
	 * @returns	A VIGEM_ERROR.
	 */
	VIGEM_API VIGEM_ERROR vigem_target_ds4_update(
		PVIGEM_CLIENT vigem,
		PVIGEM_TARGET target,
		DS4_REPORT report
	);

	/**
	 * Sends a full size state report to the provided target device. It's recommended to use this
	 * function over vigem_target_ds4_update.
	 *
	 * @author	Benjamin "Nefarius" Höglinger-Stelzer
	 * @date	07.09.2020
	 *
	 * @param 	vigem 	The driver connection object.
	 * @param 	target	The target device object.
	 * @param 	report	The report buffer.
	 *
	 * @returns	A VIGEM_ERROR.
	 */
	VIGEM_API VIGEM_ERROR vigem_target_ds4_update_ex(
		PVIGEM_CLIENT vigem,
		PVIGEM_TARGET target,
		DS4_REPORT_EX report
	);
#endif // VIGEM_DS4

	/**
	 * Returns the internal index (serial number) the bus driver assigned to the provided
	 *               target device object. Note that this value is specific to the inner workings of
	 *               the bus driver, it does not reflect related values like player index or device
	 *               arrival order experienced by other APIs. It may be used to identify the target
	 *               device object for its lifetime. This value becomes invalid once the target
	 *               device is removed from the bus and may change on the next addition of the
	 *               device.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	28.08.2017
	 *
	 * @param 	target	The target device object.
	 *
	 * @returns	The internally used index of the target device.
	 */
	VIGEM_API ULONG vigem_target_get_index(
		PVIGEM_TARGET target
	);

	/**
	 * Returns the type of the provided target device object.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	28.08.2017
	 *
	 * @param 	target	The target device object.
	 *
	 * @returns	A VIGEM_TARGET_TYPE.
	 */
	VIGEM_API VIGEM_TARGET_TYPE vigem_target_get_type(
		PVIGEM_TARGET target
	);

	/**
	 * Returns TRUE if the provided target device object is currently attached to the bus,
	 *              FALSE otherwise.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	30.08.2017
	 *
	 * @param 	target	The target device object.
	 *
	 * @returns	TRUE if device is attached to the bus, FALSE otherwise.
	 */
	VIGEM_API BOOL vigem_target_is_attached(
		PVIGEM_TARGET target
	);

	/**
	 * Returns the user index of the emulated Xenon device. This value correspondents to the
	 *                (zero-based) index number representing the player number via LED present on a
	 *                physical controller and is compatible to the dwUserIndex property of the
	 *                XInput* APIs.
	 *
	 * @author	Benjamin "Nefarius" Höglinger
	 * @date	10.05.2018
	 *
	 * @param 	vigem 	The driver connection object.
	 * @param 	target	The target device object.
	 * @param 	index 	The (zero-based) user index of the Xenon device.
	 *
	 * @returns	A VIGEM_ERROR.
	 */
	VIGEM_API VIGEM_ERROR vigem_target_x360_get_user_index(
		PVIGEM_CLIENT vigem,
		PVIGEM_TARGET target,
		PULONG index
	);

#ifdef VIGEM_DS4
	/**
	 * Waits until there's one or more pending raw output reports available to consume. This
	 * function blocks until data becomes available or the device gets disconnected. The waiting is
	 * event-based, meaning that as soon as a data packet is pending, this call returns a copy of
	 * the entire buffer. Each call returns a packet in the exact order it arrived in the driver. It
	 * is recommended to repeatedly call this function in a thread. The call aborts with an error
	 * code if the target gets unplugged in parallel.
	 *
	 * @author	Benjamin "Nefarius" Höglinger-Stelzer
	 * @date	06.08.2022
	 *
	 * @param 	vigem 	The driver connection object.
	 * @param 	target	The target device object.
	 * @param 	buffer	The fixed-size 64-bytes output report buffer that gets written to.
	 *
	 * @returns	A VIGEM_ERROR.
	 */
	VIGEM_API VIGEM_ERROR vigem_target_ds4_await_output_report(
		PVIGEM_CLIENT vigem,
		PVIGEM_TARGET target,
		PDS4_OUTPUT_BUFFER buffer
	);

	/**
	 * Waits until there's one or more pending raw output reports available to consume. This
	 * function blocks until data becomes available, the provided timeout has been reached or the
	 * device gets disconnected. The waiting is event-based, meaning that as soon as a data packet
	 * is pending, this call returns a copy of the entire buffer. Each call returns a packet in the
	 * exact order it arrived in the driver. It is recommended to repeatedly call this function in a
	 * thread. A timeout of a few hundred milliseconds can be used to break out of the loop without
	 * excessive CPU consumption. The call aborts with an error code if the target gets unplugged in
	 * parallel. If a timeout of INFINITE is specified, the function basically behaves identical to
	 * vigem_target_ds4_await_output_report.
	 *
	 * @author	Benjamin "Nefarius" Höglinger-Stelzer
	 * @date	12.08.2022
	 *
	 * @param 	vigem			The driver connection object.
	 * @param 	target			The target device object.
	 * @param 	milliseconds	The timeout in milliseconds.
	 * @param 	buffer			The fixed-size 64-bytes output report buffer that gets written to.
	 *
	 * @returns	A VIGEM_ERROR.
	 */
	VIGEM_API VIGEM_ERROR vigem_target_ds4_await_output_report_timeout(
		PVIGEM_CLIENT vigem,
		PVIGEM_TARGET target,
		DWORD milliseconds,
		PDS4_OUTPUT_BUFFER buffer
	);
#endif // VIGEM_DS4

    /**
     * Returns the output data of the Xbox gamepad. Output refers to the USB output report, which
     *                is used to set LEDs and motor values.
     *
     * @author  Matt Wszolek
     * @date    09.28.2021
     *
     * @param   vigem   The driver connection object.
     * @param   target  The target device object.
     * @param   output  The values that are set by the output reports
     *
     * @returns A VIGEM_ERROR.
     */
    VIGEM_API VIGEM_ERROR vigem_target_x360_get_output(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PXUSB_OUTPUT_DATA output);

#ifdef VIGEM_DS4
    /**
     * Returns the output data of the DualShock 4 gamepad. Output refers to the USB output report,
     *                which is used to set LED and motor values.
     *
     * @author  Matt Wszolek
     * @date    09.28.2021
     *
     * @param   vigem   The driver connection object.
     * @param   target  The target device object.
     * @param   output  The values that are set by the output reports
     *
     * @returns A VIGEM_ERROR.
     */
    VIGEM_API VIGEM_ERROR vigem_target_ds4_get_output(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PDS4_OUTPUT_DATA output);
#endif // VIGEM_DS4

#ifdef __cplusplus
}
#endif

#endif // ViGEmClient_h__
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


//
// Internal
// 
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//#include "Internal.h"
/*
MIT License

Copyright (c) 2017-2023 Nefarius Software Solutions e.U. and Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#pragma once

//
// TODO: this is... not optimal. Improve in the future.
// 
#define VIGEM_TARGETS_MAX   USHRT_MAX


//
// Represents a driver connection object.
// 
typedef struct _VIGEM_CLIENT_T
{
    HANDLE hBusDevice;
#ifdef VIGEM_DS4
    HANDLE hDS4OutputReportPickupThread;
    HANDLE hDS4OutputReportPickupThreadAbortEvent;
#endif // VIGEM_DS4
    PVIGEM_TARGET pTargetsList[VIGEM_TARGETS_MAX];
} VIGEM_CLIENT;

//
// Represents the (connection) state of a target device object.
// 
typedef enum
{
    VIGEM_TARGET_NEW,
    VIGEM_TARGET_INITIALIZED,
    VIGEM_TARGET_CONNECTED,
    VIGEM_TARGET_DISCONNECTED
} VIGEM_TARGET_STATE, *PVIGEM_TARGET_STATE;

//
// Represents a virtual gamepad object.
// 
typedef struct _VIGEM_TARGET_T
{
    ULONG Size;
    ULONG SerialNo;
    VIGEM_TARGET_STATE State;
    USHORT VendorId;
    USHORT ProductId;
    VIGEM_TARGET_TYPE Type;
    FARPROC Notification;
    LPVOID NotificationUserData;
    BOOLEAN IsWaitReadyUnsupported;
	HANDLE CancelNotificationThreadEvent;
#ifdef VIGEM_DS4
    DS4_OUTPUT_BUFFER Ds4CachedOutputReport;
    HANDLE Ds4CachedOutputReportUpdateAvailable;
    CRITICAL_SECTION Ds4CachedOutputReportUpdateLock;
#endif // VIGEM_DS4
    BOOLEAN IsDisposing;
} VIGEM_TARGET;

#define DEVICE_IO_CONTROL_BEGIN	\
	DWORD transferred = 0; \
	OVERLAPPED lOverlapped = { 0 }; \
	lOverlapped.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL)

#define DEVICE_IO_CONTROL_END \
	if (lOverlapped.hEvent) \
		CloseHandle(lOverlapped.hEvent)
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//#include "UniUtil.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

//#define VIGEM_VERBOSE_LOGGING_ENABLED

#ifndef ERROR_INVALID_DEVICE_OBJECT_PARAMETER
#define ERROR_INVALID_DEVICE_OBJECT_PARAMETER 0x0000028A
#endif


#pragma region Diagnostics

#if 0 //def _DEBUG
#define DBGPRINT(kwszDebugFormatString, ...) _DBGPRINT(ConvertAnsiToWide(__func__).c_str(), __LINE__, kwszDebugFormatString, __VA_ARGS__)
#else
#define DBGPRINT( kwszDebugFormatString, ... ) ;;
#endif

VOID _DBGPRINT(LPCWSTR kwszFunction, INT iLineNumber, LPCWSTR kwszDebugFormatString, ...)
{
#if defined(VIGEM_VERBOSE_LOGGING_ENABLED)
	INT cbFormatString = 0;
	va_list args;
	PWCHAR wszDebugString = nullptr;
	size_t st_Offset = 0;

	va_start(args, kwszDebugFormatString);

	// Get size of message string from formatting args
	cbFormatString = _scwprintf(L"[%s:%d] ", kwszFunction, iLineNumber) * sizeof(WCHAR);
	cbFormatString += _vscwprintf(kwszDebugFormatString, args) * sizeof(WCHAR);
	cbFormatString += sizeof(WCHAR); // for null-terminator

	// Allocate message string
	wszDebugString = static_cast<PWCHAR>(malloc(cbFormatString));
	if (wszDebugString == nullptr)
		return;

	// Populate the buffer with the contents of the format string
	StringCbPrintfW(wszDebugString, cbFormatString, L"[%s:%d] ", kwszFunction, iLineNumber);
	StringCbLengthW(wszDebugString, cbFormatString, &st_Offset);
	StringCbVPrintfW(&wszDebugString[st_Offset / sizeof(WCHAR)], cbFormatString - st_Offset, kwszDebugFormatString,
		args);

	// Ensure null-terminated
	wszDebugString[cbFormatString - 1] = L'\0';

	// Output message
	OutputDebugStringW(wszDebugString);
	OutputDebugStringW(L"\n");

	free(wszDebugString);
	va_end(args);
#else
//	std::ignore = kwszFunction;
//	std::ignore = iLineNumber;
//	std::ignore = kwszDebugFormatString;
#endif
}

static void to_hex(unsigned char* in, size_t insz, char* out, size_t outsz)
{
	unsigned char* pin = in;
	auto hex = "0123456789ABCDEF";
	char* pout = out;
	for (; pin < in + insz; pout += 3, pin++)
	{
		pout[0] = hex[(*pin >> 4) & 0xF];
		pout[1] = hex[*pin & 0xF];
		pout[2] = ':';
		if ((size_t)(pout + 3 - out) > outsz)
		{
			/* Better to truncate output string than overflow buffer */
			/* it would be still better to either return a status */
			/* or ensure the target buffer is large enough and it never happen */
			break;
		}
	}
	pout[-1] = 0;
}

#pragma endregion


//
// Initializes a virtual gamepad object.
// 
PVIGEM_TARGET FORCEINLINE VIGEM_TARGET_ALLOC_INIT(
	_In_ VIGEM_TARGET_TYPE Type
)
{
	auto target = static_cast<PVIGEM_TARGET>(malloc(sizeof(VIGEM_TARGET)));

	if (!target)
		return nullptr;

	memset(target, 0, sizeof(VIGEM_TARGET));

	target->Size = sizeof(VIGEM_TARGET);
	target->State = VIGEM_TARGET_INITIALIZED;
	target->Type = Type;
	return target;
}

#ifdef VIGEM_DS4
static DWORD WINAPI vigem_internal_ds4_output_report_pickup_handler(LPVOID Parameter)
{
	const auto pClient = static_cast<PVIGEM_CLIENT>(Parameter);
	DS4_AWAIT_OUTPUT await;
	DEVICE_IO_CONTROL_BEGIN;

	// Abort event first so that in the case both are signaled at once, the result will be for the abort event
	const HANDLE waitEvents[] =
	{
		pClient->hDS4OutputReportPickupThreadAbortEvent,
		lOverlapped.hEvent
	};

	DBGPRINT(L"Started DS4 Output Report pickup thread for 0x%p", pClient);

	do
	{
		DS4_AWAIT_OUTPUT_INIT(&await, 0);

		DeviceIoControl(
			pClient->hBusDevice,
			IOCTL_DS4_AWAIT_OUTPUT_AVAILABLE,
			&await,
			await.Size,
			&await,
			await.Size,
			&transferred,
			&lOverlapped
		);

		const DWORD waitResult = WaitForMultipleObjects(
			static_cast<DWORD>(std::size(waitEvents)),
			waitEvents,
			FALSE,
			INFINITE
		);

		if (waitResult == WAIT_OBJECT_0)
		{
			DBGPRINT(L"Abort event signalled during read, exiting thread", NULL);
			CancelIoEx(pClient->hBusDevice, &lOverlapped);
			break;
		}

		if (waitResult == WAIT_FAILED)
		{
			const DWORD error = GetLastError();
			DBGPRINT(L"Win32 error from multi-object wait: 0x%X", error);
			continue;
		}

		if (waitResult != WAIT_OBJECT_0 + 1)
		{
			DBGPRINT(L"Unexpected result from multi-object wait: 0x%X", waitResult);
		}

		if (GetOverlappedResult(pClient->hBusDevice, &lOverlapped, &transferred, FALSE) == FALSE)
		{
			const DWORD error = GetLastError();

			//
			// Backwards compatibility with version pre-1.19, where this IOCTL doesn't exist
			// 
			if (error == ERROR_INVALID_PARAMETER)
			{
				DBGPRINT(L"Currently used driver version doesn't support this request, aborting", NULL);
				break;
			}

			if (error == ERROR_OPERATION_ABORTED)
			{
				DBGPRINT(L"Read has been cancelled, aborting", NULL);
				break;
			}

			if (error == ERROR_IO_INCOMPLETE)
			{
				DBGPRINT(L"Pending I/O not completed, aborting", NULL);
				CancelIoEx(pClient->hBusDevice, &lOverlapped);
				break;
			}

			DBGPRINT(L"Win32 error from overlapped result: 0x%X", error);
			continue;
		}

#if defined(VIGEM_VERBOSE_LOGGING_ENABLED)
		DBGPRINT(L"Dumping buffer for %d", await.SerialNo);

		const PCHAR dumpBuffer = (PCHAR)calloc(sizeof(DS4_OUTPUT_BUFFER), 3);
		if (dumpBuffer != nullptr)
		{
			to_hex(await.Report.Buffer, sizeof(DS4_OUTPUT_BUFFER), dumpBuffer, sizeof(DS4_OUTPUT_BUFFER) * 3);
			OutputDebugStringA(dumpBuffer);
			free(dumpBuffer);
		}
#endif

		const PVIGEM_TARGET pTarget = pClient->pTargetsList[await.SerialNo];

		if (pTarget && !pTarget->IsDisposing && pTarget->Type == DualShock4Wired)
		{
			memcpy(&pTarget->Ds4CachedOutputReport, &await.Report, sizeof(DS4_OUTPUT_BUFFER));
			SetEvent(pTarget->Ds4CachedOutputReportUpdateAvailable);
		}
		else
		{
			DBGPRINT(L"No target to report to for serial %d", await.SerialNo);
		}
	} while (TRUE);

	DEVICE_IO_CONTROL_END;

	DBGPRINT(L"Finished DS4 Output Report pickup thread for 0x%p", pClient);

	return 0;
}
#endif // VIGEM_DS4

PVIGEM_CLIENT vigem_alloc()
{
	const auto driver = static_cast<PVIGEM_CLIENT>(malloc(sizeof(VIGEM_CLIENT)));

	if (!driver)
		return nullptr;

	RtlZeroMemory(driver, sizeof(VIGEM_CLIENT));

	driver->hBusDevice = INVALID_HANDLE_VALUE;
#ifdef VIGEM_DS4
	driver->hDS4OutputReportPickupThreadAbortEvent = CreateEvent(
		nullptr,
		TRUE,
		FALSE,
		nullptr
	);
#endif // VIGEM_DS4

	return driver;
}

void vigem_free(PVIGEM_CLIENT vigem)
{
	if (vigem)
	{
#ifdef VIGEM_DS4
		CloseHandle(vigem->hDS4OutputReportPickupThreadAbortEvent);
#endif // VIGEM_DS4

		free(vigem);
	}
}

VIGEM_ERROR vigem_connect(PVIGEM_CLIENT vigem)
{
	if (!vigem)
		return VIGEM_ERROR_BUS_INVALID_HANDLE;

	HINSTANCE dllHandle = fpLoadLibraryW(L"Setupapi");
	if (!dllHandle)
		return VIGEM_ERROR_NOT_SUPPORTED;

	typedef HDEVINFO (WINAPI *TSetupDiGetClassDevsA)(const GUID*, PCSTR, HWND, DWORD);
	TSetupDiGetClassDevsA fnSetupDiGetClassDevs = (TSetupDiGetClassDevsA)fpGetProcAddress(dllHandle, "SetupDiGetClassDevsA");

	typedef BOOL (WINAPI *TSetupDiEnumDeviceInterfaces)(HDEVINFO, PSP_DEVINFO_DATA, const GUID*, DWORD, PSP_DEVICE_INTERFACE_DATA);
	TSetupDiEnumDeviceInterfaces fnSetupDiEnumDeviceInterfaces = (TSetupDiEnumDeviceInterfaces)fpGetProcAddress(dllHandle, "SetupDiEnumDeviceInterfaces");

	typedef BOOL (WINAPI *TSetupDiGetDeviceInterfaceDetailA)(HDEVINFO, PSP_DEVICE_INTERFACE_DATA, PSP_DEVICE_INTERFACE_DETAIL_DATA_A, DWORD, PDWORD, PSP_DEVINFO_DATA);
	TSetupDiGetDeviceInterfaceDetailA fnSetupDiGetDeviceInterfaceDetail = (TSetupDiGetDeviceInterfaceDetailA)fpGetProcAddress(dllHandle, "SetupDiGetDeviceInterfaceDetailA");

	typedef BOOL (WINAPI *TSetupDiDestroyDeviceInfoList)(HDEVINFO);
	TSetupDiDestroyDeviceInfoList fnSetupDiDestroyDeviceInfoList = (TSetupDiDestroyDeviceInfoList)fpGetProcAddress(dllHandle, "SetupDiDestroyDeviceInfoList");

	SP_DEVICE_INTERFACE_DATA deviceInterfaceData = { 0 };
	deviceInterfaceData.cbSize = sizeof(deviceInterfaceData);
	DWORD memberIndex = 0;
	DWORD requiredSize = 0;
	auto error = VIGEM_ERROR_BUS_NOT_FOUND;

	// check for already open handle as re-opening accidentally would destroy all live targets
	if (vigem->hBusDevice != INVALID_HANDLE_VALUE)
	{
		return VIGEM_ERROR_BUS_ALREADY_CONNECTED;
	}

	const auto deviceInfoSet = fnSetupDiGetClassDevs(
		&GUID_DEVINTERFACE_BUSENUM_VIGEM,
		nullptr,
		nullptr,
		DIGCF_PRESENT | DIGCF_DEVICEINTERFACE
	);

	// enumerate device instances
	while (fnSetupDiEnumDeviceInterfaces(
		deviceInfoSet,
		nullptr,
		&GUID_DEVINTERFACE_BUSENUM_VIGEM,
		memberIndex++,
		&deviceInterfaceData
	))
	{
		// get required target buffer size
		fnSetupDiGetDeviceInterfaceDetail(deviceInfoSet, &deviceInterfaceData, nullptr, 0, &requiredSize, nullptr);

		// allocate target buffer
		const auto detailDataBuffer = static_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA>(malloc(requiredSize));
		detailDataBuffer->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		// get detail buffer
		if (!fnSetupDiGetDeviceInterfaceDetail(
			deviceInfoSet,
			&deviceInterfaceData,
			detailDataBuffer,
			requiredSize,
			&requiredSize,
			nullptr
		))
		{
			free(detailDataBuffer);
			error = VIGEM_ERROR_BUS_NOT_FOUND;
			continue;
		}

		// bus found, open it
		vigem->hBusDevice = CreateFile(
			detailDataBuffer->DevicePath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			nullptr,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH | FILE_FLAG_OVERLAPPED,
			nullptr
		);

		// check bus open result
		if (vigem->hBusDevice == INVALID_HANDLE_VALUE)
		{
			error = VIGEM_ERROR_BUS_ACCESS_FAILED;
			free(detailDataBuffer);
			continue;
		}

		DWORD transferred = 0;
		OVERLAPPED lOverlapped = { 0 };
		lOverlapped.hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

		VIGEM_CHECK_VERSION version;
		VIGEM_CHECK_VERSION_INIT(&version, VIGEM_COMMON_VERSION);

		// send compiled library version to driver to check compatibility
		DeviceIoControl(
			vigem->hBusDevice,
			IOCTL_VIGEM_CHECK_VERSION,
			&version,
			version.Size,
			nullptr,
			0,
			&transferred,
			&lOverlapped
		);

		// wait for result
		if (GetOverlappedResult(vigem->hBusDevice, &lOverlapped, &transferred, TRUE) != 0)
		{
#ifdef VIGEM_DS4
			vigem->hDS4OutputReportPickupThread = CreateThread(
				nullptr,
				0,
				vigem_internal_ds4_output_report_pickup_handler,
				vigem,
				0,
				nullptr
			);
#endif // VIGEM_DS4

			error = VIGEM_ERROR_NONE;
			free(detailDataBuffer);
			CloseHandle(lOverlapped.hEvent);
			break;
		}

		error = VIGEM_ERROR_BUS_VERSION_MISMATCH;

		CloseHandle(lOverlapped.hEvent);
		free(detailDataBuffer);
	}

	fnSetupDiDestroyDeviceInfoList(deviceInfoSet);

	return error;
}

void vigem_disconnect(PVIGEM_CLIENT vigem)
{
	if (!vigem)
		return;

#ifdef VIGEM_DS4
	if (vigem->hDS4OutputReportPickupThread && vigem->hDS4OutputReportPickupThreadAbortEvent)
	{
		DBGPRINT(L"Awaiting DS4 thread clean-up for 0x%p", vigem);

		SetEvent(vigem->hDS4OutputReportPickupThreadAbortEvent);
		WaitForSingleObject(vigem->hDS4OutputReportPickupThread, INFINITE);
		CloseHandle(vigem->hDS4OutputReportPickupThread);

		DBGPRINT(L"DS4 thread clean-up for 0x%p finished", vigem);
	}
#endif // VIGEM_DS4

	if (vigem->hBusDevice != INVALID_HANDLE_VALUE)
	{
		DBGPRINT(L"Closing bus handle for 0x%p", vigem);

		CloseHandle(vigem->hBusDevice);
		vigem->hBusDevice = INVALID_HANDLE_VALUE;
	}

	RtlZeroMemory(vigem, sizeof(VIGEM_CLIENT));
}

BOOLEAN vigem_target_is_waitable_add_supported(PVIGEM_TARGET target)
{
	//
	// Safety check to make people use the older functions and not cause issues
	// Should never pass in an invalid target but doesn't hurt to check.
	//
	if (!target)
		return FALSE;

	// TODO: Replace all this with a more robust version check system
	return !target->IsWaitReadyUnsupported;
}

PVIGEM_TARGET vigem_target_x360_alloc(void)
{
	const auto target = VIGEM_TARGET_ALLOC_INIT(Xbox360Wired);

	if (!target)
		return nullptr;

	target->VendorId = 0x045E;
	target->ProductId = 0x028E;

	return target;
}

#ifdef VIGEM_DS4
PVIGEM_TARGET vigem_target_ds4_alloc(void)
{
	const auto target = VIGEM_TARGET_ALLOC_INIT(DualShock4Wired);

	if (!target)
		return nullptr;

	target->VendorId = 0x054C;
	target->ProductId = 0x05C4;
	target->Ds4CachedOutputReportUpdateAvailable = CreateEvent(
		nullptr,
		FALSE,
		FALSE,
		nullptr
	);
	InitializeCriticalSection(&target->Ds4CachedOutputReportUpdateLock);

	return target;
}
#endif // VIGEM_DS4

void vigem_target_free(PVIGEM_TARGET target)
{
	if (target)
	{
#ifdef VIGEM_DS4
		if (target->Ds4CachedOutputReportUpdateAvailable)
		{
			CloseHandle(target->Ds4CachedOutputReportUpdateAvailable);
		}

		DeleteCriticalSection(&target->Ds4CachedOutputReportUpdateLock);
#endif // VIGEM_DS4

		free(target);
	}
}

VIGEM_ERROR vigem_target_add(PVIGEM_CLIENT vigem, PVIGEM_TARGET target)
{
	VIGEM_ERROR error = VIGEM_ERROR_NO_FREE_SLOT;
	DWORD transferred = 0;
	VIGEM_PLUGIN_TARGET plugin;
	VIGEM_WAIT_DEVICE_READY devReady;
	OVERLAPPED olPlugIn = { 0 };
	olPlugIn.hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	OVERLAPPED olWait = { 0 };
	olWait.hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

	do
	{
		if (!vigem)
		{
			error = VIGEM_ERROR_BUS_INVALID_HANDLE;
			break;
		}

		if (!target)
		{
			error = VIGEM_ERROR_INVALID_TARGET;
			break;
		}

		if (vigem->hBusDevice == INVALID_HANDLE_VALUE)
		{
			error = VIGEM_ERROR_BUS_NOT_FOUND;
			break;
		}

		if (target->State == VIGEM_TARGET_NEW)
		{
			error = VIGEM_ERROR_TARGET_UNINITIALIZED;
			break;
		}

		if (target->State == VIGEM_TARGET_CONNECTED)
		{
			error = VIGEM_ERROR_ALREADY_CONNECTED;
			break;
		}

		//
		// TODO: this is mad stupid, redesign, so that the bus fills the assigned slot
		// 
		for (target->SerialNo = 1; target->SerialNo <= VIGEM_TARGETS_MAX; target->SerialNo++)
		{
			VIGEM_PLUGIN_TARGET_INIT(&plugin, target->SerialNo, target->Type);

			plugin.VendorId = target->VendorId;
			plugin.ProductId = target->ProductId;

			/*
			 * Request plugin of device. This is an inherently asynchronous operation,
			 * which is addressed differently through the history of the driver design.
			 * Pre-v1.17 this request was kept pending until the child was deemed operational
			 * which unfortunately causes synchronization issues on some systems.
			 * Starting with v1.17 "waiting" for full power-up is done with an additional
			 * IOCTL that is sent immediately after and kept pending until the driver
			 * reports that the device can receive report updates. The following section
			 * and error handling is designed to achieve transparent backwards compatibility
			 * to not break applications using the pre-v1.17 client SDK. This is not a 100%
			 * perfect and can cause other functions to fail if called too soon but
			 * hopefully the applications will just ignore these errors and retry ;)
			 */
			DeviceIoControl(
				vigem->hBusDevice,
				IOCTL_VIGEM_PLUGIN_TARGET,
				&plugin,
				plugin.Size,
				nullptr,
				0,
				&transferred,
				&olPlugIn
			);

			//
			// This should return fairly immediately >=v1.17
			// 
			if (GetOverlappedResult(vigem->hBusDevice, &olPlugIn, &transferred, TRUE) != 0)
			{
				/*
				 * This function is announced to be blocking/synchronous, a concept that
				 * doesn't reflect the way the bus driver/PNP manager bring child devices
				 * to life. Therefore, we send another IOCTL which will be kept pending
				 * until the bus driver has been notified that the child device has
				 * reached a state that is deemed operational. This request is only
				 * supported on drivers v1.17 or higher, so gracefully cause errors
				 * of this call as a potential success and keep the device plugged in.
				 */
				VIGEM_WAIT_DEVICE_READY_INIT(&devReady, plugin.SerialNo);

				DeviceIoControl(
					vigem->hBusDevice,
					IOCTL_VIGEM_WAIT_DEVICE_READY,
					&devReady,
					devReady.Size,
					nullptr,
					0,
					&transferred,
					&olWait
				);

				if (GetOverlappedResult(vigem->hBusDevice, &olWait, &transferred, TRUE) != 0)
				{
					target->State = VIGEM_TARGET_CONNECTED;

					error = VIGEM_ERROR_NONE;
					break;
				}

				//
				// Backwards compatibility with version pre-1.17, where this IOCTL doesn't exist
				// 
				if (GetLastError() == ERROR_INVALID_PARAMETER)
				{
					target->State = VIGEM_TARGET_CONNECTED;
					target->IsWaitReadyUnsupported = true;

					error = VIGEM_ERROR_NONE;
					break;
				}

				//
				// Don't leave device connected if the wait call failed
				// 
				error = vigem_target_remove(vigem, target);
				break;
			}
		}
	} while (false);

	if (VIGEM_SUCCESS(error))
	{
		vigem->pTargetsList[target->SerialNo] = target;
	}

	if (olPlugIn.hEvent)
		CloseHandle(olPlugIn.hEvent);

	if (olWait.hEvent)
		CloseHandle(olWait.hEvent);

	return error;
}

#ifdef VIGEM_ASYNC_FUNCTIONS
VIGEM_ERROR vigem_target_add_async(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PFN_VIGEM_TARGET_ADD_RESULT result)
{
	if (!vigem)
		return VIGEM_ERROR_BUS_INVALID_HANDLE;

	if (!target)
		return VIGEM_ERROR_INVALID_TARGET;

	if (vigem->hBusDevice == INVALID_HANDLE_VALUE)
		return VIGEM_ERROR_BUS_NOT_FOUND;

	if (target->State == VIGEM_TARGET_NEW)
		return VIGEM_ERROR_TARGET_UNINITIALIZED;

	if (target->State == VIGEM_TARGET_CONNECTED)
		return VIGEM_ERROR_ALREADY_CONNECTED;

	std::thread _async{
		[](
		PVIGEM_TARGET _Target,
		PVIGEM_CLIENT _Client,
		PFN_VIGEM_TARGET_ADD_RESULT _Result)
		{
			const auto error = vigem_target_add(_Client, _Target);

			_Result(_Client, _Target, error);
		},
		target, vigem, result
	};

	_async.detach();

	return VIGEM_ERROR_NONE;
}
#endif

VIGEM_ERROR vigem_target_remove(PVIGEM_CLIENT vigem, PVIGEM_TARGET target)
{
	if (!vigem)
		return VIGEM_ERROR_BUS_INVALID_HANDLE;

	if (!target)
		return VIGEM_ERROR_INVALID_TARGET;

	if (vigem->hBusDevice == INVALID_HANDLE_VALUE)
		return VIGEM_ERROR_BUS_NOT_FOUND;

	if (target->State == VIGEM_TARGET_NEW)
		return VIGEM_ERROR_TARGET_UNINITIALIZED;

	if (target->State != VIGEM_TARGET_CONNECTED)
		return VIGEM_ERROR_TARGET_NOT_PLUGGED_IN;

	VIGEM_UNPLUG_TARGET unplug;
	DEVICE_IO_CONTROL_BEGIN;

	VIGEM_UNPLUG_TARGET_INIT(&unplug, target->SerialNo);

	DeviceIoControl(
		vigem->hBusDevice,
		IOCTL_VIGEM_UNPLUG_TARGET,
		&unplug,
		unplug.Size,
		nullptr,
		0,
		&transferred,
		&lOverlapped
	);

	if (GetOverlappedResult(vigem->hBusDevice, &lOverlapped, &transferred, TRUE) != 0)
	{
#ifdef VIGEM_DS4
		if (target->Type == DualShock4Wired)
		{
			EnterCriticalSection(&target->Ds4CachedOutputReportUpdateLock);
			{
				target->IsDisposing = TRUE;
				vigem->pTargetsList[target->SerialNo] = nullptr;

			}
			LeaveCriticalSection(&target->Ds4CachedOutputReportUpdateLock);
		}
#endif // VIGEM_DS4

		target->State = VIGEM_TARGET_DISCONNECTED;

		DEVICE_IO_CONTROL_END;

		return VIGEM_ERROR_NONE;
	}

	DEVICE_IO_CONTROL_END;

	return VIGEM_ERROR_REMOVAL_FAILED;
}

#ifdef VIGEM_ASYNC_FUNCTIONS
VIGEM_ERROR vigem_target_x360_register_notification(
	PVIGEM_CLIENT vigem,
	PVIGEM_TARGET target,
	PFN_VIGEM_X360_NOTIFICATION notification,
	LPVOID userData
)
{
	if (!vigem)
		return VIGEM_ERROR_BUS_INVALID_HANDLE;

	if (!target)
		return VIGEM_ERROR_INVALID_TARGET;

	if (vigem->hBusDevice == INVALID_HANDLE_VALUE)
		return VIGEM_ERROR_BUS_NOT_FOUND;

	if (target->SerialNo == 0 || notification == nullptr)
		return VIGEM_ERROR_INVALID_TARGET;

	if (target->Notification == reinterpret_cast<FARPROC>(notification))
		return VIGEM_ERROR_CALLBACK_ALREADY_REGISTERED;

	target->Notification = reinterpret_cast<FARPROC>(notification);
	target->NotificationUserData = userData;

	if (target->CancelNotificationThreadEvent == nullptr)
		target->CancelNotificationThreadEvent = CreateEvent(
			nullptr,
			TRUE,
			FALSE,
			nullptr
		);
	else
		ResetEvent(target->CancelNotificationThreadEvent);

	std::thread _async{
		[](
		PVIGEM_TARGET _Target,
		PVIGEM_CLIENT _Client,
		LPVOID _UserData)
		{
			DEVICE_IO_CONTROL_BEGIN;

			XUSB_REQUEST_NOTIFICATION xrn;
			XUSB_REQUEST_NOTIFICATION_INIT(&xrn, _Target->SerialNo);

			do
			{
				DeviceIoControl(
					_Client->hBusDevice,
					IOCTL_XUSB_REQUEST_NOTIFICATION,
					&xrn,
					xrn.Size,
					&xrn,
					xrn.Size,
					&transferred,
					&lOverlapped
				);

				if (GetOverlappedResult(_Client->hBusDevice, &lOverlapped, &transferred, TRUE) != 0)
				{
					if (_Target->Notification == nullptr)
					{
						DEVICE_IO_CONTROL_END;
						return;
					}

					reinterpret_cast<PFN_VIGEM_X360_NOTIFICATION>(_Target->Notification)(
						_Client, _Target, xrn.LargeMotor, xrn.SmallMotor, xrn.LedNumber, _UserData
					);

					continue;
				}

				if (GetLastError() == ERROR_ACCESS_DENIED || GetLastError() == ERROR_OPERATION_ABORTED)
				{
					DEVICE_IO_CONTROL_END;
					return;
				}
			} while (TRUE);
		},
		target, vigem, userData
	};

	_async.detach();

	return VIGEM_ERROR_NONE;
}
#endif

#ifdef VIGEM_DS4
#ifdef VIGEM_ASYNC_FUNCTIONS
VIGEM_ERROR vigem_target_ds4_register_notification(
	PVIGEM_CLIENT vigem,
	PVIGEM_TARGET target,
	PFN_VIGEM_DS4_NOTIFICATION notification,
	LPVOID userData
)
{
	if (!vigem)
		return VIGEM_ERROR_BUS_INVALID_HANDLE;

	if (!target)
		return VIGEM_ERROR_INVALID_TARGET;

	if (vigem->hBusDevice == INVALID_HANDLE_VALUE)
		return VIGEM_ERROR_BUS_NOT_FOUND;

	if (target->SerialNo == 0 || notification == nullptr)
		return VIGEM_ERROR_INVALID_TARGET;

	if (target->Notification == reinterpret_cast<FARPROC>(notification))
		return VIGEM_ERROR_CALLBACK_ALREADY_REGISTERED;

	target->Notification = reinterpret_cast<FARPROC>(notification);
	target->NotificationUserData = userData;

	if (target->CancelNotificationThreadEvent == nullptr)
		target->CancelNotificationThreadEvent = CreateEvent(
			nullptr,
			TRUE,
			FALSE,
			nullptr
		);
	else
		ResetEvent(target->CancelNotificationThreadEvent);

	std::thread _async{
		[](
		PVIGEM_TARGET _Target,
		PVIGEM_CLIENT _Client,
		LPVOID _UserData)
		{
			DEVICE_IO_CONTROL_BEGIN;

			DS4_REQUEST_NOTIFICATION ds4rn;
			DS4_REQUEST_NOTIFICATION_INIT(&ds4rn, _Target->SerialNo);

			do
			{
				DeviceIoControl(
					_Client->hBusDevice,
					IOCTL_DS4_REQUEST_NOTIFICATION,
					&ds4rn,
					ds4rn.Size,
					&ds4rn,
					ds4rn.Size,
					&transferred,
					&lOverlapped
				);

				if (GetOverlappedResult(_Client->hBusDevice, &lOverlapped, &transferred, TRUE) != 0)
				{
					if (_Target->Notification == nullptr)
					{
						DEVICE_IO_CONTROL_END;
						return;
					}

					reinterpret_cast<PFN_VIGEM_DS4_NOTIFICATION>(_Target->Notification)(
						_Client, _Target, ds4rn.Report.LargeMotor,
						ds4rn.Report.SmallMotor,
						ds4rn.Report.LightbarColor, _UserData
					);

					continue;
				}

				if (GetLastError() == ERROR_ACCESS_DENIED || GetLastError() == ERROR_OPERATION_ABORTED)
				{
					DEVICE_IO_CONTROL_END;
					return;
				}
			} while (TRUE);
		},
		target, vigem, userData
	};

	_async.detach();

	return VIGEM_ERROR_NONE;
}
#endif
#endif // VIGEM_DS4

void vigem_target_x360_unregister_notification(PVIGEM_TARGET target)
{
	if (target->CancelNotificationThreadEvent != nullptr)
		SetEvent(target->CancelNotificationThreadEvent);

	if (target->CancelNotificationThreadEvent != nullptr)
	{
		CloseHandle(target->CancelNotificationThreadEvent);
		target->CancelNotificationThreadEvent = nullptr;
	}

	target->Notification = nullptr;
	target->NotificationUserData = nullptr;
}

#ifdef VIGEM_DS4
void vigem_target_ds4_unregister_notification(PVIGEM_TARGET target)
{
	vigem_target_x360_unregister_notification(target); // The same x360_unregister handler works for DS4_unregister also
}
#endif // VIGEM_DS4

void vigem_target_set_vid(PVIGEM_TARGET target, USHORT vid)
{
	target->VendorId = vid;
}

void vigem_target_set_pid(PVIGEM_TARGET target, USHORT pid)
{
	target->ProductId = pid;
}

USHORT vigem_target_get_vid(PVIGEM_TARGET target)
{
	return target->VendorId;
}

USHORT vigem_target_get_pid(PVIGEM_TARGET target)
{
	return target->ProductId;
}

VIGEM_ERROR vigem_target_x360_update(
	PVIGEM_CLIENT vigem,
	PVIGEM_TARGET target,
	XUSB_REPORT report
)
{
	if (!vigem)
		return VIGEM_ERROR_BUS_INVALID_HANDLE;

	if (!target)
		return VIGEM_ERROR_INVALID_TARGET;

	if (vigem->hBusDevice == INVALID_HANDLE_VALUE)
		return VIGEM_ERROR_BUS_NOT_FOUND;

	if (target->SerialNo == 0)
		return VIGEM_ERROR_INVALID_TARGET;

	DEVICE_IO_CONTROL_BEGIN;

	XUSB_SUBMIT_REPORT xsr;
	XUSB_SUBMIT_REPORT_INIT(&xsr, target->SerialNo);

	xsr.Report = report;

	DeviceIoControl(
		vigem->hBusDevice,
		IOCTL_XUSB_SUBMIT_REPORT,
		&xsr,
		xsr.Size,
		nullptr,
		0,
		&transferred,
		&lOverlapped
	);

	if (GetOverlappedResult(vigem->hBusDevice, &lOverlapped, &transferred, TRUE) == 0)
	{
		if (GetLastError() == ERROR_ACCESS_DENIED)
		{
			DEVICE_IO_CONTROL_END;
			return VIGEM_ERROR_INVALID_TARGET;
		}
	}

	DEVICE_IO_CONTROL_END;

	return VIGEM_ERROR_NONE;
}

#ifdef VIGEM_DS4
VIGEM_ERROR vigem_target_ds4_update(
	PVIGEM_CLIENT vigem,
	PVIGEM_TARGET target,
	DS4_REPORT report
)
{
	if (!vigem)
		return VIGEM_ERROR_BUS_INVALID_HANDLE;

	if (!target)
		return VIGEM_ERROR_INVALID_TARGET;

	if (vigem->hBusDevice == INVALID_HANDLE_VALUE)
		return VIGEM_ERROR_BUS_NOT_FOUND;

	if (target->SerialNo == 0)
		return VIGEM_ERROR_INVALID_TARGET;

	DEVICE_IO_CONTROL_BEGIN;

	DS4_SUBMIT_REPORT dsr;
	DS4_SUBMIT_REPORT_INIT(&dsr, target->SerialNo);

	dsr.Report = report;

	DeviceIoControl(
		vigem->hBusDevice,
		IOCTL_DS4_SUBMIT_REPORT,
		&dsr,
		dsr.Size,
		nullptr,
		0,
		&transferred,
		&lOverlapped
	);

	if (GetOverlappedResult(vigem->hBusDevice, &lOverlapped, &transferred, TRUE) == 0)
	{
		if (GetLastError() == ERROR_ACCESS_DENIED)
		{
			DEVICE_IO_CONTROL_END;
			return VIGEM_ERROR_INVALID_TARGET;
		}
	}

	DEVICE_IO_CONTROL_END;

	return VIGEM_ERROR_NONE;
}

VIGEM_ERROR vigem_target_ds4_update_ex(
	PVIGEM_CLIENT vigem,
	PVIGEM_TARGET target,
	DS4_REPORT_EX report
)
{
	if (!vigem)
		return VIGEM_ERROR_BUS_INVALID_HANDLE;

	if (!target)
		return VIGEM_ERROR_INVALID_TARGET;

	if (vigem->hBusDevice == INVALID_HANDLE_VALUE)
		return VIGEM_ERROR_BUS_NOT_FOUND;

	if (target->SerialNo == 0)
		return VIGEM_ERROR_INVALID_TARGET;

	DEVICE_IO_CONTROL_BEGIN;

	DS4_SUBMIT_REPORT_EX dsr;
	DS4_SUBMIT_REPORT_EX_INIT(&dsr, target->SerialNo);

	dsr.Report = report;

	DeviceIoControl(
		vigem->hBusDevice,
		IOCTL_DS4_SUBMIT_REPORT, // Same IOCTL, just different size
		&dsr,
		dsr.Size,
		nullptr,
		0,
		&transferred,
		&lOverlapped
	);

	if (GetOverlappedResult(vigem->hBusDevice, &lOverlapped, &transferred, TRUE) == 0)
	{
		if (GetLastError() == ERROR_ACCESS_DENIED)
		{
			DEVICE_IO_CONTROL_END;
			return VIGEM_ERROR_INVALID_TARGET;
		}

		/*
		 * NOTE: this will not happen on v1.16 due to NTSTATUS accidentally been set
		 * as STATUS_SUCCESS when the submitted buffer size wasn't the expected one.
		 * For backwards compatibility this function will silently fail (not cause
		 * report updates) when run with the v1.16 driver. This API was introduced
		 * with v1.17 so it won't affect existing applications built before.
		 */
		if (GetLastError() == ERROR_INVALID_PARAMETER)
		{
			DEVICE_IO_CONTROL_END;
			return VIGEM_ERROR_NOT_SUPPORTED;
		}
	}

	DEVICE_IO_CONTROL_END;

	return VIGEM_ERROR_NONE;
}
#endif // VIGEM_DS4

ULONG vigem_target_get_index(PVIGEM_TARGET target)
{
	return target->SerialNo;
}

VIGEM_TARGET_TYPE vigem_target_get_type(PVIGEM_TARGET target)
{
	return target->Type;
}

BOOL vigem_target_is_attached(PVIGEM_TARGET target)
{
	return (target->State == VIGEM_TARGET_CONNECTED);
}

VIGEM_ERROR vigem_target_x360_get_user_index(
	PVIGEM_CLIENT vigem,
	PVIGEM_TARGET target,
	PULONG index
)
{
	if (!vigem)
		return VIGEM_ERROR_BUS_INVALID_HANDLE;

	if (!target)
		return VIGEM_ERROR_INVALID_TARGET;

	if (vigem->hBusDevice == INVALID_HANDLE_VALUE)
		return VIGEM_ERROR_BUS_NOT_FOUND;

	if (target->SerialNo == 0 || target->Type != Xbox360Wired)
		return VIGEM_ERROR_INVALID_TARGET;

	if (!index)
		return VIGEM_ERROR_INVALID_PARAMETER;

	DEVICE_IO_CONTROL_BEGIN;

	XUSB_GET_USER_INDEX gui;
	XUSB_GET_USER_INDEX_INIT(&gui, target->SerialNo);

	DeviceIoControl(
		vigem->hBusDevice,
		IOCTL_XUSB_GET_USER_INDEX,
		&gui,
		gui.Size,
		&gui,
		gui.Size,
		&transferred,
		&lOverlapped
	);

	if (GetOverlappedResult(vigem->hBusDevice, &lOverlapped, &transferred, TRUE) == 0)
	{
		const auto error = GetLastError();

		if (error == ERROR_ACCESS_DENIED)
		{
			DEVICE_IO_CONTROL_END;
			return VIGEM_ERROR_INVALID_TARGET;
		}

		if (error == ERROR_INVALID_DEVICE_OBJECT_PARAMETER)
		{
			DEVICE_IO_CONTROL_END;
			return VIGEM_ERROR_XUSB_USERINDEX_OUT_OF_RANGE;
		}
	}

	DEVICE_IO_CONTROL_END;

	*index = gui.UserIndex;

	return VIGEM_ERROR_NONE;
}

#ifdef VIGEM_DS4
VIGEM_ERROR vigem_target_ds4_await_output_report(
	PVIGEM_CLIENT vigem,
	PVIGEM_TARGET target,
	PDS4_OUTPUT_BUFFER buffer
)
{
	return vigem_target_ds4_await_output_report_timeout(vigem, target, INFINITE, buffer);
}

VIGEM_ERROR vigem_target_ds4_await_output_report_timeout(
	PVIGEM_CLIENT vigem,
	PVIGEM_TARGET target,
	DWORD milliseconds,
	PDS4_OUTPUT_BUFFER buffer
)
{
	if (!vigem)
		return VIGEM_ERROR_BUS_INVALID_HANDLE;

	if (!target)
		return VIGEM_ERROR_INVALID_TARGET;

	if (vigem->hBusDevice == INVALID_HANDLE_VALUE)
		return VIGEM_ERROR_BUS_NOT_FOUND;

	if (target->SerialNo == 0 || target->Type != DualShock4Wired)
		return VIGEM_ERROR_INVALID_TARGET;

	if (!buffer)
		return VIGEM_ERROR_INVALID_PARAMETER;

	VIGEM_ERROR error = VIGEM_ERROR_NONE;

	EnterCriticalSection(&target->Ds4CachedOutputReportUpdateLock);
	{
		if (!target->IsDisposing)
		{
			const DWORD status = WaitForSingleObject(target->Ds4CachedOutputReportUpdateAvailable, milliseconds);

			if (status == WAIT_TIMEOUT)
			{
				error = VIGEM_ERROR_TIMED_OUT;
			}
			else
			{
#if defined(VIGEM_VERBOSE_LOGGING_ENABLED)
				DBGPRINT(L"Dumping buffer for %d", target->SerialNo);

				const PCHAR dumpBuffer = (PCHAR)calloc(sizeof(DS4_OUTPUT_BUFFER), 3);
				to_hex(target->Ds4CachedOutputReport.Buffer, sizeof(DS4_OUTPUT_BUFFER), dumpBuffer, sizeof(DS4_OUTPUT_BUFFER) * 3);
				OutputDebugStringA(dumpBuffer);
#endif

				RtlCopyMemory(buffer, &target->Ds4CachedOutputReport, sizeof(DS4_OUTPUT_BUFFER));
			}
		}
		else
		{
			error = VIGEM_ERROR_IS_DISPOSING;
		}
	}
	LeaveCriticalSection(&target->Ds4CachedOutputReportUpdateLock);

	return error;
}
#endif // VIGEM_DS4

VIGEM_ERROR vigem_target_x360_get_output(
    PVIGEM_CLIENT vigem,
    PVIGEM_TARGET target,
    PXUSB_OUTPUT_DATA output
)
{
    if (!vigem)
        return VIGEM_ERROR_BUS_INVALID_HANDLE;

    if (!target)
        return VIGEM_ERROR_INVALID_TARGET;

    if (vigem->hBusDevice == INVALID_HANDLE_VALUE)
        return VIGEM_ERROR_BUS_NOT_FOUND;

    if (target->SerialNo == 0 || target->Type != Xbox360Wired)
        return VIGEM_ERROR_INVALID_TARGET;

    if (!output)
        return VIGEM_ERROR_INVALID_PARAMETER;

    DWORD transferred = 0;
    OVERLAPPED lOverlapped = { 0 };
    lOverlapped.hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    XUSB_REQUEST_NOTIFICATION xrn;
    XUSB_REQUEST_NOTIFICATION_INIT(&xrn, target->SerialNo);

    DeviceIoControl(
        vigem->hBusDevice,
        IOCTL_XUSB_REQUEST_NOTIFICATION,
        &xrn,
        xrn.Size,
        &xrn,
        xrn.Size,
        &transferred,
        &lOverlapped
    );

    if (GetOverlappedResult(vigem->hBusDevice, &lOverlapped, &transferred, TRUE) == 0)
    {
        return VIGEM_ERROR_INVALID_TARGET;
    }

    CloseHandle(lOverlapped.hEvent);

    output->LargeMotor = xrn.LargeMotor;
    output->SmallMotor = xrn.SmallMotor;
    output->LedNumber = xrn.LedNumber;

    return VIGEM_ERROR_NONE;
}

#ifdef VIGEM_DS4
VIGEM_ERROR vigem_target_ds4_get_output(
    PVIGEM_CLIENT vigem,
    PVIGEM_TARGET target,
    PDS4_OUTPUT_DATA output
)
{
    if (!vigem)
        return VIGEM_ERROR_BUS_INVALID_HANDLE;

    if (!target)
        return VIGEM_ERROR_INVALID_TARGET;

    if (vigem->hBusDevice == INVALID_HANDLE_VALUE)
        return VIGEM_ERROR_BUS_NOT_FOUND;

    if (target->SerialNo == 0 || target->Type != DualShock4Wired)
        return VIGEM_ERROR_INVALID_TARGET;

    if (!output)
        return VIGEM_ERROR_INVALID_PARAMETER;

    DWORD transferred = 0;
    OVERLAPPED lOverlapped = { 0 };
    lOverlapped.hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    DS4_REQUEST_NOTIFICATION ds4rn;
    DS4_REQUEST_NOTIFICATION_INIT(&ds4rn, target->SerialNo);

    DeviceIoControl(
        vigem->hBusDevice,
        IOCTL_DS4_REQUEST_NOTIFICATION,
        &ds4rn,
        ds4rn.Size,
        &ds4rn,
        ds4rn.Size,
        &transferred,
        &lOverlapped
    );

    if (GetOverlappedResult(vigem->hBusDevice, &lOverlapped, &transferred, TRUE) == 0)
    {
        return VIGEM_ERROR_INVALID_TARGET;
    }

    CloseHandle(lOverlapped.hEvent);

    output->LargeMotor = ds4rn.Report.LargeMotor;
    output->SmallMotor = ds4rn.Report.SmallMotor;
    output->LightbarColor = ds4rn.Report.LightbarColor;

    return VIGEM_ERROR_NONE;
}
#endif // VIGEM_DS4

}; // namespace GPViGEm

int WINAPI UIViGEm(BOOL on)
{
	#pragma GPLINKER_DLL_EXPORT

	static GPViGEm::PVIGEM_CLIENT client;
	static GPViGEm::PVIGEM_TARGET targets[4];
	static HANDLE thread;
	if (on == !!client) return 0;

	if (!client)
	{
		client = GPViGEm::vigem_alloc();
		GPViGEm::VIGEM_ERROR connect_error = GPViGEm::vigem_connect(client);
		if (connect_error != GPViGEm::VIGEM_ERROR_NONE)
		{
			GPViGEm::vigem_free(client);
			client = nullptr;
			WriteLog("ViGEm Connect Error %x\n", (unsigned)connect_error);
			return (int)connect_error;
		}

		struct Local
		{
			static DWORD WINAPI ThreadFunc(void*)
			{
				Sleep(100); // wait a bit before starting up to let main thread finish up more of the controller setup
				for (unsigned i = 0;; i = ((i + 1) % 4))
				{
					Sleep(1);
					GPGamepad& gp = pGPData->Gamepads[i % 4];
					if (!gp.Used) continue;
					RunInputUpdaters(gp);

					GPViGEm::PVIGEM_TARGET& target = targets[i];
					if (!target)
					{
						target = GPViGEm::vigem_target_x360_alloc();

						GPViGEm::VIGEM_ERROR target_error = GPViGEm::vigem_target_add(client, target);
						if (target_error != GPViGEm::VIGEM_ERROR_NONE)
						{
							WriteLog("ViGEm Target Add Error %x\n", (unsigned)target_error);
							return 0;
						}
						ULONG user_index;
						GPViGEm::vigem_target_x360_get_user_index(client, target, &user_index);
						WriteLog("Mapped Gamepad Phoenix Controller #%d to ViGEm XBox 360 Controller #%d\n", i + 1, (int)user_index + 1);
					}

					GPViGEm::XUSB_REPORT report;
					const unsigned short* vals = gp.Vals, gpOptions = pGPData->Options;
					int gpidx_btn_a     = ((gpOptions & OPTION_SwapAandB) ? GPIDX_BTN_B : GPIDX_BTN_A);
					int gpidx_btn_b     = ((gpOptions & OPTION_SwapAandB) ? GPIDX_BTN_A : GPIDX_BTN_B);
					int gpidx_trigger_l = ((gpOptions & OPTION_SwapL1R1andL2R2) ? GPIDX_BTN_L : GPIDX_TRIGGER_L);
					int gpidx_trigger_r = ((gpOptions & OPTION_SwapL1R1andL2R2) ? GPIDX_BTN_R : GPIDX_TRIGGER_R);
					int gpidx_btn_l     = ((gpOptions & OPTION_SwapL1R1andL2R2) ? GPIDX_TRIGGER_L : GPIDX_BTN_L);
					int gpidx_btn_r     = ((gpOptions & OPTION_SwapL1R1andL2R2) ? GPIDX_TRIGGER_R : GPIDX_BTN_R);
					bool mergeDPad = !!(gpOptions & OPTION_DPadToLStick);

					report.sThumbLY = (short)(gp.Axis(GPIDX_LSTICK_U, mergeDPad) * 0x7FFF / 0xFFFF) - (short)(gp.Axis(GPIDX_LSTICK_D, mergeDPad) * 0x8000 / 0xFFFF);
					report.sThumbLX = (short)(gp.Axis(GPIDX_LSTICK_R, mergeDPad) * 0x7FFF / 0xFFFF) - (short)(gp.Axis(GPIDX_LSTICK_L, mergeDPad) * 0x8000 / 0xFFFF);
					report.sThumbRY = (short)(gp.Axis(GPIDX_RSTICK_U           ) * 0x7FFF / 0xFFFF) - (short)(gp.Axis(GPIDX_RSTICK_D           ) * 0x8000 / 0xFFFF);
					report.sThumbRX = (short)(gp.Axis(GPIDX_RSTICK_R           ) * 0x7FFF / 0xFFFF) - (short)(gp.Axis(GPIDX_RSTICK_L           ) * 0x8000 / 0xFFFF);
					report.bLeftTrigger  = (BYTE)(vals[gpidx_trigger_l] * 0xFF / 0xFFFF);
					report.bRightTrigger = (BYTE)(vals[gpidx_trigger_r] * 0xFF / 0xFFFF);
					report.wButtons = 0
						| ((vals[GPIDX_DPAD_U     ] & 0x8000u) >> 15) //GPXI_GAMEPAD_DPAD_UP        = 0x0001,
						| ((vals[GPIDX_DPAD_D     ] & 0x8000u) >> 14) //GPXI_GAMEPAD_DPAD_DOWN      = 0x0002,
						| ((vals[GPIDX_DPAD_L     ] & 0x8000u) >> 13) //GPXI_GAMEPAD_DPAD_LEFT      = 0x0004,
						| ((vals[GPIDX_DPAD_R     ] & 0x8000u) >> 12) //GPXI_GAMEPAD_DPAD_RIGHT     = 0x0008,
						| ((vals[GPIDX_BTN_START  ] & 0x8000u) >> 11) //GPXI_GAMEPAD_START          = 0x0010,
						| ((vals[GPIDX_BTN_BACK   ] & 0x8000u) >> 10) //GPXI_GAMEPAD_BACK           = 0x0020,
						| ((vals[GPIDX_BTN_LSTICK ] & 0x8000u) >>  9) //GPXI_GAMEPAD_LEFT_THUMB     = 0x0040,
						| ((vals[GPIDX_BTN_RSTICK ] & 0x8000u) >>  8) //GPXI_GAMEPAD_RIGHT_THUMB    = 0x0080,
						| ((vals[gpidx_btn_l      ] & 0x8000u) >>  7) //GPXI_GAMEPAD_LEFT_SHOULDER  = 0x0100,
						| ((vals[gpidx_btn_r      ] & 0x8000u) >>  6) //GPXI_GAMEPAD_RIGHT_SHOULDER = 0x0200,
						| ((vals[gpidx_btn_a      ] & 0x8000u) >>  3) //GPXI_GAMEPAD_A              = 0x1000,
						| ((vals[gpidx_btn_b      ] & 0x8000u) >>  2) //GPXI_GAMEPAD_B              = 0x2000,
						| ((vals[GPIDX_BTN_X      ] & 0x8000u) >>  1) //GPXI_GAMEPAD_X              = 0x4000,
						| ((vals[GPIDX_BTN_Y      ] & 0x8000u) >>  0) //GPXI_GAMEPAD_Y              = 0x8000,
						;


					GPViGEm::vigem_target_x360_update(client, target, report);
				}
			}
		};
		thread = CreateThread(0, 0, (DWORD (WINAPI *)(LPVOID))Local::ThreadFunc, NULL, 0, 0);
	}
	else
	{
		TerminateThread(thread, 0);
		CloseHandle(thread);
		thread = NULL;

		for (GPViGEm::PVIGEM_TARGET& target : targets)
		{
			if (!target) continue;
			GPViGEm::vigem_target_remove(client, target);
			GPViGEm::vigem_target_free(target);
			target = NULL;
		}

		GPViGEm::vigem_disconnect(client);
		GPViGEm::vigem_free(client);
		client = NULL;
	}
	return 0;
}
