#ifndef __MRUBY_LIB
#define __MRUBY_LIB

#include "MRubyClass.h"

#ifndef _DEBUG
#  pragma comment( lib, "libmruby.lib" )
#else
#  pragma comment( lib, "libmrubyD.lib" )
#endif

class MRuby* CreateMRuby( void );

#endif
