/* Gamepad Phoenix
* Copyright (c) 2021-2022 Bernhard Schelling
*
* Gamepad Phoenix is free software: you can redistribute it and/or modify it under the terms
* of the GNU General Public License as published by the Free Software Found-
* ation, either version 3 of the License, or (at your option) any later version.
*
* Gamepad Phoenix is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
* PURPOSE. See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with Gamepad Phoenix.
* If not, see <http://www.gnu.org/licenses/>.
*/

namespace GPXInput {

enum
{
	GPXI_GAMEPAD_DPAD_UP        = 0x0001,
	GPXI_GAMEPAD_DPAD_DOWN      = 0x0002,
	GPXI_GAMEPAD_DPAD_LEFT      = 0x0004,
	GPXI_GAMEPAD_DPAD_RIGHT     = 0x0008,
	GPXI_GAMEPAD_START          = 0x0010,
	GPXI_GAMEPAD_BACK           = 0x0020,
	GPXI_GAMEPAD_LEFT_THUMB     = 0x0040,
	GPXI_GAMEPAD_RIGHT_THUMB    = 0x0080,
	GPXI_GAMEPAD_LEFT_SHOULDER  = 0x0100,
	GPXI_GAMEPAD_RIGHT_SHOULDER = 0x0200,
	GPXI_GAMEPAD_A              = 0x1000,
	GPXI_GAMEPAD_B              = 0x2000,
	GPXI_GAMEPAD_X              = 0x4000,
	GPXI_GAMEPAD_Y              = 0x8000,
	GPXI_GAMEPAD_ALL_BUTTONS    = 0xF3FF,
	GPXI_GAMEPAD_GUIDE          = 0x0400,

	GPXI_KEYSTROKE_KEYDOWN      = 0x0001,
	GPXI_KEYSTROKE_KEYUP        = 0x0002,
	GPXI_KEYSTROKE_REPEAT       = 0x0004,

	GPXI_PAD_A                  = 0x5800,
	GPXI_PAD_B                  = 0x5801,
	GPXI_PAD_X                  = 0x5802,
	GPXI_PAD_Y                  = 0x5803,
	GPXI_PAD_RSHOULDER          = 0x5804,
	GPXI_PAD_LSHOULDER          = 0x5805,
	GPXI_PAD_LTRIGGER           = 0x5806,
	GPXI_PAD_RTRIGGER           = 0x5807,
	GPXI_PAD_DPAD_UP            = 0x5810,
	GPXI_PAD_DPAD_DOWN          = 0x5811,
	GPXI_PAD_DPAD_LEFT          = 0x5812,
	GPXI_PAD_DPAD_RIGHT         = 0x5813,
	GPXI_PAD_START              = 0x5814,
	GPXI_PAD_BACK               = 0x5815,
	GPXI_PAD_LTHUMB_PRESS       = 0x5816,
	GPXI_PAD_RTHUMB_PRESS       = 0x5817,
	GPXI_PAD_LTHUMB_UP          = 0x5820,
	GPXI_PAD_LTHUMB_DOWN        = 0x5821,
	GPXI_PAD_LTHUMB_RIGHT       = 0x5822,
	GPXI_PAD_LTHUMB_LEFT        = 0x5823,
	GPXI_PAD_LTHUMB_UPLEFT      = 0x5824,
	GPXI_PAD_LTHUMB_UPRIGHT     = 0x5825,
	GPXI_PAD_LTHUMB_DOWNRIGHT   = 0x5826,
	GPXI_PAD_LTHUMB_DOWNLEFT    = 0x5827,
	GPXI_PAD_RTHUMB_UP          = 0x5830,
	GPXI_PAD_RTHUMB_DOWN        = 0x5831,
	GPXI_PAD_RTHUMB_RIGHT       = 0x5832,
	GPXI_PAD_RTHUMB_LEFT        = 0x5833,
	GPXI_PAD_RTHUMB_UPLEFT      = 0x5834,
	GPXI_PAD_RTHUMB_UPRIGHT     = 0x5835,
	GPXI_PAD_RTHUMB_DOWNRIGHT   = 0x5836,
	GPXI_PAD_RTHUMB_DOWNLEFT    = 0x5837,

	GPXI_GAMEPAD_LEFT_THUMB_DEADZONE  = 7849,
	GPXI_GAMEPAD_RIGHT_THUMB_DEADZONE = 8689,
	GPXI_GAMEPAD_TRIGGER_THRESHOLD    = 30,

