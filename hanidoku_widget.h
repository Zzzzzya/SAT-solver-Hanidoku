#pragma once
#ifndef HANIDOKU_WIDGET_H
#define HANIDOKU_WIDGET_H

#include <QWidget>
#include "Hanidoku.h"
#include "num_change.h"
#include <qdebug.h>

namespace Ui {
class Hanidoku_Widget;
}

class Hanidoku_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Hanidoku_Widget(QWidget *parent = nullptr);
    ~Hanidoku_Widget();
    Hanidoku* k=nullptr;

    num_change change;
    void show_map();
    void show_ansmap();
private:
    Ui::Hanidoku_Widget *ui;
private slots:
    void show_Hanidoku();
    void on_ptn_return_mainwindow_clicked();
    void on_ptn_sc_clicked();

    void on_map_1_1_clicked();
    void on_map_1_2_clicked();
    void on_map_1_3_clicked();
    void on_map_1_4_clicked();
    void on_map_1_5_clicked();

    void on_map_9_1_clicked();
    void on_map_9_2_clicked();
    void on_map_9_3_clicked();
    void on_map_9_4_clicked();
    void on_map_9_5_clicked();

    void on_map_2_1_clicked();
    void on_map_2_2_clicked();
    void on_map_2_3_clicked();
    void on_map_2_4_clicked();
    void on_map_2_5_clicked();
    void on_map_2_6_clicked();

    void on_map_8_1_clicked();
    void on_map_8_2_clicked();
    void on_map_8_3_clicked();
    void on_map_8_4_clicked();
    void on_map_8_5_clicked();
    void on_map_8_6_clicked();

    void on_map_3_1_clicked();
    void on_map_3_2_clicked();
    void on_map_3_3_clicked();
    void on_map_3_4_clicked();
    void on_map_3_5_clicked();
    void on_map_3_6_clicked();
    void on_map_3_7_clicked();

    void on_map_7_1_clicked();
    void on_map_7_2_clicked();
    void on_map_7_3_clicked();
    void on_map_7_4_clicked();
    void on_map_7_5_clicked();
    void on_map_7_6_clicked();
    void on_map_7_7_clicked();

    void on_map_4_1_clicked();
    void on_map_4_2_clicked();
    void on_map_4_3_clicked();
    void on_map_4_4_clicked();
    void on_map_4_5_clicked();
    void on_map_4_6_clicked();
    void on_map_4_7_clicked();
    void on_map_4_8_clicked();

    void on_map_6_1_clicked();
    void on_map_6_2_clicked();
    void on_map_6_3_clicked();
    void on_map_6_4_clicked();
    void on_map_6_5_clicked();
    void on_map_6_6_clicked();
    void on_map_6_7_clicked();
    void on_map_6_8_clicked();

    void on_map_5_1_clicked();
    void on_map_5_2_clicked();
    void on_map_5_3_clicked();
    void on_map_5_4_clicked();
    void on_map_5_5_clicked();
    void on_map_5_6_clicked();
    void on_map_5_7_clicked();
    void on_map_5_8_clicked();
    void on_map_5_9_clicked();


    void change_the_map();
    void on_ptn_show_answer_clicked();

    void on_ptn_check_clicked();

    void on_ptn_ctrl_z_clicked();

signals:
    void turn_to_mainwindow();
};

#endif // HANIDOKU_WIDGET_H
