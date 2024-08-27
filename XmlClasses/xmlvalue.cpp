#include "xmlvalue.h"
#include "xmlobject.h"

namespace XmlClasses
{
XmlValue::XmlValue(const QString &string) :
    m_value {string},
    m_type {Type::String}
{}

XmlValue::XmlValue(const XmlObject &object) :
    m_type {Type::Object}
{
    m_value = QVariant::fromValue(object);
}

bool XmlValue::isString() const
{
    return m_type == Type::String;
}

bool XmlValue::isObject() const
{
    return m_type == Type::Object;
}

XmlValue::Type XmlValue::type() const
{
    return m_type;
}

QString XmlValue::toString() const
{
    if (m_type == Type::String)
    {
        return m_value.toString();
    }
    else
    {
        return QString();
    }
}

XmlObject XmlValue::toObject() const
{
    if (m_type == Type::Object)
    {
        return m_value.value<XmlObject>();
    }
    else
    {
        return XmlObject();
    }
}

XmlValue::XmlValue() :
    m_type {Type::Undefined}
{}
}
