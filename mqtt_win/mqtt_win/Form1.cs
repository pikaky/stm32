using MQTTnet;
using MQTTnet.Client;
using MQTTnet.Client.Options;
using MQTTnet.Client.Connecting;
using MQTTnet.Client.Disconnecting;
using MQTTnet.Server;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace mqtt_win
{

    public partial class Form1 : Form
    {
        int gg = 1;

        //命名一波
        private IMqttClient client;

        public Form1()
        {
            InitializeComponent();


            //创建服务
            client = new MqttFactory().CreateMqttClient();
            // 可以打开服务了

            //基本事件 连接好后 会触发后面的委托
            client.ConnectedHandler = new MqttClientConnectedHandlerDelegate(Connectedevent);


        }
        
        private async void button_connect_Click(object sender, EventArgs e)
        {

            var options = new MqttClientOptions() { ClientId = tb_id.Text };

            //ip设置
            options.ChannelOptions = new MqttClientTcpOptions()
            {
               
                Server = tb_address.Text,
                Port = Convert.ToInt32(tb_host.Text)
            };

            //用户密码设置
            options.Credentials = new MqttClientCredentials()
            {
                Username = tb_name.Text,
                Password = tb_password.Text
            };


            options.CleanSession = true;
            options.KeepAlivePeriod = TimeSpan.FromSeconds(60);



            // 启动服务
            if (gg==1)
            {
                tb_message.AppendText(">>>正在连接....");
                await client.ConnectAsync(options);
             gg = 0;
            }

        }

        [Obsolete]
        public void Connectedevent(EventArgs e)
        {
            this.tb_message.AppendText(">>>已连接");

        }

        private void button_stop_Click(object sender, EventArgs e)

        {
            client.DisconnectAsync();
            this.tb_message.AppendText(">>>gg");
            gg = 1;
        }

        private void button_publish_Click(object sender, EventArgs e)
        {
            ClientPublishMqttTopic(tb_publish_topic.Text, tb_publish_text.Text);
        }

        public async void ClientPublishMqttTopic(string topic, string payload)
        {
            

            var message = new MqttApplicationMessage()
            {

                Topic = topic,
                Payload = Encoding.UTF8.GetBytes(payload)
                
            };
            await client.PublishAsync(message);

            tb_message.AppendText("主题：" + topic + "\n内容：" + payload + "\n发送成功！\n");

        }

        private void button_clean_Click(object sender, EventArgs e)
        {
            tb_message.Clear();
        }
    }
    
}
