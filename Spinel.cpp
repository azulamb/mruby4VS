#include <stdarg.h>

#include "Spinel.h"
#include "mruby/compile.h"
#include "mruby/irep.h"
// Spinel

#define SPINEL_FUNCALL(conv, self, name, argc) \
  va_list ap;\
  int i;\
  if ( argc )\
  {\
    va_start( ap, argc ); \
    for ( i = 0; i < argc; i++ )\
    {\
      argv[ i ] = va_arg( ap, mrb_value ); \
    }\
    va_end( ap ); \
  }\
  return conv( mrb_funcall( mrb, self, name, argc,\
    argv[ 0 ], argv[ 1 ], argv[ 2 ], argv[ 3 ], argv[ 4 ], argv[ 5 ], argv[ 6 ], argv[ 7 ],\
    argv[ 8 ], argv[ 9 ], argv[ 10 ], argv[ 11 ], argv[ 12 ], argv[ 13 ], argv[ 14 ], argv[ 15 ] ) );


Spinel::Spinel( void )
{
  mrb = open();
}

Spinel::~Spinel( void )
{
  close();
}

mrb_state * Spinel::get( void )
{
  return mrb;
}

int Spinel::getArgCount( void )
{
  return mrb->c->ci->argc;
}

// in class.c
static mrb_value check_type( mrb_state *mrb, mrb_value val, enum mrb_vtype t, const char *c, const char *m )
{
  mrb_value tmp;

  tmp = mrb_check_convert_type( mrb, val, t, c, m );
  if ( mrb_nil_p( tmp ) ) {
    mrb_raisef( mrb, E_TYPE_ERROR, "expected %S", mrb_str_new_cstr( mrb, c ) );
  }
  return tmp;
}
static mrb_value to_str( mrb_state *mrb, mrb_value val ){ return check_type( mrb, val, MRB_TT_STRING, "String", "to_str" ); }
static mrb_value to_ary( mrb_state *mrb, mrb_value val ){ return check_type( mrb, val, MRB_TT_ARRAY, "Array", "to_ary" ); }
static mrb_value to_hash( mrb_state *mrb, mrb_value val ){ return check_type( mrb, val, MRB_TT_HASH, "Hash", "to_hash" ); }

