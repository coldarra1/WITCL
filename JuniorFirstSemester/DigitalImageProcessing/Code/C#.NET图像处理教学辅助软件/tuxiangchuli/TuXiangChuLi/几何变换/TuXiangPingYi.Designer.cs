namespace WindowsApplication1
{
    partial class TuXiangPingYi
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
            this.label2 = new System.Windows.Forms.Label();
            this.textBox_lowfilter = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(95, 60);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(89, 12);
            this.label2.TabIndex = 11;
            this.label2.Tag = "";
            this.label2.Text = "请输入平移变量";
            // 
            // textBox_lowfilter
            // 
            this.textBox_lowfilter.Location = new System.Drawing.Point(82, 113);
            this.textBox_lowfilter.Name = "textBox_lowfilter";
            this.textBox_lowfilter.Size = new System.Drawing.Size(116, 21);
            this.textBox_lowfilter.TabIndex = 12;
            this.textBox_lowfilter.Text = "30";
            this.textBox_lowfilter.TextChanged += new System.EventHandler(this.textBox_lowfilter_TextChanged);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(164, 186);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(71, 23);
            this.button2.TabIndex = 14;
            this.button2.Text = "Cancel";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(60, 186);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(71, 23);
            this.button1.TabIndex = 13;
            this.button1.Text = "OK";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // TuXiangPingYi
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 266);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textBox_lowfilter);
            this.Controls.Add(this.label2);
            this.Name = "TuXiangPingYi";
            this.Text = "FormTXPY";
            this.Load += new System.EventHandler(this.TuXiangPingYi_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox_lowfilter;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
    }
}