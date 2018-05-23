#ifndef SIMULATIONDB_H
#define SIMULATIONDB_H
#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>
#include <QString>


/**
 * @brief The SimulationDB class
 * simulation_id     INT NOT NULL UNIQUE
 * name              CHAR NOT NULL,
 * event_type        CHAR NOT NULL,
 * event_time        CHAR NOT NULL,
 * location          CHAR NOT NULL
 * instruction    CHAR NOT NULL
 */
class SimulationDB
{
public:    
    /**
     * @brief Default constructor SimulationDB
     */
    SimulationDB();
    SimulationDB(const QString& path);
    // the simulation database
    QSqlDatabase simulation_DB;

    /**
     * @brief Default destructor ~SimulationDB
     */
    ~SimulationDB();
    /**
     * @brief   connected: Check whether the database is successfully connected
     * @return  whether connection is successful
     */
    bool connected();
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
    bool insert(int simulation_id, QString& name, QString& event_type, QString& event_time, QString& location, QString& instruction);

    /**
     * @brief   remove      Remove row with id from table
     * @param   id          id of the row to remove
     * @return  whether removal is successful
     */
    bool remove(int id);

    /**
     * @brief retrieveID    Retrieve row with id from table
     * @param id            id of the row to retrieve
     */
    QString retrieveID(int id);
    /**
     * @brief retrieveTable Retrieve all rows in the table
     */
    QString retrieveTable();

    /**
     * @brief   containID   Check whether the id is in the table
     * @param   id          The id to check
     * @return  whether the id exists
     */
    bool containID(int id);
    /**
     * @brief closeDB       Drop table
     */
    void closeDB();
    /**
     * @brief buildTable    Build table with name
     * @param path          name of the table
     */
    void buildTable(const QString& path);
};

#endif // SIMULATIONDB_H
