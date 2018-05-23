#include <iostream>
#include "puser.h"
#include "post.h"
#include "allpost.h"
#include <vector>
#include "fresponder.h"
#include "task.h"
#include "alltask.h"
using namespace std;

int main()
{
        QString name("a");
        QString bb("b");
        QString cccc("c");
        QString dddd("d");
        QString name2("a2");
        QString bb2("b2");
        QString cccc2("c2");
        QString dddd2("d2");

    task *t1=new task;
    t1->setfb(name);
    t1->setinstr(bb);
    t1->setprio(1);
    t1->save();

    cout<<t1->show().toStdString()<<endl;

    task *t2=new task;
    t2->setfb(name2);
    t2->setinstr(bb2);
    t2->setprio(0);
    t2->save();

    cout<<t2->show().toStdString()<<endl;

    alltask *all = new alltask();
    all->reload();
    std::vector<task*> *v=all->getTasks();
    cout<<v->back()->show().toStdString()<<endl;
    v->pop_back();
    cout<<v->back()->show().toStdString()<<endl;


//    puser *ppp=new puser();
//    QString q=("username");
//    ppp->setusername(q);
//    ppp->signup(1,q,q,q,q,1);

//    post *a=new post();

//    a->seteventtype(bb);
//    a->setlocation(cccc);
//    a->setname(name);
//    a->settime(dddd);
//    a->setveri(1);
//    a->save();

//    post *b=new post();
//    b->seteventtype(bb2);
//    b->setlocation(cccc2);
//    b->setname(name2);
//    b->settime(dddd2);
//    b->save();

    //allpost *all = new allpost();
    //all->reload();
    //std::vector<post*> *v = all->getPosts();

//    cout <<ppp->getusername().toStdString()<<endl;
   // cout <<v->back()->show().toStdString()<< endl;
//    v->pop_back();
//    cout <<v->back()->show().toStdString()<< endl;
//    v->pop_back();
    //cout <<a->show().toStdString()<< endl;
    return 0;
}
