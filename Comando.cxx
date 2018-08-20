//
// Created by florido on 19/08/18.
//

#include "Comando.h"

const std::string &FJA::Comando::GetCommand() const {
    return m_Command;
}

const std::string &FJA::Comando::GetDescription() const {
    return m_Description;
}

void FJA::Comando::SetCommand(const std::string &m_Command) {
    Comando::m_Command = m_Command;
}

void FJA::Comando::SetDescription(const std::string &m_Description) {
    Comando::m_Description = m_Description;
}