// copy by mrb_get_args in class.c
int Spinel::getArgs( const char *format, ... )
{
  char c;
  int i = 0;
  mrb_value *sp = mrb->c->stack + 1;
  va_list ap;
  int argc = mrb->c->ci->argc;
  int opt = 0;

  va_start( ap, format );
  if ( argc < 0 ) {
    struct RArray *a = mrb_ary_ptr( mrb->c->stack[ 1 ] );

    argc = a->len;
    sp = a->ptr;
  }
  while ( ( c = *format++ ) ) {
    switch ( c ) {
    case '|': case '*': case '&':
      break;
    default:
      if ( argc <= i && !opt ) {
        mrb_raise( mrb, E_ARGUMENT_ERROR, "wrong number of arguments" );
      }
      break;
    }

    switch ( c ) {
    case 'o':
    {
      mrb_value *p;

      p = va_arg( ap, mrb_value* );
      if ( i < argc ) {
        *p = *sp++;
        i++;
      }
    }
      break;
    case 'C':
    {
      mrb_value *p;

      p = va_arg( ap, mrb_value* );
      if ( i < argc ) {
        mrb_value ss;

        ss = *sp++;
        switch ( mrb_type( ss ) ) {
        case MRB_TT_CLASS:
        case MRB_TT_MODULE:
        case MRB_TT_SCLASS:
          break;
        default:
          mrb_raisef( mrb, E_TYPE_ERROR, "%S is not class/module", ss );
          break;
        }
        *p = ss;
        i++;
      }
    }
      break;
    case 'S':
    {
      mrb_value *p;

      p = va_arg( ap, mrb_value* );
      if ( i < argc ) {
        *p = to_str( mrb, *sp++ );
        i++;
      }
    }
      break;
    case 'A':
    {
      mrb_value *p;

      p = va_arg( ap, mrb_value* );
      if ( i < argc ) {
        *p = to_ary( mrb, *sp++ );
        i++;
      }
    }
      break;
    case 'H':
    {
      mrb_value *p;

      p = va_arg( ap, mrb_value* );
      if ( i < argc ) {
        *p = to_hash( mrb, *sp++ );
        i++;
      }
    }
      break;
    case 's':
    {
      mrb_value ss;
      struct RString *s;
      char **ps = 0;
      int *pl = 0;

      ps = va_arg( ap, char** );
      pl = va_arg( ap, int* );
      if ( i < argc ) {
        ss = to_str( mrb, *sp++ );
        s = mrb_str_ptr( ss );
        *ps = s->ptr;
        *pl = s->len;
        i++;
      }
    }
      break;
    case 'z':
    {
      mrb_value ss;
      struct RString *s;
      char **ps;
      mrb_int len;

      ps = va_arg( ap, char** );
      if ( i < argc ) {
        ss = to_str( mrb, *sp++ );
        s = mrb_str_ptr( ss );
        len = (mrb_int)strlen( s->ptr );
        if ( len < s->len ) {
          mrb_raise( mrb, E_ARGUMENT_ERROR, "string contains null byte" );
        }
        else if ( len > s->len ) {
          mrb_str_modify( mrb, s );
        }
        *ps = s->ptr;
        i++;
      }
    }
      break;
    case 'a':
    {
      mrb_value aa;
      struct RArray *a;
      mrb_value **pb;
      mrb_int *pl;

      pb = va_arg( ap, mrb_value** );
      pl = va_arg( ap, mrb_int* );
      if ( i < argc ) {
        aa = to_ary( mrb, *sp++ );
        a = mrb_ary_ptr( aa );
        *pb = a->ptr;
        *pl = a->len;
        i++;
      }
    }
      break;
    case 'f':
    {
      mrb_float *p;

      p = va_arg( ap, mrb_float* );
      if ( i < argc ) {
        switch ( mrb_type( *sp ) ) {
        case MRB_TT_FLOAT:
          *p = mrb_float( *sp );
          break;
        case MRB_TT_FIXNUM:
          *p = (mrb_float)mrb_fixnum( *sp );
          break;
        case MRB_TT_STRING:
          mrb_raise( mrb, E_TYPE_ERROR, "String can't be coerced into Float" );
          break;
        default:
        {
          mrb_value tmp;

          tmp = mrb_convert_type( mrb, *sp, MRB_TT_FLOAT, "Float", "to_f" );
          *p = mrb_float( tmp );
        }
          break;
        }
        sp++;
        i++;
      }
    }
      break;
    case 'i':
    {
      mrb_int *p;

      p = va_arg( ap, mrb_int* );
      if ( i < argc ) {
        switch ( mrb_type( *sp ) ) {
        case MRB_TT_FIXNUM:
          *p = mrb_fixnum( *sp );
          break;
        case MRB_TT_FLOAT:
        {
          mrb_float f = mrb_float( *sp );

          if ( !FIXABLE( f ) ) {
            mrb_raise( mrb, E_RANGE_ERROR, "float too big for int" );
          }
          *p = (mrb_int)f;
        }
          break;
        default:
          *p = mrb_fixnum( mrb_Integer( mrb, *sp ) );
          break;
        }
        sp++;
        i++;
      }
    }
      break;
    case 'b':
    {
      mrb_bool *boolp = va_arg( ap, mrb_bool* );

      if ( i < argc ) {
        mrb_value b = *sp++;
        *boolp = mrb_test( b );
        i++;
      }
    }
      break;
    case 'n':
    {
      mrb_sym *symp;

      symp = va_arg( ap, mrb_sym* );
      if ( i < argc ) {
        mrb_value ss;

        ss = *sp++;
        if ( mrb_type( ss ) == MRB_TT_SYMBOL ) {
          *symp = mrb_symbol( ss );
        }
        else if ( mrb_string_p( ss ) ) {
          *symp = mrb_intern_str( mrb, to_str( mrb, ss ) );
        }
        else {
          mrb_value obj = mrb_funcall( mrb, ss, "inspect", 0 );
          mrb_raisef( mrb, E_TYPE_ERROR, "%S is not a symbol", obj );
        }
        i++;
      }
    }
      break;

    case '&':
    {
      mrb_value *p, *bp;

      p = va_arg( ap, mrb_value* );
      if ( mrb->c->ci->argc < 0 ) {
        bp = mrb->c->stack + 2;
      }
      else {
        bp = mrb->c->stack + mrb->c->ci->argc + 1;
      }
      *p = *bp;
    }
      break;
    case '|':
      opt = 1;
      break;

    case '*':
    {
      mrb_value **var;
      int *pl;

      var = va_arg( ap, mrb_value** );
      pl = va_arg( ap, int* );
      if ( argc > i ) {
        *pl = argc - i;
        if ( *pl > 0 ) {
          *var = sp;
        }
        i = argc;
        sp += *pl;
      }
      else {
        *pl = 0;
        *var = NULL;
      }
    }
      break;
    default:
      mrb_raisef( mrb, E_ARGUMENT_ERROR, "invalid argument specifier %S", mrb_str_new( mrb, &c, 1 ) );
      break;
    }
  }
  if ( !c && argc > i ) {
    mrb_raise( mrb, E_ARGUMENT_ERROR, "wrong number of arguments" );
  }
  va_end( ap );
  return i;
}

RClass * Spinel::getObjectClass( void )
{
  return mrb->object_class;
}

RClass * Spinel::defineClassUnder( RClass *outer, const char *name )
{
  return mrb_define_class_under( mrb, outer, name, mrb->object_class );
}

mrb_value Spinel::load( const char *filepath )
{
  mrb_value ret = {};
  FILE *f;
  if ( fopen_s( &f, filepath, "r" ) != 0 )
  {
    return ret;
  }
  ret = loadFile( f );
  fclose( f );
  return ret;
}

mrb_int Spinel::funcallInt( mrb_value self, const char *name )
{
  return mrb_fixnum( mrb_funcall( mrb, self, name, 0 ) );
}

mrb_int Spinel::funcallInt( mrb_value self, const char *name, int argc, ... )
{
  SPINEL_FUNCALL( mrb_fixnum, self, name, argc );
}

mrb_int Spinel::funcallInt( const char *name )
{
  return mrb_fixnum( mrb_funcall( mrb, topSelf(), name, 0 ) );
}

mrb_int Spinel::funcallInt( const char *name, int argc, ... )
{
  SPINEL_FUNCALL( mrb_fixnum, topSelf(), name, argc );
}

mrb_float Spinel::funcallFloat( mrb_value self, const char *name )
{
  return mrb_float( mrb_funcall( mrb, self, name, 0 ) );
}

mrb_float Spinel::funcallFloat( mrb_value self, const char *name, int argc, ... )
{
  SPINEL_FUNCALL( mrb_float, self, name, argc );
}

mrb_float Spinel::funcallFloat( const char *name )
{
  return mrb_float( mrb_funcall( mrb, topSelf(), name, 0 ) );
}

mrb_float Spinel::funcallFloat( const char *name, int argc, ... )
{
  SPINEL_FUNCALL( mrb_float, topSelf( ), name, argc );
}

// mruby.h

mrb_value Spinel::classNewInstance( int argc, mrb_value *argv, RClass *c )
{
  return mrb_class_new_instance( mrb, argc, argv, c );
}

// class.c

mrb_bool Spinel::classDefined( const char *name )
{
  return mrb_class_defined( mrb, name );
}

