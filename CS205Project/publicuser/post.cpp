#include "post.h"

post::post()
{
    db=new EventDB("../pose.sqlite");
    QDateTime t = QDateTime::currentDateTime();
    noti_time = t.toString();
    //sender=s;
    event_id=-1;
    fr_instruction="";
    public_instruction="";
    verified=-1;
}


void post::setname(QString n){
    name =n;
}

void post::seteventtype(QString e){
    event_type = e;
}

void post::setlocation(QString l){
    location = l;
}

void post::settime(QString ti){
    event_time = ti;
}

void post::setnotitime(QString noti){
    noti_time = noti;
}

void post::setinstr(QString instr){
    public_instruction = instr;
}

void post::setveri(int veri){
    verified = veri;
}

int post::getid(){
    return event_id;
}

QString post::show(){
    if(verified==-1){
        QString pp = noti_time
                +"\n"+"Event Name: "+name + "    "
                + "Event Type: "+event_type + "\n "  +"When: "+event_time+"    "
                +"Location: "+location+"\n";
        return pp;
    } else if(verified == 0){
        QString pp = noti_time+"\n"+"This is a simulation"
                +"\n"+"Event Name: "+name + "    "
                + "Event Type: "+event_type + "\n "  +"When: "+event_time+"    "
                +"Location: "+location+"\n" +"Tips: " + public_instruction;
        return pp;
    }
    QString pp = noti_time
            +"\n"+"Official Notification!"+"\n"+"Event Name: "+name + "    "
            + "Event Type: "+event_type + "\n "  +"When: "+event_time+"    "
            +"Location: "+location+"\n"
            +"Tips: " + public_instruction;
    return pp;

}

void post::save(){
    event_id=db->rowCount()+1;
    db->insert(event_id,name,event_type,event_time,location,fr_instruction,public_instruction,noti_time,verified);
}

void post::setid(int i){
    event_id = i;
}

void post::load(int id){
    this->event_id = id;


}
