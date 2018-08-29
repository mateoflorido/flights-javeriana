#ifndef FLIGHTS_JAVERIANA_ARCHIVO_H
#define FLIGHTS_JAVERIANA_ARCHIVO_H

#include "Aeronautica.h"

/**
 * @brief
 * @param a
 * @param filename
 */
void ReadFlights(FJA::Aeronautica &a, std::string filename);

/**
 * @brief
 * @param a
 * @param filename
 */
void ReadAgencies(FJA::Aeronautica &a, std::string filename);

/**
 * @brief
 * @param a
 * @param filename
 */
void ReadSales(FJA::Aeronautica &a, std::string filename);

/**
 * @brief
 * @param salesReport
 */
void SaveSales(std::string &salesReport);

#endif //FLIGHTS_JAVERIANA_ARCHIVO_H
