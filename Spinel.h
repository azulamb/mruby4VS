#ifndef __SPINEL_VER
#define __SPINEL_VER "1.0.0"

//TODO: memory leak

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "MRubyClass.h"

#ifndef MRB_FUNCALL_ARGC_MAX
#  define MRB_FUNCALL_ARGC_MAX 16
#endif

/*******************************************************************************
*                                    Spinel                                    *
*                                                                              *
* Spinel is wrapper class of mruby.                                            *
*                                                                              *
*******************************************************************************/

class Spinel : public MRuby
{
protected:
  mrb_state *mrb;
  mrb_value argv[ MRB_FUNCALL_ARGC_MAX ];
public:
  Spinel( void );
  virtual ~Spinel( void );

  virtual mrb_state * get( void );
  virtual mrb_value   load( const char *filepath );

  // mruby.h
  //typedef mrb_value(*mrb_func_t)(mrb_state *mrb, mrb_value);
  virtual mrb_value   classNewInstance( int argc, mrb_value *argv, RClass *c );

  // class.c
  virtual mrb_bool    classDefined( const char *name );
  virtual RClass *    classGet( const char *name );
  virtual RClass *    classGetUnder( RClass *outer, const char *name );
  virtual RClass *    defineClassUnder( RClass *outer, const char *name, RClass *super );
  virtual RClass *    defineModuleUnder( mrb_state *mrb, RClass *outer, const char *name );
  virtual void        defineMethod( RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec );
  virtual RClass *    defineModule( const char *name );
  virtual RClass *    defineClass( const char *name, RClass *super );
  virtual mrb_value   singletonClass( mrb_value v );
  virtual void        includeModule( RClass *c, RClass *m );
  virtual void        defineClassMethod( RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec );
  virtual void        defineSingletonMethod( RObject *o, const char *name, mrb_func_t func, mrb_aspec aspec );
  virtual void        defineModuleFunction( RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec );
  virtual void        undefMethod( RClass *c, const char *name );
  virtual void        undefClassMethod( RClass *c, const char *name );
  virtual mrb_value   instanceNew( mrb_value cv );
  virtual mrb_value   objNew( RClass *c, int argc, mrb_value *argv );
  virtual RClass *    classNew( RClass *super );
  virtual RClass *    moduleNew( void );
  virtual mrb_bool    objRespondTo( RClass* c, mrb_sym mid );

  // kernel.c
  virtual mrb_value   objDup( mrb_value obj );

  // variable.c
  virtual void        defineConst( RClass *mod, const char *name, mrb_value v );

  // object.c
  virtual mrb_value   checkToInteger( mrb_value val, const char *method );

  // state.c
  virtual mrb_state * open( void );
  virtual void        close( void );
  virtual mrb_value   topSelf( void );

  // parse.y
  virtual mrb_value   loadFile( FILE *f );
  virtual mrb_value   loadString( const char *s );

  // load.c
  virtual mrb_value   loadIrep( const uint8_t *bin );

  // vm.c
  virtual mrb_value   run( RProc *proc, mrb_value self );
  virtual mrb_value   funcall( mrb_value self, const char *name );
  virtual mrb_value   funcall( mrb_value self, const char *name, int argc, ... );
  virtual mrb_value   funcall( const char *name );
  virtual mrb_value   funcall( const char *name, int argc, ... );

  // value.h
  virtual int         mfloatToStr( char *buf, mrb_float i );
  virtual mrb_float   strToMrbFloat( const char *buf );
  virtual mrb_float   mfloat( mrb_value o );
  virtual mrb_value   mfloatPool( mrb_float f );
  virtual void *      ptr( mrb_value o );
  virtual void *      cptr( mrb_value o );
  virtual int         fixnumP( mrb_value o );
  virtual int         undefP( mrb_value o );
  virtual int         nilP( mrb_value o );
  virtual int         mbool( mrb_value o );

  virtual mrb_int     fixnum( mrb_value value );
  virtual mrb_vtype   type( mrb_value o );
  virtual mrb_value   fixnumValue( mrb_int i );
  virtual mrb_value   symbolValue( mrb_sym i );
  virtual mrb_value   objValue( void *p );
  virtual mrb_value   cptrValue( void *p );
  virtual mrb_value   falseValue( void );
  virtual mrb_value   nilValue( void );
  virtual mrb_value   trueValue( void );
  virtual mrb_value   undefValue( void );
  virtual mrb_value   boolValue( mrb_bool boolean );

  // array.c
#ifdef __ENABLE_MRUBY_ARRAY

