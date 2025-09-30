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

XmlValue::XmlValue(const XmlProcessInstruction &pi) :
    m_type {Type::XmlPI}
{
    m_value = QVariant::fromValue(pi);
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

XmlProcessInstruction XmlValue::toInstruction() const
{
    if (m_type == Type::XmlPI)
    {
        return m_value.value<XmlProcessInstruction>();
    }
    else
    {
        return XmlProcessInstruction();
    }
}

XmlValue::XmlValue() :
    m_type {Type::Undefined}
{}

bool operator==(const XmlValue &value1, const XmlValue &value2) noexcept
{
    if (value1.type() != value2.type())
        return false;

    switch(value1.type())
    {
    case XmlClasses::XmlValue::Undefined: return true;
    case XmlClasses::XmlValue::String: return value1.toString()     == value2.toString();
    case XmlClasses::XmlValue::Object: return value1.toObject()     == value2.toObject();
    case XmlClasses::XmlValue::XmlPI: return value1.toInstruction() == value2.toInstruction();
    }

    return false;
}

bool operator!=(const XmlValue &value1, const XmlValue &value2) noexcept
{
    if (value1.type() != value2.type())
        return true;

    switch(value1.type())
    {
    case XmlClasses::XmlValue::Undefined: return false;
    case XmlClasses::XmlValue::String: return value1.toString()     != value2.toString();
    case XmlClasses::XmlValue::Object: return value1.toObject()     != value2.toObject();
    case XmlClasses::XmlValue::XmlPI: return value1.toInstruction() != value2.toInstruction();
    }

    return true;
}
}
