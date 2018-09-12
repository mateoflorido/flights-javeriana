#ifndef FLIGHTS_JAVERIANA_ARCHIVO_H
#define FLIGHTS_JAVERIANA_ARCHIVO_H

#include "Aeronautica.h"

/**
 * @brief Este metodo lee el archivo con las rutas
 * @param a Representa la aeronautica en donde se van a guardar las rutas
 * @param filename Representa el nombre del archivo de las rutas
 */
void ReadFlights(FJA::Aeronautica &a, std::string filename);

/**
 * @brief Este método lee el archivo con las agencias
 * @param a Representa la aeronautica en donde se van a guardar las rutas
 * @param filename Representa el nombre de el archivo de las rutas
 */
void ReadAgencies(FJA::Aeronautica &a, std::string filename);

/**
 * @brief Este método lee el archivo de las ventas de las agencias
 * @param a Representa la aeronautica en donde se van a guardar las ventas
 * @param filename Representa el nombre del archivo de las ventas
 */
void ReadSales(FJA::Aeronautica &a, std::string filename);

/**
 * @brief Este método guarda los cambios en las ventas
 * @param salesReport Representa la cadena de caracteres con todas las ventas de todas las agencias
 */
void SaveSales(std::string &salesReport);

#endif //FLIGHTS_JAVERIANA_ARCHIVO_H