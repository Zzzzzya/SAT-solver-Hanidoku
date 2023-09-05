#include <QDebug>
#include <iostream>
#include "sat_widget.h"
#include "SAT_solve_yh.h"
#include "ui_sat_widget.h"

SAT_Widget::SAT_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SAT_Widget)
{
    ui->setupUi(this);
}

SAT_Widget::~SAT_Widget()
{
    delete ui;
}

void SAT_Widget::show_sat()
{
    this->show();
}

void SAT_Widget::on_ptn_return_mainwindow_clicked()
{
    this->close();
    emit turn_to_mainwindow();
}


void SAT_Widget::on_input_returnPressed()//当输入结束时 读取该文本框的内容即为地址
{
    QString address=this->ui->input->text();
    qDebug()<<"address="<<address<<"\n";
    char*filename;
    QByteArray ba = address.toLatin1();    // must
    filename=ba.data();
    qDebug()<<"ba="<<filename<<"\n";

    SAT_solver_yh* solver=new SAT_solver_yh;
    ui->output->insertPlainText("正在运行中..\n");
    solver->createfromfile(filename);
    solver->Travel();
    int result=solver->solve();

    if(result==1)
    {
        ui->output->insertPlainText("s 1\nv ");
        for(int i=1;i<=solver->num_liter;i++)
        {
            QString out=QString::number(solver->ans[i]*i);
            ui->output->insertPlainText(out);
            ui->output->insertPlainText(" ");
        }
        ui->output->insertPlainText("\n");
        ui->output->insertPlainText("t ");
        QString time=QString::number((double)(solver->end_time - solver->start_time) / CLOCKS_PER_SEC * 1000);
        ui->output->insertPlainText(time);

    }
    else if(result==0)
    {
        ui->output->insertPlainText("s 0\n");
        QString time=QString::number((double)(solver->end_time - solver->start_time) / CLOCKS_PER_SEC * 1000);
        ui->output->insertPlainText("t ");
        ui->output->insertPlainText(time);
    }
        ui->output->insertPlainText("运行完毕！");

    delete solver;
}

