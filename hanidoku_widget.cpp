#include "ui_hanidoku_widget.h"
#include "hanidoku_widget.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


Hanidoku_Widget::Hanidoku_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hanidoku_Widget)
{
    ui->setupUi(this);
}

Hanidoku_Widget::~Hanidoku_Widget()
{
    delete ui;
}

void Hanidoku_Widget::show_map()
{
    //根据map的数值，呈现按钮的值
    this->ui->map_1_1->setText(QString::number(this->k->map[0][0]));
    this->ui->map_1_2->setText(QString::number(this->k->map[0][1]));
    this->ui->map_1_3->setText(QString::number(this->k->map[0][2]));
    this->ui->map_1_4->setText(QString::number(this->k->map[0][3]));
    this->ui->map_1_5->setText(QString::number(this->k->map[0][4]));

    this->ui->map_2_1->setText(QString::number(this->k->map[1][0]));
    this->ui->map_2_2->setText(QString::number(this->k->map[1][1]));
    this->ui->map_2_3->setText(QString::number(this->k->map[1][2]));
    this->ui->map_2_4->setText(QString::number(this->k->map[1][3]));
    this->ui->map_2_5->setText(QString::number(this->k->map[1][4]));
    this->ui->map_2_6->setText(QString::number(this->k->map[1][5]));

    this->ui->map_3_1->setText(QString::number(this->k->map[2][0]));
    this->ui->map_3_2->setText(QString::number(this->k->map[2][1]));
    this->ui->map_3_3->setText(QString::number(this->k->map[2][2]));
    this->ui->map_3_4->setText(QString::number(this->k->map[2][3]));
    this->ui->map_3_5->setText(QString::number(this->k->map[2][4]));
    this->ui->map_3_6->setText(QString::number(this->k->map[2][5]));
    this->ui->map_3_7->setText(QString::number(this->k->map[2][6]));

    this->ui->map_4_1->setText(QString::number(this->k->map[3][0]));
    this->ui->map_4_2->setText(QString::number(this->k->map[3][1]));
    this->ui->map_4_3->setText(QString::number(this->k->map[3][2]));
    this->ui->map_4_4->setText(QString::number(this->k->map[3][3]));
    this->ui->map_4_5->setText(QString::number(this->k->map[3][4]));
    this->ui->map_4_6->setText(QString::number(this->k->map[3][5]));
    this->ui->map_4_7->setText(QString::number(this->k->map[3][6]));
    this->ui->map_4_8->setText(QString::number(this->k->map[3][7]));

    this->ui->map_5_1->setText(QString::number(this->k->map[4][0]));
    this->ui->map_5_2->setText(QString::number(this->k->map[4][1]));
    this->ui->map_5_3->setText(QString::number(this->k->map[4][2]));
    this->ui->map_5_4->setText(QString::number(this->k->map[4][3]));
    this->ui->map_5_5->setText(QString::number(this->k->map[4][4]));
    this->ui->map_5_6->setText(QString::number(this->k->map[4][5]));
    this->ui->map_5_7->setText(QString::number(this->k->map[4][6]));
    this->ui->map_5_8->setText(QString::number(this->k->map[4][7]));
    this->ui->map_5_9->setText(QString::number(this->k->map[4][8]));

    this->ui->map_6_1->setText(QString::number(this->k->map[5][1]));
    this->ui->map_6_2->setText(QString::number(this->k->map[5][2]));
    this->ui->map_6_3->setText(QString::number(this->k->map[5][3]));
    this->ui->map_6_4->setText(QString::number(this->k->map[5][4]));
    this->ui->map_6_5->setText(QString::number(this->k->map[5][5]));
    this->ui->map_6_6->setText(QString::number(this->k->map[5][6]));
    this->ui->map_6_7->setText(QString::number(this->k->map[5][7]));
    this->ui->map_6_8->setText(QString::number(this->k->map[5][8]));

    this->ui->map_7_1->setText(QString::number(this->k->map[6][2]));
    this->ui->map_7_2->setText(QString::number(this->k->map[6][3]));
    this->ui->map_7_3->setText(QString::number(this->k->map[6][4]));
    this->ui->map_7_4->setText(QString::number(this->k->map[6][5]));
    this->ui->map_7_5->setText(QString::number(this->k->map[6][6]));
    this->ui->map_7_6->setText(QString::number(this->k->map[6][7]));
    this->ui->map_7_7->setText(QString::number(this->k->map[6][8]));

    this->ui->map_8_1->setText(QString::number(this->k->map[7][3]));
    this->ui->map_8_2->setText(QString::number(this->k->map[7][4]));
    this->ui->map_8_3->setText(QString::number(this->k->map[7][5]));
    this->ui->map_8_4->setText(QString::number(this->k->map[7][6]));
    this->ui->map_8_5->setText(QString::number(this->k->map[7][7]));
    this->ui->map_8_6->setText(QString::number(this->k->map[7][8]));

    this->ui->map_9_1->setText(QString::number(this->k->map[8][4]));
    this->ui->map_9_2->setText(QString::number(this->k->map[8][5]));
    this->ui->map_9_3->setText(QString::number(this->k->map[8][6]));
    this->ui->map_9_4->setText(QString::number(this->k->map[8][7]));
    this->ui->map_9_5->setText(QString::number(this->k->map[8][8]));

}


