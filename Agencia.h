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
         * @return
         */
        std::string SalesReport();

    protected:
        std::string m_AgencyID;
        std::string m_Password;
        std::vector<Venta> m_Sales;

    };
}

#endif //FLIGHTS_JAVERIANA_AGENCIA_H
