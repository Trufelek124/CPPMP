#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <sqlite3.h>
#include <iostream>

class DatabaseHelper
{
    public:
        DatabaseHelper();

        sqlite3* DB;
        int exit;

        //Creating tables
        void createTables();

        //Dropping tables
        void dropTables();

        //Data insertion
        void insertInitialData();

    protected:

    private:
};

#endif // DATABASEHELPER_H
