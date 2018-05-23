#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QUrl>
#include <QtWebEngineWidgets>
#include "../publicuser/puser.h"
#include "../publicuser/fresponder.h"
#include "../publicuser/planner.h"
#include "postui.h"
#include "postviewui.h"
#include "plaview2pui.h"
#include "taskui.h"
#include "taskviewui.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_signUp_clicked();



    void on_back_clicked();

    void on_SignIn_clicked();


    void on_back2_clicked();

    void on_back4_clicked();

    void on_back5_clicked();

    void on_signout6_clicked();

    void on_pushButton_2_clicked();

    //void on_pushButton_clicked();

    void on_noti6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_signout3_clicked();

    void on_finish_clicked();

    void on_pubchannel_clicked();

    void on_pushButton_6_clicked();

    void on_signout7_clicked();

private:
    Ui::MainWindow *ui;
    puser *p;
    fresponder *f;
    planner *pla;
    allpost *ap;
    alltask *at;
};

#endif // MAINWINDOW_H
