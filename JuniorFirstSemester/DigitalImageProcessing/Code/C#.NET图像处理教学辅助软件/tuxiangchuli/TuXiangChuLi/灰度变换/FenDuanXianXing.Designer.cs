namespace WindowsApplication1
{
    partial class FenDuanXianXing
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.textx1 = new System.Windows.Forms.TextBox();
            this.texty1 = new System.Windows.Forms.TextBox();
            this.textx2 = new System.Windows.Forms.TextBox();
            this.texty2 = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(100, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "灰度拉伸参数";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(29, 63);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(71, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "第一点X坐标";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(29, 97);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(71, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "第一点Y坐标";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(167, 208);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(71, 23);
            this.button2.TabIndex = 17;
            this.button2.Text = "Cancel";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(63, 208);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(71, 23);
            this.button1.TabIndex = 16;
            this.button1.Text = "OK";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(29, 131);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(71, 12);
            this.label4.TabIndex = 18;
            this.label4.Text = "第二点X坐标";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(29, 166);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(71, 12);
            this.label5.TabIndex = 19;
            this.label5.Text = "第二点Y坐标";
            // 
            // textx1
            // 
            this.textx1.Location = new System.Drawing.Point(138, 54);
            this.textx1.Name = "textx1";
            this.textx1.Size = new System.Drawing.Size(100, 21);
            this.textx1.TabIndex = 20;
            this.textx1.Text = "130";
            this.textx1.TextChanged += new System.EventHandler(this.textx1_TextChanged);
            // 
            // texty1
            // 
            this.texty1.Location = new System.Drawing.Point(138, 88);
            this.texty1.Name = "texty1";
            this.texty1.Size = new System.Drawing.Size(100, 21);
            this.texty1.TabIndex = 21;
            this.texty1.Text = "50";
            // 
            // textx2
            // 
            this.textx2.Location = new System.Drawing.Point(138, 122);
            this.textx2.Name = "textx2";
            this.textx2.Size = new System.Drawing.Size(100, 21);
            this.textx2.TabIndex = 22;
            this.textx2.Text = "150";
            // 
            // texty2
            // 
            this.texty2.Location = new System.Drawing.Point(138, 157);
            this.texty2.Name = "texty2";
            this.texty2.Size = new System.Drawing.Size(100, 21);
            this.texty2.TabIndex = 23;
            this.texty2.Text = "200";
            // 
            // FenDuanXianXing
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 266);
            this.Controls.Add(this.texty2);
            this.Controls.Add(this.textx2);
            this.Controls.Add(this.texty1);
            this.Controls.Add(this.textx1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "FenDuanXianXing";
            this.Text = "FenDuanXianXing";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textx1;
        private System.Windows.Forms.TextBox texty1;
        private System.Windows.Forms.TextBox textx2;
        private System.Windows.Forms.TextBox texty2;
    }
}