	GPXI_DEVTYPE_GAMEPAD         = 0x01,
	GPXI_DEVSUBTYPE_GAMEPAD      = 0x01,
	GPXI_DEVSUBTYPE_WHEEL        = 0x02,
	GPXI_DEVSUBTYPE_ARCADE_STICK = 0x03,
	GPXI_DEVSUBTYPE_FLIGHT_SICK  = 0x04,
	GPXI_DEVSUBTYPE_DANCE_PAD    = 0x05,
	GPXI_DEVSUBTYPE_GUITAR       = 0x06,
	GPXI_DEVSUBTYPE_DRUM_KIT     = 0x08,

	GPXI_CAPS_VOICE_SUPPORTED    = 0x0004,
	GPXI_FLAG_GAMEPAD            = 0x00000001,

	GPXI_BATTERY_DEVTYPE_GAMEPAD        = 0x00,
	GPXI_BATTERY_DEVTYPE_HEADSET        = 0x01,
	GPXI_BATTERY_TYPE_DISCONNECTED      = 0x00,
	GPXI_BATTERY_TYPE_WIRED             = 0x01,
	GPXI_BATTERY_TYPE_ALKALINE          = 0x02,
	GPXI_BATTERY_TYPE_NIMH              = 0x03,
	GPXI_BATTERY_TYPE_UNKNOWN           = 0xFF,
	GPXI_BATTERY_LEVEL_EMPTY            = 0x00,
	GPXI_BATTERY_LEVEL_LOW              = 0x01,
	GPXI_BATTERY_LEVEL_MEDIUM           = 0x02,
	GPXI_BATTERY_LEVEL_FULL             = 0x03,

