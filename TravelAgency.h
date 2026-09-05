#ifndef TRAVEL_AGENCY_H
#define TRAVEL_AGENCY_H

#include "User.h"
#include "Admin.h"
#include "TravelPackage.h"
#include "Booking.h"
#include <vector>
#include <string>

// TravelAgency is the "brain" of the system. Nothing outside this class
// touches the data files directly - every other part of the program
// (main.cpp) only talks to TravelAgency's public methods. That's the
// encapsulation boundary for the whole app.
class TravelAgency {
private:
    std::vector<User> users;
    std::vector<Admin> admins;
    std::vector<TravelPackage> packages;
    std::vector<Booking> bookings;

    int nextUserId;
    int nextAdminId;
    int nextPackageId;
    int nextBookingId;

    void loadUsers();
    void loadAdmins();
    void loadPackages();
    void loadBookings();
    void seedIfEmpty(); // creates a default admin + sample packages on first run

public:
    TravelAgency();
    ~TravelAgency(); // saves everything to disk automatically on shutdown

    void saveAll() const;

    // ---- Auth & profile ----
    User* registerUser(const std::string& name, const std::string& email,
                        const std::string& phone, const std::string& password,
                        const std::string& address);
    User* loginUser(const std::string& email, const std::string& password);
    Admin* loginAdmin(const std::string& email, const std::string& password);
    bool emailTaken(const std::string& email) const;
    void updateUserProfile(int userId, const std::string& newPhone, const std::string& newAddress);

    // ---- Package / listing management ----
    TravelPackage* addPackage(const std::string& destination, const std::string& description,
                               double price, int durationDays, int seats);
    bool removePackage(int packageId);
    TravelPackage* findPackage(int packageId);
    void listAllPackages() const;

    // ---- Booking ----
    Booking* createBooking(int userId, int packageId, int seats);
    bool cancelBooking(int bookingId, int requestingUserId);
    void viewUserBookings(int userId) const;

    // ---- Admin views ----
    void viewAllUsers() const;
    void viewAllBookings() const;
    User* findUserById(int userId);
};

#endif
