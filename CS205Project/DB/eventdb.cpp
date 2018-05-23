#include "eventdb.h"

/**
 * @brief Default constructor Event_DB
 */
EventDB::EventDB(){
    QString connectionName("event_connection");
    if (!QSqlDatabase::contains(connectionName)) {
        event_DB = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    } else {
        event_DB = QSqlDatabase::database(connectionName);
    }
    event_DB.setDatabaseName("event.sqlite");
    event_DB.open();
    QSqlQuery query(event_DB);
    query.exec("CREATE TABLE IF NOT EXISTS event (     event_id          INT NOT NULL UNIQUE,\
               name              CHAR,\
               event_type        CHAR NOT NULL,\
               event_time        CHAR NOT NULL,\
               location          CHAR NOT NULL,\
               fr_instruction    CHAR,\
               public_instruction CHAR,\
               noti_time         CHAR,\
               verified           INT  )");


}

EventDB::EventDB(const QString& path){
    QString connectionName("event_connection");
    if (!QSqlDatabase::contains(connectionName)) {
        event_DB = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    } else {
        event_DB = QSqlDatabase::database(connectionName);
    }
    buildTable(path);
}
/**
 * @brief Default destructor ~EventDB
 */
EventDB::~EventDB(){
    event_DB.close();
}
/**
 * @brief   connected: Check whether the database is successfully connected
 * @return  whether connection is successful
 */
bool EventDB::connected(){
    return event_DB.isOpen();
}
/**
 * @brief   insert      Insert rows to table
 * @param   event_id            event id
 * @param   name                event's name
 * @param   event_type          event's type
 * @param   event_time          event's time
 * @param   location            event's location
 * @param   fr_instruction      instruction for responder
 * @param   public_instruction  instruction for public
 * @param   noti_time           time to send out notification
 * @param   verified            whether the event is verified
 * @return  whether insertion is successful
 */
bool EventDB::insert(int event_id, QString& name, QString& event_type, QString& event_time,
                             QString& location, QString& fr_instruction, QString& public_instruction, QString& noti_time, int verified){
    bool done = false;
    QSqlQuery query(event_DB);
    query.prepare("INSERT INTO event(event_id, name, event_type, event_time, location, fr_instruction, public_instruction, noti_time, verified)"
                  "VALUES (:event_id, :name, :event_type, :event_time, :location, :fr_instruction, :public_instruction, :noti_time, :verified)");
    query.bindValue(":event_id", event_id);
    query.bindValue(":name", name);
    query.bindValue(":event_type", event_type);
    query.bindValue(":event_time", event_time);
    query.bindValue(":location", location);
    query.bindValue(":fr_instruction",fr_instruction);
    query.bindValue(":public_instruction",public_instruction);
    query.bindValue(":noti_time",noti_time);
    query.bindValue(":verified",verified);

    if (query.exec()){
        done = true;
    } else {
        qDebug()<< query.lastError();
    }
    return done;
}

/**
 * @brief   remove      Remove row with id from table
 * @param   id          id of the row to remove
 * @return  whether removal is successful
 */
bool EventDB::remove(int id){
    bool done = false;
    if (containID(id)){
        QSqlQuery query(event_DB);
        query.prepare("DELETE FROM event WHERE event_id = (:event_id)");
        query.bindValue(":event_id",id);
        if (query.exec()) done = true;

    }

    return done;
}

/**
 * @brief retrieveID    Retrieve row with id from table
 * @param id            id of the row to retrieve
 */
QString EventDB::retrieveID(int id){
    QString s;
    QSqlQuery query(event_DB);
    query.prepare("SELECT * FROM event WHERE event_id = (:event_id)");
    query.bindValue(":event_id", id);

    if (query.exec()){
        while (query.next()){
            QString event_id = query.value(0).toString();
            QString name = query.value(1).toString();
            QString event_type = query.value(2).toString();
            QString event_time = query.value(3).toString();
            QString location = query.value(4).toString();
            QString fr_instruction = query.value(5).toString();
            QString public_instruction = query.value(6).toString();
            QString noti_time = query.value(7).toString();
            QString verified = query.value(8).toString();

            s.append(event_id);
            s.append(" ");
            s.append(name);
            s.append(" ");
            s.append(event_time);
            s.append(" ");
            s.append(event_type);
            s.append(" ");
            s.append(location);
            s.append(" ");
            s.append(fr_instruction);
            s.append(" ");
            s.append(public_instruction);
            s.append(" ");
            s.append(noti_time);
            s.append(" ");
            s.append(verified);
            s.append("\n");

        }
        query.last();
    }
    return s;
}
/**
 * @brief retrieveTable Retrieve all rows in the table
 */
QString EventDB::retrieveTable(){
    QString s;
    QSqlQuery query(event_DB);
    query.prepare("SELECT * FROM event");

    if (query.exec()){
        while (query.next()){
            QString event_id = query.value(0).toString();
            QString name = query.value(1).toString();
            QString event_type = query.value(2).toString();
            QString event_time = query.value(3).toString();
            QString location = query.value(4).toString();
            QString fr_instruction = query.value(5).toString();
            QString public_instruction = query.value(6).toString();
            QString noti_time = query.value(7).toString();
            QString verified = query.value(8).toString();

            s.append(event_id);
            s.append(" ");
            s.append(name);
            s.append(" ");
            s.append(event_time);
            s.append(" ");
            s.append(event_type);
            s.append(" ");
            s.append(location);
            s.append(" ");
            s.append(fr_instruction);
            s.append(" ");
            s.append(public_instruction);
            s.append(" ");
            s.append(noti_time);
            s.append(" ");
            s.append(verified);
            s.append("\n");

        }
        query.last();
    }
    return s;
}
/**
 * @brief updateVerified Verify
 * @param id             the id of the event to verified
 * @return               whether the update process is succeeded
 */
