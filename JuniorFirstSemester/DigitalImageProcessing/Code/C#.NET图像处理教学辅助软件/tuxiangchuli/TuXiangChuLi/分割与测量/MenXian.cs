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
    public partial class MenXian : Form
    {
        public int MenXian_n;
        public int p=0;
        public MenXian()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1 mainform = new Form1();
            MenXian_n = Convert.ToInt32(textBox_lowfilter.Text);
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            p=1;
            this.Close(); 
        }
    }
}