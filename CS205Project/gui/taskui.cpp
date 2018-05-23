#include "taskui.h"
#include "ui_taskui.h"

taskui::taskui(task *t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::taskui)
{
    ui->setupUi(this);
    this->t=t;
    ui->label->setText(t->show());
}

taskui::~taskui()
{
    delete ui;
}

int taskui::getid(){
    return t->getid();
}
