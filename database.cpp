#include "database.h"

// Define the MySQL_Cursor object
MySQL_Cursor cursor;

// Define a function for executing a MySQL query
void executeQuery(MySQL_Connection *conn, String query) {
  // Create a MySQL_Cursor object and execute the query
  cursor = MySQL_Cursor(conn);
  cursor.execute(query);

  // Print the results of the query
  while (cursor.available()) {
    MySQL_Row row = cursor.getRow();
    for (int i = 0; i < row.fieldCount(); i++) {
      Serial.print(row.getField(i));
      Serial.print("\t");
    }
    Serial.println();
  }
}
