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
            if (currentAgency.empty()) {
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
            if (!currentAgency.empty()) {
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
                if (!currentAgency.empty()) {
                    if (mainCommand == "flights") {
                        if (commandline >> arg1) {
                            if (commandline >> arg2) {
                                std::vector<FJA::Ruta> rutas2;
                                rutas2 = a->ReportFlights(arg1, arg2);
                                if (!rutas2.empty()) {
                                    auto itRutas2 = rutas2.begin();
                                    std::cout << "Flights: \n";
                                    std::cout << setw(6) <<"Codigo"<< setw(10) << "Dia" << setw(14) << "Origen" << setw(14)
                                              << "Destino" << setw(5) << "Hora" << setw(9) <<"Duración "<< setw(10) << "Capacidad " << setw(12) << "Precio \n";
                                    for (; itRutas2 != rutas2.end(); itRutas2++) {
                                        std::cout << setw(6) << itRutas2->GetCode() << setw(10) << itRutas2->GetWeekDay() << setw(14) << itRutas2->GetOrigin() << setw(14)
                                                  << itRutas2->GetDestination() << setw(5) << itRutas2->GetHour() << setw(9) <<itRutas2->GetDuration() << setw(10) << irRutas2->GetCapacity() << setw(12) << itRutas2->GetPrice()<<"\n";
                                    }
                                } else
                                    std::cout << "No hay coincidencias.\n";
                            }
                        } else {
                            std::vector<FJA::Ruta> rutas;
                            rutas = a->ReportFlights(" ", " ");
                            if (!rutas.empty()) {
                                auto itRutas = rutas.begin();
                                std::cout << "Flights: \n";
                                std::cout << setw(6) <<"Codigo"<< setw(10) << "Dia" << setw(14) << "Origen" << setw(14)
                                << "Destino" << setw(5) << "Hora" << setw(9) <<"Duración "<< setw(10) << "Capacidad " << setw(12) << "Precio \n";
                                for (; itRutas != rutas.end(); itRutas++) {
                                    std::cout << setw(6) << itRutas->GetCode() << setw(10) << itRutas->GetWeekDay() << setw(14) << itRutas->GetOrigin() << setw(14)
                                              << itRutas->GetDestination() << setw(5) << itRutas->GetHour() << setw(9) <<itRutas->GetDuration() << setw(10) << irRutas->GetCapacity() << setw(12) << itRutas->GetPrice()<<"\n";
                                }
                            } else
                                std::cout << "No hay coincidencias.\n";
                        }
                    } else if (mainCommand == "inventory") {
                        //TODO
                    }
                } else
                    std::cout << "No ha iniciado sesión.";
            }
        } else if (mainCommand == "sell") {
            if (!currentAgency.empty())
                if (commandline >> arg1) {
                    if (commandline >> arg2) {
                        std::string CustomerID;
                        std::string Customer;
                        std::string buyHour;
                        std::string buyDate;
                        std::cout << "- Ingrese su numero de identificación antecedido de el tipo de documento.\n";
                        std::cout << "- Ejemplo: CC1233691510.";
                        std::cout << "Documento: ";
                        std::getline(std::cin, CustomerID);
                        std::cout << "\n- Ingrese su nombre con este formato: Apellido1 Apellido2, Nombre1 Nombre2 \n";
                        std::getline(std::cin, Customer);
                        buyHour = (std::to_string(std::localtime(&result)->tm_hour)) +
                                  (std::to_string(std::localtime(&result)->tm_min));
                        buyDate = (std::to_string(std::localtime(&result)->tm_year + 1900)) + "0" +
                                  (std::to_string(std::localtime(&result)->tm_mon + 1)) + (std::to_string(
                                (std::localtime(&result)->tm_mday)));
                        if (a->Sell(arg1, arg2, currentAgency, CustomerID, Customer, buyDate, buyHour)) {
                            std::cout << "-Operacion exitosa.\n";
                        } else {
                            std::cout << "-Datos invalidos.\n";
                        }

                    } else
                        std::cout << "- Falta segundo Argumento.\n";
                } else
                    std::cout << "- Sin argumentos válidos";
            else
                std::cout << "No ha iniciado sesión";

        } else if (mainCommand == "exit") {
            arg1 = a->SalesReport();
            SaveSales(arg1);
        }

    }
}
