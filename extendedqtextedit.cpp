#include "extendedqtextedit.h"
#include <QTextEdit>

ExtendedQTextEdit::ExtendedQTextEdit(QWidget *parent) : QTextEdit(parent)
{

}

void ExtendedQTextEdit::keyPressEvent(QKeyEvent *event)
{
    bool riseParentEvent = true;
    emit _keyPressEvent(event, &riseParentEvent);

    if (riseParentEvent)
    {
        QTextEdit::keyPressEvent(event);
    }
}
