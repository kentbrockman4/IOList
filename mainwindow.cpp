#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QList>
#include <QMessageBox>

QTreeWidgetItem *activeItem;
QTreeWidgetItem *rootIthem;

void MainWindow::initHeaders()
{
    QStringList headerLabels;
    headerLabels.append("Имя");
    headerLabels.append("ADC");
    headerLabels.append("DAC");
    headerLabels.append("DI");
    headerLabels.append("DO");
    headerLabels.append("Pt100");
    headerLabels.append("Relay");

    ui->treeWidget->setColumnCount(headerLabels.count());
    ui->treeWidget->setHeaderLabels(headerLabels);

    rootIthem = new QTreeWidgetItem();
    rootIthem->setText(0, "BNCT");
    ui->treeWidget->addTopLevelItem(rootIthem);
    activeItem = rootIthem;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initHeaders();
    connect(ui->textName, SIGNAL(_keyPressEvent(QKeyEvent*,bool*)),
            this, SLOT(_keyPressEvent(QKeyEvent*,bool*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_keyPressEvent(QKeyEvent *event, bool *riseParentEvent)
{
    if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return))
    {
        *riseParentEvent = false;

        on_pushButton_clicked();
    }
}

void MainWindow::addIthem()
{
    QTreeWidgetItem *ithem = new QTreeWidgetItem();
    ithem->setText(0, ui->textName->toPlainText());
    ithem->setText(1, QString::number(ui->numADC->value()));
    ithem->setText(2, QString::number(ui->numDAC->value()));
    ithem->setText(3, QString::number(ui->numDI->value()));
    ithem->setText(4, QString::number(ui->numDO->value()));
    ithem->setText(5, QString::number(ui->numPt100->value()));
    ithem->setText(6, QString::number(ui->numRelay->value()));

    if (activeItem != nullptr)
    {
        activeItem->addChild(ithem);
        activeItem->setExpanded(true);
    }
    else
    {
        ui->treeWidget->addTopLevelItem(ithem);
    }
}

void MainWindow::on_pushButton_clicked()
{
    addIthem();

    ui->textName->setText("");
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    activeItem = item;
}

void MainWindow::on_btnSave_clicked()
{
    //doStuffWithEveryItemInMyTree( ui->treeWidget->invisibleRootItem() );
}

void doStuffWithEveryItemInMyTree( QTreeWidgetItem *item )
{
    // Do something with item ...

    for( int i = 0; i < item->childCount(); ++i )
        doStuffWithEveryItemInMyTree( item->child(i) );
}