void Hanidoku_Widget::show_ansmap()
{
    //根据map的数值，呈现按钮的值
    this->ui->map_1_1->setText(QString::number(this->k->ansmap[0][0]));
    this->ui->map_1_2->setText(QString::number(this->k->ansmap[0][1]));
    this->ui->map_1_3->setText(QString::number(this->k->ansmap[0][2]));
    this->ui->map_1_4->setText(QString::number(this->k->ansmap[0][3]));
    this->ui->map_1_5->setText(QString::number(this->k->ansmap[0][4]));

    this->ui->map_2_1->setText(QString::number(this->k->ansmap[1][0]));
    this->ui->map_2_2->setText(QString::number(this->k->ansmap[1][1]));
    this->ui->map_2_3->setText(QString::number(this->k->ansmap[1][2]));
    this->ui->map_2_4->setText(QString::number(this->k->ansmap[1][3]));
    this->ui->map_2_5->setText(QString::number(this->k->ansmap[1][4]));
    this->ui->map_2_6->setText(QString::number(this->k->ansmap[1][5]));

    this->ui->map_3_1->setText(QString::number(this->k->ansmap[2][0]));
    this->ui->map_3_2->setText(QString::number(this->k->ansmap[2][1]));
    this->ui->map_3_3->setText(QString::number(this->k->ansmap[2][2]));
    this->ui->map_3_4->setText(QString::number(this->k->ansmap[2][3]));
    this->ui->map_3_5->setText(QString::number(this->k->ansmap[2][4]));
    this->ui->map_3_6->setText(QString::number(this->k->ansmap[2][5]));
    this->ui->map_3_7->setText(QString::number(this->k->ansmap[2][6]));

    this->ui->map_4_1->setText(QString::number(this->k->ansmap[3][0]));
    this->ui->map_4_2->setText(QString::number(this->k->ansmap[3][1]));
    this->ui->map_4_3->setText(QString::number(this->k->ansmap[3][2]));
    this->ui->map_4_4->setText(QString::number(this->k->ansmap[3][3]));
    this->ui->map_4_5->setText(QString::number(this->k->ansmap[3][4]));
    this->ui->map_4_6->setText(QString::number(this->k->ansmap[3][5]));
    this->ui->map_4_7->setText(QString::number(this->k->ansmap[3][6]));
    this->ui->map_4_8->setText(QString::number(this->k->ansmap[3][7]));

    this->ui->map_5_1->setText(QString::number(this->k->ansmap[4][0]));
    this->ui->map_5_2->setText(QString::number(this->k->ansmap[4][1]));
    this->ui->map_5_3->setText(QString::number(this->k->ansmap[4][2]));
    this->ui->map_5_4->setText(QString::number(this->k->ansmap[4][3]));
    this->ui->map_5_5->setText(QString::number(this->k->ansmap[4][4]));
    this->ui->map_5_6->setText(QString::number(this->k->ansmap[4][5]));
    this->ui->map_5_7->setText(QString::number(this->k->ansmap[4][6]));
    this->ui->map_5_8->setText(QString::number(this->k->ansmap[4][7]));
    this->ui->map_5_9->setText(QString::number(this->k->ansmap[4][8]));

    this->ui->map_6_1->setText(QString::number(this->k->ansmap[5][1]));
    this->ui->map_6_2->setText(QString::number(this->k->ansmap[5][2]));
    this->ui->map_6_3->setText(QString::number(this->k->ansmap[5][3]));
    this->ui->map_6_4->setText(QString::number(this->k->ansmap[5][4]));
    this->ui->map_6_5->setText(QString::number(this->k->ansmap[5][5]));
    this->ui->map_6_6->setText(QString::number(this->k->ansmap[5][6]));
    this->ui->map_6_7->setText(QString::number(this->k->ansmap[5][7]));
    this->ui->map_6_8->setText(QString::number(this->k->ansmap[5][8]));

    this->ui->map_7_1->setText(QString::number(this->k->ansmap[6][2]));
    this->ui->map_7_2->setText(QString::number(this->k->ansmap[6][3]));
    this->ui->map_7_3->setText(QString::number(this->k->ansmap[6][4]));
    this->ui->map_7_4->setText(QString::number(this->k->ansmap[6][5]));
    this->ui->map_7_5->setText(QString::number(this->k->ansmap[6][6]));
    this->ui->map_7_6->setText(QString::number(this->k->ansmap[6][7]));
    this->ui->map_7_7->setText(QString::number(this->k->ansmap[6][8]));

    this->ui->map_8_1->setText(QString::number(this->k->ansmap[7][3]));
    this->ui->map_8_2->setText(QString::number(this->k->ansmap[7][4]));
    this->ui->map_8_3->setText(QString::number(this->k->ansmap[7][5]));
    this->ui->map_8_4->setText(QString::number(this->k->ansmap[7][6]));
    this->ui->map_8_5->setText(QString::number(this->k->ansmap[7][7]));
    this->ui->map_8_6->setText(QString::number(this->k->ansmap[7][8]));

    this->ui->map_9_1->setText(QString::number(this->k->ansmap[8][4]));
    this->ui->map_9_2->setText(QString::number(this->k->ansmap[8][5]));
    this->ui->map_9_3->setText(QString::number(this->k->ansmap[8][6]));
    this->ui->map_9_4->setText(QString::number(this->k->ansmap[8][7]));
    this->ui->map_9_5->setText(QString::number(this->k->ansmap[8][8]));

}
void Hanidoku_Widget::show_Hanidoku()
{
    this->show();
}

