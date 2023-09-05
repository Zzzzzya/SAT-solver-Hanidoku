#ifndef SAT_WIDGET_H
#define SAT_WIDGET_H

#include <QWidget>

namespace Ui {
class SAT_Widget;
}

class SAT_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit SAT_Widget(QWidget *parent = nullptr);
    ~SAT_Widget();

private:
    Ui::SAT_Widget *ui;


private slots:
    void show_sat();
    void on_ptn_return_mainwindow_clicked();

    void on_input_returnPressed();

signals:
    void turn_to_mainwindow();
};

#endif // SAT_WIDGET_H
