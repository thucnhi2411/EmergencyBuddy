#include "alltask.h"

alltask::alltask()
{
    db=new FrTaskDB("../task.sqlite");
    tasks = std::vector<task*>();

}


void alltask::reload(){
    int n = db->rowcount();

    for(int i = 1;i<=n;i++){
        bool has_task = false;
        for(task *t : tasks){
            if(t->getid()==i) has_task=true;
        }
        if(!has_task){
            task *tt = new task();
            tt->setfb(db->getfb(i));
            tt->setinstr(db->getinstr(i));
            tt->setprio(db->getprio(i).toInt());
            tt->setid(i);

            tasks.push_back(tt);
        }


    }

}


std::vector<task*> *alltask::getTasks(){
    return &tasks;
}
