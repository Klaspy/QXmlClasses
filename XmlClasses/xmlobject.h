#ifndef XMLOBJECT_H
#define XMLOBJECT_H

#include <QMetaType>

#include "XmlClassesGlobal.h"
#include "xmlvalue.h"

class QRegularExpression;

namespace XmlClasses
{

class XmlProcessInstruction;

class XML_CLASSES_EXPORT XmlObject
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
    int size() const;
    bool isEmpty() const;
    const XmlValue &at(int i) const;
    XmlValue &operator[](int i);
    XmlValue &first();
    const XmlValue &first() const;
    XmlValue &last();
    const XmlValue &last() const;

    void append(const XmlObject &obj);
    void append(const QString &string);
    void append(const XmlProcessInstruction &instruction);
    void append(const XmlValue &value);
    
    QList<XmlValue>::const_iterator begin() const {return m_children.begin();}
    QList<XmlValue>::const_iterator end()   const {return m_children.end();}

    void prepend(const XmlObject &obj);
    void prepend(const QString &string);
    void prepend(const XmlProcessInstruction &instruction);
    void prepend(const XmlValue &value);

    void insert(int i, const XmlObject &obj);
    void insert(int i, const QString &string);
    void insert(int i, const XmlProcessInstruction &instruction);
    void insert(int i, const XmlValue &value);

    XmlObject find(const QString &name) const;
    XmlObject findR(const QString &name) const;

    QList<XmlObject> findAll(const QString &name) const;
    QList<XmlObject> findAllR(const QString &name) const;

    bool contains(const QString &name) const;
    bool containsR(const QString &name) const;

    void clear();
    ///

    operator QString() const;

    QStringList text() const;

    // get structure of object and its children (return object name and atribute name without current values)
    QString getStructure() const;

    bool operator ==(const XmlObject &other) const;
    bool operator !=(const XmlObject &other) const;

private:
    QString m_name {"name"};
    QHash<QString, QString> m_attributes;

    QList<XmlValue> m_children;

    static QRegularExpression nameExp;
    static QRegularExpression attrExp;

    QPair<bool, XmlObject> findR_private(const QString &name) const;

    void validateAttrs();
};
}

Q_DECLARE_METATYPE(XmlClasses::XmlObject)

#endif // XMLOBJECT_H
