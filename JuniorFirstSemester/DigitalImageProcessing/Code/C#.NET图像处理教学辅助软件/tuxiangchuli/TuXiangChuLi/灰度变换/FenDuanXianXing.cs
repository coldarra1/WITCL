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
    public partial class FenDuanXianXing : Form
    {
        public int x1;
        public int y1;
        public int x2;
        public int y2;
        public int p;
        public FenDuanXianXing()
        {
            InitializeComponent();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1 mainform = new Form1();
            x1 = Convert.ToInt32(textx1.Text);
            y1 = Convert.ToInt32(texty1.Text);
            x2 = Convert.ToInt32(textx2.Text);
            y2 = Convert.ToInt32(texty2.Text);
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            p = 1;
            this.Close();
        }

        private void textx1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}