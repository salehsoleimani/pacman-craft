#ifndef PACMAN_FILE_H
#define PACMAN_FILE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class file_open_exception : public runtime_error {
public:
    file_open_exception() : runtime_error("cannot open the file!") {}
};

class File : public fstream {
public:
    File(string fileName);

    void open(ios_base::openmode );
    void open(string, ios_base::openmode );

    string getline();
    string getline(char );

    ~File();
private:
    string fileName;
};


#endif