using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ConvertBmpToGray
{
    public partial class subForm2 : Form
    {
        public bool flag1 = false;
        public int subForm2_n;
        private Button btnOK;
        private Button btnCANCEL;
        private Label lblFullTime;
        private TextBox txtFullTime;
        public subForm2()
        {
            InitializeComponent();
            this.Text = "高通滤波";
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

        private void subForm2_Load(object sender, EventArgs e)
        {
            //subForm2_n = Convert.ToInt32(textBox_highfilter.Text);
            //this.Close();//关闭对话框
        }

        //private void textBox_highfilter_TextChanged(object sender, EventArgs e)
        //{
        //    subForm2_n = Convert.ToInt32(textBox_highfilter.Text);
        //}

        private void btnOK_Click(object sender, EventArgs e)
        {
            subForm2_n = Convert.ToInt32(txtFullTime.Text);
            this.Close();//关闭对话框
        }

        private void btnCANCEL_Click(object sender, EventArgs e)
        {
            flag1 = true;
            this.Close();//关闭对话框
        }
    }
}