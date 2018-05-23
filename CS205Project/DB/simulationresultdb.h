#ifndef SIMULATIONRESULTDB_H
#define SIMULATIONRESULTDB_H
#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>
#include <QString>

/**
 * @brief The SimulationResultDB class
 * simulation_id     INT NOT NULL UNIQUE
 * result            CHAR NOT NULL
 * description       CHAR NOT NULL
 */
class SimulationResultDB
{
public:

    /**
     * @brief Default constructor SimulationResultDB
     */
    SimulationResultDB();
    SimulationResultDB(const QString& path);
    // the simulation result database
    QSqlDatabase simulationR_DB;

    /**
     * @brief Default destructor ~SimulationResultDB
     */
    ~SimulationResultDB();
    /**
     * @brief   connected: Check whether the database is successfully connected
     * @return  whether connection is successful
     */
    bool connected();
    /**
     * @brief   insert      Insert rows to table
     * @param   simulation_id       simulation id
     * @param   result              simulation result
     * @param   description         simulation description
     * @return  whether insertion is successful
     */
    bool insert(int simulation_id, QString& result, QString& description);

    /**
     * @brief   remove      Remove row with id from table
     * @param   id          id of the row to remove
     * @return  whether removal is successful
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

#endif // SIMULATIONRESULTDB_H
