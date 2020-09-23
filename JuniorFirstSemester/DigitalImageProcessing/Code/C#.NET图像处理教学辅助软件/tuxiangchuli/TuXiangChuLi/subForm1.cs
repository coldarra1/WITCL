using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ConvertBmpToGray
{
    public partial class subForm1 : Form
    {
        public bool flag1 = false;
        public int subForm1_n;
        private Button btnOK;//不在Design中设计各个控件,而在这里用代码设计,这样可以使数值,关闭等正常传值运行.
        private Button btnCANCEL;
        private Label lblFullTime;
        private TextBox txtFullTime;
        public subForm1()
        {
            InitializeComponent();
            this.Text = "低通滤波";
            this.StartPosition = FormStartPosition.CenterScreen;
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.Width = 300;
            this.Height = 250;
            lblFullTime = new Label();
            txtFullTime = new TextBox();
            btnOK = new Button();
            btnCANCEL = new Button();

            //Label
            lblFullTime.Location = new Point(30, 30);
            lblFullTime.AutoSize = true;
            lblFullTime.Text = "请输入小波变换的次数:";

            //TextBox
            txtFullTime.Width = 100;
            txtFullTime.Location = new Point(90, 75);

            //Button
            btnOK.Text = "OK";
            btnOK.Location = new Point(((this.Width - (btnOK.Width * 2)) / 3), (this.Height - 100));
            btnCANCEL.Text = "CANCEL";
            btnCANCEL.Location = new Point(((this.Width / 2) + ((this.Width - (btnOK.Width * 2)) / 6)), (this.Height - 100));

            //Add button to form
            this.Controls.Add(btnOK);
            this.Controls.Add(btnCANCEL);
            this.Controls.Add(lblFullTime);
            this.Controls.Add(txtFullTime);

            //Event handlers
            btnOK.Click += new System.EventHandler(this.btnOK_Click);
            btnCANCEL.Click += new System.EventHandler(this.btnCANCEL_Click);
        }

        private void subForm1_Load(object sender, EventArgs e)
        {

        }

        //--------------------------------------------------------------------------
        //一般文本框内数据传值button1_Click()进行,textBox_lowfilter_TextChanged()用于记录当文本框内值的改变
        //private void textBox_lowfilter_TextChanged(object sender, EventArgs e)
        //{
        //    subForm1_n = Convert.ToInt32(textBox_lowfilter.Text);
        //}

        private void btnOK_Click(object sender, EventArgs e)
        {
            //Form1 mainform = new Form1();
            //mainform.menuItem19_Click(subForm1_n);//此时 menuItem19_Click()必须是共有函数          
            subForm1_n = Convert.ToInt32(txtFullTime.Text);//将文本框内数据转换为32位整数,并传值给subForm1_n
            this.Close();//关闭对话框
        }

        private void btnCANCEL_Click(object sender, EventArgs e)
        {
            flag1 = true;
            this.Close();//关闭对话框            
        }
    }
}