#include "Booking.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

std::string statusToString(BookingStatus status) {
    switch (status) {
        case BookingStatus::PENDING:   return "PENDING";
        case BookingStatus::CONFIRMED: return "CONFIRMED";
        case BookingStatus::CANCELLED: return "CANCELLED";
    }
    return "PENDING";
}

BookingStatus statusFromString(const std::string& s) {
    if (s == "CONFIRMED") return BookingStatus::CONFIRMED;
    if (s == "CANCELLED") return BookingStatus::CANCELLED;
    return BookingStatus::PENDING;
}

Booking::Booking(int id, int userId, int packageId, int seats,
                  double totalAmount, BookingStatus status, const std::string& date)
    : id(id), userId(userId), packageId(packageId), seats(seats),
      totalAmount(totalAmount), status(status), date(date) {}

int Booking::getId() const { return id; }
int Booking::getUserId() const { return userId; }
int Booking::getPackageId() const { return packageId; }
int Booking::getSeats() const { return seats; }
double Booking::getTotalAmount() const { return totalAmount; }
BookingStatus Booking::getStatus() const { return status; }
std::string Booking::getDate() const { return date; }

void Booking::confirm() { status = BookingStatus::CONFIRMED; }
void Booking::cancel() { status = BookingStatus::CANCELLED; }

void Booking::displayBooking() const {
    std::cout << "----------------------------------\n";
    std::cout << "Booking #" << id << " | Status: " << statusToString(status) << "\n";
    std::cout << "User Id    : " << userId << "\n";
    std::cout << "Package Id : " << packageId << "\n";
    std::cout << "Seats      : " << seats << "\n";
    std::cout << "Amount     : Rs. " << std::fixed << std::setprecision(2) << totalAmount << "\n";
    std::cout << "Date       : " << date << "\n";
    std::cout << "----------------------------------\n";
}

std::string Booking::serialize() const {
    std::stringstream ss;
    ss << id << "|" << userId << "|" << packageId << "|" << seats << "|"
       << totalAmount << "|" << statusToString(status) << "|" << date;
    return ss.str();
}

Booking Booking::deserialize(const std::string& line) {
    auto t = Utils::split(line, '|');
    return Booking(std::stoi(t[0]), std::stoi(t[1]), std::stoi(t[2]), std::stoi(t[3]),
                   std::stod(t[4]), statusFromString(t[5]), t[6]);
}
