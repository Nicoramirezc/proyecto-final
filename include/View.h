/**
 * @file View.h
 * @brief Declaración de la clase View.
 *
 * @details
 * Responsabilidades:
 * - Renderizar visualmente el estado actual del tablero y todos sus componentes.
 * - Presentar gráficamente información complementaria como zonas de parqueo y fila de pasajeros.
 * - Consolidar la interfaz gráfica en modo consola para el jugador.
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

#ifndef VIEW_H
#define VIEW_H

#include "Board.h"
#include "ParkingZone.h"
#include "PassengerQueue.h"
#include <vector>
using namespace std;

class View
{
public:
    View();
    ~View();
    void displayGameBoard(Board& board);
    void displayParkingZones(vector<ParkingZone>& zones);
    void displayPassengerQueue(PassengerQueue& queue);
    void displayGameStatus(Board& board, vector<ParkingZone>& zones, PassengerQueue& queue, int level);
    void clearScreen();
    void showMessage(string message);
    void showError(string error);
    void showSuccess(string message);
};

#endif