// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include "Console.h"

// -------------------------------------------------------------------------
Console::
Console()
    : Superclass() {
}

// -------------------------------------------------------------------------
Console::
Console(const std::string &prompt)
    : Superclass(prompt) {
}

// -------------------------------------------------------------------------
Console::
~Console() {
}

// -------------------------------------------------------------------------
int Console::
trigger(const std::string &s) {
  if (s == "")
    return (1);
  else if (s == "hello") {
    std::cout << "Hi!" << std::endl;
    return (1);
  } else if (s == "exit") {
    this->quit();
    return (1);
  } else {
    std::cerr << "Unknown command: " << s << std::endl;
    return (0);
  } // end if
}

// -------------------------------------------------------------------------
int Console::
hotkeys(char c) {
  if (c == Superclass::TAB) {

    if (!this->getBuffer().empty()) {
      // Clear actual prefix
      for (int i = 0; i < this->m_LinePos; ++i)
        std::cout << "\b \b";
    }
    std::string now;
    this->m_Trie.Coincidence(this->getBuffer(), now);
    if (!now.empty()) {
      this->setBuffer(now);
      std::cout << this->getBuffer();
      this->m_LinePos = this->m_Buffer.size();
    }
  } else
    return (0);
}

// eof - Console.cxx