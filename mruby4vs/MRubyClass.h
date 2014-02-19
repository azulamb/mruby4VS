#ifndef __MRUBY_CLASS
#define __MRUBY_CLASS

#ifndef NO_GETTIMEOFDAY
#  define NO_GETTIMEOFDAY
#endif

#define __ENABLE_MRUBY_ARRAY
#define __ENABLE_MRUBY_CLASS
#define __ENABLE_MRUBY_COMPILE
#define __ENABLE_MRUBY_DATA
#define __ENABLE_MRUBY_DEBUG
#define __ENABLE_MRUBY_DUMP
#define __ENABLE_MRUBY_GC
#define __ENABLE_MRUBY_HASH
#define __ENABLE_MRUBY_IREP
////#define __ENABLE_MRUBY_KHASH
#define __ENABLE_MRUBY_NUMERIC
#define __ENABLE_MRUBY_PROC
#define __ENABLE_MRUBY_RANGE
#define __ENABLE_MRUBY_STRING
#define __ENABLE_MRUBY_VARIABLE

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

#ifdef __ENABLE_MRUBY_NUMERIC
#include "mruby/numeric.h"
#endif

#ifdef __ENABLE_MRUBY_PROC
#include "mruby/proc.h"
#endif

#ifdef __ENABLE_MRUBY_RANGE
#include "mruby/range.h"
#endif

#ifdef __ENABLE_MRUBY_STRING
#include "mruby/string.h"
#endif

#ifdef __ENABLE_MRUBY_VARIABLE
#include "mruby/variable.h"
#endif

/*******************************************************************************
*                                  MRuby class                                 *
*                                                                              *
* MRuby class is interface of mruby.                                           *
*                                                                              *
*******************************************************************************/

class MRuby
{
public:
  MRuby( void ){}
  virtual ~MRuby( void ){}

  // Original

  virtual mrb_state * get( void ) = 0;
  virtual mrb_value   load( const char *filepath ) = 0;

  // Wrapper

  virtual mrb_bool    classDefined( const char *name ) = 0;
  virtual RClass *    classGet( const char *name ) = 0;
  virtual RClass *    classGetUnder( RClass *outer, const char *name ) = 0;
  virtual RClass *    defineClassUnder( RClass *outer, const char *name, RClass *super ) = 0;
  virtual RClass *    defineModuleUnder( mrb_state *mrb, RClass *outer, const char *name ) = 0;
  virtual mrb_value   classNewInstance( int argc, mrb_value *argv, RClass *c ) = 0;
  virtual void        defineMethod( RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec ) = 0;
  virtual RClass *    defineModule( const char *name ) = 0;
  virtual RClass *    defineClass( const char *name, RClass *super ) = 0;
  virtual mrb_value   singletonClass( mrb_value v ) = 0;
  virtual void        includeModule( RClass *c, RClass *m ) = 0;
  virtual void        defineClassMethod( RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec ) = 0;
  virtual void        defineSingletonMethod( RObject *o, const char *name, mrb_func_t func, mrb_aspec aspec ) = 0;
  virtual void        defineModuleFunction( RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec ) = 0;
  virtual void        undefMethod( RClass *c, const char *name ) = 0;
  virtual void        undefClassMethod( RClass *c, const char *name ) = 0;
  virtual mrb_value   instanceNew( mrb_value cv ) = 0;
  virtual mrb_value   objNew( RClass *c, int argc, mrb_value *argv ) = 0;
  virtual RClass *    classNew( RClass *super ) = 0;
  virtual RClass *    moduleNew( void ) = 0;
  virtual mrb_bool    objRespondTo( RClass* c, mrb_sym mid ) = 0;
  virtual mrb_value   objDup( mrb_value obj ) = 0;
  virtual void        defineConst( RClass *mod, const char *name, mrb_value v ) = 0;
  virtual mrb_value   checkToInteger( mrb_value val, const char *method ) = 0;
  virtual mrb_state * open( void ) = 0;
  virtual mrb_value   topSelf( void ) = 0;
  // ! Use loadFromFile if you use DLL.
  virtual mrb_value   loadFile( FILE *f ) = 0;
  virtual mrb_value   loadString( const char *s ) = 0;
  // ! Load bytecode.
  virtual mrb_value   loadIrep( const uint8_t *bin ) = 0;
  // loadFromRiteFile
  virtual mrb_value   run( RProc *proc, mrb_value self ) = 0;
  virtual mrb_value   funcall( mrb_value self, const char *name ) = 0;
  virtual mrb_value   funcall( mrb_value self, const char *name, int argc, ... ) = 0;
  virtual mrb_value   funcall( const char *name ) = 0;
  virtual mrb_value   funcall( const char *name, int argc, ... ) = 0;
  virtual mrb_int     fixnum( mrb_value value ) = 0;

