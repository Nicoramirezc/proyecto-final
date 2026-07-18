/**
 * @file Board.cpp
 * @brief Implementación de la logica de Board.
 * -----------------------------------------------------------------------------
 *
 * @author Douglas Velez Monginaite | Código 202516737-3743
 * @email douglas.velez@correounivalle.edu.co
 *
 * @author Juan Diego Lopez Gomez | Código 202519861-3743
 * @email juan.lopez.g@correounivalle.edu.co
 *
 * @author Nicolas Andres Ramirez | Código 202415510-3743
 * @email nicolas.andres.ramirez@correounivalle.edu.co
 *
*/

#include "Board.h"
#include <iostream>

Board::Board() : ancho(0), alto(0) {}
Board::Board(int w, int h) : ancho(w), alto(h) {}
Board::Board(const string& filename) : ancho(0), alto(0) {
    cargarDesdeArchivo(filename);
}
Board::~Board() {
    clearVehicles();
}

void Board::resize(int w, int h) {
    ancho = w;
    alto = h;
    clearVehicles();
}

bool Board::cargarDesdeArchivo(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    clearVehicles();
    file >> ancho >> alto;
    file.close();
    return (ancho > 0 && alto > 0);
}

int Board::getAncho() const { return ancho; }
int Board::getAlto() const { return alto; }

const vector<shared_ptr<Vehicle>>& Board::getVehiculos() const {
    return vehiculos;
}

shared_ptr<Vehicle> Board::getVehicleById(int id) const {
    for (auto& v : vehiculos)
        if (v->getId() == id)
            return v;
    return nullptr;
}

void Board::addVehicle(shared_ptr<Vehicle> vehicle) {
    if (vehicle != nullptr)
        vehiculos.push_back(vehicle);
}

void Board::removeVehicle(int vehicleId) {
    for (auto it = vehiculos.begin(); it != vehiculos.end(); ++it) {
        if ((*it)->getId() == vehicleId) {
            vehiculos.erase(it);
            return;
        }
    }
}

void Board::clearVehicles() {
    vehiculos.clear();
}

bool Board::esValido(int x, int y) const {
    return (x >= 0 && x < ancho && y >= 0 && y < alto);
}

/**
 * @brief Detección de colisiones por solapamiento de rectángulos.
 */
bool Board::hasCollision(int x, int y, int length, Orientation orient, int excludeId) const {
    int x1 = x;
    int y1 = y;
    int x2 = (orient == HORIZONTAL) ? x + length : x + 1;
    int y2 = (orient == HORIZONTAL) ? y + 1 : y + length;

    for (const auto& v : vehiculos) {
        if (v->getId() == excludeId) continue;

        int vx1 = v->getX();
        int vy1 = v->getY();
        int vx2 = (v->getOrientation() == HORIZONTAL) ? v->getX() + v->getLength() : v->getX() + 1;
        int vy2 = (v->getOrientation() == HORIZONTAL) ? v->getY() + 1 : v->getY() + v->getLength();

        if (x1 < vx2 && x2 > vx1 && y1 < vy2 && y2 > vy1)
            return true;
    }
    return false;
}

bool Board::canVehicleMove(int vehicleId, int newX, int newY) const {
    auto v = getVehicleById(vehicleId);
    if (!v) return false;

    if (newX < 0 || newY < 0) return false;

    if (v->getOrientation() == HORIZONTAL) {
        if (newX + v->getLength() > ancho || newY >= alto) return false;
    } else {
        if (newY + v->getLength() > alto || newX >= ancho) return false;
    }

    return !hasCollision(newX, newY, v->getLength(), v->getOrientation(), vehicleId);
}

bool Board::canVehicleExitBoard(int vehicleId, int direction) const {
    auto v = getVehicleById(vehicleId);
    if (!v) return false;

    int x = v->getX(), y = v->getY(), len = v->getLength();

    if (v->getOrientation() == HORIZONTAL) {
        if (direction == -1) {
            for (int i = 0; i < x; ++i)
                if (hasCollision(i, y, 1, HORIZONTAL, vehicleId)) return false;
            return true;
        } else {
            for (int i = x + len; i < ancho; ++i)
                if (hasCollision(i, y, 1, HORIZONTAL, vehicleId)) return false;
            return true;
        }
    } else {
        if (direction == -1) {
            for (int i = 0; i < y; ++i)
                if (hasCollision(x, i, 1, VERTICAL, vehicleId)) return false;
            return true;
        } else {
            for (int i = y + len; i < alto; ++i)
                if (hasCollision(x, i, 1, VERTICAL, vehicleId)) return false;
            return true;
        }
    }
}

bool Board::moveVehicle(int vehicleId, int newX, int newY) {
    if (canVehicleMove(vehicleId, newX, newY)) {
        auto v = getVehicleById(vehicleId);
        if (v) {
            v->setPosition(newX, newY);
            return true;
        }
    }
    return false;
}

void Board::mostrar() const {
    cout << "\n=== TABLERO (" << ancho << "x" << alto << ") ===" << endl;
    vector<vector<string>> grid(alto, vector<string>(ancho, "."));

    for (const auto& v : vehiculos) {
        string marker = to_string(v->getId());
        if (v->getOrientation() == HORIZONTAL) {
            for (int i = 0; i < v->getLength() && v->getX() + i < ancho; ++i)
                if (v->getY() >= 0 && v->getY() < alto)
                    grid[v->getY()][v->getX() + i] = marker;
        } else {
            for (int i = 0; i < v->getLength() && v->getY() + i < alto; ++i)
                if (v->getX() >= 0 && v->getX() < ancho)
                    grid[v->getY() + i][v->getX()] = marker;
        }
    }

    for (int y = 0; y < alto; ++y) {
        for (int x = 0; x < ancho; ++x)
            cout << grid[y][x] << " ";
        cout << endl;
    }
}