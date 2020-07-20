

#include <algorithm>
#include "Agencia.h"
#include <ctime>

FJA::Agencia::
Agencia()
    : m_Sales(std::vector<FJA::Venta>()) {}

FJA::Agencia::
Agencia(const std::string &m_AgencyID, const std::string &m_Password)
    : m_AgencyID(m_AgencyID),
      m_Password(m_Password),
      m_Sales(std::vector<FJA::Venta>()) {}

FJA::Agencia::
~Agencia() {
}

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
                           const std::string &m_Customer, const std::string &m_FlightDate, const std::string &m_BuyDate,
                           const std::string &m_BuyHour) {
  Venta v(m_Agency, m_ID, m_Flight, m_CustomerID, m_Customer, m_FlightDate, m_BuyDate, m_BuyHour);
  this->m_Sales.push_back(v);
  std::sort(this->m_Sales.begin(), this->m_Sales.end());
}

std::string FJA::Agencia::SalesReport() {
  std::string report;
  if (!this->m_Sales.empty()) {
    auto itSales = this->m_Sales.begin();
    for (; itSales != this->m_Sales.end(); itSales++) {
      report += itSales->GetAgency();
      report += "_";
      report += itSales->GetID() + ";" + itSales->GetFlight() + ";" + itSales->GetCustomer() + ";" +
          itSales->GetCustomerID() + ";" + itSales->GetFlightDate() + ";" + itSales->GetBuyDate() + ";" +
          itSales->GetBuyHour() + "\n";
    }
  }
  return report;
}

void FJA::Agencia::
Consolidate(std::string currentDate) {
    Venta aux;
  auto itSales = this->m_Sales.begin();
  while(itSales != this->m_Sales.end()) {
    if (itSales->GetFlightDate() < currentDate)
      itSales = this->m_Sales.erase(itSales);
    else
        itSales++;
  }
}

bool FJA::Agencia::
CancelFlight(std::string &SaleID) {
    std::string buyHour;
    std::string buyDate;
    std::time_t result = std::time(nullptr);
    buyHour = (std::to_string(std::localtime(&result)->tm_hour));
    if (std::localtime(&result)->tm_min < 10)
        buyHour += "0" + (std::to_string(std::localtime(&result)->tm_min));
    else
        buyHour += (std::to_string(std::localtime(&result)->tm_min));
    buyDate = (std::to_string(std::localtime(&result)->tm_year + 1900));
    if ((std::localtime(&result)->tm_mon + 1) < 10) {
        buyDate += (std::to_string(std::localtime(&result)->tm_mon + 1)) + "0" +
                   (std::to_string((std::localtime(&result)->tm_mday)));

    } else {
        buyDate += (std::to_string(std::localtime(&result)->tm_mon + 1)) +
                   (std::to_string((std::localtime(&result)->tm_mday)));
    }
  auto itSales = this->m_Sales.begin();
  for (; itSales != this->m_Sales.end(); itSales++) {
    if (itSales->GetID() == SaleID) {
      this->NewSale(this->m_AgencyID,
                    SaleID,
                    "",
                    itSales->GetCustomerID(),
                    itSales->GetCustomer(),
                    itSales->GetFlightDate(),
                    buyDate,
                    buyHour);
      return true;
    }
  }
  return false;
}