  virtual RArray*   aryPtr( mrb_value v );
  virtual mrb_value aryValue( RArray *p );
  virtual void      aryModify( RArray* a );
  virtual void      aryDecref( mrb_shared_array *shared );
  virtual mrb_value aryNewCapa( mrb_int capa );
  virtual mrb_value aryNew( void );
  virtual mrb_value aryNewFromValues( mrb_int size, const mrb_value *vals );
  virtual void      aryConcat( mrb_value self, mrb_value other );
  virtual mrb_value arySplat( mrb_value v );
  virtual void      aryPush( mrb_value ary, mrb_value ele );
  virtual mrb_value aryPop( mrb_value ary );
  virtual mrb_value aryAget( mrb_value self );
  virtual mrb_value aryRef( mrb_value ary, mrb_int n );
  virtual void      arySet( mrb_value ary, mrb_int n, mrb_value val );
  virtual mrb_int   aryLen( mrb_value ary );
  virtual void      aryReplace( mrb_value a, mrb_value b );
  virtual mrb_value checkArrayType( mrb_value self );
  virtual mrb_value aryUnshift( mrb_value self, mrb_value item );
  virtual mrb_value assocNew( mrb_value car, mrb_value cdr );
  virtual mrb_value aryEntry( mrb_value ary, mrb_int offset );
  virtual mrb_value aryShift( mrb_value self );
  virtual mrb_value aryClear( mrb_value self );
  virtual mrb_value aryJoin( mrb_value ary, mrb_value sep );

#endif

#ifdef __ENABLE_MRUBY_CLASS

  virtual RClass * classPtr( mrb_value v );
  virtual RClass * mClass( mrb_value v );
  virtual RClass * defineClassId( mrb_sym name, RClass *super );
  virtual RClass * defineModuleId( mrb_sym name );
  virtual RClass * vmDefineClass( mrb_value outer, mrb_value super, mrb_sym id );
  virtual RClass * vmDefineModule( mrb_value outer, mrb_sym id );
  virtual void     defineMethodVm( RClass *c, mrb_sym name, mrb_value body );
  virtual void     defineMethodRaw( RClass *c, mrb_sym mid, RProc *p );
  virtual void     defineMethodId( RClass *c, mrb_sym mid, mrb_func_t func, mrb_aspec aspec );
  virtual void     aliasMethod( RClass *c, mrb_sym a, mrb_sym b );
  virtual RClass * classOuterModule( RClass *c );
  virtual RProc *  methodSearchVm( RClass **cp, mrb_sym mid );
  virtual RProc *  methodSearch( RClass* c, mrb_sym mid );
  virtual RClass*  classReal( RClass* cl );
  virtual void     gcMarkMt( RClass *c );
  virtual size_t   gcMarkMtSize( RClass *c );
  virtual void     gcFreeMt( RClass *c );

#endif

#ifdef __ENABLE_MRUBY_COMPILE

  // parser.y
  virtual mrbc_context *     cContextNew( void );
  virtual void               cContextFree( mrbc_context *cxt );
  virtual const char *       cFilename( mrbc_context *c, const char *s );
  virtual void               cPartialHook( mrbc_context *c, int( *partial_hook )( mrb_parser_state* ), void *data );
  virtual mrb_parser_state * parserNew( void );
  virtual void               parserFree( mrb_parser_state *p );
  virtual void               parserParse( mrb_parser_state *p, mrbc_context *c );
  virtual void               parserSetFilename( mrb_parser_state *p, const char *f );
  virtual const char *       parserGetFilename( mrb_parser_state *p, uint16_t idx );
  virtual mrb_parser_state*  parseString( const char *s, mrbc_context *c );
  virtual mrb_parser_state*  parseNstring( const char *s, int len, mrbc_context *c );
  virtual mrb_value          loadNstring( const char *s, int len );
  virtual mrb_value          loadStringCxt( const char *s, mrbc_context *cxt );
  virtual mrb_value          loadNstringCxt( const char *s, int len, mrbc_context *cxt );
  virtual mrb_parser_state * parseFile( FILE *f, mrbc_context *c );
  virtual mrb_value          loadFileCxt( FILE *f, mrbc_context *c );

  // codegen.c
  virtual RProc *            generateCode( mrb_parser_state *p );

#endif

#ifdef __ENABLE_MRUBY_DATA
  // etc.c
  virtual RData * dataObjectAlloc( RClass* klass, void *datap, const mrb_data_type *type );
  virtual void    dataCheckType( mrb_value obj, const mrb_data_type *type );
  virtual void *  dataGetPtr( mrb_value obj, const mrb_data_type *type );
  virtual void *  dataCheckGetPtr( mrb_value obj, const mrb_data_type *type );
  virtual void *  dataCheckAndGet( mrb_value obj, const mrb_data_type *dtype );
  virtual void *  getDatatype( mrb_value val, const mrb_data_type *type );
  virtual void *  checkDatatype( mrb_value val, const mrb_data_type *type );
#endif

#ifdef __ENABLE_MRUBY_DEBUG
  virtual mrb_irep_debug_info_file * debugInfoAppendFile( mrb_irep *irep, uint32_t start_pos, uint32_t end_pos );
  virtual mrb_irep_debug_info *      debugInfoAlloc( mrb_irep *irep );
  virtual void                       debugInfoFree( mrb_irep_debug_info *d );
#endif

#ifdef __ENABLE_MRUBY_DUMP