RClass * Spinel::classGet( const char *name )
{
  return mrb_class_get( mrb, name );
}

RClass * Spinel::classGetUnder( RClass *outer, const char *name )
{
  return mrb_class_get_under( mrb, outer, name );
}

RClass * Spinel::defineClassUnder( RClass *outer, const char *name, RClass *super )
{
  return mrb_define_class_under( mrb, outer, name, super );
}

RClass * Spinel::defineModuleUnder( mrb_state *mrb, RClass *outer, const char *name )
{
  return mrb_define_module_under( mrb, outer, name );
}

void Spinel::defineMethod( RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec )
{
  return mrb_define_method( mrb, c, name, func, aspec );
}

RClass * Spinel::defineModule( const char *name )
{
  return mrb_define_module( mrb, name );
}

RClass * Spinel::defineClass( const char *name, RClass *super )
{
  return mrb_define_class( mrb, name, super );
}

mrb_value Spinel::singletonClass( mrb_value v )
{
  return mrb_singleton_class( mrb, v );
}

void Spinel::includeModule( RClass *c, RClass *m )
{
  return mrb_include_module( mrb, c, m );
}

void Spinel::defineClassMethod( RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec )
{
  return mrb_define_class_method( mrb, c, name, func, aspec );
}

void Spinel::defineSingletonMethod( RObject *o, const char *name, mrb_func_t func, mrb_aspec aspec )
{
  return mrb_define_singleton_method( mrb, o, name, func, aspec );
}

void Spinel::defineModuleFunction( RClass *c, const char *name, mrb_func_t func, mrb_aspec aspec )
{
  return mrb_define_module_function( mrb, c, name, func, aspec );
}

void Spinel::undefMethod( RClass *c, const char *name )
{
  return mrb_undef_method( mrb, c, name );
}

void Spinel::undefClassMethod( RClass *c, const char *name )
{
  return mrb_undef_class_method( mrb, c, name );
}

mrb_value Spinel::instanceNew( mrb_value cv )
{
  return mrb_instance_new( mrb, cv );
}

mrb_value Spinel::objNew( RClass *c, int argc, mrb_value *argv )
{
  return mrb_obj_new( mrb, c, argc, argv );
}

RClass * Spinel::classNew( RClass *super )
{
  return mrb_class_new( mrb, super );
}

RClass * Spinel::moduleNew( void )
{
  return mrb_module_new( mrb );
}

mrb_bool Spinel::objRespondTo( RClass* c, mrb_sym mid )
{
  return mrb_obj_respond_to( mrb, c, mid );
}

// kernel.c
mrb_value Spinel::objDup( mrb_value obj )
{
  return mrb_obj_dup( mrb, obj );
}

// variable.c
void Spinel::defineConst( RClass *mod, const char *name, mrb_value v )
{
  return mrb_define_const( mrb, mod, name, v );
}

// object.c

mrb_value Spinel::checkToInteger( mrb_value val, const char *method )
{
  return mrb_check_to_integer( mrb, val, method );
}

// state.c

mrb_state* Spinel::open( void )
{
  return mrb_open();
}

void Spinel::close( void )
{
  mrb_close( mrb );
}

mrb_value Spinel::topSelf( void )
{
  return mrb_top_self( mrb );
}

// parse.y

mrb_value Spinel::loadFile( FILE *f )
{
  return mrb_load_file( mrb, f );
}

mrb_value Spinel::loadString( const char *s )
{
  return mrb_load_string( mrb, s );
}

// load.c

mrb_value Spinel::loadIrep( const uint8_t *bin )
{
  return mrb_load_irep( mrb, bin );
}

// vm.c

mrb_value Spinel::run( RProc *proc, mrb_value self )
{
  return mrb_run( mrb, proc, self );
}

mrb_value Spinel::funcall( mrb_value self, const char *name )
{
  return mrb_funcall( mrb, self, name, 0 );
}

mrb_value Spinel::funcall( mrb_value self, const char *name, int argc, ... )
{
  SPINEL_FUNCALL( , self, name, argc );
}

mrb_value Spinel::funcall( const char *name )
{
  return mrb_funcall( mrb, topSelf(), name, 0 );
}

mrb_value Spinel::funcall( const char *name, int argc, ... )
{
  SPINEL_FUNCALL( , topSelf( ), name, argc );
}

// value.h

int Spinel::mfloatToStr( char *buf, mrb_float i )
{
  return mrb_float_to_str( buf, i );
}

mrb_float Spinel::strToMrbFloat( const char *buf )
{
  return str_to_mrb_float( buf );
}

mrb_float Spinel::mfloat( mrb_value o )
{
  return mrb_float( o );
}

mrb_value Spinel::mfloatPool( mrb_float f )
{
  return mrb_float_pool( mrb, f );
}

void * Spinel::ptr( mrb_value o )
{
  return mrb_ptr( o );
}

void * Spinel::cptr( mrb_value o )
{
  return mrb_cptr( o );
}

int Spinel::fixnumP( mrb_value o )
{
  return mrb_fixnum_p( o );
}

int Spinel::undefP( mrb_value o )
{
  return mrb_undef_p( o );
}

int Spinel::nilP( mrb_value o )
{
  return mrb_nil_p( o );
}

int Spinel::mbool( mrb_value o )
{
  return mrb_bool( o );
}

mrb_int Spinel::fixnum( mrb_value value )
{
  return mrb_fixnum( value );
}

mrb_vtype Spinel::type( mrb_value o )
{
  return mrb_type( o );
}

mrb_value Spinel::fixnumValue( mrb_int i )
{
  return mrb_fixnum_value( i );
}

mrb_value Spinel::symbolValue( mrb_sym i )
{
  return mrb_symbol_value( i );
}

mrb_value Spinel::objValue( void *p )
{
  return mrb_obj_value( p );
}

