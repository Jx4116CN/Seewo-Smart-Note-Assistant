using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Seewo_Note_Shot___配置工具
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        private void Button_Cancel_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void Button_OK_Click(object sender, EventArgs e)
        {
            Write_Console();
            Write_SPath();
            Write_SWay();
            MessageBox.Show("修改成功！\n重启电脑后生效", "提示", MessageBoxButtons.OK);
        }

        private void TextBox_SPath_DoubleClick(object sender, EventArgs e)
        {
            if (folderBrowser1.ShowDialog() == DialogResult.OK)
            {
                // 获取用户选择的文件夹路径
                this.TextBox_SPath.Text = folderBrowser1.SelectedPath;
                this.folderBrowser1.SelectedPath = folderBrowser1.SelectedPath;
            }
        }
        private void Button_SPath_MouseClick(object sender, MouseEventArgs e)
        {
            if (folderBrowser1.ShowDialog() == DialogResult.OK)
            {
                // 获取用户选择的文件夹路径
                this.TextBox_SPath.Text = folderBrowser1.SelectedPath;
                this.folderBrowser1.SelectedPath = folderBrowser1.SelectedPath;
            }
        }
    }
}
