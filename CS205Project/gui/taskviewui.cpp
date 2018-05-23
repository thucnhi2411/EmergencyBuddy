#include "taskviewui.h"
#include "ui_taskviewui.h"

taskviewui::taskviewui(int type, alltask *all, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::taskviewui)
{
    ui->setupUi(this);
    this->all=all;
    this->type=type;
    if(type==1)
        ui->label->setText("Type the Instruction Here");
    else if(type==0)
            ui->label->setText("Provide your feedback here");
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    ui->label->setPalette(pa);



    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(reloadtasks()));
    timer->start(500);

    QScrollBar* bar = ui->scrollArea->verticalScrollBar();

    QObject::connect(bar,SIGNAL(rangeChanged(int,int)),this,SLOT(scrolldown()));

    all->reload();


    std::vector<task*> *ta = all->getTasks();

    la = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setMinimumHeight(h);
    ui->scrollAreaWidgetContents->setLayout(la);

    for(task *t : *ta){
        taskui *tui = new taskui(t,ui->scrollArea);
        la->addWidget(tui);
        taskuis.push_back(tui);
        h=h+150;
    }
    ui->scrollAreaWidgetContents->setMinimumHeight(h);
    ui->scrollAreaWidgetContents->setLayout(la);
}

taskviewui::~taskviewui()
{
    delete ui;
}


void taskviewui::scrolldown(){
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());

}

void taskviewui::reloadtasks(){
    all->reload();
    std::vector<task*> *ta = all->getTasks();
    for(task *t : *ta){
        int tid = t->getid();
        bool exist = false;
        for(taskui *ti : taskuis){
            if(tid == ti->getid()) exist = true;
        }

        if(!exist){
            taskui *tui = new taskui(t,ui->scrollArea);
            la->addWidget(tui);
            taskuis.push_back(tui);
        }
    }
}




void taskviewui::on_pushButton_clicked()
{
    task *tas=new task();
    if(type==0)
        tas->setfb(ui->feedback->toPlainText());
    else if(type==1)
        tas->setinstr(ui->feedback->toPlainText());
    if(type==0&&ui->comboBox->currentIndex()==0)
        tas->setprio(1);
    else if(type==0&&ui->comboBox->currentIndex()==1) tas->setprio(2);
    else if(type==1&&ui->comboBox->currentIndex()==1) tas->setprio(-1);
    else if(type==1&&ui->comboBox->currentIndex()==0) tas->setprio(0);
    tas->save();


    all->reload();
    h=h+150;
    ui->scrollAreaWidgetContents->setMinimumHeight(h);
    reloadtasks();

    ui->feedback->clear();
}
