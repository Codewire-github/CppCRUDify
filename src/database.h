#ifndef DATABASE_H
#define DATABASE_H

#include <mysqlx/xdevapi.h>

extern mysqlx::Session* session;

void initializeDatabase();
mysqlx::Session* getSession();

#endif
