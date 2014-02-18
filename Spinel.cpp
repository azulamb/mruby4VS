#include <stdarg.h>

#include "Spinel.h"

// Spinel

Spinel::Spinel(void)
{
  mrb = open();
}

Spinel::~Spinel(void)
{
}

mrb_state * Spinel::get(void)
{
  return mrb;
}

mrb_value Spinel::load(const char *filepath)
{
  mrb_value ret = {};
  FILE *f;
  if (fopen_s( &f, filepath, "r" ) != 0)
  {
    return ret;
  }
  ret = loadFile( f );
  fclose( f );
  return ret;
}

// mruby.h

mrb_value Spinel::classNewInstance(int argc, mrb_value *argv, RClass *c)
{
  return mrb_class_new_instance( mrb, argc, argv, c );
}

// class.c

mrb_bool Spinel::classDefined(const char *name)
{
  return mrb_class_defined( mrb, name );
}

RClass * Spinel::classGet(const char *name)
{
  return mrb_class_get( mrb, name );
}

RClass * Spinel::classGetUnder(RClass *outer, const char *name)
{
  return mrb_class_get_under( mrb, outer, name );
}

RClass * Spinel::defineClassUnder(RClass *outer, const char *name, RClass *super)
{
  return mrb_define_class_under( mrb, outer, name, super );
}

RClass * Spinel::defineModuleUnder(mrb_state *mrb, RClass *outer, const char *name)
{
  return mrb_define_module_under( mrb, outer, name );
}

void Spinel::defineMethod(RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec)
{
  return mrb_define_method( mrb, c, name, func, aspec );
}

RClass * Spinel::defineModule(const char *name)
{
  return mrb_define_module(mrb, name);
}

RClass * Spinel::defineClass(const char *name, RClass *super)
{
  return mrb_define_class(mrb, name, super);
}

mrb_value Spinel::singletonClass(mrb_value v)
{
  return mrb_singleton_class( mrb, v );
}

void Spinel::includeModule(RClass *c, RClass *m)
{
  return mrb_include_module( mrb, c, m );
}

void Spinel::defineClassMethod(RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec)
{
  return mrb_define_class_method( mrb, c, name, func, aspec );
}

void Spinel::defineSingletonMethod(RObject *o, const char *name, mrb_func_t func, mrb_aspec aspec)
{
  return mrb_define_singleton_method( mrb, o, name, func, aspec );
}

void Spinel::defineModuleFunction(RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec)
{
  return mrb_define_module_function( mrb, c, name, func, aspec );
}

void Spinel::undefMethod(RClass *c, const char *name)
{
  return mrb_undef_method( mrb, c, name );
}

void Spinel::undefClassMethod(RClass *c, const char *name)
{
  return mrb_undef_class_method( mrb, c, name );
}

mrb_value Spinel::instanceNew(mrb_value cv)
{
  return mrb_instance_new( mrb, cv );
}

mrb_value Spinel::objNew(RClass *c, int argc, mrb_value *argv)
{
  return mrb_obj_new( mrb, c, argc, argv );
}

RClass * Spinel::classNew(RClass *super)
{
  return mrb_class_new( mrb, super );
}

RClass * Spinel::moduleNew( void )
{
  return mrb_module_new( mrb );
}

mrb_bool Spinel::objRespondTo(RClass* c, mrb_sym mid)
{
  return mrb_obj_respond_to( mrb, c, mid );
}

// kernel.c
mrb_value Spinel::objDup(mrb_value obj)
{
  return mrb_obj_dup( mrb, obj );
}

// variable.c
void Spinel::defineConst(RClass *mod, const char *name, mrb_value v)
{
  return mrb_define_const( mrb, mod, name, v );
}

// object.c

mrb_value Spinel::checkToInteger(mrb_value val, const char *method)
{
  return mrb_check_to_integer( mrb, val, method );
}

// state.c

mrb_state* Spinel::open(void)
{
  return mrb_open();
}

mrb_value Spinel::topSelf(void)
{
  return mrb_top_self(mrb);
}

// parse.y

mrb_value Spinel::loadFile(FILE *f)
{
  return mrb_load_file(mrb, f);
}

