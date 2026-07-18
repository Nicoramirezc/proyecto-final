/**
 * @file GameController.cpp
 * @brief Implementación del controlador principal (MVC).
 */
#include "GameController.h"
#include "Bus.h"
#include "Car.h"
#include <iostream>
#include <fstream>

GameController::GameController()
    : board(), gameRunning(false), gameWon(false), currentLevel(1) {}

GameController::~GameController() {}

bool GameController::initializeLevel(int levelNumber) {
    string levelFile = "levels/nivel" + to_string(levelNumber) + ".txt";
    if (!LevelLoader::load(levelFile, currentLevelData)) {
        cerr << "Error: No se pudo cargar " << levelFile << endl;
        return false;
    }

    board.resize(currentLevelData.width, currentLevelData.height);

    parkingZones.clear();
    for (int i = 0; i < currentLevelData.numZones; ++i)
        parkingZones.emplace_back(i + 1);

    while (!passengerQueue.isEmpty())
        passengerQueue.removePassenger();

    for (auto& v : currentLevelData.vehicles) {
        shared_ptr<Vehicle> clone;
        if (v->getType() == "Bus")
            clone = make_shared<Bus>(v->getId(), v->getX(), v->getY(),
                                     v->getLength(), v->getColor(), v->getOrientation());
        else
            clone = make_shared<Car>(v->getId(), v->getX(), v->getY(),
                                     v->getLength(), v->getColor(), v->getOrientation());
        board.addVehicle(clone);
    }

    for (auto& p : currentLevelData.passengers)
        passengerQueue.addPassenger(p);

    currentLevel = levelNumber;
    gameRunning = true;
    gameWon = false;
    return true;
}

int GameController::getCurrentLevel() const { return currentLevel; }

bool GameController::hasNextLevel() const {
    string nextFile = "levels/nivel" + to_string(currentLevel + 1) + ".txt";
    ifstream f(nextFile);
    return f.good();
}

void GameController::resetLevel() {
    board.resize(currentLevelData.width, currentLevelData.height);

    for (auto& zone : parkingZones)
        zone.removeVehicle();

    while (!passengerQueue.isEmpty())
        passengerQueue.removePassenger();

    for (auto& v : currentLevelData.vehicles) {
        shared_ptr<Vehicle> clone;
        if (v->getType() == "Bus")
            clone = make_shared<Bus>(v->getId(), v->getX(), v->getY(),
                                     v->getLength(), v->getColor(), v->getOrientation());
        else
            clone = make_shared<Car>(v->getId(), v->getX(), v->getY(),
                                     v->getLength(), v->getColor(), v->getOrientation());
        board.addVehicle(clone);
    }

    for (auto& p : currentLevelData.passengers)
        passengerQueue.addPassenger(p);

    gameRunning = true;
    gameWon = false;
}

void GameController::startGame() {
    while (gameRunning && !hasGameEnded()) {
        playTurn();
    }

    // Mensajes finales: se ejecutan aquí para asegurar que SIEMPRE se muestren,
    // incluso si hasGameEnded() detectó el fin entre turnos.
    if (hasPlayerWon()) {
        view.showSuccess("¡HAS GANADO! ¡Todos los pasajeros se han subido!");
    } else if (hasPlayerLost()) {
        view.showError("¡PERDISTE! Las zonas de parqueo se llenaron sin poder recoger a todos los pasajeros.");
    }
}

void GameController::processAutoBoarding() {
    bool occurred = true;
    while (occurred && !passengerQueue.isEmpty()) {
        occurred = false;
        Passenger next = passengerQueue.frontPassenger();

        for (int i = 0; i < (int)parkingZones.size(); ++i) {
            if (!parkingZones[i].getIsOccupied()) continue;

            auto v = parkingZones[i].getVehicle();
            if (v && v->getColor() == next.getColor() && !v->isFull()) {
                v->addPassenger();
                passengerQueue.removePassenger();
                view.showSuccess(next.getColor() + " subio al vehiculo en zona " + to_string(i + 1));
                occurred = true;

                if (v->isFull()) {
                    view.showMessage("Vehiculo lleno. Partiendo...");
                    parkingZones[i].removeVehicle();
                }
                break;
            }
        }
    }
}

vector<shared_ptr<Vehicle>> GameController::getAvailableVehicles() const {
    vector<shared_ptr<Vehicle>> avail;
    for (auto& v : board.getVehiculos())
        avail.push_back(v);
    return avail;
}

