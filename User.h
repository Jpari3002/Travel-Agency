#ifndef USER_H
#define USER_H

#include "Person.h"
#include <string>
#include <vector>

// User = a customer of the agency. Inherits everything from Person
// (id, name, email, phone, password) and adds its own profile fields.
class User : public Person {
private:
    std::string address;
    std::vector<int> bookingIds; // structured link to this user's bookings

public:
    User(int id, const std::string& name, const std::string& email,
         const std::string& phone, const std::string& password,
         const std::string& address);

    void displayInfo() const override;
    std::string getRole() const override;

    std::string getAddress() const;
    void setAddress(const std::string& newAddress);

    void addBookingId(int bookingId);
    const std::vector<int>& getBookingIds() const;

    // Turns this object into one line of text for saving to disk
    std::string serialize() const;
    // Rebuilds a User object from one saved line
    static User deserialize(const std::string& line);
};

#endif
