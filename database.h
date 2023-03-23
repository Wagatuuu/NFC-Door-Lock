#ifndef DATABASE_H
#define DATABASE_H

// Include the necessary libraries
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Define the database connection parameters
IPAddress server_addr(197,136,96.14);
char user[] = "username";
char password[] = "password";
char database[] = "database_name";

// Declare a function for establishing a database connection
bool connectToDatabase(MySQL_Connection *conn) {
  WiFiClient client;
  return conn->connect(server_addr, 3306, user, password);
}

#endif // DATABASE_H
