#include "planner.h"

planner::planner()
{
    db=new UserDB("../public.sqlite");
    role="Planner";
}


void planner::setcontact(int conif){
    contact=conif;
}

void planner::setid(int id){
    user_id=id;
}

void planner::setlocation(QString loca){
    location=loca;
}

void planner::setname(QString na){
    name=na;
}

void planner::setusername(QString usn){
    username=usn;
}

QString planner::getusername(){
    return username;
}

QString planner::getrole(int id){
    int idd = id;
    return db->retrieveRole(idd);
}

void planner::update(int id){
    int idd = id;
    user_id=idd;
    name=db->getname(idd);
    username=db->getusername(idd);
    location=db->getname(idd);
    contact=db->getcontact(idd).toInt();
}

bool planner::verifyid(int id){
    int idd = id;
    return db->containID(idd);
}

void planner::signup(int user_id, QString& role, QString& name,
                   QString& username, QString& location, int contact){
    this->user_id=user_id;
    this->role=role;
    this->name=name;
    this->username=username;
    this->location=location;
    this->contact=contact;
    db->insert(user_id,role,name,username,location,contact);

}

void planner::signup(){
    db->insert(user_id,role,name,username,location,contact);

}
