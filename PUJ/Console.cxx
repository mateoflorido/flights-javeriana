// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include "Console.h"

// -------------------------------------------------------------------------
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#  include <conio.h>
#  include <Windows.h>
const char PUJ::Console::KEY_CTRL1   = -32;
const char PUJ::Console::BACKSPACE   =   8;
const char PUJ::Console::UP_ARROW    =  72;
const char PUJ::Console::DOWN_ARROW  =  80;
const char PUJ::Console::RIGHT_ARROW =  77;
const char PUJ::Console::LEFT_ARROW  =  75;
const char PUJ::Console::NEWLINE     = '\r';

#else
#  include <termios.h>
#  include <unistd.h>
const char PUJ::Console::KEY_CTRL1 = 17;
const char PUJ::Console::BACKSPACE = 127;
const char PUJ::Console::UP_ARROW = 65;
const char PUJ::Console::DOWN_ARROW = 66;
const char PUJ::Console::RIGHT_ARROW = 67;
const char PUJ::Console::LEFT_ARROW = 68;
const char PUJ::Console::NEWLINE = '\n';

int getch() {
  struct termios oldt, newt;
  int ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  ch = getchar();
  if (ch == PUJ::Console::ESC) {
    ch = getchar();
    if (ch == 91)
      ch = PUJ::Console::KEY_CTRL1;
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return (ch);
}
#endif // defined(WIN32) || defined(_WIN32) || defined(__WIN32)

// -------------------------------------------------------------------------
const unsigned long PUJ::Console::MAX_HISTORY = 500;
const char PUJ::Console::TAB = 9;
const char PUJ::Console::ESC = 27;
const char PUJ::Console::DEL = 51;
const short PUJ::Console::M_LINE = 0;
const short PUJ::Console::M_PASSWORD = 1;

// -------------------------------------------------------------------------
PUJ::Console::
Console() {
  this->m_MaxHistory = Self::MAX_HISTORY;
  this->m_Quit = false;
  this->m_Pos = -1;
  this->m_LinePos = 0;
  this->m_SkipOut = false;
}

// -------------------------------------------------------------------------
PUJ::Console::
Console(const std::string &prompt) {
  this->m_MaxHistory = Self::MAX_HISTORY;
  this->m_Quit = false;
  this->m_Prompt = prompt;
  this->m_Pos = -1;
  this->m_LinePos = 0;
  this->m_SkipOut = false;
  this->m_Trie = FJA::Trie();
  this->m_Trie.Insert("login");
  this->m_Trie.Insert("logout");
  this->m_Trie.Insert("report");
  this->m_Trie.Insert("report flights");
  this->m_Trie.Insert("report inventory");
  this->m_Trie.Insert("report money");
  this->m_Trie.Insert("help report");
  this->m_Trie.Insert("help login");
  this->m_Trie.Insert("help logout");
  this->m_Trie.Insert("help cancel");
  this->m_Trie.Insert("help sell");
  this->m_Trie.Insert("help consolidate");
  this->m_Trie.Insert("help exit");
  this->m_Trie.Insert("sell");
  this->m_Trie.Insert("cancel");
  this->m_Trie.Insert("consolidate");
  this->m_Trie.Insert("exit");

  this->commandList.insert({

                               {"exit", "exit: exit "
                                        "\n Cierra todas las sesiones y finaliza la ejecución del programa"
                               },
                               {"report", "report: report <Modo> [arg1] [arg2]"
                                          "\n Permite realizar un reporte detallado."
                                          "\n Genera un reporte detallado del modo seleccionado."
                                          "\n Argumentos <Modo>:"
                                          "\n \t Modo\t Selecciona un modo Válido entre"
                                          "\n \t \t flights: Genera un reporte de todos los vuelos con sillas disponibles"
                                          "\n \t \t inventory: Genera un reporte de todos los vuelos vendidos, cambiados o cancelados de una agencia de viajes"
                                          "\n \t \t money: Genera un reporte de las ventas informando los activos y pasivos de la agencia"
                                          "\n \n Argumentos [arg1] [arg2]"
                                          "\n*Unicamente Modo flights*"
                                          "\n \t arg1: Origen de los vuelos a incluir en el reporte"
                                          "\n \t arg2: Fecha de los vuelos a incluir en el reporte"
                               },

                               {"sell", "sell: sell <IDVuelo> <Fecha> "
                                        "\n Realiza la venta de un vuelo determinado en una fecha seleccionada "
                                        "\n Argumentos :"
                                        "\n \t \t \tIDVuelo: Identificador del vuelo seleccionado"
                                        "\n \t \t \tFecha: Fecha del vuelo seleccionado"
                                        "\n Estado de Salida: \nGenera una venta del vuelo seleccionado"
                               },
                               {
                                   "logout", "logout: logout"
                                             "\n Permite cerrar sesión en una agencia"
                                             "\n Estado de Salida:"
                                             "\n Cierra la sesión siempre que exista una abierta"
                               },
                               {
                                   "login", "login: login <idagencia> <password>"
                                            "\n Permite iniciar sesión en una agencia"
                                            "\n Permite iniciar sesión en una agencia cuando el IDAGENCIA es válido"
                                            "\n Argumentos:\n \t \t \t IDAGENCIA\t Indica el ID de una agencia válida."
                                            "\n \t \t \t PASSWORD\t Indica el password asociado a la agencia."
                               },

                               {"read", "read: sell <Modo> "
                                        "\n Realiza la lectura de los datos en persistencia "
                                        "\n Argumentos <Modo> :"
                                        "\n \t \t \tflights: Lee los vuelos programados por la Aeronautica Civil"
                                        "\n \t \t \tagencies: Lee las agencias disponibles en el sistema"
                                        "\n \t \t \tsales: Lee las ventas realizadas por las agencias"
                                        "\n Estado de Salida: \nLee un archivo con éxito."
                               },
                               {"cancel", "cancel: cancel <id> "
                                          "\nCancela un vuelo o paquete "
                                          "\n Argumentos <id> :"
                                          "\n \t \t \t id: Es el identificador de un vuelo."
                                          "\n Estado de Salida: \nCancela el vuelo."
                               },
                               {"consolidate", "consolidate: consolidate "
                                               "\nElimina de la base de datos trasacciones pasadas ya realizadas. "
                                               "\n Estado de Salida: \nLimpia la base de datos de transacciones pasadas."
                               }
                           });

}

// -------------------------------------------------------------------------
PUJ::Console::
~Console() {
}

// -------------------------------------------------------------------------
void PUJ::Console::
run() {
  std::cout << this->m_Prompt;

  bool ok = true;
  while (ok) {
    this->m_Char = getch();
    if (this->hotkeys(this->m_Char) == 0) {
      switch (this->m_Char) {
      case Self::ESC: {
      } // end case
        break;
      case Self::KEY_CTRL1: {
        char c = getch();
        switch (c) {
        case Self::UP_ARROW: {
          if (this->m_History.size() > 0) {
            if (this->m_Pos == -1) {
              // store current command
              this->m_Unused = "";
              this->m_Unused.assign(
                  this->m_Buffer.begin(), this->m_Buffer.end()
              );
            } // end if

            // clear line
            for (int i = 0; i < this->m_LinePos; ++i)
              std::cout << "\b \b";

            // clean buffer
            this->m_Buffer.clear();

            this->m_Pos++;
            if (this->m_Pos > (this->m_History.size() - 1))
              this->m_Pos = this->m_History.size() - 1;

            // store in buffer
            for (int i = 0; i < this->m_History[this->m_Pos].size(); ++i)
              this->m_Buffer.push_back(this->m_History[this->m_Pos][i]);
            this->m_LinePos = this->m_Buffer.size();
            std::cout << this->m_History[this->m_Pos];
          } // end if
        } // end case
          break;
        case Self::DOWN_ARROW: {
          if (this->m_History.size() > 0) {
            // clear line
            for (int i = 0; i < this->m_LinePos; ++i)
              std::cout << "\b \b";

            // clean buffer
            this->m_Buffer.clear();

            this->m_Pos--;
            if (this->m_Pos < -1)
              this->m_Pos = -1;
            if (this->m_Pos >= 0) {
              std::cout << this->m_History[this->m_Pos];
              // store in buffer
              for (int i = 0; i < this->m_History[this->m_Pos].size(); ++i)
                this->m_Buffer.push_back(
                    this->m_History[this->m_Pos][i]
                );
            } else {
              if (this->m_Buffer.size() > 0) {
                std::cout << this->m_Unused;

                // store in buffer
                for (int i = 0; i < this->m_Unused.size(); ++i)
                  this->m_Buffer.push_back(this->m_Unused[i]);
              } // end if
            } // end if
            this->m_LinePos = this->m_Buffer.size();
          } // end if
        } // end case
          break;
        case Self::LEFT_ARROW: {
          // if there are characters to move left over, do so
          if (this->m_LinePos > 0) {
            std::cout << "\b";
            this->m_LinePos--;
          } // end if
        } // end case
          break;
        case Self::RIGHT_ARROW: {
          // if there are characters to move right over, do so
          if (this->m_LinePos < this->m_Buffer.size()) {
            std::cout << this->m_Buffer[this->m_LinePos];
            this->m_LinePos++;
          } // end if
        } // end case
          break;
        case Self::DEL: {
          if (this->m_LinePos < this->m_Buffer.size()) {
            this->m_SkipOut = true;
            this->m_Buffer.erase(this->m_Buffer.begin() + this->m_LinePos);
            // update screen after current position
            for (int i = this->m_LinePos; i < this->m_Buffer.size(); ++i)
              std::cout << this->m_Buffer[i];
            // erase last char
            std::cout << " ";
            for (int i = this->m_LinePos; i < this->m_Buffer.size(); ++i)
              std::cout << "\b";
            // make-up for erase position
            std::cout << "\b";
          } // end if
        } // end case
          break;
        default: {
          this->m_SkipOut = true;
        } // end case
          break;
        } // end switch
      } // end case
        break;
      case Self::BACKSPACE: {
        if (this->m_LinePos > 0) {
          // move cursor back, blank char, and move cursor back again
          std::cout << "\b \b";
          // don't forget to clean the buffer and update line position
          if (this->m_LinePos == this->m_Buffer.size()) {
            this->m_Buffer.pop_back();
            this->m_LinePos--;
          } else {
            this->m_LinePos--;
            this->m_Buffer.erase(this->m_Buffer.begin() + this->m_LinePos);
            // update screen after current position
            for (int i = this->m_LinePos; i < this->m_Buffer.size(); ++i)
              std::cout << this->m_Buffer[i];
            // erase last char
            std::cout << " ";
            for (int i = this->m_LinePos + 1; i < this->m_Buffer.size(); ++i)
              std::cout << "\b";
            // make-up for erase position and go to new position
            std::cout << "\b\b";
          } // end if
        } // end if
      } // end case
        break;
      case Self::TAB: {
      } // end case
        break;
      case Self::NEWLINE: {
        // store in string
        this->m_String.assign(
            this->m_Buffer.begin(), this->m_Buffer.end()
        );

        // save command to history
        // trimming of command should be done in callback function
        if (this->m_String.length() > 0)
          this->m_History.push_front(this->m_String);

        // run command
        std::cout << std::endl;
        this->trigger(this->m_String);

        // check for exit command
        ok = !(this->m_Quit);
        if (ok) {
          if (this->m_History.size() > this->m_MaxHistory)
            this->m_History.pop_back();

          // clean buffer
          this->m_Buffer.clear();

          // print prompt. new line should be added from callback function
          std::cout << this->m_Prompt;

          // reset position
          this->m_Pos = -1;
          this->m_LinePos = 0;
        } // end if
      } // end case
        break;
      default: {
        if (!(this->m_SkipOut)) {
          std::cout << this->m_Char;
          if (this->m_LinePos != this->m_Buffer.size()) {
            // line position is not at end. Insert new char
            this->m_Buffer.insert(
                this->m_Buffer.begin() + this->m_LinePos, this->m_Char
            );
            // update screen after current position
            for (int i = this->m_LinePos + 1; i < this->m_Buffer.size(); ++i)
              std::cout << this->m_Buffer[i];
            for (int i = this->m_LinePos + 1; i < this->m_Buffer.size(); ++i)
              std::cout << "\b";
          } else
            this->m_Buffer.push_back(this->m_Char);
          this->m_LinePos++;
        } else
          this->m_SkipOut = false;
      } // end case
        break;
      } // end switch
    } // end if
  } // end while
}

// -------------------------------------------------------------------------
void PUJ::Console::
setPrompt(const std::string &prompt) {
  this->m_Prompt = prompt;
}

// -------------------------------------------------------------------------
int PUJ::Console::
trigger(const std::string &cmd) {
  return ((this->m_Quit) ? 1 : 0);
}

// -------------------------------------------------------------------------
int PUJ::Console::
hotkeys(char c) {
  return (0);
}

// -------------------------------------------------------------------------
void PUJ::Console::
pause() {
  getch();
}

// -------------------------------------------------------------------------
void PUJ::Console::
quit() {
  this->m_Quit = true;
}

// -------------------------------------------------------------------------
std::string PUJ::Console::
getLine() {
  return (this->getLine(Self::M_LINE, ""));
}

// -------------------------------------------------------------------------
std::string PUJ::Console::
getLine(int mode, const std::string &delimiter) {
  std::string line;
  char c;
  bool ok = true;
  while (ok) {
    c = getch();
    if (c == Self::NEWLINE) {
      std::cout << std::endl;
      ok = false;
    } else if (c == Self::BACKSPACE) {
      if (line.length() > 0) {
        line = line.substr(0, line.size() - 1);
        if (mode != Self::M_PASSWORD)
          std::cout << "\b \b";
      } // end if
    } else {
      line += c;
      if (mode != Self::M_PASSWORD)
        std::cout << c;
    } // end if
  } // end while
  return (line);
}

// -------------------------------------------------------------------------
void PUJ::Console::
setMaxHistory(int count) {
  this->m_MaxHistory = count;
}

// -------------------------------------------------------------------------
void PUJ::Console::
setBuffer(const std::string &buffer) {
  this->m_Buffer.assign(buffer.begin(), buffer.end());
  this->m_LinePos = this->m_Buffer.size();
}

// -------------------------------------------------------------------------
std::string PUJ::Console::
getBuffer() const {
  return (std::string(this->m_Buffer.begin(), this->m_Buffer.end()));
}

// eof - Console.cxx
