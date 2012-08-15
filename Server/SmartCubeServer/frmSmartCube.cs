using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using Bend.Util;

namespace SmartCubeServer
{
    public partial class frmSmartCube : Form
    {
        public frmSmartCube()
        {
            InitializeComponent();
        }

        private void frmSmartCube_Load(object sender, EventArgs e)
        {
            //Server Start
            HttpServer httpServer;
            httpServer = new MyHttpServer(8080);
            Thread thread = new Thread(new ThreadStart(httpServer.listen));
            thread.Start();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            webBrowser.Navigate("http://localhost:8080");
        }
    }
}
