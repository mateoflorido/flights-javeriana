//
// Created by florido on 19/08/18.
//

#include <sstream>
#include <ctime>
#include <iostream>
#include "Consola.h"
#include <fstream>
#include "Archivo.h"

std::unordered_map<std::string, std::string> ReadCommands() {
    std::unordered_map<std::string, std::string> commandList;
    commandList = {

            {"exit",   "exit: exit "
                       "\n Cierra todas las sesiones y finaliza la ejecución del programa"
            },
            {"report", "report: report <Modo> [arg1] [arg2]"
                       "\n Permite realizar un reporte detallado."
                       "\n Genera un reporte detallado del modo seleccionado."
                       "\n Argumentos <Modo>:"
                       "\n \t Modo\t Selecciona un modo Válido entre"
                       "\n \t \t flights: Genera un reporte de todos los vuelos con sillas disponibles"
                       "\n \t \t inventory: Genera un reporte de todos los vuelos vendidos, cambiados o cancelados de una agencia de viajes"
                       "\n \n Argumentos [arg1] [arg2]"
                       "\n*Unicamente Modo flights*"
                       "\n \t arg1: Origen de los vuelos a incluir en el reporte"
                       "\n \t arg2: Fecha de los vuelos a incluir en el reporte"
            },

            {"sell",   "sell: sell <IDVuelo> <Fecha> "
                       "\n Realiza la venta de un vuelo determinado en una fecha seleccionada "
                       "\n Argumentos :"
                       "\n \tIDVuelo: Identificador del vuelo seleccionado"
                       "\n \tFecha: Fecha del vuelo seleccionado"
                       "\n Estado de Salida: \nGenera una venta del vuelo seleccionado"
            },
            {
             "logout", "logout: logout"
                       "\n Permite cerrar sesión en una agencia"
                       "\n Estado de Salida:"
                       "\n Cierra la sesión siempre que exista una abierta"
            },
            {
             "login",  "login: login <idagencia>"
                       "\n Permite iniciar sesión en una agencia"
                       "\n Permite iniciar sesión en una agencia cuando el IDAGENCIA es válido"
                       "\n Argumentos:\n \t IDAGENCIA\t Indica el ID de una agencia válida."
            }
    };


    return commandList;
}

void ConsoleHub() {
    typedef std::unordered_map<std::string, std::string> TCommandList;
    std::string command;
    std::stringstream commandline(command);
    std::string mainCommand;
    std::string arg1;
    std::string arg2;
    TCommandList commandList = ReadCommands();

    auto a = new FJA::Aeronautica();

    std::time_t result = std::time(nullptr);

    std::cout << "Bienvenido a Viajes Javeriana v0.1 alpha\n"
              << "Hoy es: "
              << std::asctime(std::localtime(&result))
              << "\nRecuerde Iniciar Sesión con el comando login <idagencia>\n"
              << "En caso de necesitar ayuda use help";

    while (command != "exit") {
        std::cout << "\n$ ";
        std::getline(std::cin, command);
        commandline.str(command);
	ReadAgencies(*a, "flights.txt");
        commandline >> mainCommand;
        if (mainCommand == "login") {
            std::cout << "Hey Listen!";
        } else if (mainCommand == "read") {

        } else if (mainCommand == "help") {
            if (!commandline.bad()) {
                std::cout << commandList.find(mainCommand)->second; //Imprimir Comando encontrado
            } else {
                auto it = commandList.begin();
                std::cout << "---------------------------------\n";

                while (it != commandList.end()) {
                    std::cout << it->second << '\n';
                    std::cout << "---------------------------------\n";
                    ++it;

                }
            }
        }

    }
}
