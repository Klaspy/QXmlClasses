#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H

#include <QTextCodec>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QStack>

#include "xmlobject.h"

namespace XmlClasses
{

struct XML_CLASSES_EXPORT XmlParseError
{
    QXmlStreamReader::Error error {QXmlStreamReader::NoError};
    QString text;

    int line {-1};
    int column {-1};
};

class XML_CLASSES_EXPORT XmlDocument
{
public:
    XmlDocument();
    XmlDocument(const XmlObject &root);

    XmlObject object() const { return m_root;}
    void setObject(const XmlObject &object) {m_root = object;}

    QString codec() const { return m_codec->name();}
    void setCodec(const QString &newCodecName);

    // QJsonDocument QXmlStreamWriter
    QByteArray toXml(bool autoFormatting = false) const;
    QByteArray toXml(QString codec, bool autoFormatting);

    static XmlDocument fromXml(const QByteArray &xml, XmlParseError *error = nullptr);
    static XmlDocument fromXml(const QString    &xml, XmlParseError *error = nullptr);

private:
    QTextCodec *m_codec;
    XmlObject m_root;

    void writeObject(QXmlStreamWriter *writer, const XmlObject &object) const;

    static XmlDocument readXml(QXmlStreamReader &reader, XmlParseError *error);
};
}

#endif // XMLDOCUMENT_H
