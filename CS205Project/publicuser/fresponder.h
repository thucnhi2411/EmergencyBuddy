#ifndef FRESPONDER_H
#define FRESPONDER_H
#include "../DB/userdb.h"

class fresponder
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
    fresponder();
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

#endif // FRESPONDER_H
