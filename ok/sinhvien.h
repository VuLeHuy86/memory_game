#ifndef SINHVIEN_H
#define SINHVIEN_H

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct sv{

private:
	string ten, ngaysinh, msv, lop;
	double gpa;

public:
    // hàm nhập thông tin cho 1 svien từ 1 dòng trong file
    void nhapthongtin(const string& line);

    // các hàm đọc thông tin của svien để so sánh
    string getTen() const;
    string getNgaysinh() const;
    string getMsv() const;
    string getLop() const;
    double getGpa() const;

    // hàm thay đổi tên svien khi cần thiết
    void setTen(const string& t);
};

#endif


