  // dump.c
  virtual int dumpIrepBinary( mrb_irep *irep, int debug_info, FILE* fp );
  virtual int dumpIrepCfunc( mrb_irep *irep, int debug_info, FILE *fp, const char *initname );

  // load.c
  virtual mrb_irep * readIrepFile( FILE*fp );
  virtual mrb_value  loadIrepFile( FILE*fp );
  virtual mrb_value  loadIrepFileCxt( FILE*fp, mrbc_context *c );

#endif

#ifdef __ENABLE_MRUBY_GC
  virtual void objspaceEachObjects( each_object_callback* callback, void *data );
  virtual void freeContext( mrb_context *c );
#endif

#ifdef __ENABLE_MRUBY_HASH

  // hash.c
  virtual RHash*    hashPtr( mrb_value v );
  virtual mrb_value hashValue( RHash *p );
  virtual mrb_value hashNewCapa( int capa );
  virtual mrb_value hashNew( void );
  virtual void      hashSet( mrb_value hash, mrb_value key, mrb_value val );
  virtual mrb_value hashGet( mrb_value hash, mrb_value key );
  virtual mrb_value hashFetch( mrb_value hash, mrb_value key, mrb_value def );
  virtual mrb_value hashDeleteKey( mrb_value hash, mrb_value key );
  virtual mrb_value hashKeys( mrb_value hash );
  virtual mrb_value checkHashType( mrb_value hash );
  virtual mrb_value hashEmptyP( mrb_value self );
  virtual mrb_value hashClear( mrb_value hash );
  virtual kh_ht *   hashTbl( mrb_value hash );
  virtual void      gcMarkHash( RHash *hash );
  virtual size_t    gcMarkHashSize( RHash *hash );
  virtual void      gcFreeHash( RHash *hash );

#endif

#ifdef __ENABLE_MRUBY_IREP

  // load.c
  virtual mrb_value  loadIrepCxt( const uint8_t*bin, mrbc_context *c );

  // state.c
  virtual mrb_irep * addIrep( void );
  virtual void       irepFree( mrb_irep *irep );
  virtual void       irepIncref( mrb_irep *irep );
  virtual void       irepDecref( mrb_irep *irep );

#endif

#ifdef __ENABLE_MRUBY_NUMERIC
  virtual mrb_value floToFixnum( mrb_value val );
  virtual mrb_value floToStr( mrb_value flo, int max_digit );
  virtual mrb_value fixnumToStr( mrb_value x, int base );
  virtual mrb_value fixnumPlus( mrb_value x, mrb_value y );
  virtual mrb_value fixnumMinus( mrb_value x, mrb_value y );
  virtual mrb_value fixnumMul( mrb_value x, mrb_value y );
  virtual mrb_value numDiv( mrb_value x, mrb_value y ); // typo? fixnum_div?
#endif

#ifdef __ENABLE_MRUBY_PROC

  // proc.c

  virtual RProc * procPtr( mrb_value v );
  virtual RProc * procNew( mrb_irep *irep );
  virtual RProc * procNewCfunc( mrb_func_t func );
  virtual RProc * closureNew( mrb_irep *irep );
  virtual RProc * closureNewCfunc( mrb_func_t func, int nlocals );
  virtual void    procCopy( struct RProc *a, struct RProc *b );

#endif

#ifdef __ENABLE_MRUBY_RANGE

  virtual RRange * rangePtr( mrb_value v );
  virtual mrb_value rangeValue( RRange *p );
  virtual mrb_value rangeNew( mrb_value beg, mrb_value end, int excl );
  virtual mrb_int   rangeBegLen( mrb_value range, mrb_int *begp, mrb_int *lenp, mrb_int len );

#endif

#ifdef __ENABLE_MRUBY_STRING

  // string.c

