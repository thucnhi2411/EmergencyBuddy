#include "task.h"

task::task()
{
    db=new FrTaskDB("../task.sqlite");
    QDateTime t = QDateTime::currentDateTime();
    noti_time = t.toString();
    //sender=s;
    event_id=-1;
    user_id=-1;
    priority=0;
    instruction="";
    feedback="";
}

QString task::getfb(){
    return feedback;
}

void task::setfb(QString fb){
    feedback = fb;
}

int task::getid(){
    return user_id;
}

QString task::getinstr(){
    return instruction;
}

void task::setid(int id){
    user_id = id;
}

void task::setinstr(QString instr){
    instruction=instr;
}

QString task::show(){
    if(priority ==0){
        QString tt=noti_time+"\n"+"From planner \n"+"Instruction:"+instruction;
        return tt;
    } else if(priority == -1){
        QString tt=noti_time+"\n"+"Simulation! \n"+"From planner \n"+"Instruction:"+instruction;
        return tt;
    } else if(priority == 2){
        QString tt=noti_time+"\n"+"Simulation! \n"+"From First Responder \n"+"Feedback:"+feedback;
        return tt;
    }
    QString tt=noti_time+"\n"+"From First Responder \n"+"Feedback:"+feedback;
    return tt;


}

int task::getprio(){
    return priority;
}

void task::setprio(int priority){
    this->priority = priority;
}

void task::save(){
    user_id=db->rowcount()+1;
    db->insert(event_id,user_id,instruction,priority,feedback);
}

void task::load(int id){
    this->user_id=id;

}