mrb_value Spinel::loadString(const char *s)
{
  return mrb_load_string(mrb, s);
}

// load.c

mrb_value Spinel::loadIrep(const uint8_t *bin)
{
  return mrb_load_irep(mrb, bin);
}

// vm.c

mrb_value Spinel::run(RProc *proc, mrb_value self)
{
  return mrb_run(mrb, proc, self);
}

mrb_value Spinel::funcall(mrb_value self, const char *name)
{
  return mrb_funcall(mrb, self, name, 0);
}

mrb_value Spinel::funcall(mrb_value self, const char *name, int argc, ...)
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

mrb_value Spinel::funcall(const char *name)
{
  return mrb_funcall(mrb, topSelf(), name, 0);
}

mrb_value Spinel::funcall(const char *name, int argc, ...)
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

mrb_int Spinel::fixnum(mrb_value value)
{
  return mrb_fixnum(value);
}

mrb_value Spinel::fixnumValue(mrb_int i)
{
  return mrb_fixnum_value(i);
}

// array.c

#ifdef __ENABLE_MRUBY_ARRAY

void Spinel::aryModify(RArray* a)
{
  return mrb_ary_modify( mrb, a );
}

void Spinel::aryDecref(mrb_shared_array *shared)
{
  return mrb_ary_decref( mrb, shared );
}

mrb_value Spinel::aryNewCapa(mrb_int capa)
{
  return mrb_ary_new_capa( mrb, capa );
}

mrb_value Spinel::aryNew(void)
{
  return mrb_ary_new( mrb );
}

mrb_value Spinel::aryNewFromValues(mrb_int size, const mrb_value *vals)
{
  return mrb_ary_new_from_values( mrb, size, vals );
}

void Spinel::aryConcat(mrb_value self, mrb_value other)
{
  return mrb_ary_concat( mrb, self, other );
}

mrb_value Spinel::arySplat(mrb_value v)
{
  return mrb_ary_splat( mrb, v );
}

void Spinel::aryPush(mrb_value ary, mrb_value ele)
{
  return mrb_ary_push( mrb, ary, ele );
}

mrb_value Spinel::aryPop(mrb_value ary)
{
  return mrb_ary_pop( mrb, ary );
}

mrb_value Spinel::aryAget(mrb_value self)
{
  return mrb_ary_aget( mrb, self );
}

mrb_value Spinel::aryRef(mrb_value ary, mrb_int n)
{
  return mrb_ary_ref( mrb, ary, n );
}

void Spinel::arySet(mrb_value ary, mrb_int n, mrb_value val)
{
  return mrb_ary_set( mrb, ary, n, val );
}

mrb_int Spinel::aryLen(mrb_value ary)
{
  return mrb_ary_len( mrb, ary );
}

void Spinel::aryReplace(mrb_value a, mrb_value b)
{
  return mrb_ary_replace( mrb, a, b );
}

mrb_value Spinel::checkArrayType(mrb_value self)
{
  return mrb_check_array_type( mrb, self );
}

mrb_value Spinel::aryUnshift(mrb_value self, mrb_value item)
{
  return mrb_ary_unshift(mrb, self, item);
}

mrb_value Spinel::assocNew(mrb_value car, mrb_value cdr)
{
  return mrb_assoc_new( mrb, car, cdr );
}

mrb_value Spinel::aryEntry(mrb_value ary, mrb_int offset)
{
  return mrb_ary_entry( ary, offset );
}

mrb_value Spinel::aryShift(mrb_value self)
{
  return mrb_ary_shift( mrb, self );
}

mrb_value Spinel::aryClear(mrb_value self)
{
  return mrb_ary_clear( mrb, self );
}

mrb_value Spinel::aryJoin(mrb_value ary, mrb_value sep)
{
  return mrb_ary_join( mrb, ary, sep );
}

#endif

// class.c

#ifdef __ENABLE_MRUBY_CLASS

RClass * Spinel::defineClassId(mrb_sym name, RClass *super)
{
  return mrb_define_class_id( mrb, name, super );
}

RClass * Spinel::defineModuleId(mrb_sym name)
{
  return mrb_define_module_id( mrb, name );
}

