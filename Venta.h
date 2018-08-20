//
// Created by florido on 19/08/18.
//

#ifndef FLIGHTS_JAVERIANA_VENTA_H
#define FLIGHTS_JAVERIANA_VENTA_H

#include <string>

namespace FJA {
    class Venta {
    public:
        Venta();

        Venta(const std::string &m_Agency, const std::string &m_ID, const std::string &m_Flight,
              const std::string &m_CustomerID, const std::string &m_Customer,
              const unsigned int &m_FlightDate, const unsigned int &m_BuyDate,
              const unsigned int &m_BuyHour);

        virtual ~Venta();

        const std::string &GetID() const;

        const std::string &GetAgency() const;

        const std::string &GetFlight() const;

        const std::string &GetCustomerID() const;

        const std::string &GetCustomer() const;

        const unsigned int &GetFlightDate() const;

        const unsigned int &GetBuyDate() const;

        const unsigned int &GetBuyHour() const;

        void SetID(const std::string &m_ID);

        void SetAgency(const std::string &m_Agency);

        void SetFlight(const std::string &m_Flight);

        void SetCustomerID(const std::string &m_CustomerID);

        void SetCustomer(const std::string &m_Customer);

        void SetFlightDate(const unsigned int &m_FlightDate);

        void SetBuyDate(const unsigned int &m_BuyDate);

        void SetBuyHour(const unsigned int &m_BuyHour);

    protected:
        std::string m_Agency;
        std::string m_ID;
        std::string m_Flight;
        std::string m_CustomerID;
        std::string m_Customer;
        unsigned int m_FlightDate;
        unsigned int m_BuyDate;
        unsigned int m_BuyHour;

    };
}

#endif //FLIGHTS_JAVERIANA_VENTA_H
