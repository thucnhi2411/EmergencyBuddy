#include "firstresponderdb.h"


FirstResponderDB::FirstResponderDB(){
    QString connectionName("fr_connection");
    if (!QSqlDatabase::contains(connectionName)) {
        fr_DB = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    } else {
        fr_DB = QSqlDatabase::database(connectionName);
    }
    fr_DB.setDatabaseName("first_responder.sqlite");

    fr_DB.open();
    QSqlQuery query(fr_DB);
    query.exec("CREATE TABLE IF NOT EXISTS first_responder (user_id INTEGER UNIQUE, \
               name CHAR,\
               location CHAR,\
               meeting_location CHAR,\
               fr_role CHAR,\
               contact INT)");
}
FirstResponderDB::FirstResponderDB(const QString &path){
    QString connectionName("fr_connection");
    if (!QSqlDatabase::contains(connectionName)) {
        fr_DB = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    } else {
        fr_DB = QSqlDatabase::database(connectionName);
    }
    buildTable(path);
}
FirstResponderDB::~FirstResponderDB(){
    fr_DB.close();
}

bool FirstResponderDB::connected(){
    return fr_DB.isOpen();
}

bool FirstResponderDB::insert(int user_id, QString& name, QString& location,
                                QString& meeting_location, QString& fr_role, int contact){
    bool done = false;
    QSqlQuery query(fr_DB);
    query.prepare("INSERT INTO first_responder(user_id, name, location, meeting_location, fr_role, contact)"
                  "VALUES (:user_id, :name, :location, :meeting_location, :fr_role, :contact)");
    query.bindValue(":user_id", user_id);
    query.bindValue(":name", name);
    query.bindValue(":location", location);
    query.bindValue(":meeting_location", meeting_location);
    query.bindValue(":fr_role", fr_role);
    query.bindValue(":contact",contact);

    if (query.exec()){
        done = true;
    } else {
        qDebug()<< query.lastError();
    }
    return done;
}

bool FirstResponderDB::remove(int id){
    bool done = false;
    if (containID(id)){
        QSqlQuery query(fr_DB);
        query.prepare("DELETE FROM first_responder WHERE user_id = (:user_id)");
        query.bindValue(":user_id",id);
        if (query.exec()) done = true;

    }

    return done;
}

bool FirstResponderDB::updateLocation(int id, QString& new_location){
    bool done = false;
    if (containID(id)){
        QSqlQuery query(fr_DB);
        query.prepare("UPDATE first_responder SET location = (:location) WHERE user_id = (:user_id)");
        query.bindValue(":location",new_location);
        query.bindValue(":user_id",id);
        if (query.exec()) done = true;

    }

    return done;


}

bool FirstResponderDB::updateContact(int id, int new_contact){
    bool done = false;
    if (containID(id)){
        QSqlQuery query(fr_DB);
        query.prepare("UPDATE first_responder SET contact = (:contact) WHERE user_id = (:user_id)");
        query.bindValue(":contact",new_contact);
        query.bindValue(":user_id",id);
        if (query.exec()) done = true;

    }

    return done;


}

QString FirstResponderDB::retrieveID(int id){
    QString s;
    QSqlQuery query(fr_DB);
    query.prepare("SELECT * FROM first_responder WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

    if (query.exec()){
        while (query.next()){
            QString id = query.value(0).toString();
            QString name = query.value(1).toString();
            QString location = query.value(2).toString();
            QString meeting_location = query.value(3).toString();
            QString fr_role = query.value(4).toString();
            QString contact = query.value(5).toString();

            s.append(id);
            s.append(" ");
            s.append(name);
            s.append(" ");
            s.append(location);
            s.append(" ");
            s.append(meeting_location);
            s.append(" ");
            s.append(fr_role);
            s.append(" ");
            s.append(contact);
            s.append("\n");

        }
        query.last();
    }
    return s;
}
QString FirstResponderDB::retrieveTable(){
    QString s;
    QSqlQuery query(fr_DB);
    query.prepare("SELECT * FROM first_responder");

    if (query.exec()){
        while (query.next()){
            QString id = query.value(0).toString();
            QString name = query.value(1).toString();
            QString location = query.value(2).toString();
            QString meeting_location = query.value(3).toString();
            QString fr_role = query.value(4).toString();
            QString contact = query.value(5).toString();

            s.append(id);
            s.append(" ");
            s.append(name);
            s.append(" ");
            s.append(location);
            s.append(" ");
            s.append(meeting_location);
            s.append(" ");
            s.append(fr_role);
            s.append(" ");
            s.append(contact);
            s.append("\n");

        }
        query.last();
    }
    return s;
}
bool FirstResponderDB::containID(int id){
    bool contained = false;
    QSqlQuery query(fr_DB);
    query.prepare("SELECT user_id FROM first_responder WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

    if (query.exec()){
        if (query.next()){
            contained = true;
        }
    }
    return contained;
}
void FirstResponderDB::closeDB(){
    QSqlQuery query(fr_DB);
    query.exec("drop table if exists first_responder");
}
void FirstResponderDB::buildTable(const QString& path){
    fr_DB.setDatabaseName(path);
    fr_DB.open();
    QSqlQuery query(fr_DB);
    query.exec("CREATE TABLE IF NOT EXISTS first_responder (user_id INTEGER UNIQUE, \
               name CHAR,\
               location CHAR,\
               meeting_location CHAR,\
               fr_role CHAR,\
               contact INT)");
}

