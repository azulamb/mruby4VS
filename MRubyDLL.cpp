#include "MRubyDLL.h"
#include "Spinel.h"

/*BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
}*/

__declspec(dllexport) class MRuby* _CreateMRuby(void)
{
  return new Spinel();
}