  virtual RString * strPtr( mrb_value s );
  virtual void      gcFreeStr( struct RString *str );
  virtual void      strModify( struct RString *s );
  virtual void      strConcat( mrb_value self, mrb_value other );
  virtual mrb_value strPlus( mrb_value a, mrb_value b );
  virtual mrb_value ptrToStr( void *p );
  virtual mrb_value objAsString( mrb_value obj );
  virtual mrb_value strResize( mrb_value str, mrb_int len );
  virtual mrb_value strSubstr( mrb_value str, mrb_int beg, mrb_int len );
  virtual mrb_value stringType( mrb_value str );
  virtual mrb_value checkString_type( mrb_value str );
  virtual mrb_value strBufNew( mrb_int capa );
  virtual mrb_value strBufCat( mrb_value str, const char *ptr, size_t len );
  virtual char *    stringValueCstr( mrb_value *ptr );
  virtual char *    stringValuePtr( mrb_value ptr );
  virtual int       strOffset( mrb_value str, int pos );
  virtual mrb_value strDup( mrb_value str );
  virtual mrb_value strIntern( mrb_value self );
  virtual mrb_value strCatCstr( mrb_value str, const char *ptr );
  virtual mrb_value strToInum( mrb_value str, int base, int badcheck );
  virtual double    strToDbl( mrb_value str, int badcheck );
  virtual mrb_value strToStr( mrb_value str );
  virtual mrb_int   strHash( mrb_value str );
  virtual mrb_value strBufAppend( mrb_value str, mrb_value str2 );
  virtual mrb_value strInspect( mrb_value str );
  virtual mrb_bool  strEqual( mrb_value str1, mrb_value str2 );
  virtual mrb_value strDump( mrb_value str );
  virtual mrb_value strCat( mrb_value str, const char *ptr, size_t len );
  virtual mrb_value strAppend( mrb_value str, mrb_value str2 );
  virtual int       strCmp( mrb_value str1, mrb_value str2 );
  virtual char *    strToCstr( mrb_value str );
  virtual mrb_value strPool( mrb_value str );
  virtual mrb_value strCat2( mrb_value str, const char *ptr );

#endif

#ifdef __ENABLE_MRUBY_VARIABLE

  // variable.c

  virtual mrb_value vmSpecialGet( mrb_sym i );
  virtual void      vmSpecialSet( mrb_sym i, mrb_value v );
  virtual mrb_value vmIvGet( mrb_sym sym );
  virtual void      vmIvSet( mrb_sym sym, mrb_value v );
  virtual mrb_value vmCvGet( mrb_sym sym );
  virtual void      vmCvSet( mrb_sym sym, mrb_value v );
  virtual mrb_value vmConstGet( mrb_sym sym );
  virtual void      vmConstSet( mrb_value mod, mrb_sym sym, mrb_value v );
  virtual mrb_value constGet( mrb_value mod, mrb_sym sym );
  virtual void      constSet( mrb_value mod, mrb_sym sym, mrb_value v );
  virtual mrb_bool  constDefined( mrb_value mod, mrb_sym sym );
  virtual void      constRemove( mrb_value mod, mrb_sym sym );
  virtual mrb_value objIvGet( RObject *obj, mrb_sym sym );
  virtual void      objIvSet( RObject *obj, mrb_sym sym, mrb_value v );
  virtual mrb_bool  objIvDefined( RObject *obj, mrb_sym sym );
  virtual void      objIvIfnone( RObject *obj, mrb_sym sym, mrb_value v );
  virtual mrb_value ivGet( mrb_value obj, mrb_sym sym );
  virtual void      ivSet( mrb_value obj, mrb_sym sym, mrb_value v );
  virtual mrb_bool  ivDefined( mrb_value obj, mrb_sym sym );
  virtual mrb_value ivRemove( mrb_value obj, mrb_sym sym );
  virtual void      ivCopy( mrb_value dest, mrb_value src );
  virtual int       constDefinedAt( RClass *klass, mrb_sym id );
  virtual mrb_value modConstants( mrb_value mod );
  virtual mrb_value fGlobalVariables( mrb_value self );
  virtual mrb_value gvGet( mrb_sym sym );
  virtual void      gvSet( mrb_sym sym, mrb_value val );
  virtual void      gvRemove( mrb_sym sym );
  virtual mrb_value objInstanceVariables( mrb_value self );
  virtual mrb_value objIvInspect( RObject *obj );
  virtual mrb_sym   classSym( RClass *c, RClass *outer );
  virtual mrb_value modClassVariables( mrb_value mod );
  virtual mrb_value modCvGet( RClass * c, mrb_sym sym );
  virtual mrb_value cvGet( mrb_value mod, mrb_sym sym );
  virtual void      modCvSet( RClass * c, mrb_sym sym, mrb_value v );
  virtual void      cvSet( mrb_value mod, mrb_sym sym, mrb_value v );
  virtual mrb_bool  modCvDefined( struct RClass * c, mrb_sym sym );
  virtual mrb_bool  cvDefined( mrb_value mod, mrb_sym sym );
  virtual void      gcMarkGv( void );
  virtual void      gcFreeGv( void );
  virtual void      gcMarkIv( RObject *obj );
  virtual size_t    gcMarkIvSize( RObject *obj );
  virtual void      gcFreeIv( RObject *obj );

#endif

  /*
  RClass * mrb_define_class_under(mrb_state *mrb, RClass *outer, const char *name, RClass *super);
  RClass * mrb_define_module_under(mrb_state *mrb, RClass *outer, const char *name);
  */
};

#endif
