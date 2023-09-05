#include "btn_hexagon.h"
#include "ui_btn_hexagon.h"


btn_hexagon::btn_hexagon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::btn_hexagon)
{
    ui->setupUi(this);
}

btn_hexagon::~btn_hexagon()
{
    delete ui;
}

void btn_hexagon::setImage(QString normal)
{
    m_normal.load(".\resource\picture\hexagon.png");
    setFixedSize(m_normal.size());
}

void btn_hexagon::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(rect(), m_normal);
}
