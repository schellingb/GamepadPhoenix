/* Gamepad Phoenix
* Copyright (c) 2021-2023 Bernhard Schelling
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

#include <ole2.h>
#include <dbt.h>

namespace GPDInput {

enum : unsigned int
{
	GPDI_VERSION_5 = 0x0500,
	GPDI_VERSION_6 = 0x0600,
	GPDI_VERSION_8 = 0x0800,

	GPDI8DEVCLASS_ALL          = 0,
	GPDI8DEVCLASS_DEVICE       = 1,
	GPDI8DEVCLASS_POINTER      = 2,
	GPDI8DEVCLASS_KEYBOARD     = 3,
	GPDI8DEVCLASS_GAMECTRL     = 4,
	GPDIDEVTYPE_MASK           = 0xFF,
	GPDI1DEVTYPE_DEVICE        = 1,
	GPDI1DEVTYPE_MOUSE         = 2,
	GPDI1DEVTYPE_KEYBOARD      = 3,
	GPDI1DEVTYPE_JOYSTICK      = 4,
	GPDIDEVTYPE_HID            = 0x00010000,
	GPDIDEVTYPE_NOHID          = 0,
	GPDI8DEVTYPE_DEVICE        = 0x11,
	GPDI8DEVTYPE_MOUSE         = 0x12,
	GPDI8DEVTYPE_KEYBOARD      = 0x13,
	GPDI8DEVTYPE_JOYSTICK      = 0x14,
	GPDI8DEVTYPE_GAMEPAD       = 0x15,
	GPDI8DEVTYPE_DRIVING       = 0x16,
	GPDI8DEVTYPE_FLIGHT        = 0x17,
	GPDI8DEVTYPE_1STPERSON     = 0x18,
	GPDI8DEVTYPE_DEVICECTRL    = 0x19,
	GPDI8DEVTYPE_SCREENPOINTER = 0x1A,
	GPDI8DEVTYPE_REMOTE        = 0x1B,
	GPDI8DEVTYPE_SUPPLEMENTAL  = 0x1C,
	GPDI8DEVTYPE_OVERRIDE_MIN  = GPDI8DEVTYPE_JOYSTICK,
	GPDI8DEVTYPE_OVERRIDE_MAX  = 0xFF, // hide everything that isn't mouse or keyboard

	GPDI8SUBDEVTYPE_JOYSTICK_UNKNOWN       = 1,
	GPDI8SUBDEVTYPE_JOYSTICK_TRADITIONAL   = 2,
	GPDI8SUBDEVTYPE_JOYSTICK_FLIGHTSTICK   = 3,
	GPDI8SUBDEVTYPE_JOYSTICK_GAMEPAD       = 4,
	GPDI8SUBDEVTYPE_JOYSTICK_RUDDER        = 5,
	GPDI8SUBDEVTYPE_JOYSTICK_WHEEL         = 6,
	GPDI8SUBDEVTYPE_JOYSTICK_HEADTRACKER   = 7,
	GPDI8SUBDEVTYPE_JOYSTICK_LIMITED       = 1,
	GPDI8SUBDEVTYPE_JOYSTICK_STANDARD      = 2,
	GPDI8SUBDEVTYPE_GAMEPAD_LIMITED        = 1,
	GPDI8SUBDEVTYPE_GAMEPAD_STANDARD       = 2,
	GPDI8SUBDEVTYPE_GAMEPAD_TILT           = 3,
	GPDI8SUBDEVTYPE_DRIVING_LIMITED        = 1,
	GPDI8SUBDEVTYPE_DRIVING_COMBINEDPEDALS = 2,
	GPDI8SUBDEVTYPE_DRIVING_DUALPEDALS     = 3,
	GPDI8SUBDEVTYPE_DRIVING_THREEPEDALS    = 4,
	GPDI8SUBDEVTYPE_DRIVING_HANDHELD       = 5,
	GPDI8SUBDEVTYPE_FLIGHT_LIMITED         = 1,
	GPDI8SUBDEVTYPE_FLIGHT_STICK           = 2,
	GPDI8SUBDEVTYPE_FLIGHT_YOKE            = 3,
	GPDI8SUBDEVTYPE_FLIGHT_RC              = 4,
	GPDI8SUBDEVTYPE_1STPERSON_LIMITED      = 1,
	GPDI8SUBDEVTYPE_1STPERSON_UNKNOWN      = 2,
	GPDI8SUBDEVTYPE_1STPERSON_SIXDOF       = 3,
	GPDI8SUBDEVTYPE_1STPERSON_SHOOTER      = 4,

	GPDIENUM_STOP                         = 0,
	GPDIENUM_CONTINUE                     = 1,

	GPDIEDFL_ALLDEVICES                   = 0x00000000,
	GPDIEDFL_ATTACHEDONLY                 = 0x00000001,
	GPDIEDFL_FORCEFEEDBACK                = 0x00000100,
	GPDIEDFL_INCLUDEALIASES               = 0x00010000,
	GPDIEDFL_INCLUDEPHANTOMS              = 0x00020000,
	GPDIEDFL_INCLUDEHIDDEN                = 0x00040000,

	GPDIPROP_BUFFERSIZE            = 1,
	GPDIPROP_AXISMODE              = 2,
	GPDIPROPAXISMODE_ABS           = 0,
	GPDIPROPAXISMODE_REL           = 1,
	GPDIPROP_GRANULARITY           = 3,
	GPDIPROP_RANGE                 = 4,
	GPDIPROP_DEADZONE              = 5,
	GPDIPROP_SATURATION            = 6,
	GPDIPROP_FFGAIN                = 7,
	GPDIPROP_FFLOAD                = 8,
	GPDIPROP_AUTOCENTER            = 9,
	GPDIPROPAUTOCENTER_OFF         = 0,
	GPDIPROPAUTOCENTER_ON          = 1,
	GPDIPROP_CALIBRATIONMODE       = 10,
	GPDIPROPCALIBRATIONMODE_COOKED = 0,
	GPDIPROPCALIBRATIONMODE_RAW    = 1,
	GPDI5PROP_CALIBRATION          = 11,
	GPDI5PROP_GUIDANDPATH          = 12,
	GPDI5PROP_INSTANCENAME         = 13,
	GPDI5PROP_PRODUCTNAME          = 14,
	GPDI5PROP_JOYSTICKID           = 15,
	GPDI5PROP_GETPORTDISPLAYNAME   = 16,
	GPDI7PROP_PHYSICALRANGE        = 18,
	GPDI7PROP_LOGICALRANGE         = 19,
	GPDI8PROP_KEYNAME              = 20,
	GPDI8PROP_CPOINTS              = 21,
	GPDI8PROP_APPDATA              = 22,
	GPDI8PROP_SCANCODE             = 23,
	GPDI8PROP_VIDPID               = 24,
	GPDI8PROP_USERNAME             = 25,
	GPDI8PROP_TYPENAME             = 26,

	GPDIODFGUID_XAxis              = 0xA36D02E0,
	GPDIODFGUID_YAxis              = 0xA36D02E1,
	GPDIODFGUID_ZAxis              = 0xA36D02E2,
	GPDIODFGUID_RzAxis             = 0xA36D02E3,
	GPDIODFGUID_Slider             = 0xA36D02E4,
	GPDIODFGUID_Button             = 0xA36D02F0,
	GPDIODFGUID_POV                = 0xA36D02F2,
	GPDIODFGUID_Unknown            = 0xA36D02F3,
	GPDIODFGUID_RxAxis             = 0xA36D02F4,
	GPDIODFGUID_RyAxis             = 0xA36D02F5,
	GPDIODFGUID_Key                = 0x55728220,

	GPDIDFT_ALL                    = 0x00000000,
	GPDIDFT_RELAXIS                = 0x00000001,
	GPDIDFT_ABSAXIS                = 0x00000002,
	GPDIDFT_AXIS                   = 0x00000003,
	GPDIDFT_PSHBUTTON              = 0x00000004,
	GPDIDFT_TGLBUTTON              = 0x00000008,
	GPDIDFT_BUTTON                 = 0x0000000C,
	GPDIDFT_POV                    = 0x00000010,
	GPDIDFT_COLLECTION             = 0x00000040,
	GPDIDFT_NODATA                 = 0x00000080,
	GPDIDFT_TYPEMASK               = 0x000000FF,
	GPDIDFT_ANYINSTANCE            = 0x00FFFF00,
	GPDIDFT_FFACTUATOR             = 0x01000000,
	GPDIDFT_FFEFFECTTRIGGER        = 0x02000000,
	GPDIDFT5_OUTPUT                = 0x10000000,
	GPDIDFT5_VENDORDEFINED         = 0x04000000,
	GPDIDFT5_ALIAS                 = 0x08000000,
	GPDIDFT_OPTIONAL               = 0x80000000,

	GPDIDOI_FFACTUATOR             = 0x00000001,
	GPDIDOI_FFEFFECTTRIGGER        = 0x00000002,
	GPDIDOI_ASPECTPOSITION         = 0x00000100,
	GPDIDOI_ASPECTVELOCITY         = 0x00000200,
	GPDIDOI_ASPECTACCEL            = 0x00000300,
	GPDIDOI_ASPECTFORCE            = 0x00000400,
	GPDIDOI_ASPECTMASK             = 0x00000F00,
	GPDIDOI_POLLED                 = 0x00008000,
	GPDIDOI5_GUIDISUSAGE           = 0x00010000,

	GPDISCL_EXCLUSIVE              = 0x00000001,
	GPDISCL_NONEXCLUSIVE           = 0x00000002,
	GPDISCL_FOREGROUND             = 0x00000004,
	GPDISCL_BACKGROUND             = 0x00000008,
	GPDISCL_NOWINKEY               = 0x00000010,

	GPDIDF_ABSAXIS                 = 0x00000001,
	GPDIDF_RELAXIS                 = 0x00000002,

	GPDIGDD_PEEK                   = 0x00000001,
	GPDI_MAX_KEYBOARD              = 256,

	GPDIPH_DEVICE                  = 0,
	GPDIPH_BYOFFSET                = 1,
	GPDIPH_BYID                    = 2,
	GPDIPH_BYUSAGE                 = 3,

	GPDI_IID_IDirectInput8A        = 0xBF798030, //bf798030-483a-4da2-aa99-5d64ed369700
	GPDI_IID_IDirectInput8W        = 0xBF798031, //bf798031-483a-4da2-aa99-5d64ed369700
	GPDI_IID_IDirectInput7A        = 0x9A4CB684, //9a4cb684-236d-11d3-8e9d-00c04f6844ae
	GPDI_IID_IDirectInput7W        = 0x9A4CB685, //9a4cb685-236d-11d3-8e9d-00c04f6844ae
	GPDI_IID_IDirectInput2A        = 0x5944E662, //5944e662-aa8a-11cf-bfc7-444553540000
	GPDI_IID_IDirectInput2W        = 0x5944E663, //5944e663-aa8a-11cf-bfc7-444553540000
	GPDI_IID_IDirectInputA         = 0x89521360, //89521360-aa8a-11cf-bfc7-444553540000
	GPDI_IID_IDirectInputW         = 0x89521361, //89521361-aa8a-11cf-bfc7-444553540000
	GPDI_IID_IDirectInputJoyConfig = 0xEB0D7DFA, //eb0d7dfa-1990-4f27-b4d6-edf2eec4a44c
	GPDI_IID_IWbemLocator          = 0xDC12A687, //dc12a687-737f-11cf-884d-00aa004b2e24
	GPDI_CLSID_DirectInput8        = 0x25E609E4, //25e609e4-b259-11cf-bfc7-444553540000
	GPDI_CLSID_DirectInput         = 0x25E609E0, //25e609e0-b259-11cf-bfc7-444553540000

	GPDIEDBSFL_ATTACHEDONLY        = 0x00000000,
	GPDIEDBSFL_THISUSER            = 0x00000010,
	GPDIEDBSFL_FORCEFEEDBACK       = GPDIEDFL_FORCEFEEDBACK,
	GPDIEDBSFL_AVAILABLEDEVICES    = 0x00001000,
	GPDIEDBSFL_MULTIMICEKEYBOARDS  = 0x00002000,
	GPDIEDBSFL_NONGAMINGDEVICES    = 0x00004000,
	GPDIEDBSFL_VALID               = 0x00007110,

	//GPDIERR_OLDDIRECTINPUTVERSION  = 0x8007047E,
	//GPDIERR_BETADIRECTINPUTVERSION = 0x80070481,
	//GPDIERR_BADDRIVERVER           = 0x80070077,
	GPDIERR_DEVICENOTREG           = 0x80040154,
	//GPDIERR_NOTFOUND               = 0x80070002,
	GPDIERR_OBJECTNOTFOUND           = 0x80070002,
	GPDIERR_INVALIDPARAM             = 0x80070057,
	//GPDIERR_NOINTERFACE            = 0x80004002,
	//GPDIERR_GENERIC                = 0x80004005,
	//GPDIERR_OUTOFMEMORY            = 0x8007000E,
	//GPDIERR_UNSUPPORTED            = 0x80004001,
	GPDIERR_NOTINITIALIZED           = 0x80070015,
	//GPDIERR_ALREADYINITIALIZED     = 0x800704DF,
	//GPDIERR_NOAGGREGATION          = 0x80040110,
	//GPDIERR_OTHERAPPHASPRIO        = 0x80070005,
	//GPDIERR_INPUTLOST              = 0x8007001E,
	//GPDIERR_ACQUIRED               = 0x800700AA,
	//GPDIERR_NOTACQUIRED            = 0x8007000C,
	//GPDIERR_READONLY               = 0x80070005,
	//GPDIERR_HANDLEEXISTS           = 0x80070005,
	//GPDIERR_PENDING                = 0x8000000A,
	//GPDIERR_INSUFFICIENTPRIVS      = 0x80040200,
	//GPDIERR_DEVICEFULL             = 0x80040201,
	//GPDIERR_MOREDATA               = 0x80040202,
	//GPDIERR_NOTDOWNLOADED          = 0x80040203,
	//GPDIERR_HASEFFECTS             = 0x80040204,
	//GPDIERR_NOTEXCLUSIVEACQUIRED   = 0x80040205,
	//GPDIERR_INCOMPLETEEFFECT       = 0x80040206,
	//GPDIERR_NOTBUFFERED            = 0x80040207,
	//GPDIERR_EFFECTPLAYING          = 0x80040208,
	//GPDIERR_UNPLUGGED              = 0x80040209,
	//GPDIERR_REPORTFULL             = 0x8004020A,
	//GPDIERR_MAPFILEFAIL            = 0x8004020B,
};

#define GPDIDFT_MAKEINSTANCE(n)  ((DWORD)(((DWORD)((n) & 0xffff)) << 8))
#define GPDIDFT_GETINSTANCE(n)   ((DWORD)(((DWORD)((n) >> 8)) & 0xffff))
#define GPDIMAKEDEVTYPE(DEVTYPE, SUBDEVTYPE, HIDFLAG) ((DEVTYPE) | ((SUBDEVTYPE)<<8) | (HIDFLAG))

struct GPDIDEVCAPS
{
	DWORD dwSize, dwFlags, dwDevType, dwAxes, dwButtons, dwPOVs;
	//DIRECTINPUT_VERSION >= GPDI_VERSION_5
	DWORD dwFFSamplePeriod, dwFFMinTimeResolution, dwFirmwareRevision, dwHardwareRevision, dwFFDriverVersion;
};

struct GPDIDeviceInstance
{
	DWORD dwSize;
	GUID guidInstance, guidProduct;
	DWORD dwDevType;
	union { struct { WCHAR tszInstanceName[MAX_PATH], tszProductName[MAX_PATH]; }; struct { char tszInstanceNameA[MAX_PATH], tszProductNameA[MAX_PATH]; }; };
	struct Extra
	{
		// DIRECTINPUT_VERSION >= GPDI_VERSION_5
		GUID guidFFDriver;
		WORD wUsagePage, wUsage;
	};
	Extra* GetExtra(bool isW) const { return (Extra*)((char*)&extra - (isW ? 0 : MAX_PATH+MAX_PATH)); }
	DWORD GetSize(bool isW) const { return (DWORD)sizeof(*this) - (DWORD)(isW ? 0 : MAX_PATH+MAX_PATH); }
	void SetStrings(bool isW, const WCHAR* instanceName, const WCHAR* productName)
	{
		if (isW) { wcscpy(tszInstanceName, instanceName); wcscpy(tszProductName, productName); }
		else { WideCharToMultiByte(CP_ACP, 0, instanceName, -1, tszInstanceNameA, MAX_PATH, NULL, NULL); WideCharToMultiByte(CP_ACP, 0, productName, -1, tszProductNameA, MAX_PATH, NULL, NULL); }
	}
	private: Extra extra;
};
GPSTATIC_ASSERT(sizeof(GPDIDeviceInstance) == 580+260+260);

struct GPDIDeviceObjectInstance
{
	DWORD dwSize;
	GUID guidType;
	DWORD dwOfs, dwType, dwFlags;
	union { WCHAR tszName[MAX_PATH]; char tszNameA[MAX_PATH]; };
	struct Extra
	{
		//DIRECTINPUT_VERSION >= GPDI_VERSION_5
		DWORD dwFFMaxForce, dwFFForceResolution;
		WORD wCollectionNumber, wDesignatorIndex, wUsagePage, wUsage;
		DWORD dwDimension;
		WORD wExponent, wReserved;
	};
	Extra* GetExtra(bool isW) const { return (Extra*)((char*)&extra - (isW ? 0 : MAX_PATH)); }
	DWORD GetSize(bool isW) const { return (DWORD)sizeof(*this) - (DWORD)(isW ? 0 : MAX_PATH); }
	void SetStrings(bool isW, const WCHAR* name)
	{
		if (isW) { wcscpy(tszName, name); }
		else { WideCharToMultiByte(CP_ACP, 0, name, -1, tszNameA, MAX_PATH, NULL, NULL); }
	}
	private: Extra extra;
};
GPSTATIC_ASSERT(sizeof(GPDIDeviceObjectInstance) == 316+260);

struct GPDIEffectInfo
{
	DWORD dwSize;
	GUID guid;
	DWORD dwEffType, dwStaticParams, dwDynamicParams;
	union { WCHAR tszName[MAX_PATH]; char tszNameA[MAX_PATH]; };
	void SetStrings(bool isW, const WCHAR* name)
	{
		if (isW) { wcscpy(tszName, name); }
		else { WideCharToMultiByte(CP_ACP, 0, name, -1, tszNameA, MAX_PATH, NULL, NULL); }
	}
};
GPSTATIC_ASSERT(sizeof(GPDIEffectInfo) == 32+260+260);

struct GPDIAction
{
	UINT_PTR uAppData;
	DWORD dwSemantic, dwFlags;
	union UAction { const WCHAR* lptszActionName; const char* lptszActionNameA; UINT uResIdString; } u;
	GUID guidInstance;
	DWORD dwObjID, dwHow;
};

struct GPDIActionFormat
{
	DWORD dwSize, dwActionSize, dwDataSize, dwNumActions;
	GPDIAction* rgoAction;
	GUID guidActionMap;
	DWORD dwGenre, dwBufferSize;
	LONG lAxisMin, lAxisMax;
	HINSTANCE hInstString;
	FILETIME ftTimeStamp;
	DWORD dwCRC;
	union { WCHAR tszActionMap[MAX_PATH]; char tszActionMapA[MAX_PATH]; };
	void SetStrings(bool isW, const WCHAR* map)
	{
		if (isW) { wcscpy(tszActionMap, map); }
		else { WideCharToMultiByte(CP_ACP, 0, map, -1, tszActionMapA, MAX_PATH, NULL, NULL); }
	}
};

struct GPDIDeviceImageInfo
{
	union { WCHAR tszImagePath[MAX_PATH]; char tszImagePathA[MAX_PATH]; };
	struct Extra
	{
		DWORD dwFlags;
		DWORD dwViewID;
		RECT rcOverlay;
		DWORD dwObjID, dwcValidPts;
		POINT rgptCalloutLine[5];
		RECT rcCalloutRect;
		DWORD dwTextAlign;
	};
	Extra* GetExtra(bool isW) const { return (Extra*)((char*)&extra - (isW ? 0 : MAX_PATH)); }
	DWORD GetSize(bool isW) const { return (DWORD)sizeof(*this) - (DWORD)(isW ? 0 : MAX_PATH); }
	void SetStrings(bool isW, const WCHAR* path)
	{
		if (isW) { wcscpy(tszImagePath, path); }
		else { WideCharToMultiByte(CP_ACP, 0, path, -1, tszImagePathA, MAX_PATH, NULL, NULL); }
	}
	private: Extra extra;
};
GPSTATIC_ASSERT(sizeof(GPDIDeviceImageInfo) == 352+260);

struct GPDIDeviceImageInfoHeader
{
	DWORD dwSize, dwSizeImageInfo, dwcViews, dwcButtons, dwcAxes, dwcPOVs, dwBufferSize, dwBufferUsed;
	GPDIDeviceImageInfo* lprgImageInfoArray; // Can't be accessed as array, needs pointer arithmetic with GetSize(isW)
};

struct GPDIColorSet { DWORD dwSize, cTextFore, cTextHighlight, cCalloutLine, cCalloutHighlight, cBorder, cControlFill, cHighlightFill, cAreaFill; };

struct GPDIConfigureDevicesParams
{
	DWORD dwSize, dwcUsers;
	LPWSTR lptszUserNames;
	DWORD dwcFormats;
	GPDIActionFormat* lprgFormats;
	HWND hwnd;
	GPDIColorSet dics;
	void* lpUnkDDSTarget;
};

struct GPDIDeviceObjectData
{
	DWORD dwOfs, dwData, dwTimeStamp, dwSequence;
	//DIRECTINPUT_VERSION >= GPDI_VERSION_8
	UINT_PTR uAppData;
};

struct GPDIObjectDataFormat
{
	const GUID *pguid;
	DWORD dwOfs, dwType, dwFlags;
};

struct GPDIDataFormat
{
	DWORD dwSize, dwObjSize, dwFlags, dwDataSize, dwNumObjs;
	GPDIObjectDataFormat* rgodf;
};

struct GPDIEnvelope { DWORD dwSize, dwAttackLevel, dwAttackTime, dwFadeLevel, dwFadeTime; };

struct GPDIEffect
{
	DWORD dwSize, dwFlags, dwDuration, dwSamplePeriod, dwGain, dwTriggerButton, dwTriggerRepeatInterval, cAxes;
	LPDWORD rgdwAxes;
	LPLONG rglDirection;
	GPDIEnvelope* lpEnvelope;
	DWORD cbTypeSpecificParams;
	LPVOID lpvTypeSpecificParams;
	//DIRECTINPUT_VERSION >= GPDI_VERSION_6
	DWORD dwStartDelay;
};

struct GPDIPropHeader      { DWORD dwSize, dwHeaderSize, dwObj, dwHow; };
struct GPDIPropDWord       { GPDIPropHeader diph; DWORD dwData; };
struct GPDIPropRange       { GPDIPropHeader diph; LONG lMin, lMax; }; // DIPROPRANGE_NOMIN = 0x80000000 / DIPROPRANGE_NOMAX = 0x7FFFFFFF
struct GPDIPropCal         { GPDIPropHeader diph; LONG lMin, lCenter, lMax; };
struct GPDIPropCalPOV      { GPDIPropHeader diph; LONG lMin[5], lMax[5]; };
struct GPDIPropGUIDAndPath { GPDIPropHeader diph; GUID guidClass; WCHAR wszPath[MAX_PATH]; };
struct GPDIPropString      { GPDIPropHeader diph; WCHAR wsz[MAX_PATH]; };
struct GPDIPropPointer     { GPDIPropHeader diph; UINT_PTR uData; };

struct GPDIEffectEscape { DWORD dwSize, dwCommand; LPVOID lpvInBuffer; DWORD cbInBuffer; LPVOID lpvOutBuffer; DWORD cbOutBuffer; };

struct GPDIFileEffect { DWORD dwSize; GUID GuidEffect; const GPDIEffect* lpDiEffect; CHAR szFriendlyName[MAX_PATH]; };

struct GPIDirectInputEffect
{
	/*** IUnknown methods ***/
	HRESULT (STDMETHODCALLTYPE *QueryInterface)(GPIDirectInputEffect** self, REFIID riid, void** ppvObject);
	ULONG   (STDMETHODCALLTYPE *AddRef)(GPIDirectInputEffect** self);
	ULONG   (STDMETHODCALLTYPE *Release)(GPIDirectInputEffect** self);
	/*** IDirectInputEffect methods ***/
	HRESULT (STDMETHODCALLTYPE *Initialize)(GPIDirectInputEffect** self, HINSTANCE, DWORD, GUID*);
	HRESULT (STDMETHODCALLTYPE *GetEffectGuid)(GPIDirectInputEffect** self, LPGUID);
	HRESULT (STDMETHODCALLTYPE *GetParameters)(GPIDirectInputEffect** self, GPDIEffect*, DWORD);
	HRESULT (STDMETHODCALLTYPE *SetParameters)(GPIDirectInputEffect** self, const GPDIEffect*, DWORD);
	HRESULT (STDMETHODCALLTYPE *Start)(GPIDirectInputEffect** self, DWORD, DWORD);
	HRESULT (STDMETHODCALLTYPE *Stop)(GPIDirectInputEffect** self);
	HRESULT (STDMETHODCALLTYPE *GetEffectStatus)(GPIDirectInputEffect** self, LPDWORD);
	HRESULT (STDMETHODCALLTYPE *Download)(GPIDirectInputEffect** self);
	HRESULT (STDMETHODCALLTYPE *Unload)(GPIDirectInputEffect** self);
	HRESULT (STDMETHODCALLTYPE *Escape)(GPIDirectInputEffect** self, GPDIEffectEscape*);
};

