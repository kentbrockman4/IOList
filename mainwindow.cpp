#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QList>
#include <QMessageBox>
#include "treewidgetiteminfo.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initHeaders();

    configureTextName();
}

MainWindow::~MainWindow()
{
    delete ui;
}

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

    auto rootIthem = new QTreeWidgetItem();
    rootIthem->setText(0, "BNCT");
    rootIthem->setText(1, "0");
    rootIthem->setText(2, "0");
    rootIthem->setText(3, "0");
    rootIthem->setText(4, "0");
    rootIthem->setText(5, "0");
    rootIthem->setText(6, "0");
    ui->treeWidget->addTopLevelItem(rootIthem);
}

void MainWindow::configureTextName()
{
    connect(ui->textName, SIGNAL(_keyPressEvent(QKeyEvent*,bool*)),
            this, SLOT(_keyPressEvent(QKeyEvent*,bool*)));
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

    ui->treeWidget->currentItem()->addChild(ithem);
    ui->treeWidget->currentItem()->setExpanded(true);
}

void MainWindow::resetInput()
{
    ui->textName->setText("");
    ui->numADC->setValue(0);
    ui->numDAC->setValue(0);
    ui->numDI->setValue(0);
    ui->numDO->setValue(0);
    ui->numPt100->setValue(0);
    ui->numRelay->setValue(0);
}

void MainWindow::on_pushButton_clicked()
{
    addIthem();

    resetInput();

    calculateParentChannels();
}

void MainWindow::calculateParentChannels()
{
    auto *thisInfo = new TreeWidgetItemInfo();
    doStuffWithEveryItemInMyTree(ui->treeWidget->topLevelItem(0), thisInfo);
}

void MainWindow::doStuffWithEveryItemInMyTree(QTreeWidgetItem *item, TreeWidgetItemInfo *parentInfo)
{
    auto name = item->text(0);
    auto childCount = item->childCount();
    qDebug() << name << ":" << childCount;
    if (childCount != 0)
    {
        TreeWidgetItemInfo thisInfo;
        for( int i = 0; i < childCount; ++i )
            doStuffWithEveryItemInMyTree(item->child(i), &thisInfo);
        item->setText(1, QString::number(thisInfo._adc));
        item->setText(2, QString::number(thisInfo._dac));
        item->setText(3, QString::number(thisInfo._di));
        item->setText(4, QString::number(thisInfo._do));
        item->setText(5, QString::number(thisInfo._pt100));
        item->setText(6, QString::number(thisInfo._relay));

        *parentInfo = *parentInfo + thisInfo;
    }
    else
    {
        parentInfo->add(item->text(1).toInt(),
                 item->text(2).toInt(),
                 item->text(3).toInt(),
                 item->text(4).toInt(),
                 item->text(5).toInt(),
                 item->text(6).toInt());
    }
}
