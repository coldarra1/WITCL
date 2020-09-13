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
    public partial class ShiZi : Form
    {
        public int ShiZi_n;
        public ShiZi()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1 mainform = new Form1();
            ShiZi_n = Convert.ToInt32(textBox_lowfilter.Text);
            this.Close();
        }

        private void ShiZi_Load(object sender, EventArgs e)
        {

        }

        private void textBox_lowfilter_TextChanged(object sender, EventArgs e)
        {

        }
    }
}