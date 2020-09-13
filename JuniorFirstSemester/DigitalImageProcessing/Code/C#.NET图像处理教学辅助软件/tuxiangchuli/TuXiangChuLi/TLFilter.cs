using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ConvertBmpToGray
{
    public partial class TLFilter : Form
    {
        public bool flag1 = false;
        public int weightX1;
        public int weightY1;
        public int weightX2;
        public int weightY2;
        private Button btnOK;
        private Button btnCANCEL;
        private Label lblweight1;
        private Label lblweight2;
        private Label lblweightX1;
        private Label lblweightY1;
        private TextBox txtweightX1;
        private TextBox txtweightY1;
        private Label lblweightX2;
        private Label lblweightY2;
        private TextBox txtweightX2;
        private TextBox txtweightY2;
        public TLFilter()
        {
            InitializeComponent();
            this.Text = "梯形低通滤波";
            this.StartPosition = FormStartPosition.CenterScreen;
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.Width = 300;
            this.Height = 250;
            lblweight1 = new Label();
            lblweight2 = new Label();
            lblweightX1 = new Label();
            lblweightY1 = new Label();
            lblweightX2 = new Label();
            lblweightY2 = new Label();
            txtweightX1 = new TextBox();
            txtweightY1 = new TextBox();
            txtweightX2 = new TextBox();
            txtweightY2 = new TextBox();
            btnOK = new Button();
            btnCANCEL = new Button();

            //Label
            lblweight1.Location = new Point(30, 30);
            lblweight1.AutoSize = true;
            lblweight1.Text = "请确定梯形低通滤波截止频率D0的分量";

            lblweight2.Location = new Point(30, 80);
            lblweight2.AutoSize = true;
            lblweight2.Text = "请确定梯形低通滤波截止频率D1的分量(D1>D0)";

            lblweightX1.Location = new Point(30, 50);
            lblweightX1.AutoSize = true;
            lblweightX1.Text = "X:";

            lblweightY1.Location = new Point(150, 50);
            lblweightY1.AutoSize = true;
            lblweightY1.Text = "Y:";

            lblweightX2.Location = new Point(30, 100);
            lblweightX2.AutoSize = true;
            lblweightX2.Text = "X:";

            lblweightY2.Location = new Point(150, 100);
            lblweightY2.AutoSize = true;
            lblweightY2.Text = "Y:";

            //TextBox
            txtweightX1.Width = 80;
            txtweightX1.Location = new Point(45, 50);

            txtweightY1.Width = 80;
            txtweightY1.Location = new Point(165, 50);

            txtweightX2.Width = 80;
            txtweightX2.Location = new Point(45, 100);

            txtweightY2.Width = 80;
            txtweightY2.Location = new Point(165, 100);

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
            this.Controls.Add(lblweightX1);
            this.Controls.Add(lblweightX2);
            this.Controls.Add(lblweightY1);
            this.Controls.Add(lblweightY2);
            this.Controls.Add(txtweightX1);
            this.Controls.Add(txtweightY1);
            this.Controls.Add(txtweightX2);
            this.Controls.Add(txtweightY2);

            //Event handlers
            btnOK.Click += new System.EventHandler(this.btnOK_Click);
            btnCANCEL.Click += new System.EventHandler(this.btnCANCEL_Click);
        }

        private void TLFilter_Load(object sender, EventArgs e)
        {

        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            weightX1 = Convert.ToInt32(txtweightX1.Text);
            weightY1 = Convert.ToInt32(txtweightY1.Text);
            weightX2 = Convert.ToInt32(txtweightX2.Text);
            weightY2 = Convert.ToInt32(txtweightY2.Text);
            this.Close();//关闭对话框
        }

        private void btnCANCEL_Click(object sender, EventArgs e)
        {
            flag1 = true;
            this.Close();//关闭对话框
        }
    }
}