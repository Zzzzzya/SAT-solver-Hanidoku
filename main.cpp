#include "mainwindow.h"
#include "hanidoku_widget.h"
#include "sat_widget.h"
#include "SAT_solve_yh.h"
#include "QDir"

#include <QApplication>

int main(int argc, char *argv[])
{



    QApplication a(argc, argv);

    QDir::setCurrent(a.applicationDirPath());

    MainWindow w;
    w.show();

    Hanidoku_Widget hanidoku;
    //hanidoku.show();
    SAT_Widget sat;
    //sat.show();


    //页面切换connect
    QObject::connect(&w,SIGNAL(turn_to_hanidoku()),&hanidoku,SLOT(show_Hanidoku()));
    QObject::connect(&w,SIGNAL(turn_to_sat()),&sat,SLOT(show_sat()));
    QObject::connect(&hanidoku,SIGNAL(turn_to_mainwindow()),&w,SLOT(show_mainwindow()));
    QObject::connect(&sat,SIGNAL(turn_to_mainwindow()),&w,SLOT(show_mainwindow()));



    return a.exec();
}