	GPXI_XUSER_MAX_COUNT                = 4,
	GPXI_XUSER_INDEX_ANY                = 0x000000FF,
};
GPSTATIC_ASSERT(GPData::NUM_GAMEPADS >= GPXI_XUSER_MAX_COUNT);

struct GPXINPUT_GAMEPAD
{
	WORD wButtons;
	BYTE bLeftTrigger, bRightTrigger;
	SHORT sThumbLX, sThumbLY, sThumbRX, sThumbRY;
};

struct GPXINPUT_STATE
{
	DWORD dwPacketNumber;
	GPXINPUT_GAMEPAD Gamepad;
};

struct GPXINPUT_VIBRATION
{
	WORD wLeftMotorSpeed, wRightMotorSpeed;
};

struct GPXINPUT_CAPABILITIES
{
	BYTE Type, SubType;
	WORD Flags;
	GPXINPUT_GAMEPAD Gamepad;
	GPXINPUT_VIBRATION Vibration;
};

struct GPXINPUT_KEYSTROKE
{
	WORD VirtualKey;
	WCHAR Unicode;
	WORD Flags;
	BYTE UserIndex, HidCode;
};

struct GPXINPUT_BATTERY_INFORMATION
{
	BYTE BatteryType, BatteryLevel;
};

static bool CheckStarted(DWORD dwUserIndex)
{
	static bool Started[GPXI_XUSER_MAX_COUNT], Logged[GPXI_XUSER_MAX_COUNT];
	if (Started[dwUserIndex]) return true;
	if (pGPData->Options & OPTION_Disable_XInput)
	{
		if (Logged[dwUserIndex]) return false;
		WriteLog("Application tried to %s %s %s %d but the interface is disabled, returning no connected device\n", "read input for", "XInput", "pad", (int)(dwUserIndex + 1));
		Logged[dwUserIndex] = true;
		return false;
	}
	WriteLog("Application started reading input for %s %s %d%s\n", "XInput", "pad", (int)(dwUserIndex + 1), "");
	Started[dwUserIndex] = true;
	return true;
}

typedef DWORD (WINAPI *GPXInputGetStateFN)(DWORD dwUserIndex, GPXINPUT_STATE* pState);
static GPXInputGetStateFN OrgGetState;
DWORD WINAPI GPXInputGetState(DWORD dwUserIndex, GPXINPUT_STATE* pState)
{
	#pragma GPLINKER_DLL_EXPORT_AS_HINT(XInputGetState, 2)
	LOGSCOPE("dwUserIndex: %u - pState: %p - Prev PacketNumber: %u - %s", dwUserIndex, pState, pState->dwPacketNumber, (dwUserIndex >= GPXI_XUSER_MAX_COUNT ? "INVALID USER INDEX" : (pGPData->Gamepads[dwUserIndex].Used ? "CONNECTED GAMEPAD" : "GAMEPAD NOT CONNECTED")));
	if (!GameUsesXInput) GameUsesXInput = true;
	if (dwUserIndex >= GPXI_XUSER_MAX_COUNT) return ERROR_BAD_ARGUMENTS;

	GPGamepad& gp = pGPData->Gamepads[dwUserIndex];
	if (!gp.Used || !CheckStarted(dwUserIndex)) return ERROR_DEVICE_NOT_CONNECTED;

	RunInputUpdaters(gp);
	const unsigned short* vals = gp.Vals;
	int gpidx_btn_a     = ((pGPData->Options & OPTION_SwapAandB) ? GPIDX_BTN_B : GPIDX_BTN_A);
	int gpidx_btn_b     = ((pGPData->Options & OPTION_SwapAandB) ? GPIDX_BTN_A : GPIDX_BTN_B);
	int gpidx_trigger_l = ((pGPData->Options & OPTION_SwapL1R1andL2R2) ? GPIDX_BTN_L : GPIDX_TRIGGER_L);
	int gpidx_trigger_r = ((pGPData->Options & OPTION_SwapL1R1andL2R2) ? GPIDX_BTN_R : GPIDX_TRIGGER_R);
	int gpidx_btn_l     = ((pGPData->Options & OPTION_SwapL1R1andL2R2) ? GPIDX_TRIGGER_L : GPIDX_BTN_L);
	int gpidx_btn_r     = ((pGPData->Options & OPTION_SwapL1R1andL2R2) ? GPIDX_TRIGGER_R : GPIDX_BTN_R);

	if (pGPData->Options & OPTION_DPadToLStick)
	{
		pState->Gamepad.sThumbLY = (short)(gp.MergeLStickAndDPad(GPIDX_LSTICK_U) * 0x7FFF / 0xFFFF) - (short)(gp.MergeLStickAndDPad(GPIDX_LSTICK_D) * 0x8000 / 0xFFFF);
		pState->Gamepad.sThumbLX = (short)(gp.MergeLStickAndDPad(GPIDX_LSTICK_R) * 0x7FFF / 0xFFFF) - (short)(gp.MergeLStickAndDPad(GPIDX_LSTICK_L) * 0x8000 / 0xFFFF);
	}
	else
	{
		pState->Gamepad.sThumbLY = (short)(vals[GPIDX_LSTICK_U] * 0x7FFF / 0xFFFF) - (short)(vals[GPIDX_LSTICK_D] * 0x8000 / 0xFFFF);
		pState->Gamepad.sThumbLX = (short)(vals[GPIDX_LSTICK_R] * 0x7FFF / 0xFFFF) - (short)(vals[GPIDX_LSTICK_L] * 0x8000 / 0xFFFF);
	}
	pState->Gamepad.sThumbRY = (short)(vals[GPIDX_RSTICK_U] * 0x7FFF / 0xFFFF) - (short)(vals[GPIDX_RSTICK_D] * 0x8000 / 0xFFFF);
	pState->Gamepad.sThumbRX = (short)(vals[GPIDX_RSTICK_R] * 0x7FFF / 0xFFFF) - (short)(vals[GPIDX_RSTICK_L] * 0x8000 / 0xFFFF);
	pState->Gamepad.bLeftTrigger  = (BYTE)(vals[gpidx_trigger_l] * 0xFF / 0xFFFF);
	pState->Gamepad.bRightTrigger = (BYTE)(vals[gpidx_trigger_r] * 0xFF / 0xFFFF);
	pState->Gamepad.wButtons = 0
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

	// dwPacketNumber must start at 1 for some games
	static GPXINPUT_STATE PrevState[GPXI_XUSER_MAX_COUNT];// = { { 1, { 0,0,0,0,0,0,0} }, { 1, { 0,0,0,0,0,0,0} }, { 1, { 0,0,0,0,0,0,0} }, { 1, { 0,0,0,0,0,0,0} }, };
	GPXINPUT_STATE* prev = &PrevState[dwUserIndex];
	if (memcmp(&pState->Gamepad, &prev->Gamepad, sizeof(pState->Gamepad)))
	{
		prev->Gamepad = pState->Gamepad;
		prev->dwPacketNumber++;
	}
	pState->dwPacketNumber = prev->dwPacketNumber;
	return ERROR_SUCCESS;
}

DWORD WINAPI GPXInputSetState(DWORD dwUserIndex, GPXINPUT_VIBRATION* pVibration)
{
	#pragma GPLINKER_DLL_EXPORT_AS_HINT(XInputSetState, 3)
	//WriteLog("[GPXInputSetState] dwUserIndex: %u - pVibration: %p\n", dwUserIndex, pVibration);
	if (!GameUsesXInput) GameUsesXInput = true;
	if (dwUserIndex >= GPXI_XUSER_MAX_COUNT || !pVibration) return ERROR_BAD_ARGUMENTS;
	if (!pGPData->Gamepads[dwUserIndex].Used || !CheckStarted(dwUserIndex)) return ERROR_DEVICE_NOT_CONNECTED;
	//TODO: Vibration
	return ERROR_SUCCESS;
}

DWORD WINAPI GPXInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, GPXINPUT_CAPABILITIES* pCapabilities)
{
	#pragma GPLINKER_DLL_EXPORT_AS_HINT(XInputGetCapabilities, 4)
	//WriteLog("[GPXInputGetCapabilities] dwUserIndex: %u - dwFlags: 0x%x - pCapabilities: %p\n", dwUserIndex, dwFlags, pCapabilities);
	if (!GameUsesXInput) GameUsesXInput = true;
	if (dwUserIndex >= GPXI_XUSER_MAX_COUNT || (dwFlags & ~GPXI_FLAG_GAMEPAD) || !pCapabilities) return ERROR_BAD_ARGUMENTS;
	if (!pGPData->Gamepads[dwUserIndex].Used || !CheckStarted(dwUserIndex)) return ERROR_DEVICE_NOT_CONNECTED;
	pCapabilities->Type = GPXI_DEVTYPE_GAMEPAD;
	pCapabilities->SubType = GPXI_DEVSUBTYPE_GAMEPAD;
	pCapabilities->Flags = 12;
	pCapabilities->Gamepad.wButtons = GPXI_GAMEPAD_ALL_BUTTONS;
	pCapabilities->Gamepad.bLeftTrigger = pCapabilities->Gamepad.bRightTrigger = (BYTE)-1;
	pCapabilities->Gamepad.sThumbLX = pCapabilities->Gamepad.sThumbLY = pCapabilities->Gamepad.sThumbRX = pCapabilities->Gamepad.sThumbRY = (SHORT)0xffc0;
	pCapabilities->Vibration.wLeftMotorSpeed = pCapabilities->Vibration.wRightMotorSpeed = 0xff; //TODO
	return ERROR_SUCCESS;
}

