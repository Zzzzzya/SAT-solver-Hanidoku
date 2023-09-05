#ifndef HEXAGON_H
#define HEXAGON_H

#include <QWidget>


class CHexagon : public QPushButton
{
public:
    CHexagon(QWidget *parent=0);
    virtual ~CHexagon() {}
protected:
    void paintEvent(QPaintEvent* pEvent);
};

#endif // HEXAGON_H
