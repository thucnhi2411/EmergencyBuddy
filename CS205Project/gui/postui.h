#ifndef POSTUI_H
#define POSTUI_H

#include <QWidget>
#include "../publicuser/post.h"

namespace Ui {
class postui;
}

class postui : public QWidget
{
    Q_OBJECT

public:
    explicit postui(post *p ,QWidget *parent = 0);
    ~postui();

    int getid();

private:
    Ui::postui *ui;
    post *p;
};

#endif // POSTUI_H
