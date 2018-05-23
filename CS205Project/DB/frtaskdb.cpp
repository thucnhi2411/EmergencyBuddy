#include "frtaskdb.h"

/**
 * @brief FrTaskDB  Constructor with path
 */

FrTaskDB::FrTaskDB(){
    QString connectionName("frtask_connection");
    if (!QSqlDatabase::contains(connectionName)) {
        fr_task_DB = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    } else {
        fr_task_DB = QSqlDatabase::database(connectionName);
    }

    fr_task_DB.setDatabaseName("fr_task.sqlite");
    fr_task_DB.open();

    QSqlQuery query(fr_task_DB);
    query.exec("CREATE TABLE IF NOT EXISTS  fr_task (\
               event_id			INT NOT NULL,\
               user_id           INT NOT NULL,\
               instruction     CHAR NOT NULL,\
               priority          INT NOT NULL,\
               feedback			CHAR        );");

}

FrTaskDB::FrTaskDB(const QString& path){
    QString connectionName("frtask_connection");
    if (!QSqlDatabase::contains(connectionName)) {
        fr_task_DB = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    } else {
        fr_task_DB = QSqlDatabase::database(connectionName);
    }
    buildTable(path);
}
/**
 * @brief Default destructor ~FrTaskDB
 */
FrTaskDB::~FrTaskDB(){
    fr_task_DB.close();
}

/**
 * @brief   connected Check whether the database is successfully connected
 * @return  whether connection is successful
 */
bool FrTaskDB::connected(){
    return fr_task_DB.isOpen();
}

/**
 * @brief insert    Insert new row into the table
 * @param event_id  event's id
 * @param user_id   user's id (not unique because a fr can have multiple tasks)
 * @param instruction   instruction
 * @param priority  priority for ordering
 * @param feedback  feedback of the event
 * @return          whether insertion is successful
 */
bool FrTaskDB::insert(int event_id, int user_id, QString& instruction, int priority, QString &feedback){
    bool done = false;
    QSqlQuery query(fr_task_DB);
    query.prepare("INSERT INTO fr_task(event_id, user_id, instruction, priority, feedback)"
                  "VALUES (:event_id, :user_id, :instruction, :priority, :feedback)");
    query.bindValue(":event_id", event_id);
    query.bindValue(":user_id", user_id);
    query.bindValue(":instruction", instruction);
    query.bindValue(":priority", priority);
    query.bindValue(":feedback", feedback);
    if (query.exec()){
        done = true;
    } else {
        qDebug()<< query.lastError();
    }
    return done;
}

/**
 * @brief   removeFr    Remove rows with id from table
 * @param   id          id of the fr to remove
 * @return  whether removal is successful
 */
bool FrTaskDB::removeFr(int user_id){
    bool done = false;
    if (containID(user_id)){
        QSqlQuery query(fr_task_DB);
        query.prepare("DELETE FROM fr_task WHERE user_id = (:user_id)");
        query.bindValue(":user_id",user_id);
        if (query.exec()) done = true;
    }

    return done;
}
/**
 * @brief removeFrTask  Remove tasks of a specific responder
 * @param user_id       user'sid
 * @param instruction   instruction
 * @return              whether removal is successful
 */
bool FrTaskDB::removeFrTask(int user_id, QString& instruction){
    bool done = false;
    if (containID(user_id)){
        QSqlQuery query(fr_task_DB);
        query.prepare("DELETE FROM fr_task WHERE user_id = (:user_id) AND instruction = (:instruction)");
        query.bindValue(":user_id",user_id);
        query.bindValue(":instruction",instruction);
        if (query.exec()) done = true;

    }

    return done;
}

/**
 * @brief retrieveID    Retrieve row with id from table
 * @param id            id of the row to retrieve
 */