  // value.h

  virtual int         mfloatToStr( char *buf, mrb_float i ) = 0; // Correct?
  virtual mrb_float   strToMrbFloat( const char *buf ) = 0; // Correct?
  virtual mrb_float   mfloat( mrb_value o ) = 0; // Correct?
  virtual mrb_value   mfloatPool( mrb_float f ) = 0; // Correct?
  virtual void *      ptr( mrb_value o ) = 0; // Correct?
  virtual void *      cptr( mrb_value o ) = 0; // Correct?
  virtual int         fixnumP( mrb_value o ) = 0; // Correct?
  virtual int         undefP( mrb_value o ) = 0; // Correct?
  virtual int         nilP( mrb_value o ) = 0; // Correct?
  virtual int         mbool( mrb_value o ) = 0; // Correct?
  virtual mrb_vtype   type( mrb_value o ) = 0;
  virtual mrb_value   fixnumValue( mrb_int i ) = 0;
  virtual mrb_value   symbolValue( mrb_sym i ) = 0;
  virtual mrb_value   objValue( void *p ) = 0;
  virtual mrb_value   cptrValue( void *p ) = 0;
  virtual mrb_value   falseValue( void ) = 0;
  virtual mrb_value   nilValue( void ) = 0;
  virtual mrb_value   trueValue( void ) = 0;
  virtual mrb_value   undefValue( void ) = 0;
  virtual mrb_value   boolValue( mrb_bool boolean ) = 0;

#ifdef __ENABLE_MRUBY_ARRAY
  virtual RArray*   aryPtr( mrb_value v ) = 0; // Correct?
  virtual mrb_value aryValue( RArray *p ) = 0; // Correct?
  virtual void      aryModify( RArray *a ) = 0;
  virtual void      aryDecref( mrb_shared_array *shared ) = 0;
  virtual mrb_value aryNewCapa( mrb_int capa ) = 0;
  virtual mrb_value aryNew( void ) = 0;
  virtual mrb_value aryNewFromValues( mrb_int size, const mrb_value *vals ) = 0;
  virtual void      aryConcat( mrb_value self, mrb_value other ) = 0;
  virtual mrb_value arySplat( mrb_value v ) = 0;
  virtual void      aryPush( mrb_value ary, mrb_value ele ) = 0;
  virtual mrb_value aryPop( mrb_value ary ) = 0;
  virtual mrb_value aryAget( mrb_value self ) = 0;
  virtual mrb_value aryRef( mrb_value ary, mrb_int n ) = 0;
  virtual void      arySet( mrb_value ary, mrb_int n, mrb_value val ) = 0;
  virtual mrb_int   aryLen( mrb_value ary ) = 0;
  virtual void      aryReplace( mrb_value a, mrb_value b ) = 0;
  virtual mrb_value checkArrayType( mrb_value self ) = 0;
  virtual mrb_value aryUnshift( mrb_value self, mrb_value item ) = 0;
  virtual mrb_value assocNew( mrb_value car, mrb_value cdr ) = 0;
  virtual mrb_value aryEntry( mrb_value ary, mrb_int offset ) = 0;
  virtual mrb_value aryShift( mrb_value self ) = 0;
  virtual mrb_value aryClear( mrb_value self ) = 0;
  virtual mrb_value aryJoin( mrb_value ary, mrb_value sep ) = 0;
#endif

#ifdef __ENABLE_MRUBY_CLASS
  virtual RClass * classPtr( mrb_value v ) = 0; // Correct?
  virtual RClass * mClass( mrb_value v ) = 0; // class
  virtual RClass * defineClassId( mrb_sym name, RClass *super ) = 0;
  virtual RClass * defineModuleId( mrb_sym name ) = 0;
  virtual RClass * vmDefineClass( mrb_value outer, mrb_value super, mrb_sym id ) = 0;
  virtual RClass * vmDefineModule( mrb_value outer, mrb_sym id ) = 0;
  virtual void     defineMethodVm( RClass *c, mrb_sym name, mrb_value body ) = 0;
  virtual void     defineMethodRaw( RClass *c, mrb_sym mid, RProc *p ) = 0;
  virtual void     defineMethodId( RClass *c, mrb_sym mid, mrb_func_t func, mrb_aspec aspec ) = 0;
  virtual void     aliasMethod( RClass *c, mrb_sym a, mrb_sym b ) = 0;
  virtual RClass * classOuterModule( RClass *c ) = 0;
  virtual RProc *  methodSearchVm( RClass **cp, mrb_sym mid ) = 0;
  virtual RProc *  methodSearch( RClass* c, mrb_sym mid ) = 0;
  virtual RClass*  classReal( RClass* cl ) = 0;
  virtual void     gcMarkMt( RClass *c ) = 0;
  virtual size_t   gcMarkMtSize( RClass *c ) = 0;
  virtual void     gcFreeMt( RClass *c ) = 0;
#endif

#ifdef __ENABLE_MRUBY_COMPILE
  virtual mrbc_context *     cContextNew( void ) = 0;
  virtual void               cContextFree( mrbc_context *cxt ) = 0;
  virtual const char *       cFilename( mrbc_context *c, const char *s ) = 0;
  virtual void               cPartialHook( mrbc_context *c, int( *partial_hook )( mrb_parser_state* ), void *data ) = 0;
  virtual mrb_parser_state * parserNew( void ) = 0;
  virtual void               parserFree( mrb_parser_state *p ) = 0;
  virtual void               parserParse( mrb_parser_state *p, mrbc_context *c ) = 0;
  virtual void               parserSetFilename( mrb_parser_state *p, const char *f ) = 0;
  virtual const char *       parserGetFilename( mrb_parser_state *p, uint16_t idx ) = 0;
  virtual mrb_parser_state*  parseString( const char *s, mrbc_context *c ) = 0;
  virtual mrb_parser_state*  parseNstring( const char *s, int len, mrbc_context *c ) = 0;
  virtual mrb_value          loadNstring( const char *s, int len ) = 0;
  virtual mrb_value          loadStringCxt( const char *s, mrbc_context *cxt ) = 0;
  virtual mrb_value          loadNstringCxt( const char *s, int len, mrbc_context *cxt ) = 0;
  virtual mrb_parser_state * parseFile( FILE *f, mrbc_context *c ) = 0;
  virtual mrb_value          loadFileCxt( FILE *f, mrbc_context *c ) = 0;
  virtual RProc *            generateCode( mrb_parser_state *p ) = 0;

#endif

#ifdef __ENABLE_MRUBY_DATA
  virtual RData * dataObjectAlloc( RClass* klass, void *datap, const mrb_data_type *type ) = 0;
  virtual void    dataCheckType( mrb_value obj, const mrb_data_type *type ) = 0;
  virtual void *  dataGetPtr( mrb_value obj, const mrb_data_type *type ) = 0;
  virtual void *  dataCheckGetPtr( mrb_value obj, const mrb_data_type *type ) = 0;
  virtual void *  dataCheckAndGet( mrb_value obj, const mrb_data_type *dtype ) = 0; // Correct?
  virtual void *  getDatatype( mrb_value val, const mrb_data_type *type ) = 0; // Correct?
  virtual void *  checkDatatype( mrb_value val, const mrb_data_type *type ) = 0; // Correct?
#endif

#ifdef __ENABLE_MRUBY_DEBUG
  virtual mrb_irep_debug_info_file * debugInfoAppendFile( mrb_irep *irep, uint32_t start_pos, uint32_t end_pos ) = 0;
  virtual mrb_irep_debug_info *      debugInfoAlloc( mrb_irep *irep ) = 0;
  virtual void                       debugInfoFree( mrb_irep_debug_info *d ) = 0;
#endif

#ifdef __ENABLE_MRUBY_DUMP
  virtual int        dumpIrepBinary( mrb_irep *irep, int debug_info, FILE* fp ) = 0;
  virtual int        dumpIrepCfunc( mrb_irep *irep, int debug_info, FILE *fp, const char *initname ) = 0;
  virtual mrb_irep * readIrepFile( FILE*fp ) = 0;
  virtual mrb_value  loadIrepFile( FILE*fp ) = 0;
  virtual mrb_value  loadIrepFileCxt( FILE*fp, mrbc_context *c ) = 0;
#endif

#ifdef __ENABLE_MRUBY_GC
  // symbol error
  virtual void objspaceEachObjects( each_object_callback* callback, void *data ) = 0;
  virtual void freeContext( mrb_context *c ) = 0;
#endif

#ifdef __ENABLE_MRUBY_HASH
  virtual RHash*    hashPtr( mrb_value v ) = 0; // Correct?
  virtual mrb_value hashValue( RHash *p ) = 0; // Correct?
  virtual mrb_value hashNewCapa( int capa ) = 0;
  virtual mrb_value hashNew( void ) = 0;
  virtual void      hashSet( mrb_value hash, mrb_value key, mrb_value val ) = 0;
  virtual mrb_value hashGet( mrb_value hash, mrb_value key ) = 0;
  virtual mrb_value hashFetch( mrb_value hash, mrb_value key, mrb_value def ) = 0;
  virtual mrb_value hashDeleteKey( mrb_value hash, mrb_value key ) = 0;
  virtual mrb_value hashKeys( mrb_value hash ) = 0;
  virtual mrb_value checkHashType( mrb_value hash ) = 0;
  virtual mrb_value hashEmptyP( mrb_value self ) = 0;
  virtual mrb_value hashClear( mrb_value hash ) = 0;
  virtual kh_ht *   hashTbl( mrb_value hash ) = 0;
  virtual void      gcMarkHash( RHash *hash ) = 0;
  virtual size_t    gcMarkHashSize( RHash *hash ) = 0;
  virtual void      gcFreeHash( RHash *hash ) = 0;
#endif

#ifdef __ENABLE_MRUBY_IREP
  virtual mrb_value  loadIrepCxt( const uint8_t*bin, mrbc_context *c ) = 0;
  virtual mrb_irep * addIrep( void ) = 0;
  virtual void       irepFree( mrb_irep *irep ) = 0;
  virtual void       irepIncref( mrb_irep *irep ) = 0;
  virtual void       irepDecref( mrb_irep *irep ) = 0;
#endif

#ifdef __ENABLE_MRUBY_NUMERIC
  virtual mrb_value floToFixnum( mrb_value val ) = 0;
  virtual mrb_value floToStr( mrb_value flo, int max_digit ) = 0;
  virtual mrb_value fixnumToStr( mrb_value x, int base ) = 0;
  virtual mrb_value fixnumPlus( mrb_value x, mrb_value y ) = 0;
  virtual mrb_value fixnumMinus( mrb_value x, mrb_value y ) = 0;
  virtual mrb_value fixnumMul( mrb_value x, mrb_value y ) = 0;
  virtual mrb_value numDiv( mrb_value x, mrb_value y ) = 0;
#endif

#ifdef __ENABLE_MRUBY_PROC
  virtual RProc * procPtr( mrb_value v ) = 0; // Correct?
  virtual RProc * procNew( mrb_irep *irep ) = 0;
  virtual RProc * procNewCfunc( mrb_func_t func ) = 0;
  virtual RProc * closureNew( mrb_irep *irep ) = 0;
  virtual RProc * closureNewCfunc( mrb_func_t func, int nlocals ) = 0;
  virtual void    procCopy( struct RProc *a, struct RProc *b ) = 0;
#endif

#ifdef __ENABLE_MRUBY_RANGE
  virtual RRange *  rangePtr( mrb_value v ) = 0; // Correct?
  virtual mrb_value rangeValue( RRange *p ) = 0; // Correct?
  virtual mrb_value rangeNew( mrb_value beg, mrb_value end, int excl ) = 0;
  virtual mrb_int   rangeBegLen( mrb_value range, mrb_int *begp, mrb_int *lenp, mrb_int len ) = 0;
#endif

#ifdef __ENABLE_MRUBY_STRING
  virtual RString * strPtr( mrb_value s ) = 0; // Correct?
  virtual void      gcFreeStr( struct RString *str ) = 0;
  virtual void      strModify( struct RString *s ) = 0;
  virtual void      strConcat( mrb_value self, mrb_value other ) = 0;
  virtual mrb_value strPlus( mrb_value a, mrb_value b ) = 0;
  virtual mrb_value ptrToStr( void *p ) = 0;
  virtual mrb_value objAsString( mrb_value obj ) = 0;
  virtual mrb_value strResize( mrb_value str, mrb_int len ) = 0;
  virtual mrb_value strSubstr( mrb_value str, mrb_int beg, mrb_int len ) = 0;
  virtual mrb_value stringType( mrb_value str ) = 0;
  virtual mrb_value checkString_type( mrb_value str ) = 0;
  virtual mrb_value strBufNew( mrb_int capa ) = 0;
  virtual mrb_value strBufCat( mrb_value str, const char *ptr, size_t len ) = 0;
  virtual char *    stringValueCstr( mrb_value *ptr ) = 0;
  virtual char *    stringValuePtr( mrb_value ptr ) = 0;
  virtual int       strOffset( mrb_value str, int pos ) = 0;
  virtual mrb_value strDup( mrb_value str ) = 0;
  virtual mrb_value strIntern( mrb_value self ) = 0;
  virtual mrb_value strCatCstr( mrb_value str, const char *ptr ) = 0;
  virtual mrb_value strToInum( mrb_value str, int base, int badcheck ) = 0;
  virtual double    strToDbl( mrb_value str, int badcheck ) = 0;
  virtual mrb_value strToStr( mrb_value str ) = 0;
  virtual mrb_int   strHash( mrb_value str ) = 0;
  virtual mrb_value strBufAppend( mrb_value str, mrb_value str2 ) = 0;
  virtual mrb_value strInspect( mrb_value str ) = 0;
  virtual mrb_bool  strEqual( mrb_value str1, mrb_value str2 ) = 0;
  virtual mrb_value strDump( mrb_value str ) = 0;
  virtual mrb_value strCat( mrb_value str, const char *ptr, size_t len ) = 0;
  virtual mrb_value strAppend( mrb_value str, mrb_value str2 ) = 0;
  virtual int       strCmp( mrb_value str1, mrb_value str2 ) = 0;
  virtual char *    strToCstr( mrb_value str ) = 0;
  virtual mrb_value strPool( mrb_value str ) = 0;
  virtual mrb_value strCat2( mrb_value str, const char *ptr ) = 0;
#endif

#ifdef __ENABLE_MRUBY_VARIABLE
  // variable.c
  virtual mrb_value vmSpecialGet( mrb_sym i ) = 0;
  virtual void      vmSpecialSet( mrb_sym i, mrb_value v ) = 0;
  virtual mrb_value vmIvGet( mrb_sym sym ) = 0;
  virtual void      vmIvSet( mrb_sym sym, mrb_value v ) = 0;
  virtual mrb_value vmCvGet( mrb_sym sym ) = 0;
  virtual void      vmCvSet( mrb_sym sym, mrb_value v ) = 0;
  virtual mrb_value vmConstGet( mrb_sym sym ) = 0;
  virtual void      vmConstSet( mrb_value mod, mrb_sym sym, mrb_value v ) = 0;
  virtual mrb_value constGet( mrb_value mod, mrb_sym sym ) = 0;
  virtual void      constSet( mrb_value mod, mrb_sym sym, mrb_value v ) = 0;
  virtual mrb_bool  constDefined( mrb_value mod, mrb_sym sym ) = 0;
  virtual void      constRemove( mrb_value mod, mrb_sym sym ) = 0;
  virtual mrb_value objIvGet( RObject *obj, mrb_sym sym ) = 0;
  virtual void      objIvSet( RObject *obj, mrb_sym sym, mrb_value v ) = 0;
  virtual mrb_bool  objIvDefined( RObject *obj, mrb_sym sym ) = 0;
  virtual void      objIvIfnone( RObject *obj, mrb_sym sym, mrb_value v ) = 0;
  virtual mrb_value ivGet( mrb_value obj, mrb_sym sym ) = 0;
  virtual void      ivSet( mrb_value obj, mrb_sym sym, mrb_value v ) = 0;
  virtual mrb_bool  ivDefined( mrb_value obj, mrb_sym sym ) = 0;
  virtual mrb_value ivRemove( mrb_value obj, mrb_sym sym ) = 0;
  virtual void      ivCopy( mrb_value dest, mrb_value src ) = 0;
  virtual int       constDefinedAt( RClass *klass, mrb_sym id ) = 0;
  virtual mrb_value modConstants( mrb_value mod ) = 0;
  virtual mrb_value fGlobalVariables( mrb_value self ) = 0;
  virtual mrb_value gvGet( mrb_sym sym ) = 0;
  virtual void      gvSet( mrb_sym sym, mrb_value val ) = 0;
  virtual void      gvRemove( mrb_sym sym ) = 0;
  virtual mrb_value objInstanceVariables( mrb_value self ) = 0;
  virtual mrb_value objIvInspect( RObject *obj ) = 0;
  virtual mrb_sym   classSym( RClass *c, RClass *outer ) = 0;
  virtual mrb_value modClassVariables( mrb_value mod ) = 0;
  virtual mrb_value modCvGet( RClass * c, mrb_sym sym ) = 0;
  virtual mrb_value cvGet( mrb_value mod, mrb_sym sym ) = 0;
  virtual void      modCvSet( RClass * c, mrb_sym sym, mrb_value v ) = 0;
  virtual void      cvSet( mrb_value mod, mrb_sym sym, mrb_value v ) = 0;
  virtual mrb_bool  modCvDefined( struct RClass * c, mrb_sym sym ) = 0;
  virtual mrb_bool  cvDefined( mrb_value mod, mrb_sym sym ) = 0;
  virtual void      gcMarkGv( void ) = 0;
  virtual void      gcFreeGv( void ) = 0;
  virtual void      gcMarkIv( RObject *obj ) = 0;
  virtual size_t    gcMarkIvSize( RObject *obj ) = 0;
  virtual void      gcFreeIv( RObject *obj ) = 0;
#endif
};


#endif
