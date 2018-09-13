#include <sstream>
#include <ctime>
#include "Consola.h"
#include <iomanip>
#include <iostream>
#include "Archivo.h"

std::unordered_map<std::string, std::string> ReadCommands() {
    std::unordered_map<std::string, std::string> commandList;
    commandList = {

            {"exit",        "exit: exit "
                            "\n Cierra todas las sesiones y finaliza la ejecución del programa"
            },
            {"report",      "report: report <Modo> [arg1] [arg2]"
                            "\n Permite realizar un reporte detallado."
                            "\n Genera un reporte detallado del modo seleccionado."
                            "\n Argumentos <Modo>:"
                            "\n \t Modo\t Selecciona un modo Válido entre"
                            "\n \t \t flights: Genera un reporte de todos los vuelos con sillas disponibles"
                            "\n \t \t inventory: Genera un reporte de todos los vuelos vendidos, cambiados o cancelados de una agencia de viajes"
                            "\n \t \t money: Genera un reporte de las ventas informando los activos y pasivos de la agencia"
                            "\n \n Argumentos [arg1] [arg2]"
                            "\n*Unicamente Modo flights*"
                            "\n \t arg1: Origen de los vuelos a incluir en el reporte"
                            "\n \t arg2: Fecha de los vuelos a incluir en el reporte"
            },

            {"sell",        "sell: sell <IDVuelo> <Fecha> "
                            "\n Realiza la venta de un vuelo determinado en una fecha seleccionada "
                            "\n Argumentos :"
                            "\n \t \t \tIDVuelo: Identificador del vuelo seleccionado"
                            "\n \t \t \tFecha: Fecha del vuelo seleccionado"
                            "\n Estado de Salida: \nGenera una venta del vuelo seleccionado"
            },
            {
             "logout",      "logout: logout"
                            "\n Permite cerrar sesión en una agencia"
                            "\n Estado de Salida:"
                            "\n Cierra la sesión siempre que exista una abierta"
            },
            {
             "login",       "login: login <idagencia>"
                            "\n Permite iniciar sesión en una agencia"
                            "\n Permite iniciar sesión en una agencia cuando el IDAGENCIA es válido"
                            "\n Argumentos:\n \t \t \t IDAGENCIA\t Indica el ID de una agencia válida."
            },

            {"read",        "read: sell <Modo> "
                            "\n Realiza la lectura de los datos en persistencia "
                            "\n Argumentos <Modo> :"
                            "\n \t \t \tflights: Lee los vuelos programados por la Aeronautica Civil"
                            "\n \t \t \tagencies: Lee las agencias disponibles en el sistema"
                            "\n \t \t \tsales: Lee las ventas realizadas por las agencias"
                            "\n Estado de Salida: \nLee un archivo con éxito."
            },
            {"cancel",      "cancel: cancel <id> "
                            "\nCancela un vuelo o paquete "
                            "\n Argumentos <id> :"
                            "\n \t \t \t id: Es el identificador de un vuelo."
                            "\n Estado de Salida: \nCancela el vuelo."
            },
            {"consolidate", "consolidate: consolidate "
                            "\nElimina de la base de datos trasacciones pasadas ya realizadas. "
                            "\n Estado de Salida: \nLimpia la base de datos de transacciones pasadas."
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
    ReadAgencies(*a, "./passwords.txt");
    ReadFlights(*a, "./flights.txt");
    ReadSales(*a, "./tickets.txt");

    while (command != "exit") {
        std::cout << "\n" << currentAgency << " $ ";

        command.clear();
        std::getline(std::cin, command);
        commandline.clear();
        commandline.str(command);
        commandline >> mainCommand;


        if (mainCommand == "login") {
            if (currentAgency.empty()) {
                if (commandline >> arg1) {
                    if (commandline >> arg2) {
                        if (a->CheckLogin(arg1, arg2)) {
                            currentAgency = arg1;
                        } else {
                            currentAgency = "";
                            std::cout << "Usuario o Contraseña no Válidos";
                        }
                    }
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
                if (commandline >> arg1) {
                    if (mainCommand == "flights")
                        ReadFlights(*a, arg1);
                    else if (mainCommand == "agencies")
                        ReadAgencies(*a, arg1);
                    else if (mainCommand == "sales")
                        ReadSales(*a, arg1);
                } else
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
                                std::cout << a->ReportFlights(arg1, arg2);
                            }
                        } else {
                            std::cout << a->ReportFlights(" ", " ");

                        }
                    } else if (mainCommand == "inventory") {
                        std::cout << a->ReportInventory(currentAgency);
                    } else if (mainCommand == "money") {
                        //TODO Enviar a Aeronautica e Imprimir
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
                    std::cout << "- Sin argumentos válidos.\n";
            else
                std::cout << "No ha iniciado sesión. \n";

        } else if (mainCommand == "cancel") {
            if(commandline >> arg1){
                if(a->CancelFLight(arg1,currentAgency))
                    std::cout << "Operación exitosa.\n";
                else
                    std::cout << "Datos invalidos.\n";
            }
            else{
                std::cout << "- Sin argumentos válidos.\n";
            }

        } else if (mainCommand == "consolidate") {
            //TODO Consolidate
        } else if (mainCommand == "exit") {
            arg1 = a->SalesReport();
            SaveSales(arg1);
        }

    }
}