using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ConvertBmpToGray;

namespace WindowsApplication1
{
    public partial class ChuangKouBianHuan : Form
    {
        public int ShangXian;
        public int XiaXian;
        public int p;
        public ChuangKouBianHuan()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1 mainform = new Form1();
            ShangXian = Convert.ToInt32(textBoxSX.Text);
            XiaXian = Convert.ToInt32(textBoxXX.Text);
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            p = 1;
            this.Close();
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBoxSX_TextChanged(object sender, EventArgs e)
        {

        }
    }
}