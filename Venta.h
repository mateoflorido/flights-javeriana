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

        Venta(const std::string &m_ID, const std::string &m_Agency, const std::string &m_Flight,
              const std::string &m_CustomerID, const std::string &m_Customer,
              const std::string &m_FlightDate, const std::string &m_BuyDate,
              const std::string &m_BuyHour);

        virtual ~Venta();

        const std::string &GetID() const;

        const std::string &GetAgency() const;

        const std::string &GetFlight() const;

        const std::string &GetCustomerID() const;

        const std::string &GetCustomer() const;

        const std::string &GetFlightDate() const;

        const std::string &GetBuyDate() const;

        const std::string &GetBuyHour() const;

        void SetID(const std::string &m_ID);

        void SetAgency(const std::string &m_Agency);

        void SetFlight(const std::string &m_Flight);

        void SetCustomerID(const std::string &m_CustomerID);

        void SetCustomer(const std::string &m_Customer);

        void SetFlightDate(const std::string &m_FlightDate);

        void SetBuyDate(const std::string &m_BuyDate);

        void SetBuyHour(const std::string &m_BuyHour);

    protected:
        std::string m_ID;
        std::string m_Agency;
        std::string m_Flight;
        std::string m_CustomerID;
        std::string m_Customer;
        std::string m_FlightDate;
        std::string m_BuyDate;
        std::string m_BuyHour;

    };
}

#endif //FLIGHTS_JAVERIANA_VENTA_H
