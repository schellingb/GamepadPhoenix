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

#define WIN32_LEAN_AND_MEAN
#include "minhook.inl"
#include <windows.h>
#include <stdarg.h>
#include <math.h>
#include <type_traits>

#ifdef NDEBUG
#define GPASSERT(cond)
#define GPCHECKNORECURSION()
#else
#define GPASSERT(cond) (void)((cond) ? ((int)0) : (WriteLog("FAILED ASSERT (%s)\n", #cond),DebugBreak(),((int)0)))
#define GPCHECKNORECURSION() static volatile unsigned int _RECCHECKN; GPASSERT(!_RECCHECKN); struct _SRECCHECK { _SRECCHECK() { GPInterlockedAdd(&_RECCHECKN, 1); } ~_SRECCHECK() { GPInterlockedAdd(&_RECCHECKN, -1); } } _RECCHECK
#endif
#define _GPSTATIC_ASSERTM(A,B) static_assertion_##A##_##B
#define _GPSTATIC_ASSERTN(A,B) _GPSTATIC_ASSERTM(A,B)
#define GPSTATIC_ASSERT(cond) typedef char _GPSTATIC_ASSERTN(__LINE__,__COUNTER__)[(cond)?1:-1]
static bool DEBUGBROKE;
#define DEBUGBREAKONCE do { if (!DEBUGBROKE) { DebugBreak(); DEBUGBROKE = true; } } while(0);
#define WAITFORDEBUGGER if(g_hHeap&&!IsDebuggerPresent()){WriteLog("WAITING FOR DEBUGGER TO CONNECT TO PID %u...\n", GetCurrentProcessId());while(!IsDebuggerPresent())Sleep(10);}

#ifdef _MSC_VER
#define GPINLINE __forceinline
#else
#define GPINLINE inline __attribute__((always_inline))
#endif

enum GPOption : unsigned short
{
	OPTION_None                 = 0,
	OPTION_DPadToLStick         = 0x1,
	OPTION_SwapAandB            = 0x2,
	OPTION_SwapL1R1andL2R2      = 0x4,
	OPTION_DI_TriggersToButtons = 0x10,
	OPTION_DI_POVtoButtons      = 0x20,
	OPTION_IndirectLoading      = 0x100,
	OPTION_Disable_XInput       = 0x200,
	OPTION_Disable_DirectInput  = 0x400,
	OPTION_Disable_MMSys        = 0x800,
	OPTION_FullscreenWindow     = 0x4000,
};

enum GPIndices : unsigned char
{
	GPIDX_LSTICK_U, GPIDX_LSTICK_D, GPIDX_LSTICK_L, GPIDX_LSTICK_R,
	GPIDX_RSTICK_U, GPIDX_RSTICK_D, GPIDX_RSTICK_L, GPIDX_RSTICK_R,
	GPIDX_TRIGGER_L, GPIDX_TRIGGER_R,
	GPIDX_DPAD_U, GPIDX_DPAD_D, GPIDX_DPAD_L, GPIDX_DPAD_R,
	GPIDX_BTN_A, GPIDX_BTN_B, GPIDX_BTN_X, GPIDX_BTN_Y, GPIDX_BTN_L, GPIDX_BTN_R,
	GPIDX_BTN_BACK, GPIDX_BTN_START, GPIDX_BTN_LSTICK, GPIDX_BTN_RSTICK,
	_GPIDX_MAX, _GPIDX_MAXCAL = GPIDX_RSTICK_R + 1,
};

enum GPCal : unsigned char
{
	GPCAL_LDEADZONE, GPCAL_LLIMIT, GPCAL_LANTI, GPCAL_LSENS, GPCAL_LSHIFTH, GPCAL_LSHIFTV,
	GPCAL_RDEADZONE, GPCAL_RLIMIT, GPCAL_RANTI, GPCAL_RSENS, GPCAL_RSHIFTH, GPCAL_RSHIFTV, _GPCAL_MAX
};

struct GPGamepad
{
	bool Used;
	unsigned int IDs[_GPIDX_MAX];
	unsigned short Vals[_GPIDX_MAX];
	signed char Cals[_GPCAL_MAX];
	int CalFix[_GPIDX_MAXCAL], CalAnti[_GPIDX_MAXCAL], CalInRange[_GPIDX_MAXCAL], CalOutRange[_GPIDX_MAXCAL];
	float CalSens[_GPIDX_MAXCAL];
	void CalcCals()
	{
		for (int idx = 0; idx != _GPIDX_MAXCAL; idx++)
		{
			int ofs = (idx < GPIDX_RSTICK_U ? 0 : (GPCAL_RDEADZONE-GPCAL_LDEADZONE));
			int dz = Cals[GPCAL_LDEADZONE+ofs]*0xFFFF/100, limit = Cals[GPCAL_LLIMIT+ofs]*0xFFFF/100, csens = Cals[GPCAL_LSENS+ofs];
			int shift = Cals[GPCAL_LSHIFTV+ofs]*((idx&2) ? 0 : (idx&1) ? 1 : -1) + Cals[GPCAL_LSHIFTH+ofs]*((idx&2) ? (idx&1) ? 1 : -1 : 0);
			CalFix[idx] = (shift*0xFFFF/100) - dz;
			CalAnti[idx] = Cals[GPCAL_LANTI+ofs]*0xFFFF/100;
			CalSens[idx] = (csens > 0 ? (1.0f + (csens * 0.04f)) : (csens < 0 ? (1.0f + (csens * 0.006f)) : 0.0f));
			CalInRange[idx] = (0xFFFF - dz - limit);
			CalOutRange[idx] = (0xFFFF - CalAnti[idx]);
			if (CalInRange[idx] <= 0) CalInRange[idx] = 1;
			if (CalOutRange[idx] <= 0) CalOutRange[idx] = 1;
		}
	}
	unsigned short Axis(int idx, bool mergeDPad = false) const
	{
		int fix = CalFix[idx], v = Vals[idx] + fix;
		if (fix > 0) v -= Vals[idx + ((idx&1)!=0 ? -1 : 1)];
		unsigned int w;
		if (v <= 0) w = 0;
		else if (v >= CalInRange[idx]) w = 0xFFFF;
		else
		{
			w = (unsigned int)v * CalOutRange[idx] / CalInRange[idx];
			if (CalSens[idx]) w = (int)(powf((float)w / CalOutRange[idx], CalSens[idx]) * CalOutRange[idx]);
			w += CalAnti[idx];
		}
		if (!mergeDPad) return (unsigned short)w;
		else { w += Vals[(idx%4)+GPIDX_DPAD_U]; return (w > 0xFFFF ? (unsigned short)0xFFFF : (unsigned short)w); }
	}
};

