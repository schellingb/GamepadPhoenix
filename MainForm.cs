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

using System;
using System.Drawing;
using System.Windows.Forms;

namespace GamepadPhoenix
{
    class MainForm : Form
    {
        protected override void SetVisibleCore(bool value)
        {
            if (value && !IsHandleCreated && WindowState == FormWindowState.Minimized)
            {
                // hide at startup if hidden to tray
                CreateHandle();
                value = false;
            }
            base.SetVisibleCore(value);
        }

        internal MainForm()
        {
            InitializeComponent();
            try { this.Icon = System.Drawing.Icon.ExtractAssociatedIcon(System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName); } catch (Exception) { }
        }

        internal Button btnLaunch;
        internal Button btnA;
        internal Timer timer;
        internal PictureBox picA;
        internal PadControl pad;
        internal PictureBox picB;
        internal PictureBox picX;
        internal PictureBox picY;
        internal PictureBox picL1;
        internal PictureBox picL2;
        internal PictureBox picR1;
        internal PictureBox picR2;
        internal PictureBox picSelect;
        internal PictureBox picStart;
        internal PictureBox picRStickL;
        internal PictureBox picRStickR;
        internal PictureBox picRStickD;
        internal PictureBox picDPadL;
        internal PictureBox picDPadR;
        internal PictureBox picDPadD;
        internal PictureBox picRStick;
        internal TabControl tabs;
        internal PictureBox picRStickU;
        internal Button btnB;
        internal Button btnX;
        internal Button btnY;
        internal Button btnStart;
        internal Button btnSelect;
        internal Button btnL1;
        internal Button btnR1;
        internal Button btnDPadU;
        internal PictureBox picDPadU;
        internal Button btnDPadL;
        internal Button btnDPadR;
        internal Button btnDPadD;
        internal Button btnLStick;
        internal Button btnLStickU;
        internal Button btnLStickL;
        internal Button btnLStickR;
        internal Button btnLStickD;
        internal Button btnRStick;
        internal Button btnRStickU;
        internal Button btnRStickL;
        internal Button btnRStickR;
        internal Button btnRStickD;
        internal Button btnR2;
        internal Button btnL2;
        internal PictureBox picLStickU;
        internal PictureBox picLStick;
        internal PictureBox picLStickL;
        internal PictureBox picLStickR;
        internal PictureBox picLStickD;
        internal Label lblBigFont;
        internal Button btnAssignAll;
        internal Panel panelPad;
        internal ListBox lstLaunchLog;
        internal ComboBox cmbAssignSource;
        internal Button btnSwapRight;
        internal Button btnSwapLeft;
        internal Button btnPresetLoad;
        internal Button btnPresetSave;
        internal Button btnAssignClear;
        internal Button btnAssignCancel;
        internal TextBox txtLaunchTarget;
        internal Button btnLaunchTargetSelect;
        internal Button btnLaunchSave;
        internal ListBox lstLaunchGames;
        internal ToolTip toolTip;
        internal TextBox txtLaunchName;
        internal TextBox txtLaunchArguments;
        internal Button btnLaunchNew;
        internal Button btnLaunchDelete;
        internal DataGridView gridMoreWii;
        internal Button btnMoreWii;
        internal Label lblMoreWii;
        internal Button btnAssignSwitch;
        internal TextBox txtMoreExcludeList;
        internal Button btnLaunchOptions;
        internal NotifyIcon systray;
        internal TextBox txtLaunchStartDir;
        internal Button btnLaunchStartDirSelect;
        internal Button btnLaunchLogClear;
        internal Button btnAssignUndo;
        internal Button btnAssignRedo;
        internal FireLogo fire;
        private GroupBox groupBox2;
        private GroupBox groupBox3;
        private GroupBox groupBox4;
        private Label label4;
        private Label label3;
        private Label label1;
        private Label label7;
        private Label label6;
        private GroupBox groupBox5;
        private GroupBox groupBox6;
        private Label label5;
        private GroupBox groupBox1;
        private TabPage tabPage1;
        private TabPage tabPage2;
        private TabPage tabPage3;
        private TabPage tabPage4;
        private GroupBox groupBox7;
        internal Button btnMoreLicenses;
        internal Button btnMoreGitHub;
        internal Button btnMoreDonate;
        internal Button btnMoreHomepage;
        internal Button btnLaunchPrepare;
        internal Label lblLoading;
        internal Label lblLoadingShadow;
        internal Button btnLaunchRestore;
        internal Button btnLaunchSelectGameEXE;
        internal Button btnMoreResetExcludes;

        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.lstLaunchLog = new System.Windows.Forms.ListBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.lstLaunchGames = new System.Windows.Forms.ListBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnLaunchRestore = new System.Windows.Forms.Button();
            this.txtLaunchName = new System.Windows.Forms.TextBox();
            this.btnLaunchSelectGameEXE = new System.Windows.Forms.Button();
            this.txtLaunchTarget = new System.Windows.Forms.TextBox();
            this.btnLaunchTargetSelect = new System.Windows.Forms.Button();
            this.txtLaunchStartDir = new System.Windows.Forms.TextBox();
            this.btnLaunchStartDirSelect = new System.Windows.Forms.Button();
            this.txtLaunchArguments = new System.Windows.Forms.TextBox();
            this.btnLaunchOptions = new System.Windows.Forms.Button();
            this.btnLaunchSave = new System.Windows.Forms.Button();
            this.btnLaunchDelete = new System.Windows.Forms.Button();
            this.btnLaunchNew = new System.Windows.Forms.Button();
            this.btnLaunchPrepare = new System.Windows.Forms.Button();
            this.btnLaunch = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.btnMoreWii = new System.Windows.Forms.Button();
            this.lblMoreWii = new System.Windows.Forms.Label();
            this.gridMoreWii = new System.Windows.Forms.DataGridView();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.btnMoreResetExcludes = new System.Windows.Forms.Button();
            this.txtMoreExcludeList = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnL2 = new System.Windows.Forms.Button();
            this.btnL1 = new System.Windows.Forms.Button();
            this.btnLStickU = new System.Windows.Forms.Button();
            this.btnLStickL = new System.Windows.Forms.Button();
            this.btnLStickD = new System.Windows.Forms.Button();
            this.btnLStickR = new System.Windows.Forms.Button();
            this.btnLStick = new System.Windows.Forms.Button();
            this.btnSelect = new System.Windows.Forms.Button();
            this.btnDPadU = new System.Windows.Forms.Button();
            this.btnDPadL = new System.Windows.Forms.Button();
            this.btnDPadD = new System.Windows.Forms.Button();
            this.btnDPadR = new System.Windows.Forms.Button();
            this.btnR2 = new System.Windows.Forms.Button();
            this.btnR1 = new System.Windows.Forms.Button();
            this.btnY = new System.Windows.Forms.Button();
            this.btnX = new System.Windows.Forms.Button();
            this.btnA = new System.Windows.Forms.Button();
            this.btnB = new System.Windows.Forms.Button();
            this.btnStart = new System.Windows.Forms.Button();
            this.btnRStickU = new System.Windows.Forms.Button();
            this.btnRStickL = new System.Windows.Forms.Button();
            this.btnRStickD = new System.Windows.Forms.Button();
            this.btnRStickR = new System.Windows.Forms.Button();
            this.btnRStick = new System.Windows.Forms.Button();
            this.picL2 = new System.Windows.Forms.PictureBox();
            this.picL1 = new System.Windows.Forms.PictureBox();
            this.picLStickU = new System.Windows.Forms.PictureBox();
            this.picLStickL = new System.Windows.Forms.PictureBox();
            this.picLStickD = new System.Windows.Forms.PictureBox();
            this.picLStickR = new System.Windows.Forms.PictureBox();
            this.picLStick = new System.Windows.Forms.PictureBox();
            this.picSelect = new System.Windows.Forms.PictureBox();
            this.picDPadU = new System.Windows.Forms.PictureBox();
            this.picDPadL = new System.Windows.Forms.PictureBox();
            this.picDPadD = new System.Windows.Forms.PictureBox();
            this.picDPadR = new System.Windows.Forms.PictureBox();
            this.picR2 = new System.Windows.Forms.PictureBox();
            this.picR1 = new System.Windows.Forms.PictureBox();
            this.picY = new System.Windows.Forms.PictureBox();
            this.picX = new System.Windows.Forms.PictureBox();
            this.picA = new System.Windows.Forms.PictureBox();
            this.picB = new System.Windows.Forms.PictureBox();
            this.picStart = new System.Windows.Forms.PictureBox();
            this.picRStickU = new System.Windows.Forms.PictureBox();
            this.picRStickL = new System.Windows.Forms.PictureBox();
            this.picRStickD = new System.Windows.Forms.PictureBox();
            this.picRStickR = new System.Windows.Forms.PictureBox();
            this.picRStick = new System.Windows.Forms.PictureBox();
            this.btnAssignClear = new System.Windows.Forms.Button();
            this.btnAssignUndo = new System.Windows.Forms.Button();
            this.btnAssignCancel = new System.Windows.Forms.Button();
            this.btnAssignRedo = new System.Windows.Forms.Button();
            this.btnAssignSwitch = new System.Windows.Forms.Button();
            this.lblBigFont = new System.Windows.Forms.Label();
            this.pad = new GamepadPhoenix.PadControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.btnLaunchLogClear = new System.Windows.Forms.Button();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.fire = new GamepadPhoenix.FireLogo();
            this.btnMoreHomepage = new System.Windows.Forms.Button();
            this.btnMoreDonate = new System.Windows.Forms.Button();
            this.btnMoreGitHub = new System.Windows.Forms.Button();
            this.btnMoreLicenses = new System.Windows.Forms.Button();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.tabs = new System.Windows.Forms.TabControl();
            this.btnAssignAll = new System.Windows.Forms.Button();
            this.panelPad = new System.Windows.Forms.Panel();
            this.btnPresetLoad = new System.Windows.Forms.Button();
            this.btnPresetSave = new System.Windows.Forms.Button();
            this.btnSwapLeft = new System.Windows.Forms.Button();
            this.btnSwapRight = new System.Windows.Forms.Button();
            this.cmbAssignSource = new System.Windows.Forms.ComboBox();
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            this.systray = new System.Windows.Forms.NotifyIcon(this.components);
            this.lblLoading = new System.Windows.Forms.Label();
            this.lblLoadingShadow = new System.Windows.Forms.Label();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.gridMoreWii)).BeginInit();
            this.groupBox6.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picL2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picL1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picLStickU)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picLStickL)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picLStickD)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picLStickR)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picLStick)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picSelect)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picDPadU)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picDPadL)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picDPadD)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picDPadR)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picR2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picR1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picA)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picB)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picStart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picRStickU)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picRStickL)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picRStickD)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picRStickR)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picRStick)).BeginInit();
            this.tabPage3.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.tabs.SuspendLayout();
            this.panelPad.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.lstLaunchLog);
            this.groupBox2.Location = new System.Drawing.Point(200, 195);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(751, 246);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Log";
            // 
            // lstLaunchLog
            // 
            this.lstLaunchLog.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lstLaunchLog.HorizontalScrollbar = true;
            this.lstLaunchLog.IntegralHeight = false;
            this.lstLaunchLog.Location = new System.Drawing.Point(6, 15);
            this.lstLaunchLog.Name = "lstLaunchLog";
            this.lstLaunchLog.ScrollAlwaysVisible = true;
            this.lstLaunchLog.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.lstLaunchLog.Size = new System.Drawing.Size(739, 224);
            this.lstLaunchLog.TabIndex = 0;
            // 
            // groupBox3
            // 
            this.groupBox3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.groupBox3.Controls.Add(this.lstLaunchGames);
            this.groupBox3.Location = new System.Drawing.Point(3, 3);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(190, 438);
            this.groupBox3.TabIndex = 0;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Games";
            // 
            // lstLaunchGames
            // 
            this.lstLaunchGames.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lstLaunchGames.FormattingEnabled = true;
            this.lstLaunchGames.IntegralHeight = false;
            this.lstLaunchGames.Location = new System.Drawing.Point(6, 19);
            this.lstLaunchGames.Name = "lstLaunchGames";
            this.lstLaunchGames.Size = new System.Drawing.Size(178, 412);
            this.lstLaunchGames.TabIndex = 0;
            // 
            // groupBox4
            // 
            this.groupBox4.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox4.Controls.Add(this.btnLaunchRestore);
            this.groupBox4.Controls.Add(this.txtLaunchName);
            this.groupBox4.Controls.Add(this.btnLaunchSelectGameEXE);
            this.groupBox4.Controls.Add(this.txtLaunchTarget);
            this.groupBox4.Controls.Add(this.btnLaunchTargetSelect);
            this.groupBox4.Controls.Add(this.txtLaunchStartDir);
            this.groupBox4.Controls.Add(this.btnLaunchStartDirSelect);
            this.groupBox4.Controls.Add(this.txtLaunchArguments);
            this.groupBox4.Controls.Add(this.btnLaunchOptions);
            this.groupBox4.Controls.Add(this.btnLaunchSave);
            this.groupBox4.Controls.Add(this.btnLaunchDelete);
            this.groupBox4.Controls.Add(this.btnLaunchNew);
            this.groupBox4.Controls.Add(this.btnLaunchPrepare);
            this.groupBox4.Controls.Add(this.btnLaunch);
            this.groupBox4.Controls.Add(this.label4);
            this.groupBox4.Controls.Add(this.label3);
            this.groupBox4.Controls.Add(this.label1);
            this.groupBox4.Controls.Add(this.label7);
            this.groupBox4.Controls.Add(this.label6);
            this.groupBox4.Location = new System.Drawing.Point(200, 3);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(751, 192);
            this.groupBox4.TabIndex = 1;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Details";
            // 
            // btnLaunchRestore
            // 
            this.btnLaunchRestore.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnLaunchRestore.Location = new System.Drawing.Point(410, 163);
            this.btnLaunchRestore.Name = "btnLaunchRestore";
            this.btnLaunchRestore.Size = new System.Drawing.Size(100, 23);
            this.btnLaunchRestore.TabIndex = 18;
            this.btnLaunchRestore.Text = "Restore";
            this.btnLaunchRestore.UseVisualStyleBackColor = true;
            // 
            // txtLaunchName
            // 
            this.txtLaunchName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtLaunchName.Location = new System.Drawing.Point(75, 20);
            this.txtLaunchName.Name = "txtLaunchName";
            this.txtLaunchName.Size = new System.Drawing.Size(670, 20);
            this.txtLaunchName.TabIndex = 1;
            // 
            // btnLaunchSelectGameEXE
            // 
            this.btnLaunchSelectGameEXE.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnLaunchSelectGameEXE.Enabled = false;
            this.btnLaunchSelectGameEXE.Location = new System.Drawing.Point(476, 45);
            this.btnLaunchSelectGameEXE.Name = "btnLaunchSelectGameEXE";
            this.btnLaunchSelectGameEXE.Size = new System.Drawing.Size(270, 22);
            this.btnLaunchSelectGameEXE.TabIndex = 4;
            this.btnLaunchSelectGameEXE.Text = "Select Game EXE";
            this.btnLaunchSelectGameEXE.UseVisualStyleBackColor = true;
            this.btnLaunchSelectGameEXE.Visible = false;
            // 
            // txtLaunchTarget
            // 
            this.txtLaunchTarget.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtLaunchTarget.Location = new System.Drawing.Point(75, 46);
            this.txtLaunchTarget.Name = "txtLaunchTarget";
            this.txtLaunchTarget.Size = new System.Drawing.Size(640, 20);
            this.txtLaunchTarget.TabIndex = 3;
            // 
            // btnLaunchTargetSelect
            // 
            this.btnLaunchTargetSelect.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnLaunchTargetSelect.Location = new System.Drawing.Point(720, 45);
            this.btnLaunchTargetSelect.Name = "btnLaunchTargetSelect";
            this.btnLaunchTargetSelect.Size = new System.Drawing.Size(26, 22);
            this.btnLaunchTargetSelect.TabIndex = 4;
            this.btnLaunchTargetSelect.Text = "...";
            this.btnLaunchTargetSelect.UseVisualStyleBackColor = true;
            // 
            // txtLaunchStartDir
            // 
            this.txtLaunchStartDir.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtLaunchStartDir.Location = new System.Drawing.Point(75, 72);
            this.txtLaunchStartDir.Name = "txtLaunchStartDir";
            this.txtLaunchStartDir.Size = new System.Drawing.Size(640, 20);
            this.txtLaunchStartDir.TabIndex = 6;
            // 
            // btnLaunchStartDirSelect
            // 
            this.btnLaunchStartDirSelect.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnLaunchStartDirSelect.Location = new System.Drawing.Point(720, 71);
            this.btnLaunchStartDirSelect.Name = "btnLaunchStartDirSelect";
            this.btnLaunchStartDirSelect.Size = new System.Drawing.Size(26, 22);
            this.btnLaunchStartDirSelect.TabIndex = 7;
            this.btnLaunchStartDirSelect.Text = "...";
            this.btnLaunchStartDirSelect.UseVisualStyleBackColor = true;
            // 
            // txtLaunchArguments
            // 
            this.txtLaunchArguments.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtLaunchArguments.Location = new System.Drawing.Point(75, 98);
            this.txtLaunchArguments.Name = "txtLaunchArguments";
            this.txtLaunchArguments.Size = new System.Drawing.Size(670, 20);
            this.txtLaunchArguments.TabIndex = 9;
            // 
            // btnLaunchOptions
            // 
            this.btnLaunchOptions.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.btnLaunchOptions.Location = new System.Drawing.Point(74, 124);
            this.btnLaunchOptions.Name = "btnLaunchOptions";
            this.btnLaunchOptions.Size = new System.Drawing.Size(672, 22);
            this.btnLaunchOptions.TabIndex = 13;
            this.btnLaunchOptions.Text = "None selected";
            this.btnLaunchOptions.UseVisualStyleBackColor = true;
            // 
            // btnLaunchSave
            // 
            this.btnLaunchSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnLaunchSave.Location = new System.Drawing.Point(5, 163);
            this.btnLaunchSave.Name = "btnLaunchSave";
            this.btnLaunchSave.Size = new System.Drawing.Size(80, 23);
            this.btnLaunchSave.TabIndex = 14;
            this.btnLaunchSave.Text = "Save";
            this.btnLaunchSave.UseVisualStyleBackColor = true;
            // 
            // btnLaunchDelete
            // 
            this.btnLaunchDelete.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnLaunchDelete.Location = new System.Drawing.Point(89, 163);
            this.btnLaunchDelete.Name = "btnLaunchDelete";
            this.btnLaunchDelete.Size = new System.Drawing.Size(80, 23);
            this.btnLaunchDelete.TabIndex = 15;
            this.btnLaunchDelete.Text = "Delete";
            this.btnLaunchDelete.UseVisualStyleBackColor = true;
            // 
            // btnLaunchNew
            // 
            this.btnLaunchNew.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnLaunchNew.Location = new System.Drawing.Point(173, 163);
            this.btnLaunchNew.Name = "btnLaunchNew";
            this.btnLaunchNew.Size = new System.Drawing.Size(80, 23);
            this.btnLaunchNew.TabIndex = 16;
            this.btnLaunchNew.Text = "New";
            this.btnLaunchNew.UseVisualStyleBackColor = true;
            // 
            // btnLaunchPrepare
            // 
            this.btnLaunchPrepare.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnLaunchPrepare.Location = new System.Drawing.Point(304, 163);
            this.btnLaunchPrepare.Name = "btnLaunchPrepare";
            this.btnLaunchPrepare.Size = new System.Drawing.Size(100, 23);
            this.btnLaunchPrepare.TabIndex = 17;
            this.btnLaunchPrepare.Text = "Prepare";
            this.btnLaunchPrepare.UseVisualStyleBackColor = true;
            // 
            // btnLaunch
            // 
            this.btnLaunch.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnLaunch.Location = new System.Drawing.Point(516, 163);
            this.btnLaunch.Name = "btnLaunch";
            this.btnLaunch.Size = new System.Drawing.Size(230, 23);
            this.btnLaunch.TabIndex = 19;
            this.btnLaunch.Text = "Launch";
            this.btnLaunch.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(8, 23);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(64, 13);
            this.label4.TabIndex = 0;
            this.label4.Text = "Name:";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(8, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Target:";
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(8, 75);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(64, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Start In:";
            // 
            // label7
            // 
            this.label7.Location = new System.Drawing.Point(8, 101);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(64, 13);
            this.label7.TabIndex = 8;
            this.label7.Text = "Arguments:";
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(8, 127);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(64, 13);
            this.label6.TabIndex = 12;
            this.label6.Text = "Options:";
            // 
            // groupBox5
            // 
            this.groupBox5.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox5.Controls.Add(this.btnMoreWii);
            this.groupBox5.Controls.Add(this.lblMoreWii);
            this.groupBox5.Controls.Add(this.gridMoreWii);
            this.groupBox5.Location = new System.Drawing.Point(3, 295);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(948, 146);
            this.groupBox5.TabIndex = 2;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Wii Controllers (Bluetooth)";
            // 
            // btnMoreWii
            // 
            this.btnMoreWii.Location = new System.Drawing.Point(5, 18);
            this.btnMoreWii.Name = "btnMoreWii";
            this.btnMoreWii.Size = new System.Drawing.Size(154, 23);
            this.btnMoreWii.TabIndex = 0;
            this.btnMoreWii.Text = "Connect New Controller";
            this.btnMoreWii.UseVisualStyleBackColor = true;
            // 
            // lblMoreWii
            // 
            this.lblMoreWii.AutoSize = true;
            this.lblMoreWii.Location = new System.Drawing.Point(166, 22);
            this.lblMoreWii.Name = "lblMoreWii";
            this.lblMoreWii.Size = new System.Drawing.Size(0, 13);
            this.lblMoreWii.TabIndex = 1;
            // 
            // gridMoreWii
            // 
            this.gridMoreWii.AllowUserToAddRows = false;
            this.gridMoreWii.AllowUserToDeleteRows = false;
            this.gridMoreWii.AllowUserToOrderColumns = true;
            this.gridMoreWii.AllowUserToResizeRows = false;
            this.gridMoreWii.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.gridMoreWii.BackgroundColor = System.Drawing.Color.White;
            this.gridMoreWii.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.gridMoreWii.GridColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.gridMoreWii.Location = new System.Drawing.Point(6, 45);
            this.gridMoreWii.Name = "gridMoreWii";
            this.gridMoreWii.RowHeadersVisible = false;
            this.gridMoreWii.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
            this.gridMoreWii.ShowCellErrors = false;
            this.gridMoreWii.ShowEditingIcon = false;
            this.gridMoreWii.ShowRowErrors = false;
            this.gridMoreWii.Size = new System.Drawing.Size(936, 94);
            this.gridMoreWii.TabIndex = 2;
            // 
            // groupBox6
            // 
            this.groupBox6.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox6.Controls.Add(this.label5);
            this.groupBox6.Controls.Add(this.btnMoreResetExcludes);
            this.groupBox6.Controls.Add(this.txtMoreExcludeList);
            this.groupBox6.Location = new System.Drawing.Point(701, 3);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(250, 292);
            this.groupBox6.TabIndex = 1;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Excluded Process Names";
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(8, 17);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(236, 27);
            this.label5.TabIndex = 0;
            this.label5.Text = "List of .EXE files that won\'t load the Gamepad Phoenix extension. Seperated by ne" +
    "w line.";
            // 
            // btnMoreResetExcludes
            // 
            this.btnMoreResetExcludes.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.btnMoreResetExcludes.Location = new System.Drawing.Point(5, 47);
            this.btnMoreResetExcludes.Name = "btnMoreResetExcludes";
            this.btnMoreResetExcludes.Size = new System.Drawing.Size(240, 23);
            this.btnMoreResetExcludes.TabIndex = 1;
            this.btnMoreResetExcludes.Text = "Reset to Default List";
            this.btnMoreResetExcludes.UseVisualStyleBackColor = true;
            // 
            // txtMoreExcludeList
            // 
            this.txtMoreExcludeList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtMoreExcludeList.Location = new System.Drawing.Point(6, 74);
            this.txtMoreExcludeList.Multiline = true;
            this.txtMoreExcludeList.Name = "txtMoreExcludeList";
            this.txtMoreExcludeList.Size = new System.Drawing.Size(238, 211);
            this.txtMoreExcludeList.TabIndex = 2;
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.btnL2);
            this.groupBox1.Controls.Add(this.btnL1);
            this.groupBox1.Controls.Add(this.btnLStickU);
            this.groupBox1.Controls.Add(this.btnLStickL);
            this.groupBox1.Controls.Add(this.btnLStickD);
            this.groupBox1.Controls.Add(this.btnLStickR);
            this.groupBox1.Controls.Add(this.btnLStick);
            this.groupBox1.Controls.Add(this.btnSelect);
            this.groupBox1.Controls.Add(this.btnDPadU);
            this.groupBox1.Controls.Add(this.btnDPadL);
            this.groupBox1.Controls.Add(this.btnDPadD);
            this.groupBox1.Controls.Add(this.btnDPadR);
            this.groupBox1.Controls.Add(this.btnR2);
            this.groupBox1.Controls.Add(this.btnR1);
            this.groupBox1.Controls.Add(this.btnY);
            this.groupBox1.Controls.Add(this.btnX);
            this.groupBox1.Controls.Add(this.btnA);
            this.groupBox1.Controls.Add(this.btnB);
            this.groupBox1.Controls.Add(this.btnStart);
            this.groupBox1.Controls.Add(this.btnRStickU);
            this.groupBox1.Controls.Add(this.btnRStickL);
            this.groupBox1.Controls.Add(this.btnRStickD);
            this.groupBox1.Controls.Add(this.btnRStickR);
            this.groupBox1.Controls.Add(this.btnRStick);
            this.groupBox1.Controls.Add(this.picL2);
            this.groupBox1.Controls.Add(this.picL1);
            this.groupBox1.Controls.Add(this.picLStickU);
            this.groupBox1.Controls.Add(this.picLStickL);
            this.groupBox1.Controls.Add(this.picLStickD);
            this.groupBox1.Controls.Add(this.picLStickR);
            this.groupBox1.Controls.Add(this.picLStick);
            this.groupBox1.Controls.Add(this.picSelect);
            this.groupBox1.Controls.Add(this.picDPadU);
            this.groupBox1.Controls.Add(this.picDPadL);
            this.groupBox1.Controls.Add(this.picDPadD);
            this.groupBox1.Controls.Add(this.picDPadR);
            this.groupBox1.Controls.Add(this.picR2);
            this.groupBox1.Controls.Add(this.picR1);
            this.groupBox1.Controls.Add(this.picY);
            this.groupBox1.Controls.Add(this.picX);
            this.groupBox1.Controls.Add(this.picA);
            this.groupBox1.Controls.Add(this.picB);
            this.groupBox1.Controls.Add(this.picStart);
            this.groupBox1.Controls.Add(this.picRStickU);
            this.groupBox1.Controls.Add(this.picRStickL);
            this.groupBox1.Controls.Add(this.picRStickD);
            this.groupBox1.Controls.Add(this.picRStickR);
            this.groupBox1.Controls.Add(this.picRStick);
            this.groupBox1.Controls.Add(this.btnAssignClear);
            this.groupBox1.Controls.Add(this.btnAssignUndo);
            this.groupBox1.Controls.Add(this.btnAssignCancel);
            this.groupBox1.Controls.Add(this.btnAssignRedo);
            this.groupBox1.Controls.Add(this.btnAssignSwitch);
            this.groupBox1.Controls.Add(this.lblBigFont);
            this.groupBox1.Controls.Add(this.pad);
            this.groupBox1.Location = new System.Drawing.Point(5, 29);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(948, 412);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            // 
            // btnL2
            // 
            this.btnL2.Location = new System.Drawing.Point(5, 22);
            this.btnL2.Name = "btnL2";
            this.btnL2.Size = new System.Drawing.Size(170, 24);
            this.btnL2.TabIndex = 0;
            this.btnL2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnL2.UseVisualStyleBackColor = true;
            // 
            // btnL1
            // 
            this.btnL1.Location = new System.Drawing.Point(5, 52);
            this.btnL1.Name = "btnL1";
            this.btnL1.Size = new System.Drawing.Size(170, 24);
            this.btnL1.TabIndex = 1;
            this.btnL1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnL1.UseVisualStyleBackColor = true;
            // 
            // btnLStickU
            // 
            this.btnLStickU.Location = new System.Drawing.Point(5, 90);
            this.btnLStickU.Name = "btnLStickU";
            this.btnLStickU.Size = new System.Drawing.Size(170, 24);
            this.btnLStickU.TabIndex = 2;
            this.btnLStickU.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnLStickU.UseVisualStyleBackColor = true;
            // 
            // btnLStickL
            // 
            this.btnLStickL.Location = new System.Drawing.Point(5, 120);
            this.btnLStickL.Name = "btnLStickL";
            this.btnLStickL.Size = new System.Drawing.Size(170, 24);
            this.btnLStickL.TabIndex = 3;
            this.btnLStickL.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnLStickL.UseVisualStyleBackColor = true;
            // 
            // btnLStickD
            // 
            this.btnLStickD.Location = new System.Drawing.Point(5, 150);
            this.btnLStickD.Name = "btnLStickD";
            this.btnLStickD.Size = new System.Drawing.Size(170, 24);
            this.btnLStickD.TabIndex = 4;
            this.btnLStickD.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnLStickD.UseVisualStyleBackColor = true;
            // 
            // btnLStickR
            // 
            this.btnLStickR.Location = new System.Drawing.Point(5, 180);
            this.btnLStickR.Name = "btnLStickR";
            this.btnLStickR.Size = new System.Drawing.Size(170, 24);
            this.btnLStickR.TabIndex = 5;
            this.btnLStickR.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnLStickR.UseVisualStyleBackColor = true;
            // 
            // btnLStick
            // 
            this.btnLStick.Location = new System.Drawing.Point(5, 210);
            this.btnLStick.Name = "btnLStick";
            this.btnLStick.Size = new System.Drawing.Size(170, 24);
            this.btnLStick.TabIndex = 6;
            this.btnLStick.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnLStick.UseVisualStyleBackColor = true;
            // 
            // btnSelect
            // 
            this.btnSelect.Location = new System.Drawing.Point(5, 245);
            this.btnSelect.Name = "btnSelect";
            this.btnSelect.Size = new System.Drawing.Size(170, 24);
            this.btnSelect.TabIndex = 7;
            this.btnSelect.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnSelect.UseVisualStyleBackColor = true;
            // 
            // btnDPadU
            // 
            this.btnDPadU.Location = new System.Drawing.Point(5, 281);
            this.btnDPadU.Name = "btnDPadU";
            this.btnDPadU.Size = new System.Drawing.Size(170, 24);
            this.btnDPadU.TabIndex = 8;
            this.btnDPadU.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnDPadU.UseVisualStyleBackColor = true;
            // 
            // btnDPadL
            // 
            this.btnDPadL.Location = new System.Drawing.Point(5, 311);
            this.btnDPadL.Name = "btnDPadL";
            this.btnDPadL.Size = new System.Drawing.Size(170, 24);
            this.btnDPadL.TabIndex = 9;
            this.btnDPadL.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnDPadL.UseVisualStyleBackColor = true;
            // 
            // btnDPadD
            // 
            this.btnDPadD.Location = new System.Drawing.Point(5, 341);
            this.btnDPadD.Name = "btnDPadD";
            this.btnDPadD.Size = new System.Drawing.Size(170, 24);
            this.btnDPadD.TabIndex = 10;
            this.btnDPadD.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnDPadD.UseVisualStyleBackColor = true;
            // 
            // btnDPadR
            // 
            this.btnDPadR.Location = new System.Drawing.Point(5, 371);
            this.btnDPadR.Name = "btnDPadR";
            this.btnDPadR.Size = new System.Drawing.Size(170, 24);
            this.btnDPadR.TabIndex = 11;
            this.btnDPadR.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.btnDPadR.UseVisualStyleBackColor = true;
            // 
            // btnR2
            // 
            this.btnR2.Location = new System.Drawing.Point(773, 22);
            this.btnR2.Name = "btnR2";
            this.btnR2.Size = new System.Drawing.Size(170, 24);
            this.btnR2.TabIndex = 12;
            this.btnR2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnR2.UseVisualStyleBackColor = true;
            // 
            // btnR1
            // 
            this.btnR1.Location = new System.Drawing.Point(773, 52);
            this.btnR1.Name = "btnR1";
            this.btnR1.Size = new System.Drawing.Size(170, 24);
            this.btnR1.TabIndex = 13;
            this.btnR1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnR1.UseVisualStyleBackColor = true;
            // 
            // btnY
            // 
            this.btnY.Location = new System.Drawing.Point(773, 90);
            this.btnY.Name = "btnY";
            this.btnY.Size = new System.Drawing.Size(170, 24);
            this.btnY.TabIndex = 14;
            this.btnY.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnY.UseVisualStyleBackColor = true;
            // 
            // btnX
            // 
            this.btnX.Location = new System.Drawing.Point(773, 120);
            this.btnX.Name = "btnX";
            this.btnX.Size = new System.Drawing.Size(170, 24);
            this.btnX.TabIndex = 15;
            this.btnX.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnX.UseVisualStyleBackColor = true;
            // 
            // btnA
            // 
            this.btnA.Location = new System.Drawing.Point(773, 150);
            this.btnA.Name = "btnA";
            this.btnA.Size = new System.Drawing.Size(170, 24);
            this.btnA.TabIndex = 16;
            this.btnA.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnA.UseVisualStyleBackColor = true;
            // 
            // btnB
            // 
            this.btnB.Location = new System.Drawing.Point(773, 180);
            this.btnB.Name = "btnB";
            this.btnB.Size = new System.Drawing.Size(170, 24);
            this.btnB.TabIndex = 17;
            this.btnB.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.toolTip.SetToolTip(this.btnB, "GAAAAAA");
            this.btnB.UseVisualStyleBackColor = true;
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(773, 216);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(170, 24);
            this.btnStart.TabIndex = 18;
            this.btnStart.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnStart.UseVisualStyleBackColor = true;
            // 
            // btnRStickU
            // 
            this.btnRStickU.Location = new System.Drawing.Point(773, 252);
            this.btnRStickU.Name = "btnRStickU";
            this.btnRStickU.Size = new System.Drawing.Size(170, 24);
            this.btnRStickU.TabIndex = 19;
            this.btnRStickU.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRStickU.UseVisualStyleBackColor = true;
            // 
            // btnRStickL
            // 
            this.btnRStickL.Location = new System.Drawing.Point(773, 282);
            this.btnRStickL.Name = "btnRStickL";
            this.btnRStickL.Size = new System.Drawing.Size(170, 24);
            this.btnRStickL.TabIndex = 20;
            this.btnRStickL.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRStickL.UseVisualStyleBackColor = true;
            // 
            // btnRStickD
            // 
            this.btnRStickD.Location = new System.Drawing.Point(773, 312);
            this.btnRStickD.Name = "btnRStickD";
            this.btnRStickD.Size = new System.Drawing.Size(170, 24);
            this.btnRStickD.TabIndex = 21;
            this.btnRStickD.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRStickD.UseVisualStyleBackColor = true;
            // 
            // btnRStickR
            // 
            this.btnRStickR.Location = new System.Drawing.Point(773, 342);
            this.btnRStickR.Name = "btnRStickR";
            this.btnRStickR.Size = new System.Drawing.Size(170, 24);
            this.btnRStickR.TabIndex = 22;
            this.btnRStickR.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRStickR.UseVisualStyleBackColor = true;
            // 
            // btnRStick
            // 
            this.btnRStick.Location = new System.Drawing.Point(773, 372);
            this.btnRStick.Name = "btnRStick";
            this.btnRStick.Size = new System.Drawing.Size(170, 24);
            this.btnRStick.TabIndex = 23;
            this.btnRStick.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRStick.UseVisualStyleBackColor = true;
            // 
            // picL2
            // 
            this.picL2.BackColor = System.Drawing.Color.Transparent;
            this.picL2.Image = global::GamepadPhoenix.Resources.L2;
            this.picL2.Location = new System.Drawing.Point(178, 19);
            this.picL2.Name = "picL2";
            this.picL2.Size = new System.Drawing.Size(30, 30);
            this.picL2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picL2.TabIndex = 19;
            this.picL2.TabStop = false;
            // 
            // picL1
            // 
            this.picL1.BackColor = System.Drawing.Color.Transparent;
            this.picL1.Image = global::GamepadPhoenix.Resources.L1;
            this.picL1.Location = new System.Drawing.Point(178, 49);
            this.picL1.Name = "picL1";
            this.picL1.Size = new System.Drawing.Size(30, 30);
            this.picL1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picL1.TabIndex = 18;
            this.picL1.TabStop = false;
            // 
            // picLStickU
            // 
            this.picLStickU.BackColor = System.Drawing.Color.Transparent;
            this.picLStickU.Image = global::GamepadPhoenix.Resources.StickUp;
            this.picLStickU.Location = new System.Drawing.Point(178, 87);
            this.picLStickU.Name = "picLStickU";
            this.picLStickU.Size = new System.Drawing.Size(30, 30);
            this.picLStickU.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picLStickU.TabIndex = 70;
            this.picLStickU.TabStop = false;
            // 
            // picLStickL
            // 
            this.picLStickL.BackColor = System.Drawing.Color.Transparent;
            this.picLStickL.Image = global::GamepadPhoenix.Resources.StickLeft;
            this.picLStickL.Location = new System.Drawing.Point(178, 117);
            this.picLStickL.Name = "picLStickL";
            this.picLStickL.Size = new System.Drawing.Size(30, 30);
            this.picLStickL.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picLStickL.TabIndex = 66;
            this.picLStickL.TabStop = false;
            // 
            // picLStickD
            // 
            this.picLStickD.BackColor = System.Drawing.Color.Transparent;
            this.picLStickD.Image = global::GamepadPhoenix.Resources.StickDown;
            this.picLStickD.Location = new System.Drawing.Point(178, 147);
            this.picLStickD.Name = "picLStickD";
            this.picLStickD.Size = new System.Drawing.Size(30, 30);
            this.picLStickD.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picLStickD.TabIndex = 68;
            this.picLStickD.TabStop = false;
            // 
            // picLStickR
            // 
            this.picLStickR.BackColor = System.Drawing.Color.Transparent;
            this.picLStickR.Image = global::GamepadPhoenix.Resources.StickRight;
            this.picLStickR.Location = new System.Drawing.Point(178, 177);
            this.picLStickR.Name = "picLStickR";
            this.picLStickR.Size = new System.Drawing.Size(30, 30);
            this.picLStickR.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picLStickR.TabIndex = 67;
            this.picLStickR.TabStop = false;
            // 
            // picLStick
            // 
            this.picLStick.BackColor = System.Drawing.Color.Transparent;
            this.picLStick.Image = global::GamepadPhoenix.Resources.StickPress;
            this.picLStick.Location = new System.Drawing.Point(178, 207);
            this.picLStick.Name = "picLStick";
            this.picLStick.Size = new System.Drawing.Size(30, 30);
            this.picLStick.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picLStick.TabIndex = 69;
            this.picLStick.TabStop = false;
            // 
            // picSelect
            // 
            this.picSelect.BackColor = System.Drawing.Color.Transparent;
            this.picSelect.Image = global::GamepadPhoenix.Resources.Select;
            this.picSelect.Location = new System.Drawing.Point(178, 242);
            this.picSelect.Name = "picSelect";
            this.picSelect.Size = new System.Drawing.Size(30, 30);
            this.picSelect.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picSelect.TabIndex = 22;
            this.picSelect.TabStop = false;
            // 
            // picDPadU
            // 
            this.picDPadU.BackColor = System.Drawing.Color.Transparent;
            this.picDPadU.Image = global::GamepadPhoenix.Resources.DPADUp;
            this.picDPadU.Location = new System.Drawing.Point(178, 278);
            this.picDPadU.Name = "picDPadU";
            this.picDPadU.Size = new System.Drawing.Size(30, 30);
            this.picDPadU.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picDPadU.TabIndex = 50;
            this.picDPadU.TabStop = false;
            // 
            // picDPadL
            // 
            this.picDPadL.BackColor = System.Drawing.Color.Transparent;
            this.picDPadL.Image = global::GamepadPhoenix.Resources.DPADLeft;
            this.picDPadL.Location = new System.Drawing.Point(178, 308);
            this.picDPadL.Name = "picDPadL";
            this.picDPadL.Size = new System.Drawing.Size(30, 30);
            this.picDPadL.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picDPadL.TabIndex = 34;
            this.picDPadL.TabStop = false;
            // 
            // picDPadD
            // 
            this.picDPadD.BackColor = System.Drawing.Color.Transparent;
            this.picDPadD.Image = global::GamepadPhoenix.Resources.DPADDown;
            this.picDPadD.Location = new System.Drawing.Point(178, 338);
            this.picDPadD.Name = "picDPadD";
            this.picDPadD.Size = new System.Drawing.Size(30, 30);
            this.picDPadD.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picDPadD.TabIndex = 36;
            this.picDPadD.TabStop = false;
            // 
            // picDPadR
            // 
            this.picDPadR.BackColor = System.Drawing.Color.Transparent;
            this.picDPadR.Image = global::GamepadPhoenix.Resources.DPADRight;
            this.picDPadR.Location = new System.Drawing.Point(178, 368);
            this.picDPadR.Name = "picDPadR";
            this.picDPadR.Size = new System.Drawing.Size(30, 30);
            this.picDPadR.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picDPadR.TabIndex = 35;
            this.picDPadR.TabStop = false;
            // 
            // picR2
            // 
            this.picR2.BackColor = System.Drawing.Color.Transparent;
            this.picR2.Image = global::GamepadPhoenix.Resources.R2;
            this.picR2.Location = new System.Drawing.Point(739, 19);
            this.picR2.Name = "picR2";
            this.picR2.Size = new System.Drawing.Size(30, 30);
            this.picR2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picR2.TabIndex = 21;
            this.picR2.TabStop = false;
            // 
            // picR1
            // 
            this.picR1.BackColor = System.Drawing.Color.Transparent;
            this.picR1.Image = global::GamepadPhoenix.Resources.R1;
            this.picR1.Location = new System.Drawing.Point(739, 49);
            this.picR1.Name = "picR1";
            this.picR1.Size = new System.Drawing.Size(30, 30);
            this.picR1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picR1.TabIndex = 20;
            this.picR1.TabStop = false;
            // 
            // picY
            // 
            this.picY.BackColor = System.Drawing.Color.Transparent;
            this.picY.Image = global::GamepadPhoenix.Resources.Y;
            this.picY.Location = new System.Drawing.Point(739, 87);
            this.picY.Name = "picY";
            this.picY.Size = new System.Drawing.Size(30, 30);
            this.picY.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picY.TabIndex = 17;
            this.picY.TabStop = false;
            // 
            // picX
            // 
            this.picX.BackColor = System.Drawing.Color.Transparent;
            this.picX.Image = global::GamepadPhoenix.Resources.X;
            this.picX.Location = new System.Drawing.Point(739, 117);
            this.picX.Name = "picX";
            this.picX.Size = new System.Drawing.Size(30, 30);
            this.picX.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picX.TabIndex = 16;
            this.picX.TabStop = false;
            // 
            // picA
            // 
            this.picA.BackColor = System.Drawing.Color.Transparent;
            this.picA.Image = global::GamepadPhoenix.Resources.A;
            this.picA.Location = new System.Drawing.Point(739, 147);
            this.picA.Name = "picA";
            this.picA.Size = new System.Drawing.Size(30, 30);
            this.picA.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picA.TabIndex = 11;
            this.picA.TabStop = false;
            // 
            // picB
            // 
            this.picB.BackColor = System.Drawing.Color.Transparent;
            this.picB.Image = global::GamepadPhoenix.Resources.B;
            this.picB.Location = new System.Drawing.Point(739, 177);
            this.picB.Name = "picB";
            this.picB.Size = new System.Drawing.Size(30, 30);
            this.picB.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picB.TabIndex = 15;
            this.picB.TabStop = false;
            // 
            // picStart
            // 
            this.picStart.BackColor = System.Drawing.Color.Transparent;
            this.picStart.Image = global::GamepadPhoenix.Resources.Start;
            this.picStart.Location = new System.Drawing.Point(739, 213);
            this.picStart.Name = "picStart";
            this.picStart.Size = new System.Drawing.Size(30, 30);
            this.picStart.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picStart.TabIndex = 23;
            this.picStart.TabStop = false;
            // 
            // picRStickU
            // 
            this.picRStickU.BackColor = System.Drawing.Color.Transparent;
            this.picRStickU.Image = global::GamepadPhoenix.Resources.StickUp;
            this.picRStickU.Location = new System.Drawing.Point(739, 249);
            this.picRStickU.Name = "picRStickU";
            this.picRStickU.Size = new System.Drawing.Size(30, 30);
            this.picRStickU.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picRStickU.TabIndex = 41;
            this.picRStickU.TabStop = false;
            // 
            // picRStickL
            // 
            this.picRStickL.BackColor = System.Drawing.Color.Transparent;
            this.picRStickL.Image = global::GamepadPhoenix.Resources.StickLeft;
            this.picRStickL.Location = new System.Drawing.Point(739, 279);
            this.picRStickL.Name = "picRStickL";
            this.picRStickL.Size = new System.Drawing.Size(30, 30);
            this.picRStickL.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picRStickL.TabIndex = 27;
            this.picRStickL.TabStop = false;
            // 
            // picRStickD
            // 
            this.picRStickD.BackColor = System.Drawing.Color.Transparent;
            this.picRStickD.Image = global::GamepadPhoenix.Resources.StickDown;
            this.picRStickD.Location = new System.Drawing.Point(739, 309);
            this.picRStickD.Name = "picRStickD";
            this.picRStickD.Size = new System.Drawing.Size(30, 30);
            this.picRStickD.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picRStickD.TabIndex = 29;
            this.picRStickD.TabStop = false;
            // 
            // picRStickR
            // 
            this.picRStickR.BackColor = System.Drawing.Color.Transparent;
            this.picRStickR.Image = global::GamepadPhoenix.Resources.StickRight;
            this.picRStickR.Location = new System.Drawing.Point(739, 339);
            this.picRStickR.Name = "picRStickR";
            this.picRStickR.Size = new System.Drawing.Size(30, 30);
            this.picRStickR.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picRStickR.TabIndex = 28;
            this.picRStickR.TabStop = false;
            // 
            // picRStick
            // 
            this.picRStick.BackColor = System.Drawing.Color.Transparent;
            this.picRStick.Image = global::GamepadPhoenix.Resources.StickPress;
            this.picRStick.Location = new System.Drawing.Point(739, 369);
            this.picRStick.Name = "picRStick";
            this.picRStick.Size = new System.Drawing.Size(30, 30);
            this.picRStick.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picRStick.TabIndex = 37;
            this.picRStick.TabStop = false;
            // 
            // btnAssignClear
            // 
            this.btnAssignClear.Location = new System.Drawing.Point(398, 339);
            this.btnAssignClear.Name = "btnAssignClear";
            this.btnAssignClear.Size = new System.Drawing.Size(60, 23);
            this.btnAssignClear.TabIndex = 24;
            this.btnAssignClear.Text = "Clear";
            this.btnAssignClear.UseVisualStyleBackColor = true;
            this.btnAssignClear.Visible = false;
            // 
            // btnAssignUndo
            // 
            this.btnAssignUndo.Location = new System.Drawing.Point(398, 339);
            this.btnAssignUndo.Name = "btnAssignUndo";
            this.btnAssignUndo.Size = new System.Drawing.Size(60, 23);
            this.btnAssignUndo.TabIndex = 25;
            this.btnAssignUndo.Text = "Undo";
            this.btnAssignUndo.UseVisualStyleBackColor = true;
            this.btnAssignUndo.Visible = false;
            // 
            // btnAssignCancel
            // 
            this.btnAssignCancel.Location = new System.Drawing.Point(494, 339);
            this.btnAssignCancel.Name = "btnAssignCancel";
            this.btnAssignCancel.Size = new System.Drawing.Size(60, 23);
            this.btnAssignCancel.TabIndex = 26;
            this.btnAssignCancel.Text = "Cancel";
            this.btnAssignCancel.UseVisualStyleBackColor = true;
            this.btnAssignCancel.Visible = false;
            // 
            // btnAssignRedo
            // 
            this.btnAssignRedo.Location = new System.Drawing.Point(494, 339);
            this.btnAssignRedo.Name = "btnAssignRedo";
            this.btnAssignRedo.Size = new System.Drawing.Size(60, 23);
            this.btnAssignRedo.TabIndex = 27;
            this.btnAssignRedo.Text = "Redo";
            this.btnAssignRedo.UseVisualStyleBackColor = true;
            this.btnAssignRedo.Visible = false;
            // 
            // btnAssignSwitch
            // 
            this.btnAssignSwitch.Location = new System.Drawing.Point(386, 374);
            this.btnAssignSwitch.Name = "btnAssignSwitch";
            this.btnAssignSwitch.Size = new System.Drawing.Size(180, 23);
            this.btnAssignSwitch.TabIndex = 28;
            this.btnAssignSwitch.Text = "Switch To Similar Device";
            this.btnAssignSwitch.UseVisualStyleBackColor = true;
            // 
            // lblBigFont
            // 
            this.lblBigFont.AutoSize = true;
            this.lblBigFont.Enabled = false;
            this.lblBigFont.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblBigFont.Location = new System.Drawing.Point(381, 161);
            this.lblBigFont.Name = "lblBigFont";
            this.lblBigFont.Size = new System.Drawing.Size(194, 42);
            this.lblBigFont.TabIndex = 30;
            this.lblBigFont.Text = "lblBigFont";
            this.lblBigFont.Visible = false;
            // 
            // pad
            // 
            this.pad.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.pad.Location = new System.Drawing.Point(218, 14);
            this.pad.Name = "pad";
            this.pad.Size = new System.Drawing.Size(512, 390);
            this.pad.TabIndex = 29;
            this.pad.TabStop = false;
            // 
            // tabPage1
            // 
            this.tabPage1.Location = new System.Drawing.Point(4, 23);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Size = new System.Drawing.Size(955, 443);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Controller X        ";
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 23);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Size = new System.Drawing.Size(955, 443);
            this.tabPage2.TabIndex = 1;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.btnLaunchLogClear);
            this.tabPage3.Controls.Add(this.groupBox2);
            this.tabPage3.Controls.Add(this.groupBox4);
            this.tabPage3.Controls.Add(this.groupBox3);
            this.tabPage3.Location = new System.Drawing.Point(4, 23);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(955, 443);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Launch Game        ";
            // 
            // btnLaunchLogClear
            // 
            this.btnLaunchLogClear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnLaunchLogClear.Location = new System.Drawing.Point(896, 415);
            this.btnLaunchLogClear.Name = "btnLaunchLogClear";
            this.btnLaunchLogClear.Size = new System.Drawing.Size(50, 20);
            this.btnLaunchLogClear.TabIndex = 3;
            this.btnLaunchLogClear.Text = "Clear";
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.groupBox5);
            this.tabPage4.Controls.Add(this.groupBox6);
            this.tabPage4.Controls.Add(this.groupBox7);
            this.tabPage4.Location = new System.Drawing.Point(4, 23);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(955, 443);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "More        ";
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.fire);
            this.groupBox7.Controls.Add(this.btnMoreHomepage);
            this.groupBox7.Controls.Add(this.btnMoreDonate);
            this.groupBox7.Controls.Add(this.btnMoreGitHub);
            this.groupBox7.Controls.Add(this.btnMoreLicenses);
            this.groupBox7.Location = new System.Drawing.Point(3, 3);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(691, 292);
            this.groupBox7.TabIndex = 0;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "About";
            // 
            // fire
            // 
            this.fire.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.fire.Location = new System.Drawing.Point(6, 19);
            this.fire.Name = "fire";
            this.fire.Size = new System.Drawing.Size(679, 240);
            this.fire.TabIndex = 1;
            this.fire.TabStop = false;
            // 
            // btnMoreHomepage
            // 
            this.btnMoreHomepage.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnMoreHomepage.Location = new System.Drawing.Point(5, 263);
            this.btnMoreHomepage.Name = "btnMoreHomepage";
            this.btnMoreHomepage.Size = new System.Drawing.Size(168, 23);
            this.btnMoreHomepage.TabIndex = 2;
            this.btnMoreHomepage.Text = "Homepage";
            this.btnMoreHomepage.UseVisualStyleBackColor = true;
            // 
            // btnMoreDonate
            // 
            this.btnMoreDonate.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnMoreDonate.Location = new System.Drawing.Point(176, 263);
            this.btnMoreDonate.Name = "btnMoreDonate";
            this.btnMoreDonate.Size = new System.Drawing.Size(168, 23);
            this.btnMoreDonate.TabIndex = 3;
            this.btnMoreDonate.Text = "Donate";
            this.btnMoreDonate.UseVisualStyleBackColor = true;
            // 
            // btnMoreGitHub
            // 
            this.btnMoreGitHub.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnMoreGitHub.Location = new System.Drawing.Point(347, 263);
            this.btnMoreGitHub.Name = "btnMoreGitHub";
            this.btnMoreGitHub.Size = new System.Drawing.Size(168, 23);
            this.btnMoreGitHub.TabIndex = 4;
            this.btnMoreGitHub.Text = "GitHub";
            this.btnMoreGitHub.UseVisualStyleBackColor = true;
            // 
            // btnMoreLicenses
            // 
            this.btnMoreLicenses.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnMoreLicenses.Location = new System.Drawing.Point(518, 263);
            this.btnMoreLicenses.Name = "btnMoreLicenses";
            this.btnMoreLicenses.Size = new System.Drawing.Size(168, 23);
            this.btnMoreLicenses.TabIndex = 5;
            this.btnMoreLicenses.Text = "Licenses";
            this.btnMoreLicenses.UseVisualStyleBackColor = true;
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Interval = 20;
            // 
            // tabs
            // 
            this.tabs.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabs.Controls.Add(this.tabPage1);
            this.tabs.Controls.Add(this.tabPage2);
            this.tabs.Controls.Add(this.tabPage3);
            this.tabs.Controls.Add(this.tabPage4);
            this.tabs.DrawMode = System.Windows.Forms.TabDrawMode.OwnerDrawFixed;
            this.tabs.ItemSize = new System.Drawing.Size(0, 19);
            this.tabs.Location = new System.Drawing.Point(-2, 1);
            this.tabs.Name = "tabs";
            this.tabs.Padding = new System.Drawing.Point(0, 3);
            this.tabs.SelectedIndex = 0;
            this.tabs.Size = new System.Drawing.Size(963, 470);
            this.tabs.TabIndex = 0;
            // 
            // btnAssignAll
            // 
            this.btnAssignAll.Location = new System.Drawing.Point(803, 6);
            this.btnAssignAll.Name = "btnAssignAll";
            this.btnAssignAll.Size = new System.Drawing.Size(145, 23);
            this.btnAssignAll.TabIndex = 5;
            this.btnAssignAll.Text = "Assign All Buttons/Axes";
            this.btnAssignAll.UseVisualStyleBackColor = true;
            // 
            // panelPad
            // 
            this.panelPad.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panelPad.Controls.Add(this.btnPresetLoad);
            this.panelPad.Controls.Add(this.btnPresetSave);
            this.panelPad.Controls.Add(this.btnSwapLeft);
            this.panelPad.Controls.Add(this.btnSwapRight);
            this.panelPad.Controls.Add(this.cmbAssignSource);
            this.panelPad.Controls.Add(this.btnAssignAll);
            this.panelPad.Controls.Add(this.groupBox1);
            this.panelPad.Location = new System.Drawing.Point(0, 24);
            this.panelPad.Name = "panelPad";
            this.panelPad.Size = new System.Drawing.Size(955, 443);
            this.panelPad.TabIndex = 1;
            // 
            // btnPresetLoad
            // 
            this.btnPresetLoad.Location = new System.Drawing.Point(12, 6);
            this.btnPresetLoad.Name = "btnPresetLoad";
            this.btnPresetLoad.Size = new System.Drawing.Size(160, 23);
            this.btnPresetLoad.TabIndex = 0;
            this.btnPresetLoad.Text = "Load Preset";
            this.btnPresetLoad.UseVisualStyleBackColor = true;
            // 
            // btnPresetSave
            // 
            this.btnPresetSave.Location = new System.Drawing.Point(178, 6);
            this.btnPresetSave.Name = "btnPresetSave";
            this.btnPresetSave.Size = new System.Drawing.Size(160, 23);
            this.btnPresetSave.TabIndex = 1;
            this.btnPresetSave.Text = "Save Preset";
            this.btnPresetSave.UseVisualStyleBackColor = true;
            // 
            // btnSwapLeft
            // 
            this.btnSwapLeft.Location = new System.Drawing.Point(411, 6);
            this.btnSwapLeft.Name = "btnSwapLeft";
            this.btnSwapLeft.Size = new System.Drawing.Size(65, 23);
            this.btnSwapLeft.TabIndex = 2;
            this.btnSwapLeft.Text = "<- Swap";
            this.btnSwapLeft.UseVisualStyleBackColor = true;
            // 
            // btnSwapRight
            // 
            this.btnSwapRight.Location = new System.Drawing.Point(482, 6);
            this.btnSwapRight.Name = "btnSwapRight";
            this.btnSwapRight.Size = new System.Drawing.Size(65, 23);
            this.btnSwapRight.TabIndex = 3;
            this.btnSwapRight.Text = "Swap ->";
            this.btnSwapRight.UseVisualStyleBackColor = true;
            // 
            // cmbAssignSource
            // 
            this.cmbAssignSource.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbAssignSource.ItemHeight = 13;
            this.cmbAssignSource.Items.AddRange(new object[] {
            "Assign from any source",
            "Assign only from XInput",
            "Assign only from DirectInput",
            "Assign only from Wii Controllers"});
            this.cmbAssignSource.Location = new System.Drawing.Point(621, 7);
            this.cmbAssignSource.Name = "cmbAssignSource";
            this.cmbAssignSource.Size = new System.Drawing.Size(175, 21);
            this.cmbAssignSource.TabIndex = 4;
            // 
            // systray
            // 
            this.systray.Visible = true;
            // 
            // lblLoading
            // 
            this.lblLoading.BackColor = System.Drawing.SystemColors.Info;
            this.lblLoading.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lblLoading.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblLoading.Location = new System.Drawing.Point(32, 93);
            this.lblLoading.Name = "lblLoading";
            this.lblLoading.Size = new System.Drawing.Size(893, 227);
            this.lblLoading.TabIndex = 31;
            this.lblLoading.Text = "Loading Game ...";
            this.lblLoading.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lblLoading.Visible = false;
            // 
            // lblLoadingShadow
            // 
            this.lblLoadingShadow.BackColor = System.Drawing.SystemColors.WindowFrame;
            this.lblLoadingShadow.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblLoadingShadow.Location = new System.Drawing.Point(43, 102);
            this.lblLoadingShadow.Name = "lblLoadingShadow";
            this.lblLoadingShadow.Size = new System.Drawing.Size(893, 227);
            this.lblLoadingShadow.TabIndex = 32;
            this.lblLoadingShadow.Visible = false;
            // 
            // MainForm
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(958, 469);
            this.Controls.Add(this.lblLoading);
            this.Controls.Add(this.lblLoadingShadow);
            this.Controls.Add(this.panelPad);
            this.Controls.Add(this.tabs);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.Text = "GamePad Phoenix";
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.gridMoreWii)).EndInit();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picL2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picL1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picLStickU)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picLStickL)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picLStickD)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picLStickR)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picLStick)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picSelect)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picDPadU)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picDPadL)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picDPadD)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picDPadR)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picR2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picR1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picA)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picB)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picStart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picRStickU)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picRStickL)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picRStickD)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picRStickR)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picRStick)).EndInit();
            this.tabPage3.ResumeLayout(false);
            this.tabPage4.ResumeLayout(false);
            this.groupBox7.ResumeLayout(false);
            this.tabs.ResumeLayout(false);
            this.panelPad.ResumeLayout(false);
            this.ResumeLayout(false);

            }

        #endregion
    }

    internal class PadControl : Control
    {
        protected BufferedGraphics gb;

        public PadControl() // needs public for designer
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.UserPaint | ControlStyles.DoubleBuffer, true);
        }

        protected override void OnResize(EventArgs e)
        {
            if (!DesignMode)
                using (Graphics graphics = CreateGraphics())
                    gb = BufferedGraphicsManager.Current.Allocate(graphics, ClientRectangle);
            base.OnResize(e);
        }

        protected override void OnPaintBackground(PaintEventArgs e)
        {
            if (gb == null) base.OnPaintBackground(e);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            if (gb == null) { base.OnPaint(e); return; }
            GUI.RenderPad(gb.Graphics);
            gb.Render(e.Graphics);
        }
    }

    internal class FireLogo : PadControl
    {
        const int W = 68, H = 48, WH = W*H;
        byte[] buf = new byte[WH];
        Random rnd = new Random();
        Brush[] bs = new Brush[6];

        void Simulate()
        {
            for (int i = W+1; i != WH; i++)
            {
                int p = buf[i], decay = ((rnd.Next()%2)), j = i-W-decay;
                if (j >= 0 && j < WH) buf[j] = (p > decay ? (byte)(p - decay) : (byte)0);
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            if (gb == null) { base.OnPaint(e); return; }
            if (buf[WH-1] == 0)
            {
                Color[] cols = new Color[6] { SystemColors.Control, Color.Yellow, Color.Gold, Color.Orange, Color.OrangeRed, Color.Red };
                for (int i = 0; i != bs.Length; i++) bs[i] = new SolidBrush(Color.FromArgb((int)(cols[i].R*.5 + SystemColors.Control.R*.5), (int)(cols[i].G*.5 + SystemColors.Control.G*.5), (int)(cols[i].B*.5 + SystemColors.Control.B*.5)));
                for (int i = 0; i != W; i++) buf[(H-1)*W+i] = 25;
                for (int i = 0; i != 500; i++) Simulate();
            }
            Simulate();

            Graphics g = gb.Graphics;
            float sx = ClientSize.Width / (float)W, sy = ClientSize.Height / (float)H, fy = 0, fx;
            for (int y = 0, j = 0, x; y < H; y++, fy += sy)
                for (x = 0, fx = 0; x < W; x++, fx += sx)
                    g.FillRectangle(bs[buf[j++]/5], fx, fy, sx, sy);

            GUI.RenderAbout(this);
            gb.Render(e.Graphics);
        }

        internal void DrawText(Font fnt, string str, int y, Brush brush, int t = 1)
        {
            Graphics g = gb.Graphics;
            var sz = g.MeasureString(str, fnt);
            int x = (int)((g.VisibleClipBounds.Width - sz.Width) / 2);
            for (int i = 0; i != 9; i++)
                g.DrawString(str, fnt, Brushes.Black, x - t + (i / 3) * t, y - t + (i % 3) * t);
            g.DrawString(str, fnt, brush, x, y);
        }
    }
}
