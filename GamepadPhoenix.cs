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

using System.Windows.Forms;
using System;
using System.IO;
using System.Drawing;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using GamepadPhoenix;

[assembly: System.Reflection.AssemblyTitle("Gamepad Phoenix")]
[assembly: System.Reflection.AssemblyProduct("Gamepad Phoenix")]
[assembly: System.Reflection.AssemblyVersion("0.9.4")]
[assembly: System.Reflection.AssemblyFileVersion("0.9.4")]
[assembly: System.Reflection.AssemblyCopyright("(C) 2021-2022 Bernhard Schelling")]
[assembly: System.Runtime.InteropServices.ComVisible(false)]

namespace GamepadPhoenix
{
    [Flags]
    public enum GPOption : ushort
    {
        None                 = 0,
        [System.ComponentModel.Description("Map D-Pad to Left Stick")]
        DPadToLStick         = 0x1,
        [System.ComponentModel.Description("Swap A and B Buttons")]
        SwapAandB            = 0x2,
        [System.ComponentModel.Description("Swap L1/R1 and L2/R2")]
        SwapL1R1andL2R2      = 0x4,
        [System.ComponentModel.Description("DirectInput: Map Triggers to Buttons instead of Analog Axis")]
        DI_TriggersToButtons = 0x10,
        [System.ComponentModel.Description("DirectInput: Map D-Pad to Buttons instead of Point of View Hat")]
        DI_POVtoButtons      = 0x20,
        [System.ComponentModel.Description("Use Indirect Loading (Prepare redirector DLL to allow external stores/launchers)")]
        IndirectLoading      = 0x100,
        [System.ComponentModel.Description("Disable XInput (return no connected controllers)")]
        Disable_XInput       = 0x200,
        [System.ComponentModel.Description("Disable DirectInput (return no joystick or only fake XInput gamepads)")]
        Disable_DirectInput  = 0x400,
        [System.ComponentModel.Description("Disable MMSys (return no joystick or only fake XInput gamepads)")]
        Disable_MMSys        = 0x800,
        [System.ComponentModel.Description("Force game window to borderless fullscreen")]
        FullscreenWindow     = 0x4000,
    }

    internal enum GPIDInterface
    {
        NONE,
        KEYBOARD,
        DINPUT,
        XINPUT,
        WII,
        CAPTURE_NEXT_KEY,
    }

    internal enum GPIDSource
    {
        NONE   = 0,
        ALL    = (1 << (int)GPIDInterface.XINPUT) | (1 << (int)GPIDInterface.DINPUT) | (1 << (int)GPIDInterface.WII),
        XINPUT = (1 << (int)GPIDInterface.XINPUT),
        DINPUT = (1 << (int)GPIDInterface.DINPUT),
        WII    = (1 << (int)GPIDInterface.WII),
    };

    internal enum GPIndices : byte
    {
        LSTICK_U, LSTICK_D, LSTICK_L, LSTICK_R, RSTICK_U, RSTICK_D, RSTICK_L, RSTICK_R,
        TRIGGER_L, TRIGGER_R, DPAD_U, DPAD_D, DPAD_L, DPAD_R, BTN_A, BTN_B, BTN_X, BTN_Y, BTN_L, BTN_R,
        BTN_BACK, BTN_START, BTN_LSTICK, BTN_RSTICK, _MAX,
    };
    internal enum GPCals : byte
    {
        LDEADZONE, LLIMIT, LANTI, LSENS, LSHIFTH, LSHIFTV,
        RDEADZONE, RLIMIT, RANTI, RSENS, RSHIFTH, RSHIFTV, _MAX
    };

    internal class GPGamepad
    {
        internal const int NUM_GAMEPADS = 4, NUM_INDICES = (int)GPIndices._MAX, NUM_CALS = (int)GPCals._MAX;
        internal const uint GPID_CAPTURE_NEXT_KEY = (uint)GPIDInterface.CAPTURE_NEXT_KEY << GPID_SHIFT_INTF;
        internal const uint GPID_KEYBOARD_DEVICE = (uint)GPIDInterface.KEYBOARD << GPID_SHIFT_INTF;

        internal uint[] IDs = new uint[NUM_INDICES];
        internal ushort[] Vals = new ushort[NUM_INDICES];
        internal sbyte[] Cals = new sbyte[NUM_CALS];
        internal List<uint> UndoBuffer = new List<uint>();
        internal int UndoIndex = 0;

        int Index;
        GCHandle hIDs, hVals, hCals;
        IntPtr ptrIDs, ptrVals, ptrCals;
        internal bool Used, DrawnPressed;
        internal GPIndices Pressed;
        internal bool IsPressed(GPIndices idx) { return ((Vals[(int)idx] & 0x8000) != 0); }

        internal GPGamepad(int idx)
        {
            Index = idx;
            hIDs  = GCHandle.Alloc(IDs,  GCHandleType.Pinned); ptrIDs  = Marshal.UnsafeAddrOfPinnedArrayElement(IDs,  0);
            hVals = GCHandle.Alloc(Vals, GCHandleType.Pinned); ptrVals = Marshal.UnsafeAddrOfPinnedArrayElement(Vals, 0);
            hCals = GCHandle.Alloc(Cals, GCHandleType.Pinned); ptrCals = Marshal.UnsafeAddrOfPinnedArrayElement(Cals, 0);
            Used = Funcs.UIGetPad(Index, ptrIDs, ptrCals);
        }

        const int GPID_SHIFT_INTF = 29, GPID_SHIFT_DEVNUM = 8, GPID_BITS_DEV = (GPID_SHIFT_INTF - GPID_SHIFT_DEVNUM);
        internal static uint GPIDMake(GPIDInterface intf_num, uint dev_num, ushort obj_num) { return (((uint)intf_num) << GPID_SHIFT_INTF) | ((uint)dev_num << GPID_SHIFT_DEVNUM) | ((uint)obj_num); }
        internal static GPIDInterface GPIDGetInterface(uint id) { return (GPIDInterface)(id >> GPID_SHIFT_INTF); }
        internal static uint GPIDGetDevNum(uint id) { return (id >> GPID_SHIFT_DEVNUM) & ((1 << GPID_BITS_DEV)-1); }
        internal static byte GPIDGetObjNum(uint id) { return unchecked((byte)id); }

        internal static GPIDInterface GPIDUniqueIntfDevNum(uint[] src)
        {
            uint sameIntfDev = 0;
            foreach (uint id in src)
            {
                if (id == 0) continue;
                uint intfDev = (id & ~(uint)((1 << GPID_SHIFT_DEVNUM) - 1));
                sameIntfDev = (sameIntfDev == 0 || sameIntfDev == intfDev ? intfDev : uint.MaxValue);
            }
            return (sameIntfDev != 0 && sameIntfDev != uint.MaxValue && sameIntfDev != GPID_KEYBOARD_DEVICE ? GPIDGetInterface(sameIntfDev) : GPIDInterface.NONE);
        }

        void Refresh(bool setPad = false, bool dontUpdateUndo = false)
        {
            if (setPad) Funcs.UISetPad(Index, ptrIDs, ptrCals);

            Used = false;
            foreach (uint id in IDs) { if (id != 0) { Used = true; break; } }

            if (dontUpdateUndo) return;
            UndoBuffer.RemoveRange(UndoIndex, UndoBuffer.Count - UndoIndex);
            bool addUndo = (UndoBuffer.Count == 0);
            if (!addUndo) { for (int i = 0; i != NUM_INDICES; i++) { if (IDs[i] != UndoBuffer[UndoBuffer.Count - NUM_INDICES + i]) { addUndo = true; break; } } }
            if (!addUndo) return;
            UndoBuffer.AddRange(IDs);
            UndoIndex = UndoBuffer.Count;
        }

        //                              LSTICK_U LSTICK_D LSTICK_L LSTICK_R RSTICK_U RSTICK_D RSTICK_L RSTICK_R TRIGGER_L TRIGGER_R DPAD_U DPAD_D DPAD_L DPAD_R BTN_A BTN_B BTN_X BTN_Y BTN_L BTN_R BTN_BACK BTN_START BTN_LSTICK BTN_RSTICK
        static ushort[] XINPUT_OBJS = {  0x00,     0x01,    0x02,    0x03,    0x04,    0x05,   0x06,     0x07,   0x08,     0x09,    0x0a,  0x0b,  0x0c,  0x0d,  0x14, 0x15, 0x16, 0x17, 0x12, 0x13, 0x0f,    0x0e,     0x10,      0x11 };
        internal const uint GPID_XINPUT_L2_OBJ = 8;
        internal void MapFullXInputPad(uint dev_num)
        {
            for (int i = 0; i != NUM_INDICES; i++) IDs[i] = GPIDMake(GPIDInterface.XINPUT, dev_num, XINPUT_OBJS[i]);
            Refresh(setPad: true);
        }

        internal void Load(uint[] ids, sbyte[] cals = null, bool clearUndoBuffer = false)
        {
            for (int i = 0; i != NUM_INDICES; i++) IDs[i] = ids[i];
            for (int i = 0; i != NUM_CALS; i++) Cals[i] = (cals == null ? (sbyte)0 : cals[i]);
            if (clearUndoBuffer) { UndoBuffer.Clear(); UndoIndex = 0; }
            Refresh(setPad: true);
        }

        internal void LoadAs(uint[] ids, sbyte[] cals, uint switchDevNum, bool removeLastUndo)
        {
            if (removeLastUndo) UndoIndex -= NUM_INDICES;
            for (int i = 0; i != NUM_INDICES; i++) IDs[i] = GPIDMake(GPIDGetInterface(ids[i]), switchDevNum, GPIDGetObjNum(ids[i]));
            for (int i = 0; i != NUM_CALS; i++) Cals[i] = (cals == null ? (sbyte)0 : cals[i]);
            Refresh(setPad: true);
        }

        internal static void Swap(GPGamepad[] pads, int a, int b)
        {
            { GPGamepad v = pads[a]; pads[a] = pads[b]; pads[b] = v; }
            { int v = pads[a].Index; pads[a].Index = pads[b].Index; pads[b].Index = v; }
            pads[a].Refresh(setPad: true);
            pads[b].Refresh(setPad: true);
        }

        internal void WriteID(GPIndices idx, uint id)
        {
            if (IDs[(int)idx] == id) return;
            IDs[(int)idx] = id;
            Refresh(setPad: true, dontUpdateUndo:(id == GPID_CAPTURE_NEXT_KEY)); // != 0 is capture or assign cancel
        }

        internal void WriteCal(GPCals cal, sbyte val)
        {
            if (Cals[(int)cal] == val) return;
            Cals[(int)cal] = val;
            Refresh(setPad: true, dontUpdateUndo:true);
        }

        internal void NavigateUndo(int p)
        {
            UndoIndex += p * NUM_INDICES;
            UndoBuffer.CopyTo(UndoIndex - NUM_INDICES, IDs, 0, NUM_INDICES);
            Refresh(setPad: true, dontUpdateUndo: true);
        }

        internal void Read(GPIDSource captureSources = GPIDSource.NONE)
        {
            Funcs.UIPad(Index, ptrVals, (uint)captureSources);
            if (captureSources != GPIDSource.NONE) Funcs.UIGetPad(Index, ptrIDs, ptrCals);
            GPIndices down = GPIndices._MAX;
            for (int i = 0; i != NUM_INDICES; i++) { if ((Vals[i] & 0x8000) != 0) { down = (GPIndices)i; if (down != GPIndices.BTN_BACK) break; } }
            if (down != GPIndices._MAX && down != Pressed && GPIDGetInterface(IDs[(int)down]) != GPIDInterface.KEYBOARD) GUI.OnPadButton(this, down);
            Pressed = down;
        }

        internal bool IsKnownPreset(Dictionary<string, Config.Preset> presets)
        {
            foreach (Config.Preset p in presets.Values)
            {
                bool same = true;
                for (int i = 0; i != NUM_INDICES; i++)
                    if (GPIDMake(GPIDGetInterface(IDs[i]), 0, GPIDGetObjNum(IDs[i])) != GPIDMake(GPIDGetInterface(p.IDs[i]), 0, GPIDGetObjNum(p.IDs[i])))
                        { same = false; break; }
                if (same) return true;
            }
            return false;
        }

        internal static void GPIDSetTexts(Button btn, ToolTip toolTip, uint id)
        {
            string dev, obj;
            switch (GPIDGetInterface(id))
            {
                default:
                case GPIDInterface.NONE:
                    toolTip.SetToolTip(btn, (btn.Text = ""));
                    return;
                case GPIDInterface.CAPTURE_NEXT_KEY:
                    btn.Text = "...";
                    toolTip.SetToolTip(btn, "Input a command to assign to this");
                    return;
                case GPIDInterface.KEYBOARD:
                    obj = Names.GetKeyboard(GPIDGetObjNum(id));
                    btn.Text = "Key " + obj;
                    toolTip.SetToolTip(btn, "Keyboard key '" + obj + "'");
                    return;
                case GPIDInterface.DINPUT:
                    dev = Marshal.PtrToStringUni(Funcs.UIGetDIName(GPIDGetDevNum(id)));
                    if (dev == null) dev = "Unknown (not connected)";
                    obj = Names.GetDirectInput(GPIDGetObjNum(id));
                    btn.Text = "Joy '" + dev.Substring(0, 7) + "...' " + obj;
                    toolTip.SetToolTip(btn, "DirectInput Joystick '" + dev + "' " + obj);
                    return;
                case GPIDInterface.XINPUT:
                    dev = (GPIDGetDevNum(id) + 1).ToString();
                    obj = Names.GetXInput(GPIDGetObjNum(id));
                    btn.Text = "Pad #" + dev + " " + obj;
                    toolTip.SetToolTip(btn, "XInput Pad #" + dev + " " + obj);
                    return;
                case GPIDInterface.WII:
                    dev = (GPIDGetDevNum(id) + 1).ToString();
                    obj = Names.GetWii(GPIDGetObjNum(id));
                    btn.Text = "Wii #" + dev + " " + obj;
                    toolTip.SetToolTip(btn, "Wii Controller #" + dev + " " + obj);
                    return;
            }
        }

