#ifndef __MRUBY_CLASS
#define __MRUBY_CLASS

#ifndef NO_GETTIMEOFDAY
#  define NO_GETTIMEOFDAY
#endif

#define __ENABLE_MRUBY_ARRAY
#define __ENABLE_MRUBY_CLASS

#include "mruby.h"
#include "mruby/value.h"

class MRuby
{
public:
  MRuby(void){}
  virtual ~MRuby(void){}

  virtual struct mrb_state * get( void ) = 0;

  virtual        mrb_bool    classDefined(const char *name) = 0;
  virtual struct RClass *    classGet(const char *name) = 0;
  virtual struct RClass *    classGetUnder(struct RClass *outer, const char *name) = 0;
  virtual struct RClass *    defineClassUnder(struct RClass *outer, const char *name, struct RClass *super) = 0;
  virtual struct RClass *    defineModuleUnder(mrb_state *mrb, struct RClass *outer, const char *name) = 0;
  virtual struct mrb_value   classNewInstance(int argc, mrb_value *argv, struct RClass *c) = 0;
  virtual        void        defineMethod(struct RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual struct RClass *    defineModule(const char *name) = 0;
  virtual struct RClass *    defineClass(const char *name, struct RClass *super) = 0;
  virtual struct mrb_value   singletonClass(mrb_value v) = 0;
  virtual        void        includeModule(struct RClass *c, struct RClass *m) = 0;
  virtual        void        defineClassMethod(struct RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual        void        defineSingletonMethod(struct RObject *o, const char *name, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual        void        defineModuleFunction(struct RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual        void        undefMethod(struct RClass *c, const char *name) = 0;
  virtual        void        undefClassMethod(struct RClass *c, const char *name) = 0;
  virtual struct mrb_value   instanceNew(mrb_value cv) = 0;
  virtual struct mrb_value   objNew(struct RClass *c, int argc, mrb_value *argv) = 0;
  virtual struct RClass *    classNew(struct RClass *super) = 0;
  virtual struct RClass *    moduleNew( void ) = 0;
  virtual        mrb_bool    objRespondTo(struct RClass* c, mrb_sym mid) = 0;
  virtual struct mrb_value   objDup(mrb_value obj) = 0;
  virtual        void        defineConst(struct RClass *mod, const char *name, mrb_value v) = 0;
  virtual struct mrb_value   checkToInteger(mrb_value val, const char *method) = 0;
  virtual struct mrb_state * open( void ) = 0;
  virtual struct mrb_value   topSelf(void) = 0;
  virtual struct mrb_value   load(FILE *f) = 0;
  virtual struct mrb_value   load(const char *s) = 0;
  // ! Load bytecode.
  virtual struct mrb_value   load(const uint8_t *bin) = 0;
  virtual struct mrb_value   loadFromFile( const char *filepath ) = 0;
  // loadFromRiteFile
  virtual struct mrb_value   run(struct RProc *proc, mrb_value self) = 0;
  virtual struct mrb_value   funcall(mrb_value self, const char *name) = 0;
  virtual struct mrb_value   funcall(mrb_value self, const char *name, int argc, ...) = 0;
  virtual struct mrb_value   funcall(const char *name) = 0;
  virtual struct mrb_value   funcall(const char *name, int argc, ...) = 0;
  // ! Please use mrb_fixnum if you can use. mrb_fixnum is macro.
  virtual        mrb_int     fixnum(struct mrb_value value) = 0;
  virtual struct mrb_value   fixnumValue(mrb_int i) = 0;

#ifdef __ENABLE_MRUBY_ARRAY
  virtual        void        aryModify(struct RArray* a) = 0;
  virtual        void        aryDecref(struct mrb_shared_array *shared) = 0;
  virtual struct mrb_value   aryNewCapa(mrb_int capa) = 0;
  virtual struct mrb_value   aryNew(void) = 0;
  virtual struct mrb_value   aryNewFromValues(mrb_int size, const struct mrb_value *vals) = 0;
  virtual        void        aryConcat(struct mrb_value self, struct mrb_value other) = 0;
  virtual struct mrb_value   arySplat(struct mrb_value v) = 0;
  virtual        void        aryPush(struct mrb_value ary, struct mrb_value ele) = 0;
  virtual struct mrb_value   aryPop(struct mrb_value ary) = 0;
  virtual struct mrb_value   aryAget(struct mrb_value self) = 0;
  virtual struct mrb_value   aryRef(struct mrb_value ary, mrb_int n) = 0;
  virtual        void        arySet(struct mrb_value ary, mrb_int n, struct mrb_value val) = 0;
  virtual        mrb_int     aryLen(struct mrb_value ary) = 0;
  virtual        void        aryReplace(struct mrb_value a, struct mrb_value b) = 0;
  virtual struct mrb_value   checkArrayType(struct mrb_value self) = 0;
  virtual struct mrb_value   aryUnshift(struct mrb_value self, struct mrb_value item) = 0;
  virtual struct mrb_value   assocNew(struct mrb_value car, struct mrb_value cdr) = 0;
  virtual struct mrb_value   aryEntry(struct mrb_value ary, mrb_int offset) = 0;
  virtual struct mrb_value   aryShift(struct mrb_value self) = 0;
  virtual struct mrb_value   aryClear(struct mrb_value self) = 0;
  virtual struct mrb_value   aryJoin(struct mrb_value ary, struct mrb_value sep) = 0;
#endif

#ifdef __ENABLE_MRUBY_CLASS
  virtual struct RClass *    defineClassId( mrb_sym name, struct RClass *super) = 0;
  virtual struct RClass *    defineModuleId(mrb_sym name) = 0;
  virtual struct RClass *    vmDefineClass(struct mrb_value outer, struct mrb_value super, mrb_sym id) = 0;
  virtual struct RClass *    vmDefineModule(struct mrb_value outer, mrb_sym id) = 0;
  virtual        void        defineMethodVm(struct RClass *c, mrb_sym name, struct mrb_value body) = 0;
  virtual        void        defineMethodRaw(struct RClass *c, mrb_sym mid, struct RProc *p) = 0;
  virtual        void        defineMethodId(struct RClass *c, mrb_sym mid, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual        void        aliasMethod(struct RClass *c, mrb_sym a, mrb_sym b) = 0;
  virtual struct RClass *    classOuterModule(struct RClass *c) = 0;
  virtual struct RProc *     methodSearchVm(struct RClass **cp, mrb_sym mid) = 0;
  virtual struct RProc *     methodSearch(struct RClass* c, mrb_sym mid) = 0;
  virtual struct RClass*     classReal(struct RClass* cl) = 0;
  virtual        void        gcMarkMt(struct RClass *c) = 0;
  virtual        size_t      gcMarkMtSize(struct RClass *c) = 0;
  virtual        void        gcFreeMt(struct RClass *c) = 0;
#endif


};


#endif
