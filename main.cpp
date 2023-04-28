#include <iostream>
#include "sqlite/sqlite3.h"
#include <sstream>
using namespace std;

bool listPassword(sqlite3* db,sqlite3_stmt* stmt, int id){
    ostringstream oss;
    oss << id;
    cout << id;
    string sql = "select pass from password where ID = " + oss.str();
    sqlite3_prepare_v2(db, sql.c_str() , -1, &stmt, 0);

    const unsigned char* password;
    while(sqlite3_step(stmt) != SQLITE_DONE){
        password = sqlite3_column_text(stmt,0);
        cout << password << "\n";
    }
    return true;
}

string insertPassword(sqlite3 *db, int id, string password) {
    char* error;
    int rc;
    string query = "INSERT INTO password VALUES (" + to_string(id) + ", '" +  password  +"');";
    rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
    if(rc != SQLITE_OK){
        cout<< "error: " << error;
    }
}

bool createAccount(sqlite3 *db, int id){
    char* error;
    int rc;
    if(id == NULL){
        id = 0;
    }
    string query = "INSERT INTO user VALUES (" + to_string(id) + ");";
    rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
    if(rc != SQLITE_OK){
        cout<< "error: " << error;
    }
}

int main() {
    char* error;
    int IDnum;
    bool choice;
    int rc;
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("passDB.db", &db);

    cout << "Are you creating a new account?"<< "\n";
    cin >> choice;
    if(choice){
        string sql = "select count(*) from user";
        sqlite3_prepare_v2(db, sql.c_str() , -1, &stmt, 0);
        while(sqlite3_step(stmt) != SQLITE_DONE){
            IDnum = sqlite3_column_int(stmt,0);
            createAccount(db, IDnum );
            cout<< "This is your ID: " +  to_string(IDnum)<< "\n";
        }
    }else{
        cout << "What is your ID?";
        cin >> IDnum;
        listPassword(db, stmt, IDnum);
    }










/*
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS user(ID INT);", NULL,NULL,&error);
    if(rc != SQLITE_OK){
        cout<< "error: " << error;
    }
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS password(ID INT, pass VARCHAR(20));", NULL,NULL,&error);
    if(rc != SQLITE_OK){
        cout<< "error: " << error;
    }

*/


    sqlite3_close(db);

}


