#include "xmlprocessInstruction.h"

namespace XmlClasses
{

XmlProcessInstruction::XmlProcessInstruction() :
    m_target {"undefined"},
    m_data {""}
{}

XmlProcessInstruction::XmlProcessInstruction(QString target, QString data) :
    m_target {target},
    m_data {data}
{
    QRegExp targetRegExp("[A-Za-z_-]+");
    if (!targetRegExp.exactMatch(m_target))
    {
        m_target = "undefined";
    }
}

void XmlProcessInstruction::setTarget(const QString &newTarget)
{
    QRegExp targetRegExp("[A-Za-z_-]+");
    if (targetRegExp.exactMatch(newTarget))
    {
        m_target = newTarget;
    }
}

XmlProcessInstruction::operator QString() const
{
    return QString("<?%1 %2?>").arg(m_target, m_data);
}

}
