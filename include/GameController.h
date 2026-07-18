/**
 * @file GameController.h
 * @brief Declaración de la clase GameController.
 *
 * @details
 * Responsabilidades:
 * - Orquestar el flujo general, coordinar subsistemas (Board, Zones, Views) y aplicar las reglas del negocio.
 * - Evaluar las acciones del jugador para resolver la lógica de transiciones, victorias o derrotas.
 * - Gestionar el ciclo de vida de la partida, los reinicios y los saltos de nivel.
 *
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

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Board.h"
#include "ParkingZone.h"
#include "PassengerQueue.h"
#include "View.h"
#include "Menu.h"
#include "LevelLoader.h"
#include <vector>
#include <memory>
using namespace std;

class GameController
{
private:
    Board board;
    vector<ParkingZone> parkingZones;
    PassengerQueue passengerQueue;
    View view;
    Menu menu;
    LevelData currentLevelData;

    bool gameRunning;
    bool gameWon;
    int currentLevel;
    string currentLevelFile;

    void processAutoBoarding();
    vector<shared_ptr<Vehicle>> getAvailableVehicles() const;
    bool handleMoveVehicle(shared_ptr<Vehicle> vehicle, int direction);
    bool handleParkVehicle(shared_ptr<Vehicle> vehicle);
    bool isParkingFull() const;
    void removeFullVehicles();

public:
    GameController();
    ~GameController();

    bool initializeLevel(int levelNumber);
    int getCurrentLevel() const;
    bool hasNextLevel() const;
    void resetLevel();
    void startGame();
    void playTurn();

    bool hasGameEnded();
    bool hasPlayerWon() const;
    bool hasPlayerLost() const;
};

#endif