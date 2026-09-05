#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"
#include <string>

// Admin = staff member who manages packages, users and bookings.
// Same base identity as User (via Person), different role and permissions.
class Admin : public Person {
private:
    std::string employeeCode;

public:
    Admin(int id, const std::string& name, const std::string& email,
          const std::string& phone, const std::string& password,
          const std::string& employeeCode);

    void displayInfo() const override;
    std::string getRole() const override;

    std::string getEmployeeCode() const;

    std::string serialize() const;
    static Admin deserialize(const std::string& line);
};

#endif
