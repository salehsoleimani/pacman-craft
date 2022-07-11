#include "File.h"
#include <iostream>
#include <stdexcept>
#include <fstream>

using namespace std;

File::File(string fileName) {
    this->fileName = fileName;
}

void File::open(ios_base::openmode iomode) {
    close();
    fstream::open(fileName,iomode);

    if (!is_open())
        throw file_open_exception();
}

void File::open(string fileName, ios_base::openmode iomode) {
    this->fileName = fileName;
    close();
    fstream::open(fileName,iomode);

    if (!is_open())
        throw file_open_exception();
}

string File::getline() {
    string str;
    std::getline(*this,str);
    return str;
}

string File::getline(char delim) {
    string str;
    std::getline(*this,str,delim);
    return str;
}

File::~File() {
    close();
}