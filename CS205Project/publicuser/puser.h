#ifndef PUSER_H
#define PUSER_H
#include "../DB/userdb.h"

class puser
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
    puser();
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

#endif // PUSER_H