void Hanidoku_Widget::on_ptn_return_mainwindow_clicked()
{
    this->close();
    emit turn_to_mainwindow();
}



//生成数独
void Hanidoku_Widget::on_ptn_sc_clicked()
{
    srand(time(nullptr));//播下随机数种子
    int xh=rand()%5000-1;

    qDebug()<<"xh="<<QString::number(xh)<<"\n";

    QObject::connect(&this->change,SIGNAL(num_have_changed()),this,SLOT(change_the_map()));

    this->k=new Hanidoku;
    this->k->Turntocnf(1,xh);
    show_map();

}

void Hanidoku_Widget::change_the_map()
{
    int i=this->change.x;
    int j=this->change.y;
    int x=this->change.changenumber;

    qDebug()<<QString("i=%1,j=%2,x=%3").arg(QString::number(i),QString::number(j),QString::number(x));

    if(this->k->map[i][j]!=0)
    {
        this->ui->output->setPlainText(QString("此格已经有数据！\n"));
    }

    this->k->map[i][j]=x;
    this->k->step_stack[++this->k->top_step_stack] = i*100+j*10;
    this->show_map();
}

void Hanidoku_Widget::on_map_1_1_clicked()
{
    change.show();
    change.set_output(1,1);
}

void Hanidoku_Widget::on_map_1_2_clicked()
{
    change.show();
    change.set_output(1,2);
}