struct GPData
{
	#define HOOK_SHARED_DATA_NAME "GamepadPhoenix"
	enum { NUM_GAMEPADS = 4, MAX_EXCLUDES = 256, SIZE_LOGBUF = 60*1024 };
	GPGamepad Gamepads[NUM_GAMEPADS];
	unsigned int InjectExcludes[MAX_EXCLUDES];
	unsigned int ExcludeCount;
	GPOption Options;
	volatile bool IsInject, FromGUI;
	volatile unsigned char Recursion;
	volatile unsigned int LogLock;
	unsigned int LogLength;
	char LogData[SIZE_LOGBUF];
};

enum GPIDInterface
{
	GPIDINTERFACE_NONE,
	GPIDINTERFACE_KEYBOARD,
	GPIDINTERFACE_DINPUT,
	GPIDINTERFACE_XINPUT,
	GPIDINTERFACE_WII,
	GPIDINTERFACE_CAPTURE_NEXT_KEY,
	GPID_CAPTURE_NEXT_KEY = GPIDINTERFACE_CAPTURE_NEXT_KEY << 29,
	GPID_SHIFT_INTF = 29,
	GPID_SHIFT_DEVNUM = 8,
	GPID_INTF_DEVNUM_MASK = ~(unsigned int)((1<<GPID_SHIFT_DEVNUM)-1),
	GPID_BITS_DEV = (GPID_SHIFT_INTF - GPID_SHIFT_DEVNUM),
};

GPINLINE unsigned int GPIDMake(GPIDInterface intf_num, unsigned int dev_num, unsigned char obj_num = 0)
{
	return (((unsigned int)intf_num) << GPID_SHIFT_INTF) | (dev_num << GPID_SHIFT_DEVNUM) | (obj_num);
}

GPINLINE GPIDInterface GPIDGetInterface(unsigned int id)
{
	return (GPIDInterface)(id >> GPID_SHIFT_INTF);
}

GPINLINE unsigned int GPIDGetDevNum(unsigned int id)
{
	return (id >> GPID_SHIFT_DEVNUM) & ((1 << GPID_BITS_DEV)-1);
}

GPINLINE unsigned char GPIDGetObjNum(unsigned int id)
{
	return (unsigned char)id;
}

template<class T> struct GPVector
{
	GPINLINE GPVector() : _begin(NULL), _end(NULL), _res(NULL) { GPSTATIC_ASSERT(std::is_trivially_copyable<T>::value); }
	GPINLINE ~GPVector() { free(_begin); }
	GPINLINE T& operator[] (size_t i) { GPASSERT(i >= 0 && i < (size_t)(_end-_begin)); return _begin[i]; }
	GPINLINE T* begin() { return _begin; }
	GPINLINE T* end() { return _end; }
	GPINLINE bool empty() { return (_begin==_end); }
	GPINLINE size_t size() { return (size_t)(_end-_begin); }
	GPINLINE T& back() { return *(end()-1); }
	GPINLINE void reserve(size_t n) { size_t sz = (size_t)(_end-_begin); _begin = (T*)realloc(_begin, n*sizeof(T)); _end = _begin+sz, _res = _begin+n; }
	GPINLINE void push_back(const T& a) { if (_end == _res) reserve(empty() ? 4 : (size_t)(_end-_begin)*2); *(_end++) = a; }
	GPINLINE void clear() { _end = _begin; }
	GPINLINE void resize(size_t n) { if (_begin + n > _res) reserve(n); _end = _begin + n; }
	GPINLINE void erase(T* it) { GPASSERT(it >= _begin && it < _end); memmove(it, it + 1, (--_end - it) * sizeof(T)); }
	GPINLINE void insert(T* it, const T& a) { GPASSERT(it >= _begin && it <= _end); memmove(it + 1, it, (_end++ - it) * sizeof(T)); *it = a; }
	bool Contains(const T& a) { for (const T& it : *this) if (it == a) return true; return false; }
	T *_begin, *_end, *_res;
};

static GPData* pGPData;
static wchar_t MyDLLPath[MAX_PATH*2];
static char MyEXEName[32];
static unsigned int CaptureSources;
static volatile unsigned int InputLock;
static volatile unsigned int KnownLibrariesLock;
static volatile unsigned int FirstThreadLock;
static GPVector<unsigned int> KnownLibraries;
static GPVector<void (*)(GPGamepad&)> InputUpdaters;
static bool GameUsesXInput;
static bool ForceVirtualDevices;
static const wchar_t* (*XDIGetDevName)(unsigned int devNum);
static void (WINAPI *HookPluginHook)(void (*pWriteLog)(const char *,...));
static HMODULE (WINAPI *fpLoadLibraryW)(LPCWSTR lpLibFileName) = &LoadLibraryW;
static FARPROC (WINAPI *fpGetProcAddress)(HMODULE hModule, LPCSTR lpProcName) = &GetProcAddress;
static BOOL (WINAPI *fpCreateProcessW)(LPCWSTR, LPWSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCWSTR, LPSTARTUPINFOW, LPPROCESS_INFORMATION) = &CreateProcessW;
static int (__cdecl *fpVSNPrintF)(char *buffer, size_t count, const char *format, va_list argptr);
static int SNPrintF(char *buffer, size_t count, const char *format, ...) { va_list ap; va_start(ap, format); int res = fpVSNPrintF(buffer, count, format, ap); va_end(ap); return res; }

static void RunInputUpdaters(GPGamepad& gp);
static void GPInterlockedAdd(volatile unsigned int* p, int add) { for (;;)  { unsigned int i = *p; if (InterlockedCompareExchange(p, (i+add), i) == i) return; } }
static bool GPLock(volatile unsigned int* p, DWORD timeout = 0) { for (DWORD i = 0, t = (timeout<<24); InterlockedCompareExchange(p, 1, 0); i++) { if (i>=t) return false; Sleep(0); } return true; }
static int LogIndent(int modify = 0);

static void VWriteLog(const char* fmt, va_list ap)
{
	static char buf[2048];
	static bool skipExeName;

	char* pBuf = buf;
	if (!skipExeName)
	{
		*pBuf++ = '[';
		strcpy(pBuf, MyEXEName);
		pBuf += strlen(pBuf);
		*pBuf++ = ']';
		*pBuf++ = ' ';
		#if 0 // detailed logging
		pBuf += SNPrintF(pBuf, sizeof(buf)-(pBuf-buf)-1, "[%u>%u] %*s", GetCurrentProcessId(), GetCurrentThreadId(), LogIndent(), "");
		#endif
	}

	int count = fpVSNPrintF(pBuf, sizeof(buf)-(pBuf-buf)-1, fmt, ap);
	if (!count) return;

	unsigned int writeLen = (unsigned int)(count < 0 ? sizeof(buf) : (int)(pBuf - buf) + count);
	if (!GPLock(&pGPData->LogLock, 1)) return;
	if (&pGPData->LogData[pGPData->LogLength + writeLen] < &pGPData->LogData[sizeof(pGPData->LogData)])
	{
		memcpy(pGPData->LogData + pGPData->LogLength, buf, writeLen);
		pGPData->LogLength += writeLen;
	}
	pGPData->LogLock = 0;
	skipExeName = (buf[writeLen-1] != '\n');
}

