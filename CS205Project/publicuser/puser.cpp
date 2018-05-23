#include "puser.h"

puser::puser()
{
    db=new UserDB("../public.sqlite");
    role="public";
}


void puser::setcontact(int conif){
    contact=conif;
}

void puser::setid(int id){
    user_id=id;
}

void puser::setlocation(QString loca){
    location=loca;
}

void puser::setname(QString na){
    name=na;
}

void puser::setusername(QString usn){
    username=usn;
}

QString puser::getusername(){
    return username;
}

QString puser::getrole(int id){
    int idd = id;
    return db->retrieveRole(idd);
}

void puser::update(int id){
    int idd = id;
    user_id=idd;
    name=db->getname(idd);
    username=db->getusername(idd);
    location=db->getname(idd);
    contact=db->getcontact(idd).toInt();
}

bool puser::verifyid(int id){
    int idd = id;
    return db->containID(idd);
}

void puser::signup(int user_id, QString& role, QString& name,
                   QString& username, QString& location, int contact){
    this->user_id=user_id;
    this->role=role;
    this->name=name;
    this->username=username;
    this->location=location;
    this->contact=contact;
    db->insert(user_id,role,name,username,location,contact);

}

void puser::signup(){
    db->insert(user_id,role,name,username,location,contact);

}

