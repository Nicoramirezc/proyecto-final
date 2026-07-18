/**
 * @file LevelLoader.cpp
 * @brief Persistencia: carga de niveles desde archivos planos.
 * @details Aplica SRP: solo lee archivos, no imprime ni maneja lógica de juego.
 */
#include "LevelLoader.h"
#include "Bus.h"
#include "Car.h"
#include <fstream>

bool LevelLoader::load(const string& filename, LevelData& data) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file >> data.width >> data.height;
    if (data.width <= 0 || data.height <= 0) {
        file.close();
        return false;
    }

    file >> data.numZones;

    int numVehicles;
    file >> numVehicles;
    data.vehicles.clear();

    for (int i = 0; i < numVehicles; ++i) {
        string type, color, orientStr;
        int id, x, y, length;
        file >> type >> id >> color >> x >> y >> orientStr >> length;

        Orientation orient = (orientStr == "HORIZONTAL") ? HORIZONTAL : VERTICAL;
        shared_ptr<Vehicle> v;
        if (type == "BUS")
            v = make_shared<Bus>(id, x, y, length, color, orient);
        else if (type == "CAR")
            v = make_shared<Car>(id, x, y, length, color, orient);

        if (v) data.vehicles.push_back(v);
    }

    int numPassengers;
    file >> numPassengers;
    data.passengers.clear();
    for (int i = 0; i < numPassengers; ++i) {
        string color;
        file >> color;
        data.passengers.emplace_back(i + 1, color);
    }

    file.close();
    return true;
}