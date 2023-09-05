#include "num_change.h"
#include "ui_num_change.h"

num_change::num_change(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::num_change)
{
    ui->setupUi(this);
}

num_change::~num_change()
{
    delete ui;
}

void num_change::set_output(int l, int r)
{

    ui->output->setPlainText(QString("改变第%1行第%2列的数据").arg(QString::number(l),QString::number(r)));
    int k=getij2(l,r);
    this->x=k/10;
    this->y=k%10;
}

int num_change::getij2(int l, int r)//根据第几行第几个返回坐标
{
    if (l <= 5)
    {
        return (l-1)*10+r-1;
    }
    else if (l > 5)
    {
        return (l - 1)*10+r + l - 6 ;
    }
    return 0;
}

int num_change::get_change()
{
    return this->changenumber;
}

void num_change::on_p1_clicked()
{
    this->changenumber=1;
    ui->output2->setPlainText(QString("为1"));
}


void num_change::on_p2_clicked()
{
    this->changenumber=2;
    ui->output2->setPlainText(QString("为2"));
}


void num_change::on_p3_clicked()
{
    this->changenumber=3;
    ui->output2->setPlainText(QString("为3"));
}


void num_change::on_p4_clicked()
{
    this->changenumber=4;
    ui->output2->setPlainText(QString("为4"));
}




void num_change::on_p5_clicked()
{
    this->changenumber=5;
    ui->output2->setPlainText(QString("为5"));
}


void num_change::on_p6_clicked()
{
    this->changenumber=6;
    ui->output2->setPlainText(QString("为6"));
}


void num_change::on_p7_clicked()
{
    this->changenumber=7;
    ui->output2->setPlainText(QString("为7"));
}


void num_change::on_p8_clicked()
{
    this->changenumber=8;
    ui->output2->setPlainText(QString("为8"));
}


void num_change::on_p9_clicked()
{
    this->changenumber=9;
    ui->output2->setPlainText(QString("为9"));
}


void num_change::on_p0_clicked()
{
    this->changenumber=0;
    ui->output2->setPlainText(QString("为0"));
}


void num_change::on_pushButton_clicked()
{
    this->is_open=false;
    emit num_have_changed();
    this->close();
}


void num_change::on_exit_clicked()
{
    this->is_open=false;
    this->changenumber=-1;
    this->close();
}

