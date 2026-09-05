#include "Admin.h"
#include "Utils.h"
#include <iostream>

Admin::Admin(int id, const std::string& name, const std::string& email,
             const std::string& phone, const std::string& password,
             const std::string& employeeCode)
    : Person(id, name, email, phone, password), employeeCode(employeeCode) {}

void Admin::displayInfo() const {
    std::cout << "----------------------------------\n";
    std::cout << "Admin #" << id << "\n";
    std::cout << "Name    : " << name << "\n";
    std::cout << "Email   : " << email << "\n";
    std::cout << "Emp Code: " << employeeCode << "\n";
    std::cout << "----------------------------------\n";
}

std::string Admin::getRole() const { return "Admin"; }
std::string Admin::getEmployeeCode() const { return employeeCode; }

std::string Admin::serialize() const {
    std::stringstream ss;
    ss << id << "|" << name << "|" << email << "|" << phone << "|"
       << password << "|" << employeeCode;
    return ss.str();
}

Admin Admin::deserialize(const std::string& line) {
    auto t = Utils::split(line, '|');
    return Admin(std::stoi(t[0]), t[1], t[2], t[3], t[4], t[5]);
}
