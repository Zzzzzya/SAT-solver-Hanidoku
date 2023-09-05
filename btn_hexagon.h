#ifndef BTN_HEXAGON_H
#define BTN_HEXAGON_H

#include <QWidget>
#include <QPainter>
namespace Ui {
class btn_hexagon;
}

class btn_hexagon : public QWidget
{
    Q_OBJECT

public:
    explicit btn_hexagon(QWidget *parent = nullptr);
    ~btn_hexagon();

    void setImage(QString normal);
    void paintEvent(QPaintEvent* ev);

private:
    Ui::btn_hexagon *ui;
    QPixmap m_normal;
};

#endif // BTN_HEXAGON_H
