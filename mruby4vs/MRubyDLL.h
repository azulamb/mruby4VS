#ifndef __LIBMRUBY_DLL
#define __LIBMRUBY_DLL

#include <windows.h>
#include "MRubyClass.h"

extern "C" __declspec(dllexport) class MRuby* _CreateMRuby(void);
#define CreateMRuby(h) (((class MRuby * (*)(void))GetProcAddress(h, "_CreateMRuby"))())

#endif
