#include "simulationdb.h"

/**
 * @brief Default constructor SimulationDB
 */
SimulationDB::SimulationDB(){
    QString connectionName("sim_connection");
    if (!QSqlDatabase::contains(connectionName)) {
        simulation_DB = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    } else {
        simulation_DB = QSqlDatabase::database(connectionName);
    }
    simulation_DB.setDatabaseName("simulation.sqlite");
    simulation_DB.open();
    QSqlQuery query(simulation_DB);
    query.exec("CREATE TABLE IF NOT EXISTS simulation (simulation_id     INT NOT NULL UNIQUE,\
               name              CHAR NOT NULL,\
               event_type        CHAR NOT NULL,\
               event_time        CHAR NOT NULL,\
               location          CHAR NOT NULL,\
               instruction    CHAR NOT NULL) ");
}

SimulationDB::SimulationDB(const QString &path){
    QString connectionName("sim_connection");
    if (!QSqlDatabase::contains(connectionName)) {
        simulation_DB = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    } else {
        simulation_DB = QSqlDatabase::database(connectionName);
    }
    buildTable(path);
}
/**
 * @brief Default destructor ~SimulationDB
 */
SimulationDB::~SimulationDB(){
    simulation_DB.close();
}
/**
 * @brief   connected: Check whether the database is successfully connected
 * @return  whether connection is successful
 */
bool SimulationDB::connected(){
    return simulation_DB.isOpen();
}
/**
 * @brief   insert      Insert rows to table
 * @param   simulation_id       simulation id
 * @param   name                sim's name
 * @param   event_type          sim's location
 * @param   event_time          sim's time
 * @param   location            sim's location
 * @param   instruction      instruction
 * @return  whether insertion is successful
 */
bool SimulationDB::insert(int simulation_id, QString& name, QString& event_type,
                          QString& event_time, QString& location, QString& instruction){
    bool done = false;
    QSqlQuery query(simulation_DB);
    query.prepare("INSERT INTO simulation(simulation_id, name, event_type, event_time, location, instruction)"
                  "VALUES (:simulation_id, :name, :event_type, :event_time, :location, :instruction)");
    query.bindValue(":simulation_id", simulation_id);
    query.bindValue(":name", name);
    query.bindValue(":event_type", event_type);
    query.bindValue(":event_time", event_time);
    query.bindValue(":location", location);
    query.bindValue(":instruction",instruction);

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
bool SimulationDB::remove(int id){
    bool done = false;
    if (containID(id)){
        QSqlQuery query(simulation_DB);
        query.prepare("DELETE FROM simulation WHERE simulation_id = (:simulation_id)");
        query.bindValue(":simulation_id",id);
        if (query.exec()) done = true;

    }

    return done;
}

/**
 * @brief retrieveID    Retrieve row with id from table
 * @param id            id of the row to retrieve
 */
QString SimulationDB::retrieveID(int id){
    QString s;
    QSqlQuery query(simulation_DB);
    query.prepare("SELECT * FROM simulation WHERE simulation_id = (:simulation_id)");
    query.bindValue(":simulation_id", id);

    if (query.exec()){
        while (query.next()){
            QString simulation_id = query.value(0).toString();
            QString name = query.value(1).toString();
            QString event_type = query.value(2).toString();
            QString event_time = query.value(3).toString();
            QString location = query.value(4).toString();
            QString instruction_id = query.value(5).toString();

            s.append(simulation_id);
            s.append(" ");
            s.append(name);
            s.append(" ");
            s.append(event_type);
            s.append(" ");
            s.append(event_time);
            s.append(" ");
            s.append(location);
            s.append(" ");
            s.append(instruction_id);
            s.append("\n");

        }
        query.last();
    }
    return s;
}
/**
 * @brief retrieveTable Retrieve all rows in the table
 */
QString SimulationDB::retrieveTable(){
    QString s;
    QSqlQuery query(simulation_DB);
    query.prepare("SELECT * FROM simulation");

    if (query.exec()){
        while (query.next()){
            QString simulation_id = query.value(0).toString();
            QString name = query.value(1).toString();
            QString event_type = query.value(2).toString();
            QString event_time = query.value(3).toString();
            QString location = query.value(4).toString();
            QString instruction_id = query.value(5).toString();

            s.append(simulation_id);
            s.append(" ");
            s.append(name);
            s.append(" ");
            s.append(event_type);
            s.append(" ");
            s.append(event_time);
            s.append(" ");
            s.append(location);
            s.append(" ");
            s.append(instruction_id);
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
bool SimulationDB::containID(int id){
    bool contained = false;
    QSqlQuery query(simulation_DB);
    query.prepare("SELECT simulation_id FROM simulation WHERE simulation_id = (:simulation_id)");
    query.bindValue(":simulation_id", id);

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
void SimulationDB::closeDB(){
    QSqlQuery query(simulation_DB);
    query.exec("drop table if exists simulation");
}
/**
 * @brief buildTable    Build table with name
 * @param path          name of the table
 */
void SimulationDB::buildTable(const QString& path){
    simulation_DB.setDatabaseName(path);
    simulation_DB.open();
    QSqlQuery query(simulation_DB);
    query.exec("CREATE TABLE IF NOT EXISTS simulation (simulation_id     INT NOT NULL UNIQUE,\
               name              CHAR NOT NULL,\
               event_type        CHAR NOT NULL,\
               event_time        CHAR NOT NULL,\
               location          CHAR NOT NULL,\
               instruction    CHAR NOT NULL )");
}
