
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 7 "src/parse.y"

#undef PARSER_DEBUG

#define YYDEBUG 1
#define YYERROR_VERBOSE 1
/*
 * Force yacc to use our memory management.  This is a little evil because
 * the macros assume that "parser_state *p" is in scope
 */
#define YYMALLOC(n)    mrb_malloc(p->mrb, (n))
#define YYFREE(o)      mrb_free(p->mrb, (o))
#define YYSTACK_USE_ALLOCA 0

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/proc.h"
#include "node.h"

#define YYLEX_PARAM p

typedef mrb_ast_node node;
typedef struct mrb_parser_state parser_state;
typedef struct mrb_parser_heredoc_info parser_heredoc_info;

static int yylex(void *lval, parser_state *p);
static void yyerror(parser_state *p, const char *s);
static void yywarn(parser_state *p, const char *s);
static void yywarning(parser_state *p, const char *s);
static void backref_error(parser_state *p, node *n);
static void tokadd(parser_state *p, int c);

#ifndef isascii
#define isascii(c) (((c) & ~0x7f) == 0)
#endif

#define identchar(c) (isalnum(c) || (c) == '_' || !isascii(c))

typedef unsigned int stack_type;

#define BITSTACK_PUSH(stack, n) ((stack) = ((stack)<<1)|((n)&1))
#define BITSTACK_POP(stack)     ((stack) = (stack) >> 1)
#define BITSTACK_LEXPOP(stack)  ((stack) = ((stack) >> 1) | ((stack) & 1))
#define BITSTACK_SET_P(stack)   ((stack)&1)

#define COND_PUSH(n)    BITSTACK_PUSH(p->cond_stack, (n))
#define COND_POP()      BITSTACK_POP(p->cond_stack)
#define COND_LEXPOP()   BITSTACK_LEXPOP(p->cond_stack)
#define COND_P()        BITSTACK_SET_P(p->cond_stack)

#define CMDARG_PUSH(n)  BITSTACK_PUSH(p->cmdarg_stack, (n))
#define CMDARG_POP()    BITSTACK_POP(p->cmdarg_stack)
#define CMDARG_LEXPOP() BITSTACK_LEXPOP(p->cmdarg_stack)
#define CMDARG_P()      BITSTACK_SET_P(p->cmdarg_stack)

#define sym(x) ((mrb_sym)(intptr_t)(x))
#define nsym(x) ((node*)(intptr_t)(x))

static inline mrb_sym
intern_cstr_gen(parser_state *p, const char *s)
{
  return mrb_intern_cstr(p->mrb, s);
}
#define intern_cstr(s) intern_cstr_gen(p,(s))

static inline mrb_sym
intern_gen(parser_state *p, const char *s, size_t len)
{
  return mrb_intern(p->mrb, s, len);
}
#define intern(s,len) intern_gen(p,(s),(len))

static inline mrb_sym
intern_gen_c(parser_state *p, const char c)
{
  return mrb_intern(p->mrb, &c, 1);
}
#define intern_c(c) intern_gen_c(p,(c))

static void
cons_free_gen(parser_state *p, node *cons)
{
  cons->cdr = p->cells;
  p->cells = cons;
}
#define cons_free(c) cons_free_gen(p, (c))

static void*
parser_palloc(parser_state *p, size_t size)
{
  void *m = mrb_pool_alloc(p->pool, size);

  if (!m) {
    longjmp(p->jmp, 1);
  }
  return m;
}

static node*
cons_gen(parser_state *p, node *car, node *cdr)
{
  node *c;

  if (p->cells) {
    c = p->cells;
    p->cells = p->cells->cdr;
  }
  else {
    c = (node *)parser_palloc(p, sizeof(mrb_ast_node));
  }

  c->car = car;
  c->cdr = cdr;
  c->lineno = p->lineno;
  c->filename_index = p->current_filename_index;
  return c;
}
#define cons(a,b) cons_gen(p,(a),(b))

static node*
list1_gen(parser_state *p, node *a)
{
  return cons(a, 0);
}
#define list1(a) list1_gen(p, (a))

static node*
list2_gen(parser_state *p, node *a, node *b)
{
  return cons(a, cons(b,0));
}
#define list2(a,b) list2_gen(p, (a),(b))

static node*
list3_gen(parser_state *p, node *a, node *b, node *c)
{
  return cons(a, cons(b, cons(c,0)));
}
#define list3(a,b,c) list3_gen(p, (a),(b),(c))

static node*
list4_gen(parser_state *p, node *a, node *b, node *c, node *d)
{
  return cons(a, cons(b, cons(c, cons(d, 0))));
}
#define list4(a,b,c,d) list4_gen(p, (a),(b),(c),(d))

static node*
list5_gen(parser_state *p, node *a, node *b, node *c, node *d, node *e)
{
  return cons(a, cons(b, cons(c, cons(d, cons(e, 0)))));
}
#define list5(a,b,c,d,e) list5_gen(p, (a),(b),(c),(d),(e))

static node*
list6_gen(parser_state *p, node *a, node *b, node *c, node *d, node *e, node *f)
{
  return cons(a, cons(b, cons(c, cons(d, cons(e, cons(f, 0))))));
}
#define list6(a,b,c,d,e,f) list6_gen(p, (a),(b),(c),(d),(e),(f))

static node*
append_gen(parser_state *p, node *a, node *b)
{
  node *c = a;

  if (!a) return b;
  while (c->cdr) {
    c = c->cdr;
  }
  if (b) {
    c->cdr = b;
  }
  return a;
}
#define append(a,b) append_gen(p,(a),(b))
#define push(a,b) append_gen(p,(a),list1(b))

static char*
parser_strndup(parser_state *p, const char *s, size_t len)
{
  char *b = (char *)parser_palloc(p, len+1);

  memcpy(b, s, len);
  b[len] = '\0';
  return b;
}
#define strndup(s,len) parser_strndup(p, s, len)

static char*
parser_strdup(parser_state *p, const char *s)
{
  return parser_strndup(p, s, strlen(s));
}
#undef strdup
#define strdup(s) parser_strdup(p, s)

// xxx -----------------------------

static node*
local_switch(parser_state *p)
{
  node *prev = p->locals;

  p->locals = cons(0, 0);
  return prev;
}

static void
local_resume(parser_state *p, node *prev)
{
  p->locals = prev;
}

static void
local_nest(parser_state *p)
{
  p->locals = cons(0, p->locals);
}

static void
local_unnest(parser_state *p)
{
  p->locals = p->locals->cdr;
}

static int
local_var_p(parser_state *p, mrb_sym sym)
{
  node *l = p->locals;

  while (l) {
    node *n = l->car;
    while (n) {
      if (sym(n->car) == sym) return 1;
      n = n->cdr;
    }
    l = l->cdr;
  }
  return 0;
}

static void
local_add_f(parser_state *p, mrb_sym sym)
{
  p->locals->car = push(p->locals->car, nsym(sym));
}

static void
local_add(parser_state *p, mrb_sym sym)
{
  if (!local_var_p(p, sym)) {
    local_add_f(p, sym);
  }
}

// (:scope (vars..) (prog...))
static node*
new_scope(parser_state *p, node *body)
{
  return cons((node*)NODE_SCOPE, cons(p->locals->car, body));
}

// (:begin prog...)
static node*
new_begin(parser_state *p, node *body)
{
  if (body)
    return list2((node*)NODE_BEGIN, body);
  return cons((node*)NODE_BEGIN, 0);
}

#define newline_node(n) (n)

// (:rescue body rescue else)
static node*
new_rescue(parser_state *p, node *body, node *resq, node *els)
{
  return list4((node*)NODE_RESCUE, body, resq, els);
}

// (:ensure body ensure)
static node*
new_ensure(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_ENSURE, cons(a, cons(0, b)));
}

// (:nil)
static node*
new_nil(parser_state *p)
{
  return list1((node*)NODE_NIL);
}

// (:true)
static node*
new_true(parser_state *p)
{
  return list1((node*)NODE_TRUE);
}

// (:false)
static node*
new_false(parser_state *p)
{
  return list1((node*)NODE_FALSE);
}

// (:alias new old)
static node*
new_alias(parser_state *p, mrb_sym a, mrb_sym b)
{
  return cons((node*)NODE_ALIAS, cons(nsym(a), nsym(b)));
}

// (:if cond then else)
static node*
new_if(parser_state *p, node *a, node *b, node *c)
{
  return list4((node*)NODE_IF, a, b, c);
}

// (:unless cond then else)
static node*
new_unless(parser_state *p, node *a, node *b, node *c)
{
  return list4((node*)NODE_IF, a, c, b);
}

// (:while cond body)
static node*
new_while(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_WHILE, cons(a, b));
}

// (:until cond body)
static node*
new_until(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_UNTIL, cons(a, b));
}

// (:for var obj body)
static node*
new_for(parser_state *p, node *v, node *o, node *b)
{
  return list4((node*)NODE_FOR, v, o, b);
}

// (:case a ((when ...) body) ((when...) body))
static node*
new_case(parser_state *p, node *a, node *b)
{
  node *n = list2((node*)NODE_CASE, a);
  node *n2 = n;

  while (n2->cdr) {
    n2 = n2->cdr;
  }
  n2->cdr = b;
  return n;
}

// (:postexe a)
static node*
new_postexe(parser_state *p, node *a)
{
  return cons((node*)NODE_POSTEXE, a);
}

// (:self)
static node*
new_self(parser_state *p)
{
  return list1((node*)NODE_SELF);
}

// (:call a b c)
static node*
new_call(parser_state *p, node *a, mrb_sym b, node *c)
{
  return list4((node*)NODE_CALL, a, nsym(b), c);
}

// (:fcall self mid args)
static node*
new_fcall(parser_state *p, mrb_sym b, node *c)
{
  return list4((node*)NODE_FCALL, new_self(p), nsym(b), c);
}

// (:super . c)
static node*
new_super(parser_state *p, node *c)
{
  return cons((node*)NODE_SUPER, c);
}

// (:zsuper)
static node*
new_zsuper(parser_state *p)
{
  return list1((node*)NODE_ZSUPER);
}

// (:yield . c)
static node*
new_yield(parser_state *p, node *c)
{
  if (c) {
    if (c->cdr) {
      yyerror(p, "both block arg and actual block given");
    }
    return cons((node*)NODE_YIELD, c->car);
  }
  return cons((node*)NODE_YIELD, 0);
}

// (:return . c)
static node*
new_return(parser_state *p, node *c)
{
  return cons((node*)NODE_RETURN, c);
}

// (:break . c)
static node*
new_break(parser_state *p, node *c)
{
  return cons((node*)NODE_BREAK, c);
}

// (:next . c)
static node*
new_next(parser_state *p, node *c)
{
  return cons((node*)NODE_NEXT, c);
}

// (:redo)
static node*
new_redo(parser_state *p)
{
  return list1((node*)NODE_REDO);
}

// (:retry)
static node*
new_retry(parser_state *p)
{
  return list1((node*)NODE_RETRY);
}

// (:dot2 a b)
static node*
new_dot2(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_DOT2, cons(a, b));
}

// (:dot3 a b)
static node*
new_dot3(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_DOT3, cons(a, b));
}

// (:colon2 b c)
static node*
new_colon2(parser_state *p, node *b, mrb_sym c)
{
  return cons((node*)NODE_COLON2, cons(b, nsym(c)));
}

// (:colon3 . c)
static node*
new_colon3(parser_state *p, mrb_sym c)
{
  return cons((node*)NODE_COLON3, nsym(c));
}

// (:and a b)
static node*
new_and(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_AND, cons(a, b));
}

// (:or a b)
static node*
new_or(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_OR, cons(a, b));
}

// (:array a...)
static node*
new_array(parser_state *p, node *a)
{
  return cons((node*)NODE_ARRAY, a);
}

// (:splat . a)
static node*
new_splat(parser_state *p, node *a)
{
  return cons((node*)NODE_SPLAT, a);
}

// (:hash (k . v) (k . v)...)
static node*
new_hash(parser_state *p, node *a)
{
  return cons((node*)NODE_HASH, a);
}

// (:sym . a)
static node*
new_sym(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_SYM, nsym(sym));
}

static mrb_sym
new_strsym(parser_state *p, node* str)
{
  const char *s = (const char*)str->cdr->car;
  size_t len = (size_t)str->cdr->cdr;

  return mrb_intern(p->mrb, s, len);
}

// (:lvar . a)
static node*
new_lvar(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_LVAR, nsym(sym));
}

// (:gvar . a)
static node*
new_gvar(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_GVAR, nsym(sym));
}

// (:ivar . a)
static node*
new_ivar(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_IVAR, nsym(sym));
}

// (:cvar . a)
static node*
new_cvar(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_CVAR, nsym(sym));
}

// (:const . a)
static node*
new_const(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_CONST, nsym(sym));
}

// (:undef a...)
static node*
new_undef(parser_state *p, mrb_sym sym)
{
  return list2((node*)NODE_UNDEF, nsym(sym));
}

// (:class class super body)
static node*
new_class(parser_state *p, node *c, node *s, node *b)
{
  return list4((node*)NODE_CLASS, c, s, cons(p->locals->car, b));
}

// (:sclass obj body)
static node*
new_sclass(parser_state *p, node *o, node *b)
{
  return list3((node*)NODE_SCLASS, o, cons(p->locals->car, b));
}

// (:module module body)
static node*
new_module(parser_state *p, node *m, node *b)
{
  return list3((node*)NODE_MODULE, m, cons(p->locals->car, b));
}

// (:def m lv (arg . body))
static node*
new_def(parser_state *p, mrb_sym m, node *a, node *b)
{
  return list5((node*)NODE_DEF, nsym(m), p->locals->car, a, b);
}

// (:sdef obj m lv (arg . body))
static node*
new_sdef(parser_state *p, node *o, mrb_sym m, node *a, node *b)
{
  return list6((node*)NODE_SDEF, o, nsym(m), p->locals->car, a, b);
}

// (:arg . sym)
static node*
new_arg(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_ARG, nsym(sym));
}

// (m o r m2 b)
// m: (a b c)
// o: ((a . e1) (b . e2))
// r: a
// m2: (a b c)
// b: a
static node*
new_args(parser_state *p, node *m, node *opt, mrb_sym rest, node *m2, mrb_sym blk)
{
  node *n;

  n = cons(m2, nsym(blk));
  n = cons(nsym(rest), n);
  n = cons(opt, n);
  return cons(m, n);
}

// (:block_arg . a)
static node*
new_block_arg(parser_state *p, node *a)
{
  return cons((node*)NODE_BLOCK_ARG, a);
}

// (:block arg body)
static node*
new_block(parser_state *p, node *a, node *b)
{
  return list4((node*)NODE_BLOCK, p->locals->car, a, b);
}

// (:lambda arg body)
static node*
new_lambda(parser_state *p, node *a, node *b)
{
  return list4((node*)NODE_LAMBDA, p->locals->car, a, b);
}

// (:asgn lhs rhs)
static node*
new_asgn(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_ASGN, cons(a, b));
}

// (:masgn mlhs=(pre rest post)  mrhs)
static node*
new_masgn(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_MASGN, cons(a, b));
}

// (:asgn lhs rhs)
static node*
new_op_asgn(parser_state *p, node *a, mrb_sym op, node *b)
{
  return list4((node*)NODE_OP_ASGN, a, nsym(op), b);
}

// (:int . i)
static node*
new_int(parser_state *p, const char *s, int base)
{
  return list3((node*)NODE_INT, (node*)strdup(s), (node*)(intptr_t)base);
}

// (:float . i)
static node*
new_float(parser_state *p, const char *s)
{
  return cons((node*)NODE_FLOAT, (node*)strdup(s));
}

// (:str . (s . len))
static node*
new_str(parser_state *p, const char *s, int len)
{
  return cons((node*)NODE_STR, cons((node*)strndup(s, len), (node*)(intptr_t)len));
}

// (:dstr . a)
static node*
new_dstr(parser_state *p, node *a)
{
  return cons((node*)NODE_DSTR, a);
}

// (:str . (s . len))
static node*
new_xstr(parser_state *p, const char *s, int len)
{
  return cons((node*)NODE_XSTR, cons((node*)strndup(s, len), (node*)(intptr_t)len));
}

// (:xstr . a)
static node*
new_dxstr(parser_state *p, node *a)
{
  return cons((node*)NODE_DXSTR, a);
}

// (:dsym . a)
static node*
new_dsym(parser_state *p, node *a)
{
  return cons((node*)NODE_DSYM, new_dstr(p, a));
}

// (:str . (a . a))
static node*
new_regx(parser_state *p, const char *p1, const char* p2)
{
  return cons((node*)NODE_REGX, cons((node*)p1, (node*)p2));
}

// (:dregx . a)
static node*
new_dregx(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_DREGX, cons(a, b));
}

// (:backref . n)
static node*
new_back_ref(parser_state *p, int n)
{
  return cons((node*)NODE_BACK_REF, (node*)(intptr_t)n);
}

// (:nthref . n)
static node*
new_nth_ref(parser_state *p, int n)
{
  return cons((node*)NODE_NTH_REF, (node*)(intptr_t)n);
}

// (:heredoc . a)
static node*
new_heredoc(parser_state *p)
{
  parser_heredoc_info *inf = (parser_heredoc_info *)parser_palloc(p, sizeof(parser_heredoc_info));
  return cons((node*)NODE_HEREDOC, (node*)inf);
}

static void
new_bv(parser_state *p, mrb_sym id)
{
}

static node*
new_literal_delim(parser_state *p)
{
  return cons((node*)NODE_LITERAL_DELIM, 0);
}

// (:words . a)
static node*
new_words(parser_state *p, node *a)
{
  return cons((node*)NODE_WORDS, a);
}

// (:symbols . a)
static node*
new_symbols(parser_state *p, node *a)
{
  return cons((node*)NODE_SYMBOLS, a);
}

// xxx -----------------------------

// (:call a op)
static node*
call_uni_op(parser_state *p, node *recv, char *m)
{
  return new_call(p, recv, intern_cstr(m), 0);
}

// (:call a op b)
static node*
call_bin_op(parser_state *p, node *recv, char *m, node *arg1)
{
  return new_call(p, recv, intern_cstr(m), list1(list1(arg1)));
}

static void
args_with_block(parser_state *p, node *a, node *b)
{
  if (b) {
    if (a->cdr) {
      yyerror(p, "both block arg and actual block given");
    }
    a->cdr = b;
  }
}

static void
call_with_block(parser_state *p, node *a, node *b)
{
  node *n;

  if (a->car == (node*)NODE_SUPER ||
      a->car == (node*)NODE_ZSUPER) {
    if (!a->cdr) a->cdr = cons(0, b);
    else {
      args_with_block(p, a->cdr, b);
    }
  }
  else {
    n = a->cdr->cdr->cdr;
    if (!n->car) n->car = cons(0, b);
    else {
      args_with_block(p, n->car, b);
    }
  }
}

static node*
negate_lit(parser_state *p, node *n)
{
  return cons((node*)NODE_NEGATE, n);
}

static node*
cond(node *n)
{
  return n;
}

static node*
ret_args(parser_state *p, node *n)
{
  if (n->cdr) {
    yyerror(p, "block argument should not be given");
    return NULL;
  }
  if (!n->car->cdr) return n->car->car;
  return new_array(p, n->car);
}

static void
assignable(parser_state *p, node *lhs)
{
  if ((int)(intptr_t)lhs->car == NODE_LVAR) {
    local_add(p, sym(lhs->cdr));
  }
}

static node*
var_reference(parser_state *p, node *lhs)
{
  node *n;

  if ((int)(intptr_t)lhs->car == NODE_LVAR) {
    if (!local_var_p(p, sym(lhs->cdr))) {
      n = new_fcall(p, sym(lhs->cdr), 0);
      cons_free(lhs);
      return n;
    }
  }

  return lhs;
}

typedef enum mrb_string_type  string_type;

static node*
new_strterm(parser_state *p, string_type type, int term, int paren)
{
  return cons((node*)(intptr_t)type, cons((node*)0, cons((node*)(intptr_t)paren, (node*)(intptr_t)term)));
}

static void
end_strterm(parser_state *p)
{
  cons_free(p->lex_strterm->cdr->cdr);
  cons_free(p->lex_strterm->cdr);
  cons_free(p->lex_strterm);
  p->lex_strterm = NULL;
}

parser_heredoc_info *
parsing_heredoc_inf(parser_state *p)
{
  node *nd = p->parsing_heredoc;
  if (nd == NULL)
    return NULL;
  /* mrb_assert(nd->car->car == NODE_HEREDOC); */
  return (parser_heredoc_info*)nd->car->cdr;
}

static void
heredoc_treat_nextline(parser_state *p)
{
  if (p->heredocs_from_nextline == NULL)
    return;
  if (p->parsing_heredoc == NULL) {
    node *n;
    p->parsing_heredoc = p->heredocs_from_nextline;
    p->lex_strterm_before_heredoc = p->lex_strterm;
    p->lex_strterm = new_strterm(p, parsing_heredoc_inf(p)->type, 0, 0);
    n = p->all_heredocs;
    if (n) {
      while (n->cdr)
	n = n->cdr;
      n->cdr = p->parsing_heredoc;
    } else {
      p->all_heredocs = p->parsing_heredoc;
    }
  } else {
    node *n, *m;
    m = p->heredocs_from_nextline;
    while (m->cdr)
      m = m->cdr;
    n = p->all_heredocs;
    mrb_assert(n != NULL);
    if (n == p->parsing_heredoc) {
      m->cdr = n;
      p->all_heredocs = p->heredocs_from_nextline;
      p->parsing_heredoc = p->heredocs_from_nextline;
    } else {
      while (n->cdr != p->parsing_heredoc) {
	n = n->cdr;
	mrb_assert(n != NULL);
      }
      m->cdr = n->cdr;
      n->cdr = p->heredocs_from_nextline;
      p->parsing_heredoc = p->heredocs_from_nextline;
    }
  }
  p->heredocs_from_nextline = NULL;
}

static void
heredoc_end(parser_state *p)
{
  p->parsing_heredoc = p->parsing_heredoc->cdr;
  if (p->parsing_heredoc == NULL) {
    p->lstate = EXPR_BEG;
    p->cmd_start = TRUE;
    end_strterm(p);
    p->lex_strterm = p->lex_strterm_before_heredoc;
    p->lex_strterm_before_heredoc = NULL;
    p->heredoc_end_now = TRUE;
  } else {
    /* next heredoc */
    p->lex_strterm->car = (node*)(intptr_t)parsing_heredoc_inf(p)->type;
  }
}
#define is_strterm_type(p,str_func) ((int)(intptr_t)((p)->lex_strterm->car) & (str_func))

// xxx -----------------------------



/* Line 189 of yacc.c  */
#line 1050 "C:/Personal/Git/mruby4VS/mruby/build/host/src/y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     keyword_class = 258,
     keyword_module = 259,
     keyword_def = 260,
     keyword_undef = 261,
     keyword_begin = 262,
     keyword_rescue = 263,
     keyword_ensure = 264,
     keyword_end = 265,
     keyword_if = 266,
     keyword_unless = 267,
     keyword_then = 268,
     keyword_elsif = 269,
     keyword_else = 270,
     keyword_case = 271,
     keyword_when = 272,
     keyword_while = 273,
     keyword_until = 274,
     keyword_for = 275,
     keyword_break = 276,
     keyword_next = 277,
     keyword_redo = 278,
     keyword_retry = 279,
     keyword_in = 280,
     keyword_do = 281,
     keyword_do_cond = 282,
     keyword_do_block = 283,
     keyword_do_LAMBDA = 284,
     keyword_return = 285,
     keyword_yield = 286,
     keyword_super = 287,
     keyword_self = 288,
     keyword_nil = 289,
     keyword_true = 290,
     keyword_false = 291,
     keyword_and = 292,
     keyword_or = 293,
     keyword_not = 294,
     modifier_if = 295,
     modifier_unless = 296,
     modifier_while = 297,
     modifier_until = 298,
     modifier_rescue = 299,
     keyword_alias = 300,
     keyword_BEGIN = 301,
     keyword_END = 302,
     keyword__LINE__ = 303,
     keyword__FILE__ = 304,
     keyword__ENCODING__ = 305,
     tIDENTIFIER = 306,
     tFID = 307,
     tGVAR = 308,
     tIVAR = 309,
     tCONSTANT = 310,
     tCVAR = 311,
     tLABEL = 312,
     tINTEGER = 313,
     tFLOAT = 314,
     tCHAR = 315,
     tXSTRING = 316,
     tREGEXP = 317,
     tSTRING = 318,
     tSTRING_PART = 319,
     tSTRING_MID = 320,
     tNTH_REF = 321,
     tBACK_REF = 322,
     tREGEXP_END = 323,
     tUPLUS = 324,
     tUMINUS = 325,
     tPOW = 326,
     tCMP = 327,
     tEQ = 328,
     tEQQ = 329,
     tNEQ = 330,
     tGEQ = 331,
     tLEQ = 332,
     tANDOP = 333,
     tOROP = 334,
     tMATCH = 335,
     tNMATCH = 336,
     tDOT2 = 337,
     tDOT3 = 338,
     tAREF = 339,
     tASET = 340,
     tLSHFT = 341,
     tRSHFT = 342,
     tCOLON2 = 343,
     tCOLON3 = 344,
     tOP_ASGN = 345,
     tASSOC = 346,
     tLPAREN = 347,
     tLPAREN_ARG = 348,
     tRPAREN = 349,
     tLBRACK = 350,
     tLBRACE = 351,
     tLBRACE_ARG = 352,
     tSTAR = 353,
     tAMPER = 354,
     tLAMBDA = 355,
     tSYMBEG = 356,
     tREGEXP_BEG = 357,
     tWORDS_BEG = 358,
     tSYMBOLS_BEG = 359,
     tSTRING_BEG = 360,
     tXSTRING_BEG = 361,
     tSTRING_DVAR = 362,
     tLAMBEG = 363,
     tHEREDOC_BEG = 364,
     tHEREDOC_END = 365,
     tLITERAL_DELIM = 366,
     tHD_LITERAL_DELIM = 367,
     tHD_STRING_PART = 368,
     tHD_STRING_MID = 369,
     tLOWEST = 370,
     tUMINUS_NUM = 371,
     idNULL = 372,
     idRespond_to = 373,
     idIFUNC = 374,
     idCFUNC = 375,
     id_core_set_method_alias = 376,
     id_core_set_variable_alias = 377,
     id_core_undef_method = 378,
     id_core_define_method = 379,
     id_core_define_singleton_method = 380,
     id_core_set_postexe = 381,
     tLAST_TOKEN = 382
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 987 "src/parse.y"

    node *nd;
    mrb_sym id;
    int num;
    unsigned int stack;
    const struct vtable *vars;