void WINAPI GPXInputEnable(BOOL enable) // not in xinput9_1_0
{
	#pragma GPLINKER_DLL_EXPORT_AS_HINT(XInputEnable, 5)
	if (!GameUsesXInput) GameUsesXInput = true;
	//WriteLog("[GPXInputEnable] UNSUPPORTED - enable: %d\n", enable);
	//DEBUGBREAKONCE
	//fpXInputEnable(enable);
}

DWORD WINAPI GPXInputGetDSoundAudioDeviceGuids(DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid) //not in xinput1_4
{
	#pragma GPLINKER_DLL_EXPORT_AS_HINT(XInputGetDSoundAudioDeviceGuids, 6)
	//WriteLog("[GPXInputGetDSoundAudioDeviceGuids] dwUserIndex: %u - pDSoundRenderGuid: %p - pDSoundCaptureGuid: %p\n", dwUserIndex, pDSoundRenderGuid, pDSoundCaptureGuid);
	if (dwUserIndex >= GPXI_XUSER_MAX_COUNT) return ERROR_BAD_ARGUMENTS;
	if (!pGPData->Gamepads[dwUserIndex].Used || !CheckStarted(dwUserIndex)) return ERROR_DEVICE_NOT_CONNECTED;
	if (pDSoundRenderGuid) memset(pDSoundRenderGuid, 0, sizeof(*pDSoundRenderGuid));
	if (pDSoundCaptureGuid) memset(pDSoundCaptureGuid, 0, sizeof(*pDSoundCaptureGuid));
	//DEBUGBREAKONCE
	return ERROR_SUCCESS;
}

DWORD WINAPI GPXInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, GPXINPUT_BATTERY_INFORMATION* pBatteryInformation) // only in xinput1_3 and xinput1_4
{
	#pragma GPLINKER_DLL_EXPORT_AS_HINT(XInputGetBatteryInformation, 7)
	//WriteLog("[GPXInputGetBatteryInformation] dwUserIndex: %u - devType: %u - pBatteryInformation: %p\n", dwUserIndex, devType, pBatteryInformation);
	if (dwUserIndex >= GPXI_XUSER_MAX_COUNT) return ERROR_BAD_ARGUMENTS;
	if (!pGPData->Gamepads[dwUserIndex].Used || !CheckStarted(dwUserIndex)) return ERROR_DEVICE_NOT_CONNECTED;
	if (pBatteryInformation)
	{
		pBatteryInformation->BatteryType = (devType == GPXI_BATTERY_DEVTYPE_GAMEPAD ? GPXI_BATTERY_TYPE_WIRED : GPXI_BATTERY_TYPE_DISCONNECTED);
		pBatteryInformation->BatteryLevel = (devType == GPXI_BATTERY_DEVTYPE_GAMEPAD ? GPXI_BATTERY_LEVEL_FULL : GPXI_BATTERY_LEVEL_EMPTY);
	}
	return ERROR_SUCCESS;
}

