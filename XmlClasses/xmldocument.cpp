#include "xmldocument.h"

#include <QDebug>

namespace XmlClasses
{
XmlDocument::XmlDocument() {
    m_codec = QTextCodec::codecForName("UTF-8");
}

XmlDocument::XmlDocument(const XmlObject &root) :
    m_root (root)
{
    m_codec = QTextCodec::codecForName("UTF-8");
}

void XmlDocument::setCodec(const QString &newCodecName)
{
    m_codec = QTextCodec::codecForName(newCodecName.toUtf8());
}

QByteArray XmlDocument::toXml(bool autoFormatting) const
{
    QByteArray outputXml;
    QXmlStreamWriter writer(&outputXml);
    qDebug() << writer.codec()->name();
    writer.setCodec(m_codec);
    writer.setAutoFormatting(autoFormatting);

    writer.writeStartDocument();
    writeObject(&writer, m_root);
    writer.writeEndDocument();

    return outputXml;
}

QByteArray XmlDocument::toXml(QString codec, bool autoFormatting)
{
    setCodec(codec);
    return toXml(autoFormatting);
}

XmlDocument XmlDocument::fromXml(const QByteArray &xml, QXmlStreamReader::Error *error)
{
    QXmlStreamReader reader(xml);
    if (reader.hasError())
    {
        *error = reader.error();
        return XmlDocument();
    }

    QStack<XmlObject> documentStack;
    std::optional<XmlObject> root {std::nullopt};
    XmlDocument resultDoc;

    QString n;
    while (reader.readNext())
    {
        n = reader.name().toString();
        switch (reader.tokenType())
        {
        case QXmlStreamReader::Invalid:
        {
            *error = reader.error();
            return XmlDocument();
        }
        case QXmlStreamReader::StartDocument:
        {
            resultDoc.setCodec(reader.documentEncoding().toString());
            break;
        }
        case QXmlStreamReader::StartElement:
        {
            XmlObject object(reader.name().toString());
            foreach (QXmlStreamAttribute attr, reader.attributes())
            {
                object.setAttribute(attr.name().toString(), attr.value().toString());
            }
            documentStack.push(object);
            break;
        }
        case QXmlStreamReader::Characters:
        {
            if (!reader.isWhitespace())
            {
                documentStack.top().append(reader.text().toString());
            }
            break;
        }
        case QXmlStreamReader::EndElement:
        {
            XmlObject object = documentStack.pop();
            if (documentStack.size() > 0)
            {
                documentStack.top().append(object);
                break;
            }
            else
            {
                resultDoc.setObject(object);
                return resultDoc;
            }
        }
        default:
        {
            qCritical() << "unhandled token" << reader.tokenString();
        }
        }
    }

    return resultDoc;
}

void XmlDocument::writeObject(QXmlStreamWriter *writer, const XmlObject &object) const
{
    writer->writeStartElement(object.name());
    foreach (QString attrName, object.attributes().keys()) {
        writer->writeAttribute(attrName, object.getAttribute(attrName));
    }

    for (int i = 0; i < object.size(); i++)
    {
        if (object.at(i).isObject())
        {
            writeObject(writer, object.at(i).toObject());
        }
        else if (object.at(i).isString())
        {
            writer->writeCharacters(object.at(i).toString());
        }
    }

    writer->writeEndElement();
}
}