static void WriteLog(const char* format,...) { va_list ap; va_start(ap, format); VWriteLog(format, ap); va_end(ap); }

#if 0 // detailed logging
static void CreateMiniDump()
{
	struct LCL { static DWORD WINAPI THREAD(void*)
	{
		enum MINIDUMP_TYPE
		{
			MiniDumpNormal = 0x0, MiniDumpWithDataSegs = 0x1, MiniDumpWithFullMemory = 0x2, MiniDumpWithHandleData = 0x4, MiniDumpFilterMemory = 0x8, MiniDumpScanMemory = 0x10, MiniDumpWithUnloadedModules = 0x20,
			MiniDumpWithIndirectlyReferencedMemory = 0x40, MiniDumpFilterModulePaths = 0x80, MiniDumpWithProcessThreadData = 0x100, MiniDumpWithPrivateReadWriteMemory = 0x200, MiniDumpWithoutOptionalData = 0x400,
			MiniDumpWithFullMemoryInfo = 0x800, MiniDumpWithThreadInfo = 0x1000, MiniDumpWithCodeSegs = 0x2000,MiniDumpWithoutAuxiliaryState = 0x4000, MiniDumpWithFullAuxiliaryState = 0x8000, MiniDumpValidTypeFlags = 0xffff,
		};
		typedef BOOL (WINAPI *PFN_MiniDumpWriteDump)(HANDLE hProcess, DWORD ProcessId, HANDLE hFile, MINIDUMP_TYPE DumpType, CONST PVOID ExceptionParam, CONST PVOID UserStreamParam, CONST PVOID CallbackParam);

		FROZEN_THREADS threads;
		Freeze(&threads, ALL_HOOKS_POS, ACTION_ENABLE);

		WriteLog("[CreateMiniDump] Load dbghelp...\n");
		HMODULE g_hModuleDbgHelp = ::LoadLibraryA( "dbghelp.dll" );
		WriteLog("[CreateMiniDump] Getproc MiniDumpWriteDump...\n");
		PFN_MiniDumpWriteDump g_pfn_MiniDumpWriteDump = (PFN_MiniDumpWriteDump)fpGetProcAddress(g_hModuleDbgHelp, "MiniDumpWriteDump" );
		WriteLog("[CreateMiniDump] Create gpminidump.dmp...\n");
		HANDLE	hFile = CreateFileA("gpminidump.dmp", GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteLog("[CreateMiniDump] Call MiniDumpWriteDump...\n");
		BOOL res = g_pfn_MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpWithThreadInfo, NULL, NULL, NULL);
		WriteLog("[CreateMiniDump] Close file...\n");
		CloseHandle( hFile );
		WriteLog("[CreateMiniDump] Result: %d\n", res);

		Unfreeze(&threads);

		return 0;
	}};
	CloseHandle(CreateThread(0, 0, (DWORD (WINAPI *)(LPVOID))LCL::THREAD, NULL, 0, 0));

	WriteLog("[CreateMiniDump] Waiting for dumpthread...\n");
	Sleep(10000);
	WriteLog("[CreateMiniDump] DONE!\n");
}

static int LogIndent(int modify)
{
	struct LogThread { DWORD ThreadId; int Indent; };
	static GPVector<LogThread> LogThreads;
	DWORD tid = GetCurrentThreadId();
	for (LogThread& lt : LogThreads) { if (lt.ThreadId == tid) { return (lt.Indent += modify); } }
	LogThreads.push_back({tid, modify});
	return modify;
}

struct LogScopeIndenter
{
	LogScopeIndenter(const char* fn, const char* fmt = NULL, ...) : Fn(fn)
	{
		WriteLog("[%s]%c", fn, (fmt?' ':'\n'));// [START]
		if (fmt) { va_list ap; va_start(ap, fmt); VWriteLog(fmt, ap); va_end(ap); WriteLog("\n"); }
		LogIndent(4);
	}
	~LogScopeIndenter()
	{
		LogIndent(-4);
		//WriteLog("[%s] [END]\n", Fn);
	}
	const char* Fn;
};
#define LOGSCOPE(...) LogScopeIndenter _LOGINDENTBLOCK(__FUNCTION__, ##__VA_ARGS__)
#else
#define LOGSCOPE(...)
#endif

static bool CreateHook(LPVOID pTarget, LPCSTR pszProcName, LPVOID pDetour, bool enableHooks, LPVOID* ppOriginal = NULL)
{
	MH_STATUS res;
	if (!pTarget)
	{
		res = MH_ERROR_FUNCTION_NOT_FOUND;
	}
	else
	{
		//GPASSERT(FindHookEntry(pTarget) == INVALID_HOOK_POS); // avoid hooking same function twice
		res = MH_CreateHook(pTarget, pDetour, ppOriginal);
	}
	if (res != MH_OK && (res != MH_ERROR_FUNCTION_NOT_FOUND || ppOriginal)) // log no error when not explicitly asking for the trampoline function
		WriteLog("[HOOK] Hooking '%s' => %s (Detour: %p - Target: %p - Original: %p)\n", pszProcName, MH_StatusToString(res), pDetour, pTarget, (ppOriginal ? *ppOriginal : 0));
	if (enableHooks)
		MH_EnableHook(MH_ALL_HOOKS);
	return (res == MH_OK);
}

GPINLINE static bool CreateHook(HMODULE hModule, LPCSTR pszProcName, LPVOID pDetour, bool enableHooks, LPVOID* ppOriginal = NULL)
{
	return CreateHook((LPVOID)fpGetProcAddress(hModule, pszProcName), pszProcName, pDetour, enableHooks, ppOriginal);
}

GPINLINE static bool CreateHook(HMODULE hModule, int ordinal, LPCSTR pszProcName, LPVOID pDetour, bool enableHooks, LPVOID* ppOriginal = NULL)
{
	return CreateHook((LPVOID)fpGetProcAddress(hModule, (LPCSTR)(void*)(size_t)ordinal), pszProcName, pDetour, enableHooks, ppOriginal);
}

static bool AlreadyHooked(LPVOID pTarget, LPVOID* ppOriginal = NULL)
{
	UINT pos = FindHookEntry(pTarget);
	if (pos != INVALID_HOOK_POS) { if (ppOriginal) *ppOriginal = g_hooks.pItems[pos].pTrampoline; return true; }
	return false;
}

