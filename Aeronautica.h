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
         * @brief
         * @param name
         * @param password
         */
        void NewAgency(const std::string &name, const std::string &password);

        /**
         * @brief
         * @param m_Code
         * @param m_WeekDay
         * @param m_Origin
         * @param m_Destination
         * @param m_Hour
         * @param m_FlightDuration
         * @param m_Capacity
         * @param m_Price
         */
        void NewRoute(const std::string &m_Code, const std::string &m_WeekDay, const std::string &m_Origin,
                      const std::string &m_Destination, const std::string &m_Hour, const unsigned int &m_FlightDuration,
                      const unsigned int &m_Capacity, const unsigned long &m_Price);

        /**
         * @brief
         * @param m_Agency
         * @param m_ID
         * @param m_Flight
         * @param m_CustomerID
         * @param m_Customer
         * @param m_FlightDate
         * @param m_BuyDate
         * @param m_BuyHour
         */
        void NewSale(const std::string &m_Agency, const std::string &m_ID, const std::string &m_Flight,
                     const std::string &m_CustomerID,
                     const std::string &m_Customer, const std::string &m_FlightDate, const std::string &m_BuyDate,
                     const std::string &m_BuyHour);

        /**
         * @brief
         * @param IdVuelo
         * @param fecha
         * @param currentAgency
         * @param CustomerID
         * @param Customer
         * @param buyDate
         * @param buyHour
         * @return
         */
        bool Sell(const std::string &IdVuelo, const std::string &fecha, const std::string &currentAgency,
                  const std::string &CustomerID, const std::string &Customer, const std::string &buyDate,
                  const std::string &buyHour);

        /**
         * @brief
         * @param IdVuelo
         * @return
         */
        int ContarVentas(const std::string &IdVuelo);

        /**
         * @brief
         * @param fecha
         * @param dia
         * @return
         */
        bool VerificarFechas(const std::string &fecha, const std::string &dia);

        /**
         * @brief
         * @param m_AgencyID
         * @param m_Password
         * @return
         */
        bool CheckLogin(const std::string &m_AgencyID, const std::string &m_Password);

        /**
         * @brief
         * @return
         */
        std::string SalesReport();

        std::vector<Ruta> ReportFlights(std::string origen, std::string fecha);

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