bool GameController::handleMoveVehicle(shared_ptr<Vehicle> vehicle, int direction) {
    cout << "Casillas a mover: ";
    int steps;
    if (!(cin >> steps)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        view.showError("Entrada invalida.");
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (steps <= 0) {
        view.showError("Debe ser mayor a 0.");
        return false;
    }

    int dx = 0, dy = 0;
    if (vehicle->getOrientation() == HORIZONTAL)
        dx = direction;
    else
        dy = direction;

    for (int i = 0; i < steps; ++i) {
        int nx = vehicle->getX() + dx;
        int ny = vehicle->getY() + dy;
        if (!board.canVehicleMove(vehicle->getId(), nx, ny)) {
            view.showError("Bloqueado en paso " + to_string(i + 1));
            return true;
        }
        board.moveVehicle(vehicle->getId(), nx, ny);
    }
    return true;
}

bool GameController::handleParkVehicle(shared_ptr<Vehicle> vehicle) {
    bool atEdge = false;

    if (vehicle->getOrientation() == HORIZONTAL) {
        if (vehicle->getX() == 0 && board.canVehicleExitBoard(vehicle->getId(), -1)) {
            atEdge = true;
        } else if (vehicle->getX() + vehicle->getLength() == board.getAncho() &&
                   board.canVehicleExitBoard(vehicle->getId(), 1)) {
            atEdge = true;
        }
    } else {
        if (vehicle->getY() == 0 && board.canVehicleExitBoard(vehicle->getId(), -1)) {
            atEdge = true;
        } else if (vehicle->getY() + vehicle->getLength() == board.getAlto() &&
                   board.canVehicleExitBoard(vehicle->getId(), 1)) {
            atEdge = true;
        }
    }

    if (!atEdge) {
        view.showError("El vehiculo debe estar en un borde y tener salida libre.");
        return false;
    }

    for (int i = 0; i < (int)parkingZones.size(); ++i) {
        if (!parkingZones[i].getIsOccupied()) {
            parkingZones[i].parkVehicle(vehicle);
            board.removeVehicle(vehicle->getId());
            view.showSuccess("Vehiculo enviado a parqueo " + to_string(i + 1));
            return true;
        }
    }

    view.showError("Todas las zonas de parqueo estan ocupadas.");
    return false;
}

void GameController::playTurn() {
    processAutoBoarding();

    if (passengerQueue.isEmpty()) {
        gameRunning = false;
        return;
    }

    if (hasPlayerLost()) {
        gameRunning = false;
        return;
    }

    view.displayGameStatus(board, parkingZones, passengerQueue, currentLevel);

    auto available = getAvailableVehicles();
    if (available.empty()) {
        view.showError("No hay vehiculos en el tablero.");
        gameRunning = false;
        return;
    }

    int sel = menu.showVehicleSelectionMenu(available);
    if (sel == (int)available.size()) {
        gameRunning = false;
        return;
    }

    auto vehicle = available[sel];

    bool done = false;
    while (!done) {
        view.displayGameStatus(board, parkingZones, passengerQueue, currentLevel);
        int action = menu.showVehicleActionMenu(vehicle);

        switch (action) {
            case 1:
                handleMoveVehicle(vehicle, 1);
                done = true;
                menu.pause();
                break;
            case 2:
                handleMoveVehicle(vehicle, -1);
                done = true;
                menu.pause();
                break;
            case 3: {
                bool ok = handleParkVehicle(vehicle);
                if (ok) done = true;
                menu.pause();
                break;
            }
            case 4:
                done = true;
                break;
        }
    }

    processAutoBoarding();
}

bool GameController::isParkingFull() const {
    for (auto& z : parkingZones)
        if (!z.getIsOccupied()) return false;
    return true;
}

void GameController::removeFullVehicles() {
    for (auto& z : parkingZones)
        if (z.getIsOccupied() && z.isVehicleFull())
            z.removeVehicle();
}

bool GameController::hasGameEnded() {
    removeFullVehicles();
    if (passengerQueue.isEmpty()) return true;
    if (hasPlayerLost()) return true;
    return false;
}

bool GameController::hasPlayerWon() const {
    return passengerQueue.isEmpty();
}

bool GameController::hasPlayerLost() const {
    if (passengerQueue.isEmpty()) return false;
    if (!isParkingFull()) return false;

    Passenger next = passengerQueue.frontPassenger();
    for (const auto& zone : parkingZones) {
        if (zone.getIsOccupied()) {
            auto v = zone.getVehicle();
            if (v && v->getColor() == next.getColor() && !v->isFull()) {
                return false;
            }
        }
    }
    return true;
}