#define HOOKFUNC_START(RET, NAME, ARGS) static RET (WINAPI *fp##NAME)ARGS; struct s##NAME { static RET WINAPI Func ARGS
#define HOOKFUNC_START_NOFP(RET, NAME, ARGS) struct s##NAME { static RET WINAPI Func ARGS
#define HOOKFUNC_END };
#define HOOKFUNC_END_HOOK(HMODULEorPTARGET, NAME, ACTIVATE) }; CreateHook(HMODULEorPTARGET, #NAME, &s##NAME::Func, ACTIVATE, (LPVOID*)&fp##NAME)
#define HOOKFUNC_END_HOOKONCE(HMODULEorPTARGET, NAME, ACTIVATE) }; if (!fp##NAME) CreateHook(HMODULEorPTARGET, #NAME, &s##NAME::Func, ACTIVATE, (LPVOID*)&fp##NAME)
#define HOOKONCE(HMODULEorPTARGET, NAME, ACTIVATE) if (!fp##NAME) CreateHook(HMODULEorPTARGET, #NAME, &s##NAME::Func, ACTIVATE, (LPVOID*)&fp##NAME)

#define GPLINKER_DLL_EXPORT                   comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)
#define GPLINKER_DLL_EXPORT_HINT(ORD)         comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__ ",@" #ORD)
#define GPLINKER_DLL_EXPORT_UNNAMED(ORD)      comment(linker, "/EXPORT:" __FUNCTION__ #ORD "="  __FUNCDNAME__ ",@" #ORD ",NONAME")
#define GPLINKER_DLL_EXPORT_AS(NAME)          comment(linker, "/EXPORT:" #NAME "="  __FUNCDNAME__)
#define GPLINKER_DLL_EXPORT_AS_HINT(NAME,ORD) comment(linker, "/EXPORT:" #NAME "="  __FUNCDNAME__ ",@" #ORD)
#define GPLINKER_DLL_EXPORT_AS_PRIVATE(NAME)  comment(linker, "/EXPORT:" #NAME "="  __FUNCDNAME__ ",PRIVATE")

#include "GPXInput.inl"
#include "GPDInput.inl"
#include "GPWinMM.inl"

static void InputSetup()
{
	LOGSCOPE("IsUILoadAllInterfaces: %d", !g_hHeap);
	bool useX = !g_hHeap, useD = useX; // UI always needs all interfaces
	if (!useX)
		for (GPGamepad& gp : pGPData->Gamepads)
			for (unsigned int i = 0; i != _GPIDX_MAX; i++)
				switch (GPIDGetInterface(gp.IDs[i]))
				{
					case GPIDINTERFACE_XINPUT:   useX = true; break;
					case GPIDINTERFACE_DINPUT:   useD = true; break;
					case GPIDINTERFACE_KEYBOARD: useD = true; break;
				}
	if (useX) GPXInput::SetupInput();
	if (useD) GPDInput::SetupInput();
}

static void RunInputUpdaters(GPGamepad& gp)
{
	//LOGSCOPE("GP: %d - InputLock: %d", (&gp - pGPData->Gamepads), InputLock);
	if (InputLock) return;
	GPLock(&InputLock, 3);
	for (void (*fn)(GPGamepad&) : InputUpdaters) fn(gp);
	InputLock = 0;
}

static void RefreshHooks()
{
	LOGSCOPE("InputLock: %d", InputLock);
	if (InputLock) return;
	GPLock(&InputLock, 3);
	GPXInput::Hook();
	GPDInput::Hook();
	GPWinMM::Hook();
	if (HookPluginHook) HookPluginHook(&WriteLog);
	InputLock = 0;
}

struct GPInject
{
	template <typename TRET> struct LambdaRef
	{
		template <typename TLambda> GPINLINE LambdaRef(TLambda&& lambda) : lm((void*)&lambda), fn((TRET(LambdaRef<TRET>::*)()const)static_cast<TRET(TLambda::*)()const>(&TLambda::operator())) {}
		GPINLINE TRET operator() () { return (((LambdaRef<TRET>*)lm)->*fn)(); }
		private: void *lm; TRET(LambdaRef<TRET>::*fn)()const; LambdaRef<TRET>& operator=(const LambdaRef<TRET>&) const;
	};

	template <typename TCHAR> static bool MatchNoCase(const TCHAR* str, const char* find)
	{
		for (; *str && *find; str++, find++) if (((*str>'Z'||*str<'A')?*str:*str|0x20)!=*find) return false;
		return true;
	}

	template <typename TCHAR> static bool IsXInput(const TCHAR* path)
	{
		const TCHAR* dir = path;
		for (const TCHAR* p = path; *p; p++) if (*p == '\\' || *p == '/') dir = p + 1;
		return ((dir[0]|0x20)=='x' && MatchNoCase(dir+1, "input") && dir[6]>='1' && dir[6]<='9');
	}

	static HMODULE MyLoadLibrary(const void* path, LambdaRef<HMODULE>&& LoadLibraryLambda, bool isW)
	{
		unsigned int hash = HashPath(path, isW);

		// Disallow loading of hid.dll unless for us while calling DirectInput.
		// This disallows games to access hardware directly and forces them to use the APIs we intercept (SDL2 does this)
		if (hash == 0x9415504E && !GPDInput::InDirectInputCall) return NULL;

		// Some games keep hammering LoadLibrary calls, so remember a list of previously loaded libraries
		GPLock(&KnownLibrariesLock, 2);
		bool known = KnownLibraries.Contains(hash);
		if (!known) KnownLibraries.push_back(hash);
		KnownLibrariesLock = 0;
		if (known) return LoadLibraryLambda();

		LOGSCOPE((isW ? "DLL: %S - GameUsesXInput: %d - IsXInput: %d" : "DLL: %s - GameUsesXInput: %d - IsXInput: %d"), path, GameUsesXInput, (isW ? IsXInput((const wchar_t*)path) : IsXInput((const char*)path)));
		if (!InputLock && !GameUsesXInput && (isW ? IsXInput((const wchar_t*)path) : IsXInput((const char*)path))) GameUsesXInput = true;

		HMODULE res = LoadLibraryLambda();
		RefreshHooks();
		return res;
	}

