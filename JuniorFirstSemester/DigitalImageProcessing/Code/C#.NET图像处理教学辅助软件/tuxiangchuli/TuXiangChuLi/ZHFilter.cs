using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ConvertBmpToGray
{
    public partial class ZHFilter : Form
    {
        public bool flag1 = false;
        public int weightX;
        public int weightY;
        public int weightN;
        private Button btnOK;
        private Button btnCANCEL;
        private Label lblweight1;
        private Label lblweight2;
        private Label lblweightX;
        private Label lblweightY;
        private Label lblweightN;
        private TextBox txtweightX;
        private TextBox txtweightY;
        private TextBox txtweightN;
        public ZHFilter()
        {
            InitializeComponent();
            this.Text = "指数高通滤波";
            this.StartPosition = FormStartPosition.CenterScreen;
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.Width = 300;
            this.Height = 250;
            lblweight1 = new Label();
            lblweight2 = new Label();
            lblweightX = new Label();
            lblweightY = new Label();
            lblweightN = new Label();
            txtweightX = new TextBox();
            txtweightY = new TextBox();
            txtweightN = new TextBox();
            btnOK = new Button();
            btnCANCEL = new Button();

            //Label
            lblweight1.Location = new Point(30, 30);
            lblweight1.AutoSize = true;
            lblweight1.Text = "请确定指数高通滤波截止频率D0的分量";

            lblweight2.Location = new Point(30, 80);
            lblweight2.AutoSize = true;
            lblweight2.Text = "请确定计算传递函数的阶数";

            lblweightX.Location = new Point(30, 50);
            lblweightX.AutoSize = true;
            lblweightX.Text = "X:";

            lblweightY.Location = new Point(150, 50);
            lblweightY.AutoSize = true;
            lblweightY.Text = "Y:";

            lblweightN.Location = new Point(30, 100);
            lblweightN.AutoSize = true;
            lblweightN.Text = "N:";

            //TextBox
            txtweightX.Width = 80;
            txtweightX.Location = new Point(45, 50);

            txtweightY.Width = 80;
            txtweightY.Location = new Point(165, 50);

            txtweightN.Width = 80;
            txtweightN.Location = new Point(45, 100);
            //Button
            btnOK.Text = "OK";
            btnOK.Location = new Point(((this.Width - (btnOK.Width * 2)) / 3), (this.Height - 100));
            btnCANCEL.Text = "CANCEL";
            btnCANCEL.Location = new Point(((this.Width / 2) + ((this.Width - (btnOK.Width * 2)) / 6)), (this.Height - 100));

            //Add button to form
            this.Controls.Add(btnOK);
            this.Controls.Add(btnCANCEL);
            this.Controls.Add(lblweight1);
            this.Controls.Add(lblweight2);
            this.Controls.Add(lblweightX);
            this.Controls.Add(lblweightY);
            this.Controls.Add(lblweightN);
            this.Controls.Add(txtweightX);
            this.Controls.Add(txtweightY);
            this.Controls.Add(txtweightN);

            //Event handlers
            btnOK.Click += new System.EventHandler(this.btnOK_Click);
            btnCANCEL.Click += new System.EventHandler(this.btnCANCEL_Click);
        }

        private void ZHFilter_Load(object sender, EventArgs e)
        {

        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            weightX = Convert.ToInt32(txtweightX.Text);
            weightY = Convert.ToInt32(txtweightY.Text);
            weightN = Convert.ToInt32(txtweightN.Text);
            this.Close();//关闭对话框
        }

        private void btnCANCEL_Click(object sender, EventArgs e)
        {
            flag1 = true;
            this.Close();//关闭对话框
        }
    }
}