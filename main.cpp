//imported libraries
#include <iostream>
#include "sqlite/sqlite3.h"
#include <sstream>

using namespace std;

//Function is given an ID and pulls the ID's passwords from the database. Then, they are printed out.
void listPassword(sqlite3 *db, sqlite3_stmt *stmt, int id) {
    ostringstream oss;
    oss << id;
    string sql = "select pass from password where ID = " + oss.str(); //Concatenates int to string
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    //Prepares the sql statement to be run.
    const unsigned char *password;
    while (sqlite3_step(stmt) != SQLITE_DONE) { //Runs the sql statement line by line
        password = sqlite3_column_text(stmt, 0);
        cout << password << "\n"; //prints out the passwords;
    }
}

//Function saves the given password under the given ID.
void insertPassword(sqlite3 *db, int id, string password) {
    char *error;
    int rc;
    string query = "INSERT INTO password VALUES (" + to_string(id) + ", '" + password + "');";
    //Sql statement that inserts the ID and password into the password table of the database.
    rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
    if (rc != SQLITE_OK) { // runs sql statement
        cout << "error: " << error;// prints error if sql statement fails.
    }
}

//function is given an ID and creates an account for that ID.
void createAccount(sqlite3 *db, int id) {
    char *error;
    int rc;
    if (id == NULL) { // checks if there is any accounts made yet.
        id = 0;
    }
    string query = "INSERT INTO user VALUES (" + to_string(id) + ");";
    //sql statement inserts ID into user table of the database.
    rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
    if (rc != SQLITE_OK) { // runs sql statement.
        cout << "error: " << error;
    }
}

//function converts string values to boolean.
bool check(string c){
    bool status = true;
    while(status) {

        if (c == "yes") {
            return true;
        }
        if (c == "no") {
            return false;
        } else  //forces user to reenter an answer if the answer does not fit any if condition
            cout << "Reenter answer with yes or no." << "\n";
            cin >> c;
        }
    }


int main() {
    //Declares variables
    int IDnum;
    string start = "yes";
    string password;
    int choice;
    sqlite3 *db;
    sqlite3_stmt *stmt;

    //Opens the database
    sqlite3_open("passDB.db", &db);

    while (check(start)) {//loop to allow the user to start over
        cout << "How can I help you? Answer with the corresponding number." << "\n";
        cout << "   1. Create a new account" << "\n";
        cout << "   2. Check passwords" << "\n";
        cout << "   3. Add a password" << "\n";
        cin >> choice; //Asks user what function they want to use
        switch(choice) { //switch statement to switch to the function in use.
            case 1: { // Checks the number of user accounts and calls createAccount with the total number.
                // This creates a new account for the user.
                string sql = "select count(*) from user"; //sql statement checks the number of user accounts.
                sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0); //prepares sql statement.
                while (sqlite3_step(stmt) != SQLITE_DONE) { //runs sql statement.
                    IDnum = sqlite3_column_int(stmt, 0);
                    createAccount(db, IDnum);
                    cout << "This is your ID: " + to_string(IDnum) << "\n"; //prints out the new account's ID.
                }
                break;
            }
            case 2: {//receives ID from user and calls listPassword function with the given value.
                cout << "What is your ID?" << "\n";
                cin >> IDnum;
                cout<< "Passwords: " << "\n";
                listPassword(db, stmt, IDnum);
                break;
            }
            case 3: { //receives ID and password from user and calls insertPassword function with given values.
                cout << "What is your ID?" << "\n";
                cin >> IDnum;
                cout << "What password do you want to add?" << "\n";
                cin >> password;
                insertPassword(db, IDnum, password);

            }
            default: { //restarts or ends the loop once the function is finished.
                cout<< "Do you want to continue? Answer yes or no."<< "\n";
                cin >> start;
                continue;
            }
        }
        cout<< "Do you want to continue? Answer yes or no."<< "\n"; //restarts or ends the loop once the function is finished.
        cin >> start;
    }
    sqlite3_close(db); //closes database.
}