	static bool IntoOpenedProcess(HANDLE hProcess)
	{
		size_t DllPathLen = (wcslen(MyDLLPath) + 1) * sizeof(MyDLLPath[0]);
		void* lpBaseAddress = VirtualAllocEx(hProcess, NULL, DllPathLen, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		bool success = false;
		if (lpBaseAddress == NULL)
			WriteLog("[INJECT] Failed to allocate memory in target process\n");
		else if (!WriteProcessMemory(hProcess, lpBaseAddress, MyDLLPath, DllPathLen, NULL))
			WriteLog("[INJECT] Failed to write memory in target process\n");
		else
		{
			pGPData->IsInject = true;
			FARPROC procLoadLibraryW = fpGetProcAddress(GetModuleHandleA("kernel32"), "LoadLibraryW");
			HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)procLoadLibraryW, lpBaseAddress, 0, NULL);
			if (hRemoteThread != INVALID_HANDLE_VALUE)
			{
				DWORD retVal = 0;
				WaitForSingleObject(hRemoteThread, 5000);
				GetExitCodeThread(hRemoteThread, &retVal);
				CloseHandle(hRemoteThread);
				success = (retVal != 0);
			}
			pGPData->IsInject = false;
		}
		if (lpBaseAddress) VirtualFreeEx(hProcess, lpBaseAddress, 0, MEM_RELEASE);
		return success;
	}

	static bool IntoNonNativeProcess(DWORD pid)
	{
		wchar_t buf[MAX_PATH*2+1];
		buf[0] = '"';

		// avoid DLL import of shell32.dll just for this one function
		HMODULE hmShell32 = LoadLibraryA("SHELL32");
		enum { ZCSIDL_WINDOWS = 0x0024, ZCSIDL_SYSTEMX86 = 0x0029 };
		typedef BOOL (WINAPI *SHGetSpecialFolderPathWFN)(HWND hwnd, LPWSTR pszPath, int csidl, BOOL fCreate);
		SHGetSpecialFolderPathWFN pSHGetSpecialFolderPathW = (SHGetSpecialFolderPathWFN)fpGetProcAddress(hmShell32, "SHGetSpecialFolderPathW");
		if (sizeof(void*) == 8) pSHGetSpecialFolderPathW(NULL, buf+1, ZCSIDL_SYSTEMX86, FALSE);
		else { pSHGetSpecialFolderPathW(NULL, buf+1, ZCSIDL_WINDOWS, FALSE); wcscat(buf, L"\\Sysnative"); }
		FreeLibrary(hmShell32);

		wcscat(buf, L"\\rundll32.exe\" \"");
		wcscat(buf, MyDLLPath);

		wchar_t *pPostDLL = buf + wcslen(buf), *pDLLBits = pPostDLL - 6;
		if (pDLLBits[0] != '3' && pDLLBits[0] != '6')
		{
			WriteLog("[INJECT] Unable to inject DLL '%S' into process of different platform (must end with '32.dll' or '64.dll')\n", MyDLLPath);
			return false;
		}
		if (sizeof(void*) == 8) { pDLLBits[0] = '3'; pDLLBits[1] = '2'; }
		else                    { pDLLBits[0] = '6'; pDLLBits[1] = '4'; }

		wcscpy(pPostDLL, L"\",RunInject ");
		wchar_t* bufPid = pPostDLL + wcslen(pPostDLL);
		for (DWORD n = 1000000000; n; n /= 10) if (pid >= n) *bufPid++ = '0' + ((pid / n) % 10);
		*bufPid = '\0';

		STARTUPINFOW si;
		memset(&si, 0, sizeof(si));
		si.cb = sizeof(STARTUPINFOW);
		PROCESS_INFORMATION pi;
		fpCreateProcessW(NULL, buf, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		return true;
	}

	static unsigned int HashPath(const void* path, bool isW)
	{
		unsigned int hash = (unsigned int)0x811c9dc5;
		if (isW) { for (const wchar_t* p = (const wchar_t*)path; *p; p++) hash = ((hash * (unsigned int)0x01000193) ^ (unsigned int)(*p >= 'a' && *p <= 'z' ? *p - ('a'-'A') : *p)); }
		else     { for (const  char  * p = (const  char  *)path; *p; p++) hash = ((hash * (unsigned int)0x01000193) ^ (unsigned int)(*p >= 'a' && *p <= 'z' ? *p - ('a'-'A') : *p)); }
		return hash;
	}

	template<typename TCHAR> static unsigned int HashExe(const TCHAR* from, const TCHAR* to)
	{
		unsigned int hash = (unsigned int)0x811c9dc5;
		for (; from != to; from++) hash = ((hash * (unsigned int)0x01000193) ^ (unsigned int)(*from >= 'a' && *from <= 'z' ? *from - ('a'-'A') : *from));
		return hash;
	}

	template<typename TCHAR> static unsigned int GetProcessHashExe(const TCHAR* applicationName, const TCHAR* commandLine)
	{
		const TCHAR *path = (applicationName ? applicationName : commandLine + (commandLine[0] == '"' ? 1 : 0));
		const TCHAR *pend = path, endChar = (applicationName ? '\0' : (commandLine[0] == '"' ? '"' : ' '));
		for (; *pend && *pend != endChar; pend++) {}
		const TCHAR *base = pend;
		for (; base != path && base[-1] != '/' && base[-1] != '\\'; base--) {}
		return HashExe(base, pend);
	}

	static unsigned int GetParam(const void* commandLine, const char* param, size_t paramLen, bool isW)
	{
		unsigned int id = 0;
		if (isW)
		{
			for (const wchar_t* p = (const wchar_t*)commandLine, first = *param; *p; p++)
				if (p[0] == first && MatchNoCase(p+1, param+1)) { for (p += paramLen; *p >= '0' && *p <= '9'; p++) id = (id*10) + (*p-'0'); if (id) break; }
		}
		else
		{
			for (const char* p = (const char*)commandLine, first = *param; *p; p++)
				if (p[0] == first && MatchNoCase(p+1, param+1)) { for (p += paramLen; *p >= '0' && *p <= '9'; p++) id = (id*10) + (*p-'0'); if (id) break; }
		}
		return id;
	}

	static BOOL RedirectStoreApp(unsigned int exeHash, const void* commandLine, LPPROCESS_INFORMATION lpProcessInformation, bool isW)
	{
		enum { STEAM_EXE_HASH = 0x6D05BC49, UBILAUNCH_EXE_HASH = 464146393 };

		unsigned int appid;
		wchar_t* envPrefix;
		switch (exeHash)
		{
			case STEAM_EXE_HASH:
				appid = GetParam(commandLine, "-applaunch ", sizeof("-applaunch ")-1, isW);
				if (!appid) appid = GetParam(commandLine, " steam://run/", sizeof(" steam://run/")-1, isW);
				if (!appid) return false;
				envPrefix = L"SteamAppId=";
				break;
			case UBILAUNCH_EXE_HASH:
				appid = GetParam(commandLine, "-upc_uplay_id ", sizeof("-upc_uplay_id ")-1, isW);
				if (!appid) return false;
				envPrefix = L"UPLAY_ARGUMENTS=-upc_uplay_id ";
				break;
			default: return false;
		}

		// Stop if this is getting called again and again by the redirected child processes
		if (pGPData->Recursion++ > 5) return FALSE;

		const wchar_t* env = GetEnvironmentStringsW(), *envEnd;
		for (envEnd = env + 1; envEnd[0]||envEnd[-1]; envEnd++) {}
		wchar_t* newenv = (wchar_t*)malloc((envEnd - env + 128) * sizeof(wchar_t));
		memcpy(newenv, env, (envEnd - env) * sizeof(wchar_t));
		wchar_t* p = wcscpy(newenv + (envEnd - env), envPrefix) + wcslen(envPrefix);
		for (unsigned int n = 1000000000; n; n /= 10) if (appid >= n) *p++ = '0'+((appid/n)%10);
		*p++ = '\0';
		p = wcscpy(p, L"GPPRNTPID=") + (sizeof("GPPRNTPID=")-1);
		for (unsigned int pid = GetCurrentProcessId(), n = 1000000000; n; n /= 10) if (pid >= n) *p++ = '0'+((pid/n)%10);
		p[0] = p[1] = '\0'; //terminate line and env block

		STARTUPINFOW si;
		memset(&si, 0, sizeof(si));
		si.cb = sizeof(STARTUPINFOW);
		BOOL res = fpCreateProcessW(NULL, GetCommandLineW(), NULL, NULL, false, (CREATE_SUSPENDED | CREATE_DEFAULT_ERROR_MODE | DETACHED_PROCESS | CREATE_UNICODE_ENVIRONMENT), newenv, NULL, &si, lpProcessInformation);
		free(newenv);
		return !!res;
	}

	static BOOL MyCreateProcess(const void* applicationName, const void* commandLine, DWORD& dwCreationFlags, LPPROCESS_INFORMATION lpProcessInformation, LambdaRef<BOOL>&& CreateProcessLambda, bool isW)
	{
		unsigned int exeHash = (isW ? GetProcessHashExe((const wchar_t*)applicationName, (const wchar_t*)commandLine) : GetProcessHashExe((const char*)applicationName, (const char*)commandLine));
		bool inject = pGPData->FromGUI, doResume = !(dwCreationFlags & CREATE_SUSPENDED);
		BOOL res = (inject && RedirectStoreApp(exeHash, commandLine, lpProcessInformation, isW));
		if (!res)
		{
			for (unsigned int *e = pGPData->InjectExcludes, *eEnd = e + pGPData->ExcludeCount; e != eEnd; e++) { if (*e == exeHash) { inject = false; break; } }
			if (inject) dwCreationFlags |= CREATE_SUSPENDED;
		}
		if (pGPData->FromGUI)
		{
			WriteLog(res ? "[INJECT] Intercepting store app launch" : inject ? "[INJECT] Creating sub process" : "[INJECT] Skipping injection into new sub process due to exclude list");
			WriteLog((isW ? " '%S' '%S' [%u]\n" : " '%s' '%s'\n"), applicationName, commandLine);
		}
		if (!res) res = CreateProcessLambda();
		if (!inject) return res;
		(IntoOpenedProcess(lpProcessInformation->hProcess) || IntoNonNativeProcess(lpProcessInformation->dwProcessId));
		if (doResume) ResumeThread(lpProcessInformation->hThread);
		return res;
	}
};

