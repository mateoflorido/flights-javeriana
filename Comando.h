//
// Created by florido on 19/08/18.
//

#ifndef FLIGHTS_JAVERIANA_COMANDO_H
#define FLIGHTS_JAVERIANA_COMANDO_H

#include <string>

namespace FJA {
    class Comando {
    public:
        const std::string &GetCommand() const;

        const std::string &GetDescription() const;

        void SetCommand(const std::string &m_Command);

        void SetDescription(const std::string &m_Description);

    protected:
        std::string m_Command;
        std::string m_Description;

    };
}

#endif //FLIGHTS_JAVERIANA_COMANDO_H
