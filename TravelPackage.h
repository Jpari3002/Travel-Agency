#ifndef TRAVEL_PACKAGE_H
#define TRAVEL_PACKAGE_H

#include <string>

// A single listing in the catalogue: one destination/tour package.
class TravelPackage {
private:
    int id;
    std::string destination;
    std::string description;
    double price;
    int durationDays;
    int seatsAvailable;

public:
    TravelPackage(int id, const std::string& destination, const std::string& description,
                  double price, int durationDays, int seatsAvailable);

    int getId() const;
    std::string getDestination() const;
    std::string getDescription() const;
    double getPrice() const;
    int getDurationDays() const;
    int getSeatsAvailable() const;

    void setPrice(double newPrice);
    void setSeatsAvailable(int seats);

    // Returns false (and books nothing) if there aren't enough seats left
    bool bookSeats(int count);
    void releaseSeats(int count); // used when a booking is cancelled

    void displayDetails() const;

    std::string serialize() const;
    static TravelPackage deserialize(const std::string& line);
};

#endif
