#ifndef __MRUBY_CLASS
#define __MRUBY_CLASS

#ifndef NO_GETTIMEOFDAY
#  define NO_GETTIMEOFDAY
#endif

#define __ENABLE_MRUBY_ARRAY
#define __ENABLE_MRUBY_CLASS
#define __ENABLE_MRUBY_COMPILE
#define __ENABLE_MRUBY_DATA
//#define __ENABLE_MRUBY_DEBUG
#define __ENABLE_MRUBY_DUMP
//#define __ENABLE_MRUBY_GC
#define __ENABLE_MRUBY_HASH
#define __ENABLE_MRUBY_IREP

#include "mruby.h"
#include "mruby/value.h"

#ifdef __ENABLE_MRUBY_ARRAY
#include "mruby/array.h"
#endif

#ifdef __ENABLE_MRUBY_CLASS
#include "mruby/class.h"
#endif

#ifdef __ENABLE_MRUBY_COMPILE
#include "mruby/compile.h"
#endif

#ifdef __ENABLE_MRUBY_DATA
#include "mruby/data.h"
#endif

#ifdef __ENABLE_MRUBY_DEBUG
#include "mruby/debug.h"
#endif

#ifdef __ENABLE_MRUBY_DUMP
#include "mruby/dump.h"
#endif

#ifdef __ENABLE_MRUBY_GC
#include "mruby/gc.h"
#endif

#ifdef __ENABLE_MRUBY_HASH
#include "mruby/hash.h"
#endif

#ifdef __ENABLE_MRUBY_IREP
#include "mruby/irep.h"
#endif


#ifdef __ENABLE_MRUBY_GC
#include "mruby/gc.h"
#endif

class MRuby
{
public:
  MRuby(void){}
  virtual ~MRuby(void){}

  virtual mrb_state *        get(void) = 0;
  virtual mrb_value          load(const char *filepath) = 0;

