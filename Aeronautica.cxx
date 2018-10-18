#include <algorithm>
#include <iomanip>
#include <iostream>
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
~Aeronautica() {
};

void
FJA::Aeronautica::
NewAgency(const std::string &name, const std::string &password) {

  auto itAgency = this->m_Agencies.begin();
  for (; itAgency != this->m_Agencies.end(); itAgency++) {
    if (itAgency->GetAgencyID() == name) {
      std::exception e;
      throw e;
    }
  }//rof
  if (itAgency == this->m_Agencies.end()) {
    this->m_Agencies.push_back(Agencia(name, password));
  }//fi
}

void
FJA::Aeronautica
::NewRoute(const std::string &m_Code, const std::string &m_WeekDay, const std::string &m_Origin,
           const std::string &m_Destination, const std::string &m_Hour, const unsigned int &m_FlightDuration,
           const unsigned int &m_Capacity, const unsigned long &m_Price) {
  auto itRoutes = this->m_Routes.begin();
  for (; itRoutes != this->m_Routes.end(); ++itRoutes) {
    if (itRoutes->GetCode() == m_Code) {
      std::exception e;
      throw e;
    }//fi

  }//rof
  if (itRoutes == this->m_Routes.end()) {

    this->m_Routes.push_back(
        Ruta(m_Code, m_WeekDay, m_Origin, m_Destination, m_Hour, m_FlightDuration, m_Capacity, m_Price));
  }//fi
}

void
FJA::Aeronautica
::NewSale(const std::string &m_Agency, const std::string &m_ID, const std::string &m_Flight,
          const std::string &m_CustomerID,
          const std::string &m_Customer, const std::string &m_FlightDate, const std::string &m_BuyDate,
          const std::string &m_BuyHour) {
  auto itRoutes = this->m_Routes.begin();
  for (; itRoutes != this->m_Routes.end(); itRoutes++) {
    if (m_Flight == itRoutes->GetCode()) {
      break;
    }
  }
  if (itRoutes != this->m_Routes.end()) {
    auto itAgencies = this->m_Agencies.begin();
    for (; itAgencies != this->m_Agencies.end(); itAgencies++) {
      if (itAgencies->GetAgencyID() == m_Agency) {
        itAgencies->NewSale(m_Agency, m_ID, m_Flight, m_CustomerID, m_Customer, m_FlightDate, m_BuyDate, m_BuyHour);
        return;
      }//fi
    }//rof
  }
}

bool
FJA::Aeronautica
::CheckLogin(const std::string &m_AgencyID, const std::string &m_Password) {
  auto itAgencies = this->m_Agencies.begin();
  for (; itAgencies != this->m_Agencies.end(); itAgencies++) {
    if (itAgencies->GetAgencyID() == m_AgencyID)
      return itAgencies->GetPassword() == m_Password;
  }
  if (itAgencies == this->m_Agencies.end())
    return false;

  return false;
}

bool
FJA::Aeronautica
::Sell(const std::string &FlightID, const std::string &Date, const std::string &AgencyID,
       const std::string &CustomerID, const std::string &Customer, const std::string &buyDate,
       const std::string &buyHour) {
  int seatsSold = SeatsSold(FlightID);
  auto itRoutes = this->m_Routes.begin();
  for (; itRoutes != this->m_Routes.end(); itRoutes++) {
    if (itRoutes->GetCode() == FlightID) {
      break;
    }
  }
  if (itRoutes != this->m_Routes.end() && CheckDates(Date, itRoutes->GetWeekDay()) &&
      seatsSold < itRoutes->GetCapacity()) {
    auto itAgencies = this->m_Agencies.begin();
    for (; itAgencies != this->m_Agencies.end(); itAgencies++) {
      std::mt19937 rng; //Random Number from 0000 to 9999
      rng.seed(std::random_device()());
      std::uniform_int_distribution<std::mt19937::result_type> dist6(0000, 9999);

      if (itAgencies->GetAgencyID() == AgencyID) {
        NewSale(itAgencies->GetAgencyID(), std::to_string(dist6(rng)), itRoutes->GetCode(), CustomerID,
                Customer, Date,
                buyDate, buyHour);
        return true;
      }
    }
  } else {
    return false;
  }
  return false;
}

int
FJA::Aeronautica
::SeatsSold(const std::string &FlightID) {
  int count = 0;
  for (auto &m_Agency : this->m_Agencies)
    for (const auto &itSales : m_Agency.GetSales()) {
      if (itSales.GetID() == FlightID)
        count++;
    }

  return count;
}

