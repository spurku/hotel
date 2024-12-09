#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits> // Tarvitaan syˆtevirheiden k‰sittelyyn

const int MAX_ROOMS = 50; // M‰‰ritet‰‰n huoneiden maksimim‰‰r‰ vakiona

struct Room {
    int number;
    bool isBooked;
    double pricePerNight;
};

void initializeRooms(std::vector<Room>& rooms, int totalRooms) {
    for (int i = 0; i < totalRooms; ++i) {
        rooms.push_back(Room{ i + 1, false, 80 + rand() % 21 }); // Hinta v‰lilt‰ 80-100 euroa
    }
}

void bookRoom(std::vector<Room>& rooms) {
    int roomNumber;
    std::cout << "Anna varattavan huoneen numero: ";
    std::cin >> roomNumber;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Virheellinen syˆte. Yrit‰ uudelleen.\n";
        return;
    }

    if (roomNumber < 1 || roomNumber > static_cast<int>(rooms.size())) {
        std::cout << "Virheellinen huonenumero. Yrit‰ uudelleen.\n";
        return;
    }

    if (rooms[roomNumber - 1].isBooked) {
        std::cout << "Huone on jo varattu. Valitse toinen huone.\n";
    }
    else {
        rooms[roomNumber - 1].isBooked = true;
        int nights;
        std::cout << "Anna ˆiden m‰‰r‰: ";
        std::cin >> nights;

        if (std::cin.fail() || nights <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "÷iden m‰‰r‰n tulee olla positiivinen luku. Yrit‰ uudelleen.\n";
            return;
        }

        double totalCost = nights * rooms[roomNumber - 1].pricePerNight;
        std::cout << "Huone varattu. Loppusumma: " << totalCost << " euroa.\n";
    }
}

void displayRooms(const std::vector<Room>& rooms) {
    std::cout << "Huoneet:\n";
    for (const auto& room : rooms) {
        std::cout << "Huone " << room.number << ": " << (room.isBooked ? "Varattu" : "Vapaa") << ", Hinta: " << room.pricePerNight << " euroa/yˆ\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Satunnaislukugeneraattorin alustus
    int totalRooms = 30 + rand() % 41; // Huoneiden m‰‰r‰ v‰lilt‰ 30-70
    if (totalRooms > MAX_ROOMS) {
        totalRooms = MAX_ROOMS;
    }
    std::vector<Room> rooms;
    initializeRooms(rooms, totalRooms);

    int choice;
    do {
        std::cout << "\n1. N‰yt‰ huoneet\n2. Varaa huone\n3. Lopeta\nValitse toiminto: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Virheellinen syˆte. Yrit‰ uudelleen.\n";
            continue;
        }

        switch (choice) {
        case 1:
            displayRooms(rooms);
            break;
        case 2:
            bookRoom(rooms);
            break;
        case 3:
            std::cout << "Ohjelma lopetetaan.\n";
            break;
        default:
            std::cout << "Virheellinen valinta. Yrit‰ uudelleen.\n";
        }
    } while (choice != 3);

    return 0;
}
