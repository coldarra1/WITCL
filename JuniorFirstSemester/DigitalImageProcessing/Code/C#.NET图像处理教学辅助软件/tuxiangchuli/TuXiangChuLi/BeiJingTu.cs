using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ConvertBmpToGray
{
    public partial class BeiJingTu : Form
    {
        public int[, ,] BeiJingTu_n = new int[600, 600,3];
        public int p;
        string file;
        public BeiJingTu()
        {

            InitializeComponent();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.openFileDialog1.Filter = "bmp files (*.bmp)|*.bmp|All files (*.*)|*.*";
            this.openFileDialog1.ShowDialog();
            file = this.openFileDialog1.FileName;//
            Bitmap bm = new Bitmap(file);//
            if (file == null)
                return;
            //MessageBox.Show(file);//这三句相当于Bitmap image = new Bitmap(ofdlg.FileName);
            this.pictureBox1.Image = bm;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Form1 mainform = new Form1();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Color c = new Color();
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    BeiJingTu_n[i, j, 0] = c.R;
                    BeiJingTu_n[i, j, 1] = c.G;
                    BeiJingTu_n[i, j, 2] = c.B;
                    
                }
            }
            //MessageBox.Show("o"+BeiJingTu_n[1,1,1]);
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            p = 1;
            this.Close();
        }
    }
}