mrb_value Spinel::cptrValue( void *p )
{
  return mrb_cptr_value( mrb, p );
}

mrb_value Spinel::falseValue( void )
{
  return mrb_false_value();
}

mrb_value Spinel::nilValue( void )
{
  return mrb_nil_value();
}

mrb_value Spinel::trueValue( void )
{
  return mrb_true_value();
}

mrb_value Spinel::undefValue( void )
{
  return mrb_undef_value();
}

mrb_value Spinel::boolValue( mrb_bool boolean )
{
  return mrb_bool_value( boolean );
}

// array.c

#ifdef __ENABLE_MRUBY_ARRAY

RArray* Spinel::aryPtr( mrb_value v )
{
  return mrb_ary_ptr( v );
}

mrb_value Spinel::aryValue( RArray *p )
{
  return mrb_ary_value( p );
}

void Spinel::aryModify( RArray* a )
{
  return mrb_ary_modify( mrb, a );
}

void Spinel::aryDecref( mrb_shared_array *shared )
{
  return mrb_ary_decref( mrb, shared );
}

mrb_value Spinel::aryNewCapa( mrb_int capa )
{
  return mrb_ary_new_capa( mrb, capa );
}

mrb_value Spinel::aryNew( void )
{
  return mrb_ary_new( mrb );
}

mrb_value Spinel::aryNewFromValues( mrb_int size, const mrb_value *vals )
{
  return mrb_ary_new_from_values( mrb, size, vals );
}

void Spinel::aryConcat( mrb_value self, mrb_value other )
{
  return mrb_ary_concat( mrb, self, other );
}

mrb_value Spinel::arySplat( mrb_value v )
{
  return mrb_ary_splat( mrb, v );
}

void Spinel::aryPush( mrb_value ary, mrb_value ele )
{
  return mrb_ary_push( mrb, ary, ele );
}

mrb_value Spinel::aryPop( mrb_value ary )
{
  return mrb_ary_pop( mrb, ary );
}

mrb_value Spinel::aryAget( mrb_value self )
{
  return mrb_ary_aget( mrb, self );
}

mrb_value Spinel::aryRef( mrb_value ary, mrb_int n )
{
  return mrb_ary_ref( mrb, ary, n );
}

void Spinel::arySet( mrb_value ary, mrb_int n, mrb_value val )
{
  return mrb_ary_set( mrb, ary, n, val );
}

mrb_int Spinel::aryLen( mrb_value ary )
{
  return mrb_ary_len( mrb, ary );
}

void Spinel::aryReplace( mrb_value a, mrb_value b )
{
  return mrb_ary_replace( mrb, a, b );
}

mrb_value Spinel::checkArrayType( mrb_value self )
{
  return mrb_check_array_type( mrb, self );
}

mrb_value Spinel::aryUnshift( mrb_value self, mrb_value item )
{
  return mrb_ary_unshift( mrb, self, item );
}

mrb_value Spinel::assocNew( mrb_value car, mrb_value cdr )
{
  return mrb_assoc_new( mrb, car, cdr );
}

mrb_value Spinel::aryEntry( mrb_value ary, mrb_int offset )
{
  return mrb_ary_entry( ary, offset );
}

mrb_value Spinel::aryShift( mrb_value self )
{
  return mrb_ary_shift( mrb, self );
}

mrb_value Spinel::aryClear( mrb_value self )
{
  return mrb_ary_clear( mrb, self );
}

mrb_value Spinel::aryJoin( mrb_value ary, mrb_value sep )
{
  return mrb_ary_join( mrb, ary, sep );
}

#endif

// class.c

#ifdef __ENABLE_MRUBY_CLASS


RClass * Spinel::classPtr( mrb_value v )
{
  return mrb_class_ptr( v );
}

RClass * Spinel::mClass( mrb_value v )
{
  return mrb_class( mrb, v );
}

RClass * Spinel::defineClassId( mrb_sym name, RClass *super )
{
  return mrb_define_class_id( mrb, name, super );
}

RClass * Spinel::defineModuleId( mrb_sym name )
{
  return mrb_define_module_id( mrb, name );
}

RClass * Spinel::vmDefineClass( mrb_value outer, mrb_value super, mrb_sym id )
{
  return mrb_vm_define_class( mrb, outer, super, id );
}

RClass * Spinel::vmDefineModule( mrb_value outer, mrb_sym id )
{
  return mrb_vm_define_module( mrb, outer, id );
}

void Spinel::defineMethodVm( RClass *c, mrb_sym name, mrb_value body )
{
  return mrb_define_method_vm( mrb, c, name, body );
}

void Spinel::defineMethodRaw( RClass *c, mrb_sym mid, RProc *p )
{
  return mrb_define_method_raw( mrb, c, mid, p );
}

void Spinel::defineMethodId( RClass *c, mrb_sym mid, mrb_func_t func, mrb_aspec aspec )
{
  return mrb_define_method_id( mrb, c, mid, func, aspec );
}

void Spinel::aliasMethod( RClass *c, mrb_sym a, mrb_sym b )
{
  return mrb_alias_method( mrb, c, a, b );
}

RClass * Spinel::classOuterModule( RClass *c )
{
  return mrb_class_outer_module( mrb, c );
}

RProc * Spinel::methodSearchVm( RClass **cp, mrb_sym mid )
{
  return mrb_method_search_vm( mrb, cp, mid );
}

RProc * Spinel::methodSearch( RClass* c, mrb_sym mid )
{
  return mrb_method_search( mrb, c, mid );
}

RClass* Spinel::classReal( RClass* cl )
{
  return mrb_class_real( cl );
}

void Spinel::gcMarkMt( RClass *c )
{
  return mrb_gc_mark_mt( mrb, c );
}

size_t Spinel::gcMarkMtSize( RClass *c )
{
  return mrb_gc_mark_mt_size( mrb, c );
}

