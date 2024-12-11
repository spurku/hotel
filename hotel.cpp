#include <iostream>
#include <vector>
#include <fstream>
#include <random> // Parempaa satunnaisuutta varten
#include <limits> 
#include <locale> // setlocale:n käyttöön

const int MAX_ROOMS = 50; // Määritetään huoneiden maksimimäärä vakiona

struct Room {
    int number;
    bool isBooked;
    double pricePerNight;
};

// Lataa huoneet tiedostosta
void loadRoomsFromFile(std::vector<Room>& rooms, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        rooms.clear();
        Room temp;
        while (file >> temp.number >> temp.isBooked >> temp.pricePerNight) {
            rooms.push_back(temp);
        }
        file.close();
        std::cout << "Huoneet ladattu tiedostosta.\n";
    } else {
        std::cout << "Tiedostoa ei löytynyt. Alustetaan uudet huoneet.\n";
    }
}

// Tallenna huoneet tiedostoon
void saveRoomsToFile(const std::vector<Room>& rooms, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& room : rooms) {
            file << room.number << " " << room.isBooked << " " << room.pricePerNight << "\n";
        }
        file.close();
        std::cout << "Huoneet tallennettu tiedostoon.\n";
    } else {
        std::cerr << "Virhe tiedoston tallennuksessa!\n";
    }
}

// Alusta huoneet, jos tiedostoa ei löydy
void initializeRooms(std::vector<Room>& rooms, int totalRooms) {
    std::random_device rd; // Todella satunnainen siemen
    std::mt19937 gen(rd()); // Satunnaisgeneraattori
    std::uniform_int_distribution<> priceDist(80, 100); // Hinta välillä 80-100

    for (int i = 0; i < totalRooms; ++i) {
        rooms.push_back(Room{ i + 1, false, static_cast<double>(priceDist(gen)) });
    }
}

// Huoneen varaaminen
void bookRoom(std::vector<Room>& rooms) {
    int roomNumber;
    std::cout << "Anna varattavan huoneen numero: ";
    std::cin >> roomNumber;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Virheellinen syöte. Yritä uudelleen.\n";
        return;
    }

    if (roomNumber < 1 || roomNumber > static_cast<int>(rooms.size())) {
        std::cout << "Virheellinen huonenumero. Yritä uudelleen.\n";
        return;
    }

    if (rooms[roomNumber - 1].isBooked) {
        std::cout << "Huone on jo varattu. Valitse toinen huone.\n";
    } else {
        rooms[roomNumber - 1].isBooked = true;
        int nights;
        std::cout << "Anna öiden määrä: ";
        std::cin >> nights;

        if (std::cin.fail() || nights <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Määrän tulee olla positiivinen luku. Yritä uudelleen.\n";
            rooms[roomNumber - 1].isBooked = false; // Peru varaaminen virheellisen syötteen jälkeen
            return;
        }

        double totalCost = nights * rooms[roomNumber - 1].pricePerNight;
        std::cout << "Huone varattu. Loppusumma: " << totalCost << " euroa.\n";
    }
}

// Näytä kaikki huoneet
void displayRooms(const std::vector<Room>& rooms) {
    std::cout << "Huoneet:\n";
    for (const auto& room : rooms) {
        std::cout << "Huone " << room.number << ": " 
                  << (room.isBooked ? "Varattu" : "Vapaa") 
                  << ", Hinta: " << room.pricePerNight << " euroa/yö\n";
    }
}

int main() {
    // Alustetaan pohjoismainen asettelu
    setlocale(LC_ALL, "fi_FI");

    std::cout << "***Huoneen varausjärjestelmä***\n\n";
    
    std::string filename = "huoneet.txt";
    std::vector<Room> rooms;

    loadRoomsFromFile(rooms, filename);
    if (rooms.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> roomCountDist(30, 70);
        int totalRooms = std::min(roomCountDist(gen), MAX_ROOMS);
        initializeRooms(rooms, totalRooms);
    }

    int choice;
    do {
        std::cout << "\n1. Näytä huoneet\n2. Varaa huone\n3. Lopeta\nValitse toiminto: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Virheellinen syöte. Yritä uudelleen.\n";
            continue;
        }

        switch (choice) {
        case 1:
            displayRooms(rooms);
            break;
        case 2:
            bookRoom(rooms);
            saveRoomsToFile(rooms, filename); // Tallenna muutokset tiedostoon
            break;
        case 3:
            saveRoomsToFile(rooms, filename); // Tallenna lopuksi
            std::cout << "Ohjelma lopetetaan.\n";
            break;
        default:
            std::cout << "Virheellinen valinta. Yritä uudelleen.\n";
        }
    } while (choice != 3);

    return 0;
}
