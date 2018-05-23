#ifndef PLANNER_H
#define PLANNER_H
#include "../DB/userdb.h"

class planner
{

private:
    UserDB *db;
    int user_id;
    QString role;
    QString name;
    QString username;
    QString location;
    int contact;

public:
    planner();
    void setid(int);
    void setname(QString);
    void setusername(QString);
    void setlocation(QString);
    void setcontact(int conif);
    QString getusername();
    QString getrole(int id);
    void update(int id);
    void signup();
    bool verifyid(int id);
    void signup(int user_id, QString &role, QString &name, QString &username, QString &location, int contact);


};

#endif // PLANNER_H
