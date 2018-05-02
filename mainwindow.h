#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include "treewidgetiteminfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initTreeWidget();

    void resetInput();
    
private:
    void calculateParentChannels();
    void addIthem();
    void refreshTotals(QTreeWidgetItem *item, TreeWidgetItemInfo *parentInfo);

private slots:
    void on_pushButton_clicked();

    void _keyPressEvent(QKeyEvent *event, bool *riseParentEvent);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_btnEdit_clicked();

private:
    Ui::MainWindow *ui;
    void configureTextName();
};

#endif // MAINWINDOW_H
