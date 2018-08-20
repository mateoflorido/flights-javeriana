//
// Created by florido on 20/08/18.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "Archivo.h"
void ReadSales(FJA::Aeronautica &a, std:: string filename){
    std::ifstream input(filename); // Open file
    std::string token; // Create token 
    std::string line; // Create store line
    std::getline(input,line); // Get line from File
    std::istringstream ss(line); // Create stream with line

    //------Arguments from Stream
    std::string angencyN;
    std::string id;
    std::string flight;
    std::string customerID;
    std::string customer;
    unsigned int flighDate;
    unsigned int buyDate;
    unsigned int buyHour;

    while (input){ // Read until end of file
	std::getline(ss, token, '_');
	agencyN = token;
	std::getline(ss, token , ';');
	id= token;
	std::getline(ss, token , ';');
	flight= token;
	std::getline(ss, token, ';');
	customerID= token;
	std::getline(ss, token, ';');
	customer= token;
	std::getline(ss, token, ';');
	flightDate= std::stoi(token);
	std::getline(ss, token, ';');
	buyDate= std::stoi(token);
	std::getline(ss, token, ';');
	buyHour= std::stoi(token);
	a.NewSale(agencyN, id, flight, customerID, customer, flightDate, buyDate, buyHour); // Create and add sale
	std::getline(input,line);
	ss.clear();
	ss.str(line);
     }

   input.close();
}
void ReadFlights(FJA::Aeronautica &a, std::string filename) {


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
    unsigned int hour;
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
            hour = std::stoi(token);
            std::getline(ss, token, ';');
            flightd = std::stoi(token);
            std::getline(ss, token, ';');
            cap = std::stoi(token);
            std::getline(ss, token, ';');
            price = std::stol(token);
            a.NewRoute(code, day, from, to, hour, flightd, cap, price); // Create and add new flight read
	    std::getline(input,line);
	    ss.clear();
	    ss.str(line);
    }

    input.close();

}

void ReadAgencies(FJA::Aeronautica &a, std::string filename) {
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
        std::cout << token;
        std::getline(ss, token, ';');
        agencyPassW = token;
        a.NewAgency(agencyN, agencyPassW); // Create and add new agency read
        std::getline(input, line);
        ss.clear();
        ss.str(line);

    }
    input.close();

}