#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QList>
#include <QMessageBox>
#include "treewidgetitem.h"


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

void MainWindow::on_pushButton_clicked()
{
    addIthem();

    ui->textName->setText("");

    calculateParentChannels();
}

void MainWindow::calculateParentChannels()
{
    auto *twi = new TreeWidgetItem();
    doStuffWithEveryItemInMyTree(ui->treeWidget->headerItem(), twi);
}

void MainWindow::doStuffWithEveryItemInMyTree(QTreeWidgetItem *item, TreeWidgetItem *twi)
{
    if (item->childCount() != 0)
    {
        twi->clear();
        for( int i = 0; i < item->childCount(); ++i )
            doStuffWithEveryItemInMyTree(item->child(i), twi);
        item->setText(1, QString::number(twi->_adc));
        item->setText(2, QString::number(twi->_dac));
        item->setText(3, QString::number(twi->_di));
        item->setText(4, QString::number(twi->_do));
        item->setText(5, QString::number(twi->_pt100));
        item->setText(6, QString::number(twi->_relay));
    }
    else
    {
        twi->add(item->text(1).toInt(),
                 item->text(2).toInt(),
                 item->text(3).toInt(),
                 item->text(4).toInt(),
                 item->text(5).toInt(),
                 item->text(6).toInt());
    }
}
