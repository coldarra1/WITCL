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
    public partial class nn : Form
    {
        public int nn_n;
        public nn()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1 mainform = new Form1();
            nn_n = Convert.ToInt32(textBox_lowfilter.Text);
            this.Close();
        }

        private void nn_Load(object sender, EventArgs e)
        {

        }

        private void textBox_lowfilter_TextChanged(object sender, EventArgs e)
        {

        }

        

    }
}