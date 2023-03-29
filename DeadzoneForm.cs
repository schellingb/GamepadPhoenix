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

using System;
using System.Drawing;
using System.Windows.Forms;

namespace GamepadPhoenix
{
    public class DeadzoneForm : Form
    {
        public DeadzoneForm()
        {
            InitializeComponent();
        }

        internal Timer timer;
        internal DeadzoneControl deadzoneControl;
        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private Label label5;
        private Label label6;
        internal TrackBar trkLeftDeadzone;
        internal TrackBar trkLeftLimit;
        internal TrackBar trkLeftAnti;
        internal TrackBar trkLeftSens;
        internal TrackBar trkLeftShiftH;
        internal TrackBar trkLeftShiftV;
        internal TrackBar trkRightDeadzone;
        internal TrackBar trkRightLimit;
        internal TrackBar trkRightAnti;
        internal TrackBar trkRightSens;
        internal TrackBar trkRightShiftH;
        internal TrackBar trkRightShiftV;
        private Label label7;
        private Label label8;
        private Label label9;
        private Label label10;
        private Label label11;
        private Label label12;
        internal NumericUpDown numLeftDeadzone;
        internal NumericUpDown numLeftLimit;
        internal NumericUpDown numLeftAnti;
        internal NumericUpDown numLeftSens;
        internal NumericUpDown numLeftShiftH;
        internal NumericUpDown numLeftShiftV;
        internal NumericUpDown numRightShiftV;
        internal NumericUpDown numRightShiftH;
        internal NumericUpDown numRightSens;
        internal NumericUpDown numRightAnti;
        internal NumericUpDown numRightLimit;
        internal NumericUpDown numRightDeadzone;
        internal Button btnOK;
        internal Button btnReset;

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
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.trkLeftDeadzone = new System.Windows.Forms.TrackBar();
            this.trkLeftLimit = new System.Windows.Forms.TrackBar();
            this.trkLeftAnti = new System.Windows.Forms.TrackBar();
            this.trkLeftSens = new System.Windows.Forms.TrackBar();
            this.trkLeftShiftH = new System.Windows.Forms.TrackBar();
            this.trkLeftShiftV = new System.Windows.Forms.TrackBar();
            this.trkRightShiftV = new System.Windows.Forms.TrackBar();
            this.trkRightShiftH = new System.Windows.Forms.TrackBar();
            this.trkRightSens = new System.Windows.Forms.TrackBar();
            this.trkRightAnti = new System.Windows.Forms.TrackBar();
            this.trkRightLimit = new System.Windows.Forms.TrackBar();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.trkRightDeadzone = new System.Windows.Forms.TrackBar();
            this.numLeftDeadzone = new System.Windows.Forms.NumericUpDown();
            this.numLeftLimit = new System.Windows.Forms.NumericUpDown();
            this.numLeftAnti = new System.Windows.Forms.NumericUpDown();
            this.numLeftSens = new System.Windows.Forms.NumericUpDown();
            this.numLeftShiftH = new System.Windows.Forms.NumericUpDown();
            this.numLeftShiftV = new System.Windows.Forms.NumericUpDown();
            this.numRightShiftV = new System.Windows.Forms.NumericUpDown();
            this.numRightShiftH = new System.Windows.Forms.NumericUpDown();
            this.numRightSens = new System.Windows.Forms.NumericUpDown();
            this.numRightAnti = new System.Windows.Forms.NumericUpDown();
            this.numRightLimit = new System.Windows.Forms.NumericUpDown();
            this.numRightDeadzone = new System.Windows.Forms.NumericUpDown();
            this.btnOK = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.deadzoneControl = new GamepadPhoenix.DeadzoneControl();
            ((System.ComponentModel.ISupportInitialize)(this.trkLeftDeadzone)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkLeftLimit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkLeftAnti)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkLeftSens)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkLeftShiftH)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkLeftShiftV)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkRightShiftV)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkRightShiftH)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkRightSens)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkRightAnti)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkRightLimit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkRightDeadzone)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLeftDeadzone)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLeftLimit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLeftAnti)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLeftSens)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLeftShiftH)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLeftShiftV)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRightShiftV)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRightShiftH)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRightSens)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRightAnti)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRightLimit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRightDeadzone)).BeginInit();
            this.SuspendLayout();
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Interval = 20;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 195);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(56, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Deadzone";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 221);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(51, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Max Limit";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 247);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(77, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Anti-Deadzone";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 273);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(54, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Sensitivity";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 299);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(78, 13);
            this.label5.TabIndex = 14;
            this.label5.Text = "Shift Horizontal";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 325);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(63, 13);
            this.label6.TabIndex = 17;
            this.label6.Text = "ShiftVertical";
            // 
            // trkLeftDeadzone
            // 
            this.trkLeftDeadzone.AutoSize = false;
            this.trkLeftDeadzone.Location = new System.Drawing.Point(99, 190);
            this.trkLeftDeadzone.Maximum = 100;
            this.trkLeftDeadzone.Name = "trkLeftDeadzone";
            this.trkLeftDeadzone.Size = new System.Drawing.Size(200, 26);
            this.trkLeftDeadzone.TabIndex = 3;
            this.trkLeftDeadzone.TickFrequency = 5;
            // 
            // trkLeftLimit
            // 
            this.trkLeftLimit.AutoSize = false;
            this.trkLeftLimit.Location = new System.Drawing.Point(99, 216);
            this.trkLeftLimit.Maximum = 100;
            this.trkLeftLimit.Name = "trkLeftLimit";
            this.trkLeftLimit.Size = new System.Drawing.Size(200, 26);
            this.trkLeftLimit.TabIndex = 6;
            this.trkLeftLimit.TickFrequency = 5;
            // 
            // trkLeftAnti
            // 
            this.trkLeftAnti.AutoSize = false;
            this.trkLeftAnti.Location = new System.Drawing.Point(99, 242);
            this.trkLeftAnti.Maximum = 100;
            this.trkLeftAnti.Name = "trkLeftAnti";
            this.trkLeftAnti.Size = new System.Drawing.Size(200, 26);
            this.trkLeftAnti.TabIndex = 9;
            this.trkLeftAnti.TickFrequency = 5;
            // 
            // trkLeftSens
            // 
            this.trkLeftSens.AutoSize = false;
            this.trkLeftSens.Location = new System.Drawing.Point(99, 268);
            this.trkLeftSens.Maximum = 100;
            this.trkLeftSens.Minimum = -100;
            this.trkLeftSens.Name = "trkLeftSens";
            this.trkLeftSens.Size = new System.Drawing.Size(200, 26);
            this.trkLeftSens.TabIndex = 12;
            this.trkLeftSens.TickFrequency = 5;
            // 
            // trkLeftShiftH
            // 
            this.trkLeftShiftH.AutoSize = false;
            this.trkLeftShiftH.Location = new System.Drawing.Point(99, 294);
            this.trkLeftShiftH.Maximum = 100;
            this.trkLeftShiftH.Minimum = -100;
            this.trkLeftShiftH.Name = "trkLeftShiftH";
            this.trkLeftShiftH.Size = new System.Drawing.Size(200, 26);
            this.trkLeftShiftH.TabIndex = 15;
            this.trkLeftShiftH.TickFrequency = 5;
            // 
            // trkLeftShiftV
            // 
            this.trkLeftShiftV.AutoSize = false;
            this.trkLeftShiftV.Location = new System.Drawing.Point(99, 320);
            this.trkLeftShiftV.Maximum = 100;
            this.trkLeftShiftV.Minimum = -100;
            this.trkLeftShiftV.Name = "trkLeftShiftV";
            this.trkLeftShiftV.Size = new System.Drawing.Size(200, 26);
            this.trkLeftShiftV.TabIndex = 18;
            this.trkLeftShiftV.TickFrequency = 5;
            // 
            // trkRightShiftV
            // 
            this.trkRightShiftV.AutoSize = false;
            this.trkRightShiftV.Location = new System.Drawing.Point(452, 320);
            this.trkRightShiftV.Maximum = 100;
            this.trkRightShiftV.Minimum = -100;
            this.trkRightShiftV.Name = "trkRightShiftV";
            this.trkRightShiftV.Size = new System.Drawing.Size(200, 26);
            this.trkRightShiftV.TabIndex = 36;
            this.trkRightShiftV.TickFrequency = 5;
            // 
            // trkRightShiftH
            // 
            this.trkRightShiftH.AutoSize = false;
            this.trkRightShiftH.Location = new System.Drawing.Point(452, 294);
            this.trkRightShiftH.Maximum = 100;
            this.trkRightShiftH.Minimum = -100;
            this.trkRightShiftH.Name = "trkRightShiftH";
            this.trkRightShiftH.Size = new System.Drawing.Size(200, 26);
            this.trkRightShiftH.TabIndex = 33;
            this.trkRightShiftH.TickFrequency = 5;
            // 
            // trkRightSens
            // 
            this.trkRightSens.AutoSize = false;
            this.trkRightSens.Location = new System.Drawing.Point(452, 268);
            this.trkRightSens.Maximum = 100;
            this.trkRightSens.Minimum = -100;
            this.trkRightSens.Name = "trkRightSens";
            this.trkRightSens.Size = new System.Drawing.Size(200, 26);
            this.trkRightSens.TabIndex = 30;
            this.trkRightSens.TickFrequency = 5;
            // 
            // trkRightAnti
            // 
            this.trkRightAnti.AutoSize = false;
            this.trkRightAnti.Location = new System.Drawing.Point(452, 242);
            this.trkRightAnti.Maximum = 100;
            this.trkRightAnti.Name = "trkRightAnti";
            this.trkRightAnti.Size = new System.Drawing.Size(200, 26);
            this.trkRightAnti.TabIndex = 27;
            this.trkRightAnti.TickFrequency = 5;
            // 
            // trkRightLimit
            // 
            this.trkRightLimit.AutoSize = false;
            this.trkRightLimit.Location = new System.Drawing.Point(452, 216);
            this.trkRightLimit.Maximum = 100;
            this.trkRightLimit.Name = "trkRightLimit";
            this.trkRightLimit.Size = new System.Drawing.Size(200, 26);
            this.trkRightLimit.TabIndex = 24;
            this.trkRightLimit.TickFrequency = 5;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(365, 325);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(63, 13);
            this.label7.TabIndex = 35;
            this.label7.Text = "ShiftVertical";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(365, 299);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(78, 13);
            this.label8.TabIndex = 32;
            this.label8.Text = "Shift Horizontal";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(365, 273);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(54, 13);
            this.label9.TabIndex = 29;
            this.label9.Text = "Sensitivity";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(365, 247);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(77, 13);
            this.label10.TabIndex = 26;
            this.label10.Text = "Anti-Deadzone";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(365, 221);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(51, 13);
            this.label11.TabIndex = 23;
            this.label11.Text = "Max Limit";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(365, 195);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(56, 13);
            this.label12.TabIndex = 20;
            this.label12.Text = "Deadzone";
            // 
            // trkRightDeadzone
            // 
            this.trkRightDeadzone.AutoSize = false;
            this.trkRightDeadzone.Location = new System.Drawing.Point(452, 190);
            this.trkRightDeadzone.Maximum = 100;
            this.trkRightDeadzone.Name = "trkRightDeadzone";
            this.trkRightDeadzone.Size = new System.Drawing.Size(200, 26);
            this.trkRightDeadzone.TabIndex = 21;
            this.trkRightDeadzone.TickFrequency = 5;
            // 
            // numLeftDeadzone
            // 
            this.numLeftDeadzone.Location = new System.Drawing.Point(300, 192);
            this.numLeftDeadzone.Name = "numLeftDeadzone";
            this.numLeftDeadzone.Size = new System.Drawing.Size(42, 20);
            this.numLeftDeadzone.TabIndex = 4;
            // 
            // numLeftLimit
            // 
            this.numLeftLimit.Location = new System.Drawing.Point(300, 218);
            this.numLeftLimit.Name = "numLeftLimit";
            this.numLeftLimit.Size = new System.Drawing.Size(42, 20);
            this.numLeftLimit.TabIndex = 7;
            // 
            // numLeftAnti
            // 
            this.numLeftAnti.Location = new System.Drawing.Point(300, 244);
            this.numLeftAnti.Name = "numLeftAnti";
            this.numLeftAnti.Size = new System.Drawing.Size(42, 20);
            this.numLeftAnti.TabIndex = 10;
            // 
            // numLeftSens
            // 
            this.numLeftSens.Location = new System.Drawing.Point(300, 270);
            this.numLeftSens.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numLeftSens.Name = "numLeftSens";
            this.numLeftSens.Size = new System.Drawing.Size(42, 20);
            this.numLeftSens.TabIndex = 13;
            // 
            // numLeftShiftH
            // 
            this.numLeftShiftH.Location = new System.Drawing.Point(300, 296);
            this.numLeftShiftH.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numLeftShiftH.Name = "numLeftShiftH";
            this.numLeftShiftH.Size = new System.Drawing.Size(42, 20);
            this.numLeftShiftH.TabIndex = 16;
            // 
            // numLeftShiftV
            // 
            this.numLeftShiftV.Location = new System.Drawing.Point(300, 322);
            this.numLeftShiftV.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numLeftShiftV.Name = "numLeftShiftV";
            this.numLeftShiftV.Size = new System.Drawing.Size(42, 20);
            this.numLeftShiftV.TabIndex = 19;
            // 
            // numRightShiftV
            // 
            this.numRightShiftV.Location = new System.Drawing.Point(655, 322);
            this.numRightShiftV.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numRightShiftV.Name = "numRightShiftV";
            this.numRightShiftV.Size = new System.Drawing.Size(42, 20);
            this.numRightShiftV.TabIndex = 37;
            // 
            // numRightShiftH
            // 
            this.numRightShiftH.Location = new System.Drawing.Point(655, 296);
            this.numRightShiftH.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numRightShiftH.Name = "numRightShiftH";
            this.numRightShiftH.Size = new System.Drawing.Size(42, 20);
            this.numRightShiftH.TabIndex = 34;
            // 
            // numRightSens
            // 
            this.numRightSens.Location = new System.Drawing.Point(655, 270);
            this.numRightSens.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numRightSens.Name = "numRightSens";
            this.numRightSens.Size = new System.Drawing.Size(42, 20);
            this.numRightSens.TabIndex = 31;
            // 
            // numRightAnti
            // 
            this.numRightAnti.Location = new System.Drawing.Point(655, 244);
            this.numRightAnti.Name = "numRightAnti";
            this.numRightAnti.Size = new System.Drawing.Size(42, 20);
            this.numRightAnti.TabIndex = 28;
            // 
            // numRightLimit
            // 
            this.numRightLimit.Location = new System.Drawing.Point(655, 218);
            this.numRightLimit.Name = "numRightLimit";
            this.numRightLimit.Size = new System.Drawing.Size(42, 20);
            this.numRightLimit.TabIndex = 25;
            // 
            // numRightDeadzone
            // 
            this.numRightDeadzone.Location = new System.Drawing.Point(655, 192);
            this.numRightDeadzone.Name = "numRightDeadzone";
            this.numRightDeadzone.Size = new System.Drawing.Size(42, 20);
            this.numRightDeadzone.TabIndex = 22;
            // 
            // btnOK
            // 
            this.btnOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnOK.Location = new System.Drawing.Point(564, 552);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(132, 23);
            this.btnOK.TabIndex = 39;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            // 
            // btnReset
            // 
            this.btnReset.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnReset.Location = new System.Drawing.Point(6, 552);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(132, 23);
            this.btnReset.TabIndex = 38;
            this.btnReset.Text = "Reset All Settings";
            this.btnReset.UseVisualStyleBackColor = true;
            // 
            // deadzoneControl
            // 
            this.deadzoneControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.deadzoneControl.Location = new System.Drawing.Point(0, 0);
            this.deadzoneControl.Name = "deadzoneControl";
            this.deadzoneControl.Size = new System.Drawing.Size(702, 581);
            this.deadzoneControl.TabIndex = 1;
            this.deadzoneControl.Text = "deazoneControl1";
            // 
            // DeadzoneForm
            // 
            this.AcceptButton = this.btnOK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(702, 581);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.numRightShiftV);
            this.Controls.Add(this.numRightShiftH);
            this.Controls.Add(this.numRightSens);
            this.Controls.Add(this.numRightAnti);
            this.Controls.Add(this.numRightLimit);
            this.Controls.Add(this.numRightDeadzone);
            this.Controls.Add(this.numLeftShiftV);
            this.Controls.Add(this.numLeftShiftH);
            this.Controls.Add(this.numLeftSens);
            this.Controls.Add(this.numLeftAnti);
            this.Controls.Add(this.numLeftLimit);
            this.Controls.Add(this.numLeftDeadzone);
            this.Controls.Add(this.trkRightShiftV);
            this.Controls.Add(this.trkRightShiftH);
            this.Controls.Add(this.trkRightSens);
            this.Controls.Add(this.trkRightAnti);
            this.Controls.Add(this.trkRightLimit);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.trkRightDeadzone);
            this.Controls.Add(this.trkLeftShiftV);
            this.Controls.Add(this.trkLeftShiftH);
            this.Controls.Add(this.trkLeftSens);
            this.Controls.Add(this.trkLeftAnti);
            this.Controls.Add(this.trkLeftLimit);
            this.Controls.Add(this.trkLeftDeadzone);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.deadzoneControl);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "DeadzoneForm";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Analog Stick Deadzone Settings";
            ((System.ComponentModel.ISupportInitialize)(this.trkLeftDeadzone)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkLeftLimit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkLeftAnti)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkLeftSens)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkLeftShiftH)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkLeftShiftV)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkRightShiftV)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkRightShiftH)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkRightSens)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkRightAnti)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkRightLimit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkRightDeadzone)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLeftDeadzone)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLeftLimit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLeftAnti)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLeftSens)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLeftShiftH)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLeftShiftV)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRightShiftV)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRightShiftH)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRightSens)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRightAnti)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRightLimit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRightDeadzone)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        #endregion
    }

    internal class DeadzoneControl : PadControl
    {
        protected override void OnPaint(PaintEventArgs e)
        {
            if (gb == null) { base.OnPaint(e); return; }
            GUI.RenderDeadzones(gb.Graphics);
            gb.Render(e.Graphics);
        }
    }
}
