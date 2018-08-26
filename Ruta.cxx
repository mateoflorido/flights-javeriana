

#include "Ruta.h"

//----------------------------------------------------------------------------------------------------------------------
FJA::Ruta::
Ruta()
        : m_Code(""),
          m_WeekDay(""),
          m_Origin(""),
          m_Destination(""),
          m_Hour(""),
          m_FlightDuration(0),
          m_Capacity(0),
          m_Price(0) {
}

FJA::Ruta::
Ruta(const std::string &m_Code, const std::string &m_WeekDay, const std::string &m_Origin,
     const std::string &m_Destination, const std::string &m_Hour, const unsigned int &m_FlightDuration,
     const unsigned int &m_Capacity, const unsigned long &m_Price)
        : m_Code(m_Code), m_WeekDay(m_WeekDay),
          m_Origin(m_Origin), m_Destination(m_Destination),
          m_Hour(m_Hour), m_FlightDuration(m_FlightDuration),
          m_Capacity(m_Capacity), m_Price(m_Price) {}


//----------------------------------------------------------------------------------------------------------------------
FJA::Ruta::
~Ruta() {

}
//----------------------------------------------------------------------------------------------------------------------

const std::string &FJA::Ruta::GetCode() const {
    return (this->m_Code);
}
//----------------------------------------------------------------------------------------------------------------------

const std::string &FJA::Ruta::GetWeekDay() const {
    return (this->m_WeekDay);
}
//----------------------------------------------------------------------------------------------------------------------


const std::string &FJA::Ruta::GetOrigin() const {
    return (this->m_Origin);
}
//----------------------------------------------------------------------------------------------------------------------

const std::string &FJA::Ruta::GetDestination() const {
    return (this->m_Destination);
}
//----------------------------------------------------------------------------------------------------------------------

const std::string &FJA::Ruta::GetHour() const {
    return (this->m_Hour);
}
//----------------------------------------------------------------------------------------------------------------------

const unsigned int &FJA::Ruta::GetDuration() const {
    return (this->m_FlightDuration);
}
//----------------------------------------------------------------------------------------------------------------------

const unsigned int &FJA::Ruta::GetCapacity() const {
    return (this->m_Capacity);
}
//----------------------------------------------------------------------------------------------------------------------

const unsigned long &FJA::Ruta::GetPrice() const {
    return (this->m_Price);
}
//----------------------------------------------------------------------------------------------------------------------

void FJA::Ruta::SetCode(const std::string &m_Code) {
    this->m_Code = m_Code;
}
//----------------------------------------------------------------------------------------------------------------------

void FJA::Ruta::SetWeekDay(const std::string &m_WeekDay) {
    this->m_WeekDay = m_WeekDay;
}
//----------------------------------------------------------------------------------------------------------------------

void FJA::Ruta::SetOrigin(const std::string &m_Origin) {
    this->m_Origin = m_Origin;
}
//----------------------------------------------------------------------------------------------------------------------

void FJA::Ruta::SetDestination(const std::string &m_Destination) {
    this->m_Destination = m_Destination;
}
//----------------------------------------------------------------------------------------------------------------------

void FJA::Ruta::SetHour(const std::string &hour) {
    this->m_Hour = m_Hour;
}
//----------------------------------------------------------------------------------------------------------------------

void FJA::Ruta::SetDuration(const unsigned int &duration) {
    this->m_FlightDuration = m_FlightDuration;
}
//----------------------------------------------------------------------------------------------------------------------

void FJA::Ruta::SetCapacity(const unsigned int &capacity) {
    this->m_Capacity = m_Capacity;
}
//----------------------------------------------------------------------------------------------------------------------

void FJA::Ruta::SetPrice(const unsigned long &price) {
    this->m_Price = m_Price;
}

//----------------------------------------------------------------------------------------------------------------------

