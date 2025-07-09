#ifndef XMLPROCESSINSTRUCTION_H
#define XMLPROCESSINSTRUCTION_H

#include <QString>
#include <QRegularExpression>
#include <QObject>

#if defined(XML_CLASSES_LIBRARY)
#define XML_CLASSES_EXPORT Q_DECL_EXPORT
#else
#define XML_CLASSES_EXPORT Q_DECL_IMPORT
#endif

namespace XmlClasses
{

class XML_CLASSES_EXPORT XmlProcessInstruction
{
public:
    XmlProcessInstruction();
    XmlProcessInstruction(QString target, QString data = "");

    QString target() const {return m_target;}
    void setTarget(const QString &newTarget);

    QString data() const {return m_data;}
    void setData(const QString &newData) {m_data = newData;}

    operator QString() const;

private:
    QString m_target;
    QString m_data;

    static QRegularExpression targetRegExp;
};
}

Q_DECLARE_METATYPE(XmlClasses::XmlProcessInstruction)

#endif // XMLPROCESSINSTRUCTION_H
