#ifndef TASKUI_H
#define TASKUI_H

#include <QWidget>
#include <../publicuser/task.h>

namespace Ui {
class taskui;
}

class taskui : public QWidget
{
    Q_OBJECT

public:
    explicit taskui(task *t, QWidget *parent = 0);
    ~taskui();
    int getid();

private:
    Ui::taskui *ui;
    task *t;
};

#endif // TASKUI_H
