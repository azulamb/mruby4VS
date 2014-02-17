#ifndef __MRUBY_CLASS
#define __MRUBY_CLASS

#ifndef NO_GETTIMEOFDAY
#  define NO_GETTIMEOFDAY
#endif

#include "mruby.h"
#include "mruby/value.h"

class MRuby
{
public:
  MRuby(void){}
  virtual ~MRuby(void){}

  virtual struct mrb_state *get( void ) = 0;

  virtual mrb_bool classDefined(const char *name) = 0;
  virtual struct RClass * classGet(const char *name) = 0;
  virtual struct RClass * classGetUnder(struct RClass *outer, const char *name) = 0;
  virtual struct RClass * defineClassUnder(struct RClass *outer, const char *name, struct RClass *super) = 0;
  virtual struct RClass * defineModuleUnder(mrb_state *mrb, struct RClass *outer, const char *name) = 0;
  virtual struct mrb_value classNewInstance(int argc, mrb_value *argv, struct RClass *c) = 0;
  virtual void defineMethod(struct RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual struct RClass * defineModule(const char *name) = 0;
  virtual struct RClass * defineClass(const char *name, struct RClass *super) = 0;
  virtual struct mrb_value singletonClass(mrb_value v) = 0;
  virtual void includeModule(struct RClass *c, struct RClass *m) = 0;
  virtual void defineClassMethod(struct RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual void defineSingletonMethod(struct RObject *o, const char *name, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual void defineModuleFunction(struct RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual void undefMethod(struct RClass *c, const char *name) = 0;
  virtual void undefClassMethod(struct RClass *c, const char *name) = 0;
  virtual struct mrb_value instanceNew(mrb_value cv) = 0;
  virtual struct mrb_value objNew(struct RClass *c, int argc, mrb_value *argv) = 0;
  virtual struct RClass * classNew(struct RClass *super) = 0;
  virtual struct RClass * moduleNew( void ) = 0;
  virtual mrb_bool objRespondTo(struct RClass* c, mrb_sym mid) = 0;
  virtual mrb_value objDup(mrb_value obj) = 0;
  virtual void defineConst(struct RClass *mod, const char *name, mrb_value v) = 0;
  virtual struct mrb_value checkToInteger(mrb_value val, const char *method) = 0;
  virtual struct mrb_state * open( void ) = 0;
  virtual struct mrb_value topSelf(void) = 0;
  virtual struct mrb_value load(FILE *f) = 0;
  virtual struct mrb_value load(const char *s) = 0;
  // ! Load bytecode.
  virtual struct mrb_value load(const uint8_t *bin) = 0;
  virtual struct mrb_value run(struct RProc *proc, mrb_value self) = 0;
  virtual struct mrb_value funcall(mrb_value self, const char *name) = 0;
  virtual struct mrb_value funcall(mrb_value self, const char *name, int argc, ...) = 0;
  virtual struct mrb_value funcall(const char *name) = 0;
  virtual struct mrb_value funcall(const char *name, int argc, ...) = 0;
  // ! Please use mrb_fixnum if you can use. mrb_fixnum is macro.
  virtual mrb_int fixnum(struct mrb_value value) = 0;
  virtual struct mrb_value fixnumValue(mrb_int i) = 0;
};

#endif
