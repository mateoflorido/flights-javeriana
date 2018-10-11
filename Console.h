// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __Console__h__
#define __Console__h__

#include "PUJ/Console.h"

/**
 */
class Console
    : public PUJ::Console
{
public:
  typedef Console      Self;
  typedef PUJ::Console Superclass;

public:
  Console( );
  Console( const std::string& prompt );
  virtual ~Console( );

  virtual int trigger( const std::string& s ) override;
  virtual int hotkeys( char c ) override;
};

#endif // __Console__h__

// eof - Console.h