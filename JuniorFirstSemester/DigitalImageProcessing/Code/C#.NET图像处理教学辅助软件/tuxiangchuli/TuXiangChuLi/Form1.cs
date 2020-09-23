using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Imaging;
using ImageFilterApp;
using Exocortex.DSP;
using WindowsApplication1;
using System.Collections;

namespace ConvertBmpToGray
{
    public partial class Form1 : Form
    {
        string file;
        int XianShi;
        
        public Form1()
        {
            InitializeComponent();
        }

        /* private Bitmap ConvertByPixel(Bitmap srcBmp)
         {
             int x, y;
             byte red, green, blue, gray;
             Color src;
             Bitmap result;
             result = new Bitmap(srcBmp.Width, srcBmp.Height);
             for (y = 0; y < srcBmp.Height; y++)
             {
                 for (x = 0; x < srcBmp.Width; x++)
                 {
                     src = srcBmp.GetPixel(x, y);
                     red = src.R;
                     green = src.G;
                     blue = src.B;
                     gray = (byte)(.299 * red + .587 * green + .114 * blue);
                     result.SetPixel(x, y, Color.FromArgb(gray, gray, gray));
                 }
             }
             return result;
         }

         private void ConvertBmp(string srcFile)
         {
             Bitmap srcBmp, targetBmp;
             srcBmp = new Bitmap(srcFile);
             targetBmp = ConvertByPixel(srcBmp);
             this.pictureBox2.Image = targetBmp;
         }*/

         private void Form1_Load(object sender, EventArgs e)
         {
             //Bitmap targetBmp = new Bitmap(260, 320, System.Drawing.Imaging.PixelFormat.Format8bppIndexed);
             //this.pictureBox1.Image = targetBmp;
         }

         /*private void button1_Click(object sender, EventArgs e)
         {
             this.openFileDialog1.Filter = "bmp files (*.bmp)|*.bmp|All files (*.*)|*.*";
             this.openFileDialog1.ShowDialog();
             file = this.openFileDialog1.FileName;//
             Bitmap bm = new Bitmap(file);//
             MessageBox.Show(file);//这三句相当于Bitmap image = new Bitmap(ofdlg.FileName);
             this.pictureBox1.Image = bm;


             //this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
         }

         private void button2_Click(object sender, EventArgs e)
         {
             this.ConvertBmp(file);//转化成灰度
         }

         private void button3_Click(object sender, EventArgs e)
         {
             this.saveFileDialog1.Filter = "bmp files (*.bmp)|*.bmp|All files (*.*)|*.*";
             this.saveFileDialog1.ShowDialog();
             this.pictureBox2.Image.Save(this.saveFileDialog1.FileName);
         }*/

        private void button4_Click(object sender, EventArgs e)
        {
            if (this.ActiveCImage == null)
            {
                return;
            }

            CImage cimage = this.ActiveCImage;//调用图像
            float scale = 1f / (float)Math.Sqrt(cimage.Width * cimage.Height);
            ComplexF[] data = cimage.Data;

            int offset = 0;
            for (int y = 0; y < cimage.Height; y++)
            {
                for (int x = 0; x < cimage.Width; x++)
                {
                    if (((x + y) & 0x1) != 0)
                    {
                        data[offset] *= -1;
                    }
                    offset++;
                }
            }

            Fourier.FFT2(data, cimage.Width, cimage.Height, FourierDirection.Forward);

            cimage.FrequencySpace = true;

            for (int i = 0; i < data.Length; i++)
            {
                data[i] *= scale;
            }

            this.ActiveCImage = cimage;
        }

        protected CImage _cimage = null;
        public CImage ActiveCImage
        {
            get { return _cimage; }
            set
            {
                _cimage = value;
                if (_cimage != null)
                {
                    Bitmap bitmap = _cimage.ToBitmap();
                    this.pictureBox2.Image = bitmap;
                    _statusbar.Text = "( " + _cimage.Width + ", " + _cimage.Height + " )";
                }
                else
                {
                    this.pictureBox2.Image = null;
                    this.pictureBox2.Visible = false;
                    _statusbar.Text = "No bitmap loaded.";
                }
            }
        }

        //////////////////////////////////////////////////////////////
        //该函数用来实现二维傅立叶变换
        //参数height、width分别表示图象的高度和宽度，ising表示正反变换
        //////////////////////////////////////////////////////////////
        private void fourier(double[] data, int height, int width, int isign)
        {//fun内定义数组
            int idim;
            long i1, i2, i3, i2rev, i3rev, ip1, ip2, ip3, ifp1, ifp2;
            long ibit, k1, k2, n, nprev, nrem, ntot;
            long[] nn = new long[3];
            double pi = 3.1415926;
            double tempi, tempr;
            double theta, wi, wpi, wpr, wr, wtemp;
            ntot = height * width;
            nn[1] = height;
            nn[2] = width;
            nprev = 1;
            for (idim = 2; idim >= 1; idim--)
            {
                n = nn[idim];
                if (n != 0)
                {
                    nrem = ntot / (n * nprev);
                    ip1 = nprev << 1;
                    ip2 = ip1 * n;
                    ip3 = ip2 * nrem;
                    i2rev = 1;
                    for (i2 = 1; i2 <= ip2; i2 += ip1)
                    {
                        if (i2 < i2rev)
                        {
                            for (i1 = i2; i1 <= i2 + ip1 - 2; i1 += 2)
                            {
                                for (i3 = i1; i3 <= ip3; i3 += ip2)
                                {
                                    i3rev = i2rev + i3 - i2;
                                    double[] temp = new double[height * width * 2 + 1];

                                    temp[i3] = data[i3];
                                    data[i3] = data[i3rev];
                                    data[i3rev] = temp[i3];

                                    temp[i3 + 1] = data[i3 + 1];
                                    data[i3 + 1] = data[i3rev + 1];
                                    data[i3rev + 1] = temp[i3 + 1];
                                }
                            }
                        }
                        ibit = ip2 >> 1;
                        while (ibit >= ip1 && i2rev > ibit)
                        {
                            i2rev -= ibit;
                            ibit >>= 1;
                        }
                        i2rev += ibit;
                    }
                    ifp1 = ip1;
                    while (ifp1 < ip2)
                    {
                        ifp2 = ifp1 << 1;
                        theta = isign * pi * 2 / (ifp2 / ip1);
                        wtemp = Math.Sin(0.5 * theta);
                        wpr = -2.0 * wtemp * wtemp;
                        wpi = Math.Sin(theta);
                        wr = 1.0;
                        wi = 0.0;
                        for (i3 = 1; i3 <= ifp1; i3 += ip1)
                        {
                            for (i1 = i3; i1 <= i3 + ip1 - 2; i1 += 2)
                            {
                                for (i2 = i1; i2 <= ip3; i2 += ifp2)
                                {
                                    k1 = i2;
                                    k2 = k1 + ifp1;
                                    tempr = wr * data[k2] - wi * data[k2 + 1];
                                    tempi = wr * data[k2 + 1] + wi * data[k2];
                                    data[k2] = data[k1] - tempr;
                                    data[k2 + 1] = data[k1 + 1] - tempi;
                                    data[k1] += tempr;
                                    data[k1 + 1] += tempi;
                                }
                            }
                            wr = (wtemp = wr) * wpr - wi * wpi + wr;
                            wi = wi * wpr + wtemp * wpi + wi;
                        }
                        ifp1 = ifp2;
                    }
                    nprev *= n;
                }
            }
        }







