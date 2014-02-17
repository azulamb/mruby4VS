#include <stdarg.h>
#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/irep.h>
#include <mruby/array.h>
#include "Spinel.h"

// Spinel

Spinel::Spinel(void)
{
  mrb = open();
}

Spinel::~Spinel(void)
{
}

struct mrb_state * Spinel::get(void)
{
  return mrb;
}

// mruby.h

struct mrb_value Spinel::classNewInstance(int argc, mrb_value *argv, struct RClass *c)
{
  return mrb_class_new_instance( mrb, argc, argv, c );
}

// class.c

mrb_bool Spinel::classDefined(const char *name)
{
  return mrb_class_defined( mrb, name );
}

struct RClass * Spinel::classGet(const char *name)
{
  return mrb_class_get( mrb, name );
}

struct RClass * Spinel::classGetUnder(struct RClass *outer, const char *name)
{
  return mrb_class_get_under( mrb, outer, name );
}

struct RClass * Spinel::defineClassUnder(struct RClass *outer, const char *name, struct RClass *super)
{
  return mrb_define_class_under( mrb, outer, name, super );
}

struct RClass * Spinel::defineModuleUnder(mrb_state *mrb, struct RClass *outer, const char *name)
{
  return mrb_define_module_under( mrb, outer, name );
}

void Spinel::defineMethod(struct RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec)
{
  return mrb_define_method( mrb, c, name, func, aspec );
}

struct RClass * Spinel::defineModule(const char *name)
{
  return mrb_define_module(mrb, name);
}

struct RClass * Spinel::defineClass(const char *name, struct RClass *super)
{
  return mrb_define_class(mrb, name, super);
}

struct mrb_value Spinel::singletonClass(mrb_value v)
{
  return mrb_singleton_class( mrb, v );
}

void Spinel::includeModule(struct RClass *c, struct RClass *m)
{
  return mrb_include_module( mrb, c, m );
}

void Spinel::defineClassMethod(struct RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec)
{
  return mrb_define_class_method( mrb, c, name, func, aspec );
}

void Spinel::defineSingletonMethod(struct RObject *o, const char *name, mrb_func_t func, mrb_aspec aspec)
{
  return mrb_define_singleton_method( mrb, o, name, func, aspec );
}

void Spinel::defineModuleFunction(struct RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec)
{
  return mrb_define_module_function( mrb, c, name, func, aspec );
}

void Spinel::undefMethod(struct RClass *c, const char *name)
{
  return mrb_undef_method( mrb, c, name );
}

void Spinel::undefClassMethod(struct RClass *c, const char *name)
{
  return mrb_undef_class_method( mrb, c, name );
}

struct mrb_value Spinel::instanceNew(mrb_value cv)
{
  return mrb_instance_new( mrb, cv );
}

struct mrb_value Spinel::objNew(struct RClass *c, int argc, mrb_value *argv)
{
  return mrb_obj_new( mrb, c, argc, argv );
}

struct RClass * Spinel::classNew(struct RClass *super)
{
  return mrb_class_new( mrb, super );
}

struct RClass * Spinel::moduleNew( void )
{
  return mrb_module_new( mrb );
}

mrb_bool Spinel::objRespondTo(struct RClass* c, mrb_sym mid)
{
  return mrb_obj_respond_to( mrb, c, mid );
}

// kernel.c
mrb_value Spinel::objDup(mrb_value obj)
{
  return mrb_obj_dup( mrb, obj );
}

// variable.c
void Spinel::defineConst(struct RClass *mod, const char *name, mrb_value v)
{
  return mrb_define_const( mrb, mod, name, v );
}

// object.c

struct mrb_value Spinel::checkToInteger(mrb_value val, const char *method)
{
  return mrb_check_to_integer( mrb, val, method );
}

// state.c

struct mrb_state* Spinel::open(void)
{
  return mrb_open();
}

struct mrb_value Spinel::topSelf(void)
{
  return mrb_top_self(mrb);
}

// parse.y

struct mrb_value Spinel::load(FILE *f)
{
  return mrb_load_file(mrb, f);
}

struct mrb_value Spinel::load(const char *s)
{
  return mrb_load_string(mrb, s);
}

// load.c

struct mrb_value Spinel::load(const uint8_t *bin)
{
  return mrb_load_irep(mrb, bin);
}

// vm.c

struct mrb_value Spinel::run(struct RProc *proc, mrb_value self)
{
  return mrb_run(mrb, proc, self);
}

