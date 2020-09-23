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
    public partial class ShuangYu : Form
    {
        public int ShuangYu_n1;
        public int ShuangYu_n2;
        public int p;
        public ShuangYu()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1 mainform = new Form1();
            ShuangYu_n1 = Convert.ToInt32(textBox_lowfilter.Text);
            ShuangYu_n2 = Convert.ToInt32(textBox1.Text);
            this.Close();
        }

       

        private void button2_Click(object sender, EventArgs e)
        {
            p = 1;
            this.Close();
        }

        private void textBox_lowfilter_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

       

      
    }
}