bool
FJA::Aeronautica
::CheckDates(const std::string &Date, const std::string &Day) {

  if (Date.size() == 8) {
    int y = std::stoi(Date.substr(0, 4));
    int m = std::stoi(Date.substr(4, 2));
    int d = std::stoi(Date.substr(6, 2));
    int check;
    int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= (m < 3);
    check = (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;

    if (check == 0 && Day == "Domingo")
      return true;
    if (check == 1 && Day == "Lunes")
      return true;
    if (check == 2 && Day == "Martes")
      return true;
    if (check == 3 && Day == "Miercoles")
      return true;
    if (check == 4 && Day == "Jueves")
      return true;
    if (check == 5 && Day == "Viernes")
      return true;
    if (check == 6 && Day == "Sabado")
      return true;
    return false;
  } else
    return false;
}

std::string
FJA::Aeronautica
::SalesReport() {
  if (!this->m_Agencies.empty()) {
    std::string report;
    auto itAgencies = this->m_Agencies.begin();
    for (; itAgencies != this->m_Agencies.end(); itAgencies++) {
      report += itAgencies->SalesReport();
    }
    return report;
  }
  return std::string();
}

std::string
FJA::Aeronautica
::ReportFlights(std::string origen, std::string fecha) {
  std::vector<FJA::Ruta> retorno;
  std::stringstream ss;
  auto itRutas = this->m_Routes.begin();
  if (origen == " " && fecha == " ") {
    for (; itRutas != this->m_Routes.end(); itRutas++) {
      if (SeatsSold(itRutas->GetCode()) < itRutas->GetCapacity())
        retorno.push_back(*itRutas);
    }
  } else {
    for (; itRutas != this->m_Routes.end(); itRutas++) {
      if (itRutas->GetOrigin() == origen && CheckDates(fecha, itRutas->GetWeekDay())) {
        if (SeatsSold(itRutas->GetCode()) < itRutas->GetCapacity())
          retorno.push_back(*itRutas);
      }
    }
  }
  int codigoW = 8, diaW = 10, originW = 15, destinationW = 15, horaW = 6, durationW = 15, capW = 15, priceW = 15;

  std::string column = " |";

  int totalW = codigoW + diaW + originW + destinationW + horaW + durationW + capW + priceW + column.size() * 8;

  std::string separator = column + std::string(totalW - 1, '-') + '|';
  auto itFlights = retorno.begin();

  ss << separator << "\n" << column
     << std::setw(codigoW) << "Codigo" << column
     << std::setw(diaW) << "Dia" << column
     << std::setw(originW) << "Origen" << column
     << std::setw(destinationW) << "Destination" << column
     << std::setw(horaW) << "Hora" << column
     << std::setw(durationW) << "Duración" << column
     << std::setw(capW) << "Capacidad" << column
     << std::setw(priceW) << "Precio" << column << "\n" << separator << "\n";
  for (; itFlights != retorno.end(); itFlights++) {
    ss << column << std::setw(codigoW) << itFlights->GetCode() << column
       << std::setw(diaW) << itFlights->GetWeekDay() << column
       << std::setw(originW) << itFlights->GetOrigin() << column
       << std::setw(destinationW) << itFlights->GetDestination() << column
       << std::setw(horaW) << itFlights->GetHour() << column
       << std::setw(durationW) << itFlights->GetDuration() << column
       << std::setw(capW) << itFlights->GetCapacity() << column
       << std::setw(priceW) << itFlights->GetPrice() << column << "\n";
  }
  ss << separator << "\n";
  return ss.str();

}

std::string
FJA::Aeronautica
::ReportInventory(std::string AgencyID) {
  auto itAgencies = this->m_Agencies.begin();
  for (; itAgencies != this->m_Agencies.end(); itAgencies++) {
    if (itAgencies->GetAgencyID() == AgencyID)
      break;
  }
  if (itAgencies != this->m_Agencies.end()) {
    std::stringstream ss;
    int agencyW = 7, flightW = 7, idW = 5, customerIDW = 12, customerW = 50, statusW = 9;

    std::string column = " |";
    int totalW = agencyW + flightW + idW + customerIDW + customerW + statusW + column.size() * 6;
    std::string separator = column + std::string(totalW - 1, '-') + '|';
    auto itSales = itAgencies->GetSales().begin();
    auto itSNext = std::next(itSales, 1);
    std::string status = "Vendido";

    ss << separator << "\n" << column
       << std::setw(agencyW) << "Agencia" << column
       << std::setw(idW) << "ID" << column
       << std::setw(flightW) << "Vuelo" << column
       << std::setw(customerIDW) << "ID Cliente" << column
       << std::setw(customerW) << "Cliente" << column
       << std::setw(statusW) << "Estado" << column << "\n" << separator << "\n";

    for (; itSales != itAgencies->GetSales().end(); itSales++) {
      if (itSNext != itAgencies->GetSales().end()) {
        if (itSales->GetID() == itSNext->GetID()) {
          if (itSNext->GetFlightDate().empty()) {
            ss << column << std::setw(agencyW) << itSales->GetAgency() << column
               << std::setw(idW) << itSales->GetID() << column
               << std::setw(flightW) << itSales->GetFlight() << column
               << std::setw(customerIDW) << itSales->GetCustomerID() << column
               << std::setw(customerW) << itSales->GetCustomer() << column
               << std::setw(statusW) << status << column << "\n";
            status = "Cancelado";
          } else if (std::stoi(itSales->GetBuyDate()) < std::stoi(itSNext->GetBuyDate())) {
            ss << column << std::setw(agencyW) << itSales->GetAgency() << column
               << std::setw(idW) << itSales->GetID() << column
               << std::setw(flightW) << itSales->GetFlight() << column
               << std::setw(customerIDW) << itSales->GetCustomerID() << column
               << std::setw(customerW) << itSales->GetCustomer() << column
               << std::setw(statusW) << status << column << "\n";
            status = "Cambiado";
          }

        } else {

          ss << column << std::setw(agencyW) << itSales->GetAgency() << column
             << std::setw(idW) << itSales->GetID() << column
             << std::setw(flightW) << itSales->GetFlight() << column
             << std::setw(customerIDW) << itSales->GetCustomerID() << column
             << std::setw(customerW) << itSales->GetCustomer() << column
             << std::setw(statusW) << status << column << "\n";
          status = "Vendido";
        }
      } else {
        ss << column << std::setw(agencyW) << itSales->GetAgency() << column
           << std::setw(idW) << itSales->GetID() << column
           << std::setw(flightW) << itSales->GetFlight() << column
           << std::setw(customerIDW) << itSales->GetCustomerID() << column
           << std::setw(customerW) << itSales->GetCustomer() << column
           << std::setw(statusW) << status << column << "\n";
        status = "Vendido";
      }
      if (itSNext != itAgencies->GetSales().end()) {
        itSNext++;
      }
    }
    ss << separator << "\n";
    return ss.str();
  }
  return "No hay coincidencias";

}

bool
FJA::Aeronautica
::CancelFlight(std::string SaleID, std::string AgencyID) {
  auto itAgencies = this->m_Agencies.begin();
  for (; itAgencies != this->m_Agencies.end(); itAgencies++) {
    if (itAgencies->GetAgencyID() == AgencyID)
      break;
  }

  if (itAgencies != this->m_Agencies.end()) {
    return itAgencies->CancelFlight(SaleID);
  }
  return false;
}

void
FJA::Aeronautica
::Consolidate(std::string currentDate) {
  auto itAgencies = this->m_Agencies.begin();
  for (; itAgencies != this->m_Agencies.end(); itAgencies++) {
    itAgencies->Consolidate(currentDate);
  }
}

std::string
FJA::Aeronautica
::ReportMoney(std::string AgencyID) {

  long localDebt = 0;
  long totalDebt = 0;
  long totalCredit = 0;
  auto itAgencies = this->m_Agencies.begin();
  for (; itAgencies != this->m_Agencies.end(); itAgencies++) {
    if (itAgencies->GetAgencyID() == AgencyID)
      break;
  }
  if (itAgencies != this->m_Agencies.end()) {
    std::stringstream ss;
    int agencyW = 7, flightW = 7, idW = 5, customerIDW = 12, customerW = 50, statusW = 9;

    std::string column = " |";
    int totalW = agencyW + flightW + idW + customerIDW + customerW + statusW + column.size() * 6;
    std::string separator = column + std::string(totalW - 1, '-') + '|';
    auto itSales = itAgencies->GetSales().begin();
    auto itSNext = std::next(itSales, 1);
    std::string status = "Vendido";

    ss << separator << "\n" << column
       << std::setw(agencyW) << "Agencia" << column
       << std::setw(idW) << "ID" << column
       << std::setw(flightW) << "Vuelo" << column
       << std::setw(customerIDW) << "ID Cliente" << column
       << std::setw(customerW) << "Cliente" << column
       << std::setw(statusW) << "Estado" << column << "\n" << separator << "\n";

    for (; itSales != itAgencies->GetSales().end(); itSales++) {
      if (itSNext != itAgencies->GetSales().end()) { // El segundo iterador no ha llegado al final
        if (itSales->GetID() == itSNext->GetID()) { //Puede ser un cambio o cancelacion
          if (itSNext->GetFlightDate().empty()) {//El siguiente es cancelado
            for (auto itRoutes = this->m_Routes.begin(); itRoutes != this->m_Routes.end(); itRoutes++) {
              if (itRoutes->GetCode() == itSales->GetFlight() && status == "Vendido") {
                localDebt = itRoutes->GetPrice();
              } else if (itRoutes->GetCode() == itSales->GetFlight() && status == "Cambiado") {
                localDebt = localDebt - itRoutes->GetPrice();
              }
            }
            ss << column << std::setw(agencyW) << itSales->GetAgency() << column
               << std::setw(idW) << itSales->GetID() << column
               << std::setw(flightW) << itSales->GetFlight() << column
               << std::setw(customerIDW) << itSales->GetCustomerID() << column
               << std::setw(customerW) << itSales->GetCustomer() << column
               << std::setw(statusW) << status << column << "\n";
            status = "Cancelado";
          } else if (std::stoi(itSales->GetBuyDate()) < std::stoi(itSNext->GetBuyDate())) {//El siguiente es cambiado
            for (auto itRoutes = this->m_Routes.begin(); itRoutes != this->m_Routes.end(); itRoutes++) {
              if (itRoutes->GetCode() == itSales->GetFlight() && status == "Vendido") {
                localDebt = itRoutes->GetPrice();
              } else if (itRoutes->GetCode() == itSales->GetFlight() && status == "Cambiado") {
                localDebt = localDebt - itRoutes->GetPrice();
              }
            }
            ss << column << std::setw(agencyW) << itSales->GetAgency() << column
               << std::setw(idW) << itSales->GetID() << column
               << std::setw(flightW) << itSales->GetFlight() << column
               << std::setw(customerIDW) << itSales->GetCustomerID() << column
               << std::setw(customerW) << itSales->GetCustomer() << column
               << std::setw(statusW) << status << column << "\n";
            status = "Cambiado";
          }

        }
          //-----------------------------------CASO NORMAL----------------------------------------------------------------
        else { //Es una venta normal. i.e. sin Cambios o Cancelaciones

          for (auto itRoutes = this->m_Routes.begin(); itRoutes != this->m_Routes.end(); itRoutes++) {
            if (status == "Cancelado") {
              localDebt = localDebt * 0.85;
              totalCredit += localDebt;
              localDebt = 0;
              break;
            } else if (itRoutes->GetCode() == itSales->GetFlight() && status == "Cambiado") {
              localDebt = localDebt - itRoutes->GetPrice();
            } else if (itRoutes->GetCode() == itSales->GetFlight() && status == "Vendido") {
              localDebt = 0;
            }
          }
          ss << column << std::setw(agencyW) << itSales->GetAgency() << column
             << std::setw(idW) << itSales->GetID() << column
             << std::setw(flightW) << itSales->GetFlight() << column
             << std::setw(customerIDW) << itSales->GetCustomerID() << column
             << std::setw(customerW) << itSales->GetCustomer() << column
             << std::setw(statusW) << status << column << "\n";
          status = "Vendido";
        }
      } else {// El segundo iterador ha llegado al final
        for (auto itRoutes = this->m_Routes.begin(); itRoutes != this->m_Routes.end(); itRoutes++) {
          if (itRoutes->GetCode() == itSales->GetFlight() && status == "Cancelado") {
            localDebt = localDebt * 0.85;
            totalCredit += localDebt;
            localDebt = 0;
          } else if (itRoutes->GetCode() == itSales->GetFlight() && status == "Cambiado") {
            localDebt = localDebt - itRoutes->GetPrice();
          } else if (itRoutes->GetCode() == itSales->GetFlight() && status == "Vendido") {
            localDebt = 0;
          }
        }
        ss << column << std::setw(agencyW) << itSales->GetAgency() << column
           << std::setw(idW) << itSales->GetID() << column
           << std::setw(flightW) << itSales->GetFlight() << column
           << std::setw(customerIDW) << itSales->GetCustomerID() << column
           << std::setw(customerW) << itSales->GetCustomer() << column
           << std::setw(statusW) << status << column << "\n";
        status = "Vendido";
      }
      if (itSNext != itAgencies->GetSales().end()) { //Continuar al siguiente elemento si aún existe uno.
        itSNext++;
      }
      if (status == "Vendido" || status == "Cambiado") {
        if (localDebt < 0) {
          totalDebt += labs(localDebt);
          localDebt = 0;
        } else {
          totalCredit += localDebt;
          localDebt = 0;
        }
      }
    }

    ss << separator << "\n"
       << column << std::setw(49) << "Debitos" << column
       << std::setw(49) << "Creditos" << column << "\n"
       << separator << "\n"
       << column << std::setw(49) << totalDebt << column
       << std::setw(49) << totalCredit<< column << "\n";
    ss << separator << "\n";
    return ss.str();

  return "No hay coincidencias";

}
std::vector<std::string>
FJA::Aeronautica
::GetIDAgencies() {
  std::vector<std::string> ret;
  auto itAgen = this->m_Agencies.begin();
  for(;itAgen != this->m_Agencies.end(); itAgen++){
    ret.push_back(itAgen->GetAgencyID());
  }
  return ret;
}
