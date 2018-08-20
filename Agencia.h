//
// Created by florido on 19/08/18.
//

#ifndef FLIGHTS_JAVERIANA_AGENCIA_H
#define FLIGHTS_JAVERIANA_AGENCIA_H

#include <string>
#include <vector>
#include "Venta.h"

namespace FJA {
    class Agencia {
    public:
        Agencia();

        virtual ~Agencia();

        const std::string &GetAgencyID() const;

        const std::string &GetPassword() const;

        const std::vector<Venta> &GetSales() const;

        void SetAgencyID(const std::string &m_AgencyID);

        void SetPassword(const std::string &m_Password);

        void SetSales(const std::vector<Venta> &m_Sales);

        void NewSale(const std::string &m_Agency, const std::string &m_ID, const std::string &m_Flight,
                     const std::string &m_CustomerID,
                     const std::string &m_Customer, const unsigned int &m_FlightDate, const unsigned int &m_BuyDate,
                     const unsigned int &m_BuyHour);

    protected:
        std::string m_AgencyID;
        std::string m_Password;
        std::vector<Venta> m_Sales;

    };
}

#endif //FLIGHTS_JAVERIANA_AGENCIA_H
