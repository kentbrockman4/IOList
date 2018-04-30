#ifndef EXTENDEDQTEXTEDIT_H
#define EXTENDEDQTEXTEDIT_H

#include <QTextEdit>

class ExtendedQTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit ExtendedQTextEdit(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);

signals:
    void _keyPressEvent(QKeyEvent *event, bool *riseParentEvent);

public slots:
};

#endif // EXTENDEDQTEXTEDIT_H
