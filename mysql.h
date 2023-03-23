#ifndef mysqlh_h
#define mysqlh_h

#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// MySQL Connection and Cursor objects
WiFiClient client;
MySQL_Connection conn((Client *)&client);
MySQL_Cursor *cursor;

// Database parameters
IPAddress server_addr(197,136,96,14/); // IP address of the MySQL server
char user[] = "username"; // MySQL username
char password[] = "password"; // MySQL password
char database[] = "database_name"; // MySQL database name

// Function for connecting to the MySQL database
bool connectToMySQL() {
  bool connected = false;
  
  // Try to connect to the MySQL server
  if (conn.connect(server_addr, 3306, user, password, database)) {
    Serial.println("Connected to MySQL server successfully.");
    connected = true;
  } else {
    Serial.println("Failed to connect to MySQL server.");
  }
  
  return connected;
}

// Function for executing a SELECT query on the MySQL database
void executeQuery(String query) {
  // Initialize the cursor object
  cursor = new MySQL_Cursor(&conn);
  
  // Execute the query
  cursor->execute(query);
  
  // Get the number of rows in the result set
  int rows = cursor->get_num_rows();
  
  // Print the results to the Serial Monitor
  for (int i = 0; i < rows; i++) {
    cursor->next();
    Serial.println(cursor->getString(1));
  }
  
  // Close the cursor object
  delete cursor;
}

#endif