typedef BOOL (CALLBACK *GPDIEnumEffectsInFileCB)(const GPDIFileEffect*, LPVOID);
typedef BOOL (CALLBACK *GPDIConfigureDevicesCB)(void* pUnk, LPVOID);

typedef BOOL (CALLBACK *GPDIEnumDeviceObjectsCB)(const GPDIDeviceObjectInstance* doi, LPVOID);
typedef BOOL (CALLBACK *GPDIEnumDevicesCB)(const GPDIDeviceInstance* di, LPVOID);
typedef BOOL (CALLBACK *GPDIEnumDevicesBySemanticsCB)(const GPDIDeviceInstance* di, struct GPDirectInputDevice*, DWORD, DWORD, LPVOID);
typedef BOOL (CALLBACK *GPDIEnumEffectsCB)(const GPDIEffectInfo* ei, LPVOID);
typedef BOOL (CALLBACK *GPDIEnumCreatedEffectObjectsCB)(GPIDirectInputEffect*, LPVOID);

static const GUID GPDI_GUID_FirstProduct   = { 0x20002000, 0x3414, 0x442D, { 0x9A, 0x2F, 0x7F, 0xC2, 0xC6, 0x1A, 0xDE, 0xFB } };
static const GUID GPDI_GUID_FirstInstance  = { 0x60000000, 0xC1BD, 0x47DB, { 0x83, 0xDB, 0x26, 0x73, 0x67, 0x65, 0x0D, 0x07 } };
static const GUID GPDI_GUID_IDirectInput8A = { 0xBF798030, 0x483A, 0x4DA2, { 0xAA, 0x99, 0x5D, 0x64, 0xED, 0x36, 0x97, 0x00 } };
static const GUID GPDI_GUID_IDirectInput8W = { 0xBF798031, 0x483A, 0x4DA2, { 0xAA, 0x99, 0x5D, 0x64, 0xED, 0x36, 0x97, 0x00 } };
static const GUID GPDI_GUID_ObjXAxis       = { 0xA36D02E0, 0xC9F3, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };
static const GUID GPDI_GUID_ObjYAxis       = { 0xA36D02E1, 0xC9F3, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };
static const GUID GPDI_GUID_ObjZAxis       = { 0xA36D02E2, 0xC9F3, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };
static const GUID GPDI_GUID_ObjRxAxis      = { 0xA36D02F4, 0xC9F3, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };
static const GUID GPDI_GUID_ObjRyAxis      = { 0xA36D02F5, 0xC9F3, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };
static const GUID GPDI_GUID_ObjRzAxis      = { 0xA36D02E3, 0xC9F3, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };
static const GUID GPDI_GUID_ObjSlider      = { 0xA36D02E4, 0xC9F3, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };
static const GUID GPDI_GUID_ObjButton      = { 0xA36D02F0, 0xC9F3, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };
static const GUID GPDI_GUID_ObjKey         = { 0x55728220, 0xD33C, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };
static const GUID GPDI_GUID_ObjPOV         = { 0xA36D02F2, 0xC9F3, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };
static const GUID GPDI_GUID_ObjUnknown     = { 0xA36D02F3, 0xC9F3, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };
static const GUID GPDI_GUID_DevIntfHID     = { 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } };
static const GUID GPDI_GUID_XBOXProduct    = { 0x028E045E, 0x0000, 0x0000, { 0x00, 0x00, 0x50, 0x49, 0x44, 0x56, 0x49, 0x44 } };
static const wchar_t XBOXProductName[]    = L"Controller (XBOX 360 For Windows)";
static const wchar_t XBOXDeviceInstance[] = L"HID\\VID_045E&PID_028E&IG_00\\2&11111111&0&0000";
static const char    XBOXDevicePath[]     = "\\\\?\\HID#VID_045E&PID_028E&IG_00#2&1111111&0&0000#{4d1e55b2-f16f-11cf-88cb-001111000030}";

static bool ForceXInputDeviceId, Logged[GPData::NUM_GAMEPADS];
static volatile unsigned int InDirectInputCall;
static void EnterDirectInputCall() { GPInterlockedAdd(&InDirectInputCall, 1); }
static void LeaveDirectInputCall() { GPInterlockedAdd(&InDirectInputCall, -1); }

static void Hook(bool forceLoad = false);

struct GPDIJoyState
{
	enum { AXIS_COUNT = 8, POV_COUNT = 4, BUTTON_COUNT = 64 };
	union { DWORD axes[AXIS_COUNT]; struct { DWORD lX, lY, lZ, rX, rY, rZ, sliders[2]; }; };
	DWORD pov[POV_COUNT];
	BYTE buttons[BUTTON_COUNT];
	static const GPDIDataFormat* GetDataFormat()
	{
		static GPDIDataFormat dfJoy;
		if (!dfJoy.dwSize)
		{
			const GUID* axisGuids[6] = { &GPDI_GUID_ObjXAxis, &GPDI_GUID_ObjYAxis, &GPDI_GUID_ObjZAxis, &GPDI_GUID_ObjRxAxis, &GPDI_GUID_ObjRyAxis, &GPDI_GUID_ObjRzAxis };
			static GPDIObjectDataFormat dfJoyObjs[3+3+2+4+GPDIJoyState::BUTTON_COUNT];
			for (int i = 0; i !=                         6; i++) dfJoyObjs[i] =         { axisGuids[i],        (DWORD)FIELD_OFFSET(GPDIJoyState,    axes[i]), GPDIDFT_AXIS                         | GPDIDFT_ANYINSTANCE | GPDIDFT_OPTIONAL, 0, };
			for (int i = 0; i !=                         2; i++) dfJoyObjs[3+3+i] =     { &GPDI_GUID_ObjSlider, (DWORD)FIELD_OFFSET(GPDIJoyState, sliders[i]), GPDIDFT_AXIS                         | GPDIDFT_ANYINSTANCE | GPDIDFT_OPTIONAL, 0, };
			for (int i = 0; i !=                         4; i++) dfJoyObjs[3+3+2+i] =   { &GPDI_GUID_ObjPOV,    (DWORD)FIELD_OFFSET(GPDIJoyState,     pov[i]), GPDIDFT_POV                          | GPDIDFT_ANYINSTANCE | GPDIDFT_OPTIONAL, 0, };
			for (int i = 0; i != GPDIJoyState::BUTTON_COUNT; i++) dfJoyObjs[3+3+2+4+i] = { NULL,                (DWORD)FIELD_OFFSET(GPDIJoyState, buttons[i]), GPDIDFT_PSHBUTTON | GPDIDFT_TGLBUTTON | GPDIDFT_ANYINSTANCE | GPDIDFT_OPTIONAL, 0, };
			dfJoy = { sizeof(GPDIDataFormat), sizeof(GPDIObjectDataFormat), GPDIDF_ABSAXIS, sizeof(GPDIJoyState), 3+3+2+4+GPDIJoyState::BUTTON_COUNT, dfJoyObjs };
		}
		return &dfJoy;
	}
};

struct GPDIKeyboardState
{
	BYTE keys[GPDI_MAX_KEYBOARD];
	static const GPDIDataFormat* GetDataFormat()
	{
		static GPDIDataFormat dfKey;
		static GPDIObjectDataFormat dfKeyObjs[GPDI_MAX_KEYBOARD];
		for (int i = 0; i != GPDI_MAX_KEYBOARD; i++) dfKeyObjs[i] = { &GPDI_GUID_ObjKey, (DWORD)FIELD_OFFSET(GPDIKeyboardState, keys[i]), GPDIDFT_OPTIONAL|GPDIDFT_BUTTON|GPDIDFT_MAKEINSTANCE(i), 0 };
		dfKey = { sizeof(GPDIDataFormat), sizeof(GPDIObjectDataFormat), GPDIDF_RELAXIS, sizeof(GPDIKeyboardState), GPDI_MAX_KEYBOARD, dfKeyObjs };
		return &dfKey;
	}
};

struct GPDIMouseState
{
	enum { AXIS_COUNT = 3, BUTTON_COUNT = 8, EXCESS_SIZE = (BUTTON_COUNT*sizeof(BYTE)) };
	union { LONG axes[AXIS_COUNT]; struct { LONG x, y, z; }; };
	BYTE buttons[BUTTON_COUNT], held[BUTTON_COUNT];
	static const GPDIDataFormat* GetDataFormat()
	{
		static GPDIDataFormat dfMouse;
		static GPDIObjectDataFormat dfMouseObjs[AXIS_COUNT+BUTTON_COUNT];
		const GUID* axisGuids[AXIS_COUNT] = { &GPDI_GUID_ObjXAxis, &GPDI_GUID_ObjYAxis, &GPDI_GUID_ObjZAxis };
		for (int i = 0; i !=   AXIS_COUNT; i++) dfMouseObjs[i]            = { axisGuids[i],         (DWORD)FIELD_OFFSET(GPDIMouseState,    axes[i]), GPDIDFT_AXIS   | GPDIDFT_ANYINSTANCE | (i >= 2 ? GPDIDFT_OPTIONAL : 0), 0, };
		for (int i = 0; i != BUTTON_COUNT; i++) dfMouseObjs[AXIS_COUNT+i] = { &GPDI_GUID_ObjButton, (DWORD)FIELD_OFFSET(GPDIMouseState, buttons[i]), GPDIDFT_BUTTON | GPDIDFT_ANYINSTANCE | (i >= 1 ? GPDIDFT_OPTIONAL : 0), 0, };
		dfMouse = { sizeof(GPDIDataFormat), sizeof(GPDIObjectDataFormat), GPDIDF_RELAXIS, sizeof(GPDIMouseState)-EXCESS_SIZE, AXIS_COUNT+BUTTON_COUNT, dfMouseObjs };
		return &dfMouse;
	}
};

struct GPDIObj
{
	enum EMap : unsigned char { NONE, AXIS_STICK, AXIS_MERGELSTICKANDDPAD, AXIS_PAIR, AXIS_SINGLE, BUTTON, DPAD, AXIS_UNMAPPED };
	const WCHAR* Name;
	const GUID* Guid;
	WORD Type, Flags, CollectionNumber, UsagePage, Usage, Dimension;
	LONG RangeMin, RangeMax;
	EMap Map;
	unsigned char ValIdx;
	LONG RangeCenter;
	float FactorToNeg, FactorToPos;
	DWORD HwOfs, dwOfs;
	UINT_PTR appdata;
};

struct GPDirectInputDevice
{
	bool IsW;
	DWORD Version;
	ULONG Refs;

	GPGamepad& GP;
	unsigned short PrevVals[_GPIDX_MAX];

	GPVector<GPDIObj> Objs;

	HANDLE Event, EventThread;

	static void SwapObj(GPDIObj& a, GPDIObj& b) { GPDIObj c = a; a = b; b = c; }