        private void Once(int n, double[,] m_pData2)
        {
            int i, j;
            Color c1 = new Color();
            Color c2 = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int[,] r1 = new int[box1.Width, box1.Height * box1.Width];
            int[,] g1 = new int[box1.Width, box1.Height * box1.Width];
            int[,] b1 = new int[box1.Width, box1.Height * box1.Width];
            int[,] r2 = new int[box1.Width, box1.Height * box1.Width];
            int[,] g2 = new int[box1.Width, box1.Height * box1.Width];
            int[,] b2 = new int[box1.Width, box1.Height * box1.Width];

            for (int k = 1; k <= n; k++)
            {
                int nwide = box1.Width / (int)Math.Pow(2, k);
                int nHeight = box1.Height / (int)Math.Pow(2, k);

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < nwide; i++)
                    {
                        int w = i * 2;
                        c1 = box1.GetPixel(w, j);
                        r1[i, j] = c1.R;
                        g1[i, j] = c1.G;
                        b1[i, j] = c1.B;

                        c2 = box1.GetPixel(w + 1, j);
                        r1[i + nwide, j] = c2.R;
                        g1[i + nwide, j] = c2.G;
                        b1[i + nwide, j] = c2.B;
                    }
                }

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < nwide - 1; i++)
                    {
                        r1[i + nwide - 1, j] = (int)Math.Abs(r1[i + nwide - 1, j] - r1[i, j] + 128);
                        g1[i + nwide - 1, j] = (int)Math.Abs(g1[i + nwide - 1, j] - g1[i, j] + 128);
                        b1[i + nwide - 1, j] = (int)Math.Abs(b1[i + nwide - 1, j] - b1[i, j] + 128);
                    }
                }

                for (i = 0; i < (int)Math.Abs(box1.Width / Math.Pow(2, k - 1)); i++)
                {
                    for (j = (int)Math.Abs(box1.Height * (1 - 1 / Math.Pow(2, (k - 1)))); j < (int)Math.Abs(box1.Height * (1 - 1 / Math.Pow(2, (k - 1)))) + nHeight; j++)
                    {
                        int m, h;
                        m = (int)Math.Abs(box1.Height * (1 - 1 / Math.Pow(2, (k - 1))));
                        h = (j - m) * 2;

                        r2[i, j] = r1[i, m + h];
                        g2[i, j] = g1[i, m + h];
                        b2[i, j] = b1[i, m + h];

                        r2[i, j + nHeight] = r1[i, m + h + 1];
                        g2[i, j + nHeight] = g1[i, m + h + 1];
                        b2[i, j + nHeight] = b1[i, m + h + 1];
                    }
                }

                for (i = 0; i < (int)Math.Abs(box1.Width / Math.Pow(2, k - 1)); i++)
                {
                    for (j = (int)Math.Abs(box1.Height * (1 - 1 / Math.Pow(2, (k - 1)))); j < (int)Math.Abs(box1.Height * (1 - 1 / Math.Pow(2, (k - 1)))) + nHeight; j++)
                    {
                        r2[i, j + nHeight] = (int)Math.Abs(r2[i, j + nHeight] - r2[i, j] + 128);
                        g2[i, j + nHeight] = (int)Math.Abs(g2[i, j + nHeight] - g2[i, j] + 128);
                        b2[i, j + nHeight] = (int)Math.Abs(b2[i, j + nHeight] - b2[i, j] + 128);
                    }
                }

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < box1.Width / (int)Math.Pow(2, k - 1); i++)
                    {
                        if (r2[i, j] < 0) r2[i, j] = 0;
                        if (r2[i, j] > 255) r2[i, j] = 255;
                        if (g2[i, j] < 0) g2[i, j] = 0;
                        if (g2[i, j] > 255) g2[i, j] = 255;
                        if (b2[i, j] < 0) b2[i, j] = 0;
                        if (b2[i, j] > 255) b2[i, j] = 255;
                        m_pData2[i, j] = 0.3 * r2[i, j] + 0.59 * g2[i, j] + 0.11 * b2[i, j];
                    }
                }
            }
        }

        private void IDWT(double[,] m_pData2, int n)
        {
            int i, j;
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);

            for (int k = n; k >= 1; k--)
            {
                int nwide = box1.Width / (int)Math.Pow(2, k);
                int nHeight = box1.Height / (int)Math.Pow(2, k);
                int[,] temp1 = new int[box1.Width, box1.Height * box1.Width];
                int[,] temp2 = new int[box1.Width, box1.Height * box1.Width];
                int[,] temp3 = new int[box1.Width, box1.Height * box1.Width];
                int[,] m_pData = new int[3 * box1.Width + 3, box1.Height + box1.Width + 1];

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < box1.Width; i++)
                    {
                        temp1[i, j] = (int)(m_pData2[i, j]);
                    }
                }

                for (i = 0; i < box1.Width / (int)Math.Pow(2, k - 1); i++)
                {
                    for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))) + nHeight; j++)
                    {
                        temp1[i, j] = (int)Math.Abs(temp1[i, j + nHeight] + temp1[i, j] - 128);
                    }
                }

                for (i = 0; i < box1.Width / (int)Math.Pow(2, k - 1); i++)
                {
                    for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))) + nHeight; j++)
                    {
                        int m, h;
                        m = (int)Math.Abs(box1.Height * (1 - 1 / Math.Pow(2, (k - 1))));
                        h = (j - m) * 2;

                        temp2[i, m + h] = temp1[i, j];
                        temp2[i, m + h + 1] = temp1[i, j + nHeight];
                    }
                }

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < nwide - 1; i++)
                    {
                        temp2[i + nwide, j] += Math.Abs(temp2[i, j] - 128);
                    }
                }

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < nwide; i++)
                    {
                        int w = i * 2;
                        temp3[w, j] = temp2[i, j];
                        temp3[w + 1, j] = temp2[i + nwide, j];
                    }
                }

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < box1.Width / (int)Math.Pow(2, k - 1); i++)
                    {
                        if (temp3[i, j] < 0) temp3[i, j] = 0;
                        if (temp3[i, j] > 255) temp3[i, j] = 255;
                        m_pData2[i, j] = temp3[i, j];
                    }
                }

                for (j = 0; j < box1.Height; j++)
                {
                    for (i = 0; i < box1.Width; i++)
                    {
                        m_pData[3 * i, box1.Height - j - 1] = (int)(m_pData2[i, box1.Height - 1 - j]);
                        m_pData[3 * i + 1, box1.Height - j - 1] = (int)(m_pData2[i, box1.Height - 1 - j]);
                        m_pData[3 * i + 2, box1.Height - j - 1] = (int)(m_pData2[i, box1.Height - 1 - j]);
                        Color cc = Color.FromArgb(m_pData[3 * i, box1.Height - j - 1], m_pData[3 * i + 1, box1.Height - j - 1], m_pData[3 * i + 2, box1.Height - j - 1]);
                        box2.SetPixel(i, j, cc);
                    }
                }
                pictureBox2.Refresh();
                pictureBox2.Image = box2;
            }
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void Open_Click(object sender, EventArgs e)
        {
            this.openFileDialog1.Filter = "bmp files (*.bmp)|*.bmp|All files (*.*)|*.*";
            if (this.openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                file = this.openFileDialog1.FileName;
                Bitmap bm = new Bitmap(file);
                //MessageBox.Show(file);
                this.pictureBox1.Image = bm;
            }
           

            //this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
        }

        private void SSave_Click(object sender, EventArgs e)
        {
            this.saveFileDialog1.Filter = "bmp files (*.bmp)|*.bmp|All files (*.*)|*.*";
            this.saveFileDialog1.ShowDialog();
            this.pictureBox2.Image.Save(this.saveFileDialog1.FileName);
        }

        private void 图像平移ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TuXiangPingYi frm = new TuXiangPingYi();//图像平移
            frm.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm.StartPosition = FormStartPosition.CenterParent;

            frm.ShowDialog(this);

            int n = frm.TuXiangPingYi_n;//模式对话框传值
            if (frm.p == 1)//ｃｏｎｃｅｌｌ功能判断
            {
                return;

            }
            Color c = new Color();
            // Color cc = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width + 100, box1.Height + 100);
            int rr, gg, bb;
            int[, ,] pic = new int[600, 600, 3];
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    pic[i, j, 0] = c.R;
                    pic[i, j, 1] = c.G;
                    pic[i, j, 2] = c.B;
                }
            }
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    rr = pic[i, j, 0];
                    gg = pic[i, j, 1];
                    bb = pic[i, j, 2];
                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i + n, j + n, c1);
                }

            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void JingXiang_Click(object sender, EventArgs e)
        {

        }

        private void SuiPing_Click(object sender, EventArgs e)
        {

            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int rr, gg, bb;
            int[, ,] pic = new int[600, 600, 3];
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    pic[i, j, 0] = c.R;
                    pic[i, j, 1] = c.G;
                    pic[i, j, 2] = c.B;
                }
            }

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    rr = pic[box1.Width - i, j, 0];
                    gg = pic[box1.Width - i, j, 1];
                    bb = pic[box1.Width - i, j, 2];
                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }

            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 水平镜像ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int rr, gg, bb;
            int[, ,] pic = new int[600, 600, 3];
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    pic[i, j, 0] = c.R;
                    pic[i, j, 1] = c.G;
                    pic[i, j, 2] = c.B;
                }
            }

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    rr = pic[box1.Width - i, j, 0];
                    gg = pic[box1.Width - i, j, 1];
                    bb = pic[box1.Width - i, j, 2];
                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }

            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 傅立叶变换ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            if (this.ActiveCImage == null)
            {
                return;
            }

            CImage cimage = this.ActiveCImage;//调用图像
            float scale = 1f / (float)Math.Sqrt(cimage.Width * cimage.Height);
            ComplexF[] data = cimage.Data;

            int offset = 0;
            for (int y = 0; y < cimage.Height; y++)
            {
                for (int x = 0; x < cimage.Width; x++)
                {
                    if (((x + y) & 0x1) != 0)
                    {
                        data[offset] *= -1;
                    }
                    offset++;
                }
            }

            Fourier.FFT2(data, cimage.Width, cimage.Height, FourierDirection.Forward);

            cimage.FrequencySpace = true;

            for (int i = 0; i < data.Length; i++)
            {
                data[i] *= scale;
            }

            this.ActiveCImage = cimage;
        }

        private void 理想低通滤波ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            PerfectFilterL form_pfl = new PerfectFilterL();
            form_pfl.FormBorderStyle = FormBorderStyle.FixedSingle;//对话框边缘风格
            form_pfl.StartPosition = FormStartPosition.CenterParent;//在父窗体的中间显示该对话框    
            form_pfl.ShowDialog(this);//此处必须有this,否则模态对话框(垄断用户输入)不能显示                 
            //form1.Show(this);//显示非模态对话框
            int u = form_pfl.weightX;
            int v = form_pfl.weightY;
            bool flag2 = false;
            flag2 = form_pfl.flag1;
            if (flag2 == true)
            {
                return;
            }
            int i, j;
            double d0, max = 0.0;//中间变量
            Color c1 = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            //int lLineBytes = (byte)(box1.Width * 8);//计算图象每行的字节数        
            double[] t = new double[box1.Height * box1.Width * 2 + 1];//分配存储器空间
            double[] H = new double[box1.Height * box1.Width * 2 + 1];
            int[] r1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] g1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] b1 = new int[box1.Height * box1.Width * 2 + 1];
            d0 = Math.Sqrt(u * u + v * v);//计算截止频率d0

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    t[(2 * box1.Width) * j + 2 * i + 1] = 0.3 * r1[box1.Width * j + i] + 0.59 * g1[box1.Width * j + i] + 0.11 * b1[box1.Width * j + i];//给时域赋值
                    t[(2 * box1.Width) * j + 2 * i + 2] = 0.0;

                    if ((Math.Sqrt(i * i + j * j)) <= d0)
                    {
                        H[2 * i + (2 * box1.Width) * j + 1] = 1.0;
                    }
                    else
                    {
                        H[2 * i + (2 * box1.Width) * j + 1] = 0.0;
                    }
                    H[2 * i + (2 * box1.Width) * j + 2] = 0.0;
                }
            }

            fourier(t, box1.Height, box1.Width, 1);

            for (j = 1; j < box1.Height * box1.Width * 2; j += 2)
            {
                t[j] = t[j] * H[j] - t[j + 1] * H[j + 1];
                t[j + 1] = t[j] * H[j + 1] + t[j + 1] * H[j];
            }

            fourier(t, box1.Height, box1.Width, -1);

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    t[(2 * box1.Width) * j + 2 * i + 1] = Math.Sqrt(t[(2 * box1.Width) * j + 2 * i + 1] * t[(2 * box1.Width) * j + 2 * i + 1] + t[(2 * box1.Width) * j + 2 * i + 2] * t[(2 * box1.Width) * j + 2 * i + 2]);
                    if (max < t[(2 * box1.Width) * j + 2 * i + 1])
                    {
                        max = t[(2 * box1.Width) * j + 2 * i + 1];
                    }
                }
            }

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    r1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    g1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    b1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);

                    if (r1[box1.Width * j + i] < 0) r1[box1.Width * j + i] = 0;
                    if (r1[box1.Width * j + i] > 255) r1[box1.Width * j + i] = 255;
                    if (g1[box1.Width * j + i] < 0) g1[box1.Width * j + i] = 0;
                    if (g1[box1.Width * j + i] > 255) g1[box1.Width * j + i] = 255;
                    if (b1[box1.Width * j + i] < 0) b1[box1.Width * j + i] = 0;
                    if (b1[box1.Width * j + i] > 255) b1[box1.Width * j + i] = 255;

                    Color c = Color.FromArgb(r1[box1.Width * j + i], g1[box1.Width * j + i], b1[box1.Width * j + i]);
                    box2.SetPixel(i, j, c);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 梯形低通滤波ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            TLFilter form_tlf = new TLFilter();
            form_tlf.FormBorderStyle = FormBorderStyle.FixedSingle;//对话框边缘风格
            form_tlf.StartPosition = FormStartPosition.CenterParent;//在父窗体的中间显示该对话框    
            form_tlf.ShowDialog(this);//此处必须有this,否则模态对话框(垄断用户输入)不能显示                 
            //form1.Show(this);//显示非模态对话框
            int u = form_tlf.weightX1;
            int v = form_tlf.weightY1;
            int u1 = form_tlf.weightX2;
            int v1 = form_tlf.weightY2;
            bool flag2 = false;
            flag2 = form_tlf.flag1;
            if (flag2 == true)
            {
                return;
            }
            int i, j;
            double max = 0.0, d0, d, d1;//中间变量
            Color c1 = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int[] r1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] g1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] b1 = new int[box1.Height * box1.Width * 2 + 1];

            double[] t = new double[box1.Height * box1.Width * 2 + 1];//分配存储器空间
            double[] H = new double[box1.Height * box1.Width * 2 + 1];

            d0 = Math.Sqrt(u * u + v * v);//计算截止频率d0
            d1 = Math.Sqrt(u1 * u1 + v1 * v1);//计算截止频率d1

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    t[(2 * box1.Width) * j + 2 * i + 1] = 0.3 * r1[box1.Width * j + i] + 0.59 * g1[box1.Width * j + i] + 0.11 * b1[box1.Width * j + i];//给时域赋值
                    t[(2 * box1.Width) * j + 2 * i + 2] = 0.0;

                    d = Math.Sqrt(i * i + j * j);
                    if (d < d0)
                    {
                        H[2 * i + (2 * box1.Width) * j + 1] = 1;
                        H[2 * i + (2 * box1.Width) * j + 2] = 0.0;
                    }
                    if (d > d1)
                    {
                        H[2 * i + (2 * box1.Width) * j + 1] = 0.0;
                        H[2 * i + (2 * box1.Width) * j + 2] = 0.0;
                    }
                    else
                    {
                        H[2 * i + (2 * box1.Width) * j + 1] = (d - d1) / (d0 - d1);
                        H[2 * i + (2 * box1.Width) * j + 2] = 0.0;
                    }
                }
            }

            fourier(t, box1.Height, box1.Width, 1);

            for (j = 1; j < box1.Height * box1.Width * 2; j += 2)
            {
                t[j] = t[j] * H[j] - t[j + 1] * H[j + 1];
                t[j + 1] = t[j] * H[j + 1] + t[j + 1] * H[j];
            }

            fourier(t, box1.Height, box1.Width, -1);

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    t[(2 * box1.Width) * j + 2 * i + 1] = Math.Sqrt(t[(2 * box1.Width) * j + 2 * i + 1] * t[(2 * box1.Width) * j + 2 * i + 1] + t[(2 * box1.Width) * j + 2 * i + 2] * t[(2 * box1.Width) * j + 2 * i + 2]);
                    if (max < t[(2 * box1.Width) * j + 2 * i + 1])
                    {
                        max = t[(2 * box1.Width) * j + 2 * i + 1];
                    }
                }
            }

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    r1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    g1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    b1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);

                    if (r1[box1.Width * j + i] < 0) r1[box1.Width * j + i] = 0;
                    if (r1[box1.Width * j + i] > 255) r1[box1.Width * j + i] = 255;
                    if (g1[box1.Width * j + i] < 0) g1[box1.Width * j + i] = 0;
                    if (g1[box1.Width * j + i] > 255) g1[box1.Width * j + i] = 255;
                    if (b1[box1.Width * j + i] < 0) b1[box1.Width * j + i] = 0;
                    if (b1[box1.Width * j + i] > 255) b1[box1.Width * j + i] = 255;

                    Color c = Color.FromArgb(r1[box1.Width * j + i], g1[box1.Width * j + i], b1[box1.Width * j + i]);
                    box2.SetPixel(i, j, c);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 布特沃斯低通滤波ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            BwFilterL form_bfl = new BwFilterL();
            form_bfl.FormBorderStyle = FormBorderStyle.FixedSingle;//对话框边缘风格
            form_bfl.StartPosition = FormStartPosition.CenterParent;//在父窗体的中间显示该对话框    
            form_bfl.ShowDialog(this);//此处必须有this,否则模态对话框(垄断用户输入)不能显示              
            int u = form_bfl.weightX;
            int v = form_bfl.weightY;
            int n = form_bfl.weightN;
            bool flag2 = false;
            flag2 = form_bfl.flag1;
            if (flag2 == true)
            {
                return;
            }
            int i, j;
            double d0, d, max = 0.0;//中间变量
            Color c1 = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            double[] t = new double[box1.Height * box1.Width * 2 + 1];//分配存储器空间
            double[] H = new double[box1.Height * box1.Width * 2 + 1];
            int[] r1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] g1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] b1 = new int[box1.Height * box1.Width * 2 + 1];
            d0 = Math.Sqrt(u * u + v * v);//计算截止频率d0

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    t[(2 * box1.Width) * j + 2 * i + 1] = 0.3 * r1[box1.Width * j + i] + 0.59 * g1[box1.Width * j + i] + 0.11 * b1[box1.Width * j + i];//给时域赋值
                    t[(2 * box1.Width) * j + 2 * i + 2] = 0.0;

                    d = Math.Sqrt(i * i + j * j);
                    H[2 * i + (2 * box1.Width) * j + 1] = 1 / (1 + Math.Pow((d / d0), (2 * n)));
                    H[2 * i + (2 * box1.Width) * j + 2] = 0.0;
                }
            }

            fourier(t, box1.Height, box1.Width, 1);

            for (j = 1; j < box1.Height * box1.Width * 2; j += 2)
            {
                t[j] = t[j] * H[j] - t[j + 1] * H[j + 1];
                t[j + 1] = t[j] * H[j + 1] + t[j + 1] * H[j];
            }

            fourier(t, box1.Height, box1.Width, -1);

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    t[(2 * box1.Width) * j + 2 * i + 1] = Math.Sqrt(t[(2 * box1.Width) * j + 2 * i + 1] * t[(2 * box1.Width) * j + 2 * i + 1] + t[(2 * box1.Width) * j + 2 * i + 2] * t[(2 * box1.Width) * j + 2 * i + 2]);
                    if (max < t[(2 * box1.Width) * j + 2 * i + 1])
                    {
                        max = t[(2 * box1.Width) * j + 2 * i + 1];
                    }
                }
            }

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    r1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    g1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    b1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);

                    if (r1[box1.Width * j + i] < 0) r1[box1.Width * j + i] = 0;
                    if (r1[box1.Width * j + i] > 255) r1[box1.Width * j + i] = 255;
                    if (g1[box1.Width * j + i] < 0) g1[box1.Width * j + i] = 0;
                    if (g1[box1.Width * j + i] > 255) g1[box1.Width * j + i] = 255;
                    if (b1[box1.Width * j + i] < 0) b1[box1.Width * j + i] = 0;
                    if (b1[box1.Width * j + i] > 255) b1[box1.Width * j + i] = 255;

                    Color c = Color.FromArgb(r1[box1.Width * j + i], g1[box1.Width * j + i], b1[box1.Width * j + i]);
                    box2.SetPixel(i, j, c);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 指数低通滤波ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            ZLFilter form_zlf = new ZLFilter();
            form_zlf.FormBorderStyle = FormBorderStyle.FixedSingle;//对话框边缘风格
            form_zlf.StartPosition = FormStartPosition.CenterParent;//在父窗体的中间显示该对话框    
            form_zlf.ShowDialog(this);//此处必须有this,否则模态对话框(垄断用户输入)不能显示                 
            int u = form_zlf.weightX;
            int v = form_zlf.weightY;
            int n = form_zlf.weightN;
            bool flag2 = false;
            flag2 = form_zlf.flag1;
            if (flag2 == true)
            {
                return;
            }
            int i, j;
            double d0, d, max = 0.0;//中间变量
            Color c1 = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            double[] t = new double[box1.Height * box1.Width * 2 + 1];//分配存储器空间
            double[] H = new double[box1.Height * box1.Width * 2 + 1];
            int[] r1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] g1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] b1 = new int[box1.Height * box1.Width * 2 + 1];
            d0 = Math.Sqrt(u * u + v * v);//计算截止频率d0

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    t[(2 * box1.Width) * j + 2 * i + 1] = 0.3 * r1[box1.Width * j + i] + 0.59 * g1[box1.Width * j + i] + 0.11 * b1[box1.Width * j + i];//给时域赋值
                    t[(2 * box1.Width) * j + 2 * i + 2] = 0.0;

                    d = Math.Sqrt(i * i + j * j);
                    H[2 * i + (2 * box1.Width) * j + 1] = Math.Exp(-Math.Pow((d / d0), n));
                    H[2 * i + (2 * box1.Width) * j + 2] = 0.0;
                }
            }

            fourier(t, box1.Height, box1.Width, 1);

            for (j = 1; j < box1.Height * box1.Width * 2; j += 2)
            {
                t[j] = t[j] * H[j] - t[j + 1] * H[j + 1];
                t[j + 1] = t[j] * H[j + 1] + t[j + 1] * H[j];
            }

            fourier(t, box1.Height, box1.Width, -1);

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    t[(2 * box1.Width) * j + 2 * i + 1] = Math.Sqrt(t[(2 * box1.Width) * j + 2 * i + 1] * t[(2 * box1.Width) * j + 2 * i + 1] + t[(2 * box1.Width) * j + 2 * i + 2] * t[(2 * box1.Width) * j + 2 * i + 2]);
                    if (max < t[(2 * box1.Width) * j + 2 * i + 1])
                    {
                        max = t[(2 * box1.Width) * j + 2 * i + 1];
                    }
                }
            }

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    r1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    g1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    b1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);

                    if (r1[box1.Width * j + i] < 0) r1[box1.Width * j + i] = 0;
                    if (r1[box1.Width * j + i] > 255) r1[box1.Width * j + i] = 255;
                    if (g1[box1.Width * j + i] < 0) g1[box1.Width * j + i] = 0;
                    if (g1[box1.Width * j + i] > 255) g1[box1.Width * j + i] = 255;
                    if (b1[box1.Width * j + i] < 0) b1[box1.Width * j + i] = 0;
                    if (b1[box1.Width * j + i] > 255) b1[box1.Width * j + i] = 255;

                    Color c = Color.FromArgb(r1[box1.Width * j + i], g1[box1.Width * j + i], b1[box1.Width * j + i]);
                    box2.SetPixel(i, j, c);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 理想高通滤波ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            PerfectFilterH form_pfh = new PerfectFilterH();
            form_pfh.FormBorderStyle = FormBorderStyle.FixedSingle;//对话框边缘风格
            form_pfh.StartPosition = FormStartPosition.CenterParent;//在父窗体的中间显示该对话框    
            form_pfh.ShowDialog(this);//此处必须有this,否则模态对话框(垄断用户输入)不能显示                           
            int u = form_pfh.weightX;
            int v = form_pfh.weightY;
            bool flag2 = false;
            flag2 = form_pfh.flag1;
            if (flag2 == true)
            {
                return;
            }
            int i, j;
            double d0, max = 0.0;//中间变量
            Color c1 = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            //int lLineBytes = (byte)(box1.Width * 8);//计算图象每行的字节数        
            double[] t = new double[box1.Height * box1.Width * 2 + 1];//分配存储器空间
            double[] H = new double[box1.Height * box1.Width * 2 + 1];
            int[] r1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] g1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] b1 = new int[box1.Height * box1.Width * 2 + 1];
            d0 = Math.Sqrt(u * u + v * v);//计算截止频率d0

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    t[(2 * box1.Width) * j + 2 * i + 1] = 0.3 * r1[box1.Width * j + i] + 0.59 * g1[box1.Width * j + i] + 0.11 * b1[box1.Width * j + i];//给时域赋值
                    t[(2 * box1.Width) * j + 2 * i + 2] = 0.0;

                    if ((Math.Sqrt(i * i + j * j)) <= d0)
                    {
                        H[2 * j + (2 * box1.Width) * i + 1] = 0.0;
                    }
                    else
                    {
                        H[2 * j + (2 * box1.Width) * i + 1] = 1.0;
                    }
                    H[2 * j + (2 * box1.Width) * i + 2] = 0.0;
                }
            }

            fourier(t, box1.Height, box1.Width, 1);

            for (j = 1; j < box1.Height * box1.Width * 2; j += 2)
            {
                t[j] = t[j] * H[j] - t[j + 1] * H[j + 1];
                t[j + 1] = t[j] * H[j + 1] + t[j + 1] * H[j];
            }

            fourier(t, box1.Height, box1.Width, -1);

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    t[(2 * box1.Width) * j + 2 * i + 1] = Math.Sqrt(t[(2 * box1.Width) * j + 2 * i + 1] * t[(2 * box1.Width) * j + 2 * i + 1] + t[(2 * box1.Width) * j + 2 * i + 2] * t[(2 * box1.Width) * j + 2 * i + 2]);
                    if (max < t[(2 * box1.Width) * j + 2 * i + 1])
                    {
                        max = t[(2 * box1.Width) * j + 2 * i + 1];
                    }
                }
            }

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    r1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    g1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    b1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);

                    if (r1[box1.Width * j + i] < 0) r1[box1.Width * j + i] = 0;
                    if (r1[box1.Width * j + i] > 255) r1[box1.Width * j + i] = 255;
                    if (g1[box1.Width * j + i] < 0) g1[box1.Width * j + i] = 0;
                    if (g1[box1.Width * j + i] > 255) g1[box1.Width * j + i] = 255;
                    if (b1[box1.Width * j + i] < 0) b1[box1.Width * j + i] = 0;
                    if (b1[box1.Width * j + i] > 255) b1[box1.Width * j + i] = 255;

                    Color c = Color.FromArgb(r1[box1.Width * j + i], g1[box1.Width * j + i], b1[box1.Width * j + i]);
                    box2.SetPixel(i, j, c);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 梯形高通滤波ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            THFilter form_thf = new THFilter();
            form_thf.FormBorderStyle = FormBorderStyle.FixedSingle;//对话框边缘风格
            form_thf.StartPosition = FormStartPosition.CenterParent;//在父窗体的中间显示该对话框    
            form_thf.ShowDialog(this);//此处必须有this,否则模态对话框(垄断用户输入)不能显示                 
            int u = form_thf.weightX1;
            int v = form_thf.weightY1;
            int u1 = form_thf.weightX2;
            int v1 = form_thf.weightY2;
            bool flag2 = false;
            flag2 = form_thf.flag1;
            if (flag2 == true)
            {
                return;
            }
            int i, j;
            double max = 0.0, d0, d, d1;//中间变量
            Color c1 = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int[] r1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] g1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] b1 = new int[box1.Height * box1.Width * 2 + 1];

            double[] t = new double[box1.Height * box1.Width * 2 + 1];//分配存储器空间
            double[] H = new double[box1.Height * box1.Width * 2 + 1];

            d0 = Math.Sqrt(u * u + v * v);//计算截止频率d0
            d1 = Math.Sqrt(u1 * u1 + v1 * v1);//计算截止频率d1

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    t[(2 * box1.Width) * j + 2 * i + 1] = 0.3 * r1[box1.Width * j + i] + 0.59 * g1[box1.Width * j + i] + 0.11 * b1[box1.Width * j + i];//给时域赋值
                    t[(2 * box1.Width) * j + 2 * i + 2] = 0.0;

                    d = Math.Sqrt(i * i + j * j);
                    if (d < d0)
                    {
                        H[2 * j + (2 * box1.Width) * i + 1] = 0;
                        H[2 * j + (2 * box1.Width) * i + 2] = 0.0;
                    }
                    if (d > d1)
                    {
                        H[2 * j + (2 * box1.Width) * i + 1] = 1;
                        H[2 * j + (2 * box1.Width) * i + 2] = 0.0;
                    }
                    else
                    {
                        H[2 * j + (2 * box1.Width) * i + 1] = (d - d0) / (d1 - d0);
                        H[2 * j + (2 * box1.Width) * i + 2] = 0.0;
                    }
                }
            }

            fourier(t, box1.Height, box1.Width, 1);

            for (j = 1; j < box1.Height * box1.Width * 2; j += 2)
            {
                t[j] = t[j] * H[j] - t[j + 1] * H[j + 1];
                t[j + 1] = t[j] * H[j + 1] + t[j + 1] * H[j];
            }

            fourier(t, box1.Height, box1.Width, -1);

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    t[(2 * box1.Width) * j + 2 * i + 1] = Math.Sqrt(t[(2 * box1.Width) * j + 2 * i + 1] * t[(2 * box1.Width) * j + 2 * i + 1] + t[(2 * box1.Width) * j + 2 * i + 2] * t[(2 * box1.Width) * j + 2 * i + 2]);
                    if (max < t[(2 * box1.Width) * j + 2 * i + 1])
                    {
                        max = t[(2 * box1.Width) * j + 2 * i + 1];
                    }
                }
            }

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    r1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    g1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    b1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);

                    if (r1[box1.Width * j + i] < 0) r1[box1.Width * j + i] = 0;
                    if (r1[box1.Width * j + i] > 255) r1[box1.Width * j + i] = 255;
                    if (g1[box1.Width * j + i] < 0) g1[box1.Width * j + i] = 0;
                    if (g1[box1.Width * j + i] > 255) g1[box1.Width * j + i] = 255;
                    if (b1[box1.Width * j + i] < 0) b1[box1.Width * j + i] = 0;
                    if (b1[box1.Width * j + i] > 255) b1[box1.Width * j + i] = 255;

                    Color c = Color.FromArgb(r1[box1.Width * j + i], g1[box1.Width * j + i], b1[box1.Width * j + i]);
                    box2.SetPixel(i, j, c);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 布特沃斯高通滤波ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            BwFilterH form_bfh = new BwFilterH();
            form_bfh.FormBorderStyle = FormBorderStyle.FixedSingle;//对话框边缘风格
            form_bfh.StartPosition = FormStartPosition.CenterParent;//在父窗体的中间显示该对话框    
            form_bfh.ShowDialog(this);//此处必须有this,否则模态对话框(垄断用户输入)不能显示                 
            int u = form_bfh.weightX;
            int v = form_bfh.weightY;
            int n = form_bfh.weightN;
            bool flag2 = false;
            flag2 = form_bfh.flag1;
            if (flag2 == true)
            {
                return;
            }
            int i, j;
            double d0, d, max = 0.0;//中间变量
            Color c1 = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            double[] t = new double[box1.Height * box1.Width * 2 + 1];//分配存储器空间
            double[] H = new double[box1.Height * box1.Width * 2 + 1];
            int[] r1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] g1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] b1 = new int[box1.Height * box1.Width * 2 + 1];
            d0 = Math.Sqrt(u * u + v * v);//计算截止频率d0

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    t[(2 * box1.Width) * j + 2 * i + 1] = 0.3 * r1[box1.Width * j + i] + 0.59 * g1[box1.Width * j + i] + 0.11 * b1[box1.Width * j + i];//给时域赋值
                    t[(2 * box1.Width) * j + 2 * i + 2] = 0.0;

                    d = Math.Sqrt(i * i + j * j);
                    H[2 * j + (2 * box1.Width) * i + 1] = 1 / (1 + Math.Pow((d0 / d), (2 * n)));
                    H[2 * j + (2 * box1.Width) * i + 2] = 0.0;
                }
            }

            fourier(t, box1.Height, box1.Width, 1);

            for (j = 1; j < box1.Height * box1.Width * 2; j += 2)
            {
                t[j] = t[j] * H[j] - t[j + 1] * H[j + 1];
                t[j + 1] = t[j] * H[j + 1] + t[j + 1] * H[j];
            }

            fourier(t, box1.Height, box1.Width, -1);

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    t[(2 * box1.Width) * j + 2 * i + 1] = Math.Sqrt(t[(2 * box1.Width) * j + 2 * i + 1] * t[(2 * box1.Width) * j + 2 * i + 1] + t[(2 * box1.Width) * j + 2 * i + 2] * t[(2 * box1.Width) * j + 2 * i + 2]);
                    if (max < t[(2 * box1.Width) * j + 2 * i + 1])
                    {
                        max = t[(2 * box1.Width) * j + 2 * i + 1];
                    }
                }
            }

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    r1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    g1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    b1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);

                    if (r1[box1.Width * j + i] < 0) r1[box1.Width * j + i] = 0;
                    if (r1[box1.Width * j + i] > 255) r1[box1.Width * j + i] = 255;
                    if (g1[box1.Width * j + i] < 0) g1[box1.Width * j + i] = 0;
                    if (g1[box1.Width * j + i] > 255) g1[box1.Width * j + i] = 255;
                    if (b1[box1.Width * j + i] < 0) b1[box1.Width * j + i] = 0;
                    if (b1[box1.Width * j + i] > 255) b1[box1.Width * j + i] = 255;

                    Color c = Color.FromArgb(r1[box1.Width * j + i], g1[box1.Width * j + i], b1[box1.Width * j + i]);
                    box2.SetPixel(i, j, c);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 指数高通滤波ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            ZHFilter form_zhf = new ZHFilter();
            form_zhf.FormBorderStyle = FormBorderStyle.FixedSingle;//对话框边缘风格
            form_zhf.StartPosition = FormStartPosition.CenterParent;//在父窗体的中间显示该对话框    
            form_zhf.ShowDialog(this);//此处必须有this,否则模态对话框(垄断用户输入)不能显示  
            int u = form_zhf.weightX;
            int v = form_zhf.weightY;
            int n = form_zhf.weightN;
            bool flag2 = false;
            flag2 = form_zhf.flag1;
            if (flag2 == true)
            {
                return;
            }
            int i, j;
            double d0, d, max = 0.0;//中间变量
            Color c1 = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            double[] t = new double[box1.Height * box1.Width * 2 + 1];//分配存储器空间
            double[] H = new double[box1.Height * box1.Width * 2 + 1];
            int[] r1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] g1 = new int[box1.Height * box1.Width * 2 + 1];
            int[] b1 = new int[box1.Height * box1.Width * 2 + 1];
            d0 = Math.Sqrt(u * u + v * v);//计算截止频率d0

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    t[(2 * box1.Width) * j + 2 * i + 1] = 0.3 * r1[box1.Width * j + i] + 0.59 * g1[box1.Width * j + i] + 0.11 * b1[box1.Width * j + i];//给时域赋值
                    t[(2 * box1.Width) * j + 2 * i + 2] = 0.0;

                    d = Math.Sqrt(i * i + j * j);
                    H[2 * j + (2 * box1.Width) * i + 1] = Math.Exp(-Math.Pow((d0 / d), n));
                    H[2 * j + (2 * box1.Width) * i + 2] = 0.0;
                }
            }

            fourier(t, box1.Height, box1.Width, 1);

            for (j = 1; j < box1.Height * box1.Width * 2; j += 2)
            {
                t[j] = t[j] * H[j] - t[j + 1] * H[j + 1];
                t[j + 1] = t[j] * H[j + 1] + t[j + 1] * H[j];
            }

            fourier(t, box1.Height, box1.Width, -1);

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    t[(2 * box1.Width) * j + 2 * i + 1] = Math.Sqrt(t[(2 * box1.Width) * j + 2 * i + 1] * t[(2 * box1.Width) * j + 2 * i + 1] + t[(2 * box1.Width) * j + 2 * i + 2] * t[(2 * box1.Width) * j + 2 * i + 2]);
                    if (max < t[(2 * box1.Width) * j + 2 * i + 1])
                    {
                        max = t[(2 * box1.Width) * j + 2 * i + 1];
                    }
                }
            }

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    c1 = box1.GetPixel(i, j);
                    r1[box1.Width * j + i] = c1.R;
                    g1[box1.Width * j + i] = c1.G;
                    b1[box1.Width * j + i] = c1.B;

                    r1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    g1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);
                    b1[box1.Width * j + i] = (byte)(t[(2 * box1.Width) * j + 2 * i + 1] * 255.0 / max);

                    if (r1[box1.Width * j + i] < 0) r1[box1.Width * j + i] = 0;
                    if (r1[box1.Width * j + i] > 255) r1[box1.Width * j + i] = 255;
                    if (g1[box1.Width * j + i] < 0) g1[box1.Width * j + i] = 0;
                    if (g1[box1.Width * j + i] > 255) g1[box1.Width * j + i] = 255;
                    if (b1[box1.Width * j + i] < 0) b1[box1.Width * j + i] = 0;
                    if (b1[box1.Width * j + i] > 255) b1[box1.Width * j + i] = 255;

                    Color c = Color.FromArgb(r1[box1.Width * j + i], g1[box1.Width * j + i], b1[box1.Width * j + i]);
                    box2.SetPixel(i, j, c);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 小波行变换ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            int i, j;
            Color c1 = new Color();
            Color c2 = new Color();

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int nwide = box1.Width / 2;
            int r1, r2, g1, g2, b1, b2, rr, gg, bb;

            for (j = 0; j < box1.Height; j++)
            {
                for (i = 0; i < nwide; i++)
                {
                    int w = i * 2;
                    c1 = box1.GetPixel(w, j);
                    r1 = c1.R;
                    g1 = c1.G;
                    b1 = c1.B;

                    Color cc = Color.FromArgb(r1, g1, b1);
                    box2.SetPixel(i, j, cc);

                    c2 = box1.GetPixel(w + 1, j);
                    r2 = c2.R;
                    g2 = c2.G;
                    b2 = c2.B;

                    rr = Math.Abs(r2 - r1 + 128);
                    gg = g2 - g1 + 128;
                    bb = b2 - b1 + 128;

                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;

                    Color c = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(nwide + i, j, c);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }



        private void 小波列变换ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            int i, j;
            Color c1 = new Color();
            Color c2 = new Color();

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int nHeight = box1.Height / 2;
            int r1, r2, g1, g2, b1, b2, rr, gg, bb;

            for (i = 0; i < box1.Width; i++)
            {
                for (j = 0; j < nHeight; j++)
                {
                    int w = j * 2;
                    c1 = box1.GetPixel(i, w);
                    r1 = c1.R;
                    g1 = c1.G;
                    b1 = c1.B;

                    Color cc = Color.FromArgb(r1, g1, b1);
                    box2.SetPixel(i, j, cc);

                    c2 = box1.GetPixel(i, w + 1);
                    r2 = c2.R;
                    g2 = c2.G;
                    b2 = c2.B;

                    rr = Math.Abs(r2 - r1 + 128);
                    gg = g2 - g1 + 128;
                    bb = b2 - b1 + 128;

                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;

                    Color c = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, nHeight + j, c);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 小波逆变换ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            int n = 2;
            int i, j;
            Color c1 = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int[,] r1 = new int[300, 900];
            int[,] g1 = new int[300, 900];
            int[,] b1 = new int[300, 900];
            int[,] r2 = new int[300, 900];
            int[,] g2 = new int[300, 900];
            int[,] b2 = new int[300, 900];
            int[,] r3 = new int[300, 900];
            int[,] g3 = new int[300, 900];
            int[,] b3 = new int[300, 900];

            for (int k = n; k >= 1; k--)
            {
                int nwide = box1.Width / (int)Math.Pow(2, k);
                int nHeight = box1.Height / (int)Math.Pow(2, k);

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < box1.Width; i++)
                    {
                        c1 = box1.GetPixel(i, j);
                        r1[i, j] = c1.R;
                        g1[i, j] = c1.G;
                        b1[i, j] = c1.B;
                    }
                }

                for (i = 0; i < box1.Width / (int)Math.Pow(2, k - 1); i++)
                {
                    for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))) + nHeight; j++)
                    {
                        r1[i, j] = (int)Math.Abs(r1[i, j + nHeight] + r1[i, j] - 128);
                        g1[i, j] = (int)Math.Abs(g1[i, j + nHeight] + g1[i, j] - 128);
                        b1[i, j] = (int)Math.Abs(b1[i, j + nHeight] + b1[i, j] - 128);
                    }
                }

                for (i = 0; i < box1.Width / (int)Math.Pow(2, k - 1); i++)
                {
                    for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))) + nHeight; j++)
                    {
                        int m, h;
                        m = (int)Math.Abs(box1.Height * (1 - 1 / Math.Pow(2, (k - 1))));
                        h = (j - m) * 2;

                        r2[i, m + h] = r1[i, j];
                        g2[i, m + h] = g1[i, j];
                        b2[i, m + h] = b1[i, j];

                        r2[i, m + h + 1] = r1[i, j + nHeight];
                        g2[i, m + h + 1] = g1[i, j + nHeight];
                        b2[i, m + h + 1] = b1[i, j + nHeight];
                    }
                }

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < nwide - 1; i++)
                    {
                        r2[i + nwide, j] = (int)Math.Abs(r2[i + nwide, j] + r2[i, j] - 128);
                        g2[i + nwide, j] = (int)Math.Abs(g2[i + nwide, j] + g2[i, j] - 128);
                        b2[i + nwide, j] = (int)Math.Abs(b2[i + nwide, j] + b2[i, j] - 128);
                    }
                }

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < nwide; i++)
                    {
                        int w = i * 2;
                        r3[w, j] = r2[i, j];
                        g3[w, j] = g2[i, j];
                        b3[w, j] = b2[i, j];

                        r3[w + 1, j] = r2[i + nwide, j];
                        g3[w + 1, j] = g2[i + nwide, j];
                        b3[w + 1, j] = b2[i + nwide, j];
                    }
                }

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < box1.Width / (int)Math.Pow(2, k - 1); i++)
                    {
                        if (r3[i, j] < 0) r3[i, j] = 0;
                        if (r3[i, j] > 255) r3[i, j] = 255;
                        if (g3[i, j] < 0) g3[i, j] = 0;
                        if (g3[i, j] > 255) g3[i, j] = 255;
                        if (b3[i, j] < 0) b3[i, j] = 0;
                        if (b3[i, j] > 255) b3[i, j] = 255;

                        Color cc = Color.FromArgb(r3[i, j], g3[i, j], b3[i, j]);
                        box2.SetPixel(i, j, cc);
                    }
                }
                pictureBox2.Refresh();
                pictureBox2.Image = box2;
            }
        }

        private void 小波一次变换ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            int i, j;
            Color c1 = new Color();
            Color c2 = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int[,] r1 = new int[box1.Width, box1.Height * box1.Width];
            int[,] g1 = new int[box1.Width, box1.Height * box1.Width];
            int[,] b1 = new int[box1.Width, box1.Height * box1.Width];
            int[,] r2 = new int[box1.Width, box1.Height * box1.Width];
            int[,] g2 = new int[box1.Width, box1.Height * box1.Width];
            int[,] b2 = new int[box1.Width, box1.Height * box1.Width];

            int n = 2;
            for (int k = 1; k <= n; k++)
            {
                int nwide = box1.Width / (int)Math.Pow(2, k);
                int nHeight = box1.Height / (int)Math.Pow(2, k);

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < nwide; i++)
                    {
                        int w = i * 2;
                        c1 = box1.GetPixel(w, j);
                        r1[i, j] = c1.R;
                        g1[i, j] = c1.G;
                        b1[i, j] = c1.B;

                        c2 = box1.GetPixel(w + 1, j);
                        r1[i + nwide, j] = c2.R;
                        g1[i + nwide, j] = c2.G;
                        b1[i + nwide, j] = c2.B;
                    }
                }

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < nwide - 1; i++)
                    {
                        r1[i + nwide - 1, j] = (int)Math.Abs(r1[i + nwide - 1, j] - r1[i, j] + 128);
                        g1[i + nwide - 1, j] = (int)Math.Abs(g1[i + nwide - 1, j] - g1[i, j] + 128);
                        b1[i + nwide - 1, j] = (int)Math.Abs(b1[i + nwide - 1, j] - b1[i, j] + 128);
                    }
                }

                for (i = 0; i < (int)Math.Abs(box1.Width / Math.Pow(2, k - 1)); i++)
                {
                    for (j = (int)Math.Abs(box1.Height * (1 - 1 / Math.Pow(2, (k - 1)))); j < (int)Math.Abs(box1.Height * (1 - 1 / Math.Pow(2, (k - 1)))) + nHeight; j++)
                    {
                        int m, h;
                        m = (int)Math.Abs(box1.Height * (1 - 1 / Math.Pow(2, (k - 1))));
                        h = (j - m) * 2;

                        r2[i, j] = r1[i, m + h];
                        g2[i, j] = g1[i, m + h];
                        b2[i, j] = b1[i, m + h];

                        r2[i, j + nHeight] = r1[i, m + h + 1];
                        g2[i, j + nHeight] = g1[i, m + h + 1];
                        b2[i, j + nHeight] = b1[i, m + h + 1];
                    }
                }

                for (i = 0; i < (int)Math.Abs(box1.Width / Math.Pow(2, k - 1)); i++)
                {
                    for (j = (int)Math.Abs(box1.Height * (1 - 1 / Math.Pow(2, (k - 1)))); j < (int)Math.Abs(box1.Height * (1 - 1 / Math.Pow(2, (k - 1)))) + nHeight; j++)
                    {
                        r2[i, j + nHeight] = (int)Math.Abs(r2[i, j + nHeight] - r2[i, j] + 128);
                        g2[i, j + nHeight] = (int)Math.Abs(g2[i, j + nHeight] - g2[i, j] + 128);
                        b2[i, j + nHeight] = (int)Math.Abs(b2[i, j + nHeight] - b2[i, j] + 128);
                    }
                }

                for (j = box1.Height * (1 - 1 / (int)Math.Pow(2, (k - 1))); j < box1.Height; j++)
                {
                    for (i = 0; i < box1.Width / (int)Math.Pow(2, k - 1); i++)
                    {
                        if (r2[i, j] < 0) r2[i, j] = 0;
                        if (r2[i, j] > 255) r2[i, j] = 255;
                        if (g2[i, j] < 0) g2[i, j] = 0;
                        if (g2[i, j] > 255) g2[i, j] = 255;
                        if (b2[i, j] < 0) b2[i, j] = 0;
                        if (b2[i, j] > 255) b2[i, j] = 255;

                        Color cc = Color.FromArgb(r2[i, j], g2[i, j], b2[i, j]);
                        box2.SetPixel(i, j, cc);
                    }
                }
                pictureBox2.Refresh();
                pictureBox2.Image = box2;
            }
        }

        private void 小波二次变换ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.ActiveCImage = new CImage(this.openFileDialog1.FileName);
            int i, j;
            Color c1 = new Color();
            Color c2 = new Color();

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int nwide = box1.Width / 2;
            int nwide1 = box1.Width / 4;
            int nHeight = box1.Height / 2;
            int nHeight1 = box1.Height / 4;
            int r1, r2, g1, g2, b1, b2, rr, gg, bb;

            for (j = 0; j < nHeight; j++)
            {
                for (i = 0; i < nwide; i++)
                {
                    int w = i * 2;
                    int p = j * 2;

                    c1 = box1.GetPixel(w, p);
                    r1 = c1.R;
                    g1 = c1.G;
                    b1 = c1.B;

                    c2 = box1.GetPixel(w + 1, p + 1);
                    r2 = c2.R;
                    g2 = c2.G;
                    b2 = c2.B;

                    rr = Math.Abs(r2 - r1 + 128);
                    gg = g2 - g1 + 128;
                    bb = b2 - b1 + 128;

                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;

                    Color c = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(nwide + i, nHeight + j, c);
                    box2.SetPixel(i, nHeight + j, c);
                    box2.SetPixel(nwide + i, j, c);
                }
            }

            for (j = 0; j < nHeight1; j++)
            {
                for (i = 0; i < nwide1; i++)
                {
                    int w = i * 4;
                    int p = j * 4;

                    c1 = box1.GetPixel(w, p);
                    r1 = c1.R;
                    g1 = c1.G;
                    b1 = c1.B;

                    Color cc = Color.FromArgb(r1, g1, b1);
                    box2.SetPixel(i, j, cc);

                    c2 = box1.GetPixel(w + 1, p + 1);
                    r2 = c2.R;
                    g2 = c2.G;
                    b2 = c2.B;

                    rr = Math.Abs(r2 - r1 + 128);
                    gg = g2 - g1 + 128;
                    bb = b2 - b1 + 128;

                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;

                    Color c = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(nwide1 + i, nHeight1 + j, c);
                    box2.SetPixel(i, nHeight1 + j, c);
                    box2.SetPixel(nwide1 + i, j, c);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 垂直镜像ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int rr, gg, bb;
            int[, ,] pic = new int[600, 600, 3];
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    pic[i, j, 0] = c.R;
                    pic[i, j, 1] = c.G;
                    pic[i, j, 2] = c.B;
                }
            }

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    rr = pic[i, box1.Height - j, 0];
                    gg = pic[i, box1.Height - j, 1];
                    bb = pic[i, box1.Height - j, 2];
                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }

            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 缩放ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SuoFang frm = new SuoFang();
            frm.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm.StartPosition = FormStartPosition.Manual;

            frm.ShowDialog(this);

            float n = frm.SuoFang_n;//模式对话框传值
            if (frm.p == 1)//ｃｏｎｃｅｌｌ功能判断
            {
                return;

            }

            int[, ,] pic = new int[600, 600, 3];
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(pictureBox1.Image);
            Graphics g = this.pictureBox2.CreateGraphics();
            g.Clear(pictureBox1.BackColor);

            g.DrawImage(box1, 0, 0, (int)box2.Width * n, (int)box2.Height * n);
        }

        private void 转置ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int rr, gg, bb;
            int[, ,] pic = new int[600, 600, 3];
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    pic[i, j, 0] = c.R;
                    pic[i, j, 1] = c.G;
                    pic[i, j, 2] = c.B;
                }
            }

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    rr = pic[j, i, 0];
                    gg = pic[j, i, 1];
                    bb = pic[j, i, 2];
                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }

            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 旋转ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width * 2, box1.Height * 2);
            int rr, gg, bb;
            int k1, k2;
            const double pi = 3.14159;
            int[, ,] pic = new int[600, 600, 3];
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    pic[i, j, 0] = c.R;
                    pic[i, j, 1] = c.G;
                    pic[i, j, 2] = c.B;
                }
            }
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    rr = pic[i, j, 0];
                    gg = pic[i, j, 1];
                    bb = pic[i, j, 2];
                    Color c1 = Color.FromArgb(rr, gg, bb);
                    k1 = (int)(i * Math.Cos(pi / 2) + j * Math.Sin(pi / 2));
                    k2 = (int)(-i * Math.Sin(pi / 2) + j * Math.Cos(pi / 2)) + box1.Width;
                    if (k1 > 0 & k1 < box1.Width & k2 > 0 & k2 < box1.Height)

                        box2.SetPixel(k1, k2, c1);

                }

            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void 非0元素取1法ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            double num = 1;
            int r, g, b;
            Color cc1 = Color.FromArgb(255, 255, 255);
            Color cc2 = Color.FromArgb(0, 0, 0);
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    g = c.G;
                    b = c.B;
                    if (r >= num)
                        r = 255;
                    else
                        r = 0;
                    if (g >= num)
                        g = 255;
                    else
                        g = 0;
                    if (b >= num)
                        b = 255;
                    else
                        b = 0;
                    Color c1 = Color.FromArgb(r, g, b);
                    box2.SetPixel(i, j, c1);


                }

            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 固定阈值ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GuDing frm2 = new GuDing();
            frm2.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm2.StartPosition = FormStartPosition.CenterParent;
            frm2.ShowDialog(this);
            int n = frm2.GuDing_n;
            if (frm2.p == 1)
            {
                return;

            }
            int r, g, b;
            Color cc1 = Color.FromArgb(255, 255, 255);
            Color cc2 = Color.FromArgb(0, 0, 0);
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    g = c.G;
                    b = c.B;
                    if (r >= n)
                        r = 255;
                    else
                        r = 0;
                    if (g >= n)
                        g = 255;
                    else
                        g = 0;
                    if (b >= n)
                        b = 255;
                    else
                        b = 0;
                    Color c1 = Color.FromArgb(r, g, b);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 双固定阈值ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ShuangYu frm3 = new ShuangYu();
            frm3.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm3.StartPosition = FormStartPosition.CenterParent;
            frm3.ShowDialog(this);
            double n1 = frm3.ShuangYu_n1;
            double n2 = frm3.ShuangYu_n2;
            //double num1 = 100;
            //double num2 = 200;
            if (frm3.p == 1)
            {
                return;
            }
            int r, g, b;
            Color cc1 = Color.FromArgb(255, 255, 255);
            Color cc2 = Color.FromArgb(0, 0, 0);
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    g = c.G;
                    b = c.B;
                    if (r >= n2 || r <= n1)
                        r = 0;
                    else
                        r = 255;
                    if (g >= n2 || g <= n1)
                        g = 0;
                    else
                        g = 255;
                    if (b >= n2 || b <= n1)
                        b = 0;
                    else
                        b = 255;
                    Color c1 = Color.FromArgb(r, g, b);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 反色变换ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width + 20, box1.Height + 20);
            int rr, r;
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    rr = 255 - r;
                    Color c1 = Color.FromArgb(rr, rr, rr);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 窗口灰度变换ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ChuangKouBianHuan ChuangKou = new ChuangKouBianHuan();
            ChuangKou.FormBorderStyle = FormBorderStyle.FixedDialog;
            ChuangKou.StartPosition = FormStartPosition.CenterParent;
            ChuangKou.ShowDialog(this);
            double n1 = ChuangKou.XiaXian;
            double n2 = ChuangKou.ShangXian;

            //double num1 = 100;
            //double num2 = 200;
            if (ChuangKou.p == 1)
            {
                return;
            }
            int r, g, b;
            Color cc1 = Color.FromArgb(255, 255, 255);
            Color cc2 = Color.FromArgb(0, 0, 0);
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    g = c.G;
                    b = c.B;
                    if (r < n1)
                        r = 0;
                    else if (r > n2)
                        r = 255;
                    if (b < n1)
                        b = 0;
                    else if (b > n2)
                        b = 255;
                    if (g < n1)
                        g = 0;
                    else if (g > n2)
                        g = 255;

                    Color c1 = Color.FromArgb(r, g, b);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 分段线性变换ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FenDuanXianXing FenDuan = new FenDuanXianXing();
            Error frm1 = new Error();
            FenDuan.FormBorderStyle = FormBorderStyle.FixedDialog;
            FenDuan.StartPosition = FormStartPosition.CenterParent;
            FenDuan.ShowDialog(this);
            int x1 = FenDuan.x1;
            int y1 = FenDuan.y1;
            int x2 = FenDuan.x2;
            int y2 = FenDuan.y2;
            if (FenDuan.p == 1)
            {
                return;
            }


            int r, g, b;
            Color cc1 = Color.FromArgb(255, 255, 255);
            Color cc2 = Color.FromArgb(0, 0, 0);
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int[] bMap = new int[256];
            if (x1 < 0 || x2 == x1 || x2 > 255)
            {
                frm1.FormBorderStyle = FormBorderStyle.FixedDialog;
                frm1.StartPosition = FormStartPosition.CenterParent;
                frm1.ShowDialog(this);
            }
            else
            {
                for (int i = 0; i < box1.Width; i++)
                {
                    for (int j = 0; j < box1.Height; j++)
                    {
                        c = box1.GetPixel(i, j);
                        r = c.R;
                        g = c.G;
                        b = c.B;

                        if (r <= x1)
                            r = y1 * r / x1;
                        else if (x1 < r && r <= x2)
                            r = (y2 - y1) * (r - x1) / (x2 - x1) + y1;
                        else if (x2 < r && r < 255)
                            r = (255 - y2) * (r - x2) / (255 - x2) + y2;

                        if (b <= x1)
                            b = y1 * b / x1;
                        else if (x1 < b && b <= x2)
                            b = (y2 - y1) * (b - x1) / (x2 - x1) + y1;
                        else if (x2 < b && b < 255)
                            b = (255 - y2) * (b - x2) / (255 - x2) + y2;

                        if (g <= x1)
                            g = y1 * g / x1;
                        else if (x1 < g && g <= x2)
                            g = (y2 - y1) * (g - x1) / (x2 - x1) + y1;
                        else if (x2 < g && g < 255)
                            g = (255 - y2) * (g - x2) / (255 - x2) + y2;


                        Color c1 = Color.FromArgb(r, g, b);
                        box2.SetPixel(i, j, c1);
                    }
                }
                pictureBox2.Refresh();
                pictureBox2.Image = box2;
            }
        }

        private void 图像直方图ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            int[,] h = new int[400, 400];
            int[] t = new int[300];
            Color c = Color.FromArgb(0);
            int i, j;
            int r;
            int max = 0;
            Bitmap pic = new Bitmap(pictureBox1.Image);
            for (i = 1; i < pictureBox1.Image.Width; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height; j++)
                {
                    c = pic.GetPixel(i, j);
                    r = c.R;
                    h[i, j] = r;
                }
            }
            for (i = 1; i < pictureBox1.Image.Width; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height; j++)
                {
                    for (r = 0; r < 255; r++)
                    {
                        if (h[i, j] == r)
                        {
                            t[r] = t[r] + 1;
                        }
                    }
                }
            }
            //获得直方图的高度
            max = t[0];
            for (i = 0; i < t.Length - 1; i++)
            {

                if (t[i] > max)
                {
                    max = t[i];
                }
            }
            max = max / 2 + 1;
            Bitmap box2 = new Bitmap(255, max);
            for (r = 0; r < 255; r++)
            {
                for (j = 1; j < t[r]; j++)
                {
                    box2.SetPixel(r, max - j / 2 - 1, c);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 分布均衡化ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width + 20, box1.Height + 20);
            Bitmap temp = new Bitmap(box1.Width, box1.Height);
            Bitmap process = (Bitmap)this.pictureBox1.Image;
            int[] cr = new int[256];
            int[] cg = new int[256];
            int[] cb = new int[256];
            int numofpixel = box1.Height * box1.Width;
            Color pixel;
            for (int x = 0; x < box1.Width; x++)
            {
                for (int y = 0; y < box1.Height; y++)
                {
                    pixel = process.GetPixel(x, y);
                    for (int i = 1; i < 256; i++)
                    {
                        if (pixel.R == i)
                        {
                            cr[i] += 1;
                        }
                        if (pixel.G == i)
                        {
                            cg[i] += 1;
                        }
                        if (pixel.B == i)
                        {
                            cb[i] += 1;
                        }
                    }
                }
            }
            for (int i = 0; i < 255; i++)
            {
                cr[i + 1] = cr[i] + cr[i + 1];
                cg[i + 1] = cg[i] + cg[i + 1];
                cb[i + 1] = cb[i] + cb[i + 1];
            }

            for (int x = 0; x < box1.Width; x++)
            {
                for (int y = 0; y < box1.Height; y++)
                {
                    pixel = process.GetPixel(x, y);
                    int tR = cr[pixel.R] * 255 / numofpixel;
                    int tG = cg[pixel.G] * 255 / numofpixel;
                    int tB = cb[pixel.B] * 255 / numofpixel;

                    temp.SetPixel(x, y, Color.FromArgb(tR, tG, tB));
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = temp;
        }

        private void 二值图像的黑白点噪声滤波ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);//把图片框中的图片给一个Bitmap类型
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int cc, r1, r2, r3, r4, r5, r6, r7, r8;
            int averg;
            for (i = 1; i < pictureBox1.Image.Width - 2; i += 1)
            {
                for (j = 1; j < pictureBox1.Image.Height - 2; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    cc = c.R;
                    c = box1.GetPixel(i + 1, j);
                    r1 = c.R;
                    c = box1.GetPixel(i - 1, j);
                    r2 = c.R;
                    c = box1.GetPixel(i - 1, j + 1);
                    r3 = c.R;
                    c = box1.GetPixel(i - 1, j - 1);
                    r4 = c.R;
                    c = box1.GetPixel(i + 1, j - 1);
                    r5 = c.R;
                    c = box1.GetPixel(i + 1, j + 1);
                    r6 = c.R;
                    c = box1.GetPixel(i, j + 1);
                    r7 = c.R;
                    c = box1.GetPixel(i, j - 1);
                    r8 = c.R;
                    //求周围8近邻均值
                    averg = (int)((r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8) / 8);
                    if (Math.Abs(averg - cc) > 127.5)
                    {
                        cc = averg;
                        Color c1 = Color.FromArgb(cc, cc, cc);//用FromArgb方法有颜色分量值创建Color结构
                        box2.SetPixel(i, j, c1);
                    }
                    else
                    {
                        Color c2 = Color.FromArgb(cc, cc, cc);//用FromArgb方法有颜色分量值创建Color结构
                        box2.SetPixel(i, j, c2);
                    }
                }
            }
            pictureBox2.Refresh();//刷新
            pictureBox2.Image = box2;//图片赋到图片框2中
        }

        private void 邻域ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);//把图片框中的图片给一个Bitmap类型
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int cc, r1, r2, r3, r4;
            for (i = 1; i < pictureBox1.Image.Width - 2; i += 1)
            {
                for (j = 1; j < pictureBox1.Image.Height - 2; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    cc = c.R;
                    c = box1.GetPixel(i + 1, j);
                    r1 = c.R;
                    c = box1.GetPixel(i - 1, j);
                    r2 = c.R;
                    c = box1.GetPixel(i - 1, j + 1);
                    r3 = c.R;
                    c = box1.GetPixel(i - 1, j - 1);
                    r4 = c.R;
                    //4连接的情况下，消除上下左右都为255（白点）的孤立黑点
                    if ((r1 == 255) && (r2 == 255) && (r3 == 255) && (r4 == 255))
                    {
                        Color c1 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c1);
                    }
                    else
                    {
                        Color c2 = Color.FromArgb(cc, cc, cc);
                        box2.SetPixel(i, j, c2);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 邻域ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);//把图片框中的图片给一个Bitmap类型
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int cc, r1, r2, r3, r4, r5, r6, r7, r8;
            for (i = 1; i < pictureBox1.Image.Width - 2; i += 1)
            {
                for (j = 1; j < pictureBox1.Image.Height - 2; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    cc = c.R;
                    c = box1.GetPixel(i + 1, j);
                    r1 = c.R;
                    c = box1.GetPixel(i - 1, j);
                    r2 = c.R;
                    c = box1.GetPixel(i - 1, j + 1);
                    r3 = c.R;
                    c = box1.GetPixel(i - 1, j - 1);
                    r4 = c.R;
                    c = box1.GetPixel(i + 1, j - 1);
                    r5 = c.R;
                    c = box1.GetPixel(i + 1, j + 1);
                    r6 = c.R;
                    c = box1.GetPixel(i, j + 1);
                    r7 = c.R;
                    c = box1.GetPixel(i, j - 1);
                    r8 = c.R;
                    //8连接的情况下，消除上下左右都为255（白点）的孤立黑点
                    if ((r1 == 255) && (r2 == 255) && (r3 == 255) && (r4 == 255) && (r5 == 255) && (r6 == 255) && (r7 == 255) && (r8 == 255))
                    {
                        Color c1 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c1);
                    }
                    else
                    {
                        Color c2 = Color.FromArgb(cc, cc, cc);
                        box2.SetPixel(i, j, c2);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 邻域平均法ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int rr, gg, bb, r1, g1, b1, rx, gx, bx, k1, k2;

            for (i = 1; i < pictureBox1.Image.Width - 1; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height - 1; j++)
                {
                    rx = 0; gx = 0; bx = 0;
                    for (k1 = -1; k1 <= 1; k1++)
                    {
                        for (k2 = -1; k2 <= 1; k2++)
                        {
                            c = box1.GetPixel(i + k1, j + k2);
                            r1 = c.R;
                            g1 = c.G;
                            b1 = c.B;

                            rx = rx + r1;
                            gx = gx + g1;
                            bx = bx + b1;
                        }
                    }
                    rr = (int)(rx / 9);
                    gg = (int)(gx / 9);
                    bb = (int)(bx / 9);

                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;

                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 均值滤波ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int cr, cg, cb;
            int r1, r2, r3, r4, r5, r6, r7, r8;
            int g1, g2, g3, g4, g5, g6, g7, g8;
            int b1, b2, b3, b4, b5, b6, b7, b8;
            int avergR, avergG, avergB;
            for (i = 1; i < pictureBox1.Image.Width - 2; i += 1)
            {
                for (j = 1; j < pictureBox1.Image.Height - 2; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    cr = c.R; cg = c.G; cb = c.B;
                    c = box1.GetPixel(i + 1, j);
                    r1 = c.R; g1 = c.G; b1 = c.B;
                    c = box1.GetPixel(i - 1, j);
                    r2 = c.R; g2 = c.G; b2 = c.B;
                    c = box1.GetPixel(i - 1, j + 1);
                    r3 = c.R; g3 = c.G; b3 = c.B;
                    c = box1.GetPixel(i - 1, j - 1);
                    r4 = c.R; g4 = c.G; b4 = c.B;
                    c = box1.GetPixel(i + 1, j - 1);
                    r5 = c.R; g5 = c.G; b5 = c.B;
                    c = box1.GetPixel(i + 1, j + 1);
                    r6 = c.R; g6 = c.G; b6 = c.B;
                    c = box1.GetPixel(i, j + 1);
                    r7 = c.R; g7 = c.G; b7 = c.B;
                    c = box1.GetPixel(i, j - 1);
                    r8 = c.R; g8 = c.G; b8 = c.B;
                    //求周围8近邻均值
                    avergR = (int)((r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8) / 8);
                    avergG = (int)((g1 + g2 + g3 + g4 + g5 + g6 + g7 + g8) / 8);
                    avergB = (int)((b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8) / 8);
                    cr = avergR; cg = avergG; cb = avergB;
                    Color c1 = Color.FromArgb(cr, cg, cb);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 超限邻域平均法默认T100ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ChaoXian frm13 = new ChaoXian();
            frm13.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm13.StartPosition = FormStartPosition.CenterParent;
            frm13.ShowDialog(this);
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int T = frm13.ChaoXian_T;//取得阀值
            int i, j;
            int cr, r1, r2, r3, r4, r5, r6, r7, r8;
            int cg, g1, g2, g3, g4, g5, g6, g7, g8;
            int cb, b1, b2, b3, b4, b5, b6, b7, b8;
            int avergR, avergG, avergB;
            for (i = 1; i < pictureBox1.Image.Width - 2; i += 1)
            {
                for (j = 1; j < pictureBox1.Image.Height - 2; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    cr = c.R; cg = c.G; cb = c.B;
                    c = box1.GetPixel(i + 1, j);
                    r1 = c.R; g1 = c.G; b1 = c.B;
                    c = box1.GetPixel(i - 1, j);
                    r2 = c.R; g2 = c.G; b2 = c.B;
                    c = box1.GetPixel(i - 1, j + 1);
                    r3 = c.R; g3 = c.G; b3 = c.B;
                    c = box1.GetPixel(i - 1, j - 1);
                    r4 = c.R; g4 = c.G; b4 = c.B;
                    c = box1.GetPixel(i + 1, j - 1);
                    r5 = c.R; g5 = c.G; b5 = c.B;
                    c = box1.GetPixel(i + 1, j + 1);
                    r6 = c.R; g6 = c.G; b6 = c.B;
                    c = box1.GetPixel(i, j + 1);
                    r7 = c.R; g7 = c.G; b7 = c.B;
                    c = box1.GetPixel(i, j - 1);
                    r8 = c.R; g8 = c.G; b8 = c.B;
                    //求周围8近邻均值
                    avergR = (int)((r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8) / 8);
                    avergG = (int)((g1 + g2 + g3 + g4 + g5 + g6 + g7 + g8) / 8);
                    avergB = (int)((b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8) / 8);
                    if (Math.Abs(((avergR - cr) + (avergB - cb) + (avergG - cg)) / 3) > T)
                    {
                        Color c1 = Color.FromArgb(avergR, avergG, avergB);
                        box2.SetPixel(i, j, c1);
                    }
                    else
                    {
                        Color c2 = Color.FromArgb(cr, cg, cb);
                        box2.SetPixel(i, j, c2);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void nN均值滤波器ToolStripMenuItem_Click(object sender, EventArgs e)
        {

            nn frm14 = new nn();
            Error frm1 = new Error();
            frm14.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm14.StartPosition = FormStartPosition.CenterParent;
            frm14.ShowDialog(this);
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int n = frm14.nn_n;//获取n值
            int i, j, n2;
            if (n < 3 || n % 2 != 1)//检查取值是否为3.5.7等的奇数
            {
                frm1.FormBorderStyle = FormBorderStyle.FixedDialog;
                frm1.StartPosition = FormStartPosition.CenterParent;
                frm1.ShowDialog(this);
            }
            else
            {
                n2 = (n - 1) / 2;
                int rr, gg, bb, r1, g1, b1, k1, k2, m, m2, m3, sumr, sumg, sumb;
                int[] mado = new int[1000];
                int[] mado2 = new int[1000];
                int[] mado3 = new int[1000];
                for (i = n2; i < pictureBox1.Image.Width - n2; i++)
                {
                    for (j = n2; j < pictureBox1.Image.Height - n2; j++)
                    {
                        //求N*N屏蔽窗口内的总和sumr,sumg和sumb
                        sumr = 0; sumg = 0; sumb = 0;
                        m = 0; m2 = 0; m3 = 0;
                        for (k1 = i - n2; k1 <= i + n2; k1++)
                        {
                            for (k2 = j - n2; k2 <= j + n2; k2++)
                            {
                                c = box1.GetPixel(k1, k2);
                                r1 = c.R;
                                g1 = c.G;
                                b1 = c.B;
                                mado[m] = r1;
                                mado2[m2] = g1;
                                mado3[m3] = b1;
                                m = m + 1; m2 = m2 + 1; m3 = m3 + 1;
                                sumr += mado[m]; sumg += mado2[m2]; sumb += mado3[m3];
                            }
                        }
                        //把N*N屏蔽窗口内的平均值四舍五入后作为显示图像的像素值
                        rr = (int)((float)sumr / (n * n) + 0.5);
                        gg = (int)((float)sumg / (n * n) + 0.5);
                        bb = (int)((float)sumb / (n * n) + 0.5);
                        Color c1 = Color.FromArgb(rr, gg, bb);
                        box2.SetPixel(i, j, c1);
                    }
                }
                pictureBox2.Refresh();
                pictureBox2.Image = box2;
            }
        }

        private void 选择式掩模平滑ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int cr, cg, cb;
            int n, nminr, bminr, nming, bming, nminb, bminb;
            int[] jir = new int[9];
            int[] jig = new int[9];
            int[] jib = new int[9];
            int[] meanr = new int[9];
            int[] meang = new int[9];
            int[] meanb = new int[9];
            int[] bunsanr = new int[9];
            int[] bunsang = new int[9];
            int[] bunsanb = new int[9];
            for (i = 2; i < pictureBox1.Image.Width - 3; i += 1)
            {
                for (j = 2; j < pictureBox1.Image.Height - 3; j += 1)
                {
                    //求9种近邻区域的均值及其方差
                    //第1近邻区域
                    c = box1.GetPixel(i, j);
                    jir[0] = c.R; jig[0] = c.G; jib[0] = c.B;
                    c = box1.GetPixel(i + 1, j);
                    jir[1] = c.R; jig[1] = c.G; jib[1] = c.B;
                    c = box1.GetPixel(i - 1, j);
                    jir[2] = c.R; jig[2] = c.G; jib[2] = c.B;
                    c = box1.GetPixel(i - 1, j + 1);
                    jir[3] = c.R; jig[3] = c.G; jib[3] = c.B;
                    c = box1.GetPixel(i - 1, j - 1);
                    jir[4] = c.R; jig[4] = c.G; jib[4] = c.B;
                    c = box1.GetPixel(i + 1, j - 1);
                    jir[5] = c.R; jig[5] = c.G; jib[5] = c.B;
                    c = box1.GetPixel(i + 1, j + 1);
                    jir[6] = c.R; jig[6] = c.G; jib[6] = c.B;
                    c = box1.GetPixel(i, j + 1);
                    jir[7] = c.R; jig[7] = c.G; jib[7] = c.B;
                    c = box1.GetPixel(i, j - 1);
                    jir[8] = c.R; jig[8] = c.G; jib[8] = c.B;
                    meanr[0] = (int)(jir[0] + jir[1] + jir[2] + jir[3] + jir[4] + jir[5] + jir[6] + jir[7] + jir[8]) / 9;
                    meang[0] = (int)(jig[0] + jig[1] + jig[2] + jig[3] + jig[4] + jig[5] + jig[6] + jig[7] + jig[8]) / 9;
                    meanb[0] = (int)(jib[0] + jib[1] + jib[2] + jib[3] + jib[4] + jib[5] + jib[6] + jib[7] + jib[8]) / 9;
                    bunsanr[0] = 0; bunsang[0] = 0; bunsanb[0] = 0;
                    for (n = 0; n <= 8; n++)
                    {
                        bunsanr[0] += jir[n] * jir[n] - meanr[0] * meanr[0];
                        bunsang[0] += jig[n] * jig[n] - meang[0] * meang[0];
                        bunsanb[0] += jib[n] * jib[n] - meanb[0] * meanb[0];
                    }
                    //第2近邻区域
                    c = box1.GetPixel(i, j);
                    jir[0] = c.R; jig[0] = c.G; jib[0] = c.B;
                    c = box1.GetPixel(i - 1, j - 1);
                    jir[1] = c.R; jig[1] = c.G; jib[1] = c.B;
                    c = box1.GetPixel(i, j - 1);
                    jir[2] = c.R; jig[2] = c.G; jib[2] = c.B;
                    c = box1.GetPixel(i + 1, j - 1);
                    jir[3] = c.R; jig[3] = c.G; jib[3] = c.B;
                    c = box1.GetPixel(i - 1, j - 2);
                    jir[4] = c.R; jig[4] = c.G; jib[4] = c.B;
                    c = box1.GetPixel(i, j - 2);
                    jir[5] = c.R; jig[5] = c.G; jib[5] = c.B;
                    c = box1.GetPixel(i + 1, j - 2);
                    jir[6] = c.R; jig[6] = c.G; jib[6] = c.B;

                    meanr[1] = (int)(jir[0] + jir[1] + jir[2] + jir[3] + jir[4] + jir[5] + jir[6]) / 7;
                    meang[1] = (int)(jig[0] + jig[1] + jig[2] + jig[3] + jig[4] + jig[5] + jig[6]) / 7;
                    meanb[1] = (int)(jib[0] + jib[1] + jib[2] + jib[3] + jib[4] + jib[5] + jib[6]) / 7;
                    bunsanr[1] = 0; bunsang[1] = 0; bunsanb[1] = 0;
                    for (n = 0; n <= 6; n++)
                    {
                        bunsanr[1] += jir[n] * jir[n] - meanr[1] * meanr[1];
                        bunsang[1] += jig[n] * jig[n] - meang[1] * meang[1];
                        bunsanb[1] += jib[n] * jib[n] - meanb[1] * meanb[1];
                    }
                    //第3近邻区域
                    c = box1.GetPixel(i, j);
                    jir[0] = c.R; jig[0] = c.G; jib[0] = c.B;
                    c = box1.GetPixel(i - 2, j - 1);
                    jir[1] = c.R; jig[1] = c.G; jib[1] = c.B;
                    c = box1.GetPixel(i - 2, j);
                    jir[2] = c.R; jig[2] = c.G; jib[2] = c.B;
                    c = box1.GetPixel(i - 2, j + 1);
                    jir[3] = c.R; jig[3] = c.G; jib[3] = c.B;
                    c = box1.GetPixel(i - 1, j - 1);
                    jir[4] = c.R; jig[4] = c.G; jib[4] = c.B;
                    c = box1.GetPixel(i - 1, j);
                    jir[5] = c.R; jig[5] = c.G; jib[5] = c.B;
                    c = box1.GetPixel(i - 1, j + 1);
                    jir[6] = c.R; jig[6] = c.G; jib[6] = c.B;

                    meanr[2] = (int)(jir[0] + jir[1] + jir[2] + jir[3] + jir[4] + jir[5] + jir[6]) / 7;
                    meang[2] = (int)(jig[0] + jig[1] + jig[2] + jig[3] + jig[4] + jig[5] + jig[6]) / 7;
                    meanb[2] = (int)(jib[0] + jib[1] + jib[2] + jib[3] + jib[4] + jib[5] + jib[6]) / 7;
                    bunsanr[2] = 0; bunsang[2] = 0; bunsanb[2] = 0;
                    for (n = 0; n <= 6; n++)
                    {
                        bunsanr[2] += jir[n] * jir[n] - meanr[2] * meanr[2];
                        bunsang[2] += jig[n] * jig[n] - meang[2] * meang[2];
                        bunsanb[2] += jib[n] * jib[n] - meanb[2] * meanb[2];
                    }
                    //第4近邻区域
                    c = box1.GetPixel(i, j);
                    jir[0] = c.R; jig[0] = c.G; jib[0] = c.B;
                    c = box1.GetPixel(i - 1, j + 1);
                    jir[1] = c.R; jig[1] = c.G; jib[1] = c.B;
                    c = box1.GetPixel(i, j + 1);
                    jir[2] = c.R; jig[2] = c.G; jib[2] = c.B;
                    c = box1.GetPixel(i + 1, j + 1);
                    jir[3] = c.R; jig[3] = c.G; jib[3] = c.B;
                    c = box1.GetPixel(i - 1, j + 2);
                    jir[4] = c.R; jig[4] = c.G; jib[4] = c.B;
                    c = box1.GetPixel(i, j + 2);
                    jir[5] = c.R; jig[5] = c.G; jib[5] = c.B;
                    c = box1.GetPixel(i + 1, j + 2);
                    jir[6] = c.R; jig[6] = c.G; jib[6] = c.B;

                    meanr[3] = (int)(jir[0] + jir[1] + jir[2] + jir[3] + jir[4] + jir[5] + jir[6]) / 7;
                    meang[3] = (int)(jig[0] + jig[1] + jig[2] + jig[3] + jig[4] + jig[5] + jig[6]) / 7;
                    meanb[3] = (int)(jib[0] + jib[1] + jib[2] + jib[3] + jib[4] + jib[5] + jib[6]) / 7;
                    bunsanr[3] = 0; bunsang[3] = 0; bunsanb[3] = 0;
                    for (n = 0; n <= 6; n++)
                    {
                        bunsanr[3] += jir[n] * jir[n] - meanr[3] * meanr[3];
                        bunsang[3] += jig[n] * jig[n] - meang[3] * meang[3];
                        bunsanb[3] += jib[n] * jib[n] - meanb[3] * meanb[3];
                    }
                    //第5近邻区域
                    c = box1.GetPixel(i, j);
                    jir[0] = c.R; jig[0] = c.G; jib[0] = c.B;
                    c = box1.GetPixel(i + 2, j - 1);
                    jir[1] = c.R; jig[1] = c.G; jib[1] = c.B;
                    c = box1.GetPixel(i + 2, j);
                    jir[2] = c.R; jig[2] = c.G; jib[2] = c.B;
                    c = box1.GetPixel(i + 2, j + 1);
                    jir[3] = c.R; jig[3] = c.G; jib[3] = c.B;
                    c = box1.GetPixel(i + 1, j - 1);
                    jir[4] = c.R; jig[4] = c.G; jib[4] = c.B;
                    c = box1.GetPixel(i + 1, j);
                    jir[5] = c.R; jig[5] = c.G; jib[5] = c.B;
                    c = box1.GetPixel(i + 1, j + 1);
                    jir[6] = c.R; jig[6] = c.G; jib[6] = c.B;

                    meanr[4] = (int)(jir[0] + jir[1] + jir[2] + jir[3] + jir[4] + jir[5] + jir[6]) / 7;
                    meang[4] = (int)(jig[0] + jig[1] + jig[2] + jig[3] + jig[4] + jig[5] + jig[6]) / 7;
                    meanb[4] = (int)(jib[0] + jib[1] + jib[2] + jib[3] + jib[4] + jib[5] + jib[6]) / 7;
                    bunsanr[4] = 0; bunsang[4] = 0; bunsanb[4] = 0;
                    for (n = 0; n <= 6; n++)
                    {
                        bunsanr[4] += jir[n] * jir[n] - meanr[4] * meanr[4];
                        bunsang[4] += jig[n] * jig[n] - meang[4] * meang[4];
                        bunsanb[4] += jib[n] * jib[n] - meanb[4] * meanb[4];
                    }
                    //第6近邻区域
                    c = box1.GetPixel(i, j);
                    jir[0] = c.R; jig[0] = c.G; jib[0] = c.B;
                    c = box1.GetPixel(i - 2, j - 2);
                    jir[1] = c.R; jig[1] = c.G; jib[1] = c.B;
                    c = box1.GetPixel(i - 2, j - 1);
                    jir[2] = c.R; jig[2] = c.G; jib[2] = c.B;
                    c = box1.GetPixel(i - 1, j - 2);
                    jir[3] = c.R; jig[3] = c.G; jib[3] = c.B;
                    c = box1.GetPixel(i - 1, j - 1);
                    jir[4] = c.R; jig[4] = c.G; jib[4] = c.B;
                    c = box1.GetPixel(i - 1, j);
                    jir[5] = c.R; jig[5] = c.G; jib[5] = c.B;
                    c = box1.GetPixel(i, j - 1);
                    jir[6] = c.R; jig[6] = c.G; jib[6] = c.B;

                    meanr[5] = (int)(jir[0] + jir[1] + jir[2] + jir[3] + jir[4] + jir[5] + jir[6]) / 7;
                    meang[5] = (int)(jig[0] + jig[1] + jig[2] + jig[3] + jig[4] + jig[5] + jig[6]) / 7;
                    meanb[5] = (int)(jib[0] + jib[1] + jib[2] + jib[3] + jib[4] + jib[5] + jib[6]) / 7;
                    bunsanr[5] = 0; bunsang[5] = 0; bunsanb[5] = 0;
                    for (n = 0; n <= 6; n++)
                    {
                        bunsanr[5] += jir[n] * jir[n] - meanr[5] * meanr[5];
                        bunsang[5] += jig[n] * jig[n] - meang[5] * meang[5];
                        bunsanb[5] += jib[n] * jib[n] - meanb[5] * meanb[5];
                    }
                    //第7近邻区域
                    c = box1.GetPixel(i, j);
                    jir[0] = c.R; jig[0] = c.G; jib[0] = c.B;
                    c = box1.GetPixel(i - 2, j + 2);
                    jir[1] = c.R; jig[1] = c.G; jib[1] = c.B;
                    c = box1.GetPixel(i - 2, j + 1);
                    jir[2] = c.R; jig[2] = c.G; jib[2] = c.B;
                    c = box1.GetPixel(i - 1, j + 2);
                    jir[3] = c.R; jig[3] = c.G; jib[3] = c.B;
                    c = box1.GetPixel(i - 1, j + 1);
                    jir[4] = c.R; jig[4] = c.G; jib[4] = c.B;
                    c = box1.GetPixel(i - 1, j);
                    jir[5] = c.R; jig[5] = c.G; jib[5] = c.B;
                    c = box1.GetPixel(i, j + 1);
                    jir[6] = c.R; jig[6] = c.G; jib[6] = c.B;

                    meanr[6] = (int)(jir[0] + jir[1] + jir[2] + jir[3] + jir[4] + jir[5] + jir[6]) / 7;
                    meang[6] = (int)(jig[0] + jig[1] + jig[2] + jig[3] + jig[4] + jig[5] + jig[6]) / 7;
                    meanb[6] = (int)(jib[0] + jib[1] + jib[2] + jib[3] + jib[4] + jib[5] + jib[6]) / 7;
                    bunsanr[6] = 0; bunsang[6] = 0; bunsanb[6] = 0;
                    for (n = 0; n <= 6; n++)
                    {
                        bunsanr[6] += jir[n] * jir[n] - meanr[6] * meanr[6];
                        bunsang[6] += jig[n] * jig[n] - meang[6] * meang[6];
                        bunsanb[6] += jib[n] * jib[n] - meanb[6] * meanb[6];
                    }
                    //第8近邻区域
                    c = box1.GetPixel(i, j);
                    jir[0] = c.R; jig[0] = c.G; jib[0] = c.B;
                    c = box1.GetPixel(i + 2, j + 2);
                    jir[1] = c.R; jig[1] = c.G; jib[1] = c.B;
                    c = box1.GetPixel(i + 2, j + 1);
                    jir[2] = c.R; jig[2] = c.G; jib[2] = c.B;
                    c = box1.GetPixel(i + 1, j + 2);
                    jir[3] = c.R; jig[3] = c.G; jib[3] = c.B;
                    c = box1.GetPixel(i + 1, j + 1);
                    jir[4] = c.R; jig[4] = c.G; jib[4] = c.B;
                    c = box1.GetPixel(i + 1, j);
                    jir[5] = c.R; jig[5] = c.G; jib[5] = c.B;
                    c = box1.GetPixel(i, j + 1);
                    jir[6] = c.R; jig[6] = c.G; jib[6] = c.B;

                    meanr[7] = (int)(jir[0] + jir[1] + jir[2] + jir[3] + jir[4] + jir[5] + jir[6]) / 7;
                    meang[7] = (int)(jig[0] + jig[1] + jig[2] + jig[3] + jig[4] + jig[5] + jig[6]) / 7;
                    meanb[7] = (int)(jib[0] + jib[1] + jib[2] + jib[3] + jib[4] + jib[5] + jib[6]) / 7;
                    bunsanr[7] = 0; bunsang[7] = 0; bunsanb[7] = 0;
                    for (n = 0; n <= 6; n++)
                    {
                        bunsanr[7] += jir[n] * jir[n] - meanr[7] * meanr[7];
                        bunsang[7] += jig[n] * jig[n] - meang[7] * meang[7];
                        bunsanb[7] += jib[n] * jib[n] - meanb[7] * meanb[7];
                    }
                    //第9近邻区域
                    c = box1.GetPixel(i, j);
                    jir[0] = c.R; jig[0] = c.G; jib[0] = c.B;
                    c = box1.GetPixel(i + 2, j - 2);
                    jir[1] = c.R; jig[1] = c.G; jib[1] = c.B;
                    c = box1.GetPixel(i + 2, j - 1);
                    jir[2] = c.R; jig[2] = c.G; jib[2] = c.B;
                    c = box1.GetPixel(i + 1, j - 2);
                    jir[3] = c.R; jig[3] = c.G; jib[3] = c.B;
                    c = box1.GetPixel(i + 1, j - 1);
                    jir[4] = c.R; jig[4] = c.G; jib[4] = c.B;
                    c = box1.GetPixel(i + 1, j);
                    jir[5] = c.R; jig[5] = c.G; jib[5] = c.B;
                    c = box1.GetPixel(i, j - 1);
                    jir[6] = c.R; jig[6] = c.G; jib[6] = c.B;

                    meanr[8] = (int)(jir[0] + jir[1] + jir[2] + jir[3] + jir[4] + jir[5] + jir[6]) / 7;
                    meang[8] = (int)(jig[0] + jig[1] + jig[2] + jig[3] + jig[4] + jig[5] + jig[6]) / 7;
                    meanb[8] = (int)(jib[0] + jib[1] + jib[2] + jib[3] + jib[4] + jib[5] + jib[6]) / 7;
                    bunsanr[8] = 0; bunsang[8] = 0; bunsanb[8] = 0;
                    for (n = 0; n <= 6; n++)
                    {
                        bunsanr[8] += jir[n] * jir[n] - meanr[8] * meanr[8];
                        bunsang[8] += jig[n] * jig[n] - meang[8] * meang[8];
                        bunsanb[8] += jib[n] * jib[n] - meanb[8] * meanb[8];
                    }
                    //求方差最小的近邻区域nminr,nming,nminb
                    bminr = bunsanr[0]; bming = bunsang[0]; bminb = bunsanb[0];
                    nminr = 0; nming = 0; nminb = 0;
                    for (n = 0; n <= 8; n++)
                    {
                        if (bminr > bunsanr[n])
                        {
                            bminr = bunsanr[n];
                            nminr = n;
                        }
                        //把nminr的值四舍五入后作为显示图像的颜色分量值
                        cr = (int)(meanr[nminr] + 0.5);
                        if (bming > bunsang[n])
                        {
                            bming = bunsang[n];
                            nming = n;
                        }
                        //把nming的值四舍五入后作为显示图像的颜色分量值
                        cg = (int)(meang[nming] + 0.5);
                        if (bminb > bunsanb[n])
                        {
                            bminb = bunsanb[n];
                            nminb = n;
                        }
                        //把nminb的值四舍五入后作为显示图像的颜色分量值
                        cb = (int)(meanb[nminb] + 0.5);
                        Color c1 = Color.FromArgb(cr, cg, cb);
                        box2.SetPixel(i, j, c1);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void nN中值滤波器ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            nnZhongZhi frm17 = new nnZhongZhi();
            Error frm1 = new Error();
            frm17.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm17.StartPosition = FormStartPosition.CenterParent;
            frm17.ShowDialog(this);
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int n = frm17.nnZhongZhi_n;//获取n值
            int i, j, nn, n2, chuo;
            if (n < 3 || n % 2 != 1)//检查取值是否为3.5.7等的奇数
            {
                frm1.FormBorderStyle = FormBorderStyle.FixedDialog;
                frm1.StartPosition = FormStartPosition.CenterParent;
                frm1.ShowDialog(this);
            }
            else
            {
                n2 = (n - 1) / 2;
                nn = n * n;
                chuo = (nn - 1) / 2;
                int rr, gg, bb, r1, g1, b1, k1, k2, chg, m, m2, m3, madom, madom2, madom3;
                int[] mado = new int[1000];
                int[] mado2 = new int[1000];
                int[] mado3 = new int[1000];
                for (i = n2; i < pictureBox1.Image.Width - n2; i++)
                {
                    for (j = n2; j < pictureBox1.Image.Height - n2; j++)
                    {
                        //把N*N屏蔽窗口部分的所有像素颜色分量值分别放入mado[m],mado2[m2],mado[m3]
                        rr = 0; gg = 0; bb = 0;
                        m = 0; m2 = 0; m3 = 0;
                        for (k1 = i - n2; k1 <= i + n2; k1++)
                        {
                            for (k2 = j - n2; k2 <= j + n2; k2++)
                            {
                                c = box1.GetPixel(k1, k2);
                                r1 = c.R;
                                g1 = c.G;
                                b1 = c.B;
                                mado[m] = r1;
                                mado2[m2] = g1;
                                mado3[m3] = b1;
                                m = m + 1; m2 = m2 + 1; m3 = m3 + 1;
                            }
                        }
                        do
                        {
                            chg = 0;
                            //把mado[m]中的值按下降顺序用冒泡法排序
                            for (m = 0; m < nn - 1; m++)
                            {
                                if (mado[m] < mado[m + 1])
                                {
                                    madom = mado[m];
                                    mado[m] = mado[m + 1];
                                    mado[m + 1] = madom;
                                    chg = 1;
                                }
                            }
                            //把mado2[m2]中的值按下降顺序用冒泡法排序
                            for (m2 = 0; m2 < nn - 1; m2++)
                            {
                                if (mado2[m2] < mado2[m2 + 1])
                                {
                                    madom2 = mado2[m2];
                                    mado2[m2] = mado2[m2 + 1];
                                    mado2[m2 + 1] = madom2;
                                    chg = 1;
                                }
                            }
                            //把mado3[m3]中的值按下降顺序用冒泡法排序
                            for (m3 = 0; m3 < nn - 1; m3++)
                            {
                                if (mado3[m3] < mado3[m3 + 1])
                                {
                                    madom3 = mado3[m3];
                                    mado3[m3] = mado3[m3 + 1];
                                    mado3[m3 + 1] = madom3;
                                    chg = 1;
                                }
                            }
                        } while (chg == 1);
                        //求中值rr,gg,bb
                        rr = mado[chuo];
                        gg = mado2[chuo];
                        bb = mado3[chuo];
                        Color c1 = Color.FromArgb(rr, gg, bb);
                        box2.SetPixel(i, j, c1);
                    }
                }
                pictureBox2.Refresh();
                pictureBox2.Image = box2;
            }
        }

        private void 十字形中值滤波器ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ShiZi frm18 = new ShiZi();
            Error frm1 = new Error();
            frm18.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm18.StartPosition = FormStartPosition.CenterParent;
            frm18.ShowDialog(this);
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int n = frm18.ShiZi_n;//获取n值
            int i, j, nn, n2, chuo;
            if (n < 3 || n % 2 != 1)//检查取值是否为3.5.7等的奇数
            {
                frm1.FormBorderStyle = FormBorderStyle.FixedDialog;
                frm1.StartPosition = FormStartPosition.CenterParent;
                frm1.ShowDialog(this);
            }
            else
            {
                n2 = (n - 1) / 2;
                nn = n + n - 1;
                chuo = (nn - 1) / 2;
                int rr, gg, bb, r1, g1, b1, k1, k2, chg, m, m2, m3, madom, madom2, madom3;
                int[] mado = new int[1000];
                int[] mado2 = new int[1000];
                int[] mado3 = new int[1000];
                for (i = n2; i < pictureBox1.Image.Width - n2; i++)
                {
                    for (j = n2; j < pictureBox1.Image.Height - n2; j++)
                    {
                        //把十字形屏蔽窗口部分的所有像素颜色分量值分别放入mado[m],mado2[m2],mado[m3]
                        m = 0; m2 = 0; m3 = 0;
                        //代入含中心的水平部分
                        for (k1 = i - n2; k1 <= i + n2; k1++)
                        {
                            c = box1.GetPixel(k1, j);
                            r1 = c.R;
                            g1 = c.G;
                            b1 = c.B;
                            mado[m] = r1;
                            mado2[m2] = g1;
                            mado3[m3] = b1;
                            m = m + 1; m2 = m2 + 1; m3 = m3 + 1;
                        }
                        //代入不含中心的垂直部分
                        for (k2 = j - n2; k2 <= j + n2; k2++)
                        {
                            if (k1 == j) continue;
                            c = box1.GetPixel(i, k2);
                            r1 = c.R;
                            g1 = c.G;
                            b1 = c.B;
                            mado[m] = r1;
                            mado2[m2] = g1;
                            mado3[m3] = b1;
                            m = m + 1; m2 = m2 + 1; m3 = m3 + 1;
                        }
                        do
                        {
                            chg = 0;
                            //把mado[m]中的值按下降顺序用冒泡法排序
                            for (m = 0; m < nn - 1; m++)
                            {
                                if (mado[m] < mado[m + 1])
                                {
                                    madom = mado[m];
                                    mado[m] = mado[m + 1];
                                    mado[m + 1] = madom;
                                    chg = 1;
                                }
                            }
                            //把mado2[m2]中的值按下降顺序用冒泡法排序
                            for (m2 = 0; m2 < nn - 1; m2++)
                            {
                                if (mado2[m2] < mado2[m2 + 1])
                                {
                                    madom2 = mado2[m2];
                                    mado2[m2] = mado2[m2 + 1];
                                    mado2[m2 + 1] = madom2;
                                    chg = 1;
                                }
                            }
                            //把mado3[m3]中的值按下降顺序用冒泡法排序
                            for (m3 = 0; m3 < nn - 1; m3++)
                            {
                                if (mado3[m3] < mado3[m3 + 1])
                                {
                                    madom3 = mado3[m3];
                                    mado3[m3] = mado3[m3 + 1];
                                    mado3[m3 + 1] = madom3;
                                    chg = 1;
                                }
                            }
                        } while (chg == 1);
                        //求中值rr,gg,bb
                        rr = mado[chuo];
                        gg = mado2[chuo];
                        bb = mado3[chuo];
                        Color c1 = Color.FromArgb(rr, gg, bb);
                        box2.SetPixel(i, j, c1);
                    }
                }
                pictureBox2.Refresh();
                pictureBox2.Image = box2;
            }
        }

        private void nN最大值滤波器ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            nnZuiDa frm19 = new nnZuiDa();
            Error frm1 = new Error();
            frm19.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm19.StartPosition = FormStartPosition.CenterParent;
            frm19.ShowDialog(this);
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int n = frm19.nnZuiDa_n;//获取n值
            int i, j, nn, n2;
            if (n < 3 || n % 2 != 1)//检查取值是否为3.5.7等的奇数
            {
                frm1.FormBorderStyle = FormBorderStyle.FixedDialog;
                frm1.StartPosition = FormStartPosition.CenterParent;
                frm1.ShowDialog(this);
            }
            else
            {
                n2 = (n - 1) / 2;
                nn = n * n;
                int rr, gg, bb, r1, g1, b1, k1, k2, m, m2, m3, madomax, madomax2, madomax3;
                int[] mado = new int[1000];
                int[] mado2 = new int[1000];
                int[] mado3 = new int[1000];
                for (i = n2; i < pictureBox1.Image.Width - n2; i++)
                {
                    for (j = n2; j < pictureBox1.Image.Height - n2; j++)
                    {
                        //把N*N屏蔽窗口部分的所有像素颜色分量值分别放入mado[m],mado2[m2],mado[m3]
                        rr = 0; gg = 0; bb = 0;
                        m = 0; m2 = 0; m3 = 0;
                        for (k1 = i - n2; k1 <= i + n2; k1++)
                        {
                            for (k2 = j - n2; k2 <= j + n2; k2++)
                            {
                                c = box1.GetPixel(k1, k2);
                                r1 = c.R;
                                g1 = c.G;
                                b1 = c.B;
                                mado[m] = r1;
                                mado2[m2] = g1;
                                mado3[m3] = b1;
                                m = m + 1; m2 = m2 + 1; m3 = m3 + 1;
                            }
                        }
                        //找出mado[m]中的最大值madomax,用最大频率值
                        madomax = mado[0];
                        for (m = 1; m < nn; m++)
                        {
                            if (madomax < mado[m])
                            {
                                madomax = mado[m];
                                mado[m] = mado[m + 1];
                            }
                        }
                        //找出mado2[m2]中的最大值madomax2,用最大频率值
                        madomax2 = mado2[0];
                        for (m2 = 1; m2 < nn; m2++)
                        {
                            if (madomax2 < mado2[m2])
                            {
                                madomax2 = mado[m2];
                                mado[m2] = mado[m2 + 1];
                            }
                        }
                        //找出mado3[m3]中的最大值madomax3,用最大频率值
                        madomax3 = mado3[0];
                        for (m3 = 1; m3 < nn; m3++)
                        {
                            if (madomax3 < mado3[m3])
                            {
                                madomax3 = mado3[m3];
                                mado3[m3] = mado3[m3 + 1];
                            }
                        }
                        rr = madomax;
                        gg = madomax2;
                        bb = madomax3;
                        Color c1 = Color.FromArgb(rr, gg, bb);
                        box2.SetPixel(i, j, c1);
                    }
                }
                pictureBox2.Refresh();
                pictureBox2.Image = box2;
            }
        }

        private void 模板ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, m, n;
            int rr, gg, bb, ki, kj, kp, kq, k1, k2;
            int[,] r1 = new int[800, 800];
            int[,] g1 = new int[800, 800];
            int[,] b1 = new int[800, 800];
            int[,] r2 = new int[800, 800];
            int[,] g2 = new int[800, 800];
            int[,] b2 = new int[800, 800];
            float[,] h1 = new float[300, 300];

            h1[0, 0] = 0.1f; h1[0, 1] = 0.1f; h1[0, 2] = 0.1f;
            h1[1, 0] = 0.1f; h1[1, 1] = 0.2f; h1[1, 2] = 0.1f;
            h1[2, 0] = 0.1f; h1[2, 1] = 0.1f; h1[2, 2] = 0.1f;
            for (i = 0; i <= pictureBox1.Image.Width - 1; i++)
            {
                for (j = 0; j <= pictureBox1.Image.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    r1[i, j] = c.R;
                    g1[i, j] = c.G;
                    b1[i, j] = c.B;
                }
            }
            m = pictureBox1.Image.Width; n = pictureBox1.Image.Height;
            for (k1 = 1; k1 <= m - 1; k1++)
            {
                for (k2 = 1; k2 <= n - 1; k2++)
                {
                    rr = 0; gg = 0; bb = 0;
                    for (i = 0; i <= 2; i++)
                    {
                        for (j = 0; j <= 2; j++)
                        {
                            ki = k1 - i; kj = k2 - j;
                            if (((ki >= 0) & (ki <= m)) & ((kj >= 0) & (kj <= n)))
                            {
                                rr = rr + (int)(r1[ki, kj] * h1[i, j]);
                                gg = gg + (int)(g1[ki, kj] * h1[i, j]);
                                bb = bb + (int)(b1[ki, kj] * h1[i, j]);

                            }
                        }
                    }
                    kp = k1 - 1;
                    kq = k2 - 1;
                    r2[kp, kq] = rr;
                    g2[kp, kq] = gg;
                    b2[kp, kq] = bb;
                    Color cc = Color.FromArgb(r2[kp, kq], g2[kp, kq], b2[kp, kq]);
                    box2.SetPixel(k1, k2, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 模板ToolStripMenuItem1_Click(object sender, EventArgs e)
        {

            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, m, n;
            int rr, gg, bb, ki, kj, kp, kq, k1, k2;
            int[,] r1 = new int[800, 800];
            int[,] g1 = new int[800, 800];
            int[,] b1 = new int[800, 800];
            int[,] r2 = new int[800, 800];
            int[,] g2 = new int[800, 800];
            int[,] b2 = new int[800, 800];
            float[,] h1 = new float[300, 300];

            h1[0, 0] = 1 / 35f; h1[0, 1] = 1 / 35f; h1[0, 2] = 1 / 35f; h1[0, 3] = 1 / 35f; h1[0, 4] = 1 / 35f;
            h1[1, 0] = 1 / 35f; h1[1, 1] = 2 / 35f; h1[1, 2] = 2 / 35f; h1[1, 3] = 2 / 35f; h1[1, 4] = 1 / 35f;
            h1[2, 0] = 1 / 35f; h1[2, 1] = 2 / 35f; h1[2, 2] = 3 / 35f; h1[2, 3] = 2 / 35f; h1[2, 4] = 1 / 35f;
            h1[3, 0] = 1 / 35f; h1[3, 1] = 2 / 35f; h1[3, 2] = 2 / 35f; h1[3, 3] = 2 / 35f; h1[3, 4] = 1 / 35f;
            h1[4, 0] = 1 / 35f; h1[4, 1] = 1 / 35f; h1[4, 2] = 1 / 35f; h1[4, 3] = 1 / 35f; h1[4, 4] = 1 / 35f;
            for (i = 0; i <= pictureBox1.Image.Width - 1; i++)
            {
                for (j = 0; j <= pictureBox1.Image.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    r1[i, j] = c.R;
                    g1[i, j] = c.G;
                    b1[i, j] = c.B;
                }
            }
            m = pictureBox1.Image.Width; n = pictureBox1.Image.Height;
            for (k1 = 1; k1 <= m - 1; k1++)
            {
                for (k2 = 1; k2 <= n - 1; k2++)
                {
                    rr = 0; gg = 0; bb = 0;
                    for (i = 0; i <= 4; i++)
                    {
                        for (j = 0; j <= 4; j++)
                        {
                            ki = k1 - i; kj = k2 - j;
                            if (((ki >= 0) & (ki <= m)) & ((kj >= 0) & (kj <= n)))
                            {
                                rr = rr + (int)(r1[ki, kj] * h1[i, j]);
                                gg = gg + (int)(g1[ki, kj] * h1[i, j]);
                                bb = bb + (int)(b1[ki, kj] * h1[i, j]);

                            }
                        }
                    }
                    kp = k1 - 1;
                    kq = k2 - 1;
                    r2[kp, kq] = rr;
                    g2[kp, kq] = gg;
                    b2[kp, kq] = bb;
                    Color cc = Color.FromArgb(r2[kp, kq], g2[kp, kq], b2[kp, kq]);
                    box2.SetPixel(k1, k2, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 图像水平增强ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, m, n;
            int rr, gg, bb, ki, kj, kp, kq, k1, k2;
            int[,] r1 = new int[800, 800];
            int[,] g1 = new int[800, 800];
            int[,] b1 = new int[800, 800];
            int[,] r2 = new int[800, 800];
            int[,] g2 = new int[800, 800];
            int[,] b2 = new int[800, 800];
            int[,] h1 = new int[30, 30];
            //定义(3*1)矩阵
            h1[0, 0] = -1; h1[0, 1] = 2; h1[0, 2] = -1;

            for (i = 0; i <= pictureBox1.Image.Width - 2; i++)
            {
                for (j = 0; j <= pictureBox1.Image.Height - 2; j++)
                {
                    c = box1.GetPixel(i, j);
                    r1[i, j] = c.R;
                    g1[i, j] = c.G;
                    b1[i, j] = c.B;
                }
            }
            m = pictureBox1.Image.Width; n = pictureBox1.Image.Height;
            for (k1 = 1; k1 <= m - 1; k1++)
            {
                for (k2 = 1; k2 <= n - 1; k2++)
                {
                    rr = 0; gg = 0; bb = 0;
                    for (i = 0; i <= 2; i++)
                    {
                        for (j = 0; j <= 2; j++)
                        {
                            ki = k1 - i; kj = k2 - j;
                            if (((ki >= 0) & (ki <= m)) & ((kj >= 0) & (kj <= n)))
                            {
                                //对应的3行的颜色分量值分别乘以矩阵对应值，再相加
                                rr = (int)(rr + r1[ki, kj] * h1[i, j]);
                                gg = (int)(gg + g1[ki, kj] * h1[i, j]);
                                bb = (int)(bb + b1[ki, kj] * h1[i, j]);

                            }
                        }
                    }
                    kp = k1 - 1;
                    kq = k2 - 1;
                    r2[kp, kq] = Math.Abs(rr);
                    g2[kp, kq] = Math.Abs(gg);
                    b2[kp, kq] = Math.Abs(bb);
                    if (r2[kp, kq] < 0) r2[kp, kq] = 0;
                    if (r2[kp, kq] > 255) r2[kp, kq] = 255;
                    if (g2[kp, kq] < 0) g2[kp, kq] = 0;
                    if (g2[kp, kq] > 255) g2[kp, kq] = 255;
                    if (b2[kp, kq] < 0) b2[kp, kq] = 0;
                    if (b2[kp, kq] > 255) b2[kp, kq] = 255;
                    Color cc = Color.FromArgb(r2[kp, kq], g2[kp, kq], b2[kp, kq]);
                    box2.SetPixel(k1, k2, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 图像垂直增强ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, m, n;
            int rr, gg, bb, ki, kj, kp, kq, k1, k2;
            int[,] r1 = new int[800, 800];
            int[,] g1 = new int[800, 800];
            int[,] b1 = new int[800, 800];
            int[,] r2 = new int[800, 800];
            int[,] g2 = new int[800, 800];
            int[,] b2 = new int[800, 800];
            int[,] h1 = new int[30, 30];

            //定义(3*3)矩阵
            h1[0, 0] = -1; h1[0, 1] = 0; h1[0, 2] = 0;
            h1[1, 0] = 2; h1[1, 1] = 0; h1[1, 2] = 0;
            h1[2, 0] = -1; h1[2, 1] = 0; h1[2, 2] = 0;

            for (i = 0; i <= pictureBox1.Image.Width - 2; i++)
            {
                for (j = 0; j <= pictureBox1.Image.Height - 2; j++)
                {
                    c = box1.GetPixel(i, j);
                    r1[i, j] = c.R;
                    g1[i, j] = c.G;
                    b1[i, j] = c.B;
                }
            }
            m = pictureBox1.Image.Width; n = pictureBox1.Image.Height;
            for (k1 = 1; k1 <= m - 1; k1++)
            {
                for (k2 = 1; k2 <= n - 1; k2++)
                {
                    rr = 0; gg = 0; bb = 0;
                    for (i = 0; i <= 2; i++)
                    {
                        for (j = 0; j <= 2; j++)
                        {
                            ki = k1 - i; kj = k2 - j;
                            if (((ki >= 0) & (ki <= m)) & ((kj >= 0) & (kj <= n)))
                            {
                                //对应的3行的颜色分量值分别乘以矩阵对应值，再相加
                                rr = (int)(rr + r1[ki, kj] * h1[i, j]);
                                gg = (int)(gg + g1[ki, kj] * h1[i, j]);
                                bb = (int)(bb + b1[ki, kj] * h1[i, j]);

                            }
                        }
                    }
                    kp = k1 - 1;
                    kq = k2 - 1;
                    r2[kp, kq] = Math.Abs(rr);
                    g2[kp, kq] = Math.Abs(gg);
                    b2[kp, kq] = Math.Abs(bb);
                    if (r2[kp, kq] < 0) r2[kp, kq] = 0;
                    if (r2[kp, kq] > 255) r2[kp, kq] = 255;
                    if (g2[kp, kq] < 0) g2[kp, kq] = 0;
                    if (g2[kp, kq] > 255) g2[kp, kq] = 255;
                    if (b2[kp, kq] < 0) b2[kp, kq] = 0;
                    if (b2[kp, kq] > 255) b2[kp, kq] = 255;
                    Color cc = Color.FromArgb(r2[kp, kq], g2[kp, kq], b2[kp, kq]);
                    box2.SetPixel(k1, k2, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 图像水平垂直双向增强ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, m, n;
            int rr, gg, bb, ki, kj, kp, kq, k1, k2;
            int[,] r1 = new int[800, 800];
            int[,] g1 = new int[800, 800];
            int[,] b1 = new int[800, 800];
            int[,] r2 = new int[800, 800];
            int[,] g2 = new int[800, 800];
            int[,] b2 = new int[800, 800];
            int[,] h1 = new int[30, 30];
            //定义(3*3)矩阵
            h1[0, 0] = -1; h1[0, 1] = -1; h1[0, 2] = -1;
            h1[1, 0] = -1; h1[1, 1] = 8; h1[1, 2] = -1;
            h1[2, 0] = -1; h1[2, 1] = -1; h1[2, 2] = -1;

            for (i = 0; i <= pictureBox1.Image.Width - 2; i++)
            {
                for (j = 0; j <= pictureBox1.Image.Height - 2; j++)
                {
                    c = box1.GetPixel(i, j);
                    r1[i, j] = c.R;
                    g1[i, j] = c.G;
                    b1[i, j] = c.B;
                }
            }
            m = pictureBox1.Image.Width; n = pictureBox1.Image.Height;
            for (k1 = 1; k1 <= m - 1; k1++)
            {
                for (k2 = 1; k2 <= n - 1; k2++)
                {
                    rr = 0; gg = 0; bb = 0;
                    for (i = 0; i <= 2; i++)
                    {
                        for (j = 0; j <= 2; j++)
                        {
                            ki = k1 - i; kj = k2 - j;
                            if (((ki >= 0) & (ki <= m)) & ((kj >= 0) & (kj <= n)))
                            {
                                //对应的3行的颜色分量值分别乘以矩阵对应值，再相加
                                rr = (int)(rr + r1[ki, kj] * h1[i, j]);
                                gg = (int)(gg + g1[ki, kj] * h1[i, j]);
                                bb = (int)(bb + b1[ki, kj] * h1[i, j]);

                            }
                        }
                    }
                    kp = k1 - 1;
                    kq = k2 - 1;
                    r2[kp, kq] = Math.Abs(rr);
                    g2[kp, kq] = Math.Abs(gg);
                    b2[kp, kq] = Math.Abs(bb);
                    if (r2[kp, kq] < 0) r2[kp, kq] = 0;
                    if (r2[kp, kq] > 255) r2[kp, kq] = 255;
                    if (g2[kp, kq] < 0) g2[kp, kq] = 0;
                    if (g2[kp, kq] > 255) g2[kp, kq] = 255;
                    if (b2[kp, kq] < 0) b2[kp, kq] = 0;
                    if (b2[kp, kq] > 255) b2[kp, kq] = 255;
                    Color cc = Color.FromArgb(r2[kp, kq], g2[kp, kq], b2[kp, kq]);
                    box2.SetPixel(k1, k2, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 并联型结构滤波ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, m, n;
            int rr, gg, bb, ki, kj, kp, kq, k1, k2;
            int[,] r1 = new int[800, 800];
            int[,] g1 = new int[800, 800];
            int[,] b1 = new int[800, 800];
            int[,] r2 = new int[800, 800];
            int[,] g2 = new int[800, 800];
            int[,] b2 = new int[800, 800];
            int[,] h1 = new int[30, 30];
            //定义(3*3)矩阵
            h1[0, 0] = -1; h1[0, 1] = 0; h1[0, 2] = 0;
            h1[1, 0] = 2; h1[1, 1] = 0; h1[1, 2] = 0;
            h1[2, 0] = -1; h1[2, 1] = 2; h1[2, 2] = -1;

            for (i = 0; i <= pictureBox1.Image.Width - 2; i++)
            {
                for (j = 0; j <= pictureBox1.Image.Height - 2; j++)
                {
                    c = box1.GetPixel(i, j);
                    r1[i, j] = c.R;
                    g1[i, j] = c.G;
                    b1[i, j] = c.B;
                }
            }
            m = pictureBox1.Image.Width; n = pictureBox1.Image.Height;
            for (k1 = 1; k1 <= m - 1; k1++)
            {
                for (k2 = 1; k2 <= n - 1; k2++)
                {
                    rr = 0; gg = 0; bb = 0;
                    for (i = 0; i <= 2; i++)
                    {
                        for (j = 0; j <= 2; j++)
                        {
                            ki = k1 - i; kj = k2 - j;
                            if (((ki >= 0) & (ki <= m)) & ((kj >= 0) & (kj <= n)))
                            {
                                //对应的3行的颜色分量值分别乘以矩阵对应值，再相加
                                rr = (int)(rr + r1[ki, kj] * h1[i, j]);
                                gg = (int)(gg + g1[ki, kj] * h1[i, j]);
                                bb = (int)(bb + b1[ki, kj] * h1[i, j]);

                            }
                        }
                    }
                    kp = k1 - 1;
                    kq = k2 - 1;
                    r2[kp, kq] = Math.Abs(rr);
                    g2[kp, kq] = Math.Abs(gg);
                    b2[kp, kq] = Math.Abs(bb);
                    if (r2[kp, kq] < 0) r2[kp, kq] = 0;
                    if (r2[kp, kq] > 255) r2[kp, kq] = 255;
                    if (g2[kp, kq] < 0) g2[kp, kq] = 0;
                    if (g2[kp, kq] > 255) g2[kp, kq] = 255;
                    if (b2[kp, kq] < 0) b2[kp, kq] = 0;
                    if (b2[kp, kq] > 255) b2[kp, kq] = 255;
                    Color cc = Color.FromArgb(r2[kp, kq], g2[kp, kq], b2[kp, kq]);
                    box2.SetPixel(k1, k2, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 级联型结构滤波ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, m, n;
            int rr, gg, bb, ki, kj, kp, kq, k1, k2;
            int[,] r1 = new int[800, 800];
            int[,] g1 = new int[800, 800];
            int[,] b1 = new int[800, 800];
            int[,] r2 = new int[800, 800];
            int[,] g2 = new int[800, 800];
            int[,] b2 = new int[800, 800];
            int[,] h1 = new int[30, 30];
            //定义(3*3)矩阵
            h1[0, 0] = 1; h1[0, 1] = -2; h1[0, 2] = 1;
            h1[1, 0] = -2; h1[1, 1] = 4; h1[1, 2] = -2;
            h1[2, 0] = 1; h1[2, 1] = -2; h1[2, 2] = 1;
            for (i = 0; i <= pictureBox1.Image.Width - 2; i++)
            {
                for (j = 0; j <= pictureBox1.Image.Height - 2; j++)
                {
                    c = box1.GetPixel(i, j);
                    r1[i, j] = c.R;
                    g1[i, j] = c.G;
                    b1[i, j] = c.B;
                }
            }
            m = pictureBox1.Image.Width; n = pictureBox1.Image.Height;
            for (k1 = 1; k1 <= m - 1; k1++)
            {
                for (k2 = 1; k2 <= n - 1; k2++)
                {
                    rr = 0; gg = 0; bb = 0;
                    for (i = 0; i <= 2; i++)
                    {
                        for (j = 0; j <= 2; j++)
                        {
                            ki = k1 - i; kj = k2 - j;
                            if (((ki >= 0) & (ki <= m)) & ((kj >= 0) & (kj <= n)))
                            {
                                //对应的3行的颜色分量值分别乘以矩阵对应值，再相加
                                rr = (int)(rr + r1[ki, kj] * h1[i, j]);
                                gg = (int)(gg + g1[ki, kj] * h1[i, j]);
                                bb = (int)(bb + b1[ki, kj] * h1[i, j]);

                            }
                        }
                    }
                    kp = k1 - 1;
                    kq = k2 - 1;
                    r2[kp, kq] = Math.Abs(rr);
                    g2[kp, kq] = Math.Abs(gg);
                    b2[kp, kq] = Math.Abs(bb);
                    if (r2[kp, kq] < 0) r2[kp, kq] = 0;
                    if (r2[kp, kq] > 255) r2[kp, kq] = 255;
                    if (g2[kp, kq] < 0) g2[kp, kq] = 0;
                    if (g2[kp, kq] > 255) g2[kp, kq] = 255;
                    if (b2[kp, kq] < 0) b2[kp, kq] = 0;
                    if (b2[kp, kq] > 255) b2[kp, kq] = 255;
                    Color cc = Color.FromArgb(r2[kp, kq], g2[kp, kq], b2[kp, kq]);
                    box2.SetPixel(k1, k2, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 直接以梯度值代替ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Color cc = new Color();
            Color ccc = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int rr, gg, bb;
            double r1, g1, b1, r2, g2, b2, r3, g3, b3;
            for (i = 1; i <= pictureBox1.Image.Width - 1; i++)
            {
                for (j = 1; j <= pictureBox1.Image.Height - 1; j++)
                {
                    rr = 0; gg = 0; bb = 0;
                    c = box1.GetPixel(i, j);
                    r1 = c.R;
                    g1 = c.G;
                    b1 = c.B;

                    cc = box1.GetPixel(i - 1, j);
                    r2 = cc.R;
                    g2 = cc.G;
                    b2 = cc.B;

                    ccc = box1.GetPixel(i, j - 1);
                    r3 = ccc.R;
                    g3 = ccc.G;
                    b3 = ccc.B;
                    //根据微分公式计算当前像素的颜色分量灰度值
                    rr = (int)(Math.Sqrt((r1 - r2) * (r1 - r2) + (r1 - r3) * (r1 - r3)));
                    gg = (int)(Math.Sqrt((g1 - g2) * (g1 - g2) + (g1 - g3) * (g1 - g3)));
                    bb = (int)(Math.Sqrt((b1 - b2) * (b1 - b2) + (b1 - b3) * (b1 - b3)));

                    if (rr > 255) rr = 255;
                    if (gg > 255) gg = 255;
                    if (bb > 255) bb = 255;

                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 辅以门限判断ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Color cc = new Color();
            Color ccc = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int rr, gg, bb;
            double r1, g1, b1, r2, g2, b2, r3, g3, b3;
            for (i = 1; i <= pictureBox1.Image.Width - 1; i++)
            {
                for (j = 1; j <= pictureBox1.Image.Height - 1; j++)
                {
                    rr = 0; gg = 0; bb = 0;
                    c = box1.GetPixel(i, j);
                    r1 = c.R;
                    g1 = c.G;
                    b1 = c.B;

                    cc = box1.GetPixel(i - 1, j);
                    r2 = cc.R;
                    g2 = cc.G;
                    b2 = cc.B;

                    ccc = box1.GetPixel(i, j - 1);
                    r3 = ccc.R;
                    g3 = ccc.G;
                    b3 = ccc.B;

                    //根据微分公式计算当前像素的颜色分量灰度值
                    rr = (int)(Math.Sqrt((r1 - r2) * (r1 - r2) + (r1 - r3) * (r1 - r3)));
                    gg = (int)(Math.Sqrt((g1 - g2) * (g1 - g2) + (g1 - g3) * (g1 - g3)));
                    bb = (int)(Math.Sqrt((b1 - b2) * (b1 - b2) + (b1 - b3) * (b1 - b3)));
                    //比较梯度是否大于30，是则将梯度值加100，不是则将该像素点的灰度值恢复，如果梯度加100大于255，将其置为255
                    if (rr < 30) rr = (int)r1;
                    if (rr >= 30) rr = rr + 100;
                    if (gg < 30) gg = (int)g1;
                    if (gg >= 30) gg = gg + 100;
                    if (bb < 30) bb = (int)b1;
                    if (bb >= 30) bb = bb + 100;

                    if (rr > 255) rr = 255;
                    if (gg > 255) gg = 255;
                    if (bb > 255) bb = 255;

                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 给边缘规定一个特定的灰度值ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Color cc = new Color();
            Color ccc = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int rr, gg, bb;
            double r1, g1, b1, r2, g2, b2, r3, g3, b3;
            for (i = 1; i <= pictureBox1.Image.Width - 1; i++)
            {
                for (j = 1; j <= pictureBox1.Image.Height - 1; j++)
                {
                    rr = 0; gg = 0; bb = 0;
                    c = box1.GetPixel(i, j);
                    r1 = c.R;
                    g1 = c.G;
                    b1 = c.B;

                    cc = box1.GetPixel(i - 1, j);
                    r2 = cc.R;
                    g2 = cc.G;
                    b2 = cc.B;

                    ccc = box1.GetPixel(i, j - 1);
                    r3 = ccc.R;
                    g3 = ccc.G;
                    b3 = ccc.B;
                    //根据微分公式计算当前像素的颜色分量灰度值
                    rr = (int)(Math.Sqrt((r1 - r2) * (r1 - r2) + (r1 - r3) * (r1 - r3)));
                    gg = (int)(Math.Sqrt((g1 - g2) * (g1 - g2) + (g1 - g3) * (g1 - g3)));
                    bb = (int)(Math.Sqrt((b1 - b2) * (b1 - b2) + (b1 - b3) * (b1 - b3)));
                    //比较梯度是否大于150，是则将灰度值置为255，不是则将该像素点的灰度值恢复
                    if (rr <= 150) rr = (int)r1;
                    if (rr > 150) rr = 255;
                    if (gg <= 150) gg = (int)g1;
                    if (gg > 150) gg = 255;
                    if (bb <= 150) bb = (int)b1;
                    if (bb > 150) bb = 255;

                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 给背景规定灰度级ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Color cc = new Color();
            Color ccc = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int rr, gg, bb;
            double r1, g1, b1, r2, g2, b2, r3, g3, b3;
            for (i = 1; i <= pictureBox1.Image.Width - 1; i++)
            {
                for (j = 1; j <= pictureBox1.Image.Height - 1; j++)
                {
                    rr = 0; gg = 0; bb = 0;
                    c = box1.GetPixel(i, j);
                    r1 = c.R;
                    g1 = c.G;
                    b1 = c.B;

                    cc = box1.GetPixel(i - 1, j);
                    r2 = cc.R;
                    g2 = cc.G;
                    b2 = cc.B;

                    ccc = box1.GetPixel(i, j - 1);
                    r3 = ccc.R;
                    g3 = ccc.G;
                    b3 = ccc.B;
                    //根据微分公式计算当前像素的颜色分量灰度值
                    rr = (int)(Math.Sqrt((r1 - r2) * (r1 - r2) + (r1 - r3) * (r1 - r3)));
                    gg = (int)(Math.Sqrt((g1 - g2) * (g1 - g2) + (g1 - g3) * (g1 - g3)));
                    bb = (int)(Math.Sqrt((b1 - b2) * (b1 - b2) + (b1 - b3) * (b1 - b3)));
                    //比较梯度是否大于30，是则将该像素点的灰度值恢复，不是则将灰度值置为0
                    if (rr <= 30) rr = 0;
                    if (rr > 30) rr = (int)r1;
                    if (gg <= 30) gg = 0;
                    if (gg > 30) gg = (int)g1;
                    if (bb <= 30) bb = 0;
                    if (bb > 30) bb = (int)b1;

                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 根据梯度二值化图像ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Color cc = new Color();
            Color ccc = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int rr, gg, bb;
            double r1, g1, b1, r2, g2, b2, r3, g3, b3;
            for (i = 1; i <= pictureBox1.Image.Width - 1; i++)
            {
                for (j = 1; j <= pictureBox1.Image.Height - 1; j++)
                {
                    rr = 0; gg = 0; bb = 0;
                    c = box1.GetPixel(i, j);
                    r1 = c.R;
                    g1 = c.G;
                    b1 = c.B;

                    cc = box1.GetPixel(i - 1, j);
                    r2 = cc.R;
                    g2 = cc.G;
                    b2 = cc.B;

                    ccc = box1.GetPixel(i, j - 1);
                    r3 = ccc.R;
                    g3 = ccc.G;
                    b3 = ccc.B;
                    //根据微分公式计算当前像素的颜色分量灰度值
                    rr = (int)(Math.Sqrt((r1 - r2) * (r1 - r2) + (r1 - r3) * (r1 - r3)));
                    gg = (int)(Math.Sqrt((g1 - g2) * (g1 - g2) + (g1 - g3) * (g1 - g3)));
                    bb = (int)(Math.Sqrt((b1 - b2) * (b1 - b2) + (b1 - b3) * (b1 - b3)));
                    //比较梯度是否大于30，是则将灰度值置为255，不是则将灰度值置为0
                    if (rr <= 30) rr = 0;
                    if (rr > 30) rr = 255;
                    if (gg <= 30) gg = 0;
                    if (gg > 30) gg = 255;
                    if (bb <= 30) bb = 0;
                    if (bb > 30) bb = 255;

                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 位彩色图像的梯度锐化ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Color cc = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int rr, gg, bb, r1, g1, b1, r2, g2, b2;
            for (i = 1; i <= pictureBox1.Image.Width - 1; i++)
            {
                for (j = 1; j <= pictureBox1.Image.Height - 1; j++)
                {
                    rr = 0; gg = 0; bb = 0;
                    c = box1.GetPixel(i, j);
                    r1 = c.R;
                    g1 = c.G;
                    b1 = c.B;

                    cc = box1.GetPixel(i - 1, j);
                    r2 = cc.R;
                    g2 = cc.G;
                    b2 = cc.B;
                    ////根据微分公式计算当前像素的颜色分量灰度值
                    rr = r1 + Math.Abs((r1 - r2) / 4);
                    gg = g1 + Math.Abs((g1 - g2) / 4);
                    bb = b1 + Math.Abs((b1 - b2) / 4);

                    if (rr > 255) rr = 255;
                    if (gg > 255) gg = 255;
                    if (bb > 255) bb = 255;

                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void roberts边缘检测算子ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c1 = new Color();
            Color c2 = new Color();
            Color c3 = new Color();
            Color c4 = new Color();
            int rr, gg, bb, i, j;
            int r1, r2, r3, r4, fxr, fyr;
            int g1, g2, g3, g4, fxg, fyg;
            int b1, b2, b3, b4, fxb, fyb;
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (i = 0; i < pictureBox1.Image.Width - 2; i++)
            {
                for (j = 0; j < pictureBox1.Image.Height - 2; j++)
                {
                    c1 = box1.GetPixel(i, j);
                    c2 = box1.GetPixel(i + 1, j + 1);
                    c3 = box1.GetPixel(i + 1, j);
                    c4 = box1.GetPixel(i, j + 1);
                    r1 = c1.R; g1 = c1.G; b1 = c1.B;
                    r2 = c2.R; g2 = c2.G; b2 = c2.B;
                    r3 = c3.R; g3 = c3.G; b3 = c3.B;
                    r4 = c4.R; g4 = c4.G; b4 = c4.B;
                    //生成Roberts边缘检测算子
                    fxr = r1 - r2; fxg = g1 - g2; fxb = b1 - b2;
                    fyr = r3 - r4; fyg = g3 - g4; fyb = b3 - b4;
                    //处理当前像素颜色分量
                    rr = Math.Abs(fxr) + Math.Abs(fyr);
                    gg = Math.Abs(fxg) + Math.Abs(fyg);
                    bb = Math.Abs(fxb) + Math.Abs(fyb);

                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;
                    Color cc = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, cc);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void sobel边缘检测算子ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c1 = new Color();
            Color c2 = new Color();
            Color c3 = new Color();
            Color c4 = new Color();
            Color c5 = new Color();
            Color c6 = new Color();
            Color c7 = new Color();
            Color c8 = new Color();
            Color c9 = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int rr, r1, r2, r3, r4, r5, r6, r7, r8, r9, fxr, fyr;
            int gg, g1, g2, g3, g4, g5, g6, g7, g8, g9, fxg, fyg;
            int bb, b1, b2, b3, b4, b5, b6, b7, b8, b9, fxb, fyb;
            for (i = 1; i < pictureBox1.Image.Width - 2; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height - 2; j++)
                {
                    c1 = box1.GetPixel(i, j - 1);
                    c2 = box1.GetPixel(i - 1, j);
                    c3 = box1.GetPixel(i, j);
                    c4 = box1.GetPixel(i + 1, j);
                    c5 = box1.GetPixel(i, j + 1);
                    c6 = box1.GetPixel(i - 1, j - 1);
                    c7 = box1.GetPixel(i - 1, j + 1);
                    c8 = box1.GetPixel(i + 1, j - 1);
                    c9 = box1.GetPixel(i + 1, j + 1);
                    r1 = c1.R; g1 = c1.G; b1 = c1.B;
                    r2 = c2.R; g2 = c2.G; b2 = c2.B;
                    r3 = c3.R; g3 = c3.G; b3 = c3.B;
                    r4 = c4.R; g4 = c4.G; b4 = c4.B;
                    r5 = c5.R; g5 = c5.G; b5 = c5.B;
                    r6 = c6.R; g6 = c6.G; b6 = c6.B;
                    r7 = c7.R; g7 = c7.G; b7 = c7.B;
                    r8 = c8.R; g8 = c8.G; b8 = c8.B;
                    r9 = c9.R; g9 = c9.G; b9 = c9.B;
                    //生成Sobel边缘检测算子
                    fxr = r6 + 2 * r2 + r7 - r8 - 2 * r4 - r9;
                    fyr = r6 + 2 * r1 + r8 - r7 - 2 * r5 - r9;
                    fxg = g6 + 2 * g2 + g7 - g8 - 2 * g4 - g9;
                    fyg = g6 + 2 * g1 + g8 - g7 - 2 * g5 - g9;
                    fxb = b6 + 2 * b2 + b7 - b8 - 2 * b4 - b9;
                    fyb = b6 + 2 * b1 + b8 - b7 - 2 * b5 - b9;
                    //处理当前像素颜色分量
                    rr = Math.Abs(fxr) + Math.Abs(fyr);
                    gg = Math.Abs(fxg) + Math.Abs(fyg);
                    bb = Math.Abs(fxb) + Math.Abs(fyb);

                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;
                    Color cc = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void prewitt边缘检测算子ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c1 = new Color();
            Color c2 = new Color();
            Color c3 = new Color();
            Color c4 = new Color();
            Color c5 = new Color();
            Color c6 = new Color();
            Color c7 = new Color();
            Color c8 = new Color();
            Color c9 = new Color();
            int i, j;
            int rr, r1, r2, r3, r4, r5, r6, r7, r8, r9, fxr1, fxr2, fxr3, fxr4, fxr5, fxr6, fxr7, fxr8;
            int gg, g1, g2, g3, g4, g5, g6, g7, g8, g9, fxg1, fxg2, fxg3, fxg4, fxg5, fxg6, fxg7, fxg8;
            int bb, b1, b2, b3, b4, b5, b6, b7, b8, b9, fxb1, fxb2, fxb3, fxb4, fxb5, fxb6, fxb7, fxb8;
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (i = 1; i < pictureBox1.Image.Width - 2; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height - 2; j++)
                {
                    c1 = box1.GetPixel(i, j - 1);
                    c2 = box1.GetPixel(i - 1, j);
                    c3 = box1.GetPixel(i, j);
                    c4 = box1.GetPixel(i + 1, j);
                    c5 = box1.GetPixel(i, j + 1);
                    c6 = box1.GetPixel(i - 1, j - 1);
                    c7 = box1.GetPixel(i - 1, j + 1);
                    c8 = box1.GetPixel(i + 1, j - 1);
                    c9 = box1.GetPixel(i + 1, j + 1);
                    r1 = c1.R; g1 = c1.G; b1 = c1.B;
                    r2 = c2.R; g2 = c2.G; b2 = c2.B;
                    r3 = c3.R; g3 = c3.G; b3 = c3.B;
                    r4 = c4.R; g4 = c4.G; b4 = c4.B;
                    r5 = c5.R; g5 = c5.G; b5 = c5.B;
                    r6 = c6.R; g6 = c6.G; b6 = c6.B;
                    r7 = c7.R; g7 = c7.G; b7 = c7.B;
                    r8 = c8.R; g8 = c8.G; b8 = c8.B;
                    r9 = c9.R; g9 = c9.G; b9 = c9.B;
                    //根据不同模板计算出Prewitt边缘检测算子
                    fxr1 = -2 * r3 + r1 + r4 + r5 + r8 + r9 - r2 - r6 - r7;
                    fxr2 = -2 * r3 + r2 + r4 + r5 + r7 + r9 - r1 - r6 - r8;
                    fxr3 = -2 * r3 + r6 + r2 + r1 + r8 + r4 - r7 - r5 - r9;
                    fxr4 = -2 * r3 + r2 + r5 + r6 + r7 + r9 - r1 - r4 - r8;
                    fxr5 = -2 * r3 + r6 + r2 + r7 + r1 + r8 - r4 - r5 - r9;
                    fxr6 = -2 * r3 + r4 + r5 + r7 + r8 + r9 - r1 - r2 - r6;
                    fxr7 = -2 * r3 + r1 + r4 + r6 + r8 + r9 - r2 - r5 - r7;
                    fxr8 = -2 * r3 + r1 + r2 + r5 + r6 + r6 - r4 - r8 - r9;
                    //求出最大值
                    fxr1 = Math.Max(fxr1, fxr2);
                    fxr1 = Math.Max(fxr1, fxr3);
                    fxr1 = Math.Max(fxr1, fxr4);
                    fxr1 = Math.Max(fxr1, fxr5);
                    fxr1 = Math.Max(fxr1, fxr6);
                    fxr1 = Math.Max(fxr1, fxr7);
                    fxr1 = Math.Max(fxr1, fxr8);
                    //将最大值设置为颜色分量
                    rr = Math.Abs(fxr1);

                    fxg1 = -2 * g3 + g1 + g4 + g5 + g8 + g9 - g2 - g6 - g7;
                    fxg2 = -2 * g3 + g2 + g4 + g5 + g7 + g9 - g1 - g6 - g8;
                    fxg3 = -2 * g3 + g6 + g2 + g1 + g8 + g4 - g7 - g5 - g9;
                    fxg4 = -2 * g3 + g2 + g5 + g6 + g7 + g9 - g1 - g4 - g8;
                    fxg5 = -2 * g3 + g6 + g2 + g7 + g1 + g8 - g4 - g5 - g9;
                    fxg6 = -2 * g3 + g4 + g5 + g7 + g8 + g9 - g1 - g2 - g6;
                    fxg7 = -2 * g3 + g1 + g4 + g6 + g8 + g9 - g2 - g5 - g7;
                    fxg8 = -2 * g3 + g1 + g2 + g5 + g6 + g6 - g4 - g8 - g9;
                    fxg1 = Math.Max(fxg1, fxg2);
                    fxg1 = Math.Max(fxg1, fxg3);
                    fxg1 = Math.Max(fxg1, fxg4);
                    fxg1 = Math.Max(fxg1, fxg5);
                    fxg1 = Math.Max(fxg1, fxg6);
                    fxg1 = Math.Max(fxg1, fxg7);
                    fxg1 = Math.Max(fxg1, fxg8);
                    gg = Math.Abs(fxg1);

                    fxb1 = -2 * b3 + b1 + b4 + b5 + b8 + b9 - b2 - b6 - b7;
                    fxb2 = -2 * b3 + b2 + b4 + b5 + b7 + b9 - b1 - b6 - b8;
                    fxb3 = -2 * b3 + b6 + b2 + b1 + b8 + b4 - b7 - b5 - b9;
                    fxb4 = -2 * b3 + b2 + b5 + b6 + b7 + b9 - b1 - b4 - b8;
                    fxb5 = -2 * b3 + b6 + b2 + b7 + b1 + b8 - b4 - b5 - b9;
                    fxb6 = -2 * b3 + b4 + b5 + b7 + b8 + b9 - b1 - b2 - b6;
                    fxb7 = -2 * b3 + b1 + b4 + b6 + b8 + b9 - b2 - b5 - b7;
                    fxb8 = -2 * b3 + b1 + b2 + b5 + b6 + b6 - b4 - b8 - b9;
                    fxb1 = Math.Max(fxb1, fxb2);
                    fxb1 = Math.Max(fxb1, fxb3);
                    fxb1 = Math.Max(fxb1, fxb4);
                    fxb1 = Math.Max(fxb1, fxb5);
                    fxb1 = Math.Max(fxb1, fxb6);
                    fxb1 = Math.Max(fxb1, fxb7);
                    fxb1 = Math.Max(fxb1, fxb8);
                    bb = Math.Abs(fxb1);

                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;

                    Color cc = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void krisch边缘检测算子ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c1 = new Color();
            Color c2 = new Color();
            Color c3 = new Color();
            Color c4 = new Color();
            Color c5 = new Color();
            Color c6 = new Color();
            Color c7 = new Color();
            Color c8 = new Color();
            Color c9 = new Color();
            int i, j;
            int rr, r1, r2, r3, r4, r5, r6, r7, r8, r9, fxr1, fxr2, fxr3, fxr4, fxr5, fxr6, fxr7, fxr8;
            int gg, g1, g2, g3, g4, g5, g6, g7, g8, g9, fxg1, fxg2, fxg3, fxg4, fxg5, fxg6, fxg7, fxg8;
            int bb, b1, b2, b3, b4, b5, b6, b7, b8, b9, fxb1, fxb2, fxb3, fxb4, fxb5, fxb6, fxb7, fxb8;
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (i = 1; i < pictureBox1.Image.Width - 2; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height - 2; j++)
                {
                    c1 = box1.GetPixel(i, j - 1);
                    c2 = box1.GetPixel(i - 1, j);
                    c3 = box1.GetPixel(i, j);
                    c4 = box1.GetPixel(i + 1, j);
                    c5 = box1.GetPixel(i, j + 1);
                    c6 = box1.GetPixel(i - 1, j - 1);
                    c7 = box1.GetPixel(i - 1, j + 1);
                    c8 = box1.GetPixel(i + 1, j - 1);
                    c9 = box1.GetPixel(i + 1, j + 1);
                    r1 = c1.R; g1 = c1.G; b1 = c1.B;
                    r2 = c2.R; g2 = c2.G; b2 = c2.B;
                    r3 = c3.R; g3 = c3.G; b3 = c3.B;
                    r4 = c4.R; g4 = c4.G; b4 = c4.B;
                    r5 = c5.R; g5 = c5.G; b5 = c5.B;
                    r6 = c6.R; g6 = c6.G; b6 = c6.B;
                    r7 = c7.R; g7 = c7.G; b7 = c7.B;
                    r8 = c8.R; g8 = c8.G; b8 = c8.B;
                    r9 = c9.R; g9 = c9.G; b9 = c9.B;
                    //根据不同模板计算出Krisch边缘检测算子
                    fxr1 = -3 * r1 - 3 * r2 + 5 * r4 - 3 * r5 - 3 * r6 - 3 * r7 + 5 * r8 + 5 * r9;
                    fxr2 = 5 * r1 - 3 * r2 + 5 * r4 - 3 * r5 - 3 * r6 - 3 * r7 + 5 * r8 - 3 * r9;
                    fxr3 = 5 * r1 - 3 * r2 - 3 * r4 - 3 * r5 + 5 * r6 - 3 * r7 + 5 * r8 - 3 * r9;
                    fxr4 = 5 * r1 + 5 * r2 - 3 * r4 - 3 * r5 + 5 * r6 - 3 * r7 - 3 * r8 - 3 * r9;
                    fxr5 = -3 * r1 + 5 * r2 - 3 * r4 - 3 * r5 + 5 * r6 + 5 * r7 - 3 * r8 - 3 * r9;
                    fxr6 = -3 * r1 + 5 * r2 - 3 * r4 + 5 * r5 - 3 * r6 + 5 * r7 - 3 * r8 - 3 * r9;
                    fxr7 = -3 * r1 - 3 * r2 - 3 * r4 + 5 * r5 - 3 * r6 + 5 * r7 - 3 * r8 + 5 * r9;
                    fxr8 = -3 * r1 - 3 * r2 + 5 * r4 + 5 * r5 - 3 * r6 - 3 * r7 - 3 * r8 + 5 * r9;
                    //求出最大值
                    fxr1 = Math.Max(fxr1, fxr2);
                    fxr1 = Math.Max(fxr1, fxr3);
                    fxr1 = Math.Max(fxr1, fxr4);
                    fxr1 = Math.Max(fxr1, fxr5);
                    fxr1 = Math.Max(fxr1, fxr6);
                    fxr1 = Math.Max(fxr1, fxr7);
                    fxr1 = Math.Max(fxr1, fxr8);
                    //将最大值设置为颜色分量
                    rr = Math.Abs(fxr1);

                    fxg1 = -3 * g1 - 3 * g2 + 5 * g4 - 3 * g5 - 3 * g6 - 3 * g7 + 5 * g8 + 5 * g9;
                    fxg2 = 5 * g1 - 3 * g2 + 5 * g4 - 3 * g5 - 3 * g6 - 3 * g7 + 5 * g8 - 3 * g9;
                    fxg3 = 5 * g1 - 3 * g2 - 3 * g4 - 3 * g5 + 5 * g6 - 3 * g7 + 5 * g8 - 3 * g9;
                    fxg4 = 5 * g1 + 5 * g2 - 3 * g4 - 3 * g5 + 5 * g6 - 3 * g7 - 3 * g8 - 3 * g9;
                    fxg5 = -3 * g1 + 5 * g2 - 3 * g4 - 3 * g5 + 5 * g6 + 5 * g7 - 3 * g8 - 3 * g9;
                    fxg6 = -3 * g1 + 5 * g2 - 3 * g4 + 5 * g5 - 3 * g6 + 5 * g7 - 3 * g8 - 3 * g9;
                    fxg7 = -3 * g1 - 3 * g2 - 3 * g4 + 5 * g5 - 3 * g6 + 5 * g7 - 3 * g8 + 5 * g9;
                    fxg8 = -3 * g1 - 3 * g2 + 5 * g4 + 5 * g5 - 3 * g6 - 3 * g7 - 3 * g8 + 5 * g9;
                    fxg1 = Math.Max(fxg1, fxg2);
                    fxg1 = Math.Max(fxg1, fxg3);
                    fxg1 = Math.Max(fxg1, fxg4);
                    fxg1 = Math.Max(fxg1, fxg5);
                    fxg1 = Math.Max(fxg1, fxg6);
                    fxg1 = Math.Max(fxg1, fxg7);
                    fxg1 = Math.Max(fxg1, fxg8);
                    gg = Math.Abs(fxg1);

                    fxb1 = -3 * b1 - 3 * b2 + 5 * b4 - 3 * b5 - 3 * b6 - 3 * b7 + 5 * b8 + 5 * b9;
                    fxb2 = 5 * b1 - 3 * b2 + 5 * b4 - 3 * b5 - 3 * b6 - 3 * b7 + 5 * b8 - 3 * b9;
                    fxb3 = 5 * b1 - 3 * b2 - 3 * b4 - 3 * b5 + 5 * b6 - 3 * b7 + 5 * b8 - 3 * b9;
                    fxb4 = 5 * b1 + 5 * b2 - 3 * b4 - 3 * b5 + 5 * b6 - 3 * b7 - 3 * b8 - 3 * b9;
                    fxb5 = -3 * b1 + 5 * b2 - 3 * b4 - 3 * b5 + 5 * b6 + 5 * b7 - 3 * b8 - 3 * b9;
                    fxb6 = -3 * b1 + 5 * b2 - 3 * b4 + 5 * b5 - 3 * b6 + 5 * b7 - 3 * b8 - 3 * b9;
                    fxb7 = -3 * b1 - 3 * b2 - 3 * b4 + 5 * b5 - 3 * b6 + 5 * b7 - 3 * b8 + 5 * b9;
                    fxb8 = -3 * b1 - 3 * b2 + 5 * b4 + 5 * b5 - 3 * b6 - 3 * b7 - 3 * b8 + 5 * b9;
                    fxb1 = Math.Max(fxb1, fxb2);
                    fxb1 = Math.Max(fxb1, fxb3);
                    fxb1 = Math.Max(fxb1, fxb4);
                    fxb1 = Math.Max(fxb1, fxb5);
                    fxb1 = Math.Max(fxb1, fxb6);
                    fxb1 = Math.Max(fxb1, fxb7);
                    fxb1 = Math.Max(fxb1, fxb8);
                    bb = Math.Abs(fxb1);

                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;

                    Color cc = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 邻域微分ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c1 = new Color();
            Color c2 = new Color();
            Color c3 = new Color();
            Color c4 = new Color();
            Color c5 = new Color();
            int rr, gg, bb, i, j;
            int r1, r2, r3, r4, r5, fxr;
            int g1, g2, g3, g4, g5, fxg;
            int b1, b2, b3, b4, b5, fxb;
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (i = 1; i < pictureBox1.Image.Width - 2; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height - 2; j++)
                {
                    c1 = box1.GetPixel(i, j - 1);
                    c2 = box1.GetPixel(i - 1, j);
                    c3 = box1.GetPixel(i, j);
                    c4 = box1.GetPixel(i + 1, j);
                    c5 = box1.GetPixel(i, j + 1);
                    r1 = c1.R;
                    r2 = c2.R;
                    r3 = c3.R;
                    r4 = c4.R;
                    r5 = c5.R;
                    fxr = 4 * r3 - r1 - r2 - r4 - r5;
                    rr = Math.Abs(fxr) * 5 + 128;
                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    g1 = c1.G;
                    g2 = c2.G;
                    g3 = c3.G;
                    g4 = c4.G;
                    g5 = c5.G;
                    fxg = 4 * g3 - g1 - g2 - g4 - g5;
                    gg = Math.Abs(fxg) * 5 + 128;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    b1 = c1.B;
                    b2 = c2.B;
                    b3 = c3.B;
                    b4 = c4.B;
                    b5 = c5.B;
                    fxb = 4 * b3 - b1 - b2 - b4 - b5;
                    bb = Math.Abs(fxb) * 5 + 128;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;
                    Color cc = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        

        private void robinson边缘检测算子ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c1 = new Color();
            Color c2 = new Color();
            Color c3 = new Color();
            Color c4 = new Color();
            Color c5 = new Color();
            Color c6 = new Color();
            Color c7 = new Color();
            Color c8 = new Color();
            Color c9 = new Color();
            int i, j;
            int rr, r1, r2, r3, r4, r5, r6, r7, r8, r9, fxr1, fxr2, fxr3, fxr4, fxr5, fxr6, fxr7, fxr8;
            int gg, g1, g2, g3, g4, g5, g6, g7, g8, g9, fxg1, fxg2, fxg3, fxg4, fxg5, fxg6, fxg7, fxg8;
            int bb, b1, b2, b3, b4, b5, b6, b7, b8, b9, fxb1, fxb2, fxb3, fxb4, fxb5, fxb6, fxb7, fxb8;
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (i = 1; i < pictureBox1.Image.Width - 2; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height - 2; j++)
                {
                    c1 = box1.GetPixel(i, j - 1);
                    c2 = box1.GetPixel(i - 1, j);
                    c3 = box1.GetPixel(i, j);
                    c4 = box1.GetPixel(i + 1, j);
                    c5 = box1.GetPixel(i, j + 1);
                    c6 = box1.GetPixel(i - 1, j - 1);
                    c7 = box1.GetPixel(i - 1, j + 1);
                    c8 = box1.GetPixel(i + 1, j - 1);
                    c9 = box1.GetPixel(i + 1, j + 1);
                    r1 = c1.R; g1 = c1.G; b1 = c1.B;
                    r2 = c2.R; g2 = c2.G; b2 = c2.B;
                    r3 = c3.R; g3 = c3.G; b3 = c3.B;
                    r4 = c4.R; g4 = c4.G; b4 = c4.B;
                    r5 = c5.R; g5 = c5.G; b5 = c5.B;
                    r6 = c6.R; g6 = c6.G; b6 = c6.B;
                    r7 = c7.R; g7 = c7.G; b7 = c7.B;
                    r8 = c8.R; g8 = c8.G; b8 = c8.B;
                    r9 = c9.R; g9 = c9.G; b9 = c9.B;
                    //根据不同模板计算出Robinson边缘检测算子
                    fxr1 = -2 * r2 + 2 * r4 - r6 - r7 + r8 + r9;
                    fxr2 = r1 - r2 + r4 - r5 - 2 * r7 + 2 * r8;
                    fxr3 = 2 * r1 - 2 * r5 + r6 - r7 + r8 - r9;
                    fxr4 = r1 + r2 - r4 - r5 + 2 * r6 - 2 * r9;
                    fxr5 = 2 * r2 - 2 * r4 + r6 + r7 - r8 - r9;
                    fxr6 = -r1 + r2 - r4 + r5 + 2 * r7 - 2 * r8;
                    fxr7 = -2 * r1 + 2 * r5 - r6 + r7 - r8 + r9;
                    fxr8 = -r1 - r2 + r4 + r5 - 2 * r6 + 2 * r9;
                    //求出最大值
                    fxr1 = Math.Max(fxr1, fxr2);
                    fxr1 = Math.Max(fxr1, fxr3);
                    fxr1 = Math.Max(fxr1, fxr4);
                    fxr1 = Math.Max(fxr1, fxr5);
                    fxr1 = Math.Max(fxr1, fxr6);
                    fxr1 = Math.Max(fxr1, fxr7);
                    fxr1 = Math.Max(fxr1, fxr8);
                    //将最大值设置为颜色分量
                    rr = Math.Abs(fxr1);

                    fxg1 = -2 * g2 + 2 * g4 - g6 - g7 + g8 + g9;
                    fxg2 = g1 - g2 + g4 - g5 - 2 * g7 + 2 * g8;
                    fxg3 = 2 * g1 - 2 * g5 + g6 - g7 + g8 - g9;
                    fxg4 = g1 + g2 - g4 - g5 + 2 * g6 - 2 * g9;
                    fxg5 = 2 * g2 - 2 * g4 + g6 + g7 - g8 - g9;
                    fxg6 = -g1 + g2 - g4 + g5 + 2 * g7 - 2 * g8;
                    fxg7 = -2 * g1 + 2 * g5 - g6 + g7 - g8 + g9;
                    fxg8 = -g1 - g2 + g4 + g5 - 2 * g6 + 2 * g9;
                    fxg1 = Math.Max(fxg1, fxg2);
                    fxg1 = Math.Max(fxg1, fxg3);
                    fxg1 = Math.Max(fxg1, fxg4);
                    fxg1 = Math.Max(fxg1, fxg5);
                    fxg1 = Math.Max(fxg1, fxg6);
                    fxg1 = Math.Max(fxg1, fxg7);
                    fxg1 = Math.Max(fxg1, fxg8);
                    gg = Math.Abs(fxg1);

                    fxb1 = -2 * b2 + 2 * b4 - b6 - b7 + b8 + b9;
                    fxb2 = b1 - b2 + b4 - b5 - 2 * b7 + 2 * b8;
                    fxb3 = 2 * b1 - 2 * b5 + b6 - b7 + b8 - b9;
                    fxb4 = b1 + b2 - b4 - b5 + 2 * b6 - 2 * b9;
                    fxb5 = 2 * b2 - 2 * b4 + b6 + b7 - b8 - b9;
                    fxb6 = -b1 + b2 - b4 + b5 + 2 * b7 - 2 * b8;
                    fxb7 = -2 * b1 + 2 * b5 - b6 + b7 - b8 + b9;
                    fxb8 = -b1 - b2 + b4 + b5 - 2 * b6 + 2 * b9;
                    fxb1 = Math.Max(fxb1, fxb2);
                    fxb1 = Math.Max(fxb1, fxb3);
                    fxb1 = Math.Max(fxb1, fxb4);
                    fxb1 = Math.Max(fxb1, fxb5);
                    fxb1 = Math.Max(fxb1, fxb6);
                    fxb1 = Math.Max(fxb1, fxb7);
                    fxb1 = Math.Max(fxb1, fxb8);
                    bb = Math.Abs(fxb1);

                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;

                    Color cc = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void smoothed边缘检测算子ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c1 = new Color();
            Color c2 = new Color();
            Color c3 = new Color();
            Color c4 = new Color();
            Color c5 = new Color();
            Color c6 = new Color();
            Color c7 = new Color();
            Color c8 = new Color();
            Color c9 = new Color();
            int i, j;
            int rr, r1, r2, r3, r4, r5, r6, r7, r8, r9, fxr, fyr;
            int gg, g1, g2, g3, g4, g5, g6, g7, g8, g9, fxg, fyg;
            int bb, b1, b2, b3, b4, b5, b6, b7, b8, b9, fxb, fyb;
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (i = 1; i < pictureBox1.Image.Width - 2; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height - 2; j++)
                {
                    c1 = box1.GetPixel(i, j - 1);
                    c2 = box1.GetPixel(i - 1, j);
                    c3 = box1.GetPixel(i, j);
                    c4 = box1.GetPixel(i + 1, j);
                    c5 = box1.GetPixel(i, j + 1);
                    c6 = box1.GetPixel(i - 1, j - 1);
                    c7 = box1.GetPixel(i - 1, j + 1);
                    c8 = box1.GetPixel(i + 1, j - 1);
                    c9 = box1.GetPixel(i + 1, j + 1);
                    r1 = c1.R; g1 = c1.G; b1 = c1.B;
                    r2 = c2.R; g2 = c2.G; b2 = c2.B;
                    r3 = c3.R; g3 = c3.G; b3 = c3.B;
                    r4 = c4.R; g4 = c4.G; b4 = c4.B;
                    r5 = c5.R; g5 = c5.G; b5 = c5.B;
                    r6 = c6.R; g6 = c6.G; b6 = c6.B;
                    r7 = c7.R; g7 = c7.G; b7 = c7.B;
                    r8 = c8.R; g8 = c8.G; b8 = c8.B;
                    r9 = c9.R; g9 = c9.G; b9 = c9.B;
                    //计算出Smoothed边缘检测算子
                    fxr = -r6 - r2 - r7 + r8 + r4 + r9;
                    fyr = r6 + r1 + r8 - r7 - r5 - r9;
                    fxg = -g6 - g2 - g7 + g8 + g4 + g9;
                    fyg = g6 + g1 + g8 - g7 - g5 - g9;
                    fxb = -b6 - b2 - b7 + b8 + b4 + b9;
                    fyb = b6 + b1 + b8 - b7 - b5 - b9;
                    //处理当前像素颜色分量
                    rr = Math.Abs(fxr) + Math.Abs(fyr);
                    gg = Math.Abs(fxg) + Math.Abs(fyg);
                    bb = Math.Abs(fxb) + Math.Abs(fyb);
                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;
                    Color cc = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 右下边缘抽出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c1 = new Color();
            Color c2 = new Color();
            Color c3 = new Color();
            Color c4 = new Color();
            Color c5 = new Color();
            Color c6 = new Color();
            Color c7 = new Color();
            Color c8 = new Color();
            Color c9 = new Color();
            int i, j;
            int rr, r1, r2, r3, r4, r5, r6, r7, r8, r9, fxr;
            int gg, g1, g2, g3, g4, g5, g6, g7, g8, g9, fxg;
            int bb, b1, b2, b3, b4, b5, b6, b7, b8, b9, fxb;
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (i = 1; i < pictureBox1.Image.Width - 2; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height - 2; j++)
                {
                    c1 = box1.GetPixel(i, j - 1);
                    c2 = box1.GetPixel(i - 1, j);
                    c3 = box1.GetPixel(i, j);
                    c4 = box1.GetPixel(i + 1, j);
                    c5 = box1.GetPixel(i, j + 1);
                    c6 = box1.GetPixel(i - 1, j - 1);
                    c7 = box1.GetPixel(i - 1, j + 1);
                    c8 = box1.GetPixel(i + 1, j - 1);
                    c9 = box1.GetPixel(i + 1, j + 1);
                    r1 = c1.R; g1 = c1.G; b1 = c1.B;
                    r2 = c2.R; g2 = c2.G; b2 = c2.B;
                    r3 = c3.R; g3 = c3.G; b3 = c3.B;
                    r4 = c4.R; g4 = c4.G; b4 = c4.B;
                    r5 = c5.R; g5 = c5.G; b5 = c5.B;
                    r6 = c6.R; g6 = c6.G; b6 = c6.B;
                    r7 = c7.R; g7 = c7.G; b7 = c7.B;
                    r8 = c8.R; g8 = c8.G; b8 = c8.B;
                    r9 = c9.R; g9 = c9.G; b9 = c9.B;
                    fxr = -2 * r2 - 2 * r5 + 2 * r1 + 2 * r4;
                    fxg = -2 * g2 - 2 * g5 + 2 * g1 + 2 * g4;
                    fxb = -2 * b2 - 2 * b5 + 2 * b1 + 2 * b4;
                    rr = Math.Abs(fxr);
                    gg = Math.Abs(fxg);
                    bb = Math.Abs(fxb);
                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;
                    Color cc = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void toolStripMenuItem3_Click(object sender, EventArgs e)
        {

        }

        private void 基本高通ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, m, n;
            int rr, gg, bb, ki, kj, kp, kq, k1, k2;
            int[,] r1 = new int[800, 800];
            int[,] g1 = new int[800, 800];
            int[,] b1 = new int[800, 800];
            int[,] r2 = new int[800, 800];
            int[,] g2 = new int[800, 800];
            int[,] b2 = new int[800, 800];
            int[,] h1 = new int[30, 30];

            h1[0, 0] = 1; h1[0, 1] = -2; h1[0, 2] = 1;
            h1[1, 0] = -2; h1[1, 1] = 5; h1[1, 2] = -2;
            h1[2, 0] = 1; h1[2, 1] = -2; h1[2, 2] = 1;
            for (i = 0; i <= pictureBox1.Image.Width - 2; i++)
            {
                for (j = 0; j <= pictureBox1.Image.Height - 2; j++)
                {
                    c = box1.GetPixel(i, j);
                    r1[i, j] = c.R;
                    g1[i, j] = c.G;
                    b1[i, j] = c.B;
                }
            }
            m = pictureBox1.Image.Width; n = pictureBox1.Image.Height;
            for (k1 = 1; k1 <= m - 1; k1++)
            {
                for (k2 = 1; k2 <= n - 1; k2++)
                {
                    rr = 0; gg = 0; bb = 0;
                    for (i = 0; i <= 2; i++)
                    {
                        for (j = 0; j <= 2; j++)
                        {
                            ki = k1 - i; kj = k2 - j;
                            if (((ki >= 0) & (ki <= m)) & ((kj >= 0) & (kj <= n)))
                            {
                                rr = (int)(rr + r1[ki, kj] * h1[i, j]);
                                gg = (int)(gg + g1[ki, kj] * h1[i, j]);
                                bb = (int)(bb + b1[ki, kj] * h1[i, j]);

                            }
                        }
                    }
                    kp = k1 - 1;
                    kq = k2 - 1;
                    r2[kp, kq] = Math.Abs(rr);
                    g2[kp, kq] = Math.Abs(gg);
                    b2[kp, kq] = Math.Abs(bb);
                    if (r2[kp, kq] < 0) r2[kp, kq] = 0;
                    if (r2[kp, kq] > 255) r2[kp, kq] = 255;
                    if (g2[kp, kq] < 0) g2[kp, kq] = 0;
                    if (g2[kp, kq] > 255) g2[kp, kq] = 255;
                    if (b2[kp, kq] < 0) b2[kp, kq] = 0;
                    if (b2[kp, kq] > 255) b2[kp, kq] = 255;
                    Color cc = Color.FromArgb(r2[kp, kq], g2[kp, kq], b2[kp, kq]);
                    box2.SetPixel(k1, k2, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 中等高通ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, m, n;
            int rr, gg, bb, ki, kj, kp, kq, k1, k2;
            int[,] r1 = new int[800, 800];
            int[,] g1 = new int[800, 800];
            int[,] b1 = new int[800, 800];
            int[,] r2 = new int[800, 800];
            int[,] g2 = new int[800, 800];
            int[,] b2 = new int[800, 800];
            int[,] h1 = new int[30, 30];

            h1[0, 0] = 0; h1[0, 1] = -1; h1[0, 2] = 0;
            h1[1, 0] = -1; h1[1, 1] = 5; h1[1, 2] = -1;
            h1[2, 0] = 0; h1[2, 1] = -1; h1[2, 2] = 0;
            for (i = 0; i <= pictureBox1.Image.Width - 2; i++)
            {
                for (j = 0; j <= pictureBox1.Image.Height - 2; j++)
                {
                    c = box1.GetPixel(i, j);
                    r1[i, j] = c.R;
                    g1[i, j] = c.G;
                    b1[i, j] = c.B;
                }
            }
            m = pictureBox1.Image.Width; n = pictureBox1.Image.Height;
            for (k1 = 1; k1 <= m - 1; k1++)
            {
                for (k2 = 1; k2 <= n - 1; k2++)
                {
                    rr = 0; gg = 0; bb = 0;
                    for (i = 0; i <= 2; i++)
                    {
                        for (j = 0; j <= 2; j++)
                        {
                            ki = k1 - i; kj = k2 - j;
                            if (((ki >= 0) & (ki <= m)) & ((kj >= 0) & (kj <= n)))
                            {
                                rr = (int)(rr + r1[ki, kj] * h1[i, j]);
                                gg = (int)(gg + g1[ki, kj] * h1[i, j]);
                                bb = (int)(bb + b1[ki, kj] * h1[i, j]);

                            }
                        }
                    }
                    kp = k1 - 1;
                    kq = k2 - 1;
                    r2[kp, kq] = Math.Abs(rr);
                    g2[kp, kq] = Math.Abs(gg);
                    b2[kp, kq] = Math.Abs(bb);
                    if (r2[kp, kq] < 0) r2[kp, kq] = 0;
                    if (r2[kp, kq] > 255) r2[kp, kq] = 255;
                    if (g2[kp, kq] < 0) g2[kp, kq] = 0;
                    if (g2[kp, kq] > 255) g2[kp, kq] = 255;
                    if (b2[kp, kq] < 0) b2[kp, kq] = 0;
                    if (b2[kp, kq] > 255) b2[kp, kq] = 255;
                    Color cc = Color.FromArgb(r2[kp, kq], g2[kp, kq], b2[kp, kq]);
                    box2.SetPixel(k1, k2, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 过量高通ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, m, n;
            int rr, gg, bb, ki, kj, kp, kq, k1, k2;
            int[,] r1 = new int[800, 800];
            int[,] g1 = new int[800, 800];
            int[,] b1 = new int[800, 800];
            int[,] r2 = new int[800, 800];
            int[,] g2 = new int[800, 800];
            int[,] b2 = new int[800, 800];
            int[,] h1 = new int[30, 30];

            h1[0, 0] = -1; h1[0, 1] = -1; h1[0, 2] = -1;
            h1[1, 0] = -1; h1[1, 1] = 9; h1[1, 2] = -1;
            h1[2, 0] = -1; h1[2, 1] = -1; h1[2, 2] = -1;
            for (i = 0; i <= pictureBox1.Image.Width - 2; i++)
            {
                for (j = 0; j <= pictureBox1.Image.Height - 2; j++)
                {
                    c = box1.GetPixel(i, j);
                    r1[i, j] = c.R;
                    g1[i, j] = c.G;
                    b1[i, j] = c.B;
                }
            }
            m = pictureBox1.Image.Width; n = pictureBox1.Image.Height;
            for (k1 = 1; k1 <= m - 1; k1++)
            {
                for (k2 = 1; k2 <= n - 1; k2++)
                {
                    rr = 0; gg = 0; bb = 0;
                    for (i = 0; i <= 2; i++)
                    {
                        for (j = 0; j <= 2; j++)
                        {
                            ki = k1 - i; kj = k2 - j;
                            if (((ki >= 0) & (ki <= m)) & ((kj >= 0) & (kj <= n)))
                            {
                                rr = (int)(rr + r1[ki, kj] * h1[i, j]);
                                gg = (int)(gg + g1[ki, kj] * h1[i, j]);
                                bb = (int)(bb + b1[ki, kj] * h1[i, j]);

                            }
                        }
                    }
                    kp = k1 - 1;
                    kq = k2 - 1;
                    r2[kp, kq] = Math.Abs(rr);
                    g2[kp, kq] = Math.Abs(gg);
                    b2[kp, kq] = Math.Abs(bb);
                    if (r2[kp, kq] < 0) r2[kp, kq] = 0;
                    if (r2[kp, kq] > 255) r2[kp, kq] = 255;
                    if (g2[kp, kq] < 0) g2[kp, kq] = 0;
                    if (g2[kp, kq] > 255) g2[kp, kq] = 255;
                    if (b2[kp, kq] < 0) b2[kp, kq] = 0;
                    if (b2[kp, kq] > 255) b2[kp, kq] = 255;
                    Color cc = Color.FromArgb(r2[kp, kq], g2[kp, kq], b2[kp, kq]);
                    box2.SetPixel(k1, k2, cc);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 彩色图像的浮雕处理ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int j;
            Color c = new Color();
            Color cc = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int rr, gg, bb, r1, g1, b1, r2, g2, b2;
            for (int i = 0; i < box1.Width - 1; i++)
                for (j = 0; j < box1.Height - 1; j++)
                {
                    rr = 0; gg = 0; bb = 0;
                    c = box1.GetPixel(i, j);
                    r1 = c.R;
                    g1 = c.G;
                    b1 = c.B;

                    cc = box1.GetPixel(i + 1, j + 1);
                    r2 = cc.R;
                    g2 = cc.G;
                    b2 = cc.B;

                    rr = Math.Abs(r2 - r1 + 128);
                    gg = Math.Abs(g2 - g1 + 128);
                    bb = Math.Abs(b2 - b1 + 128);

                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;

                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 彩色图像的霓虹处理ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Color cc = new Color();
            Color ccc = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int rr, gg, bb, r1, g1, b1, r2, g2, b2, rr1, rr2, gg1, gg2, bb1, bb2, r3, g3, b3;
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    rr = 0; gg = 0; bb = 0;
                    c = box1.GetPixel(i, j);
                    r1 = c.R;
                    g1 = c.G;
                    b1 = c.B;

                    cc = box1.GetPixel(i + 1, j);
                    r2 = cc.R;
                    g2 = cc.G;
                    b2 = cc.B;

                    ccc = box1.GetPixel(i, j + 1);
                    r3 = ccc.R;
                    g3 = ccc.G;
                    b3 = ccc.B;

                    rr1 = (r1 - r2) * (r1 - r2); rr2 = (r1 - r3) * (r1 - r3);
                    gg1 = (g1 - g2) * (g1 - g2); gg2 = (g1 - g3) * (g1 - g3);
                    bb1 = (b1 - b2) * (b1 - b2); bb2 = (b1 - b3) * (b1 - b3);

                    rr = (int)(2 * Math.Sqrt(rr1 + rr2));
                    gg = (int)(2 * Math.Sqrt(gg1 + gg2));
                    bb = (int)(2 * Math.Sqrt(bb1 + bb2));

                    if (rr < 0) rr = 0;
                    if (rr > 255) rr = 255;
                    if (gg < 0) gg = 0;
                    if (gg > 255) gg = 255;
                    if (bb < 0) bb = 0;
                    if (bb > 255) bb = 255;

                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 横向微分ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int r, g, b;
            int[, ,] pic = new int[600, 600, 3];

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    pic[i, j, 0] = c.R;
                    pic[i, j, 1] = c.G;
                    pic[i, j, 2] = c.B;
                }
            }
            for (int i = 0; i < box1.Width - 1; i++)
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = pic[i, j, 0] = Math.Abs(pic[i, j, 0] - pic[i, j + 1, 0]);
                    g = pic[i, j, 1] = Math.Abs(pic[i, j, 1] - pic[i, j + 1, 1]);
                    b = pic[i, j, 2] = Math.Abs(pic[i, j, 2] - pic[i, j + 1, 2]);
                    Color c1 = Color.FromArgb(r, g, b);
                    box2.SetPixel(i, j, c1);

                }

            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 纵向微分ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int r, g, b;
            int[, ,] pic = new int[600, 600, 3];

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    pic[i, j, 0] = c.R;
                    pic[i, j, 1] = c.G;
                    pic[i, j, 2] = c.B;
                }
            }
            for (int i = 0; i < box1.Width - 1; i++)
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = pic[i, j, 0] = Math.Abs(pic[i, j, 0] - pic[i + 1, j, 0]);
                    g = pic[i, j, 1] = Math.Abs(pic[i, j, 1] - pic[i + 1, j, 1]);
                    b = pic[i, j, 2] = Math.Abs(pic[i, j, 2] - pic[i + 1, j, 2]);
                    Color c1 = Color.FromArgb(r, g, b);
                    box2.SetPixel(i, j, c1);

                }

            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 双向微分ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int r, g, b;
            int[, ,] pic = new int[600, 600, 3];

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    pic[i, j, 0] = c.R;
                    pic[i, j, 1] = c.G;
                    pic[i, j, 2] = c.B;
                }
            }
            for (int i = 0; i < box1.Width - 1; i++)
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = pic[i, j, 0] = Math.Abs(pic[i, j, 0] - pic[i + 1, j + 1, 0]);
                    g = pic[i, j, 1] = Math.Abs(pic[i, j, 1] - pic[i + 1, j + 1, 1]);
                    b = pic[i, j, 2] = Math.Abs(pic[i, j, 2] - pic[i + 1, j + 1, 2]);
                    Color c1 = Color.FromArgb(r, g, b);
                    box2.SetPixel(i, j, c1);

                }

            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 灰度直方图ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);

            int[,] h = new int[400, 400];
            int[] t = new int[300];
            Color c = Color.FromArgb(0);
            int i, j;
            int r;
            int max = 0;

            Bitmap pic = new Bitmap(pictureBox1.Image);
            //扫描原图，对各个像素进行灰度统计
            for (i = 1; i < pictureBox1.Image.Width; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height; j++)
                {
                    c = pic.GetPixel(i, j);
                    r = c.R;
                    h[i, j] = r;
                }
            }
            //灰度统计计数
            for (i = 1; i < pictureBox1.Image.Width; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height; j++)
                {
                    for (r = 0; r < 255; r++)
                    {
                        if (h[i, j] == r)
                        {
                            t[r] = t[r] + 1;
                        }
                    }
                }
            }
            //获得直方图的高度
            max = t[0];
            for (i = 0; i < t.Length - 1; i++)
            {
                if (t[i] > max)
                {
                    max = t[i];
                }
            }
            max = max / 2 + 1;
            Bitmap box2 = new Bitmap(255, max);
            for (r = 0; r < 255; r++)
            {
                for (j = 1; j < t[r]; j++)
                {
                    box2.SetPixel(r, max - j / 2 - 1, c);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 直方图门限选择ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MenXian frm1 = new MenXian();
            frm1.FormBorderStyle = FormBorderStyle.FixedDialog;//对话框边缘风格
            frm1.StartPosition = FormStartPosition.CenterParent;//在父窗体的中间显示该对话框   
            frm1.ShowDialog(this);//此处必须有this,否则模态对话框(垄断用户输入)不能显示

            int n = frm1.MenXian_n;

            //bool flag2 = false;
            //flag2 = frm1.flag1;
            if (frm1.p == 1)
            {
                return;
            }

            int r, g, b;
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);

            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    g = c.G;
                    b = c.B;
                    if ((Math.Abs(r - n) < 30) && (Math.Abs(g - n) < 30) && (Math.Abs(b - n) < 30))
                    {
                        Color c1 = Color.FromArgb(0, 0, 0);
                        box2.SetPixel(i, j, c1);
                    }
                    else
                    {
                        Color c1 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c1);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 半阈值选择分割ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MenXian frm1 = new MenXian();
            frm1.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm1.StartPosition = FormStartPosition.CenterParent;
            frm1.ShowDialog(this);

            int n = frm1.MenXian_n;
            //bool flag2 = false;
            //flag2 = frm1.flag1;
            if (frm1.p == 1)
            {
                return;
            }

            int r, g, b;
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);

            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    g = c.G;
                    b = c.B;
                    if (r < 110 && g < 110 && b < 110)
                    {
                        r = g = b = 0;
                    }
                    else
                    {
                        r = g = b = 255;
                    }
                    if (((r - n) < 50) && ((g - n) < 50) && ((b - n) < 50))
                    {
                        Color c1 = Color.FromArgb(0, 0, 0);
                        box2.SetPixel(i, j, c1);
                    }
                    else
                    {
                        Color c1 = Color.FromArgb(r, g, b);
                        box2.SetPixel(i, j, c1);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 迭代阈值图像分割ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int[,] h = new int[400, 400];
            float[] t = new float[300];
            int T1 = 127;
            int T2 = 0;
            int cc;
            float temp0, temp1, temp2, temp3;
            temp0 = temp1 = temp2 = temp3 = 0;

            for (i = 1; i < pictureBox1.Image.Width; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height; j++)
                {
                    c = box1.GetPixel(i, j);
                    cc = c.R;
                    h[i, j] = cc;
                }
            }
            for (i = 1; i < pictureBox1.Image.Width; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height; j++)
                {
                    for (cc = 0; cc < 255; cc++)
                    {
                        if (h[i, j] == cc)
                        {
                            t[cc] = t[cc] + 1;
                        }
                    }
                }
            }
            for (int a = 0; a < 256; a++)
            {
                t[a] = t[a] / (box1.Height * box1.Width * 1.0f);
            }
            for (i = 0; i < T1 + 1; i++)
            {
                temp0 += t[i] * i;
                temp1 += t[i];
            }
            for (i = T1 + 1; i < 256; i++)
            {
                temp2 += t[i] * i;
                temp3 += t[i];
            }
            T2 = (int)(temp0 / temp1 + temp2 / temp3) / 2;

            if (T1 != T2)
            {
                T1 = T2;
            }

            for (j = 0; j < box1.Height; j++)
                for (i = 0; i < box1.Width; i++)
                {
                    c = box1.GetPixel(i, j);
                    cc = c.R;
                    if (cc < T1)
                    {
                        Color c1 = Color.FromArgb(0, 0, 0);
                        box2.SetPixel(i, j, c1);
                    }
                    else
                    {
                        Color c1 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c1);
                    }
                }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 类判别分析法ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            double num;
            int i, j;
            int k;
            int[,] h = new int[400, 400];
            int r;
            int[] hd = new int[300];
            double[] p = new double[300];
            double[] tt = new double[300];
            double u = 0;
            double[] uu = new double[300];
            double[] w = new double[300];
            double[] b = new double[300];
            double max;
            double maxb = 0;
            int t;
            Color cc1 = Color.FromArgb(255, 255, 255);
            Color cc2 = Color.FromArgb(0, 0, 0);
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            for (i = 1; i < pictureBox1.Image.Width; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    h[i, j] = r;
                }
            }
            for (i = 1; i < pictureBox1.Image.Width; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height; j++)
                {
                    for (r = 0; r < 255; r++)
                    {
                        if (h[i, j] == r)
                            tt[r] = tt[r] + 1;
                    }
                }

            }
            for (t = 0; t < 255; t++)
            {
                p[t] = tt[t] / (pictureBox1.Image.Width * pictureBox1.Image.Height);
            }
            for (t = 1; t < 256; t++)
            {
                u = u + (t - 1) * p[t];
            }
            for (k = 1; k < 256; k++)
            {
                uu[k] = uu[k - 1] + (k - 1) * p[k];
                w[k] = w[k - 1] + p[k];
                if (w[k] * (1 - w[k]) != 0)
                    b[k] = ((u * w[k] - uu[k]) * (u * w[k] - uu[k])) / (w[k] * (1 - w[k]));
            }
            max = b[0];
            for (k = 0; k < 255; k++)
            {
                if (b[k] >= max)
                    max = b[k];
            }
            for (k = 0; k < 255; k++)
            {
                if (b[k] == max)
                    maxb = k;
            }
            num = maxb - 1;
            for (i = 1; i < pictureBox1.Image.Width; i++)
            {
                for (j = 1; j < pictureBox1.Image.Height; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    if (r > (maxb - 1))
                        box1.SetPixel(i, j, cc2);
                    else
                        box1.SetPixel(i, j, cc1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box1;
        }

        private void 灰度级切片法ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);

            int rr, lev, wid, x, m;
            int[] lut = new int[256];
            int[, ,] pic = new int[600, 600, 3];
            lev = 30;
            wid = 100;
            for (x = 0; x <= lev; x++)
            {
                lut[x] = 255;
            }
            for (x = lev; x <= lev + wid - 1; x++)
            {
                lut[x] = 0;
            }
            for (x = 129; x <= 255; x += 1)
            {
                lut[x] = 255;
            }
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    pic[i, j, 0] = c.R;
                    pic[i, j, 1] = c.G;
                    pic[i, j, 2] = c.B;
                }
            }
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    m = pic[i, j, 2];
                    rr = lut[m];
                    Color c1 = Color.FromArgb(rr, rr, rr);
                    box1.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box1;
        }

        private void 等灰度片二值化ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int rr, lev, wid, x, y, m;
            int[] lut = new int[256];
            int[, ,] pic = new int[600, 600, 3];
            lev = 50;
            wid = 100;
            y = 0;
            while (y <= 256)
            {
                for (x = 0; x <= lev - 1; x++)
                {
                    lut[y] = 255;
                    y = y + 1;
                    if (y > 255) goto loop;
                }
                for (x = 0; x <= wid - 1; x++)
                {
                    lut[y] = 0;
                    y = y + 1;
                    if (y > 255) goto loop;
                }
            }
        loop:

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    pic[i, j, 0] = c.R;
                    pic[i, j, 1] = c.G;
                    pic[i, j, 2] = c.B;
                }
            }
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    m = pic[i, j, 2];
                    rr = lut[m];
                    Color c1 = Color.FromArgb(rr, rr, rr);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 线性二值化ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int rr, lev, wid, x, y, m;
            int[] lut = new int[256];
            int[, ,] pic = new int[600, 600, 3];
            lev = 50;
            wid = 120;
            y = 0;
            while (y <= 256)
            {

                for (x = 0; x <= lev - 1; x++)
                {
                    lut[y] = 255;
                    y = y + 1;
                    if (y > 255) goto loop;
                }

                for (x = 0; x <= wid - 1; x++)
                {
                    lut[y] = y / 2;
                    y = y + 1;
                    if (y > 255) goto loop;
                }
            }

        loop:

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    pic[i, j, 0] = c.R;
                    pic[i, j, 1] = c.G;
                    pic[i, j, 2] = c.B;
                }
            }
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    m = pic[i, j, 2];
                    rr = lut[m];
                    Color c1 = Color.FromArgb(rr, rr, rr);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 轮廓提取法ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int cc, r1, r2, r3, r4, r5, r6, r7, r8;

            for (j = 1; j < box1.Height - 2; j++)
                for (i = 1; i < box1.Width - 2; i++)
                {
                    c = box1.GetPixel(i, j);
                    cc = c.R;
                    c = box1.GetPixel(i + 1, j);
                    r1 = c.R;
                    c = box1.GetPixel(i - 1, j);
                    r2 = c.R;
                    c = box1.GetPixel(i - 1, j + 1);
                    r3 = c.R;
                    c = box1.GetPixel(i - 1, j - 1);
                    r4 = c.R;
                    c = box1.GetPixel(i + 1, j - 1);
                    r5 = c.R;
                    c = box1.GetPixel(i + 1, j + 1);
                    r6 = c.R;
                    c = box1.GetPixel(i, j + 1);
                    r7 = c.R;
                    c = box1.GetPixel(i, j - 1);
                    r8 = c.R;
                    if ((Math.Abs(r1 - cc) < 10) && (Math.Abs(r2 - cc) < 10) && (Math.Abs(r3 - cc) < 10) && (Math.Abs(r4 - cc) < 10) && (Math.Abs(r5 - cc) < 10) && (Math.Abs(r6 - cc) < 10) && (Math.Abs(r7 - cc) < 10) && (Math.Abs(r8 - cc) < 10))
                    {
                        Color c1 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c1);
                    }
                    else
                    {
                        Color c2 = Color.FromArgb(cc, cc, cc);
                        box2.SetPixel(i, j, c2);
                    }
                }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 边界跟踪法ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color cc = new Color();
            Color c0 = new Color();
            Color c1 = new Color();
            Color c2 = new Color();
            Color c3 = new Color();
            Color c4 = new Color();
            Color c5 = new Color();
            Color c6 = new Color();
            Color c7 = new Color();

            Color cc3 = new Color();
            Color lpc = new Color();

            int i, j;
            int x = 0;
            int y = 0;
            int m = 1;
            int n = 1;
            int rr, r0, r1, r2, r3, r4, r5, r6, r7, lpcr;
            int rr3;
            int[,] state = new int[8, 2] { { -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 0 } };//8个方向和起始扫描方向

            bool findpoint;//当前查找点
            bool findstartpoint = false;//查找起始点
            int startdirect = 0;//跟踪边界

            ArrayList height1 = new ArrayList();//动态数组
            ArrayList width1 = new ArrayList();

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);

            for (i = 0; i < box1.Width; i++)
            {
                for (j = 0; j < box1.Height; j++)
                {
                    cc = box1.GetPixel(i, j);
                    rr = cc.R;
                    if (rr == 0)
                    {
                        height1.Add("j");
                        width1.Add("i");
                        m = i;
                        n = j;
                        Color bla = Color.FromArgb(0, 0, 0);
                        box1.SetPixel(i, j, bla);
                    }
                }

            }
            cc3 = box1.GetPixel(m, n);
            rr3 = cc3.R;

            c0 = box1.GetPixel(m - 1, n - 1);
            c1 = box1.GetPixel(m, n - 1);
            c2 = box1.GetPixel(m + 1, n - 1);
            c3 = box1.GetPixel(m + 1, n);
            c4 = box1.GetPixel(m + 1, n + 1);
            c5 = box1.GetPixel(m, n + 1);
            c6 = box1.GetPixel(m - 1, n + 1);
            c7 = box1.GetPixel(m - 1, n);

            r0 = c0.R;
            r1 = c1.R;
            r2 = c2.R;
            r3 = c3.R;
            r4 = c4.R;
            r5 = c5.R;
            r6 = c6.R;
            r7 = c7.R;

            x = m;
            y = n;

            while (!findstartpoint)
            {
                findpoint = false;
                while (!findpoint)
                {
                    lpc = box1.GetPixel(x + state[startdirect, 1], y + state[startdirect, 0]);//原像素
                    lpcr = lpc.R;

                    if (lpcr == 0)
                    {
                        findpoint = true;

                        x = x + state[startdirect, 1];
                        y = y + state[startdirect, 0];
                        if (x == m && y == n)
                        {
                            findstartpoint = true;
                        }

                        Color pic = Color.FromArgb(0, 0, 0);
                        box2.SetPixel(x, y, pic);
                        startdirect--;

                        if (startdirect == -1)
                        {
                            startdirect = 7;
                        }
                        startdirect--;
                        if (startdirect == -1)
                        {
                            startdirect = 7;
                        }
                    }
                    else
                    {
                        startdirect++;
                        if (startdirect == 8)
                        {
                            startdirect = 0;
                        }
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 区域增长法ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Color seed = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int cc, ss;
            for (j = 1; j < box1.Height - 1; j++)
                for (i = 1; i < box1.Width - 1; i++)
                {
                    c = box1.GetPixel(i, j);
                    cc = c.R;
                    seed = box1.GetPixel(50, 50);
                    ss = seed.R;
                    if ((Math.Abs(cc - ss) < 10))
                    {
                        Color c1 = Color.FromArgb(ss, ss, ss);
                        box2.SetPixel(i, j, c1);
                    }
                    else
                    {
                        Color c2 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c2);
                    }

                }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 邻4减法ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);//把图片框中的图片给bitmap类型
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int r;
            int[,] ss = new int[600, 600];
            for (int i = 0; i < box1.Width - 1; i += 1)
            {
                for (int j = 0; j < box1.Height - 1; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    if (r == 0)
                    { ss[i, j] = 1; }
                    else
                    {
                        ss[i, j] = 0;
                        //用fromargb方法由颜色分量值创造color结构
                        Color c1 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c1);
                    }
                }
            }
            for (int i = 1; i < box1.Width - 1; i += 1)
            {
                for (int j = 1; j < box1.Height - 1; j += 1)
                {
                    if (ss[i, j - 1] + ss[i, j + 1] + ss[i + 1, j] + ss[i - 1, j] >= 4)
                    {
                        Color c1 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c1);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 邻8减法ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);//把图片框中的图片给bitmap类型
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int r;
            int[,] ss = new int[600, 600];
            for (int i = 0; i < box1.Width - 1; i += 1)
            {
                for (int j = 0; j < box1.Height - 1; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    if (r == 0)
                    { ss[i, j] = 1; }
                    else
                    {
                        ss[i, j] = 0;
                        Color c1 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c1);
                    }
                }
            }
            for (int i = 1; i < box1.Width - 1; i += 1)
            {
                for (int j = 1; j < box1.Height - 1; j += 1)
                {
                    if (ss[i, j - 1] + ss[i, j + 1] + ss[i + 1, j] + ss[i - 1, j] + ss[i - 1, j - 1] + ss[i - 1, j + 1] + ss[i + 1, j - 1] + ss[i + 1, j + 1] >= 8)
                    {
                        Color c1 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c1);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 全图检测法ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);//把图片框中的图片给bitmap类型
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int r;
            int[,] ss = new int[600, 600];
            int[,] kk = new int[600, 600];
            for (int i = 0; i < box1.Width - 1; i += 1)
            {
                for (int j = 0; j < box1.Height - 1; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    if (r == 0)
                    { ss[i, j] = 1; }
                    else
                    {
                        ss[i, j] = 0;
                        Color c1 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c1);
                    }
                }
            }
            for (int i = 1; i < box1.Width - 1; i += 1)
            {
                for (int j = 1; j < box1.Height - 1; j += 1)
                {
                    if (ss[i, j] == 1 && ss[i, j - 1] == 0)
                    {
                        kk[i, j] = 1;
                    }
                    else
                    {
                        if (ss[i, j] == 0 && ss[i, j - 1] == 1)
                        {
                            kk[i, j - 1] = 1;
                        }
                    }

                }
            }
            for (int i = 1; i < box1.Width - 1; i += 1)
            {
                for (int j = 1; j < box1.Height - 1; j += 1)
                {
                    if (ss[i - 1, j] == 0 && ss[i, j] == 1)
                    {
                        kk[i, j] = 1;
                    }
                    else
                    {
                        if (ss[i - 1, j] == 1 && ss[i, j] == 0)
                        {
                            kk[i - 1, j] = 1;
                        }
                    }

                }
            }
            for (int i = 0; i < box1.Width - 1; i += 1)
            {
                for (int j = 0; j < box1.Height - 1; j += 1)
                {
                    if (kk[i, j] != 1)
                    {
                        Color c1 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c1);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 图像面积测量ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int r;
            int sign = 0;
            int[] flag = new int[10000];
            flag[sign] = 0;
            for (i = 0; i < box1.Width; i++)
            {
                for (j = 0; j < box1.Height; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    if (r > 128)
                    {
                        r = 255;
                    }
                    else
                    {
                        r = 0;
                    }

                    if (r == 0)
                    {
                        sign = r;
                        flag[sign] += 1;
                    }
                    Color c1 = Color.FromArgb(r, r, r);
                    box2.SetPixel(i, j, c1);
                }

            }

            Label lbl = new Label();
            string name = "图形的面积是：" + Convert.ToString(flag[sign]);
            lbl.Name = name;
            lbl.Text = name;
            lbl.AutoSize = true;
            Point drawPoint = new Point();
            drawPoint.X = 75;
            drawPoint.Y = 240;
            lbl.Location = drawPoint;
            pictureBox2.Controls.Add(lbl);
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 图像周长测量ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color cc = new Color();
            Color c0 = new Color();
            Color c1 = new Color();
            Color c2 = new Color();
            Color c3 = new Color();
            Color c4 = new Color();
            Color c5 = new Color();
            Color c6 = new Color();
            Color c7 = new Color();

            Color cc3 = new Color();
            Color lpc = new Color();
            Color c = new Color();
            int r;
            int i, j;
            int x = 0;
            int y = 0;
            int m = 1;
            int n = 1;
            int rr, r0, r1, r2, r3, r4, r5, r6, r7, lpcr;
            int rr3;
            int sign = 0;
            int[] flag = new int[256];
            flag[sign] = 0;
            int[,] state = new int[8, 2] { { -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 0 } };//8个方向和起始扫描方向

            bool findpoint;//当前查找点
            bool findstartpoint = false;//查找起始点
            int startdirect = 0;//跟踪边界

            ArrayList height1 = new ArrayList();//动态数组
            ArrayList width1 = new ArrayList();

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);

            for (i = 0; i < box1.Width; i++)
            {
                for (j = 0; j < box1.Height; j++)
                {
                    cc = box1.GetPixel(i, j);
                    rr = cc.R;
                    if (rr == 0)
                    {
                        height1.Add("j");
                        width1.Add("i");
                        m = i;
                        n = j;
                        Color bla = Color.FromArgb(0, 0, 0);
                        box1.SetPixel(i, j, bla);
                    }
                }
            }

            cc3 = box1.GetPixel(m, n);
            rr3 = cc3.R;

            c0 = box1.GetPixel(m - 1, n - 1);
            c1 = box1.GetPixel(m, n - 1);
            c2 = box1.GetPixel(m + 1, n - 1);
            c3 = box1.GetPixel(m + 1, n);
            c4 = box1.GetPixel(m + 1, n + 1);
            c5 = box1.GetPixel(m, n + 1);
            c6 = box1.GetPixel(m - 1, n + 1);
            c7 = box1.GetPixel(m - 1, n);

            r0 = c0.R;
            r1 = c1.R;
            r2 = c2.R;
            r3 = c3.R;
            r4 = c4.R;
            r5 = c5.R;
            r6 = c6.R;
            r7 = c7.R;

            x = m;
            y = n;

            for (i = 0; i < box2.Width; i++)
            {
                for (j = 0; j < box2.Height; j++)
                {
                    c = box2.GetPixel(i, j);
                    r = c.R;
                    r = 255;
                    Color whi = Color.FromArgb(r, r, r);
                    box2.SetPixel(i, j, whi);
                }

            }

            while (!findstartpoint)
            {
                findpoint = false;
                while (!findpoint)
                {
                    lpc = box1.GetPixel(x + state[startdirect, 1], y + state[startdirect, 0]);//原像素
                    lpcr = lpc.R;

                    if (lpcr == 0)
                    {
                        findpoint = true;

                        x = x + state[startdirect, 1];
                        y = y + state[startdirect, 0];
                        if (x == m && y == n)
                        {
                            findstartpoint = true;
                        }

                        Color pic = Color.FromArgb(0, 0, 0);
                        box2.SetPixel(x, y, pic);

                        startdirect--;

                        if (startdirect == -1)
                        {
                            startdirect = 7;
                        }
                        startdirect--;
                        if (startdirect == -1)
                        {
                            startdirect = 7;
                        }
                    }
                    else
                    {
                        startdirect++;
                        if (startdirect == 8)
                        {
                            startdirect = 0;
                        }
                    }
                }

            }

            for (i = 0; i < box2.Width; i++)
            {
                for (j = 0; j < box2.Height; j++)
                {
                    c = box2.GetPixel(i, j);
                    r = c.R;
                    if (r == 0)
                    {
                        sign = r;
                        flag[sign] += 1;
                    }
                }
            }

            pictureBox2.Refresh();
            pictureBox2.Image = box2;
            Label lbl = new Label();
            string name = "图形的周长是：" + Convert.ToString(flag[sign]);
            lbl.Name = name;
            lbl.Text = name;
            lbl.AutoSize = true;
            Point drawPoint = new Point();
            drawPoint.X = 75;
            drawPoint.Y = 210;
            lbl.Location = drawPoint;
            pictureBox2.Controls.Add(lbl);
        }

        private void 水平投影ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int r;
            int blacknum;

            for (i = 0; i < box1.Width; i++)
            {
                for (j = 0; j < box1.Height; j++)
                {
                    c = box2.GetPixel(i, j);
                    r = c.R;
                    if (r > 128)
                    {
                        r = 255;
                    }
                    else
                    {
                        r = 0;
                    }
                }
            }
            for (i = 0; i < box2.Width; i++)
            {
                for (j = 0; j < box2.Height; j++)
                {
                    c = box2.GetPixel(i, j);
                    r = c.R;
                    r = 255;
                    Color whi = Color.FromArgb(r, r, r);
                    box2.SetPixel(i, j, whi);
                }

            }
            for (j = 0; j < box1.Height; j++)
            {
                blacknum = 0;
                for (i = 0; i < box1.Width; i++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    if (r == 0)
                    {
                        blacknum++;
                    }

                }
                for (i = 0; i < blacknum; i++)
                {
                    Color pic = Color.FromArgb(0, 0, 0);
                    box2.SetPixel(i, j, pic);
                }

            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 垂直投影ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;
            int r;
            int blacknum;
            for (i = 0; i < box1.Width; i++)
            {
                for (j = 0; j < box1.Height; j++)
                {
                    c = box2.GetPixel(i, j);
                    r = c.R;
                    if (r > 128)
                    {
                        r = 255;
                    }
                    else
                    {
                        r = 0;
                    }
                }
            }
            for (i = 0; i < box2.Width; i++)
            {
                for (j = 0; j < box2.Height; j++)
                {
                    c = box2.GetPixel(i, j);
                    r = c.R;
                    r = 255;
                    Color whi = Color.FromArgb(r, r, r);
                    box2.SetPixel(i, j, whi);
                }

            }
            for (i = 0; i < box1.Width; i++)
            {
                blacknum = 0;
                for (j = 0; j < box1.Height; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    if (r == 0)
                    {
                        blacknum++;
                    }

                }
                for (j = 0; j < blacknum; j++)
                {
                    Color pic = Color.FromArgb(0, 0, 0);
                    box2.SetPixel(i, j, pic);
                }

            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 邻域4收缩ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int rr;

            for (int i = 1; i < box1.Width - 1; i += 1)
            {
                for (int j = 1; j < box1.Height - 1; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    rr = c.R;
                    Color c1 = Color.FromArgb(rr, rr, rr);
                    box2.SetPixel(i, j, c1);
                    if (rr == 0)
                    {
                        rr = 255;
                        Color c2 = Color.FromArgb(rr, rr, rr);
                        box2.SetPixel(i, j, c1);
                        box2.SetPixel(i, j - 1, c2);
                        box2.SetPixel(i + 1, j, c2);
                        box2.SetPixel(i, j + 1, c2);
                        box2.SetPixel(i - 1, j, c2);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box1;
        }

        private void ShouSuo8_Click(object sender, EventArgs e)
        {

            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int rr;

            for (int i = 1; i < box1.Width - 1; i += 1)
            {
                for (int j = 1; j < box1.Height - 1; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    rr = c.R;
                    Color c1 = Color.FromArgb(rr, rr, rr);
                    box2.SetPixel(i, j, c1);
                    if (rr == 0)
                    {
                        rr = 255;
                        Color c2 = Color.FromArgb(rr, rr, rr);
                        box2.SetPixel(i - 1, j - 1, c2);
                        box2.SetPixel(i, j - 1, c2);
                        box2.SetPixel(i + 1, j - 1, c2);
                        box2.SetPixel(i + 1, j, c2);
                        box2.SetPixel(i, j + 1, c2);
                        box2.SetPixel(i + 1, j + 1, c2);
                        box2.SetPixel(i - 1, j, c2);
                        box2.SetPixel(i - 1, j + 1, c2);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 邻域8收缩ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int rr;

            for (int i = 1; i < box1.Width - 1; i += 1)
            {
                for (int j = 1; j < box1.Height - 1; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    rr = c.R;
                    Color c1 = Color.FromArgb(rr, rr, rr);
                    box2.SetPixel(i, j, c1);
                    if (rr == 0)
                    {
                        rr = 255;
                        Color c2 = Color.FromArgb(rr, rr, rr);
                        box2.SetPixel(i - 1, j - 1, c2);
                        box2.SetPixel(i, j - 1, c2);
                        box2.SetPixel(i + 1, j - 1, c2);
                        box2.SetPixel(i + 1, j, c2);
                        box2.SetPixel(i, j + 1, c2);
                        box2.SetPixel(i + 1, j + 1, c2);
                        box2.SetPixel(i - 1, j, c2);
                        box2.SetPixel(i - 1, j + 1, c2);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 邻域4膨胀ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int rr;

            for (int i = 1; i < box1.Width - 1; i += 1)
            {
                for (int j = 1; j < box1.Height - 1; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    rr = c.R;
                    Color c1 = Color.FromArgb(rr, rr, rr);
                    box2.SetPixel(i, j, c1);
                    if (rr == 0)
                    {
                        box2.SetPixel(i, j, c1);
                        box2.SetPixel(i, j - 1, c1);
                        box2.SetPixel(i + 1, j, c1);
                        box2.SetPixel(i, j + 1, c1);
                        box2.SetPixel(i - 1, j, c1);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 邻域8膨胀ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int rr;

            for (int i = 1; i < box1.Width - 1; i += 1)
            {
                for (int j = 1; j < box1.Height - 1; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    rr = c.R;
                    Color c1 = Color.FromArgb(rr, rr, rr);
                    box2.SetPixel(i, j, c1);
                    if (rr == 0)
                    {
                        box2.SetPixel(i - 1, j - 1, c1);
                        box2.SetPixel(i, j - 1, c1);
                        box2.SetPixel(i + 1, j - 1, c1);
                        box2.SetPixel(i + 1, j, c1);
                        box2.SetPixel(i, j + 1, c1);
                        box2.SetPixel(i + 1, j + 1, c1);
                        box2.SetPixel(i - 1, j, c1);
                        box2.SetPixel(i - 1, j + 1, c1);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 邻域4清除孤立点ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int cc, r1, r2, r3, r4;

            for (int i = 1; i < box1.Width - 2; i += 1)
            {
                for (int j = 1; j < box1.Height - 2; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    cc = c.R;
                    c = box1.GetPixel(i + 1, j);
                    r1 = c.R;
                    c = box1.GetPixel(i - 1, j);
                    r2 = c.R;
                    c = box1.GetPixel(i - 1, j + 1);
                    r3 = c.R;
                    c = box1.GetPixel(i - 1, j - 1);
                    r4 = c.R;
                    if ((r2 == 255) && (r3 == 255) && (r4 == 255) && (r1 == 255))
                    {
                        Color c1 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c1);
                    }
                    else
                    {
                        Color c2 = Color.FromArgb(cc, cc, cc);
                        box2.SetPixel(i, j, c2);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 邻域8清除孤立点ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Color c = new Color();
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int cc, r1, r2, r3, r4, r5, r6, r7, r8;

            for (int i = 1; i < box1.Width - 2; i += 1)
            {
                for (int j = 1; j < box1.Height - 2; j += 1)
                {
                    c = box1.GetPixel(i, j);
                    cc = c.R;
                    c = box1.GetPixel(i + 1, j);
                    r1 = c.R;
                    c = box1.GetPixel(i - 1, j);
                    r2 = c.R;
                    c = box1.GetPixel(i - 1, j + 1);
                    r3 = c.R;
                    c = box1.GetPixel(i - 1, j - 1);
                    r4 = c.R;
                    c = box1.GetPixel(i + 1, j - 1);
                    r5 = c.R;
                    c = box1.GetPixel(i + 1, j + 1);
                    r6 = c.R;
                    c = box1.GetPixel(i, j + 1);
                    r7 = c.R;
                    c = box1.GetPixel(i, j - 1);
                    r8 = c.R;
                    if ((r2 == 255) && (r3 == 255) && (r4 == 255) && (r5 == 255) && (r6 == 255) && (r7 == 255) && (r8 == 255) && (r1 == 255))
                    {
                        Color c1 = Color.FromArgb(255, 255, 255);
                        box2.SetPixel(i, j, c1);
                    }
                    else
                    {
                        Color c2 = Color.FromArgb(cc, cc, cc);
                        box2.SetPixel(i, j, c2);
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 水平腐蚀ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;//循环变量
            //使用水平方向的结构元素进行腐蚀
            // 由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边
            // 的两列像素
            for (j = 0; j < box1.Height; j++)
            {
                for (i = 1; i < box1.Width - 1; i++)
                {
                    //目标图像中的当前点先赋成黑色
                    box2.SetPixel(i, j, Color.Black);

                    //如果源图像中当前点自身或者左右有一个点不是黑色，
                    //则将目标图像中的当前点赋成白色
                    if (box1.GetPixel(i - 1, j).R > 128 ||
                        box1.GetPixel(i, j).R > 128 ||
                        box1.GetPixel(i + 1, j).R > 128)
                        box2.SetPixel(i, j, Color.White);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 垂直腐蚀ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;            //循环变量
            //使用垂真方向的结构元素进行腐蚀
            // 由于使用3×1的结构元素，为防止越界，所以不处理最上边和最下边
            // 的两行像素
            for (j = 1; j < box1.Height - 1; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    //目标图像中的当前点先赋成黑色
                    box2.SetPixel(i, j, Color.Black);

                    //如果源图像中当前点自身或者左右有一个点不是黑色，
                    //则将目标图像中的当前点赋成白色
                    if (box1.GetPixel(i, j - 1).R > 128 ||
                        box1.GetPixel(i, j).R > 128 ||
                        box1.GetPixel(i, j + 1).R > 128)
                        box2.SetPixel(i, j, Color.White);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 全方向腐蚀ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, n, m;//循环变量
            //使用自定义的结构元素进行腐蚀
            // 由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边
            // 的两列像素和最上边和最下边的两列像素
            for (j = 1; j < box1.Height - 1; j++)
            {
                for (i = 1; i < box1.Width - 1; i++)
                {
                    //目标图像中的当前点先赋成黑色
                    box2.SetPixel(i, j, Color.Black);
                    //如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
                    //则将目标图像中的当前点赋成白色
                    for (m = 0; m < 3; m++)
                    {
                        for (n = 0; n < 3; n++)
                        {
                            if (box1.GetPixel(i + m - 1, j + n - 1).R > 128)
                            {
                                box2.SetPixel(i, j, Color.White);
                                break;
                            }
                        }
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 水平膨胀ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;//循环变量
            //使用水平方向的结构元素进行腐蚀
            // 由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边
            // 的两列像素
            for (j = 0; j < box1.Height; j++)
            {
                for (i = 1; i < box1.Width - 1; i++)
                {
                    //目标图像中的当前点先赋成黑色
                    box2.SetPixel(i, j, Color.White);

                    //如果源图像中当前点自身或者左右有一个点不是黑色，
                    //则将目标图像中的当前点赋成白色
                    if (box1.GetPixel(i - 1, j).R < 128 ||
                        box1.GetPixel(i, j).R < 128 ||
                        box1.GetPixel(i + 1, j).R < 128)
                        box2.SetPixel(i, j, Color.Black);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 垂直膨胀ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j;            //循环变量
            //使用垂真方向的结构元素进行腐蚀
            // 由于使用3×1的结构元素，为防止越界，所以不处理最上边和最下边
            // 的两行像素
            for (j = 1; j < box1.Height - 1; j++)
            {
                for (i = 0; i < box1.Width; i++)
                {
                    //目标图像中的当前点先赋成黑色
                    box2.SetPixel(i, j, Color.White);

                    //如果源图像中当前点自身或者左右有一个点不是黑色，
                    //则将目标图像中的当前点赋成白色
                    if (box1.GetPixel(i, j - 1).R < 128 ||
                        box1.GetPixel(i, j).R < 128 ||
                        box1.GetPixel(i, j + 1).R < 128)
                        box2.SetPixel(i, j, Color.Black);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 全方向膨胀ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, n, m;//循环变量
            //使用自定义的结构元素进行腐蚀
            // 由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边
            // 的两列像素和最上边和最下边的两列像素
            for (j = 1; j < box1.Height - 1; j++)
            {
                for (i = 1; i < box1.Width - 1; i++)
                {
                    //目标图像中的当前点先赋成白色
                    box2.SetPixel(i, j, Color.White);
                    //如果原图像中对应结构元素中为白色的那些点中有一个不是白色，
                    //则将目标图像中的当前点赋成黑色
                    for (m = 0; m < 3; m++)
                    {
                        for (n = 0; n < 3; n++)
                        {
                            if (box1.GetPixel(i + m - 1, j + n - 1).R < 128)
                            {
                                box2.SetPixel(i, j, Color.Black);
                                break;
                            }
                        }
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 图像开运算ToolStripMenuItem_Click(object sender, EventArgs e)
        {

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, n, m;//循环变量
            //使用自定义的结构元素进行腐蚀
            // 由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边
            // 的两列像素和最上边和最下边的两列像素
            for (j = 1; j < box1.Height - 1; j++)
            {
                for (i = 1; i < box1.Width - 1; i++)
                {
                    //目标图像中的当前点先赋成黑色
                    box2.SetPixel(i, j, Color.Black);
                    //如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
                    //则将目标图像中的当前点赋成白色
                    for (m = 0; m < 3; m++)
                    {
                        for (n = 0; n < 3; n++)
                        {
                            if (box1.GetPixel(i + m - 1, j + n - 1).R > 128)
                            {
                                box2.SetPixel(i, j, Color.White);
                                break;
                            }
                        }
                    }
                }
            }

            Bitmap box3 = new Bitmap(box2.Width, box2.Height);
            //使用自定义的结构元素进行腐蚀
            // 由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边
            // 的两列像素和最上边和最下边的两列像素
            for (j = 1; j < box2.Height - 1; j++)
            {
                for (i = 1; i < box2.Width - 1; i++)
                {
                    //目标图像中的当前点先赋成黑色
                    box3.SetPixel(i, j, Color.White);
                    //如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
                    //则将目标图像中的当前点赋成白色
                    for (m = 0; m < 3; m++)
                    {
                        for (n = 0; n < 3; n++)
                        {
                            if (box2.GetPixel(i + m - 1, j + n - 1).R < 128)
                            {
                                box3.SetPixel(i, j, Color.Black);
                                break;
                            }
                        }
                    }
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box3;
        }

        private void 图像闭运算ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);

            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            int i, j, n, m;//循环变量
            //使用自定义的结构元素进行腐蚀
            // 由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边
            // 的两列像素和最上边和最下边的两列像素
            for (j = 1; j < box1.Height - 1; j++)
            {
                for (i = 1; i < box1.Width - 1; i++)
                {
                    //目标图像中的当前点先赋成黑色
                    box2.SetPixel(i, j, Color.White);
                    //如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
                    //则将目标图像中的当前点赋成白色
                    for (m = 0; m < 3; m++)
                    {
                        for (n = 0; n < 3; n++)
                        {
                            if (box1.GetPixel(i + m - 1, j + n - 1).R < 128)
                            {
                                box2.SetPixel(i, j, Color.Black);
                                break;
                            }
                        }
                    }
                }
            }

            Bitmap box3 = new Bitmap(box2.Width, box2.Height);
            //使用自定义的结构元素进行腐蚀
            // 由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边
            // 的两列像素和最上边和最下边的两列像素
            for (j = 1; j < box2.Height - 1; j++)
            {
                for (i = 1; i < box2.Width - 1; i++)
                {
                    //目标图像中的当前点先赋成黑色
                    box3.SetPixel(i, j, Color.Black);
                    //如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
                    //则将目标图像中的当前点赋成白色
                    for (m = 0; m < 3; m++)
                    {
                        for (n = 0; n < 3; n++)
                        {
                            if (box2.GetPixel(i + m - 1, j + n - 1).R > 128)
                            {
                                box3.SetPixel(i, j, Color.White);
                                break;
                            }
                        }
                    }
                }
            }
            pictureBox2.Refresh();
            //pictureBox2.Image = box3;
        }

        private void 图像细化ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);


            bool bModified;            //脏标记    
            int i, j, n, m;            //循环变量

            //四个条件
            bool bCondition1;
            bool bCondition2;
            bool bCondition3;
            bool bCondition4;

            int nCount;    //计数器    
            int[,] neighbour = new int[5, 5];    //5×5相邻区域像素值



            bModified = true;
            while (bModified)
            {
                bModified = false;

                //由于使用5×5的结构元素，为防止越界，所以不处理外围的几行和几列像素
                for (j = 2; j < box1.Height - 2; j++)
                {
                    for (i = 2; i < box1.Width - 2; i++)
                    {
                        bCondition1 = false;
                        bCondition2 = false;
                        bCondition3 = false;
                        bCondition4 = false;

                        if (box1.GetPixel(i, j).R > 127)
                        {
                            if (box1.GetPixel(i, j).R < 255)
                                box1.SetPixel(i, j, Color.White);
                            continue;
                        }

                        //获得当前点相邻的5×5区域内像素值，白色用0代表，黑色用1代表
                        for (m = 0; m < 5; m++)
                        {
                            for (n = 0; n < 5; n++)
                            {
                                neighbour[m, n] = box1.GetPixel(i + m - 2, j + n - 2).R < 127 ? 1 : 0;
                            }
                        }

                        //逐个判断条件。
                        //判断2<=NZ(P1)<=6
                        nCount = neighbour[1, 1] + neighbour[1, 2] + neighbour[1, 3]
                                + neighbour[2, 1] + neighbour[2, 3] +
                                +neighbour[3, 1] + neighbour[3, 2] + neighbour[3, 3];
                        if (nCount >= 2 && nCount <= 6)
                        {
                            bCondition1 = true;
                        }

                        //判断Z0(P1)=1
                        nCount = 0;
                        if (neighbour[1, 2] == 0 && neighbour[1, 1] == 1)
                            nCount++;
                        if (neighbour[1, 1] == 0 && neighbour[2, 1] == 1)
                            nCount++;
                        if (neighbour[2, 1] == 0 && neighbour[3, 1] == 1)
                            nCount++;
                        if (neighbour[3, 1] == 0 && neighbour[3, 2] == 1)
                            nCount++;
                        if (neighbour[3, 2] == 0 && neighbour[3, 3] == 1)
                            nCount++;
                        if (neighbour[3, 3] == 0 && neighbour[2, 3] == 1)
                            nCount++;
                        if (neighbour[2, 3] == 0 && neighbour[1, 3] == 1)
                            nCount++;
                        if (neighbour[1, 3] == 0 && neighbour[1, 2] == 1)
                            nCount++;
                        if (nCount == 1)
                            bCondition2 = true;

                        //判断P2*P4*P8=0 or Z0(p2)!=1
                        if (neighbour[1, 2] * neighbour[2, 1] * neighbour[2, 3] == 0)
                        {
                            bCondition3 = true;
                        }
                        else
                        {
                            nCount = 0;
                            if (neighbour[0, 2] == 0 && neighbour[0, 1] == 1)
                                nCount++;
                            if (neighbour[0, 1] == 0 && neighbour[1, 1] == 1)
                                nCount++;
                            if (neighbour[1, 1] == 0 && neighbour[2, 1] == 1)
                                nCount++;
                            if (neighbour[2, 1] == 0 && neighbour[2, 2] == 1)
                                nCount++;
                            if (neighbour[2, 2] == 0 && neighbour[2, 3] == 1)
                                nCount++;
                            if (neighbour[2, 3] == 0 && neighbour[1, 3] == 1)
                                nCount++;
                            if (neighbour[1, 3] == 0 && neighbour[0, 3] == 1)
                                nCount++;
                            if (neighbour[0, 3] == 0 && neighbour[0, 2] == 1)
                                nCount++;
                            if (nCount != 1)
                                bCondition3 = true;
                        }

                        //判断P2*P4*P6=0 or Z0(p4)!=1
                        if (neighbour[1, 2] * neighbour[2, 1] * neighbour[3, 2] == 0)
                        {
                            bCondition4 = true;
                        }
                        else
                        {
                            nCount = 0;
                            if (neighbour[1, 1] == 0 && neighbour[1, 0] == 1)
                                nCount++;
                            if (neighbour[1, 0] == 0 && neighbour[2, 0] == 1)
                                nCount++;
                            if (neighbour[2, 0] == 0 && neighbour[3, 0] == 1)
                                nCount++;
                            if (neighbour[3, 0] == 0 && neighbour[3, 1] == 1)
                                nCount++;
                            if (neighbour[3, 1] == 0 && neighbour[3, 2] == 1)
                                nCount++;
                            if (neighbour[3, 2] == 0 && neighbour[2, 2] == 1)
                                nCount++;
                            if (neighbour[2, 2] == 0 && neighbour[1, 2] == 1)
                                nCount++;
                            if (neighbour[1, 2] == 0 && neighbour[1, 1] == 1)
                                nCount++;
                            if (nCount != 1)
                                bCondition4 = true;
                        }

                        if (bCondition1 && bCondition2 && bCondition3 && bCondition4)
                        {
                            box1.SetPixel(i, j, Color.White);
                            bModified = true;
                        }
                        else
                        {
                            box1.SetPixel(i, j, Color.Black);
                        }
                    }
                }
            }
            // 复制细化后的图像
            pictureBox2.Refresh();
            pictureBox2.Image = box1;
        }

        private void 图像粗化ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);

            int i, j, n, m, temp;            //循环变量
            for (j = 0; j < box1.Height; j++)
                for (i = 0; i < box1.Width; i++)
                {
                    Color c = box1.GetPixel(i, j);
                    temp = (c.R + c.G + c.B) / 3;
                    if (temp > 127)
                        temp = 0;
                    else
                        temp = 255;
                    Color c1 = Color.FromArgb(temp, temp, temp);
                    box1.SetPixel(i, j, c1);
                }
            bool bModified;            //脏标记    

            //四个条件
            bool bCondition1;
            bool bCondition2;
            bool bCondition3;
            bool bCondition4;

            int nCount;    //计数器    
            int[,] neighbour = new int[5, 5];    //5×5相邻区域像素值



            bModified = true;
            while (bModified)
            {
                bModified = false;

                //由于使用5×5的结构元素，为防止越界，所以不处理外围的几行和几列像素
                for (j = 2; j < box1.Height - 2; j++)
                {
                    for (i = 2; i < box1.Width - 2; i++)
                    {
                        bCondition1 = false;
                        bCondition2 = false;
                        bCondition3 = false;
                        bCondition4 = false;

                        if (box1.GetPixel(i, j).R > 127)
                        {
                            if (box1.GetPixel(i, j).R < 255)
                                box1.SetPixel(i, j, Color.White);
                            continue;
                        }

                        //获得当前点相邻的5×5区域内像素值，白色用0代表，黑色用1代表
                        for (m = 0; m < 5; m++)
                        {
                            for (n = 0; n < 5; n++)
                            {
                                neighbour[m, n] = box1.GetPixel(i + m - 2, j + n - 2).R < 127 ? 1 : 0;
                            }
                        }

                        //逐个判断条件。
                        //判断2<=NZ(P1)<=6
                        nCount = neighbour[1, 1] + neighbour[1, 2] + neighbour[1, 3]
                                + neighbour[2, 1] + neighbour[2, 3] +
                                +neighbour[3, 1] + neighbour[3, 2] + neighbour[3, 3];
                        if (nCount >= 2 && nCount <= 6)
                        {
                            bCondition1 = true;
                        }

                        //判断Z0(P1)=1
                        nCount = 0;
                        if (neighbour[1, 2] == 0 && neighbour[1, 1] == 1)
                            nCount++;
                        if (neighbour[1, 1] == 0 && neighbour[2, 1] == 1)
                            nCount++;
                        if (neighbour[2, 1] == 0 && neighbour[3, 1] == 1)
                            nCount++;
                        if (neighbour[3, 1] == 0 && neighbour[3, 2] == 1)
                            nCount++;
                        if (neighbour[3, 2] == 0 && neighbour[3, 3] == 1)
                            nCount++;
                        if (neighbour[3, 3] == 0 && neighbour[2, 3] == 1)
                            nCount++;
                        if (neighbour[2, 3] == 0 && neighbour[1, 3] == 1)
                            nCount++;
                        if (neighbour[1, 3] == 0 && neighbour[1, 2] == 1)
                            nCount++;
                        if (nCount == 1)
                            bCondition2 = true;

                        //判断P2*P4*P8=0 or Z0(p2)!=1
                        if (neighbour[1, 2] * neighbour[2, 1] * neighbour[2, 3] == 0)
                        {
                            bCondition3 = true;
                        }
                        else
                        {
                            nCount = 0;
                            if (neighbour[0, 2] == 0 && neighbour[0, 1] == 1)
                                nCount++;
                            if (neighbour[0, 1] == 0 && neighbour[1, 1] == 1)
                                nCount++;
                            if (neighbour[1, 1] == 0 && neighbour[2, 1] == 1)
                                nCount++;
                            if (neighbour[2, 1] == 0 && neighbour[2, 2] == 1)
                                nCount++;
                            if (neighbour[2, 2] == 0 && neighbour[2, 3] == 1)
                                nCount++;
                            if (neighbour[2, 3] == 0 && neighbour[1, 3] == 1)
                                nCount++;
                            if (neighbour[1, 3] == 0 && neighbour[0, 3] == 1)
                                nCount++;
                            if (neighbour[0, 3] == 0 && neighbour[0, 2] == 1)
                                nCount++;
                            if (nCount != 1)
                                bCondition3 = true;
                        }

                        //判断P2*P4*P6=0 or Z0(p4)!=1
                        if (neighbour[1, 2] * neighbour[2, 1] * neighbour[3, 2] == 0)
                        {
                            bCondition4 = true;
                        }
                        else
                        {
                            nCount = 0;
                            if (neighbour[1, 1] == 0 && neighbour[1, 0] == 1)
                                nCount++;
                            if (neighbour[1, 0] == 0 && neighbour[2, 0] == 1)
                                nCount++;
                            if (neighbour[2, 0] == 0 && neighbour[3, 0] == 1)
                                nCount++;
                            if (neighbour[3, 0] == 0 && neighbour[3, 1] == 1)
                                nCount++;
                            if (neighbour[3, 1] == 0 && neighbour[3, 2] == 1)
                                nCount++;
                            if (neighbour[3, 2] == 0 && neighbour[2, 2] == 1)
                                nCount++;
                            if (neighbour[2, 2] == 0 && neighbour[1, 2] == 1)
                                nCount++;
                            if (neighbour[1, 2] == 0 && neighbour[1, 1] == 1)
                                nCount++;
                            if (nCount != 1)
                                bCondition4 = true;
                        }

                        if (bCondition1 && bCondition2 && bCondition3 && bCondition4)
                        {
                            box1.SetPixel(i, j, Color.White);
                            bModified = true;
                        }
                        else
                        {
                            box1.SetPixel(i, j, Color.Black);
                        }
                    }
                }
            }
            // 复制细化后的图像
            pictureBox2.Refresh();
            pictureBox2.Image = box1;
        }

        private void 中轴变换ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            //int lWidth = box1.Width;
            //int lHeight = box1.Height;
            //Bitmap newBmp = new Bitmap(lWidth, lHeight);

            bool bModified;            //脏标记    
            int i, j, n, m;            //循环变量

            //8个条件
            bool bCondition1;
            bool bCondition2;
            bool bCondition3;
            bool bCondition4;


            int nCount;    //计数器    
            int[,] neighbour = new int[5, 5];    //5×5相邻区域像素值



            bModified = true;
            while (bModified)
            {
                bModified = false;

                //由于使用5×5的结构元素，为防止越界，所以不处理外围的几行和几列像素
                for (j = 2; j < box1.Height - 2; j++)
                {
                    for (i = 2; i < box1.Width - 2; i++)
                    {
                        bCondition1 = false;
                        bCondition2 = false;
                        bCondition3 = false;
                        bCondition4 = false;

                        if (box1.GetPixel(i, j).R > 127)
                        {
                            if (box1.GetPixel(i, j).R < 255)
                                box1.SetPixel(i, j, Color.White);
                            continue;
                        }

                        //获得当前点相邻的5×5区域内像素值，白色用0代表，黑色用1代表
                        for (m = 0; m < 5; m++)
                        {
                            for (n = 0; n < 5; n++)
                            {
                                neighbour[m, n] = box1.GetPixel(i + m - 2, j + n - 2).R < 127 ? 1 : 0;
                            }
                        }
                        //判断1-1条件是否成立
                        nCount = neighbour[1, 1] + neighbour[1, 2] + neighbour[1, 3]
                                + neighbour[2, 1] + neighbour[2, 3] +
                                +neighbour[3, 1] + neighbour[3, 2] + neighbour[3, 3];
                        if (nCount >= 2 && nCount <= 6)
                        {
                            bCondition1 = true;
                        }
                        //判断1-2是否成立
                        nCount = 0;
                        if (neighbour[1, 2] == 0 && neighbour[1, 1] == 1)
                            nCount++;
                        if (neighbour[1, 1] == 0 && neighbour[2, 1] == 1)
                            nCount++;
                        if (neighbour[2, 1] == 0 && neighbour[3, 1] == 1)
                            nCount++;
                        if (neighbour[3, 1] == 0 && neighbour[3, 2] == 1)
                            nCount++;
                        if (neighbour[3, 2] == 0 && neighbour[3, 3] == 1)
                            nCount++;
                        if (neighbour[3, 3] == 0 && neighbour[2, 3] == 1)
                            nCount++;
                        if (neighbour[2, 3] == 0 && neighbour[1, 3] == 1)
                            nCount++;
                        if (neighbour[1, 3] == 0 && neighbour[1, 2] == 1)
                            nCount++;
                        if (nCount == 1)
                            bCondition2 = true;
                        //判断1-3是否成立
                        if (neighbour[1, 2] * neighbour[2, 1] * neighbour[3, 2] == 0)
                        {
                            bCondition3 = true;
                        }
                        //判断1-4是否成立
                        if (neighbour[2, 1] * neighbour[3, 2] * neighbour[2, 3] == 0)
                        {
                            bCondition4 = true;
                        }
                        if (bCondition1 && bCondition2 && bCondition3 && bCondition4)
                        {
                            box1.SetPixel(i, j, Color.White);
                            //bModified = true;
                        }

                    }
                }




                //由于使用5×5的结构元素，为防止越界，所以不处理外围的几行和几列像素
                for (j = 2; j < box1.Height - 2; j++)
                {
                    for (i = 2; i < box1.Width - 2; i++)
                    {
                        bCondition1 = false;
                        bCondition2 = false;
                        bCondition3 = false;
                        bCondition4 = false;

                        if (box1.GetPixel(i, j).R > 127)
                        {
                            if (box1.GetPixel(i, j).R < 255)
                                box1.SetPixel(i, j, Color.White);
                            continue;
                        }

                        //获得当前点相邻的5×5区域内像素值，白色用0代表，黑色用1代表
                        for (m = 0; m < 5; m++)
                        {
                            for (n = 0; n < 5; n++)
                            {
                                neighbour[m, n] = box1.GetPixel(i + m - 2, j + n - 2).R < 127 ? 1 : 0;
                            }
                        }
                        //判断2-1条件是否成立
                        nCount = neighbour[1, 1] + neighbour[1, 2] + neighbour[1, 3]
                                + neighbour[2, 1] + neighbour[2, 3] +
                                +neighbour[3, 1] + neighbour[3, 2] + neighbour[3, 3];
                        if (nCount >= 2 && nCount <= 6)
                        {
                            bCondition1 = true;
                        }
                        //判断2-2是否成立
                        nCount = 0;
                        if (neighbour[1, 2] == 0 && neighbour[1, 1] == 1)
                            nCount++;
                        if (neighbour[1, 1] == 0 && neighbour[2, 1] == 1)
                            nCount++;
                        if (neighbour[2, 1] == 0 && neighbour[3, 1] == 1)
                            nCount++;
                        if (neighbour[3, 1] == 0 && neighbour[3, 2] == 1)
                            nCount++;
                        if (neighbour[3, 2] == 0 && neighbour[3, 3] == 1)
                            nCount++;
                        if (neighbour[3, 3] == 0 && neighbour[2, 3] == 1)
                            nCount++;
                        if (neighbour[2, 3] == 0 && neighbour[1, 3] == 1)
                            nCount++;
                        if (neighbour[1, 3] == 0 && neighbour[1, 2] == 1)
                            nCount++;
                        if (nCount == 1)
                            bCondition2 = true;
                        //判断2-3是否成立
                        if (neighbour[1, 2] * neighbour[2, 1] * neighbour[2, 3] == 0)
                        {
                            bCondition3 = true;
                        }
                        //判断2-4是否成立
                        if (neighbour[1, 2] * neighbour[3, 2] * neighbour[2, 3] == 0)
                        {
                            bCondition4 = true;
                        }
                        if (bCondition1 && bCondition2 && bCondition3 && bCondition4)
                        {
                            box1.SetPixel(i, j, Color.White);
                            bModified = true;
                        }

                    }
                }
            }
            // 复制中轴变换后的图像
            pictureBox2.Refresh();
            pictureBox2.Image = box1;
        }

        private void toolBar1_ButtonClick(object sender, ToolBarButtonClickEventArgs e)
        {
            if (e.Button == toolBarButton1)
            {
                this.openFileDialog1.Filter = "bmp files (*.bmp)|*.bmp|All files (*.*)|*.*";
                //this.openFileDialog1.ShowDialog(); //这句调用打开文件对话框
                if (this.openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    file = this.openFileDialog1.FileName;
                    Bitmap bm = new Bitmap(file);
                    //MessageBox.Show(file);
                    this.pictureBox1.Image = bm;
                }
            }
            if (e.Button == toolBarButton2)
            {
                this.saveFileDialog1.Filter = "bmp files (*.bmp)|*.bmp|All files (*.*)|*.*";
                this.saveFileDialog1.ShowDialog();
                this.pictureBox2.Image.Save(this.saveFileDialog1.FileName);
                //string str;
                //Bitmap box2 = new Bitmap(pictureBox2.Image);
                //Graphics g = this.CreateGraphics();
                //saveFileDialog1.Filter = "bmp文件(*.BMP)|*.BMP|ALL File(*.*)|*.*";
                //saveFileDialog1.ShowDialog();
                //str = saveFileDialog1.FileName;
                //pictureBox2.Image.Save(str);
            }
        }

        private void 图像的扫描ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            
            Graphics gb = pictureBox2.CreateGraphics();
            
            switch (XianShi)
            {

                case 1://向下扫描
                    for (float x = 0; x < box1.Height; x+=0.1f)
                    {
                        PointF ul = new PointF(0, 0);
                        PointF ur = new PointF(box1.Width, 0);
                        PointF dl = new PointF(0, x);
                        PointF[] destPara = { ul, ur, dl };
                        RectangleF srcRect = new RectangleF(0, 0, box1.Width, x);
                        GraphicsUnit units = GraphicsUnit.Pixel;
                        gb.DrawImage(box1, destPara, srcRect, units);
                        
                        //gb.DrawImageUnscaledAndClipped(box1, new Rectangle(0, 0, box1.Width, x1));
                    }
                    break;

                case 2://向上扫描
                    
                    for (float x = box1.Height-0.1f; x >0; x-=0.1f)
                    {
                        PointF ul = new PointF(0, x);
                        PointF ur = new PointF(box1.Width, x);
                        PointF dl = new PointF(0, box1.Height);
                        PointF[] destPara = { ul, ur, dl };
                        RectangleF srcRect = new RectangleF(0, x, box1.Width, box1.Height-x);
                        GraphicsUnit units = GraphicsUnit.Pixel;
                        gb.DrawImage(box1, destPara, srcRect, units);
                        //gb.DrawImageUnscaledAndClipped(box1, new Rectangle(0,0, box1.Width, 10));
                    }
                    break;

                case 3://向右扫描
                    
                    for (float x = 0; x < box1.Width; x+=0.1f)
                    {
                        PointF ul = new PointF(0,0);
                        PointF ur = new PointF(x,0);
                        PointF dl = new PointF(0 , box1.Height);
                        PointF[] destPara = { ul,ur,dl };
                        RectangleF srcRect = new RectangleF(0, 0, x, box1.Height);
                        GraphicsUnit units = GraphicsUnit.Pixel;
                        gb.DrawImage(box1, destPara, srcRect, units);

                        //gb.DrawImage(box1, destPara);
                        //gb.DrawImageUnscaledAndClipped(box1, new Rectangle(0, 0, x3, box1.Height));
                    }
                    break;

                case 4://向左扫描

                    for (float x = box1.Width; x >0; x -= 0.1f)
                    {
                        PointF ul = new PointF(x, 0);
                        PointF ur = new PointF(box1.Width, 0);
                        PointF dl = new PointF(x, box1.Height);
                        PointF[] destPara = { ul, ur, dl };
                        RectangleF srcRect = new RectangleF(x, 0, box1.Width-x, box1.Height);
                        GraphicsUnit units = GraphicsUnit.Pixel;
                        gb.DrawImage(box1, destPara, srcRect, units);

                        //gb.DrawImage(box1, destPara);
                        //gb.DrawImageUnscaledAndClipped(box1, new Rectangle(0, 0, x3, box1.Height));
                    }
                    break;

                case 5://水平右移
                    for (float x = -box1.Width; x <= 0; x += 0.3f)
                    {
                        gb.DrawImage(box1, x, 0.0f);
                
                    }
                    break;

                case 6://水平下移
                    for (float x = -box1.Height; x <= 0; x += 0.3f)
                    {
                        gb.DrawImage(box1, 0.0f, x);

                    }
                    break;

                case 7://交叉飞入
                    float middle = box1.Height / 2;
                    for (float x = 0; x <= box1.Width; x += 0.3f)
                    {
                        RectangleF srcRect1 = new RectangleF(0, 0, box1.Width, middle);
                        GraphicsUnit units1 = GraphicsUnit.Pixel;
                        gb.DrawImage(box1, x - box1.Width, 0.0f, srcRect1, units1);

                        RectangleF srcRect2 = new RectangleF(0, middle, box1.Width, middle);
                        GraphicsUnit units2 = GraphicsUnit.Pixel;
                        gb.DrawImage(box1, box1.Width - x, middle, srcRect2, units2);

                        
                    }
                    break;

                case 8://中间扩张
                    float middle1 = box1.Height / 2;
                    
                    for (float x = 0; x < middle1; x += 0.1f)
                    {
                        PointF ul = new PointF(0, middle1-x);
                        PointF ur = new PointF(box1.Width, middle1-x);
                        PointF dl = new PointF(0, middle1+x);
                        PointF[] destPara = { ul, ur, dl };
                        RectangleF srcRect = new RectangleF(0, middle1-x, box1.Width, x*2);
                        GraphicsUnit units = GraphicsUnit.Pixel;
                        gb.DrawImage(box1, destPara, srcRect, units);

                        //gb.DrawImageUnscaledAndClipped(box1, new Rectangle(0, 0, box1.Width, x1));
                    }
                    break;

                case 9://中间收缩
                    float middle2 = box1.Height / 2;

                    for (float x = 0; x < middle2; x += 0.1f)
                    {
                        PointF ul1 = new PointF(0, 0);
                        PointF ur1 = new PointF(box1.Width, 0);
                        PointF dl1 = new PointF(0, x);
                        PointF[] destPara1 = { ul1, ur1, dl1 };
                        RectangleF srcRect1 = new RectangleF(0, 0, box1.Width, x);
                        GraphicsUnit units1 = GraphicsUnit.Pixel;
                        gb.DrawImage(box1, destPara1, srcRect1, units1);

                        PointF ul2 = new PointF(0, box1.Height-x);
                        PointF ur2 = new PointF(box1.Width, box1.Height - x);
                        PointF dl2 = new PointF(0, box1.Height);
                        PointF[] destPara2 = { ul2, ur2, dl2 };
                        RectangleF srcRect2 = new RectangleF(0, box1.Height-x, box1.Width, x);
                        GraphicsUnit units2 = GraphicsUnit.Pixel;
                        gb.DrawImage(box1, destPara2, srcRect2, units2);

                    }
                    break;

                case 10://百叶窗自左向右
                    float distance = box1.Width/20;
                    for (float x = 0; x < distance; x += 0.1f)
                    {
                        for (int i = 0; i <= 21; i++)
                        {
                            PointF ul = new PointF(i*distance, 0);
                            PointF ur = new PointF(i*distance+x, 0);
                            PointF dl = new PointF(i * distance, box1.Height);
                            PointF[] destPara = { ul, ur, dl };
                            RectangleF srcRect = new RectangleF(i * distance, 0, x, box1.Height);
                            GraphicsUnit units = GraphicsUnit.Pixel;
                            gb.DrawImage(box1, destPara, srcRect, units);
                        }
                        
                    }
                    break;

                case 11://百叶窗自左向右
                    distance = box1.Height / 20;
                    for (float x = 0; x < distance; x += 0.1f)
                    {
                        for (int i = 0; i <= 21; i++)
                        {
                            PointF ul = new PointF(0, i * distance);
                            PointF ur = new PointF(box1.Width, i * distance );
                            PointF dl = new PointF(0, i * distance + x);
                            PointF[] destPara = { ul, ur, dl };
                            RectangleF srcRect = new RectangleF(0, i * distance,box1.Width , x);
                            GraphicsUnit units = GraphicsUnit.Pixel;
                            gb.DrawImage(box1, destPara, srcRect, units);
                        }

                    }
                    break;

                case 12://水平栅条

                    distance = box1.Height / 20;
                    for (float x = 0; x <= box1.Width; x += 0.8f)
                    {
                        for (int i = 0; i <= 21; i+=2)
                        {
                            RectangleF srcRect1 = new RectangleF(0, i*distance, box1.Width, distance);
                            GraphicsUnit units1 = GraphicsUnit.Pixel;
                            gb.DrawImage(box1, x - box1.Width, i*distance, srcRect1, units1);

                            RectangleF srcRect2 = new RectangleF(0, (i+1) * distance, box1.Width, distance);
                            GraphicsUnit units2 = GraphicsUnit.Pixel;
                            gb.DrawImage(box1,  box1.Width-x, (i+1) * distance, srcRect2, units2);
                        }
                    }
                    break;

                case 13://垂直栅条

                    distance = box1.Width / 20;
                    for (float x = 0; x <= box1.Height; x += 0.8f)
                    {
                        for (int i = 0; i <= 21; i += 2)
                        {
                            RectangleF srcRect1 = new RectangleF(i * distance,0 ,distance , box1.Height);
                            GraphicsUnit units1 = GraphicsUnit.Pixel;
                            gb.DrawImage(box1, i * distance, x - box1.Height, srcRect1, units1);

                            RectangleF srcRect2 = new RectangleF((i + 1) * distance, 0,distance ,box1.Height );
                            GraphicsUnit units2 = GraphicsUnit.Pixel;
                            gb.DrawImage(box1,(i + 1) * distance , box1.Height - x, srcRect2, units2);
                        }
                    }
                    break;

                case 14://图像渐显
                    Color c = new Color();
                    int r, g, b;
                    for (int x = 0; x <=256; x+=16)
                    {
                        for (int i = 0; i < box1.Width - 1; i++)
                        {
                            for (int j = 0; j < box1.Height - 1; j++)
                            {
                                c = box1.GetPixel(i, j);
                                r = c.R * x / 256;
                                g = c.G * x / 256;
                                b = c.B * x / 256;

                                Color c1 = Color.FromArgb(r, g, b);
                                box2.SetPixel(i, j, c1);
                                
                            }
                        }
                        gb.DrawImage(box2, 0.0f, 0.0f);
                    }
                    break;

               /* case 15://马赛克效果

                    distance = box1.Width / 10;
                    Random rnd = new Random();
                    for(int i=0;i<81;i++){
                    int myrnd = rnd.Next(81);
                    //MessageBox.Show("随技数为：" + myrnd);
                    for (float x = 0; x <= distance; x += 0.2f)
                    {
                        

                        RectangleF srcRect1 = new RectangleF(myrnd * distance, myrnd * distance, distance, distance);
                        GraphicsUnit units1 = GraphicsUnit.Pixel;
                        gb.DrawImage(box1, myrnd * distance, myrnd * distance, srcRect1, units1);
                        

                    } 
                    }
                    break;*/

            }
            timer1.Enabled = false; 
            pictureBox2.Refresh();
            pictureBox2.Image = box1;
            
        }

        private void 向右扫描ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //System.Timers.Timer t = new System.Timers.Timer(10000);
            //t.Elapsed += new System.Timers.ElapsedEventHandler(timer1_Tick);
            //t.AutoReset = true;
            //t.Enabled = true;
            XianShi = 3;
            timer1 = new Timer();
            timer1.Interval = 100;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);
            

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    Color c1 = Color.FromArgb(255, 255, 255);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 水平右移ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XianShi = 5;
            timer1 = new Timer();
            timer1.Interval = 100;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);
        }

        private void 水平上移ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XianShi = 6;
            timer1 = new Timer();
            timer1.Interval = 100;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);
        }

        private void 向下扫描toolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            XianShi = 1;
            timer1 = new Timer();
            timer1.Interval = 100;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    Color c1 = Color.FromArgb(255, 255, 255);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 向上扫描toolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    Color c1 = Color.FromArgb(255, 255, 255);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
            XianShi = 2;
            timer1 = new Timer();
            timer1.Interval = 50;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);
        }

        private void 向左扫描ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XianShi = 4;
            timer1 = new Timer();
            timer1.Interval = 100;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    Color c1 = Color.FromArgb(255, 255, 255);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 中间扩张ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XianShi = 8;
            timer1 = new Timer();
            timer1.Interval = 100;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    Color c1 = Color.FromArgb(255, 255, 255);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 中间收缩ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XianShi = 9;
            timer1 = new Timer();
            timer1.Interval = 100;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    Color c1 = Color.FromArgb(255, 255, 255);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 交叉飞入ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XianShi = 7;
            timer1 = new Timer();
            timer1.Interval = 100;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);
        }

        private void 自左向右ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XianShi = 10;
            timer1 = new Timer();
            timer1.Interval = 100;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    Color c1 = Color.FromArgb(255, 255, 255);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 自上而下ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XianShi = 11;
            timer1 = new Timer();
            timer1.Interval = 100;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    Color c1 = Color.FromArgb(255, 255, 255);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 水平栅条ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XianShi = 12;
            timer1 = new Timer();
            timer1.Interval = 100;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);
        }

        private void 垂直栅条ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XianShi = 13;
            timer1 = new Timer();
            timer1.Interval = 100;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);
        }

        private void 图像渐显ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XianShi = 14;
            timer1 = new Timer();
            timer1.Interval = 1;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);
        }

       /* private void 马赛克效果ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            XianShi = 15;
            timer1 = new Timer();
            timer1.Interval = 100;
            timer1.Enabled = true;
            timer1.Tick += new EventHandler(timer1_Tick);
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            for (int i = 0; i < box1.Width; i++)
            {
                for (int j = 0; j < box1.Height; j++)
                {
                    Color c1 = Color.FromArgb(255, 255, 255);
                    box2.SetPixel(i, j, c1);
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
            MessageBox.Show("目前未能实现");

        }*/

       
        private void 图像的加运算ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BeiJingTu frm = new BeiJingTu();//图像平移
            frm.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm.StartPosition = FormStartPosition.CenterParent;
            frm.ShowDialog(this);

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            Color c = new Color();
            int[, ,] pic = new int[600, 600, 3];
            int r, g, b;
            int rr, gg, bb;
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    pic[i, j, 0] = frm.BeiJingTu_n[i, j, 0];
                    pic[i, j, 1] = frm.BeiJingTu_n[i, j, 1];
                    pic[i, j, 2] = frm.BeiJingTu_n[i, j, 2];
                }
            }

            if (frm.p == 1)//ｃｏｎｃｅｌｌ功能判断
            {
                return;

            }
            //MessageBox.Show("成功调用" + pic[1, 1, 1]);

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    g = c.G;
                    b = c.B;
                    rr = pic[i, j, 0] + r;
                    gg = pic[i, j, 1] + g;
                    bb = pic[i, j, 2] + b;
                    if (rr > 255)
                        rr = 255;
                    if (gg > 255)
                        gg = 255;
                    if (bb > 255)
                        bb = 255;
                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j , c1);
                }

            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 图像的减运算ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BeiJingTu frm = new BeiJingTu();//图像平移
            frm.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm.StartPosition = FormStartPosition.CenterParent;
            frm.ShowDialog(this);

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            Color c = new Color();
            int[, ,] pic = new int[600, 600, 3];
            int r, g, b;
            int rr, gg, bb;
            if (frm.p == 1)//ｃｏｎｃｅｌｌ功能判断
                return;

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    pic[i, j, 0] = frm.BeiJingTu_n[i, j, 0];
                    pic[i, j, 1] = frm.BeiJingTu_n[i, j, 1];
                    pic[i, j, 2] = frm.BeiJingTu_n[i, j, 2];
                }
            }
            

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    r = c.R;
                    g = c.G;
                    b = c.B;
                    rr = r - pic[i, j, 0];
                    gg = g - pic[i, j, 1];
                    bb = b - pic[i, j, 2];
                    if (rr < 0)
                        rr = 0;
                    if (gg < 0)
                        gg = 0;
                    if (bb < 0)
                        bb = 0;
                    Color c1 = Color.FromArgb(rr, gg, bb);
                    box2.SetPixel(i, j, c1);
                }

            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 与运算ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BeiJingTu frm = new BeiJingTu();
            frm.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm.StartPosition = FormStartPosition.CenterParent;
            frm.ShowDialog(this);

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            Color c = new Color();
            int[, ,] pic = new int[600, 600, 3];
            int r=0, g=0, b=0;
            
            if (frm.p == 1)//ｃｏｎｃｅｌｌ功能判断
                return;

            
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    if (frm.BeiJingTu_n[i, j, 0] > 128 & c.R > 128)
                        r = 255;
                    else
                        r = 0;
                    if (frm.BeiJingTu_n[i, j, 1] > 128 & c.G > 128)
                        g = 255;
                    else
                        g = 0;
                    if (frm.BeiJingTu_n[i, j, 2] > 128 & c.B > 128)
                        b = 255;
                    else
                        b = 0;
                    Color c1 = Color.FromArgb(r, g, b);
                    box2.SetPixel(i, j, c1);
                }
            }
            
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 或运算ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BeiJingTu frm = new BeiJingTu();
            frm.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm.StartPosition = FormStartPosition.CenterParent;
            frm.ShowDialog(this);

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            Color c = new Color();
            int[, ,] pic = new int[600, 600, 3];
            int r = 0, g = 0, b = 0;
            
            if (frm.p == 1)//ｃｏｎｃｅｌｌ功能判断
                return;
            
            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    if (frm.BeiJingTu_n[i, j, 0] > 128 | c.R > 128)
                        r = 0;
                    else
                        r = 255;
                    if (frm.BeiJingTu_n[i, j, 1] > 128 | c.B > 128)
                        b = 0;
                    else
                        b = 255;
                    if (frm.BeiJingTu_n[i, j, 2] > 128 | c.G > 128)
                        g = 0;
                    else
                        g = 255;
                    Color c1 = Color.FromArgb(r, g, b);
                    box2.SetPixel(i, j, c1);
                  
                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 非运算ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            Color c = new Color();
            int r = 0, g = 0, b = 0;
            


            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    
                    c = box1.GetPixel(i, j);
                    if (c.R > 128)
                        r = 0;
                    else
                        r = 255;
                    if (c.G > 128)
                        g = 0;
                    else
                        g = 255;
                    if (c.B > 128)
                        b = 0;
                    else
                        b = 255;
                    Color c1 = Color.FromArgb(r, g, b);
                    box2.SetPixel(i, j, c1);
                }

            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 或非运算ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BeiJingTu frm = new BeiJingTu();
            frm.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm.StartPosition = FormStartPosition.CenterParent;
            frm.ShowDialog(this);

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            Color c = new Color();
            int[, ,] pic = new int[600, 600, 3];
            int r = 0, g = 0, b = 0;

            if (frm.p == 1)//ｃｏｎｃｅｌｌ功能判断
                return;

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    if (frm.BeiJingTu_n[i, j, 0] < 128 & c.R < 128)
                        r = 0;
                    else
                        r = 255;
                    if (frm.BeiJingTu_n[i, j, 1] < 128 & c.B < 128)
                        b = 0;
                    else
                        b = 255;
                    if (frm.BeiJingTu_n[i, j, 2] < 128 & c.G < 128)
                        g = 0;
                    else
                        g = 255;
                    Color c1 = Color.FromArgb(r, g, b);
                    box2.SetPixel(i, j, c1);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 与非运算ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BeiJingTu frm = new BeiJingTu();
            frm.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm.StartPosition = FormStartPosition.CenterParent;
            frm.ShowDialog(this);

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            Color c = new Color();
            int[, ,] pic = new int[600, 600, 3];
            int r = 0, g = 0, b = 0;

            if (frm.p == 1)//ｃｏｎｃｅｌｌ功能判断
                return;

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    if (frm.BeiJingTu_n[i, j, 0] < 128 | c.R < 128)
                        r = 0;
                    else
                        r = 255;
                    if (frm.BeiJingTu_n[i, j, 1] < 128 | c.B < 128)
                        b = 0;
                    else
                        b = 255;
                    if (frm.BeiJingTu_n[i, j, 2] < 128 | c.G < 128)
                        g = 0;
                    else
                        g = 255;
                    Color c1 = Color.FromArgb(r, g, b);
                    box2.SetPixel(i, j, c1);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void 异或运算ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BeiJingTu frm = new BeiJingTu();
            frm.FormBorderStyle = FormBorderStyle.FixedDialog;
            frm.StartPosition = FormStartPosition.CenterParent;
            frm.ShowDialog(this);

            Bitmap box1 = new Bitmap(pictureBox1.Image);
            Bitmap box2 = new Bitmap(box1.Width, box1.Height);
            Color c = new Color();
            int[, ,] pic = new int[600, 600, 3];
            int r = 0, g = 0, b = 0;

            if (frm.p == 1)//ｃｏｎｃｅｌｌ功能判断
                return;

            for (int i = 0; i < box1.Width - 1; i++)
            {
                for (int j = 0; j < box1.Height - 1; j++)
                {
                    c = box1.GetPixel(i, j);
                    if (frm.BeiJingTu_n[i, j, 0] > 128 & c.R > 128)
                        r = 0;
                    else if (frm.BeiJingTu_n[i, j, 0] <= 128 & c.R <= 128)
                        r = 0;
                    else
                        r = 255;
                    if (frm.BeiJingTu_n[i, j, 1] > 128 & c.G > 128)
                        g = 0;
                    else if (frm.BeiJingTu_n[i, j, 1] <= 128 & c.G <= 128)
                        g = 0;
                    else
                        g = 255;
                    if (frm.BeiJingTu_n[i, j, 2] > 128 & c.B > 128)
                        b = 0;
                    else if (frm.BeiJingTu_n[i, j, 2] <= 128 & c.B <= 128)
                        b = 0;
                    else
                        b = 255;
                    Color c1 = Color.FromArgb(r, g, b);
                    box2.SetPixel(i, j, c1);

                }
            }
            pictureBox2.Refresh();
            pictureBox2.Image = box2;
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }

       
            
       

        
    }
}