#ifndef TASKVIEWUI_H
#define TASKVIEWUI_H

#include <QWidget>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QLabel>
#include "taskui.h"
#include "../publicuser/alltask.h"

namespace Ui {
class taskviewui;
}

class taskviewui : public QWidget
{
    Q_OBJECT

public:
    explicit taskviewui(int type,alltask *all, QWidget *parent = 0);
    ~taskviewui();

private:
    Ui::taskviewui *ui;
    std::vector<taskui*> taskuis;
    alltask *all;
    QTimer *timer;
    QVBoxLayout *la;
    int h=200;
    int type;


private slots:
    void reloadtasks();
    void scrolldown();
    void on_pushButton_clicked();
};

#endif // TASKVIEWUI_H