RClass * Spinel::vmDefineClass(mrb_value outer, mrb_value super, mrb_sym id)
{
  return mrb_vm_define_class( mrb, outer, super, id );
}

RClass * Spinel::vmDefineModule(mrb_value outer, mrb_sym id)
{
  return mrb_vm_define_module( mrb, outer, id );
}

void Spinel::defineMethodVm(RClass *c, mrb_sym name, mrb_value body)
{
  return mrb_define_method_vm( mrb, c, name, body );
}

void Spinel::defineMethodRaw(RClass *c, mrb_sym mid, RProc *p)
{
  return mrb_define_method_raw( mrb, c, mid, p );
}

void Spinel::defineMethodId(RClass *c, mrb_sym mid, mrb_func_t func, mrb_aspec aspec)
{
  return mrb_define_method_id( mrb, c, mid, func, aspec );
}

void Spinel::aliasMethod(RClass *c, mrb_sym a, mrb_sym b)
{
  return mrb_alias_method( mrb, c, a, b );
}

RClass * Spinel::classOuterModule(RClass *c)
{
  return mrb_class_outer_module( mrb, c );
}

RProc * Spinel::methodSearchVm(RClass **cp, mrb_sym mid)
{
  return mrb_method_search_vm( mrb, cp, mid );
}

RProc * Spinel::methodSearch(RClass* c, mrb_sym mid)
{
  return mrb_method_search( mrb, c, mid );
}

RClass* Spinel::classReal(RClass* cl)
{
  return mrb_class_real( cl );
}

void Spinel::gcMarkMt(RClass *c)
{
  return mrb_gc_mark_mt( mrb, c );
}

size_t Spinel::gcMarkMtSize(RClass *c)
{
  return mrb_gc_mark_mt_size( mrb, c );
}

void Spinel::gcFreeMt(RClass *c)
{
  return mrb_gc_free_mt( mrb, c );
}

#endif

#ifdef __ENABLE_MRUBY_COMPILE

// parser.y
mrbc_context * Spinel::cContextNew(void)
{
  return mrbc_context_new( mrb );
}

void Spinel::cContextFree(mrbc_context *cxt)
{
  return mrbc_context_free( mrb, cxt );
}

const char * Spinel::cFilename(mrbc_context *c, const char *s)
{
  return mrbc_filename( mrb, c, s );
}

void Spinel::cPartialHook(mrbc_context *c, int(*partial_hook)(mrb_parser_state*), void *data)
{
  return mrbc_partial_hook( mrb, c, partial_hook,data );
}

mrb_parser_state * Spinel::parserNew(void)
{
  return mrb_parser_new( mrb );
}

void Spinel::parserFree(mrb_parser_state *p)
{
  return mrb_parser_free( p );
}

void Spinel::parserParse(mrb_parser_state *p, mrbc_context *c)
{
  return mrb_parser_parse( p, c );
}

void Spinel::parserSetFilename(mrb_parser_state *p, const char *f)
{
  return mrb_parser_set_filename( p, f );
}

const char * Spinel::parserGetFilename(mrb_parser_state *p, uint16_t idx)
{
  return mrb_parser_get_filename( p, idx );
}

mrb_parser_state* Spinel::parseString(const char *s, mrbc_context *c)
{
  return mrb_parse_string( mrb, s, c );
}

mrb_parser_state* Spinel::parseNstring(const char *s, int len, mrbc_context *c)
{
  return mrb_parse_nstring( mrb, s, len, c );
}

mrb_value Spinel::loadNstring(const char *s, int len)
{
  return mrb_load_nstring( mrb, s, len );
}

mrb_value Spinel::loadStringCxt(const char *s, mrbc_context *cxt)
{
  return mrb_load_string_cxt( mrb, s, cxt );
}

mrb_value Spinel::loadNstringCxt(const char *s, int len, mrbc_context *cxt)
{
  return mrb_load_nstring_cxt( mrb, s, len, cxt );
}

mrb_parser_state * Spinel::parseFile(FILE *f, mrbc_context *c)
{
  return mrb_parse_file( mrb, f, c );
}

