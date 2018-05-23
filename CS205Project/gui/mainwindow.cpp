#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    p= new puser();
    f= new fresponder();
    pla = new planner();

    ap = new allpost();
    ap->reload();
    postviewui *pview = new postviewui(ap,this);
    ui->verticalLayout->addWidget(pview);

    plaview2pui *plannerview = new plaview2pui(ap,this);
    ui->verticalLayout_2->addWidget(plannerview);

    at = new alltask();
    at->reload();
    taskviewui *tview = new taskviewui(0,at,this);
    ui->tasklayout->addWidget(tview);

    taskviewui *fview = new taskviewui(1,at,this);
    ui->feedbacklayout->addWidget(fview);

    QWebEngineView* webs=new QWebEngineView;
    QWebEnginePage* page = webs->page();

    connect(page, &QWebEnginePage::featurePermissionRequested,
                [this, page](const QUrl &securityOrigin, QWebEnginePage::Feature feature) {
        if (feature != QWebEnginePage::Geolocation)
            return;
        QMessageBox msgBox(this);
                msgBox.setText(tr("%1 wants to know your location").arg(securityOrigin.host()));
                msgBox.setInformativeText(tr("Do you want to send your current location to this website?"));
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::Yes);

                if (msgBox.exec() == QMessageBox::Yes) {
                    page->setFeaturePermission(
                        securityOrigin, feature, QWebEnginePage::PermissionGrantedByUser);
                } else {
                    page->setFeaturePermission(
                        securityOrigin, feature, QWebEnginePage::PermissionDeniedByUser);
                }
    });

    page->load(QUrl("qrc:/map.html"));
    //webs->show();
    ui->gridLayout->addWidget(webs);

    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_signUp_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->idinput2->clear();
    ui->pnum->clear();
    ui->name2->clear();
    ui->username->clear();
}




void MainWindow::on_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_SignIn_clicked()
{
    ui->errorlabel->setText("");
    if(ui->who->currentIndex()==0){
        QString id = ui->idinput1->text();
        int idd = id.toInt();
        if(p->verifyid(idd)&&p->getrole(idd)==ui->who->currentText()){
            p->setid(idd);
            p->update(idd);

            ui->stackedWidget->setCurrentIndex(1);

        } else{
            ui->errorlabel->setText("Invalid ID");
        }

    } else if(ui->who->currentIndex()==1){
        QString id = ui->idinput1->text();
        int idd = id.toInt();
        if(f->verifyid(idd)&&f->getrole(idd)==ui->who->currentText()){
            f->setid(idd);
            f->update(idd);
            ui->stackedWidget->setCurrentIndex(4);

        } else{
            ui->errorlabel->setText("Invalid ID");
        }
    } else if(ui->who->currentIndex()==2){        
        QString id = ui->idinput1->text();
        int idd = id.toInt();
        if(pla->verifyid(idd)&&pla->getrole(idd)==ui->who->currentText()){
            pla->setid(idd);
            pla->update(idd);
            ui->stackedWidget->setCurrentIndex(3);

        } else{
            ui->errorlabel->setText("Invalid ID");
        }
    }



}



void MainWindow::on_back2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_back4_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_back5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}




void MainWindow::on_signout6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

//void MainWindow::on_pushButton_clicked()
//{
//    ui->stackedWidget->setCurrentIndex(1);
//}

void MainWindow::on_noti6_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_signout3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_finish_clicked()
{
    if(ui->who_2->currentIndex()==0){
        QString role = ui->who_2->currentText();
        QString name = ui->name2->text();
        QString id = ui->idinput2->text();
        int idd = id.toInt();
        QString username = ui->username->text();
        QString phnum = ui->pnum->text();
        int phnumm = phnum.toInt();
        QString location = "null";
        p->signup(idd,role,name,username,location,phnumm);
    } else if(ui->who_2->currentIndex()==1){
        QString role = ui->who_2->currentText();
        QString name = ui->name2->text();
        QString id = ui->idinput2->text();
        int idd = id.toInt();
        QString username = ui->username->text();
        QString phnum = ui->pnum->text();
        int phnumm = phnum.toInt();
        QString location = "null";
        f->signup(idd,role,name,username,location,phnumm);
    } else if(ui->who_2->currentIndex()==2){
        QString role = ui->who_2->currentText();
        QString name = ui->name2->text();
        QString id = ui->idinput2->text();
        int idd = id.toInt();
        QString username = ui->username->text();
        QString phnum = ui->pnum->text();
        int phnumm = phnum.toInt();
        QString location = "null";
        pla->signup(idd,role,name,username,location,phnumm);
    }

    ui->stackedWidget->setCurrentIndex(0);


}

void MainWindow::on_pubchannel_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_signout7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
