using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ConvertBmpToGray
{
    public partial class PerfectFilterL : Form
    {
        public bool flag1 = false;
        public int weightX;
        public int weightY;
        private Button btnOK;
        private Button btnCANCEL;
        private Label lblweight;
        private Label lblweightX;
        private Label lblweightY;
        private TextBox txtweightX;
        private TextBox txtweightY;
        public PerfectFilterL()
        {
            InitializeComponent();
            this.Text = "理想底通滤波";
            this.StartPosition = FormStartPosition.CenterScreen;
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.Width = 300;
            this.Height = 250;
            lblweight = new Label();
            lblweightX = new Label();
            lblweightY = new Label();
            txtweightX = new TextBox();
            txtweightY = new TextBox();
            btnOK = new Button();
            btnCANCEL = new Button();

            //Label
            lblweight.Location = new Point(30, 30);
            lblweight.AutoSize = true;
            lblweight.Text = "请确定理想底通滤波截止频率D0的分量";

            lblweightX.Location = new Point(30, 75);
            lblweightX.AutoSize = true;
            lblweightX.Text = "X:";

            lblweightY.Location = new Point(150, 75);
            lblweightY.AutoSize = true;
            lblweightY.Text = "Y:";

            //TextBox
            txtweightX.Width = 80;
            txtweightX.Location = new Point(45, 75);
            ////////////////txtweightX.

            txtweightY.Width = 80;
            txtweightY.Location = new Point(165, 75);

            //Button
            btnOK.Text = "OK";
            btnOK.Location = new Point(((this.Width - (btnOK.Width * 2)) / 3), (this.Height - 100));
            btnCANCEL.Text = "CANCEL";
            btnCANCEL.Location = new Point(((this.Width / 2) + ((this.Width - (btnOK.Width * 2)) / 6)), (this.Height - 100));

            //Add button to form
            this.Controls.Add(btnOK);
            this.Controls.Add(btnCANCEL);
            this.Controls.Add(lblweight);
            this.Controls.Add(txtweightX);
            this.Controls.Add(lblweightX);
            this.Controls.Add(txtweightY);
            this.Controls.Add(lblweightY);

            //Event handlers
            btnOK.Click += new System.EventHandler(this.btnOK_Click);
            btnCANCEL.Click += new System.EventHandler(this.btnCANCEL_Click);
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            weightX = Convert.ToInt32(txtweightX.Text);
            weightY = Convert.ToInt32(txtweightY.Text);
            this.Close();//关闭对话框
        }

        private void btnCANCEL_Click(object sender, EventArgs e)
        {
            flag1 = true;
            this.Close();
        }

        private void PerfectFilterL_Load(object sender, EventArgs e)
        {

        }

    }
}