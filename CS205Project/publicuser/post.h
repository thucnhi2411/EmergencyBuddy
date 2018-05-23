#ifndef POST_H
#define POST_H
#include "puser.h"
#include <QString>
#include <QDateTime>
#include "../DB/eventdb.h"

class post
{

private:
    EventDB *db;
    int event_id;
    //puser *sender= NULL;
    QString name;
    QString event_type;
    QString event_time;
    QString location;
    QString fr_instruction;
    QString public_instruction;
    QString noti_time;
    int verified;
public:
    post();

    int getid();

    void setid(int i);

    void setname(QString n);

    void seteventtype(QString e);

    void setlocation(QString l);

    void settime(QString ti);

    void setnotitime(QString noti);

    void setinstr(QString instr);

    void setveri(int veri);

    QString show();

    void save();

    void load(int id);


};

#endif // POST_H
