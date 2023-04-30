#include <iostream>
#include "sqlite/sqlite3.h"
#include <sstream>

using namespace std;

bool listPassword(sqlite3 *db, sqlite3_stmt *stmt, int id) {
    ostringstream oss;
    oss << id;
    string sql = "select pass from password where ID = " + oss.str();
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    const unsigned char *password;
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        password = sqlite3_column_text(stmt, 0);
        cout << password << "\n";
    }
    return true;
}

string insertPassword(sqlite3 *db, int id, string password) {
    char *error;
    int rc;
    string query = "INSERT INTO password VALUES (" + to_string(id) + ", '" + password + "');";
    rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
    if (rc != SQLITE_OK) {
        cout << "error: " << error;
    }
}

bool createAccount(sqlite3 *db, int id) {
    char *error;
    int rc;
    if (id == NULL) {
        id = 0;
    }
    string query = "INSERT INTO user VALUES (" + to_string(id) + ");";
    rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
    if (rc != SQLITE_OK) {
        cout << "error: " << error;
    }
}

bool check(string c){
    bool status = true;
    while(status) {

        if (c == "yes") {
            return true;
        }
        if (c == "no") {
            return false;
        } else {
            cout << "Reenter answer with yes or no." << "\n";
            cin >> c;
        }
    }
}

int main() {
    int IDnum;
    string choice;
    string start = "yes";
    string password;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_open("passDB.db", &db);
    while (check(start)) {
        cout << "Are you creating a new account?" << "\n";
        cin >> choice;
        if (check(choice)) {
            string sql = "select count(*) from user";
            sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
            while (sqlite3_step(stmt) != SQLITE_DONE) {
                IDnum = sqlite3_column_int(stmt, 0);
                createAccount(db, IDnum);
                cout << "This is your ID: " + to_string(IDnum) << "\n";
            }
        }
        cout << "Do you want to see your passwords?" << "\n";
        cin >> choice;
        if (check(choice)) {
            cout << "What is your ID?" << "\n";
            cin >> IDnum;
            listPassword(db, stmt, IDnum);
        }
        cout << "Do you want to add a password?" << "\n";
        cin >> choice;
        if (check(choice)) {
            cout << "What is your ID?" << "\n";
            cin >> IDnum;
            cout << "What password do you want to add?" << "\n";
            cin >> password;
            insertPassword(db, IDnum, password);
        }
        cout<< "Do you want to continue?"<< "\n";
        cin >> start;
    }


    sqlite3_close(db);

}


