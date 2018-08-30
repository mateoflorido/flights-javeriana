#ifndef FLIGHTS_JAVERIANA_AERONAUTICA_H
#define FLIGHTS_JAVERIANA_AERONAUTICA_H

#include <vector>
#include "Agencia.h"
#include "Ruta.h"
#include <random>
#include <sstream>

namespace FJA {
    class Aeronautica {
    public:
        Aeronautica();

        Aeronautica(const std::vector<Agencia> &m_Agencies, const std::vector<Ruta> &m_Routes);

        virtual ~Aeronautica();

        /**
         * @brief Este método crea una agencia en la aeronautica 
         * @param name Representa el nombre de la agencia	
         * @param password Representa la contraseña de la agencia
         */
        void NewAgency(const std::string &name, const std::string &password);

        /**
         * @brief Este método crea una ruta en la aeronautica
         * @param m_Code Representa el código de la ruta
         * @param m_WeekDay Representa el día en que la ruta opera
         * @param m_Origin Representa la ciudad origen de la ruta
         * @param m_Destination Representa el destino de la ruta
         * @param m_Hour Representa la hora de salida de la ruta
         * @param m_FlightDuration Representa la duración de vuelo
         * @param m_Capacity Representa la capacidad de la ruta
         * @param m_Price Representa el precio por silla de la ruta
         */
        void NewRoute(const std::string &m_Code, const std::string &m_WeekDay, const std::string &m_Origin,
                      const std::string &m_Destination, const std::string &m_Hour, const unsigned int &m_FlightDuration,
                      const unsigned int &m_Capacity, const unsigned long &m_Price);

        /**
         * @brief Este método crea una venta en una agencia
         * @param m_Agency Representa el nombre de la agencia en donde se va a hacver la ruta
         * @param m_ID Representa el ID de la venta
         * @param m_Flight Representa el codigo de la ruta
         * @param m_CustomerID Representa el documento del cliente
         * @param m_Customer Representa el nombre del cliente
         * @param m_FlightDate Representa la fecha de la ruta
         * @param m_BuyDate Representa la fecha de la venta
         * @param m_BuyHour Representa la hora de la venta
         */
        void NewSale(const std::string &m_Agency, const std::string &m_ID, const std::string &m_Flight,
                     const std::string &m_CustomerID,
                     const std::string &m_Customer, const std::string &m_FlightDate, const std::string &m_BuyDate,
                     const std::string &m_BuyHour);

        /**
         * @brief Este método realiza y guarda una nueva venta
         * @param IdVuelo Representa el ID de la ruta
         * @param fecha Representa la fecha de la ruta
         * @param currentAgency Representa la agencia con cesión iniciada
         * @param CustomerID Representa el documento del cliente
         * @param Customer Representa el nombre del cliente
         * @param buyDate Representa la fecha de la venta
         * @param buyHour Representa la hora de la venta
         * @return Retorna la confirmación, o no, de la venta exitosa 
         */
        bool Sell(const std::string &IdVuelo, const std::string &fecha, const std::string &currentAgency,
                  const std::string &CustomerID, const std::string &Customer, const std::string &buyDate,
                  const std::string &buyHour);

        /**
         * @brief Este método cuenta las sillas vendidas de una ruta
         * @param IdVuelo Represetna el ID de la ruta
         * @return Un numero entero con la cantidad de sillas vendidas
         */
        int ContarVentas(const std::string &IdVuelo);

        /**
         * @brief Este método varifica que una ruta opera en una fecha especificada
         * @param fecha Representa la fecha supuesta de el vuelo
         * @param dia Representa los días en que opera la ruta
         * @return La confirmación de si opera, o no, en la fecha dada
         */
        bool VerificarFechas(const std::string &fecha, const std::string &dia);

        /**
         * @brief Este método verifica si la agencia y contraseña son correctos
         * @param m_AgencyID Representa el nombre de la agencia
         * @param m_Password Representa la contraseña de la agencia
         * @return La comfirmación, o no, de si son correctos los datos
         */
        bool CheckLogin(const std::string &m_AgencyID, const std::string &m_Password);

        /**
         * @brief Este método saca los reportes de venta de las agencias
         * @return Una cadena de caracteres con los resportes de venta de las agencias
         */
        std::string SalesReport();

        /**
         * @brief Este método saca los reportes de las rutas con origen y fecha especificada
         * @param origen Representa el origen de las rutas que se van a reportar
         * @param fecha Representa la fecha de las rutas que se van a reportar
         * @return Una cadena de caracteres con el reporte de las rutas especificadas
         */
        std::string ReportFlights(std::string origen, std::string fecha);

        /**
         * @brief Este método saca los reportes de las ventas, cambios y cancelaciones 
         * @param AgencyID Representa Representa la agencia que tiene las ventas
         * @return Una cadena de caracteres con el reporte de todos los tipos de ventas
         */
        std::string ReportInventory(std::string AgencyID);

    protected:
        typedef std::vector<Agencia> TAgencies;
        typedef std::vector<Ruta> TRoutes;

    protected:
        TAgencies m_Agencies;
        TRoutes m_Routes;
    };
}

#endif //FLIGHTS_JAVERIANA_AERONAUTICA_H
