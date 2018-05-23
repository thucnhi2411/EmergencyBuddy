#ifndef EVENTDB_H
#define EVENTDB_H

#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>
#include <QString>

/**
 * @brief The EventDB class
 * event_id          INT NOT NULL, UNIQUE
 * name              CHAR NOT NULL
 * event_type        CHAR NOT NULL
 * event_time        CHAR NOT NULL
 * location          CHAR NOT NULL
 * fr_instruction    CHAR
 * public_instruction CHAR
 * noti_time         CHAR
 * verified          INT
 */
class EventDB
{
public:

    /**
     * @brief Default constructor UpcomingEventDB
     */
    EventDB();
    EventDB(const QString& path);
    // the simulation database
    QSqlDatabase event_DB;


    /**
     * @brief Default destructor ~UpcomingEventDB
     */
    ~EventDB();
    /**
     * @brief   connected: Check whether the database is successfully connected
     * @return  whether connection is successful
     */
    bool connected();
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
     * @return  whether insertion is successful
     */
    bool insert(int event_id, QString& name, QString& event_type, QString& event_time,
                                 QString& location, QString& fr_instruction, QString& public_instruction, QString& noti_time, int verified);

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
     * @brief updateVerified Verify
     * @param id             the id of the event to verified
     * @return               whether the update process is succeeded
     */
    bool updateVerified(int id);
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
     * @brief rowCount
     * @return number of row
     */
    int rowCount();

    QString getname(int id);
    QString geteventtype(int id);
    QString geteventtime(int id);
    QString getlocation(int id);
    QString getfrinstruction(int id);
    QString getpublicinstruction(int id);
    QString getnotitime(int id);
    QString getverify(int id);
};

#endif // EVENTDB_H
