#include "userdb.h"

UserDB::UserDB()
{
    QString connectionName("user_connection");

    if (!QSqlDatabase::contains(connectionName)) {
        user_DB = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    } else {
        user_DB = QSqlDatabase::database(connectionName);

    }

    user_DB.setDatabaseName("user.sqlite");
    user_DB.open();
    QSqlQuery query(user_DB);
    query.exec("CREATE TABLE IF NOT EXISTS user (user_id INTEGER UNIQUE, \
               role CHAR,\
               name CHAR,\
               username CHAR,\
               location CHAR,\
               contact INT)");
}

UserDB::UserDB(const QString &path){
    QString connectionName("user_connection");

    if (!QSqlDatabase::contains(connectionName)) {
        user_DB = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    } else {
        user_DB = QSqlDatabase::database(connectionName);

    }
    buildTable(path);
}

UserDB::~UserDB(){
    user_DB.close();
}

bool UserDB::connected(){
    return user_DB.isOpen();
}

bool UserDB::insert(int user_id, QString& role, QString& name,
                    QString& username, QString& location, int contact){
    bool done = false;
    QSqlQuery query(user_DB);
    query.prepare("INSERT INTO user(user_id, role, name, username, location, contact)"
                  "VALUES (:user_id, :role, :name, :username, :location, :contact)");
    query.bindValue(":user_id", user_id);
    query.bindValue(":role", role);
    query.bindValue(":name", name);
    query.bindValue(":username", username);
    query.bindValue(":location", location);
    query.bindValue(":contact",contact);

    if (query.exec()){
        done = true;
    } else {
        qDebug()<< query.lastError();
    }
    return done;
}

bool UserDB::remove(int id){
    bool done = false;
    if (containID(id)){
        QSqlQuery query(user_DB);
        query.prepare("DELETE FROM user WHERE user_id = (:user_id)");
        query.bindValue(":user_id",id);
        if (query.exec()) done = true;

    }

    return done;


}

bool UserDB::updateLocation(int id, QString& new_location){
    bool done = false;
    if (containID(id)){
        QSqlQuery query(user_DB);
        query.prepare("UPDATE user SET location = (:location) WHERE user_id = (:user_id)");
        query.bindValue(":location",new_location);
        query.bindValue(":user_id",id);
        if (query.exec()) done = true;

    }

    return done;


}

bool UserDB::updateContact(int id, int new_contact){
    bool done = false;
    if (containID(id)){
        QSqlQuery query(user_DB);
        query.prepare("UPDATE user SET contact = (:contact) WHERE user_id = (:user_id)");
        query.bindValue(":contact",new_contact);
        query.bindValue(":user_id",id);
        if (query.exec()) done = true;

    }

    return done;


}

QString UserDB::retrieveID(int id){
    QString s;
    QSqlQuery query(user_DB);
    query.prepare("SELECT * FROM user WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

    if (query.exec()){
        while (query.next()){
            QString id = query.value(0).toString();
            QString role = query.value(1).toString();
            QString name = query.value(2).toString();
            QString username = query.value(3).toString();
            QString location = query.value(4).toString();
            QString contact = query.value(5).toString();

            s.append(id);
            s.append(" ");
            s.append(role);
            s.append(" ");
            s.append(name);
            s.append(" ");
            s.append(username);
            s.append(" ");
            s.append(location);
            s.append(" ");
            s.append(contact);
            s.append("\n");


        }
        query.last();
    }
    return s;
}

QString UserDB::retrieveTable(){
    QString s;
    QSqlQuery query(user_DB);
    query.prepare("SELECT * FROM user");

    if (query.exec()){
        while (query.next()){
            QString id = query.value(0).toString();
            QString role = query.value(1).toString();
            QString name = query.value(2).toString();
            QString username = query.value(3).toString();
            QString location = query.value(4).toString();
            QString contact = query.value(5).toString();

            s.append(id);
            s.append(" ");
            s.append(role);
            s.append(" ");
            s.append(name);
            s.append(" ");
            s.append(username);
            s.append(" ");
            s.append(location);
            s.append(" ");
            s.append(contact);
            s.append("\n");


        }
        query.last();
    }
    return s;

}

bool UserDB::containID(int id){
    bool contained = false;
    QSqlQuery query(user_DB);
    query.prepare("SELECT user_id FROM user WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

    if (query.exec()){
        if (query.next()){
            contained = true;
        }
    }
    return contained;
}

bool UserDB::containUsername(QString& username){
    bool contained = false;
    QSqlQuery query(user_DB);
    query.prepare("SELECT username FROM user WHERE username = (:username)");
    query.bindValue(":username", username);

    if (query.exec()){
        if (query.next()){
            contained = true;
        }
    }
    return contained;
}

void UserDB::closeDB(){
    QSqlQuery query(user_DB);
    query.exec("drop table if exists user");

}

void UserDB::buildTable(const QString& path){
    user_DB.setDatabaseName(path);
    user_DB.open();
    QSqlQuery query(user_DB);
    query.exec("CREATE TABLE IF NOT EXISTS user (user_id INTEGER UNIQUE, \
               role CHAR,\
               name CHAR,\
               username CHAR,\
               location CHAR,\
               contact INT)");
}

int UserDB::rowCount(){
    int sum = 0;
    QSqlQuery query(user_DB);
    query.prepare("SELECT * FROM user");

    if (query.exec()){
        while (query.next()){
            sum++;
        }
    }
    return sum;
}

/**
 * @brief retrieveRole  get user's role
 * @param id            user's id
 * @return              user's role
 */
QString UserDB::retrieveRole(int id){
    QString role;
    QSqlQuery query(user_DB);
    query.prepare("SELECT role FROM user WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

    if (query.exec()){
        if (query.next()){
            role = query.value(0).toString();
        }
    }
    return role;
}

QString UserDB::getname(int id){
    QString role;
    QSqlQuery query(user_DB);
    query.prepare("SELECT name FROM user WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

    if (query.exec()){
        if (query.next()){
            role = query.value(0).toString();
        }
    }
    return role;
}
QString UserDB::getusername(int id){
    QString role;
    QSqlQuery query(user_DB);
    query.prepare("SELECT username FROM user WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

    if (query.exec()){
        if (query.next()){
            role = query.value(0).toString();
        }
    }
    return role;
}
QString UserDB::getlocation(int id){
    QString role;
    QSqlQuery query(user_DB);
    query.prepare("SELECT location FROM user WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

    if (query.exec()){
        if (query.next()){
            role = query.value(0).toString();
        }
    }
    return role;
}
QString UserDB::getcontact(int id){
    QString role;
    QSqlQuery query(user_DB);
    query.prepare("SELECT contact FROM user WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

    if (query.exec()){
        if (query.next()){
            role = query.value(0).toString();
        }
    }
    return role;
}

int UserDB::getID(QString& name){
    int role = -1;
    QSqlQuery query(user_DB);
    query.prepare("SELECT user_id FROM user WHERE name = (:name)");
    query.bindValue(":name", name);

    if (query.exec()){
        if (query.next()){
            role = query.value(0).toInt();
        }
    }
    return role;
}
