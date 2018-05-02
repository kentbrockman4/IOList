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

    initTreeWidget();

    configureTextName();

    setBtnVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTreeWidget()
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

    ui->treeWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);
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

        this->add();
    }
}

void MainWindow::addIthem()
{
    QTreeWidgetItem *ithem;
    if (editMode)
    {
        ithem = ui->treeWidget->currentItem();
    }
    else
    {
        ithem = new QTreeWidgetItem();
    }

    ithem->setText(0, ui->textName->toPlainText());
    ithem->setText(1, QString::number(ui->numADC->value()));
    ithem->setText(2, QString::number(ui->numDAC->value()));
    ithem->setText(3, QString::number(ui->numDI->value()));
    ithem->setText(4, QString::number(ui->numDO->value()));
    ithem->setText(5, QString::number(ui->numPt100->value()));
    ithem->setText(6, QString::number(ui->numRelay->value()));

    if (editMode)
    {
        setEditMode(false);
    }
    else
    {
        ui->treeWidget->currentItem()->addChild(ithem);
        ui->treeWidget->currentItem()->setExpanded(true);
    }

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

void MainWindow::add()
{
    addIthem();

    resetInput();

    calculateParentChannels();
}

void MainWindow::calculateParentChannels()
{
    auto *thisInfo = new TreeWidgetItemInfo();
    refreshTotals(ui->treeWidget->topLevelItem(0), thisInfo);
}

void MainWindow::refreshTotals(QTreeWidgetItem *item, TreeWidgetItemInfo *parentInfo)
{
    auto childCount = item->childCount();
    if (childCount != 0)
    {
        TreeWidgetItemInfo thisInfo;
        for( int i = 0; i < childCount; ++i )
            refreshTotals(item->child(i), &thisInfo);
        item->setText(1, QString::number(thisInfo._adc));
        item->setText(2, QString::number(thisInfo._dac));
        item->setText(3, QString::number(thisInfo._di));
        item->setText(4, QString::number(thisInfo._do));
        item->setText(5, QString::number(thisInfo._pt100));
        item->setText(6, QString::number(thisInfo._relay));

        *parentInfo = *parentInfo + thisInfo;

        auto color = Qt::lightGray;
        item->setBackgroundColor(0, color);
        item->setBackgroundColor(1, color);
        item->setBackgroundColor(2, color);
        item->setBackgroundColor(3, color);
        item->setBackgroundColor(4, color);
        item->setBackgroundColor(5, color);
        item->setBackgroundColor(6, color);
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

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    ui->textName->setText(item->text(0));
    ui->numADC->setValue(item->text(1).toInt());
    ui->numDAC->setValue(item->text(2).toInt());
    ui->numDI->setValue(item->text(3).toInt());
    ui->numDO->setValue(item->text(4).toInt());
    ui->numPt100->setValue(item->text(5).toInt());
    ui->numRelay->setValue(item->text(6).toInt());

    setEditMode(true);
}

void MainWindow::on_btnAdd_clicked()
{
    this->add();
}

void MainWindow::on_btnCancel_clicked()
{
    setEditMode(false);
}

void MainWindow::setBtnVisible(bool newValue)
{
    ui->btnCancel->setVisible(newValue);
    ui->btnDelete->setVisible(newValue);
}

void MainWindow::setEditMode(bool newValue)
{
    editMode = newValue;
    setBtnVisible(newValue);
    if (newValue)
        ui->btnAdd->setText("Edit");
    else
        ui->btnAdd->setText("Add");
}

void MainWindow::on_btnDelete_clicked()
{
    setEditMode(false);

    try
    {
        deleteChildItems(ui->treeWidget->currentItem());
    }
    catch(std::exception &e)
    {
        qDebug() << e.what();
    }
    catch(...)
    {
        qDebug() << "err";
    }

}

void MainWindow::deleteChildItems(QTreeWidgetItem *item)
{
    auto name = item->text(0);
    int childCount = item->childCount();

    for(int i=0; i <childCount ; i++)
    {
        deleteChildItems(item->child(i));
    }

    delete item;
}