void Hanidoku_Widget::on_map_1_3_clicked()
{
    change.show();
    change.set_output(1,3);
}

void Hanidoku_Widget::on_map_1_4_clicked()
{
    change.show();
    change.set_output(1,4);
}

void Hanidoku_Widget::on_map_1_5_clicked()
{
    change.show();
    change.set_output(1,5);
}

//9
void Hanidoku_Widget::on_map_9_1_clicked()
{
    change.show();
    change.set_output(9,1);
}

void Hanidoku_Widget::on_map_9_2_clicked()
{
    change.show();
    change.set_output(9,2);
}

void Hanidoku_Widget::on_map_9_3_clicked()
{
    change.show();
    change.set_output(9,3);
}

void Hanidoku_Widget::on_map_9_4_clicked()
{
    change.show();
    change.set_output(9,4);
}

void Hanidoku_Widget::on_map_9_5_clicked()
{
    change.show();
    change.set_output(9,5);
}

//2
void Hanidoku_Widget::on_map_2_1_clicked()
{
    change.show();
    change.set_output(2,1);
}

void Hanidoku_Widget::on_map_2_2_clicked()
{
    change.show();
    change.set_output(2,2);
}

void Hanidoku_Widget::on_map_2_3_clicked()
{
    change.show();
    change.set_output(2,3);
}

void Hanidoku_Widget::on_map_2_4_clicked()
{
    change.show();
    change.set_output(2,4);
}

void Hanidoku_Widget::on_map_2_5_clicked()
{
    change.show();
    change.set_output(2,5);
}

void Hanidoku_Widget::on_map_2_6_clicked()
{
    change.show();
    change.set_output(2,6);
}

//8
void Hanidoku_Widget::on_map_8_1_clicked()
{
    change.show();
    change.set_output(8,1);
}

void Hanidoku_Widget::on_map_8_2_clicked()
{
    change.show();
    change.set_output(8,2);
}

void Hanidoku_Widget::on_map_8_3_clicked()
{
    change.show();
    change.set_output(8,3);
}

void Hanidoku_Widget::on_map_8_4_clicked()
{
    change.show();
    change.set_output(8,4);
}

void Hanidoku_Widget::on_map_8_5_clicked()
{
    change.show();
    change.set_output(8,5);
}

void Hanidoku_Widget::on_map_8_6_clicked()
{
    change.show();
    change.set_output(8,6);
}

//3
void Hanidoku_Widget::on_map_3_1_clicked()
{
    change.show();
    change.set_output(3,1);
}

void Hanidoku_Widget::on_map_3_2_clicked()
{
    change.show();
    change.set_output(3,2);
}

void Hanidoku_Widget::on_map_3_3_clicked()
{
    change.show();
    change.set_output(3,3);
}

void Hanidoku_Widget::on_map_3_4_clicked()
{
    change.show();
    change.set_output(3,4);
}

void Hanidoku_Widget::on_map_3_5_clicked()
{
    change.show();
    change.set_output(3,5);
}

void Hanidoku_Widget::on_map_3_6_clicked()
{
    change.show();
    change.set_output(3,6);
}

void Hanidoku_Widget::on_map_3_7_clicked()
{
    change.show();
    change.set_output(3,7);
}

//7
void Hanidoku_Widget::on_map_7_1_clicked()
{
    change.show();
    change.set_output(7,1);
}

void Hanidoku_Widget::on_map_7_2_clicked()
{
    change.show();
    change.set_output(7,2);
}

void Hanidoku_Widget::on_map_7_3_clicked()
{
    change.show();
    change.set_output(7,3);
}