struct mrb_value Spinel::funcall(mrb_value self, const char *name)
{
  return mrb_funcall(mrb, self, name, 0);
}

struct mrb_value Spinel::funcall(mrb_value self, const char *name, int argc, ...)
{
  va_list ap;
  int i;

  if (argc)
  {
    va_start(ap, argc);
    for (i = 0; i < argc; i++)
    {
      argv[i] = va_arg(ap, mrb_value);
    }
    va_end(ap);
  }

  return mrb_funcall(mrb, self, name, argc,
    argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
    argv[8], argv[9], argv[10], argv[11], argv[12], argv[13], argv[14], argv[15]);
}

struct mrb_value Spinel::funcall(const char *name)
{
  return mrb_funcall(mrb, topSelf(), name, 0);
}

struct mrb_value Spinel::funcall(const char *name, int argc, ...)
{
  va_list ap;
  int i;

  if (argc)
  {
    va_start(ap, argc);
    for (i = 0; i < argc; i++)
    {
      argv[i] = va_arg(ap, mrb_value);
    }
    va_end(ap);
  }
  return mrb_funcall(mrb, topSelf(), name, argc,
    argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
    argv[8], argv[9], argv[10], argv[11], argv[12], argv[13], argv[14], argv[15]);
}

// value.h

mrb_int Spinel::fixnum(struct mrb_value value)
{
  return mrb_fixnum(value);
}

struct mrb_value Spinel::fixnumValue(mrb_int i)
{
  return mrb_fixnum_value(i);
}

// array.c

#ifdef ENABLE_MRUBY_ARRAY

void Spinel::aryModify(struct RArray* a)
{
  return mrb_ary_modify( mrb, a );
}

void Spinel::aryDecref(mrb_shared_array *shared)
{
  return mrb_ary_decref( mrb, shared );
}

struct mrb_value Spinel::aryNewCapa(mrb_int capa)
{
  return mrb_ary_new_capa( mrb, capa );
}

struct mrb_value Spinel::aryNew(void)
{
  return mrb_ary_new( mrb );
}

struct mrb_value Spinel::aryNewFromValues(mrb_int size, const struct mrb_value *vals)
{
  return mrb_ary_new_from_values( mrb, size, vals );
}

void Spinel::aryConcat(struct mrb_value self, struct mrb_value other)
{
  return mrb_ary_concat( mrb, self, other );
}

struct mrb_value Spinel::arySplat(struct mrb_value v)
{
  return mrb_ary_splat( mrb, v );
}

void Spinel::aryPush(struct mrb_value ary, struct mrb_value ele)
{
  return mrb_ary_push( mrb, ary, ele );
}

struct mrb_value Spinel::aryPop(struct mrb_value ary)
{
  return mrb_ary_pop( mrb, ary );
}

struct mrb_value Spinel::aryAget(struct mrb_value self)
{
  return mrb_ary_aget( mrb, self );
}

struct mrb_value Spinel::aryRef(struct mrb_value ary, mrb_int n)
{
  return mrb_ary_ref( mrb, ary, n );
}

void Spinel::arySet(struct mrb_value ary, mrb_int n, struct mrb_value val)
{
  return mrb_ary_set( mrb, ary, n, val );
}

mrb_int Spinel::aryLen(struct mrb_value ary)
{
  return mrb_ary_len( mrb, ary );
}

void Spinel::aryReplace(struct mrb_value a, struct mrb_value b)
{
  return mrb_ary_replace( mrb, a, b );
}

struct mrb_value Spinel::checkArrayType(struct mrb_value self)
{
  return mrb_check_array_type( mrb, self );
}

struct mrb_value Spinel::aryUnshift(struct mrb_value self, struct mrb_value item)
{
  return mrb_ary_unshift(mrb, self, item);
}

struct mrb_value Spinel::assocNew(struct mrb_value car, struct mrb_value cdr)
{
  return mrb_assoc_new( mrb, car, cdr );
}

struct mrb_value Spinel::aryEntry(struct mrb_value ary, mrb_int offset)
{
  return mrb_ary_entry( ary, offset );
}

struct mrb_value Spinel::aryShift(struct mrb_value self)
{
  return mrb_ary_shift( mrb, self );
}

struct mrb_value Spinel::aryClear(struct mrb_value self)
{
  return mrb_ary_clear( mrb, self );
}

struct mrb_value Spinel::aryJoin(struct mrb_value ary, struct mrb_value sep)
{
  return mrb_ary_join( mrb, ary, sep );
}

#endif
