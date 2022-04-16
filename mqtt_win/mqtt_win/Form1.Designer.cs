
namespace mqtt_win
{
    partial class Form1
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
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.button_connect = new System.Windows.Forms.Button();
            this.button_stop = new System.Windows.Forms.Button();
            this.tb_address = new System.Windows.Forms.TextBox();
            this.tb_host = new System.Windows.Forms.TextBox();
            this.tb_id = new System.Windows.Forms.TextBox();
            this.tb_name = new System.Windows.Forms.TextBox();
            this.tb_password = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.tb_message = new System.Windows.Forms.RichTextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.tb_publish_text = new System.Windows.Forms.RichTextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.tb_publish_topic = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.button_publish = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button_connect
            // 
            this.button_connect.Location = new System.Drawing.Point(27, 357);
            this.button_connect.Name = "button_connect";
            this.button_connect.Size = new System.Drawing.Size(75, 23);
            this.button_connect.TabIndex = 0;
            this.button_connect.Text = "connect";
            this.button_connect.UseVisualStyleBackColor = true;
            this.button_connect.Click += new System.EventHandler(this.button_connect_Click);
            // 
            // button_stop
            // 
            this.button_stop.Location = new System.Drawing.Point(133, 357);
            this.button_stop.Name = "button_stop";
            this.button_stop.Size = new System.Drawing.Size(75, 23);
            this.button_stop.TabIndex = 1;
            this.button_stop.Text = "stop";
            this.button_stop.UseVisualStyleBackColor = true;
            this.button_stop.Click += new System.EventHandler(this.button_stop_Click);
            // 
            // tb_address
            // 
            this.tb_address.Location = new System.Drawing.Point(96, 34);
            this.tb_address.Name = "tb_address";
            this.tb_address.Size = new System.Drawing.Size(142, 25);
            this.tb_address.TabIndex = 2;
            // 
            // tb_host
            // 
            this.tb_host.Location = new System.Drawing.Point(96, 79);
            this.tb_host.Name = "tb_host";
            this.tb_host.Size = new System.Drawing.Size(142, 25);
            this.tb_host.TabIndex = 3;
            // 
            // tb_id
            // 
            this.tb_id.Location = new System.Drawing.Point(96, 128);
            this.tb_id.Name = "tb_id";
            this.tb_id.Size = new System.Drawing.Size(142, 25);
            this.tb_id.TabIndex = 4;
            // 
            // tb_name
            // 
            this.tb_name.Location = new System.Drawing.Point(96, 176);
            this.tb_name.Name = "tb_name";
            this.tb_name.Size = new System.Drawing.Size(142, 25);
            this.tb_name.TabIndex = 5;
            // 
            // tb_password
            // 
            this.tb_password.Location = new System.Drawing.Point(96, 226);
            this.tb_password.Name = "tb_password";
            this.tb_password.Size = new System.Drawing.Size(142, 25);
            this.tb_password.TabIndex = 6;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 37);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(63, 15);
            this.label1.TabIndex = 7;
            this.label1.Text = "address";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(24, 82);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(39, 15);
            this.label2.TabIndex = 8;
            this.label2.Text = "host";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 131);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(79, 15);
            this.label3.TabIndex = 9;
            this.label3.Text = "cliend id";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(24, 179);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(39, 15);
            this.label4.TabIndex = 10;
            this.label4.Text = "name";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 229);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(71, 15);
            this.label5.TabIndex = 11;
            this.label5.Text = "password";
            // 
            // tb_message
            // 
            this.tb_message.Location = new System.Drawing.Point(419, 226);
            this.tb_message.Name = "tb_message";
            this.tb_message.ReadOnly = true;
            this.tb_message.Size = new System.Drawing.Size(338, 154);
            this.tb_message.TabIndex = 12;
            this.tb_message.Text = "";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(356, 229);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(37, 15);
            this.label6.TabIndex = 13;
            this.label6.Text = "消息";
            // 
            // tb_publish_text
            // 
            this.tb_publish_text.Location = new System.Drawing.Point(419, 79);
            this.tb_publish_text.Name = "tb_publish_text";
            this.tb_publish_text.Size = new System.Drawing.Size(338, 115);
            this.tb_publish_text.TabIndex = 14;
            this.tb_publish_text.Text = "";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(346, 82);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(67, 15);
            this.label7.TabIndex = 15;
            this.label7.Text = "发布消息";
            // 
            // tb_publish_topic
            // 
            this.tb_publish_topic.Location = new System.Drawing.Point(419, 27);
            this.tb_publish_topic.Name = "tb_publish_topic";
            this.tb_publish_topic.Size = new System.Drawing.Size(206, 25);
            this.tb_publish_topic.TabIndex = 16;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(346, 30);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(67, 15);
            this.label8.TabIndex = 17;
            this.label8.Text = "发布主题";
            // 
            // button_publish
            // 
            this.button_publish.Location = new System.Drawing.Point(237, 356);
            this.button_publish.Name = "button_publish";
            this.button_publish.Size = new System.Drawing.Size(75, 23);
            this.button_publish.TabIndex = 18;
            this.button_publish.Text = "publish";
            this.button_publish.UseVisualStyleBackColor = true;
            this.button_publish.Click += new System.EventHandler(this.button_publish_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(419, 386);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 19;
            this.button1.Text = "清屏";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button_clean_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.button_publish);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.tb_publish_topic);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.tb_publish_text);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.tb_message);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tb_password);
            this.Controls.Add(this.tb_name);
            this.Controls.Add(this.tb_id);
            this.Controls.Add(this.tb_host);
            this.Controls.Add(this.tb_address);
            this.Controls.Add(this.button_stop);
            this.Controls.Add(this.button_connect);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_connect;
        private System.Windows.Forms.Button button_stop;
        private System.Windows.Forms.TextBox tb_address;
        private System.Windows.Forms.TextBox tb_host;
        private System.Windows.Forms.TextBox tb_id;
        private System.Windows.Forms.TextBox tb_name;
        private System.Windows.Forms.TextBox tb_password;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.RichTextBox tb_message;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.RichTextBox tb_publish_text;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox tb_publish_topic;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button button_publish;
        private System.Windows.Forms.Button button1;
    }
}

