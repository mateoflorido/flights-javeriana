//
// Created by florido on 20/08/18.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "Archivo.h"

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

    while (input) {
        while (std::getline(ss, token, ';')) {
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
            a.NewRoute(code, day, from, to, hour, flightd, cap, price);
        }
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
    std::string agencyN;//Create agency name store
    std::string agencyPassW;// Create agency password store
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
