#ifndef __SPINEL_VER
#define __SPINEL_VER "0.3.0"

//TODO: memory leak

#include <stdio.h>
#include <stdint.h>
#include "MRubyClass.h"

#ifndef MRB_FUNCALL_ARGC_MAX
#  define MRB_FUNCALL_ARGC_MAX 16
#endif

class Spinel : public MRuby
{
protected:
  struct mrb_state *mrb;
  mrb_value argv[MRB_FUNCALL_ARGC_MAX];
public:
  Spinel(void);
  virtual ~Spinel(void);

  virtual struct mrb_state * get(void);

  // mruby.h
  //typedef mrb_value(*mrb_func_t)(mrb_state *mrb, mrb_value);
  virtual struct mrb_value   classNewInstance(int argc, mrb_value *argv, struct RClass *c);

  // class.c
  virtual        mrb_bool    classDefined(const char *name);
  virtual struct RClass *    classGet(const char *name);
  virtual struct RClass *    classGetUnder(struct RClass *outer, const char *name);
  virtual struct RClass *    defineClassUnder(struct RClass *outer, const char *name, struct RClass *super);
  virtual struct RClass *    defineModuleUnder(mrb_state *mrb, struct RClass *outer, const char *name);
  virtual        void        defineMethod(struct RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec);
  virtual struct RClass *    defineModule( const char *name);
  virtual struct RClass *    defineClass(const char *name, struct RClass *super);
  virtual struct mrb_value   singletonClass(mrb_value v);
  virtual        void        includeModule(struct RClass *c, struct RClass *m);
  virtual        void        defineClassMethod(struct RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec);
  virtual        void        defineSingletonMethod(struct RObject *o, const char *name, mrb_func_t func, mrb_aspec aspec);
  virtual        void        defineModuleFunction(struct RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec);
  virtual        void        undefMethod(struct RClass *c, const char *name);
  virtual        void        undefClassMethod(struct RClass *c, const char *name);
  virtual struct mrb_value   instanceNew(mrb_value cv);
  virtual struct mrb_value   objNew(struct RClass *c, int argc, mrb_value *argv);
  virtual struct RClass *    classNew(struct RClass *super);
  virtual struct RClass *    moduleNew( void );
  virtual        mrb_bool    objRespondTo(struct RClass* c, mrb_sym mid);

  // kernel.c
  virtual struct mrb_value   objDup(mrb_value obj);

  // variable.c
  virtual        void        defineConst(struct RClass *mod, const char *name, mrb_value v);

  // object.c
  virtual struct mrb_value   checkToInteger(mrb_value val, const char *method);

  // state.c
  virtual struct mrb_state * open(void);
  virtual struct mrb_value   topSelf(void);

  // parse.y
  virtual struct mrb_value   load(FILE *f);
  virtual struct mrb_value   load(const char *s);

  // load.c
  virtual struct mrb_value   load(const uint8_t *bin);

  // vm.c
  virtual struct mrb_value   run(struct RProc *proc, mrb_value self);
  virtual struct mrb_value   funcall(mrb_value self, const char *name);
  virtual struct mrb_value   funcall(mrb_value self, const char *name, int argc, ...);
  virtual struct mrb_value   funcall(const char *name);
  virtual struct mrb_value   funcall(const char *name, int argc, ...);

  // value.h
  virtual        mrb_int     fixnum(struct mrb_value value);
  virtual struct mrb_value   fixnumValue(mrb_int i);

  // array.c
#ifdef ENABLE_MRUBY_ARRAY
  virtual        void        aryModify(struct RArray* a);
  virtual        void        aryDecref(struct mrb_shared_array *shared);
  virtual struct mrb_value   aryNewCapa(mrb_int capa);
  virtual struct mrb_value   aryNew(void);
  virtual struct mrb_value   aryNewFromValues(mrb_int size, const struct mrb_value *vals);
  virtual        void        aryConcat(struct mrb_value self, struct mrb_value other);
  virtual struct mrb_value   arySplat(struct mrb_value v);
  virtual        void        aryPush(struct mrb_value ary, struct mrb_value ele);
  virtual struct mrb_value   aryPop(struct mrb_value ary);
  virtual struct mrb_value   aryAget(struct mrb_value self);
  virtual struct mrb_value   aryRef(struct mrb_value ary, mrb_int n);
  virtual        void        arySet(struct mrb_value ary, mrb_int n, struct mrb_value val);
  virtual        mrb_int     aryLen(struct mrb_value ary);
  virtual        void        aryReplace(struct mrb_value a, struct mrb_value b);
  virtual struct mrb_value   checkArrayType(struct mrb_value self);
  virtual struct mrb_value   aryUnshift(struct mrb_value self, struct mrb_value item);
  virtual struct mrb_value   assocNew(struct mrb_value car, struct mrb_value cdr);
  virtual struct mrb_value   aryEntry(struct mrb_value ary, mrb_int offset);
  virtual struct mrb_value   aryShift(struct mrb_value self);
  virtual struct mrb_value   aryClear(struct mrb_value self);
  virtual struct mrb_value   aryJoin(struct mrb_value ary, struct mrb_value sep); 
#endif
  /*
  struct RClass * mrb_define_class_under(mrb_state *mrb, struct RClass *outer, const char *name, struct RClass *super);
  struct RClass * mrb_define_module_under(mrb_state *mrb, struct RClass *outer, const char *name);
  */
};

#endif
