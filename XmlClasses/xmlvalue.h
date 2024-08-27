#ifndef XMLVALUE_H
#define XMLVALUE_H

#include <QString>
#include <QVariant>

namespace XmlClasses
{
class XmlObject;

class XmlValue
{
    friend class XmlObject;

public:
    XmlValue(const QString &text);
    XmlValue(const XmlObject &object);

    enum Type
    {
        Undefined,
        String,
        Object
    };

    bool isString() const;
    bool isObject() const;
    XmlValue::Type type() const;

    QString toString() const;
    XmlObject toObject() const;

private:
    XmlValue();

    QVariant m_value {QVariant::Invalid};

    Type m_type;
};
}

#endif // XMLVALUE_H