	GPDirectInputDevice(bool isW, DWORD version, GPGamepad& gp) : IsW(isW), Version(version), Refs(1), GP(gp), Event(NULL), EventThread(NULL)
	{
		memset(&PrevVals, 0, sizeof(PrevVals));

		bool isXInputPad = (GameUsesXInput && !ForceVirtualDevices && !(pGPData->Options & OPTION_Disable_XInput));
		bool usePOVtoButtons = (!isXInputPad && (pGPData->Options & OPTION_DI_POVtoButtons));
		bool useTriggersToButtons = (!isXInputPad && (pGPData->Options & OPTION_DI_TriggersToButtons));
		int gpidx_btn_a     = ((pGPData->Options & OPTION_SwapAandB) ? GPIDX_BTN_B : GPIDX_BTN_A);
		int gpidx_btn_b     = ((pGPData->Options & OPTION_SwapAandB) ? GPIDX_BTN_A : GPIDX_BTN_B);
		int gpidx_trigger_l = ((pGPData->Options & OPTION_SwapL1R1andL2R2) ? GPIDX_BTN_L : GPIDX_TRIGGER_L);
		int gpidx_trigger_r = ((pGPData->Options & OPTION_SwapL1R1andL2R2) ? GPIDX_BTN_R : GPIDX_TRIGGER_R);
		int gpidx_btn_l     = ((pGPData->Options & OPTION_SwapL1R1andL2R2) ? GPIDX_TRIGGER_L : GPIDX_BTN_L);
		int gpidx_btn_r     = ((pGPData->Options & OPTION_SwapL1R1andL2R2) ? GPIDX_TRIGGER_R : GPIDX_BTN_R);

		Objs.push_back({ L"X Axis",     &GPDI_GUID_ObjXAxis,      GPDIDFT_ABSAXIS, GPDIDOI_ASPECTPOSITION, 1, 1, 48,  0, 0, 0xFFFF, GPDIObj::AXIS_STICK,   GPIDX_LSTICK_L });
		Objs.push_back({ L"Y Axis",     &GPDI_GUID_ObjYAxis,      GPDIDFT_ABSAXIS, GPDIDOI_ASPECTPOSITION, 1, 1, 49,  0, 0, 0xFFFF, GPDIObj::AXIS_STICK,   GPIDX_LSTICK_U });
		if (isXInputPad)
			Objs.push_back({ L"Z Axis",     &GPDI_GUID_ObjZAxis,  GPDIDFT_ABSAXIS, GPDIDOI_ASPECTPOSITION, 3, 1, 50,  0, 0xFFFF, 0, GPDIObj::AXIS_PAIR,    gpidx_trigger_l });
		if (!isXInputPad && !useTriggersToButtons)
			Objs.push_back({ L"Z Axis",     &GPDI_GUID_ObjZAxis,  GPDIDFT_ABSAXIS, GPDIDOI_ASPECTPOSITION, 3, 1, 50,  0, 0, 0xFFFF, GPDIObj::AXIS_SINGLE,  gpidx_trigger_l });
		Objs.push_back({ L"X Rotation", &GPDI_GUID_ObjRxAxis,     GPDIDFT_ABSAXIS, GPDIDOI_ASPECTPOSITION, 2, 1, 51,  0, 0, 0xFFFF, GPDIObj::AXIS_STICK,   GPIDX_RSTICK_L });
		Objs.push_back({ L"Y Rotation", &GPDI_GUID_ObjRyAxis,     GPDIDFT_ABSAXIS, GPDIDOI_ASPECTPOSITION, 2, 1, 52,  0, 0, 0xFFFF, GPDIObj::AXIS_STICK,   GPIDX_RSTICK_U });
		if (!isXInputPad && !useTriggersToButtons)
			Objs.push_back({ L"Z Rotation", &GPDI_GUID_ObjRzAxis, GPDIDFT_ABSAXIS, GPDIDOI_ASPECTPOSITION, 3, 1, 53,  0, 0, 0xFFFF, GPDIObj::AXIS_SINGLE,  gpidx_trigger_r });
		if (!usePOVtoButtons)
			Objs.push_back({ L"Hat Switch", &GPDI_GUID_ObjPOV,   GPDIDFT_POV,                           0, 0, 1, 57, 14, 0,  35999, GPDIObj::DPAD,         GPIDX_DPAD_U });
		Objs.push_back({ L"Button 0",   &GPDI_GUID_ObjButton,    GPDIDFT_PSHBUTTON,                     0, 0, 9,  1,  0, 0,    128, GPDIObj::BUTTON,       gpidx_btn_a });
		Objs.push_back({ L"Button 1",   &GPDI_GUID_ObjButton,    GPDIDFT_PSHBUTTON,                     0, 0, 9,  2,  0, 0,    128, GPDIObj::BUTTON,       gpidx_btn_b });
		Objs.push_back({ L"Button 2",   &GPDI_GUID_ObjButton,    GPDIDFT_PSHBUTTON,                     0, 0, 9,  3,  0, 0,    128, GPDIObj::BUTTON,       GPIDX_BTN_X });
		Objs.push_back({ L"Button 3",   &GPDI_GUID_ObjButton,    GPDIDFT_PSHBUTTON,                     0, 0, 9,  4,  0, 0,    128, GPDIObj::BUTTON,       GPIDX_BTN_Y });
		Objs.push_back({ L"Button 4",   &GPDI_GUID_ObjButton,    GPDIDFT_PSHBUTTON,                     0, 0, 9,  5,  0, 0,    128, GPDIObj::BUTTON,       gpidx_btn_l });
		Objs.push_back({ L"Button 5",   &GPDI_GUID_ObjButton,    GPDIDFT_PSHBUTTON,                     0, 0, 9,  6,  0, 0,    128, GPDIObj::BUTTON,       gpidx_btn_r });
		Objs.push_back({ L"Button 6",   &GPDI_GUID_ObjButton,    GPDIDFT_PSHBUTTON,                     0, 0, 9,  7,  0, 0,    128, GPDIObj::BUTTON,       GPIDX_BTN_BACK });
		Objs.push_back({ L"Button 7",   &GPDI_GUID_ObjButton,    GPDIDFT_PSHBUTTON,                     0, 0, 9,  8,  0, 0,    128, GPDIObj::BUTTON,       GPIDX_BTN_START });
		Objs.push_back({ L"Button 8",   &GPDI_GUID_ObjButton,    GPDIDFT_PSHBUTTON,                     0, 0, 9,  9,  0, 0,    128, GPDIObj::BUTTON,       GPIDX_BTN_LSTICK });
		Objs.push_back({ L"Button 9",   &GPDI_GUID_ObjButton,    GPDIDFT_PSHBUTTON,                     0, 0, 9, 10,  0, 0,    128, GPDIObj::BUTTON,       GPIDX_BTN_RSTICK });

		if (usePOVtoButtons)
		{
			Objs.push_back({ L"Button 10", &GPDI_GUID_ObjButton, GPDIDFT_PSHBUTTON,                     0, 0, 9, 11,  0, 0,    128, GPDIObj::BUTTON,       GPIDX_DPAD_U });
			Objs.push_back({ L"Button 11", &GPDI_GUID_ObjButton, GPDIDFT_PSHBUTTON,                     0, 0, 9, 12,  0, 0,    128, GPDIObj::BUTTON,       GPIDX_DPAD_D });
			Objs.push_back({ L"Button 12", &GPDI_GUID_ObjButton, GPDIDFT_PSHBUTTON,                     0, 0, 9, 13,  0, 0,    128, GPDIObj::BUTTON,       GPIDX_DPAD_L });
			Objs.push_back({ L"Button 13", &GPDI_GUID_ObjButton, GPDIDFT_PSHBUTTON,                     0, 0, 9, 14,  0, 0,    128, GPDIObj::BUTTON,       GPIDX_DPAD_R });
		}
		if (useTriggersToButtons)
		{
			Objs.push_back({ (usePOVtoButtons ? L"Button 14" : L"Button 10"),  &GPDI_GUID_ObjButton, GPDIDFT_PSHBUTTON, 0, 0, 9, 11, 0, 0, 128, GPDIObj::AXIS_SINGLE, gpidx_trigger_l });
			Objs.push_back({ (usePOVtoButtons ? L"Button 15" : L"Button 11"),  &GPDI_GUID_ObjButton, GPDIDFT_PSHBUTTON, 0, 0, 9, 12, 0, 0, 128, GPDIObj::AXIS_SINGLE, gpidx_trigger_r });
		}
		Objs.push_back({ L"Collection 0 - Game Pad" , &GPDI_GUID_ObjUnknown, GPDIDFT_COLLECTION|GPDIDFT_NODATA, 0, 0, 1, 5 });
		Objs.push_back({ L"Collection 1"            , &GPDI_GUID_ObjUnknown, GPDIDFT_COLLECTION|GPDIDFT_NODATA, 0, 0, 1, 0 });
		Objs.push_back({ L"Collection 2"            , &GPDI_GUID_ObjUnknown, GPDIDFT_COLLECTION|GPDIDFT_NODATA, 0, 0, 1, 0 });
		Objs.push_back({ L"Collection 3"            , &GPDI_GUID_ObjUnknown, GPDIDFT_COLLECTION|GPDIDFT_NODATA, 0, 0, 1, 0 });

		DWORD ofs = 0, countAxis = 0, countPov = 0, countButton = 0, countCollection = 0;
		for (GPDIObj& o : Objs)
		{
			o.HwOfs = ofs;
			o.dwOfs = (DWORD)-1;
			switch (o.Type)
			{
				case GPDIDFT_ABSAXIS:                  ofs += 4; o.Type |= GPDIDFT_MAKEINSTANCE(countAxis++); break;
				case GPDIDFT_POV:                      ofs += 4; o.Type |= GPDIDFT_MAKEINSTANCE(countPov++); break;
				case GPDIDFT_PSHBUTTON:                ofs += 1; o.Type |= GPDIDFT_MAKEINSTANCE(countButton++); break;
				case GPDIDFT_COLLECTION|GPDIDFT_NODATA: o.HwOfs = 0; o.Type |= GPDIDFT_MAKEINSTANCE(countCollection++); break;
			}
			o.RangeCenter = o.RangeMin + ((o.RangeMax - o.RangeMin + 1) / 2);
			o.FactorToNeg = (o.RangeCenter - o.RangeMin + 0.5f) / -65535.0f;
			o.FactorToPos = (o.RangeMax - o.RangeCenter + 0.5f) / 65535.0f;
		}

		if (isXInputPad)
		{
			// Make layout match a real XInput controller
			SwapObj(Objs[0], Objs[1]); // Swap X and Y (keep instance numbers)
			SwapObj(Objs[2], Objs[4]); // Swap Z and RY (keep instance numbers)
			Objs.insert(&Objs[16], Objs[5]); // Copy Hat to after Buttons (no change in HwOfs!)
			Objs.erase(&Objs[5]); // Remove old Hat
			Objs[0].HwOfs = 0; // X has offset 0
			Objs[1].HwOfs = 4; // Y has offset 4
			Objs[2].HwOfs = 8; // Ry has offset 8
			Objs[4].HwOfs = 16; // Z has offset 16
		}

		if (pGPData->Options & OPTION_DPadToLStick)
		{
			Objs[0].Map = Objs[1].Map = GPDIObj::AXIS_MERGELSTICKANDDPAD;
		}

		if (!Logged[&gp - pGPData->Gamepads])
		{
			Logged[&gp - pGPData->Gamepads] = true;
			WriteLog("Application started reading input for %s %s %d%s\n", "DirectInput", "joystick", (int)(&gp - pGPData->Gamepads) + 1, (isXInputPad ? " (simulating XInput gamepad because XInput was also loaded)" : ""));
		}
	}

	~GPDirectInputDevice() { SetEventNotification(NULL); }

