#include "Person.h"

Person::Person(int id, const std::string& name, const std::string& email,
               const std::string& phone, const std::string& password)
    : id(id), name(name), email(email), phone(phone), password(password) {}

int Person::getId() const { return id; }
std::string Person::getName() const { return name; }
std::string Person::getEmail() const { return email; }
std::string Person::getPhone() const { return phone; }

void Person::setName(const std::string& newName) { name = newName; }
void Person::setPhone(const std::string& newPhone) { phone = newPhone; }

bool Person::checkPassword(const std::string& candidate) const {
    return password == candidate;
}
