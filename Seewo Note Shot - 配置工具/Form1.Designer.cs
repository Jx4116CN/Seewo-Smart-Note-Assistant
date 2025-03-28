using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System;

namespace Seewo_Note_Shot___配置工具
{
    partial class Form1
    {
        private int spacing = 11;
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        public string RoamingPath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);

        private void InitializeComponent()
        {
            this.TabControl1 = new System.Windows.Forms.TabControl();
            this.TabPage_save = new System.Windows.Forms.TabPage();
            this.TabPage_debug = new System.Windows.Forms.TabPage();
            this.Label_Console = new System.Windows.Forms.Label();
            this.CheckBox_Console = new System.Windows.Forms.CheckBox();
            this.Button_Cancel = new System.Windows.Forms.Button();
            this.Button_OK = new System.Windows.Forms.Button();
            this.TabControl1.SuspendLayout();
            this.TabPage_debug.SuspendLayout();
            this.SuspendLayout();
            // 
            // TabControl1
            // 
            this.TabControl1.Controls.Add(this.TabPage_save);
            this.TabControl1.Controls.Add(this.TabPage_debug);
            this.TabControl1.Font = new System.Drawing.Font("黑体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.TabControl1.Location = new System.Drawing.Point(12, 12);
            this.TabControl1.Name = "TabControl1";
            this.TabControl1.SelectedIndex = 0;
            this.TabControl1.Size = new System.Drawing.Size(320, 548);
            this.TabControl1.TabIndex = 0;
            // 
            // TabPage_save
            // 
            this.TabPage_save.Location = new System.Drawing.Point(4, 24);
            this.TabPage_save.Name = "TabPage_save";
            this.TabPage_save.Size = new System.Drawing.Size(312, 520);
            this.TabPage_save.TabIndex = 0;
            this.TabPage_save.Text = "存储";
            // 
            // TabPage_debug
            // 
            this.TabPage_debug.Controls.Add(this.Label_Console);
            this.TabPage_debug.Controls.Add(this.CheckBox_Console);
            this.TabPage_debug.Location = new System.Drawing.Point(4, 24);
            this.TabPage_debug.Name = "TabPage_debug";
            this.TabPage_debug.Size = new System.Drawing.Size(312, 520);
            this.TabPage_debug.TabIndex = 0;
            this.TabPage_debug.Text = "调试";
            // 
            // Label_Console
            // 
            this.Label_Console.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.Label_Console.Location = new System.Drawing.Point(45, 14);
            this.Label_Console.Name = "Label_Console";
            this.Label_Console.Size = new System.Drawing.Size(100, 23);
            this.Label_Console.TabIndex = 0;
            this.Label_Console.Text = "显示控制台";
            // 
            // CheckBox_Console
            // 
            this.CheckBox_Console.Location = new System.Drawing.Point(14, 12);
            this.CheckBox_Console.Name = "CheckBox_Console";
            this.CheckBox_Console.Size = new System.Drawing.Size(25, 25);
            this.CheckBox_Console.TabIndex = 1;
            // 
            // Button_Cancel
            // 
            this.Button_Cancel.Location = new System.Drawing.Point(257, 566);
            this.Button_Cancel.Name = "Button_Cancel";
            this.Button_Cancel.Size = new System.Drawing.Size(75, 23);
            this.Button_Cancel.TabIndex = 0;
            this.Button_Cancel.Text = "取消";
            this.Button_Cancel.Click += new System.EventHandler(this.Button_Cancel_Click);
            // 
            // Button_OK
            // 
            this.Button_OK.Location = new System.Drawing.Point(176, 566);
            this.Button_OK.Name = "Button_OK";
            this.Button_OK.Size = new System.Drawing.Size(75, 23);
            this.Button_OK.TabIndex = 2;
            this.Button_OK.Text = "确认";
            this.Button_OK.Click += new System.EventHandler(this.Button_OK_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(344, 601);
            this.Controls.Add(this.TabControl1);
            this.Controls.Add(this.Button_Cancel);
            this.Controls.Add(this.Button_OK);
            this.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(360, 640);
            this.MinimumSize = new System.Drawing.Size(360, 640);
            this.Name = "Form1";
            this.Text = "Seewo Note Shot - 配置工具";
            this.TabControl1.ResumeLayout(false);
            this.TabPage_debug.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        public bool console;
        private Label Label_Console;
        private CheckBox CheckBox_Console;
        static string Path_Console = "\\Seewo Note Shot\\Settings\\console.bool";
        public void Read_Console()
        {
        Read:
            string filePath = RoamingPath + "\\Seewo Note Shot\\Settings\\console.bool";
            try
            {
                using (BinaryReader reader = new BinaryReader(File.Open(filePath, FileMode.Open)))
                {
                    console = reader.ReadBoolean();
                }
            }
            catch (Exception ex)
            {
                if (DialogResult.Retry == MessageBox.Show("Failed to open the file - " + filePath + "\nMessage: " + ex.Message, "Error", MessageBoxButtons.RetryCancel))
                    goto Read;
                else
                    Application.Exit();
            }
        }
        public void Write_Console()
        {
        Read:
            string filePath = RoamingPath + Path_Console;
            try
            {
                using (BinaryWriter writer = new BinaryWriter(File.Open(filePath, FileMode.OpenOrCreate)))
                {
                    console = this.CheckBox_Console.Checked;
                    writer.Write(console);
                }
            }
            catch (Exception ex)
            {
                if (DialogResult.Retry == MessageBox.Show("Failed to open the file - " + filePath + "\nMessage: " + ex.Message, "Error", MessageBoxButtons.RetryCancel))
                    goto Read;
                else
                    Application.Exit();
            }
        }

        private Button Button_OK;
        private Button Button_Cancel;

        private TabControl TabControl1;
        private TabPage TabPage_save;
        private TabPage TabPage_debug;
    }
}