	static DWORD WINAPI EventThreadFunc(GPDirectInputDevice* self)
	{
		Sleep(1000); // wait a bit before starting up to let main thread finish up more of the controller setup
		for (DWORD dwInOut;;)
		{
			self->GetDeviceData(0, NULL, &dwInOut, GPDIGDD_PEEK);
			if (dwInOut)
				SetEvent(self->Event);
			Sleep(10);
		}
		return 0;
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(const GUID& riid, void** ppvObject) { *ppvObject = this; AddRef(); return S_OK; }
	virtual ULONG STDMETHODCALLTYPE AddRef() { return ++Refs; }
	virtual ULONG STDMETHODCALLTYPE Release() { if (!--Refs) { delete this; return 0; } return Refs; }
	virtual HRESULT STDMETHODCALLTYPE GetCapabilities(GPDIDEVCAPS* lpDIDevCaps)
	{
		lpDIDevCaps->dwFlags = 5;
		lpDIDevCaps->dwDevType = (Version >= GPDI_VERSION_8 ? GPDIMAKEDEVTYPE(GPDI8DEVTYPE_GAMEPAD, GPDI8SUBDEVTYPE_GAMEPAD_STANDARD, GPDIDEVTYPE_HID) : GPDI1DEVTYPE_JOYSTICK);
		lpDIDevCaps->dwAxes = lpDIDevCaps->dwButtons = lpDIDevCaps->dwPOVs = 0;
		for (GPDIObj& o : Objs)
		{
			if (o.Type & GPDIDFT_AXIS) lpDIDevCaps->dwAxes++;
			if (o.Type & GPDIDFT_BUTTON) lpDIDevCaps->dwButtons++;
			if (o.Type & GPDIDFT_POV) lpDIDevCaps->dwPOVs++;
		}
		if (lpDIDevCaps->dwSize >= sizeof(*lpDIDevCaps))
		{
			lpDIDevCaps->dwFFSamplePeriod = 0;
			lpDIDevCaps->dwFFMinTimeResolution = 0;
			lpDIDevCaps->dwFirmwareRevision = 0;
			lpDIDevCaps->dwHardwareRevision = 0;
			lpDIDevCaps->dwFFDriverVersion = 0;
		}
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE EnumObjects(GPDIEnumDeviceObjectsCB lpCallback, LPVOID pvRef, DWORD dwFlags)
	{
		GPDIDeviceObjectInstance i;
		auto e = i.GetExtra(IsW);
		memset(&i, 0, sizeof(i));
		i.dwSize = i.GetSize(IsW);
		for (GPDIObj& o : Objs)
		{
			if (dwFlags && !(o.Type & dwFlags)) continue;
			i.guidType = *o.Guid;
			i.dwOfs = o.HwOfs;
			i.dwType = o.Type;
			i.dwFlags = o.Flags;
			i.SetStrings(IsW, o.Name);
			e->wCollectionNumber = o.CollectionNumber;
			e->wUsagePage = o.UsagePage;
			e->wUsage = o.Usage;
			e->dwDimension = o.Dimension;
			lpCallback(&i, pvRef);
		}
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE GetProperty(const GUID& rguidProp, GPDIPropHeader* pdiph)
	{
		for (GPDIObj& o : Objs)
		{
			switch (pdiph->dwHow)
			{
				case GPDIPH_DEVICE:   if (pdiph->dwObj == 0) break; else return E_FAIL;
				case GPDIPH_BYOFFSET: if (o.dwOfs == pdiph->dwObj) break; else continue;
				case GPDIPH_BYID:     if (o.Type == pdiph->dwObj) break; else continue;
				case GPDIPH_BYUSAGE:  if (o.Usage == pdiph->dwObj) break; else continue;
				default: return E_FAIL;
			}
			switch ((size_t)(void*)&rguidProp)
			{
				case GPDIPROP_BUFFERSIZE:
					((GPDIPropDWord*)pdiph)->dwData = 0;
					return S_OK;
				case GPDIPROP_AXISMODE:
					if (o.Type != GPDIDFT_ABSAXIS) return E_FAIL;
					((GPDIPropDWord*)pdiph)->dwData = GPDIPROPAXISMODE_ABS;
					return S_OK;
				case GPDIPROP_GRANULARITY:
					((GPDIPropDWord*)pdiph)->dwData = 1;
					return S_OK;
				case GPDIPROP_RANGE:
					if (o.RangeMin < o.RangeMax) { ((GPDIPropRange*)pdiph)->lMin = o.RangeMin; ((GPDIPropRange*)pdiph)->lMax = o.RangeMax; }
					else                         { ((GPDIPropRange*)pdiph)->lMin = o.RangeMax; ((GPDIPropRange*)pdiph)->lMax = o.RangeMin; }
					return S_OK;
				case GPDIPROP_DEADZONE:
					((GPDIPropDWord*)pdiph)->dwData = 0;
					return S_OK;
				case GPDIPROP_SATURATION:
					((GPDIPropDWord*)pdiph)->dwData = 10000;
				case GPDIPROP_FFGAIN:
					((GPDIPropDWord*)pdiph)->dwData = 0;
					return S_OK;
				case GPDIPROP_FFLOAD:
					((GPDIPropDWord*)pdiph)->dwData = 0;
					return S_OK;
				case GPDIPROP_AUTOCENTER:
					((GPDIPropDWord*)pdiph)->dwData = GPDIPROPAUTOCENTER_ON;
					return S_OK;
				case GPDIPROP_CALIBRATIONMODE:
					((GPDIPropDWord*)pdiph)->dwData = GPDIPROPCALIBRATIONMODE_COOKED;
					return S_OK;
				case GPDI5PROP_CALIBRATION:
					((GPDIPropCal*)pdiph)->lMin = 0;
					((GPDIPropCal*)pdiph)->lCenter = 0x8000;
					((GPDIPropCal*)pdiph)->lMax = 0xFFFF;
					return S_OK;
				case GPDI5PROP_GUIDANDPATH:
					((GPDIPropGUIDAndPath*)pdiph)->guidClass = GPDI_GUID_DevIntfHID;
					MultiByteToWideChar(CP_ACP, 0, XBOXDevicePath, sizeof(XBOXDevicePath), ((GPDIPropGUIDAndPath*)pdiph)->wszPath, MAX_PATH);
					return S_OK;
				//case GPDI5PROP_INSTANCENAME: // unsupported
				//case GPDI5PROP_PRODUCTNAME:  // unsupported
				case GPDI5PROP_JOYSTICKID:
					((GPDIPropDWord*)pdiph)->dwData = (DWORD)(1 + (&GP - pGPData->Gamepads));
					return S_OK;
				case GPDI5PROP_GETPORTDISPLAYNAME:
					wcscpy(((GPDIPropString*)pdiph)->wsz, XBOXProductName);
					return S_FALSE; // real device does this, too
				case GPDI7PROP_PHYSICALRANGE:
				case GPDI7PROP_LOGICALRANGE:
					((GPDIPropRange*)pdiph)->lMin = 0;
					((GPDIPropRange*)pdiph)->lMax = 0xFFFF;
					return S_OK;
				case GPDI8PROP_APPDATA:
					((GPDIPropPointer*)pdiph)->uData = o.appdata;
					return S_OK;
				case GPDI8PROP_VIDPID:
					((GPDIPropDWord*)pdiph)->dwData = GPDI_GUID_XBOXProduct.Data1;
					return S_OK;
				case GPDI8PROP_USERNAME:
					return S_FALSE; // no user set
				case GPDI8PROP_TYPENAME:
					MultiByteToWideChar(CP_ACP, 0, "VID_045E&PID_028E", sizeof("VID_045E&PID_028E"), ((GPDIPropGUIDAndPath*)pdiph)->wszPath, MAX_PATH);
					return S_OK;
			}
		}
		return GPDIERR_OBJECTNOTFOUND;
	}
	virtual HRESULT STDMETHODCALLTYPE SetProperty(const GUID& rguidProp, const GPDIPropHeader* pdiph)
	{
		for (GPDIObj& o : Objs)
		{
			switch (pdiph->dwHow)
			{
				case GPDIPH_DEVICE:   if (pdiph->dwObj == 0) break; else return E_FAIL;
				case GPDIPH_BYOFFSET: if (o.dwOfs == pdiph->dwObj) break; else continue;
				case GPDIPH_BYID:     if (o.Type == pdiph->dwObj) break; else continue;
				case GPDIPH_BYUSAGE:  if (o.Usage == pdiph->dwObj) break; else continue;
				default: return E_FAIL;
			}
			switch ((size_t)&rguidProp)
			{
				case GPDIPROP_RANGE:
					if (((const GPDIPropRange*)pdiph)->lMin >= ((const GPDIPropRange*)pdiph)->lMax) return E_FAIL;
					if (o.RangeMin > o.RangeMax) { o.RangeMin = ((const GPDIPropRange*)pdiph)->lMax; o.RangeMax = ((const GPDIPropRange*)pdiph)->lMin; }
					else                         { o.RangeMin = ((const GPDIPropRange*)pdiph)->lMin; o.RangeMax = ((const GPDIPropRange*)pdiph)->lMax; }
					o.RangeCenter = o.RangeMin + ((o.RangeMax - o.RangeMin + 1) / 2);
					o.FactorToNeg = (o.RangeCenter - o.RangeMin + 0.5f) / -65535.0f;
					o.FactorToPos = (o.RangeMax - o.RangeCenter + 0.5f) / 65535.0f;
					break;
				case GPDIPROP_DEADZONE: // todo
				case GPDIPROP_SATURATION: // todo
				case GPDIPROP_FFGAIN: // todo
				//case GPDI5PROP_INSTANCENAME: // unsupported
				//case GPDI5PROP_PRODUCTNAME:  // unsupported
				case GPDI8PROP_CPOINTS:
				case GPDI8PROP_APPDATA:
					o.appdata = ((GPDIPropPointer*)pdiph)->uData;
					break;
			}
		}
		return S_OK; //accept all setprop
	}
	virtual HRESULT STDMETHODCALLTYPE Acquire()
	{
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE Unacquire()
	{
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE GetDeviceState(DWORD cbData, LPVOID lpvData)
	{
		if (!lpvData) return E_FAIL;

		RunInputUpdaters(GP);

		DWORD val;
		memset(lpvData, 0, cbData);
		for (const GPDIObj& o : Objs)
		{
			switch (o.Map)
			{
				case GPDIObj::AXIS_STICK:
					val = (DWORD)(o.RangeCenter
						+ (LONG)(GP.Axis(o.ValIdx) * o.FactorToNeg)
						+ (LONG)(GP.Axis(o.ValIdx+1) * o.FactorToPos));
					goto write_val;

				case GPDIObj::AXIS_MERGELSTICKANDDPAD:
					val = (DWORD)(o.RangeCenter
						+ (LONG)(GP.Axis(o.ValIdx, true) * o.FactorToNeg)
						+ (LONG)(GP.Axis(o.ValIdx+1, true) * o.FactorToPos));
					goto write_val;

				case GPDIObj::AXIS_PAIR:
					val = (DWORD)(o.RangeCenter
						+ (LONG)(GP.Vals[o.ValIdx] * o.FactorToNeg)
						+ (LONG)(GP.Vals[o.ValIdx+1] * o.FactorToPos));
					goto write_val;

				case GPDIObj::AXIS_SINGLE:
					val = (DWORD)(o.RangeCenter
						+ (LONG)(GP.Vals[o.ValIdx] * o.FactorToPos));
					goto write_val;

				case GPDIObj::AXIS_UNMAPPED:
					val = (DWORD)o.RangeCenter;
					goto write_val;

				case GPDIObj::BUTTON:
					val = ((GP.Vals[o.ValIdx] & 0x8000u) ? (DWORD)o.RangeMax : (DWORD)o.RangeMin);
					goto write_val;

				case GPDIObj::DPAD:
					unsigned int mask =
						((GP.Vals[o.ValIdx  ] & 0x8000u) >> 15) | // 1 UP
						((GP.Vals[o.ValIdx+1] & 0x8000u) >> 14) | // 2 DOWN
						((GP.Vals[o.ValIdx+2] & 0x8000u) >> 13) | // 4 LEFT
						((GP.Vals[o.ValIdx+3] & 0x8000u) >> 12);  // 8 RIGHT
					static const DWORD DPADDatas[] = { 0xFFFFFFFF, 0, 18000, 0xFFFFFFFF, 27000, 31500, 22500, 27000, 9000, 4500, 13500, 9000, 0xFFFFFFFF, 0, 18000, 0xFFFFFFFF };
					val = DPADDatas[mask];
					if (val != 0xFFFFFFFF && (o.RangeMin != 0 || o.RangeMax != 35999))
						val = o.RangeMin + (DWORD)((val / 35999.0) * (o.RangeMax - o.RangeMin));
					goto write_val;

				write_val:
					if (o.Type & GPDIDFT_BUTTON) { if (o.dwOfs < cbData) *((BYTE*)lpvData + o.dwOfs) = (BYTE)(val & 0x80); }
					else                        { if (o.dwOfs + sizeof(DWORD) <= cbData) memcpy((char*)lpvData + o.dwOfs, &val, sizeof(DWORD)); }
			}
		}
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE GetDeviceData(DWORD cbObjectData, GPDIDeviceObjectData* rgdod, LPDWORD pdwInOut, DWORD dwFlags)
	{
		if (!pdwInOut) return E_FAIL;

		RunInputUpdaters(GP);

		DWORD wantNum = (rgdod && !(dwFlags & GPDIGDD_PEEK) ? *pdwInOut : 0), haveNum = 0;
		for (const GPDIObj& o : Objs)
		{
			switch (o.Map)
			{
				case GPDIObj::AXIS_STICK:
				{
					unsigned short v0 = GP.Axis(o.ValIdx), v1 = GP.Axis(o.ValIdx+1);
					if (PrevVals[o.ValIdx] == v0 && PrevVals[o.ValIdx+1] == v1) continue;
					haveNum++;
					if (!wantNum) continue;
					rgdod->dwData = o.RangeCenter
						+ (DWORD)((PrevVals[o.ValIdx  ] = v0) * o.FactorToNeg)
						+ (DWORD)((PrevVals[o.ValIdx+1] = v1) * o.FactorToPos);
					goto write_want;
				}
				case GPDIObj::AXIS_MERGELSTICKANDDPAD:
				{
					unsigned short v0 = GP.Axis(o.ValIdx, true), v1 = GP.Axis(o.ValIdx+1, true);
					if (PrevVals[o.ValIdx] == v0 && PrevVals[o.ValIdx+1] == v1) continue;
					haveNum++;
					if (!wantNum) continue;
					rgdod->dwData = o.RangeCenter
						+ (DWORD)((PrevVals[o.ValIdx  ] = v0) * o.FactorToNeg)
						+ (DWORD)((PrevVals[o.ValIdx+1] = v1) * o.FactorToPos);
					goto write_want;
				}
				case GPDIObj::AXIS_PAIR:
					if (PrevVals[o.ValIdx] == GP.Vals[o.ValIdx] && PrevVals[o.ValIdx+1] == GP.Vals[o.ValIdx+1]) continue;
					haveNum++;
					if (!wantNum) continue;
					rgdod->dwData = o.RangeCenter
						+ (DWORD)((PrevVals[o.ValIdx  ] = GP.Vals[o.ValIdx  ]) * o.FactorToNeg)
						+ (DWORD)((PrevVals[o.ValIdx+1] = GP.Vals[o.ValIdx+1]) * o.FactorToPos);
					goto write_want;

				case GPDIObj::AXIS_SINGLE:
					if (PrevVals[o.ValIdx] == GP.Vals[o.ValIdx]) continue;
					haveNum++;
					if (!wantNum) continue;
					rgdod->dwData = o.RangeCenter
						+ (DWORD)((PrevVals[o.ValIdx  ] = GP.Vals[o.ValIdx  ]) * o.FactorToPos);
					goto write_want;

				case GPDIObj::BUTTON:
					if ((PrevVals[o.ValIdx] & 0x8000u) == (GP.Vals[o.ValIdx] & 0x8000u)) continue;
					haveNum++;
					if (!wantNum) continue;
					rgdod->dwData = (((PrevVals[o.ValIdx] = GP.Vals[o.ValIdx]) & 0x8000u) ? o.RangeMax : o.RangeMin);
					goto write_want;

				case GPDIObj::DPAD:
					if (   (PrevVals[o.ValIdx  ] & 0x8000u) == (GP.Vals[o.ValIdx  ] & 0x8000u)
						&& (PrevVals[o.ValIdx+1] & 0x8000u) == (GP.Vals[o.ValIdx+1] & 0x8000u)
						&& (PrevVals[o.ValIdx+2] & 0x8000u) == (GP.Vals[o.ValIdx+2] & 0x8000u)
						&& (PrevVals[o.ValIdx+3] & 0x8000u) == (GP.Vals[o.ValIdx+3] & 0x8000u)) continue;
					haveNum++;
					if (!wantNum) continue;
					unsigned int mask =
						(((PrevVals[o.ValIdx  ] = GP.Vals[o.ValIdx  ]) & 0x8000u) >> 15) | // 1 UP
						(((PrevVals[o.ValIdx+1] = GP.Vals[o.ValIdx+1]) & 0x8000u) >> 14) | // 2 DOWN
						(((PrevVals[o.ValIdx+2] = GP.Vals[o.ValIdx+2]) & 0x8000u) >> 13) | // 4 LEFT
						(((PrevVals[o.ValIdx+3] = GP.Vals[o.ValIdx+3]) & 0x8000u) >> 12);  // 8 RIGHT
					static const DWORD DPADDatas[] = { 0xFFFFFFFF, 0, 18000, 0xFFFFFFFF, 27000, 31500, 22500, 27000, 9000, 4500, 13500, 9000, 0xFFFFFFFF, 0, 18000, 0xFFFFFFFF };
					rgdod->dwData = DPADDatas[mask];
					if (rgdod->dwData != 0xFFFFFFFF && (o.RangeMin != 0 || o.RangeMax != 35999))
						rgdod->dwData = o.RangeMin + (DWORD)((rgdod->dwData / 35999.0) * (o.RangeMax - o.RangeMin));
					goto write_want;

				write_want:
					static DWORD seq = 133147;
					if (haveNum == 1) seq += 2;
					rgdod->dwTimeStamp = GP.TimeStamp;
					rgdod->dwOfs = o.dwOfs;
					rgdod->dwSequence = seq;
					if (cbObjectData == sizeof(*rgdod)) rgdod->uAppData = (UINT_PTR)-1;
					rgdod = (GPDIDeviceObjectData*)((char*)rgdod + cbObjectData);
					wantNum--;
					continue;
			}
		}
		*pdwInOut = haveNum;
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE SetDataFormat(const GPDIDataFormat* lpdf)
	{
		if (!lpdf || lpdf->dwSize != sizeof(*lpdf) || lpdf->dwObjSize != sizeof(GPDIObjectDataFormat)) return E_FAIL;
		enum { C_AnyAxis, C_XAxis, C_YAxis, C_RxAxis, C_RyAxis, C_ZAxis, C_RzAxis, C_Slider, C_Button, C_POV, C_Unknow, C_Key, C_NUM };
		DWORD counters[C_NUM] = {0};
		static const DWORD odfguids[C_NUM] = { 0, GPDIODFGUID_XAxis, GPDIODFGUID_YAxis, GPDIODFGUID_RxAxis, GPDIODFGUID_RyAxis, GPDIODFGUID_ZAxis, GPDIODFGUID_RzAxis, GPDIODFGUID_Slider, GPDIODFGUID_Button, GPDIODFGUID_POV, GPDIODFGUID_Unknown, GPDIODFGUID_Key };
		static const DWORD odfdfts[C_NUM] = { GPDIDFT_AXIS, GPDIDFT_AXIS, GPDIDFT_AXIS, GPDIDFT_AXIS, GPDIDFT_AXIS, GPDIDFT_AXIS, GPDIDFT_AXIS, GPDIDFT_AXIS, GPDIDFT_BUTTON, GPDIDFT_POV, 0, GPDIDFT_BUTTON };

		for (GPDIObj& o : Objs) o.dwOfs = (DWORD)-1;

		for (const GPDIObjectDataFormat *f = lpdf->rgodf, *oEnd = f + lpdf->dwNumObjs; f != oEnd; f++)
		{
			DWORD typ = (f->dwType & GPDIDFT_TYPEMASK);
			DWORD ins = GPDIDFT_GETINSTANCE(f->dwType);
			bool anyInstance = (ins == GPDIDFT_GETINSTANCE(GPDIDFT_ANYINSTANCE));
			for (DWORD i = 0; i != C_NUM; i++)
			{
				if ((f->pguid && f->pguid->Data1 == odfguids[i] && (!typ || (typ & odfdfts[i]))) || (!f->pguid && (typ & odfdfts[i])))
				{
					if (anyInstance) ins = counters[i]++;
					for (GPDIObj& o : Objs)
					{
						if (o.Map == GPDIObj::NONE) continue;
						if (odfguids[i] && o.Guid->Data1 != odfguids[i]) continue;
						if (odfdfts[i] && !(o.Type & odfdfts[i])) continue;
						if (ins) { ins--; continue; }
						if (o.dwOfs == (DWORD)-1) o.dwOfs = f->dwOfs;
						break;
					}
					break;
				}
			}
		}
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE SetEventNotification(HANDLE hEvent)
	{
		if (EventThread)
		{
			TerminateThread(EventThread, 0);
			CloseHandle(EventThread);
			EventThread = NULL;
		}
		Event = hEvent;
		if (hEvent)
			EventThread = CreateThread(0, 0, (DWORD (WINAPI *)(LPVOID))EventThreadFunc, this, 0, 0);
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
	{
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE GetObjectInfo(GPDIDeviceObjectInstance* doi, DWORD dwObj, DWORD dwHow)
	{
		if (!doi || !doi->dwSize) return E_FAIL;
		for (GPDIObj& o : Objs)
		{
			switch (dwHow)
			{
				case GPDIPH_BYOFFSET: if (o.dwOfs == dwObj) break; else continue;
				case GPDIPH_BYID:     if (o.Type == dwObj) break; else continue;
				case GPDIPH_BYUSAGE:  if (o.Usage == dwObj) break; else continue;
				default: return E_FAIL;
			}
			doi->guidType = *o.Guid;
			doi->dwOfs = o.HwOfs;
			doi->dwType = o.Type;
			doi->dwFlags = o.Flags;
			doi->SetStrings(IsW, o.Name);
			if (doi->dwSize == doi->GetSize(IsW))
			{
				auto e = doi->GetExtra(IsW);
				e->wCollectionNumber = o.CollectionNumber;
				e->wUsagePage = o.UsagePage;
				e->wUsage = o.Usage;
				e->dwDimension = o.Dimension;
				e->dwFFMaxForce = e->dwFFForceResolution = e->wDesignatorIndex = e->wExponent = e->wReserved = 0;
			}
			return S_OK;
		}
		return GPDIERR_OBJECTNOTFOUND;
	}
	virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo(GPDIDeviceInstance* di)
	{
		if (di->dwSize < (DWORD)((char*)di->GetExtra(IsW) - (char*)di)) return E_INVALIDARG;
		di->guidInstance = GPDI_GUID_FirstInstance; di->guidInstance.Data1 += (int)(&GP - pGPData->Gamepads);
		if (GameUsesXInput && !ForceVirtualDevices && !(pGPData->Options & OPTION_Disable_XInput))
		{
			di->guidProduct = GPDI_GUID_XBOXProduct;
			di->SetStrings(IsW, XBOXProductName, XBOXProductName);
		}
		else
		{
			di->guidProduct  = GPDI_GUID_FirstProduct;  di->guidProduct.Data1  += (int)(&GP - pGPData->Gamepads);
			wchar_t name[] = { 'P','h','o','e','n','i','x','P','a','d',' ','1','\0' };
			name[11] += (wchar_t)((&GP - pGPData->Gamepads) % 10);
			di->SetStrings(IsW, name, name);
		}
		di->dwDevType = (Version >= GPDI_VERSION_8 ? GPDIMAKEDEVTYPE(GPDI8DEVTYPE_GAMEPAD, GPDI8SUBDEVTYPE_GAMEPAD_STANDARD, GPDIDEVTYPE_HID) : GPDI1DEVTYPE_JOYSTICK);
		if (di->dwSize == di->GetSize(IsW))
		{
			auto e = di->GetExtra(IsW);
			memset(&e->guidFFDriver, 0, sizeof(e->guidFFDriver));
			e->wUsagePage = 1;
			e->wUsage = 5;
		}
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE RunControlPanel(HWND hwndOwner, DWORD dwFlags)
	{
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE hinst, DWORD dwVersion, const GUID& rguid)
	{
		Version = dwVersion;
		return S_OK;
	}
	// DirectInputDevice2 methods:
	virtual HRESULT STDMETHODCALLTYPE CreateEffect(const GUID& rguid, const GPDIEffect* lpeff, GPIDirectInputEffect** ppdeff, void* punkOuter)
	{
		return 1;
	}
	virtual HRESULT STDMETHODCALLTYPE EnumEffects(GPDIEnumEffectsCB lpCallback, LPVOID pvRef, DWORD dwEffType)
	{
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE GetEffectInfo(GPDIEffectInfo* ei, const GUID& rguid)
	{
		return 1;
	}
	virtual HRESULT STDMETHODCALLTYPE GetForceFeedbackState(LPDWORD pdwOut)
	{
		return 1;
	}
	virtual HRESULT STDMETHODCALLTYPE SendForceFeedbackCommand(DWORD dwFlags)
	{
		return 1;
	}
	virtual HRESULT STDMETHODCALLTYPE EnumCreatedEffectObjects(GPDIEnumCreatedEffectObjectsCB lpCallback, LPVOID pvRef, DWORD fl)
	{
		return 1;
	}
	virtual HRESULT STDMETHODCALLTYPE Escape(GPDIEffectEscape* pesc)
	{
		return 1;
	}
	virtual HRESULT STDMETHODCALLTYPE Poll()
	{
		return (Version >= GPDI_VERSION_8 ? S_FALSE : S_OK);
	}
	virtual HRESULT STDMETHODCALLTYPE SendDeviceData(DWORD cbObjectData, const GPDIDeviceObjectData* rgdod, LPDWORD pdwInOut, DWORD fl)
	{
		return 1;
	}
	// DirectInputDevice7 methods:
	virtual HRESULT STDMETHODCALLTYPE EnumEffectsInFile(void* lpszFileNameAorW, GPDIEnumEffectsInFileCB pec, LPVOID pvRef, DWORD dwFlags)
	{
		return 1;
	}
	virtual HRESULT STDMETHODCALLTYPE WriteEffectToFile(void* lpszFileNameAorW, DWORD dwEntries, GPDIFileEffect* rgDiFileEft, DWORD dwFlags)
	{
		return 1;
	}
	// DirectInputDevice8 methods:
	virtual HRESULT STDMETHODCALLTYPE BuildActionMap(GPDIActionFormat* lpdiaf, void* lpszUserNameAorW, DWORD dwFlags)
	{
		return 1;
	}
	virtual HRESULT STDMETHODCALLTYPE SetActionMap(GPDIActionFormat* lpdiaf, void* lpszUserNameAorW, DWORD dwFlags)
	{
		return 1;
	}
	virtual HRESULT STDMETHODCALLTYPE GetImageInfo(GPDIDeviceImageInfoHeader* lpdiDevImageInfoHeader)
	{
		return 1;
	}
};

struct GPDirectInputLegacyDevice
{
	// Behavior based on dinputto8 by Elisha Riedlinger (https://github.com/elishacloud/dinputto8)
	GPDirectInputDevice* Real;
	DWORD Offset;
	bool CanAcquire;
	GPDIDeviceObjectData ObjectData[GPDI_MAX_KEYBOARD];

	GPDirectInputLegacyDevice(GPDirectInputDevice* real) : Real(real), Offset(0), CanAcquire(false) { }

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(const GUID& riid, void** ppvObject) { *ppvObject = this; AddRef(); return S_OK; }
	virtual ULONG STDMETHODCALLTYPE AddRef() { return Real->AddRef(); }
	virtual ULONG STDMETHODCALLTYPE Release() { ULONG res = Real->Release(); if (!res) delete this; return res; }
	virtual HRESULT STDMETHODCALLTYPE GetCapabilities(GPDIDEVCAPS* lpDIDevCaps) { return Real->GetCapabilities(lpDIDevCaps); }
	virtual HRESULT STDMETHODCALLTYPE EnumObjects(GPDIEnumDeviceObjectsCB lpCallback, LPVOID pvRef, DWORD dwFlags) { return Real->EnumObjects(lpCallback, pvRef, dwFlags); }
	virtual HRESULT STDMETHODCALLTYPE GetProperty(const GUID& rguidProp, GPDIPropHeader* pdiph) { return Real->GetProperty(rguidProp, pdiph); }
	virtual HRESULT STDMETHODCALLTYPE SetProperty(const GUID& rguidProp, const GPDIPropHeader* pdiph) { return Real->SetProperty(rguidProp, pdiph); }
	virtual HRESULT STDMETHODCALLTYPE Acquire()
	{
		if (!CanAcquire) { CanAcquire = true; return GPDIERR_NOTINITIALIZED; }
		return Real->Acquire();
	}
	virtual HRESULT STDMETHODCALLTYPE Unacquire() { return Real->Unacquire(); }
	virtual HRESULT STDMETHODCALLTYPE GetDeviceState(DWORD cbData, LPVOID lpvData)
	{
		if (!Offset) return Real->GetDeviceState(cbData, lpvData);
		unsigned char tmp[GPDI_MAX_KEYBOARD] = {};
		HRESULT res = Real->GetDeviceState(GPDI_MAX_KEYBOARD, tmp);
		if (res != S_OK) return res;
		memset(lpvData, 0, cbData);
		for (DWORD i = Offset, xEnd = (cbData < Offset + GPDI_MAX_KEYBOARD ? cbData : Offset + GPDI_MAX_KEYBOARD); i < xEnd; i++)
			((unsigned char*)lpvData)[i] = tmp[i - Offset];
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE GetDeviceData(DWORD cbObjectData, GPDIDeviceObjectData* rgdod, LPDWORD pdwInOut, DWORD dwFlags)
	{
		if (dwFlags == GPDIGDD_PEEK || !rgdod || cbObjectData == sizeof(GPDIDeviceObjectData))
			return Real->GetDeviceData(sizeof(GPDIDeviceObjectData), rgdod, pdwInOut, dwFlags);

		if (!pdwInOut || !*pdwInOut || *pdwInOut == (DWORD)-1 || !cbObjectData) return GPDIERR_INVALIDPARAM;

		if (*pdwInOut > GPDI_MAX_KEYBOARD) *pdwInOut = GPDI_MAX_KEYBOARD;
		HRESULT res = Real->GetDeviceData(sizeof(GPDIDeviceObjectData), ObjectData, pdwInOut, dwFlags);
		if (res == S_OK)
			for (DWORD i = 0, sz = (cbObjectData > sizeof(GPDIDeviceObjectData) ? sizeof(GPDIDeviceObjectData) : cbObjectData); i != *pdwInOut; i++)
				memcpy((char*)rgdod + (i * cbObjectData), &ObjectData[i], sz);
		return res;
	}
	virtual HRESULT STDMETHODCALLTYPE SetDataFormat(const GPDIDataFormat* lpdf)
	{
		if (!lpdf || !lpdf->dwNumObjs || lpdf->dwObjSize != sizeof(GPDIObjectDataFormat))
			return Real->SetDataFormat(lpdf);

		if (lpdf->dwNumObjs < GPDI_MAX_KEYBOARD && (lpdf->rgodf[0].dwType & GPDIDFT_BUTTON) && lpdf->rgodf[0].dwOfs != 0 && lpdf->rgodf[0].pguid->Data1 == GPDIODFGUID_Key)
		{
			Offset = lpdf->rgodf[0].dwOfs - 1;
			if (Real->SetDataFormat(GPDIKeyboardState::GetDataFormat()) == S_OK)
				return S_OK;
		}
		Offset = 0;

		GPVector<GPDIObjectDataFormat> di8odf;
		di8odf.resize(lpdf->dwNumObjs);

		GPDIDataFormat di8df = { sizeof(GPDIDataFormat), lpdf->dwObjSize, lpdf->dwFlags, lpdf->dwDataSize, lpdf->dwNumObjs, &di8odf[0] };
		for (GPDIObjectDataFormat* from = lpdf->rgodf, *to = di8df.rgodf, *toEnd = to + di8df.dwNumObjs; to != toEnd; from++, to++)
		{
			*to = *from;
			if ((from->dwType & GPDIDFT_ANYINSTANCE) == 0xFF00) to->dwType |= GPDIDFT_ANYINSTANCE;
		}
		return Real->SetDataFormat(&di8df);
	}
	virtual HRESULT STDMETHODCALLTYPE SetEventNotification(HANDLE hEvent) { return Real->SetEventNotification(hEvent); }
	virtual HRESULT STDMETHODCALLTYPE SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
	{
		HRESULT res = Real->SetCooperativeLevel(hwnd, dwFlags);
		if (res == S_OK) CanAcquire = true;
		return res;
	}
	virtual HRESULT STDMETHODCALLTYPE GetObjectInfo(GPDIDeviceObjectInstance* doi, DWORD dwObj, DWORD dwHow) { return Real->GetObjectInfo(doi, dwObj, dwHow); }
	virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo(GPDIDeviceInstance* di)
	{
		HRESULT res = Real->GetDeviceInfo(di);
		if (res != S_OK) return res;
		DWORD dt = (di->dwDevType & GPDIDEVTYPE_MASK);
		di->dwDevType =
			(dt <= GPDI1DEVTYPE_JOYSTICK ? di->dwDevType :
			(dt <= GPDI8DEVTYPE_DEVICE || dt == GPDI8DEVTYPE_DEVICECTRL ? GPDI1DEVTYPE_DEVICE :
			(dt <= GPDI8DEVTYPE_MOUSE ? GPDI1DEVTYPE_MOUSE :
			(dt <= GPDI8DEVTYPE_KEYBOARD ? GPDI1DEVTYPE_KEYBOARD :
			(dt <= GPDI8DEVTYPE_SUPPLEMENTAL ? GPDI1DEVTYPE_JOYSTICK : GPDI1DEVTYPE_DEVICE)))));
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE RunControlPanel(HWND hwndOwner, DWORD dwFlags) { return Real->RunControlPanel(hwndOwner, dwFlags); }
	virtual HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE hinst, DWORD dwVersion, const GUID& rguid) { return Real->Initialize(hinst, dwVersion, rguid); }
	// DirectInputDevice2 methods:
	virtual HRESULT STDMETHODCALLTYPE CreateEffect(const GUID& rguid, const GPDIEffect* lpeff, GPIDirectInputEffect** ppdeff, void* punkOuter)
	{
		// Would need a GPDirectInputLegacyEffect if ever used for anything that isn't mouse or keyboard
		return Real->CreateEffect(rguid, lpeff, ppdeff, punkOuter);
	}
	virtual HRESULT STDMETHODCALLTYPE EnumEffects(GPDIEnumEffectsCB lpCallback, LPVOID pvRef, DWORD dwEffType) { return Real->EnumEffects(lpCallback, pvRef, dwEffType); }
	virtual HRESULT STDMETHODCALLTYPE GetEffectInfo(GPDIEffectInfo* ei, const GUID& rguid) { return Real->GetEffectInfo(ei, rguid); }
	virtual HRESULT STDMETHODCALLTYPE GetForceFeedbackState(LPDWORD pdwOut) { return Real->GetForceFeedbackState(pdwOut); }
	virtual HRESULT STDMETHODCALLTYPE SendForceFeedbackCommand(DWORD dwFlags) { return Real->SendForceFeedbackCommand(dwFlags); }
	virtual HRESULT STDMETHODCALLTYPE EnumCreatedEffectObjects(GPDIEnumCreatedEffectObjectsCB lpCallback, LPVOID pvRef, DWORD fl)
	{
		// Would need a GPIDirectInputLegacyEffect if ever used for anything that isn't mouse or keyboard
		return Real->EnumCreatedEffectObjects(lpCallback, pvRef, fl);
	}
	virtual HRESULT STDMETHODCALLTYPE Escape(GPDIEffectEscape* pesc) { return Real->Escape(pesc); }
	virtual HRESULT STDMETHODCALLTYPE Poll() { HRESULT res = Real->Poll(); return (res == S_FALSE ? S_OK : res); }
	virtual HRESULT STDMETHODCALLTYPE SendDeviceData(DWORD cbObjectData, const GPDIDeviceObjectData* rgdod, LPDWORD pdwInOut, DWORD fl)
	{
		if (!pdwInOut || !rgdod || !cbObjectData) return GPDIERR_INVALIDPARAM;

		if (*pdwInOut > GPDI_MAX_KEYBOARD) *pdwInOut = GPDI_MAX_KEYBOARD;
		for (DWORD i = 0, sz = (cbObjectData > sizeof(GPDIDeviceObjectData) ? sizeof(GPDIDeviceObjectData) : cbObjectData); i != *pdwInOut; i++)
			memcpy((char*)rgdod + (i * cbObjectData), &ObjectData[i], sz);
		return Real->SendDeviceData(sizeof(GPDIDeviceObjectData), ObjectData, pdwInOut, fl);
	}
	// DirectInputDevice7 methods:
	virtual HRESULT STDMETHODCALLTYPE EnumEffectsInFile(void* lpszFileNameAorW, GPDIEnumEffectsInFileCB pec, LPVOID pvRef, DWORD dwFlags) { return Real->EnumEffectsInFile(lpszFileNameAorW, pec, pvRef, dwFlags); }
	virtual HRESULT STDMETHODCALLTYPE WriteEffectToFile(void* lpszFileNameAorW, DWORD dwEntries, GPDIFileEffect* rgDiFileEft, DWORD dwFlags) { return Real->WriteEffectToFile(lpszFileNameAorW, dwEntries, rgDiFileEft, dwFlags); }
};

struct GPDirectInputInterface
{
	GPDirectInputInterface* Real;
	bool IsW;
	DWORD Version;
	GPDirectInputInterface(GPDirectInputInterface* real, bool isW, DWORD version) : Real(real), IsW(isW), Version(version) { }

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(const GUID& riid, void** ppvObject)
	{
		if (riid.Data1 == GPDI_IID_IDirectInputJoyConfig)
			return Real->QueryInterface(riid, ppvObject);
		*ppvObject = this;
		AddRef();
		return S_OK;
	}
	virtual ULONG STDMETHODCALLTYPE AddRef() { return Real->AddRef(); }
	virtual ULONG STDMETHODCALLTYPE Release() { ULONG res = Real->Release(); if (!res) delete this; return res; }

	virtual HRESULT STDMETHODCALLTYPE CreateDevice(const GUID& rguid, GPDirectInputDevice** lplpDirectInputDevice, void* pUnkOuter)
	{
		if (rguid.Data2 == GPDI_GUID_FirstInstance.Data2 && rguid.Data3 == GPDI_GUID_FirstInstance.Data3)
		{
			if ((unsigned)(rguid.Data1 - GPDI_GUID_FirstInstance.Data1) > GPData::NUM_GAMEPADS) return GPDIERR_DEVICENOTREG;
			*lplpDirectInputDevice = new GPDirectInputDevice(IsW, Version, pGPData->Gamepads[rguid.Data1 - GPDI_GUID_FirstInstance.Data1]);
			return S_OK;
		}
		EnterDirectInputCall();
		HRESULT res = Real->CreateDevice(rguid, lplpDirectInputDevice, pUnkOuter);
		LeaveDirectInputCall();
		if (res == S_OK && Version < GPDI_VERSION_8)
		{
			WriteLog("Converting DirectInput %d device to DirectInput 8\n", (Version >> 8));
			*lplpDirectInputDevice = (GPDirectInputDevice*)new GPDirectInputLegacyDevice(*lplpDirectInputDevice);
		}
		return res;
	}

	bool PrepareDeviceInstance(int i, GPDIDeviceInstance& di)
	{
		if (!pGPData->Gamepads[i].Used) return false;
		if ((pGPData->Options & (OPTION_Disable_DirectInput|OPTION_Disable_XInput)) == OPTION_Disable_DirectInput)
		{
			GameUsesXInput = true;
		}
		else if (pGPData->Options & OPTION_Disable_DirectInput)
		{
			if (!Logged[i])
			{
				Logged[i] = true;
				WriteLog("Application tried to %s %s %s %d but the interface is disabled, returning no connected device\n", "query", "DirectInput", "joystick", i + 1);
			}
			return false;
		}
		memset(&di, 0, sizeof(di));
		di.dwSize = di.GetSize(IsW);
		di.guidInstance = GPDI_GUID_FirstInstance; di.guidInstance.Data1 += i;
		if (GameUsesXInput && !ForceVirtualDevices && !(pGPData->Options & OPTION_Disable_XInput))
		{
			ForceXInputDeviceId = true;
			di.guidProduct  = GPDI_GUID_XBOXProduct;
			di.SetStrings(IsW, XBOXProductName, XBOXProductName);
		}
		else
		{
			ForceVirtualDevices = true; // if the caller has seen virtual devices once, keep returning only virtual devices
			di.guidProduct  = GPDI_GUID_FirstProduct; di.guidProduct.Data1 += i;
			wchar_t name[] = { 'P','h','o','e','n','i','x','P','a','d',' ','1','\0' };
			name[11] += (wchar_t)(i % 10);
			di.SetStrings(IsW, name, name);
		}
		//WriteLog((IsW ? "GPDirectInputInterface::EnumDevices - Return virtual product %S\n" : "GPDirectInputInterface::EnumDevices - Return virtual product %s\n"), (IsW ? (char*)di.tszInstanceName : di.tszInstanceNameA));
		di.dwDevType = (Version >= GPDI_VERSION_8 ? GPDIMAKEDEVTYPE(GPDI8DEVTYPE_GAMEPAD, GPDI8SUBDEVTYPE_GAMEPAD_STANDARD, GPDIDEVTYPE_HID) : GPDI1DEVTYPE_JOYSTICK);
		di.GetExtra(IsW)->wUsagePage = 1;
		di.GetExtra(IsW)->wUsage = 5;
		return true;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumDevices(DWORD dwDevType, GPDIEnumDevicesCB lpCallback, LPVOID pvRef, DWORD dwFlags)
	{
		//WriteLog("GPDirectInputInterface::EnumDevices - dwDevType: %x, dwFlags: %x\n", dwDevType, dwFlags);
		struct SData { GPDIEnumDevicesCB lpCallback; LPVOID pvRef; } dt = { lpCallback, pvRef };
		struct Local { static BOOL CALLBACK CB(const GPDIDeviceInstance* di, SData& dt)
		{
			if ((di->dwDevType & GPDIDEVTYPE_MASK) >= GPDI8DEVTYPE_OVERRIDE_MIN && (di->dwDevType & GPDIDEVTYPE_MASK) <= GPDI8DEVTYPE_OVERRIDE_MAX)
				return GPDIENUM_CONTINUE;
			return (dt.lpCallback ? dt.lpCallback(di, dt.pvRef) : GPDIENUM_CONTINUE);
		}};
		EnterDirectInputCall();
		HRESULT res = Real->EnumDevices(dwDevType, (GPDIEnumDevicesCB)Local::CB, &dt, dwFlags);
		LeaveDirectInputCall();
		if (res != S_OK) return res;

		if (((dwDevType == GPDI8DEVCLASS_ALL) || (dwDevType == GPDI8DEVCLASS_GAMECTRL) || (dwDevType >= GPDI8DEVTYPE_OVERRIDE_MIN && dwDevType <= GPDI8DEVTYPE_OVERRIDE_MAX)) && (dwFlags & GPDIEDFL_FORCEFEEDBACK) == 0)
		{
			GPDIDeviceInstance di;
			for (int i = 0; i != GPData::NUM_GAMEPADS; i++)
				if (PrepareDeviceInstance(i, di))
					lpCallback(&di, pvRef);
		}
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceStatus(const GUID& rguid)
	{
		HRESULT res;
		if (rguid.Data2 == GPDI_GUID_FirstInstance.Data2 && rguid.Data3 == GPDI_GUID_FirstInstance.Data3)
			return (((unsigned)(rguid.Data1 - GPDI_GUID_FirstInstance.Data1) <= GPData::NUM_GAMEPADS && pGPData->Gamepads[rguid.Data1 - GPDI_GUID_FirstInstance.Data1].Used) ? S_OK : S_FALSE);

		EnterDirectInputCall();
		res = Real->GetDeviceStatus(rguid);
		LeaveDirectInputCall();
		return res;
	}

	virtual HRESULT STDMETHODCALLTYPE RunControlPanel(HWND hwndOwner, DWORD dwFlags) { return Real->RunControlPanel(hwndOwner, dwFlags); }
	virtual HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE hinst, DWORD dwVersion) { return Real->Initialize(hinst, dwVersion); }

	virtual HRESULT STDMETHODCALLTYPE FindDevice(const GUID& rguid, const void* pszNameAorW, LPGUID pguidInstance)
	{
		//WriteLog("[DII] [FindDevice] UNSUPPORTED\n");
		return GPDIERR_DEVICENOTREG;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumDevicesBySemantics(const void* ptszUserNameAorW, GPDIActionFormat* lpdiActionFormat, GPDIEnumDevicesBySemanticsCB lpCallback, LPVOID pvRef, DWORD dwFlags)
	{
		if (Version == 0x700)
		{
			// DI7 has this function signature instead here
			// virtual HRESULT STDMETHODCALLTYPE CreateDeviceEx(const GUID& rguid, const GUID& riid, LPVOID *pvOut, LPUNKNOWN lpUnknownOuter)
			return CreateDevice(*(const GUID*)ptszUserNameAorW, (GPDirectInputDevice**)lpCallback, (void*)pvRef);
		}

		// TODO: dwRemaining passed to the callback by this function is not correct
		struct SData { GPDIEnumDevicesBySemanticsCB lpCallback; LPVOID pvRef; } dt = { lpCallback, pvRef };
		struct Local { static BOOL CALLBACK CB(const GPDIDeviceInstance* di, GPDirectInputDevice* did, DWORD dwFlags, DWORD dwRemaining, SData& dt)
		{
			if ((di->dwDevType & GPDIDEVTYPE_MASK) >= GPDI8DEVTYPE_OVERRIDE_MIN && (di->dwDevType & GPDIDEVTYPE_MASK) <= GPDI8DEVTYPE_OVERRIDE_MAX)
			{
				did->Release();
				return GPDIENUM_CONTINUE;
			}
			return (dt.lpCallback ? dt.lpCallback(di, did, dwFlags, dwRemaining, dt.pvRef) : GPDIENUM_CONTINUE);
		}};
		EnterDirectInputCall();
		HRESULT res = Real->EnumDevicesBySemantics(ptszUserNameAorW, lpdiActionFormat, (GPDIEnumDevicesBySemanticsCB)Local::CB, &dt, dwFlags);
		LeaveDirectInputCall();
		if (res != S_OK) return res;

		if ((dwFlags & (GPDIEDBSFL_FORCEFEEDBACK | GPDIEDBSFL_MULTIMICEKEYBOARDS | GPDIEDBSFL_NONGAMINGDEVICES)) == 0)
		{
			GPDIDeviceInstance di;
			for (int i = 0; i != GPData::NUM_GAMEPADS; i++)
			{
				if (!PrepareDeviceInstance(i, di)) continue;
				GPDirectInputDevice* did = new GPDirectInputDevice(IsW, Version, pGPData->Gamepads[i]);
				lpCallback(&di, did, 0, 0, pvRef);
			}
		}
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE ConfigureDevices(GPDIConfigureDevicesCB lpdiCallback, GPDIConfigureDevicesParams* lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
	{
		// IDirectInput8::ConfigureDevices is deprecated. This method always fails on Windows Vista and later versions of Windows.
		return S_FALSE;
	}
};

#if 0
struct Report
{
	static void Print(const char* prfx, int domodes, int mode, const char* func, HRESULT res, const char* fmt = NULL, ...)
	{
		static int indent; indent += (mode == 1 ? 4 : (mode == 2 ? -4 : 0));
		if (!(domodes & mode)) return;
		if (mode == 1)          WriteLog("  %*s%s [PRE] %s%s", indent, "", prfx, func, (fmt ? "     " : "\n"));
		else if (domodes == 3)  WriteLog("  %*s%s [RES] %s %u%s", indent + 4, "", prfx, func, res, (fmt ? " - " : "\n"));
		else if (domodes == 2)  WriteLog("  %*s%s %s = %u%s", indent + 4, "", prfx, func, res, (fmt ? "     - " : "\n"));
		static int lw; if (mode < 4) lw = (int)(strlen(func)); else WriteLog("  %*s%s    - ", indent, "", prfx);
		if (fmt) { va_list ap; va_start(ap, fmt); VWriteLog(fmt, ap); va_end(ap); if (mode < 4) WriteLog("\n"); }
	}
	static int RepSPrintF(char* buf, size_t len, const char* fmt,...) { va_list ap; va_start(ap, fmt); int r = fpVSNPrintF(buf, len, fmt, ap); va_end(ap); return r; }
	static const char* DIDFTSTR(DWORD f)
	{
		static char buf[512];
		RepSPrintF(buf, 512, "%x%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", f,
			(f==GPDIDFT_ALL?"|ALL":""),(f&GPDIDFT_RELAXIS?"|RELAXIS":""),(f&GPDIDFT_ABSAXIS?"|ABSAXIS":""),
			(f&GPDIDFT_PSHBUTTON?"|PSHBUTTON":""),(f&GPDIDFT_TGLBUTTON?"|TGLBUTTON":""),(f&GPDIDFT_POV?"|POV":""),
			(f&0x20?"|0x20":""),(f&GPDIDFT_COLLECTION?"|COLLECTION":""),(f&GPDIDFT_NODATA?"|NODATA":""),
			(f&GPDIDFT_ANYINSTANCE?((f&GPDIDFT_ANYINSTANCE)==GPDIDFT_ANYINSTANCE?"|ANYINSTANCE":"|ANYINSTANCE_WEIRD"):""),
			(f&GPDIDFT_FFACTUATOR?"|FFACTUATOR":""),(f&GPDIDFT_FFEFFECTTRIGGER?"|FFEFFECTTRIGGER":""),
			(f&GPDIDFT5_VENDORDEFINED?"|VENDORDEFINED":""),(f&GPDIDFT5_ALIAS?"|ALIAS":""),(f&GPDIDFT5_OUTPUT?"|OUTPUT":""),
			(f&0x20000000?"|0x20000000":""),(f&0x40000000?"|0x40000000":""),(f&GPDIDFT_OPTIONAL?"|OPTIONAL":""));
		return buf;
	}
	static const char* DIOSTR(DWORD f)
	{
		static char buf[512];
		RepSPrintF(buf, 512, "%x%s%s%s%s%s%s%s%s", f,
			(f&GPDIDOI_FFACTUATOR?"|FFACTUATOR":""),(f&GPDIDOI_FFEFFECTTRIGGER?"|FFEFFECTTRIGGER":""),(f&GPDIDOI_ASPECTPOSITION?"|ASPECTPOSITION":""),
			(f&GPDIDOI_ASPECTVELOCITY?"|ASPECTVELOCITY":""),(f&GPDIDOI_ASPECTFORCE?"|ASPECTFORCE":""),(f&GPDIDOI_POLLED?"|POLLED":""),(f&GPDIDOI5_GUIDISUSAGE?"|GUIDISUSAGE":""),
			(f&~(GPDIDOI_FFACTUATOR|GPDIDOI_FFEFFECTTRIGGER|GPDIDOI_ASPECTPOSITION|GPDIDOI_ASPECTVELOCITY|GPDIDOI_ASPECTACCEL|GPDIDOI_ASPECTFORCE|GPDIDOI_ASPECTMASK|GPDIDOI_POLLED|GPDIDOI5_GUIDISUSAGE)?"|SOME_UNKNOWNS???":""));
		return buf;
	}
	static const char* DISCLSTR(DWORD f)
	{
		static char buf[512];
		RepSPrintF(buf, 512, "%x%s%s%s%s%s%s", f,
			(f&GPDISCL_EXCLUSIVE?"|EXCLUSIVE":""),(f&GPDISCL_NONEXCLUSIVE?"|NONEXCLUSIVE":""),(f&GPDISCL_FOREGROUND?"|FOREGROUND":""),
			(f&GPDISCL_BACKGROUND?"|BACKGROUND":""),(f&GPDISCL_NOWINKEY?"|NOWINKEY":""),
			(f&~(GPDISCL_EXCLUSIVE|GPDISCL_NONEXCLUSIVE|GPDISCL_FOREGROUND|GPDISCL_BACKGROUND|GPDISCL_NOWINKEY)?"|SOME_UNKNOWNS???":""));
		return buf;
	}
	static const char* GUIDTYPESTR(const GUID& g)
	{
		DWORD o = g.Data1;
		return (o==0xA36D02E0?"XAxis":(o==0xA36D02E1?"YAxis":(o==0xA36D02E2?"ZAxis":(o==0xA36D02E3?"RzAxis":(o==0xA36D02E4?"Slider":(o==0xA36D02F0?"Button":(o==0xA36D02F2?"POV":(o==0xA36D02F3?"Unknow":(o==0xA36D02F4?"RxAxis":(o==0xA36D02F5?"RyAxis":(o==0x55728220?"Key":"UNKNOWN")))))))))));
	}
	#define PROXYMETHOD(DO, RET, NAME, ARGS, PARAMS, ...) virtual RET STDMETHODCALLTYPE NAME ARGS { Report::Print(PROXYPREFIX, DO, 1, #NAME,   0, __VA_ARGS__); auto res = Outer->NAME PARAMS;                                          Report::Print(PROXYPREFIX, DO, 2, #NAME, res, __VA_ARGS__); return res; }
	#define PROXYPRINTM(DO, RET, NAME, ARGS, PARAMS, ...) virtual RET STDMETHODCALLTYPE NAME ARGS { Report::Print(PROXYPREFIX, DO, 1, #NAME,   0, __VA_ARGS__); auto res = Outer->NAME PARAMS; /*if (res == S_OK)*/ Print##NAME PARAMS; Report::Print(PROXYPREFIX, DO, 2, #NAME, res, __VA_ARGS__); return res; }
	#define PROXYCUSTOM(DO, RET, NAME, ARGS, PARAMS, ...) virtual RET STDMETHODCALLTYPE NAME ARGS { Report::Print(PROXYPREFIX, DO, 1, #NAME,   0, __VA_ARGS__); auto res = Custom##NAME PARAMS;                                         Report::Print(PROXYPREFIX, DO, 2, #NAME, res, __VA_ARGS__); return res; }
	#define PROXYPRINTF(...)       Report::Print(PROXYPREFIX, 4, 4, "", 0, __VA_ARGS__)
	#define PROXYPRINTFAW(fmta, fmtw, ...) Report::Print(PROXYPREFIX, 4, 4, "", 0, (IsW?fmtw:fmta), __VA_ARGS__)
	#define GUIDFMT "{ 0x%08X, 0x%04X, 0x%04X, { 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X } }"
	#define GUIDPRINTF(G) (G).Data1, (G).Data2, (G).Data3, (G).Data4[0], (G).Data4[1], (G).Data4[2], (G).Data4[3], (G).Data4[4], (G).Data4[5], (G).Data4[6], (G).Data4[7]

	struct DirectInputDevice
	{
		GPDirectInputDevice* Outer;
		bool IsW;
		DirectInputDevice(GPDirectInputDevice* outer, bool isW) : Outer(outer), IsW(isW) { }
		#define PROXYPREFIX "    [DEV]"
		PROXYCUSTOM(3, HRESULT, QueryInterface, (const GUID& riid, void** ppvObject), (riid, ppvObject), "ID: " GUIDFMT " - Object: %p", GUIDPRINTF(riid), (ppvObject ? *ppvObject : 0))
		HRESULT CustomQueryInterface(const GUID& riid, void** ppvObject) { *ppvObject = this; AddRef(); return S_OK; }
		PROXYMETHOD(2, ULONG, AddRef, (), ())
		PROXYMETHOD(2, ULONG, Release, (), ())
		PROXYPRINTM(3, HRESULT, GetCapabilities, (GPDIDEVCAPS* lpDIDevCaps), (lpDIDevCaps))
		void PrintGetCapabilities(GPDIDEVCAPS* p)
		{
			PROXYPRINTF("dwSize: %u, dwFlags: %u, dwDevType: %u, dwAxes: %u, dwButtons: %u, dwPOVs: %u\n", p->dwSize, p->dwFlags, p->dwDevType, p->dwAxes, p->dwButtons, p->dwPOVs);
			if (p->dwSize == sizeof(*p))
				PROXYPRINTF("dwFFSamplePeriod: %u, dwFFMinTimeResolution: %u, dwFirmwareRevision: %u, dwHardwareRevision: %u, dwFFDriverVersion: %u\n", p->dwFFSamplePeriod, p->dwFFMinTimeResolution, p->dwFirmwareRevision, p->dwHardwareRevision, p->dwFFDriverVersion);
		}
		PROXYCUSTOM(3, HRESULT, EnumObjects, (GPDIEnumDeviceObjectsCB lpCallback, LPVOID pvRef, DWORD dwFlags), (lpCallback, pvRef, dwFlags), "CB: %s - pvRef: %s - flags: %s", (lpCallback ? "OK" : "NULL"), (pvRef ? "SET" : "NULL"), Report::DIDFTSTR(dwFlags))
		HRESULT CustomEnumObjects(GPDIEnumDeviceObjectsCB lpCallback, LPVOID pvRef, DWORD dwFlags)
		{
			struct SData { bool isW; GPDIEnumDeviceObjectsCB lpCallback; LPVOID pvRef; } dt = { IsW, lpCallback, pvRef };
			struct Local { static BOOL CALLBACK CB(const GPDIDeviceObjectInstance* doi, SData& dt)
			{
				bool IsW = dt.isW;
				auto e = doi->GetExtra(IsW);
				PROXYPRINTFAW(
					"CB! Size: %u - Type: " GUIDFMT " (%s) - Ofs: %u - Type: %u - Flags: %u - Name: %s\n",
					"CB! Size: %u - Type: " GUIDFMT " (%s) - Ofs: %u - Type: %u - Flags: %u - Name: %S\n",
					doi->dwSize, GUIDPRINTF(doi->guidType), Report::GUIDTYPESTR(doi->guidType),
					doi->dwOfs, doi->dwType, doi->dwFlags, doi->tszName);
				if (doi->dwSize == doi->GetSize(IsW))
					PROXYPRINTF("FFMaxForce: %u - FFForceRes: %u - CollNumber: %d - DesigIdx: %d - UsagePage: %d - Usage: %d - Dimension: %d - Exp: %d - Res: %d\n",
						e->dwFFMaxForce, e->dwFFForceResolution, e->wCollectionNumber, e->wDesignatorIndex, e->wUsagePage, e->wUsage, e->dwDimension, e->wExponent, e->wReserved);
				return (dt.lpCallback ? dt.lpCallback(doi, dt.pvRef) : GPDIENUM_CONTINUE);
			}};
			return Outer->EnumObjects((GPDIEnumDeviceObjectsCB)Local::CB, &dt, dwFlags);
		}
		PROXYPRINTM(3, HRESULT, GetProperty, (const GUID& rguidProp, GPDIPropHeader* pdiph), (rguidProp, pdiph))
		void PrintGetProperty(const GUID& g, const GPDIPropHeader* p)
		{
			const char* propnames[] = {"NULL","BUFFERSIZE","AXISMODE","GRANULARITY","RANGE","DEADZONE","SATURATION","FFGAIN","FFLOAD","AUTOCENTER","CALIBRATIONMODE","CALIBRATION","GUIDANDPATH","INSTANCENAME","PRODUCTNAME","JOYSTICKID","GETPORTDISPLAYNAME","UNKNOWN_17","PHYSICALRANGE","LOGICALRANGE","KEYNAME","CPOINTS","APPDATA","SCANCODE","VIDPID","USERNAME","TYPENAME","UNKNOWN_27","UNKNOWN_28","UNKNOWN_29","UNKNOWN"};
			if ((size_t)&g < 30) { PROXYPRINTF("GUID: %u (%s), dwSize: %u, dwHeaderSize: %u, dwObj: %u, dwHow: %u - DATA:", &g, ((size_t)&g<30?propnames[(size_t)&g]:"-"), p->dwSize, p->dwHeaderSize, p->dwObj, p->dwHow); }
			else                 { PROXYPRINTF("GUID: " GUIDFMT ", dwSize: %u, dwHeaderSize: %u, dwObj: %u, dwHow: %u - DATA:", GUIDPRINTF(g), p->dwSize, p->dwHeaderSize, p->dwObj, p->dwHow); }
			for (DWORD i = p->dwHeaderSize; i != p->dwSize; i++) WriteLog(" %02x", ((BYTE*)p)[i]);
			for (DWORD i = p->dwHeaderSize; i < p->dwSize-3; i+=4) WriteLog(" %u", *(DWORD*)&((BYTE*)p)[i]);
			switch ((size_t)&g)
			{
				case GPDIPROP_RANGE:{
					const GPDIPropRange* pdiphRange = (const GPDIPropRange*)p;
					PROXYPRINTF("    RANGE - MIN: %d - MAX: %d", pdiphRange->lMin, pdiphRange->lMax);
					}break;
				case GPDI5PROP_GUIDANDPATH:{
					const GPDIPropGUIDAndPath* pdiphGUIDAndPath = (const GPDIPropGUIDAndPath*)p;
					PROXYPRINTF("    GUIDANDPATH - guidClass: " GUIDFMT " - Path: %S", GUIDPRINTF(pdiphGUIDAndPath->guidClass), pdiphGUIDAndPath->wszPath);
					}break;
			}
			WriteLog("\n");
		}
		PROXYPRINTM(3, HRESULT, SetProperty, (const GUID& rguidProp, const GPDIPropHeader* pdiph), (rguidProp, pdiph),)
		void PrintSetProperty(const GUID& g, const GPDIPropHeader* p) { PrintGetProperty(g, p); }
		PROXYMETHOD(0, HRESULT, Acquire, (), (),)
		PROXYMETHOD(2, HRESULT, Unacquire, (), (),)
		PROXYPRINTM(/*3*/0, HRESULT, GetDeviceState, (DWORD cbData, LPVOID lpvData), (cbData, lpvData),"Size: %u - Data %p...", cbData, *(UINT_PTR*)lpvData)
		void PrintGetDeviceState(DWORD cbData, LPVOID lpvData)
		{
			return;
			char buf[2048], *pbuf = buf;
			for (BYTE* p = (BYTE*)lpvData, *pEnd = p + cbData; p != pEnd && pbuf + 8 < buf + sizeof(buf); p++)
				pbuf += RepSPrintF(pbuf, 2048, "0x%02X, ", *p);
			WriteLog("{ %s }\n", buf);
		}
		PROXYPRINTM(0, HRESULT, GetDeviceData, (DWORD cbObjectData, GPDIDeviceObjectData* rgdod, LPDWORD pdwInOut, DWORD dwFlags), (cbObjectData, rgdod, pdwInOut, dwFlags), "SizeObjectData: %u - NumObj: %u - RGDODPTR: %p - Flags: %u (!0==PEEK)", cbObjectData, *pdwInOut, rgdod, dwFlags)
		void PrintGetDeviceData(DWORD cbObjectData, GPDIDeviceObjectData* rgdod, LPDWORD pdwInOut, DWORD dwFlags)
		{
			if (*pdwInOut && *pdwInOut != 0xFFFFFFFF)
				PROXYPRINTF("SizeObjectData: %u - NumObj: %u - RGDODPTR: %p - Flags: %u (!0==PEEK)\n", cbObjectData, *pdwInOut, rgdod, dwFlags);
			for (DWORD i = 0; i != *pdwInOut && rgdod; i++, rgdod = (GPDIDeviceObjectData*)((char*)rgdod + cbObjectData))
			{
				PROXYPRINTF("[%u] Ofs: %u - Data: %u - Time: %u - Seq: %u - AppData: %p\n", i,
					rgdod->dwOfs, rgdod->dwData, rgdod->dwTimeStamp, rgdod->dwSequence, rgdod->uAppData);
			}
		}
		PROXYPRINTM(3, HRESULT, SetDataFormat, (const GPDIDataFormat* lpdf), (lpdf), "Size: %u - ObjSize: %u - Flags: %x - DataSize: %u - NumObjs: %u", lpdf->dwSize, lpdf->dwObjSize, lpdf->dwFlags, lpdf->dwDataSize, lpdf->dwNumObjs)
		void PrintSetDataFormat(const GPDIDataFormat* lpdf)
		{
			for (DWORD i = 0; i != lpdf->dwNumObjs; i++)
				PROXYPRINTF("[%u] PGUID: %x (%s) - Ofs: %u - Type: %s - Flags: %s\n",
				i, (lpdf->rgodf[i].pguid ? lpdf->rgodf[i].pguid->Data1 : 0), (lpdf->rgodf[i].pguid ? Report::GUIDTYPESTR(*lpdf->rgodf[i].pguid) : ""),
				lpdf->rgodf[i].dwOfs, Report::DIDFTSTR(lpdf->rgodf[i].dwType), Report::DIOSTR(lpdf->rgodf[i].dwFlags));
		}
		PROXYMETHOD(2, HRESULT, SetEventNotification, (HANDLE hEvent), (hEvent),)
		PROXYMETHOD(2, HRESULT, SetCooperativeLevel, (HWND hwnd, DWORD dwFlags), (hwnd, dwFlags),"HWND: %p - DISCL: %s", hwnd, Report::DISCLSTR(dwFlags))
		PROXYPRINTM(3, HRESULT, GetObjectInfo, (GPDIDeviceObjectInstance* doi, DWORD dwObj, DWORD dwHow), (doi, dwObj, dwHow), "dwObj: %u - dwHow: %u", dwObj, dwHow)
		void PrintGetObjectInfo(GPDIDeviceObjectInstance* doi, DWORD dwObj, DWORD dwHow)
		{
			auto e = doi->GetExtra(IsW);
			PROXYPRINTF("Size: %u, guidType: " GUIDFMT ", Ofs: %u, Type: %u, dwFlags: %x\n", doi->dwSize, GUIDPRINTF(doi->guidType), doi->dwOfs, doi->dwType, DIOSTR(doi->dwFlags));
			PROXYPRINTFAW("tszName: %s\n", "tszName: %S\n", doi->tszName);
			if (doi->dwSize == doi->GetSize(IsW)) PROXYPRINTF("CollectionNumber: %u, UsagePage: %u, Usage: %u, Dimension: %u\n", e->wCollectionNumber, e->wUsagePage, e->wUsage, e->dwDimension);
		}
		PROXYPRINTM(3, HRESULT, GetDeviceInfo, (GPDIDeviceInstance* di), (di))
		void PrintGetDeviceInfo(GPDIDeviceInstance* di)
		{
			auto e = di->GetExtra(IsW);
			PROXYPRINTF("Size: %u, guidInstance: " GUIDFMT ", guidProduct: " GUIDFMT ", DevType: %x\n", di->dwSize, GUIDPRINTF(di->guidInstance), GUIDPRINTF(di->guidProduct), di->dwDevType);
			PROXYPRINTFAW("tszInstanceName: %s, tszProductName: %s\n", "tszInstanceName: %S, tszProductName: %S\n", di->tszInstanceName, (IsW ? (char*)di->tszProductName : di->tszProductNameA));
			if (di->dwSize == di->GetSize(IsW)) PROXYPRINTF("guidFFDriver: " GUIDFMT ", wUsagePage: %d, wUsage: %d\n", GUIDPRINTF(e->guidFFDriver), e->wUsagePage, e->wUsage);
		}
		PROXYMETHOD(2, HRESULT, RunControlPanel, (HWND hwndOwner, DWORD dwFlags), (hwndOwner, dwFlags),)
		PROXYMETHOD(2, HRESULT, Initialize, (HINSTANCE hinst, DWORD dwVersion, const GUID& rguid), (hinst, dwVersion, rguid),)
		PROXYMETHOD(2, HRESULT, CreateEffect, (const GUID& rguid, const GPDIEffect* lpeff, GPIDirectInputEffect** ppdeff, void* punkOuter), (rguid, lpeff, ppdeff, punkOuter),)
		PROXYCUSTOM(3, HRESULT, EnumEffects, (GPDIEnumEffectsCB lpCallback, LPVOID pvRef, DWORD dwEffType), (lpCallback, pvRef, dwEffType), "CB: %s - pvRef: %s - dwEffType: %u", (lpCallback ? "OK" : "NULL"), (pvRef ? "SET" : "NULL"), dwEffType)
		HRESULT CustomEnumEffects(GPDIEnumEffectsCB lpCallback, LPVOID pvRef, DWORD dwEffType)
		{
			struct SData { bool isW; GPDIEnumEffectsCB lpCallback; LPVOID pvRef; } dt = { IsW, lpCallback, pvRef };
			struct Local { static BOOL CALLBACK CB(const GPDIEffectInfo* ei, SData& dt)
			{
				bool IsW = dt.isW;
				PROXYPRINTFAW(
					"CB! Size: %u - guid: " GUIDFMT " - dwEffType: %u - dwStaticParams: %u - dwDynamicParams: %u - Name: %s\n",
					"CB! Size: %u - guid: " GUIDFMT " - dwEffType: %u - dwStaticParams: %u - dwDynamicParams: %u - Name: %S\n",
					ei->dwSize, GUIDPRINTF(ei->guid), ei->dwEffType, ei->dwStaticParams, ei->dwDynamicParams, ei->tszName);
				return (dt.lpCallback ? dt.lpCallback(ei, dt.pvRef) : GPDIENUM_CONTINUE);
			}};
			return Outer->EnumEffects((GPDIEnumEffectsCB)Local::CB, &dt, dwEffType);
		}
		PROXYMETHOD(2, HRESULT, GetEffectInfo, (GPDIEffectInfo* ei, const GUID& rguid), (ei, rguid),)
		PROXYMETHOD(2, HRESULT, GetForceFeedbackState, (LPDWORD pdwOut), (pdwOut),)
		PROXYMETHOD(2, HRESULT, SendForceFeedbackCommand, (DWORD dwFlags), (dwFlags),)
		PROXYMETHOD(2, HRESULT, EnumCreatedEffectObjects, (GPDIEnumCreatedEffectObjectsCB lpCallback, LPVOID pvRef, DWORD fl), (lpCallback, pvRef, fl),)
		PROXYMETHOD(2, HRESULT, Escape, (GPDIEffectEscape* pesc), (pesc),)
		PROXYMETHOD(0, HRESULT, Poll, (), (),)
		PROXYMETHOD(2, HRESULT, SendDeviceData, (DWORD cbObjectData, const GPDIDeviceObjectData* rgdod, LPDWORD pdwInOut, DWORD fl), (cbObjectData, rgdod, pdwInOut, fl),)
		PROXYMETHOD(2, HRESULT, EnumEffectsInFile, (void* lpszFileNameAorW, GPDIEnumEffectsInFileCB pec, LPVOID pvRef, DWORD dwFlags), (lpszFileNameAorW, pec, pvRef, dwFlags),)
		PROXYMETHOD(2, HRESULT, WriteEffectToFile, (void* lpszFileNameAorW, DWORD dwEntries, GPDIFileEffect* rgDiFileEft, DWORD dwFlags), (lpszFileNameAorW, dwEntries, rgDiFileEft, dwFlags),)
		PROXYMETHOD(2, HRESULT, BuildActionMap, (GPDIActionFormat* lpdiaf, void* lpszUserNameAorW, DWORD dwFlags), (lpdiaf, lpszUserNameAorW, dwFlags),)
		PROXYMETHOD(2, HRESULT, SetActionMap, (GPDIActionFormat* lpdiaf, void* lpszUserNameAorW, DWORD dwFlags), (lpdiaf, lpszUserNameAorW, dwFlags),)
		PROXYMETHOD(2, HRESULT, GetImageInfo, (GPDIDeviceImageInfoHeader* lpdiDevImageInfoHeader), (lpdiDevImageInfoHeader),)
		#undef PROXYPREFIX
	};

	struct DirectInputInterface
	{
		GPDirectInputInterface* Outer;
		bool IsW;
		DirectInputInterface(GPDirectInputInterface* outer, bool isW) : Outer(outer), IsW(isW) { }
		#define PROXYPREFIX "[DI8]"
		PROXYCUSTOM(3, HRESULT, QueryInterface, (const GUID& riid, void** ppvObject), (riid, ppvObject), "ID: " GUIDFMT " - Object: %p", GUIDPRINTF(riid), (ppvObject ? *ppvObject : 0))
		HRESULT CustomQueryInterface(const GUID& riid, void** ppvObject) { if (riid.Data1 == GPDI_IID_IDirectInputJoyConfig) return Outer->QueryInterface(riid, ppvObject); *ppvObject = this; AddRef(); return S_OK; }
		PROXYMETHOD(2, ULONG, AddRef, (), ())
		PROXYMETHOD(2, ULONG, Release, (), ())
		PROXYCUSTOM(3, HRESULT, CreateDevice, (const GUID& rguid, GPDirectInputDevice** lplpDirectInputDevice, void* pUnkOuter), (rguid, lplpDirectInputDevice, pUnkOuter), GUIDFMT " - Device: %p", GUIDPRINTF(rguid), (lplpDirectInputDevice ? *lplpDirectInputDevice : NULL))
		HRESULT CustomCreateDevice(const GUID& rguid, GPDirectInputDevice** lplpDirectInputDevice, void* pUnkOuter)
		{
			HRESULT res = Outer->CreateDevice(rguid, lplpDirectInputDevice, pUnkOuter);
			if (res != S_OK) return res;
			*lplpDirectInputDevice = (GPDirectInputDevice*)new Report::DirectInputDevice(*lplpDirectInputDevice, IsW);
			return S_OK;
		}
		PROXYCUSTOM(3, HRESULT, EnumDevices, (DWORD dwDevType, GPDIEnumDevicesCB lpCallback, LPVOID pvRef, DWORD dwFlags), (dwDevType, lpCallback, pvRef, dwFlags), "DevType: %x - CB: %p - Flags: %u", dwDevType, lpCallback, dwFlags)
		HRESULT CustomEnumDevices(DWORD dwDevType, GPDIEnumDevicesCB lpCallback, LPVOID pvRef, DWORD dwFlags)
		{
			struct SData { bool isW; GPDIEnumDevicesCB lpCallback; LPVOID pvRef; } dt = { IsW, lpCallback, pvRef };
			struct Local { static BOOL CALLBACK CB(/*const*/ GPDIDeviceInstance* di, SData& dt)
			{
				bool IsW = dt.isW;
				auto e = di->GetExtra(IsW);
				PROXYPRINTF("CB! Size: %u - Instance: " GUIDFMT " - Product: " GUIDFMT " - DevType: %x\n", di->dwSize, GUIDPRINTF(di->guidInstance), GUIDPRINTF(di->guidProduct), di->dwDevType);
				PROXYPRINTFAW("tszInstanceName: %s, tszProductName: %s\n", "tszInstanceName: %S, tszProductName: %S\n", di->tszInstanceName, (IsW ? (char*)di->tszProductName : di->tszProductNameA));
				PROXYPRINTF("    guidFFDriver: " GUIDFMT " - wUsagePage: %u - wUsage: %u\n", GUIDPRINTF(e->guidFFDriver), e->wUsagePage, e->wUsage);
				PROXYPRINTF("    --------------------- BEFORE CALLING USER CALLBACK [%p]\n", dt.lpCallback);
				BOOL cbres = (dt.lpCallback ? dt.lpCallback(di, dt.pvRef) : GPDIENUM_CONTINUE);
				PROXYPRINTF("    --------------------- AFTER CALLING USER CALLBACK - RES: %d\n", cbres);
				return cbres;
			}};
			return Outer->EnumDevices(dwDevType, (GPDIEnumDevicesCB)Local::CB, &dt, dwFlags);
		}
		PROXYMETHOD(3, HRESULT, GetDeviceStatus, (const GUID& rguidInstance), (rguidInstance))
		PROXYMETHOD(3, HRESULT, RunControlPanel, (HWND hwndOwner, DWORD dwFlags), (hwndOwner, dwFlags))
		PROXYMETHOD(3, HRESULT, Initialize, (HINSTANCE hinst, DWORD dwVersion), (hinst, dwVersion))
		PROXYMETHOD(3, HRESULT, FindDevice, (const GUID& rguid, LPCWSTR pszName, LPGUID pguidInstance), (rguid, pszName, pguidInstance))
		PROXYMETHOD(3, HRESULT, EnumDevicesBySemantics, (const void* ptszUserNameAorW, GPDIActionFormat* lpdiActionFormat, GPDIEnumDevicesBySemanticsCB lpCallback, LPVOID pvRef, DWORD dwFlags), (ptszUserNameAorW, lpdiActionFormat, lpCallback, pvRef, dwFlags))
		PROXYMETHOD(3, HRESULT, ConfigureDevices, (GPDIConfigureDevicesCB lpdiCallback, GPDIConfigureDevicesParams* lpdiCDParams, DWORD dwFlags, LPVOID pvRefData), (lpdiCallback, lpdiCDParams, dwFlags, pvRefData))
		#undef PROXYPREFIX
	};
};
#endif

typedef HRESULT (WINAPI *GPDirectInput8CreateFN)(HINSTANCE hinst, DWORD dwVersion, const GUID& riidltf, GPDirectInputInterface** ppvOut, void* punkOuter);
static GPDirectInput8CreateFN ModuleCreate8;
HRESULT WINAPI GPDirectInput8Create(HINSTANCE hinst, DWORD dwVersion, const GUID& riidltf, GPDirectInputInterface** ppvOut, void* punkOuter)
{
	LOGSCOPE();
	#pragma GPLINKER_DLL_EXPORT_AS(DirectInput8Create)
	if (!ModuleCreate8)
	{
		// if created by COM or one of the legacy DirectInput functions below
		LOGSCOPE("Load DirectInput - InputLock: %d", InputLock);
		GPLock(&InputLock, 3);
		Hook(true);
		InputLock = 0;
		if (!ModuleCreate8) return E_FAIL; // dinput not available on this system
	}
	bool isA = (riidltf.Data1 == GPDI_IID_IDirectInput8A), isW = (riidltf.Data1 == GPDI_IID_IDirectInput8W);
	HRESULT res = ModuleCreate8(hinst, GPDI_VERSION_8, riidltf, ppvOut, punkOuter);
	#if 0 //def GPDIREPORTREALDEVICE
	if (res == S_OK) *ppvOut = (GPDirectInputInterface*)new Report::DirectInputInterface(*ppvOut, isW);
	#endif
	//WriteLog("DirectInput8Create - hinst: %p - dwVersion: %x - riidltf: " GUIDFMT ", A:%d, W:%d, res: %p\n", (void*)hinst, dwVersion, GUIDPRINTF(riidltf), isA, isW, res);
	if (1 && res == S_OK && (isA || isW))
	{
		WriteLog("Application started DirectInput interface\n");
		if (GameUsesXInput && !ForceVirtualDevices && !(pGPData->Options & OPTION_Disable_XInput))
		{
			Hook();
			ForceXInputDeviceId = true;
		}
		*ppvOut = new GPDirectInputInterface(*ppvOut, isW, dwVersion);
		#if 0 //def GPDIREPORTVIRTUALDEVICE
		*ppvOut = (GPDirectInputInterface*)new Report::DirectInputInterface(*ppvOut, isW);
		#endif
	}
	return res;
}

static HRESULT WINAPI GPDirectInputCreateEx(HINSTANCE hinst, DWORD dwVersion, const GUID& riidltf, GPDirectInputInterface** ppvOut, void* punkOuter)
{
	const unsigned long id = riidltf.Data1;
	const GUID& riid8 = ((id == GPDI_IID_IDirectInput8W || id == GPDI_IID_IDirectInput2W || id == GPDI_IID_IDirectInput7W || id == GPDI_IID_IDirectInputW) ? GPDI_GUID_IDirectInput8W : GPDI_GUID_IDirectInput8A);
	return GPDirectInput8Create(hinst, dwVersion, riid8, ppvOut, punkOuter);
}

static HRESULT WINAPI GPDirectInputCreateA(HINSTANCE hinst, DWORD dwVersion, GPDirectInputInterface** ppvOut, void* punkOuter)
{
	return GPDirectInput8Create(hinst, dwVersion, GPDI_GUID_IDirectInput8A, ppvOut, punkOuter);
}

static HRESULT WINAPI GPDirectInputCreateW(HINSTANCE hinst, DWORD dwVersion, GPDirectInputInterface** ppvOut, void* punkOuter)
{
	return GPDirectInput8Create(hinst, dwVersion, GPDI_GUID_IDirectInput8W, ppvOut, punkOuter);
}

HRESULT WINAPI FakeDINPUT8COMInterface()
{
	#pragma GPLINKER_DLL_EXPORT_AS_PRIVATE(DllCanUnloadNow)
	#pragma GPLINKER_DLL_EXPORT_AS_PRIVATE(DllGetClassObject)
	#pragma GPLINKER_DLL_EXPORT_AS_PRIVATE(DllRegisterServer)
	#pragma GPLINKER_DLL_EXPORT_AS_PRIVATE(DllUnregisterServer)
	return E_FAIL;
}

#define GPDI_DEBUG_WRITELOG(...)
#if 0 // log detailed API calls
#undef  GPDI_DEBUG_WRITELOG
#define GPDI_DEBUG_WRITELOG(...) WriteLog(__VA_ARGS__);
#endif

struct GPInjectCOM
{
	static LPVOID Pre(const GUID& riid)
	{
		GPDI_DEBUG_WRITELOG("[COM] Create Instance - riid: " GUIDFMT "\n", GUIDPRINTF(riid));
		DWORD diVer, isW = 0;
		switch (riid.Data1)
		{
			case GPDI_IID_IDirectInput8A: diVer = 0x800; break;
			case GPDI_IID_IDirectInput8W: diVer = 0x800; isW = 1; break;
			case GPDI_IID_IDirectInput7A: diVer = 0x700; break;
			case GPDI_IID_IDirectInput7W: diVer = 0x700; isW = 1; break;
			case GPDI_IID_IDirectInput2A: diVer = 0x200; break;
			case GPDI_IID_IDirectInput2W: diVer = 0x200; isW = 1; break;
			case GPDI_IID_IDirectInputA:  diVer = 0x100; break;
			case GPDI_IID_IDirectInputW:  diVer = 0x100; isW = 1; break;
			default: return NULL;
		}
		GPDirectInputInterface* ppv = NULL;
		GPDI_DEBUG_WRITELOG("[COM] Create Instance - DirectInput Version: %x\n", diVer);
		return (GPDirectInputCreateEx(GetModuleHandleA(NULL), diVer, (isW ? GPDI_GUID_IDirectInput8W : GPDI_GUID_IDirectInput8A), &ppv, NULL) == S_OK ? ppv : NULL);
	}

	static HRESULT Post(HRESULT res, const GUID& riid, LPVOID *ppv)
	{
		HOOKFUNC_START(HRESULT, WBEMClassObjectGet, (void* self, LPCWSTR wszName, long lFlags, VARIANT *out_pVal, void *out_pCImType, long *out_plFlavor))
		{
			HRESULT res = fpWBEMClassObjectGet(self, wszName, lFlags, out_pVal, out_pCImType, out_plFlavor);
			GPDI_DEBUG_WRITELOG("[WBEM] wbemServices::ClassObject::Get - wszName: %S - bstrvap: %S, res: %x\n", wszName, (out_pVal && out_pVal->vt == VT_BSTR && out_pVal->bstrVal ? out_pVal->bstrVal : L"-"), res);
			if (ForceXInputDeviceId && !InDirectInputCall && out_pVal && out_pVal->vt == VT_BSTR && out_pVal->bstrVal && (!wcscmp(wszName, L"DeviceID") || !wcscmp(wszName, L"PNPDeviceID")))
			{
				GPDI_DEBUG_WRITELOG("[WBEM] FORCING XINPUT DEVICE ID!!!\n");
				ForceXInputDeviceId = false;
				GPASSERT(GPDI_GUID_XBOXProduct.Data1 == 0x028E045E); // make sure this still matches
				out_pVal->bstrVal = (wchar_t*)XBOXDeviceInstance;
			}
			return res;
		}HOOKFUNC_END
		HOOKFUNC_START(HRESULT, WBEMInstanceEnumNext, (void* self, long lTimeout, ULONG uCount, void *apObjects[], ULONG *puReturned))
		{
			if (puReturned) *puReturned = 0;
			HRESULT res = fpWBEMInstanceEnumNext(self, lTimeout, uCount, apObjects, puReturned); // res is S_FALSE once *puReturned is less than uCount
			GPDI_DEBUG_WRITELOG("[WBEM] wbemServices::InstanceEnum::Next - uCount: %d, puReturned: %d, res: %x\n", (int)uCount, (int)(puReturned ? *puReturned : 0), res);
			if (!apObjects || !apObjects[0] || !puReturned || !*puReturned) return res;
			HOOKONCE((*(void***)apObjects[0])[4], WBEMClassObjectGet, true);
			return res;
		}HOOKFUNC_END
		HOOKFUNC_START(HRESULT, WBEMCreateInstanceEnum, (void* self, const BSTR strFilter, long lFlags, void* pCtx, void **ppEnumWbemClassObject))
		{
			HRESULT res = fpWBEMCreateInstanceEnum(self, strFilter, lFlags, pCtx, ppEnumWbemClassObject);
			GPDI_DEBUG_WRITELOG("[WBEM] wbemServices::CreateInstanceEnum - res: %x\n", res);
			if (res != S_OK || !ppEnumWbemClassObject || !*ppEnumWbemClassObject) return res;
			HOOKONCE((*(void***)*ppEnumWbemClassObject)[4], WBEMInstanceEnumNext, true);
			return S_OK;
		}HOOKFUNC_END
		HOOKFUNC_START(HRESULT, WBEMConnectServer, (void* self, const BSTR strNetworkResource, const BSTR strUser, const BSTR strPassword, const BSTR strLocale, long lSecurityFlags, const BSTR strAuthority, void *pCtx, void **ppNamespace))
		{
			HRESULT res = fpWBEMConnectServer(self, strNetworkResource, strUser, strPassword, strLocale, lSecurityFlags, strAuthority, pCtx, ppNamespace);
			GPDI_DEBUG_WRITELOG("[WBEM] ConnectServer - res: %x\n", res);
			if (res != S_OK || !ppNamespace || !*ppNamespace) return res;
			HOOKONCE((*(void***)*ppNamespace)[18], WBEMCreateInstanceEnum, true);
			return S_OK;
		}HOOKFUNC_END
		GPDI_DEBUG_WRITELOG("[COM] Created Instance - riid: " GUIDFMT ", ppv: %p, *ppv: %p, res: %x\n", GUIDPRINTF(riid), ppv, (ppv ? *ppv : ppv), res);
		if (res != S_OK || riid.Data1 != GPDI_IID_IWbemLocator) return res;
		void** wbemLocatorVtbl = *(void***)*ppv;
		HOOKONCE(wbemLocatorVtbl[3], WBEMConnectServer, true);
		return S_OK;
	}
};

static void Hook(bool forceLoad)
{
	LOGSCOPE("forceLoad: %d", forceLoad);
	GPCHECKNORECURSION();
	wchar_t path[512];
	wchar_t* ver = path + GetSystemDirectoryW(path, 480) + 7;
	wcscpy(ver - 7, L"\\dinput");

	if (!ModuleCreate8)
	{
		wcscpy(ver, L"8.dll");
		HMODULE hmDI8 = (forceLoad ? fpLoadLibraryW(path) : GetModuleHandleW(path));
		GPASSERT(!ModuleCreate8); // Make sure this wasn't somehow recursively called
		if (hmDI8 && ((ModuleCreate8 = (GPDirectInput8CreateFN)fpGetProcAddress(hmDI8, "DirectInput8Create")) != NULL) && g_hHeap)
		{
			if (!forceLoad) fpLoadLibraryW(path); // Increase reference count to keep hooked library loaded until process ends
			CreateHook((LPVOID)ModuleCreate8, "DirectInput8Create", GPDirectInput8Create, true, (LPVOID*)&ModuleCreate8);
			WriteLog("Intercepting DirectInput8 DLL %S%s\n", path, (forceLoad ? " (also used by Gamepad Phoenix)" : ""));
		}
		if (!g_hHeap) return;
	}

	static bool HookedLegacy;
	if (!HookedLegacy)
	{
		wcscpy(ver, L".dll");
		HMODULE hmDI = GetModuleHandleW(path);
		if (hmDI)
		{
			HookedLegacy = true;
			fpLoadLibraryW(path); // Increase reference count to keep hooked library loaded until process ends
			CreateHook(hmDI, "DirectInputCreateA",  GPDirectInputCreateA,  false);
			CreateHook(hmDI, "DirectInputCreateW",  GPDirectInputCreateW,  false);
			CreateHook(hmDI, "DirectInputCreateEx", GPDirectInputCreateEx,  true);
			WriteLog("Intercepting legacy DirectInput DLL %S\n", path);
		}
	}

	// Some games use various methods of checking if a DirectInput joystick is also an XInput device
	// So we hook these APIs and return fake identifiers that make our simulated joysticks look like proper XInput devices
	// Setupapi and RawInput are used by actual DirectInput internally, so we check against InDirectInputCall to not infer with it
	GPASSERT(GPDI_GUID_XBOXProduct.Data1 == 0x028E045E); // make sure this still matches

	static bool HookedSetupApi;
	HMODULE hmSetupApi;
	if (!HookedSetupApi && (hmSetupApi = GetModuleHandleW(L"Setupapi")) != NULL)
	{
		HookedSetupApi = true;
		fpLoadLibraryW(L"Setupapi"); // Increase reference count to keep hooked library loaded until process ends
		HOOKFUNC_START(BOOL, SetupDiGetDeviceInstanceIdW, (HANDLE DeviceInfoSet, void* DeviceInfoData, PWSTR DeviceInstanceId, DWORD DeviceInstanceIdSize, PDWORD RequiredSize))
		{
			//if (!InDirectInputCall) WriteLog("[SetupDiGetDeviceInstanceIdW PRE] DeviceInfoSet: %p - DeviceInfoData: %p - DeviceInstanceId: %S - DeviceInstanceIdSize: %u - RequiredSize: %u\n", DeviceInfoSet, DeviceInfoData, DeviceInstanceId, DeviceInstanceIdSize, (RequiredSize ? *RequiredSize : -1));
			BOOL res = fpSetupDiGetDeviceInstanceIdW(DeviceInfoSet, DeviceInfoData, DeviceInstanceId, DeviceInstanceIdSize, RequiredSize);
			//if (!InDirectInputCall) WriteLog("[SetupDiGetDeviceInstanceIdW PST] DeviceInfoSet: %p - DeviceInfoData: %p - DeviceInstanceId: %S - DeviceInstanceIdSize: %u - RequiredSize: %u - res: %d\n", DeviceInfoSet, DeviceInfoData, DeviceInstanceId, DeviceInstanceIdSize, (RequiredSize ? *RequiredSize : -1), res);
			if (ForceXInputDeviceId && !InDirectInputCall && res && DeviceInstanceIdSize >= (sizeof(XBOXDeviceInstance)/sizeof(XBOXDeviceInstance[0])))
			{
				GPDI_DEBUG_WRITELOG("[SETUPAPI] FORCING XINPUT DEVICE ID!!!\n");
				ForceXInputDeviceId = false;
				wcscpy(DeviceInstanceId, XBOXDeviceInstance);
				if (RequiredSize) *RequiredSize = (sizeof(XBOXDeviceInstance)/sizeof(XBOXDeviceInstance[0]));
				GPDI_DEBUG_WRITELOG("[SetupDiGetDeviceInstanceIdW FIX] DeviceInfoSet: %p - DeviceInfoData: %p - DeviceInstanceId: %S - DeviceInstanceIdSize: %u - RequiredSize: %u - res: %d\n", DeviceInfoSet, DeviceInfoData, DeviceInstanceId, DeviceInstanceIdSize, (RequiredSize ? *RequiredSize : -1), res);
			}
			return res;
		}
		HOOKFUNC_END_HOOK(hmSetupApi, SetupDiGetDeviceInstanceIdW, true); // this gets called by SetupDiGetDeviceInstanceIdA, no need to hook that
		WriteLog("Intercepting SetupAPI device functions\n");
	}

	static bool HookedRawInput;
	HMODULE hmUser32;
	if (!HookedRawInput && (hmUser32 = GetModuleHandleW(L"User32")) != NULL)
	{
		HookedRawInput = true;
		fpLoadLibraryW(L"User32"); // Increase reference count to keep hooked library loaded until process ends
		struct sGetRawInputDeviceInfo { static void Intercept(UINT uiCommand, LPVOID pData, UINT cbSize, UINT& res, bool isW)
		{
			if (uiCommand == RIDI_DEVICEINFO && ((RID_DEVICE_INFO*)pData)->dwType == RIM_TYPEHID && cbSize >= sizeof(RID_DEVICE_INFO))
			{
				RID_DEVICE_INFO* rdi = (RID_DEVICE_INFO*)pData;
				GPDI_DEBUG_WRITELOG("[GetRawInputDeviceInfoA HID] dwVendorId: 0x%04X - dwProductId: 0x%04X - dwVersionNumber: %u - usUsagePage: %u - usUsage: %u\n", rdi->hid.dwVendorId, rdi->hid.dwProductId, rdi->hid.dwVersionNumber, rdi->hid.usUsagePage, rdi->hid.usUsage);
				rdi->hid.dwVendorId = 0x045E;
				rdi->hid.dwProductId = 0x028E;
				rdi->hid.dwVersionNumber = 0;
				rdi->hid.usUsagePage = 1;
				rdi->hid.usUsage = 5;
				res = sizeof(RID_DEVICE_INFO);
				GPDI_DEBUG_WRITELOG("[GetRawInputDeviceInfoA FIX] dwVendorId: 0x%04X - dwProductId: 0x%04X - dwVersionNumber: %u - usUsagePage: %u - usUsage: %u\n", rdi->hid.dwVendorId, rdi->hid.dwProductId, rdi->hid.dwVersionNumber, rdi->hid.usUsagePage, rdi->hid.usUsage);
			}
			if (uiCommand == RIDI_DEVICENAME && cbSize >= sizeof(XBOXDevicePath))
			{
				GPDI_DEBUG_WRITELOG("[SETUPAPI] FORCING XINPUT DEVICE ID!!!\n");
				ForceXInputDeviceId = false;
				GPDI_DEBUG_WRITELOG("[GetRawInputDeviceInfoA NAM] devicename: ");GPDI_DEBUG_WRITELOG((isW ? "%S\n" : "%s\n"), pData);
				if (isW) MultiByteToWideChar(CP_ACP, 0, XBOXDevicePath, sizeof(XBOXDevicePath), (wchar_t*)pData, cbSize);
				else strcpy((char*)pData, XBOXDevicePath);
				res = sizeof(XBOXDevicePath);
				GPDI_DEBUG_WRITELOG("[GetRawInputDeviceInfoA FIX] devicename: ");GPDI_DEBUG_WRITELOG((isW ? "%S\n" : "%s\n"), pData);
			}
		}};
		HOOKFUNC_START(UINT, GetRawInputDeviceInfoA, (HANDLE hDevice, UINT uiCommand, LPVOID pData, PUINT pcbSize))
		{
			UINT res = fpGetRawInputDeviceInfoA(hDevice, uiCommand, pData, pcbSize);
			if (ForceXInputDeviceId && !InDirectInputCall && (int)res > 0) sGetRawInputDeviceInfo::Intercept(uiCommand, pData, *pcbSize, res, false);
			return res;
		}
		HOOKFUNC_END_HOOK(hmUser32, GetRawInputDeviceInfoA, false);
		HOOKFUNC_START(UINT, GetRawInputDeviceInfoW, (HANDLE hDevice, UINT uiCommand, LPVOID pData, PUINT pcbSize))
		{
			UINT res = fpGetRawInputDeviceInfoW(hDevice, uiCommand, pData, pcbSize);
			if (ForceXInputDeviceId && !InDirectInputCall && (int)res > 0) sGetRawInputDeviceInfo::Intercept(uiCommand, pData, *pcbSize, res, true);
			return res;
		}
		HOOKFUNC_END_HOOK(hmUser32, GetRawInputDeviceInfoW, false);
		HOOKFUNC_START(UINT, GetRawInputDeviceList, (PRAWINPUTDEVICELIST pRawInputDeviceList, PUINT puiNumDevices, UINT cbSize))
		{
			GPDI_DEBUG_WRITELOG("[GetRawInputDeviceList PRE] pRawInputDeviceList: %p - puiNumDevices: %u - cbSize: %u\n", pRawInputDeviceList, (puiNumDevices ? *puiNumDevices : 0), cbSize);
			UINT res = fpGetRawInputDeviceList(pRawInputDeviceList, puiNumDevices, cbSize);
			GPDI_DEBUG_WRITELOG("[GetRawInputDeviceList PST] pRawInputDeviceList: %p - puiNumDevices: %u - cbSize: %u - Res: %u\n", pRawInputDeviceList, (puiNumDevices ? *puiNumDevices : 0), cbSize, res);
			return res;
		}
		HOOKFUNC_END_HOOK(hmUser32, GetRawInputDeviceList, true);
		WriteLog("Intercepting RawInput device functions\n");
	}

	static bool hookedOle32;
	HMODULE hmOle32;
	if (!hookedOle32 && (hmOle32 = GetModuleHandleW(L"ole32")) != NULL)
	{
		hookedOle32 = true;
		fpLoadLibraryW(L"ole32"); // Increase reference count to keep hooked library loaded until process ends
		HOOKFUNC_START(HRESULT, CoCreateInstance, (const GUID& rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, const GUID& riid, LPVOID *ppv))
		{
			if (ppv && (*ppv = GPInjectCOM::Pre(riid)) != NULL) return S_OK;
			return GPInjectCOM::Post(fpCoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppv), riid, ppv);
		}
		HOOKFUNC_END_HOOK(hmOle32, CoCreateInstance, false);
		HOOKFUNC_START(HRESULT, CoGetClassObject, (const GUID& rclsid, DWORD dwClsContext, LPVOID pvReserved, const GUID& riid, LPVOID *ppv))
		{
			if (ppv && (*ppv = GPInjectCOM::Pre(riid)) != NULL) return S_OK;
			return GPInjectCOM::Post(fpCoGetClassObject(rclsid, dwClsContext, pvReserved, riid, ppv), riid, ppv);
		}
		HOOKFUNC_END_HOOK(hmOle32, CoGetClassObject, false);
		HOOKFUNC_START(HRESULT, CoCreateInstanceEx, (const GUID& Clsid, LPUNKNOWN punkOuter, DWORD dwClsCtx, void* pServerInfo, DWORD dwCount, MULTI_QI *pResults))
		{
			if (dwCount == 1 && pResults && pResults->pIID && pResults->pItf && (pResults->pItf = (LPUNKNOWN)GPInjectCOM::Pre(*pResults->pIID)) != NULL) return (pResults->hr = S_OK);
			HRESULT res = fpCoCreateInstanceEx(Clsid, punkOuter, dwClsCtx, pServerInfo, dwCount, pResults);
			return (pResults && pResults->pIID ? GPInjectCOM::Post(res, *pResults->pIID, (LPVOID*)pResults->pItf) : res);
		}
		HOOKFUNC_END_HOOK(hmOle32, CoCreateInstanceEx, true);
		WriteLog("Intercepting COM interface\n");
	}
}

static void SetupInput()
{
	LOGSCOPE("DirectInput loaded already: %d", !!ModuleCreate8);
	if (!ModuleCreate8) Hook(true);
	if (!ModuleCreate8) return; // dinput not available on this system

	enum { GPDI_MAX_MAPPED_DEVICES = 32 }; //because of bitmask in Update
	union GPDIMappedState { GPDIJoyState joy; GPDIKeyboardState key; GPDIMouseState mouse; };
	struct GPDIMappedDevice { GPDirectInputDevice* dev; unsigned int intf_devnum; wchar_t* name; DWORD szState; GPDIMappedState state[2]; unsigned char statebit; bool capturing; };
	static GPVector<GPDIMappedDevice> MappedDevices;
	static HWND deviceNotificationHwnd = 0;
	static bool deviceUpdateNeeded;
	static GPDirectInputInterface* dii;

	EnterDirectInputCall();
	HRESULT createRes = ModuleCreate8(GetModuleHandleW(NULL), 0x800, GPDI_GUID_IDirectInput8W, &dii, 0);
	LeaveDirectInputCall();
	if (createRes != S_OK || !dii) { GPASSERT(false); return; } // invalid dinput?
	//dii = (GPDirectInputInterface*)new Report::DirectInputInterface(dii, true);

	struct GPDICallbacks
	{
		static const wchar_t* GetDevName(unsigned int devNum)
		{
			unsigned int intf_devnum = GPIDMake(GPIDINTERFACE_DINPUT, devNum);
			for (const GPDIMappedDevice& md : MappedDevices)
					if (md.intf_devnum == intf_devnum)
						return md.name;
			return NULL;
		}

		static BOOL CALLBACK Enum(const GPDIDeviceInstance* di, LPVOID pdii)
		{
			LOGSCOPE("DevType: %u - InstanceName: %S", di->dwDevType, di->tszInstanceName);
			if (MappedDevices.size() == GPDI_MAX_MAPPED_DEVICES) { WriteLog("Reached maximum of %d supported DirectInput devices!\n", GPDI_MAX_MAPPED_DEVICES); return GPDIENUM_STOP; }
			GPDirectInputDevice* dev = NULL;
			if (FAILED(((GPDirectInputInterface*)pdii)->CreateDevice(di->guidInstance, &dev, NULL))) return GPDIENUM_CONTINUE;
			if (dev == NULL) return GPDIENUM_CONTINUE;
			//if (FAILED(dev->SetCooperativeLevel((HWND)0, GPDISCL_NONEXCLUSIVE | GPDISCL_FOREGROUND))) { dev->Release(); return GPDIENUM_CONTINUE; }
			if ((di->dwDevType & GPDIDEVTYPE_MASK) >= GPDI8DEVTYPE_OVERRIDE_MIN && (di->dwDevType & GPDIDEVTYPE_MASK) <= GPDI8DEVTYPE_OVERRIDE_MAX)
			{
				if (FAILED(dev->SetDataFormat(GPDIJoyState::GetDataFormat()))) { dev->Release(); return GPDIENUM_CONTINUE; }

				GPDIPropRange propRange = { { sizeof(propRange), sizeof(propRange.diph), 0, GPDIPH_BYOFFSET }, 0, 0xFFFF };
				for (int i = 0; i != GPDIJoyState::AXIS_COUNT; i++)
				{
					propRange.diph.dwObj = (DWORD)FIELD_OFFSET(GPDIJoyState, axes[i]);
					dev->SetProperty(*(const GUID*)(size_t)GPDIPROP_RANGE, &propRange.diph);
				}

				unsigned int hash = (unsigned int)0x811c9dc5;
				for (const char* p = (const char*)&di->guidInstance, *pEnd = (const char*)&di->guidProduct + sizeof(GUID); p != pEnd;)
					hash = ((hash * (unsigned int)0x01000193) ^ (unsigned int)*(p++));

				recheck_conflict_devnum:
				unsigned int intf_devnum = GPIDMake(GPIDINTERFACE_DINPUT, (hash & ((1 << GPID_BITS_DEV)-1)), 0);
				for (const GPDIMappedDevice& md : MappedDevices)
					if (md.intf_devnum == intf_devnum)
						{ hash++; goto recheck_conflict_devnum; }

				MappedDevices.push_back({ dev, intf_devnum, wcsdup(di->tszInstanceName), (DWORD)sizeof(GPDIJoyState) });
			}
			else if ((di->dwDevType & GPDIDEVTYPE_MASK) == GPDI8DEVTYPE_KEYBOARD)
			{
				if (FAILED(dev->SetDataFormat(GPDIKeyboardState::GetDataFormat()))) { dev->Release(); return GPDIENUM_CONTINUE; }
				MappedDevices.push_back({ dev, GPIDMake(GPIDINTERFACE_KEYBOARD, 0, 0), NULL, (DWORD)sizeof(GPDIKeyboardState) });
			}
			else if ((di->dwDevType & GPDIDEVTYPE_MASK) == GPDI8DEVTYPE_MOUSE)
			{
				if (FAILED(dev->SetDataFormat(GPDIMouseState::GetDataFormat()))) { dev->Release(); return GPDIENUM_CONTINUE; }
				MappedDevices.push_back({ dev, GPIDMake(GPIDINTERFACE_MOUSE, 0, 0), NULL, (DWORD)sizeof(GPDIMouseState)-GPDIMouseState::EXCESS_SIZE });
			}
			return GPDIENUM_CONTINUE;
		}

		static void Update(GPGamepad& gp)
		{
			MSG msg;
			while (deviceNotificationHwnd && PeekMessageA(&msg, deviceNotificationHwnd, 0, 0, PM_REMOVE))
				TranslateMessage(&msg), DispatchMessage(&msg);

			if (deviceUpdateNeeded)
			{
				WriteLog("Direct Input update devices...\n");
				deviceUpdateNeeded = false;
				MappedDevices.clear();
				EnterDirectInputCall();
				dii->EnumDevices(GPDI8DEVCLASS_ALL, GPDICallbacks::Enum, dii, GPDIEDFL_ATTACHEDONLY);
				LeaveDirectInputCall();
			}

			if (!MappedDevices.size()) return;
			GPDIMappedDevice *md, *mdBegin = &MappedDevices[0], *mdEnd = mdBegin + MappedDevices.size();
			GPDIMappedState *state, *state_prev;
			for (unsigned int md_intf_devnum = 0, polledDevices = 0, i = 0; i != _GPIDX_MAX; i++)
			{
				unsigned int gpId = gp.IDs[i];
				switch (GPIDGetInterface(gpId))
				{
					case GPIDINTERFACE_KEYBOARD: case GPIDINTERFACE_MOUSE: case GPIDINTERFACE_DINPUT: case GPIDINTERFACE_CAPTURE_NEXT_KEY: break;
					default: continue;
				}
				unsigned int gp_intf_devnum = (gpId & GPID_INTF_DEVNUM_MASK);
				bool isCapture = (gp_intf_devnum == GPID_CAPTURE_NEXT_KEY);
				if (md_intf_devnum != gp_intf_devnum)
				{
					for (md = mdBegin; md != mdEnd; md++)
					{
						if (md->intf_devnum != gp_intf_devnum && !isCapture) continue;

						if (!(polledDevices & (1U << (md - mdBegin))))
						{
							polledDevices |= (1U << (md - mdBegin));
							if (FAILED(md->dev->Poll()))
								if (FAILED(md->dev->Acquire()))
									if (FAILED(md->dev->Acquire()))
										md->dev->Poll();

							md->dev->GetDeviceState(md->szState, &md->state[md->statebit ^= 1]);

							if (isCapture != md->capturing)
							{
								md->capturing = isCapture;
								if (isCapture)
								{
									// clear existing state
									md->dev->Poll();
									md->dev->GetDeviceState(md->szState, &md->state[0]);
									md->dev->GetDeviceState(md->szState, &md->state[1]);
								}
							}
						}
						if (!isCapture) { state = &md->state[md->statebit]; md_intf_devnum = md->intf_devnum; break; }
					}
					if (md == mdEnd) { md_intf_devnum = 0; if (!isCapture) continue; }
				}
				switch (GPIDGetInterface(gp_intf_devnum))
				{
					case GPIDINTERFACE_KEYBOARD:
					{
						unsigned int o = GPIDGetObjNum(gpId);
						BYTE pressed = (o < GPDI_MAX_KEYBOARD ? state->key.keys[o] : 0);
						gp.Vals[i] = (pressed ? 0xFFFF : 0);
						break;
					}
					case GPIDINTERFACE_MOUSE:
					{
						unsigned int o = GPIDGetObjNum(gpId);
						if (o < (GPDIMouseState::AXIS_COUNT*2))
						{
							LONG val = state->mouse.axes[o / 2];
							switch (o & 1)
							{
								case 0: val = (val > 0 ? ( val * 600) : 0); break;
								case 1: val = (val < 0 ? (-val * 600) : 0); break;
							}
							// use the Sensitivity analog stick calibration value as a factor to decide how fast mouse controlled sticks move back to the center
							float sens = (i <= GPIDX_RSTICK_R ? 0.01f+0.00045f*(gp.Cals[i <= GPIDX_LSTICK_R ? GPCAL_LSENS : GPCAL_RSENS]+100) : 0.07f);
							float factor = GPPow(0.75f, gp.DeltaTime * sens);
							val += (int)(gp.Vals[i] * factor);
							gp.Vals[i] = (unsigned short)(val > 0xFFFF ? 0xFFFF : val);
							if (gp.Vals[i] > 0x4000 && i <= GPIDX_RSTICK_R) gp.Vals[i^1] = 0; // clear other side of analog stick axis
						}
						else if (o < (GPDIMouseState::AXIS_COUNT*2+GPDIMouseState::BUTTON_COUNT))
						{
							BYTE pressed = state->mouse.buttons[o-(GPDIMouseState::AXIS_COUNT*2)];
							gp.Vals[i] = (pressed ? 0xFFFF : 0);
						}
						break;
					}
					case GPIDINTERFACE_DINPUT:
					{
						unsigned int o = GPIDGetObjNum(gpId);
						if (o < (GPDIJoyState::AXIS_COUNT*4))
						{
							DWORD val = state->joy.axes[o / 4];
							switch (o & 3)
							{
								case 0: gp.Vals[i] = (val > 0x8000 ? (unsigned short)((val - 0x8000) * 0xFFFF / 0x7FFF) : 0); break;
								case 1: gp.Vals[i] = (val < 0x8000 ? (unsigned short)((0x8000 - val) * 0xFFFF / 0x8000) : 0); break;
								case 2: gp.Vals[i] = (val > 0x8000 ? (unsigned short)((0xFFFF - val) * 0xFFFF / 0x7FFF) : 0); break;
								case 3: gp.Vals[i] = (val < 0x8000 ? (unsigned short)((val         ) * 0xFFFF / 0x8000) : 0); break;
							}
						}
						else if (o < (GPDIJoyState::AXIS_COUNT*4+GPDIJoyState::POV_COUNT*4))
						{
							DWORD val = state->joy.pov[(o-(GPDIJoyState::AXIS_COUNT*4)) / 4];
							switch (o & 3)
							{
								case 0: gp.Vals[i] = ((val < 6000 || (val > 30000 && val <= 42000)) ? 0xFFFF : 0); break;
								case 1: gp.Vals[i] = ((val > 12000 && val < 24000) ? 0xFFFF : 0); break;
								case 2: gp.Vals[i] = ((val > 21000 && val < 33000) ? 0xFFFF : 0); break;
								case 3: gp.Vals[i] = ((val >  3000 && val < 15000) ? 0xFFFF : 0); break;
							}
						}
						else if (o < (GPDIJoyState::AXIS_COUNT*4+GPDIJoyState::POV_COUNT*4+GPDIJoyState::BUTTON_COUNT))
						{
							BYTE pressed = state->joy.buttons[o-(GPDIJoyState::AXIS_COUNT*4+GPDIJoyState::POV_COUNT*4)];
							gp.Vals[i] = (pressed ? 0xFFFF : 0);
						}
						break;
					}
					case GPIDINTERFACE_CAPTURE_NEXT_KEY:
						for (md = mdBegin; md != mdEnd; md++)
						{
							state = &md->state[md->statebit], state_prev = &md->state[!md->statebit];
							switch (GPIDGetInterface(md->intf_devnum))
							{
								case GPIDINTERFACE_KEYBOARD:
									if (!(CaptureSources & (1 << GPIDINTERFACE_KEYBOARD))) continue;
									for (unsigned int o = 0; o != sizeof(state->key.keys); o++)
										if (!state_prev->key.keys[o] && state->key.keys[o])
											{ gp.IDs[i] = GPIDMake(GPIDINTERFACE_KEYBOARD, 0, o); break; }
									break;
								case GPIDINTERFACE_MOUSE:
									if (!(CaptureSources & (1 << GPIDINTERFACE_MOUSE))) continue;
									for (unsigned int j = 0; j != GPDIMouseState::AXIS_COUNT; j++)
									{
										LONG val = state->mouse.axes[j], prev = state_prev->mouse.axes[j];
										unsigned int mode =
											(prev <  0x20 && val >=  0x20 ? 0 :
											(prev > -0x20 && val <= -0x20 ? 1 : 0xFF));
										if (mode == 0xFF) continue;
										gp.IDs[i] = md->intf_devnum + j * 2 + mode;
										break;
									}
									for (unsigned int j = 0; j != GPDIMouseState::BUTTON_COUNT; j++)
									{
										if (!state->mouse.buttons[j]) { state_prev->mouse.held[j] = 0; state->mouse.held[j] = 0; }
										else if (state->mouse.held[j]++ == 5) { state_prev->mouse.held[j] = 0; state->mouse.held[j] = 0; gp.IDs[i] = md->intf_devnum + j + (GPDIMouseState::AXIS_COUNT*2); break; }
									}
									break;
								case GPIDINTERFACE_DINPUT:
									if (!(CaptureSources & (1 << GPIDINTERFACE_DINPUT))) continue;
									for (unsigned int j = 0; j != GPDIJoyState::AXIS_COUNT; j++)
									{
										DWORD val = state->joy.axes[j], prev = state_prev->joy.axes[j];
										unsigned int mode =
											(prev < 0xC000 && val >= 0xC000 ? 0 :
											(prev > 0x4000 && val <= 0x4000 ? 1 : 0xFF));
										if (mode == 0xFF) continue;
										gp.IDs[i] = md->intf_devnum + j * 4 + mode;
										break;
									}
									for (unsigned int j = 0; j != GPDIJoyState::POV_COUNT; j++)
									{
										if (state_prev->joy.pov[j] <= 39000) continue;
										DWORD val = state->joy.pov[j];
										unsigned int mode =
											((val < 3000 || (val > 33000 && val <= 39000)) ? 0 :
											((val > 15000 && val < 21000) ? 1 :
											((val > 24000 && val < 30000) ? 2 :
											((val >  6000 && val < 12000) ? 3 : 0xFF))));
										if (mode == 0xFF) continue;
										gp.IDs[i] = md->intf_devnum + j * 4 + mode + (GPDIJoyState::AXIS_COUNT*4);
										break;
									}
									for (unsigned int j = 0; j != GPDIJoyState::BUTTON_COUNT; j++)
									{
										if (state_prev->joy.buttons[j] || !state->joy.buttons[j]) continue;
										gp.IDs[i] = md->intf_devnum + j + (GPDIJoyState::AXIS_COUNT*4+GPDIJoyState::POV_COUNT*4);
										break;
									}
									break;
							}
						}
						break;
				}
			}
		}

		static LRESULT CALLBACK DetectWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			if (message == WM_DEVICECHANGE && (wParam == DBT_DEVICEARRIVAL || wParam == DBT_DEVICEREMOVECOMPLETE))
				deviceUpdateNeeded = true;
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
	};

	WNDCLASSEXA wndclass;
	memset(&wndclass, 0, sizeof(wndclass));
	wndclass.cbSize = sizeof(wndclass);
	wndclass.hInstance = GetModuleHandleA(NULL);
	wndclass.lpszClassName = "Message";
	wndclass.lpfnWndProc = GPDICallbacks::DetectWndProc;

	DEV_BROADCAST_DEVICEINTERFACE_A dbh;
	memset(&dbh, 0, sizeof(dbh));
	dbh.dbcc_size = sizeof(dbh);
	dbh.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	dbh.dbcc_classguid = GPDI_GUID_DevIntfHID;

	if (!RegisterClassExA(&wndclass) ||
		!(deviceNotificationHwnd = CreateWindowExA(0, wndclass.lpszClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL)) ||
		!RegisterDeviceNotificationA(deviceNotificationHwnd, &dbh, DEVICE_NOTIFY_WINDOW_HANDLE))
		WriteLog("Failed to create device notification window (%u, %u)\n", deviceNotificationHwnd, GetLastError());

	EnterDirectInputCall();
	dii->EnumDevices(GPDI8DEVCLASS_ALL, GPDICallbacks::Enum, dii, GPDIEDFL_ATTACHEDONLY);
	LeaveDirectInputCall();
	XDIGetDevName = GPDICallbacks::GetDevName;
	InputUpdaters.push_back(GPDICallbacks::Update);
}

}; // namespace GPDInput
