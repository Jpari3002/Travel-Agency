#include "TravelAgency.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <ctime>

namespace fs = std::filesystem;

static const std::string DATA_DIR = "data";
static const std::string USERS_FILE = DATA_DIR + "/users.txt";
static const std::string ADMINS_FILE = DATA_DIR + "/admins.txt";
static const std::string PACKAGES_FILE = DATA_DIR + "/packages.txt";
static const std::string BOOKINGS_FILE = DATA_DIR + "/bookings.txt";

static std::string todayDate() {
    std::time_t t = std::time(nullptr);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&t));
    return std::string(buf);
}

TravelAgency::TravelAgency()
    : nextUserId(1), nextAdminId(1), nextPackageId(1), nextBookingId(1) {
    fs::create_directories(DATA_DIR);
    loadAdmins();
    loadUsers();
    loadPackages();
    loadBookings();
    seedIfEmpty();
}

TravelAgency::~TravelAgency() {
    saveAll();
}

// ---------------- File loading ----------------

void TravelAgency::loadUsers() {
    std::ifstream file(USERS_FILE);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        User u = User::deserialize(line);
        nextUserId = std::max(nextUserId, u.getId() + 1);
        users.push_back(u);
    }
}

void TravelAgency::loadAdmins() {
    std::ifstream file(ADMINS_FILE);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Admin a = Admin::deserialize(line);
        nextAdminId = std::max(nextAdminId, a.getId() + 1);
        admins.push_back(a);
    }
}

void TravelAgency::loadPackages() {
    std::ifstream file(PACKAGES_FILE);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        TravelPackage p = TravelPackage::deserialize(line);
        nextPackageId = std::max(nextPackageId, p.getId() + 1);
        packages.push_back(p);
    }
}

void TravelAgency::loadBookings() {
    std::ifstream file(BOOKINGS_FILE);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Booking b = Booking::deserialize(line);
        nextBookingId = std::max(nextBookingId, b.getId() + 1);
        bookings.push_back(b);
    }
}

void TravelAgency::seedIfEmpty() {
    // First run: nothing on disk yet, so create one admin account and a
    // small catalogue so the app isn't empty the moment it's cloned.
    if (admins.empty()) {
        admins.emplace_back(nextAdminId++, "Default Admin", "admin@travel.com",
                             "9999999999", "admin123", "EMP001");
    }
    if (packages.empty()) {
        packages.emplace_back(nextPackageId++, "Goa Beach Getaway",
                               "4N/5D beach resort stay with water sports included", 14999.0, 5, 20);
        packages.emplace_back(nextPackageId++, "Manali Snow Trek",
                               "Guided Himalayan trek with camping and bonfire nights", 11999.0, 6, 15);
        packages.emplace_back(nextPackageId++, "Kerala Backwaters",
                               "Houseboat stay through the Alleppey backwaters", 18999.0, 4, 10);
    }
}

// ---------------- File saving ----------------

void TravelAgency::saveAll() const {
    fs::create_directories(DATA_DIR);

    std::ofstream userFile(USERS_FILE);
    for (const auto& u : users) userFile << u.serialize() << "\n";

    std::ofstream adminFile(ADMINS_FILE);
    for (const auto& a : admins) adminFile << a.serialize() << "\n";

    std::ofstream packageFile(PACKAGES_FILE);
    for (const auto& p : packages) packageFile << p.serialize() << "\n";

    std::ofstream bookingFile(BOOKINGS_FILE);
    for (const auto& b : bookings) bookingFile << b.serialize() << "\n";
}

// ---------------- Auth & profile ----------------

bool TravelAgency::emailTaken(const std::string& email) const {
    for (const auto& u : users) if (u.getEmail() == email) return true;
    for (const auto& a : admins) if (a.getEmail() == email) return true;
    return false;
}

