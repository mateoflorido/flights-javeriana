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
    std::cerr
        << std::endl
        << "TAB! (" << this->getBuffer() << ")"
        << std::endl;
  } else
    return (0);
}

// eof - Console.cxx