/* Line 214 of yacc.c  */
#line 1223 "C:/Personal/Git/mruby4VS/mruby/build/host/src/y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 1235 "C:/Personal/Git/mruby4VS/mruby/build/host/src/y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   11399

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  154
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  157
/* YYNRULES -- Number of rules.  */
#define YYNRULES  552
/* YYNRULES -- Number of states.  */
#define YYNSTATES  968

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   382

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     153,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   130,     2,     2,     2,   128,   123,     2,
     149,   150,   126,   124,   147,   125,   146,   127,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   118,   152,
     120,   116,   119,   117,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   145,     2,   151,   122,     2,   148,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   143,   121,   144,   131,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   129,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    12,    14,    18,    21,
      23,    24,    30,    35,    38,    40,    42,    46,    49,    50,
      55,    58,    62,    66,    70,    74,    78,    83,    85,    89,
      93,   100,   106,   112,   118,   124,   128,   132,   136,   140,
     142,   146,   150,   152,   156,   160,   164,   167,   169,   171,
     173,   175,   177,   182,   183,   189,   192,   196,   201,   207,
     212,   218,   221,   224,   227,   230,   233,   235,   239,   241,
     245,   247,   250,   254,   260,   263,   268,   271,   276,   278,
     282,   284,   288,   291,   295,   297,   300,   302,   307,   311,
     315,   319,   323,   326,   328,   330,   335,   339,   343,   347,
     351,   354,   356,   358,   360,   363,   365,   369,   371,   373,
     375,   377,   379,   381,   383,   385,   386,   391,   393,   395,
     397,   399,   401,   403,   405,   407,   409,   411,   413,   415,
     417,   419,   421,   423,   425,   427,   429,   431,   433,   435,
     437,   439,   441,   443,   445,   447,   449,   451,   453,   455,
     457,   459,   461,   463,   465,   467,   469,   471,   473,   475,
     477,   479,   481,   483,   485,   487,   489,   491,   493,   495,
     497,   499,   501,   503,   505,   507,   509,   511,   513,   515,
     517,   519,   521,   523,   525,   527,   529,   533,   539,   543,
     549,   556,   562,   568,   574,   580,   585,   589,   593,   597,
     601,   605,   609,   613,   617,   621,   626,   631,   634,   637,
     641,   645,   649,   653,   657,   661,   665,   669,   673,   677,
     681,   685,   689,   692,   695,   699,   703,   707,   711,   718,
     720,   722,   724,   727,   732,   735,   739,   741,   743,   745,
     747,   750,   755,   758,   760,   763,   766,   771,   773,   774,
     777,   780,   783,   785,   787,   790,   794,   799,   804,   810,
     814,   819,   822,   824,   826,   828,   830,   832,   834,   836,
     838,   839,   844,   845,   850,   851,   855,   859,   863,   866,
     870,   874,   876,   881,   885,   887,   892,   896,   899,   901,
     904,   905,   910,   917,   924,   925,   926,   934,   935,   936,
     944,   950,   955,   956,   957,   967,   968,   975,   976,   977,
     986,   987,   993,   994,  1001,  1002,  1003,  1013,  1015,  1017,
    1019,  1021,  1023,  1025,  1027,  1030,  1032,  1034,  1036,  1042,
    1044,  1047,  1049,  1051,  1053,  1057,  1059,  1063,  1065,  1070,
    1077,  1081,  1087,  1090,  1095,  1097,  1101,  1108,  1117,  1122,
    1129,  1134,  1137,  1144,  1147,  1152,  1159,  1162,  1167,  1170,
    1175,  1177,  1179,  1181,  1185,  1187,  1192,  1194,  1199,  1201,
    1205,  1207,  1209,  1214,  1216,  1220,  1224,  1225,  1231,  1234,
    1239,  1245,  1251,  1254,  1259,  1264,  1268,  1272,  1276,  1279,
    1281,  1286,  1287,  1293,  1294,  1300,  1306,  1308,  1310,  1317,
    1319,  1321,  1323,  1325,  1328,  1330,  1333,  1335,  1337,  1339,
    1341,  1343,  1345,  1347,  1350,  1354,  1356,  1359,  1361,  1362,
    1367,  1369,  1372,  1375,  1379,  1382,  1386,  1388,  1389,  1391,
    1393,  1396,  1398,  1401,  1403,  1406,  1408,  1409,  1414,  1417,
    1421,  1423,  1428,  1431,  1433,  1435,  1437,  1439,  1441,  1444,
    1447,  1451,  1453,  1455,  1458,  1461,  1463,  1465,  1467,  1469,
    1471,  1473,  1475,  1477,  1479,  1481,  1483,  1485,  1487,  1489,
    1491,  1493,  1494,  1499,  1502,  1506,  1509,  1516,  1525,  1530,
    1537,  1542,  1549,  1552,  1557,  1564,  1567,  1572,  1575,  1580,
    1582,  1583,  1585,  1587,  1589,  1591,  1593,  1595,  1597,  1601,
    1603,  1607,  1611,  1615,  1617,  1621,  1623,  1627,  1629,  1631,
    1634,  1636,  1638,  1640,  1643,  1646,  1648,  1650,  1651,  1656,
    1658,  1661,  1663,  1667,  1671,  1674,  1676,  1678,  1680,  1682,
    1684,  1686,  1688,  1690,  1692,  1694,  1696,  1698,  1699,  1701,
    1702,  1704,  1707,  1710,  1711,  1713,  1715,  1717,  1719,  1720,
    1724,  1726,  1729
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     155,     0,    -1,    -1,   156,   157,    -1,   158,   301,    -1,
     310,    -1,   159,    -1,   158,   309,   159,    -1,     1,   159,
      -1,   164,    -1,    -1,    46,   160,   143,   157,   144,    -1,
     162,   247,   225,   250,    -1,   163,   301,    -1,   310,    -1,
     164,    -1,   163,   309,   164,    -1,     1,   164,    -1,    -1,
      45,   185,   165,   185,    -1,     6,   186,    -1,   164,    40,
     168,    -1,   164,    41,   168,    -1,   164,    42,   168,    -1,
     164,    43,   168,    -1,   164,    44,   164,    -1,    47,   143,
     162,   144,    -1,   166,    -1,   174,   116,   169,    -1,   272,
      90,   169,    -1,   221,   145,   195,   304,    90,   169,    -1,
     221,   146,    51,    90,   169,    -1,   221,   146,    55,    90,
     169,    -1,   221,    88,    55,    90,   169,    -1,   221,    88,
      51,    90,   169,    -1,   274,    90,   169,    -1,   181,   116,
     202,    -1,   174,   116,   191,    -1,   174,   116,   202,    -1,
     167,    -1,   181,   116,   169,    -1,   181,   116,   166,    -1,
     169,    -1,   167,    37,   167,    -1,   167,    38,   167,    -1,
      39,   302,   167,    -1,   130,   169,    -1,   190,    -1,   167,
      -1,   173,    -1,   170,    -1,   240,    -1,   240,   300,   298,
     197,    -1,    -1,    97,   172,   231,   162,   144,    -1,   297,
     197,    -1,   297,   197,   171,    -1,   221,   146,   298,   197,
      -1,   221,   146,   298,   197,   171,    -1,   221,    88,   298,
     197,    -1,   221,    88,   298,   197,   171,    -1,    32,   197,
      -1,    31,   197,    -1,    30,   196,    -1,    21,   196,    -1,
      22,   196,    -1,   176,    -1,    92,   175,   303,    -1,   176,
      -1,    92,   175,   303,    -1,   178,    -1,   178,   177,    -1,
     178,    98,   180,    -1,   178,    98,   180,   147,   179,    -1,
     178,    98,    -1,   178,    98,   147,   179,    -1,    98,   180,
      -1,    98,   180,   147,   179,    -1,    98,    -1,    98,   147,
     179,    -1,   180,    -1,    92,   175,   303,    -1,   177,   147,
      -1,   178,   177,   147,    -1,   177,    -1,   178,   177,    -1,
     271,    -1,   221,   145,   195,   304,    -1,   221,   146,    51,
      -1,   221,    88,    51,    -1,   221,   146,    55,    -1,   221,
      88,    55,    -1,    89,    55,    -1,   274,    -1,   271,    -1,
     221,   145,   195,   304,    -1,   221,   146,    51,    -1,   221,
      88,    51,    -1,   221,   146,    55,    -1,   221,    88,    55,
      -1,    89,    55,    -1,   274,    -1,    51,    -1,    55,    -1,
      89,   182,    -1,   182,    -1,   221,    88,   182,    -1,    51,
      -1,    55,    -1,    52,    -1,   188,    -1,   189,    -1,   184,
      -1,   267,    -1,   185,    -1,    -1,   186,   147,   187,   185,
      -1,   121,    -1,   122,    -1,   123,    -1,    72,    -1,    73,
      -1,    74,    -1,    80,    -1,    81,    -1,   119,    -1,    76,
      -1,   120,    -1,    77,    -1,    75,    -1,    86,    -1,    87,
      -1,   124,    -1,   125,    -1,   126,    -1,    98,    -1,   127,
      -1,   128,    -1,    71,    -1,   130,    -1,   131,    -1,    69,
      -1,    70,    -1,    84,    -1,    85,    -1,   148,    -1,    48,
      -1,    49,    -1,    50,    -1,    46,    -1,    47,    -1,    45,
      -1,    37,    -1,     7,    -1,    21,    -1,    16,    -1,     3,
      -1,     5,    -1,    26,    -1,    15,    -1,    14,    -1,    10,
      -1,     9,    -1,    36,    -1,    20,    -1,    25,    -1,     4,
      -1,    22,    -1,    34,    -1,    39,    -1,    38,    -1,    23,
      -1,     8,    -1,    24,    -1,    30,    -1,    33,    -1,    32,
      -1,    13,    -1,    35,    -1,     6,    -1,    17,    -1,    31,
      -1,    11,    -1,    12,    -1,    18,    -1,    19,    -1,   181,
     116,   190,    -1,   181,   116,   190,    44,   190,    -1,   272,
      90,   190,    -1,   272,    90,   190,    44,   190,    -1,   221,
     145,   195,   304,    90,   190,    -1,   221,   146,    51,    90,
     190,    -1,   221,   146,    55,    90,   190,    -1,   221,    88,
      51,    90,   190,    -1,   221,    88,    55,    90,   190,    -1,
      89,    55,    90,   190,    -1,   274,    90,   190,    -1,   190,
      82,   190,    -1,   190,    83,   190,    -1,   190,   124,   190,
      -1,   190,   125,   190,    -1,   190,   126,   190,    -1,   190,
     127,   190,    -1,   190,   128,   190,    -1,   190,    71,   190,
      -1,   129,    58,    71,   190,    -1,   129,    59,    71,   190,
      -1,    69,   190,    -1,    70,   190,    -1,   190,   121,   190,
      -1,   190,   122,   190,    -1,   190,   123,   190,    -1,   190,
      72,   190,    -1,   190,   119,   190,    -1,   190,    76,   190,
      -1,   190,   120,   190,    -1,   190,    77,   190,    -1,   190,
      73,   190,    -1,   190,    74,   190,    -1,   190,    75,   190,
      -1,   190,    80,   190,    -1,   190,    81,   190,    -1,   130,
     190,    -1,   131,   190,    -1,   190,    86,   190,    -1,   190,
      87,   190,    -1,   190,    78,   190,    -1,   190,    79,   190,
      -1,   190,   117,   190,   302,   118,   190,    -1,   203,    -1,
     190,    -1,   310,    -1,   201,   305,    -1,   201,   147,   295,
     305,    -1,   295,   305,    -1,   149,   195,   303,    -1,   310,
      -1,   193,    -1,   310,    -1,   196,    -1,   201,   147,    -1,
     201,   147,   295,   147,    -1,   295,   147,    -1,   173,    -1,
     201,   200,    -1,   295,   200,    -1,   201,   147,   295,   200,
      -1,   199,    -1,    -1,   198,   196,    -1,    99,   191,    -1,
     147,   199,    -1,   310,    -1,   191,    -1,    98,   191,    -1,
     201,   147,   191,    -1,   201,   147,    98,   191,    -1,   201,
     147,   260,   191,    -1,   201,   147,   260,    98,   191,    -1,
     201,   147,   191,    -1,   201,   147,    98,   191,    -1,    98,
     191,    -1,   251,    -1,   252,    -1,   256,    -1,   257,    -1,
     258,    -1,   273,    -1,   274,    -1,    52,    -1,    -1,     7,
     204,   161,    10,    -1,    -1,    93,   167,   205,   303,    -1,
      -1,    93,   206,   303,    -1,    92,   162,   150,    -1,   221,
      88,    55,    -1,    89,    55,    -1,    95,   192,   151,    -1,
      96,   294,   144,    -1,    30,    -1,    31,   149,   196,   303,
      -1,    31,   149,   303,    -1,    31,    -1,    39,   149,   167,
     303,    -1,    39,   149,   303,    -1,   297,   242,    -1,   241,
      -1,   241,   242,    -1,    -1,   100,   207,   236,   237,    -1,
      11,   168,   222,   162,   224,    10,    -1,    12,   168,   222,
     162,   225,    10,    -1,    -1,    -1,    18,   208,   168,   223,
     209,   162,    10,    -1,    -1,    -1,    19,   210,   168,   223,
     211,   162,    10,    -1,    16,   168,   301,   245,    10,    -1,
      16,   301,   245,    10,    -1,    -1,    -1,    20,   226,    25,
     212,   168,   223,   213,   162,    10,    -1,    -1,     3,   183,
     275,   214,   161,    10,    -1,    -1,    -1,     3,    86,   167,
     215,   306,   216,   161,    10,    -1,    -1,     4,   183,   217,
     161,    10,    -1,    -1,     5,   184,   218,   277,   161,    10,
      -1,    -1,    -1,     5,   292,   300,   219,   184,   220,   277,
     161,    10,    -1,    21,    -1,    22,    -1,    23,    -1,    24,
      -1,   203,    -1,   306,    -1,    13,    -1,   306,    13,    -1,
     306,    -1,    27,    -1,   225,    -1,    14,   168,   222,   162,
     224,    -1,   310,    -1,    15,   162,    -1,   181,    -1,   174,
      -1,   280,    -1,    92,   229,   303,    -1,   227,    -1,   228,
     147,   227,    -1,   228,    -1,   228,   147,    98,   280,    -1,
     228,   147,    98,   280,   147,   228,    -1,   228,   147,    98,
      -1,   228,   147,    98,   147,   228,    -1,    98,   280,    -1,
      98,   280,   147,   228,    -1,    98,    -1,    98,   147,   228,
      -1,   282,   147,   285,   147,   288,   291,    -1,   282,   147,
     285,   147,   288,   147,   282,   291,    -1,   282,   147,   285,
     291,    -1,   282,   147,   285,   147,   282,   291,    -1,   282,
     147,   288,   291,    -1,   282,   147,    -1,   282,   147,   288,
     147,   282,   291,    -1,   282,   291,    -1,   285,   147,   288,
     291,    -1,   285,   147,   288,   147,   282,   291,    -1,   285,
     291,    -1,   285,   147,   282,   291,    -1,   288,   291,    -1,
     288,   147,   282,   291,    -1,   290,    -1,   310,    -1,   232,
      -1,   121,   233,   121,    -1,    79,    -1,   121,   230,   233,
     121,    -1,   302,    -1,   302,   152,   234,   302,    -1,   235,
      -1,   234,   147,   235,    -1,    51,    -1,   279,    -1,   149,
     278,   233,   150,    -1,   278,    -1,   108,   162,   144,    -1,
      29,   162,    10,    -1,    -1,    28,   239,   231,   162,    10,
      -1,   173,   238,    -1,   240,   300,   298,   194,    -1,   240,
     300,   298,   194,   242,    -1,   240,   300,   298,   197,   238,
      -1,   297,   193,    -1,   221,   146,   298,   194,    -1,   221,
      88,   298,   193,    -1,   221,    88,   299,    -1,   221,   146,
     193,    -1,   221,    88,   193,    -1,    32,   193,    -1,    32,
      -1,   221,   145,   195,   304,    -1,    -1,   143,   243,   231,
     162,   144,    -1,    -1,    26,   244,   231,   162,    10,    -1,
      17,   201,   222,   162,   246,    -1,   225,    -1,   245,    -1,
       8,   248,   249,   222,   162,   247,    -1,   310,    -1,   191,
      -1,   202,    -1,   310,    -1,    91,   181,    -1,   310,    -1,
       9,   162,    -1,   310,    -1,   270,    -1,   266,    -1,   265,
      -1,   269,    -1,    60,    -1,    63,    -1,   105,    63,    -1,
     105,   253,    63,    -1,   254,    -1,   253,   254,    -1,    65,
      -1,    -1,    64,   255,   162,   144,    -1,   111,    -1,   112,
     260,    -1,   106,    61,    -1,   106,   253,    61,    -1,   102,
      62,    -1,   102,   253,    62,    -1,   109,    -1,    -1,   260,
      -1,   261,    -1,   260,   261,    -1,   110,    -1,   262,   110,
      -1,   263,    -1,   262,   263,    -1,   114,    -1,    -1,   113,
     264,   162,   144,    -1,   103,    63,    -1,   103,   253,    63,
      -1,   267,    -1,   101,   105,   254,    63,    -1,   101,   268,
      -1,   184,    -1,    54,    -1,    53,    -1,    56,    -1,    63,
      -1,   105,    63,    -1,   104,    63,    -1,   104,   253,    63,
      -1,    58,    -1,    59,    -1,   129,    58,    -1,   129,    59,
      -1,    51,    -1,    54,    -1,    53,    -1,    56,    -1,    55,
      -1,   271,    -1,   271,    -1,    34,    -1,    33,    -1,    35,
      -1,    36,    -1,    49,    -1,    48,    -1,    66,    -1,    67,
      -1,   306,    -1,    -1,   120,   276,   168,   306,    -1,     1,
     306,    -1,   149,   278,   303,    -1,   278,   306,    -1,   282,
     147,   286,   147,   288,   291,    -1,   282,   147,   286,   147,
     288,   147,   282,   291,    -1,   282,   147,   286,   291,    -1,
     282,   147,   286,   147,   282,   291,    -1,   282,   147,   288,
     291,    -1,   282,   147,   288,   147,   282,   291,    -1,   282,
     291,    -1,   286,   147,   288,   291,    -1,   286,   147,   288,
     147,   282,   291,    -1,   286,   291,    -1,   286,   147,   282,
     291,    -1,   288,   291,    -1,   288,   147,   282,   291,    -1,
     290,    -1,    -1,    55,    -1,    54,    -1,    53,    -1,    56,
      -1,   279,    -1,    51,    -1,   280,    -1,    92,   229,   303,
      -1,   281,    -1,   282,   147,   281,    -1,    51,   116,   191,
      -1,    51,   116,   221,    -1,   284,    -1,   285,   147,   284,
      -1,   283,    -1,   286,   147,   283,    -1,   126,    -1,    98,
      -1,   287,    51,    -1,   287,    -1,   123,    -1,    99,    -1,
     289,    51,    -1,   147,   290,    -1,   310,    -1,   273,    -1,
      -1,   149,   293,   167,   303,    -1,   310,    -1,   295,   305,
      -1,   296,    -1,   295,   147,   296,    -1,   191,    91,   191,
      -1,    57,   191,    -1,    51,    -1,    55,    -1,    52,    -1,
      51,    -1,    55,    -1,    52,    -1,   188,    -1,    51,    -1,
      52,    -1,   188,    -1,   146,    -1,    88,    -1,    -1,   309,
      -1,    -1,   307,    -1,   302,   150,    -1,   302,   151,    -1,
      -1,   307,    -1,   147,    -1,   152,    -1,   307,    -1,    -1,
     153,   308,   259,    -1,   306,    -1,   309,   152,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,  1146,  1146,  1146,  1156,  1162,  1166,  1170,  1174,  1180,
    1182,  1181,  1193,  1219,  1225,  1229,  1233,  1237,  1243,  1243,
    1247,  1251,  1255,  1259,  1263,  1267,  1271,  1276,  1277,  1281,
    1285,  1289,  1293,  1297,  1302,  1306,  1311,  1315,  1319,  1323,
    1326,  1330,  1337,  1338,  1342,  1346,  1350,  1354,  1357,  1364,
    1365,  1368,  1369,  1373,  1372,  1385,  1389,  1394,  1398,  1403,
    1407,  1412,  1416,  1420,  1424,  1428,  1434,  1438,  1444,  1445,
    1451,  1455,  1459,  1463,  1467,  1471,  1475,  1479,  1483,  1487,
    1493,  1494,  1500,  1504,  1510,  1514,  1520,  1524,  1528,  1532,
    1536,  1540,  1546,  1552,  1559,  1563,  1567,  1571,  1575,  1579,
    1585,  1591,  1598,  1602,  1605,  1609,  1613,  1619,  1620,  1621,
    1622,  1627,  1634,  1635,  1638,  1642,  1642,  1648,  1649,  1650,
    1651,  1652,  1653,  1654,  1655,  1656,  1657,  1658,  1659,  1660,
    1661,  1662,  1663,  1664,  1665,  1666,  1667,  1668,  1669,  1670,
    1671,  1672,  1673,  1674,  1675,  1676,  1679,  1679,  1679,  1680,
    1680,  1681,  1681,  1681,  1682,  1682,  1682,  1682,  1683,  1683,
    1683,  1684,  1684,  1684,  1685,  1685,  1685,  1685,  1686,  1686,
    1686,  1686,  1687,  1687,  1687,  1687,  1688,  1688,  1688,  1688,
    1689,  1689,  1689,  1689,  1690,  1690,  1693,  1697,  1701,  1705,
    1709,  1713,  1717,  1721,  1725,  1730,  1735,  1740,  1744,  1748,
    1752,  1756,  1760,  1764,  1768,  1772,  1776,  1780,  1784,  1788,
    1792,  1796,  1800,  1804,  1808,  1812,  1816,  1820,  1824,  1828,
    1832,  1836,  1840,  1844,  1848,  1852,  1856,  1860,  1864,  1868,
    1874,  1881,  1882,  1886,  1890,  1896,  1902,  1903,  1906,  1907,
    1908,  1912,  1916,  1922,  1926,  1930,  1934,  1938,  1944,  1944,
    1955,  1961,  1965,  1971,  1975,  1979,  1983,  1987,  1991,  1997,
    2001,  2005,  2011,  2012,  2013,  2014,  2015,  2016,  2017,  2018,
    2023,  2022,  2033,  2033,  2037,  2037,  2041,  2045,  2049,  2053,
    2057,  2061,  2065,  2069,  2073,  2077,  2081,  2085,  2089,  2090,
    2096,  2095,  2108,  2115,  2122,  2122,  2122,  2128,  2128,  2128,
    2134,  2140,  2145,  2147,  2144,  2154,  2153,  2166,  2171,  2165,
    2184,  2183,  2196,  2195,  2208,  2209,  2208,  2222,  2226,  2230,
    2234,  2240,  2247,  2248,  2249,  2252,  2253,  2256,  2257,  2265,
    2266,  2272,  2276,  2279,  2283,  2289,  2293,  2299,  2303,  2307,
    2311,  2315,  2319,  2323,  2327,  2331,  2337,  2341,  2345,  2349,
    2353,  2357,  2361,  2365,  2369,  2373,  2377,  2381,  2385,  2389,
    2393,  2399,  2400,  2407,  2412,  2417,  2424,  2428,  2434,  2435,
    2438,  2443,  2446,  2450,  2456,  2460,  2467,  2466,  2479,  2489,
    2493,  2498,  2505,  2509,  2513,  2517,  2521,  2525,  2529,  2533,
    2537,  2544,  2543,  2554,  2553,  2565,  2573,  2582,  2585,  2592,
    2595,  2599,  2600,  2603,  2607,  2610,  2614,  2617,  2618,  2619,
    2620,  2623,  2624,  2625,  2629,  2635,  2636,  2642,  2647,  2646,
    2657,  2661,  2667,  2671,  2677,  2681,  2687,  2690,  2691,  2694,
    2695,  2698,  2704,  2710,  2711,  2714,  2721,  2720,  2734,  2738,
    2745,  2749,  2756,  2763,  2764,  2765,  2766,  2767,  2771,  2777,
    2781,  2787,  2788,  2789,  2793,  2799,  2803,  2807,  2811,  2815,
    2821,  2827,  2831,  2835,  2839,  2843,  2847,  2854,  2863,  2864,
    2867,  2872,  2871,  2880,  2887,  2893,  2899,  2903,  2907,  2911,
    2915,  2919,  2923,  2927,  2931,  2935,  2939,  2943,  2947,  2951,
    2956,  2962,  2967,  2972,  2977,  2984,  2988,  2995,  2999,  3005,
    3009,  3015,  3022,  3029,  3033,  3039,  3043,  3049,  3050,  3053,
    3058,  3065,  3066,  3069,  3076,  3080,  3087,  3092,  3092,  3117,
    3118,  3124,  3128,  3134,  3138,  3144,  3145,  3146,  3149,  3150,
    3151,  3152,  3155,  3156,  3157,  3160,  3161,  3164,  3165,  3168,
    3169,  3172,  3175,  3178,  3179,  3180,  3183,  3184,  3188,  3187,
    3194,  3195,  3199
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "keyword_class", "keyword_module",
  "keyword_def", "keyword_undef", "keyword_begin", "keyword_rescue",
  "keyword_ensure", "keyword_end", "keyword_if", "keyword_unless",
  "keyword_then", "keyword_elsif", "keyword_else", "keyword_case",
  "keyword_when", "keyword_while", "keyword_until", "keyword_for",
  "keyword_break", "keyword_next", "keyword_redo", "keyword_retry",
  "keyword_in", "keyword_do", "keyword_do_cond", "keyword_do_block",
  "keyword_do_LAMBDA", "keyword_return", "keyword_yield", "keyword_super",
  "keyword_self", "keyword_nil", "keyword_true", "keyword_false",
  "keyword_and", "keyword_or", "keyword_not", "modifier_if",
  "modifier_unless", "modifier_while", "modifier_until", "modifier_rescue",
  "keyword_alias", "keyword_BEGIN", "keyword_END", "keyword__LINE__",
  "keyword__FILE__", "keyword__ENCODING__", "tIDENTIFIER", "tFID", "tGVAR",
  "tIVAR", "tCONSTANT", "tCVAR", "tLABEL", "tINTEGER", "tFLOAT", "tCHAR",
  "tXSTRING", "tREGEXP", "tSTRING", "tSTRING_PART", "tSTRING_MID",
  "tNTH_REF", "tBACK_REF", "tREGEXP_END", "tUPLUS", "tUMINUS", "tPOW",
  "tCMP", "tEQ", "tEQQ", "tNEQ", "tGEQ", "tLEQ", "tANDOP", "tOROP",
  "tMATCH", "tNMATCH", "tDOT2", "tDOT3", "tAREF", "tASET", "tLSHFT",
  "tRSHFT", "tCOLON2", "tCOLON3", "tOP_ASGN", "tASSOC", "tLPAREN",
  "tLPAREN_ARG", "tRPAREN", "tLBRACK", "tLBRACE", "tLBRACE_ARG", "tSTAR",
  "tAMPER", "tLAMBDA", "tSYMBEG", "tREGEXP_BEG", "tWORDS_BEG",
  "tSYMBOLS_BEG", "tSTRING_BEG", "tXSTRING_BEG", "tSTRING_DVAR", "tLAMBEG",
  "tHEREDOC_BEG", "tHEREDOC_END", "tLITERAL_DELIM", "tHD_LITERAL_DELIM",
  "tHD_STRING_PART", "tHD_STRING_MID", "tLOWEST", "'='", "'?'", "':'",
  "'>'", "'<'", "'|'", "'^'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "tUMINUS_NUM", "'!'", "'~'", "idNULL", "idRespond_to", "idIFUNC",
  "idCFUNC", "id_core_set_method_alias", "id_core_set_variable_alias",
  "id_core_undef_method", "id_core_define_method",
  "id_core_define_singleton_method", "id_core_set_postexe", "tLAST_TOKEN",
  "'{'", "'}'", "'['", "'.'", "','", "'`'", "'('", "')'", "']'", "';'",
  "'\\n'", "$accept", "program", "$@1", "top_compstmt", "top_stmts",
  "top_stmt", "@2", "bodystmt", "compstmt", "stmts", "stmt", "$@3",
  "command_asgn", "expr", "expr_value", "command_call", "block_command",
  "cmd_brace_block", "$@4", "command", "mlhs", "mlhs_inner", "mlhs_basic",
  "mlhs_item", "mlhs_list", "mlhs_post", "mlhs_node", "lhs", "cname",
  "cpath", "fname", "fsym", "undef_list", "$@5", "op", "reswords", "arg",
  "arg_value", "aref_args", "paren_args", "opt_paren_args",
  "opt_call_args", "call_args", "command_args", "@6", "block_arg",
  "opt_block_arg", "args", "mrhs", "primary", "$@7", "$@8", "$@9", "@10",
  "$@11", "$@12", "$@13", "$@14", "$@15", "$@16", "@17", "@18", "@19",
  "@20", "@21", "$@22", "@23", "primary_value", "then", "do", "if_tail",
  "opt_else", "for_var", "f_marg", "f_marg_list", "f_margs", "block_param",
  "opt_block_param", "block_param_def", "opt_bv_decl", "bv_decls", "bvar",
  "f_larglist", "lambda_body", "do_block", "$@24", "block_call",
  "method_call", "brace_block", "$@25", "$@26", "case_body", "cases",
  "opt_rescue", "exc_list", "exc_var", "opt_ensure", "literal", "string",
  "string_rep", "string_interp", "@27", "xstring", "regexp", "heredoc",
  "opt_heredoc_bodies", "heredoc_bodies", "heredoc_body",
  "heredoc_string_rep", "heredoc_string_interp", "@28", "words", "symbol",
  "basic_symbol", "sym", "symbols", "numeric", "variable", "var_lhs",
  "var_ref", "backref", "superclass", "$@29", "f_arglist", "f_args",
  "f_bad_arg", "f_norm_arg", "f_arg_item", "f_arg", "f_opt", "f_block_opt",
  "f_block_optarg", "f_optarg", "restarg_mark", "f_rest_arg",
  "blkarg_mark", "f_block_arg", "opt_f_block_arg", "singleton", "$@30",
  "assoc_list", "assocs", "assoc", "operation", "operation2", "operation3",
  "dot_or_colon", "opt_terms", "opt_nl", "rparen", "rbracket", "trailer",
  "term", "nl", "$@31", "terms", "none", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,    61,    63,    58,    62,
      60,   124,    94,    38,    43,    45,    42,    47,    37,   371,
      33,   126,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   123,   125,    91,    46,    44,    96,    40,
      41,    93,    59,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   154,   156,   155,   157,   158,   158,   158,   158,   159,
     160,   159,   161,   162,   163,   163,   163,   163,   165,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     166,   166,   167,   167,   167,   167,   167,   167,   168,   169,
     169,   170,   170,   172,   171,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   174,   174,   175,   175,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     177,   177,   178,   178,   179,   179,   180,   180,   180,   180,
     180,   180,   180,   180,   181,   181,   181,   181,   181,   181,
     181,   181,   182,   182,   183,   183,   183,   184,   184,   184,
     184,   184,   185,   185,   186,   187,   186,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     191,   192,   192,   192,   192,   193,   194,   194,   195,   195,
     195,   195,   195,   196,   196,   196,   196,   196,   198,   197,
     199,   200,   200,   201,   201,   201,   201,   201,   201,   202,
     202,   202,   203,   203,   203,   203,   203,   203,   203,   203,
     204,   203,   205,   203,   206,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     207,   203,   203,   203,   208,   209,   203,   210,   211,   203,
     203,   203,   212,   213,   203,   214,   203,   215,   216,   203,
     217,   203,   218,   203,   219,   220,   203,   203,   203,   203,
     203,   221,   222,   222,   222,   223,   223,   224,   224,   225,
     225,   226,   226,   227,   227,   228,   228,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   231,   231,   232,   232,   232,   233,   233,   234,   234,
     235,   235,   236,   236,   237,   237,   239,   238,   240,   240,
     240,   240,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   243,   242,   244,   242,   245,   246,   246,   247,   247,
     248,   248,   248,   249,   249,   250,   250,   251,   251,   251,
     251,   252,   252,   252,   252,   253,   253,   254,   255,   254,
     254,   254,   256,   256,   257,   257,   258,   259,   259,   260,
     260,   261,   261,   262,   262,   263,   264,   263,   265,   265,
     266,   266,   267,   268,   268,   268,   268,   268,   268,   269,
     269,   270,   270,   270,   270,   271,   271,   271,   271,   271,
     272,   273,   273,   273,   273,   273,   273,   273,   274,   274,
     275,   276,   275,   275,   277,   277,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   279,   279,   279,   279,   280,   280,   281,   281,   282,
     282,   283,   284,   285,   285,   286,   286,   287,   287,   288,
     288,   289,   289,   290,   291,   291,   292,   293,   292,   294,
     294,   295,   295,   296,   296,   297,   297,   297,   298,   298,
     298,   298,   299,   299,   299,   300,   300,   301,   301,   302,
     302,   303,   304,   305,   305,   305,   306,   306,   308,   307,
     309,   309,   310
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     3,     2,     1,
       0,     5,     4,     2,     1,     1,     3,     2,     0,     4,
       2,     3,     3,     3,     3,     3,     4,     1,     3,     3,
       6,     5,     5,     5,     5,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     2,     1,     1,     1,
       1,     1,     4,     0,     5,     2,     3,     4,     5,     4,
       5,     2,     2,     2,     2,     2,     1,     3,     1,     3,
       1,     2,     3,     5,     2,     4,     2,     4,     1,     3,
       1,     3,     2,     3,     1,     2,     1,     4,     3,     3,
       3,     3,     2,     1,     1,     4,     3,     3,     3,     3,
       2,     1,     1,     1,     2,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     5,     3,     5,
       6,     5,     5,     5,     5,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     4,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     3,     3,     3,     6,     1,
       1,     1,     2,     4,     2,     3,     1,     1,     1,     1,
       2,     4,     2,     1,     2,     2,     4,     1,     0,     2,
       2,     2,     1,     1,     2,     3,     4,     4,     5,     3,
       4,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     3,     3,     3,     2,     3,
       3,     1,     4,     3,     1,     4,     3,     2,     1,     2,
       0,     4,     6,     6,     0,     0,     7,     0,     0,     7,
       5,     4,     0,     0,     9,     0,     6,     0,     0,     8,
       0,     5,     0,     6,     0,     0,     9,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     5,     1,
       2,     1,     1,     1,     3,     1,     3,     1,     4,     6,
       3,     5,     2,     4,     1,     3,     6,     8,     4,     6,
       4,     2,     6,     2,     4,     6,     2,     4,     2,     4,
       1,     1,     1,     3,     1,     4,     1,     4,     1,     3,
       1,     1,     4,     1,     3,     3,     0,     5,     2,     4,
       5,     5,     2,     4,     4,     3,     3,     3,     2,     1,
       4,     0,     5,     0,     5,     5,     1,     1,     6,     1,
       1,     1,     1,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     1,     2,     1,     0,     4,
       1,     2,     2,     3,     2,     3,     1,     0,     1,     1,
       2,     1,     2,     1,     2,     1,     0,     4,     2,     3,
       1,     4,     2,     1,     1,     1,     1,     1,     2,     2,
       3,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     2,     3,     2,     6,     8,     4,     6,
       4,     6,     2,     4,     6,     2,     4,     2,     4,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     3,     3,     1,     3,     1,     3,     1,     1,     2,
       1,     1,     1,     2,     2,     1,     1,     0,     4,     1,
       2,     1,     3,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     0,
       1,     2,     2,     0,     1,     1,     1,     1,     0,     3,
       1,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     0,     0,   270,
       0,     0,   537,   294,   297,     0,   317,   318,   319,   320,
     281,   248,   248,   463,   462,   464,   465,   539,     0,    10,
       0,   467,   466,   455,   527,   457,   456,   459,   458,   451,
     452,   411,   412,   468,   469,     0,     0,     0,     0,   274,
     552,   552,    78,   290,     0,     0,     0,     0,     0,     0,
     426,     0,     0,     0,     3,   537,     6,     9,    27,    39,
      42,    50,    49,     0,    66,     0,    70,    80,     0,    47,
     229,     0,    51,   288,   262,   263,   264,   265,   266,   409,
     408,   440,   410,   407,   461,     0,   267,   268,   248,     5,
       8,   317,   318,   281,   284,   389,     0,   102,   103,     0,
       0,     0,     0,   105,     0,   321,     0,   461,   268,     0,
     310,   156,   166,   157,   179,   153,   172,   162,   161,   182,
     183,   177,   160,   159,   155,   180,   184,   185,   164,   154,
     167,   171,   173,   165,   158,   174,   181,   176,   175,   168,
     178,   163,   152,   170,   169,   151,   149,   150,   146,   147,
     148,   107,   109,   108,   141,   142,   138,   120,   121,   122,
     129,   126,   128,   123,   124,   143,   144,   130,   131,   135,
     125,   127,   117,   118,   119,   132,   133,   134,   136,   137,
     139,   140,   145,   517,   312,   110,   111,   516,     0,   175,
     168,   178,   163,   146,   147,   107,   108,     0,   112,   114,
      20,   113,     0,     0,    48,     0,     0,     0,   461,     0,
     268,     0,   546,   548,   537,     0,   550,   547,   538,     0,
       0,     0,   332,   331,     0,     0,   461,   268,     0,     0,
       0,     0,   243,   230,   253,    64,   247,   552,   552,   521,
      65,    63,   539,    62,     0,   552,   388,    61,   539,     0,
     540,    18,     0,     0,   207,     0,   208,   278,     0,     0,
       0,   537,    15,   539,    68,    14,   272,   539,     0,   543,
     543,   231,     0,     0,   543,   519,     0,     0,    76,     0,
      86,    93,   490,   445,   444,   446,   447,     0,   443,   442,
     424,   418,   417,   420,     0,     0,   415,   438,     0,   449,
       0,   413,     0,   422,     0,   453,   454,    46,   222,   223,
       4,   538,     0,     0,     0,     0,     0,     0,     0,   376,
     378,     0,    82,     0,    74,    71,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   552,     0,   536,   535,     0,   393,
     391,   289,     0,     0,   382,    55,   287,   307,   102,   103,
     104,   453,   454,     0,   471,   305,   470,     0,   552,     0,
       0,     0,   490,   314,     0,   115,     0,   552,   278,   323,
       0,   322,     0,     0,   552,     0,     0,     0,     0,   427,
       0,     0,     0,   551,     0,     0,   278,     0,   552,     0,
     302,   524,   254,   250,     0,     0,   244,   252,     0,   245,
     539,     0,   283,   249,   539,   239,   552,   552,   238,   539,
     286,    45,     0,     0,     0,     0,     0,     0,    17,   539,
     276,    13,   538,    67,   539,   275,   279,   545,   232,   544,
     545,   234,   280,   520,    92,    84,     0,    79,     0,     0,
     552,     0,   496,   493,   492,   491,   494,     0,   508,   512,
     511,   507,   490,     0,   373,   495,   497,   499,   552,   505,
     552,   510,   552,     0,   489,   448,     0,     0,   431,   436,
     435,   421,   429,     0,   433,   425,   416,   439,   450,   414,
     423,     0,     0,     7,    21,    22,    23,    24,    25,    43,
      44,   552,     0,    28,    37,     0,    38,   539,     0,    72,
      83,    41,    40,     0,   186,   253,    36,   204,   212,   217,
     218,   219,   214,   216,   226,   227,   220,   221,   197,   198,
     224,   225,   539,   213,   215,   209,   210,   211,   199,   200,
     201,   202,   203,   528,   533,   529,   534,   387,   248,   385,
     539,   528,   530,   529,   531,   386,   248,   528,   529,   248,
     552,   552,    29,   188,    35,   196,    53,    56,     0,   473,
       0,     0,   102,   103,   106,     0,   539,   552,     0,   539,
     490,     0,     0,     0,     0,   271,   552,   552,   399,   552,
     324,   186,   532,   529,   539,   528,   529,   552,   549,   428,
       0,     0,   301,   326,   295,   325,   298,   532,   277,   539,
     528,   529,     0,   523,     0,   255,   251,     0,   552,   522,
     282,   541,   235,   240,   242,   285,    19,     0,    26,   195,
      69,    16,   273,   543,    85,    77,    89,    91,   539,   528,
     529,     0,   496,     0,   344,   335,   337,   539,   333,   539,
       0,     0,   291,     0,   482,   515,     0,   485,   509,     0,
     487,   513,   441,     0,     0,   430,   432,   434,   205,   206,
     364,   539,     0,   362,   361,   261,     0,    81,    75,     0,
       0,     0,     0,     0,     0,   384,    59,     0,   390,     0,
       0,   237,   383,    57,   236,   379,    52,     0,     0,     0,
     552,   308,     0,     0,   390,   311,   518,   539,     0,   475,
     315,   116,   400,   401,   552,   402,     0,   552,   329,     0,
       0,   327,     0,     0,   390,     0,     0,     0,   300,     0,
       0,     0,     0,   390,     0,   256,     0,   257,   246,   552,
      11,   233,    87,   501,   539,     0,   342,     0,   498,     0,
     366,     0,     0,   500,   552,   552,   514,   552,   506,   552,
     552,   419,     0,   496,   539,     0,   552,   503,   552,   552,
     360,     0,     0,   259,    73,   187,     0,    34,   193,    33,
     194,    60,   542,     0,    31,   191,    32,   192,    58,   380,
     381,     0,     0,   189,     0,     0,   472,   306,   474,   313,
     490,     0,     0,   404,   330,     0,    12,   406,     0,   292,
       0,   293,   255,   552,     0,     0,   303,   258,   241,   334,
     345,     0,   340,   336,   372,     0,   375,   374,     0,   478,
       0,   480,     0,   486,     0,   483,   488,   437,     0,     0,
     363,   351,   353,     0,   356,     0,   358,   377,   260,   228,
      30,   190,   394,   392,     0,     0,     0,     0,   403,     0,
      94,   101,     0,   405,     0,   396,   397,   395,   296,   299,
       0,     0,   343,     0,   338,   370,   539,   368,   371,   552,
     552,   552,   552,     0,   502,   365,   552,   552,   552,   504,
     552,   552,    54,   309,     0,   100,     0,   552,     0,   552,
     552,     0,   341,     0,     0,   367,   479,     0,   476,   481,
     484,   278,     0,     0,   348,     0,   350,   357,     0,   354,
     359,   316,   532,    99,   539,   528,   529,   398,   328,   304,
     339,   369,   552,   532,   277,   552,   552,   552,   552,   390,
     477,   349,     0,   346,   352,   355,   552,   347
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    64,    65,    66,   262,   396,   397,   271,
     272,   442,    68,    69,   215,    70,    71,   587,   720,    72,
      73,   273,    74,    75,    76,   467,    77,   216,   113,   114,
     208,   209,   210,   604,   195,   196,    79,   244,   278,   567,
     712,   434,   435,   253,   254,   246,   426,   436,   526,    80,
     212,   454,   277,   292,   229,   751,   230,   752,   632,   890,
     591,   588,   815,   390,   392,   603,   820,   265,   400,   624,
     740,   741,   235,   665,   666,   667,   784,   692,   693,   769,
     896,   897,   483,   672,   330,   521,    82,    83,   376,   581,
     580,   412,   887,   607,   734,   822,   826,    84,    85,   305,
     306,   497,    86,    87,    88,   618,   637,   502,   503,   504,
     684,    89,    90,    91,   299,    92,    93,   218,   219,    96,
     220,   385,   590,   601,   602,   485,   486,   487,   488,   489,
     787,   788,   490,   491,   492,   493,   776,   674,   198,   391,
     283,   437,   249,   119,   595,   569,   368,   225,   431,   432,
     708,   458,   401,   260,   409,   228,   275
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -766
static const yytype_int16 yypact[] =
{
    -766,   139,  1626,  -766,  7609,  9465,  9801,  5895,  6978,  -766,
    9117,  9117,  5356,  -766,  -766,  9577,  8305,  8305,  -766,  -766,
    8305,  3464,  3020,  -766,  -766,  -766,  -766,    70,  6978,  -766,
      -1,  -766,  -766,  6029,  3168,  -766,  -766,  6163,  -766,  -766,
    -766,  -766,  -766,  -766,  -766,  9233,  9233,    97,  4652,  9117,
    8421,  8653,  7255,  -766,  6686,   685,   718,   859,   903,   569,
    -766,   124,  9349,  9233,  -766,    42,  -766,  1039,  -766,   306,
    -766,  -766,   131,    68,  -766,   128,  9689,  -766,   188,  3147,
      11,   229,    16,    59,  -766,  -766,  -766,  -766,  -766,  -766,
    -766,  -766,  -766,  -766,   375,   219,  -766,   547,   111,  -766,
    -766,  -766,  -766,  -766,   162,   175,   180,   233,   284,  9117,
     281,  4805,   305,  -766,    38,  -766,   267,  -766,  -766,   111,
    -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,
    -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,
    -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,    43,    47,
      85,   137,  -766,  -766,  -766,  -766,  -766,  -766,   212,   220,
    -766,   234,  -766,   238,  -766,  -766,  -766,  -766,  -766,  -766,
    -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,
    -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,
    -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,    16,  -766,
    -766,  -766,  -766,  -766,  -766,  -766,  -766,  6832,  -766,  -766,
     167,  -766,  3801,   291,   306,    56,   255,   399,    25,   295,
      28,    56,  -766,  -766,    42,   371,  -766,  -766,   242,  9117,
    9117,   355,  -766,  -766,   404,   395,    94,   102,  9233,  9233,
    9233,  9233,  -766,  3147,   335,  -766,  -766,   292,   293,  -766,
    -766,  -766,  5240,  -766,  8305,  8305,  -766,  -766,  5494,  9117,
    -766,  -766,   285,  4958,  -766,   418,   372,   553,  7841,  4652,
     300,    42,  1039,   303,   342,  -766,   306,   303,   310,   165,
     178,  -766,   335,   329,   178,  -766,   419,  9913,   312,   420,
     452,   455,   758,  -766,  -766,  -766,  -766,   921,  -766,  -766,
    -766,  -766,  -766,  -766,   237,   691,  -766,  -766,   930,  -766,
     954,  -766,   957,  -766,   648,   405,   424,  -766,  -766,  -766,
    -766,  5610,  9117,  9117,  9117,  9117,  7841,  9117,  9117,  -766,
    -766,  8769,  -766,  4652,  7374,   346,  8769,  9233,  9233,  9233,
    9233,  9233,  9233,  9233,  9233,  9233,  9233,  9233,  9233,  9233,
    9233,  9233,  9233,  9233,  9233,  9233,  9233,  9233,  9233,  9233,
    9233,  9233,  9233, 10198,  8305, 10279,  -766,  -766, 11251,  -766,
    -766,  -766,  9349,  9349,  -766,   392,  -766,   306,  -766,   495,
    -766,  -766,  -766,    42,  -766,  -766,  -766, 10360,  8305, 10441,
    3801,  9117,  1057,  -766,   435,  -766,   489,   493,    50,  -766,
    3945,   496,  9233, 10522,  8305, 10603,  9233,  9233,  4223,   237,
     371,  8885,   500,  -766,    54,    54,   103, 10684,  8305, 10765,
    -766,  -766,  -766,  -766,  9233,  7493,  -766,  -766,  8537,  -766,
     303,   365,  -766,  -766,   303,  -766,   373,   381,  -766,    45,
    -766,  -766,  6978,  4361,   374, 10522, 10603,  9233,  1039,   303,
    -766,  -766,  5745,   390,   303,  -766,  -766,  7725,  -766,  -766,
    8653,  -766,  -766,  -766,   495,   128,  9913,  -766,  9913, 10846,
    8305, 10927,   409,  -766,  -766,  -766,  -766,  1199,  -766,  -766,
    -766,  -766,   790,    66,  -766,  -766,  -766,  -766,   391,  -766,
     408,   483,   410,   488,  -766,  -766,   498,  4958,  -766,  -766,
    -766,   237,  -766,   246,  -766,  -766,  -766,  -766,  -766,  -766,
    -766,  9233,  9233,  -766,  -766,  -766,  -766,  -766,  -766,  -766,
    -766,    33,  9233,  -766,   411,   415,  -766,   303,  9913,   428,
    -766,  -766,  -766,   430,  2548,  -766,  -766,   372,  6997,  6997,
    6997,  6997,  1121,  1121, 10135,  1428,  6997,  6997,  3295,  3295,
     727,   727,  2408,  1121,  1121,   665,   665,   876,   264,   264,
     372,   372,   372,  3556,  6418,  3648,  6539,  -766,   175,  -766,
     303,   557,  -766,   615,  -766,  -766,  3316,  -766,  -766,  2070,
      33,    33,  -766,  2732,  -766,  3147,  -766,  -766,    42,  -766,
    9117,  3801,   308,   387,  -766,   175,   303,   175,   559,    45,
     790,  3801,    42,  7124,  6978,  -766,  9001,   536,  -766,   422,
    -766,  2999,  6297,  2872,   303,    53,   207,   536,  -766,   237,
     582,    34,  -766,  -766,  -766,  -766,  -766,   145,   154,   303,
     130,   142,  9117,  -766,  9233,   335,  -766,  7957,   293,  -766,
    -766,  -766,  -766,  7493,  8537,  -766,  -766,   450,  -766,  3147,
      17,  1039,  -766,   178,   346,  -766,   308,   387,   303,   135,
     146,  9233,  -766,  1199,    95,  -766,   446,   303,  -766,   303,
    5102,  4958,  -766,   790,  -766,  -766,   790,  -766,  -766,   449,
    -766,  -766,  -766,   459,  4958,  -766,  -766,  -766,   372,   372,
    -766,   642,  5102,  -766,  -766,   461,  8073,  -766,  -766,  9913,
    9349,  9233,   509,  9349,  9349,  -766,   392,   460,   617,  9349,
    9349,  -766,  -766,   392,  -766,    59,   131,  5102,  4958,  9233,
      33,  -766,    42,   632,  -766,  -766,  -766,   303,   634,  -766,
    -766,  -766,   411,  -766,   558,  -766,  4514,   639,  -766,  9117,
     641,  -766,  9233,  9233,   226,  9233,  9233,   652,  -766,  8189,
    4084,  5102,  5102,   155,    54,  -766,  9233,  -766,  -766,   524,
    -766,  -766,   378,  -766,   303,   992,   525,  1207,  -766,   527,
     523,   668,   535,  -766,   538,   544,  -766,   552,  -766,   554,
     552,  -766,   539,   566,   303,   589,   556,  -766,   564,   567,
    -766,   705,  9233,   573,  -766,  3147,  9233,  -766,  3147,  -766,
    3147,  -766,  -766,  9349,  -766,  3147,  -766,  3147,  -766,  -766,
    -766,   713,   580,  3147,  4958,  3801,  -766,  -766,  -766,  -766,
    1057, 10025,    56,  -766,  -766,  5102,  -766,  -766,    56,  -766,
    9233,  -766,  -766,   115,   716,   717,  -766,  -766,  8537,  -766,
     581,   992,   429,  -766,  -766,   974,  -766,  -766,   790,  -766,
     449,  -766,   449,  -766,   449,  -766,  -766,  -766, 10137,   609,
    -766,  1065,  -766,  1065,  -766,   449,  -766,  -766,   590,  3147,
    -766,  3147,  -766,  -766,   619,   756,  3801,   712,  -766,   541,
     452,   455,  3801,  -766,  3945,  -766,  -766,  -766,  -766,  -766,
    5102,   992,   581,   992,   622,  -766,   192,  -766,  -766,   552,
     623,   552,   552,   721,   543,  -766,   633,   638,   552,  -766,
     647,   552,  -766,  -766,   789,   495, 11008,  8305, 11089,   493,
     422,   791,   581,   992,   974,  -766,  -766,   449,  -766,  -766,
    -766,  -766, 11170,  1065,  -766,   449,  -766,  -766,   449,  -766,
    -766,  -766,    81,   387,   303,    64,    83,  -766,  -766,  -766,
     581,  -766,   552,   655,   657,   552,   661,   552,   552,   121,
    -766,  -766,   449,  -766,  -766,  -766,   552,  -766
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -766,  -766,  -766,   376,  -766,    20,  -766,  -369,   321,  -766,
      27,  -766,  -313,   189,    76,   -45,  -766,  -584,  -766,   -15,
     801,  -168,   -14,   -61,  -276,  -418,   -19,  2012,   -74,   811,
      13,   -18,  -766,  -766,  -242,  -766,  1550,   314,  -766,    -8,
     244,  -361,   100,    -9,  -766,  -374,  -232,    86,  -299,     3,
    -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,
    -766,  -766,  -766,  -766,  -766,  -766,  -766,   608,  -196,  -387,
     -95,  -546,  -766,  -703,  -665,   163,  -766,  -456,  -766,  -599,
    -766,   -97,  -766,  -766,   116,  -766,  -766,  -766,   -76,  -766,
    -766,  -391,  -766,   -86,  -766,  -766,  -766,  -766,  -766,   687,
     817,  -766,  -766,  -766,  -766,  -766,  -199,  -441,  -766,   331,
    -766,  -766,  -766,    18,  -766,  -766,  -766,  1760,   209,   828,
    2050,  -766,  -766,    19,  -270,  -752,  -397,  -605,   297,  -634,
    -765,   -21,   169,  -766,  -600,  -766,  -239,   315,  -766,  -766,
    -766,    24,  -376,  1122,  -333,  -766,   649,   -27,   -23,   601,
    -551,  -222,    -6,     0,  -766,     1,    -2
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -553
static const yytype_int16 yytable[] =
{
      99,   242,   242,   570,   259,   242,   226,   371,   115,   115,
     261,   466,   227,   257,   256,   335,   429,   317,   115,   620,
     194,   598,   484,   531,   100,   408,   211,   596,   626,    67,
     568,    67,   576,   288,   274,   579,   380,   536,   320,   383,
     248,   248,   778,   614,   248,   724,   211,   399,   281,   285,
     655,   636,   639,   494,   636,   115,   597,   629,   461,   226,
     685,   737,   463,   744,   843,   227,   321,   298,   773,   399,
     568,   747,   576,   775,   280,   284,   779,   -96,   753,   115,
     668,   623,   327,   328,   639,   369,   597,   221,   224,   375,
     374,   789,   785,   898,   -97,   670,   -98,   256,   909,  -321,
     840,   449,   247,   247,   366,   501,   247,   762,   386,   658,
     698,   374,   690,   597,   227,  -460,   245,   250,   407,   -94,
     251,   566,   801,   574,   717,   718,   574,  -101,  -100,   808,
     736,  -463,   411,   -67,   -95,  -462,   279,   369,   597,     3,
     447,   -94,   263,   745,  -101,   566,   662,   574,   473,   474,
     475,   476,   267,   494,   691,   -96,  -321,  -321,   384,   329,
     -88,   566,   367,   574,   -81,   527,  -100,   -98,   909,   -96,
     -97,   -90,   898,  -464,   671,   566,   892,   574,   685,   -99,
     -95,   749,   315,   316,   331,   859,   222,   223,   843,  -463,
     222,   223,   466,  -462,   222,   223,   685,   410,   223,   214,
     214,   214,   370,   566,   574,   429,   222,   223,   222,   223,
     619,    95,   669,    95,   778,   227,   -96,   -96,   226,   258,
     298,   227,   723,   223,   227,  -465,   465,   566,   922,   574,
    -528,  -464,   728,   -97,   -97,   -98,   -98,   242,   276,   242,
     242,   -86,   765,   494,   451,   427,   427,   773,   900,   -93,
     -92,   -88,   466,   438,   370,   274,   773,    95,   950,  -525,
     255,   907,   -90,   910,   814,   226,   668,   766,   639,   636,
     636,   227,   452,   -95,   -95,   332,   248,   -88,   248,   459,
     459,   794,   -88,  -465,   459,   -88,   523,   885,   -88,   -90,
     115,   532,   -89,   -90,  -528,   448,   -90,   746,   377,   -90,
    -467,   -91,   -87,  -529,   336,   414,   415,   733,  -466,   372,
    -526,   252,   457,   594,   395,   529,   830,   363,   223,   274,
      95,  -455,  -455,   -98,   255,   460,  -459,   582,   584,   258,
     727,   223,   378,   956,  -532,   337,   379,   115,   247,   924,
     247,   513,   -95,   327,   328,   223,   398,   498,    67,   242,
     499,   500,   430,   518,   433,   387,   686,   575,  -467,   499,
     500,   494,   438,   381,   382,   282,  -466,   836,   668,   270,
     668,   402,  -459,   242,   364,   365,  -525,   589,  -455,  -455,
    -455,   575,  -525,   227,  -459,   406,   438,   531,   411,   242,
     360,   361,   362,   959,   413,   608,  -532,   575,   514,   515,
     516,   517,   438,   242,  -390,   654,   758,   465,   625,   625,
     416,   575,   388,   389,   227,   227,   438,   525,   214,   214,
     420,    95,   525,   466,   646,   750,   424,  -526,   443,  -459,
    -459,   761,   270,  -526,   427,   427,   739,   736,   575,   425,
     428,    99,   886,   337,   668,   894,   875,   439,   441,   638,
     450,  -532,   790,  -532,  -532,   242,   223,  -528,   -66,   468,
     211,   456,   639,   575,   636,  -460,  -390,   465,   438,   115,
      67,   115,    95,   462,   464,  -277,   511,    95,    95,   651,
     662,   653,   473,   474,   475,   476,   675,   403,   675,   586,
     675,   -94,   417,   530,   668,   512,   668,   621,   495,   605,
     662,   606,   473,   474,   475,   476,   445,   914,   469,   610,
     622,   214,   214,   214,   214,   641,   519,   520,   648,   694,
     643,  -390,   -86,  -390,  -390,   661,   668,   758,   644,   702,
      95,   115,  -277,  -277,   678,    95,  -529,   -81,   673,   681,
    -461,   477,    95,  -268,   404,   405,   700,   707,   479,   418,
     419,   736,   421,   422,   423,   676,   944,   679,  -253,   706,
     705,   682,   696,   404,   446,   470,   471,   713,   711,   725,
     716,   711,   480,   707,   714,   699,   893,   714,   694,   694,
     599,   494,   721,  -278,   444,   597,   731,   705,   227,   711,
     270,   707,   748,   767,   760,   714,   729,  -461,  -461,    95,
    -268,  -268,   227,   781,   735,   738,   707,   738,  -254,    95,
      81,   802,    81,   116,   116,   738,   730,    95,   217,   217,
     217,   227,   211,   234,   217,   217,   882,   796,   217,   916,
     313,   932,   884,   301,   302,   707,   427,   373,   465,   809,
    -278,  -278,   817,   447,   819,   524,   770,   709,   825,   821,
     535,   829,    95,   459,   270,   532,    81,   217,   797,   799,
     289,    95,   831,  -101,   804,   806,   722,   759,   770,  -100,
     217,   838,   841,   -96,   566,   845,   574,   844,   846,   847,
     303,   304,   858,   857,   289,   848,   917,   918,   388,   389,
     566,   850,   525,   783,   -93,   473,   474,   475,   476,   852,
     -92,   854,   115,   861,   -88,   710,    95,   803,   754,   510,
     860,   863,   301,   302,   865,   867,   816,   217,   694,    81,
    -255,   609,   227,   872,   873,   535,   888,   889,   891,   617,
     905,   -98,   823,   -95,   477,   827,   337,  -256,   633,   635,
     478,   479,   282,   308,   310,   312,   314,   300,   625,   301,
     302,   350,   351,   505,   227,   301,   302,   427,   870,   303,
     304,   770,   -90,   912,   -87,   480,   913,   915,   481,   923,
     927,   635,   675,   675,   282,   675,   931,   675,   675,   214,
     933,   307,   301,   302,   675,   935,   675,   675,   357,   358,
     359,   360,   361,   362,   938,   223,   303,   304,   337,   941,
      95,   949,   303,   304,  -528,   677,  -529,   680,   962,   472,
      95,   473,   474,   475,   476,   828,   232,   120,   683,   647,
      81,   214,   227,   715,   115,   948,   764,   951,   227,   303,
     304,   738,   810,   947,   687,   197,   695,   217,   217,   876,
     906,   472,   774,   473,   474,   475,   476,   393,     0,     0,
     477,   358,   359,   360,   361,   362,   478,   479,     0,   440,
     217,   115,   217,   217,     0,     0,   217,   217,     0,     0,
       0,    81,     0,   925,   453,     0,    81,    81,   455,    95,
      95,   480,   477,     0,   481,     0,     0,     0,   478,   479,
       0,     0,     0,    95,     0,   289,     0,   675,   675,   675,
     675,    95,   242,     0,   675,   675,   675,   482,   675,   675,
     575,     0,     0,   480,     0,   438,   481,   608,   738,     0,
     732,   707,   309,   301,   302,     0,    95,    95,   214,    81,
     217,   217,   217,   217,    81,   217,   217,     0,     0,   217,
       0,    81,   289,     0,   217,    95,     0,   337,   755,     0,
     675,   757,     0,   675,   675,   675,   675,   635,   282,    95,
      95,    95,   350,   351,   675,     0,   311,   301,   302,     0,
     303,   304,   217,   777,     0,   763,   780,     0,     0,     0,
     217,   217,     0,     0,   495,   301,   302,     0,   786,     0,
       0,   771,   772,   507,   301,   302,   217,     0,    81,   217,
     358,   359,   360,   361,   362,   782,     0,     0,    81,     0,
     793,     0,   217,   791,   303,   304,    81,   508,   301,   302,
     509,   301,   302,    95,    95,   895,   217,   473,   474,   475,
     476,   640,   303,   304,    95,   642,     0,     0,   811,   812,
     645,   303,   304,   662,     0,   473,   474,   475,   476,     0,
     650,    81,     0,     0,     0,   652,     0,   824,     0,     0,
      81,     0,     0,   832,     0,   303,   304,     0,   303,   304,
     837,   833,   834,   835,   289,     0,   289,     0,   217,   322,
     323,   324,   325,   326,   663,    95,     0,     0,     0,   849,
     851,    95,   853,    95,   855,   856,     0,     0,     0,    95,
       0,   862,     0,   864,   866,    81,   868,     0,   472,     0,
     473,   474,   475,   476,   496,     0,   783,     0,   473,   474,
     475,   476,   506,     0,    98,   506,    98,   506,   697,   506,
       0,   506,    98,    98,    98,   874,   289,     0,    98,    98,
       0,     0,    98,     0,     0,   899,   883,   901,     0,   477,
       0,   902,   282,     0,     0,   478,   479,   477,     0,     0,
     908,     0,   911,   478,   479,     0,     0,     0,     0,     0,
      98,    98,     0,     0,     0,     0,     0,     0,     0,     0,
     480,     0,     0,   481,    98,     0,     0,     0,   480,     0,
       0,   481,   337,     0,     0,     0,     0,     0,   217,    81,
     726,     0,     0,   919,     0,   920,   600,   350,   351,    81,
       0,   921,     0,     0,   926,   928,   929,   930,     0,     0,
       0,   934,   936,   937,   952,   939,   940,     0,     0,     0,
     955,    98,   957,    98,     0,   958,     0,     0,     0,     0,
     217,     0,   355,   356,   357,   358,   359,   360,   361,   362,
     662,     0,   473,   474,   475,   476,     0,     0,   662,   966,
     473,   474,   475,   476,     0,     0,     0,   960,   768,     0,
     961,   963,   964,   965,     0,     0,     0,     0,    81,    81,
       0,   967,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   663,    81,     0,     0,     0,     0,   664,     0,   663,
      81,     0,     0,     0,     0,   842,     0,   289,   217,     0,
       0,   217,   217,     0,     0,     0,     0,   217,   217,     0,
       0,     0,     0,     0,     0,    81,    81,     0,   818,     0,
       0,     0,     0,     0,    98,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    81,     0,     0,   217,     0,     0,
       0,    98,    98,     0,     0,     0,     0,     0,    81,    81,
      81,     0,     0,     0,     0,   839,     0,     0,     0,     0,
       0,     0,     0,     0,    98,     0,    98,    98,     0,     0,
      98,    98,     0,     0,     0,    98,     0,     0,     0,     0,
      98,    98,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   217,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    81,    81,     0,     0,     0,     0,     0,   879,
       0,     0,     0,    81,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    98,    98,    98,    98,    98,    98,    98,
      98,     0,     0,    98,     0,    98,     0,     0,    98,     0,
       0,     0,     0,     0,     0,     0,   904,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    81,     0,    98,     0,     0,     0,
      81,     0,    81,     0,    98,    98,     0,     0,    81,   337,
     338,   339,   340,   341,   342,   343,   344,     0,   346,   347,
      98,     0,    98,    98,   350,   351,     0,     0,     0,     0,
       0,     0,    98,     0,     0,   217,    98,     0,     0,     0,
      98,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      98,     0,     0,     0,     0,     0,     0,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,     0,     0,     0,
       0,     0,     0,     0,     0,    98,   243,   243,     0,     0,
     243,     0,     0,     0,    98,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    98,     0,     0,   264,   266,     0,     0,     0,
     243,   243,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   318,   319,     0,     0,     0,     0,     0,    98,
       0,     0,     0,     0,     0,     0,  -552,     4,     0,     5,
       6,     7,     8,     9,     0,     0,     0,    10,    11,     0,
       0,     0,    12,     0,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,     0,     0,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
       0,    28,    29,    30,    31,    32,     0,    33,    34,    35,
      36,    37,    38,     0,    39,    40,    41,     0,     0,    42,
       0,     0,    43,    44,     0,    45,    46,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    98,    98,     0,    47,     0,     0,    48,    49,
       0,    50,    51,    98,    52,     0,    53,    54,    55,    56,
      57,    58,    59,     0,     0,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    98,    61,    62,    63,     0,     0,
       0,     0,    94,     0,    94,   117,   117,   117,     0,     0,
       0,     0,     0,     0,     0,   236,     0,     0,  -552,  -552,
       0,     0,     0,     0,     0,     0,     0,     0,   243,   243,
     243,   318,    98,    98,     0,     0,     0,     0,     0,     0,
       0,     0,   243,     0,   243,   243,    98,     0,    94,     0,
       0,     0,   290,     0,    98,     0,     0,     0,     0,     0,
       0,     0,    98,     0,     0,    98,    98,     0,     0,     0,
       0,    98,    98,     0,     0,     0,   290,     0,     0,    98,
      98,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    98,     0,
       0,    98,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,    98,    98,    98,     0,     0,     0,     0,     0,
       0,   243,     0,     0,     0,     0,   534,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   562,     0,   243,     0,     0,     0,     0,     0,
       0,     0,   583,   585,     0,    98,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    98,    98,   243,     0,
       0,     0,     0,     0,     0,     0,     0,    98,     0,     0,
       0,     0,   611,     0,   243,     0,   583,   585,     0,     0,
       0,   243,     0,     0,     0,     0,     0,     0,   243,     0,
       0,     0,    94,     0,   243,   243,     0,     0,   243,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   649,    98,     0,
       0,     0,     0,     0,    98,     0,    98,   243,     0,     0,
     243,     0,    98,     0,    78,     0,    78,     0,     0,     0,
     243,     0,     0,    94,     0,     0,     0,   233,    94,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    98,
       0,     0,     0,     0,     0,     0,     0,   290,     0,     0,
       0,     0,    97,     0,    97,   118,   118,     0,     0,     0,
      78,   688,   689,     0,     0,   237,     0,     0,     0,     0,
    -552,     0,   243,     0,     0,     0,     0,     0,  -552,  -552,
    -552,    94,     0,  -552,  -552,  -552,    94,  -552,     0,     0,
       0,     0,     0,    94,   290,     0,  -552,  -552,    97,     0,
       0,     0,   291,     0,     0,     0,     0,  -552,  -552,     0,
    -552,  -552,  -552,  -552,  -552,     0,     0,     0,     0,     0,
       0,     0,     0,    78,     0,     0,   291,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,     0,     0,     0,     0,     0,   243,     0,  -552,     0,
      94,    97,     0,     0,     0,     0,     0,     0,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   243,     0,     0,   243,     0,     0,
       0,     0,     0,   243,   243,     0,     0,     0,     0,     0,
       0,     0,     0,    94,     0,     0,     0,     0,     0,     0,
       0,   243,    94,  -552,  -552,     0,  -552,     0,     0,   255,
    -552,     0,  -552,  -552,    78,     0,   290,     0,   290,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   243,     0,     0,     0,
     611,   795,     0,   798,   800,     0,     0,    94,     0,   805,
     807,     0,    97,     0,     0,     0,     0,     0,     0,   813,
       0,     0,     0,     0,     0,    78,     0,     0,     0,     0,
      78,    78,     0,     0,     0,     0,     0,     0,   290,     0,
       0,     0,   798,   800,     0,   805,   807,     0,     0,   243,
       0,     0,     0,     0,     0,     0,   243,     0,     0,     0,
       0,     0,     0,    97,     0,     0,     0,     0,    97,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    78,     0,     0,     0,   291,    78,     0,
       0,     0,   243,     0,     0,    78,   869,     0,   533,     0,
       0,    94,     0,   871,     0,     0,     0,     0,     0,     0,
       0,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    97,     0,     0,     0,     0,    97,     0,     0,     0,
     871,     0,     0,    97,   291,     0,     0,     0,   243,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    78,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    78,     0,     0,     0,     0,     0,     0,     0,
      78,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,    94,     0,     0,     0,     0,     0,     0,     0,     0,
      97,     0,     0,     0,    94,     0,     0,     0,     0,     0,
      97,     0,    94,     0,     0,    78,     0,     0,    97,   290,
       0,     0,     0,     0,    78,     0,     0,   243,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,    94,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,     0,    97,   350,   351,    94,     0,     0,     0,
       0,     0,    97,     0,     0,     0,     0,     0,     0,    78,
      94,    94,    94,     0,     0,     0,   291,     0,   291,     0,
       0,     0,     0,     0,     0,   352,     0,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   223,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    94,    94,     0,     0,   291,     0,
       0,   880,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,   701,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    78,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    78,     0,     0,     0,     0,   117,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,     0,     0,   350,   351,    94,     0,     0,     0,
       0,    97,    94,     0,    94,     0,     0,     0,     0,     0,
      94,    97,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   352,     0,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,     0,     0,     0,
       0,     0,    78,    78,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -230,    78,     0,     0,     0,
       0,     0,     0,     0,    78,     0,     0,     0,     0,     0,
       0,     0,   533,     0,     0,     0,     0,     0,     0,     0,
      97,    97,     0,     0,     0,     0,     0,     0,     0,    78,
      78,     0,     0,     0,    97,     0,     0,     0,     0,     0,
       0,     0,    97,     0,     0,     0,     0,     0,    78,   291,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    78,    78,    78,     0,     0,    97,    97,     0,
       0,     0,     0,     0,     0,     0,   719,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    97,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      97,    97,    97,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,     0,     0,   350,   351,
       0,     0,     0,     0,     0,     0,    78,    78,     0,     0,
       0,     0,     0,   878,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   352,
       0,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,     0,     0,     0,    97,    97,     0,     0,     0,     0,
       0,   881,  -277,     0,     0,    97,     0,     0,     0,     0,
    -277,  -277,  -277,     0,     0,  -277,  -277,  -277,    78,  -277,
       0,     0,     0,     0,    78,     0,    78,     0,     0,  -277,
    -277,  -277,    78,     0,     0,     0,     0,     0,   118,  -277,
    -277,     0,  -277,  -277,  -277,  -277,  -277,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    97,     0,     0,     0,
       0,     0,    97,     0,    97,     0,     0,     0,     0,     0,
      97,     0,     0,  -277,  -277,  -277,  -277,  -277,  -277,  -277,
    -277,  -277,  -277,  -277,  -277,  -277,     0,     0,  -277,  -277,
    -277,     0,   743,  -277,     0,     0,     0,     0,     0,  -277,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -277,     0,     0,     0,     0,     0,     0,     0,   -99,  -277,
    -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,
    -277,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -277,  -277,  -277,  -277,
    -389,     0,  -277,  -277,  -277,  -277,     0,     0,  -389,  -389,
    -389,     0,     0,  -389,  -389,  -389,     0,  -389,     0,     0,
       0,     0,     0,   701,     0,     0,  -389,  -389,  -389,     0,
       0,     0,     0,     0,     0,     0,     0,  -389,  -389,     0,
    -389,  -389,  -389,  -389,  -389,     0,     0,     0,     0,     0,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,     0,     0,   350,   351,     0,     0,     0,
       0,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,
    -389,  -389,  -389,  -389,     0,     0,  -389,  -389,  -389,     0,
       0,  -389,     0,     0,     0,     0,   352,  -389,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -389,     0,  -389,
    -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,  -389,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -389,  -389,  -389,  -389,  -389,  -269,   255,
    -389,  -389,  -389,  -389,     0,     0,  -269,  -269,  -269,     0,
       0,  -269,  -269,  -269,     0,  -269,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -269,  -269,  -269,     0,     0,
       0,     0,     0,     0,     0,  -269,  -269,     0,  -269,  -269,
    -269,  -269,  -269,     0,     0,     0,     0,     0,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,     0,     0,   350,   351,     0,     0,     0,     0,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,     0,     0,  -269,  -269,  -269,     0,     0,  -269,
       0,     0,     0,     0,   352,  -269,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,  -269,     0,     0,     0,
       0,     0,     0,     0,     0,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,  -269,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -269,  -269,  -269,  -269,  -552,     0,  -269,  -269,
    -269,  -269,     0,     0,  -552,  -552,  -552,     0,     0,  -552,
    -552,  -552,     0,  -552,     0,     0,     0,     0,     0,     0,
       0,     0,  -552,  -552,  -552,     0,     0,     0,     0,     0,
       0,     0,     0,  -552,  -552,     0,  -552,  -552,  -552,  -552,
    -552,     0,     0,     0,     0,     0,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,  -553,  -553,     0,
       0,   350,   351,     0,     0,     0,     0,  -552,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,
       0,     0,  -552,  -552,  -552,     0,     0,  -552,     0,     0,
       0,     0,     0,  -552,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -552,     0,  -552,  -552,  -552,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -552,
    -552,  -552,  -552,  -552,  -284,   255,  -552,  -552,  -552,  -552,
       0,     0,  -284,  -284,  -284,     0,     0,  -284,  -284,  -284,
       0,  -284,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -284,  -284,     0,     0,     0,     0,     0,     0,     0,
       0,  -284,  -284,     0,  -284,  -284,  -284,  -284,  -284,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -284,  -284,  -284,  -284,  -284,
    -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,     0,     0,
    -284,  -284,  -284,     0,     0,  -284,  -532,     0,     0,     0,
       0,  -284,     0,     0,  -532,  -532,  -532,     0,     0,     0,
    -532,  -532,     0,  -532,     0,     0,     0,     0,     0,     0,
       0,  -284,  -532,  -284,  -284,  -284,  -284,  -284,  -284,  -284,
    -284,  -284,  -284,  -532,  -532,     0,  -532,  -532,  -532,  -532,
    -532,     0,     0,     0,     0,     0,     0,     0,  -284,  -284,
    -284,  -284,     0,   252,  -284,  -284,  -284,  -284,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -532,  -532,  -532,
    -532,  -532,  -532,  -532,  -532,  -532,  -532,  -532,  -532,  -532,
       0,     0,  -532,  -532,  -532,     0,   703,     0,  -277,     0,
       0,     0,     0,     0,     0,     0,  -277,  -277,  -277,     0,
       0,     0,  -277,  -277,     0,  -277,     0,     0,     0,     0,
       0,     0,   -97,  -532,     0,  -532,  -532,  -532,  -532,  -532,
    -532,  -532,  -532,  -532,  -532,  -277,  -277,     0,  -277,  -277,
    -277,  -277,  -277,     0,     0,     0,     0,     0,     0,  -532,
    -532,  -532,  -532,   -89,     0,     0,  -532,     0,  -532,  -532,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -277,
    -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,
    -277,  -277,     0,     0,  -277,  -277,  -277,     0,   704,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -99,  -277,     0,  -277,  -277,  -277,
    -277,  -277,  -277,  -277,  -277,  -277,  -277,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -277,  -277,  -277,   -91,     0,     0,  -277,     0,
    -277,  -277,   268,     0,     5,     6,     7,     8,     9,  -552,
    -552,  -552,    10,    11,     0,     0,  -552,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,    28,     0,    30,    31,
      32,     0,    33,    34,    35,    36,    37,    38,     0,    39,
      40,    41,     0,     0,    42,     0,     0,    43,    44,     0,
      45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      47,     0,     0,    48,    49,     0,    50,    51,     0,    52,
       0,    53,    54,    55,    56,    57,    58,    59,     0,     0,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   268,     0,     5,     6,
       7,     8,     9,  -552,  -552,  -552,    10,    11,     0,  -552,
    -552,    12,     0,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
      28,     0,    30,    31,    32,     0,    33,    34,    35,    36,
      37,    38,     0,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,    45,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    47,     0,     0,    48,    49,     0,
      50,    51,     0,    52,     0,    53,    54,    55,    56,    57,
      58,    59,     0,     0,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,     0,     0,     0,
       0,     0,     0,     0,     0,   268,     0,     5,     6,     7,
       8,     9,     0,     0,  -552,    10,    11,  -552,  -552,  -552,
      12,  -552,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,    20,    21,    22,    23,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,     0,    28,
       0,    30,    31,    32,     0,    33,    34,    35,    36,    37,
      38,     0,    39,    40,    41,     0,     0,    42,     0,     0,
      43,    44,     0,    45,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    47,     0,     0,    48,    49,     0,    50,
      51,     0,    52,     0,    53,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,     0,     0,     0,     0,
       0,     0,     0,     0,   268,     0,     5,     6,     7,     8,
       9,     0,     0,  -552,    10,    11,  -552,  -552,  -552,    12,
       0,    13,    14,    15,    16,    17,    18,    19,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,     0,    28,     0,
      30,    31,    32,     0,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,    45,    46,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    47,     0,     0,    48,    49,     0,    50,    51,
       0,    52,     0,    53,    54,    55,    56,    57,    58,    59,
       0,     0,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    61,    62,    63,     0,     0,     0,     0,     0,
       0,     0,     4,     0,     5,     6,     7,     8,     9,     0,
       0,     0,    10,    11,     0,  -552,  -552,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,    28,    29,    30,    31,
      32,     0,    33,    34,    35,    36,    37,    38,     0,    39,
      40,    41,     0,     0,    42,     0,     0,    43,    44,     0,
      45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      47,     0,     0,    48,    49,     0,    50,    51,     0,    52,
       0,    53,    54,    55,    56,    57,    58,    59,     0,     0,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -552,     0,     0,     0,     0,
       0,     0,     0,  -552,  -552,   268,     0,     5,     6,     7,
       8,     9,     0,  -552,  -552,    10,    11,     0,     0,     0,
      12,     0,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,    20,    21,    22,    23,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,     0,    28,
       0,    30,    31,    32,     0,    33,    34,    35,    36,    37,
      38,     0,    39,    40,    41,     0,     0,    42,     0,     0,
      43,    44,     0,    45,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    47,     0,     0,    48,    49,     0,    50,
      51,     0,    52,     0,    53,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,     0,     0,     0,     0,
       0,     0,     0,   268,     0,     5,     6,     7,     8,     9,
       0,     0,     0,    10,    11,     0,  -552,  -552,    12,     0,
      13,    14,    15,    16,    17,    18,    19,     0,     0,     0,
       0,     0,    20,    21,    22,    23,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,     0,    28,     0,    30,
      31,    32,     0,    33,    34,    35,    36,    37,    38,     0,
      39,    40,    41,     0,     0,    42,     0,     0,    43,    44,
       0,    45,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    47,     0,     0,   269,    49,     0,    50,    51,     0,
      52,     0,    53,    54,    55,    56,    57,    58,    59,     0,
       0,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -552,     0,  -552,  -552,   268,     0,     5,     6,
       7,     8,     9,     0,     0,     0,    10,    11,     0,     0,
       0,    12,     0,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
      28,     0,    30,    31,    32,     0,    33,    34,    35,    36,
      37,    38,     0,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,    45,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    47,     0,     0,    48,    49,     0,
      50,    51,     0,    52,     0,    53,    54,    55,    56,    57,
      58,    59,     0,     0,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -552,     0,  -552,  -552,   268,
       0,     5,     6,     7,     8,     9,     0,     0,     0,    10,
      11,     0,     0,     0,    12,     0,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     0,     0,     0,    20,    21,
      22,    23,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,     0,    28,     0,    30,    31,    32,     0,    33,
      34,    35,    36,    37,    38,     0,    39,    40,    41,     0,
       0,    42,     0,     0,    43,    44,     0,    45,    46,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    47,     0,     0,
      48,    49,     0,    50,    51,     0,    52,     0,    53,    54,
      55,    56,    57,    58,    59,     0,     0,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,    62,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -552,   268,     0,     5,     6,     7,     8,     9,
    -552,  -552,  -552,    10,    11,     0,     0,     0,    12,     0,
      13,    14,    15,    16,    17,    18,    19,     0,     0,     0,
       0,     0,    20,    21,    22,    23,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,     0,    28,     0,    30,
      31,    32,     0,    33,    34,    35,    36,    37,    38,     0,
      39,    40,    41,     0,     0,    42,     0,     0,    43,    44,
       0,    45,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    47,     0,     0,    48,    49,     0,    50,    51,     0,
      52,     0,    53,    54,    55,    56,    57,    58,    59,     0,
       0,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     0,     9,     0,     0,
       0,    10,    11,     0,  -552,  -552,    12,     0,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,   106,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,    33,    34,    35,    36,    37,    38,   238,    39,    40,
      41,     0,     0,    42,     0,     0,    43,    44,     0,    45,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   213,
       0,     0,   111,    49,     0,    50,    51,     0,   239,   240,
      53,    54,    55,    56,    57,    58,    59,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,    61,
     241,    63,    12,     0,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,     0,     0,    20,    21,    22,    23,
      24,    25,    26,   223,     0,    27,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,    33,    34,    35,
      36,    37,    38,     0,    39,    40,    41,     0,     0,    42,
       0,     0,    43,    44,     0,    45,    46,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   213,     0,     0,   111,    49,
       0,    50,    51,     0,     0,     0,    53,    54,    55,    56,
      57,    58,    59,     0,     0,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    62,    63,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     6,     7,
       0,     9,     0,     0,     0,    10,    11,     0,   222,   223,
      12,     0,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,    20,    21,    22,    23,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     0,    33,    34,    35,    36,    37,
      38,     0,    39,    40,    41,     0,     0,    42,     0,     0,
      43,    44,     0,    45,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   213,     0,     0,   111,    49,     0,    50,
      51,     0,     0,     0,    53,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     8,     9,     0,     0,
       0,    10,    11,    61,    62,    63,    12,     0,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,   223,     0,    27,
       0,     0,     0,     0,     0,    28,    29,    30,    31,    32,
       0,    33,    34,    35,    36,    37,    38,     0,    39,    40,
      41,     0,     0,    42,     0,     0,    43,    44,     0,    45,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    47,
       0,     0,    48,    49,     0,    50,    51,     0,    52,     0,
      53,    54,    55,    56,    57,    58,    59,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      62,    63,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     8,     9,     0,     0,     0,    10,    11,     0,     0,
       0,    12,   413,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
      28,     0,    30,    31,    32,     0,    33,    34,    35,    36,
      37,    38,     0,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,    45,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    47,     0,     0,    48,    49,     0,
      50,    51,     0,    52,     0,    53,    54,    55,    56,    57,
      58,    59,     0,     0,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   413,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,     0,     0,     0,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,     0,     0,     0,     0,     0,
     155,   156,   157,   158,   159,   160,   161,   162,    35,    36,
     163,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,   173,   174,     0,     0,   175,
     176,   177,   178,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,     0,   190,   191,     0,     0,     0,
       0,     0,  -525,  -525,  -525,     0,  -525,     0,     0,     0,
    -525,  -525,     0,   192,   193,  -525,     0,  -525,  -525,  -525,
    -525,  -525,  -525,  -525,     0,  -525,     0,     0,     0,  -525,
    -525,  -525,  -525,  -525,  -525,  -525,     0,     0,  -525,     0,
       0,     0,     0,     0,     0,     0,     0,  -525,  -525,     0,
    -525,  -525,  -525,  -525,  -525,  -525,  -525,  -525,  -525,  -525,
       0,     0,  -525,     0,     0,  -525,  -525,     0,  -525,  -525,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -525,     0,
       0,  -525,  -525,     0,  -525,  -525,     0,  -525,  -525,  -525,
    -525,  -525,  -525,  -525,  -525,  -525,     0,     0,  -525,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -525,  -525,
    -525,     0,     0,     0,     0,     0,  -526,  -526,  -526,     0,
    -526,     0,  -525,     0,  -526,  -526,     0,     0,  -525,  -526,
       0,  -526,  -526,  -526,  -526,  -526,  -526,  -526,     0,  -526,
       0,     0,     0,  -526,  -526,  -526,  -526,  -526,  -526,  -526,
       0,     0,  -526,     0,     0,     0,     0,     0,     0,     0,
       0,  -526,  -526,     0,  -526,  -526,  -526,  -526,  -526,  -526,
    -526,  -526,  -526,  -526,     0,     0,  -526,     0,     0,  -526,
    -526,     0,  -526,  -526,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -526,     0,     0,  -526,  -526,     0,  -526,  -526,
       0,  -526,  -526,  -526,  -526,  -526,  -526,  -526,  -526,  -526,
       0,     0,  -526,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -526,  -526,  -526,     0,     0,     0,     0,     0,
    -528,  -528,  -528,     0,  -528,     0,  -526,     0,  -528,  -528,
       0,     0,  -526,  -528,     0,  -528,  -528,  -528,  -528,  -528,
    -528,  -528,     0,     0,     0,     0,     0,  -528,  -528,  -528,
    -528,  -528,  -528,  -528,     0,     0,  -528,     0,     0,     0,
       0,     0,     0,     0,     0,  -528,  -528,     0,  -528,  -528,
    -528,  -528,  -528,  -528,  -528,  -528,  -528,  -528,     0,     0,
    -528,     0,     0,  -528,  -528,     0,  -528,  -528,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -528,   742,     0,  -528,
    -528,     0,  -528,  -528,     0,  -528,  -528,  -528,  -528,  -528,
    -528,  -528,  -528,  -528,     0,     0,  -528,     0,     0,     0,
       0,     0,     0,   -97,     0,     0,     0,     0,     0,     0,
       0,  -530,  -530,  -530,     0,  -530,  -528,  -528,  -528,  -530,
    -530,     0,     0,     0,  -530,     0,  -530,  -530,  -530,  -530,
    -530,  -530,  -530,     0,     0,     0,  -528,     0,  -530,  -530,
    -530,  -530,  -530,  -530,  -530,     0,     0,  -530,     0,     0,
       0,     0,     0,     0,     0,     0,  -530,  -530,     0,  -530,
    -530,  -530,  -530,  -530,  -530,  -530,  -530,  -530,  -530,     0,
       0,  -530,     0,     0,  -530,  -530,     0,  -530,  -530,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -530,     0,     0,
    -530,  -530,     0,  -530,  -530,     0,  -530,  -530,  -530,  -530,
    -530,  -530,  -530,  -530,  -530,     0,     0,  -530,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -531,  -531,  -531,     0,  -531,  -530,  -530,  -530,
    -531,  -531,     0,     0,     0,  -531,     0,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,     0,     0,     0,  -530,     0,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,     0,     0,  -531,     0,
       0,     0,     0,     0,     0,     0,     0,  -531,  -531,     0,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,
       0,     0,  -531,     0,     0,  -531,  -531,     0,  -531,  -531,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -531,     0,
       0,  -531,  -531,     0,  -531,  -531,     0,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,     0,     0,  -531,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -531,  -531,
    -531,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -531,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,     0,     0,     0,   145,   146,   147,   199,
     200,   201,   202,   152,   153,   154,     0,     0,     0,     0,
       0,   155,   156,   157,   203,   204,   160,   205,   162,   293,
     294,   206,   295,     0,     0,     0,     0,     0,     0,   296,
       0,     0,     0,     0,     0,   164,   165,   166,   167,   168,
     169,   170,   171,   172,     0,     0,   173,   174,     0,     0,
     175,   176,   177,   178,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   179,     0,     0,     0,     0,     0,
       0,   297,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,     0,   190,   191,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   192,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,     0,
       0,     0,   145,   146,   147,   199,   200,   201,   202,   152,
     153,   154,     0,     0,     0,     0,     0,   155,   156,   157,
     203,   204,   160,   205,   162,   293,   294,   206,   295,     0,
       0,     0,     0,     0,     0,   296,     0,     0,     0,     0,
       0,   164,   165,   166,   167,   168,   169,   170,   171,   172,
       0,     0,   173,   174,     0,     0,   175,   176,   177,   178,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     179,     0,     0,     0,     0,     0,     0,   394,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,     0,   190,   191,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     192,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,     0,     0,     0,   145,   146,
     147,   199,   200,   201,   202,   152,   153,   154,     0,     0,
       0,     0,     0,   155,   156,   157,   203,   204,   160,   205,
     162,     0,     0,   206,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   164,   165,   166,
     167,   168,   169,   170,   171,   172,     0,     0,   173,   174,
       0,     0,   175,   176,   177,   178,     0,     0,   337,  -553,
    -553,  -553,  -553,   342,   343,     0,   179,  -553,  -553,   207,
       0,     0,     0,   350,   351,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,     0,   190,   191,
       0,     0,     0,     0,     0,     0,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   192,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,     0,     0,     0,   145,   146,   147,   199,   200,   201,
     202,   152,   153,   154,     0,     0,     0,     0,     0,   155,
     156,   157,   203,   204,   160,   205,   162,     0,     0,   206,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   164,   165,   166,   167,   168,   169,   170,
     171,   172,     0,     0,   173,   174,     0,     0,   175,   176,
     177,   178,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,   190,   191,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,     0,     0,
       0,    12,   192,    13,    14,    15,   101,   102,    18,    19,
       0,     0,     0,     0,     0,   103,   104,   105,    23,    24,
      25,    26,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,    33,    34,    35,    36,
      37,    38,     0,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   286,     0,     0,   111,    49,     0,
      50,    51,     0,     0,     0,    53,    54,    55,    56,    57,
      58,    59,     0,     0,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     6,     7,
       0,     9,     0,     0,   112,    10,    11,     0,     0,     0,
      12,     0,    13,    14,    15,   101,   102,    18,    19,     0,
       0,     0,   287,     0,   103,   104,   105,    23,    24,    25,
      26,     0,     0,   106,     0,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     0,    33,    34,    35,    36,    37,
      38,     0,    39,    40,    41,     0,     0,    42,     0,     0,
      43,    44,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   286,     0,     0,   111,    49,     0,    50,
      51,     0,     0,     0,    53,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     6,     7,     0,
       9,     0,     0,   112,    10,    11,     0,     0,     0,    12,
       0,    13,    14,    15,   101,   102,    18,    19,     0,     0,
       0,   528,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    33,    34,    35,    36,    37,    38,
     238,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,    45,    46,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   213,     0,     0,   111,    49,     0,    50,    51,
       0,   634,   240,    53,    54,    55,    56,    57,    58,    59,
       0,     0,    60,   498,     0,     0,   499,   500,     0,     0,
       0,     0,     5,     6,     7,     8,     9,     0,     0,     0,
      10,    11,    61,   241,    63,    12,     0,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,     0,    28,    29,    30,    31,    32,     0,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
       0,     0,    42,     0,     0,    43,    44,     0,    45,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,     0,
       0,    48,    49,     0,    50,    51,     0,    52,     0,    53,
      54,    55,    56,    57,    58,    59,     0,     0,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,    61,    62,
      63,    12,     0,    13,    14,    15,   101,   102,    18,    19,
       0,     0,     0,     0,     0,   103,   104,   105,    23,    24,
      25,    26,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,    33,    34,    35,    36,
      37,    38,   238,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,    45,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   213,     0,     0,   111,    49,     0,
      50,    51,     0,   634,     0,    53,    54,    55,    56,    57,
      58,    59,     0,     0,    60,   498,     0,     0,   499,   500,
       0,     0,     0,     0,     5,     6,     7,     8,     9,     0,
       0,     0,    10,    11,    61,   241,    63,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,    28,     0,    30,    31,
      32,     0,    33,    34,    35,    36,    37,    38,     0,    39,
      40,    41,     0,     0,    42,     0,     0,    43,    44,     0,
      45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      47,     0,     0,    48,    49,     0,    50,    51,     0,    52,
       0,    53,    54,    55,    56,    57,    58,    59,     0,     0,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     9,     0,     0,     0,    10,    11,
      61,    62,    63,    12,     0,    13,    14,    15,   101,   102,
      18,    19,     0,     0,     0,     0,     0,   103,   104,   105,
      23,    24,    25,    26,     0,     0,   106,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,     0,     0,
      42,     0,     0,    43,    44,     0,    45,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   213,     0,     0,   111,
      49,     0,    50,    51,     0,   756,     0,    53,    54,    55,
      56,    57,    58,    59,     0,     0,    60,   498,     0,     0,
     499,   500,     0,     0,     0,     0,     5,     6,     7,     0,
       9,     0,     0,     0,    10,    11,    61,   241,    63,    12,
       0,    13,    14,    15,   101,   102,    18,    19,     0,     0,
       0,     0,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,    45,    46,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   213,     0,     0,   111,    49,     0,    50,    51,
       0,   792,     0,    53,    54,    55,    56,    57,    58,    59,
       0,     0,    60,   498,     0,     0,   499,   500,     0,     0,
       0,     0,     5,     6,     7,     0,     9,     0,     0,     0,
      10,    11,    61,   241,    63,    12,     0,    13,    14,    15,
     101,   102,    18,    19,     0,     0,     0,     0,     0,   103,
     104,   105,    23,    24,    25,    26,     0,     0,   106,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
       0,     0,    42,     0,     0,    43,    44,     0,    45,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   213,     0,
       0,   111,    49,     0,    50,    51,     0,   634,     0,    53,
      54,    55,    56,    57,    58,    59,     0,     0,    60,   498,
       0,     0,   499,   500,     0,     0,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,    61,   241,
      63,    12,     0,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,    33,    34,    35,    36,
      37,    38,   238,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,    45,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   213,     0,     0,   111,    49,     0,
      50,    51,     0,   239,   240,    53,    54,    55,    56,    57,
      58,    59,     0,     0,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    61,   241,    63,    12,     0,    13,
      14,    15,   101,   102,    18,    19,     0,     0,     0,     0,
       0,   103,   104,   105,    23,    24,    25,    26,     0,     0,
     106,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,    33,    34,    35,    36,    37,    38,   238,    39,
      40,    41,     0,     0,    42,     0,     0,    43,    44,     0,
      45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     213,     0,     0,   111,    49,     0,    50,    51,     0,   239,
       0,    53,    54,    55,    56,    57,    58,    59,     0,     0,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     9,     0,     0,     0,    10,    11,
      61,   241,    63,    12,     0,    13,    14,    15,   101,   102,
      18,    19,     0,     0,     0,     0,     0,   103,   104,   105,
      23,    24,    25,    26,     0,     0,   106,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,    33,    34,
      35,    36,    37,    38,   238,    39,    40,    41,     0,     0,
      42,     0,     0,    43,    44,     0,    45,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   213,     0,     0,   111,
      49,     0,    50,    51,     0,     0,   240,    53,    54,    55,
      56,    57,    58,    59,     0,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     6,     7,     0,
       9,     0,     0,     0,    10,    11,    61,   241,    63,    12,
       0,    13,    14,    15,   101,   102,    18,    19,     0,     0,
       0,     0,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    33,    34,    35,    36,    37,    38,
     238,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,    45,    46,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   213,     0,     0,   111,    49,     0,    50,    51,
       0,     0,     0,    53,    54,    55,    56,    57,    58,    59,
       0,     0,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     5,     6,     7,     0,     9,     0,     0,     0,
      10,    11,    61,   241,    63,    12,     0,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,     0,     0,   106,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
       0,     0,    42,     0,     0,    43,    44,     0,    45,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   213,     0,
       0,   111,    49,     0,    50,    51,     0,   522,     0,    53,
      54,    55,    56,    57,    58,    59,     0,     0,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,    61,   241,
      63,    12,     0,    13,    14,    15,   101,   102,    18,    19,
       0,     0,     0,     0,     0,   103,   104,   105,    23,    24,
      25,    26,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,    33,    34,    35,    36,
      37,    38,     0,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,    45,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   213,     0,     0,   111,    49,     0,
      50,    51,     0,   239,     0,    53,    54,    55,    56,    57,
      58,    59,     0,     0,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    61,   241,    63,    12,     0,    13,
      14,    15,   101,   102,    18,    19,     0,     0,     0,     0,
       0,   103,   104,   105,    23,    24,    25,    26,     0,     0,
     106,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,    33,    34,    35,    36,    37,    38,     0,    39,
      40,    41,     0,     0,    42,     0,     0,    43,    44,     0,
      45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     213,     0,     0,   111,    49,     0,    50,    51,     0,   522,
       0,    53,    54,    55,    56,    57,    58,    59,     0,     0,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     9,     0,     0,     0,    10,    11,
      61,   241,    63,    12,     0,    13,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,     0,     0,
      42,     0,     0,    43,    44,     0,    45,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   213,     0,     0,   111,
      49,     0,    50,    51,     0,     0,     0,    53,    54,    55,
      56,    57,    58,    59,     0,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     6,     7,     0,
       9,     0,     0,     0,    10,    11,    61,    62,    63,    12,
       0,    13,    14,    15,   101,   102,    18,    19,     0,     0,
       0,     0,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,    45,    46,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   213,     0,     0,   111,    49,     0,    50,    51,
       0,     0,     0,    53,    54,    55,    56,    57,    58,    59,
       0,     0,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     5,     6,     7,     0,     9,     0,     0,     0,
      10,    11,    61,   241,    63,    12,     0,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,     0,     0,   106,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
       0,     0,    42,     0,     0,    43,    44,     0,    45,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   213,     0,
       0,   111,    49,     0,    50,    51,     0,     0,     0,    53,
      54,    55,    56,    57,    58,    59,     0,     0,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,    61,   241,
      63,    12,     0,    13,    14,    15,   101,   102,    18,    19,
       0,     0,     0,     0,     0,   103,   104,   105,    23,    24,
      25,    26,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,   107,    34,    35,    36,
     108,    38,     0,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   109,     0,     0,   110,     0,     0,   111,    49,     0,
      50,    51,     0,     0,     0,    53,    54,    55,    56,    57,
      58,    59,     0,     0,    60,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     9,     0,     0,     0,    10,    11,
       0,     0,     0,    12,   112,    13,    14,    15,   101,   102,
      18,    19,     0,     0,     0,     0,     0,   103,   104,   105,
      23,    24,    25,    26,     0,     0,   106,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,     0,     0,
      42,     0,     0,    43,    44,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   231,     0,     0,    48,
      49,     0,    50,    51,     0,    52,     0,    53,    54,    55,
      56,    57,    58,    59,     0,     0,    60,     0,     0,     0,
       0,     0,     5,     6,     7,     0,     9,     0,     0,     0,
      10,    11,     0,     0,     0,    12,   112,    13,    14,    15,
     101,   102,    18,    19,     0,     0,     0,     0,     0,   103,
     104,   105,    23,    24,    25,    26,     0,     0,   106,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
       0,     0,    42,     0,     0,    43,    44,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   286,     0,
       0,   333,    49,     0,    50,    51,     0,   334,     0,    53,
      54,    55,    56,    57,    58,    59,     0,     0,    60,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,     0,     0,     0,    12,   112,    13,
      14,    15,   101,   102,    18,    19,     0,     0,     0,     0,
       0,   103,   104,   105,    23,    24,    25,    26,     0,     0,
     106,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,   107,    34,    35,    36,   108,    38,     0,    39,
      40,    41,     0,     0,    42,     0,     0,    43,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     110,     0,     0,   111,    49,     0,    50,    51,     0,     0,
       0,    53,    54,    55,    56,    57,    58,    59,     0,     0,
      60,     0,     0,     0,     0,     0,     5,     6,     7,     0,
       9,     0,     0,     0,    10,    11,     0,     0,     0,    12,
     112,    13,    14,    15,   101,   102,    18,    19,     0,     0,
       0,     0,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   286,     0,     0,   333,    49,     0,    50,    51,
       0,     0,     0,    53,    54,    55,    56,    57,    58,    59,
       0,     0,    60,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,     0,     0,
       0,    12,   112,    13,    14,    15,   101,   102,    18,    19,
       0,     0,     0,     0,     0,   103,   104,   105,    23,    24,
      25,    26,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,    33,    34,    35,    36,
      37,    38,     0,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   877,     0,     0,   111,    49,     0,
      50,    51,     0,     0,     0,    53,    54,    55,    56,    57,
      58,    59,     0,     0,    60,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     9,     0,     0,     0,    10,    11,
       0,     0,     0,    12,   112,    13,    14,    15,   101,   102,
      18,    19,     0,     0,     0,     0,     0,   103,   104,   105,
      23,    24,    25,    26,     0,     0,   106,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,     0,     0,
      42,     0,     0,    43,    44,     0,   337,   338,   339,   340,
     341,   342,   343,     0,     0,   346,   347,     0,     0,     0,
       0,   350,   351,     0,     0,     0,   903,     0,     0,   111,
      49,     0,    50,    51,     0,     0,     0,    53,    54,    55,
      56,    57,    58,    59,     0,     0,    60,     0,     0,   563,
     564,     0,     0,   565,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,     0,     0,   112,   164,   165,   166,
     167,   168,   169,   170,   171,   172,     0,     0,   173,   174,
       0,     0,   175,   176,   177,   178,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,     0,   190,   191,
     571,   572,     0,     0,   573,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   192,   255,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,   173,
     174,     0,     0,   175,   176,   177,   178,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,     0,   190,
     191,   592,   564,     0,     0,   593,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   192,   255,   164,
     165,   166,   167,   168,   169,   170,   171,   172,     0,     0,
     173,   174,     0,     0,   175,   176,   177,   178,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   179,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,     0,
     190,   191,   577,   572,     0,     0,   578,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   192,   255,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,   173,   174,     0,     0,   175,   176,   177,   178,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
       0,   190,   191,   612,   564,     0,     0,   613,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   192,
     255,   164,   165,   166,   167,   168,   169,   170,   171,   172,
       0,     0,   173,   174,     0,     0,   175,   176,   177,   178,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,     0,   190,   191,   615,   572,     0,     0,   616,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     192,   255,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,   173,   174,     0,     0,   175,   176,   177,
     178,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,     0,   190,   191,   627,   564,     0,     0,   628,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   192,   255,   164,   165,   166,   167,   168,   169,   170,
     171,   172,     0,     0,   173,   174,     0,     0,   175,   176,
     177,   178,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,   190,   191,   630,   572,     0,     0,
     631,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   192,   255,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,   173,   174,     0,     0,   175,
     176,   177,   178,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,     0,   190,   191,   656,   564,     0,
       0,   657,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   192,   255,   164,   165,   166,   167,   168,
     169,   170,   171,   172,     0,     0,   173,   174,     0,     0,
     175,   176,   177,   178,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,     0,   190,   191,   659,   572,
       0,     0,   660,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   192,   255,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,   173,   174,     0,
       0,   175,   176,   177,   178,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,     0,   190,   191,   942,
     564,     0,     0,   943,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   192,   255,   164,   165,   166,
     167,   168,   169,   170,   171,   172,     0,     0,   173,   174,
       0,     0,   175,   176,   177,   178,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,     0,   190,   191,
     945,   572,     0,     0,   946,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   192,   255,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,   173,
     174,     0,     0,   175,   176,   177,   178,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,     0,   190,
     191,   953,   564,     0,     0,   954,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   192,   255,   164,
     165,   166,   167,   168,   169,   170,   171,   172,     0,     0,
     173,   174,     0,     0,   175,   176,   177,   178,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   179,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,     0,
     190,   191,   577,   572,     0,     0,   578,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   192,   255,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,   173,   174,     0,     0,   175,   176,   177,   178,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
       0,   190,   191,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   192
};

static const yytype_int16 yycheck[] =
{
       2,    16,    17,   364,    27,    20,    12,    83,     5,     6,
      28,   287,    12,    22,    22,    76,   248,    62,    15,   410,
       7,   390,   292,   336,     4,   221,     8,   388,   415,     2,
     363,     4,   365,    52,    48,   368,   110,   336,    65,     1,
      16,    17,   676,   404,    20,   596,    28,    13,    50,    51,
     468,   425,   428,   292,   428,    52,   389,   418,   280,    65,
     501,   607,   284,   614,   767,    65,    65,    54,   673,    13,
     403,   617,   405,   673,    50,    51,   676,    13,   629,    76,
     477,    27,    37,    38,   460,    26,   419,    11,    12,    98,
      98,   691,   691,   845,    13,    29,    13,   105,   863,    88,
     765,   269,    16,    17,    88,   304,    20,   658,   114,   470,
     528,   119,    79,   446,   114,    90,    16,    17,    90,    25,
      20,   363,   706,   365,   580,   581,   368,    25,    25,   713,
      15,    88,    17,   116,    13,    88,    50,    26,   471,     0,
      90,   116,   143,    90,   116,   387,    51,   389,    53,    54,
      55,    56,    55,   392,   121,    25,   145,   146,   120,    28,
      25,   403,   146,   405,   147,   333,   116,    25,   933,   116,
      25,    25,   924,    88,   108,   417,   841,   419,   619,    25,
      25,   147,    58,    59,   116,   784,   152,   153,   891,   146,
     152,   153,   468,   146,   152,   153,   637,   224,   153,    10,
      11,    12,   143,   445,   446,   437,   152,   153,   152,   153,
     409,     2,   482,     4,   848,   215,   152,   153,   224,   149,
     207,   221,   591,   153,   224,    88,   287,   469,   893,   471,
     149,   146,   601,   152,   153,   152,   153,   252,    49,   254,
     255,   147,   147,   482,   271,   247,   248,   852,   848,   147,
     147,   116,   528,   255,   143,   269,   861,    48,   923,    26,
     149,   861,   116,   863,   720,   271,   663,   664,   644,   643,
     644,   271,   271,   152,   153,   147,   252,   147,   254,   279,
     280,   699,   147,   146,   284,   150,   331,   833,   153,   147,
     287,   336,   147,   147,   149,   268,   150,    90,   109,   153,
      88,   147,   147,   149,   116,   229,   230,   606,    88,    90,
      26,   149,   147,   387,   147,   334,    90,    88,   153,   333,
     111,    88,    88,   116,   149,   147,    88,   372,   373,   149,
     600,   153,    51,   933,    26,    71,    55,   334,   252,   147,
     254,   321,   116,    37,    38,   153,    55,   110,   321,   364,
     113,   114,   252,   326,   254,    88,   110,   365,   146,   113,
     114,   600,   364,    58,    59,    51,   146,   754,   765,    48,
     767,   116,    88,   388,   145,   146,   143,   383,   145,   146,
     146,   389,   149,   383,   146,    90,   388,   700,    17,   404,
     126,   127,   128,   944,   152,   397,    88,   405,   322,   323,
     324,   325,   404,   418,    26,   466,   638,   468,   414,   415,
      55,   419,   145,   146,   414,   415,   418,   331,   229,   230,
      25,   212,   336,   699,   442,   621,    91,   143,   143,   145,
     146,   653,   111,   149,   436,   437,    14,    15,   446,   147,
     147,   443,   833,    71,   841,   842,   815,   258,   259,   425,
     150,   143,   691,   145,   146,   470,   153,   149,   116,   147,
     442,   151,   838,   471,   838,    90,    88,   528,   470,   466,
     443,   468,   263,   144,    55,    88,    71,   268,   269,   452,
      51,   457,    53,    54,    55,    56,   488,    88,   490,    97,
     492,   116,    88,   147,   891,    71,   893,   411,    63,    10,
      51,     8,    53,    54,    55,    56,    88,   876,    88,    13,
      10,   322,   323,   324,   325,   150,   327,   328,   144,   521,
     147,   143,   147,   145,   146,   116,   923,   759,   147,   552,
     321,   528,   145,   146,    51,   326,   149,   147,   147,    51,
      88,    92,   333,    88,   145,   146,   116,   570,    99,   145,
     146,    15,   238,   239,   240,   147,   917,   147,   147,   568,
     568,    63,   147,   145,   146,   145,   146,   576,   576,    10,
     579,   579,   123,   596,   576,   147,   147,   579,   580,   581,
     391,   820,   588,    88,   263,   918,   604,   595,   588,   597,
     269,   614,    10,   147,   144,   597,   602,   145,   146,   390,
     145,   146,   602,   144,   606,   607,   629,   609,   147,   400,
       2,   151,     4,     5,     6,   617,   603,   408,    10,    11,
      12,   621,   604,    15,    16,    17,   822,   118,    20,    88,
      61,    88,   828,    64,    65,   658,   638,    90,   699,   715,
     145,   146,    10,    90,    10,   331,   669,    90,     9,    91,
     336,    10,   443,   653,   333,   700,    48,    49,   703,   704,
      52,   452,    10,   116,   709,   710,   590,   643,   691,   116,
      62,   147,   147,   116,   916,   152,   918,   150,    10,   144,
     111,   112,   116,   144,    76,   147,   145,   146,   145,   146,
     932,   147,   606,    51,   147,    53,    54,    55,    56,   147,
     147,   147,   699,   147,   147,    90,   497,    90,   632,    61,
     121,   147,    64,    65,   147,    10,   722,   109,   720,   111,
     147,   400,   722,    10,   144,   411,    10,    10,   147,   408,
     121,   116,   734,   116,    92,   737,    71,   147,   424,   425,
      98,    99,   428,    56,    57,    58,    59,    62,   754,    64,
      65,    86,    87,    62,   754,    64,    65,   759,   803,   111,
     112,   784,   147,   144,   147,   123,    10,    55,   126,   147,
     147,   457,   774,   775,   460,   777,    55,   779,   780,   590,
     147,    63,    64,    65,   786,   147,   788,   789,   123,   124,
     125,   126,   127,   128,   147,   153,   111,   112,    71,    10,
     591,    10,   111,   112,   149,   490,   149,   492,   147,    51,
     601,    53,    54,    55,    56,   739,    15,     6,   497,   443,
     212,   632,   822,   579,   821,   920,   663,   924,   828,   111,
     112,   833,   716,   919,   503,     7,   522,   229,   230,   820,
     861,    51,   673,    53,    54,    55,    56,   198,    -1,    -1,
      92,   124,   125,   126,   127,   128,    98,    99,    -1,   258,
     252,   858,   254,   255,    -1,    -1,   258,   259,    -1,    -1,
      -1,   263,    -1,   896,   273,    -1,   268,   269,   277,   670,
     671,   123,    92,    -1,   126,    -1,    -1,    -1,    98,    99,
      -1,    -1,    -1,   684,    -1,   287,    -1,   899,   900,   901,
     902,   692,   917,    -1,   906,   907,   908,   149,   910,   911,
     918,    -1,    -1,   123,    -1,   917,   126,   919,   920,    -1,
     606,   944,    63,    64,    65,    -1,   717,   718,   739,   321,
     322,   323,   324,   325,   326,   327,   328,    -1,    -1,   331,
      -1,   333,   334,    -1,   336,   736,    -1,    71,   634,    -1,
     952,   637,    -1,   955,   956,   957,   958,   643,   644,   750,
     751,   752,    86,    87,   966,    -1,    63,    64,    65,    -1,
     111,   112,   364,   676,    -1,   661,   679,    -1,    -1,    -1,
     372,   373,    -1,    -1,    63,    64,    65,    -1,   691,    -1,
      -1,   670,   671,    63,    64,    65,   388,    -1,   390,   391,
     124,   125,   126,   127,   128,   684,    -1,    -1,   400,    -1,
     696,    -1,   404,   692,   111,   112,   408,    63,    64,    65,
      63,    64,    65,   814,   815,    51,   418,    53,    54,    55,
      56,   430,   111,   112,   825,   434,    -1,    -1,   717,   718,
     439,   111,   112,    51,    -1,    53,    54,    55,    56,    -1,
     449,   443,    -1,    -1,    -1,   454,    -1,   736,    -1,    -1,
     452,    -1,    -1,   749,    -1,   111,   112,    -1,   111,   112,
     756,   750,   751,   752,   466,    -1,   468,    -1,   470,    40,
      41,    42,    43,    44,    92,   876,    -1,    -1,    -1,   774,
     775,   882,   777,   884,   779,   780,    -1,    -1,    -1,   890,
      -1,   786,    -1,   788,   789,   497,   792,    -1,    51,    -1,
      53,    54,    55,    56,   297,    -1,    51,    -1,    53,    54,
      55,    56,   305,    -1,     2,   308,     4,   310,   527,   312,
      -1,   314,    10,    11,    12,   814,   528,    -1,    16,    17,
      -1,    -1,    20,    -1,    -1,   848,   825,   850,    -1,    92,
      -1,   854,   838,    -1,    -1,    98,    99,    92,    -1,    -1,
     863,    -1,   865,    98,    99,    -1,    -1,    -1,    -1,    -1,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     123,    -1,    -1,   126,    62,    -1,    -1,    -1,   123,    -1,
      -1,   126,    71,    -1,    -1,    -1,    -1,    -1,   590,   591,
     599,    -1,    -1,   882,    -1,   884,   149,    86,    87,   601,
      -1,   890,    -1,    -1,   899,   900,   901,   902,    -1,    -1,
      -1,   906,   907,   908,   927,   910,   911,    -1,    -1,    -1,
     933,   109,   935,   111,    -1,   938,    -1,    -1,    -1,    -1,
     632,    -1,   121,   122,   123,   124,   125,   126,   127,   128,
      51,    -1,    53,    54,    55,    56,    -1,    -1,    51,   962,
      53,    54,    55,    56,    -1,    -1,    -1,   952,   667,    -1,
     955,   956,   957,   958,    -1,    -1,    -1,    -1,   670,   671,
      -1,   966,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    92,   684,    -1,    -1,    -1,    -1,    98,    -1,    92,
     692,    -1,    -1,    -1,    -1,    98,    -1,   699,   700,    -1,
      -1,   703,   704,    -1,    -1,    -1,    -1,   709,   710,    -1,
      -1,    -1,    -1,    -1,    -1,   717,   718,    -1,   727,    -1,
      -1,    -1,    -1,    -1,   212,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   736,    -1,    -1,   739,    -1,    -1,
      -1,   229,   230,    -1,    -1,    -1,    -1,    -1,   750,   751,
     752,    -1,    -1,    -1,    -1,   764,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   252,    -1,   254,   255,    -1,    -1,
     258,   259,    -1,    -1,    -1,   263,    -1,    -1,    -1,    -1,
     268,   269,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   803,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   814,   815,    -1,    -1,    -1,    -1,    -1,   821,
      -1,    -1,    -1,   825,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   321,   322,   323,   324,   325,   326,   327,
     328,    -1,    -1,   331,    -1,   333,    -1,    -1,   336,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   858,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   876,    -1,   364,    -1,    -1,    -1,
     882,    -1,   884,    -1,   372,   373,    -1,    -1,   890,    71,
      72,    73,    74,    75,    76,    77,    78,    -1,    80,    81,
     388,    -1,   390,   391,    86,    87,    -1,    -1,    -1,    -1,
      -1,    -1,   400,    -1,    -1,   917,   404,    -1,    -1,    -1,
     408,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     418,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   443,    16,    17,    -1,    -1,
      20,    -1,    -1,    -1,   452,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   470,    -1,    -1,    45,    46,    -1,    -1,    -1,
      50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,   497,
      -1,    -1,    -1,    -1,    -1,    -1,     0,     1,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    12,    -1,
      -1,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    -1,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    60,    -1,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   590,   591,    -1,    89,    -1,    -1,    92,    93,
      -1,    95,    96,   601,    98,    -1,   100,   101,   102,   103,
     104,   105,   106,    -1,    -1,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   632,   129,   130,   131,    -1,    -1,
      -1,    -1,     2,    -1,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    -1,    -1,   152,   153,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   238,   239,
     240,   241,   670,   671,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   252,    -1,   254,   255,   684,    -1,    48,    -1,
      -1,    -1,    52,    -1,   692,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   700,    -1,    -1,   703,   704,    -1,    -1,    -1,
      -1,   709,   710,    -1,    -1,    -1,    76,    -1,    -1,   717,
     718,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   736,    -1,
      -1,   739,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   111,   750,   751,   752,    -1,    -1,    -1,    -1,    -1,
      -1,   331,    -1,    -1,    -1,    -1,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,    -1,   364,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   372,   373,    -1,   803,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   814,   815,   388,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   825,    -1,    -1,
      -1,    -1,   402,    -1,   404,    -1,   406,   407,    -1,    -1,
      -1,   411,    -1,    -1,    -1,    -1,    -1,    -1,   418,    -1,
      -1,    -1,   212,    -1,   424,   425,    -1,    -1,   428,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   447,   876,    -1,
      -1,    -1,    -1,    -1,   882,    -1,   884,   457,    -1,    -1,
     460,    -1,   890,    -1,     2,    -1,     4,    -1,    -1,    -1,
     470,    -1,    -1,   263,    -1,    -1,    -1,    15,   268,   269,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   917,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   287,    -1,    -1,
      -1,    -1,     2,    -1,     4,     5,     6,    -1,    -1,    -1,
      48,   511,   512,    -1,    -1,    15,    -1,    -1,    -1,    -1,
       0,    -1,   522,    -1,    -1,    -1,    -1,    -1,     8,     9,
      10,   321,    -1,    13,    14,    15,   326,    17,    -1,    -1,
      -1,    -1,    -1,   333,   334,    -1,    26,    27,    48,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    37,    38,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   111,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     390,    -1,    -1,    -1,    -1,    -1,   606,    -1,    88,    -1,
     400,   111,    -1,    -1,    -1,    -1,    -1,    -1,   408,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   634,    -1,    -1,   637,    -1,    -1,
      -1,    -1,    -1,   643,   644,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   443,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   661,   452,   143,   144,    -1,   146,    -1,    -1,   149,
     150,    -1,   152,   153,   212,    -1,   466,    -1,   468,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   696,    -1,    -1,    -1,
     700,   701,    -1,   703,   704,    -1,    -1,   497,    -1,   709,
     710,    -1,   212,    -1,    -1,    -1,    -1,    -1,    -1,   719,
      -1,    -1,    -1,    -1,    -1,   263,    -1,    -1,    -1,    -1,
     268,   269,    -1,    -1,    -1,    -1,    -1,    -1,   528,    -1,
      -1,    -1,   742,   743,    -1,   745,   746,    -1,    -1,   749,
      -1,    -1,    -1,    -1,    -1,    -1,   756,    -1,    -1,    -1,
      -1,    -1,    -1,   263,    -1,    -1,    -1,    -1,   268,   269,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   321,    -1,    -1,    -1,   287,   326,    -1,
      -1,    -1,   792,    -1,    -1,   333,   796,    -1,   336,    -1,
      -1,   591,    -1,   803,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   601,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   321,    -1,    -1,    -1,    -1,   326,    -1,    -1,    -1,
     830,    -1,    -1,   333,   334,    -1,    -1,    -1,   838,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   390,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   400,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     408,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     670,   671,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     390,    -1,    -1,    -1,   684,    -1,    -1,    -1,    -1,    -1,
     400,    -1,   692,    -1,    -1,   443,    -1,    -1,   408,   699,
      -1,    -1,    -1,    -1,   452,    -1,    -1,   917,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   717,   718,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    -1,   443,    86,    87,   736,    -1,    -1,    -1,
      -1,    -1,   452,    -1,    -1,    -1,    -1,    -1,    -1,   497,
     750,   751,   752,    -1,    -1,    -1,   466,    -1,   468,    -1,
      -1,    -1,    -1,    -1,    -1,   117,    -1,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   497,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   153,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   814,   815,    -1,    -1,   528,    -1,
      -1,   821,    -1,    -1,    -1,   825,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   591,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   601,    -1,    -1,    -1,    -1,   858,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    -1,    -1,    86,    87,   876,    -1,    -1,    -1,
      -1,   591,   882,    -1,   884,    -1,    -1,    -1,    -1,    -1,
     890,   601,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,    -1,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,    -1,    -1,    -1,
      -1,    -1,   670,   671,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   147,   684,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   692,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   700,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     670,   671,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   717,
     718,    -1,    -1,    -1,   684,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   692,    -1,    -1,    -1,    -1,    -1,   736,   699,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   750,   751,   752,    -1,    -1,   717,   718,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   736,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     750,   751,   752,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    -1,    -1,    86,    87,
      -1,    -1,    -1,    -1,    -1,    -1,   814,   815,    -1,    -1,
      -1,    -1,    -1,   821,    -1,    -1,    -1,   825,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
      -1,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,    -1,    -1,    -1,   814,   815,    -1,    -1,    -1,    -1,
      -1,   821,     0,    -1,    -1,   825,    -1,    -1,    -1,    -1,
       8,     9,    10,    -1,    -1,    13,    14,    15,   876,    17,
      -1,    -1,    -1,    -1,   882,    -1,   884,    -1,    -1,    27,
      28,    29,   890,    -1,    -1,    -1,    -1,    -1,   858,    37,
      38,    -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   876,    -1,    -1,    -1,
      -1,    -1,   882,    -1,   884,    -1,    -1,    -1,    -1,    -1,
     890,    -1,    -1,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    -1,    -1,    86,    87,
      88,    -1,    90,    91,    -1,    -1,    -1,    -1,    -1,    97,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   144,   145,   146,   147,
       0,    -1,   150,   151,   152,   153,    -1,    -1,     8,     9,
      10,    -1,    -1,    13,    14,    15,    -1,    17,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    86,    87,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    -1,    86,    87,    88,    -1,
      -1,    91,    -1,    -1,    -1,    -1,   117,    97,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,    -1,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   143,   144,   145,   146,   147,     0,   149,
     150,   151,   152,   153,    -1,    -1,     8,     9,    10,    -1,
      -1,    13,    14,    15,    -1,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    86,    87,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    -1,    -1,    86,    87,    88,    -1,    -1,    91,
      -1,    -1,    -1,    -1,   117,    97,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   108,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   144,   145,   146,   147,     0,    -1,   150,   151,
     152,   153,    -1,    -1,     8,     9,    10,    -1,    -1,    13,
      14,    15,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    -1,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    86,    87,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      -1,    -1,    86,    87,    88,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    97,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,    -1,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   143,
     144,   145,   146,   147,     0,   149,   150,   151,   152,   153,
      -1,    -1,     8,     9,    10,    -1,    -1,    13,    14,    15,
      -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    -1,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    -1,    -1,
      86,    87,    88,    -1,    -1,    91,     0,    -1,    -1,    -1,
      -1,    97,    -1,    -1,     8,     9,    10,    -1,    -1,    -1,
      14,    15,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,    26,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,    37,    38,    -1,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   144,   145,
     146,   147,    -1,   149,   150,   151,   152,   153,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      -1,    -1,    86,    87,    88,    -1,    90,    -1,     0,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     8,     9,    10,    -1,
      -1,    -1,    14,    15,    -1,    17,    -1,    -1,    -1,    -1,
      -1,    -1,   116,   117,    -1,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,    37,    38,    -1,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,   143,
     144,   145,   146,   147,    -1,    -1,   150,    -1,   152,   153,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    -1,    -1,    86,    87,    88,    -1,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   116,   117,    -1,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   144,   145,   146,   147,    -1,    -1,   150,    -1,
     152,   153,     1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,    -1,    15,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    -1,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,
      -1,   100,   101,   102,   103,   104,   105,   106,    -1,    -1,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     129,   130,   131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,
       5,     6,     7,   152,   153,    10,    11,    12,    -1,    14,
      15,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    47,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    -1,   100,   101,   102,   103,   104,
     105,   106,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,   131,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,     5,
       6,     7,    -1,    -1,    10,    11,    12,   152,   153,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    47,    48,    49,    -1,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,
      66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,
      96,    -1,    98,    -1,   100,   101,   102,   103,   104,   105,
     106,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,     3,     4,     5,     6,
       7,    -1,    -1,    10,    11,    12,   152,   153,    15,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      47,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    -1,   100,   101,   102,   103,   104,   105,   106,
      -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   129,   130,   131,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    12,    -1,   152,   153,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    -1,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,
      -1,   100,   101,   102,   103,   104,   105,   106,    -1,    -1,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     129,   130,   131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   144,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   152,   153,     1,    -1,     3,     4,     5,
       6,     7,    -1,     9,    10,    11,    12,    -1,    -1,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    47,    48,    49,    -1,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,
      66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,
      96,    -1,    98,    -1,   100,   101,   102,   103,   104,   105,
     106,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    12,    -1,   152,   153,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,
      48,    49,    -1,    51,    52,    53,    54,    55,    56,    -1,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,
      98,    -1,   100,   101,   102,   103,   104,   105,   106,    -1,
      -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,   131,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   150,    -1,   152,   153,     1,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,
      -1,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    47,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    -1,   100,   101,   102,   103,   104,
     105,   106,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,   131,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   150,    -1,   152,   153,     1,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    47,    48,    49,    -1,    51,
      52,    53,    54,    55,    56,    -1,    58,    59,    60,    -1,
      -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    93,    -1,    95,    96,    -1,    98,    -1,   100,   101,
     102,   103,   104,   105,   106,    -1,    -1,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   144,     1,    -1,     3,     4,     5,     6,     7,
     152,   153,    10,    11,    12,    -1,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,
      48,    49,    -1,    51,    52,    53,    54,    55,    56,    -1,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,
      98,    -1,   100,   101,   102,   103,   104,   105,   106,    -1,
      -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,   130,   131,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,    -1,   152,   153,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,   106,    -1,    -1,   109,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   129,
     130,   131,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,   153,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    60,    -1,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,
      -1,    95,    96,    -1,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,    -1,    -1,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,    -1,   152,   153,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    -1,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,
      66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,
      96,    -1,    -1,    -1,   100,   101,   102,   103,   104,   105,
     106,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    12,   129,   130,   131,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,   153,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      -1,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,
     100,   101,   102,   103,   104,   105,   106,    -1,    -1,   109,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,
      -1,    16,   152,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    47,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    -1,   100,   101,   102,   103,   104,
     105,   106,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130,   131,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   152,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    80,    81,    -1,    -1,    84,
      85,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,    -1,   130,   131,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,    -1,   148,   149,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,    -1,    -1,   109,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,
     131,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,   143,    -1,    11,    12,    -1,    -1,   149,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
      -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   129,   130,   131,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,   143,    -1,    11,    12,
      -1,    -1,   149,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,    -1,    -1,   109,    -1,    -1,    -1,
      -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,   129,   130,   131,    11,
      12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,   149,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    93,    -1,    95,    96,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,    -1,    -1,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,   129,   130,   131,
      11,    12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,   149,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,    -1,    -1,   109,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,
     131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    -1,    -1,    80,    81,    -1,    -1,
      84,    85,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,    -1,   130,   131,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   148,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,
      -1,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,    80,    81,    -1,    -1,    84,    85,    86,    87,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,    -1,   130,   131,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     148,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    -1,    -1,    80,    81,
      -1,    -1,    84,    85,    86,    87,    -1,    -1,    71,    72,
      73,    74,    75,    76,    77,    -1,    98,    80,    81,   101,
      -1,    -1,    -1,    86,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,    -1,   130,   131,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   148,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    -1,    -1,    80,    81,    -1,    -1,    84,    85,
      86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,    -1,   130,   131,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,
      -1,    16,   148,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,   129,    11,    12,    -1,    -1,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,   147,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    -1,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,
      96,    -1,    -1,    -1,   100,   101,   102,   103,   104,   105,
     106,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,   129,    11,    12,    -1,    -1,    -1,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,   147,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
      -1,    -1,   109,   110,    -1,    -1,   113,   114,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    12,   129,   130,   131,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    -1,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,   100,
     101,   102,   103,   104,   105,   106,    -1,    -1,   109,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,   129,   130,
     131,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    -1,   100,   101,   102,   103,   104,
     105,   106,    -1,    -1,   109,   110,    -1,    -1,   113,   114,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    12,   129,   130,   131,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    -1,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,
      -1,   100,   101,   102,   103,   104,   105,   106,    -1,    -1,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
     129,   130,   131,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    -1,   100,   101,   102,
     103,   104,   105,   106,    -1,    -1,   109,   110,    -1,    -1,
     113,   114,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,   129,   130,   131,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    -1,   100,   101,   102,   103,   104,   105,   106,
      -1,    -1,   109,   110,    -1,    -1,   113,   114,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,   129,   130,   131,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,   100,
     101,   102,   103,   104,   105,   106,    -1,    -1,   109,   110,
      -1,    -1,   113,   114,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,   129,   130,
     131,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,   106,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   129,   130,   131,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,
      -1,   100,   101,   102,   103,   104,   105,   106,    -1,    -1,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
     129,   130,   131,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    -1,    99,   100,   101,   102,
     103,   104,   105,   106,    -1,    -1,   109,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,   129,   130,   131,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
      -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,   129,   130,   131,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,   100,
     101,   102,   103,   104,   105,   106,    -1,    -1,   109,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,   129,   130,
     131,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    -1,   100,   101,   102,   103,   104,
     105,   106,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   129,   130,   131,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    -1,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,
      -1,   100,   101,   102,   103,   104,   105,   106,    -1,    -1,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
     129,   130,   131,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,    -1,    -1,   109,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,   129,   130,   131,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
      -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,   129,   130,   131,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    -1,    -1,   100,
     101,   102,   103,   104,   105,   106,    -1,    -1,   109,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,   129,   130,
     131,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
      -1,    -1,    -1,    16,   129,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    -1,   100,   101,   102,
     103,   104,   105,   106,    -1,    -1,   109,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,    -1,    -1,    -1,    16,   129,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      -1,    -1,    63,    -1,    -1,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,   100,
     101,   102,   103,   104,   105,   106,    -1,    -1,   109,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,    -1,    -1,    -1,    16,   129,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    -1,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,    -1,    -1,
     109,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,
     129,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
      -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,
      -1,    16,   129,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
      -1,    -1,    -1,    16,   129,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    80,    81,    -1,    -1,    -1,
      -1,    86,    87,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,    -1,    -1,   109,    -1,    -1,    51,
      52,    -1,    -1,    55,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,    -1,    -1,   129,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    -1,    -1,    80,    81,
      -1,    -1,    84,    85,    86,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,    -1,   130,   131,
      51,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   148,   149,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    80,
      81,    -1,    -1,    84,    85,    86,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,    -1,   130,
     131,    51,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,   149,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    -1,    -1,
      80,    81,    -1,    -1,    84,    85,    86,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,    -1,
     130,   131,    51,    52,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,   149,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    80,    81,    -1,    -1,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
      -1,   130,   131,    51,    52,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,
     149,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,    80,    81,    -1,    -1,    84,    85,    86,    87,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,    -1,   130,   131,    51,    52,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     148,   149,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    80,    81,    -1,    -1,    84,    85,    86,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,    -1,   130,   131,    51,    52,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   148,   149,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    -1,    -1,    80,    81,    -1,    -1,    84,    85,
      86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,    -1,   130,   131,    51,    52,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   148,   149,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    80,    81,    -1,    -1,    84,
      85,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,    -1,   130,   131,    51,    52,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   148,   149,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    -1,    -1,    80,    81,    -1,    -1,
      84,    85,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,    -1,   130,   131,    51,    52,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   148,   149,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    80,    81,    -1,
      -1,    84,    85,    86,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,    -1,   130,   131,    51,
      52,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   148,   149,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    -1,    -1,    80,    81,
      -1,    -1,    84,    85,    86,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,    -1,   130,   131,
      51,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   148,   149,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    80,
      81,    -1,    -1,    84,    85,    86,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,    -1,   130,
     131,    51,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,   149,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    -1,    -1,
      80,    81,    -1,    -1,    84,    85,    86,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,    -1,
     130,   131,    51,    52,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,   149,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    80,    81,    -1,    -1,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
      -1,   130,   131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   155,   156,     0,     1,     3,     4,     5,     6,     7,
      11,    12,    16,    18,    19,    20,    21,    22,    23,    24,
      30,    31,    32,    33,    34,    35,    36,    39,    45,    46,
      47,    48,    49,    51,    52,    53,    54,    55,    56,    58,
      59,    60,    63,    66,    67,    69,    70,    89,    92,    93,
      95,    96,    98,   100,   101,   102,   103,   104,   105,   106,
     109,   129,   130,   131,   157,   158,   159,   164,   166,   167,
     169,   170,   173,   174,   176,   177,   178,   180,   181,   190,
     203,   221,   240,   241,   251,   252,   256,   257,   258,   265,
     266,   267,   269,   270,   271,   272,   273,   274,   297,   310,
     159,    21,    22,    30,    31,    32,    39,    51,    55,    86,
      89,    92,   129,   182,   183,   203,   221,   271,   274,   297,
     183,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    45,    46,    47,    48,    49,
      50,    51,    52,    55,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    80,    81,    84,    85,    86,    87,    98,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     130,   131,   148,   149,   184,   188,   189,   273,   292,    33,
      34,    35,    36,    48,    49,    51,    55,   101,   184,   185,
     186,   267,   204,    89,   167,   168,   181,   221,   271,   272,
     274,   168,   152,   153,   168,   301,   306,   307,   309,   208,
     210,    89,   174,   181,   221,   226,   271,   274,    57,    98,
      99,   130,   173,   190,   191,   196,   199,   201,   295,   296,
     196,   196,   149,   197,   198,   149,   193,   197,   149,   302,
     307,   185,   160,   143,   190,   221,   190,    55,     1,    92,
     162,   163,   164,   175,   176,   310,   167,   206,   192,   201,
     295,   310,   191,   294,   295,   310,    89,   147,   180,   221,
     271,   274,   207,    53,    54,    56,    63,   105,   184,   268,
      62,    64,    65,   111,   112,   253,   254,    63,   253,    63,
     253,    63,   253,    61,   253,    58,    59,   169,   190,   190,
     301,   309,    40,    41,    42,    43,    44,    37,    38,    28,
     238,   116,   147,    92,    98,   177,   116,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      86,    87,   117,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,    88,   145,   146,    88,   146,   300,    26,
     143,   242,    90,    90,   193,   197,   242,   167,    51,    55,
     182,    58,    59,     1,   120,   275,   306,    88,   145,   146,
     217,   293,   218,   300,   105,   147,   161,   162,    55,    13,
     222,   306,   116,    88,   145,   146,    90,    90,   222,   308,
     301,    17,   245,   152,   168,   168,    55,    88,   145,   146,
      25,   191,   191,   191,    91,   147,   200,   310,   147,   200,
     196,   302,   303,   196,   195,   196,   201,   295,   310,   167,
     303,   167,   165,   143,   162,    88,   146,    90,   164,   175,
     150,   301,   309,   303,   205,   303,   151,   147,   305,   307,
     147,   305,   144,   305,    55,   177,   178,   179,   147,    88,
     145,   146,    51,    53,    54,    55,    56,    92,    98,    99,
     123,   126,   149,   236,   278,   279,   280,   281,   282,   283,
     286,   287,   288,   289,   290,    63,   254,   255,   110,   113,
     114,   260,   261,   262,   263,    62,   254,    63,    63,    63,
      61,    71,    71,   159,   168,   168,   168,   168,   164,   167,
     167,   239,    98,   169,   191,   201,   202,   175,   147,   180,
     147,   166,   169,   181,   190,   191,   202,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,    51,    52,    55,   188,   193,   298,   299,
     195,    51,    52,    55,   188,   193,   298,    51,    55,   298,
     244,   243,   169,   190,   169,   190,    97,   171,   215,   306,
     276,   214,    51,    55,   182,   298,   195,   298,   161,   167,
     149,   277,   278,   219,   187,    10,     8,   247,   310,   162,
      13,   190,    51,    55,   195,    51,    55,   162,   259,   260,
     245,   201,    10,    27,   223,   306,   223,    51,    55,   195,
      51,    55,   212,   191,    98,   191,   199,   260,   295,   296,
     303,   150,   303,   147,   147,   303,   185,   157,   144,   190,
     303,   164,   303,   295,   177,   179,    51,    55,   195,    51,
      55,   116,    51,    92,    98,   227,   228,   229,   280,   278,
      29,   108,   237,   147,   291,   310,   147,   291,    51,   147,
     291,    51,    63,   162,   264,   261,   110,   263,   190,   190,
      79,   121,   231,   232,   310,   191,   147,   303,   179,   147,
     116,    44,   302,    90,    90,   193,   197,   302,   304,    90,
      90,   193,   194,   197,   310,   194,   197,   231,   231,    44,
     172,   306,   168,   161,   304,    10,   303,   278,   161,   306,
     184,   185,   191,   202,   248,   310,    15,   225,   310,    14,
     224,   225,    90,    90,   304,    90,    90,   225,    10,   147,
     222,   209,   211,   304,   168,   191,    98,   191,   200,   295,
     144,   305,   304,   191,   229,   147,   280,   147,   303,   233,
     302,   162,   162,   281,   286,   288,   290,   282,   283,   288,
     282,   144,   162,    51,   230,   233,   282,   284,   285,   288,
     290,   162,    98,   191,   179,   190,   118,   169,   190,   169,
     190,   171,   151,    90,   169,   190,   169,   190,   171,   242,
     238,   162,   162,   190,   231,   216,   306,    10,   303,    10,
     220,    91,   249,   310,   162,     9,   250,   310,   168,    10,
      90,    10,   191,   162,   162,   162,   223,   191,   147,   303,
     228,   147,    98,   227,   150,   152,    10,   144,   147,   291,
     147,   291,   147,   291,   147,   291,   291,   144,   116,   233,
     121,   147,   291,   147,   291,   147,   291,    10,   191,   190,
     169,   190,    10,   144,   162,   161,   277,    89,   181,   221,
     271,   274,   222,   162,   222,   225,   245,   246,    10,    10,
     213,   147,   228,   147,   280,    51,   234,   235,   279,   282,
     288,   282,   282,    89,   221,   121,   285,   288,   282,   284,
     288,   282,   144,    10,   161,    55,    88,   145,   146,   162,
     162,   162,   228,   147,   147,   302,   291,   147,   291,   291,
     291,    55,    88,   147,   291,   147,   291,   291,   147,   291,
     291,    10,    51,    55,   195,    51,    55,   247,   224,    10,
     228,   235,   282,    51,    55,   282,   288,   282,   282,   304,
     291,   291,   147,   291,   291,   291,   282,   291
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (p, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, p)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, p); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, parser_state *p)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, p)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    parser_state *p;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (p);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, parser_state *p)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, p)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    parser_state *p;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, p);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, parser_state *p)
#else
static void
yy_reduce_print (yyvsp, yyrule, p)
    YYSTYPE *yyvsp;
    int yyrule;
    parser_state *p;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , p);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, p); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, parser_state *p)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, p)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    parser_state *p;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (p);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (parser_state *p);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (parser_state *p)