void Spinel::gcFreeMt( RClass *c )
{
  return mrb_gc_free_mt( mrb, c );
}

#endif

#ifdef __ENABLE_MRUBY_COMPILE

// parser.y
mrbc_context * Spinel::cContextNew( void )
{
  return mrbc_context_new( mrb );
}

void Spinel::cContextFree( mrbc_context *cxt )
{
  return mrbc_context_free( mrb, cxt );
}

const char * Spinel::cFilename( mrbc_context *c, const char *s )
{
  return mrbc_filename( mrb, c, s );
}

void Spinel::cPartialHook( mrbc_context *c, int( *partial_hook )( mrb_parser_state* ), void *data )
{
  return mrbc_partial_hook( mrb, c, partial_hook, data );
}

mrb_parser_state * Spinel::parserNew( void )
{
  return mrb_parser_new( mrb );
}

void Spinel::parserFree( mrb_parser_state *p )
{
  return mrb_parser_free( p );
}

void Spinel::parserParse( mrb_parser_state *p, mrbc_context *c )
{
  return mrb_parser_parse( p, c );
}

void Spinel::parserSetFilename( mrb_parser_state *p, const char *f )
{
  return mrb_parser_set_filename( p, f );
}

const char * Spinel::parserGetFilename( mrb_parser_state *p, uint16_t idx )
{
  return mrb_parser_get_filename( p, idx );
}

mrb_parser_state* Spinel::parseString( const char *s, mrbc_context *c )
{
  return mrb_parse_string( mrb, s, c );
}

mrb_parser_state* Spinel::parseNstring( const char *s, int len, mrbc_context *c )
{
  return mrb_parse_nstring( mrb, s, len, c );
}

mrb_value Spinel::loadNstring( const char *s, int len )
{
  return mrb_load_nstring( mrb, s, len );
}

mrb_value Spinel::loadStringCxt( const char *s, mrbc_context *cxt )
{
  return mrb_load_string_cxt( mrb, s, cxt );
}

mrb_value Spinel::loadNstringCxt( const char *s, int len, mrbc_context *cxt )
{
  return mrb_load_nstring_cxt( mrb, s, len, cxt );
}

mrb_parser_state * Spinel::parseFile( FILE *f, mrbc_context *c )
{
  return mrb_parse_file( mrb, f, c );
}

mrb_value Spinel::loadFileCxt( FILE *f, mrbc_context *c )
{
  return mrb_load_file_cxt( mrb, f, c );
}

// codegen.c
RProc * Spinel::generateCode( mrb_parser_state *p )
{
  return mrb_generate_code( mrb, p );
}

#endif

#ifdef __ENABLE_MRUBY_DATA
// etc.c
RData * Spinel::dataObjectAlloc( RClass* klass, void *datap, const mrb_data_type *type )
{
  return mrb_data_object_alloc( mrb, klass, datap, type );
}

RData * Spinel::dataWrapStruct( RClass* klass, const mrb_data_type *type, void *ptr )
{
  return Data_Wrap_Struct( mrb, klass, type, ptr );
}

void Spinel::dataCheckType( mrb_value obj, const mrb_data_type *type )
{
  return mrb_data_check_type( mrb, obj, type );
}

void * Spinel::dataGetPtr( mrb_value obj, const mrb_data_type *type )
{
  return mrb_data_get_ptr( mrb, obj, type );
}

void * Spinel::dataCheckGetPtr( mrb_value obj, const mrb_data_type *type )
{
  return mrb_data_check_get_ptr( mrb, obj, type );
}

void * Spinel::dataCheckAndGet( mrb_value obj, const mrb_data_type *dtype )
{
  return mrb_data_check_and_get( mrb, obj, dtype );
}

void * Spinel::getDatatype( mrb_value val, const mrb_data_type *type )
{
  return mrb_get_datatype( mrb, val, type );
}
void * Spinel::checkDatatype( mrb_value val, const mrb_data_type *type )
{
  return mrb_check_datatype( mrb, val, type );
}

#endif

#ifdef __ENABLE_MRUBY_DEBUG

mrb_irep_debug_info_file * Spinel::debugInfoAppendFile( mrb_irep *irep, uint32_t start_pos, uint32_t end_pos )
{
  return mrb_debug_info_append_file( mrb, irep, start_pos, end_pos );
}

mrb_irep_debug_info * Spinel::debugInfoAlloc( mrb_irep *irep )
{
  return mrb_debug_info_alloc( mrb, irep );
}

void Spinel::debugInfoFree( mrb_irep_debug_info *d )
{
  return mrb_debug_info_free( mrb, d );
}

#endif

#ifdef __ENABLE_MRUBY_DUMP

// dump.c

int Spinel::dumpIrepBinary( mrb_irep *irep, int debug_info, FILE* fp )
{
  return mrb_dump_irep_binary( mrb, irep, debug_info, fp );
}

int Spinel::dumpIrepCfunc( mrb_irep *irep, int debug_info, FILE *fp, const char *initname )
{
  return mrb_dump_irep_cfunc( mrb, irep, debug_info, fp, initname );
}

// load.c

mrb_irep * Spinel::readIrepFile( FILE*fp )
{
  return mrb_read_irep_file( mrb, fp );
}

mrb_value Spinel::loadIrepFile( FILE*fp )
{
  return mrb_load_irep_file( mrb, fp );
}

mrb_value Spinel::loadIrepFileCxt( FILE*fp, mrbc_context *c )
{
  return mrb_load_irep_file_cxt( mrb, fp, c );
}

#endif

#ifdef __ENABLE_MRUBY_GC

#define __SYMBOL_NOT_FOUND

#ifdef __SYMBOL_NOT_FOUND
// gc.c
#include "mruby/proc.h"
#include "mruby/range.h"
#include "mruby/string.h"