static void HookKernel()
{
	HMODULE hmKernel = GetModuleHandleA("KernelBase");
	if (!hmKernel || !fpGetProcAddress(hmKernel, "LoadLibraryA")) hmKernel = GetModuleHandleA("kernel32");
	fpGetProcAddress = (FARPROC(WINAPI*)(HMODULE,LPCSTR))fpGetProcAddress(hmKernel, "GetProcAddress");

	HOOKFUNC_START(HMODULE, LoadLibraryA, (LPCSTR lpLibFileName)) { return GPInject::MyLoadLibrary(lpLibFileName, [&](){return fpLoadLibraryA(lpLibFileName);}, false); }
	HOOKFUNC_END_HOOK(hmKernel, LoadLibraryA, false);
	HOOKFUNC_START_NOFP(HMODULE, LoadLibraryW, (LPCWSTR lpLibFileName)) { return GPInject::MyLoadLibrary(lpLibFileName, [&](){return fpLoadLibraryW(lpLibFileName);}, true); }
	HOOKFUNC_END_HOOK(hmKernel, LoadLibraryW, false);
	HOOKFUNC_START(HMODULE, LoadLibraryExA, (LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)) { return GPInject::MyLoadLibrary(lpLibFileName, [&](){return fpLoadLibraryExA(lpLibFileName, hFile, dwFlags);}, false); }
	HOOKFUNC_END_HOOK(hmKernel, LoadLibraryExA, false);
	HOOKFUNC_START(HMODULE, LoadLibraryExW, (LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)) { return GPInject::MyLoadLibrary(lpLibFileName, [&](){return fpLoadLibraryExW(lpLibFileName, hFile, dwFlags);}, true); }
	HOOKFUNC_END_HOOK(hmKernel, LoadLibraryExW, false);

	HOOKFUNC_START(BOOL, CreateProcessA, (LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)) { return GPInject::MyCreateProcess(lpApplicationName, lpCommandLine, dwCreationFlags, lpProcessInformation, [&]() { return fpCreateProcessA(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation); }, false); }
	HOOKFUNC_END_HOOK(hmKernel, CreateProcessA, false);
	HOOKFUNC_START_NOFP(BOOL, CreateProcessW, (LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)) { return GPInject::MyCreateProcess(lpApplicationName, lpCommandLine, dwCreationFlags, lpProcessInformation, [&]() { return fpCreateProcessW(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation); }, true); }
	HOOKFUNC_END_HOOK(hmKernel, CreateProcessW, false);
	if (fpGetProcAddress(hmKernel, "CreateProcessAsUserA"))
	{
		HOOKFUNC_START(BOOL, CreateProcessAsUserA, (HANDLE hToken, LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)) { return GPInject::MyCreateProcess(lpApplicationName, lpCommandLine, dwCreationFlags, lpProcessInformation, [&]() { return fpCreateProcessAsUserA(hToken, lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation); }, false); }
		HOOKFUNC_END_HOOK(hmKernel, CreateProcessAsUserA, false);
		HOOKFUNC_START(BOOL, CreateProcessAsUserW, (HANDLE hToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)) { return GPInject::MyCreateProcess(lpApplicationName, lpCommandLine, dwCreationFlags, lpProcessInformation, [&]() { return fpCreateProcessAsUserW(hToken, lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation); }, true); }
		HOOKFUNC_END_HOOK(hmKernel, CreateProcessAsUserW, true);
	}
}

struct GPFullscreenize
{
	typedef LONG (WINAPI *PFN_SetWindowLongA)(HWND hWnd, int nIndex, LONG dwNewLong);
	typedef BOOL (WINAPI *PFN_SetWindowPos)  (HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);
	typedef LONG (WINAPI *PFN_GetWindowLongA)(HWND hWnd, int nIndex);
	static PFN_SetWindowLongA fpSetWindowLongA;
	static PFN_SetWindowPos   fpSetWindowPos;
	static PFN_GetWindowLongA fpGetWindowLongA;

	static void Prepare()
	{
		HMODULE hUser32 = fpLoadLibraryW(L"User32");
		if (!hUser32) { GPASSERT(0); return; }
		fpSetWindowLongA = (PFN_SetWindowLongA)fpGetProcAddress(hUser32, "SetWindowLongA");
		fpSetWindowPos   = (PFN_SetWindowPos)  fpGetProcAddress(hUser32, "SetWindowPos");
		fpGetWindowLongA = (PFN_GetWindowLongA)fpGetProcAddress(hUser32, "GetWindowLongA");
		GPASSERT(fpSetWindowLongA && fpSetWindowPos && fpGetWindowLongA);
		CloseHandle(CreateThread(0, 0, WindowedFullscreenThread, NULL, 0, 0));
	}

