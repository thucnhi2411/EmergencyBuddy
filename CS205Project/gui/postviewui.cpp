#include "postviewui.h"
#include "ui_postviewui.h"

postviewui::postviewui(allpost *all, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::postviewui)
{
    ui->setupUi(this);
    this->all=all;

    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(reloadposts()));
    timer->start(5000);

    QScrollBar* bar = ui->scrollArea->verticalScrollBar();

    QObject::connect(bar,SIGNAL(rangeChanged(int,int)),this,SLOT(scrolldown()));

    all->reload();


    std::vector<post*> *po = all->getPosts();

    la = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setMinimumHeight(h);
    ui->scrollAreaWidgetContents->setLayout(la);

    for(post *p : *po){
        postui *pui = new postui(p,ui->scrollArea);
        la->addWidget(pui);
        postuis.push_back(pui);
        h=h+150;
    }
    ui->scrollAreaWidgetContents->setMinimumHeight(h);
    ui->scrollAreaWidgetContents->setLayout(la);


}

void postviewui::scrolldown(){
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());

}

void postviewui::reloadposts(){
    all->reload();
    std::vector<post*> *po = all->getPosts();
    for(post *p : *po){
        int pid = p->getid();
        bool exist = false;
        for(postui *pi : postuis){
            if(pid == pi->getid()) exist = true;
        }

        if(!exist){
            postui *pui = new postui(p,ui->scrollArea);
            la->addWidget(pui);
            postuis.push_back(pui);
        }
    }



}





postviewui::~postviewui()
{
    delete ui;
}

void postviewui::on_submit_clicked()
{
    post *pos = new post();
    pos->seteventtype(ui->etype->text());
    pos->setlocation(ui->elocaiton->text());
    pos->setname(ui->ename->text());
    pos->settime(ui->etime->text());
    pos->save();
    all->reload();
    h=h+150;
    ui->scrollAreaWidgetContents->setMinimumHeight(h);
    reloadposts();

    ui->etype->clear();
    ui->elocaiton->clear();
    ui->ename->clear();
    ui->etime->clear();
}