#else
int
yyparse (p)
    parser_state *p;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 1146 "src/parse.y"
    {
		     p->lstate = EXPR_BEG;
		     if (!p->locals) p->locals = cons(0,0);
		   ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 1151 "src/parse.y"
    {
		      p->tree = new_scope(p, (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 1157 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(1) - (2)].nd);
		    ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 1163 "src/parse.y"
    {
		      (yyval.nd) = new_begin(p, 0);
		    ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 1167 "src/parse.y"
    {
		      (yyval.nd) = new_begin(p, (yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 1171 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (3)].nd), newline_node((yyvsp[(3) - (3)].nd)));
		    ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 1175 "src/parse.y"
    {
		      (yyval.nd) = new_begin(p, 0);
		    ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 1182 "src/parse.y"
    {
		      (yyval.nd) = local_switch(p);
		    ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 1186 "src/parse.y"
    {
		      yyerror(p, "BEGIN not supported");
		      local_resume(p, (yyvsp[(2) - (5)].nd));
		      (yyval.nd) = 0;
		    ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 1197 "src/parse.y"
    {
		      if ((yyvsp[(2) - (4)].nd)) {
			(yyval.nd) = new_rescue(p, (yyvsp[(1) - (4)].nd), (yyvsp[(2) - (4)].nd), (yyvsp[(3) - (4)].nd));
		      }
		      else if ((yyvsp[(3) - (4)].nd)) {
			yywarn(p, "else without rescue is useless");
			(yyval.nd) = push((yyvsp[(1) - (4)].nd), (yyvsp[(3) - (4)].nd));
		      }
		      else {
			(yyval.nd) = (yyvsp[(1) - (4)].nd);
		      }
		      if ((yyvsp[(4) - (4)].nd)) {
			if ((yyval.nd)) {
			  (yyval.nd) = new_ensure(p, (yyval.nd), (yyvsp[(4) - (4)].nd));
			}
			else {
			  (yyval.nd) = push((yyvsp[(4) - (4)].nd), new_nil(p));
			}
		      }
		    ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 1220 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(1) - (2)].nd);
		    ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 1226 "src/parse.y"
    {
		      (yyval.nd) = new_begin(p, 0);
		    ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 1230 "src/parse.y"
    {
		      (yyval.nd) = new_begin(p, (yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 1234 "src/parse.y"
    {
			(yyval.nd) = push((yyvsp[(1) - (3)].nd), newline_node((yyvsp[(3) - (3)].nd)));
		    ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 1238 "src/parse.y"
    {
		      (yyval.nd) = new_begin(p, (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 1243 "src/parse.y"
    {p->lstate = EXPR_FNAME;;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 1244 "src/parse.y"
    {
		      (yyval.nd) = new_alias(p, (yyvsp[(2) - (4)].id), (yyvsp[(4) - (4)].id));
		    ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 1248 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (2)].nd);
		    ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 1252 "src/parse.y"
    {
			(yyval.nd) = new_if(p, cond((yyvsp[(3) - (3)].nd)), (yyvsp[(1) - (3)].nd), 0);
		    ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 1256 "src/parse.y"
    {
		      (yyval.nd) = new_unless(p, cond((yyvsp[(3) - (3)].nd)), (yyvsp[(1) - (3)].nd), 0);
		    ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 1260 "src/parse.y"
    {
		      (yyval.nd) = new_while(p, cond((yyvsp[(3) - (3)].nd)), (yyvsp[(1) - (3)].nd));
		    ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 1264 "src/parse.y"
    {
		      (yyval.nd) = new_until(p, cond((yyvsp[(3) - (3)].nd)), (yyvsp[(1) - (3)].nd));
		    ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 1268 "src/parse.y"
    {
		      (yyval.nd) = new_rescue(p, (yyvsp[(1) - (3)].nd), list1(list3(0, 0, (yyvsp[(3) - (3)].nd))), 0);
		    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 1272 "src/parse.y"
    {
		      yyerror(p, "END not suported");
		      (yyval.nd) = new_postexe(p, (yyvsp[(3) - (4)].nd));
		    ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 1278 "src/parse.y"
    {
		      (yyval.nd) = new_masgn(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 1282 "src/parse.y"
    {
		      (yyval.nd) = new_op_asgn(p, (yyvsp[(1) - (3)].nd), (yyvsp[(2) - (3)].id), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 1286 "src/parse.y"
    {
		      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[(1) - (6)].nd), intern("[]",2), (yyvsp[(3) - (6)].nd)), (yyvsp[(5) - (6)].id), (yyvsp[(6) - (6)].nd));
		    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 1290 "src/parse.y"
    {
		      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[(1) - (5)].nd), (yyvsp[(3) - (5)].id), 0), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].nd));
		    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 1294 "src/parse.y"
    {
		      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[(1) - (5)].nd), (yyvsp[(3) - (5)].id), 0), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].nd));
		    ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 1298 "src/parse.y"
    {
		      yyerror(p, "constant re-assignment");
		      (yyval.nd) = 0;
		    ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 1303 "src/parse.y"
    {
		      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[(1) - (5)].nd), (yyvsp[(3) - (5)].id), 0), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].nd));
		    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 1307 "src/parse.y"
    {
		      backref_error(p, (yyvsp[(1) - (3)].nd));
		      (yyval.nd) = new_begin(p, 0);
		    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 1312 "src/parse.y"
    {
		      (yyval.nd) = new_asgn(p, (yyvsp[(1) - (3)].nd), new_array(p, (yyvsp[(3) - (3)].nd)));
		    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 1316 "src/parse.y"
    {
		      (yyval.nd) = new_masgn(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 1320 "src/parse.y"
    {
		      (yyval.nd) = new_masgn(p, (yyvsp[(1) - (3)].nd), new_array(p, (yyvsp[(3) - (3)].nd)));
		    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 1327 "src/parse.y"
    {
		      (yyval.nd) = new_asgn(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 1331 "src/parse.y"
    {
		      (yyval.nd) = new_asgn(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 1339 "src/parse.y"
    {
		      (yyval.nd) = new_and(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 1343 "src/parse.y"
    {
		      (yyval.nd) = new_or(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 1347 "src/parse.y"
    {
		      (yyval.nd) = call_uni_op(p, cond((yyvsp[(3) - (3)].nd)), "!");
		    ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 1351 "src/parse.y"
    {
		      (yyval.nd) = call_uni_op(p, cond((yyvsp[(2) - (2)].nd)), "!");
		    ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 1358 "src/parse.y"
    {
		      if (!(yyvsp[(1) - (1)].nd)) (yyval.nd) = new_nil(p);
		      else (yyval.nd) = (yyvsp[(1) - (1)].nd);
		    ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 1373 "src/parse.y"
    {
		      local_nest(p);
		    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1379 "src/parse.y"
    {
		      (yyval.nd) = new_block(p, (yyvsp[(3) - (5)].nd), (yyvsp[(4) - (5)].nd));
		      local_unnest(p);
		    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 1386 "src/parse.y"
    {
		      (yyval.nd) = new_fcall(p, (yyvsp[(1) - (2)].id), (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 1390 "src/parse.y"
    {
		      args_with_block(p, (yyvsp[(2) - (3)].nd), (yyvsp[(3) - (3)].nd));
		      (yyval.nd) = new_fcall(p, (yyvsp[(1) - (3)].id), (yyvsp[(2) - (3)].nd));
		    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 1395 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (4)].nd), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].nd));
		    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 1399 "src/parse.y"
    {
		      args_with_block(p, (yyvsp[(4) - (5)].nd), (yyvsp[(5) - (5)].nd));
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (5)].nd), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].nd));
		   ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 1404 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (4)].nd), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].nd));
		    ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 1408 "src/parse.y"
    {
		      args_with_block(p, (yyvsp[(4) - (5)].nd), (yyvsp[(5) - (5)].nd));
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (5)].nd), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].nd));
		    ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 1413 "src/parse.y"
    {
		      (yyval.nd) = new_super(p, (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 1417 "src/parse.y"
    {
		      (yyval.nd) = new_yield(p, (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 1421 "src/parse.y"
    {
		      (yyval.nd) = new_return(p, ret_args(p, (yyvsp[(2) - (2)].nd)));
		    ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1425 "src/parse.y"
    {
		      (yyval.nd) = new_break(p, ret_args(p, (yyvsp[(2) - (2)].nd)));
		    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1429 "src/parse.y"
    {
		      (yyval.nd) = new_next(p, ret_args(p, (yyvsp[(2) - (2)].nd)));
		    ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 1435 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(1) - (1)].nd);
		    ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1439 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (3)].nd);
		    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1446 "src/parse.y"
    {
		      (yyval.nd) = list1((yyvsp[(2) - (3)].nd));
		    ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1452 "src/parse.y"
    {
		      (yyval.nd) = list1((yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 1456 "src/parse.y"
    {
		      (yyval.nd) = list1(push((yyvsp[(1) - (2)].nd),(yyvsp[(2) - (2)].nd)));
		    ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1460 "src/parse.y"
    {
		      (yyval.nd) = list2((yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1464 "src/parse.y"
    {
		      (yyval.nd) = list3((yyvsp[(1) - (5)].nd), (yyvsp[(3) - (5)].nd), (yyvsp[(5) - (5)].nd));
		    ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1468 "src/parse.y"
    {
		      (yyval.nd) = list2((yyvsp[(1) - (2)].nd), new_nil(p));
		    ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1472 "src/parse.y"
    {
		      (yyval.nd) = list3((yyvsp[(1) - (4)].nd), new_nil(p), (yyvsp[(4) - (4)].nd));
		    ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1476 "src/parse.y"
    {
		      (yyval.nd) = list2(0, (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1480 "src/parse.y"
    {
		      (yyval.nd) = list3(0, (yyvsp[(2) - (4)].nd), (yyvsp[(4) - (4)].nd));
		    ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1484 "src/parse.y"
    {
		      (yyval.nd) = list2(0, new_nil(p));
		    ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1488 "src/parse.y"
    {
		      (yyval.nd) = list3(0, new_nil(p), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 1495 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (3)].nd);
		    ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1501 "src/parse.y"
    {
		      (yyval.nd) = list1((yyvsp[(1) - (2)].nd));
		    ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1505 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (3)].nd), (yyvsp[(2) - (3)].nd));
		    ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1511 "src/parse.y"
    {
		      (yyval.nd) = list1((yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1515 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (2)].nd), (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1521 "src/parse.y"
    {
		      assignable(p, (yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1525 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (4)].nd), intern("[]",2), (yyvsp[(3) - (4)].nd));
		    ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1529 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].id), 0);
		    ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1533 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].id), 0);
		    ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1537 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].id), 0);
		    ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1541 "src/parse.y"
    {
		      if (p->in_def || p->in_single)
			yyerror(p, "dynamic constant assignment");
		      (yyval.nd) = new_colon2(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].id));
		    ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1547 "src/parse.y"
    {
		      if (p->in_def || p->in_single)
			yyerror(p, "dynamic constant assignment");
		      (yyval.nd) = new_colon3(p, (yyvsp[(2) - (2)].id));
		    ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1553 "src/parse.y"
    {
		      backref_error(p, (yyvsp[(1) - (1)].nd));
		      (yyval.nd) = 0;
		    ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1560 "src/parse.y"
    {
		      assignable(p, (yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1564 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (4)].nd), intern("[]",2), (yyvsp[(3) - (4)].nd));
		    ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1568 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].id), 0);
		    ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1572 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].id), 0);
		    ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 1576 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].id), 0);
		    ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1580 "src/parse.y"
    {
		      if (p->in_def || p->in_single)
			yyerror(p, "dynamic constant assignment");
		      (yyval.nd) = new_colon2(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].id));
		    ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1586 "src/parse.y"
    {
		      if (p->in_def || p->in_single)
			yyerror(p, "dynamic constant assignment");
		      (yyval.nd) = new_colon3(p, (yyvsp[(2) - (2)].id));
		    ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1592 "src/parse.y"
    {
		      backref_error(p, (yyvsp[(1) - (1)].nd));
		      (yyval.nd) = 0;
		    ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1599 "src/parse.y"
    {
		      yyerror(p, "class/module name must be CONSTANT");
		    ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1606 "src/parse.y"
    {
		      (yyval.nd) = cons((node*)1, nsym((yyvsp[(2) - (2)].id)));
		    ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1610 "src/parse.y"
    {
		      (yyval.nd) = cons((node*)0, nsym((yyvsp[(1) - (1)].id)));
		    ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1614 "src/parse.y"
    {
		      (yyval.nd) = cons((yyvsp[(1) - (3)].nd), nsym((yyvsp[(3) - (3)].id)));
		    ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1623 "src/parse.y"
    {
		      p->lstate = EXPR_ENDFN;
		      (yyval.id) = (yyvsp[(1) - (1)].id);
		    ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1628 "src/parse.y"
    {
		      p->lstate = EXPR_ENDFN;
		      (yyval.id) = (yyvsp[(1) - (1)].id);
		    ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1639 "src/parse.y"
    {
		      (yyval.nd) = new_undef(p, (yyvsp[(1) - (1)].id));
		    ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1642 "src/parse.y"
    {p->lstate = EXPR_FNAME;;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1643 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (4)].nd), nsym((yyvsp[(4) - (4)].id)));
		    ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1648 "src/parse.y"
    { (yyval.id) = intern_c('|'); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1649 "src/parse.y"
    { (yyval.id) = intern_c('^'); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1650 "src/parse.y"
    { (yyval.id) = intern_c('&'); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1651 "src/parse.y"
    { (yyval.id) = intern("<=>",3); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1652 "src/parse.y"
    { (yyval.id) = intern("==",2); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1653 "src/parse.y"
    { (yyval.id) = intern("===",3); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1654 "src/parse.y"
    { (yyval.id) = intern("=~",2); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1655 "src/parse.y"
    { (yyval.id) = intern("!~",2); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1656 "src/parse.y"
    { (yyval.id) = intern_c('>'); ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1657 "src/parse.y"
    { (yyval.id) = intern(">=",2); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1658 "src/parse.y"
    { (yyval.id) = intern_c('<'); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1659 "src/parse.y"
    { (yyval.id) = intern("<=",2); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1660 "src/parse.y"
    { (yyval.id) = intern("!=",2); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1661 "src/parse.y"
    { (yyval.id) = intern("<<",2); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1662 "src/parse.y"
    { (yyval.id) = intern(">>",2); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1663 "src/parse.y"
    { (yyval.id) = intern_c('+'); ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1664 "src/parse.y"
    { (yyval.id) = intern_c('-'); ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1665 "src/parse.y"
    { (yyval.id) = intern_c('*'); ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1666 "src/parse.y"
    { (yyval.id) = intern_c('*'); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1667 "src/parse.y"
    { (yyval.id) = intern_c('/'); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1668 "src/parse.y"
    { (yyval.id) = intern_c('%'); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1669 "src/parse.y"
    { (yyval.id) = intern("**",2); ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1670 "src/parse.y"
    { (yyval.id) = intern_c('!'); ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1671 "src/parse.y"
    { (yyval.id) = intern_c('~'); ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1672 "src/parse.y"
    { (yyval.id) = intern("+@",2); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1673 "src/parse.y"
    { (yyval.id) = intern("-@",2); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1674 "src/parse.y"
    { (yyval.id) = intern("[]",2); ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1675 "src/parse.y"
    { (yyval.id) = intern("[]=",3); ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1676 "src/parse.y"
    { (yyval.id) = intern_c('`'); ;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1694 "src/parse.y"
    {
		      (yyval.nd) = new_asgn(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1698 "src/parse.y"
    {
		      (yyval.nd) = new_asgn(p, (yyvsp[(1) - (5)].nd), new_rescue(p, (yyvsp[(3) - (5)].nd), list1(list3(0, 0, (yyvsp[(5) - (5)].nd))), 0));
		    ;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1702 "src/parse.y"
    {
		      (yyval.nd) = new_op_asgn(p, (yyvsp[(1) - (3)].nd), (yyvsp[(2) - (3)].id), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1706 "src/parse.y"
    {
		      (yyval.nd) = new_op_asgn(p, (yyvsp[(1) - (5)].nd), (yyvsp[(2) - (5)].id), new_rescue(p, (yyvsp[(3) - (5)].nd), list1(list3(0, 0, (yyvsp[(5) - (5)].nd))), 0));
		    ;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1710 "src/parse.y"
    {
		      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[(1) - (6)].nd), intern("[]",2), (yyvsp[(3) - (6)].nd)), (yyvsp[(5) - (6)].id), (yyvsp[(6) - (6)].nd));
		    ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1714 "src/parse.y"
    {
		      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[(1) - (5)].nd), (yyvsp[(3) - (5)].id), 0), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].nd));
		    ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1718 "src/parse.y"
    {
		      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[(1) - (5)].nd), (yyvsp[(3) - (5)].id), 0), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].nd));
		    ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1722 "src/parse.y"
    {
		      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[(1) - (5)].nd), (yyvsp[(3) - (5)].id), 0), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].nd));
		    ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1726 "src/parse.y"
    {
		      yyerror(p, "constant re-assignment");
		      (yyval.nd) = new_begin(p, 0);
		    ;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1731 "src/parse.y"
    {
		      yyerror(p, "constant re-assignment");
		      (yyval.nd) = new_begin(p, 0);
		    ;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1736 "src/parse.y"
    {
		      backref_error(p, (yyvsp[(1) - (3)].nd));
		      (yyval.nd) = new_begin(p, 0);
		    ;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1741 "src/parse.y"
    {
		      (yyval.nd) = new_dot2(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1745 "src/parse.y"
    {
		      (yyval.nd) = new_dot3(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1749 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "+", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1753 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "-", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1757 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "*", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1761 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "/", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1765 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "%", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1769 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "**", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1773 "src/parse.y"
    {
		      (yyval.nd) = call_uni_op(p, call_bin_op(p, (yyvsp[(2) - (4)].nd), "**", (yyvsp[(4) - (4)].nd)), "-@");
		    ;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1777 "src/parse.y"
    {
		      (yyval.nd) = call_uni_op(p, call_bin_op(p, (yyvsp[(2) - (4)].nd), "**", (yyvsp[(4) - (4)].nd)), "-@");
		    ;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1781 "src/parse.y"
    {
		      (yyval.nd) = call_uni_op(p, (yyvsp[(2) - (2)].nd), "+@");
		    ;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1785 "src/parse.y"
    {
		      (yyval.nd) = call_uni_op(p, (yyvsp[(2) - (2)].nd), "-@");
		    ;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1789 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "|", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1793 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "^", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1797 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "&", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 1801 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "<=>", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1805 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), ">", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1809 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), ">=", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1813 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "<", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1817 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "<=", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1821 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "==", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1825 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "===", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1829 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "!=", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1833 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "=~", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1837 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "!~", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1841 "src/parse.y"
    {
		      (yyval.nd) = call_uni_op(p, cond((yyvsp[(2) - (2)].nd)), "!");
		    ;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1845 "src/parse.y"
    {
		      (yyval.nd) = call_uni_op(p, cond((yyvsp[(2) - (2)].nd)), "~");
		    ;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1849 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), "<<", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1853 "src/parse.y"
    {
		      (yyval.nd) = call_bin_op(p, (yyvsp[(1) - (3)].nd), ">>", (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1857 "src/parse.y"
    {
		      (yyval.nd) = new_and(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1861 "src/parse.y"
    {
		      (yyval.nd) = new_or(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1865 "src/parse.y"
    {
		      (yyval.nd) = new_if(p, cond((yyvsp[(1) - (6)].nd)), (yyvsp[(3) - (6)].nd), (yyvsp[(6) - (6)].nd));
		    ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1869 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(1) - (1)].nd);
		    ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1875 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(1) - (1)].nd);
		      if (!(yyval.nd)) (yyval.nd) = new_nil(p);
		    ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1883 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(1) - (2)].nd);
		    ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1887 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (4)].nd), new_hash(p, (yyvsp[(3) - (4)].nd)));
		    ;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1891 "src/parse.y"
    {
		      (yyval.nd) = cons(new_hash(p, (yyvsp[(1) - (2)].nd)), 0);
		    ;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1897 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (3)].nd);
		    ;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 1909 "src/parse.y"
    {
		      (yyval.nd) = cons((yyvsp[(1) - (2)].nd),0);
		    ;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 1913 "src/parse.y"
    {
		      (yyval.nd) = cons(push((yyvsp[(1) - (4)].nd), new_hash(p, (yyvsp[(3) - (4)].nd))), 0);
		    ;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 1917 "src/parse.y"
    {
		      (yyval.nd) = cons(list1(new_hash(p, (yyvsp[(1) - (2)].nd))), 0);
		    ;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 1923 "src/parse.y"
    {
		      (yyval.nd) = cons(list1((yyvsp[(1) - (1)].nd)), 0);
		    ;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 1927 "src/parse.y"
    {
		      (yyval.nd) = cons((yyvsp[(1) - (2)].nd), (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 1931 "src/parse.y"
    {
		      (yyval.nd) = cons(list1(new_hash(p, (yyvsp[(1) - (2)].nd))), (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 1935 "src/parse.y"
    {
		      (yyval.nd) = cons(push((yyvsp[(1) - (4)].nd), new_hash(p, (yyvsp[(3) - (4)].nd))), (yyvsp[(4) - (4)].nd));
		    ;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 1939 "src/parse.y"
    {
		      (yyval.nd) = cons(0, (yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 1944 "src/parse.y"
    {
		      (yyval.stack) = p->cmdarg_stack;
		      CMDARG_PUSH(1);
		    ;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 1949 "src/parse.y"
    {
		      p->cmdarg_stack = (yyvsp[(1) - (2)].stack);
		      (yyval.nd) = (yyvsp[(2) - (2)].nd);
		    ;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 1956 "src/parse.y"
    {
		      (yyval.nd) = new_block_arg(p, (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 1962 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (2)].nd);
		    ;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 1966 "src/parse.y"
    {
		      (yyval.nd) = 0;
		    ;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 1972 "src/parse.y"
    {
		      (yyval.nd) = cons((yyvsp[(1) - (1)].nd), 0);
		    ;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 1976 "src/parse.y"
    {
		      (yyval.nd) = cons(new_splat(p, (yyvsp[(2) - (2)].nd)), 0);
		    ;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 1980 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 1984 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (4)].nd), new_splat(p, (yyvsp[(4) - (4)].nd)));
		    ;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 1988 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (4)].nd), (yyvsp[(4) - (4)].nd));
		    ;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 1992 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (5)].nd), new_splat(p, (yyvsp[(5) - (5)].nd)));
		    ;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 1998 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 2002 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (4)].nd), new_splat(p, (yyvsp[(4) - (4)].nd)));
		    ;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 2006 "src/parse.y"
    {
		      (yyval.nd) = list1(new_splat(p, (yyvsp[(2) - (2)].nd)));
		    ;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 2019 "src/parse.y"
    {
		      (yyval.nd) = new_fcall(p, (yyvsp[(1) - (1)].id), 0);
		    ;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 2023 "src/parse.y"
    {
		      (yyvsp[(1) - (1)].stack) = p->cmdarg_stack;
		      p->cmdarg_stack = 0;
		    ;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 2029 "src/parse.y"
    {
		      p->cmdarg_stack = (yyvsp[(1) - (4)].stack);
		      (yyval.nd) = (yyvsp[(3) - (4)].nd);
		    ;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 2033 "src/parse.y"
    {p->lstate = EXPR_ENDARG;;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 2034 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (4)].nd);
		    ;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 2037 "src/parse.y"
    {p->lstate = EXPR_ENDARG;;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 2038 "src/parse.y"
    {
		      (yyval.nd) = 0;
		    ;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 2042 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (3)].nd);
		    ;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 2046 "src/parse.y"
    {
		      (yyval.nd) = new_colon2(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].id));
		    ;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 2050 "src/parse.y"
    {
		      (yyval.nd) = new_colon3(p, (yyvsp[(2) - (2)].id));
		    ;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 2054 "src/parse.y"
    {
		      (yyval.nd) = new_array(p, (yyvsp[(2) - (3)].nd));
		    ;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 2058 "src/parse.y"
    {
		      (yyval.nd) = new_hash(p, (yyvsp[(2) - (3)].nd));
		    ;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 2062 "src/parse.y"
    {
		      (yyval.nd) = new_return(p, 0);
		    ;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 2066 "src/parse.y"
    {
		      (yyval.nd) = new_yield(p, (yyvsp[(3) - (4)].nd));
		    ;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 2070 "src/parse.y"
    {
		      (yyval.nd) = new_yield(p, 0);
		    ;}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 2074 "src/parse.y"
    {
		      (yyval.nd) = new_yield(p, 0);
		    ;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 2078 "src/parse.y"
    {
		      (yyval.nd) = call_uni_op(p, cond((yyvsp[(3) - (4)].nd)), "!");
		    ;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 2082 "src/parse.y"
    {
		      (yyval.nd) = call_uni_op(p, new_nil(p), "!");
		    ;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 2086 "src/parse.y"
    {
		      (yyval.nd) = new_fcall(p, (yyvsp[(1) - (2)].id), cons(0, (yyvsp[(2) - (2)].nd)));
		    ;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 2091 "src/parse.y"
    {
		      call_with_block(p, (yyvsp[(1) - (2)].nd), (yyvsp[(2) - (2)].nd));
		      (yyval.nd) = (yyvsp[(1) - (2)].nd);
		    ;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 2096 "src/parse.y"
    {
		      local_nest(p);
		      (yyval.num) = p->lpar_beg;
		      p->lpar_beg = ++p->paren_nest;
		    ;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 2103 "src/parse.y"
    {
		      p->lpar_beg = (yyvsp[(2) - (4)].num);
		      (yyval.nd) = new_lambda(p, (yyvsp[(3) - (4)].nd), (yyvsp[(4) - (4)].nd));
		      local_unnest(p);
		    ;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 2112 "src/parse.y"
    {
		      (yyval.nd) = new_if(p, cond((yyvsp[(2) - (6)].nd)), (yyvsp[(4) - (6)].nd), (yyvsp[(5) - (6)].nd));
		    ;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 2119 "src/parse.y"
    {
		      (yyval.nd) = new_unless(p, cond((yyvsp[(2) - (6)].nd)), (yyvsp[(4) - (6)].nd), (yyvsp[(5) - (6)].nd));
		    ;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 2122 "src/parse.y"
    {COND_PUSH(1);;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 2122 "src/parse.y"
    {COND_POP();;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 2125 "src/parse.y"
    {
		      (yyval.nd) = new_while(p, cond((yyvsp[(3) - (7)].nd)), (yyvsp[(6) - (7)].nd));
		    ;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 2128 "src/parse.y"
    {COND_PUSH(1);;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 2128 "src/parse.y"
    {COND_POP();;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 2131 "src/parse.y"
    {
		      (yyval.nd) = new_until(p, cond((yyvsp[(3) - (7)].nd)), (yyvsp[(6) - (7)].nd));
		    ;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 2137 "src/parse.y"
    {
		      (yyval.nd) = new_case(p, (yyvsp[(2) - (5)].nd), (yyvsp[(4) - (5)].nd));
		    ;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 2141 "src/parse.y"
    {
		      (yyval.nd) = new_case(p, 0, (yyvsp[(3) - (4)].nd));
		    ;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 2145 "src/parse.y"
    {COND_PUSH(1);;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 2147 "src/parse.y"
    {COND_POP();;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 2150 "src/parse.y"
    {
		      (yyval.nd) = new_for(p, (yyvsp[(2) - (9)].nd), (yyvsp[(5) - (9)].nd), (yyvsp[(8) - (9)].nd));
		    ;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 2154 "src/parse.y"
    {
		      if (p->in_def || p->in_single)
			yyerror(p, "class definition in method body");
		      (yyval.nd) = local_switch(p);
		    ;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 2161 "src/parse.y"
    {
		      (yyval.nd) = new_class(p, (yyvsp[(2) - (6)].nd), (yyvsp[(3) - (6)].nd), (yyvsp[(5) - (6)].nd));
		      local_resume(p, (yyvsp[(4) - (6)].nd));
		    ;}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 2166 "src/parse.y"
    {
		      (yyval.num) = p->in_def;
		      p->in_def = 0;
		    ;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 2171 "src/parse.y"
    {
		      (yyval.nd) = cons(local_switch(p), (node*)(intptr_t)p->in_single);
		      p->in_single = 0;
		    ;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 2177 "src/parse.y"
    {
		      (yyval.nd) = new_sclass(p, (yyvsp[(3) - (8)].nd), (yyvsp[(7) - (8)].nd));
		      local_resume(p, (yyvsp[(6) - (8)].nd)->car);
		      p->in_def = (yyvsp[(4) - (8)].num);
		      p->in_single = (int)(intptr_t)(yyvsp[(6) - (8)].nd)->cdr;
		    ;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 2184 "src/parse.y"
    {
		      if (p->in_def || p->in_single)
			yyerror(p, "module definition in method body");
		      (yyval.nd) = local_switch(p);
		    ;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 2191 "src/parse.y"
    {
		      (yyval.nd) = new_module(p, (yyvsp[(2) - (5)].nd), (yyvsp[(4) - (5)].nd));
		      local_resume(p, (yyvsp[(3) - (5)].nd));
		    ;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 2196 "src/parse.y"
    {
		      p->in_def++;
		      (yyval.nd) = local_switch(p);
		    ;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 2203 "src/parse.y"
    {
		      (yyval.nd) = new_def(p, (yyvsp[(2) - (6)].id), (yyvsp[(4) - (6)].nd), (yyvsp[(5) - (6)].nd));
		      local_resume(p, (yyvsp[(3) - (6)].nd));
		      p->in_def--;
		    ;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 2208 "src/parse.y"
    {p->lstate = EXPR_FNAME;;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 2209 "src/parse.y"
    {
		      p->in_single++;
		      p->lstate = EXPR_ENDFN; /* force for args */
		      (yyval.nd) = local_switch(p);
		    ;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 2217 "src/parse.y"
    {
		      (yyval.nd) = new_sdef(p, (yyvsp[(2) - (9)].nd), (yyvsp[(5) - (9)].id), (yyvsp[(7) - (9)].nd), (yyvsp[(8) - (9)].nd));
		      local_resume(p, (yyvsp[(6) - (9)].nd));
		      p->in_single--;
		    ;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 2223 "src/parse.y"
    {
		      (yyval.nd) = new_break(p, 0);
		    ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 2227 "src/parse.y"
    {
		      (yyval.nd) = new_next(p, 0);
		    ;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 2231 "src/parse.y"
    {
		      (yyval.nd) = new_redo(p);
		    ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 2235 "src/parse.y"
    {
		      (yyval.nd) = new_retry(p);
		    ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 2241 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(1) - (1)].nd);
		      if (!(yyval.nd)) (yyval.nd) = new_nil(p);
		    ;}
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 2260 "src/parse.y"
    {
		      (yyval.nd) = new_if(p, cond((yyvsp[(2) - (5)].nd)), (yyvsp[(4) - (5)].nd), (yyvsp[(5) - (5)].nd));
		    ;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 2267 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (2)].nd);
		    ;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 2273 "src/parse.y"
    {
		      (yyval.nd) = list1(list1((yyvsp[(1) - (1)].nd)));
		    ;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 2280 "src/parse.y"
    {
		      (yyval.nd) = new_arg(p, (yyvsp[(1) - (1)].id));
		    ;}
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 2284 "src/parse.y"
    {
		      (yyval.nd) = new_masgn(p, (yyvsp[(2) - (3)].nd), 0);
		    ;}
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 2290 "src/parse.y"
    {
		      (yyval.nd) = list1((yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 2294 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 2300 "src/parse.y"
    {
		      (yyval.nd) = list3((yyvsp[(1) - (1)].nd),0,0);
		    ;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 2304 "src/parse.y"
    {
		      (yyval.nd) = list3((yyvsp[(1) - (4)].nd), new_arg(p, (yyvsp[(4) - (4)].id)), 0);
		    ;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 2308 "src/parse.y"
    {
		      (yyval.nd) = list3((yyvsp[(1) - (6)].nd), new_arg(p, (yyvsp[(4) - (6)].id)), (yyvsp[(6) - (6)].nd));
		    ;}
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 2312 "src/parse.y"
    {
		      (yyval.nd) = list3((yyvsp[(1) - (3)].nd), (node*)-1, 0);
		    ;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 2316 "src/parse.y"
    {
		      (yyval.nd) = list3((yyvsp[(1) - (5)].nd), (node*)-1, (yyvsp[(5) - (5)].nd));
		    ;}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 2320 "src/parse.y"
    {
		      (yyval.nd) = list3(0, new_arg(p, (yyvsp[(2) - (2)].id)), 0);
		    ;}
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 2324 "src/parse.y"
    {
		      (yyval.nd) = list3(0, new_arg(p, (yyvsp[(2) - (4)].id)), (yyvsp[(4) - (4)].nd));
		    ;}
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 2328 "src/parse.y"
    {
		      (yyval.nd) = list3(0, (node*)-1, 0);
		    ;}
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 2332 "src/parse.y"
    {
		      (yyval.nd) = list3(0, (node*)-1, (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 2338 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (6)].nd), (yyvsp[(3) - (6)].nd), (yyvsp[(5) - (6)].id), 0, (yyvsp[(6) - (6)].id));
		    ;}
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 2342 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (8)].nd), (yyvsp[(3) - (8)].nd), (yyvsp[(5) - (8)].id), (yyvsp[(7) - (8)].nd), (yyvsp[(8) - (8)].id));
		    ;}
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 2346 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (4)].nd), (yyvsp[(3) - (4)].nd), 0, 0, (yyvsp[(4) - (4)].id));
		    ;}
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 2350 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (6)].nd), (yyvsp[(3) - (6)].nd), 0, (yyvsp[(5) - (6)].nd), (yyvsp[(6) - (6)].id));
		    ;}
    break;

  case 350:

/* Line 1455 of yacc.c  */
#line 2354 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (4)].nd), 0, (yyvsp[(3) - (4)].id), 0, (yyvsp[(4) - (4)].id));
		    ;}
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 2358 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (2)].nd), 0, 1, 0, 0);
		    ;}
    break;

  case 352:

/* Line 1455 of yacc.c  */
#line 2362 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (6)].nd), 0, (yyvsp[(3) - (6)].id), (yyvsp[(5) - (6)].nd), (yyvsp[(6) - (6)].id));
		    ;}
    break;

  case 353:

/* Line 1455 of yacc.c  */
#line 2366 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (2)].nd), 0, 0, 0, (yyvsp[(2) - (2)].id));
		    ;}
    break;

  case 354:

/* Line 1455 of yacc.c  */
#line 2370 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, (yyvsp[(1) - (4)].nd), (yyvsp[(3) - (4)].id), 0, (yyvsp[(4) - (4)].id));
		    ;}
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 2374 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, (yyvsp[(1) - (6)].nd), (yyvsp[(3) - (6)].id), (yyvsp[(5) - (6)].nd), (yyvsp[(6) - (6)].id));
		    ;}
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 2378 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, (yyvsp[(1) - (2)].nd), 0, 0, (yyvsp[(2) - (2)].id));
		    ;}
    break;

  case 357:

/* Line 1455 of yacc.c  */
#line 2382 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, (yyvsp[(1) - (4)].nd), 0, (yyvsp[(3) - (4)].nd), (yyvsp[(4) - (4)].id));
		    ;}
    break;

  case 358:

/* Line 1455 of yacc.c  */
#line 2386 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, 0, (yyvsp[(1) - (2)].id), 0, (yyvsp[(2) - (2)].id));
		    ;}
    break;

  case 359:

/* Line 1455 of yacc.c  */
#line 2390 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, 0, (yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].nd), (yyvsp[(4) - (4)].id));
		    ;}
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 2394 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, 0, 0, 0, (yyvsp[(1) - (1)].id));
		    ;}
    break;

  case 362:

/* Line 1455 of yacc.c  */
#line 2401 "src/parse.y"
    {
		      p->cmd_start = TRUE;
		      (yyval.nd) = (yyvsp[(1) - (1)].nd);
		    ;}
    break;

  case 363:

/* Line 1455 of yacc.c  */
#line 2408 "src/parse.y"
    {
		      local_add_f(p, 0);
		      (yyval.nd) = 0;
		    ;}
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 2413 "src/parse.y"
    {
		      local_add_f(p, 0);
		      (yyval.nd) = 0;
		    ;}
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 2418 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (4)].nd);
		    ;}
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 2425 "src/parse.y"
    {
		      (yyval.nd) = 0;
		    ;}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 2429 "src/parse.y"
    {
		      (yyval.nd) = 0;
		    ;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2439 "src/parse.y"
    {
		      local_add_f(p, (yyvsp[(1) - (1)].id));
		      new_bv(p, (yyvsp[(1) - (1)].id));
		    ;}
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 2447 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (4)].nd);
		    ;}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 2451 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(1) - (1)].nd);
		    ;}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 2457 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (3)].nd);
		    ;}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 2461 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (3)].nd);
		    ;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 2467 "src/parse.y"
    {
		      local_nest(p);
		    ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2473 "src/parse.y"
    {
		      (yyval.nd) = new_block(p,(yyvsp[(3) - (5)].nd),(yyvsp[(4) - (5)].nd));
		      local_unnest(p);
		    ;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 2480 "src/parse.y"
    {
		      if ((yyvsp[(1) - (2)].nd)->car == (node*)NODE_YIELD) {
			yyerror(p, "block given to yield");
		      }
		      else {
			call_with_block(p, (yyvsp[(1) - (2)].nd), (yyvsp[(2) - (2)].nd));
		      }
		      (yyval.nd) = (yyvsp[(1) - (2)].nd);
		    ;}
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 2490 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (4)].nd), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].nd));
		    ;}
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 2494 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (5)].nd), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].nd));
		      call_with_block(p, (yyval.nd), (yyvsp[(5) - (5)].nd));
		    ;}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 2499 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (5)].nd), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].nd));
		      call_with_block(p, (yyval.nd), (yyvsp[(5) - (5)].nd));
		    ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2506 "src/parse.y"
    {
		      (yyval.nd) = new_fcall(p, (yyvsp[(1) - (2)].id), (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2510 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (4)].nd), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].nd));
		    ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2514 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (4)].nd), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].nd));
		    ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2518 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].id), 0);
		    ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2522 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (3)].nd), intern("call",4), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 2526 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (3)].nd), intern("call",4), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2530 "src/parse.y"
    {
		      (yyval.nd) = new_super(p, (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2534 "src/parse.y"
    {
		      (yyval.nd) = new_zsuper(p);
		    ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2538 "src/parse.y"
    {
		      (yyval.nd) = new_call(p, (yyvsp[(1) - (4)].nd), intern("[]",2), (yyvsp[(3) - (4)].nd));
		    ;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 2544 "src/parse.y"
    {
		      local_nest(p);
		    ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2549 "src/parse.y"
    {
		      (yyval.nd) = new_block(p,(yyvsp[(3) - (5)].nd),(yyvsp[(4) - (5)].nd));
		      local_unnest(p);
		    ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2554 "src/parse.y"
    {
		      local_nest(p);
		    ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2559 "src/parse.y"
    {
		      (yyval.nd) = new_block(p,(yyvsp[(3) - (5)].nd),(yyvsp[(4) - (5)].nd));
		      local_unnest(p);
		    ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2568 "src/parse.y"
    {
		      (yyval.nd) = cons(cons((yyvsp[(2) - (5)].nd), (yyvsp[(4) - (5)].nd)), (yyvsp[(5) - (5)].nd));
		    ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2574 "src/parse.y"
    {
		      if ((yyvsp[(1) - (1)].nd)) {
			(yyval.nd) = cons(cons(0, (yyvsp[(1) - (1)].nd)), 0);
		      }
		      else {
			(yyval.nd) = 0;
		      }
		    ;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2588 "src/parse.y"
    {
		      (yyval.nd) = list1(list3((yyvsp[(2) - (6)].nd), (yyvsp[(3) - (6)].nd), (yyvsp[(5) - (6)].nd)));
		      if ((yyvsp[(6) - (6)].nd)) (yyval.nd) = append((yyval.nd), (yyvsp[(6) - (6)].nd));
		    ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2596 "src/parse.y"
    {
			(yyval.nd) = list1((yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 2604 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (2)].nd);
		    ;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2611 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (2)].nd);
		    ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2626 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (2)].nd);
		    ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2630 "src/parse.y"
    {
		      (yyval.nd) = new_dstr(p, push((yyvsp[(2) - (3)].nd), (yyvsp[(3) - (3)].nd)));
		    ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2637 "src/parse.y"
    {
		      (yyval.nd) = append((yyvsp[(1) - (2)].nd), (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2643 "src/parse.y"
    {
		      (yyval.nd) = list1((yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 2647 "src/parse.y"
    {
		      (yyval.nd) = p->lex_strterm;
		      p->lex_strterm = NULL;
		    ;}
    break;

  case 419:

/* Line 1455 of yacc.c  */
#line 2653 "src/parse.y"
    {
		      p->lex_strterm = (yyvsp[(2) - (4)].nd);
		      (yyval.nd) = list2((yyvsp[(1) - (4)].nd), (yyvsp[(3) - (4)].nd));
		    ;}
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 2658 "src/parse.y"
    {
		      (yyval.nd) = list1(new_literal_delim(p));
		    ;}
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 2662 "src/parse.y"
    {
		      (yyval.nd) = list1(new_literal_delim(p));
		    ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 2668 "src/parse.y"
    {
			(yyval.nd) = (yyvsp[(2) - (2)].nd);
		    ;}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 2672 "src/parse.y"
    {
		      (yyval.nd) = new_dxstr(p, push((yyvsp[(2) - (3)].nd), (yyvsp[(3) - (3)].nd)));
		    ;}
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 2678 "src/parse.y"
    {
			(yyval.nd) = (yyvsp[(2) - (2)].nd);
		    ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 2682 "src/parse.y"
    {
		      (yyval.nd) = new_dregx(p, (yyvsp[(2) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 2699 "src/parse.y"
    {
		      parser_heredoc_info * inf = parsing_heredoc_inf(p);
		      inf->doc = push(inf->doc, new_str(p, "", 0));
		      heredoc_end(p);
		    ;}
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 2705 "src/parse.y"
    {
		      heredoc_end(p);
		    ;}
    break;

  case 435:

/* Line 1455 of yacc.c  */
#line 2715 "src/parse.y"
    {
		      parser_heredoc_info * inf = parsing_heredoc_inf(p);
		      inf->doc = push(inf->doc, (yyvsp[(1) - (1)].nd));
		      heredoc_treat_nextline(p);
		    ;}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 2721 "src/parse.y"
    {
		      (yyval.nd) = p->lex_strterm;
		      p->lex_strterm = NULL;
		    ;}
    break;

  case 437:

/* Line 1455 of yacc.c  */
#line 2727 "src/parse.y"
    {
		      parser_heredoc_info * inf = parsing_heredoc_inf(p);
		      p->lex_strterm = (yyvsp[(2) - (4)].nd);
		      inf->doc = push(push(inf->doc, (yyvsp[(1) - (4)].nd)), (yyvsp[(3) - (4)].nd));
		    ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 2735 "src/parse.y"
    {
		      (yyval.nd) = new_words(p, list1((yyvsp[(2) - (2)].nd)));
		    ;}
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 2739 "src/parse.y"
    {
		      (yyval.nd) = new_words(p, push((yyvsp[(2) - (3)].nd), (yyvsp[(3) - (3)].nd)));
		    ;}
    break;

  case 440:

/* Line 1455 of yacc.c  */
#line 2746 "src/parse.y"
    {
		      (yyval.nd) = new_sym(p, (yyvsp[(1) - (1)].id));
		    ;}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 2750 "src/parse.y"
    {
		      p->lstate = EXPR_END;
		      (yyval.nd) = new_dsym(p, push((yyvsp[(3) - (4)].nd), (yyvsp[(4) - (4)].nd)));
		    ;}
    break;

  case 442:

/* Line 1455 of yacc.c  */
#line 2757 "src/parse.y"
    {
		      p->lstate = EXPR_END;
		      (yyval.id) = (yyvsp[(2) - (2)].id);
		    ;}
    break;

  case 447:

/* Line 1455 of yacc.c  */
#line 2768 "src/parse.y"
    {
		      (yyval.id) = new_strsym(p, (yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 448:

/* Line 1455 of yacc.c  */
#line 2772 "src/parse.y"
    {
		      (yyval.id) = new_strsym(p, (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 449:

/* Line 1455 of yacc.c  */
#line 2778 "src/parse.y"
    {
		      (yyval.nd) = new_symbols(p, list1((yyvsp[(2) - (2)].nd)));
		    ;}
    break;

  case 450:

/* Line 1455 of yacc.c  */
#line 2782 "src/parse.y"
    {
		      (yyval.nd) = new_symbols(p, push((yyvsp[(2) - (3)].nd), (yyvsp[(3) - (3)].nd)));
		    ;}
    break;

  case 453:

/* Line 1455 of yacc.c  */
#line 2790 "src/parse.y"
    {
		      (yyval.nd) = negate_lit(p, (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 454:

/* Line 1455 of yacc.c  */
#line 2794 "src/parse.y"
    {
		      (yyval.nd) = negate_lit(p, (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 455:

/* Line 1455 of yacc.c  */
#line 2800 "src/parse.y"
    {
		      (yyval.nd) = new_lvar(p, (yyvsp[(1) - (1)].id));
		    ;}
    break;

  case 456:

/* Line 1455 of yacc.c  */
#line 2804 "src/parse.y"
    {
		      (yyval.nd) = new_ivar(p, (yyvsp[(1) - (1)].id));
		    ;}
    break;

  case 457:

/* Line 1455 of yacc.c  */
#line 2808 "src/parse.y"
    {
		      (yyval.nd) = new_gvar(p, (yyvsp[(1) - (1)].id));
		    ;}
    break;

  case 458:

/* Line 1455 of yacc.c  */
#line 2812 "src/parse.y"
    {
		      (yyval.nd) = new_cvar(p, (yyvsp[(1) - (1)].id));
		    ;}
    break;

  case 459:

/* Line 1455 of yacc.c  */
#line 2816 "src/parse.y"
    {
		      (yyval.nd) = new_const(p, (yyvsp[(1) - (1)].id));
		    ;}
    break;

  case 460:

/* Line 1455 of yacc.c  */
#line 2822 "src/parse.y"
    {
		      assignable(p, (yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 461:

/* Line 1455 of yacc.c  */
#line 2828 "src/parse.y"
    {
		      (yyval.nd) = var_reference(p, (yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 462:

/* Line 1455 of yacc.c  */
#line 2832 "src/parse.y"
    {
		      (yyval.nd) = new_nil(p);
		    ;}
    break;

  case 463:

/* Line 1455 of yacc.c  */
#line 2836 "src/parse.y"
    {
		      (yyval.nd) = new_self(p);
   		    ;}
    break;

  case 464:

/* Line 1455 of yacc.c  */
#line 2840 "src/parse.y"
    {
		      (yyval.nd) = new_true(p);
   		    ;}
    break;

  case 465:

/* Line 1455 of yacc.c  */
#line 2844 "src/parse.y"
    {
		      (yyval.nd) = new_false(p);
   		    ;}
    break;

  case 466:

/* Line 1455 of yacc.c  */
#line 2848 "src/parse.y"
    {
		      if (!p->filename) {
			p->filename = "(null)";
		      }
		      (yyval.nd) = new_str(p, p->filename, strlen(p->filename));
		    ;}
    break;

  case 467:

/* Line 1455 of yacc.c  */
#line 2855 "src/parse.y"
    {
		      char buf[16];

		      snprintf(buf, sizeof(buf), "%d", p->lineno);
		      (yyval.nd) = new_int(p, buf, 10);
		    ;}
    break;

  case 470:

/* Line 1455 of yacc.c  */
#line 2868 "src/parse.y"
    {
		      (yyval.nd) = 0;
		    ;}
    break;

  case 471:

/* Line 1455 of yacc.c  */
#line 2872 "src/parse.y"
    {
		      p->lstate = EXPR_BEG;
		      p->cmd_start = TRUE;
		    ;}
    break;

  case 472:

/* Line 1455 of yacc.c  */
#line 2877 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(3) - (4)].nd);
		    ;}
    break;

  case 473:

/* Line 1455 of yacc.c  */
#line 2881 "src/parse.y"
    {
		      yyerrok;
		      (yyval.nd) = 0;
		    ;}
    break;

  case 474:

/* Line 1455 of yacc.c  */
#line 2888 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(2) - (3)].nd);
		      p->lstate = EXPR_BEG;
		      p->cmd_start = TRUE;
		    ;}
    break;

  case 475:

/* Line 1455 of yacc.c  */
#line 2894 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(1) - (2)].nd);
		    ;}
    break;

  case 476:

/* Line 1455 of yacc.c  */
#line 2900 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (6)].nd), (yyvsp[(3) - (6)].nd), (yyvsp[(5) - (6)].id), 0, (yyvsp[(6) - (6)].id));
		    ;}
    break;

  case 477:

/* Line 1455 of yacc.c  */
#line 2904 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (8)].nd), (yyvsp[(3) - (8)].nd), (yyvsp[(5) - (8)].id), (yyvsp[(7) - (8)].nd), (yyvsp[(8) - (8)].id));
		    ;}
    break;

  case 478:

/* Line 1455 of yacc.c  */
#line 2908 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (4)].nd), (yyvsp[(3) - (4)].nd), 0, 0, (yyvsp[(4) - (4)].id));
		    ;}
    break;

  case 479:

/* Line 1455 of yacc.c  */
#line 2912 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (6)].nd), (yyvsp[(3) - (6)].nd), 0, (yyvsp[(5) - (6)].nd), (yyvsp[(6) - (6)].id));
		    ;}
    break;

  case 480:

/* Line 1455 of yacc.c  */
#line 2916 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (4)].nd), 0, (yyvsp[(3) - (4)].id), 0, (yyvsp[(4) - (4)].id));
		    ;}
    break;

  case 481:

/* Line 1455 of yacc.c  */
#line 2920 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (6)].nd), 0, (yyvsp[(3) - (6)].id), (yyvsp[(5) - (6)].nd), (yyvsp[(6) - (6)].id));
		    ;}
    break;

  case 482:

/* Line 1455 of yacc.c  */
#line 2924 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, (yyvsp[(1) - (2)].nd), 0, 0, 0, (yyvsp[(2) - (2)].id));
		    ;}
    break;

  case 483:

/* Line 1455 of yacc.c  */
#line 2928 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, (yyvsp[(1) - (4)].nd), (yyvsp[(3) - (4)].id), 0, (yyvsp[(4) - (4)].id));
		    ;}
    break;

  case 484:

/* Line 1455 of yacc.c  */
#line 2932 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, (yyvsp[(1) - (6)].nd), (yyvsp[(3) - (6)].id), (yyvsp[(5) - (6)].nd), (yyvsp[(6) - (6)].id));
		    ;}
    break;

  case 485:

/* Line 1455 of yacc.c  */
#line 2936 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, (yyvsp[(1) - (2)].nd), 0, 0, (yyvsp[(2) - (2)].id));
		    ;}
    break;

  case 486:

/* Line 1455 of yacc.c  */
#line 2940 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, (yyvsp[(1) - (4)].nd), 0, (yyvsp[(3) - (4)].nd), (yyvsp[(4) - (4)].id));
		    ;}
    break;

  case 487:

/* Line 1455 of yacc.c  */
#line 2944 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, 0, (yyvsp[(1) - (2)].id), 0, (yyvsp[(2) - (2)].id));
		    ;}
    break;

  case 488:

/* Line 1455 of yacc.c  */
#line 2948 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, 0, (yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].nd), (yyvsp[(4) - (4)].id));
		    ;}
    break;

  case 489:

/* Line 1455 of yacc.c  */
#line 2952 "src/parse.y"
    {
		      (yyval.nd) = new_args(p, 0, 0, 0, 0, (yyvsp[(1) - (1)].id));
		    ;}
    break;

  case 490:

/* Line 1455 of yacc.c  */
#line 2956 "src/parse.y"
    {
		      local_add_f(p, 0);
		      (yyval.nd) = new_args(p, 0, 0, 0, 0, 0);
		    ;}
    break;

  case 491:

/* Line 1455 of yacc.c  */
#line 2963 "src/parse.y"
    {
		      yyerror(p, "formal argument cannot be a constant");
		      (yyval.nd) = 0;
		    ;}
    break;

  case 492:

/* Line 1455 of yacc.c  */
#line 2968 "src/parse.y"
    {
		      yyerror(p, "formal argument cannot be an instance variable");
		      (yyval.nd) = 0;
		    ;}
    break;

  case 493:

/* Line 1455 of yacc.c  */
#line 2973 "src/parse.y"
    {
		      yyerror(p, "formal argument cannot be a global variable");
		      (yyval.nd) = 0;
		    ;}
    break;

  case 494:

/* Line 1455 of yacc.c  */
#line 2978 "src/parse.y"
    {
		      yyerror(p, "formal argument cannot be a class variable");
		      (yyval.nd) = 0;
		    ;}
    break;

  case 495:

/* Line 1455 of yacc.c  */
#line 2985 "src/parse.y"
    {
		      (yyval.id) = 0;
		    ;}
    break;

  case 496:

/* Line 1455 of yacc.c  */
#line 2989 "src/parse.y"
    {
		      local_add_f(p, (yyvsp[(1) - (1)].id));
		      (yyval.id) = (yyvsp[(1) - (1)].id);
		    ;}
    break;

  case 497:

/* Line 1455 of yacc.c  */
#line 2996 "src/parse.y"
    {
		      (yyval.nd) = new_arg(p, (yyvsp[(1) - (1)].id));
		    ;}
    break;

  case 498:

/* Line 1455 of yacc.c  */
#line 3000 "src/parse.y"
    {
		      (yyval.nd) = new_masgn(p, (yyvsp[(2) - (3)].nd), 0);
		    ;}
    break;

  case 499:

/* Line 1455 of yacc.c  */
#line 3006 "src/parse.y"
    {
		      (yyval.nd) = list1((yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 500:

/* Line 1455 of yacc.c  */
#line 3010 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 501:

/* Line 1455 of yacc.c  */
#line 3016 "src/parse.y"
    {
		      local_add_f(p, (yyvsp[(1) - (3)].id));
		      (yyval.nd) = cons(nsym((yyvsp[(1) - (3)].id)), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 502:

/* Line 1455 of yacc.c  */
#line 3023 "src/parse.y"
    {
		      local_add_f(p, (yyvsp[(1) - (3)].id));
		      (yyval.nd) = cons(nsym((yyvsp[(1) - (3)].id)), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 503:

/* Line 1455 of yacc.c  */
#line 3030 "src/parse.y"
    {
		      (yyval.nd) = list1((yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 504:

/* Line 1455 of yacc.c  */
#line 3034 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 505:

/* Line 1455 of yacc.c  */
#line 3040 "src/parse.y"
    {
		      (yyval.nd) = list1((yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 506:

/* Line 1455 of yacc.c  */
#line 3044 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 509:

/* Line 1455 of yacc.c  */
#line 3054 "src/parse.y"
    {
		      local_add_f(p, (yyvsp[(2) - (2)].id));
		      (yyval.id) = (yyvsp[(2) - (2)].id);
		    ;}
    break;

  case 510:

/* Line 1455 of yacc.c  */
#line 3059 "src/parse.y"
    {
		      local_add_f(p, 0);
		      (yyval.id) = -1;
		    ;}
    break;

  case 513:

/* Line 1455 of yacc.c  */
#line 3070 "src/parse.y"
    {
		      local_add_f(p, (yyvsp[(2) - (2)].id));
		      (yyval.id) = (yyvsp[(2) - (2)].id);
		    ;}
    break;

  case 514:

/* Line 1455 of yacc.c  */
#line 3077 "src/parse.y"
    {
		      (yyval.id) = (yyvsp[(2) - (2)].id);
		    ;}
    break;

  case 515:

/* Line 1455 of yacc.c  */
#line 3081 "src/parse.y"
    {
		      local_add_f(p, 0);
		      (yyval.id) = 0;
		    ;}
    break;

  case 516:

/* Line 1455 of yacc.c  */
#line 3088 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(1) - (1)].nd);
		      if (!(yyval.nd)) (yyval.nd) = new_nil(p);
		    ;}
    break;

  case 517:

/* Line 1455 of yacc.c  */
#line 3092 "src/parse.y"
    {p->lstate = EXPR_BEG;;}
    break;

  case 518:

/* Line 1455 of yacc.c  */
#line 3093 "src/parse.y"
    {
		      if ((yyvsp[(3) - (4)].nd) == 0) {
			yyerror(p, "can't define singleton method for ().");
		      }
		      else {
			switch ((enum node_type)(int)(intptr_t)(yyvsp[(3) - (4)].nd)->car) {
			case NODE_STR:
			case NODE_DSTR:
			case NODE_XSTR:
			case NODE_DXSTR:
			case NODE_DREGX:
			case NODE_MATCH:
			case NODE_FLOAT:
			case NODE_ARRAY:
			case NODE_HEREDOC:
			  yyerror(p, "can't define singleton method for literals");
			default:
			  break;
			}
		      }
		      (yyval.nd) = (yyvsp[(3) - (4)].nd);
		    ;}
    break;

  case 520:

/* Line 1455 of yacc.c  */
#line 3119 "src/parse.y"
    {
		      (yyval.nd) = (yyvsp[(1) - (2)].nd);
		    ;}
    break;

  case 521:

/* Line 1455 of yacc.c  */
#line 3125 "src/parse.y"
    {
		      (yyval.nd) = list1((yyvsp[(1) - (1)].nd));
		    ;}
    break;

  case 522:

/* Line 1455 of yacc.c  */
#line 3129 "src/parse.y"
    {
		      (yyval.nd) = push((yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 523:

/* Line 1455 of yacc.c  */
#line 3135 "src/parse.y"
    {
		      (yyval.nd) = cons((yyvsp[(1) - (3)].nd), (yyvsp[(3) - (3)].nd));
		    ;}
    break;

  case 524:

/* Line 1455 of yacc.c  */
#line 3139 "src/parse.y"
    {
		      (yyval.nd) = cons(new_sym(p, (yyvsp[(1) - (2)].id)), (yyvsp[(2) - (2)].nd));
		    ;}
    break;

  case 546:

/* Line 1455 of yacc.c  */
#line 3183 "src/parse.y"
    {yyerrok;;}
    break;

  case 548:

/* Line 1455 of yacc.c  */
#line 3188 "src/parse.y"
    {
		      p->lineno++;
		      p->column = 0;
		    ;}
    break;

  case 551:

/* Line 1455 of yacc.c  */
#line 3195 "src/parse.y"
    {yyerrok;;}
    break;

  case 552:

/* Line 1455 of yacc.c  */
#line 3199 "src/parse.y"
    {
		      (yyval.nd) = 0;
		    ;}
    break;



/* Line 1455 of yacc.c  */
#line 9257 "C:/Personal/Git/mruby4VS/mruby/build/host/src/y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (p, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (p, yymsg);
	  }
	else
	  {
	    yyerror (p, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, p);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, p);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (p, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, p);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, p);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 3203 "src/parse.y"

#define yylval  (*((YYSTYPE*)(p->ylval)))

static void
yyerror(parser_state *p, const char *s)
{
  char* c;
  int n;

  if (! p->capture_errors) {
#ifdef ENABLE_STDIO
    if (p->filename) {
      fprintf(stderr, "%s:%d:%d: %s\n", p->filename, p->lineno, p->column, s);
    }
    else {
      fprintf(stderr, "line %d:%d: %s\n", p->lineno, p->column, s);
    }
#endif
  }
  else if (p->nerr < sizeof(p->error_buffer) / sizeof(p->error_buffer[0])) {
    n = strlen(s);
    c = (char *)parser_palloc(p, n + 1);
    memcpy(c, s, n + 1);
    p->error_buffer[p->nerr].message = c;
    p->error_buffer[p->nerr].lineno = p->lineno;
    p->error_buffer[p->nerr].column = p->column;
  }
  p->nerr++;
}

static void
yyerror_i(parser_state *p, const char *fmt, int i)
{
  char buf[256];

  snprintf(buf, sizeof(buf), fmt, i);
  yyerror(p, buf);
}

static void
yywarn(parser_state *p, const char *s)
{
  char* c;
  int n;

  if (! p->capture_errors) {
#ifdef ENABLE_STDIO
    if (p->filename) {
      fprintf(stderr, "%s:%d:%d: %s\n", p->filename, p->lineno, p->column, s);
    }
    else {
      fprintf(stderr, "line %d:%d: %s\n", p->lineno, p->column, s);
    }
#endif
  }
  else if (p->nwarn < sizeof(p->warn_buffer) / sizeof(p->warn_buffer[0])) {
    n = strlen(s);
    c = (char *)parser_palloc(p, n + 1);
    memcpy(c, s, n + 1);
    p->warn_buffer[p->nwarn].message = c;
    p->warn_buffer[p->nwarn].lineno = p->lineno;
    p->warn_buffer[p->nwarn].column = p->column;
  }
  p->nwarn++;
}

static void
yywarning(parser_state *p, const char *s)
{
  yywarn(p, s);
}

static void
yywarning_s(parser_state *p, const char *fmt, const char *s)
{
  char buf[256];

  snprintf(buf, sizeof(buf), fmt, s);
  yywarning(p, buf);
}

static void
backref_error(parser_state *p, node *n)
{
  int c;

  c = (int)(intptr_t)n->car;

  if (c == NODE_NTH_REF) {
    yyerror_i(p, "can't set variable $%d", (int)(intptr_t)n->cdr);
  } else if (c == NODE_BACK_REF) {
    yyerror_i(p, "can't set variable $%c", (int)(intptr_t)n->cdr);
  } else {
    mrb_bug(p->mrb, "Internal error in backref_error() : n=>car == %d", c);
  }
}

static int peeks(parser_state *p, const char *s);
static int skips(parser_state *p, const char *s);

static inline int
nextc(parser_state *p)
{
  int c;

  if (p->pb) {
    node *tmp;

    c = (int)(intptr_t)p->pb->car;
    tmp = p->pb;
    p->pb = p->pb->cdr;
    cons_free(tmp);
  }
  else {
#ifdef ENABLE_STDIO
    if (p->f) {
      if (feof(p->f)) goto eof;
      c = fgetc(p->f);
      if (c == EOF) goto eof;
    }
    else
#endif
    if (!p->s || p->s >= p->send) {
       goto eof;
    }
    else {
      c = (unsigned char)*p->s++;
    }
  }
  p->column++;
  return c;

 eof:
  if (!p->cxt) return -1;
  else {
    if (p->cxt->partial_hook(p) < 0)
      return -1;
    return -2;
  }
}

static void
pushback(parser_state *p, int c)
{
  if (c < 0) return;
  p->column--;
  p->pb = cons((node*)(intptr_t)c, p->pb);
}

static void
skip(parser_state *p, char term)
{
  int c;

  for (;;) {
    c = nextc(p);
    if (c < 0) break;
    if (c == term) break;
  }
}

static int
peek_n(parser_state *p, int c, int n)
{
  node *list = 0;
  int c0;

  do {
    c0 = nextc(p);
    if (c0 < 0) return FALSE;
    list = push(list, (node*)(intptr_t)c0);
  } while(n--);
  if (p->pb) {
    p->pb = append(p->pb, (node*)list);
  }
  else {
    p->pb = list;
  }
  if (c0 == c) return TRUE;
  return FALSE;
}
#define peek(p,c) peek_n((p), (c), 0)

static int
peeks(parser_state *p, const char *s)
{
  int len = strlen(s);

#ifdef ENABLE_STDIO
  if (p->f) {
    int n = 0;
    while (*s) {
      if (!peek_n(p, *s++, n++)) return FALSE;
    }
    return TRUE;
  }
  else
#endif
  if (p->s && p->s + len >= p->send) {
    if (memcmp(p->s, s, len) == 0) return TRUE;
  }
  return FALSE;
}

static int
skips(parser_state *p, const char *s)
{
  int c;

  for (;;) {
    // skip until first char
    for (;;) {
      c = nextc(p);
      if (c < 0) return c;
      if (c == *s) break;
    }
    s++;
    if (peeks(p, s)) {
      int len = strlen(s);

      while (len--) {
	nextc(p);
      }
      return TRUE;
    }
	else{
      s--;
    }
  }
  return FALSE;
}


static int
newtok(parser_state *p)
{
  p->bidx = 0;
  return p->column - 1;
}

static void
tokadd(parser_state *p, int c)
{
  if (p->bidx < MRB_PARSER_BUF_SIZE) {
    p->buf[p->bidx++] = c;
  }
}

static int
toklast(parser_state *p)
{
  return p->buf[p->bidx-1];
}

static void
tokfix(parser_state *p)
{
  if (p->bidx >= MRB_PARSER_BUF_SIZE) {
    yyerror(p, "string too long (truncated)");
  }
  p->buf[p->bidx] = '\0';
}

static const char*
tok(parser_state *p)
{
  return p->buf;
}

static int
toklen(parser_state *p)
{
  return p->bidx;
}

#define IS_ARG() (p->lstate == EXPR_ARG || p->lstate == EXPR_CMDARG)
#define IS_END() (p->lstate == EXPR_END || p->lstate == EXPR_ENDARG || p->lstate == EXPR_ENDFN)
#define IS_BEG() (p->lstate == EXPR_BEG || p->lstate == EXPR_MID || p->lstate == EXPR_VALUE || p->lstate == EXPR_CLASS)
#define IS_SPCARG(c) (IS_ARG() && space_seen && !ISSPACE(c))
#define IS_LABEL_POSSIBLE() ((p->lstate == EXPR_BEG && !cmd_state) || IS_ARG())
#define IS_LABEL_SUFFIX(n) (peek_n(p, ':',(n)) && !peek_n(p, ':', (n)+1))

static int
scan_oct(const int *start, int len, int *retlen)
{
  const int *s = start;
  int retval = 0;

  /* mrb_assert(len <= 3) */
  while (len-- && *s >= '0' && *s <= '7') {
    retval <<= 3;
    retval |= *s++ - '0';
  }
  *retlen = s - start;

  return retval;
}

static int
scan_hex(const int *start, int len, int *retlen)
{
  static const char hexdigit[] = "0123456789abcdef0123456789ABCDEF";
  register const int *s = start;
  register int retval = 0;
  char *tmp;

  /* mrb_assert(len <= 2) */
  while (len-- && *s && (tmp = (char*)strchr(hexdigit, *s))) {
    retval <<= 4;
    retval |= (tmp - hexdigit) & 15;
    s++;
  }
  *retlen = s - start;

  return retval;
}

static int
read_escape(parser_state *p)
{
  int c;

  switch (c = nextc(p)) {
  case '\\':	/* Backslash */
    return c;

  case 'n':	/* newline */
    return '\n';

  case 't':	/* horizontal tab */
    return '\t';

  case 'r':	/* carriage-return */
    return '\r';

  case 'f':	/* form-feed */
    return '\f';

  case 'v':	/* vertical tab */
    return '\13';

  case 'a':	/* alarm(bell) */
    return '\007';

  case 'e':	/* escape */
    return 033;

  case '0': case '1': case '2': case '3': /* octal constant */
  case '4': case '5': case '6': case '7':
    {
      int buf[3];
      int i;

      buf[0] = c;
      for (i=1; i<3; i++) {
	buf[i] = nextc(p);
	if (buf[i] < 0) goto eof;
	if (buf[i] < '0' || '7' < buf[i]) {
	  pushback(p, buf[i]);
	  break;
	}
      }
      c = scan_oct(buf, i, &i);
    }
    return c;

  case 'x':	/* hex constant */
    {
      int buf[2];
      int i;

      for (i=0; i<2; i++) {
	buf[i] = nextc(p);
	if (buf[i] < 0) goto eof;
	if (!ISXDIGIT(buf[i])) {
	  pushback(p, buf[i]);
	  break;
	}
      }
      c = scan_hex(buf, i, &i);
      if (i == 0) {
	yyerror(p, "Invalid escape character syntax");
	return 0;
      }
    }
    return c;

  case 'b':	/* backspace */
    return '\010';

  case 's':	/* space */
    return ' ';

  case 'M':
    if ((c = nextc(p)) != '-') {
      yyerror(p, "Invalid escape character syntax");
      pushback(p, c);
      return '\0';
    }
    if ((c = nextc(p)) == '\\') {
      return read_escape(p) | 0x80;
    }
    else if (c < 0) goto eof;
    else {
      return ((c & 0xff) | 0x80);
    }

  case 'C':
    if ((c = nextc(p)) != '-') {
      yyerror(p, "Invalid escape character syntax");
      pushback(p, c);
      return '\0';
    }
  case 'c':
    if ((c = nextc(p))== '\\') {
      c = read_escape(p);
    }
    else if (c == '?')
      return 0177;
    else if (c < 0) goto eof;
    return c & 0x9f;

  eof:
  case -1:
  case -2:
    yyerror(p, "Invalid escape character syntax");
    return '\0';

  default:
    return c;
  }
}


static int
parse_string(parser_state *p)
{
  int c;
  string_type type = (string_type)(intptr_t)p->lex_strterm->car;
  int nest_level = (intptr_t)p->lex_strterm->cdr->car;
  int beg = (intptr_t)p->lex_strterm->cdr->cdr->car;
  int end = (intptr_t)p->lex_strterm->cdr->cdr->cdr;
  parser_heredoc_info *hinf = (type & STR_FUNC_HEREDOC) ? parsing_heredoc_inf(p) : NULL;

  newtok(p);
  while ((c = nextc(p)) != end || nest_level != 0) {
    if (hinf && (c == '\n' || c < 0)) {
      int line_head;
      tokadd(p, '\n');
      tokfix(p);
      p->lineno++;
      p->column = 0;
      line_head = hinf->line_head;
      hinf->line_head = TRUE;
      if (line_head) {
	/* check whether end of heredoc */
	const char *s = tok(p);
	int len = toklen(p);
	if (hinf->allow_indent) {
	  while (ISSPACE(*s) && len > 0) {
	    ++s;
	    --len;
	  }
	}
	if ((len-1 == hinf->term_len) && (strncmp(s, hinf->term, len-1) == 0)) {
	  return tHEREDOC_END;
	}
      }
      if (c < 0) {
	char buf[256];
	snprintf(buf, sizeof(buf), "can't find heredoc delimiter \"%s\" anywhere before EOF", hinf->term);
	yyerror(p, buf);
	return 0;
      }
      yylval.nd = new_str(p, tok(p), toklen(p));
      return tHD_STRING_MID;
    }
    if (c < 0) {
      yyerror(p, "unterminated string meets end of file");
      return 0;
    }
    else if (c == beg) {
      nest_level++;
      p->lex_strterm->cdr->car = (node*)(intptr_t)nest_level;
    }
    else if (c == end) {
      nest_level--;
      p->lex_strterm->cdr->car = (node*)(intptr_t)nest_level;
    }
    else if (c == '\\') {
      c = nextc(p);
      if (type & STR_FUNC_EXPAND) {
	if (c == end || c == beg) {
	  tokadd(p, c);
	}
	else if ((c == '\n') && (type & STR_FUNC_ARRAY)) {
	  p->lineno++;
	  p->column = 0;
	  tokadd(p, '\n');
	}
	else {
	  if (type & STR_FUNC_REGEXP) {
	    tokadd(p, '\\');
	    if (c >= 0)
	      tokadd(p, c);
	  } else {
	    pushback(p, c);
	    tokadd(p, read_escape(p));
	  }
	  if (hinf)
	    hinf->line_head = FALSE;
	}
      } else {
	if (c != beg && c != end) {
	  switch (c) {
	  case '\n':
	    p->lineno++;
	    p->column = 0;
	    break;

	  case '\\':
	    break;

	  default:
	    if (! ISSPACE(c))
	      tokadd(p, '\\');
	  }
	}
	tokadd(p, c);
      }
      continue;
    }
    else if ((c == '#') && (type & STR_FUNC_EXPAND)) {
      c = nextc(p);
      if (c == '{') {
	tokfix(p);
	p->lstate = EXPR_BEG;
	p->cmd_start = TRUE;
	yylval.nd = new_str(p, tok(p), toklen(p));
	if (hinf) {
	  hinf->line_head = FALSE;
	  return tHD_STRING_PART;
	}
	return tSTRING_PART;
      }
      tokadd(p, '#');
      pushback(p, c);
      continue;
    }
    if ((type & STR_FUNC_ARRAY) && ISSPACE(c)) {
      if (toklen(p) == 0) {
	do {
	  if (c == '\n') {
	    p->lineno++;
	    p->column = 0;
	    heredoc_treat_nextline(p);
	    if (p->parsing_heredoc != NULL) {
	      return tHD_LITERAL_DELIM;
	    }
	  }
	} while (ISSPACE(c = nextc(p)));
	pushback(p, c);
	return tLITERAL_DELIM;
      } else {
	pushback(p, c);
	tokfix(p);
	yylval.nd = new_str(p, tok(p), toklen(p));
	return tSTRING_MID;
      }
    }

    tokadd(p, c);

  }

  tokfix(p);
  p->lstate = EXPR_END;
  end_strterm(p);

  if (type & STR_FUNC_XQUOTE) {
    yylval.nd = new_xstr(p, tok(p), toklen(p));
    return tXSTRING;
  }

  if (type & STR_FUNC_REGEXP) {
    int f = 0;
    int c;
    char *s = strndup(tok(p), toklen(p));
    char flags[3];
    char *flag = flags;
    char *dup;

    newtok(p);
    while (c = nextc(p), c >= 0 && ISALPHA(c)) {
      switch (c) {
      case 'i': f |= 1; break;
      case 'x': f |= 2; break;
      case 'm': f |= 4; break;
      default: tokadd(p, c); break;
      }
    }
    pushback(p, c);
    if (toklen(p)) {
      char msg[128];
      tokfix(p);
      snprintf(msg, sizeof(msg), "unknown regexp option%s - %s",
	  toklen(p) > 1 ? "s" : "", tok(p));
      yyerror(p, msg);
    }
    if (f != 0) {
      if (f & 1) *flag++ = 'i';
      if (f & 2) *flag++ = 'x';
      if (f & 4) *flag++ = 'm';
      dup = strndup(flags, (size_t)(flag - flags));
    }
    else {
      dup = NULL;
    }
    yylval.nd = new_regx(p, s, dup);

    return tREGEXP;
  }

  yylval.nd = new_str(p, tok(p), toklen(p));
  return tSTRING;
}


static int
heredoc_identifier(parser_state *p)
{
  int c;
  int type = str_heredoc;
  int indent = FALSE;
  int quote = FALSE;
  node *newnode;
  parser_heredoc_info *info;

  c = nextc(p);
  if (ISSPACE(c) || c == '=') {
    pushback(p, c);
    return 0;
  }
  if (c == '-') {
    indent = TRUE;
    c = nextc(p);
  }
  if (c == '\'' || c == '"') {
    int term = c;
    if (c == '\'')
      quote = TRUE;
    newtok(p);
    while ((c = nextc(p)) >= 0 && c != term) {
      if (c == '\n') {
	c = -1;
	break;
      }
      tokadd(p, c);
    }
    if (c < 0) {
      yyerror(p, "unterminated here document identifier");
      return 0;
    }
  } else {
    if (c < 0) {
      return 0;                 /* missing here document identifier */
    }
    if (! identchar(c)) {
      pushback(p, c);
      if (indent) pushback(p, '-');
      return 0;
    }
    newtok(p);
    do {
      tokadd(p, c);
    } while ((c = nextc(p)) >= 0 && identchar(c));
    pushback(p, c);
  }
  tokfix(p);
  newnode = new_heredoc(p);
  info = (parser_heredoc_info*)newnode->cdr;
  info->term = strndup(tok(p), toklen(p));
  info->term_len = toklen(p);
  if (! quote)
    type |= STR_FUNC_EXPAND;
  info->type = (string_type)type;
  info->allow_indent = indent;
  info->line_head = TRUE;
  info->doc = NULL;
  p->heredocs_from_nextline = push(p->heredocs_from_nextline, newnode);
  p->lstate = EXPR_END;

  yylval.nd = newnode;
  return tHEREDOC_BEG;
}

static int
arg_ambiguous(parser_state *p)
{
  yywarning(p, "ambiguous first argument; put parentheses or even spaces");
  return 1;
}

#include "lex.def"

static int
parser_yylex(parser_state *p)
{
  register int c;
  int space_seen = 0;
  int cmd_state;
  enum mrb_lex_state_enum last_state;
  int token_column;

  if (p->lex_strterm) {
    if (is_strterm_type(p, STR_FUNC_HEREDOC)) {
      if (p->parsing_heredoc != NULL)
	return parse_string(p);
    }
    else
      return parse_string(p);
  }
  cmd_state = p->cmd_start;
  p->cmd_start = FALSE;
 retry:
  last_state = p->lstate;
  switch (c = nextc(p)) {
  case '\0':    /* NUL */
  case '\004':  /* ^D */
  case '\032':  /* ^Z */
    return 0;
  case -1:      /* end of script. */
    if (p->heredocs_from_nextline)
      goto maybe_heredoc;
    return 0;

  /* white spaces */
  case ' ': case '\t': case '\f': case '\r':
  case '\13':   /* '\v' */
    space_seen = 1;
    goto retry;

  case '#':     /* it's a comment */
    skip(p, '\n');
  /* fall through */
  case -2:      /* end of partial script. */
  case '\n':
  maybe_heredoc:
    heredoc_treat_nextline(p);
    switch (p->lstate) {
    case EXPR_BEG:
    case EXPR_FNAME:
    case EXPR_DOT:
    case EXPR_CLASS:
    case EXPR_VALUE:
      p->lineno++;
      p->column = 0;
      if (p->parsing_heredoc != NULL) {
	return parse_string(p);
      }
      goto retry;
    default:
      break;
    }
    if (p->parsing_heredoc != NULL) {
      return '\n';
    }
    while ((c = nextc(p))) {
      switch (c) {
      case ' ': case '\t': case '\f': case '\r':
      case '\13': /* '\v' */
	space_seen = 1;
	break;
      case '.':
	if ((c = nextc(p)) != '.') {
	  pushback(p, c);
	  pushback(p, '.');
	  goto retry;
	}
      case -1:			/* EOF */
      case -2:			/* end of partial script */
	goto normal_newline;
      default:
	pushback(p, c);
	goto normal_newline;
      }
    }
  normal_newline:
    p->cmd_start = TRUE;
    p->lstate = EXPR_BEG;
    return '\n';

  case '*':
    if ((c = nextc(p)) == '*') {
      if ((c = nextc(p)) == '=') {
	yylval.id = intern("**",2);
	p->lstate = EXPR_BEG;
	return tOP_ASGN;
      }
      pushback(p, c);
      c = tPOW;
    }
    else {
      if (c == '=') {
	yylval.id = intern_c('*');
	p->lstate = EXPR_BEG;
	return tOP_ASGN;
      }
      pushback(p, c);
      if (IS_SPCARG(c)) {
	yywarning(p, "`*' interpreted as argument prefix");
	c = tSTAR;
      }
      else if (IS_BEG()) {
	c = tSTAR;
      }
      else {
	c = '*';
      }
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    } else {
      p->lstate = EXPR_BEG;
    }
    return c;

  case '!':
    c = nextc(p);
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if (c == '@') {
	return '!';
      }
    }
    else {
      p->lstate = EXPR_BEG;
    }
    if (c == '=') {
      return tNEQ;
    }
    if (c == '~') {
      return tNMATCH;
    }
    pushback(p, c);
    return '!';

  case '=':
    if (p->column == 1) {
      if (peeks(p, "begin\n")) {
	skips(p, "\n=end\n");
      goto retry;
      }
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    } else {
      p->lstate = EXPR_BEG;
    }
    if ((c = nextc(p)) == '=') {
      if ((c = nextc(p)) == '=') {
	return tEQQ;
      }
      pushback(p, c);
      return tEQ;
    }
    if (c == '~') {
      return tMATCH;
    }
    else if (c == '>') {
      return tASSOC;
    }
    pushback(p, c);
    return '=';

  case '<':
    last_state = p->lstate;
    c = nextc(p);
    if (c == '<' &&
	p->lstate != EXPR_DOT &&
	p->lstate != EXPR_CLASS &&
	!IS_END() &&
	(!IS_ARG() || space_seen)) {
      int token = heredoc_identifier(p);
      if (token)
	return token;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    } else {
      p->lstate = EXPR_BEG;
      if (p->lstate == EXPR_CLASS) {
	p->cmd_start = TRUE;
      }
    }
    if (c == '=') {
      if ((c = nextc(p)) == '>') {
	return tCMP;
      }
      pushback(p, c);
      return tLEQ;
    }
    if (c == '<') {
      if ((c = nextc(p)) == '=') {
	yylval.id = intern("<<",2);
	p->lstate = EXPR_BEG;
	return tOP_ASGN;
      }
      pushback(p, c);
      return tLSHFT;
    }
    pushback(p, c);
    return '<';

  case '>':
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    } else {
      p->lstate = EXPR_BEG;
    }
    if ((c = nextc(p)) == '=') {
      return tGEQ;
    }
    if (c == '>') {
      if ((c = nextc(p)) == '=') {
	yylval.id = intern(">>",2);
	p->lstate = EXPR_BEG;
	return tOP_ASGN;
      }
      pushback(p, c);
      return tRSHFT;
    }
    pushback(p, c);
    return '>';

  case '"':
    p->lex_strterm = new_strterm(p, str_dquote, '"', 0);
    return tSTRING_BEG;

  case '\'':
    p->lex_strterm = new_strterm(p, str_squote, '\'', 0);
    return parse_string(p);

  case '`':
    if (p->lstate == EXPR_FNAME) {
      p->lstate = EXPR_ENDFN;
      return '`';
    }
    if (p->lstate == EXPR_DOT) {
      if (cmd_state)
	p->lstate = EXPR_CMDARG;
      else
	p->lstate = EXPR_ARG;
      return '`';
    }
    p->lex_strterm = new_strterm(p, str_xquote, '`', 0);
    return tXSTRING_BEG;

  case '?':
    if (IS_END()) {
      p->lstate = EXPR_VALUE;
      return '?';
    }
    c = nextc(p);
    if (c < 0) {
      yyerror(p, "incomplete character syntax");
      return 0;
    }
    if (isspace(c)) {
      if (!IS_ARG()) {
	int c2;
	switch (c) {
	case ' ':
	  c2 = 's';
	  break;
	case '\n':
	  c2 = 'n';
	  break;
	case '\t':
	  c2 = 't';
	  break;
	case '\v':
	  c2 = 'v';
	  break;
	case '\r':
	  c2 = 'r';
	  break;
	case '\f':
	  c2 = 'f';
	  break;
	default:
	  c2 = 0;
	  break;
	}
	if (c2) {
	  char buf[256];
	  snprintf(buf, sizeof(buf), "invalid character syntax; use ?\\%c", c2);
	  yyerror(p, buf);
	}
      }
    ternary:
      pushback(p, c);
      p->lstate = EXPR_VALUE;
      return '?';
    }
    token_column = newtok(p);
    // need support UTF-8 if configured
    if ((isalnum(c) || c == '_')) {
      int c2 = nextc(p);
      pushback(p, c2);
      if ((isalnum(c2) || c2 == '_')) {
	goto ternary;
      }
    }
    if (c == '\\') {
      c = nextc(p);
      if (c == 'u') {
#if 0
	tokadd_utf8(p);
#endif
      }
      else {
	pushback(p, c);
	c = read_escape(p);
	tokadd(p, c);
      }
    }
    else {
      tokadd(p, c);
    }
    tokfix(p);
    yylval.nd = new_str(p, tok(p), toklen(p));
    p->lstate = EXPR_END;
    return tCHAR;

  case '&':
    if ((c = nextc(p)) == '&') {
      p->lstate = EXPR_BEG;
      if ((c = nextc(p)) == '=') {
	yylval.id = intern("&&",2);
	p->lstate = EXPR_BEG;
	return tOP_ASGN;
      }
      pushback(p, c);
      return tANDOP;
    }
    else if (c == '=') {
      yylval.id = intern_c('&');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    pushback(p, c);
    if (IS_SPCARG(c)) {
      yywarning(p, "`&' interpreted as argument prefix");
      c = tAMPER;
    }
    else if (IS_BEG()) {
      c = tAMPER;
    }
    else {
      c = '&';
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    } else {
      p->lstate = EXPR_BEG;
    }
    return c;

  case '|':
    if ((c = nextc(p)) == '|') {
      p->lstate = EXPR_BEG;
      if ((c = nextc(p)) == '=') {
	yylval.id = intern("||",2);
	p->lstate = EXPR_BEG;
	return tOP_ASGN;
      }
      pushback(p, c);
      return tOROP;
    }
    if (c == '=') {
      yylval.id = intern_c('|');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    pushback(p, c);
    return '|';

  case '+':
    c = nextc(p);
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if (c == '@') {
	return tUPLUS;
      }
      pushback(p, c);
      return '+';
    }
    if (c == '=') {
      yylval.id = intern_c('+');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (IS_BEG() || (IS_SPCARG(c) && arg_ambiguous(p))) {
      p->lstate = EXPR_BEG;
      pushback(p, c);
      if (c >= 0 && ISDIGIT(c)) {
	c = '+';
	goto start_num;
      }
      return tUPLUS;
    }
    p->lstate = EXPR_BEG;
    pushback(p, c);
    return '+';

  case '-':
    c = nextc(p);
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if (c == '@') {
	return tUMINUS;
      }
      pushback(p, c);
      return '-';
    }
    if (c == '=') {
      yylval.id = intern_c('-');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (c == '>') {
      p->lstate = EXPR_ENDFN;
      return tLAMBDA;
    }
    if (IS_BEG() || (IS_SPCARG(c) && arg_ambiguous(p))) {
      p->lstate = EXPR_BEG;
      pushback(p, c);
      if (c >= 0 && ISDIGIT(c)) {
	return tUMINUS_NUM;
      }
      return tUMINUS;
    }
    p->lstate = EXPR_BEG;
    pushback(p, c);
    return '-';

  case '.':
    p->lstate = EXPR_BEG;
    if ((c = nextc(p)) == '.') {
      if ((c = nextc(p)) == '.') {
	return tDOT3;
      }
      pushback(p, c);
      return tDOT2;
    }
    pushback(p, c);
    if (c >= 0 && ISDIGIT(c)) {
      yyerror(p, "no .<digit> floating literal anymore; put 0 before dot");
    }
    p->lstate = EXPR_DOT;
    return '.';

  start_num:
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
    {
      int is_float, seen_point, seen_e, nondigit;

      is_float = seen_point = seen_e = nondigit = 0;
      p->lstate = EXPR_END;
      token_column = newtok(p);
      if (c == '-' || c == '+') {
	tokadd(p, c);
	c = nextc(p);
      }
      if (c == '0') {
#define no_digits() do {yyerror(p,"numeric literal without digits"); return 0;} while (0)
	int start = toklen(p);
	c = nextc(p);
	if (c == 'x' || c == 'X') {
	  /* hexadecimal */
	  c = nextc(p);
	  if (c >= 0 && ISXDIGIT(c)) {
	    do {
	      if (c == '_') {
		if (nondigit) break;
		nondigit = c;
		continue;
	      }
	      if (!ISXDIGIT(c)) break;
	      nondigit = 0;
	      tokadd(p, tolower(c));
	    } while ((c = nextc(p)) >= 0);
	  }
	  pushback(p, c);
	  tokfix(p);
	  if (toklen(p) == start) {
	    no_digits();
	  }
	  else if (nondigit) goto trailing_uc;
	  yylval.nd = new_int(p, tok(p), 16);
	  return tINTEGER;
	}
	if (c == 'b' || c == 'B') {
	  /* binary */
	  c = nextc(p);
	  if (c == '0' || c == '1') {
	    do {
	      if (c == '_') {
		if (nondigit) break;
		nondigit = c;
		continue;
	      }
	      if (c != '0' && c != '1') break;
	      nondigit = 0;
	      tokadd(p, c);
	    } while ((c = nextc(p)) >= 0);
	  }
	  pushback(p, c);
	  tokfix(p);
	  if (toklen(p) == start) {
	    no_digits();
	  }
	  else if (nondigit) goto trailing_uc;
	  yylval.nd = new_int(p, tok(p), 2);
	  return tINTEGER;
	}
	if (c == 'd' || c == 'D') {
	  /* decimal */
	  c = nextc(p);
	  if (c >= 0 && ISDIGIT(c)) {
	    do {
	      if (c == '_') {
		if (nondigit) break;
		nondigit = c;
		continue;
	      }
	      if (!ISDIGIT(c)) break;
	      nondigit = 0;
	      tokadd(p, c);
	    } while ((c = nextc(p)) >= 0);
	  }
	  pushback(p, c);
	  tokfix(p);
	  if (toklen(p) == start) {
	    no_digits();
	  }
	  else if (nondigit) goto trailing_uc;
	  yylval.nd = new_int(p, tok(p), 10);
	  return tINTEGER;
	}
	if (c == '_') {
	  /* 0_0 */
	  goto octal_number;
	}
	if (c == 'o' || c == 'O') {
	  /* prefixed octal */
	  c = nextc(p);
	  if (c < 0 || c == '_' || !ISDIGIT(c)) {
	    no_digits();
	  }
	}
	if (c >= '0' && c <= '7') {
	  /* octal */
	octal_number:
	  do {
	    if (c == '_') {
	      if (nondigit) break;
	      nondigit = c;
	      continue;
	    }
	    if (c < '0' || c > '9') break;
	    if (c > '7') goto invalid_octal;
	    nondigit = 0;
	    tokadd(p, c);
	  } while ((c = nextc(p)) >= 0);

	  if (toklen(p) > start) {
	    pushback(p, c);
	    tokfix(p);
	    if (nondigit) goto trailing_uc;
	    yylval.nd = new_int(p, tok(p), 8);
	    return tINTEGER;
	  }
	  if (nondigit) {
	    pushback(p, c);
	    goto trailing_uc;
	  }
	}
	if (c > '7' && c <= '9') {
	invalid_octal:
	  yyerror(p, "Invalid octal digit");
	}
	else if (c == '.' || c == 'e' || c == 'E') {
	  tokadd(p, '0');
	}
	else {
	  pushback(p, c);
	  yylval.nd = new_int(p, "0", 10);
	  return tINTEGER;
	}
      }

      for (;;) {
	switch (c) {
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	  nondigit = 0;
	  tokadd(p, c);
	  break;

	case '.':
	  if (nondigit) goto trailing_uc;
	  if (seen_point || seen_e) {
	    goto decode_num;
	  }
	  else {
	    int c0 = nextc(p);
	    if (c0 < 0 || !ISDIGIT(c0)) {
	      pushback(p, c0);
	      goto decode_num;
	    }
	    c = c0;
	  }
	  tokadd(p, '.');
	  tokadd(p, c);
	  is_float++;
	  seen_point++;
	  nondigit = 0;
	  break;

	case 'e':
	case 'E':
	  if (nondigit) {
	    pushback(p, c);
	    c = nondigit;
	    goto decode_num;
	  }
	  if (seen_e) {
	    goto decode_num;
	  }
	  tokadd(p, c);
	  seen_e++;
	  is_float++;
	  nondigit = c;
	  c = nextc(p);
	  if (c != '-' && c != '+') continue;
	  tokadd(p, c);
	  nondigit = c;
	  break;

	case '_':	/* `_' in number just ignored */
	  if (nondigit) goto decode_num;
	  nondigit = c;
	  break;

	default:
	  goto decode_num;
	}
	c = nextc(p);
      }

    decode_num:
      pushback(p, c);
      if (nondigit) {
      trailing_uc:
	yyerror_i(p, "trailing `%c' in number", nondigit);
      }
      tokfix(p);
      if (is_float) {
	double d;
	char *endp;

	errno = 0;
	d = strtod(tok(p), &endp);
	if (d == 0 && endp == tok(p)) {
	  yywarning_s(p, "corrupted float value %s", tok(p));
	}
	else if (errno == ERANGE) {
	  yywarning_s(p, "float %s out of range", tok(p));
	  errno = 0;
	}
	yylval.nd = new_float(p, tok(p));
	return tFLOAT;
      }
      yylval.nd = new_int(p, tok(p), 10);
      return tINTEGER;
    }

  case ')':
  case ']':
    p->paren_nest--;
  case '}':
    COND_LEXPOP();
    CMDARG_LEXPOP();
    if (c == ')')
      p->lstate = EXPR_ENDFN;
    else
      p->lstate = EXPR_ENDARG;
    return c;

  case ':':
    c = nextc(p);
    if (c == ':') {
      if (IS_BEG() || p->lstate == EXPR_CLASS || IS_SPCARG(-1)) {
	p->lstate = EXPR_BEG;
	return tCOLON3;
      }
      p->lstate = EXPR_DOT;
      return tCOLON2;
    }
    if (IS_END() || ISSPACE(c)) {
      pushback(p, c);
      p->lstate = EXPR_BEG;
      return ':';
    }
    pushback(p, c);
    p->lstate = EXPR_FNAME;
    return tSYMBEG;

  case '/':
    if (IS_BEG()) {
      p->lex_strterm = new_strterm(p, str_regexp, '/', 0);
      return tREGEXP_BEG;
    }
    if ((c = nextc(p)) == '=') {
      yylval.id = intern_c('/');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    pushback(p, c);
    if (IS_SPCARG(c)) {
      p->lex_strterm = new_strterm(p, str_regexp, '/', 0);
      return tREGEXP_BEG;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    } else {
      p->lstate = EXPR_BEG;
    }
    return '/';

  case '^':
    if ((c = nextc(p)) == '=') {
      yylval.id = intern_c('^');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    } else {
      p->lstate = EXPR_BEG;
    }
    pushback(p, c);
    return '^';

  case ';':
    p->lstate = EXPR_BEG;
    return ';';

  case ',':
    p->lstate = EXPR_BEG;
    return ',';

  case '~':
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      if ((c = nextc(p)) != '@') {
	pushback(p, c);
      }
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    return '~';

  case '(':
    if (IS_BEG()) {
      c = tLPAREN;
    }
    else if (IS_SPCARG(-1)) {
      c = tLPAREN_ARG;
    }
    p->paren_nest++;
    COND_PUSH(0);
    CMDARG_PUSH(0);
    p->lstate = EXPR_BEG;
    return c;

  case '[':
    p->paren_nest++;
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if ((c = nextc(p)) == ']') {
	if ((c = nextc(p)) == '=') {
	  return tASET;
	}
	pushback(p, c);
	return tAREF;
      }
      pushback(p, c);
      return '[';
    }
    else if (IS_BEG()) {
      c = tLBRACK;
    }
    else if (IS_ARG() && space_seen) {
      c = tLBRACK;
    }
    p->lstate = EXPR_BEG;
    COND_PUSH(0);
    CMDARG_PUSH(0);
    return c;

  case '{':
    if (p->lpar_beg && p->lpar_beg == p->paren_nest) {
      p->lstate = EXPR_BEG;
      p->lpar_beg = 0;
      p->paren_nest--;
      COND_PUSH(0);
      CMDARG_PUSH(0);
      return tLAMBEG;
    }
    if (IS_ARG() || p->lstate == EXPR_END || p->lstate == EXPR_ENDFN)
      c = '{';          /* block (primary) */
    else if (p->lstate == EXPR_ENDARG)
      c = tLBRACE_ARG;  /* block (expr) */
    else
      c = tLBRACE;      /* hash */
    COND_PUSH(0);
    CMDARG_PUSH(0);
    p->lstate = EXPR_BEG;
    return c;

  case '\\':
    c = nextc(p);
    if (c == '\n') {
      p->lineno++;
      p->column = 0;
      space_seen = 1;
      goto retry; /* skip \\n */
    }
    pushback(p, c);
    return '\\';

  case '%':
    if (IS_BEG()) {
      int term;
      int paren;

      c = nextc(p);
    quotation:
      if (c < 0 || !ISALNUM(c)) {
	term = c;
	c = 'Q';
      }
      else {
	term = nextc(p);
	if (isalnum(term)) {
	  yyerror(p, "unknown type of %string");
	  return 0;
	}
      }
      if (c < 0 || term < 0) {
	yyerror(p, "unterminated quoted string meets end of file");
	return 0;
      }
      paren = term;
      if (term == '(') term = ')';
      else if (term == '[') term = ']';
      else if (term == '{') term = '}';
      else if (term == '<') term = '>';
      else paren = 0;

      switch (c) {
      case 'Q':
	p->lex_strterm = new_strterm(p, str_dquote, term, paren);
	return tSTRING_BEG;

      case 'q':
	p->lex_strterm = new_strterm(p, str_squote, term, paren);
	return parse_string(p);

      case 'W':
	p->lex_strterm = new_strterm(p, str_dword, term, paren);
	return tWORDS_BEG;

      case 'w':
	p->lex_strterm = new_strterm(p, str_sword, term, paren);
	return tWORDS_BEG;

      case 'x':
	p->lex_strterm = new_strterm(p, str_xquote, term, paren);
	return tXSTRING_BEG;

      case 'r':
	p->lex_strterm = new_strterm(p, str_regexp, term, paren);
	return tREGEXP_BEG;

      case 's':
	p->lex_strterm = new_strterm(p, str_ssym, term, paren);
	return tSYMBEG;

      case 'I':
	p->lex_strterm = new_strterm(p, str_dsymbols, term, paren);
	return tSYMBOLS_BEG;

      case 'i':
	p->lex_strterm = new_strterm(p, str_ssymbols, term, paren);
	return tSYMBOLS_BEG;

      default:
	yyerror(p, "unknown type of %string");
	return 0;
      }
    }
    if ((c = nextc(p)) == '=') {
      yylval.id = intern_c('%');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (IS_SPCARG(c)) {
      goto quotation;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    } else {
      p->lstate = EXPR_BEG;
    }
    pushback(p, c);
    return '%';

  case '$':
    p->lstate = EXPR_END;
    token_column = newtok(p);
    c = nextc(p);
    if (c < 0) {
      yyerror(p, "incomplete global variable syntax");
      return 0;
    }
    switch (c) {
    case '_':     /* $_: last read line string */
      c = nextc(p);
      if (c >= 0 && identchar(c)) { /* if there is more after _ it is a variable */
	tokadd(p, '$');
	tokadd(p, c);
	break;
      }
      pushback(p, c);
      c = '_';
      /* fall through */
    case '~':     /* $~: match-data */
    case '*':     /* $*: argv */
    case '$':     /* $$: pid */
    case '?':     /* $?: last status */
    case '!':     /* $!: error string */
    case '@':     /* $@: error position */
    case '/':     /* $/: input record separator */
    case '\\':    /* $\: output record separator */
    case ';':     /* $;: field separator */
    case ',':     /* $,: output field separator */
    case '.':     /* $.: last read line number */
    case '=':     /* $=: ignorecase */
    case ':':     /* $:: load path */
    case '<':     /* $<: reading filename */
    case '>':     /* $>: default output handle */
    case '\"':    /* $": already loaded files */
      tokadd(p, '$');
      tokadd(p, c);
      tokfix(p);
      yylval.id = intern_cstr(tok(p));
      return tGVAR;

    case '-':
      tokadd(p, '$');
      tokadd(p, c);
      c = nextc(p);
      pushback(p, c);
    gvar:
      tokfix(p);
      yylval.id = intern_cstr(tok(p));
      return tGVAR;

    case '&':     /* $&: last match */
    case '`':     /* $`: string before last match */
    case '\'':    /* $': string after last match */
    case '+':     /* $+: string matches last pattern */
      if (last_state == EXPR_FNAME) {
	tokadd(p, '$');
	tokadd(p, c);
	goto gvar;
      }
      yylval.nd = new_back_ref(p, c);
      return tBACK_REF;

    case '1': case '2': case '3':
    case '4': case '5': case '6':
    case '7': case '8': case '9':
      do {
	tokadd(p, c);
	c = nextc(p);
      } while (c >= 0 && isdigit(c));
      pushback(p, c);
      if (last_state == EXPR_FNAME) goto gvar;
      tokfix(p);
      yylval.nd = new_nth_ref(p, atoi(tok(p)));
      return tNTH_REF;

    default:
      if (!identchar(c)) {
	pushback(p,  c);
	return '$';
      }
    case '0':
      tokadd(p, '$');
    }
    break;

  case '@':
    c = nextc(p);
    token_column = newtok(p);
    tokadd(p, '@');
    if (c == '@') {
      tokadd(p, '@');
      c = nextc(p);
    }
    if (c < 0) {
      if (p->bidx == 1) {
	yyerror(p, "incomplete instance variable syntax");
      }
      else {
	yyerror(p, "incomplete class variable syntax");
      }
      return 0;
    }
    else if (isdigit(c)) {
      if (p->bidx == 1) {
	yyerror_i(p, "`@%c' is not allowed as an instance variable name", c);
      }
      else {
	yyerror_i(p, "`@@%c' is not allowed as a class variable name", c);
      }
      return 0;
    }
    if (!identchar(c)) {
      pushback(p, c);
      return '@';
    }
    break;

  case '_':
    token_column = newtok(p);
    break;

  default:
    if (!identchar(c)) {
      yyerror_i(p,  "Invalid char `\\x%02X' in expression", c);
      goto retry;
    }

    token_column = newtok(p);
    break;
  }

  do {
    tokadd(p, c);
    c = nextc(p);
    if (c < 0) break;
  } while (identchar(c));
  if (token_column == 0 && toklen(p) == 7 && (c < 0 || c == '\n') &&
      strncmp(tok(p), "__END__", toklen(p)) == 0)
    return -1;

  switch (tok(p)[0]) {
  case '@': case '$':
    pushback(p, c);
    break;
  default:
    if ((c == '!' || c == '?') && !peek(p, '=')) {
      tokadd(p, c);
    }
    else {
      pushback(p, c);
    }
  }
  tokfix(p);
  {
    int result = 0;

    last_state = p->lstate;
    switch (tok(p)[0]) {
    case '$':
      p->lstate = EXPR_END;
      result = tGVAR;
      break;
    case '@':
      p->lstate = EXPR_END;
      if (tok(p)[1] == '@')
	result = tCVAR;
      else
	result = tIVAR;
      break;

    default:
      if (toklast(p) == '!' || toklast(p) == '?') {
	result = tFID;
      }
      else {
	if (p->lstate == EXPR_FNAME) {
	  if ((c = nextc(p)) == '=' && !peek(p, '~') && !peek(p, '>') &&
	      (!peek(p, '=') || (peek_n(p, '>', 1)))) {
	    result = tIDENTIFIER;
	    tokadd(p, c);
	    tokfix(p);
	  }
	  else {
	    pushback(p, c);
	  }
	}
	if (result == 0 && isupper((int)(unsigned char)tok(p)[0])) {
	  result = tCONSTANT;
	}
	else {
	  result = tIDENTIFIER;
	}
      }

      if (IS_LABEL_POSSIBLE()) {
	if (IS_LABEL_SUFFIX(0)) {
	  p->lstate = EXPR_BEG;
	  nextc(p);
	  tokfix(p);
	  yylval.id = intern_cstr(tok(p));
	  return tLABEL;
	}
      }
      if (p->lstate != EXPR_DOT) {
	const struct kwtable *kw;

	/* See if it is a reserved word.  */
	kw = mrb_reserved_word(tok(p), toklen(p));
	if (kw) {
	  enum mrb_lex_state_enum state = p->lstate;
	  p->lstate = kw->state;
	  if (state == EXPR_FNAME) {
	    yylval.id = intern_cstr(kw->name);
	    return kw->id[0];
	  }
	  if (p->lstate == EXPR_BEG) {
	    p->cmd_start = TRUE;
	  }
	  if (kw->id[0] == keyword_do) {
	    if (p->lpar_beg && p->lpar_beg == p->paren_nest) {
	      p->lpar_beg = 0;
	      p->paren_nest--;
	      return keyword_do_LAMBDA;
	    }
	    if (COND_P()) return keyword_do_cond;
	    if (CMDARG_P() && state != EXPR_CMDARG)
	      return keyword_do_block;
	    if (state == EXPR_ENDARG || state == EXPR_BEG)
	      return keyword_do_block;
	    return keyword_do;
	  }
	  if (state == EXPR_BEG || state == EXPR_VALUE)
	    return kw->id[0];
	  else {
	    if (kw->id[0] != kw->id[1])
	      p->lstate = EXPR_BEG;
	    return kw->id[1];
	  }
	}
      }

      if (IS_BEG() || p->lstate == EXPR_DOT || IS_ARG()) {
	if (cmd_state) {
	  p->lstate = EXPR_CMDARG;
	}
	else {
	  p->lstate = EXPR_ARG;
	}
      }
      else if (p->lstate == EXPR_FNAME) {
	p->lstate = EXPR_ENDFN;
      }
      else {
	p->lstate = EXPR_END;
      }
    }
    {
      mrb_sym ident = intern_cstr(tok(p));

      yylval.id = ident;
#if 0
      if (last_state != EXPR_DOT && islower(tok(p)[0]) && lvar_defined(ident)) {
	p->lstate = EXPR_END;
      }
#endif
    }
    return result;
  }
}

static int
yylex(void *lval, parser_state *p)
{
  int t;

  p->ylval = lval;
  t = parser_yylex(p);

  return t;
}

static void
parser_init_cxt(parser_state *p, mrbc_context *cxt)
{
  if (!cxt) return;
  if (cxt->lineno) p->lineno = cxt->lineno;
  if (cxt->filename) mrb_parser_set_filename(p, cxt->filename);
  if (cxt->syms) {
    int i;

    p->locals = cons(0,0);
    for (i=0; i<cxt->slen; i++) {
      local_add_f(p, cxt->syms[i]);
    }
  }
  p->capture_errors = cxt->capture_errors;
  if (cxt->partial_hook) {
    p->cxt = cxt;
  }
}

static void
parser_update_cxt(parser_state *p, mrbc_context *cxt)
{
  node *n, *n0;
  int i = 0;

  if (!cxt) return;
  if ((int)(intptr_t)p->tree->car != NODE_SCOPE) return;
  n0 = n = p->tree->cdr->car;
  while (n) {
    i++;
    n = n->cdr;
  }
  cxt->syms = (mrb_sym *)mrb_realloc(p->mrb, cxt->syms, i*sizeof(mrb_sym));
  cxt->slen = i;
  for (i=0, n=n0; n; i++,n=n->cdr) {
    cxt->syms[i] = sym(n->car);
  }
}

void codedump_all(mrb_state*, struct RProc*);
void parser_dump(mrb_state *mrb, node *tree, int offset);

void
mrb_parser_parse(parser_state *p, mrbc_context *c)
{
  if (setjmp(p->jmp) != 0) {
    yyerror(p, "memory allocation error");
    p->nerr++;
    p->tree = 0;
    return;
  }

  p->cmd_start = TRUE;
  p->in_def = p->in_single = FALSE;
  p->nerr = p->nwarn = 0;
  p->lex_strterm = NULL;

  parser_init_cxt(p, c);
  yyparse(p);
  if (!p->tree) {
    p->tree = new_nil(p);
  }
  parser_update_cxt(p, c);
  if (c && c->dump_result) {
    parser_dump(p->mrb, p->tree, 0);
  }
}

parser_state*
mrb_parser_new(mrb_state *mrb)
{
  mrb_pool *pool;
  parser_state *p;
  static const parser_state parser_state_zero = { 0 };

  pool = mrb_pool_open(mrb);
  if (!pool) return 0;
  p = (parser_state *)mrb_pool_alloc(pool, sizeof(parser_state));
  if (!p) return 0;

  *p = parser_state_zero;
  p->mrb = mrb;
  p->pool = pool;
  p->in_def = p->in_single = 0;

  p->s = p->send = NULL;
#ifdef ENABLE_STDIO
  p->f = NULL;
#endif

  p->cmd_start = TRUE;
  p->in_def = p->in_single = FALSE;

  p->capture_errors = 0;
  p->lineno = 1;
  p->column = 0;
#if defined(PARSER_TEST) || defined(PARSER_DEBUG)
  yydebug = 1;
#endif

  p->lex_strterm = NULL;
  p->all_heredocs = p->parsing_heredoc = NULL;
  p->lex_strterm_before_heredoc = NULL;

  p->current_filename_index = -1;
  p->filename_table = NULL;
  p->filename_table_length = 0;

  return p;
}

void
mrb_parser_free(parser_state *p) {
  mrb_pool_close(p->pool);
}

mrbc_context*
mrbc_context_new(mrb_state *mrb)
{
  mrbc_context *c;

  c = (mrbc_context *)mrb_calloc(mrb, 1, sizeof(mrbc_context));
  return c;
}

void
mrbc_context_free(mrb_state *mrb, mrbc_context *cxt)
{
  mrb_free(mrb, cxt->syms);
  mrb_free(mrb, cxt);
}

const char*
mrbc_filename(mrb_state *mrb, mrbc_context *c, const char *s)
{
  if (s) {
    int len = strlen(s);
    char *p = (char *)mrb_alloca(mrb, len + 1);

    memcpy(p, s, len + 1);
    c->filename = p;
  }
  return c->filename;
}

void
mrbc_partial_hook(mrb_state *mrb, mrbc_context *c, int (*func)(struct mrb_parser_state*), void *data)
{
  c->partial_hook = func;
  c->partial_data = data;
}

void
mrb_parser_set_filename(struct mrb_parser_state *p, const char *f)
{
  mrb_sym sym;
  size_t len;
  size_t i;
  mrb_sym* new_table;

  sym = mrb_intern_cstr(p->mrb, f);
  p->filename = mrb_sym2name_len(p->mrb, sym, &len);
  p->lineno = (p->filename_table_length > 0)? 0 : 1;
  
  for(i = 0; i < p->filename_table_length; ++i) {
    if(p->filename_table[i] == sym) {
      p->current_filename_index = i;
      return;
    }
  }

  p->current_filename_index = p->filename_table_length++;

  new_table = parser_palloc(p, sizeof(mrb_sym) * p->filename_table_length);
  if (p->filename_table) {
    memcpy(new_table, p->filename_table, sizeof(mrb_sym) * p->filename_table_length);
  }
  p->filename_table = new_table;
  p->filename_table[p->filename_table_length - 1] = sym;
}

char const* mrb_parser_get_filename(struct mrb_parser_state* p, uint16_t idx) {
  if (idx >= p->filename_table_length) { return NULL; }
  else {
    size_t len;
    return mrb_sym2name_len(p->mrb, p->filename_table[idx], &len);
  }
}

#ifdef ENABLE_STDIO
parser_state*
mrb_parse_file(mrb_state *mrb, FILE *f, mrbc_context *c)
{
  parser_state *p;

  p = mrb_parser_new(mrb);
  if (!p) return 0;
  p->s = p->send = NULL;
  p->f = f;

  mrb_parser_parse(p, c);
  return p;
}
#endif

parser_state*
mrb_parse_nstring(mrb_state *mrb, const char *s, int len, mrbc_context *c)
{
  parser_state *p;

  p = mrb_parser_new(mrb);
  if (!p) return 0;
  p->s = s;
  p->send = s + len;

  mrb_parser_parse(p, c);
  return p;
}

parser_state*
mrb_parse_string(mrb_state *mrb, const char *s, mrbc_context *c)
{
  return mrb_parse_nstring(mrb, s, strlen(s), c);
}

static mrb_value
load_exec(mrb_state *mrb, parser_state *p, mrbc_context *c)
{
  struct RClass *target = mrb->object_class;
  struct RProc *proc;
  mrb_value v;

  if (!p) {
    return mrb_undef_value();
  }
  if (!p->tree || p->nerr) {
    if (p->capture_errors) {
      char buf[256];
      int n;

      n = snprintf(buf, sizeof(buf), "line %d: %s\n",
      p->error_buffer[0].lineno, p->error_buffer[0].message);
      mrb->exc = mrb_obj_ptr(mrb_exc_new(mrb, E_SYNTAX_ERROR, buf, n));
      mrb_parser_free(p);
      return mrb_undef_value();
    }
    else {
      static const char msg[] = "syntax error";
      mrb->exc = mrb_obj_ptr(mrb_exc_new(mrb, E_SYNTAX_ERROR, msg, sizeof(msg) - 1));
      mrb_parser_free(p);
      return mrb_undef_value();
    }
  }
  proc = mrb_generate_code(mrb, p);
  mrb_parser_free(p);
  if (proc == NULL) {
    static const char msg[] = "codegen error";
    mrb->exc = mrb_obj_ptr(mrb_exc_new(mrb, E_SCRIPT_ERROR, msg, sizeof(msg) - 1));
    return mrb_undef_value();
  }
  if (c) {
    if (c->dump_result) codedump_all(mrb, proc);
    if (c->no_exec) return mrb_obj_value(proc);
    if (c->target_class) {
      target = c->target_class;
    }
  }
  proc->target_class = target;
  if (mrb->c->ci) {
    mrb->c->ci->target_class = target;
  }
  v = mrb_context_run(mrb, proc, mrb_top_self(mrb), 0);
  if (mrb->exc) return mrb_nil_value();
  return v;
}

#ifdef ENABLE_STDIO
mrb_value
mrb_load_file_cxt(mrb_state *mrb, FILE *f, mrbc_context *c)
{
  return load_exec(mrb, mrb_parse_file(mrb, f, c), c);
}

mrb_value
mrb_load_file(mrb_state *mrb, FILE *f)
{
  return mrb_load_file_cxt(mrb, f, NULL);
}
#endif

mrb_value
mrb_load_nstring_cxt(mrb_state *mrb, const char *s, int len, mrbc_context *c)
{
  return load_exec(mrb, mrb_parse_nstring(mrb, s, len, c), c);
}

mrb_value
mrb_load_nstring(mrb_state *mrb, const char *s, int len)
{
  return mrb_load_nstring_cxt(mrb, s, len, NULL);
}

mrb_value
mrb_load_string_cxt(mrb_state *mrb, const char *s, mrbc_context *c)
{
  return mrb_load_nstring_cxt(mrb, s, strlen(s), c);
}

mrb_value
mrb_load_string(mrb_state *mrb, const char *s)
{
  return mrb_load_string_cxt(mrb, s, NULL);
}

#ifdef ENABLE_STDIO

static void
dump_prefix(int offset)
{
  while (offset--) {
    putc(' ', stdout);
    putc(' ', stdout);
  }
}

static void
dump_recur(mrb_state *mrb, node *tree, int offset)
{
  while (tree) {
    parser_dump(mrb, tree->car, offset);
    tree = tree->cdr;
  }
}

#endif

void
parser_dump(mrb_state *mrb, node *tree, int offset)
{
#ifdef ENABLE_STDIO
  int n;

  if (!tree) return;
 again:
  dump_prefix(offset);
  n = (int)(intptr_t)tree->car;
  tree = tree->cdr;
  switch (n) {
  case NODE_BEGIN:
    printf("NODE_BEGIN:\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_RESCUE:
    printf("NODE_RESCUE:\n");
    if (tree->car) {
      dump_prefix(offset+1);
      printf("body:\n");
      parser_dump(mrb, tree->car, offset+2);
    }
    tree = tree->cdr;
    if (tree->car) {
      node *n2 = tree->car;

      dump_prefix(offset+1);
      printf("rescue:\n");
      while (n2) {
	node *n3 = n2->car;
	if (n3->car) {
	  dump_prefix(offset+2);
	  printf("handle classes:\n");
	  dump_recur(mrb, n3->car, offset+3);
	}
	if (n3->cdr->car) {
	  dump_prefix(offset+2);
	  printf("exc_var:\n");
	  parser_dump(mrb, n3->cdr->car, offset+3);
	}
	if (n3->cdr->cdr->car) {
	  dump_prefix(offset+2);
	  printf("rescue body:\n");
	  parser_dump(mrb, n3->cdr->cdr->car, offset+3);
	}
	n2 = n2->cdr;
      }
    }
    tree = tree->cdr;
    if (tree->car) {
      dump_prefix(offset+1);
      printf("else:\n");
      parser_dump(mrb, tree->car, offset+2);
    }
    break;

  case NODE_ENSURE:
    printf("NODE_ENSURE:\n");
    dump_prefix(offset+1);
    printf("body:\n");
    parser_dump(mrb, tree->car, offset+2);
    dump_prefix(offset+1);
    printf("ensure:\n");
    parser_dump(mrb, tree->cdr->cdr, offset+2);
    break;

  case NODE_LAMBDA:
    printf("NODE_BLOCK:\n");
    goto block;

  case NODE_BLOCK:
  block:
    printf("NODE_BLOCK:\n");
    tree = tree->cdr;
    if (tree->car) {
      node *n = tree->car;

      if (n->car) {
	dump_prefix(offset+1);
	printf("mandatory args:\n");
	dump_recur(mrb, n->car, offset+2);
      }
      n = n->cdr;
      if (n->car) {
	dump_prefix(offset+1);
	printf("optional args:\n");
	{
	  node *n2 = n->car;

	  while (n2) {
	    dump_prefix(offset+2);
	    printf("%s=", mrb_sym2name(mrb, sym(n2->car->car)));
	    parser_dump(mrb, n2->car->cdr, 0);
	    n2 = n2->cdr;
	  }
	}
      }
      n = n->cdr;
      if (n->car) {
	dump_prefix(offset+1);
	printf("rest=*%s\n", mrb_sym2name(mrb, sym(n->car)));
      }
      n = n->cdr;
      if (n->car) {
	dump_prefix(offset+1);
	printf("post mandatory args:\n");
	dump_recur(mrb, n->car, offset+2);
      }
      n = n->cdr;
      if (n) {
	dump_prefix(offset+1);
	printf("blk=&%s\n", mrb_sym2name(mrb, sym(n)));
      }
    }
    dump_prefix(offset+1);
    printf("body:\n");
    parser_dump(mrb, tree->cdr->car, offset+2);
    break;

  case NODE_IF:
    printf("NODE_IF:\n");
    dump_prefix(offset+1);
    printf("cond:\n");
    parser_dump(mrb, tree->car, offset+2);
    dump_prefix(offset+1);
    printf("then:\n");
    parser_dump(mrb, tree->cdr->car, offset+2);
    if (tree->cdr->cdr->car) {
      dump_prefix(offset+1);
      printf("else:\n");
      parser_dump(mrb, tree->cdr->cdr->car, offset+2);
    }
    break;

  case NODE_AND:
    printf("NODE_AND:\n");
    parser_dump(mrb, tree->car, offset+1);
    parser_dump(mrb, tree->cdr, offset+1);
    break;

  case NODE_OR:
    printf("NODE_OR:\n");
    parser_dump(mrb, tree->car, offset+1);
    parser_dump(mrb, tree->cdr, offset+1);
    break;

  case NODE_CASE:
    printf("NODE_CASE:\n");
    if (tree->car) {
      parser_dump(mrb, tree->car, offset+1);
    }
    tree = tree->cdr;
    while (tree) {
      dump_prefix(offset+1);
      printf("case:\n");
      dump_recur(mrb, tree->car->car, offset+2);
      dump_prefix(offset+1);
      printf("body:\n");
      parser_dump(mrb, tree->car->cdr, offset+2);
      tree = tree->cdr;
    }
    break;

  case NODE_WHILE:
    printf("NODE_WHILE:\n");
    dump_prefix(offset+1);
    printf("cond:\n");
    parser_dump(mrb, tree->car, offset+2);
    dump_prefix(offset+1);
    printf("body:\n");
    parser_dump(mrb, tree->cdr, offset+2);
    break;

  case NODE_UNTIL:
    printf("NODE_UNTIL:\n");
    dump_prefix(offset+1);
    printf("cond:\n");
    parser_dump(mrb, tree->car, offset+2);
    dump_prefix(offset+1);
    printf("body:\n");
    parser_dump(mrb, tree->cdr, offset+2);
    break;

  case NODE_FOR:
    printf("NODE_FOR:\n");
    dump_prefix(offset+1);
    printf("var:\n");
    {
      node *n2 = tree->car;

      if (n2->car) {
	dump_prefix(offset+2);
	printf("pre:\n");
	dump_recur(mrb, n2->car, offset+3);
      }
      n2 = n2->cdr;
      if (n2) {
	if (n2->car) {
	  dump_prefix(offset+2);
	  printf("rest:\n");
	  parser_dump(mrb, n2->car, offset+3);
	}
	n2 = n2->cdr;
	if (n2) {
	  if (n2->car) {
	    dump_prefix(offset+2);
	    printf("post:\n");
	    dump_recur(mrb, n2->car, offset+3);
	  }
	}
      }
    }
    tree = tree->cdr;
    dump_prefix(offset+1);
    printf("in:\n");
    parser_dump(mrb, tree->car, offset+2);
    tree = tree->cdr;
    dump_prefix(offset+1);
    printf("do:\n");
    parser_dump(mrb, tree->car, offset+2);
    break;

  case NODE_SCOPE:
    printf("NODE_SCOPE:\n");
    {
      node *n2 = tree->car;

      if (n2  && (n2->car || n2->cdr)) {
	dump_prefix(offset+1);
	printf("local variables:\n");
	dump_prefix(offset+2);
	while (n2) {
	  if (n2->car) {
	    if (n2 != tree->car) printf(", ");
	    printf("%s", mrb_sym2name(mrb, sym(n2->car)));
	  }
	  n2 = n2->cdr;
	}
	printf("\n");
      }
    }
    tree = tree->cdr;
    offset++;
    goto again;

  case NODE_FCALL:
  case NODE_CALL:
    printf("NODE_CALL:\n");
    parser_dump(mrb, tree->car, offset+1);
    dump_prefix(offset+1);
    printf("method='%s' (%d)\n",
    mrb_sym2name(mrb, sym(tree->cdr->car)),
    (int)(intptr_t)tree->cdr->car);
    tree = tree->cdr->cdr->car;
    if (tree) {
      dump_prefix(offset+1);
      printf("args:\n");
      dump_recur(mrb, tree->car, offset+2);
      if (tree->cdr) {
	dump_prefix(offset+1);
	printf("block:\n");
	parser_dump(mrb, tree->cdr, offset+2);
      }
    }
    break;

  case NODE_DOT2:
    printf("NODE_DOT2:\n");
    parser_dump(mrb, tree->car, offset+1);
    parser_dump(mrb, tree->cdr, offset+1);
    break;

  case NODE_DOT3:
    printf("NODE_DOT3:\n");
    parser_dump(mrb, tree->car, offset+1);
    parser_dump(mrb, tree->cdr, offset+1);
    break;

  case NODE_COLON2:
    printf("NODE_COLON2:\n");
    parser_dump(mrb, tree->car, offset+1);
    dump_prefix(offset+1);
    printf("::%s\n", mrb_sym2name(mrb, sym(tree->cdr)));
    break;

  case NODE_COLON3:
    printf("NODE_COLON3:\n");
    dump_prefix(offset+1);
    printf("::%s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_ARRAY:
    printf("NODE_ARRAY:\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_HASH:
    printf("NODE_HASH:\n");
    while (tree) {
      dump_prefix(offset+1);
      printf("key:\n");
      parser_dump(mrb, tree->car->car, offset+2);
      dump_prefix(offset+1);
      printf("value:\n");
      parser_dump(mrb, tree->car->cdr, offset+2);
      tree = tree->cdr;
    }
    break;

  case NODE_SPLAT:
    printf("NODE_SPLAT:\n");
    parser_dump(mrb, tree, offset+1);
    break;

  case NODE_ASGN:
    printf("NODE_ASGN:\n");
    dump_prefix(offset+1);
    printf("lhs:\n");
    parser_dump(mrb, tree->car, offset+2);
    dump_prefix(offset+1);
    printf("rhs:\n");
    parser_dump(mrb, tree->cdr, offset+2);
    break;

  case NODE_MASGN:
    printf("NODE_MASGN:\n");
    dump_prefix(offset+1);
    printf("mlhs:\n");
    {
      node *n2 = tree->car;

      if (n2->car) {
	dump_prefix(offset+2);
	printf("pre:\n");
	dump_recur(mrb, n2->car, offset+3);
      }
      n2 = n2->cdr;
      if (n2) {
	if (n2->car) {
	  dump_prefix(offset+2);
	  printf("rest:\n");
	  if (n2->car == (node*)-1) {
	    dump_prefix(offset+2);
	    printf("(empty)\n");
	  }
	  else {
	    parser_dump(mrb, n2->car, offset+3);
	  }
	}
	n2 = n2->cdr;
	if (n2) {
	  if (n2->car) {
	    dump_prefix(offset+2);
	    printf("post:\n");
	    dump_recur(mrb, n2->car, offset+3);
	  }
	}
      }
    }
    dump_prefix(offset+1);
    printf("rhs:\n");
    parser_dump(mrb, tree->cdr, offset+2);
    break;

  case NODE_OP_ASGN:
    printf("NODE_OP_ASGN:\n");
    dump_prefix(offset+1);
    printf("lhs:\n");
    parser_dump(mrb, tree->car, offset+2);
    tree = tree->cdr;
    dump_prefix(offset+1);
    printf("op='%s' (%d)\n", mrb_sym2name(mrb, sym(tree->car)), (int)(intptr_t)tree->car);
    tree = tree->cdr;
    parser_dump(mrb, tree->car, offset+1);
    break;

  case NODE_SUPER:
    printf("NODE_SUPER:\n");
    if (tree) {
      dump_prefix(offset+1);
      printf("args:\n");
      dump_recur(mrb, tree->car, offset+2);
      if (tree->cdr) {
	dump_prefix(offset+1);
	printf("block:\n");
	parser_dump(mrb, tree->cdr, offset+2);
      }
    }
    break;

  case NODE_ZSUPER:
    printf("NODE_ZSUPER\n");
    break;

  case NODE_RETURN:
    printf("NODE_RETURN:\n");
    parser_dump(mrb, tree, offset+1);
    break;

  case NODE_YIELD:
    printf("NODE_YIELD:\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_BREAK:
    printf("NODE_BREAK:\n");
    parser_dump(mrb, tree, offset+1);
    break;

  case NODE_NEXT:
    printf("NODE_NEXT:\n");
    parser_dump(mrb, tree, offset+1);
    break;

  case NODE_REDO:
    printf("NODE_REDO\n");
    break;

  case NODE_RETRY:
    printf("NODE_RETRY\n");
    break;

  case NODE_LVAR:
    printf("NODE_LVAR %s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_GVAR:
    printf("NODE_GVAR %s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_IVAR:
    printf("NODE_IVAR %s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_CVAR:
    printf("NODE_CVAR %s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_CONST:
    printf("NODE_CONST %s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_MATCH:
    printf("NODE_MATCH:\n");
    dump_prefix(offset + 1);
    printf("lhs:\n");
    parser_dump(mrb, tree->car, offset + 2);
    dump_prefix(offset + 1);
    printf("rhs:\n");
    parser_dump(mrb, tree->cdr, offset + 2);
    break;

  case NODE_BACK_REF:
    printf("NODE_BACK_REF: $%c\n", (int)(intptr_t)tree);
    break;

  case NODE_NTH_REF:
    printf("NODE_NTH_REF: $%d\n", (int)(intptr_t)tree);
    break;

  case NODE_ARG:
    printf("NODE_ARG %s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_BLOCK_ARG:
    printf("NODE_BLOCK_ARG:\n");
    parser_dump(mrb, tree, offset+1);
    break;

  case NODE_INT:
    printf("NODE_INT %s base %d\n", (char*)tree->car, (int)(intptr_t)tree->cdr->car);
    break;

  case NODE_FLOAT:
    printf("NODE_FLOAT %s\n", (char*)tree);
    break;

  case NODE_NEGATE:
    printf("NODE_NEGATE\n");
    parser_dump(mrb, tree, offset+1);
    break;

  case NODE_STR:
    printf("NODE_STR \"%s\" len %d\n", (char*)tree->car, (int)(intptr_t)tree->cdr);
    break;

  case NODE_DSTR:
    printf("NODE_DSTR\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_XSTR:
    printf("NODE_XSTR \"%s\" len %d\n", (char*)tree->car, (int)(intptr_t)tree->cdr);
    break;

  case NODE_DXSTR:
    printf("NODE_DXSTR\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_REGX:
    printf("NODE_REGX /%s/%s\n", (char*)tree->car, (char*)tree->cdr);
    break;

  case NODE_DREGX:
    printf("NODE_DREGX\n");
    dump_recur(mrb, tree->car, offset+1);
    dump_prefix(offset);
    printf("tail: %s\n", (char*)tree->cdr->cdr->car);
    dump_prefix(offset);
    printf("opt: %s\n", (char*)tree->cdr->cdr->cdr);
    break;

  case NODE_SYM:
    printf("NODE_SYM :%s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_SELF:
    printf("NODE_SELF\n");
    break;

  case NODE_NIL:
    printf("NODE_NIL\n");
    break;

  case NODE_TRUE:
    printf("NODE_TRUE\n");
    break;

  case NODE_FALSE:
    printf("NODE_FALSE\n");
    break;

  case NODE_ALIAS:
    printf("NODE_ALIAS %s %s:\n",
	    mrb_sym2name(mrb, sym(tree->car)),
	    mrb_sym2name(mrb, sym(tree->cdr)));
    break;

  case NODE_UNDEF:
    printf("NODE_UNDEF");
    {
      node *t = tree;
      while (t) {
	printf(" %s", mrb_sym2name(mrb, sym(t->car)));
	t = t->cdr;
      }
    }
    printf(":\n");
    break;

  case NODE_CLASS:
    printf("NODE_CLASS:\n");
    if (tree->car->car == (node*)0) {
      dump_prefix(offset+1);
      printf(":%s\n", mrb_sym2name(mrb, sym(tree->car->cdr)));
    }
    else if (tree->car->car == (node*)1) {
      dump_prefix(offset+1);
      printf("::%s\n", mrb_sym2name(mrb, sym(tree->car->cdr)));
    }
    else {
      parser_dump(mrb, tree->car->car, offset+1);
      dump_prefix(offset+1);
      printf("::%s\n", mrb_sym2name(mrb, sym(tree->car->cdr)));
    }
    if (tree->cdr->car) {
      dump_prefix(offset+1);
      printf("super:\n");
      parser_dump(mrb, tree->cdr->car, offset+2);
    }
    dump_prefix(offset+1);
    printf("body:\n");
    parser_dump(mrb, tree->cdr->cdr->car->cdr, offset+2);
    break;

  case NODE_MODULE:
    printf("NODE_MODULE:\n");
    if (tree->car->car == (node*)0) {
      dump_prefix(offset+1);
      printf(":%s\n", mrb_sym2name(mrb, sym(tree->car->cdr)));
    }
    else if (tree->car->car == (node*)1) {
      dump_prefix(offset+1);
      printf("::%s\n", mrb_sym2name(mrb, sym(tree->car->cdr)));
    }
    else {
      parser_dump(mrb, tree->car->car, offset+1);
      dump_prefix(offset+1);
      printf("::%s\n", mrb_sym2name(mrb, sym(tree->car->cdr)));
    }
    dump_prefix(offset+1);
    printf("body:\n");
    parser_dump(mrb, tree->cdr->car->cdr, offset+2);
    break;

  case NODE_SCLASS:
    printf("NODE_SCLASS:\n");
    parser_dump(mrb, tree->car, offset+1);
    dump_prefix(offset+1);
    printf("body:\n");
    parser_dump(mrb, tree->cdr->car->cdr, offset+2);
    break;

  case NODE_DEF:
    printf("NODE_DEF:\n");
    dump_prefix(offset+1);
    printf("%s\n", mrb_sym2name(mrb, sym(tree->car)));
    tree = tree->cdr;
    {
      node *n2 = tree->car;

      if (n2 && (n2->car || n2->cdr)) {
	dump_prefix(offset+1);
	printf("local variables:\n");
	dump_prefix(offset+2);
	while (n2) {
	  if (n2->car) {
	    if (n2 != tree->car) printf(", ");
	    printf("%s", mrb_sym2name(mrb, sym(n2->car)));
	  }
	  n2 = n2->cdr;
	}
	printf("\n");
      }
    }
    tree = tree->cdr;
    if (tree->car) {
      node *n = tree->car;

      if (n->car) {
	dump_prefix(offset+1);
	printf("mandatory args:\n");
	dump_recur(mrb, n->car, offset+2);
      }
      n = n->cdr;
      if (n->car) {
	dump_prefix(offset+1);
	printf("optional args:\n");
	{
	  node *n2 = n->car;

	  while (n2) {
	    dump_prefix(offset+2);
	    printf("%s=", mrb_sym2name(mrb, sym(n2->car->car)));
	    parser_dump(mrb, n2->car->cdr, 0);
	    n2 = n2->cdr;
	  }
	}
      }
      n = n->cdr;
      if (n->car) {
	dump_prefix(offset+1);
	printf("rest=*%s\n", mrb_sym2name(mrb, sym(n->car)));
      }
      n = n->cdr;
      if (n->car) {
	dump_prefix(offset+1);
	printf("post mandatory args:\n");
	dump_recur(mrb, n->car, offset+2);
      }
      n = n->cdr;
      if (n) {
	dump_prefix(offset+1);
	printf("blk=&%s\n", mrb_sym2name(mrb, sym(n)));
      }
    }
    parser_dump(mrb, tree->cdr->car, offset+1);
    break;

  case NODE_SDEF:
    printf("NODE_SDEF:\n");
    parser_dump(mrb, tree->car, offset+1);
    tree = tree->cdr;
    dump_prefix(offset+1);
    printf(":%s\n", mrb_sym2name(mrb, sym(tree->car)));
    tree = tree->cdr->cdr;
    if (tree->car) {
      node *n = tree->car;

      if (n->car) {
	dump_prefix(offset+1);
	printf("mandatory args:\n");
	dump_recur(mrb, n->car, offset+2);
      }
      n = n->cdr;
      if (n->car) {
	dump_prefix(offset+1);
	printf("optional args:\n");
	{
	  node *n2 = n->car;

	  while (n2) {
	    dump_prefix(offset+2);
	    printf("%s=", mrb_sym2name(mrb, sym(n2->car->car)));
	    parser_dump(mrb, n2->car->cdr, 0);
	    n2 = n2->cdr;
	  }
	}
      }
      n = n->cdr;
      if (n->car) {
	dump_prefix(offset+1);
	printf("rest=*%s\n", mrb_sym2name(mrb, sym(n->car)));
      }
      n = n->cdr;
      if (n->car) {
	dump_prefix(offset+1);
	printf("post mandatory args:\n");
	dump_recur(mrb, n->car, offset+2);
      }
      n = n->cdr;
      if (n) {
	dump_prefix(offset+1);
	printf("blk=&%s\n", mrb_sym2name(mrb, sym(n)));
      }
    }
    tree = tree->cdr;
    parser_dump(mrb, tree->car, offset+1);
    break;

  case NODE_POSTEXE:
    printf("NODE_POSTEXE:\n");
    parser_dump(mrb, tree, offset+1);
    break;

  case NODE_HEREDOC:
    printf("NODE_HEREDOC:\n");
    parser_dump(mrb, ((parser_heredoc_info*)tree)->doc, offset+1);
    break;

  default:
    printf("node type: %d (0x%x)\n", (int)n, (int)n);
    break;
  }
#endif
}