	static DWORD WINAPI WindowedFullscreenThread(LPVOID)
	{
		Sleep(1000); // give application time to prepare (otherwise games like Guacamele might end up with stretched non-native resolution)
		for (DWORD pid = GetCurrentProcessId(), hwndPid;;Sleep(200))
		{
			for (HWND hwnd = NULL; (hwnd = FindWindowEx(NULL, hwnd, NULL, NULL)) != NULL;)
			{
				if (!GetWindowThreadProcessId(hwnd, &hwndPid) || hwndPid != pid) continue;
				LONG style = fpGetWindowLongA(hwnd, GWL_STYLE);
				if (!(style & WS_VISIBLE)) continue;
				HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
				MONITORINFO info = { sizeof(info) };
				GetMonitorInfo(monitor, &info);
				RECT rc, &mr = info.rcMonitor;
				GetWindowRect(hwnd, &rc);
				if (rc.left != mr.left || rc.top != mr.top || rc.right != mr.right || rc.bottom != mr.bottom)
				{
					fpSetWindowLongA(hwnd, GWL_STYLE, style & ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU));
					fpSetWindowPos(hwnd, NULL, mr.left, mr.top, mr.right - mr.left, mr.bottom - mr.top, SWP_FRAMECHANGED);
				}
				return 0;
			}
		}
	}
};

GPFullscreenize::PFN_SetWindowLongA GPFullscreenize::fpSetWindowLongA;
GPFullscreenize::PFN_SetWindowPos   GPFullscreenize::fpSetWindowPos;
GPFullscreenize::PFN_GetWindowLongA GPFullscreenize::fpGetWindowLongA;

BOOL WINAPI DllMain(HINSTANCE const instance, DWORD const reason, LPVOID const reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		HANDLE hSharedFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(GPData), HOOK_SHARED_DATA_NAME);
		if (!hSharedFile || hSharedFile == INVALID_HANDLE_VALUE)
		{
			MessageBoxA(NULL, "Unable to connect to Gamepad Phoenix", "Error", 0);
			return true;
		}
		pGPData = (GPData*)MapViewOfFile(hSharedFile, FILE_MAP_WRITE, 0, 0, 0);
		if (!pGPData)
		{
			CloseHandle(hSharedFile);
			MessageBoxA(NULL, "Unable to connect to Gamepad Phoenix", "Error", 0);
			return true;
		}
		bool isInject = pGPData->IsInject;
		if (isInject) pGPData->IsInject = false; // unset as soon as possible

		// use vsprintf from Windows (save 6kb in output)
		fpVSNPrintF = (int(__cdecl*)(char*,size_t,const char*,va_list))fpGetProcAddress(GetModuleHandleA("ntdll"), "_vsnprintf");
		if (!fpVSNPrintF) fpVSNPrintF = (int(__cdecl*)(char*,size_t,const char*,va_list))fpGetProcAddress(LoadLibraryA("msvcrt"), "_vsnprintf");

		GetModuleFileNameW(NULL, MyDLLPath, (sizeof(MyDLLPath)/sizeof(MyDLLPath[0])-1));
		wchar_t* pEXELastSlash = wcsrchr(MyDLLPath, '\\');
		wchar_t* pEXEBaseName = (pEXELastSlash ? pEXELastSlash + 1 : MyDLLPath);
		WideCharToMultiByte(CP_UTF8, 0, pEXEBaseName, -1, MyEXEName, sizeof(MyEXEName) - 1, NULL, NULL);

		wchar_t* pDLLBits = MyDLLPath + GetModuleFileNameW(instance, MyDLLPath, (sizeof(MyDLLPath)/sizeof(MyDLLPath[0])-1)) - 6;
		bool isIndirectDLL = (pDLLBits[0] != '3' && pDLLBits[0] != '6');

		//WriteLog("[DLL] Attach - MyDLL: %S - IsInject: %d\n", MyDLLPath, pGPData->IsInject);

		if (isInject || isIndirectDLL)
		{
			WriteLog("Loaded Gamepad Phoenix extension into program\n");
			if (isIndirectDLL)
			{
				pGPData->FromGUI = false;
				pGPData->Recursion = 0;
				wchar_t *dllExt = pDLLBits + 3, orgDllExt[3], hookPlugin[MAX_PATH];
				memcpy(orgDllExt, dllExt, sizeof(orgDllExt));
				memcpy(dllExt, L"INI", sizeof(orgDllExt));
				GetPrivateProfileStructW(L"GamepadPhoenix", L"Options", &pGPData->Options, sizeof(pGPData->Options), MyDLLPath);
				GetPrivateProfileStructW(L"GamepadPhoenix", L"ExcludeCount", &pGPData->ExcludeCount, sizeof(pGPData->ExcludeCount), MyDLLPath);
				GetPrivateProfileStructW(L"GamepadPhoenix", L"InjectExcludes", &pGPData->InjectExcludes, sizeof(pGPData->InjectExcludes[0])*pGPData->ExcludeCount, MyDLLPath);
				GetPrivateProfileStringW(L"GamepadPhoenix", L"HookPlugin", NULL, hookPlugin, sizeof(hookPlugin)/sizeof(*hookPlugin), MyDLLPath);
				//WriteLog("[DLL] Indirect - INI: %S - Mode: %d - Options: %d - ExcludeCount: %d\n", MyDLLPath, pGPData->Mode, pGPData->Options, pGPData->ExcludeCount);
				memcpy(dllExt, orgDllExt, sizeof(orgDllExt));
				if (hookPlugin[0])
				{
					HookPluginHook = (void (WINAPI*)(void (*pWriteLog)(const char *,...)))fpGetProcAddress(fpLoadLibraryW(hookPlugin), "GamepadPhoenixHook");
					WriteLog("%s HookPlugin '%S'\n", (HookPluginHook ? "Using" : "Failed to load"), hookPlugin);
				}
			}
			if ((pGPData->Options & (OPTION_Disable_XInput|OPTION_Disable_DirectInput|OPTION_Disable_MMSys)) == (OPTION_Disable_DirectInput|OPTION_Disable_MMSys))
				GameUsesXInput = true;

			MH_Initialize();
			HookKernel();
			RefreshHooks();

			// We acquire all needed input interfaces as early as possible to avoid someone hooking into the API (like Steam does with XInput)
			GPLock(&InputLock, 3);
			InputSetup();
			InputLock = 0;
		}
	}
	if (reason == DLL_THREAD_ATTACH && g_hHeap && GPLock(&FirstThreadLock))
	{
		char strParentPid[16];
		DWORD len = GetEnvironmentVariableA("GPPRNTPID", strParentPid, 16);
		DWORD parentPid = 0;
		for (char* p = strParentPid, *pEnd = p + len; p != pEnd; p++) parentPid = (parentPid * 10) + (*p - '0');
		HANDLE hParent = (parentPid ? OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, FALSE, parentPid) : NULL);
		if (hParent)
		{
			// When launched through an intercepted store app launch command terminate the parent process so a game that refuses to run twice isn't confused
			TerminateProcess(hParent, 0);
			WaitForSingleObject(hParent, 2000);
			CloseHandle(hParent);
		}
		if (pGPData->Options & OPTION_FullscreenWindow)
			GPFullscreenize::Prepare();
	}
	return TRUE;
}