#ifndef MRB_HEAP_PAGE_SIZE
#define MRB_HEAP_PAGE_SIZE 1024
#endif
struct free_obj {
  MRB_OBJECT_HEADER;
  struct RBasic *next;
};
typedef struct {
  union {
    struct free_obj free;
    struct RBasic basic;
    struct RObject object;
    struct RClass klass;
    struct RString string;
    struct RArray array;
    struct RHash hash;
    struct RRange range;
    struct RData data;
    struct RProc proc;
  } as;
} RVALUE;
struct heap_page {
  struct RBasic *freelist;
  struct heap_page *prev;
  struct heap_page *next;
  struct heap_page *free_next;
  struct heap_page *free_prev;
  mrb_bool old : 1;
  RVALUE objects[MRB_HEAP_PAGE_SIZE];
};
#endif

void Spinel::objspaceEachObjects( each_object_callback* callback, void *data )
{
#ifndef __SYMBOL_NOT_FOUND
  mrb_objspace_each_objects(mrb, callback, data);
#else
  // symbol not found.
  struct heap_page *page = mrb->heaps;

  while ( page != NULL ) {
    RVALUE *p, *pend;

    p = page->objects;
    pend = p + MRB_HEAP_PAGE_SIZE;
    for ( ; p < pend; p++ ) {
      ( *callback )( mrb, &p->as.basic, data );
    }

    page = page->next;
  }
#endif
}

void Spinel::freeContext( mrb_context *c )
{
#ifndef __SYMBOL_NOT_FOUND
  mrb_free_context( mrb, c );
#else
  if ( !c ) return;
  mrb_free( mrb, c->stbase );
  mrb_free( mrb, c->cibase );
  mrb_free( mrb, c->rescue );
  mrb_free( mrb, c->ensure );
  mrb_free( mrb, c );
#endif
}

#endif

#ifdef __ENABLE_MRUBY_HASH

// hash.c

RHash* Spinel::hashPtr( mrb_value v )
{
  return mrb_hash_ptr( v );
}

mrb_value Spinel::hashValue( RHash *p )
{
  return mrb_hash_value( p );
}

mrb_value Spinel::hashNewCapa( int capa )
{
  return mrb_hash_new_capa( mrb, capa );
}

mrb_value Spinel::hashNew( void )
{
  return mrb_hash_new( mrb );
}

void Spinel::hashSet( mrb_value hash, mrb_value key, mrb_value val )
{
  return mrb_hash_set( mrb, hash, key, val );
}

mrb_value Spinel::hashGet( mrb_value hash, mrb_value key )
{
  return mrb_hash_get( mrb, hash, key );
}

mrb_value Spinel::hashFetch( mrb_value hash, mrb_value key, mrb_value def )
{
  return mrb_hash_fetch( mrb, hash, key, def );
}

mrb_value Spinel::hashDeleteKey( mrb_value hash, mrb_value key )
{
  return mrb_hash_delete_key( mrb, hash, key );
}

mrb_value Spinel::hashKeys( mrb_value hash )
{
  return mrb_hash_keys( mrb, hash );
}

mrb_value Spinel::checkHashType( mrb_value hash )
{
  return mrb_check_hash_type( mrb, hash );
}

mrb_value Spinel::hashEmptyP( mrb_value self )
{
  return mrb_hash_empty_p( mrb, self );
}

mrb_value Spinel::hashClear( mrb_value hash )
{
  return mrb_hash_clear( mrb, hash );
}

kh_ht * Spinel::hashTbl( mrb_value hash )
{
  return mrb_hash_tbl( mrb, hash );
}

void Spinel::gcMarkHash( RHash *hash )
{
  return mrb_gc_mark_hash( mrb, hash );
}

size_t Spinel::gcMarkHashSize( RHash *hash )
{
  return mrb_gc_mark_hash_size( mrb, hash );
}

void Spinel::gcFreeHash( RHash *hash )
{
  return mrb_gc_free_hash( mrb, hash );
}

#endif

#ifdef __ENABLE_MRUBY_IREP

// load.c
mrb_value Spinel::loadIrepCxt( const uint8_t*bin, mrbc_context *c )
{
  return mrb_load_irep_cxt( mrb, bin, c );
}

// state.c
mrb_irep * Spinel::addIrep( void )
{
  return mrb_add_irep( mrb );
}

void Spinel::irepFree( mrb_irep *irep )
{
  return mrb_irep_free( mrb, irep );
}

void Spinel::irepIncref( mrb_irep *irep )
{
  return mrb_irep_incref( mrb, irep );
}

void Spinel::irepDecref( mrb_irep *irep )
{
  return mrb_irep_decref( mrb, irep );
}

#endif

#ifdef __ENABLE_MRUBY_NUMERIC

mrb_value Spinel::floToFixnum( mrb_value val )
{
  return mrb_flo_to_fixnum( mrb, val );
}

mrb_value Spinel::floToStr( mrb_value flo, int max_digit )
{
  return mrb_flo_to_str( mrb, flo, max_digit );
}

mrb_value Spinel::fixnumToStr( mrb_value x, int base )
{
  return mrb_fixnum_to_str( mrb, x, base );
}

mrb_value Spinel::fixnumPlus( mrb_value x, mrb_value y )
{
  return mrb_fixnum_plus( mrb, x, y );
}

mrb_value Spinel::fixnumMinus( mrb_value x, mrb_value y )
{
  return mrb_fixnum_minus( mrb, x, y );
}

mrb_value Spinel::fixnumMul( mrb_value x, mrb_value y )
{
  return mrb_fixnum_mul( mrb, x, y );
}

mrb_value Spinel::numDiv( mrb_value x, mrb_value y )
{
  return mrb_num_div( mrb, x, y );
}
#endif

#ifdef __ENABLE_MRUBY_PROC

// proc.c

RProc * Spinel::procPtr( mrb_value v )
{
  return mrb_proc_ptr( v );
}

