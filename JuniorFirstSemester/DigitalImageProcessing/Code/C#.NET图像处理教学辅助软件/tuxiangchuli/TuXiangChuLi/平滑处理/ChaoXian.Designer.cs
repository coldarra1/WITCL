namespace WindowsApplication1
{
    partial class ChaoXian
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
            this.textBox_lowfilter = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(40, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "请输入阀值T:";
            // 
            // textBox_lowfilter
            // 
            this.textBox_lowfilter.Location = new System.Drawing.Point(42, 73);
            this.textBox_lowfilter.Name = "textBox_lowfilter";
            this.textBox_lowfilter.Size = new System.Drawing.Size(116, 21);
            this.textBox_lowfilter.TabIndex = 3;
            this.textBox_lowfilter.Text = "100";
            this.textBox_lowfilter.TextChanged += new System.EventHandler(this.textBox_lowfilter_TextChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(209, 73);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(71, 23);
            this.button1.TabIndex = 5;
            this.button1.Text = "OK";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // ChaoXian
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(324, 120);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textBox_lowfilter);
            this.Controls.Add(this.label1);
            this.Name = "ChaoXian";
            this.Text = "超限邻域平均法";
            this.Load += new System.EventHandler(this.ChaoXian_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox_lowfilter;
        private System.Windows.Forms.Button button1;
    }
}