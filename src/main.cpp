/**
 * @file main.cpp
 * @brief Punto de entrada del juego.
 */
#include "GameController.h"
#include "Menu.h"
#include <iostream>
using namespace std;

int main() {
    Menu mainMenu;

    while (true) {
        int op = mainMenu.showMainMenu();

        if (op == 1) {
            GameController game;
            if (!game.initializeLevel(1)) {
                cout << "\nError: No se encontro 'levels/nivel1.txt'" << endl;
                mainMenu.pause();
                continue;
            }

            bool inGame = true;
            while (inGame) {
                game.startGame();

                if (game.hasPlayerWon()) {
                    if (game.hasNextLevel()) {
                        cout << "\n=== NIVEL " << game.getCurrentLevel() << " COMPLETADO ===" << endl;
                        mainMenu.pause();
                        game.initializeLevel(game.getCurrentLevel() + 1);
                    } else {
                        cout << "\n=== ¡FELICITACIONES! COMPLETASTE TODO ===" << endl;
                        mainMenu.pause();
                        inGame = false;
                    }
                } else if (game.hasPlayerLost()) {
                    mainMenu.pause();  // Pausa para leer el mensaje de derrota
                    cout << "\n1. Reintentar nivel " << game.getCurrentLevel() << endl;
                    cout << "2. Volver al menu" << endl;
                    int opt = -1;
                    while (opt != 1 && opt != 2) {
                        cout << "Opcion: ";
                        if (!(cin >> opt)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            opt = -1;
                        }
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (opt == 1)
                        game.resetLevel();
                    else
                        inGame = false;
                } else {
                    inGame = false;
                }
            }
        } else if (op == 2) {
            cout << "\n===== INSTRUCCIONES =====" << endl;
            cout << "1. Selecciona un vehiculo del tablero." << endl;
            cout << "2. Muevelo en su eje (adelante o atras) por N casillas." << endl;
            cout << "3. Cuando toque un borde, envialo a zona de parqueo." << endl;
            cout << "4. Si el color coincide con el pasajero del frente, sube automaticamente." << endl;
            cout << "5. Si los parkings se llenan y quedan pasajeros sin recoger, pierdes." << endl;
            cout << "6. Recoge a todos los pasajeros para ganar el nivel." << endl;
            mainMenu.pause();
        } else if (op == 3) {
            cout << "\n¡Gracias por jugar!" << endl;
            break;
        }
    }
    return 0;
}