QString FrTaskDB::retrieveID(int id){
    QString s;
    QSqlQuery query(fr_task_DB);
    query.prepare("SELECT * FROM fr_task WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

    if (query.exec()){
        while (query.next()){
            QString event_id = query.value(0).toString();
            QString user_id = query.value(1).toString();
            QString instruction = query.value(2).toString();
            QString priority = query.value(3).toString();
            QString feedback = query.value(4).toString();
            s.append(event_id);
            s.append(" ");
            s.append(user_id);
            s.append(" ");
            s.append(instruction);
            s.append(" ");
            s.append(priority);
            s.append(" ");
            s.append(feedback);
            s.append("\n");

        }
        query.last();
    }
    return s;
}

/**
 * @brief retrieveTable Retrieve all rows in the table
 */
QString FrTaskDB::retrieveTable(){
    QString s;
    QSqlQuery query(fr_task_DB);
    query.prepare("SELECT * FROM fr_task");

    if (query.exec()){
        while (query.next()){
            QString event_id = query.value(0).toString();
            QString user_id = query.value(1).toString();
            QString instruction_id = query.value(2).toString();
            QString priority = query.value(3).toString();
            QString feedback = query.value(4).toString();
            s.append(event_id);
            s.append(" ");
            s.append(user_id);
            s.append(" ");
            s.append(instruction_id);
            s.append(" ");
            s.append(priority);
            s.append(" ");
            s.append(feedback);
            s.append("\n");

        }
        query.last();
    }
    return s;
}

/**
 * @brief   containID   Check whether the id is in the table
 * @param   id          The id to check
 * @return  whether the id exists
 */
bool FrTaskDB::containID(int id){
    bool contained = false;
    QSqlQuery query(fr_task_DB);
    query.prepare("SELECT user_id FROM fr_task WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

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
void FrTaskDB::closeDB(){
    QSqlQuery query(fr_task_DB);
    query.exec("drop table if exists fr_task");
}
/**
 * @brief buildTable    Build table with name
 * @param path          name of the table
 */
void FrTaskDB::buildTable(const QString& path){
    fr_task_DB.setDatabaseName(path);
    fr_task_DB.open();
    QSqlQuery query(fr_task_DB);
    query.exec("CREATE TABLE IF NOT EXISTS  fr_task (\
               event_id			INT NOT NULL,\
               user_id           INT NOT NULL,\
               instruction    CHAR NOT NULL,\
               priority          INT NOT NULL,\
               feedback			CHAR        );");
}

/**
 * @brief updateFeedback
 * @param event_id  event's id
 * @param user_id   user's id
 * @param instr_id  instr's id
 * @param feedback  feedback to update
 */
void FrTaskDB::updateFeedback(int event_id, int user_id, QString& instr_id, QString& feedback){
    if (containID(user_id)){
        QSqlQuery query(fr_task_DB);
        query.prepare("UPDATE fr_task SET feedback = (:feedback) WHERE event_id = (:event_id)"
                      "AND user_id = (:user_id) AND instruction = (:instruction)");
        query.bindValue(":feedback", feedback);
        query.bindValue(":event_id", event_id);
        query.bindValue(":user_id", user_id);
        query.bindValue(":instruction", instr_id);
        query.exec();
    }
}


QString FrTaskDB::getfb(int id){
    QString s;
    QSqlQuery query(fr_task_DB);
    query.prepare("SELECT * FROM fr_task WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

    if (query.exec()){
        while (query.next()){
            QString feedback = query.value(4).toString();

            s=feedback;

        }
        query.last();
    }
    return s;
}

QString FrTaskDB::getinstr(int id){
    QString s;
    QSqlQuery query(fr_task_DB);
    query.prepare("SELECT * FROM fr_task WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

    if (query.exec()){
        while (query.next()){
            QString instruction = query.value(2).toString();

            s=instruction;

        }
        query.last();
    }
    return s;
}

QString FrTaskDB::getprio(int id){
    QString s;
    QSqlQuery query(fr_task_DB);
    query.prepare("SELECT * FROM fr_task WHERE user_id = (:user_id)");
    query.bindValue(":user_id", id);

    if (query.exec()){
        while (query.next()){
            QString priority = query.value(3).toString();

            s=priority;

        }
        query.last();
    }
    return s;
}



int FrTaskDB::rowcount(){
    int sum = 0;
    QSqlQuery query(fr_task_DB);
    query.prepare("SELECT * FROM fr_task");

    if (query.exec()){
        while (query.next()){
            sum++;
        }
    }
    return sum;
}