mrb_value Spinel::loadFileCxt(FILE *f, mrbc_context *c)
{
  return mrb_load_file_cxt( mrb, f, c );
}

// codegen.c
RProc * Spinel::generateCode(mrb_parser_state *p)
{
  return mrb_generate_code( mrb, p );
}

#endif

#ifdef __ENABLE_MRUBY_DUMP

// dump.c

int Spinel::dumpIrepBinary(mrb_irep *irep, int debug_info, FILE* fp)
{
  return mrb_dump_irep_binary( mrb, irep, debug_info, fp );
}

int Spinel::dumpIrepCfunc(mrb_irep *irep, int debug_info, FILE *fp, const char *initname)
{
  return mrb_dump_irep_cfunc( mrb,irep, debug_info, fp, initname );
}

// load.c

mrb_irep * Spinel::readIrepFile(FILE*fp)
{
  return mrb_read_irep_file( mrb, fp );
}

mrb_value Spinel::loadIrepFile(FILE*fp)
{
  return mrb_load_irep_file( mrb, fp );
}

mrb_value Spinel::loadIrepFileCxt(FILE*fp, mrbc_context *c)
{
  return mrb_load_irep_file_cxt( mrb, fp, c );
}

#endif

#ifdef __ENABLE_MRUBY_GC

// gc.c

void Spinel::objspaceEachObjects(each_object_callback* callback, void *data)
{
  return mrb_objspace_each_objects(mrb, callback, data);
}

void Spinel::freeContext(mrb_context *c)
{
  return mrb_free_context( mrb, c );
}

#endif

#ifdef __ENABLE_MRUBY_HASH

// hash.c

mrb_value Spinel::hashNewCapa(int capa)
{
  return mrb_hash_new_capa( mrb, capa );
}

mrb_value Spinel::hashNew(void)
{
  return mrb_hash_new( mrb );
}

void Spinel::hashSet(mrb_value hash, mrb_value key, mrb_value val)
{
  return mrb_hash_set( mrb, hash, key, val );
}

mrb_value Spinel::hashGet(mrb_value hash, mrb_value key)
{
  return mrb_hash_get( mrb, hash, key );
}

mrb_value Spinel::hashFetch(mrb_value hash, mrb_value key, mrb_value def)
{
  return mrb_hash_fetch( mrb, hash, key, def );
}

mrb_value Spinel::hashDeleteKey(mrb_value hash, mrb_value key)
{
  return mrb_hash_delete_key( mrb, hash, key );
}

mrb_value Spinel::hashKeys(mrb_value hash)
{
  return mrb_hash_keys( mrb, hash );
}

mrb_value Spinel::checkHashType(mrb_value hash)
{
  return mrb_check_hash_type( mrb, hash );
}

mrb_value Spinel::hashEmptyP(mrb_value self)
{
  return mrb_hash_empty_p( mrb, self );
}

mrb_value Spinel::hashClear(mrb_value hash)
{
  return mrb_hash_clear( mrb, hash );
}

kh_ht * Spinel::hashTbl(mrb_value hash)
{
  return mrb_hash_tbl( mrb, hash );
}

void Spinel::gcMarkHash(RHash *hash)
{
  return mrb_gc_mark_hash( mrb, hash );
}

size_t Spinel::gcMarkHashSize(RHash *hash)
{
  return mrb_gc_mark_hash_size( mrb, hash );
}

void Spinel::gcFreeHash(RHash *hash)
{
  return mrb_gc_free_hash( mrb, hash );
}

#endif

#ifdef __ENABLE_MRUBY_IREP

// load.c
mrb_value Spinel::loadIrepCxt(const uint8_t*bin, mrbc_context *c)
{
  return mrb_load_irep_cxt( mrb, bin, c );
}

// state.c
mrb_irep * Spinel::addIrep(void)
{
  return mrb_add_irep( mrb );
}

void Spinel::irepFree(mrb_irep *irep)
{
  return mrb_irep_free( mrb, irep );
}

void Spinel::irepIncref(mrb_irep *irep)
{
  return mrb_irep_incref( mrb, irep );
}

void Spinel::irepDecref(mrb_irep *irep)
{
  return mrb_irep_decref( mrb, irep );
}

#endif