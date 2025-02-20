#ifndef XMLOBJECT_H
#define XMLOBJECT_H

#include <QHash>
#include <QRegExp>

#include "xmlvalue.h"

namespace XmlClasses
{
class XML_CLASSES_EXPORT XmlObject
{
public:
    XmlObject();
    XmlObject(const QString &name);
    XmlObject(const QString &name, std::initializer_list<std::pair<QString, QString>> attributes);

    QString name() const {return m_name;}
    void setName(const QString &newName);

    /// attributes manipulate functions
    QHash<QString, QString> attributes() const {return m_attributes;}
    QString getAttribute(const QString &key) const {return m_attributes.value(key);}
    void setAttribute(const QString &key, const QString &value);
    void removeAttribute(const QString &key) {m_attributes.remove(key);}
    ///

    /// children manipulate functions
    int size() const                {return m_children.size();}
    bool isEmpty() const            {return m_children.isEmpty();}
    const XmlValue &at(int i) const {return m_children.at(i);}
    XmlValue &operator[](int i)     {return m_children[i];}
    XmlValue &first()               {return m_children.first();}
    const XmlValue &first() const   {return m_children.first();}
    XmlValue &last()                {return m_children.last();}
    const XmlValue &last() const    {return m_children.last();}

    void append(const XmlObject &obj)                            {m_children.append(XmlValue(obj));}
    void append(const QString &string)                           {m_children.append(XmlValue(string));}
    void append(const XmlProcessInstruction &instruction)        {m_children.append(XmlValue(instruction));}
    void append(const XmlValue &value)                           {m_children.append(value);}

    void prepend(const XmlObject &obj)                           {m_children.prepend(XmlValue(obj));}
    void prepend(const QString &string)                          {m_children.prepend(XmlValue(string));}
    void prepend(const XmlProcessInstruction &instruction)       {m_children.prepend(XmlValue(instruction));}
    void prepend(const XmlValue &value)                           {m_children.prepend(value);}

    void insert(int i, const XmlObject &obj)                     {m_children.insert(i, XmlValue(obj));}
    void insert(int i, const QString &string)                    {m_children.insert(i, XmlValue(string));}
    void insert(int i, const XmlProcessInstruction &instruction) {m_children.insert(i, XmlValue(instruction));}
    void insert(int i, const XmlValue &value)                    {m_children.insert(i, value);}

    XmlObject find(const QString &name) const;
    XmlObject findR(const QString &name) const;

    QList<XmlObject> findAll(const QString &name) const;
    QList<XmlObject> findAllR(const QString &name) const;

    bool contains(const QString &name) const;
    bool containsR(const QString &name) const;

    void clear() {m_children.clear();}
    ///

    operator QString() const;

    QStringList text() const;

    // get structure of object and its children (return object name and atribute name without current values)
    QString getStructure() const;

private:
    QString m_name {"name"};
    QHash<QString, QString> m_attributes;

    QList<XmlValue> m_children;

    QPair<bool, XmlObject> findR_private(const QString &name) const;

    void validateAttrs();
};
}

Q_DECLARE_METATYPE(XmlClasses::XmlObject)

#endif // XMLOBJECT_H
