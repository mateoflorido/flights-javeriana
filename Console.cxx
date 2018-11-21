// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <ctime>
#include "Console.h"
#include "Archivo.h"

// -------------------------------------------------------------------------
Console::
Console()
        : Superclass() {
}

// -------------------------------------------------------------------------
Console::
Console(const std::string &prompt)
        : Superclass(prompt) {
    this->Greet();
    ReadAgencies(this->m_Aero, "./passwords.txt");
    ReadFlights(this->m_Aero, "./flights.txt");
    ReadSales(this->m_Aero, "./tickets.txt");
    this->m_Aero.GraphInitialize();
    std::vector<std::string> IDs = this->m_Aero.GetIDAgencies();
    auto itID = IDs.begin();
    for (; itID != IDs.end(); itID++) {
        this->m_Trie.Insert("login " + (*itID));
    }
}

// -------------------------------------------------------------------------
Console::
~Console() {
}

// -------------------------------------------------------------------------
int Console::
trigger(const std::string &s) {

    std::stringstream commandline(s);
    std::string mainCommand;
    std::string arg1;
    std::string arg2;
    std::string arg3;

    commandline >> mainCommand;

    if (mainCommand == "")
        return (1);
    else if (mainCommand == "login") {
        if (this->m_Agency.empty()) {
            if (commandline >> arg1) {
                if (commandline >> arg2) {
                    if (this->m_Aero.CheckLogin(arg1, arg2)) {
                        this->m_Agency = arg1;
                        this->setPrompt(arg1 + "$ ");
                    } else {
                        this->m_Agency.clear();
                        std::cerr << "Usuario o Contraseña no Válidos\n";
                    }
                } else
                    std::cout << "No ha ingresado una contraseña.\n";
            } else
                std::cout << "No ha ingresado un usuario.\n";
        } else
            std::cerr << "Agencia: " << this->m_Agency << " Termine sesión para ingresar en otra cuenta.\n";
        return (1);
    } else if (mainCommand == "logout") {
        if (!this->m_Agency.empty()) {
            std::cout << " Cerrando Sesión de " << this->m_Agency << '\n';
            this->m_Agency.clear();
            this->m_Prompt = "$ ";
        } else
            std::cout << "No ha iniciado sesión.\n";
        return (1);
    } else if (mainCommand == "read") {
        if (commandline >> mainCommand) {
            if (commandline >> arg1) {
                if (arg1 == "flights")
                    ReadFlights(this->m_Aero, arg1);
                else if (arg1 == "agencies")
                    ReadAgencies(this->m_Aero, arg1);
                else if (arg1 == "sales")
                    ReadSales(this->m_Aero, arg1);
            } else
                std::cout << "Argumento no Válido: \n" << commandList.find("read")->second;
        }
        return (1);
    } else if (mainCommand == "help") {
        if (commandline >> arg1) {
            if (this->commandList.find(arg1) != commandList.end())
                std::cout << this->commandList.find(arg1)->second;
            else
                std::cout << "No existe el comando seleccionado. Utilice 'help' para ver la lista de comandos"
                             " disponibles \n";
        } else {
            auto it = this->commandList.begin();
            std::cout << "--------------------------------\n";
            while (it != this->commandList.end()) {
                std::cout << it->second << '\n';
                std::cout << "---------------------------------\n";
                ++it;
            }
        }
        std::cout << "\n";
        return (1);
    } else if (mainCommand == "report") {
        if (commandline >> mainCommand) {
            if (!this->m_Agency.empty()) {
                if (mainCommand == "flights") {
                    if (commandline >> arg1) {
                        if (commandline >> arg2) {
                            std::cout << this->m_Aero.ReportFlights(arg1, arg2);
                        }
                    } else {
                        std::cout << this->m_Aero.ReportFlights(" ", " ");

                    }
                } else if (mainCommand == "inventory") {
                    std::cout << this->m_Aero.ReportInventory(this->m_Agency);
                } else if (mainCommand == "money") {
                    std::cout << this->m_Aero.ReportMoney(this->m_Agency);
                }
            } else
                std::cout << "No ha iniciado sesión.\n";
        }
    } else if (mainCommand == "sell") {
        if (!this->m_Agency.empty())
            if (commandline >> arg1) {
                if (commandline >> arg2) {
                    std::string CustomerID;
                    std::string Customer;
                    std::string buyHour;
                    std::string buyDate;
                    std::cout << "- Ingrese su numero de identificación antecedido de el tipo de documento.\n";
                    std::cout << "- Ejemplo: CC1233691510.\n";
                    std::cout << "Documento: ";
                    std::getline(std::cin, CustomerID);
                    std::cout << "\n- Ingrese su nombre con este formato: Apellido1 Apellido2, Nombre1 Nombre2 \n";
                    std::getline(std::cin, Customer);
                    std::time_t result = std::time(nullptr);
                    buyHour = (std::to_string(std::localtime(&result)->tm_hour));
                    if (std::localtime(&result)->tm_min < 10)
                        buyHour += "0" + (std::to_string(std::localtime(&result)->tm_min));
                    else
                        buyHour += (std::to_string(std::localtime(&result)->tm_min));
                    buyDate = (std::to_string(std::localtime(&result)->tm_year + 1900));
                    if ((std::localtime(&result)->tm_mon + 1) < 10) {
                        buyDate += (std::to_string(std::localtime(&result)->tm_mon + 1)) + "0" +
                                   (std::to_string((std::localtime(&result)->tm_mday)));

                    } else {
                        buyDate += (std::to_string(std::localtime(&result)->tm_mon + 1)) +
                                   (std::to_string((std::localtime(&result)->tm_mday)));
                    }

                    if (this->m_Aero.Sell(arg1, arg2, this->m_Agency, CustomerID, Customer, buyDate, buyHour)) {
                        std::cout << "-Operacion exitosa.\n";
                    } else {
                        std::cout << "-Datos invalidos.\n";
                    }

                } else
                    std::cout << "- Falta segundo Argumento.\n";
            } else
                std::cout << "- Sin argumentos válidos.\n";
        else
            std::cout << "No ha iniciado sesión.\n";

    } else if (mainCommand == "cancel") {
        if (commandline >> arg1) {
            if (this->m_Aero.CancelFlight(arg1, this->m_Agency))
                std::cout << "Operación exitosa.\n";
            else
                std::cout << "Datos invalidos.\n";
        } else {
            std::cout << "- Sin argumentos válidos.\n";
        }

    } else if (mainCommand == "consolidate") {
        std::string currentDate;
        std::time_t result = std::time(nullptr);
        currentDate = (std::to_string(std::localtime(&result)->tm_year + 1900));
        if ((std::localtime(&result)->tm_mon + 1) < 10) {
            currentDate += (std::to_string(std::localtime(&result)->tm_mon + 1));
            if ((std::localtime(&result)->tm_mday) < 10) {
                currentDate += "0" + (std::to_string(std::localtime(&result)->tm_mday));
            } else
                currentDate += (std::to_string(std::localtime(&result)->tm_mday));

        } else {
            currentDate += (std::to_string(std::localtime(&result)->tm_mon + 1));
            if ((std::localtime(&result)->tm_mday) < 10) {
                currentDate += "0" + (std::to_string(std::localtime(&result)->tm_mday));
            } else
                currentDate += (std::to_string(std::localtime(&result)->tm_mday));
        }
        this->m_Aero.Consolidate(currentDate);
        std::cout << "Consolidate Exitoso\n";
    } else if (mainCommand == "change") {
        if (!this->m_Agency.empty()) {
            if (commandline >> arg1) {
                if (commandline >> arg2) {
                    if (commandline >> arg3) {
                        std::string CustomerID = arg1;
                        std::string IDFlightO = arg2;
                        std::string IDFlightN = arg3;
                        std::string buyHour;
                        std::string buyDate;
                        std::string date;
                        float newPrice = 0;
                        std::time_t result = std::time(nullptr);
                        buyHour = (std::to_string(std::localtime(&result)->tm_hour));
                        if (std::localtime(&result)->tm_min < 10)
                            buyHour += "0" + (std::to_string(std::localtime(&result)->tm_min));
                        else
                            buyHour += (std::to_string(std::localtime(&result)->tm_min));
                        buyDate = (std::to_string(std::localtime(&result)->tm_year + 1900));
                        if ((std::localtime(&result)->tm_mon + 1) < 10) {
                            buyDate += (std::to_string(std::localtime(&result)->tm_mon + 1)) + "0" +
                                       (std::to_string((std::localtime(&result)->tm_mday)));

                        } else {
                            buyDate += (std::to_string(std::localtime(&result)->tm_mon + 1)) +
                                       (std::to_string((std::localtime(&result)->tm_mday)));
                        }
                        std::cout << "Ingrese la fecha en la que desea viajar: ";
                        std::cin >> date;
                        if (this->m_Aero.ChangeSale(CustomerID, IDFlightO, IDFlightN, this->m_Agency, buyHour, buyDate,
                                                    date, newPrice)) {
                            std::cout << "Operacion exitosa " << std::endl;
                            if (newPrice < 0) {
                                newPrice = abs(newPrice);
                                std::cout << "La tarifa disminuye " << newPrice << std::endl;
                            } else {
                                if (newPrice == 0) {
                                    std::cout << "No existe cambio en la tarifa ";
                                }
                                std::cout << "La tarifa aumenta " << newPrice << std::endl;
                            }
                        } else {
                            std::cout << "Datos invalidos" << std::endl;
                        }
                    } else
                        std::cout << "Falta tercer argumento " << std::endl;
                } else
                    std::cout << "Falta segundo argumento" << std::endl;
            } else
                std::cout << "Sin argumentos validos" << std::endl;
        }
    } else if(mainCommand == "path") {
        if(!this->m_Agency.empty()){
            if(commandline >> arg1){
                if(commandline >> arg2){
                    this->m_Aero.RecommendedRoutes(arg1,arg2);
                }
                else{
                    std::cout<<"Falta segundo argumento" << std::endl;
                }
            }
            else{
                std::cout << "Sin argumentos validos" << std::endl;
            }
        }
        else{
            std::cout<<"No ha iniciado sesion"<<std::endl;
        }
    }
    else if (mainCommand == "exit") {
        mainCommand = this->m_Aero.SalesReport();
        SaveSales(mainCommand);
        this->quit();
        return (1);
    } else {
        std::cerr << "Comando Desconocido: " << s << std::endl;
        return (0);
    } // end if
}

