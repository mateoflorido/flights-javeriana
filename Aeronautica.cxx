#include <algorithm>
#include <iomanip>
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
           const std::string &m_Destination, const std::string &m_Hour, const unsigned int &m_FlightDuration,
           const unsigned int &m_Capacity, const unsigned long &m_Price) {
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
          const std::string &m_Customer, const std::string &m_FlightDate, const std::string &m_BuyDate,
          const std::string &m_BuyHour) {
    auto itAgencies = this->m_Agencies.begin();
    for (; itAgencies != this->m_Agencies.end(); itAgencies++) {
        if (itAgencies->GetAgencyID() == m_Agency) {
            itAgencies->NewSale(m_Agency, m_ID, m_Flight, m_CustomerID, m_Customer, m_FlightDate, m_BuyDate, m_BuyHour);

        }
    }
}

bool FJA::Aeronautica
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

bool FJA::Aeronautica
::Sell(const std::string &IdVuelo, const std::string &fecha, const std::string &currentAgency,
       const std::string &CustomerID, const std::string &Customer, const std::string &buyDate,
       const std::string &buyHour) {
    int sillasV = ContarVentas(IdVuelo);
    auto itRoutes = this->m_Routes.begin();
    for (; itRoutes != this->m_Routes.end(); itRoutes++) {
        if (itRoutes->GetCode() == IdVuelo) {
            break;
        }
    }
    if (itRoutes != this->m_Routes.end() && VerificarFechas(fecha, itRoutes->GetWeekDay()) &&
        sillasV < itRoutes->GetCapacity()) {
        auto itAgencies = this->m_Agencies.begin();
        for (; itAgencies != this->m_Agencies.end(); itAgencies++) {
            std::mt19937 rng; //Random Number from 0000 to 9999
            rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(0000, 9999);

            if (itAgencies->GetAgencyID() == currentAgency) {
                NewSale(itAgencies->GetAgencyID(), std::to_string(dist6(rng)), itRoutes->GetCode(), CustomerID,
                        Customer, fecha,
                        buyDate, buyHour);
                return true;
            }
        }
    } else {
        return false;
    }
    return false;
}

int FJA::Aeronautica
::ContarVentas(const std::string &IdVuelo) {
    int conta = 0;
    for (auto &m_Agencie : this->m_Agencies)
        for (auto itSales = m_Agencie.GetSales().begin(); itSales != m_Agencie.GetSales().end(); itSales++) {
            if (itSales->GetID() == IdVuelo)
                conta++;
        }

    return conta;
}

bool FJA::Aeronautica
::VerificarFechas(const std::string &fecha, const std::string &dia) {

    if (fecha.size() == 8) {
        std::string year = fecha.substr(0, 4);
        std::string month = fecha.substr(4, 2);
        std::string day = fecha.substr(6, 2);
        int y = std::stoi(year);
        int m = std::stoi(month);
        int d = std::stoi(day);
        int resultado;
        int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        y -= (m < 3);
        resultado = (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;

        if (resultado == 0 && dia == "Domingo")
            return true;
        if (resultado == 1 && dia == "Lunes")
            return true;
        if (resultado == 2 && dia == "Martes")
            return true;
        if (resultado == 3 && dia == "Miercoles")
            return true;
        if (resultado == 4 && dia == "Jueves")
            return true;
        if (resultado == 5 && dia == "Viernes")
            return true;
        if (resultado == 6 && dia == "Sabado")
            return true;
        return false;
    } else
        return false;
}

std::string FJA::Aeronautica
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

std::vector<FJA::Ruta> FJA::Aeronautica
::ReportFlights(std::string origen, std::string fecha) {
    std::vector<FJA::Ruta> retorno;
    auto itRutas = this->m_Routes.begin();
    if (origen == " " && fecha == " ") {
        for (; itRutas != this->m_Routes.end(); itRutas++) {
            if (ContarVentas(itRutas->GetCode()) < itRutas->GetCapacity())
                retorno.push_back(*itRutas);
        }
    } else {
        for (; itRutas != this->m_Routes.end(); itRutas++) {
            if (itRutas->GetOrigin() == origen && VerificarFechas(fecha, itRutas->GetWeekDay())) {
                if (ContarVentas(itRutas->GetCode()) < itRutas->GetCapacity())
                    retorno.push_back(*itRutas);
            }
        }
    }
    return retorno;
}

std::string FJA::Aeronautica
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
                    if (itSNext->GetFlight().empty()) {
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
