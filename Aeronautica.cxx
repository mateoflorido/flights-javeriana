//
// Created by florido on 19/08/18.
//

#include "Aeronautica.h"

FJA::Aeronautica::
Aeronautica()
        : m_Agencies(std::vector<FJA::Agencia>()),
          m_Routes(std::vector<Ruta>()) {}

FJA::Aeronautica::
Aeronautica(const std::vector<FJA::Agencia> &m_Agencies, const std::vector<FJA::Ruta> &m_Routes)
        : m_Agencies(m_Agencies),
          m_Routes(m_Routes) {}


FJA::Aeronautica::
~Aeronautica() = default;

void FJA::Aeronautica::
NewAgency(const std::string &name, const std::string &password) {

    auto itAgency = this->m_Agencies.begin();
    for (; itAgency != this->m_Agencies.end(); itAgency++) {
        if (itAgency->GetAgencyID() == name) {
            throw;
        }
    }//rof
    if (itAgency == this->m_Agencies.end()) {
        Agencia a;
        a.SetAgencyID(name);
        a.SetPassword(password);
        this->m_Agencies.push_back(a);
    }//fi
}

void FJA::Aeronautica
::NewRoute(const std::string &m_Code, const std::string &m_WeekDay, const std::string &m_Origin,
           const std::string &m_Destination, unsigned int m_Hour, unsigned int m_FlightDuration,
           unsigned int m_Capacity, unsigned long m_Price) {
    auto itRoutes = this->m_Routes.begin();
    for (; itRoutes != this->m_Routes.end(); ++itRoutes) {
        if (itRoutes->GetCode() == m_Code)
            throw;
    }
    if (itRoutes == this->m_Routes.end()) {
        Ruta r(m_Code, m_WeekDay, m_Origin, m_Destination, m_Hour, m_FlightDuration, m_Capacity, m_Price);
        this->m_Routes.push_back(r);
    }
}

void FJA::Aeronautica
::NewSale(const std::string &m_Agency, const std::string &m_ID, const std::string &m_Flight,
          const std::string &m_CustomerID,
          const std::string &m_Customer, const unsigned int &m_FlightDate, const unsigned int &m_BuyDate,
          const unsigned int &m_BuyHour) {
    auto itAgencies = this->m_Agencies.begin();
    for(;itAgencies != this->m_Agencies.end(); itAgencies++){
        if(itAgencies->GetAgencyID() == m_Agency){
	    Venta v(m_Agency, m_ID, m_Flight, m_CustomerID, m_Customer, m_FlightDate, m_BuyDate, m_BuyHour);
            itAgencies->GetSales.push_back(v)
        }
    }
}
