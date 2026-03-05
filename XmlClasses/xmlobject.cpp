#include "xmlobject.h"

#include <QHash>
#include <QRegularExpression>

#include "xmlvalue.h"
#include "xmlprocessInstruction.h"

namespace XmlClasses
{

QRegularExpression XmlObject::nameExp = QRegularExpression("^[А-Яа-яЁёA-Za-z_:]{1}[А-Яа-яЁёA-Za-z0-9_.-:]*$");
QRegularExpression XmlObject::attrExp = QRegularExpression("^[А-Яа-яЁёA-Za-z_:]{1}[А-Яа-яЁёA-Za-z0-9_.-:]*$");

XmlObject::XmlObject() {}

XmlObject::XmlObject(const QString &name) :
    m_name {name}
{
    if (!nameExp.match(m_name).hasMatch())
    {
        m_name = "name";
    }
}

XmlObject::XmlObject(const QString &name, std::initializer_list<std::pair<QString, QString>> attributes) :
    m_name {name},
    m_attributes {attributes}
{
    if (!nameExp.match(m_name).hasMatch())
    {
        m_name = "name";
    }

    validateAttrs();
}

QString XmlObject::name() const {return m_name;}

void XmlObject::setName(const QString &newName)
{
    if (nameExp.match(newName).hasMatch())
    {
        m_name = newName;
    }

    validateAttrs();
}

QHash<QString, QString> XmlObject::attributes() const {return m_attributes;}

QString XmlObject::getAttribute(const QString &key) const {return m_attributes.value(key);}

void XmlObject::setAttribute(const QString &key, const QString &value)
{
    if (attrExp.match(key).hasMatch())
    {
        m_attributes.insert(key, value);
    }
}

void XmlObject::removeAttribute(const QString &key) {m_attributes.remove(key);}

int XmlObject::size() const                {return m_children.size();}

bool XmlObject::isEmpty() const            {return m_children.isEmpty();}

const XmlValue &XmlObject::at(int i) const {return m_children.at(i);}

XmlValue &XmlObject::operator[](int i)     {return m_children[i];}

XmlValue &XmlObject::first()               {return m_children.first();}

const XmlValue &XmlObject::first() const   {return m_children.first();}

XmlValue &XmlObject::last()                {return m_children.last();}

const XmlValue &XmlObject::last() const    {return m_children.last();}

void XmlObject::append(const XmlObject &obj)
{
    m_children.append(XmlValue(obj));
}

void XmlObject::append(const QString &string)
{
    m_children.append(XmlValue(string));
}

void XmlObject::append(const XmlProcessInstruction &instruction)
{
    m_children.append(XmlValue(instruction));
}

void XmlObject::append(const XmlValue &value)
{
    m_children.append(value);
}

void XmlObject::prepend(const XmlObject &obj)
{
    m_children.prepend(XmlValue(obj));
}

void XmlObject::prepend(const QString &string)
{
    m_children.prepend(XmlValue(string));
}

void XmlObject::prepend(const XmlProcessInstruction &instruction)
{
    m_children.prepend(XmlValue(instruction));
}

void XmlObject::prepend(const XmlValue &value)
{
    m_children.prepend(value);
}

void XmlObject::insert(int i, const XmlObject &obj)
{
    m_children.insert(i, XmlValue(obj));
}

void XmlObject::insert(int i, const QString &string)
{
    m_children.insert(i, XmlValue(string));
}

void XmlObject::insert(int i, const XmlProcessInstruction &instruction)
{
    m_children.insert(i, XmlValue(instruction));
}

void XmlObject::insert(int i, const XmlValue &value)
{
    m_children.insert(i, value);
}

XmlObject XmlObject::find(const QString &name) const
{
    for (int i = 0; i < m_children.size(); i++)
    {
        if (m_children.at(i).isObject() && m_children.at(i).toObject().name() == name)
        {
            return m_children.at(i).toObject();
        }
    }

    return XmlObject();
}

XmlObject XmlObject::findR(const QString &name) const
{
    for (int i = 0; i < m_children.size(); i++)
    {
        if (m_children.at(i).isObject())
        {
            if(m_children.at(i).toObject().name() == name)
            {
                return m_children.at(i).toObject();
            }
            else
            {
                auto pair = m_children.at(i).toObject().findR_private(name);
                if (pair.first)
                {
                    return pair.second;
                }
            }
        }
    }

    return XmlObject();
}

QList<XmlObject> XmlObject::findAll(const QString &name) const
{
    QList<XmlObject> resultList;
    for (int i = 0; i < m_children.size(); i++)
    {
        if (m_children.at(i).isObject() && m_children.at(i).toObject().name() == name)
        {
            resultList.append(m_children.at(i).toObject());
        }
    }

    return resultList;
}

QList<XmlObject> XmlObject::findAllR(const QString &name) const
{
    QList<XmlObject> resultList;
    for (int i = 0; i < m_children.size(); i++)
    {
        if (m_children.at(i).isObject())
        {
            if (m_children.at(i).toObject().name() == name)
            {
                resultList.append(m_children.at(i).toObject());
            }

            resultList.append(m_children.at(i).toObject().findAllR(name));
        }
    }

    return resultList;
}

bool XmlObject::contains(const QString &name) const
{
    for (int i = 0; i < m_children.size(); i++)
    {
        if (m_children.at(i).isObject() && m_children.at(i).toObject().name() == name)
        {
            return true;
        }
    }

    return false;
}

bool XmlObject::containsR(const QString &name) const
{
    for (int i = 0; i < m_children.size(); i++)
    {
        if (m_children.at(i).isObject())
        {
            if(m_children.at(i).toObject().name() == name)
            {
                return true;
            }
            else
            {
                auto pair = m_children.at(i).toObject().findR_private(name);
                if (pair.first)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void XmlObject::clear() {m_children.clear();}

XmlObject::operator QString() const
{
    QString result = "<" + m_name;
    for (QHash<QString, QString>::const_iterator i = m_attributes.constBegin(); i != m_attributes.constEnd(); ++i)
    {
        result += " " + i.key() + "=\"" + i.value() + "\"";
    }

    if (m_children.isEmpty())
    {
        result += "/>";
    }
    else
    {
        result += ">";
        for (int i = 0; i < m_children.size(); i++)
        {
            if (m_children.at(i).isObject())
            {
                result += m_children.at(i).toObject();
            }
            else if (m_children.at(i).isString())
            {
                result += m_children.at(i).toString();
            }
            else if (m_children.at(i).isPI())
            {
                result += m_children.at(i).toInstruction();
            }
        }
        result += "</" + m_name + ">";
    }

    return result;
}

QStringList XmlObject::text() const
{
    QStringList result;
    foreach (const XmlValue &value, m_children)
    {
        if (value.isString())
        {
            result.append(value.toString());
        }
    }

    return result;
}

QString XmlObject::getStructure() const
{
    QString result = "<" + m_name;
    for (QHash<QString, QString>::const_iterator i = m_attributes.constBegin(); i != m_attributes.constEnd(); ++i)
    {
        result += " " + i.key();
    }

    if (m_children.isEmpty())
    {
        result += "/>";
    }
    else
    {
        result += ">";
        for (int i = 0; i < m_children.size(); i++)
        {
            if (m_children.at(i).isObject())
            {
                result += m_children.at(i).toObject().getStructure();
            }
            else if (m_children.at(i).isString())
            {
                result += "string";
            }
            else if (m_children.at(i).isPI())
            {
                result += "<?process instruction?>";
            }
        }
        result += "</" + m_name + ">";
    }

    return result;
}

bool XmlObject::operator ==(const XmlObject &other) const
{
    if (attributes() != other.attributes() || size() != other.size())
        return false;

    for (int i = 0, total = size(); i < total; ++i)
    {
        if (at(i) != other.at(i))
        {
            return false;
        }
    }
    return true;
}

bool XmlObject::operator !=(const XmlObject &other) const
{
    if (attributes() != other.attributes() || size() != other.size())
        return true;

    for (int i = 0, total = size(); i < total; ++i)
    {
        if (at(i) != other.at(i))
        {
            return true;
        }
    }
    return false;
}

QPair<bool, XmlObject> XmlObject::findR_private(const QString &name) const
{
    for (int i = 0; i < m_children.size(); i++)
    {
        if (m_children.at(i).isObject())
        {
            if(m_children.at(i).toObject().name() == name)
            {
                return {true, m_children.at(i).toObject()};
            }
            else
            {
                auto pair = m_children.at(i).toObject().findR_private(name);
                if (pair.first)
                {
                    return pair;
                }
            }
        }
    }

    return {false, XmlObject()};
}

void XmlObject::validateAttrs()
{
    foreach (QString attr, m_attributes.keys()) {
        if (!attrExp.match(attr).hasMatch())
        {
            m_attributes.remove(attr);
        }
    }
}
}
