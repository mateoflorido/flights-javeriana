

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
            if (itAgencies->GetPassword() == m_Password)
                return true;
            else
                return false;
    }
    if (itAgencies == this->m_Agencies.end())
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
    if (itRoutes != this->m_Routes.end() && VerificarFechas(fecha, itRoutes->GetWeekDay()) == true) {
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
}

int FJA::Aeronautica
::ContarVentas(const std::string &IdVuelo) {
    int conta = 0;
    for (auto itAg = this->m_Agencies.begin(); itAg != this->m_Agencies.end(); itAg++)
        for (auto itSales = itAg->GetSales().begin(); itSales != itAg->GetSales().end(); itSales++) {
            if (itSales->GetID() == IdVuelo)
                conta++;
        }

    return conta;
}

bool FJA::Aeronautica
::VerificarFechas(const std::string &fecha, const std::string &dia) {

    std::string year =  fecha.substr(1,3);
    std::string month = fecha.substr(4,5);
    std::string day = fecha.substr(6,7);
    int resultado = (std::stoi(year) + std::stoi(month) + std::stoi(day)) % 7;   //0=sabado
    if (resultado == 0 && dia == "Sabado")
        return true;
    if (resultado == 1 && dia == "Domingo")
        return true;
    if (resultado == 2 && dia == "Lunes")
        return true;
    if (resultado == 3 && dia == "Martes")
        return true;
    if (resultado == 4 && dia == "Miercoles")
        return true;
    if (resultado == 5 && dia == "Jueves")
        return true;
    if (resultado == 6 && dia == "Viernes")
        return true;
    return false;
}


