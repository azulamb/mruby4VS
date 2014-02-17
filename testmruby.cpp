// DLL have bug.
//#define USEDLL

#ifdef USEDLL
#  include "MRubyDLL.h"
#else
#  include "MRubyLib.h"
#endif

int a = 10;

int main( void )
{
#ifdef USEDLL
#  ifdef _DEBUG
  HMODULE hmruby = LoadLibrary("mruby4vs/mrubyD.dll");
#  else
  HMODULE hmruby = LoadLibrary("mruby4vs/mruby.dll");
#  endif
  class MRuby* mruby = CreateMRuby(hmruby);
#else
  class MRuby *mruby = CreateMRuby();
#endif

#ifdef USEDLL
  // DLL cannnot run load(FILE *)
  // I do not know the cause.
  mruby->load( "def test\nreturn 10\nend" );
  a = mrb_fixnum(mruby->funcall("test"));
  printf("%d\n", a); // 10
#else
  FILE *f;
  if ( fopen_s( &f, "test.rb", "r") == 0 )
  {
    mruby->load( f );
    fclose(f);
    mrb_value val = mrb_fixnum_value(20);
    a = mrb_fixnum(mruby->funcall("test1"));
    printf("%d\n", a); // 10
    a = mrb_fixnum(mruby->funcall("test2", 1, val));
    printf("%d\n", a); // 20 * 2 => 40
    a = mrb_fixnum(mruby->funcall("test3", 2, val, mrb_fixnum_value(30)));
    printf("%d\n", a); // 20 + 30 => 50
  }
#endif
}
