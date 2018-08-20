//
// Created by florido on 19/08/18.
//

#include "Venta.h"

FJA::Venta::
Venta()
        : m_Agency(""),
          m_ID(""),
          m_Flight(""),
          m_CustomerID(""),
          m_Customer(""),
          m_FlightDate(),
          m_BuyDate(),
          m_BuyHour() {}


FJA::Venta::
Venta(const std::string &m_Agency, const std::string &m_ID, const std::string &m_Flight,
      const std::string &m_CustomerID,
      const std::string &m_Customer, const unsigned int &m_FlightDate, const unsigned int &m_BuyDate,
      const unsigned int &m_BuyHour)
        : m_Agency(m_Agency),
          m_ID(m_ID),
          m_Flight(m_Flight),
          m_CustomerID(m_CustomerID),
          m_Customer(m_Customer),
          m_FlightDate(m_FlightDate),
          m_BuyDate(m_BuyDate),
          m_BuyHour(m_BuyHour) {}

FJA::Venta::
~Venta() {}


const std::string
&

FJA::Venta::GetID() const {
    return (this->m_ID);
}

const std::string &FJA::Venta::GetAgency() const {
    return m_Agency;
}

const std::string &FJA::Venta::GetFlight() const {
    return (this->m_Flight);
}

const std::string &FJA::Venta::GetCustomerID() const {
    return (this->m_CustomerID);
}

const std::string &FJA::Venta::GetCustomer() const {
    return (this->m_Customer);
}

const unsigned int &FJA::Venta::GetFlightDate() const {
    return (this->m_FlightDate);
}

const unsigned int &FJA::Venta::GetBuyDate() const {
    return (this->m_BuyDate);
}

const unsigned int &FJA::Venta::GetBuyHour() const {
    return (this->m_BuyHour);
}

void FJA::Venta::SetID(const std::string &m_ID) {
    this->m_ID = m_ID;
}

void FJA::Venta::SetFlight(const std::string &m_Flight) {
    this->m_Flight = m_Flight;
}

void FJA::Venta::SetCustomerID(const std::string &m_CustomerID) {
    this->m_CustomerID = m_CustomerID;
}

void FJA::Venta::SetCustomer(const std::string &m_Customer) {
    this->m_Customer = m_Customer;
}

void FJA::Venta::SetFlightDate(const unsigned int &m_FlightDate) {
    this->m_FlightDate = m_FlightDate;
}

void FJA::Venta::SetBuyDate(const unsigned int &m_BuyDate) {
    this->m_BuyDate = m_BuyDate;
}

void FJA::Venta::SetBuyHour(const unsigned int &m_BuyHour) {
    this->m_BuyHour = m_BuyHour;
}

void FJA::Venta::SetAgency(const std::string &m_Agency) {
    Venta::m_Agency = m_Agency;
}