        static class Names
        {
            static string[] KeyboardKeys = new string[]
            {
                "", "Esc", "1","2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace", "Tab",
                "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Ctrl (Left)", "A", "S",
                "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", "Shift (Left)", "Backslash", "Z", "X", "C", "V", "B",
                "N", "M", ",", ".", "/", "Shift (Right)", "* (Numpad)", "Alt (Left)", "Space", "Caps Lock", "F1", "F2", "F3", "F4", "F5",
                "F6", "F7", "F8", "F9", "F10", "Num Lock", "Scroll Lock", "7 (Numpad)", "8 (Numpad)", "9 (Numpad)", "- (Numpad)", "4 (Numpad)", "5 (Numpad)", "6 (Numpad)", "+ (Numpad)", "1 (Numpad)",
                "2 (Numpad)", "3 (Numpad)", "0 (Numpad)", ". (Numpad)", "", "", "", "F11", "F12", "", "", "", "", "", "", "",
                "", "", "", "", "F13", "F14", "F15", "", "", "", "", "", "", "", "", "",
                "Kana", "", "", "", "", "", "", "", "", "Convert", "", "No Convert", "", "Yen", "", "",
                "", "", "", "", "", "", "", "", "", "", "", "", "", "= (Numpad)", "", "",
                "^", "@", ":", "_", "Kanji", "Stop", "(Japan AX)", "(J3100)", "", "", "", "", "Enter (Numpad)", "Ctrl (Right)", "", "",
                "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                "", "", "", ", (Numpad)", "", "/ (Numpad)", "", "Print Screen", "Alt (Right)", "", "", "", "", "", "", "",
                "", "", "", "", "", "Pause", "", "Home", "Arrow Up", "Page Up", "", "Arrow Left", "", "Arrow Right", "", "End",
                "Arrow Down", "Page Down", "Insert", "Delete", "", "", "", "", "", "", "", "Windows (Left)", "Windows (Right)", "Menu", "Power", "Sleep",
            };
            static string[] XInputObj = new string[]
            {
                "Left Stick Up",  "Left Stick Down",  "Left Stick Left",  "Left Stick Right",
                "Right Stick Up", "Right Stick Down", "Right Stick Left", "Right Stick Right",
                "Left Trigger", "Right Trigger",
                "DPAD Up", "DPAD Down", "DPAD Left", "DPAD Right",
                "Start", "Back",
                "Left Stick Press", "Right Stick Press",
                "Left Shoulder", "Right Shoulder",
                "A", "B", "X", "Y",
            };
            static string[] WiiObj = new string[]
            {
                "Remote Up", "Remote Down", "Remote Left", "Remote Right",
                "Remote A", "Remote B", "Remote One", "Remote Two",
                "Remote Plus", "Remote Minus", "Remote Home",
                "Left Stick Up",  "Left Stick Down",  "Left Stick Left",  "Left Stick Right",
                "Right Stick Up", "Right Stick Down", "Right Stick Left", "Right Stick Right",
                "Pad Up", "Pad Down", "Pad Left", "Pad Right", "Pad Plus", "Pad Minus",
                "Pad L", "Pad R", "Pad ZL", "Pad ZR",
                "Pad B", "Pad A", "Pad Y", "Pad X", "Pad Home",
                "Left Trigger", "Right Trigger",
            };
            internal static string GetKeyboard(uint o) { return KeyboardKeys[o >= KeyboardKeys.Length ? 0 : o]; }
            internal static string GetXInput(uint o) { return XInputObj[o >= XInputObj.Length ? 0 : o]; }
            enum GPDIJoyState { AXIS_COUNT = 8, POV_COUNT = 4, BUTTON_COUNT = 64 };
            internal static string GetDirectInput(uint o)
            {
                if (o < ((uint)GPDIJoyState.AXIS_COUNT*4))
                {
                    return ((o & 2) == 2 ? "Inv" : "") + "Axis " + (1+o/4).ToString() + ((o & 1) == 1 ? "+" : "-");
                }
                else if (o < ((uint)GPDIJoyState.AXIS_COUNT*4+(uint)GPDIJoyState.POV_COUNT*4))
                {
                    return "POV " + (1+(o-((uint)GPDIJoyState.AXIS_COUNT*4))/4).ToString() + " " + ((o&3)==0 ? "Up" : ((o&3)==1 ? "Down" : ((o&3)==2 ? "Left" : "Right")));
                }
                else if (o < ((uint)GPDIJoyState.AXIS_COUNT*4+(uint)GPDIJoyState.POV_COUNT*4+(uint)GPDIJoyState.BUTTON_COUNT))
                {
                    return "Button " + (1+o-((uint)GPDIJoyState.AXIS_COUNT*4+(uint)GPDIJoyState.POV_COUNT*4)).ToString();
                }
                return "";
            }
            internal static string GetWii(uint o) { return WiiObj[o >= WiiObj.Length ? 0 : o]; }
        }
    }

