#ifndef FIRSTRESPONDERDB_H
#define FIRSTRESPONDERDB_H


#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>
#include <QString>

/**
 * @brief The FirstResponder_DB class
 * Create an sqlite3 table "first_responder"
 * user_id           INT NOT NULL UNIQUE,
 * name              CHAR NOT NULL,
 * location          CHAR NOT NULL,
 * meeting_location  CHAR NOT NULL,
 * fr_role           CHAR NOT NULL,
 * contact           INT NOT NULL
 */
class FirstResponderDB
{
public:
    /**
     * @brief Default constructor FirstResponderDB
     */
    FirstResponderDB();
    FirstResponderDB(const QString& path);

    // the first_responder database
    QSqlDatabase fr_DB;

    /**
     * @brief Default destructor ~FirstResponderDB
     */
    ~FirstResponderDB();
    /**
     * @brief   connected: Check whether the database is successfully connected
     * @return  whether connection is successful
     */
    bool connected();
    /**
     * @brief   insert      Insert rows to table
     * @param   user_id     user id
     * @param   name        fr's name
     * @param   location    fr's location
     * @param   meeting_location fr's meeting location
     * @param   fr_role     fr's role
     * @param   contact     fr's contact
     * @return  whether insertion is successful
     */
    bool insert(int user_id, QString& name, QString& location, QString& meeting_location, QString& fr_role, int contact);

    /**
     * @brief   remove      Remove row with id from table
     * @param   id          id of the row to remove
     * @return  whether removal is successful
     */
    bool remove(int id);
    /**
     * @brief updateLocation Update location with id
     * @param id             id
     * @param new_location   new location
     * @return               whether updating is successful
     */
    bool updateLocation(int id, QString& new_location);
    /**
     * @brief updateContact Update new contact with id
     * @param id            id
     * @param new_contact   new contact
     * @return              whether updating is successful
     */
    bool updateContact(int id, int new_contact);

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

#endif // FIRSTRESPONDERDB_H
