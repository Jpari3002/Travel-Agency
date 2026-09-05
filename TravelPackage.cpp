#include "TravelPackage.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

TravelPackage::TravelPackage(int id, const std::string& destination, const std::string& description,
                             double price, int durationDays, int seatsAvailable)
    : id(id), destination(destination), description(description),
      price(price), durationDays(durationDays), seatsAvailable(seatsAvailable) {}

int TravelPackage::getId() const { return id; }
std::string TravelPackage::getDestination() const { return destination; }
std::string TravelPackage::getDescription() const { return description; }
double TravelPackage::getPrice() const { return price; }
int TravelPackage::getDurationDays() const { return durationDays; }
int TravelPackage::getSeatsAvailable() const { return seatsAvailable; }

void TravelPackage::setPrice(double newPrice) { price = newPrice; }
void TravelPackage::setSeatsAvailable(int seats) { seatsAvailable = seats; }

bool TravelPackage::bookSeats(int count) {
    if (count <= 0 || count > seatsAvailable) return false;
    seatsAvailable -= count;
    return true;
}

void TravelPackage::releaseSeats(int count) {
    seatsAvailable += count;
}

void TravelPackage::displayDetails() const {
    std::cout << "----------------------------------\n";
    std::cout << "Package #" << id << " - " << destination << "\n";
    std::cout << "Duration : " << durationDays << " days\n";
    std::cout << "Price    : Rs. " << std::fixed << std::setprecision(2) << price << " / person\n";
    std::cout << "Seats    : " << seatsAvailable << " available\n";
    std::cout << "Details  : " << description << "\n";
    std::cout << "----------------------------------\n";
}

std::string TravelPackage::serialize() const {
    std::stringstream ss;
    ss << id << "|" << destination << "|" << description << "|"
       << price << "|" << durationDays << "|" << seatsAvailable;
    return ss.str();
}

TravelPackage TravelPackage::deserialize(const std::string& line) {
    auto t = Utils::split(line, '|');
    return TravelPackage(std::stoi(t[0]), t[1], t[2], std::stod(t[3]),
                          std::stoi(t[4]), std::stoi(t[5]));
}
