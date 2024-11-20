#include <QCoreApplication>
#include <QFile>
#include <QDebug>

#include "XmlClasses/xmldocument.h"

using namespace XmlClasses;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile inputXml(":/example.xml");
    inputXml.open(QIODevice::ReadOnly);
    XmlDocument document = XmlDocument::fromXml(inputXml.readAll());
    inputXml.close();
    QByteArray readedXml = document.toXml(true);
    qInfo() << "readed xml from file:\n" << readedXml.data();

    XmlObject root = document.object();
    qInfo() << "string representation of xml root object:\n" << root << "\n";
    qInfo() << "xml root object structure:\n" << root.getStructure() << "\n";

    qInfo() << "all elements in root:";
    for (int i = 0; i < root.size(); i++)
    {
        XmlValue childValue = root.at(i);
        switch (childValue.type())
        {
        case XmlValue::String:
        {
            qInfo() << "string:" << childValue.toString();
            break;
        }
        case XmlValue::Object:
        {
            qInfo() << "xml element:" << childValue.toObject().name();
            break;
        }
        case XmlValue::XmlPI:
        {
            qInfo() << "process instruction:" << childValue.toInstruction().target();
            break;
        }
        case XmlValue::Undefined:
        {
            // never reach in valid document
            qInfo() << "invalid value";
        }
        }
    }
    qInfo(" ");

    // find first xml element with name in children list
    XmlObject attrsObject = root.find("attributesElement");

    QHash<QString, QString> attributes = attrsObject.attributes();

    qInfo() << "attributes of xml element" << attrsObject.name();
    foreach (const QString &key, attributes.keys())
    {
        qInfo().nospace() << key << ": " << attributes.value(key);
    }
    qInfo(" ");

    // search elements with name in all children tree
    QList<XmlObject> list = root.findAllR("children");

    qInfo() << "list of elements with name \"children\":";
    for (int i = 0; i < list.size(); i++)
    {
        qInfo() << list.at(i);
    }
    qInfo(" ");

    return 0;
}
