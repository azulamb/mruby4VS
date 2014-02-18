// DLL have bug.
//#define USEDLL

#ifdef USEDLL
#  include "MRubyDLL.h"
#else
#  include "MRubyLib.h"
#endif

int main( void )
{
  int a = 10;

  // Create mruby instance.
#ifdef USEDLL
  // Load DLL
#  ifdef _DEBUG
  HMODULE hmruby = LoadLibrary("mruby4vs/mrubyD.dll");
#  else
  HMODULE hmruby = LoadLibrary("mruby4vs/mruby.dll");
#  endif
  class MRuby* mruby = CreateMRuby(hmruby);
#else
  class MRuby *mruby = CreateMRuby();
#endif

  // load mruby file.
  mruby->load("test.rb");

  mrb_value val = mrb_fixnum_value(20);
  a = mrb_fixnum(mruby->funcall("test1"));
  printf("%d\n", a); // 10
  a = mrb_fixnum(mruby->funcall("test2", 1, val));
  printf("%d\n", a); // 20 * 2 => 40
  a = mrb_fixnum(mruby->funcall("test3", 2, val, mrb_fixnum_value(30)));
  printf("%d\n", a); // 20 + 30 => 50

  delete( mruby );
}
