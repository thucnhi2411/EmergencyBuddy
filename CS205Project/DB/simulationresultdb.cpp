#include "simulationresultdb.h"


/**
 * @brief Default constructor SimulationResultDB
 */
SimulationResultDB::SimulationResultDB(){
    QString connectionName("simRconnection");
    if (!QSqlDatabase::contains(connectionName)) {
        simulationR_DB = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    } else {
        simulationR_DB = QSqlDatabase::database(connectionName);
    }

    simulationR_DB.setDatabaseName("simulation_result.sqlite");
    simulationR_DB.open();
    QSqlQuery query(simulationR_DB);
    query.exec("CREATE TABLE IF NOT EXISTS simulation_result (simulation_id     INT NOT NULL UNIQUE,\
               result            CHAR NOT NULL,\
               description       CHAR NOT NULL )");
}

SimulationResultDB::SimulationResultDB(const QString &path){
    QString connectionName("simRconnection");
    if (!QSqlDatabase::contains(connectionName)) {
        simulationR_DB = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    } else {
        simulationR_DB = QSqlDatabase::database(connectionName);
    }
    buildTable(path);
}

/**
 * @brief Default destructor ~SimulationResultDB
 */
SimulationResultDB::~SimulationResultDB(){
    simulationR_DB.close();
}
/**
 * @brief   connected: Check whether the database is successfully connected
 * @return  whether connection is successful
 */
bool SimulationResultDB::connected(){
    return simulationR_DB.isOpen();
}
/**
 * @brief   insert      Insert rows to table
 * @param   simulation_id       simulation id
 * @param   result              simulation result
 * @param   description         simulation description
 * @return  whether insertion is successful
 */
bool SimulationResultDB::insert(int simulation_id, QString& result, QString& description){
    bool done = false;
    QSqlQuery query(simulationR_DB);
    query.prepare("INSERT INTO simulation_result(simulation_id, result, description)"
                  "VALUES (:simulation_id, :result, :description)");
    query.bindValue(":simulation_id", simulation_id);
    query.bindValue(":result", result);
    query.bindValue(":description", description);

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

QString SimulationResultDB::retrieveID(int id){
    QString s;
    QSqlQuery query(simulationR_DB);
    query.prepare("SELECT * FROM simulation_result WHERE simulation_id = (:simulation_id)");
    query.bindValue(":simulation_id", id);

    if (query.exec()){
        while (query.next()){
            QString simulation_id = query.value(0).toString();
            QString result = query.value(1).toString();
            QString description = query.value(2).toString();

            s.append(simulation_id);
            s.append(" ");
            s.append(result);
            s.append(" ");
            s.append(description);
            s.append("\n");

        }
        query.last();
    }
    return s;
}
/**
 * @brief retrieveTable Retrieve all rows in the table
 */
QString SimulationResultDB::retrieveTable(){
    QString s;
    QSqlQuery query(simulationR_DB);
    query.prepare("SELECT * FROM simulation_result");

    if (query.exec()){
        while (query.next()){
            QString simulation_id = query.value(0).toString();
            QString result = query.value(1).toString();
            QString description = query.value(2).toString();

            s.append(simulation_id);
            s.append(" ");
            s.append(result);
            s.append(" ");
            s.append(description);
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
bool SimulationResultDB::containID(int id){
    bool contained = false;
    QSqlQuery query(simulationR_DB);
    query.prepare("SELECT simulation_id FROM simulation_result WHERE simulation_id = (:simulation_id)");
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
void SimulationResultDB::closeDB(){
    QSqlQuery query(simulationR_DB);
    query.exec("drop table if exists simulation_result");
}
/**
 * @brief buildTable    Build table with name
 * @param path          name of the table
 */
void SimulationResultDB::buildTable(const QString& path){
    simulationR_DB.setDatabaseName(path);
    simulationR_DB.open();
    QSqlQuery query(simulationR_DB);
    query.exec("CREATE TABLE IF NOT EXISTS simulation_result (simulation_id     INT NOT NULL UNIQUE,\
               result            CHAR NOT NULL,\
               description       CHAR NOT NULL )");
}