BOOL WINAPI FakeXInputDllMain(HINSTANCE const instance, DWORD const reason, LPVOID const reserved)
{
	#pragma GPLINKER_DLL_EXPORT_AS_HINT(DllMain, 1) // not needed but exported to match the interface of real XInput dlls
	return DllMain(instance, reason, reserved);
}

void WINAPI RunInject(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow)
{
	#pragma GPLINKER_DLL_EXPORT
	DWORD pid = 0;
	for (char* p = lpszCmdLine; *p; p++) pid = (pid * 10) + (*p - '0');
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	GPInject::IntoOpenedProcess(process);
	CloseHandle(process);
}

void WINAPI UISetPad(int idx, unsigned int* ids, signed char* cals)
{
	#pragma GPLINKER_DLL_EXPORT
	GPGamepad& gp = pGPData->Gamepads[idx];
	if (memcmp(gp.IDs, ids, sizeof(gp.IDs)))
	{
		memcpy(gp.IDs, ids, sizeof(gp.IDs));
		memset(gp.Vals, 0, sizeof(gp.Vals));
	}
	memcpy(gp.Cals, cals, sizeof(gp.Cals));
	gp.CalcCals();
	gp.Used = false;
	for (unsigned int id : gp.IDs) { if (id) { gp.Used = true; break; } }
}

BOOL WINAPI UIGetPad(int idx, unsigned int* ids, signed char* cals)
{
	#pragma GPLINKER_DLL_EXPORT
	GPGamepad& gp = pGPData->Gamepads[idx];
	bool changed = !!memcmp(ids, gp.IDs, sizeof(gp.IDs));
	memcpy(ids, gp.IDs, sizeof(gp.IDs));
	memcpy(cals, gp.Cals, sizeof(gp.Cals));
	return changed;
}

void WINAPI UIPad(int idx, unsigned short* vals, unsigned int captureSources)
{
	#pragma GPLINKER_DLL_EXPORT
	GPGamepad& gp = pGPData->Gamepads[idx];
	if (gp.Used)
	{
		if (InputUpdaters.empty()) InputSetup();
		CaptureSources = captureSources;
		RunInputUpdaters(gp);
	}
	memcpy(vals, gp.Vals, sizeof(gp.Vals));
}

BOOL WINAPI UILockLog(BOOL wantLock, void** out_log, int* out_length)
{
	#pragma GPLINKER_DLL_EXPORT
	if (!pGPData->LogLength) return false;
	if (wantLock)
	{
		GPLock(&pGPData->LogLock, 1);
		*out_log = (void*)pGPData->LogData;
		*out_length = (int)pGPData->LogLength;
	}
	else
	{
		GPASSERT(pGPData->LogLock == 1);
		pGPData->LogLength = 0;
		pGPData->LogLock = 0;
	}
	return true;
}

void WINAPI UISetup(GPOption options, const wchar_t* excludeList, const wchar_t* preparedDllIni)
{
	#pragma GPLINKER_DLL_EXPORT
	pGPData->Options = options;
	pGPData->ExcludeCount = 0;
	for (const wchar_t *p = excludeList, *exe = p; ; p++)
	{
		if (*p >= ' ') continue;
		if (p > exe) pGPData->InjectExcludes[pGPData->ExcludeCount++] = GPInject::HashExe(exe, p);
		if (!*p) break;
		exe = p + 1;
	}
	if (preparedDllIni)
	{
		WritePrivateProfileStructW(L"GamepadPhoenix", L"Options", &pGPData->Options, sizeof(pGPData->Options), preparedDllIni);
		WritePrivateProfileStructW(L"GamepadPhoenix", L"ExcludeCount", &pGPData->ExcludeCount, sizeof(pGPData->ExcludeCount), preparedDllIni);
		WritePrivateProfileStructW(L"GamepadPhoenix", L"InjectExcludes", &pGPData->InjectExcludes, sizeof(pGPData->InjectExcludes[0])*pGPData->ExcludeCount, preparedDllIni);
	}
}

void WINAPI UILaunch(const wchar_t* commandLine, const wchar_t* startDir)
{
	#pragma GPLINKER_DLL_EXPORT
	pGPData->FromGUI = true;
	pGPData->Recursion = 0;
	STARTUPINFOW si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(STARTUPINFOW);
	PROCESS_INFORMATION pi;
	wchar_t* commandLineDup = wcsdup(commandLine);
	GPASSERT(!g_hHeap); //UI shouldn't hook functions
	BOOL res = fpCreateProcessW(NULL, commandLineDup, NULL, NULL, false, (CREATE_SUSPENDED | CREATE_DEFAULT_ERROR_MODE | DETACHED_PROCESS), NULL, startDir, &si, &pi);
	free(commandLineDup);
	if (!res) return;
	WriteLog("[LAUNCH] UI launching process '%S'\n", commandLine);
	res = ((pGPData->Options & OPTION_IndirectLoading) || GPInject::IntoOpenedProcess(pi.hProcess) || GPInject::IntoNonNativeProcess(pi.dwProcessId));
	ResumeThread(pi.hThread);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

const wchar_t* WINAPI UIGetDIName(unsigned int devNum)
{
	#pragma GPLINKER_DLL_EXPORT
	if (InputUpdaters.empty()) InputSetup();
	return XDIGetDevName(devNum);
}

#include "GPWii.inl"

// save 15kb by removing the need for LocaleNameToIndexTable and LcidToLocaleNameTable
extern "C" void LocaleNameToIndexTable() {}
extern "C" void LcidToLocaleNameTable() {}
extern "C" void* __crtGetStringTypeA() {return 0;}
extern "C" void* __cdecl __crtLCMapStringA() {return 0;}
extern "C" void* __crtGetLocaleInfoEx() {GPASSERT(0);return 0;}
extern "C" void* __crtLCMapStringEx() {GPASSERT(0);return 0;}
extern "C" void* __crtIsValidLocaleName() {GPASSERT(0);return 0;}
extern "C" void* __crtEnumSystemLocalesEx() {GPASSERT(0);return 0;}
extern "C" void* __crtGetUserDefaultLocaleName() {GPASSERT(0);return 0;}
extern "C" void* __crtDownlevelLCIDToLocaleName() {GPASSERT(0);return 0;}
