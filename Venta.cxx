//
// Created by florido on 19/08/18.
//

#include "Venta.h"

FJA::Venta::
Venta()
        : m_ID(""),
          m_Flight(""),
          m_CustomerID(""),
          m_Customer(""),
          m_FlightDate(""),
          m_BuyDate(""),
          m_BuyHour("") {}


FJA::Venta::
Venta(const std::string &m_ID, const std::string &m_Flight, const std::string &m_CustomerID,
      const std::string &m_Customer, const std::string &m_FlightDate, const std::string &m_BuyDate,
      const std::string &m_BuyHour)
        : m_ID(m_ID),
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

const std::string &FJA::Venta::GetFlight() const {
    return (this->m_Flight);
}

const std::string &FJA::Venta::GetCustomerID() const {
    return (this->m_CustomerID);
}

const std::string &FJA::Venta::GetCustomer() const {
    return (this->m_Customer);
}

const std::string &FJA::Venta::GetFlightDate() const {
    return (this->m_FlightDate);
}

const std::string &FJA::Venta::GetBuyDate() const {
    return (this->m_BuyDate);
}

const std::string &FJA::Venta::GetBuyHour() const {
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

void FJA::Venta::SetFlightDate(const std::string &m_FlightDate) {
    this->m_FlightDate = m_FlightDate;
}

void FJA::Venta::SetBuyDate(const std::string &m_BuyDate) {
    this->m_BuyDate = m_BuyDate;
}

void FJA::Venta::SetBuyHour(const std::string &m_BuyHour) {
    this->m_BuyHour = m_BuyHour;
}
