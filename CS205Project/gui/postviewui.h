#ifndef POSTVIEWUI_H
#define POSTVIEWUI_H

#include <QWidget>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QLabel>
#include "postui.h"
#include "../publicuser/allpost.h"

namespace Ui {
class postviewui;
}

class postviewui : public QWidget
{
    Q_OBJECT

public:
    explicit postviewui(allpost *all, QWidget *parent = 0);
    ~postviewui();

private slots:
    void reloadposts();
    void scrolldown();

    void on_submit_clicked();

private:
    Ui::postviewui *ui;
    std::vector<postui*> postuis;
    allpost *all;
    QTimer *timer;
    QVBoxLayout *la;
    int h=200;
};

#endif // POSTVIEWUI_H