  virtual mrb_bool           classDefined(const char *name) = 0;
  virtual RClass *           classGet(const char *name) = 0;
  virtual RClass *           classGetUnder(RClass *outer, const char *name) = 0;
  virtual RClass *           defineClassUnder(RClass *outer, const char *name, RClass *super) = 0;
  virtual RClass *           defineModuleUnder(mrb_state *mrb, RClass *outer, const char *name) = 0;
  virtual mrb_value          classNewInstance(int argc, mrb_value *argv, RClass *c) = 0;
  virtual void               defineMethod(RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual RClass *           defineModule(const char *name) = 0;
  virtual RClass *           defineClass(const char *name, RClass *super) = 0;
  virtual mrb_value          singletonClass(mrb_value v) = 0;
  virtual void               includeModule(RClass *c, RClass *m) = 0;
  virtual void               defineClassMethod(RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual void               defineSingletonMethod(RObject *o, const char *name, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual void               defineModuleFunction(RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual void               undefMethod(RClass *c, const char *name) = 0;
  virtual void               undefClassMethod(RClass *c, const char *name) = 0;
  virtual mrb_value          instanceNew(mrb_value cv) = 0;
  virtual mrb_value          objNew(RClass *c, int argc, mrb_value *argv) = 0;
  virtual RClass *           classNew(RClass *super) = 0;
  virtual RClass *           moduleNew(void) = 0;
  virtual mrb_bool           objRespondTo(RClass* c, mrb_sym mid) = 0;
  virtual mrb_value          objDup(mrb_value obj) = 0;
  virtual void               defineConst(RClass *mod, const char *name, mrb_value v) = 0;
  virtual mrb_value          checkToInteger(mrb_value val, const char *method) = 0;
  virtual mrb_state *        open(void) = 0;
  virtual mrb_value          topSelf(void) = 0;
  // ! Use loadFromFile if you use DLL.
  virtual mrb_value          loadFile(FILE *f) = 0;
  virtual mrb_value          loadString(const char *s) = 0;
  // ! Load bytecode.
  virtual mrb_value          loadIrep(const uint8_t *bin) = 0;
  // loadFromRiteFile
  virtual mrb_value          run(RProc *proc, mrb_value self) = 0;
  virtual mrb_value          funcall(mrb_value self, const char *name) = 0;
  virtual mrb_value          funcall(mrb_value self, const char *name, int argc, ...) = 0;
  virtual mrb_value          funcall(const char *name) = 0;
  virtual mrb_value          funcall(const char *name, int argc, ...) = 0;
  // ! Please use mrb_fixnum if you can use. mrb_fixnum is macro.
  virtual mrb_int            fixnum(mrb_value value) = 0;
  virtual mrb_value          fixnumValue(mrb_int i) = 0;

#ifdef __ENABLE_MRUBY_ARRAY
  virtual void               aryModify(RArray *a) = 0;
  virtual void               aryDecref(mrb_shared_array *shared) = 0;
  virtual mrb_value          aryNewCapa(mrb_int capa) = 0;
  virtual mrb_value          aryNew(void) = 0;
  virtual mrb_value          aryNewFromValues(mrb_int size, const mrb_value *vals) = 0;
  virtual void               aryConcat(mrb_value self, mrb_value other) = 0;
  virtual mrb_value          arySplat(mrb_value v) = 0;
  virtual void               aryPush(mrb_value ary, mrb_value ele) = 0;
  virtual mrb_value          aryPop(mrb_value ary) = 0;
  virtual mrb_value          aryAget(mrb_value self) = 0;
  virtual mrb_value          aryRef(mrb_value ary, mrb_int n) = 0;
  virtual void               arySet(mrb_value ary, mrb_int n, mrb_value val) = 0;
  virtual mrb_int            aryLen(mrb_value ary) = 0;
  virtual void               aryReplace(mrb_value a, mrb_value b) = 0;
  virtual mrb_value          checkArrayType(mrb_value self) = 0;
  virtual mrb_value          aryUnshift(mrb_value self, mrb_value item) = 0;
  virtual mrb_value          assocNew(mrb_value car, mrb_value cdr) = 0;
  virtual mrb_value          aryEntry(mrb_value ary, mrb_int offset) = 0;
  virtual mrb_value          aryShift(mrb_value self) = 0;
  virtual mrb_value          aryClear(mrb_value self) = 0;
  virtual mrb_value          aryJoin(mrb_value ary, mrb_value sep) = 0;
#endif

#ifdef __ENABLE_MRUBY_CLASS
  virtual RClass *           defineClassId(mrb_sym name, RClass *super) = 0;
  virtual RClass *           defineModuleId(mrb_sym name) = 0;
  virtual RClass *           vmDefineClass(mrb_value outer, mrb_value super, mrb_sym id) = 0;
  virtual RClass *           vmDefineModule(mrb_value outer, mrb_sym id) = 0;
  virtual void               defineMethodVm(RClass *c, mrb_sym name, mrb_value body) = 0;
  virtual void               defineMethodRaw(RClass *c, mrb_sym mid, RProc *p) = 0;
  virtual void               defineMethodId(RClass *c, mrb_sym mid, mrb_func_t func, mrb_aspec aspec) = 0;
  virtual void               aliasMethod(RClass *c, mrb_sym a, mrb_sym b) = 0;
  virtual RClass *           classOuterModule(RClass *c) = 0;
  virtual RProc *            methodSearchVm(RClass **cp, mrb_sym mid) = 0;
  virtual RProc *            methodSearch(RClass* c, mrb_sym mid) = 0;
  virtual RClass*            classReal(RClass* cl) = 0;
  virtual void               gcMarkMt(RClass *c) = 0;
  virtual size_t             gcMarkMtSize(RClass *c) = 0;
  virtual void               gcFreeMt(RClass *c) = 0;
#endif

#ifdef __ENABLE_MRUBY_COMPILE
  virtual mrbc_context *     cContextNew(void) = 0;
  virtual void               cContextFree(mrbc_context *cxt) = 0;
  virtual const char *       cFilename(mrbc_context *c, const char *s) = 0;
  virtual void               cPartialHook(mrbc_context *c, int(*partial_hook)(mrb_parser_state*), void *data) = 0;
  virtual mrb_parser_state * parserNew(void) = 0;
  virtual void               parserFree(mrb_parser_state *p) = 0;
  virtual void               parserParse(mrb_parser_state *p, mrbc_context *c) = 0;
  virtual void               parserSetFilename(mrb_parser_state *p, const char *f) = 0;
  virtual const char *       parserGetFilename(mrb_parser_state *p, uint16_t idx) = 0;
  virtual mrb_parser_state*  parseString(const char *s, mrbc_context *c) = 0;
  virtual mrb_parser_state*  parseNstring(const char *s, int len, mrbc_context *c) = 0;
  virtual mrb_value          loadNstring(const char *s, int len) = 0;
  virtual mrb_value          loadStringCxt(const char *s, mrbc_context *cxt) = 0;
  virtual mrb_value          loadNstringCxt(const char *s, int len, mrbc_context *cxt) = 0;
  virtual mrb_parser_state * parseFile(FILE *f, mrbc_context *c) = 0;
  virtual mrb_value          loadFileCxt(FILE *f, mrbc_context *c) = 0;
  virtual RProc *            generateCode(mrb_parser_state *p) = 0;

#endif

#ifdef __ENABLE_MRUBY_DATA
  RData *mrb_data_object_alloc(mrb_state *mrb, RClass* klass, void *datap, const mrb_data_type *type);
  void mrb_data_check_type(mrb_state *mrb, mrb_value, const mrb_data_type*);
  void *mrb_data_get_ptr(mrb_state *mrb, mrb_value, const mrb_data_type*);
  void *mrb_data_check_get_ptr(mrb_state *mrb, mrb_value, const mrb_data_type*);
#endif

#ifdef __ENABLE_MRUBY_DEBUG
#endif

#ifdef __ENABLE_MRUBY_DUMP
  virtual int                dumpIrepBinary(mrb_irep *irep, int debug_info, FILE* fp) = 0;
  virtual int                dumpIrepCfunc(mrb_irep *irep, int debug_info, FILE *fp, const char *initname) = 0;
  virtual mrb_irep *         readIrepFile(FILE*fp) = 0;
  virtual mrb_value          loadIrepFile(FILE*fp) = 0;
  virtual mrb_value          loadIrepFileCxt(FILE*fp, mrbc_context *c) = 0;
#endif

#ifdef __ENABLE_MRUBY_GC
  // symbol error
  virtual        void               objspaceEachObjects(each_object_callback* callback, void *data) = 0;
  virtual        void               freeContext(mrb_context *c) = 0;
#endif

#ifdef __ENABLE_MRUBY_HASH
  virtual mrb_value          hashNewCapa(int capa) = 0;
  virtual mrb_value          hashNew(void) = 0;
  virtual void               hashSet(mrb_value hash, mrb_value key, mrb_value val) = 0;
  virtual mrb_value          hashGet(mrb_value hash, mrb_value key) = 0;
  virtual mrb_value          hashFetch(mrb_value hash, mrb_value key, mrb_value def) = 0;
  virtual mrb_value          hashDeleteKey(mrb_value hash, mrb_value key) = 0;
  virtual mrb_value          hashKeys(mrb_value hash) = 0;
  virtual mrb_value          checkHashType(mrb_value hash) = 0;
  virtual mrb_value          hashEmptyP(mrb_value self) = 0;
  virtual mrb_value          hashClear(mrb_value hash) = 0;
  virtual kh_ht *            hashTbl(mrb_value hash) = 0;
  virtual void               gcMarkHash(RHash *hash) = 0;
  virtual size_t             gcMarkHashSize(RHash *hash) = 0;
  virtual void               gcFreeHash(RHash *hash) = 0;
#endif

#ifdef __ENABLE_MRUBY_IREP
  // load.c
  virtual mrb_value          loadIrepCxt(const uint8_t*bin, mrbc_context *c) = 0;
  // state.c
  virtual mrb_irep *         addIrep(void) = 0;
  virtual void               irepFree(mrb_irep *irep) = 0;
  virtual void               irepIncref(mrb_irep *irep) = 0;
  virtual void               irepDecref(mrb_irep *irep) = 0;
#endif
};


#endif
