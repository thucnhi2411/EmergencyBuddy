#include "postui.h"
#include "ui_postui.h"

postui::postui(post *p, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::postui)
{
    ui->setupUi(this);
    this->p=p;
    ui->label->setText(p->show());
}

postui::~postui()
{
    delete ui;
}

int postui::getid(){
    return p->getid();
}
