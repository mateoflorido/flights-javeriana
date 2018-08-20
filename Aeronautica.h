//
// Created by florido on 19/08/18.
//

#ifndef FLIGHTS_JAVERIANA_AERONAUTICA_H
#define FLIGHTS_JAVERIANA_AERONAUTICA_H

#include <vector>
#include "Agencia.h"
#include "Ruta.h"

namespace FJA {
    class Aeronautica {
    public:
        Aeronautica();
        Aeronautica(const std::vector<Agencia> &m_Agencies, const std::vector<Ruta> &m_Routes);
        virtual ~Aeronautica();

    protected:
        std::vector<Agencia> m_Agencies;
        std::vector<Ruta> m_Routes;
    };
}

#endif //FLIGHTS_JAVERIANA_AERONAUTICA_H
