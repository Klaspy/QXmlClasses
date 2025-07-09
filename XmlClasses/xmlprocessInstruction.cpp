#include "xmlprocessInstruction.h"

namespace XmlClasses
{

QRegularExpression XmlProcessInstruction::targetRegExp = QRegularExpression("^[A-Za-z_-]+$");

XmlProcessInstruction::XmlProcessInstruction() :
    m_target {"undefined"},
    m_data {""}
{}

XmlProcessInstruction::XmlProcessInstruction(QString target, QString data) :
    m_target {target},
    m_data {data}
{
    if (!targetRegExp.match(m_target).hasMatch())
    {
        m_target = "undefined";
    }
}

void XmlProcessInstruction::setTarget(const QString &newTarget)
{
    if (targetRegExp.match(newTarget).hasMatch())
    {
        m_target = newTarget;
    }
}

XmlProcessInstruction::operator QString() const
{
    return QString("<?%1 %2?>").arg(m_target, m_data);
}

}
