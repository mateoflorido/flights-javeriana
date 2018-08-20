//
// Created by florido on 19/08/18.
//

#include "Agencia.h"

FJA::Agencia::
Agencia()
        : m_Sales(std::vector<FJA::Venta>()) {}

FJA::Agencia::
~Agencia() {}


const std::string &FJA::Agencia::GetAgencyID() const {
    return (this->m_AgencyID);
}

const std::string &FJA::Agencia::GetPassword() const {
    return (this->m_Password);
}

const std::vector<FJA::Venta> &FJA::Agencia::GetSales() const {
    return (this->m_Sales);
}

void FJA::Agencia::SetAgencyID(const std::string &m_AgencyID) {
    this->m_AgencyID = m_AgencyID;
}

void FJA::Agencia::SetPassword(const std::string &m_Password) {
    this->m_Password = m_Password;
}


void FJA::Agencia::SetSales(const std::vector<FJA::Venta> &m_Sales) {
    this->m_Sales = m_Sales;

}

void FJA::Agencia::NewSale(const std::string &m_Agency, const std::string &m_ID, const std::string &m_Flight,
             const std::string &m_CustomerID,
             const std::string &m_Customer, const unsigned int &m_FlightDate, const unsigned int &m_BuyDate,
             const unsigned int &m_BuyHour){
    Venta v(m_Agency, m_ID, m_Flight, m_CustomerID, m_Customer, m_FlightDate, m_BuyDate, m_BuyHour);
    this->m_Sales.push_back(v);
}