#include "treewidgetitem.h"
#include <QtCore>

TreeWidgetItem::TreeWidgetItem()
{


}

void TreeWidgetItem::add(int _adc,
                         int _dac,
                         int _di,
                         int _do,
                         int _pt100,
                         int _relay)
{
    this->_adc += _adc;
    this->_dac += _dac;
    this->_di += _di;
    this->_do += _do;
    this->_pt100 += _pt100;
    this->_relay += _relay;
}

void TreeWidgetItem::clear()
{
    _adc = 0;
    _dac = 0;
    _di = 0;
    _do = 0;
    _pt100 = 0;
    _relay = 0;
}

