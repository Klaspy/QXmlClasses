#include "xmldocument.h"

#include <QDebug>

namespace XmlClasses
{
XmlDocument::XmlDocument() {
#if QT_VERSION < QT_VERSION_CHECK(6, 0 ,0)
    m_codec = QTextCodec::codecForName("UTF-8");
#endif
}

XmlDocument::XmlDocument(const XmlObject &root) :
    m_root (root)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0 ,0)
    m_codec = QTextCodec::codecForName("UTF-8");
#endif
}

#if QT_VERSION < QT_VERSION_CHECK(6, 0 ,0)
void XmlDocument::setCodec(const QString &newCodecName)
{
    m_codec = QTextCodec::codecForName(newCodecName.toUtf8());
}
#endif

QByteArray XmlDocument::toXml(bool autoFormatting) const
{
    QByteArray outputXml;
    QXmlStreamWriter writer(&outputXml);
#if QT_VERSION < QT_VERSION_CHECK(6, 0 ,0)
    writer.setCodec(m_codec);
#endif
    writer.setAutoFormatting(autoFormatting);

    writer.writeStartDocument();
    writeObject(&writer, m_root);
    writer.writeEndDocument();

    return outputXml;
}

#if QT_VERSION < QT_VERSION_CHECK(6, 0 ,0)
QByteArray XmlDocument::toXml(QString codec, bool autoFormatting)
{
    setCodec(codec);
    return toXml(autoFormatting);
}
#endif

XmlDocument XmlDocument::fromXml(const QByteArray &xml, XmlParseError *error)
{
    if (error != nullptr)
    {
        error->error  = QXmlStreamReader::NoError;
        error->text   = "";
        error->line   = -1;
        error->column = -1;
    }

    QXmlStreamReader reader(xml);
    if (reader.hasError())
    {
        if (error != nullptr)
        {
            error->error = reader.error();
            error->text  = reader.text().toString();
        }
        return XmlDocument();
    }
    return readXml(reader, error);
}

XmlDocument XmlDocument::fromXml(const QString &xml, XmlParseError *error)
{
    if (error != nullptr)
    {
        error->error  = QXmlStreamReader::NoError;
        error->text   = "";
        error->line   = -1;
        error->column = -1;
    }

    QXmlStreamReader reader(xml);
    if (reader.hasError())
    {
        if (error != nullptr)
        {
            error->error = reader.error();
            error->text  = reader.text().toString();
        }
        return XmlDocument();
    }
    return readXml(reader, error);
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
        else if (object.at(i).isPI())
        {
            const XmlProcessInstruction &pi = object.at(i).toInstruction();
            writer->writeProcessingInstruction(pi.target(), pi.data());
        }
    }

    writer->writeEndElement();
}

XmlDocument XmlDocument::readXml(QXmlStreamReader &reader, XmlParseError *error)
{
    QStack<XmlObject> documentStack;
    XmlDocument resultDoc;

    while (reader.readNext())
    {
        switch (reader.tokenType())
        {
        case QXmlStreamReader::StartDocument:
        {
#if QT_VERSION < QT_VERSION_CHECK(6, 0 ,0)
            resultDoc.setCodec(reader.documentEncoding().toString());
#endif
            break;
        }
        case QXmlStreamReader::EndDocument:
        {
            if (documentStack.isEmpty())
            {
                return XmlDocument();
            }
            else
            {
                resultDoc.setObject(documentStack.first());
                return resultDoc;
            }
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
        case QXmlStreamReader::EndElement:
        {
            if (documentStack.size() > 1)
            {
                XmlObject object = documentStack.pop();
                documentStack.top().append(object);
            }
            break;
        }
        case QXmlStreamReader::Characters:
        {
            if (!reader.isWhitespace())
            {
                QString text = reader.text().toString();
                documentStack.top().append(text);
            }
            break;
        }
        case QXmlStreamReader::ProcessingInstruction:
        {
            if (!documentStack.empty())
            {
                XmlProcessInstruction pi(reader.processingInstructionTarget().toString(),
                                         reader.processingInstructionData().toString());
                documentStack.top().append(pi);
            }
            break;
        }
        case QXmlStreamReader::Invalid:
        {
            qCritical() << "QXmlDocument: error while parsing data:" << reader.errorString()
                        << "; line" << reader.lineNumber() << ", column" << reader.columnNumber();
            if (error != nullptr)
            {
                error->error  = reader.error();
                error->text   = reader.errorString();
                error->line   = reader.lineNumber();
                error->column = reader.columnNumber();
            }
            return XmlDocument();
        }
        default:
        {
            if (reader.tokenType() != QXmlStreamReader::Comment)
            {
                qCritical() << "unresolved token" << reader.tokenString()
                            << "; line" << reader.lineNumber() << ", column" << reader.columnNumber();
            }
        }
        }
    }

    return XmlDocument();
}
}
