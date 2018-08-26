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
    std::string currentAgency;

    auto a = new FJA::Aeronautica();

    std::time_t result = std::time(nullptr);

    std::cout << "Bienvenido a Viajes Javeriana v0.1 alpha\n"
              << "Hoy es: "
              << std::asctime(std::localtime(&result))
              << "\nRecuerde Iniciar Sesión con el comando login <idagencia>\n"
              << "En caso de necesitar ayuda use help";

    while (command != "exit") {
        std::cout << "\n" << currentAgency << " $ ";

        command.clear();
        std::getline(std::cin, command);
        commandline.clear();
        commandline.str(command);
        commandline >> mainCommand;

        if (mainCommand == "login") {
            if (currentAgency == "") {
                std::cout << "Ingrese el Usuario: ";
                std::getline(std::cin, arg1);
                std::cout << "Ingrese su contraseña: ";
                std::getline(std::cin, arg2);
                if (a->CheckLogin(arg1, arg2)) {
                    currentAgency = arg1;
                } else {
                    currentAgency = "";
                    std::cout << "Usuario o Contraseña no Válidos";
                }
            } else
                std::cout << "Agencia: " << currentAgency << " Termine sesión para ingresar en otra cuenta.";

        } else if (mainCommand == "logout") {
            if (currentAgency != "") {
                std::cout << " Cerrando Sesión de " << currentAgency << '\n';
                currentAgency = "";
            } else
                std::cout << "No hay una sesión iniciada.";
        } else if (mainCommand == "read") {
            if (commandline >> mainCommand) {
                if (mainCommand == "flights")
                    ReadFlights(*a, "./flights.txt");
                else if (mainCommand == "agencies")
                    ReadAgencies(*a, "./passwords.txt");
                else if (mainCommand == "sales")
                    ReadSales(*a, "./tickets.txt");
                else
                    std::cout << "Argumento no Válido: \n" << commandList.find("sell")->second;
            }

        } else if (mainCommand == "help") {
            if (commandline >> mainCommand) {
                if (commandList.find(mainCommand) != commandList.end())
                    std::cout << commandList.find(mainCommand)->second; //Imprimir Comando encontrado
                else
                    std::cout << "No existe el comando seleccionado. Utilice 'help' para ver la lista de comandos"
                                 " disponibles";
            } else {
                auto it = commandList.begin();
                std::cout << "---------------------------------\n";

                while (it != commandList.end()) {
                    std::cout << it->second << '\n';
                    std::cout << "---------------------------------\n";
                    ++it;

                }
            }
        } else if (mainCommand == "report") {
            if (commandline >> mainCommand) {
                if (currentAgency != "") {
                    if (mainCommand == "flights") {
                        //TODO
                    } else if (mainCommand == "inventory") {
                        //TODO
                    }
                } else
                    std::cout << "No ha iniciado sesión.";
            }
        } else if (mainCommand == "sell") {
            if (currentAgency != "")
                if (commandline >> mainCommand) {
                    if (commandline >> mainCommand) {
		      std::string CustomerID;
                      std::string Customer;
                      std::string buyHour;
                      std::string buyDate;
                      std::cout<<"- Ingrese su numero de identificación antecedido de el tipo de documento.\n";
                      std::cout<<"- Ejemplo: CC1233691510.";
                      std::cout<<"Documento: ";
                      std::getline(std::cin, CustomerID);
                      std::cout<<"\n- Ingrese su nombre con este formato: Apellido1 Apellido2, Nombre1 Nombre2 \n";
                      std::getline(std::cin, Customer);
                      buyHour=(std::to_string(std::localtime(&result).tm_hour))+(std::to_string(std::localtime(&result).tm_min));
                      buyDate=(std::to_string(std::localtime(&result).tm_year+1900))+(std::localtime(&result).tm_mon+1)+(std::localtime(&result).tm_mday);
                      if(a.Sell(arg1,arg2,currentAgency,CustomerID,Customer,buyDate,buyHour)){
                        std::cout<<"-Operacion exitosa.\n";
                      }
                      else{
                        std::cout<<"-Datos invalidos.\n"
                      }

                    } else
                        std::cout << "- Falta segundo Argumento.\n";
                } else
                    std::cout << "- Sin argumentos válidos";
            else
                std::cout << "No ha iniciado sesión";

        }

    }
}
