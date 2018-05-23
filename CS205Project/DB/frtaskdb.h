#ifndef FRTASKDB_H
#define FRTASKDB_H

#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>
#include <QString>

/**
 * @brief The FrTaskDB class
 * event_id          INT NOT NULL
 * user_id           INT NOT NULL
 * instruction       CHAR
 * priority          INT NOT NULL
 * feedback          CHAR
 */
class FrTaskDB
{
public:


    // first_responder_task database
    QSqlDatabase fr_task_DB;
    /**
     * @brief FrTaskDB    Default constructor
     */

    FrTaskDB();
    FrTaskDB(const QString& path);
    /**
     * @brief Default destructor ~FrTaskDB
     */
    ~FrTaskDB();

    /**
     * @brief   connected Check whether the database is successfully connected
     * @return  whether connection is successful
     */
    bool connected();

    /**
     * @brief insert    Insert new row into the table
     * @param event_id  event's id
     * @param user_id   user's id (not unique because a fr can have multiple tasks)
     * @param instruction    instruction
     * @param priority  priority for ordering
     * @param feedback  feedback of the event
     * @return          whether insertion is successful
     */
    bool insert(int event_id, int user_id, QString& instruction, int priority, QString &feedback);
    /**
     * @brief   removeFr    Remove rows with id from table
     * @param   id          id of the fr to remove
     * @return  whether removal is successful
     */
    bool removeFr(int user_id);
    /**
     * @brief removeFrTask  Remove tasks of a specific responder
     * @param user_id       user'sid
     * @param instruction   instruction
     * @return              whether removal is successful
     */
    bool removeFrTask(int user_id, QString& instruction);

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
    /**
     * @brief updateFeedback
     * @param event_id  event's id
     * @param user_id   user's id
     * @param instr  instr
     * @param feedback  feedback to update
     */
    void updateFeedback(int event_id, int user_id, QString& instr_id, QString& feedback);
    void openTable();
    int rowcount();

    QString getinstr(int id);

    QString getfb(int id);

    QString getprio(int id);
};

#endif // FRTASKDB_H