DWORD WINAPI GPXInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, GPXINPUT_KEYSTROKE* pKeystroke) // only in xinput1_3 and xinput1_4
{
	#pragma GPLINKER_DLL_EXPORT_AS_HINT(XInputGetKeystroke, 8)
	//WriteLog("[GPXInputGetKeystroke] UNSUPPORTED - dwUserIndex: %u - dwReserved: 0x%x - pKeystroke: %p\n", dwUserIndex, dwReserved, pKeystroke);
	if (dwUserIndex >= GPXI_XUSER_MAX_COUNT) return ERROR_BAD_ARGUMENTS;
	if (!pGPData->Gamepads[dwUserIndex].Used || !CheckStarted(dwUserIndex)) return ERROR_DEVICE_NOT_CONNECTED;
	return ERROR_EMPTY; //fpXInputGetKeystroke(dwUserIndex, dwReserved, pKeystroke);
}

DWORD WINAPI GPXInputGetAudioDeviceIds(DWORD dwUserIndex, LPWSTR pRenderDeviceId, UINT *pRenderCount, LPWSTR pCaptureDeviceId, UINT *pCaptureCount) //only in xinput1_4
{
	#pragma GPLINKER_DLL_EXPORT_AS_HINT(XInputGetAudioDeviceIds, 10)
	//WriteLog("[GPXInputGetAudioDeviceIds] dwUserIndex: %u - pRenderDeviceId: %p - pRenderCount: %p - pCaptureDeviceId: %p - pCaptureCount: %p\n", dwUserIndex, pRenderDeviceId, pRenderCount, pCaptureDeviceId, pCaptureCount);
	if (dwUserIndex >= GPXI_XUSER_MAX_COUNT) return ERROR_BAD_ARGUMENTS;
	if (!pGPData->Gamepads[dwUserIndex].Used || !CheckStarted(dwUserIndex)) return ERROR_DEVICE_NOT_CONNECTED;
	if (pRenderCount && *pRenderCount) { *pRenderDeviceId = '\0'; *pRenderCount = 0; }
	if (pCaptureCount && *pCaptureCount) { *pCaptureDeviceId = '\0'; *pCaptureCount = 0; }
	return ERROR_SUCCESS;
}

DWORD WINAPI GPXInputGetStateEx(DWORD dwUserIndex, GPXINPUT_STATE* pState) // hidden function Ordinal 100
{
	#pragma GPLINKER_DLL_EXPORT_UNNAMED(100)
	//WriteLog("[GPXInputGetStateEx] dwUserIndex: %u - pState: %p\n", dwUserIndex, pState);
	return GPXInputGetState(dwUserIndex, pState);
}

DWORD WINAPI GPXInputWaitForGuideButton(DWORD dwUserIndex, DWORD dwFlag, void* pUnknown) // hidden function Ordinal 101
{
	#pragma GPLINKER_DLL_EXPORT_UNNAMED(101)
	//WriteLog("[GPXInputWaitForGuideButton] UNSUPPORTED - dwUserIndex: %u - dwFlag: 0x%x - pUnknown: %p\n", dwUserIndex, dwFlag, pUnknown);
	return ERROR_SUCCESS; // do nothing for now
}

DWORD WINAPI GPXInputCancelGuideButtonWait(DWORD dwUserIndex) // hidden function Ordinal 102
{
	#pragma GPLINKER_DLL_EXPORT_UNNAMED(102)
	//WriteLog("[GPXInputCancelGuideButtonWait] UNSUPPORTED - dwUserIndex: %u\n", dwUserIndex);
	return ERROR_SUCCESS; // do nothing for now
}

DWORD WINAPI GPXInputPowerOffController(DWORD dwUserIndex) // hidden function Ordinal 103
{
	#pragma GPLINKER_DLL_EXPORT_UNNAMED(103)
	//WriteLog("[GPXInputPowerOffController] UNSUPPORTED - dwUserIndex: %u\n", dwUserIndex);
	return E_FAIL;
}