// -------------------------------------------------------------------------
int Console::
hotkeys(char c) {
    if (c == Superclass::TAB) {

        if (!this->getBuffer().empty()) {
            // Clear actual prefix
            std::string now;
            if (this->getBuffer() == this->lastSuggestion) {
                this->m_Trie.AllCoincidence(this->lastComplete, now);
                std::cout << now;
                std::cout << std::endl;

            } else {
                this->m_Trie.Coincidence(this->getBuffer(), now);
                this->lastComplete = this->getBuffer();
                if (!now.empty()) {
                    for (int i = 0; i < this->m_LinePos; ++i)
                        std::cout << "\b \b";
                    this->setBuffer(now);
                    this->lastSuggestion = now;
                    std::cout << this->getBuffer();
                    this->m_LinePos = this->m_Buffer.size();
                    this->m_Trie.AllCoincidence(this->lastComplete, now);
                }
            }
        }
    } else
        return (0);
}

//---------------------------------------------------------------------------
void Console::
Greet() {

    std::time_t result = std::time(nullptr);
    std::cout << "Bienvenido a Viajes Javeriana v0.1 alpha\n"
              << "Hoy es: "
              << std::asctime(std::localtime(&result))
              << "\nRecuerde Iniciar Sesión con el comando login <idagencia> <mot de passe>\n"
              << "En caso de necesitar ayuda use help\n";
}


// eof - Console.cxx