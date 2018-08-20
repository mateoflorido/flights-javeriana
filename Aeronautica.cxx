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