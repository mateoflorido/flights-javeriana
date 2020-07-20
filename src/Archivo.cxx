#include <fstream>
#include <sstream>
#include <iostream>
#include "Archivo.h"

void
ReadSales(FJA::Aeronautica &a, std::string filename) {
  std::ifstream input(filename); // Open file
  std::string token; // Create token
  std::string line; // Create store line
  std::getline(input, line); // Get line from File
  std::istringstream ss(line); // Create stream with line

  //------Arguments from Stream
  std::string agencyN;
  std::string id;
  std::string flight;
  std::string customerID;
  std::string customer;
  std::string flightDate;
  std::string buyDate;
  std::string buyHour;

  while (input) { // Read until end of file
    std::getline(ss, token, '_');
    agencyN = token;
    std::getline(ss, token, ';');
    id = token;
    std::getline(ss, token, ';');
    flight = token;
    if (flight.empty()) {
      flight.clear();
    }
    std::getline(ss, token, ';');
    customer = token;
    std::getline(ss, token, ';');
    customerID = token;
    std::getline(ss, token, ';');
    flightDate = token;
    std::getline(ss, token, ';');
    buyDate = token;
    std::getline(ss, token, ';');
    buyHour = token;
    a.NewSale(agencyN, id, flight, customerID, customer, flightDate, buyDate, buyHour); // Create and add sale
    std::getline(input, line);
    ss.clear();
    ss.str(line);
  }

  input.close();
}

void
ReadFlights(FJA::Aeronautica &a, std::string filename) {

  std::ifstream input(filename); //Open file
  std::string token; // Create Token
  std::string line; // Create store line
  std::getline(input, line); // Get line from File
  std::istringstream ss(line); //Create stream with line


  //------Arguments from Stream
  std::string code;
  std::string day;
  std::string from;
  std::string to;
  std::string hour;
  unsigned int flightd;
  unsigned int cap;
  unsigned long price;

  while (input) { // Read until end of file

    std::getline(ss, token, ';');
    code = token;
    std::getline(ss, token, ';');
    day = token;
    std::getline(ss, token, ';');
    from = token;
    std::getline(ss, token, ';');
    to = token;
    std::getline(ss, token, ';');
    hour = token;
    std::getline(ss, token, ';');
    flightd = static_cast<unsigned int>(std::stoi(token));
    std::getline(ss, token, ';');
    cap = static_cast<unsigned int>(std::stoi(token));
    std::getline(ss, token, ';');
    price = static_cast<unsigned long>(std::stol(token));
    try {
      a.NewRoute(code, day, from, to, hour, flightd, cap, price); // Create and add new flight read
    }
    catch (std::exception &e) {
      std::cout << "Ruta " + code + " ya registrada.\n";
    }
    std::getline(input, line);
    ss.clear();
    ss.str(line);
  }

  input.close();

}

void
ReadAgencies(FJA::Aeronautica &a, std::string filename) {
  std::ifstream input(filename); //Open file
  std::string token;// Create token
  std::string line; // Create store
  std::getline(input, line);// Get line form file
  std::istringstream ss(line);// Create stream with line

  //--------------Arguments from Stream

  std::string agencyN;
  std::string agencyPassW;

  while (input) { // Read until end of file

    std::getline(ss, token, ';');
    agencyN = token;
    std::getline(ss, token, ';');
    token.erase(token.end() - 1, token.end());
    agencyPassW = token;
    try {
      a.NewAgency(agencyN, agencyPassW); // Create and add new agency read
    }
    catch (const std::exception &e) {
      std::cout << "Agencia " + agencyN + " ya registrada.\n";
    }

    std::getline(input, line);
    ss.clear();
    ss.str(line);

  }
  input.close();

}

void
SaveSales(std::string &salesReport) {
  std::ofstream output;
  output.open("tickets.txt");
  output << salesReport;
  output.close();
}
