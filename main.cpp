#include <iostream>
#include "sqlite/sqlite3.h"
using namespace std;

bool listPassword(sqlite3* db,sqlite3_stmt* stmt, int id){
    sqlite3_prepare_v2(db, "select pass from password where id = " + id + "", -1, &stmt, 0);
    const unsigned char* password;
    while(sqlite3_step(stmt) != SQLITE_DONE){
        password = sqlite3_column_text(stmt,1);
        cout << password;
    }
    return true;
}

string insertPassword(sqlite3* db,sqlite3_stmt* stmt, int id , string password){
    char* error;
    int rc;
    string query = "insert into password VALUES (" + id + ", " + 'password'  +" );";
    cout<< query;
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

    cout << "Are you creating a new account?";
    cin >> choice;
    if(choice){
        IDnum  = sqlite3_exec(db, "SELECT COUNT(1) FROM user;", NULL,NULL,&error);
        if(IDnum != SQLITE_OK){
            cout<< "error: " << error;
        }
        cout<< "This is your ID: " +  IDnum;
    }else{
        cout << "What is your ID?";
        cin >> IDnum;
        listPassword(db, stmt, IDnum);
    }
    cout << "";

    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS user(ID INT);", NULL,NULL,&error);
    if(rc != SQLITE_OK){
        cout<< "error: " << error;
    }
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS password(ID INT, pass VARCHAR(20));", NULL,NULL,&error);
    if(rc != SQLITE_OK){
        cout<< "error: " << error;
    }




    sqlite3_close(db);

}


