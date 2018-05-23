#include "plaview2pui.h"
#include "ui_plaview2pui.h"

plaview2pui::plaview2pui(allpost *all, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plaview2pui)
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

plaview2pui::~plaview2pui()
{
    delete ui;
}

void plaview2pui::scrolldown(){
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());

}

void plaview2pui::reloadposts(){
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

void plaview2pui::on_pushButton_clicked()
{
    post *pos = new post();
    pos->seteventtype(ui->typen->text());
    pos->setlocation(ui->locationn->text());
    pos->setname(ui->namen->text());
    pos->settime(ui->timen->text());
    pos->setinstr(ui->tips->toPlainText());
    if(ui->comboBox->currentIndex()==0)
        pos->setveri(1);
    else pos->setveri(0);
    pos->save();
    all->reload();
    h=h+150;
    ui->scrollAreaWidgetContents->setMinimumHeight(h);
    reloadposts();
    ui->typen->clear();
    ui->locationn->clear();
    ui->namen->clear();
    ui->timen->clear();
    ui->tips->clear();
}
