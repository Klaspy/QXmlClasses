#ifndef XMLVALUE_H
#define XMLVALUE_H

#include <QString>
#include <QVariant>

#include "xmlprocessInstruction.h"

namespace XmlClasses
{
class XmlObject;

class XmlValue
{
    friend class XmlObject;

public:
    XmlValue(const QString &text);
    XmlValue(const XmlObject &object);
    XmlValue(const XmlProcessInstruction &pi);

    enum Type
    {
        Undefined,
        String,
        Object,
        XmlPI
    };

    bool isString() const {return m_type == Type::String;}
    bool isObject() const {return m_type == Type::Object;}
    bool isPI()     const {return m_type == Type::XmlPI ;}
    XmlValue::Type type() const;

    QString toString() const;
    XmlObject toObject() const;
    XmlProcessInstruction toInstruction() const;

private:
    XmlValue();

    QVariant m_value {QVariant::Invalid};

    Type m_type;
};
}

#endif // XMLVALUE_H
