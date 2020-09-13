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
    public partial class nnZhongZhi : Form
    {
        public int nnZhongZhi_n;
        public nnZhongZhi()
        {
            InitializeComponent();
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            Form1 mainform = new Form1();
            nnZhongZhi_n = Convert.ToInt32(textBox_lowfilter.Text);
            this.Close();
        }

        private void nnZhongZhi_Load(object sender, EventArgs e)
        {

        }

        private void textBox_lowfilter_TextChanged(object sender, EventArgs e)
        {

        }
    }
}