    static internal class Funcs
    {
        [UnmanagedFunctionPointer(CallingConvention.Winapi)] internal delegate void D_UIPad(int idx, IntPtr vals, uint captureSources = 0);
        [UnmanagedFunctionPointer(CallingConvention.Winapi)] internal delegate void D_UISetPad(int idx, IntPtr ids, IntPtr cals);
        [UnmanagedFunctionPointer(CallingConvention.Winapi)] internal delegate bool D_UIGetPad(int idx, IntPtr ids, IntPtr cals);
        [UnmanagedFunctionPointer(CallingConvention.Winapi)] internal delegate bool D_UILockLog(bool wantLock, out IntPtr out_log, out int out_length);
        [UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet=CharSet.Unicode)] internal delegate void D_UISetup(GPOption options, string excludeList, string preparedDllIni = null);
        [UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet=CharSet.Unicode)] internal delegate void D_UILaunch(string commandLine, string startDir);
        [UnmanagedFunctionPointer(CallingConvention.Winapi)] internal delegate IntPtr D_UIGetDIName(uint devNum);
        [UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet=CharSet.Unicode)] internal delegate int D_UIWii(string hidPath, bool on, int LEDs = 0);

        internal static D_UIPad       UIPad;
        internal static D_UISetPad    UISetPad;
        internal static D_UIGetPad    UIGetPad;
        internal static D_UILockLog   UILockLog;
        internal static D_UISetup     UISetup;
        internal static D_UILaunch    UILaunch;
        internal static D_UIGetDIName UIGetDIName;
        internal static D_UIWii       UIWii;

        internal static string DLL32 = "GamepadPhoenix32.dll", DLL64 = "GamepadPhoenix64.dll";
        internal static int SizeDLL32, SizeDLL64;

        static internal void Load()
        {
            IntPtr hModule = LoadLibraryA(IntPtr.Size == 4 ? DLL32 : DLL64);
            if (hModule == IntPtr.Zero || !File.Exists(IntPtr.Size != 4 ? DLL32 : DLL64))
            {
                MessageBox.Show("Missing DLLs " + DLL32 + " and " + DLL64 + ". Unable to continue.", "Gamepad Phoenix", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                Environment.Exit(1);
                return;
            }
            SizeDLL32 = (int)new FileInfo(DLL32).Length;
            SizeDLL64 = (int)new FileInfo(DLL64).Length;
            UIPad       = (D_UIPad      )Marshal.GetDelegateForFunctionPointer(GetProcAddress(hModule, "UIPad"      ), typeof(D_UIPad      ));
            UISetPad    = (D_UISetPad   )Marshal.GetDelegateForFunctionPointer(GetProcAddress(hModule, "UISetPad"   ), typeof(D_UISetPad   ));
            UIGetPad    = (D_UIGetPad   )Marshal.GetDelegateForFunctionPointer(GetProcAddress(hModule, "UIGetPad"   ), typeof(D_UIGetPad   ));
            UILockLog   = (D_UILockLog  )Marshal.GetDelegateForFunctionPointer(GetProcAddress(hModule, "UILockLog"  ), typeof(D_UILockLog  ));
            UISetup     = (D_UISetup    )Marshal.GetDelegateForFunctionPointer(GetProcAddress(hModule, "UISetup"    ), typeof(D_UISetup    ));
            UILaunch    = (D_UILaunch   )Marshal.GetDelegateForFunctionPointer(GetProcAddress(hModule, "UILaunch"   ), typeof(D_UILaunch   ));
            UIGetDIName = (D_UIGetDIName)Marshal.GetDelegateForFunctionPointer(GetProcAddress(hModule, "UIGetDIName"), typeof(D_UIGetDIName));
            UIWii       = (D_UIWii      )Marshal.GetDelegateForFunctionPointer(GetProcAddress(hModule, "UIWii"      ), typeof(D_UIWii      ));
        }

        [DllImport("kernel32.dll", ExactSpelling = true, CharSet=CharSet.Ansi)] static extern IntPtr LoadLibraryA(string lpLibFileName);
        [DllImport("kernel32.dll", ExactSpelling = true, CharSet=CharSet.Ansi)] static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);
    }

    public class Config
    {
        internal const string DefaultExcludeList = ""
            + "steam.exe" + "|"
            + "upc.exe" + "|"
            + "Origin.exe" + "|"
            + "EOSOverlayRenderer-Win32-Shipping.exe" + "|"
            + "EOSOverlayRenderer-Win64-Shipping.exe" + "|"
            + "explorer.exe" + "|"
            + "WerFault.exe" + "|"
            + "vsjitdebugger.exe";
        public class Preset
        {
            public Preset() { }
            internal Preset(string name, GPGamepad pad)
            {
                Name = name;
                Array.Copy(pad.IDs, IDs, IDs.Length);
                foreach (sbyte c in pad.Cals) { if (c != 0) { Cals = new sbyte[(int)GPCals._MAX]; Array.Copy(pad.Cals, Cals, Cals.Length); break; } }
            }
            [System.Xml.Serialization.XmlAttribute] public string Name = "";
            [System.Xml.Serialization.XmlAttribute] public uint[] IDs = new uint[(int)GPIndices._MAX];
            [System.Xml.Serialization.XmlAttribute] public sbyte[] Cals;
        }
        public class GamePad
        {
            [System.Xml.Serialization.XmlAttribute] public uint[] IDs;
            [System.Xml.Serialization.XmlAttribute] public sbyte[] Cals;
        }
        public class Game
        {
            [System.Xml.Serialization.XmlAttribute] public string Name = "";
            [System.Xml.Serialization.XmlAttribute] [System.ComponentModel.DefaultValue("")] public string Target = "", StartDir = "", Arguments = "";
            [System.Xml.Serialization.XmlIgnore] public GPOption Options = GPOption.None;
            [System.Xml.Serialization.XmlAttribute("Options")] [System.ComponentModel.DefaultValue("")]
            public string _XMLOptions
            {
                get { return (Options == GPOption.None ? "" : Options.ToString()); }
                set { try { Options = (GPOption)Enum.Parse(typeof(GPOption), value, true); } catch { } }
            }
            public override string ToString() { return Name; }
        }
        public List<GamePad> Gamepads = new List<GamePad>();
        public List<Preset> Presets = new List<Preset>();
        public List<Game> Games = new List<Game>();
        [System.ComponentModel.DefaultValue(DefaultExcludeList)] public string ExcludeList = DefaultExcludeList;
        public bool ShouldSerializeGamepads() { return Gamepads != null && Gamepads.Count > 0; }
        public bool ShouldSerializePresets() { return Presets != null && Presets.Count > 0; }
        public bool ShouldSerializeGames() { return Games != null && Games.Count > 0; }

        static int lastSaveHash = 0;

        static string ConfigFileName = new FileInfo(System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName).DirectoryName + Path.DirectorySeparatorChar + "GamepadPhoenix.xml";

        static internal void Load(out GPGamepad[] pads, out Dictionary<string, Preset> presets, ListBox games, TextBox excludes)
        {
            Config cfg = null;
            if (File.Exists(ConfigFileName)) try
            {
                string xml = File.ReadAllText(ConfigFileName, System.Text.Encoding.UTF8);
                lastSaveHash = xml.GetHashCode();
                using (var r = new StringReader(xml))
                    cfg = (Config)(new System.Xml.Serialization.XmlSerializer(typeof(Config))).Deserialize(r);
            }
            catch (Exception e) { MessageBox.Show("Error while loading GamepadPhoenix.xml config file:\n" + e.ToString(), "Gamepad Phoenix", MessageBoxButtons.OK, MessageBoxIcon.Stop); }
            if (cfg == null) { cfg = new Config(); lastSaveHash = "<Config />".GetHashCode(); }

            foreach (Config.GamePad gp in cfg.Gamepads)
                if (gp.IDs == null || gp.IDs.Length != (int)GPIndices._MAX)
                    gp.IDs = new uint[(int)GPIndices._MAX];
            bool havePads = false;
            pads = new GPGamepad[GPGamepad.NUM_GAMEPADS];
            for (int i = 0; i != GPGamepad.NUM_GAMEPADS; i++)
                havePads |= (pads[i] = new GPGamepad(i)).Used;
            if (!havePads && cfg.Gamepads != null)
                for (int i = 0; i < cfg.Gamepads.Count && i < GPGamepad.NUM_GAMEPADS; i++)
                    pads[i].Load(cfg.Gamepads[i].IDs, cfg.Gamepads[i].Cals, true);

            presets = new Dictionary<string,Preset>();
            foreach (Config.Preset p in cfg.Presets)
                if (p.IDs != null && p.IDs.Length == (int)GPIndices._MAX)
                    presets.Add(p.Name, p);

            games.Items.Clear();
            foreach (Config.Game g in cfg.Games)
                games.Items.Add(g);

            excludes.Text = System.Text.RegularExpressions.Regex.Replace(cfg.ExcludeList.Trim(), "[\\0-\\x19|]+", Environment.NewLine);
        }

        static internal bool Save(GPGamepad[] pads, Dictionary<string, Preset> presets, ListBox games, TextBox excludes)
        {
            Config cfg = new Config();
            int iEnd;
            for (int n = GPGamepad.NUM_GAMEPADS - 1;; n--) { if (n < 0 || pads[n].Used) { iEnd = n + 1; break; } }
            for (int i = 0; i != iEnd; i++)
            {
                GamePad gp = new GamePad();
                gp.IDs = pads[i].IDs;
                foreach (sbyte c in pads[i].Cals) { if (c != 0) { gp.Cals = pads[i].Cals; break; } }
                cfg.Gamepads.Add(gp);
            }
            foreach (Preset p in presets.Values)
                cfg.Presets.Add(p);
            foreach (object o in games.Items)
                cfg.Games.Add((Game)o);
            cfg.ExcludeList = System.Text.RegularExpressions.Regex.Replace(excludes.Text.Trim(), "[\\0-\\x19]+", "|");

            try { using (StringWriter sw = new StringWriter())
            {
                (new System.Xml.Serialization.XmlSerializer(typeof(Config))).Serialize(sw, cfg, new System.Xml.Serialization.XmlSerializerNamespaces(new [] { new System.Xml.XmlQualifiedName("", "") }));
                string xml = sw.ToString().Substring(sw.ToString().IndexOf("<Config")); // remove xml header
                int saveHash = xml.GetHashCode();
                if (lastSaveHash != saveHash)
                {
                    File.WriteAllText(ConfigFileName, xml, new System.Text.UTF8Encoding(false));
                    lastSaveHash = saveHash;
                }
            }}
            catch (Exception e) { MessageBox.Show("Error while saving GamepadPhoenix.xml config file:\n" + e.Message, "Gamepad Phoenix", MessageBoxButtons.OK, MessageBoxIcon.Stop); return false; }
            return true;
        }
    };

    static class IndirectLoading
    {
        static string[] DllOverrides = { "DINPUT8", "XINPUT1_3", "XINPUT1_4", "XINPUT1_2", "XINPUT1_1", "XINPUT9_1_0" };

        static byte[] ReadDirectory(FileStream fs, int dir, ref ushort machine, ref long rvaOffset)
        {
            byte[] buf = new byte[40];
            fs.Seek(0x3C, SeekOrigin.Begin);
            fs.Read(buf, 0, 4);
            uint lfanew = System.BitConverter.ToUInt32(buf, 0);
            fs.Seek(lfanew + 4, SeekOrigin.Begin);
            fs.Read(buf, 0, 4);
            machine = System.BitConverter.ToUInt16(buf, 0);
            ushort numberOfSections = System.BitConverter.ToUInt16(buf, 2);
            fs.Seek(lfanew + 0x14, SeekOrigin.Begin);
            fs.Read(buf, 0, 2);
            ushort sizeOfOptionalHeader = System.BitConverter.ToUInt16(buf, 0);
            fs.Seek(lfanew + 0x18 + sizeOfOptionalHeader - 0x80 + dir * 8, SeekOrigin.Begin);
            fs.Read(buf, 0, 8);
            uint dirRVA = System.BitConverter.ToUInt32(buf, 0), dirSize = System.BitConverter.ToUInt32(buf, 4);
            if (dirSize == 0) return null;
            fs.Seek(lfanew + 0x18 + sizeOfOptionalHeader, SeekOrigin.Begin);
            while (numberOfSections-- != 0)
            {
                fs.Read(buf, 0, 40);
                uint virtAddr = System.BitConverter.ToUInt32(buf, 12), rawSize = System.BitConverter.ToUInt32(buf, 16), rawAddr = System.BitConverter.ToUInt32(buf, 20);
                if (dirRVA < virtAddr || dirRVA >= virtAddr + rawSize) continue;
                byte[] res = new byte[dirSize];
                rvaOffset = (long)rawAddr - (long)virtAddr;
                fs.Seek(dirRVA + rvaOffset, SeekOrigin.Begin);
                fs.Read(res, 0, (int)dirSize);
                return res;
            }
            return null;
        }

        internal enum Ver { None, Current, Old };
        static Ver IsGPDLL(string path)
        {
            FileInfo fi = new FileInfo(path);
            if (!fi.Exists) return Ver.None;
            int len = (int)fi.Length;
            if (len == Funcs.SizeDLL32 || len == Funcs.SizeDLL64) { return Ver.Current; }
            try { using (FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.Read))
            {
                ushort machine = 0; long rvaOffset = 0;
                return (System.Text.Encoding.ASCII.GetString(ReadDirectory(fs, 0, ref machine, ref rvaOffset)).IndexOf("\0UIPad\0") != -1 ? Ver.Old : Ver.None); // also contains original linked dll file name
            }} catch {}
            return Ver.None;
        }

        internal static void ClearIndirectDLLs(string target)
        {
            try
            {
                string dir = Path.GetDirectoryName(target);
                foreach (string dll in DllOverrides)
                {
                    string path = dir + "\\" + dll + ".DLL";
                    if (!File.Exists(path) || IsGPDLL(path) == Ver.None) continue;
                    File.Delete(path);
                    try { File.Delete(path.Substring(0, path.Length - 3) + "INI"); } catch {  }
                    MessageBox.Show("Prepared game has been reverted and " + dll + ".DLL next to the game has been removed.", "Restore Game", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            } catch (Exception e) { MessageBox.Show("Error while trying to remove prepared file:\n" + e.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Stop); }
        }

        static bool CopyDLL(string dir, string dll, ushort machine)
        {
            string path = dir + "\\" + dll + ".DLL";
            bool exists = File.Exists(path);
            if (exists && IsGPDLL(path) == Ver.None) return false;
            string gpDll = "GamepadPhoenix" + (machine == 0x8664 ? "64" : "32") + ".dll";
            if (!exists || new FileInfo(path).Length != new FileInfo(gpDll).Length)
                File.Copy(gpDll, path, true);
            MessageBox.Show("Game has been prepared and " + gpDll + " has been copied next to the game as " + dll + ".DLL\n\nNow start the game through its launcher or store. You can also try launching it from here.\n\nBe aware that this tool needs to be running when doing so.", "Prepare Game", MessageBoxButtons.OK, MessageBoxIcon.Information);
            return true;
        }

        internal static bool PrepareIndirectDLL(string target)
        {
            try { using (FileStream fs = new FileStream(target, FileMode.Open, FileAccess.Read, FileShare.Read))
            {
                string dir = Path.GetDirectoryName(target);
                ushort machine = 0; long rvaOffset = 0;
                byte[] imports = ReadDirectory(fs, 1, ref machine, ref rvaOffset), bufDllName = new byte[16];
                for (int offset = 0; offset <= (imports == null ? 0 : imports.Length - 0x14); offset += 0x14)
                {
                    uint dllNameRVA = System.BitConverter.ToUInt32(imports, offset + 0xC);
                    if (dllNameRVA == 0) continue;
                    fs.Seek(dllNameRVA + rvaOffset, SeekOrigin.Begin);
                    fs.Read(bufDllName, 0, 16);
                    string dllName = System.Text.Encoding.ASCII.GetString(bufDllName);
                    foreach (string dll in DllOverrides)
                        if (dllName.StartsWith(dll + ".DLL\0", StringComparison.OrdinalIgnoreCase) && CopyDLL(dir, dll, machine))
                            return true;
                    if (dllName.StartsWith("UNITYPLAYER.DLL\0", StringComparison.OrdinalIgnoreCase) && CopyDLL(dir, "XINPUT1_3", machine))
                        return true;
                }
                byte[] buf = new byte[8192];
                int earliestDLLOverride = DllOverrides.Length;
                for (long i = 0; earliestDLLOverride > 0; i += 8192-16)
                {
                    if (fs.Seek(i, SeekOrigin.Begin) != i || fs.Read(buf, 0, 8192) <= 0) break;
                    string bufstr = System.Text.Encoding.ASCII.GetString(buf);
                    if (bufstr.IndexOf("INPUT", StringComparison.OrdinalIgnoreCase) == -1) continue;
                    for (int dll = 0; dll != earliestDLLOverride; dll++)
                        if (bufstr.IndexOf(DllOverrides[dll] + ".DLL", StringComparison.OrdinalIgnoreCase) != -1)
                            { earliestDLLOverride = dll; break; }
                }
                if (earliestDLLOverride != DllOverrides.Length && CopyDLL(dir, DllOverrides[earliestDLLOverride], machine))
                    return true;
                if (MessageBox.Show("Game might not support indirect loading (no overridable DLLs imported).\n\nDo you want to try to prepare it anyway?", "Prepare", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                    foreach (string dll in DllOverrides)
                        if ((machine != 0x8664 || dll != "DINPUT8") && CopyDLL(dir, dll, machine)) // Assume 64 bit apps to be more likely to use XINPUT and not DINPUT
                            return true;
            }} catch (Exception e) { MessageBox.Show("Game could not be prepared for indirect loading:\n" + e.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Stop); }
            return false;
        }

        internal static Ver IsPrepared(string target, ref string path)
        {
            string dir = Path.GetDirectoryName(target);
            foreach (string dll in DllOverrides)
                { string p = dir + "\\" + dll + ".DLL"; Ver v = IsGPDLL(p); if (v != Ver.None) { path = p; return v; } }
            return Ver.None;
        }
    }

    static class GUI
    {
        enum EPadPartType { NONE, STICK, TRIGGER, BUTTON, DPAD };
        class PadPart
        {
            internal Image img;
            internal int x = -1, y = -1;
            internal GPIndices idx = GPIndices._MAX, shareIdx = GPIndices._MAX, stickBtnIdx = GPIndices._MAX;
            internal EPadPartType type;
            internal Button assignBtn;
            internal string name;
            internal Rectangle r;
            internal uint oldId;
        }

        static GPGamepad[] Pads;
        static Point HoverPos;
        static int PadIdx = 0, UpdateCycle = 0;
        static PadPart PadPartHover, PadPartAssign;
        static List<PadPart> AssignQueue = new List<PadPart>();
        static Pen PenBlack = new Pen(Color.Black, 4), PenWhite = new Pen(Color.White, 2);
        static Pen PenThin = new Pen(Color.Black, 1);
        static Dictionary<string, Config.Preset> Presets;
        static bool IsDeviceSwitch, IsAutoLoad, FVisible = true;
        static MainForm f;
        static Form presetsForm;
        static PadPart[] PadParts;
        static byte[] LogBuf = new byte[512];
        static Config.Game ActiveGame;
        static DateTime FormActivateTime = DateTime.MaxValue;

        [System.STAThread] static void Main(string[] args)
        {
            Funcs.Load(); // Connect to native DLL
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            f = new MainForm();
            Config.Load(out Pads, out Presets, f.lstLaunchGames, f.txtMoreExcludeList);

            SetupPadTab();
            SetupLaunchTab();
            SetupMoreTab();

            // Systray support (could store last f.WindowState before minimizing into f.Tag but our form doesn't maximize)
            f.SizeChanged += (object sender, EventArgs e) => { if (f.WindowState == FormWindowState.Minimized) f.Visible = FVisible = false;  };
            f.systray.Click += ToggleWindowVisibility;
            f.systray.DoubleClick += ToggleWindowVisibility;
            f.systray.Text = f.Text;
            f.systray.Icon = f.Icon;

            // Auto launch via command line
            bool launch = false;
            if (args.Length > 0)
            {
                foreach (Config.Game g in f.lstLaunchGames.Items) { if (g.Name.Equals(args[0])) { f.lstLaunchGames.SelectedItem = g; launch = SetActiveGame(g); break; } }
                if (!launch) launch = SetActiveGame(new Config.Game { Target = args[0], Arguments = (args.Length > 1 ? args[1] : "") }, true);
            }
            if (launch)
            {
                LaunchGame();
                f.WindowState = FormWindowState.Minimized;
                f.tabs.SelectedIndex = f.tabs.TabCount - 2; // set before calling OnSelectTab
                f.panelPad.BringToFront(); // otherwise the tab control can end up in front of it...
            }

            // Finish form setup
            f.Activated += (object _s, EventArgs _e) => { FormActivateTime = DateTime.UtcNow; ShowLoading(false); };
            f.Deactivate += (object _s, EventArgs _e) => { FormActivateTime = DateTime.MaxValue; ShowLoading(false); };
            f.FormClosing += (object _s, FormClosingEventArgs _e) => _e.Cancel = !Config.Save(Pads, Presets, f.lstLaunchGames, f.txtMoreExcludeList);
            f.lblLoading.Click += (object _s, EventArgs _e) => { FormActivateTime = DateTime.MaxValue; ShowLoading(false); };
            f.timer.Tick += TickTimer;
            f.tabs.DrawItem += DrawTab;
            f.tabs.Selected += OnSelectTab;
            f.tabs.MouseClick += (object _s, MouseEventArgs e) =>
            {
                if (e.Button != MouseButtons.Right) return;
                for (int i = 0, numPadTabs = f.tabs.TabCount - 2; i != numPadTabs; i++)
                {
                    Rectangle r = f.tabs.GetTabRect(i);
                    if (!r.Contains(e.Location)) continue;
                    if (!Pads[i].Used) return;
                    f.tabs.SelectedIndex = i;
                    ContextMenuStrip cms = new ContextMenuStrip();
                    cms.Items.Add("Clear All Assignments");
                    cms.ItemClicked += (object __s, ToolStripItemClickedEventArgs __e) =>
                    {
                        if (!Pads[PadIdx].IsKnownPreset(Presets) && MessageBox.Show(f, "Are you sure you want to override and clear the current settings?", "Clear", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes) return;
                        Pads[PadIdx].Load(new uint[GPGamepad.NUM_INDICES]);
                        OnSelectTab();
                    };
                    cms.Show(f, new Point(e.X, e.Y));
                    return;
                }
            };
            OnSelectTab();

            Application.Run(f);
            Wii.Shutdown();
        }

        static void ShowLoading(bool on = true)
        {
            f.lblLoading.Visible = f.lblLoadingShadow.Visible = on;
            f.lblLoading.BringToFront();
        }

        static void ToggleWindowVisibility(object _s = null, EventArgs _e = null)
        {
            f.Visible = FVisible = !(FVisible && Window.IsOnScreen(f) > 0);
            if (FVisible) { f.WindowState = FormWindowState.Normal; f.Activate(); f.BringToFront(); }
        }

        static void LaunchGame(bool saveConfig = false)
        {
            string dllPath = null;
            if (saveConfig) Config.Save(Pads, Presets, f.lstLaunchGames, f.txtMoreExcludeList);
            if ((ActiveGame.Options & GPOption.IndirectLoading) != 0 && IndirectLoading.IsPrepared(ActiveGame.Target, ref dllPath) != IndirectLoading.Ver.Current)
            {
                if (!IndirectLoading.PrepareIndirectDLL(ActiveGame.Target)) return;
                RefreshLaunchTab(true);
            }
            ShowLoading();
            string startDir = (ActiveGame.StartDir.Length > 0 && Directory.Exists(ActiveGame.StartDir) ? ActiveGame.StartDir : Path.GetDirectoryName(ActiveGame.Target));
            Funcs.UISetup(ActiveGame.Options, f.txtMoreExcludeList.Text);
            Funcs.UILaunch("\"" + ActiveGame.Target + "\" " + ActiveGame.Arguments, startDir);
        }

        static void RefreshLaunchTab(bool writePreparedDllIni = false)
        {
            string dllPath = null;
            bool indirect = ((ActiveGame.Options & GPOption.IndirectLoading) != 0);
            bool valid = (ActiveGame.Target.Length != 0 && File.Exists(ActiveGame.Target));
            IndirectLoading.Ver prepared = (indirect && valid ? IndirectLoading.IsPrepared(ActiveGame.Target, ref dllPath) : IndirectLoading.Ver.None);
            f.btnLaunchPrepare.Enabled = (indirect && prepared != IndirectLoading.Ver.Current);
            f.btnLaunchRestore.Enabled = (indirect && prepared != IndirectLoading.Ver.None);
            f.btnLaunchPrepare.Visible = f.btnLaunchRestore.Visible = indirect;
            f.btnLaunch.Enabled = valid;
            f.btnLaunchOptions.Text = ActiveGame.Options.ToString().Replace("_", ": ");
            if (dllPath != null && writePreparedDllIni)
                Funcs.UISetup(ActiveGame.Options, f.txtMoreExcludeList.Text, dllPath.Substring(0, dllPath.Length - 3) + "INI");
            bool showBigSelectEXE = (ActiveGame.Target.Length == 0);
            if (f.btnLaunchSelectGameEXE.Enabled != showBigSelectEXE)
            {
                f.btnLaunchTargetSelect.Visible = f.btnLaunchTargetSelect.Enabled = !showBigSelectEXE;
                f.btnLaunchSelectGameEXE.Visible = f.btnLaunchSelectGameEXE.Enabled = showBigSelectEXE;
                f.txtLaunchTarget.Width += (f.btnLaunchSelectGameEXE.Width - f.btnLaunchTargetSelect.Width) * (showBigSelectEXE ? -1 : 1);
            }
            if (f.btnLaunchNew.Focused && f.btnLaunchSelectGameEXE.Enabled)
                f.btnLaunchSelectGameEXE.Focus();
        }

        static bool SetActiveGame(Config.Game g, bool isNew = false)
        {
            if (ActiveGame == g) return f.btnLaunch.Enabled;
            ActiveGame = g;
            f.txtLaunchName.Text = ActiveGame.Name;
            f.txtLaunchTarget.Text = ActiveGame.Target;
            if (f.txtLaunchStartDir.Text == ActiveGame.StartDir) f.txtLaunchStartDir.Text = "-"; //force update
            f.txtLaunchStartDir.Text = ActiveGame.StartDir;
            f.txtLaunchArguments.Text = ActiveGame.Arguments;
            f.btnLaunchSave.Enabled = isNew;
            f.btnLaunchDelete.Enabled = !isNew;
            RefreshLaunchTab();
            return f.btnLaunch.Enabled;
        }

        static void OpenPresetList(bool doSave)
        {
            AssignCancel();
            if (!doSave)
            {
                PadPartAssign = PadParts[1];
                PadPartAssign.oldId = Pads[PadIdx].IDs[(int)PadPartAssign.idx];
                Pads[PadIdx].WriteID(PadPartAssign.idx, GPGamepad.GPID_CAPTURE_NEXT_KEY);
                IsAutoLoad = true;
            }
            PresetsForm pf = new PresetsForm();
            pf.lblAutoLoad.Visible = !doSave;
            if (doSave) { pf.lstPresets.Top -= pf.lblAutoLoad.Height; pf.lstPresets.Height += pf.lblAutoLoad.Height; }
            foreach (string n in Presets.Keys)
                pf.lstPresets.Items.Add(n);
            Action refreshPresets = () =>
            {
                bool known = (Presets.ContainsKey(pf.txtName.Text));
                if (pf.txtName.Text != pf.lstPresets.Text)
                    pf.lstPresets.SelectedItem = (known ? pf.txtName.Text : null);
                pf.btnDelete.Enabled = known;
                pf.btnOK.Enabled = (pf.txtName.Text.Length != 0 && (doSave || known));
            };
            pf.btnDelete.Click += (object sender, System.EventArgs e) =>
            {
                if (MessageBox.Show(pf, "Are you sure you want to delete the preset '" + pf.txtName.Text + "'?", "Delete Preset", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
                    return;
                Presets.Remove(pf.txtName.Text);
                pf.lstPresets.Items.Remove(pf.lstPresets.SelectedItem);
                refreshPresets();
            };
            pf.lstPresets.SelectedIndexChanged += (object sender, System.EventArgs e) =>
            {
                if (pf.lstPresets.Text.Length != 0 && pf.txtName.Text != pf.lstPresets.Text)
                    pf.txtName.Text = pf.lstPresets.Text;
            };
            pf.lstPresets.DoubleClick += (object sender, System.EventArgs e) =>
            {
                if (pf.lstPresets.Text.Length != 0)
                    pf.DialogResult = DialogResult.OK;
            };
            pf.txtName.TextChanged += (object sender, System.EventArgs e) => refreshPresets();
            refreshPresets();
            presetsForm = pf;
            bool ok = (pf.ShowDialog() == DialogResult.OK);
            presetsForm = null;
            AssignCancel(); // reset capture next key
            if (ok && doSave)
            {
                if (!Presets.ContainsKey(pf.txtName.Text) || MessageBox.Show(f, "Save and override preset '" + pf.txtName.Text + "'?", "Save Preset", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                    Presets[pf.txtName.Text] = new Config.Preset(pf.txtName.Text, Pads[PadIdx]);
            }
            else if (ok && !doSave && (!Pads[PadIdx].Used || Pads[PadIdx].IsKnownPreset(Presets) || MessageBox.Show(f, "Are you sure you want to override the current settings with the preset '" + pf.txtName.Text + "'?", "Load Preset", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes))
            {
                Pads[PadIdx].Load(Presets[pf.txtName.Text].IDs, Presets[pf.txtName.Text].Cals);
                OnSelectTab();
            }
        }

        static void SetupPadTab()
        {
            PadParts = new PadPart[]
            {
                new PadPart { idx = GPIndices.TRIGGER_L, assignBtn = f.btnL2,      name = "L2 (Trigger)",        x =  76, y =   0, img = Resources.L2,     type = EPadPartType.TRIGGER },
                new PadPart { idx = GPIndices.TRIGGER_R, assignBtn = f.btnR2,      name = "R2 (Trigger)",        x = 310, y =   0, img = Resources.R2,     type = EPadPartType.TRIGGER },
                new PadPart { idx = GPIndices.BTN_L,     assignBtn = f.btnL1,      name = "L1 (Bumper)",         x =  60, y =  28, img = Resources.L1,     type = EPadPartType.BUTTON  },
                new PadPart { idx = GPIndices.BTN_R,     assignBtn = f.btnR1,      name = "R1 (Bumper)",         x = 325, y =  28, img = Resources.R1,     type = EPadPartType.BUTTON  },
                new PadPart {                                                                                    x =   0, y =   0, img = Resources.BG,                                 },
                new PadPart {                                                                                    x =  87, y =  91, img = Resources.Circle,                             },
                new PadPart { idx = GPIndices.LSTICK_U, stickBtnIdx = GPIndices.BTN_LSTICK,                      x = 100, y = 104, img = Resources.Stick,  type = EPadPartType.STICK   },
                new PadPart {                                                                                    x = 282, y = 189, img = Resources.Circle,                             },
                new PadPart { idx = GPIndices.RSTICK_U, stickBtnIdx = GPIndices.BTN_RSTICK,                      x = 295, y = 202, img = Resources.Stick,  type = EPadPartType.STICK   },
                new PadPart {                                                                                    x = 149, y = 187, img = Resources.DPADBlack,                          },
                new PadPart { idx = GPIndices.DPAD_U,                                                            x = 149, y = 187, img = Resources.DPAD,   type = EPadPartType.DPAD    },
                new PadPart { idx = GPIndices.BTN_Y,      assignBtn = f.btnY,       name = "Y (Top Button)",     x = 371, y =  75, img = Resources.Y,      type = EPadPartType.BUTTON  },
                new PadPart { idx = GPIndices.BTN_X,      assignBtn = f.btnX,       name = "X (Left Button)",    x = 335, y = 110, img = Resources.X,      type = EPadPartType.BUTTON  },
                new PadPart { idx = GPIndices.BTN_A,      assignBtn = f.btnA,       name = "A (Bottom Button)",  x = 371, y = 146, img = Resources.A,      type = EPadPartType.BUTTON  },
                new PadPart { idx = GPIndices.BTN_B,      assignBtn = f.btnB,       name = "B (Right Button)",   x = 408, y = 110, img = Resources.B,      type = EPadPartType.BUTTON  },
                new PadPart { idx = GPIndices.BTN_START,  assignBtn = f.btnStart,   name = "Start Button",       x = 281, y = 115, img = Resources.Start,  type = EPadPartType.BUTTON  },
                new PadPart { idx = GPIndices.BTN_BACK,   assignBtn = f.btnSelect,  name = "Back/Select Button", x = 206, y = 115, img = Resources.Select, type = EPadPartType.BUTTON  },
                new PadPart { idx = GPIndices.DPAD_U,     assignBtn = f.btnDPadU,   name = "D-Pad Up",           x = 188, y = 201, shareIdx = GPIndices.DPAD_U },
                new PadPart { idx = GPIndices.DPAD_L,     assignBtn = f.btnDPadL,   name = "D-Pad Left",         x = 161, y = 227, shareIdx = GPIndices.DPAD_U },
                new PadPart { idx = GPIndices.DPAD_D,     assignBtn = f.btnDPadD,   name = "D-Pad Down",         x = 188, y = 253, shareIdx = GPIndices.DPAD_U },
                new PadPart { idx = GPIndices.DPAD_R,     assignBtn = f.btnDPadR,   name = "D-Pad Right",        x = 212, y = 227, shareIdx = GPIndices.DPAD_U },
                new PadPart { idx = GPIndices.LSTICK_U,   assignBtn = f.btnLStickU, name = "Left-Stick Up",      x = 126, y = 100, shareIdx = GPIndices.LSTICK_U },
                new PadPart { idx = GPIndices.LSTICK_L,   assignBtn = f.btnLStickL, name = "Left-Stick Left",    x =  95, y = 129, shareIdx = GPIndices.LSTICK_U },
                new PadPart { idx = GPIndices.LSTICK_D,   assignBtn = f.btnLStickD, name = "Left-Stick Down",    x = 126, y = 158, shareIdx = GPIndices.LSTICK_U },
                new PadPart { idx = GPIndices.LSTICK_R,   assignBtn = f.btnLStickR, name = "Left-Stick Right",   x = 153, y = 129, shareIdx = GPIndices.LSTICK_U },
                new PadPart { idx = GPIndices.BTN_LSTICK, assignBtn = f.btnLStick,  name = "Left-Stick Button",  x = 126, y = 129, shareIdx = GPIndices.LSTICK_U },
                new PadPart { idx = GPIndices.RSTICK_U,   assignBtn = f.btnRStickU, name = "Right-Stick Up",     x = 321, y = 198, shareIdx = GPIndices.RSTICK_U },
                new PadPart { idx = GPIndices.RSTICK_L,   assignBtn = f.btnRStickL, name = "Right-Stick Left",   x = 290, y = 227, shareIdx = GPIndices.RSTICK_U },
                new PadPart { idx = GPIndices.RSTICK_D,   assignBtn = f.btnRStickD, name = "Right-Stick Down",   x = 321, y = 256, shareIdx = GPIndices.RSTICK_U },
                new PadPart { idx = GPIndices.RSTICK_R,   assignBtn = f.btnRStickR, name = "Right-Stick Right",  x = 348, y = 227, shareIdx = GPIndices.RSTICK_U },
                new PadPart { idx = GPIndices.BTN_RSTICK, assignBtn = f.btnRStick,  name = "Right-Stick Button", x = 321, y = 227, shareIdx = GPIndices.RSTICK_U },
            };
            foreach (PadPart part in PadParts)
            {
                if (part.img != null)
                    part.r = new Rectangle(part.x, part.y, part.img.Width, part.img.Height);
                else if (part.idx != GPIndices._MAX && part.x >= 0)
                    part.r = new Rectangle(part.x - 20, part.y - 20, 40, 40);
                if (part.assignBtn != null)
                    { part.assignBtn.Tag = part; part.assignBtn.Click += AssignBtnClick; }
            }
            f.pad.MouseMove += (object sender, MouseEventArgs e) => { HoverPos = e.Location; };
            f.pad.MouseLeave += (object sender, System.EventArgs e) => { HoverPos = new Point(-9999, -9999); };
            f.pad.Click += OnClickPad;
            f.pad.DoubleClick += OnClickPad;
            f.btnAssignAll.Click += (object _s, System.EventArgs _e) =>
            {
                AssignQueue.Clear();
                foreach (PadPart part in PadParts)
                    if (part.assignBtn != null)
                        AssignQueue.Add(part);
                AssignBtnClick();
            };
            f.btnAssignCancel.Click += AssignCancel;
            f.btnAssignClear.Click += (object _s, System.EventArgs _e) =>
            {
                if (PadPartAssign == null) return;
                Pads[PadIdx].WriteID(PadPartAssign.idx, 0);
                FinishAssign();
            };
            f.btnAssignSwitch.Click += (object _s, System.EventArgs _e) =>
            {
                if (PadPartAssign != null) { AssignCancel(); return; }
                PadPartAssign = PadParts[0];
                PadPartAssign.oldId = Pads[PadIdx].IDs[(int)PadPartAssign.idx];
                Pads[PadIdx].WriteID(PadPartAssign.idx, GPGamepad.GPID_CAPTURE_NEXT_KEY);
                IsDeviceSwitch = true;
            };
            f.btnDeadzones.Click += (object _s, System.EventArgs _e) =>
            {
                OnDeadzonesButton();
            };

            f.btnPresetSave.Click += (object _s, System.EventArgs _e) => OpenPresetList(true);
            f.btnPresetLoad.Click += (object _s, System.EventArgs _e) => OpenPresetList(false);

            f.btnAssignUndo.Click += (object _s, System.EventArgs _e) => { Pads[PadIdx].NavigateUndo(-1); OnSelectTab(); };
            f.btnAssignRedo.Click += (object _s, System.EventArgs _e) => { Pads[PadIdx].NavigateUndo( 1); OnSelectTab(); };

            f.btnSwapLeft.Click  += (object _s, System.EventArgs _e) => { GPGamepad.Swap(Pads, PadIdx, PadIdx - 1); f.tabs.SelectedIndex -= 1; };
            f.btnSwapRight.Click += (object _s, System.EventArgs _e) => { GPGamepad.Swap(Pads, PadIdx, PadIdx + 1); f.tabs.SelectedIndex += 1; };

            f.cmbAssignSource.SelectedIndex = 0;
        }

        static void SetupLaunchTab()
        {
            f.AllowDrop = true;
            f.DragEnter += (object sender, DragEventArgs e) =>
            {
                if (e.Data.GetDataPresent(DataFormats.FileDrop))
                    e.Effect = DragDropEffects.Copy;
            };
            f.DragDrop += (object sender, DragEventArgs e) =>
            {
                string[] files = (e.Data.GetData(DataFormats.FileDrop) as string[]);
                if (files == null || files.Length < 1) return;
                f.tabs.SelectedIndex = f.tabs.TabCount - 2;
                f.btnLaunchNew.PerformClick();
                f.txtLaunchTarget.Text = files[0];
            };

            f.lstLaunchGames.AllowDrop = true;
            f.lstLaunchGames.DragOver += (object sender, DragEventArgs e) =>
            {
                e.Effect = (e.Data.GetDataPresent(typeof(Config.Game)) ? DragDropEffects.Move : DragDropEffects.None);
            };
            f.lstLaunchGames.DragDrop += (object sender, DragEventArgs e) =>
            {
                if (!e.Data.GetDataPresent(typeof(Config.Game))) return;
                int idx = f.lstLaunchGames.IndexFromPoint(f.lstLaunchGames.PointToClient(new Point(e.X, e.Y)));
                if (idx < 0) idx = f.lstLaunchGames.Items.Count-1;
                object data = e.Data.GetData(typeof(Config.Game));
                f.lstLaunchGames.Items.Remove(data);
                f.lstLaunchGames.Items.Insert(idx, data);
                f.lstLaunchGames.SelectedItem = data;
            };

            f.lstLaunchGames.MouseDown += (object _s, MouseEventArgs e) =>
            {
                if (e.Button != MouseButtons.Left || f.lstLaunchGames.SelectedItem == null) return;
                if (e.Clicks == 1) f.lstLaunchGames.DoDragDrop(f.lstLaunchGames.SelectedItem, DragDropEffects.Move);
                if (e.Clicks == 2 && f.btnLaunch.Enabled) f.btnLaunch.PerformClick();
                SetActiveGame((Config.Game)f.lstLaunchGames.SelectedItem, false);
            };
            f.lstLaunchGames.SelectedValueChanged += (object _s, System.EventArgs _e) =>
            {
                if (f.lstLaunchGames.SelectedItem == null) return;
                SetActiveGame((Config.Game)f.lstLaunchGames.SelectedItem, false);
            };
            f.btnLaunchNew.Click += (object _s, System.EventArgs _e) =>
            {
                f.lstLaunchGames.SelectedItem = null;
                SetActiveGame(new Config.Game(), true);
            };
            f.btnLaunchDelete.Click += (object _s, System.EventArgs _e) =>
            {
                f.lstLaunchGames.Items.Remove(ActiveGame);
                f.btnLaunchSave.Enabled = true;
                f.btnLaunchDelete.Enabled = false;
            };
            f.btnLaunchSave.Click += (object _s, System.EventArgs _e) =>
            {
                f.lstLaunchGames.Items.Add(ActiveGame);
                f.lstLaunchGames.SelectedItem = ActiveGame;
                f.btnLaunchSave.Enabled = false;
                f.btnLaunchDelete.Enabled = true;
            };
            f.txtLaunchName.TextChanged += (object _s, System.EventArgs _e) =>
            {
                if (ActiveGame.Name == f.txtLaunchName.Text) return;
                ActiveGame.Name = f.txtLaunchName.Text;
                if (f.lstLaunchGames.SelectedItem != null) f.lstLaunchGames.Items[f.lstLaunchGames.SelectedIndex] = ActiveGame;
            };
            Action selectTarget = () =>
            {
                OpenFileDialog fd = new OpenFileDialog();
                fd.Filter = "Executables|*.exe;*.com;*.bat|All files (*.*)|*.*";
                fd.DefaultExt = "exe";
                fd.CheckFileExists = true;
                if (ActiveGame.Target.Length > 0) { fd.InitialDirectory = Path.GetDirectoryName(ActiveGame.Target); fd.FileName = ActiveGame.Target; }
                if (fd.ShowDialog() == DialogResult.OK) f.txtLaunchTarget.Text = fd.FileName;
                fd.Dispose();
            };
            f.btnLaunchSelectGameEXE.Click += (object _s, System.EventArgs _e) => selectTarget();
            f.btnLaunchTargetSelect.Click += (object _s, System.EventArgs _e) => selectTarget();
            f.btnLaunchStartDirSelect.Click += (object _s, System.EventArgs _e) =>
            {
                FolderBrowserDialog fd = new FolderBrowserDialog();
                fd.ShowNewFolderButton = false;
                if (f.txtLaunchStartDir.Text.Length > 0) fd.SelectedPath = f.txtLaunchStartDir.Text;
                if (fd.ShowDialog() == DialogResult.OK) f.txtLaunchStartDir.Text = fd.SelectedPath;
                fd.Dispose();
            };
            f.txtLaunchTarget.TextChanged += (object _s, System.EventArgs _e) =>
            {
                if (ActiveGame.Target == f.txtLaunchTarget.Text) return;
                if (f.txtLaunchName.Text == "" || (ActiveGame.Target != "" && f.txtLaunchName.Text == Path.GetFileNameWithoutExtension(ActiveGame.Target)))
                    f.txtLaunchName.Text = Path.GetFileNameWithoutExtension(f.txtLaunchTarget.Text);
                ActiveGame.Target = f.txtLaunchTarget.Text;
                if (ActiveGame.StartDir.Length == 0 && ActiveGame.Target.Length > 0)
                    f.txtLaunchStartDir.Text = Path.GetDirectoryName(ActiveGame.Target);
                RefreshLaunchTab(true);
            };
            f.txtLaunchStartDir.TextChanged += (object _s, System.EventArgs _e) =>
            {
                if (f.txtLaunchStartDir.Text == "-") return;
                string targetDir = (ActiveGame.Target.Length > 0 ? Path.GetDirectoryName(ActiveGame.Target) : "");
                string startDir = (f.txtLaunchStartDir.Text.Equals(targetDir, StringComparison.OrdinalIgnoreCase) ? "" : f.txtLaunchStartDir.Text);
                f.txtLaunchStartDir.ForeColor = (startDir.Length == 0 ? SystemColors.GrayText : SystemColors.ControlText);
                if (startDir.Length == 0) f.txtLaunchStartDir.Text = targetDir;
                ActiveGame.StartDir = startDir;
            };
            f.txtLaunchArguments.TextChanged += (object _s, System.EventArgs _e) =>
            {
                if (ActiveGame.Arguments == f.txtLaunchArguments.Text) return;
                ActiveGame.Arguments = f.txtLaunchArguments.Text;
            };
            f.btnLaunchPrepare.Click += (object _s, System.EventArgs _e) =>
            {
                IndirectLoading.PrepareIndirectDLL(ActiveGame.Target);
                RefreshLaunchTab(true);
            };
            f.btnLaunchRestore.Click += (object _s, System.EventArgs _e) =>
            {
                IndirectLoading.ClearIndirectDLLs(ActiveGame.Target);
                RefreshLaunchTab();
            };
            f.btnLaunch.Click += (object _s, System.EventArgs _e) => LaunchGame(true);
            f.btnLaunchLogClear.Click += (object _s, System.EventArgs _e) => f.lstLaunchLog.Items.Clear();
            f.lstLaunchLog.VisibleChanged += (object _s, System.EventArgs _e) =>
            {
                // Workaround for ListBox bug where the scrolling with TopIndex does not work until first shown
                if (f.lstLaunchLog.Tag != null) return;
                f.lstLaunchLog.TopIndex = f.lstLaunchLog.Items.Count - 1;
                f.lstLaunchLog.Tag = f.lstLaunchLog;
            };
            f.lstLaunchLog.KeyDown += (object _s, KeyEventArgs e) =>
            {
                if (e.Control && e.KeyCode == Keys.A)
                {
                    f.lstLaunchLog.SelectedItems.Clear();
                    for (int i = 0; i != f.lstLaunchLog.Items.Count; i++) f.lstLaunchLog.SelectedIndices.Add(i);
                }
                if (e.Control && e.KeyCode == Keys.C)
                {
                    System.Text.StringBuilder buf = new System.Text.StringBuilder();
                    foreach (object i in f.lstLaunchLog.SelectedItems) buf.AppendLine(i.ToString());
                    if (buf.Length > 0) Clipboard.SetText(buf.ToString());
                }
            };
            f.btnLaunchOptions.Click += (object _s, EventArgs _e) =>
            {
                f.btnLaunchOptions.Enabled = false;
                ToolStripDropDown dd = new ToolStripDropDown { CanOverflow = true, AutoClose = true, DropShadowEnabled = true, BackColor = SystemColors.Window, AutoSize = false, Width = f.btnLaunchOptions.Width };
                foreach (GPOption o in Enum.GetValues(typeof(GPOption)))
                {
                    if (o == GPOption.None) continue;
                    string n = ((System.ComponentModel.DescriptionAttribute)o.GetType().GetMember(o.ToString())[0].GetCustomAttributes(typeof(System.ComponentModel.DescriptionAttribute), false)[0]).Description;
                    var chkItem = new CheckBox{Text = n, Checked = (ActiveGame.Options & o) != 0, BackColor = Color.Transparent, Tag = o };
                    chkItem.Click += (object sender, EventArgs __e) =>
                    {
                        ActiveGame.Options ^= (GPOption)(sender as CheckBox).Tag;
                        if ((GPOption)(sender as CheckBox).Tag == GPOption.IndirectLoading)
                            IndirectLoading.ClearIndirectDLLs(ActiveGame.Target);
                        RefreshLaunchTab(true);
                    };
                    dd.Items.Add(new ToolStripControlHost(chkItem) { Margin = Padding.Empty, Padding = new Padding(10,0,0,0), AutoSize = true });
                }
                dd.Height = dd.GetPreferredSize(Size.Empty).Height;
                dd.Closed += (object sender, ToolStripDropDownClosedEventArgs __e) => f.btnLaunchOptions.Enabled = true;
                Point locationOnForm = f.PointToClient(f.btnLaunchOptions.Parent.PointToScreen(f.btnLaunchOptions.Location));
                dd.Show(f.PointToScreen(new Point(locationOnForm.X, locationOnForm.Y + f.btnLaunchOptions.Height)), ToolStripDropDownDirection.BelowRight);
            };
            SetActiveGame(new Config.Game(), true);
        }

        static void SetupMoreTab()
        {
            f.toolTip.SetToolTip(f.btnMoreHomepage, "https://schelling.itch.io/gamepad-phoenix");
            f.btnMoreHomepage.Click += (object _s, EventArgs _e) => System.Diagnostics.Process.Start("https://schelling.itch.io/gamepad-phoenix");
            f.toolTip.SetToolTip(f.btnMoreDonate, "https://paypal.com/donate?hosted_button_id=3WX4KRRTHN6EL");
            f.btnMoreDonate.Click += (object _s, EventArgs _e) => System.Diagnostics.Process.Start("https://paypal.com/donate?hosted_button_id=3WX4KRRTHN6EL");
            f.toolTip.SetToolTip(f.btnMoreGitHub, "https://github.com/schellingb/GamepadPhoenix");
            f.btnMoreGitHub.Click += (object _s, EventArgs _e) => System.Diagnostics.Process.Start("https://github.com/schellingb/GamepadPhoenix");
            f.btnMoreLicenses.Click += (object _s, EventArgs _e) =>
            {
                System.IO.MemoryStream ms = new System.IO.MemoryStream(Resources.LICENSE, false);
                System.IO.Compression.DeflateStream ds = new System.IO.Compression.DeflateStream(ms, System.IO.Compression.CompressionMode.Decompress, false);
                byte[] buf = new byte[35000];
                ds.Read(buf, 0, buf.Length);
                ds.Dispose();
                ms.Dispose();

                Form pu = new Form{Icon = f.Icon, StartPosition = FormStartPosition.CenterParent, FormBorderStyle = FormBorderStyle.SizableToolWindow,  Text = f.btnMoreLicenses.Text, Width = 600, Height = f.Height - 100 };
                pu.Controls.Add(new TextBox{ Multiline = true, ReadOnly = true, Text = System.Text.Encoding.UTF8.GetString(buf), Dock = DockStyle.Fill, ScrollBars = ScrollBars.Vertical });
                (pu.Controls[0] as TextBox).Select(0,0);
                pu.ShowDialog();
            };
            f.btnMoreResetExcludes.Click += (object _s, EventArgs _e) => f.txtMoreExcludeList.Text = System.Text.RegularExpressions.Regex.Replace(Config.DefaultExcludeList, "[|]", Environment.NewLine);
            Wii.Setup(f);
        }

        static void DrawTab(object sender, DrawItemEventArgs e)
        {
            int idx = e.Index, numTabs = f.tabs.TabCount;
            if (idx >= numTabs) return;
            string str = f.tabs.TabPages[idx].Text.Trim();
            bool isAddControllerTab = (str.Length == 0);
            bool isPad = (idx < numTabs - 2 && !isAddControllerTab);
            if (isPad) str = str.Substring(0, str.Length-1) + (idx + 1).ToString();
            else if (isAddControllerTab) str = "+";

            Rectangle paddedBounds = e.Bounds;
            SizeF size = e.Graphics.MeasureString(str, f.tabs.Font);
            paddedBounds.X += (paddedBounds.Width - (int)size.Width) / 2;
            paddedBounds.Y += 4;

            e.Graphics.FillRectangle(idx == f.tabs.SelectedIndex ? SystemBrushes.Control : SystemBrushes.ControlLight, e.Bounds);
            Brush b = SystemBrushes.ControlText;
            if (isPad)
            {
                GPGamepad pad = Pads[idx];
                if (pad.Pressed != GPIndices._MAX && PadPartAssign == null) { b = SystemBrushes.MenuHighlight; pad.DrawnPressed = true; }
                else if (pad.DrawnPressed) pad.DrawnPressed = false;
                if (!pad.Used) b = SystemBrushes.ControlDark;
            }
            e.Graphics.DrawString(str, f.tabs.Font, b, paddedBounds);
        }

        static void RedrawTabLabel(int padIdx)
        {
            Rectangle r = f.tabs.GetTabRect(padIdx);
            r.Inflate(-1, -1);
            f.tabs.Invalidate(r);
        }

        static void RefreshTabs()
        {
            int curTab = f.tabs.SelectedIndex, numPadTabs = f.tabs.TabCount - 2;
            bool isPad = (curTab < numPadTabs);
            int padCount = GPGamepad.NUM_GAMEPADS, minPads = (isPad ? curTab + 1 : 1);
            while (padCount > minPads && !Pads[padCount - 1].Used) padCount--;

            int needPadTabs = padCount + (padCount < GPGamepad.NUM_GAMEPADS ? 1 : 0);
            var h = f.tabs.Handle; // this is needed for TabPages.Insert to work during startup
            for (;needPadTabs > numPadTabs; numPadTabs++) f.tabs.TabPages.Insert(numPadTabs, "");
            for (;needPadTabs < numPadTabs; numPadTabs--) f.tabs.TabPages.RemoveAt(needPadTabs);
            for (int i = 1; i < padCount; i++)
                if (f.tabs.TabPages[i].Text.Length == 0)
                    f.tabs.TabPages[i].Text = f.tabs.TabPages[0].Text;
            if (padCount < GPGamepad.NUM_GAMEPADS && f.tabs.TabPages[padCount].Text.Length != 0)
                f.tabs.TabPages[padCount].Text = "";
        }

        static void OnSelectTab(object _s = null, TabControlEventArgs _e = null)
        {
            AssignCancel();
            RefreshTabs();
            bool isPad = (f.tabs.SelectedIndex < f.tabs.TabCount - 2);
            f.panelPad.Visible = isPad;
            if (!isPad) return;

            PadIdx = f.tabs.SelectedIndex;
            f.btnSwapLeft.Enabled = (PadIdx > 0);
            f.btnSwapRight.Enabled = (PadIdx < GPGamepad.NUM_GAMEPADS - 1);
            foreach (PadPart part in PadParts)
            {
                if (part.assignBtn == null) continue;
                if (Pads[PadIdx].IDs[(int)part.idx] == GPGamepad.GPID_CAPTURE_NEXT_KEY)
                    Pads[PadIdx].WriteID(part.idx, 0);
                GPGamepad.GPIDSetTexts(part.assignBtn, f.toolTip, Pads[PadIdx].IDs[(int)part.idx]);
            }
            f.pad.Invalidate();
            RefreshPadButtonVisibility();
            if (_s == null) RedrawTabLabel(PadIdx);
        }

        static void RefreshPadButtonVisibility()
        {
            f.btnAssignCancel.Visible = f.btnAssignClear.Visible = (PadPartAssign != null);
            f.btnAssignUndo.Visible = f.btnAssignRedo.Visible = (PadPartAssign == null);
            f.btnAssignUndo.Enabled = (Pads[PadIdx].UndoIndex > GPGamepad.NUM_INDICES);
            f.btnAssignRedo.Enabled = (Pads[PadIdx].UndoBuffer.Count > Pads[PadIdx].UndoIndex);
            f.btnAssignSwitch.Visible = (PadPartAssign == null && GPGamepad.GPIDUniqueIntfDevNum(Pads[PadIdx].IDs) != GPIDInterface.NONE);
        }

        static void OnClickPad(object _s, System.EventArgs _e)
        {
            if (PadPartHover == null) return;

            PadPart wasAssigning = PadPartAssign;
            AssignCancel();
            AssignQueue.Clear();
            foreach (PadPart part in PadParts)
                if (part.assignBtn != null && (part.idx == PadPartHover.idx || part.shareIdx == PadPartHover.idx))
                    AssignQueue.Add(part);
            if (AssignQueue.Count > 0 && !AssignQueue.Contains(wasAssigning))
                AssignBtnClick();
        }

        static void AssignBtnClick(object sender = null, System.EventArgs _e = null)
        {
            PadPart part;
            if (sender == null) { part = AssignQueue[0]; AssignQueue.RemoveAt(0); }
            else { part = (PadPart)((Button)sender).Tag; AssignQueue.Clear(); }

            bool wasAssigning = (PadPartAssign == part);
            AssignCancel();
            if (!wasAssigning)
            {
                part.oldId = Pads[PadIdx].IDs[(int)part.idx];
                Pads[PadIdx].WriteID(part.idx, GPGamepad.GPID_CAPTURE_NEXT_KEY);
                GPGamepad.GPIDSetTexts(part.assignBtn, f.toolTip, Pads[PadIdx].IDs[(int)part.idx]);
                PadPartAssign = part;
            }
            RefreshPadButtonVisibility();
        }

        static void AssignCancel(object _s = null, System.EventArgs _e = null)
        {
            if (PadPartAssign == null) return;
            AssignQueue.Clear();
            Pads[PadIdx].WriteID(PadPartAssign.idx, PadPartAssign.oldId);
            IsDeviceSwitch = IsAutoLoad = false;
            FinishAssign();
        }

        static void FinishAssign()
        {
            uint[] gpIDs = Pads[PadIdx].IDs;
            uint newid = gpIDs[(int)PadPartAssign.idx];
            bool mapFullXInput = (PadPartAssign.idx == GPIndices.TRIGGER_L && GPGamepad.GPIDGetInterface(newid) == GPIDInterface.XINPUT && GPGamepad.GPIDGetObjNum(newid) == GPGamepad.GPID_XINPUT_L2_OBJ && AssignQueue.Count > 8);
            if (IsDeviceSwitch || IsAutoLoad || mapFullXInput)
            {
                bool accept = false;
                gpIDs[(int)PadPartAssign.idx] = PadPartAssign.oldId;
                if (IsDeviceSwitch && (GPGamepad.GPIDUniqueIntfDevNum(gpIDs) == GPGamepad.GPIDGetInterface(newid)))
                {
                    Pads[PadIdx].LoadAs(gpIDs, Pads[PadIdx].Cals, GPGamepad.GPIDGetDevNum(newid), true);
                    accept = true;
                }
                else if (IsAutoLoad)
                {
                    uint autoIntfObj = GPGamepad.GPIDMake(GPGamepad.GPIDGetInterface(newid), 0, GPGamepad.GPIDGetObjNum(newid));
                    foreach (Config.Preset p in Presets.Values)
                    {
                        uint presetBtnL = p.IDs[(int)GPIndices.BTN_L];
                        if (autoIntfObj != GPGamepad.GPIDMake(GPGamepad.GPIDGetInterface(presetBtnL), 0, GPGamepad.GPIDGetObjNum(presetBtnL))) continue;
                        if (GPGamepad.GPIDUniqueIntfDevNum(p.IDs) == GPIDInterface.NONE) continue;
                        Pads[PadIdx].LoadAs(p.IDs, p.Cals, GPGamepad.GPIDGetDevNum(newid), true);
                        accept = true;
                        if (presetsForm != null) presetsForm.Close();
                        break;
                    }
                }
                else if (mapFullXInput)
                {
                    Pads[PadIdx].MapFullXInputPad(GPGamepad.GPIDGetDevNum(newid));
                    accept = true;
                }
                if (accept)
                {
                    IsDeviceSwitch = IsAutoLoad = false;
                    AssignQueue.Clear();
                    PadPartAssign = null;
                    OnSelectTab();
                }
                else
                {
                    Pads[PadIdx].WriteID(PadPartAssign.idx, GPGamepad.GPID_CAPTURE_NEXT_KEY);
                }
                return;
            }

            GPGamepad.GPIDSetTexts(PadPartAssign.assignBtn, f.toolTip, newid);
            PadPartAssign = null;

            RedrawTabLabel(PadIdx);

            if (AssignQueue.Count == 0) RefreshPadButtonVisibility();
            else { System.Threading.Thread.Sleep(100); AssignBtnClick(); }
        }

        static void TickTimer(object _s = null, EventArgs _e = null)
        {
            int onscreen = (FVisible ? Window.IsOnScreen(f) : 0);
            int newTimerInterval = (onscreen != 0 ? (onscreen == 2 ? 16 : 32) : 300);
            if (newTimerInterval != f.timer.Interval) f.timer.Interval = newTimerInterval;

            if (onscreen != 0)
            {
                if (f.panelPad.Visible) f.pad.Invalidate();
                if (f.fire.Visible) f.fire.Invalidate();

                for (int i = 0, process = (f.tabs.SelectedIndex == f.tabs.TabCount - 2 ? GPGamepad.NUM_GAMEPADS : 1); i != process; i++)
                {
                    UpdateCycle = ((UpdateCycle + 1) % GPGamepad.NUM_GAMEPADS);
                    GPGamepad pad = Pads[UpdateCycle];
                    if (!pad.Used) continue;
                    if (!f.panelPad.Visible || UpdateCycle != PadIdx) pad.Read();
                    if ((pad.Pressed != GPIndices._MAX) != pad.DrawnPressed) RedrawTabLabel(UpdateCycle);
                }
            }

            IntPtr log;
            int len;
            if (Funcs.UILockLog(true, out log, out len))
            {
                if (len > LogBuf.Length) LogBuf = new byte[len];
                Marshal.Copy(log, LogBuf, 0, len);
                Funcs.UILockLog(false, out log, out len);
                foreach (string line in System.Text.Encoding.UTF8.GetString(LogBuf, 0, len).Split(new char[] { '\n' }, System.StringSplitOptions.RemoveEmptyEntries))
                {
                    #if DEBUG
                    System.Console.WriteLine(line);
                    #endif
                    bool AutoScroll = (f.lstLaunchLog.TopIndex >= (f.lstLaunchLog.Items.Count - f.lstLaunchLog.ClientSize.Height / f.lstLaunchLog.ItemHeight - 1));
                    f.lstLaunchLog.Items.Add("[" + System.DateTime.Now.ToLongTimeString() + "] " + line);
                    if (AutoScroll) f.lstLaunchLog.TopIndex = f.lstLaunchLog.Items.Count - 1;
                }
            }
        }

        static internal void OnPadButton(GPGamepad pad, GPIndices btn)
        {
            if (btn == GPIndices.BTN_BACK || DateTime.UtcNow.Subtract(FormActivateTime).TotalMilliseconds < 300) return;
            if (pad.IsPressed(GPIndices.BTN_BACK))
            {
                switch (btn)
                {
                    case GPIndices.BTN_R: case GPIndices.TRIGGER_R:
                        if (f.tabs.SelectedIndex < f.tabs.TabCount - 1) f.tabs.SelectedIndex = f.tabs.SelectedIndex += (f.tabs.TabPages[f.tabs.SelectedIndex + 1].Text.Length == 0 ? 2 : 1);
                        return;
                    case GPIndices.BTN_L: case GPIndices.TRIGGER_L:
                        if (f.tabs.SelectedIndex > 0) f.tabs.SelectedIndex -= (f.tabs.TabPages[f.tabs.SelectedIndex - 1].Text.Length == 0 ? 2 : 1);
                        return;
                    case GPIndices.BTN_A: case GPIndices.BTN_B: case GPIndices.BTN_X: case GPIndices.BTN_Y:
                        f.tabs.SelectedIndex = f.tabs.TabCount - 2;
                        return;
                    case GPIndices.DPAD_L: case GPIndices.LSTICK_L: case GPIndices.RSTICK_L:
                        if (f.panelPad.Visible && f.btnSwapLeft.Enabled) f.btnSwapLeft.PerformClick();
                        return;
                    case GPIndices.DPAD_R: case GPIndices.LSTICK_R: case GPIndices.RSTICK_R:
                        if (f.panelPad.Visible && f.btnSwapRight.Enabled) f.btnSwapRight.PerformClick();
                        return;
                }
            }
            if (f.tabs.SelectedIndex == f.tabs.TabCount - 2)
            {
                int move = 0;
                switch (btn)
                {
                    case GPIndices.DPAD_U: case GPIndices.LSTICK_U: move =  -1; break;
                    case GPIndices.DPAD_D: case GPIndices.LSTICK_D: move =   1; break;
                    case GPIndices.DPAD_L: case GPIndices.LSTICK_L: move = -10; break;
                    case GPIndices.DPAD_R: case GPIndices.LSTICK_R: move =  10; break;
                    case GPIndices.BTN_START: case GPIndices.BTN_A: case GPIndices.BTN_B: case GPIndices.BTN_X: case GPIndices.BTN_Y:
                        if (f.btnLaunch.Enabled) LaunchGame(true);
                        return;
                }
                if (move != 0)
                    f.lstLaunchGames.SelectedIndex = Math.Min(f.lstLaunchGames.Items.Count - 1, Math.Max(0,  f.lstLaunchGames.SelectedIndex + move));
            }
        }

        static ushort DeadzoneAxis(int idx, ushort[] gpVals, sbyte[] gpCals)
        {
            int ofs = (idx < (int)GPIndices.RSTICK_U ? 0 : ((int)GPCals.RDEADZONE - (int)GPCals.LDEADZONE));
            int dz = gpCals[(int)GPCals.LDEADZONE + ofs] * 0xFFFF / 100, limit = gpCals[(int)GPCals.LLIMIT + ofs] * 0xFFFF / 100;
            int shift = gpCals[(int)GPCals.LSHIFTV + ofs] * ((idx&2)!=0 ? 0 : (idx&1)!=0 ? 1 : -1) + gpCals[(int)GPCals.LSHIFTH + ofs] * ((idx&2)!=0 ? (idx&1)!=0 ? 1 : -1 : 0);
            int fix = (shift * 0xFFFF / 100) - dz, anti = gpCals[(int)GPCals.LANTI + ofs] * 0xFFFF / 100, csens = gpCals[(int)GPCals.LSENS + ofs];
            float sens = (csens > 0 ? (1.0f + (csens * 0.04f)) : (csens < 0 ? (1.0f + (csens * 0.006f)) : 0.0f));
            uint inrange = (uint)Math.Max(1, (0xFFFF - dz - limit)), outrange = (uint)Math.Max(1, (0xFFFF - anti));
            int v = gpVals[idx] + fix;
            if (fix > 0) v -= gpVals[idx + ((idx&1)!=0 ? -1 : 1)];
            if (v <= 0) return 0;
            if (v >= inrange) return 0xFFFF;
            uint w = (uint)v * outrange / inrange;
            if (sens != 0) w = (uint)(Math.Pow((float)w / outrange, sens) * outrange);
            return (ushort)(w + anti);
        }

        static internal void RenderPad(Graphics g)
        {
            if (PadPartAssign != null)
            {
                GPIDSource captureSources;
                switch (f.cmbAssignSource.SelectedIndex)
                {
                    case 0: captureSources = GPIDSource.ALL; break;
                    case 1: captureSources = GPIDSource.XINPUT; break;
                    case 2: captureSources = GPIDSource.DINPUT; break;
                    case 3: captureSources = GPIDSource.WII; break;
                    default: throw new System.Exception();
                }
                if (IsDeviceSwitch) captureSources = (GPIDSource)(1 << (int)GPGamepad.GPIDGetInterface(PadPartAssign.oldId));
                if (IsAutoLoad) captureSources = GPIDSource.ALL;
                Pads[PadIdx].Read(captureSources);
            }
            else
            {
                Pads[PadIdx].Read();
            }

            PadPartHover = null;
            ushort[] gpVals = Pads[PadIdx].Vals;
            sbyte[] gpCals = Pads[PadIdx].Cals;
            g.Clear(SystemColors.Control);
            foreach (PadPart part in PadParts)
            {
                if (part.img != null)
                {
                    var r = part.r;
                    var img = part.img;
                    var pressed = false;
                    if (PadPartAssign == null)
                    {
                        switch (part.type)
                        {
                            case EPadPartType.BUTTON:
                                pressed = ((gpVals[(int)part.idx] & 0x8000) != 0);
                                if (pressed && part.y < 40) { r.Y += 3; }
                                else if (pressed) { r.X += 1; r.Y += 5; }
                                break;
                            case EPadPartType.DPAD:
                                r.Y += ((gpVals[(int)part.idx+1] & 0x8000) >> 13) - ((gpVals[(int)part.idx  ] & 0x8000) >> 13);
                                r.X += ((gpVals[(int)part.idx+3] & 0x8000) >> 13) - ((gpVals[(int)part.idx+2] & 0x8000) >> 13);
                                break;
                            case EPadPartType.STICK:
                                r.Y += (int)(DeadzoneAxis((int)part.idx+1, gpVals, gpCals)*0.0002f - DeadzoneAxis((int)part.idx  , gpVals, gpCals)*0.0002f);
                                r.X += (int)(DeadzoneAxis((int)part.idx+3, gpVals, gpCals)*0.0002f - DeadzoneAxis((int)part.idx+2, gpVals, gpCals)*0.0002f);
                                pressed = ((gpVals[(int)part.stickBtnIdx] & 0x8000) != 0);
                                if (pressed) img = f.picLStick.Image;
                                break;
                            case EPadPartType.TRIGGER:
                                pressed = ((gpVals[(int)part.idx] & 0x8000) != 0);
                                r.Y += (int)(gpVals[(int)part.idx]*0.0002f);
                                break;
                        }
                    }
                    g.DrawImage(img, r);
                    if (part.idx != GPIndices._MAX && r.Contains(HoverPos))
                    {
                        PadPartHover = part;
                    }
                    if (pressed)
                    {
                        r.Inflate(5, 5);
                        g.DrawImage(Resources.GlowPress, r);
                    }
                }
                else if (part.idx != GPIndices._MAX && part.x >= 0 && ((gpVals[(int)part.idx] & 0x8000) != 0) && PadPartAssign == null && part.shareIdx != GPIndices.LSTICK_U && part.shareIdx != GPIndices.RSTICK_U)
                {
                    g.DrawImage(Resources.GlowPress, part.r);
                }
            }
            for (int i = 0; i != 4; i++)
            {
                var r = new Rectangle(211 + i * 24, 37, 18, 15);
                g.DrawImage((i <= PadIdx ? Resources.LEDOn : Resources.LEDOff), r);
            }
            if (PadPartHover != null && (PadPartAssign == null || (PadPartAssign.idx != PadPartHover.idx && PadPartAssign.shareIdx != PadPartHover.idx)))
            {
                var glowrec = PadPartHover.r;
                glowrec.Inflate(5, 5);
                foreach (PadPart sharePart in PadParts)
                {
                    if ((sharePart.idx != PadPartHover.idx && sharePart.shareIdx != PadPartHover.idx) || sharePart.assignBtn == null) continue;
                    int x = (sharePart.assignBtn.Left > f.pad.Left ? 512 : 0);
                    int y = sharePart.assignBtn.Top + sharePart.assignBtn.Height / 2 - f.pad.Top;
                    g.DrawLine(PenBlack, glowrec.X + glowrec.Width / 2, glowrec.Y + glowrec.Height / 2, x, y);
                    g.DrawLine(PenWhite, glowrec.X + glowrec.Width / 2, glowrec.Y + glowrec.Height / 2, x, y);
                }
                g.DrawImage(Resources.GlowHover, glowrec);
            }
            if (PadPartAssign != null)
            {
                if (Pads[PadIdx].IDs[(int)PadPartAssign.idx] != GPGamepad.GPID_CAPTURE_NEXT_KEY)
                {
                    FinishAssign();
                }
                if (PadPartAssign != null)
                {
                    string str = (IsAutoLoad ? "Press L1 to load preset" : IsDeviceSwitch ? "Push new device\n  (of same type)" : "Press '" + PadPartAssign.name + "'");
                    var sz = g.MeasureString(str, f.lblBigFont.Font);
                    int txtX = (int)((g.VisibleClipBounds.Width - sz.Width) / 2);
                    int txtY = (int)((g.VisibleClipBounds.Height - sz.Height) / 2);
                    if (!IsDeviceSwitch)
                        g.DrawImage(Resources.GlowAssign, PadPartAssign.r);

                    for (int i = 0; i != 9; i++)
                        g.DrawString(str, f.lblBigFont.Font, Brushes.Black, txtX - 2 + (i / 3) * 2, txtY - 2 + (i % 3) * 2);
                    g.DrawString(str, f.lblBigFont.Font, Brushes.Red, txtX, txtY);
                }
            }
        }

        internal static void RenderAbout(FireLogo fireLogo)
        {
            fireLogo.DrawText(f.lblBigFont.Font, "Gamepad Phoenix", 30, Brushes.Yellow, 2);
            fireLogo.DrawText(f.lblMoreWii.Font, "Version " + Application.ProductVersion, 80, Brushes.Pink, 1);
            fireLogo.DrawText(f.lblMoreWii.Font, "Gamepad Phoenix - Copyright (c) 2021-2022 Bernhard Schelling", fireLogo.Height - 45, Brushes.LightYellow, 1);
            fireLogo.DrawText(f.lblMoreWii.Font, "Powered by MinHook - Copyright (c) 2009-2017 Tsuda Kageyu", fireLogo.Height - 25, Brushes.LightYellow, 1);
        }

        internal static void OnDeadzonesButton()
        {
            DeadzoneForm df = new DeadzoneForm();
            df.timer.Tick += (object s, EventArgs e) => { df.deadzoneControl.Invalidate(); };
            TrackBar[]      trks = new [] { df.trkLeftDeadzone, df.trkLeftLimit, df.trkLeftAnti, df.trkLeftSens, df.trkLeftShiftH, df.trkLeftShiftV, df.trkRightDeadzone, df.trkRightLimit, df.trkRightAnti, df.trkRightSens, df.trkRightShiftH, df.trkRightShiftV };
            NumericUpDown[] nums = new [] { df.numLeftDeadzone, df.numLeftLimit, df.numLeftAnti, df.numLeftSens, df.numLeftShiftH, df.numLeftShiftV, df.numRightDeadzone, df.numRightLimit, df.numRightAnti, df.numRightSens, df.numRightShiftH, df.numRightShiftV };
            for (int i = 0; i != trks.Length; i++)
            {
                int idx = i;
                Action update = () => Pads[PadIdx].WriteCal((GPCals)idx, (sbyte)trks[idx].Value);
                nums[idx].Value = trks[idx].Value = Pads[PadIdx].Cals[idx];
                trks[idx].ValueChanged += (object s, EventArgs e) => { nums[idx].Value = trks[idx].Value; update(); };
                nums[idx].ValueChanged += (object s, EventArgs e) => { trks[idx].Value = (int)nums[idx].Value; };
            }
            df.btnReset.Click += (object s, EventArgs e) =>
            {
                if (MessageBox.Show(f, "Are you sure you want to reset the current settings?", "Reset", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes) return;
                for (int idx = 0; idx != (int)GPCals._MAX; idx++) nums[idx].Value = 0;
            };
            df.btnOK.Click += (object s, EventArgs e) => df.DialogResult = DialogResult.OK;
            df.ShowDialog();
        }

        internal static void RenderDeadzones(Graphics g)
        {
            ushort[] gpVals = Pads[PadIdx].Vals;
            sbyte[] gpCals = Pads[PadIdx].Cals;
            g.Clear(SystemColors.Control);
            for (int stick = 0; stick != 2; stick++)
            {
                int ofsVal = (stick == 0 ? 0 : ((int)GPIndices.RSTICK_U - (int)GPIndices.LSTICK_U));
                int ofsCal = (stick == 0 ? 0 : ((int)GPCals.RDEADZONE - (int)GPCals.LDEADZONE));
                float x = 200 + stick * 350, r = 80, d=r*2;
                float rLimit = r * (1.0f - (gpCals[ofsCal+(int)GPCals.LLIMIT] / 100.0f)), dLimit = rLimit*2;
                float rDead = r * (gpCals[ofsCal+(int)GPCals.LDEADZONE] / 100.0f), dDead = rDead*2;
                float rAnti = r * (gpCals[ofsCal+(int)GPCals.LANTI] / 100.0f), dAnti = rAnti*2;
                for (int corr = 0; corr != 2; corr++)
                {
                    ushort sr = (corr == 0 ? gpVals[ofsVal + (int)GPIndices.LSTICK_R] : DeadzoneAxis(ofsVal + (int)GPIndices.LSTICK_R, gpVals, gpCals));
                    ushort sl = (corr == 0 ? gpVals[ofsVal + (int)GPIndices.LSTICK_L] : DeadzoneAxis(ofsVal + (int)GPIndices.LSTICK_L, gpVals, gpCals));
                    ushort sd = (corr == 0 ? gpVals[ofsVal + (int)GPIndices.LSTICK_D] : DeadzoneAxis(ofsVal + (int)GPIndices.LSTICK_D, gpVals, gpCals));
                    ushort su = (corr == 0 ? gpVals[ofsVal + (int)GPIndices.LSTICK_U] : DeadzoneAxis(ofsVal + (int)GPIndices.LSTICK_U, gpVals, gpCals));
                    float valX = Math.Max(-1.0f, Math.Min(1.0f, (sr - sl)/65535.0f));
                    float valY = Math.Max(-1.0f, Math.Min(1.0f, (sd - su)/65535.0f));
                    string strx = valX.ToString("0.0%"), stry = valY.ToString("0.0%");
                    SizeF szx = g.MeasureString(strx, f.lblMoreWii.Font), szy = g.MeasureString(stry, f.lblMoreWii.Font);
                    float y = 10+r + corr * 360, sx = x + valX*r, sy = y + valY*r;
                    g.FillRectangle(SystemBrushes.ControlDarkDark, x-r, y-r, d, d);
                    g.DrawRectangle(PenBlack,                      x-r, y-r, d, d);
                    if (corr == 0)
                    {
                        g.FillEllipse(Brushes.PaleVioletRed, x-r+0.5f, y-r+0.5f, d-1, d-1);
                        g.FillEllipse(SystemBrushes.ControlDark, x-rLimit+0.5f, y-rLimit+0.5f, dLimit-1, dLimit-1);
                        g.FillRectangle(Brushes.Pink, x-rLimit+2, y-rDead, dLimit-4, dDead);
                        g.FillRectangle(Brushes.Pink, x-rDead, y-rLimit+2, dDead, dLimit-4);
                        g.FillRectangle(Brushes.PaleVioletRed, x-rDead, y-rDead, dDead, dDead);
                    }
                    else
                    {
                        g.FillEllipse(SystemBrushes.ControlDark, x-r+0.5f, y-r+0.5f, d-1, d-1);
                        g.FillRectangle(Brushes.PaleVioletRed, x-rAnti, y-rAnti, dAnti, dAnti);
                    }
                    g.DrawEllipse(PenBlack, x-r+0.5f, y-r+0.5f, d-1, d-1);
                    g.DrawLine(PenThin, x-r, y, x+r, y);
                    g.DrawLine(PenThin, x, y-r, x, y+r);
                    g.FillRectangle(Brushes.Goldenrod, sx - 2, sy - 2, 5, 5);
                    g.DrawString(strx, f.lblMoreWii.Font, (valX == 0.0f ? Brushes.Black : (valX > 0 ?  Brushes.DarkGreen : Brushes.DarkRed)), sx - szx.Width*0.5f, y+r+5);
                    g.DrawString(stry, f.lblMoreWii.Font, (valY == 0.0f ? Brushes.Black : (valY > 0 ?  Brushes.DarkGreen : Brushes.DarkRed)), x+r+5, sy - szy.Height*0.5f);
                }
            }
            g.RotateTransform(-90);
            g.DrawString("Raw",       f.lblBigFont.Font, Brushes.Black, -130, 25);
            g.DrawString("Corrected", f.lblBigFont.Font, Brushes.Black, -540, 25);
            g.ResetTransform();
        }}

    static class Window
    {
        internal static int IsOnScreen(Form window)
        {
            IntPtr hwnd = window.Handle, hwndFg = GetForegroundWindow();
            if (window.Handle == hwndFg) return 2;
            RECT rec, fg;
            GetWindowRect(hwnd, out rec);
            GetWindowRect(hwndFg, out fg);
            if (fg.left > rec.left || fg.right < rec.right || fg.top > rec.top || fg.bottom < rec.bottom)
                foreach (var pt in new Point[] { new Point(rec.left + 2, rec.top + 2), new Point(rec.right - 2, rec.top + 2), new Point(rec.left + 2, rec.bottom - 2), new Point(rec.right - 2, rec.bottom - 2) })
                    if (WindowFromPoint(pt) == hwnd && MonitorFromPoint(pt) != IntPtr.Zero)
                        return 1;
            return 0;
        }
        [DllImport("user32.dll", ExactSpelling = true)] static extern IntPtr GetForegroundWindow();
        [DllImport("user32.dll", ExactSpelling = true)] static extern IntPtr WindowFromPoint(Point p);
        [DllImport("user32.dll", ExactSpelling = true)] static extern IntPtr MonitorFromPoint(Point pt, uint dwFlags = 0);
        [DllImport("user32.dll", ExactSpelling = true)] static extern bool GetWindowRect(IntPtr hWnd, [Out] out RECT lpRect);
        [StructLayout(LayoutKind.Sequential)] struct RECT { public int left, top, right, bottom; }
    }

    static class Wii
    {
        static WiiFinder wf;

        static void MakeCol<T>(DataGridView dgv, string HeaderText, string DataPropertyName, float FillWeight) where T : DataGridViewCell, new()
        {
            DataGridViewColumn res = new DataGridViewColumn(new T());
            res.HeaderText = HeaderText;
            res.DataPropertyName = "Col" + DataPropertyName;
            res.HeaderCell.Style.WrapMode = DataGridViewTriState.False;
            res.SortMode = DataGridViewColumnSortMode.Programmatic;
            res.FillWeight = FillWeight;
            dgv.Columns.Add(res);
        }

        internal static void Setup(MainForm f)
        {
            if (wf != null) return;
            wf = new WiiFinder();

            f.gridMoreWii.AutoGenerateColumns = false;
            f.gridMoreWii.AutoSize = false;
            f.gridMoreWii.DataSource = wf.cl;
            MakeCol<DataGridViewTextBoxCell>(f.gridMoreWii,  "Controller ID", "ID", 0.60f);
            MakeCol<DataGridViewCheckBoxCell>(f.gridMoreWii, "LED 1", "Led1", 0.10f);
            MakeCol<DataGridViewCheckBoxCell>(f.gridMoreWii, "LED 2", "Led2", 0.10f);
            MakeCol<DataGridViewCheckBoxCell>(f.gridMoreWii, "LED 3", "Led3", 0.10f);
            MakeCol<DataGridViewCheckBoxCell>(f.gridMoreWii, "LED 4", "Led4", 0.10f);
            f.gridMoreWii.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            f.gridMoreWii.ClipboardCopyMode = DataGridViewClipboardCopyMode.Disable;

            // This directly modifies the setter when changing a checkbox value before leaving the cell
            f.gridMoreWii.CellContentClick       += (object sender, DataGridViewCellEventArgs e) => { DataGridViewCheckBoxCell dgvcbc = f.gridMoreWii[e.ColumnIndex, e.RowIndex] as DataGridViewCheckBoxCell; if (dgvcbc != null) dgvcbc.Value = dgvcbc.EditedFormattedValue; };
            f.gridMoreWii.CellContentDoubleClick += (object sender, DataGridViewCellEventArgs e) => { DataGridViewCheckBoxCell dgvcbc = f.gridMoreWii[e.ColumnIndex, e.RowIndex] as DataGridViewCheckBoxCell; if (dgvcbc != null) dgvcbc.Value = dgvcbc.EditedFormattedValue; };

            // Find already connected controllers
            WiiUpdateControllerList();

            f.btnMoreWii.Click += (object sender, System.EventArgs e) =>
            {
                if (wf.IsRunning()) wf.Shutdown();
                else wf.Run();
            };
            wf.OnChangeState = (WiiFinder.EState state) =>
            {
                return (!f.IsDisposed && (bool)f.Invoke((Func<bool>) delegate
                {
                    bool done = (!wf.IsRunning() || state == WiiFinder.EState.Found_New_Controller);
                    bool connectedNewDevice = ((done || state == WiiFinder.EState.Removed_Old_Device_Instance) && WiiUpdateControllerList());
                    f.btnMoreWii.Text = (done || state == WiiFinder.EState.Error ? "Connect New Controller" : "Abort Controller Search");
                    f.lblMoreWii.Text = (state == WiiFinder.EState.Error ? "Error: Unable to connect Bluetooth" : "Status: " + state.ToString().Replace('_', ' ') + (state.ToString().Contains("ing") ? "..." : ""));
                    return connectedNewDevice;
                }));
            };
        }

        internal static void Shutdown()
        {
            if (wf != null) wf.Shutdown();
        }

        static bool WiiUpdateControllerList()
        {
            List<string> FoundHIDPaths = WiiFinder.GetConnectedControllers();
            for (int i = wf.cl.Count; i-- > 0;)
            {
                WiiController wc = wf.cl[i];
                foreach (string hp in FoundHIDPaths) if (hp == wc.HIDPath) goto still_here;
                Funcs.UIWii(wc.HIDPath, false);
                wf.cl.RemoveAt(i);
                wf.cl.BroadcastListChanged();
                still_here:;
            }
            int oldCount = wf.cl.Count;
            foreach (string hp in FoundHIDPaths)
            {
                bool known = false;
                foreach (WiiController wc in wf.cl) if (wc.HIDPath == hp) known = true;
                if (known) continue;
                int leds = Funcs.UIWii(hp, true);
                if (leds == 0) continue;
                wf.cl.Add(new WiiController(wf.cl.Count, hp, leds));
                wf.cl.BroadcastListChanged();
            }
            return (wf.cl.Count > oldCount);
        }

        class ControllerList : System.Collections.Generic.List<WiiController>, System.ComponentModel.IBindingList
        {
            public bool AllowEdit                  { get { return true;  } }
            public bool IsSorted                   { get { return false; } }
            public bool SupportsChangeNotification { get { return true;  } }
            public bool SupportsSorting            { get { return false; } }
            public bool SupportsSearching          { get { return false; } }
            public bool AllowNew                   { get { return false; } }
            public bool AllowRemove                { get { return false; } }
            public System.ComponentModel.ListSortDirection SortDirection { get { return System.ComponentModel.ListSortDirection.Ascending; } }
            public System.ComponentModel.PropertyDescriptor SortProperty { get { return null; } }
            public void AddIndex(System.ComponentModel.PropertyDescriptor property) { }
            public object AddNew() { return null; }
            public void ApplySort(System.ComponentModel.PropertyDescriptor property, System.ComponentModel.ListSortDirection direction) { }
            public int Find(System.ComponentModel.PropertyDescriptor property, object key) { return 0; }
            public void RemoveIndex(System.ComponentModel.PropertyDescriptor property) { }
            public void RemoveSort() { }
            public event System.ComponentModel.ListChangedEventHandler ListChanged;
            public void BroadcastListChanged() { if (ListChanged != null) ListChanged(this, new System.ComponentModel.ListChangedEventArgs(System.ComponentModel.ListChangedType.Reset, 0)); }
        }

        class WiiFinder
        {
            internal ControllerList cl = new ControllerList();

            internal static List<string> GetConnectedControllers()
            {
                List<string> foundHIDPaths = new List<string>();
                DeviceInterfaceData devData = new DeviceInterfaceData();
                devData.cbSize = Marshal.SizeOf(devData);
                Guid guid;
                HidD_GetHidGuid(out guid);
                IntPtr hDevInfo = SetupDiGetClassDevsW(ref guid, IntPtr.Zero, IntPtr.Zero, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
                for (uint index = 0, pathLen; SetupDiEnumDeviceInterfaces(hDevInfo, IntPtr.Zero, ref guid, index, ref devData); index++)
                {
                    // Read pathLen first then actual path
                    SetupDiGetDeviceInterfaceDetailW(hDevInfo, ref devData, IntPtr.Zero, 0, out pathLen, IntPtr.Zero);
                    DeviceInterfaceDetailData devDetail = new DeviceInterfaceDetailData();
                    devDetail.cbSize = (uint)(IntPtr.Size == 8 ? 8 : 6); // based on (sizeof(DWORD) + sizeof(wchar[1])) and native struct packing
                    if (!SetupDiGetDeviceInterfaceDetailW(hDevInfo, ref devData, ref devDetail, pathLen, IntPtr.Zero, IntPtr.Zero)) continue;

                    // Vendor and product ids (VID = Nintendo, PID = Wiimote, WUP_PID = Wii U Pro Controller/New Wiimote)
                    const ushort VID = 0x057e, PID = 0x0306, WUP_PID = 0x0330;
                    if (devDetail.DevicePath.IndexOf("57E", StringComparison.OrdinalIgnoreCase) == -1) continue; // VID must be contained

                    // Read hid attributes to check if the connected device is a Wii controller
                    HidD_Attributes attributes = new HidD_Attributes();
                    attributes.Size = Marshal.SizeOf(attributes);
                    IntPtr hHidFile = CreateFileW(devDetail.DevicePath, FileAccess.Read, FileShare.ReadWrite, IntPtr.Zero, FileMode.Open, 0, IntPtr.Zero);
                    if ((HidD_GetAttributes(hHidFile, ref attributes)) && attributes.VendorID == VID && (attributes.ProductID == PID || attributes.ProductID == WUP_PID))
                        foundHIDPaths.Add(devDetail.DevicePath);
                    CloseHandle(hHidFile);
                }
                SetupDiDestroyDeviceInfoList(hDevInfo);
                return foundHIDPaths;
            }

            public enum EState
            {
                None,
                Searching_For_Wii_Controller,
                Removing_Old_Device_Instance,
                Removed_Old_Device_Instance,
                Registering_HID_Service,
                Found_New_Controller,
                Search_Aborted,
                Error,
            }

            public System.Func<EState, bool> OnChangeState;
            EState State;
            System.Threading.Thread Worker = null;
            bool WorkerRunning;

            bool SetState(EState state)
            {
                if (State == state) return false;
                State = state;
                return OnChangeState(state);
            }

            public void Run()
            {
                if (Worker != null) Shutdown(false);
                WorkerRunning = true;
                Worker = new System.Threading.Thread(new System.Threading.ThreadStart(delegate() { this.ThreadRun(); }));
                Worker.Start();
            }

            public bool IsRunning() { return WorkerRunning; }

            public void Shutdown(bool setState = true)
            {
                WorkerRunning = false;
                if (Worker == null) return;
                while (Worker.ThreadState != System.Threading.ThreadState.Stopped) System.Threading.Thread.Sleep(5);
                Worker = null;
                if (setState) SetState(EState.Search_Aborted);
            }

            void ThreadRun()
            {
                BluetoothDeviceSearchParams sp = new BluetoothDeviceSearchParams();
                sp.dwSize = Marshal.SizeOf(typeof(BluetoothDeviceSearchParams));
                sp.fIssueInquiry = sp.fReturnAuthenticated = sp.fReturnConnected = sp.fReturnRemembered = sp.fReturnUnknown = true;
                sp.cTimeoutMultiplier = 1; // 1 ~ 48, increments of 1.28 second
                int loop = 0;
                for (bool continueSearch = true; WorkerRunning && continueSearch;)
                {
                    SetState(EState.Searching_For_Wii_Controller);
                    BluetoothDeviceInfo dev = new BluetoothDeviceInfo();
                    dev.dwSize = Marshal.SizeOf(typeof(BluetoothDeviceInfo));
                    if (((++loop)%5) == 0 && sp.cTimeoutMultiplier < 5) sp.cTimeoutMultiplier++;
                    IntPtr handle = BluetoothFindFirstDevice(ref sp, ref dev);
                    if (handle == IntPtr.Zero)
                    {
                        int lasterror = Marshal.GetLastWin32Error();
                        if (lasterror == ERROR_SUCCESS || lasterror == ERROR_NO_MORE_ITEMS) continue;
                        SetState(EState.Error);
                        break;
                    }
                    for (bool more = true; more && WorkerRunning && continueSearch; more = BluetoothFindNextDevice(handle, ref dev))
                    {
                        if (dev.szName.StartsWith("Nintendo RVL") && !dev.fConnected)
                        {
                            if (dev.fRemembered)
                            {
                                SetState(EState.Removing_Old_Device_Instance);
                                BluetoothRemoveDevice(ref dev.Address);
                                SetState(EState.Removed_Old_Device_Instance);
                            }
                            else
                            {
                                SetState(EState.Registering_HID_Service);
                                bool registerHID = (BluetoothSetServiceState(IntPtr.Zero, ref dev, ref HumanInterfaceDeviceServiceClass_UUID, BLUETOOTH_SERVICE_ENABLE) == ERROR_SUCCESS);
                                bool connectedNewDevice = (registerHID && SetState(EState.Found_New_Controller));
                                if (connectedNewDevice) { continueSearch = false; break; }
                            }
                        }
                        SetState(EState.Searching_For_Wii_Controller);
                    }
                    BluetoothFindDeviceClose(handle);
                }
                WorkerRunning = false;
            }

            [StructLayout(LayoutKind.Sequential)] struct DeviceInterfaceData { public int cbSize; public Guid InterfaceClassGuid; public int Flags; public IntPtr RESERVED; }
            [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode, Pack = 1)] struct DeviceInterfaceDetailData { public UInt32 cbSize; [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)] public string DevicePath; }
            [StructLayout(LayoutKind.Sequential)] struct HidD_Attributes { public int Size; public ushort VendorID; public ushort ProductID; public ushort VersionNumber; }
            [DllImport("hid.dll", ExactSpelling = true)] static extern void HidD_GetHidGuid(out Guid gHid);
            [DllImport("hid.dll", ExactSpelling = true)] static extern bool HidD_GetAttributes(IntPtr HidDeviceObject, ref HidD_Attributes Attributes);
            [DllImport("setupapi.dll", ExactSpelling = true, SetLastError = true                           )] static extern IntPtr SetupDiGetClassDevsW(ref Guid ClassGuid, IntPtr Enumerator, IntPtr hwndParent, uint Flags);
            [DllImport("setupapi.dll", ExactSpelling = true, SetLastError = true, CharSet = CharSet.Unicode)] static extern bool SetupDiEnumDeviceInterfaces(IntPtr hDevInfo, IntPtr devInfo, ref Guid interfaceClassGuid, UInt32 memberIndex, ref DeviceInterfaceData deviceInterfaceData);
            [DllImport("setupapi.dll", ExactSpelling = true, SetLastError = true, CharSet = CharSet.Unicode)] static extern bool SetupDiGetDeviceInterfaceDetailW(IntPtr hDevInfo, ref DeviceInterfaceData deviceInterfaceData, IntPtr deviceInterfaceDetailData, UInt32 deviceInterfaceDetailDataSize, out UInt32 requiredSize, IntPtr deviceInfoData);
            [DllImport("setupapi.dll", ExactSpelling = true, SetLastError = true, CharSet = CharSet.Unicode)] static extern bool SetupDiGetDeviceInterfaceDetailW(IntPtr hDevInfo, ref DeviceInterfaceData deviceInterfaceData, ref DeviceInterfaceDetailData deviceInterfaceDetailData, UInt32 deviceInterfaceDetailDataSize, IntPtr requiredSize, IntPtr deviceInfoData);
            [DllImport("setupapi.dll", ExactSpelling = true, SetLastError = true                           )] static extern bool SetupDiDestroyDeviceInfoList(IntPtr hDevInfo);
            [DllImport("kernel32.dll", ExactSpelling = true, SetLastError = true, CharSet = CharSet.Unicode)] static extern IntPtr CreateFileW(string filename, [MarshalAs(UnmanagedType.U4)] FileAccess access, [MarshalAs(UnmanagedType.U4)] FileShare share, IntPtr securityAttributes, [MarshalAs(UnmanagedType.U4)] FileMode creationDisposition, uint flags, IntPtr template);
            [DllImport("kernel32.dll", ExactSpelling = true, SetLastError = true                           )] static extern bool CloseHandle(IntPtr hObject);

            [StructLayout(LayoutKind.Sequential)] struct SystemTime { public ushort wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds; }
            [StructLayout(LayoutKind.Sequential)] struct BluetoothAddress { public byte byte1, byte2, byte3, byte4, byte5, byte6, _pad1, _pad2; }
            [StructLayout(LayoutKind.Sequential)] struct BluetoothDeviceSearchParams
            {
                public int dwSize;
                public bool fReturnAuthenticated, fReturnRemembered, fReturnUnknown, fReturnConnected, fIssueInquiry;
                public byte cTimeoutMultiplier;
                public IntPtr hRadio;
            }
            [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)] struct BluetoothDeviceInfo
            {
                public int dwSize, padding;
                public BluetoothAddress Address;
                public uint ulClassofDevice;
                public bool fConnected, fRemembered, fAuthenticated;
                public SystemTime stLastSeen, stLastUsed;
                [MarshalAs(UnmanagedType.ByValTStr, SizeConst = BLUETOOTH_MAX_NAME_SIZE)] public string szName;
            }
            [DllImport("irprops.cpl", ExactSpelling = true, SetLastError = true, CharSet = CharSet.Unicode)] static extern IntPtr BluetoothFindFirstDevice(ref BluetoothDeviceSearchParams SearchParams, ref BluetoothDeviceInfo DeviceInfo);
            [DllImport("irprops.cpl", ExactSpelling = true, SetLastError = true, CharSet = CharSet.Unicode)] static extern bool BluetoothFindNextDevice(IntPtr hFind, ref BluetoothDeviceInfo DeviceInfo);
            [DllImport("irprops.cpl", ExactSpelling = true, SetLastError = true, CharSet = CharSet.Unicode)] static extern bool BluetoothFindDeviceClose(IntPtr hFind);
            [DllImport("irprops.cpl", ExactSpelling = true, SetLastError = true, CharSet = CharSet.Unicode)] static extern int BluetoothSetServiceState(IntPtr hRadio, ref BluetoothDeviceInfo DeviceInfo, ref Guid guid, int ServiceFlags);
            [DllImport("irprops.cpl", ExactSpelling = true, SetLastError = true, CharSet = CharSet.Unicode)] static extern int BluetoothRemoveDevice(ref BluetoothAddress Address);
            const int DIGCF_PRESENT = 0x00000002, DIGCF_DEVICEINTERFACE = 0x00000010, BLUETOOTH_MAX_NAME_SIZE = 248, BLUETOOTH_SERVICE_ENABLE = 1, ERROR_SUCCESS = 0, ERROR_NO_MORE_ITEMS = 259;
            static Guid HumanInterfaceDeviceServiceClass_UUID = new Guid(0x00001124, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB);
        }

        class WiiController
        {
            public WiiController(int index, string hidDevicePath, int leds)
            {
                Index = index;
                HIDPath = hidDevicePath;
                LEDs = leds;
            }
            public string HIDPath;
            int Index, LEDs;
            public string ColId { get
            {
                string s = HIDPath;
                if (s.Contains("pid&")) s = s.Substring(s.IndexOf("pid&")+4);
                if (s.Contains("&")) s = s.Substring(s.IndexOf("&")+1);
                if (s.Contains("&")) s = s.Substring(0, s.IndexOf("&"));
                return s;
            }}
            public bool ColLed1 { get { return (LEDs&1)!=0;  } set { SetLed(0, value); } }
            public bool ColLed2 { get { return (LEDs&2)!=0;  } set { SetLed(1, value); } }
            public bool ColLed3 { get { return (LEDs&4)!=0;  } set { SetLed(2, value); } }
            public bool ColLed4 { get { return (LEDs&8)!=0;  } set { SetLed(3, value); } }
            void SetLed(int n, bool val)
            {
                if (Funcs.UIWii(HIDPath, true, (LEDs=(val ? LEDs|(1<<n) : LEDs&~(1<<n)))) == 0)
                    WiiUpdateControllerList();
            }
        }
    }
}
