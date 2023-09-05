#ifndef NUM_CHANGE_H
#define NUM_CHANGE_H

#include <QWidget>


namespace Ui {
class num_change;
}

class num_change : public QWidget
{
    Q_OBJECT

public:
    explicit num_change(QWidget *parent = nullptr);
    ~num_change();
    int changenumber=-1;
    bool is_open=true;
    int x=0,y=0;
    void set_output(int,int);
    int getij2(int,int);
    int get_change();
private slots:
    void on_p1_clicked();

    void on_p2_clicked();

    void on_p3_clicked();

    void on_p4_clicked();

    void on_p5_clicked();

    void on_p6_clicked();

    void on_p7_clicked();

    void on_p8_clicked();

    void on_p9_clicked();

    void on_p0_clicked();

    void on_pushButton_clicked();

    void on_exit_clicked();

private:
    Ui::num_change *ui;

signals:
    void num_have_changed();
};

#endif // NUM_CHANGE_H
