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
    public partial class Form1 : Form
    {
        public Form1()
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
            MessageBox.Show("修改成功！\n重启电脑后生效", "提示", MessageBoxButtons.OK);
        }
    }
}