RProc * Spinel::procNew( mrb_irep *irep )
{
  return mrb_proc_new( mrb, irep );
}

RProc * Spinel::procNewCfunc( mrb_func_t func )
{
  return mrb_proc_new_cfunc( mrb, func );
}

RProc * Spinel::closureNew( mrb_irep *irep )
{
  return mrb_closure_new( mrb, irep );
}

RProc * Spinel::closureNewCfunc( mrb_func_t func, int nlocals )
{
  return mrb_closure_new_cfunc( mrb, func, nlocals );
}

void Spinel::procCopy( struct RProc *a, struct RProc *b )
{
  return mrb_proc_copy( a, b );
}

#endif

#ifdef __ENABLE_MRUBY_RANGE

RRange * Spinel::rangePtr( mrb_value v )
{
  return mrb_range_ptr( v );
}

mrb_value Spinel::rangeValue( RRange *p )
{
  return mrb_range_value( p );
}

mrb_value Spinel::rangeNew( mrb_value beg, mrb_value end, int excl )
{
  return mrb_range_new( mrb, beg, end, excl );
}

mrb_int Spinel::rangeBegLen( mrb_value range, mrb_int *begp, mrb_int *lenp, mrb_int len )
{
  return mrb_range_beg_len( mrb, range, begp, lenp, len );
}

#endif

#ifdef __ENABLE_MRUBY_STRING

RString * Spinel::strPtr( mrb_value s )
{
  return mrb_str_ptr( s );
}

void Spinel::gcFreeStr( struct RString *str )
{
  return mrb_gc_free_str( mrb, str );
}

void Spinel::strModify( struct RString *s )
{
  return mrb_str_modify( mrb, s );
}

void Spinel::strConcat( mrb_value self, mrb_value other )
{
  return mrb_str_concat( mrb, self, other );
}

mrb_value Spinel::strPlus( mrb_value a, mrb_value b )
{
  return mrb_str_plus( mrb, a, b );
}

mrb_value Spinel::ptrToStr( void *p )
{
  return mrb_ptr_to_str( mrb, p );
}

mrb_value Spinel::objAsString( mrb_value obj )
{
  return mrb_obj_as_string( mrb, obj );
}

mrb_value Spinel::strResize( mrb_value str, mrb_int len )
{
  return mrb_str_resize( mrb, str, len );
}

mrb_value Spinel::strSubstr( mrb_value str, mrb_int beg, mrb_int len )
{
  return mrb_str_substr( mrb, str, beg, len );
}

mrb_value Spinel::stringType( mrb_value str )
{
  return mrb_string_type( mrb, str );
}

mrb_value Spinel::checkString_type( mrb_value str )
{
  return mrb_check_string_type( mrb, str );
}

mrb_value Spinel::strBufNew( mrb_int capa )
{
  return mrb_str_buf_new( mrb, capa );
}

mrb_value Spinel::strBufCat( mrb_value str, const char *ptr, size_t len )
{
  return mrb_str_buf_cat( mrb, str, ptr, len );
}

char * Spinel::stringValueCstr( mrb_value *ptr )
{
  return mrb_string_value_cstr( mrb, ptr );
}

char * Spinel::stringValuePtr( mrb_value ptr )
{
  return mrb_string_value_ptr( mrb, ptr );
}

int Spinel::strOffset( mrb_value str, int pos )
{
  return mrb_str_offset( mrb, str, pos );
}

mrb_value Spinel::strDup( mrb_value str )
{
  return mrb_str_dup( mrb, str );
}

mrb_value Spinel::strIntern( mrb_value self )
{
  return mrb_str_intern( mrb, self );
}

mrb_value Spinel::strCatCstr( mrb_value str, const char *ptr )
{
  return mrb_str_cat_cstr( mrb, str, ptr );
}

mrb_value Spinel::strToInum( mrb_value str, int base, int badcheck )
{
  return mrb_str_to_inum( mrb, str, base, badcheck );
}

double Spinel::strToDbl( mrb_value str, int badcheck )
{
  return mrb_str_to_dbl( mrb, str, badcheck );
}

mrb_value Spinel::strToStr( mrb_value str )
{
  return mrb_str_to_str( mrb, str );
}

mrb_int Spinel::strHash( mrb_value str )
{
  return mrb_str_hash( mrb, str );
}

mrb_value Spinel::strBufAppend( mrb_value str, mrb_value str2 )
{
  return mrb_str_buf_append( mrb, str, str2 );
}

mrb_value Spinel::strInspect( mrb_value str )
{
  return mrb_str_inspect( mrb, str );
}

mrb_bool Spinel::strEqual( mrb_value str1, mrb_value str2 )
{
  return mrb_str_equal( mrb, str1, str2 );
}

mrb_value Spinel::strDump( mrb_value str )
{
  return mrb_str_dump( mrb, str );
}

mrb_value Spinel::strCat( mrb_value str, const char *ptr, size_t len )
{
  return mrb_str_cat( mrb, str, ptr, len );
}

mrb_value Spinel::strAppend( mrb_value str, mrb_value str2 )
{
  return mrb_str_append( mrb, str, str2 );
}

int Spinel::strCmp( mrb_value str1, mrb_value str2 )
{
  return mrb_str_cmp( mrb, str1, str2 );
}

char * Spinel::strToCstr( mrb_value str )
{
  return mrb_str_to_cstr( mrb, str );
}

mrb_value Spinel::strPool( mrb_value str )
{
  return mrb_str_pool( mrb, str );
}

mrb_value Spinel::strCat2( mrb_value str, const char *ptr )
{
  return mrb_str_cat_cstr( mrb, str, ptr );
}
#endif

#ifdef __ENABLE_MRUBY_VARIABLE

// variable.c

mrb_value Spinel::vmSpecialGet( mrb_sym i )
{
  return mrb_vm_special_get( mrb, i );
}

