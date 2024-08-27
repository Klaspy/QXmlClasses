#ifndef XMLOBJECT_H
#define XMLOBJECT_H

#include <QHash>

#include "xmlvalue.h"

namespace XmlClasses
{
class XmlObject
{
public:
    XmlObject();
    XmlObject(const QString &name);
    XmlObject(const QString &name, std::initializer_list<std::pair<QString, QString>> attributes);

    QString name() const;
    void setName(const QString &newName);

    /// attributes manipulate functions
    QHash<QString, QString> attributes() const;
    QString getAttribute(const QString &key) const;
    void setAttribute(const QString &key, const QString &value);
    void removeAttribute(const QString &key);
    ///

    /// children manipulate functions
    int size() const              {return m_children.size();}
    bool isEmpty() const          {return m_children.isEmpty();}
    XmlValue at(int i) const      {return m_children.at(i);}
    XmlValue &operator[](int i)   {return m_children[i];}
    XmlValue &first()             {return m_children.first();}
    const XmlValue &first() const {return m_children.first();}
    XmlValue &last()              {return m_children.last();}
    const XmlValue &last() const  {return m_children.last();}

    void append(const XmlObject &obj)         {m_children.append(XmlValue(obj));}
    void append(const QString &string)        {m_children.append(XmlValue(string));}
    void prepend(const XmlObject &obj)        {m_children.prepend(XmlValue(obj));}
    void prepend(const QString &string)       {m_children.prepend(XmlValue(string));}
    void insert(int i, const XmlObject &obj)  {m_children.insert(i, XmlValue(obj));}
    void insert(int i, const QString &string) {m_children.insert(i, XmlValue(string));}

    void clear() {m_children.clear();}
    ///

    operator QString() const;

private:
    QString m_name {""};
    QHash<QString, QString> m_attributes;

    QList<XmlValue> m_children;
};
}

Q_DECLARE_METATYPE(XmlClasses::XmlObject)

#endif // XMLOBJECT_H
