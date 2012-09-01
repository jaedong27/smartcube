using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Diagnostics;
using System.Xml;
using System.Xml.Serialization;

namespace SmartCubeServer
{
    class ObjectSerializer
    {
        //Class 객체를 XML 객체로 Serialize
        static public XmlNode SerializeObject(Object pObject, Type type)
        {
            try
            {
                MemoryStream memoryStream = new MemoryStream();
                XmlTextWriter xmlTextWriter = new XmlTextWriter(memoryStream, Encoding.UTF8);
                XmlSerializer xs = new XmlSerializer(type);
                xs.Serialize(xmlTextWriter, pObject);
                memoryStream.Position = 0;
                XmlDocument doc = new XmlDocument();
                doc.Load(memoryStream);
                return doc.DocumentElement;
            }
            catch (Exception e)
            {
                Debug.WriteLine(e.Message);
            }
            return null;

        }

        //XML 객체를 Class 객체로 Deserialize
        static public Object DeserializeObject(XmlNode xmlNode, Type type)
        {
            try
            {
                XmlSerializer xs = new XmlSerializer(type);
                XmlReader reader = new XmlTextReader(new StringReader(xmlNode.OuterXml));
                return xs.Deserialize(reader);
            }
            catch (Exception e)
            {
                Debug.WriteLine(e.Message);
            }
            return null;
        }
    }
}