void Spinel::vmSpecialSet( mrb_sym i, mrb_value v )
{
  return mrb_vm_special_set( mrb, i, v );
}

mrb_value Spinel::vmIvGet( mrb_sym sym )
{
  return mrb_vm_iv_get( mrb, sym );
}

void Spinel::vmIvSet( mrb_sym sym, mrb_value v )
{
  return mrb_vm_iv_set( mrb, sym, v );
}

mrb_value Spinel::vmCvGet( mrb_sym sym )
{
  return mrb_vm_cv_get( mrb, sym );
}

void Spinel::vmCvSet( mrb_sym sym, mrb_value v )
{
  return mrb_vm_cv_set( mrb, sym, v );
}

mrb_value Spinel::vmConstGet( mrb_sym sym )
{
  return mrb_vm_const_get( mrb, sym );
}

void Spinel::vmConstSet( mrb_value mod, mrb_sym sym, mrb_value v )
{
  return mrb_vm_const_set( mrb, sym, v );
}

mrb_value Spinel::constGet( mrb_value mod, mrb_sym sym )
{
  return mrb_const_get( mrb, mod, sym );
}

void Spinel::constSet( mrb_value mod, mrb_sym sym, mrb_value v )
{
  return mrb_const_set( mrb, mod, sym, v );
}

mrb_bool Spinel::constDefined( mrb_value mod, mrb_sym sym )
{
  return mrb_const_defined( mrb, mod, sym );
}

void Spinel::constRemove( mrb_value mod, mrb_sym sym )
{
  return mrb_const_remove( mrb, mod, sym );
}

mrb_value Spinel::objIvGet( RObject *obj, mrb_sym sym )
{
  return mrb_obj_iv_get( mrb, obj, sym );
}
void Spinel::objIvSet( RObject *obj, mrb_sym sym, mrb_value v )
{
  return mrb_obj_iv_set( mrb, obj, sym, v );
}

mrb_bool Spinel::objIvDefined( RObject *obj, mrb_sym sym )
{
  return mrb_obj_iv_defined( mrb, obj, sym );
}

void Spinel::objIvIfnone( RObject *obj, mrb_sym sym, mrb_value v )
{
  return mrb_obj_iv_ifnone( mrb, obj, sym, v );
}

mrb_value Spinel::ivGet( mrb_value obj, mrb_sym sym )
{
  return mrb_iv_get( mrb, obj, sym );
}

void Spinel::ivSet( mrb_value obj, mrb_sym sym, mrb_value v )
{
  return mrb_iv_set( mrb, obj, sym, v );
}

mrb_bool Spinel::ivDefined( mrb_value obj, mrb_sym sym )
{
  return mrb_iv_defined( mrb, obj, sym );
}

mrb_value Spinel::ivRemove( mrb_value obj, mrb_sym sym )
{
  return mrb_iv_remove( mrb, obj, sym );
}

void Spinel::ivCopy( mrb_value dest, mrb_value src )
{
  return mrb_iv_copy( mrb, dest, src );
}

int Spinel::constDefinedAt( RClass *klass, mrb_sym id )
{
  return mrb_const_defined_at( mrb, klass, id );
}

mrb_value Spinel::modConstants( mrb_value mod )
{
  return mrb_mod_constants( mrb, mod );
}

mrb_value Spinel::fGlobalVariables( mrb_value self )
{
  return mrb_f_global_variables( mrb, self );
}

mrb_value Spinel::gvGet( mrb_sym sym )
{
  return mrb_gv_get( mrb, sym );
}

void Spinel::gvSet( mrb_sym sym, mrb_value val )
{
  return mrb_gv_set( mrb, sym, val );
}

void Spinel::gvRemove( mrb_sym sym )
{
  return mrb_gv_remove( mrb, sym );
}

mrb_value Spinel::objInstanceVariables( mrb_value self )
{
  return mrb_obj_instance_variables( mrb, self );
}

mrb_value Spinel::objIvInspect( RObject *obj )
{
  return mrb_obj_iv_inspect( mrb, obj );
}

mrb_sym Spinel::classSym( RClass *c, RClass *outer )
{
  return mrb_class_sym( mrb, c, outer );
}

mrb_value Spinel::modClassVariables( mrb_value mod )
{
  return mrb_mod_class_variables( mrb, mod );
}

mrb_value Spinel::modCvGet( RClass * c, mrb_sym sym )
{
  return mrb_mod_cv_get( mrb, c, sym );
}

mrb_value Spinel::cvGet( mrb_value mod, mrb_sym sym )
{
  return mrb_cv_get( mrb, mod, sym );
}

void Spinel::modCvSet( RClass * c, mrb_sym sym, mrb_value v )
{
  return mrb_mod_cv_set( mrb, c, sym, v );
}

void Spinel::cvSet( mrb_value mod, mrb_sym sym, mrb_value v )
{
  return mrb_cv_set( mrb, mod, sym, v );
}

mrb_bool Spinel::modCvDefined( struct RClass * c, mrb_sym sym )
{
  return mrb_mod_cv_defined( mrb, c, sym );
}

mrb_bool Spinel::cvDefined( mrb_value mod, mrb_sym sym )
{
  return mrb_cv_defined( mrb, mod, sym );
}

void Spinel::gcMarkGv( void )
{
  return mrb_gc_mark_gv( mrb );
}

void Spinel::gcFreeGv( void )
{
  return mrb_gc_free_gv( mrb );
}

void Spinel::gcMarkIv( RObject *obj )
{
  return mrb_gc_mark_iv( mrb, obj );
}

size_t Spinel::gcMarkIvSize( RObject *obj )
{
  return mrb_gc_mark_iv_size( mrb, obj );
}

void Spinel::gcFreeIv( RObject *obj )
{
  return mrb_gc_free_iv( mrb, obj );
}

#endif