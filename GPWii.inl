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

int WINAPI UIWii(const wchar_t* hidPath, BOOL on, int LEDs = 0)
{
	#pragma GPLINKER_DLL_EXPORT
	typedef BOOL (WINAPI *HidD_SetOutputReportFN)(HANDLE HidDeviceObject, const void* lpReportBuffer, unsigned int ReportBufferLength);
	static HidD_SetOutputReportFN pHidD_SetOutputReport;
	if (!pHidD_SetOutputReport)
	{
		HMODULE hHidDLL = LoadLibraryA("hid.dll");
		pHidD_SetOutputReport = (HidD_SetOutputReportFN)(hHidDLL == INVALID_HANDLE_VALUE ? NULL : fpGetProcAddress(hHidDLL, "HidD_SetOutputReport"));
	}

	struct Wii
	{
		enum
		{
			REPORT_LENGTH = 22,
			MAX_READ_LENGTH = 32,

			InputReport_Status           = 0x20, /// Status report
			InputReport_ReadData         = 0x21, /// Read data from memory location
			InputReport_OutputReportAck  = 0x22, /// Register write complete
			InputReport_Buttons          = 0x30, /// Button data only
			InputReport_ButtonsAccel     = 0x31, /// Button and accelerometer data
			InputReport_IRAccel          = 0x33, /// IR sensor and accelerometer data
			InputReport_ButtonsExtension = 0x34, /// Button and extension controller data
			InputReport_ExtensionAccel   = 0x35, /// Extension and accelerometer data
			InputReport_IRExtensionAccel = 0x37, /// IR sensor, extension controller and accelerometer data

			OutputReport_LEDs            = 0x11,
			OutputReport_Type            = 0x12,
			OutputReport_IR              = 0x13,
			OutputReport_Status          = 0x15,
			OutputReport_WriteMemory     = 0x16,
			OutputReport_ReadMemory      = 0x17,
			OutputReport_IR2             = 0x1a,

			LEDState_Extension           = 0x02,
			LEDStateShift_LEDs           = 4, // LED 1 ~ 4 is 0x10, 0x20, 0x40, 0x80

			WiiButtons1_Left            = 0x01,
			WiiButtons1_Right           = 0x02,
			WiiButtons1_Down            = 0x04,
			WiiButtons1_Up              = 0x08,
			WiiButtons1_Plus            = 0x10,
			WiiButtons2_Two             = 0x01,
			WiiButtons2_One             = 0x02,
			WiiButtons2_B               = 0x04,
			WiiButtons2_A               = 0x08,
			WiiButtons2_Minus           = 0x10,
			WiiButtons2_Home            = 0x80,

			ExtButtons_Nunchuk_C                   = 0x02,
			ExtButtons_Nunchuk_Z                   = 0x01,
			ExtButtons1_Classic_R        = 0x02,
			ExtButtons1_Classic_Plus     = 0x04,
			ExtButtons1_Classic_Home     = 0x08,
			ExtButtons1_Classic_Minus    = 0x10,
			ExtButtons1_Classic_L        = 0x20,
			ExtButtons1_Classic_Down     = 0x40,
			ExtButtons1_Classic_Right    = 0x80,
			ExtButtons2_Classic_Up       = 0x01,
			ExtButtons2_Classic_Left     = 0x02,
			ExtButtons2_Classic_ZR       = 0x04,
			ExtButtons2_Classic_X        = 0x08,
			ExtButtons2_Classic_A        = 0x10,
			ExtButtons2_Classic_Y        = 0x20,
			ExtButtons2_Classic_B        = 0x40,
			ExtButtons2_Classic_ZL       = 0x80,
			ExtButtons3_Pro_RStick       = 0x01,
			ExtButtons3_Pro_LStick       = 0x02,
			ExtButtons3_Pro_charging     = 0x04,
			ExtButtons3_Pro_usbConnected = 0x08,

			REGISTER_IR                    = 0x04b00030,
			REGISTER_IR_SENSITIVITY_1      = 0x04b00000,
			REGISTER_IR_SENSITIVITY_2      = 0x04b0001a,
			REGISTER_IR_MODE               = 0x04b00033,

			REGISTER_EXTENSION_INIT_1      = 0x04a400f0,
			REGISTER_EXTENSION_INIT_2      = 0x04a400fb,
			REGISTER_EXTENSION_TYPE        = 0x04a400fa,
			REGISTER_EXTENSION_CALIBRATION = 0x04a40020,

			ExtensionType_None                 = 0x00000000, // Wiimote, no extension
			ExtensionType_BalanceBoard         = 0x00A40402, // Balance Board
			ExtensionType_ClassicController    = 0x00A40101, // Wiimote + Classic Controller
			ExtensionType_ClassicControllerPro = 0x01A40101, // Wiimote + Classic Controller Pro
			ExtensionType_Nunchuk              = 0x00A40000, // Wiimote + Nunchuk
			ExtensionType_NunchukB             = 0xFFA40000, // Wiimote + Nunchuk (type 2)
			ExtensionType_ProController        = 0x00A40120, // Wii U Pro Controller
			ExtensionType_MotionPlus           = 0x00A40405, // Wiimote + Motion Plus
			ExtensionType_MotionPlusNunchuk    = 0x00A40505, // Wiimote + Motion Plus + Nunchuk passthrough
			ExtensionType_MotionPlusCC         = 0x00A40705, // Wiimote + Motion Plus + Classic Controller passthrough
			ExtensionType_Guitar               = 0x00A40103,
			ExtensionType_Drums                = 0x01A40103,
			ExtensionType_TaikoDrum            = 0x00A40111,
			ExtensionType_TurnTable            = 0x03A40103,
			ExtensionType_DrawTablet           = 0xFFA40013,
			ExtensionType_FalseState           = 0x01000000, // Seen when reconnecting to a Pro Controller
			ExtensionType_PartiallyInserted    = 0xFFFFFFFF,
		};

		bool AbortRead;
		unsigned int DevNum, HidPathHash;
		HANDLE h, hThread;
		unsigned char BatteryRaw, LEDState, LEDRequest;
		unsigned int ExtensionType;

		struct { unsigned char WiiButtons1, WiiButtons2, ExtXL, ExtYL, ExtXR, ExtYR, ExtTL, ExtTR, ExtButtons1, ExtButtons2, ExtButtons3; } State, StatePrev;

		struct StickCal
		{
			unsigned char Max, Min, Mid;
			unsigned short GetUp(unsigned char v) { if (v > Max) Max = v; return (v > Mid ? (v - Mid) * 0xFFFF / (Max - Mid) : 0); }
			unsigned short GetDn(unsigned char v) { if (v < Min) Min = v; return (v < Mid ? (Mid - v) * 0xFFFF / (Mid - Min) : 0); }
		};
		struct { StickCal XL, YL, XR, YR, TL, TR; } ExtCal;

		void RequestLEDs(int LEDs) { LEDRequest = (unsigned char)LEDs; SetLEDs(0); }
		void SetLEDs(int LEDs) { LEDState = (unsigned char)((LEDState & ~(0xF<<LEDStateShift_LEDs)) | (LEDs<<LEDStateShift_LEDs)); }
		int GetLEDs() { return (LEDState>>LEDStateShift_LEDs); }

		unsigned char GetRumbleBit() { return 0x00; }

		void Run()
		{
			if (!LEDState && !LEDRequest)
			{
				WriteReport(OutputReport_Status);
				ReadUntil(InputReport_Status);
				//WriteReport(OutputReport_IR);WriteReport(OutputReport_IR2);
				if (!GetLEDs()) LEDRequest = (unsigned char)(1 << (DevNum % 4));
			}
			if (LEDRequest)
			{
				if (!WriteReport(OutputReport_LEDs, (unsigned char)(LEDRequest<<LEDStateShift_LEDs))) return;
				SetLEDs(LEDRequest);
				LEDRequest = 0;
			}
			ReadUntil(0xFF);
		}

		bool WriteReport(unsigned char outputReport, unsigned char b1 = 0, unsigned char b2 = 0, unsigned char b3 = 0, unsigned char b4 = 0, unsigned char b5 = 0, unsigned char b6 = 0)
		{
			//WriteLog("WriteReport - %s\n", GetReportName(outputReport));
			unsigned char buf[REPORT_LENGTH];
			buf[0] = outputReport;
			buf[1] = (b1 | GetRumbleBit());
			buf[2] = b2, buf[3] = b3; buf[4] = b4, buf[5] = b5, buf[6] = b6;
			memset(buf+7, 0, sizeof(buf)-7);
			return !!(pHidD_SetOutputReport ? pHidD_SetOutputReport(h, buf, REPORT_LENGTH) : WriteFile(h, buf, REPORT_LENGTH, NULL, NULL));
		}

		void ReadData(int address, short size, unsigned char* readBuf)
		{
			WriteReport(OutputReport_ReadMemory,
				(unsigned char)((address & 0xff000000) >> 24),
				(unsigned char)((address & 0x00ff0000) >> 16),
				(unsigned char)((address & 0x0000ff00) >> 8),
				(unsigned char)(address & 0x000000ff),
				(unsigned char)((size & 0xff00) >> 8),
				(unsigned char)(size & 0xff));
			ReadUntil(InputReport_ReadData, (address & 0xffff), size, readBuf);
		}

		void WriteData(int address, unsigned char write0)
		{
			GPASSERT(6 + 1 <= REPORT_LENGTH);
			WriteReport(OutputReport_WriteMemory,
				(unsigned char)((address & 0xff000000) >> 24),
				(unsigned char)((address & 0x00ff0000) >> 16),
				(unsigned char)((address & 0x0000ff00) >> 8),
				(unsigned char)(address & 0x000000ff),
				1, write0);
			ReadUntil(InputReport_OutputReportAck);
		}

		void ParseButtons(unsigned char* buf)
		{
			State.WiiButtons1 = buf[1];
			State.WiiButtons2 = buf[2];
		}

		void ParseExtension(const unsigned char* data)
		{
			switch (ExtensionType)
			{
				case ExtensionType_ClassicController:
				case ExtensionType_ClassicControllerPro:
					State.ExtXL = (unsigned char)(data[0] & 0x3f);
					State.ExtYL = (unsigned char)(data[1] & 0x3f);
					State.ExtXR = (unsigned char)((data[2] >> 7) | (data[1] & 0xc0) >> 5 | (data[0] & 0xc0) >> 3);
					State.ExtYR = (unsigned char)(data[2] & 0x1f);
					State.ExtTL = (unsigned char)(((data[2] & 0x60) >> 2) | (data[3] >> 5));
					State.ExtTR = (unsigned char)(data[3] & 0x1f);
					State.ExtButtons1 = data[4];
					State.ExtButtons2 = data[5];
					State.ExtButtons3 = 0xFF;
					break;
				case ExtensionType_Nunchuk:
				case ExtensionType_NunchukB:
					State.ExtXL = data[0];
					State.ExtYL = data[1];
					State.ExtButtons1 = (data[5] & ExtButtons_Nunchuk_C ? 0xFF : ~ExtButtons1_Classic_L);
					State.ExtButtons2 = (data[5] & ExtButtons_Nunchuk_Z ? 0xFF : ~ExtButtons2_Classic_ZL);
					State.ExtButtons3 = 0xFF;
					break;
				case ExtensionType_ProController:
					State.ExtButtons1 = data[8];
					State.ExtButtons2 = data[9];
					State.ExtButtons3 = data[10];
					{ int v = ((data[1] << 8) | data[0]); State.ExtXL = ((v < 1023 ? 1023 : (v > 3071 ? 3071 : v)) - 1023) * 0xFF / 2048; }
					{ int v = ((data[5] << 8) | data[4]); State.ExtYL = ((v < 1023 ? 1023 : (v > 3071 ? 3071 : v)) - 1023) * 0xFF / 2048; }
					{ int v = ((data[3] << 8) | data[2]); State.ExtXR = ((v < 1023 ? 1023 : (v > 3071 ? 3071 : v)) - 1023) * 0xFF / 2048; }
					{ int v = ((data[7] << 8) | data[6]); State.ExtYR = ((v < 1023 ? 1023 : (v > 3071 ? 3071 : v)) - 1023) * 0xFF / 2048; }
					break;
			}
		}

		void ReadUntil(unsigned char waitForType, int readAddress = 0, int readSize = 0, unsigned char* readBuf = NULL)
		{
			while (!AbortRead && h)
			{
				unsigned char buf[REPORT_LENGTH];
				if (!ReadFile(h, buf, REPORT_LENGTH, NULL, NULL))
				{
					CloseHandle(h);
					h = NULL;
					WriteLog("Wii - Read failed\n");
					return;
				}
				//WriteLog("ReadReport - %s\n", GetReportName(buf[0]));
				switch (buf[0])
				{
					case InputReport_Status:           //= 0x20, /// Status report
					{
						ParseButtons(buf);
						BatteryRaw = buf[6];
						//mWiimoteState.Battery = (((100.0f * 48.0f * (float)((int)buff[6] / 48.0f))) / 192.0f);

						bool hadExtension = !!(LEDState & LEDState_Extension), haveExtension = !!(buf[3] & LEDState_Extension);
						if (hadExtension != haveExtension)
						{
							memset(&ExtCal, 0, sizeof(ExtCal));
							ExtensionType = ExtensionType_None;
							if (haveExtension)
							{
								unsigned char extBuf[16];
								WriteData(REGISTER_EXTENSION_INIT_1, 0x55);
								WriteData(REGISTER_EXTENSION_INIT_2, 0x00);
								ReadData(REGISTER_EXTENSION_TYPE, 6, extBuf);
								switch (((unsigned int)extBuf[0] << 24) | ((unsigned int)extBuf[2] << 16) | ((unsigned int)extBuf[4]) << 8 | extBuf[5])
								{
									case ExtensionType_ClassicController:
									case ExtensionType_ClassicControllerPro:
										ExtensionType = ExtensionType_ClassicController;
										ReadData(REGISTER_EXTENSION_CALIBRATION, 16, extBuf);
#if 0
										ExtCal.XL.Max = ((extBuf[ 0] >> 2) > 0 ? (extBuf[ 0] >> 2) : 63-5);
										ExtCal.XL.Min = ((extBuf[ 1] >> 2) > 0 ? (extBuf[ 1] >> 2) :  0+5);
										ExtCal.XL.Mid = ((extBuf[ 2] >> 2) > 0 ? (extBuf[ 2] >> 2) : 31);
										ExtCal.YL.Max = ((extBuf[ 3] >> 2) > 0 ? (extBuf[ 3] >> 2) : 63-5);
										ExtCal.YL.Min = ((extBuf[ 4] >> 2) > 0 ? (extBuf[ 4] >> 2) :  0+5);
										ExtCal.YL.Mid = ((extBuf[ 5] >> 2) > 0 ? (extBuf[ 5] >> 2) : 31);
										ExtCal.XR.Max = ((extBuf[ 6] >> 3) > 0 ? (extBuf[ 6] >> 3) : 31-3);
										ExtCal.XR.Min = ((extBuf[ 7] >> 3) > 0 ? (extBuf[ 7] >> 3) :  0+3);
										ExtCal.XR.Mid = ((extBuf[ 8] >> 3) > 0 ? (extBuf[ 8] >> 3) : 15);
										ExtCal.YR.Max = ((extBuf[ 9] >> 3) > 0 ? (extBuf[ 9] >> 3) : 31-3);
										ExtCal.YR.Min = ((extBuf[10] >> 3) > 0 ? (extBuf[10] >> 3) :  0+3);
										ExtCal.YR.Mid = ((extBuf[11] >> 3) > 0 ? (extBuf[11] >> 3) : 15);
#else
										ExtCal.XL.Max = ((extBuf[ 0] >> 2) > 0 ? (extBuf[ 0] >> 2) : 63);
										ExtCal.XL.Min = ((extBuf[ 1] >> 2) > 0 ? (extBuf[ 1] >> 2) :  0);
										ExtCal.XL.Mid = ((extBuf[ 2] >> 2) > 0 ? (extBuf[ 2] >> 2) : 31);
										ExtCal.YL.Max = ((extBuf[ 3] >> 2) > 0 ? (extBuf[ 3] >> 2) : 63);
										ExtCal.YL.Min = ((extBuf[ 4] >> 2) > 0 ? (extBuf[ 4] >> 2) :  0);
										ExtCal.YL.Mid = ((extBuf[ 5] >> 2) > 0 ? (extBuf[ 5] >> 2) : 31);
										ExtCal.XR.Max = ((extBuf[ 6] >> 3) > 0 ? (extBuf[ 6] >> 3) : 31);
										ExtCal.XR.Min = ((extBuf[ 7] >> 3) > 0 ? (extBuf[ 7] >> 3) :  0);
										ExtCal.XR.Mid = ((extBuf[ 8] >> 3) > 0 ? (extBuf[ 8] >> 3) : 15);
										ExtCal.YR.Max = ((extBuf[ 9] >> 3) > 0 ? (extBuf[ 9] >> 3) : 31);
										ExtCal.YR.Min = ((extBuf[10] >> 3) > 0 ? (extBuf[10] >> 3) :  0);
										ExtCal.YR.Mid = ((extBuf[11] >> 3) > 0 ? (extBuf[11] >> 3) : 15);
#endif
										ExtCal.TL.Mid =  0; //(extBuf[12] >> 3) is apparently incorrect
										ExtCal.TL.Max = 31; //(extBuf[14] >> 3) is apparently incorrect
										ExtCal.TL.Mid =  0; //(extBuf[13] >> 3) is apparently incorrect
										ExtCal.TL.Max = 31; //(extBuf[15] >> 3) is apparently incorrect
										break;
									case ExtensionType_Nunchuk:
									case ExtensionType_NunchukB:
										ExtensionType = ExtensionType_Nunchuk;
										ReadData(REGISTER_EXTENSION_CALIBRATION, 16, extBuf);
										ExtCal.XL.Max = extBuf[8];
										ExtCal.XL.Min = extBuf[9];
										ExtCal.XL.Mid = extBuf[10];
										ExtCal.YL.Max = extBuf[11];
										ExtCal.YL.Min = extBuf[12];
										ExtCal.YL.Mid = extBuf[13];
										break;
									case ExtensionType_ProController:
										ExtensionType = ExtensionType_ProController;
										ExtCal.XL.Max = ExtCal.YL.Max = ExtCal.XR.Max = ExtCal.YR.Max = 255;
										ExtCal.XL.Min = ExtCal.YL.Min = ExtCal.XR.Min = ExtCal.YR.Min = 0;
										ExtCal.XL.Mid = ExtCal.YL.Mid = ExtCal.XR.Mid = ExtCal.YR.Mid = 127;
										break;
								}
							}
						}
						State.ExtXL = ExtCal.XL.Mid;
						State.ExtYL = ExtCal.YL.Mid;
						State.ExtXR = ExtCal.XR.Mid;
						State.ExtYR = ExtCal.YR.Mid;
						State.ExtTL = ExtCal.TL.Mid;
						State.ExtTR = ExtCal.TR.Mid;
						State.ExtButtons1 = State.ExtButtons2 = State.ExtButtons3 = 0xFF;
						StatePrev = State;
						WriteReport(OutputReport_Type, 0x00, (ExtensionType == ExtensionType_None ? InputReport_Buttons : InputReport_ButtonsExtension)); //0x04 = continuous data, 0x00 only changing data
						LEDState = buf[3];
						if (waitForType == InputReport_Status) return;
						break;
					}
					case InputReport_ReadData:         //= 0x21, /// Read data from memory location
					{
						ParseButtons(buf);
						GPASSERT(!(buf[3] & 0x08)); //Error reading data from Wiimote: Bytes do not exist.
#if 1
						if (buf[3] & 0x07) { WriteLog("Error reading data from Wiimote: Attempt to read from write-only registers.\n"); }
#else
						GPASSERT(!(buf[3] & 0x07)); //Error reading data from Wiimote: Attempt to read from write-only registers.
#endif
						int size = (buf[3] >> 4) + 1, offset = (buf[4] << 8 | buf[5]);
						if (readBuf)
						{
							if (offset - readAddress + size <= readSize)
								memcpy(readBuf + offset - readAddress, buf + 6, size);
							if (waitForType == InputReport_ReadData && readAddress + readSize == offset + size) return;
						}
						break;
					}
					case InputReport_OutputReportAck:  //= 0x22, /// Register write complete
						if (waitForType == InputReport_OutputReportAck) return;
						break;
					case InputReport_Buttons:          //= 0x30, /// Button data only
						ParseButtons(buf);
						break;
					case InputReport_ButtonsAccel:     //= 0x31, /// Button and accelerometer data
						ParseButtons(buf);
						break;
					case InputReport_IRAccel:          //= 0x33, /// IR sensor and accelerometer data
						ParseButtons(buf);
						break;
					case InputReport_ButtonsExtension: //= 0x34, /// Button and extension controller data
						ParseButtons(buf);
						ParseExtension(buf+3);
						break;
					case InputReport_ExtensionAccel:   //= 0x35, /// Extension and accelerometer data
						ParseButtons(buf);
						ParseExtension(buf+6);
						break;
					case InputReport_IRExtensionAccel: //= 0x37, /// IR sensor, extension controller and accelerometer data
						ParseButtons(buf);
						ParseExtension(buf+16);
						break;
				}
				WriteGPData();
			}
		}

		void WriteGPData()
		{
			for (GPGamepad& gp : pGPData->Gamepads)
			{
				for (unsigned int i = 0; i != _GPIDX_MAX; i++)
				{
					unsigned char o;
					switch (GPIDGetInterface(gp.IDs[i]))
					{
						case GPIDINTERFACE_WII:
							if (GPIDGetDevNum(gp.IDs[i]) != DevNum) continue;
							o = GPIDGetObjNum(gp.IDs[i]);
							switch (o)
							{
								case  0: gp.Vals[i] = ((State.WiiButtons1 & WiiButtons1_Up   ) ? 0xFFFF : 0); continue;
								case  1: gp.Vals[i] = ((State.WiiButtons1 & WiiButtons1_Down ) ? 0xFFFF : 0); continue;
								case  2: gp.Vals[i] = ((State.WiiButtons1 & WiiButtons1_Left ) ? 0xFFFF : 0); continue;
								case  3: gp.Vals[i] = ((State.WiiButtons1 & WiiButtons1_Right) ? 0xFFFF : 0); continue;
								case  4: gp.Vals[i] = ((State.WiiButtons2 & WiiButtons2_A    ) ? 0xFFFF : 0); continue;
								case  5: gp.Vals[i] = ((State.WiiButtons2 & WiiButtons2_B    ) ? 0xFFFF : 0); continue;
								case  6: gp.Vals[i] = ((State.WiiButtons2 & WiiButtons2_One  ) ? 0xFFFF : 0); continue;
								case  7: gp.Vals[i] = ((State.WiiButtons2 & WiiButtons2_Two  ) ? 0xFFFF : 0); continue;
								case  8: gp.Vals[i] = ((State.WiiButtons1 & WiiButtons1_Plus ) ? 0xFFFF : 0); continue;
								case  9: gp.Vals[i] = ((State.WiiButtons2 & WiiButtons2_Minus) ? 0xFFFF : 0); continue;
								case 10: gp.Vals[i] = ((State.WiiButtons2 & WiiButtons2_Home ) ? 0xFFFF : 0); continue;
								case 11: gp.Vals[i] = ExtCal.YL.GetUp(State.ExtYL); continue;
								case 12: gp.Vals[i] = ExtCal.YL.GetDn(State.ExtYL); continue;
								case 13: gp.Vals[i] = ExtCal.XL.GetDn(State.ExtXL); continue;
								case 14: gp.Vals[i] = ExtCal.XL.GetUp(State.ExtXL); continue;
								case 15: gp.Vals[i] = ExtCal.YR.GetUp(State.ExtYR); continue;
								case 16: gp.Vals[i] = ExtCal.YR.GetDn(State.ExtYR); continue;
								case 17: gp.Vals[i] = ExtCal.XR.GetDn(State.ExtXR); continue;
								case 18: gp.Vals[i] = ExtCal.XR.GetUp(State.ExtXR); continue;
								case 19: gp.Vals[i] = ((State.ExtButtons2 & ExtButtons2_Classic_Up   ) ? 0 : 0xFFFF); continue;
								case 20: gp.Vals[i] = ((State.ExtButtons1 & ExtButtons1_Classic_Down ) ? 0 : 0xFFFF); continue;
								case 21: gp.Vals[i] = ((State.ExtButtons2 & ExtButtons2_Classic_Left ) ? 0 : 0xFFFF); continue;
								case 22: gp.Vals[i] = ((State.ExtButtons1 & ExtButtons1_Classic_Right) ? 0 : 0xFFFF); continue;
								case 23: gp.Vals[i] = ((State.ExtButtons1 & ExtButtons1_Classic_Plus ) ? 0 : 0xFFFF); continue;
								case 24: gp.Vals[i] = ((State.ExtButtons1 & ExtButtons1_Classic_Minus) ? 0 : 0xFFFF); continue;
								case 25: gp.Vals[i] = ((State.ExtButtons1 & ExtButtons1_Classic_L    ) ? 0 : 0xFFFF); continue;
								case 26: gp.Vals[i] = ((State.ExtButtons1 & ExtButtons1_Classic_R    ) ? 0 : 0xFFFF); continue;
								case 27: gp.Vals[i] = ((State.ExtButtons2 & ExtButtons2_Classic_ZL   ) ? 0 : 0xFFFF); continue;
								case 28: gp.Vals[i] = ((State.ExtButtons2 & ExtButtons2_Classic_ZR   ) ? 0 : 0xFFFF); continue;
								case 29: gp.Vals[i] = ((State.ExtButtons2 & ExtButtons2_Classic_B    ) ? 0 : 0xFFFF); continue;
								case 30: gp.Vals[i] = ((State.ExtButtons2 & ExtButtons2_Classic_A    ) ? 0 : 0xFFFF); continue;
								case 31: gp.Vals[i] = ((State.ExtButtons2 & ExtButtons2_Classic_Y    ) ? 0 : 0xFFFF); continue;
								case 32: gp.Vals[i] = ((State.ExtButtons2 & ExtButtons2_Classic_X    ) ? 0 : 0xFFFF); continue;
								case 33: gp.Vals[i] = ((State.ExtButtons1 & ExtButtons1_Classic_Home ) ? 0 : 0xFFFF); continue;
								case 34: gp.Vals[i] = ((State.ExtButtons3 & ExtButtons3_Pro_RStick   ) ? 0 : 0xFFFF); continue;
								case 35: gp.Vals[i] = ((State.ExtButtons3 & ExtButtons3_Pro_LStick   ) ? 0 : 0xFFFF); continue;
								case 36: gp.Vals[i] = ExtCal.TL.GetUp(State.ExtTL); continue;
								case 37: gp.Vals[i] = ExtCal.TR.GetUp(State.ExtTR); continue;
							}
							break;
						case GPIDINTERFACE_CAPTURE_NEXT_KEY:
							if (!(CaptureSources & (1 << GPIDINTERFACE_WII))) break;
							o =
								(((State.WiiButtons1 & WiiButtons1_Up    ) && !(StatePrev.WiiButtons1 & WiiButtons1_Up    )) ?  0 :
								(((State.WiiButtons1 & WiiButtons1_Down  ) && !(StatePrev.WiiButtons1 & WiiButtons1_Down  )) ?  1 :
								(((State.WiiButtons1 & WiiButtons1_Left  ) && !(StatePrev.WiiButtons1 & WiiButtons1_Left  )) ?  2 :
								(((State.WiiButtons1 & WiiButtons1_Right ) && !(StatePrev.WiiButtons1 & WiiButtons1_Right )) ?  3 :
								(((State.WiiButtons2 & WiiButtons2_A     ) && !(StatePrev.WiiButtons2 & WiiButtons2_A     )) ?  4 :
								(((State.WiiButtons2 & WiiButtons2_B     ) && !(StatePrev.WiiButtons2 & WiiButtons2_B     )) ?  5 :
								(((State.WiiButtons2 & WiiButtons2_One   ) && !(StatePrev.WiiButtons2 & WiiButtons2_One   )) ?  6 :
								(((State.WiiButtons2 & WiiButtons2_Two   ) && !(StatePrev.WiiButtons2 & WiiButtons2_Two   )) ?  7 :
								(((State.WiiButtons1 & WiiButtons1_Plus  ) && !(StatePrev.WiiButtons1 & WiiButtons1_Plus  )) ?  8 :
								(((State.WiiButtons2 & WiiButtons2_Minus ) && !(StatePrev.WiiButtons2 & WiiButtons2_Minus )) ?  9 :
								(((State.WiiButtons2 & WiiButtons2_Home  ) && !(StatePrev.WiiButtons2 & WiiButtons2_Home  )) ? 10 :
								((ExtCal.YL.GetUp(State.ExtYL) >= 0x8000 && ExtCal.YL.GetUp(StatePrev.ExtYL) < 0x8000) ? 11 :
								((ExtCal.YL.GetDn(State.ExtYL) >= 0x8000 && ExtCal.YL.GetDn(StatePrev.ExtYL) < 0x8000) ? 12 :
								((ExtCal.XL.GetDn(State.ExtXL) >= 0x8000 && ExtCal.XL.GetDn(StatePrev.ExtXL) < 0x8000) ? 13 :
								((ExtCal.XL.GetUp(State.ExtXL) >= 0x8000 && ExtCal.XL.GetUp(StatePrev.ExtXL) < 0x8000) ? 14 :
								((ExtCal.YR.GetUp(State.ExtYR) >= 0x8000 && ExtCal.YR.GetUp(StatePrev.ExtYR) < 0x8000) ? 15 :
								((ExtCal.YR.GetDn(State.ExtYR) >= 0x8000 && ExtCal.YR.GetDn(StatePrev.ExtYR) < 0x8000) ? 16 :
								((ExtCal.XR.GetDn(State.ExtXR) >= 0x8000 && ExtCal.XR.GetDn(StatePrev.ExtXR) < 0x8000) ? 17 :
								((ExtCal.XR.GetUp(State.ExtXR) >= 0x8000 && ExtCal.XR.GetUp(StatePrev.ExtXR) < 0x8000) ? 18 :
								((!(State.ExtButtons2 & ExtButtons2_Classic_Up   ) && (StatePrev.ExtButtons2 & ExtButtons2_Classic_Up   )) ? 19 :
								((!(State.ExtButtons1 & ExtButtons1_Classic_Down ) && (StatePrev.ExtButtons1 & ExtButtons1_Classic_Down )) ? 20 :
								((!(State.ExtButtons2 & ExtButtons2_Classic_Left ) && (StatePrev.ExtButtons2 & ExtButtons2_Classic_Left )) ? 21 :
								((!(State.ExtButtons1 & ExtButtons1_Classic_Right) && (StatePrev.ExtButtons1 & ExtButtons1_Classic_Right)) ? 22 :
								((!(State.ExtButtons1 & ExtButtons1_Classic_Plus ) && (StatePrev.ExtButtons1 & ExtButtons1_Classic_Plus )) ? 23 :
								((!(State.ExtButtons1 & ExtButtons1_Classic_Minus) && (StatePrev.ExtButtons1 & ExtButtons1_Classic_Minus)) ? 24 :
								((!(State.ExtButtons1 & ExtButtons1_Classic_L    ) && (StatePrev.ExtButtons1 & ExtButtons1_Classic_L    )) ? 25 :
								((!(State.ExtButtons1 & ExtButtons1_Classic_R    ) && (StatePrev.ExtButtons1 & ExtButtons1_Classic_R    )) ? 26 :
								((!(State.ExtButtons2 & ExtButtons2_Classic_ZL   ) && (StatePrev.ExtButtons2 & ExtButtons2_Classic_ZL   )) ? 27 :
								((!(State.ExtButtons2 & ExtButtons2_Classic_ZR   ) && (StatePrev.ExtButtons2 & ExtButtons2_Classic_ZR   )) ? 28 :
								((!(State.ExtButtons2 & ExtButtons2_Classic_B    ) && (StatePrev.ExtButtons2 & ExtButtons2_Classic_B    )) ? 29 :
								((!(State.ExtButtons2 & ExtButtons2_Classic_A    ) && (StatePrev.ExtButtons2 & ExtButtons2_Classic_A    )) ? 30 :
								((!(State.ExtButtons2 & ExtButtons2_Classic_Y    ) && (StatePrev.ExtButtons2 & ExtButtons2_Classic_Y    )) ? 31 :
								((!(State.ExtButtons2 & ExtButtons2_Classic_X    ) && (StatePrev.ExtButtons2 & ExtButtons2_Classic_X    )) ? 32 :
								((!(State.ExtButtons1 & ExtButtons1_Classic_Home ) && (StatePrev.ExtButtons1 & ExtButtons1_Classic_Home )) ? 33 :
								((!(State.ExtButtons3 & ExtButtons3_Pro_RStick   ) && (StatePrev.ExtButtons3 & ExtButtons3_Pro_RStick   )) ? 34 :
								((!(State.ExtButtons3 & ExtButtons3_Pro_LStick   ) && (StatePrev.ExtButtons3 & ExtButtons3_Pro_LStick   )) ? 35 :
								((ExtCal.XR.GetUp(State.ExtTL) >= 0x8000 && ExtCal.XR.GetUp(StatePrev.ExtTL) < 0x8000) ? 36 :
								((ExtCal.XR.GetUp(State.ExtTR) >= 0x8000 && ExtCal.XR.GetUp(StatePrev.ExtTR) < 0x8000) ? 37 :
								0xFF))))))))))))))))))))))))))))))))))))));
							if (o == 0xFF) continue;
							gp.IDs[i] = GPIDMake(GPIDINTERFACE_WII, DevNum, o);
							break;
					}
				}
			}
			StatePrev = State;
		}

		static DWORD WINAPI ThreadFunc(Wii* self) { self->Run(); return 0; }

		//static const char* GetReportName(unsigned char n)
		//{
		//	switch (n)
		//	{
		//		case InputReport_Status           : return "InputReport_Status          ";
		//		case InputReport_ReadData         : return "InputReport_ReadData        ";
		//		case InputReport_OutputReportAck  : return "InputReport_OutputReportAck ";
		//		case InputReport_Buttons          : return "InputReport_Buttons         ";
		//		case InputReport_ButtonsAccel     : return "InputReport_ButtonsAccel    ";
		//		case InputReport_IRAccel          : return "InputReport_IRAccel         ";
		//		case InputReport_ButtonsExtension : return "InputReport_ButtonsExtension";
		//		case InputReport_ExtensionAccel   : return "InputReport_ExtensionAccel  ";
		//		case InputReport_IRExtensionAccel : return "InputReport_IRExtensionAccel";
		//		case OutputReport_LEDs            : return "OutputReport_LEDs           ";
		//		case OutputReport_Type            : return "OutputReport_Type           ";
		//		case OutputReport_IR              : return "OutputReport_IR             ";
		//		case OutputReport_Status          : return "OutputReport_Status         ";
		//		case OutputReport_WriteMemory     : return "OutputReport_WriteMemory    ";
		//		case OutputReport_ReadMemory      : return "OutputReport_ReadMemory     ";
		//		case OutputReport_IR2             : return "OutputReport_IR2            ";
		//	}
		//	static char r[] = {'U','N','K','N','O','W','N','X','X','X','\0'};
		//	r[7] = '0'+((n/100)%10);
		//	r[8] = '0'+((n/10)%10);
		//	r[9] = '0'+((n/1)%10);
		//	return r;
		//}
	};

	unsigned int hash = (unsigned int)0x811c9dc5;
	for (const wchar_t* p = hidPath; *p; p++) hash = ((hash * (unsigned int)0x01000193) ^ (unsigned int)*p);

	static GPVector<Wii*> Wiis;
	Wii* w = nullptr;
	for (Wii* it : Wiis) { if (it->HidPathHash == hash) { w = it; break; } }
	if (!w)
	{
		if (!on) return 0;
		w = new Wii;
		memset(w, 0, sizeof(*w));
		w->DevNum = 0; recheck: for (Wii* it : Wiis) { if (it->DevNum == w->DevNum) { w->DevNum++; goto recheck; } }
		w->HidPathHash = hash;
		Wiis.push_back(w);
	}
	else
	{
		stop:
		w->AbortRead = true;
		Sleep(50);
		TerminateThread(w->hThread, 0);
		CloseHandle(w->hThread);
		w->AbortRead = false;
		if (!on)
		{
			if (w->h) CloseHandle(w->h);
			delete w;
			for (Wii*& it : Wiis) { if (it == w) { Wiis.erase(Wiis.begin() + (&it - &Wiis[0])); break; } }
			return 0;
		}
	}
	if (!w->h) w->h = CreateFileW(hidPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (LEDs) { w->RequestLEDs(LEDs); LEDs = 0; }
	w->hThread = CreateThread(0, 0, (DWORD (WINAPI *)(LPVOID))Wii::ThreadFunc, w, 0, 0);
	for (int i = 0; i != 3000/50; i++)
	{
		LEDs = w->GetLEDs();
		if (LEDs || !WaitForSingleObject(w->hThread, 0)) break;
		Sleep(50);
	}
	if (!LEDs)
	{
		WriteLog("Failed to get Wii controller status\n");
		on = FALSE;
		goto stop;
	}
	return LEDs;
}
