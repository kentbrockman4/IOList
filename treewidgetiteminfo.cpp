#include "treewidgetiteminfo.h"
#include <QtCore>

TreeWidgetItemInfo::TreeWidgetItemInfo()
{


}

TreeWidgetItemInfo TreeWidgetItemInfo::operator+(const TreeWidgetItemInfo& rhs)
{
    TreeWidgetItemInfo tmp;

    tmp._adc += this->_adc + rhs._adc;
    tmp._dac += this->_dac + rhs._dac;
    tmp._di += this->_di + rhs._di;
    tmp._do += this->_do + rhs._do;
    tmp._pt100 += this->_pt100 + rhs._pt100;
    tmp._relay += this->_relay + rhs._relay;

    return tmp;
}

void TreeWidgetItemInfo::add(int _adc,
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

void TreeWidgetItemInfo::clear()
{
    _adc = 0;
    _dac = 0;
    _di = 0;
    _do = 0;
    _pt100 = 0;
    _relay = 0;
}

