//
// Created by florido on 19/08/18.
//

#ifndef FLIGHTS_JAVERIANA_AERONAUTICA_H
#define FLIGHTS_JAVERIANA_AERONAUTICA_H

#include <vector>
#include "Agencia.h"
#include "Ruta.h"
#include <random>

namespace FJA {
    class Aeronautica {
    public:
        Aeronautica();

        Aeronautica(const std::vector<Agencia> &m_Agencies, const std::vector<Ruta> &m_Routes);

        virtual ~Aeronautica();

        void NewAgency(const std::string &name, const std::string &password);

        void NewRoute(const std::string &m_Code, const std::string &m_WeekDay, const std::string &m_Origin,
                      const std::string &m_Destination, const std::string &m_Hour, const unsigned int &m_FlightDuration,
                      const unsigned int &m_Capacity, const unsigned long &m_Price);

        void NewSale(const std::string &m_Agency, const std::string &m_ID, const std::string &m_Flight,
                     const std::string &m_CustomerID,
                     const std::string &m_Customer, const std::string &m_FlightDate, const std::string &m_BuyDate,
                     const std::string &m_BuyHour);

        bool Sell(const std::string &IdVuelo, const std::string &fecha, const std::string &currentAgency,
                  const std::string &CustomerID, const std::string &Customer, const std::string &buyDate,
                  const std::string &buyHour);

        int ContarVentas(const std::string &IdVuelo);

        bool VerificarFechas(const std::string &fecha, const std::string &dia);

        bool CheckLogin(const std::string &m_AgencyID, const std::string &m_Password);

    protected:
        typedef std::vector<Agencia> TAgencies;
        typedef std::vector<Ruta> TRoutes;

    protected:
        TAgencies m_Agencies;
        TRoutes m_Routes;
    };
}

#endif //FLIGHTS_JAVERIANA_AERONAUTICA_H
