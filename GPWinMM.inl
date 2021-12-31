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

namespace GPWinMM {

enum
{
	GPMM_SYSERR_NOERROR      = 0,  /* no error */
	GPMM_SYSERR_ERROR        = 1,  /* unspecified error */
	GPMM_SYSERR_BADDEVICEID  = 2,  /* device ID out of range */
	GPMM_SYSERR_NOTENABLED   = 3,  /* driver failed enable */
	GPMM_SYSERR_ALLOCATED    = 4,  /* device already allocated */
	GPMM_SYSERR_INVALHANDLE  = 5,  /* device handle is invalid */
	GPMM_SYSERR_NODRIVER     = 6,  /* no device driver present */
	GPMM_SYSERR_NOMEM        = 7,  /* memory allocation error */
	GPMM_SYSERR_NOTSUPPORTED = 8,  /* function isn't supported */
	GPMM_SYSERR_BADERRNUM    = 9,  /* error value out of range */
	GPMM_SYSERR_INVALFLAG    = 10, /* invalid flag passed */
	GPMM_SYSERR_INVALPARAM   = 11, /* invalid parameter passed */
	GPMM_SYSERR_HANDLEBUSY   = 12, /* handle being used simultaneously on another thread (eg callback) */
	GPMM_SYSERR_INVALIDALIAS = 13, /* specified alias not found */
	GPMM_SYSERR_BADDB        = 14, /* bad registry database */
	GPMM_SYSERR_KEYNOTFOUND  = 15, /* registry key not found */
	GPMM_SYSERR_READERROR    = 16, /* registry read error */
	GPMM_SYSERR_WRITEERROR   = 17, /* registry write error */
	GPMM_SYSERR_DELETEERROR  = 18, /* registry delete error */
	GPMM_SYSERR_VALNOTFOUND  = 19, /* registry value not found */
	GPMM_SYSERR_NODRIVERCB   = 20, /* driver does not call DriverCallback */
	GPMM_SYSERR_MOREDATA     = 21, /* more data to be returned */
	GPMM_SYSERR_LASTERROR    = 21, /* last error in range */
	GPMM_JOYERR_PARMS        = (160+5), /* bad parameters */
	GPMM_JOYERR_NOCANDO      = (160+6), /* request not completed */
	GPMM_JOYERR_UNPLUGGED    = (160+7), /* joystick is unplugged */

	/* constants used with JOYINFO and JOYINFOEX structures and MM_JOY* messages */
	GPMM_JOY_BUTTON1         = 0x0001,
	GPMM_JOY_BUTTON2         = 0x0002,
	GPMM_JOY_BUTTON3         = 0x0004,
	GPMM_JOY_BUTTON4         = 0x0008,
	GPMM_JOY_BUTTON1CHG      = 0x0100,
	GPMM_JOY_BUTTON2CHG      = 0x0200,
	GPMM_JOY_BUTTON3CHG      = 0x0400,
	GPMM_JOY_BUTTON4CHG      = 0x0800,

	/* constants used with JOYINFOEX */
	GPMM_JOY_BUTTON5         = 0x00000010,
	GPMM_JOY_BUTTON6         = 0x00000020,
	GPMM_JOY_BUTTON7         = 0x00000040,
	GPMM_JOY_BUTTON8         = 0x00000080,
	GPMM_JOY_BUTTON9         = 0x00000100,
	GPMM_JOY_BUTTON10        = 0x00000200,
	GPMM_JOY_BUTTON11        = 0x00000400,
	GPMM_JOY_BUTTON12        = 0x00000800,
	GPMM_JOY_BUTTON13        = 0x00001000,
	GPMM_JOY_BUTTON14        = 0x00002000,
	GPMM_JOY_BUTTON15        = 0x00004000,
	GPMM_JOY_BUTTON16        = 0x00008000,
	GPMM_JOY_BUTTON17        = 0x00010000,
	GPMM_JOY_BUTTON18        = 0x00020000,
	GPMM_JOY_BUTTON19        = 0x00040000,
	GPMM_JOY_BUTTON20        = 0x00080000,
	GPMM_JOY_BUTTON21        = 0x00100000,
	GPMM_JOY_BUTTON22        = 0x00200000,
	GPMM_JOY_BUTTON23        = 0x00400000,
	GPMM_JOY_BUTTON24        = 0x00800000,
	GPMM_JOY_BUTTON25        = 0x01000000,
	GPMM_JOY_BUTTON26        = 0x02000000,
	GPMM_JOY_BUTTON27        = 0x04000000,
	GPMM_JOY_BUTTON28        = 0x08000000,
	GPMM_JOY_BUTTON29        = 0x10000000,
	GPMM_JOY_BUTTON30        = 0x20000000,
	GPMM_JOY_BUTTON31        = 0x40000000,
	GPMM_JOY_BUTTON32        = 0x80000000,

