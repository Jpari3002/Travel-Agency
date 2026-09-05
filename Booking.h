#ifndef BOOKING_H
#define BOOKING_H

#include <string>

// A booking's lifecycle. Kept as an enum instead of a raw string/int so
// invalid statuses can't sneak in - the compiler enforces valid values.
enum class BookingStatus { PENDING, CONFIRMED, CANCELLED };

std::string statusToString(BookingStatus status);
BookingStatus statusFromString(const std::string& s);

class Booking {
private:
    int id;
    int userId;
    int packageId;
    int seats;
    double totalAmount;
    BookingStatus status;
    std::string date;

public:
    Booking(int id, int userId, int packageId, int seats,
            double totalAmount, BookingStatus status, const std::string& date);

    int getId() const;
    int getUserId() const;
    int getPackageId() const;
    int getSeats() const;
    double getTotalAmount() const;
    BookingStatus getStatus() const;
    std::string getDate() const;

    void confirm();
    void cancel();

    void displayBooking() const;

    std::string serialize() const;
    static Booking deserialize(const std::string& line);
};

#endif