bool EventDB::updateVerified(int id){
    bool done = false;
    if (containID(id)){
        QSqlQuery query(event_DB);
        query.prepare("UPDATE event SET verified = 1 WHERE event_id = (:event_id)");
        query.bindValue(":event_id",id);
        if (query.exec()) done = true;

    }

    return done;
}
/**
 * @brief   containID   Check whether the id is in the table
 * @param   id          The id to check
 * @return  whether the id exists
 */
bool EventDB::containID(int id){
    bool contained = false;
    QSqlQuery query(event_DB);
    query.prepare("SELECT event_id FROM event WHERE event_id = (:event_id)");
    query.bindValue(":event_id", id);

    if (query.exec()){
        if (query.next()){
            contained = true;
        }
    }
    return contained;
}
/**
 * @brief closeDB       Drop table
 */
void EventDB::closeDB(){
    QSqlQuery query(event_DB);
    query.exec("drop table if exists event");
}
/**
 * @brief buildTable    Build table with name
 * @param path          name of the table
 */
void EventDB::buildTable(const QString& path){
    event_DB.setDatabaseName(path);
    event_DB.open();
    QSqlQuery query(event_DB);
    query.exec("CREATE TABLE IF NOT EXISTS event (     event_id          INT NOT NULL UNIQUE,\
               name              CHAR,\
               event_type        CHAR NOT NULL,\
               event_time        CHAR NOT NULL,\
               location          CHAR NOT NULL,\
               fr_instruction    CHAR,\
               public_instruction CHAR,\
               noti_time         CHAR,\
               verified           INT  )");
}
/**
 * @brief EventDB::rowCount
 * @return  number of rows
 */
int EventDB::rowCount(){
    int sum = 0;
    QSqlQuery query(event_DB);
    query.prepare("SELECT * FROM event");

    if (query.exec()){
        while (query.next()){
            sum++;
        }
    }
    return sum;
}

QString EventDB::getname(int id){
    QString s;
    QSqlQuery query(event_DB);
    query.prepare("SELECT name FROM event WHERE event_id = (:event_id)");
    query.bindValue(":event_id", id);

    if (query.exec()){
        while (query.next()){
            s = query.value(0).toString();
        }
        query.last();
    }
    return s;
}

QString EventDB::geteventtype(int id){
    QString s;
    QSqlQuery query(event_DB);
    query.prepare("SELECT event_type FROM event WHERE event_id = (:event_id)");
    query.bindValue(":event_id", id);

    if (query.exec()){
        while (query.next()){
            s = query.value(0).toString();
        }
        query.last();
    }
    return s;
}
QString EventDB::geteventtime(int id){
    QString s;
    QSqlQuery query(event_DB);
    query.prepare("SELECT event_time FROM event WHERE event_id = (:event_id)");
    query.bindValue(":event_id", id);

    if (query.exec()){
        while (query.next()){
            s = query.value(0).toString();
        }
        query.last();
    }
    return s;
}
QString EventDB::getlocation(int id){
    QString s;
    QSqlQuery query(event_DB);
    query.prepare("SELECT location FROM event WHERE event_id = (:event_id)");
    query.bindValue(":event_id", id);

    if (query.exec()){
        while (query.next()){
            s = query.value(0).toString();
        }
        query.last();
    }
    return s;
}
QString EventDB::getfrinstruction(int id){
    QString s;
    QSqlQuery query(event_DB);
    query.prepare("SELECT fr_instruction FROM event WHERE event_id = (:event_id)");
    query.bindValue(":event_id", id);

    if (query.exec()){
        while (query.next()){
            s = query.value(0).toString();
        }
        query.last();
    }
    return s;
}
QString EventDB::getpublicinstruction(int id){
    QString s;
    QSqlQuery query(event_DB);
    query.prepare("SELECT public_instruction FROM event WHERE event_id = (:event_id)");
    query.bindValue(":event_id", id);

    if (query.exec()){
        while (query.next()){
            s = query.value(0).toString();
        }
        query.last();
    }
    return s;
}
QString EventDB::getnotitime(int id){
    QString s;
    QSqlQuery query(event_DB);
    query.prepare("SELECT noti_time FROM event WHERE event_id = (:event_id)");
    query.bindValue(":event_id", id);

    if (query.exec()){
        while (query.next()){
            s = query.value(0).toString();
        }
        query.last();
    }
    return s;
}
QString EventDB::getverify(int id){
    QString s;
    QSqlQuery query(event_DB);
    query.prepare("SELECT verified FROM event WHERE event_id = (:event_id)");
    query.bindValue(":event_id", id);

    if (query.exec()){
        while (query.next()){
            s = query.value(0).toString();
        }
        query.last();
    }
    return s;
}



