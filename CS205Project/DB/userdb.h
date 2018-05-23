#ifndef USERDB_H
#define USERDB_H

#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>
#include <QString>

/**
 * @brief The UserDB class
 *
 * Create an sqlite3 table "user"
 * user_id           INT NOT NULL UNIQUE
 * role              CHAR NOT NULL
 * name              CHAR NOT NULL
 * username          CHAR NOT NULL
 * location          CHAR NOT NULL
 * contact           INT NOT NULL
 */
class UserDB
{
public:

    // user database
    QSqlDatabase user_DB;
    /**
     * @brief UserDB    Default constructor
     */

    UserDB();
    UserDB(const QString& path);

    /**
     * @brief Default destructor ~UserDB
     */
    ~UserDB();

    /**
     * @brief   connected Check whether the database is successfully connected
     * @return  whether connection is successful
     */
    bool connected();

    /**
     * @brief insert    Insert row to the table
     * @param user_id   user's id
     * @param role      user's role (planner/first responder/public)
     * @param name      user's name
     * @param username  user's username
     * @param location  user's location
     * @param contact   user's contact
     * @return          whether insertion is successful
     */
    bool insert(int user_id, QString& role, QString& name, QString& username, QString& location, int contact);
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
     * @brief   containUsername   Check whether the username is in the table
     * @param   username          The username to check
     * @return  whether the id exists
     */
    bool containUsername(QString& username);
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
    /**
     * @brief retrieveRole  get user's role
     * @param id            user's id
     * @return              user's role
     */
    QString retrieveRole(int id);
    QString getname(int id);
    QString getusername(int id);
    QString getlocation(int id);
    QString getcontact(int id);
    int getID(QString& name);

};

#endif // USERDB_H