DWORD WINAPI GPXInputGetBaseBusInformation(DWORD dwUserIndex, DWORD dwFlags) // hidden function Ordinal 104
{
	#pragma GPLINKER_DLL_EXPORT_UNNAMED(104)
	//WriteLog("[GPXInputGetBaseBusInformation] UNSUPPORTED - dwUserIndex: %u - dwFlags: 0x%x\n", dwUserIndex, dwFlags);
	return E_FAIL;
}

DWORD WINAPI GPXInputGetCapabilitiesEx(DWORD a1, DWORD dwUserIndex, DWORD dwFlags, GPXINPUT_CAPABILITIES* pCapabilities) // hidden function Ordinal 108
{
	#pragma GPLINKER_DLL_EXPORT_UNNAMED(108)
	//WriteLog("[GPXInputGetCapabilitiesEx] a1: %u - dwUserIndex: %u - dwFlags: 0x%x - pCapabilities: %p\n", a1, dwUserIndex, dwFlags, pCapabilities);
	return GPXInputGetCapabilities(dwUserIndex, dwFlags, pCapabilities);
}

static void Hook(bool forceLoad = false)
{
	LOGSCOPE("forceLoad: %d", forceLoad);
	GPCHECKNORECURSION();
	wchar_t buf[512];
	wchar_t* base = buf + GetSystemDirectoryW(buf, 480) + 1, *ver = base + 6;
	wcscpy(base - 1, L"\\xinput");

	bool redoForceLoad = false;
	redo:
	static short LoadedNs;
	static HMODULE LoadedHms[10];
	if (LoadedNs == ((1<<10)-1)) return;
	for (unsigned char n = 0; n != 10; n++)
	{
		if (LoadedNs&(1<<n)) continue;

		enum { VERSIONCOUNT = 5, IDXVERSION910 = 4 };
		static const wchar_t* xinputVersions[VERSIONCOUNT] = { L"1_3", L"1_4", L"1_2", L"1_1", L"9_1_0" };
		wcscpy(ver, xinputVersions[n % VERSIONCOUNT]);
		wcscat(ver, L".dll");

		const wchar_t* path = (n < 5 ? buf : base);
		HMODULE hmXInput = (forceLoad ? fpLoadLibraryW : GetModuleHandleW)(path);
		if (!hmXInput) continue;
		LoadedHms[n] = hmXInput;
		LoadedNs |= (1<<n);
		if (LoadedHms[n + (n < 5 ? 5 : -5)] == hmXInput) continue;
		if (!forceLoad) GameUsesXInput = true;
		if (fpGetProcAddress(hmXInput, "UIPad")) continue; // skip if its our own fake DLL

		LPVOID pGetState = (LPVOID)fpGetProcAddress(hmXInput, "XInputGetState");
		LOGSCOPE("%s: %S - GetState: %p - AlreadyHooked: %d", (forceLoad ? "force loaded library" : "found already loaded module"), path, pGetState, AlreadyHooked(pGetState));
		if (!pGetState) continue;
		if (g_hHeap && !AlreadyHooked(pGetState, &pGetState)) // local path and system path is probably same file so check AlreadyHooked
		{
			if (!forceLoad) fpLoadLibraryW(path); // Increase reference count to keep hooked library loaded until process ends
			CreateHook(pGetState, "XInputGetState",                   GPXInputGetState,                  false, &pGetState);
			CreateHook(hmXInput,  "XInputSetState",                   GPXInputSetState,                  false);
			CreateHook(hmXInput,  "XInputGetCapabilities",            GPXInputGetCapabilities,           false);
			CreateHook(hmXInput,  "XInputEnable",                     GPXInputEnable,                    false);
			CreateHook(hmXInput,  "XInputGetKeystroke",               GPXInputGetKeystroke,              false);
			CreateHook(hmXInput,  "XInputGetBatteryInformation",      GPXInputGetBatteryInformation,     false);
			CreateHook(hmXInput,  "XInputGetDSoundAudioDeviceGuids",  GPXInputGetDSoundAudioDeviceGuids, false);
			CreateHook(hmXInput,  "XInputGetAudioDeviceIds",          GPXInputGetAudioDeviceIds,         false);
			CreateHook(hmXInput,  100, "XInputGetStateEx",            GPXInputGetStateEx,                false);
			CreateHook(hmXInput,  101, "XInputWaitForGuideButton",    GPXInputWaitForGuideButton,        false);
			CreateHook(hmXInput,  102, "XInputCancelGuideButtonWait", GPXInputCancelGuideButtonWait,     false);
			CreateHook(hmXInput,  103, "XInputPowerOffController",    GPXInputPowerOffController,        false);
			CreateHook(hmXInput,  104, "XInputGetBaseBusInformation", GPXInputGetBaseBusInformation,     false);
			CreateHook(hmXInput,  108, "XInputGetCapabilitiesEx",     GPXInputGetCapabilitiesEx,          true);
			WriteLog("Intercepting XInput DLL %S%s\n", path, (forceLoad ? " (also used by Gamepad Phoenix)" : ""));
			if (fpGetProcAddress(hmXInput, "Reset"))
				WriteLog("Detected usage of XInput emulator DLL, this might lead to unwanted results.\n");
		}
		if (!OrgGetState)
		{
			if ((n % VERSIONCOUNT) < IDXVERSION910 || forceLoad)
			{
				OrgGetState = (GPXInputGetStateFN)pGetState;
			}
			else
			{
				// Modern 9_1_0 DLLs internally redirect to newer DLL versions so we avoid its GetState in games that use 9_1_0.
				// If we didn't explicitly force load and use any of the new versions here, our hooks could get removed by
				// whatever 9_1_0 does internally once we start calling that GetState.
				redoForceLoad = true;
			}
		}
		if (forceLoad) return;
	}
	if (redoForceLoad) { forceLoad = true; goto redo; }
}