void Hanidoku_Widget::on_map_7_4_clicked()
{
    change.show();
    change.set_output(7,4);
}

void Hanidoku_Widget::on_map_7_5_clicked()
{
    change.show();
    change.set_output(7,5);
}

void Hanidoku_Widget::on_map_7_6_clicked()
{
    change.show();
    change.set_output(7,6);
}

void Hanidoku_Widget::on_map_7_7_clicked()
{
    change.show();
    change.set_output(7,7);
}

//4
void Hanidoku_Widget::on_map_4_1_clicked()
{
    change.show();
    change.set_output(4,1);
}

void Hanidoku_Widget::on_map_4_2_clicked()
{
    change.show();
    change.set_output(4,2);
}

void Hanidoku_Widget::on_map_4_3_clicked()
{
    change.show();
    change.set_output(4,3);
}

void Hanidoku_Widget::on_map_4_4_clicked()
{
    change.show();
    change.set_output(4,4);
}

void Hanidoku_Widget::on_map_4_5_clicked()
{
    change.show();
    change.set_output(4,5);
}

void Hanidoku_Widget::on_map_4_6_clicked()
{
    change.show();
    change.set_output(4,6);
}

void Hanidoku_Widget::on_map_4_7_clicked()
{
    change.show();
    change.set_output(4,7);
}

void Hanidoku_Widget::on_map_4_8_clicked()
{
    change.show();
    change.set_output(4,8);
}

//6
void Hanidoku_Widget::on_map_6_1_clicked()
{
    change.show();
    change.set_output(6,1);
}

void Hanidoku_Widget::on_map_6_2_clicked()
{
    change.show();
    change.set_output(6,2);
}

void Hanidoku_Widget::on_map_6_3_clicked()
{
    change.show();
    change.set_output(6,3);
}

void Hanidoku_Widget::on_map_6_4_clicked()
{
    change.show();
    change.set_output(6,4);
}

void Hanidoku_Widget::on_map_6_5_clicked()
{
    change.show();
    change.set_output(6,5);
}

void Hanidoku_Widget::on_map_6_6_clicked()
{
    change.show();
    change.set_output(6,6);
}

void Hanidoku_Widget::on_map_6_7_clicked()
{
    change.show();
    change.set_output(6,7);
}

void Hanidoku_Widget::on_map_6_8_clicked()
{
    change.show();
    change.set_output(6,8);
}

//5
void Hanidoku_Widget::on_map_5_1_clicked()
{
    change.show();
    change.set_output(5,1);
}

void Hanidoku_Widget::on_map_5_2_clicked()
{
    change.show();
    change.set_output(5,2);
}

void Hanidoku_Widget::on_map_5_3_clicked()
{
    change.show();
    change.set_output(5,3);
}

void Hanidoku_Widget::on_map_5_4_clicked()
{
    change.show();
    change.set_output(5,4);
}

void Hanidoku_Widget::on_map_5_5_clicked()
{
    change.show();
    change.set_output(5,5);
}

void Hanidoku_Widget::on_map_5_6_clicked()
{
    change.show();
    change.set_output(5,6);
}

void Hanidoku_Widget::on_map_5_7_clicked()
{
    change.show();
    change.set_output(5,7);
}

void Hanidoku_Widget::on_map_5_8_clicked()
{
    change.show();
    change.set_output(5,8);
}

void Hanidoku_Widget::on_map_5_9_clicked()
{
    change.show();
    change.set_output(5,9);
}

void Hanidoku_Widget::on_ptn_show_answer_clicked()
{
    this->show_ansmap();
}


void Hanidoku_Widget::on_ptn_check_clicked()
{
    if(this->k->checkcurrentmap())this->ui->output->setPlainText(QString("目前为止正确！\n"));
    else this->ui->output->setPlainText(QString("目前为止有错！\n"));
}


void Hanidoku_Widget::on_ptn_ctrl_z_clicked()
{
    this->k->output();
    this->show_map();
}

