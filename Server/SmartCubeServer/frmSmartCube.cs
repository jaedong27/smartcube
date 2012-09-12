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
using System.Xml;

using SmartCubeServer;
using System.Xml.Serialization;

using System.Runtime.Serialization.Json;
using System.IO;

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
            /*HttpServer httpServer;
            httpServer = new MyHttpServer(8080);
            Thread thread = new Thread(new ThreadStart(httpServer.listen));
            thread.Start();*/

            SmartCubeHttpServer httpServer;
            httpServer = new SmartCubeHttpServer(8080);
            Thread thread = new Thread(new ThreadStart(httpServer.listen));
            thread.Start();
        }

        /*
            //webBrowser.Navigate("http://localhost:8080");
            SmartCubeStatus vcube = new SmartCubeStatus();
            vcube.length = 3;
            // Person 객체를 XMLNode 객체로 변환
            XmlNode xmlPersion = ObjectSerializer.SerializeObject(vcube, typeof(SmartCubeStatus));
            //Console.WriteLine(xmlPersion.OuterXml);
            System.Diagnostics.Debug.WriteLine(xmlPersion.OuterXml);

            // XMLNode 객체를 Person 객체로 변환
            //Person person2 = (Person)RKZSerializer.DeserializeObject(xmlPersion, typeof(Person));
            //Console.WriteLine(person2.Age);
             */

        private void button1_Click(object sender, EventArgs e)
        {
            webBrowser.Navigate("\\\\vmware-host\\Shared Folders\\jaedong\\Desktop\\SmartCubeSource\\Application\\Test.html");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //webBrowser.Navigate("http://localhost:8080");
            /*SmartCubeStatus vcube = new SmartCubeStatus();
            vcube.length = 3;
            // Person 객체를 XMLNode 객체로 변환
            XmlNode xmlPersion = ObjectSerializer.SerializeObject(vcube, typeof(SmartCubeStatus));
            //Console.WriteLine(xmlPersion.OuterXml);
            System.Diagnostics.Debug.WriteLine(xmlPersion.OuterXml);

            // XMLNode 객체를 Person 객체로 변환
            //SmartCubeStatus person2 = (Person)RKZSerializer.DeserializeObject(xmlPersion, typeof(SmartCubeStatus));
            //System.Diagnostics.Debug.WriteLine(person2.Age);
            */
            

            
        }
        
        [Serializable]
        internal class Person
        {
            internal string name;
            internal int age;
        }
    }
}
