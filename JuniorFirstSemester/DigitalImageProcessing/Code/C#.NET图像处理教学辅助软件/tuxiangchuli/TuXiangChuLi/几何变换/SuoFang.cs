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
    public partial class SuoFang : Form
    {
        public float SuoFang_n;
        public int p;
        public SuoFang()
        {
            InitializeComponent();
        }

        private void SuoFang_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1 mainform = new Form1();
            SuoFang_n = Convert.ToSingle(textBox_lowfilter.Text);
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            p = 1;
            this.Close();
        }
    }
}