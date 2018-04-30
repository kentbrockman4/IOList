#ifndef TREEWIDGETITEM_H
#define TREEWIDGETITEM_H

#include <QtCore>

class TreeWidgetItem
{

public:
    TreeWidgetItem();
    void clear();
    void add(int _adc,
                    int _dac,
                    int _di,
                    int _do,
                    int _pt100,
                    int _relay);

    void getResult(int* _adc,
                    int* _dac,
                    int* _di,
                    int* _do,
                    int* _pt100,
                    int* _relay);

    int _adc;
    int _dac;
    int _di;
    int _do;
    int _pt100;
    int _relay;
};

#endif // TREEWIDGETITEM_H