static void SetupInput()
{
	LOGSCOPE("XInput loaded already: %d", !!OrgGetState);
	if (!OrgGetState) Hook(true);
	if (!OrgGetState) return; // XInput not available on this system

	static GPXINPUT_STATE states[2][GPXI_XUSER_MAX_COUNT];
	struct GPXICallbacks
	{
		static void Update(GPGamepad& gp)
		{
			//LOGSCOPE("GP: %d", (&gp - pGPData->Gamepads));
			bool queried[GPXI_XUSER_MAX_COUNT] = { false, false, false, false };
			static unsigned char statebit;
			statebit ^= 1;

			for (unsigned int i = 0, devnum; i != _GPIDX_MAX; i++)
			{
				unsigned int gpId = gp.IDs[i];
				switch (GPIDGetInterface(gpId))
				{
					case GPIDINTERFACE_XINPUT:
						devnum = GPIDGetDevNum(gpId);
						if (devnum < GPXI_XUSER_MAX_COUNT)
						{
							GPXINPUT_STATE& state = states[statebit][devnum];
							if (!queried[devnum])
							{
								queried[devnum] = true;
								//LOGSCOPE("Call GetState %d", devnum);
								if (OrgGetState(devnum, &state) != ERROR_SUCCESS) memset(&state, 0, sizeof(state));
							}
							switch (GPIDGetObjNum(gpId))
							{
								case  0: gp.Vals[i] = (state.Gamepad.sThumbLY > 0 ? (unsigned short)(state.Gamepad.sThumbLY *  0xFFFF / 0x7FFF) : 0); break;
								case  1: gp.Vals[i] = (state.Gamepad.sThumbLY < 0 ? (unsigned short)(state.Gamepad.sThumbLY * -0xFFFF / 0x8000) : 0); break;
								case  2: gp.Vals[i] = (state.Gamepad.sThumbLX < 0 ? (unsigned short)(state.Gamepad.sThumbLX * -0xFFFF / 0x8000) : 0); break;
								case  3: gp.Vals[i] = (state.Gamepad.sThumbLX > 0 ? (unsigned short)(state.Gamepad.sThumbLX *  0xFFFF / 0x7FFF) : 0); break;
								case  4: gp.Vals[i] = (state.Gamepad.sThumbRY > 0 ? (unsigned short)(state.Gamepad.sThumbRY *  0xFFFF / 0x7FFF) : 0); break;
								case  5: gp.Vals[i] = (state.Gamepad.sThumbRY < 0 ? (unsigned short)(state.Gamepad.sThumbRY * -0xFFFF / 0x8000) : 0); break;
								case  6: gp.Vals[i] = (state.Gamepad.sThumbRX < 0 ? (unsigned short)(state.Gamepad.sThumbRX * -0xFFFF / 0x8000) : 0); break;
								case  7: gp.Vals[i] = (state.Gamepad.sThumbRX > 0 ? (unsigned short)(state.Gamepad.sThumbRX *  0xFFFF / 0x7FFF) : 0); break;
								case  8: gp.Vals[i] = (unsigned short)(state.Gamepad.bLeftTrigger  * 0xFFFF / 0xFF); break;
								case  9: gp.Vals[i] = (unsigned short)(state.Gamepad.bRightTrigger * 0xFFFF / 0xFF); break;
								case 10: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_DPAD_UP       ) ? 0xFFFF : 0); break;
								case 11: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_DPAD_DOWN     ) ? 0xFFFF : 0); break;
								case 12: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_DPAD_LEFT     ) ? 0xFFFF : 0); break;
								case 13: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_DPAD_RIGHT    ) ? 0xFFFF : 0); break;
								case 14: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_START         ) ? 0xFFFF : 0); break;
								case 15: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_BACK          ) ? 0xFFFF : 0); break;
								case 16: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_LEFT_THUMB    ) ? 0xFFFF : 0); break;
								case 17: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_RIGHT_THUMB   ) ? 0xFFFF : 0); break;
								case 18: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_LEFT_SHOULDER ) ? 0xFFFF : 0); break;
								case 19: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_RIGHT_SHOULDER) ? 0xFFFF : 0); break;
								case 20: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_A             ) ? 0xFFFF : 0); break;
								case 21: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_B             ) ? 0xFFFF : 0); break;
								case 22: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_X             ) ? 0xFFFF : 0); break;
								case 23: gp.Vals[i] = ((state.Gamepad.wButtons & GPXI_GAMEPAD_Y             ) ? 0xFFFF : 0); break;
							}
						}
						break;

					case GPIDINTERFACE_CAPTURE_NEXT_KEY:
						if (!(CaptureSources & (1 << GPIDINTERFACE_XINPUT))) break;
						for (devnum = 0; devnum != GPXI_XUSER_MAX_COUNT; devnum++)
						{
							GPXINPUT_STATE &state = states[statebit][devnum], &prev = states[!statebit][devnum];
							if (!queried[devnum])
							{
								queried[devnum] = true;
								if (OrgGetState(devnum, &state) != ERROR_SUCCESS) memset(&state, 0, sizeof(state));
							}
							unsigned int o =
								((state.Gamepad.sThumbLY >  0x4000 && prev.Gamepad.sThumbLY <=  0x4000) ? 0 :
								((state.Gamepad.sThumbLY < -0x4000 && prev.Gamepad.sThumbLY >= -0x4000) ? 1 :
								((state.Gamepad.sThumbLX < -0x4000 && prev.Gamepad.sThumbLX >= -0x4000) ? 2 :
								((state.Gamepad.sThumbLX >  0x4000 && prev.Gamepad.sThumbLX <=  0x4000) ? 3 :
								((state.Gamepad.sThumbRY >  0x4000 && prev.Gamepad.sThumbRY <=  0x4000) ? 4 :
								((state.Gamepad.sThumbRY < -0x4000 && prev.Gamepad.sThumbRY >= -0x4000) ? 5 :
								((state.Gamepad.sThumbRX < -0x4000 && prev.Gamepad.sThumbRX >= -0x4000) ? 6 :
								((state.Gamepad.sThumbRX >  0x4000 && prev.Gamepad.sThumbRX <=  0x4000) ? 7 :
								((state.Gamepad.bLeftTrigger  > 0x80 && prev.Gamepad.bLeftTrigger  <= 0x80) ? 8 :
								((state.Gamepad.bRightTrigger > 0x80 && prev.Gamepad.bRightTrigger <= 0x80) ? 9 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_DPAD_UP       ) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_DPAD_UP       )) ? 10 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_DPAD_DOWN     ) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_DPAD_DOWN     )) ? 11 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_DPAD_LEFT     ) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_DPAD_LEFT     )) ? 12 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_DPAD_RIGHT    ) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_DPAD_RIGHT    )) ? 13 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_START         ) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_START         )) ? 14 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_BACK          ) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_BACK          )) ? 15 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_LEFT_THUMB    ) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_LEFT_THUMB    )) ? 16 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_RIGHT_THUMB   ) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_RIGHT_THUMB   )) ? 17 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_LEFT_SHOULDER ) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_LEFT_SHOULDER )) ? 18 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_RIGHT_SHOULDER) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_RIGHT_SHOULDER)) ? 19 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_A             ) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_A             )) ? 20 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_B             ) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_B             )) ? 21 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_X             ) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_X             )) ? 22 :
								(((state.Gamepad.wButtons & GPXI_GAMEPAD_Y             ) && !(prev.Gamepad.wButtons & GPXI_GAMEPAD_Y             )) ? 23 :
								0xFF))))))))))))))))))))))));
							if (o == 0xFF) continue;
							gp.IDs[i] = GPIDMake(GPIDINTERFACE_XINPUT, devnum, o);
							break;
						}
						break;
				}
			}
		}
	};

	InputUpdaters.push_back(GPXICallbacks::Update);
}

}; // namespace GPXInput
