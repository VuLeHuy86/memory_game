#include "sinhvien.h"

using namespace std;

void sv::nhapthongtin(const string& line) {
    stringstream ss(line);
    string temp_gpa;
    getline(ss, ten, '-');
    getline(ss, ngaysinh, '-');
    getline(ss, msv, '-');
    getline(ss, lop, '-');
    getline(ss, temp_gpa, '-');
    gpa = stod(temp_gpa);
}

string sv::getTen() const { return ten; }
string sv::getNgaysinh() const { return ngaysinh; }
string sv::getMsv() const { return msv; }
string sv::getLop() const { return lop; }
double sv::getGpa() const { return gpa; }

void sv::setTen(const string& t) {
    ten = t;
}