	/* constants used with JOYINFOEX structure */
	GPMM_JOY_POVCENTERED  = 0xFFFFFFFF,
	GPMM_JOY_POVFORWARD   = 0,
	GPMM_JOY_POVRIGHT     = 9000,
	GPMM_JOY_POVBACKWARD  = 18000,
	GPMM_JOY_POVLEFT      = 27000,

	GPMM_JOY_RETURNX             = 0x00000001,
	GPMM_JOY_RETURNY             = 0x00000002,
	GPMM_JOY_RETURNZ             = 0x00000004,
	GPMM_JOY_RETURNR             = 0x00000008,
	GPMM_JOY_RETURNU             = 0x00000010, /* axis 5 */
	GPMM_JOY_RETURNV             = 0x00000020, /* axis 6 */
	GPMM_JOY_RETURNPOV           = 0x00000040,
	GPMM_JOY_RETURNBUTTONS       = 0x00000080,
	GPMM_JOY_RETURNRAWDATA       = 0x00000100,
	GPMM_JOY_RETURNPOVCTS        = 0x00000200,
	GPMM_JOY_RETURNCENTERED      = 0x00000400,
	GPMM_JOY_USEDEADZONE         = 0x00000800,
	GPMM_JOY_RETURNALL           = (GPMM_JOY_RETURNX | GPMM_JOY_RETURNY | GPMM_JOY_RETURNZ | GPMM_JOY_RETURNR | GPMM_JOY_RETURNU | GPMM_JOY_RETURNV | GPMM_JOY_RETURNPOV | GPMM_JOY_RETURNBUTTONS),
	GPMM_JOY_CAL_READALWAYS      = 0x00010000,
	GPMM_JOY_CAL_READXYONLY      = 0x00020000,
	GPMM_JOY_CAL_READ3           = 0x00040000,
	GPMM_JOY_CAL_READ4           = 0x00080000,
	GPMM_JOY_CAL_READXONLY       = 0x00100000,
	GPMM_JOY_CAL_READYONLY       = 0x00200000,
	GPMM_JOY_CAL_READ5           = 0x00400000,
	GPMM_JOY_CAL_READ6           = 0x00800000,
	GPMM_JOY_CAL_READZONLY       = 0x01000000,
	GPMM_JOY_CAL_READRONLY       = 0x02000000,
	GPMM_JOY_CAL_READUONLY       = 0x04000000,
	GPMM_JOY_CAL_READVONLY       = 0x08000000,

	/* joystick ID constants */
	GPMM_JOYSTICKID1     = 0,
	GPMM_JOYSTICKID2     = 1,

