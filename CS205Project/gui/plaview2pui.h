#ifndef PLAVIEW2PUI_H
#define PLAVIEW2PUI_H

#include <QWidget>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QLabel>
#include "postui.h"
#include "../publicuser/allpost.h"

namespace Ui {
class plaview2pui;
}

class plaview2pui : public QWidget
{
    Q_OBJECT

public:
    explicit plaview2pui(allpost *all, QWidget *parent = 0);
    ~plaview2pui();

private:
    Ui::plaview2pui *ui;
    std::vector<postui*> postuis;
    allpost *all;
    QTimer *timer;
    QVBoxLayout *la;
    int h=200;

private slots:
    void reloadposts();
    void scrolldown();



    void on_pushButton_clicked();
};

#endif // PLAVIEW2PUI_H
