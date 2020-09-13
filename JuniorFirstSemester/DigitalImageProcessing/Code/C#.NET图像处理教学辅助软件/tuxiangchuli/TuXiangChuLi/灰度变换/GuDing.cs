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
    public partial class GuDing : Form
    {
        public int GuDing_n;
        public int p = 0;
        public GuDing()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1 mainform = new Form1();
            GuDing_n = Convert.ToInt32(textBox_lowfilter.Text);
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
    }
}