	/* joystick driver capabilites */
	GPMM_JOYCAPS_HASZ    = 0x0001,
	GPMM_JOYCAPS_HASR    = 0x0002,
	GPMM_JOYCAPS_HASU    = 0x0004,
	GPMM_JOYCAPS_HASV    = 0x0008,
	GPMM_JOYCAPS_HASPOV  = 0x0010,
	GPMM_JOYCAPS_POV4DIR = 0x0020,
	GPMM_JOYCAPS_POVCTS  = 0x0040,
};

struct GPJoyInfoEx
{
	DWORD dwSize;                /* size of structure */
	DWORD dwFlags;               /* flags to indicate what to return */
	DWORD dwXpos, dwYpos, dwZpos, dwRpos, dwUpos, dwVpos; // x/y/z/rudder/5th/6th axis position
	DWORD dwButtons;             /* button states */
	DWORD dwButtonNumber;        /* current button number pressed */
	DWORD dwPOV;                 /* point of view state */
	DWORD dwReserved1, dwReserved2;
};

struct GPJoyCaps
{
	WORD wMid, wPid;                 // manufacturer/product ID
	union { WCHAR szPname[32]; char szPnameA[32]; }; // product name (NULL terminated string)
	struct Extra
	{
		UINT wXmin, wXmax, wYmin, wYmax, wZmin, wZmax; // min/max x/y/z position values
		UINT wNumButtons;             // number of buttons */
		UINT wPeriodMin, wPeriodMax;  // minimum/maximum message period when captured */
		UINT wRmin, wRmax, wUmin, wUmax, wVmin, wVmax; // min/max rudder/5th/6th axis position values
		UINT wCaps;                 /* joystick capabilites */
		UINT wMaxAxes;              /* maximum number of axes supported */
		UINT wNumAxes;              /* number of axes in use */
		UINT wMaxButtons;           /* maximum number of buttons supported */
		union { WCHAR szRegKey[32]; char szRegKeyA[32]; };   // registry key
		union { WCHAR szOEMVxD[260]; char szOEMVxDA[260]; }; // OEM VxD in use
	};
	Extra* GetExtra(bool isW) const { return (Extra*)((char*)&extra - (isW ? 0 : 32)); }
	DWORD GetSize(bool isW) const { return (DWORD)sizeof(*this) - (DWORD)(isW ? 0 : (32+32+260)); }
	void SetStrings(bool isW, const WCHAR* pname, const WCHAR* regkey, const WCHAR* oemvxd)
	{
		if (isW) { wcscpy(szPname, pname); wcscpy(extra.szRegKey, regkey); wcscpy(extra.szOEMVxD, oemvxd); }
		else { WideCharToMultiByte(CP_ACP, 0, pname, -1, szPnameA, 32, NULL, NULL); WideCharToMultiByte(CP_ACP, 0, regkey, -1, GetExtra(false)->szRegKeyA, 32, NULL, NULL); WideCharToMultiByte(CP_ACP, 0, oemvxd, -1, GetExtra(false)->szOEMVxDA, 260, NULL, NULL); }
	}
	private: Extra extra;
};
GPSTATIC_ASSERT(sizeof(GPJoyCaps) == 4+32*2+76+32*2+260*2);

struct GPJoyInfo { UINT wXpos, wYpos, wZpos, wButtons; };

// All but GPjoyGetNumDevs return error code (0 means no error)
static UINT WINAPI GPjoyConfigChanged(DWORD dwFlags)
{
	return 0;
}

static bool CheckStarted(UINT_PTR uJoyID)
{
	static bool Started[GPData::NUM_GAMEPADS], Logged[GPData::NUM_GAMEPADS];
	if (uJoyID >= GPData::NUM_GAMEPADS) return false;
	if (Started[uJoyID]) return true;
	if ((pGPData->Options & (OPTION_Disable_MMSys|OPTION_Disable_XInput)) == OPTION_Disable_MMSys)
	{
		GameUsesXInput = true;
	}
	else if (pGPData->Options & OPTION_Disable_MMSys)
	{
		if (Logged[uJoyID]) return false;
		WriteLog("Application tried to %s %s %s %d but the interface is disabled, returning no connected device\n", "read input for", "WinMM", "joystick", (int)(uJoyID + 1));
		Logged[uJoyID] = true;
		return false;
	}
	bool isXInputPad = (GameUsesXInput && !ForceVirtualDevices && !(pGPData->Options & OPTION_Disable_XInput));
	WriteLog("Application started reading input for %s %s %d%s\n", "WinMM", "joystick", (int)(uJoyID + 1) + 1, (isXInputPad ? " (simulating XInput gamepad because XInput was also loaded)" : ""));
	Started[uJoyID] = true;
	return true;
}

static UINT WINAPI GPjoyGetDevCaps(bool isW, UINT_PTR uJoyID, GPJoyCaps* pjc, UINT cbjc)
{
	if (!pjc || cbjc != pjc->GetSize(isW)) return GPMM_SYSERR_INVALPARAM;
	if (!CheckStarted(uJoyID)) return GPMM_SYSERR_NODRIVER;
	if (!pGPData->Gamepads[uJoyID].Used) return GPMM_JOYERR_UNPLUGGED;

	if (!GameUsesXInput) ForceVirtualDevices = true; // if the caller has seen virtual devices once, keep returning only virtual devices
	bool isXInputPad = (GameUsesXInput && !ForceVirtualDevices && !(pGPData->Options & OPTION_Disable_XInput));
	bool usePOVtoButtons = (!isXInputPad && (pGPData->Options & OPTION_DI_POVtoButtons));
	bool useTriggersToButtons = (!isXInputPad && (pGPData->Options & OPTION_DI_TriggersToButtons));

	pjc->wMid = (WORD)(0x2000);
	pjc->wPid = (WORD)(0x2000 + uJoyID);
	pjc->SetStrings(isW, L"GamepadPhoenix", L"DINPUT.DLL", L"");
	auto* e = pjc->GetExtra(isW);
	e->wXmin = e->wYmin = e->wZmin = e->wRmin = e->wUmin = e->wVmin = 0;
	e->wXmax = e->wYmax = e->wZmax = e->wRmax = e->wUmax = e->wVmax = 0xFFFF;
	e->wNumButtons = 10 + (usePOVtoButtons ? 4 : 0) + (useTriggersToButtons ? 2 : 0);
	e->wPeriodMin  = 10;
	e->wPeriodMax = 1000;
	e->wCaps = GPMM_JOYCAPS_HASR | GPMM_JOYCAPS_HASU
		| (usePOVtoButtons ? 0 : GPMM_JOYCAPS_HASPOV | GPMM_JOYCAPS_POV4DIR)
		| (isXInputPad ? GPMM_JOYCAPS_HASZ : (useTriggersToButtons ? 0 : GPMM_JOYCAPS_HASV | GPMM_JOYCAPS_HASZ));
	e->wMaxAxes = 6;
	e->wNumAxes = (isXInputPad ? 5 : (useTriggersToButtons ? 4 : 6));
	e->wMaxButtons = 32;
	return 0;
}
static UINT WINAPI GPjoyGetDevCapsA(UINT_PTR uJoyID, GPJoyCaps* pjc, UINT cbjc) { return GPjoyGetDevCaps(false, uJoyID, pjc, cbjc); }
static UINT WINAPI GPjoyGetDevCapsW(UINT_PTR uJoyID, GPJoyCaps* pjc, UINT cbjc) { return GPjoyGetDevCaps(true, uJoyID, pjc, cbjc); }

static UINT WINAPI GPjoyGetNumDevs(VOID)
{
	UINT n = GPData::NUM_GAMEPADS;
	while (--n) if (pGPData->Gamepads[n].Used) break;
	return n + 1;
}

static UINT WINAPI GPjoyGetPos(UINT uJoyID, GPJoyInfo* pji)
{
	if (!pji) return GPMM_SYSERR_INVALPARAM;
	if (!CheckStarted(uJoyID)) return GPMM_SYSERR_NODRIVER;
	GPGamepad& gp = pGPData->Gamepads[uJoyID];
	if (!gp.Used) return GPMM_JOYERR_UNPLUGGED;

	bool isXInputPad = (GameUsesXInput && !ForceVirtualDevices && !(pGPData->Options & OPTION_Disable_XInput));
	bool usePOVtoButtons = (!isXInputPad && (pGPData->Options & OPTION_DI_POVtoButtons));
	bool useTriggersToButtons = (!isXInputPad && (pGPData->Options & OPTION_DI_TriggersToButtons));
	const unsigned short* vals = gp.Vals;
	RunInputUpdaters(gp);

	if (pGPData->Options & OPTION_DPadToLStick)
	{
		pji->wXpos = 0x7FFF + (UINT)(gp.MergeLStickAndDPad(GPIDX_LSTICK_R) * 0x8000 / 0xFFFF) - (UINT)(gp.MergeLStickAndDPad(GPIDX_LSTICK_L) * 0x7FFF / 0xFFFF);
		pji->wYpos = 0x7FFF + (UINT)(gp.MergeLStickAndDPad(GPIDX_LSTICK_D) * 0x8000 / 0xFFFF) - (UINT)(gp.MergeLStickAndDPad(GPIDX_LSTICK_U) * 0x7FFF / 0xFFFF);
	}
	else
	{
		pji->wXpos = 0x7FFF + (UINT)(vals[GPIDX_LSTICK_R] * 0x8000 / 0xFFFF) - (UINT)(vals[GPIDX_LSTICK_L] * 0x7FFF / 0xFFFF);
		pji->wYpos = 0x7FFF + (UINT)(vals[GPIDX_LSTICK_D] * 0x8000 / 0xFFFF) - (UINT)(vals[GPIDX_LSTICK_U] * 0x7FFF / 0xFFFF);
	}
	int gpidx_btn_a     = ((pGPData->Options & OPTION_SwapAandB) ? GPIDX_BTN_B : GPIDX_BTN_A);
	int gpidx_btn_b     = ((pGPData->Options & OPTION_SwapAandB) ? GPIDX_BTN_A : GPIDX_BTN_B);
	int gpidx_trigger_l = ((pGPData->Options & OPTION_SwapL1R1andL2R2) ? GPIDX_BTN_L : GPIDX_TRIGGER_L);
	int gpidx_trigger_r = ((pGPData->Options & OPTION_SwapL1R1andL2R2) ? GPIDX_BTN_R : GPIDX_TRIGGER_R);
	int gpidx_btn_l     = ((pGPData->Options & OPTION_SwapL1R1andL2R2) ? GPIDX_TRIGGER_L : GPIDX_BTN_L);
	int gpidx_btn_r     = ((pGPData->Options & OPTION_SwapL1R1andL2R2) ? GPIDX_TRIGGER_R : GPIDX_BTN_R);
	pji->wButtons = 0
			| ((vals[gpidx_btn_a      ] & 0x8000u) >> 15)
			| ((vals[gpidx_btn_b      ] & 0x8000u) >> 14)
			| ((vals[GPIDX_BTN_X      ] & 0x8000u) >> 13)
			| ((vals[GPIDX_BTN_Y      ] & 0x8000u) >> 12)
			| ((vals[gpidx_btn_l      ] & 0x8000u) >> 11)
			| ((vals[gpidx_btn_r      ] & 0x8000u) >> 10)
			| ((vals[GPIDX_BTN_START  ] & 0x8000u) >>  9)
			| ((vals[GPIDX_BTN_BACK   ] & 0x8000u) >>  8)
			| ((vals[GPIDX_BTN_LSTICK ] & 0x8000u) >>  7)
			| ((vals[GPIDX_BTN_RSTICK ] & 0x8000u) >>  6)
			;
	if (isXInputPad)
		pji->wZpos = 0x7FFF + (UINT)(vals[gpidx_trigger_l] * 0x7F81 / 0xFFFF) - (UINT)(vals[gpidx_trigger_r] * 0x7F7F / 0xFFFF);
	else
		pji->wZpos = 0x7FFF + (UINT)(vals[gpidx_trigger_l] * 0x8000 / 0xFFFF);
	if (usePOVtoButtons)
		pji->wButtons |= 0
			| ((vals[GPIDX_DPAD_U     ] & 0x8000u) >> 5)
			| ((vals[GPIDX_DPAD_D     ] & 0x8000u) >> 4)
			| ((vals[GPIDX_DPAD_L     ] & 0x8000u) >> 3)
			| ((vals[GPIDX_DPAD_R     ] & 0x8000u) >> 2);
	if (useTriggersToButtons)
		pji->wZpos = 0, pji->wButtons |= 0
			| ((vals[gpidx_trigger_l  ] & 0x8000u) >> 1)
			| ((vals[gpidx_trigger_r  ] & 0x8000u) >> 0);
	return 0;
}

static UINT WINAPI GPjoyGetPosEx(UINT uJoyID, GPJoyInfoEx* pji)
{
	if (!pji || pji->dwSize != sizeof(*pji)) return GPMM_SYSERR_INVALPARAM;
	if (uJoyID == 0xFFFF || uJoyID == 0xFFFFFFFF) uJoyID = 0;
	GPJoyInfo ji;
	UINT res = GPjoyGetPos(uJoyID, &ji);
	if (res) return res;

	bool isXInputPad = (GameUsesXInput && !ForceVirtualDevices && !(pGPData->Options & OPTION_Disable_XInput));
	bool usePOVtoButtons = (!isXInputPad && (pGPData->Options & OPTION_DI_POVtoButtons));
	bool useTriggersToButtons = (!isXInputPad && (pGPData->Options & OPTION_DI_TriggersToButtons));
	const unsigned short* vals = pGPData->Gamepads[uJoyID].Vals;

	pji->dwButtons = pji->dwButtonNumber = 0;
	if (pji->dwFlags & GPMM_JOY_RETURNBUTTONS)
	{
		pji->dwButtons = ji.wButtons;
		for (UINT i = 1; (ji.wButtons & ~(i-1)) && i; i <<= 1)
			if (ji.wButtons & i)
				pji->dwButtonNumber++;
	}
	pji->dwXpos = ji.wXpos;
	pji->dwYpos = ji.wYpos;
	pji->dwZpos = ji.wZpos;
	pji->dwRpos = 0x7FFF - (UINT)(vals[GPIDX_RSTICK_L] * 0x7FFF / 0xFFFF) + (UINT)(vals[GPIDX_RSTICK_R] * 0x8000 / 0xFFFF);
	pji->dwUpos = 0x7FFF - (UINT)(vals[GPIDX_RSTICK_U] * 0x7FFF / 0xFFFF) + (UINT)(vals[GPIDX_RSTICK_D] * 0x8000 / 0xFFFF);
	if (!isXInputPad && !useTriggersToButtons)
		pji->dwVpos = 0x7FFF + (UINT)(vals[(pGPData->Options & OPTION_SwapL1R1andL2R2) ? GPIDX_BTN_R : GPIDX_TRIGGER_R] * 0x8000 / 0xFFFF);
	if (!usePOVtoButtons)
	{
		unsigned int mask =
			((vals[GPIDX_DPAD_U] & 0x8000u) >> 15) | // 1 UP
			((vals[GPIDX_DPAD_D] & 0x8000u) >> 14) | // 2 DOWN
			((vals[GPIDX_DPAD_L] & 0x8000u) >> 13) | // 4 LEFT
			((vals[GPIDX_DPAD_R] & 0x8000u) >> 12);  // 8 RIGHT
		static const DWORD DPADDatas[] = { 0xFFFF, 0, 18000, 0xFFFF, 27000, 31500, 22500, 27000, 9000, 4500, 13500, 9000, 0xFFFF, 0, 18000, 0xFFFF };
		pji->dwPOV = DPADDatas[mask];
	}
	return 0;
}

static UINT WINAPI GPjoyGetThreshold(UINT uJoyID, LPUINT puThreshold)
{
	if (!puThreshold) return GPMM_SYSERR_INVALPARAM;
	if (!CheckStarted(uJoyID)) return GPMM_SYSERR_NODRIVER;
	if (!pGPData->Gamepads[uJoyID].Used) return GPMM_JOYERR_UNPLUGGED;
	*puThreshold = 0;
	return 0;
}

static UINT WINAPI GPjoyReleaseCapture(UINT uJoyID)
{
	return GPMM_JOYERR_NOCANDO;
}

static UINT WINAPI GPjoySetCapture(HWND hwnd, UINT uJoyID, UINT uPeriod, BOOL fChanged)
{
	return GPMM_JOYERR_NOCANDO;
}

static UINT WINAPI GPjoySetThreshold(UINT uJoyID, UINT uThreshold)
{
	if (!CheckStarted(uJoyID)) return GPMM_SYSERR_NODRIVER;
	if (!pGPData->Gamepads[uJoyID].Used) return GPMM_JOYERR_UNPLUGGED;
	if (!uThreshold) return 0;
	return GPMM_JOYERR_NOCANDO;
}

static void Hook()
{
	LOGSCOPE();
	GPCHECKNORECURSION();

	static bool hookedWinMM;
	if (hookedWinMM) return;
	HMODULE hmWinMM = GetModuleHandleA("winmm");
	if (!hmWinMM) return;
	hookedWinMM = true;

	CreateHook(hmWinMM,  "joyConfigChanged",  GPjoyConfigChanged,  false);
	CreateHook(hmWinMM,  "joyGetDevCapsA",    GPjoyGetDevCapsA,    false);
	CreateHook(hmWinMM,  "joyGetDevCapsW",    GPjoyGetDevCapsW,    false);
	CreateHook(hmWinMM,  "joyGetNumDevs",     GPjoyGetNumDevs,     false);
	CreateHook(hmWinMM,  "joyGetPos",         GPjoyGetPos,         false);
	CreateHook(hmWinMM,  "joyGetPosEx",       GPjoyGetPosEx,       false);
	CreateHook(hmWinMM,  "joyGetThreshold",   GPjoyGetThreshold,   false);
	CreateHook(hmWinMM,  "joyReleaseCapture", GPjoyReleaseCapture, false);
	CreateHook(hmWinMM,  "joySetCapture",     GPjoySetCapture,     false);
	CreateHook(hmWinMM,  "joySetThreshold",   GPjoySetThreshold,   true);
	WriteLog("Intercepting WinMM interface\n");
}

}; // namespace GPWinMM
