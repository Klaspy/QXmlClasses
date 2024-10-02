#ifndef XMLPROCESSINSTRUCTION_H
#define XMLPROCESSINSTRUCTION_H

#include <QString>
#include <QRegExp>
#include <QObject>

namespace XmlClasses
{

class XmlProcessInstruction
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
};
}

Q_DECLARE_METATYPE(XmlClasses::XmlProcessInstruction)

#endif // XMLPROCESSINSTRUCTION_H
