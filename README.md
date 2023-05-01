# PasswordSaver

PasswordSaver is a C++ program that locally saves passwords to an embedded database.

## Description

PasswordSaver is a program built in C++ and SQL. It utilizes SQLite to save passwords into a database. The program is light and simple with a command-line user-interface.

### Installing

Install from GitHub repository.

### Executing program

Download program and run in an IDE. The user will be given a prompt where they can choose between creating an account, listing passwords, or adding a password. If the
user does not have an account, they will need to create a new one to save a password. Otherwise, they can choose between list passwords and add password. If they choose the first option, they will be asked for an ID. Then, passwords are listed for that one ID. If they choose the second option, the user will be asked for an ID and password. The ID and password is then inserted into the database. Once finished, the user is asked if they want to start over.

## Authors
 
   [Nicholas Tran](https://github.com/NickT144)

## Version History

* 0.1
    * Changed UI
    * Full functionality
* 0.001
    * Initial Release

## License

[MIT](https://choosealicense.com/licenses/mit/)

## Acknowledgments

Inspiration, code snippets, etc.
* [SQLite](https://sqlite.org/index.html)
