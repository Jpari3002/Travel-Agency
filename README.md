# Travel Agency Management System

A travel agency management system with two independent implementations:

1. **`frontend/`** — a browser-based UI in plain HTML, CSS and JavaScript (ES6 classes).
2. **`backend-cpp/`** — a console application in C++ that persists data to disk.

Both sides model the same thing: customer profiles, a catalogue of travel
package listings, bookings, and basic admin controls (add/remove listings,
view users, view all bookings). They're built independently so each one
stands on its own as a complete OOP project — they don't talk to each other.

## OOP principles used

Both implementations follow the same class design:

- **Abstraction** — `Person` (C++: pure virtual class, JS: throws if
  instantiated directly) defines the shape every person in the system has,
  without knowing whether that person is a customer or an admin.
- **Inheritance** — `User` and `Admin` both extend `Person` and inherit its
  fields (id, name, email, phone) instead of duplicating them.
- **Polymorphism** — `displayInfo()` / `getRole()` behave differently
  depending on whether the object is a `User` or an `Admin`, even though both
  are handled through the same `Person` interface.
- **Encapsulation** — all state lives inside `TravelAgency` (C++) /
  `TravelAgency` (JS). Nothing outside that class touches the raw arrays or
  files directly; everything goes through its public methods.

## `frontend/` — HTML/CSS/JS

```
frontend/
├── index.html         Page structure
├── css/style.css       All styling
└── js/
    ├── models.js       Person, User, Admin, TravelPackage, Booking classes
    ├── agency.js       TravelAgency — the manager class holding all data
    └── app.js          DOM rendering + event handling (the only file that touches the page)
```

**To run:** open `frontend/index.html` directly in a browser, or serve the
folder with any static server (e.g. `npx serve frontend`).

Demo admin login: `admin@travel.com` / `admin123`. A few sample packages are
seeded on load.

Note: this demo keeps all data in memory, so refreshing the page resets it.
That's a deliberate simplification — swapping in `localStorage` or a real
backend API only means changing the inside of `TravelAgency`'s methods; the
rest of the app wouldn't need to change.

## `backend-cpp/` — C++ console app

```
backend-cpp/
├── include/            Header files (Person, User, Admin, TravelPackage, Booking, TravelAgency, Utils)
├── src/                Matching .cpp files + main.cpp (the menu)
├── data/                Auto-created on first run — users.txt, admins.txt, packages.txt, bookings.txt
└── Makefile
```

**To build and run:**

```bash
cd backend-cpp
make
./travel_agency
```

Data is saved to plain text files under `data/` on every exit, so your
users, listings and bookings persist between runs. A default admin account
(same credentials as above) and sample packages are created automatically
the first time you run it.

Requires a C++17 compiler (uses `<filesystem>`). Tested with g++ 13.

## Uploading this to GitHub

From the project's root folder:

```bash
git init
git add .
git commit -m "Initial commit: Travel Agency Management System"
git branch -M main
git remote add origin https://github.com/<your-username>/<your-repo-name>.git
git push -u origin main
```

Create the empty repository on GitHub first (no README/license, so it
doesn't conflict with what's already here), then run the commands above
with your repo's URL. The `.gitignore` already excludes the compiled
binary and the `data/` folder, so your repo stays source-only — anyone who
clones it gets a clean first run.

## What's ambiguous and worth flagging

Your brief mentioned "job listing," which doesn't quite fit a travel
agency. I've treated it as "travel package/tour listing" (destinations
customers can browse and book) since that's what the rest of the brief
(user profiles, admin controls) points to. If you actually meant something
else, like staff/job postings within the agency, let me know and I'll
adjust the listing model.
