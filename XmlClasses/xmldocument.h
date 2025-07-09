#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H

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

#if QT_VERSION < QT_VERSION_CHECK(6, 0 ,0)
    QString codec() const { return m_codec->name();}
    void setCodec(const QString &newCodecName);
#endif

    // QJsonDocument QXmlStreamWriter
    QByteArray toXml(bool autoFormatting = false) const;
#if QT_VERSION < QT_VERSION_CHECK(6, 0 ,0)
    QByteArray toXml(QString codec, bool autoFormatting);
#endif

    static XmlDocument fromXml(const QByteArray &xml, XmlParseError *error = nullptr);
    static XmlDocument fromXml(const QString    &xml, XmlParseError *error = nullptr);

private:
#if QT_VERSION < QT_VERSION_CHECK(6, 0 ,0)
    QTextCodec *m_codec;
#endif
    XmlObject m_root;

    void writeObject(QXmlStreamWriter *writer, const XmlObject &object) const;

    static XmlDocument readXml(QXmlStreamReader &reader, XmlParseError *error);
};
}

#endif // XMLDOCUMENT_H
