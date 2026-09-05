#include "TravelAgency.h"
#include <iostream>
#include <limits>
#include <string>

// Reads a whole line safely, even right after using >> on the stream.
static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

static int readInt(const std::string& prompt) {
    std::cout << prompt;
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

static double readDouble(const std::string& prompt) {
    std::cout << prompt;
    double value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

static void userMenu(TravelAgency& agency, User& user) {
    while (true) {
        std::cout << "\n===== Welcome, " << user.getName() << " =====\n";
        std::cout << "1. View travel packages\n";
        std::cout << "2. Book a package\n";
        std::cout << "3. View my bookings\n";
        std::cout << "4. Cancel a booking\n";
        std::cout << "5. Update my profile\n";
        std::cout << "6. Logout\n";
        int choice = readInt("Choose an option: ");

        switch (choice) {
            case 1:
                agency.listAllPackages();
                break;
            case 2: {
                agency.listAllPackages();
                int packageId = readInt("Enter package id to book: ");
                int seats = readInt("Number of seats: ");
                Booking* b = agency.createBooking(user.getId(), packageId, seats);
                if (b) {
                    std::cout << "Booking confirmed!\n";
                    b->displayBooking();
                }
                break;
            }
            case 3:
                agency.viewUserBookings(user.getId());
                break;
            case 4: {
                int bookingId = readInt("Enter booking id to cancel: ");
                bool ok = agency.cancelBooking(bookingId, user.getId());
                std::cout << (ok ? "Booking cancelled.\n" : "Couldn't cancel that booking.\n");
                break;
            }
            case 5: {
                std::string phone = readLine("New phone (leave blank to keep current): ");
                std::string address = readLine("New address (leave blank to keep current): ");
                agency.updateUserProfile(user.getId(), phone, address);
                std::cout << "Profile updated.\n";
                break;
            }
            case 6:
                return;
            default:
                std::cout << "Invalid option.\n";
        }
    }
}

static void adminMenu(TravelAgency& agency, Admin& admin) {
    while (true) {
        std::cout << "\n===== Admin Panel: " << admin.getName() << " =====\n";
        std::cout << "1. View all packages\n";
        std::cout << "2. Add a new package\n";
        std::cout << "3. Remove a package\n";
        std::cout << "4. View all users\n";
        std::cout << "5. View all bookings\n";
        std::cout << "6. Logout\n";
        int choice = readInt("Choose an option: ");

        switch (choice) {
            case 1:
                agency.listAllPackages();
                break;
            case 2: {
                std::string destination = readLine("Destination: ");
                std::string description = readLine("Description: ");
                double price = readDouble("Price per person: ");
                int duration = readInt("Duration (days): ");
                int seats = readInt("Total seats: ");
                agency.addPackage(destination, description, price, duration, seats);
                std::cout << "Package added.\n";
                break;
            }
            case 3: {
                int packageId = readInt("Enter package id to remove: ");
                bool ok = agency.removePackage(packageId);
                std::cout << (ok ? "Package removed.\n" : "No package with that id.\n");
                break;
            }
            case 4:
                agency.viewAllUsers();
                break;
            case 5:
                agency.viewAllBookings();
                break;
            case 6:
                return;
            default:
                std::cout << "Invalid option.\n";
        }
    }
}

int main() {
    TravelAgency agency;

    std::cout << "==========================================\n";
    std::cout << "   TRAVEL AGENCY MANAGEMENT SYSTEM\n";
    std::cout << "==========================================\n";

    while (true) {
        std::cout << "\n1. Login as User\n";
        std::cout << "2. Login as Admin\n";
        std::cout << "3. Register (new customer)\n";
        std::cout << "4. Exit\n";
        int choice = readInt("Choose an option: ");

        if (choice == 1) {
            std::string email = readLine("Email: ");
            std::string password = readLine("Password: ");
            User* user = agency.loginUser(email, password);
            if (user) userMenu(agency, *user);
            else std::cout << "Invalid email or password.\n";
        } else if (choice == 2) {
            std::string email = readLine("Email: ");
            std::string password = readLine("Password: ");
            Admin* admin = agency.loginAdmin(email, password);
            if (admin) adminMenu(agency, *admin);
            else std::cout << "Invalid email or password.\n";
        } else if (choice == 3) {
            std::string name = readLine("Full name: ");
            std::string email = readLine("Email: ");
            std::string phone = readLine("Phone: ");
            std::string password = readLine("Password: ");
            std::string address = readLine("Address: ");
            User* user = agency.registerUser(name, email, phone, password, address);
            if (user) {
                std::cout << "Registration successful. You can now log in.\n";
            } else {
                std::cout << "That email is already registered.\n";
            }
        } else if (choice == 4) {
            std::cout << "Saving data and exiting. Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
