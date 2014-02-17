#include "Spinel.h"

class MRuby* CreateMRuby(void)
{
  return new Spinel();
}
