//
// Created by Mateo Florido on 19/08/18.
//

#ifndef FLIGHTS_JAVERIANA_RUTA_H
#define FLIGHTS_JAVERIANA_RUTA_H

#include <string>

namespace FJA {
    class Ruta {
    public:
        Ruta();

        virtual ~Ruta();

        const std::string &GetCode() const;

        Ruta(const std::string &m_Code, const std::string &m_WeekDay, const std::string &m_Origin,
             const std::string &m_Destination, unsigned int m_Hour, unsigned int m_FlightDuration,
             unsigned int m_Capacity, unsigned long m_Price);

        const std::string &GetWeekDay() const;

        const std::string &GetOrigin() const;

        const std::string &GetDestination() const;

        const unsigned int &GetHour() const;

        const unsigned int &GetDuration() const;

        const unsigned int &GetCapacity() const;

        const unsigned long &GetPrice() const;

        void SetCode(const std::string &code);

        void SetWeekDay(const std::string &weekday);

        void SetOrigin(const std::string &origin);

        void SetDestination(const std::string &destination);

        void SetHour(const unsigned int &hour);

        void SetDuration(const unsigned int &duration);

        void SetCapacity(const unsigned int &capacity);

        void SetPrice(const unsigned long &price);

    protected:
        std::string m_Code;
        std::string m_WeekDay;
        std::string m_Origin;
        std::string m_Destination;
        unsigned int m_Hour;
        unsigned int m_FlightDuration;
        unsigned int m_Capacity;
        unsigned long m_Price;

    };

}


#endif //FLIGHTS_JAVERIANA_RUTA_H

