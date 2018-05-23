#ifndef TASK_H
#define TASK_H
#include <../DB/frtaskdb.h>
#include <QString>
#include <QDateTime>

class task
{

private:
    FrTaskDB *db;
    int event_id;
    int user_id;
    int priority;
    QString instruction;
    QString feedback;
    QString noti_time;

public:
    task();
    int getid();
    void setid(int id);
    void setinstr(QString instr);
    QString getinstr();
    void setfb(QString fb);
    QString getfb();
    QString show();
    int getprio();
    void setprio(int priority);
    void save();
    void load(int id);

};

#endif // TASK_H
