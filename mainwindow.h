#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include "treewidgetitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initHeaders();

private:
    void calculateParentChannels();
    void addIthem();
    void doStuffWithEveryItemInMyTree(QTreeWidgetItem *item, TreeWidgetItem *twi);

private slots:
    void on_pushButton_clicked();

    void _keyPressEvent(QKeyEvent *event, bool *riseParentEvent);

private:
    Ui::MainWindow *ui;
    void configureTextName();
};

#endif // MAINWINDOW_H
