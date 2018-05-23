#include "fresponder.h"

fresponder::fresponder()
{
    db=new UserDB("../public.sqlite");
    role="First Responder";
}


void fresponder::setcontact(int conif){
    contact=conif;
}

void fresponder::setid(int id){
    user_id=id;
}

void fresponder::setlocation(QString loca){
    location=loca;
}

void fresponder::setname(QString na){
    name=na;
}

void fresponder::setusername(QString usn){
    username=usn;
}

QString fresponder::getusername(){
    return username;
}

QString fresponder::getrole(int id){
    int idd = id;
    return db->retrieveRole(idd);
}

void fresponder::update(int id){
    int idd = id;
    user_id=idd;
    name=db->getname(idd);
    username=db->getusername(idd);
    location=db->getname(idd);
    contact=db->getcontact(idd).toInt();
}

bool fresponder::verifyid(int id){
    int idd = id;
    return db->containID(idd);
}

void fresponder::signup(int user_id, QString& role, QString& name,
                   QString& username, QString& location, int contact){
    this->user_id=user_id;
    this->role=role;
    this->name=name;
    this->username=username;
    this->location=location;
    this->contact=contact;
    db->insert(user_id,role,name,username,location,contact);

}

void fresponder::signup(){
    db->insert(user_id,role,name,username,location,contact);

}

