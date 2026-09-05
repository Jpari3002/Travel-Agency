CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
SRC = src/main.cpp src/Person.cpp src/User.cpp src/Admin.cpp src/TravelPackage.cpp src/Booking.cpp src/TravelAgency.cpp
TARGET = travel_agency

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
