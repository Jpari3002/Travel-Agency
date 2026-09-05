#include "User.h"
#include "Utils.h"
#include <iostream>

User::User(int id, const std::string& name, const std::string& email,
           const std::string& phone, const std::string& password,
           const std::string& address)
    : Person(id, name, email, phone, password), address(address) {}

void User::displayInfo() const {
    std::cout << "----------------------------------\n";
    std::cout << "User #" << id << "\n";
    std::cout << "Name    : " << name << "\n";
    std::cout << "Email   : " << email << "\n";
    std::cout << "Phone   : " << phone << "\n";
    std::cout << "Address : " << address << "\n";
    std::cout << "Bookings: " << bookingIds.size() << "\n";
    std::cout << "----------------------------------\n";
}

std::string User::getRole() const { return "User"; }

std::string User::getAddress() const { return address; }
void User::setAddress(const std::string& newAddress) { address = newAddress; }

void User::addBookingId(int bookingId) { bookingIds.push_back(bookingId); }
const std::vector<int>& User::getBookingIds() const { return bookingIds; }

std::string User::serialize() const {
    std::stringstream ss;
    ss << id << "|" << name << "|" << email << "|" << phone << "|"
       << password << "|" << address << "|" << Utils::joinIds(bookingIds);
    return ss.str();
}

User User::deserialize(const std::string& line) {
    auto t = Utils::split(line, '|');
    // t[0]=id t[1]=name t[2]=email t[3]=phone t[4]=password t[5]=address t[6]=bookingIds(optional)
    User u(std::stoi(t[0]), t[1], t[2], t[3], t[4], t.size() > 5 ? t[5] : "");
    if (t.size() > 6) {
        for (int bid : Utils::splitIds(t[6])) u.addBookingId(bid);
    }
    return u;
}
