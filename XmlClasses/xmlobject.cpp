#include "xmlobject.h"
#include "xmlvalue.h"

namespace XmlClasses
{
XmlObject::XmlObject() {}

XmlObject::XmlObject(const QString &name) :
    m_name {name}
{}

XmlObject::XmlObject(const QString &name, std::initializer_list<std::pair<QString, QString>> attributes) :
    m_name {name},
    m_attributes {attributes}
{}

QString XmlObject::name() const
{
    return m_name;
}

void XmlObject::setName(const QString &newName)
{
    m_name = newName;
}

QHash<QString, QString> XmlObject::attributes() const
{
    return m_attributes;
}

QString XmlObject::getAttribute(const QString &key) const
{
    return m_attributes.value(key);
}

void XmlObject::setAttribute(const QString &key, const QString &value)
{
    m_attributes.insert(key, value);
}

void XmlObject::removeAttribute(const QString &key)
{
    m_attributes.remove(key);
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

XmlObject::operator QString() const
{
    QString result = "<";
    result += m_name;
    foreach (QString attr, m_attributes.keys()) {
        result += " " + attr + ":\"" + m_attributes.value(attr) + "\"";
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
        }
        result += "</" + m_name + ">";
    }

    return result;
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
}
