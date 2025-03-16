using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System;

namespace Seewo_Note_Shot___配置工具
{
    partial class Form1
    {
        static Screen screen = Screen.PrimaryScreen;
        static int screenW = screen.Bounds.Width;
        static int screenH = screen.Bounds.Height;
        static int formW = screenW / 5;
        static int formH = screenH / 2;
        static int spacing = screenH / 80;

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
            this.components = new System.ComponentModel.Container();
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(formW, formH);
            this.MinimumSize = new System.Drawing.Size(formW, formH);
            this.MaximumSize = new System.Drawing.Size(formW, formH);
            this.MaximizeBox = false;
            this.Text = "Seewo Note Shot - 配置工具";

            Init_Console();
            Init_Finished();
        }

        private void Init_Console()
        {
            Read_Console();
            this.Label_Console = new System.Windows.Forms.Label();
            this.Label_Console.Text = "显示控制台";
            this.Label_Console.Font = new System.Drawing.Font("Microsoft Sans Serif", spacing);
            this.Label_Console.Width = spacing * 8;
            this.Label_Console.Height = spacing * 2;
            this.Label_Console.Left = spacing;
            this.Label_Console.Top = spacing;
            this.Controls.Add(this.Label_Console);

            this.CheckBox_Console = new System.Windows.Forms.CheckBox();
            this.CheckBox_Console.Checked = console;
            this.CheckBox_Console.Width = spacing;
            this.CheckBox_Console.Height = spacing;
            this.CheckBox_Console.Left = Label_Console.Right;
            this.CheckBox_Console.Top = Label_Console.Top + (Label_Console.Height - CheckBox_Console.Height) / 2;
            this.Controls.Add(this.CheckBox_Console);

        }

        private void Init_Finished()
        {
            this.Button_Cancel = new System.Windows.Forms.Button();
            this.Button_Cancel.Size = new System.Drawing.Size(spacing * 5, spacing * 2);
            this.Button_Cancel.Location = new System.Drawing.Point(formW - spacing * 2 - this.Button_Cancel.Width, formH - spacing * 6);
            this.Button_Cancel.Name = "取消";
            this.Button_Cancel.TabIndex = 0;
            this.Button_Cancel.Text = "取消";
            this.Button_Cancel.Click += new System.EventHandler(this.Button_Cancel_Click);
            this.Controls.Add(Button_Cancel);

            this.Button_OK = new System.Windows.Forms.Button();
            this.Button_OK.Size = new System.Drawing.Size(Button_Cancel.Width, Button_Cancel.Height);
            this.Button_OK.Location = new System.Drawing.Point(Button_Cancel.Left - spacing * 6, Button_Cancel.Top);
            this.Button_OK.Name = "确认";
            this.Button_OK.Text = "确认";
            this.Button_OK.Click += new System.EventHandler(this.Button_OK_Click);
            this.Controls.Add(Button_OK);
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
    }
}