User* TravelAgency::registerUser(const std::string& name, const std::string& email,
                                  const std::string& phone, const std::string& password,
                                  const std::string& address) {
    if (emailTaken(email)) return nullptr;
    users.emplace_back(nextUserId++, name, email, phone, password, address);
    return &users.back();
}

User* TravelAgency::loginUser(const std::string& email, const std::string& password) {
    for (auto& u : users) {
        if (u.getEmail() == email && u.checkPassword(password)) return &u;
    }
    return nullptr;
}

Admin* TravelAgency::loginAdmin(const std::string& email, const std::string& password) {
    for (auto& a : admins) {
        if (a.getEmail() == email && a.checkPassword(password)) return &a;
    }
    return nullptr;
}

void TravelAgency::updateUserProfile(int userId, const std::string& newPhone, const std::string& newAddress) {
    for (auto& u : users) {
        if (u.getId() == userId) {
            if (!newPhone.empty()) u.setPhone(newPhone);
            if (!newAddress.empty()) u.setAddress(newAddress);
            return;
        }
    }
}

User* TravelAgency::findUserById(int userId) {
    for (auto& u : users) if (u.getId() == userId) return &u;
    return nullptr;
}

// ---------------- Package / listing management ----------------

TravelPackage* TravelAgency::addPackage(const std::string& destination, const std::string& description,
                                         double price, int durationDays, int seats) {
    packages.emplace_back(nextPackageId++, destination, description, price, durationDays, seats);
    return &packages.back();
}

bool TravelAgency::removePackage(int packageId) {
    auto it = std::remove_if(packages.begin(), packages.end(),
        [packageId](const TravelPackage& p) { return p.getId() == packageId; });
    if (it == packages.end()) return false;
    packages.erase(it, packages.end());
    return true;
}

TravelPackage* TravelAgency::findPackage(int packageId) {
    for (auto& p : packages) if (p.getId() == packageId) return &p;
    return nullptr;
}

void TravelAgency::listAllPackages() const {
    if (packages.empty()) {
        std::cout << "No packages available right now.\n";
        return;
    }
    for (const auto& p : packages) p.displayDetails();
}

// ---------------- Booking ----------------

Booking* TravelAgency::createBooking(int userId, int packageId, int seats) {
    TravelPackage* pkg = findPackage(packageId);
    if (!pkg) {
        std::cout << "That package id doesn't exist.\n";
        return nullptr;
    }
    if (!pkg->bookSeats(seats)) {
        std::cout << "Not enough seats available for that package.\n";
        return nullptr;
    }

    double total = pkg->getPrice() * seats;
    bookings.emplace_back(nextBookingId++, userId, packageId, seats, total,
                           BookingStatus::CONFIRMED, todayDate());
    Booking& created = bookings.back();

    User* user = findUserById(userId);
    if (user) user->addBookingId(created.getId());

    return &created;
}

bool TravelAgency::cancelBooking(int bookingId, int requestingUserId) {
    for (auto& b : bookings) {
        if (b.getId() == bookingId && b.getUserId() == requestingUserId) {
            if (b.getStatus() == BookingStatus::CANCELLED) return false;
            TravelPackage* pkg = findPackage(b.getPackageId());
            if (pkg) pkg->releaseSeats(b.getSeats());
            b.cancel();
            return true;
        }
    }
    return false;
}

void TravelAgency::viewUserBookings(int userId) const {
    bool found = false;
    for (const auto& b : bookings) {
        if (b.getUserId() == userId) {
            b.displayBooking();
            found = true;
        }
    }
    if (!found) std::cout << "You don't have any bookings yet.\n";
}

// ---------------- Admin views ----------------

void TravelAgency::viewAllUsers() const {
    if (users.empty()) {
        std::cout << "No registered users yet.\n";
        return;
    }
    for (const auto& u : users) u.displayInfo();
}

void TravelAgency::viewAllBookings() const {
    if (bookings.empty()) {
        std::cout << "No bookings yet.\n";
        return;
    }
    for (const auto& b : bookings) b.displayBooking();
}
