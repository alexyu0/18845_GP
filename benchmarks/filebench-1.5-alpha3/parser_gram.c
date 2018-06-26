/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 30 "parser_gram.y"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <locale.h>
#include <sys/utsname.h>
#include <sys/statvfs.h>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "parsertypes.h"
#include "filebench.h"
#include "utils.h"
#include "stats.h"
#include "vars.h"
#include "eventgen.h"
#include "aslr.h"
#include "multi_client_sync.h"

/* yacc and lex externals */
extern FILE *yyin;
extern int yydebug;
extern void yyerror(char *s);
extern int yylex(void);

/* executable name to execute worker processes later */
char *execname;

/* utilities */
static cmd_t *alloc_cmd(void);
static attr_t *alloc_attr(void);
static attr_t *alloc_lvar_attr(var_t *var);
static attr_t *get_attr(cmd_t *cmd, int64_t name);
static void get_attr_lvars(cmd_t *cmd, flowop_t *flowop);
static list_t *alloc_list();
static probtabent_t *alloc_probtabent(void);
static void add_lvar_to_list(var_t *newlvar, var_t **lvar_list);

/* Info Commands */
static void parser_fileset_list(cmd_t *);
static void parser_flowop_list(cmd_t *);

/* Define Commands */
static void parser_proc_define(cmd_t *);
static void parser_thread_define(cmd_t *, procflow_t *);
static void parser_flowop_define(cmd_t *, threadflow_t *, flowop_t **, int);
static void parser_composite_flowop_define(cmd_t *);
static void parser_file_define(cmd_t *);
static void parser_fileset_define(cmd_t *);
static void parser_var_assign_random(char *, cmd_t *);
static void parser_var_assign_custom(char *, cmd_t *);

/* Create Commands */
static void parser_fileset_create(cmd_t *);

/* Run Commands */
static void parser_run(cmd_t *cmd);
static void parser_run_variable(cmd_t *cmd);
static void parser_psrun(cmd_t *cmd);

/* Shutdown (Quit) Commands */
static void parser_filebench_shutdown(cmd_t *cmd);

/* Other Commands */
static void parser_echo(cmd_t *cmd);
static void parser_system(cmd_t *cmd);
static void parser_eventgen(cmd_t *cmd);
static void parser_enable_mc(cmd_t *cmd);
static void parser_domultisync(cmd_t *cmd);
static void parser_sleep(cmd_t *cmd);
static void parser_sleep_variable(cmd_t *cmd);
static void parser_version(cmd_t *cmd);
static void parser_enable_lathist(cmd_t *cmd);

#line 114 "parser_gram.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	int64_t		 ival;
	unsigned char	 bval;
	char *		 sval;
	avd_t		 avd;
	cmd_t		*cmd;
	attr_t		*attr;
	list_t		*list;
	probtabent_t	*rndtb;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 122 "parser_gram.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define FSC_LIST 257
#define FSC_DEFINE 258
#define FSC_QUIT 259
#define FSC_DEBUG 260
#define FSC_CREATE 261
#define FSC_SLEEP 262
#define FSC_SET 263
#define FSC_SYSTEM 264
#define FSC_EVENTGEN 265
#define FSC_ECHO 266
#define FSC_RUN 267
#define FSC_PSRUN 268
#define FSC_VERSION 269
#define FSC_ENABLE 270
#define FSC_DOMULTISYNC 271
#define FSV_STRING 272
#define FSV_VAL_POSINT 273
#define FSV_VAL_NEGINT 274
#define FSV_VAL_BOOLEAN 275
#define FSV_VARIABLE 276
#define FSV_WHITESTRING 277
#define FSV_RANDUNI 278
#define FSV_RANDTAB 279
#define FSV_URAND 280
#define FSV_RAND48 281
#define FSE_FILE 282
#define FSE_FILES 283
#define FSE_FILESET 284
#define FSE_PROC 285
#define FSE_THREAD 286
#define FSE_FLOWOP 287
#define FSE_CVAR 288
#define FSE_RAND 289
#define FSE_MODE 290
#define FSE_MULTI 291
#define FSK_SEPLST 292
#define FSK_OPENLST 293
#define FSK_CLOSELST 294
#define FSK_OPENPAR 295
#define FSK_CLOSEPAR 296
#define FSK_ASSIGN 297
#define FSK_IN 298
#define FSK_QUOTE 299
#define FSA_SIZE 300
#define FSA_PREALLOC 301
#define FSA_PARALLOC 302
#define FSA_PATH 303
#define FSA_REUSE 304
#define FSA_MEMSIZE 305
#define FSA_RATE 306
#define FSA_READONLY 307
#define FSA_TRUSTTREE 308
#define FSA_IOSIZE 309
#define FSA_FILENAME 310
#define FSA_WSS 311
#define FSA_NAME 312
#define FSA_RANDOM 313
#define FSA_INSTANCES 314
#define FSA_DSYNC 315
#define FSA_TARGET 316
#define FSA_ITERS 317
#define FSA_NICE 318
#define FSA_VALUE 319
#define FSA_BLOCKING 320
#define FSA_HIGHWATER 321
#define FSA_DIRECTIO 322
#define FSA_DIRWIDTH 323
#define FSA_FD 324
#define FSA_SRCFD 325
#define FSA_ROTATEFD 326
#define FSA_ENTRIES 327
#define FSA_DIRDEPTHRV 328
#define FSA_DIRGAMMA 329
#define FSA_USEISM 330
#define FSA_TYPE 331
#define FSA_LEAFDIRS 332
#define FSA_INDEXED 333
#define FSA_RANDTABLE 334
#define FSA_RANDSRC 335
#define FSA_ROUND 336
#define FSA_RANDSEED 337
#define FSA_RANDGAMMA 338
#define FSA_RANDMEAN 339
#define FSA_MIN 340
#define FSA_MAX 341
#define FSA_MASTER 342
#define FSA_CLIENT 343
#define FSS_TYPE 344
#define FSS_SEED 345
#define FSS_GAMMA 346
#define FSS_MEAN 347
#define FSS_MIN 348
#define FSS_SRC 349
#define FSS_ROUND 350
#define FSA_LVAR_ASSIGN 351
#define FSA_ALLDONE 352
#define FSA_FIRSTDONE 353
#define FSA_TIMEOUT 354
#define FSA_LATHIST 355
#define FSA_NOREADAHEAD 356
#define FSA_IOPRIO 357
#define FSA_WRITEONLY 358
#define FSA_PARAMETERS 359
#define FSA_NOUSESTATS 360
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    0,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
   15,   15,   13,   20,   21,   22,   22,   23,   53,   53,
   54,   54,   54,   54,   54,   54,    4,    4,    9,   12,
   12,   12,   12,   24,   24,   24,   24,   25,   26,   27,
   27,   27,   27,   16,   17,   17,   19,   18,   18,    6,
    7,    7,   10,   11,   11,    3,    3,    3,    5,    5,
    5,    5,    5,   14,   14,    1,   30,   30,   29,   29,
   31,   31,   28,   28,   41,   41,   41,   40,   40,   40,
   40,   68,   67,   67,   34,   34,   32,   32,   35,   35,
   33,   33,   37,   37,   37,   36,   36,   39,   39,   38,
   38,   48,   48,   49,   50,   59,   59,   59,   58,   58,
   58,   58,   58,   58,   58,   58,   58,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   62,   62,   62,   62,   62,   62,   42,   63,   63,
   63,   43,   64,   64,   66,   66,   66,   66,   66,   55,
   55,   55,   55,   55,   56,   56,   56,   56,   56,   56,
   56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
   56,   60,   65,   65,   47,   47,   47,   46,   45,   45,
   45,   45,   45,   45,    8,    8,   51,   51,   52,   61,
   61,   44,   44,   44,   44,   44,   69,   69,
};
static const YYINT yylen[] = {                            2,
    2,    2,    0,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    2,    2,    2,    1,    3,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    2,    1,
    1,    1,    1,    4,    4,    6,    4,    7,    7,    4,
    4,    4,    3,    1,    1,    2,    5,    1,    2,    6,
    3,    3,    2,    2,    2,    2,    2,    1,    1,    2,
    2,    3,    3,    2,    2,    1,    1,    3,    1,    3,
    3,    1,    3,    1,    1,    3,    7,    3,    1,    3,
    3,    7,    1,    3,    1,    3,    3,    1,    1,    3,
    3,    1,    1,    3,    3,    3,    1,    1,    3,    3,
    1,    1,    3,    3,    3,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    3,    3,    3,    3,    3,
    5,    3,    3,    1,    6,    2,    1,    3,    3,    1,
    1,    1,    3,    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         3,
    0,    2,    0,    0,   54,    0,    0,    0,    0,    0,
   21,    0,    0,    0,   25,    0,    0,    1,   12,   11,
   13,    4,    5,    0,    7,    9,   16,   14,   17,    0,
   15,   10,   18,   19,   20,   40,   41,   42,   43,   37,
   38,    0,    0,    0,    0,   39,   63,   64,   65,    0,
    0,    0,    0,    0,    0,   66,   67,    0,    0,    0,
   27,    0,   28,  200,  201,  185,    0,    0,  182,  108,
    0,    0,  121,  122,  123,  120,  124,  126,  125,  119,
  127,    0,   77,    0,  131,  132,  133,  129,  134,  136,
  135,  128,  138,  130,  139,  140,  141,  137,   79,    0,
    0,  116,  117,  118,   95,    0,    0,    0,    0,    0,
   53,   29,   30,   32,   31,   36,   34,   33,   35,   73,
   72,  183,  184,    0,  112,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   47,
   44,   45,    0,    0,    0,   51,   52,   50,    0,    0,
  202,  204,  205,  206,    0,  115,    0,  187,  186,  188,
  109,  110,   78,   81,   80,   83,   96,    0,    0,   58,
   97,    0,    0,    0,    0,    0,    0,  113,  114,    0,
    0,  161,  160,  163,  162,  164,   99,    0,    0,   60,
   59,   76,   74,  180,  166,  165,  167,  168,  172,  175,
  176,  177,  178,  179,  173,  169,  170,  171,  174,  181,
  103,    0,    0,  195,    0,  155,  159,  157,  158,  156,
    0,  197,    0,  142,    0,    0,  147,  143,  144,  145,
  146,   85,    0,    0,   46,  203,  192,  190,  189,  193,
    0,    0,    0,    0,    0,    0,    0,   49,    0,    0,
    0,    0,   48,    0,    0,  100,    0,  101,  104,  105,
  106,  198,  199,  149,  150,  151,   90,  148,  153,  154,
   91,  152,    0,   86,   88,  191,   57,    0,    0,    0,
    0,   93,  207,  208,    0,    0,   87,    0,   94,    0,
    0,    0,   92,
};
static const YYINT yydgoto[] = {                          1,
  193,   18,   19,   20,   21,   22,   23,   24,   25,   26,
   27,   28,   29,  173,   30,   31,  174,  169,  170,   32,
   33,   34,   35,   36,   37,   38,   39,   99,  100,   82,
   83,  105,  187,  106,  188,  211,  212,   70,   71,  232,
  233,  267,  271,  156,  158,   66,   67,  124,  125,   63,
  221,  222,   53,   54,  189,  213,  101,   84,  107,   72,
   68,  234,  268,  272,  126,  223,  281,  282,  285,
};
static const YYINT yysindex[] = {                         0,
  367,    0, -255, -163,    0, -239, -238, -118, -264, -224,
    0, -224, -117, -260,    0, -283, -216,    0,    0,    0,
    0,    0,    0, -258,    0,    0,    0,    0,    0, -214,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -285,  -83, -165, -258,    0,    0,    0,    0, -186,
 -256, -168, -208, -176, -176,    0,    0, -147, -141, -170,
    0, -134,    0,    0,    0,    0, -142, -131,    0,    0,
 -111, -122,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -102,    0,  -88,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -80,
  -81,    0,    0,    0,    0,  -94,  -69,  -91,  -62, -157,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -61,    0,  -67, -237, -251, -237, -214,
 -237, -285, -237,  -83, -237, -165,  -54, -237, -171,    0,
    0,    0,  -60,  -59,  -44,    0,    0,    0, -170, -237,
    0,    0,    0,    0,  -43,    0,  -58,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -281, -266,    0,
    0,  -31,  385, -257, -195, -241,  -57,    0,    0,  -56,
 -105,    0,    0,    0,    0,    0,    0,  -89,  -50,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -42,  -49,    0,  385,    0,    0,    0,    0,    0,
 -218,    0,  -46,    0,  -45,  -41,    0,    0,    0,    0,
    0,    0, -203,  -23,    0,    0,    0,    0,    0,    0,
  -24, -281, -171, -237, -269, -237, -195,    0, -237, -268,
  -75, -254,    0, -237,  -22,    0, -227,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -21,    0,    0,    0,    0,  -38,  -15, -116,
 -229,    0,    0,    0,  -13,  -15,    0, -116,    0,  -12,
 -116,  -11,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  222,  238,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  254,    0,    0,    0,    0,    0,  273,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  289,  305,    0,    0,  324,  351,    0,
    0,    0,    0,    0,    0,    0,   79,    0,    0,    0,
  118,  102,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  390,    0,  169,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  406,
  185,    0,    0,    0,    0,    0,  -85,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  422,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    1,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -181,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -78,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -133, -182,    0, -180,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -144,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -169,    0,    0,   38,    0,  113,    0,
    0,    0,    0,    0,    0,    0,    0,  150,    0,    0,
  153,  151,   44,    0,    0,   45,    0,  161,    0,   40,
    0,    0,    0, -129,   51,  170,  252,    0,  152,    0,
    0,   52,    0,  288,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   16, -126,
};
#define YYTABLESIZE 741
static const YYINT yytable[] = {                        160,
  194,  162,  110,  164,  215,  166,  157,   60,  171,  264,
  265,   50,   58,   59,   73,   74,   75,   76,   77,  168,
  179,   78,   79,  182,  157,   51,   80,  190,   40,  172,
  183,   41,  184,   46,  151,  152,  214,  153,  154,  194,
  195,  196,  197,  198,   47,  199,  200,  201,  185,  202,
  203,  204,  205,   64,  206,  207,  208,  224,   65,  172,
   64,  155,  286,  209,  287,   65,  277,  114,  115,  266,
  224,   61,   81,  247,   52,  186,  225,  248,  196,  273,
  226,  227,  228,  229,  230,  231,  210,  215,  252,  225,
  116,   69,  253,  226,  227,  228,  229,  230,  231,  117,
  118,  111,   62,  111,  107,   55,   56,  112,  113,  107,
  109,  107,   55,   56,  258,  172,  261,   22,   42,  263,
   43,   44,  119,   45,  275,  120,  107,  107,  107,  107,
  107,  121,  107,  107,  107,  216,  107,  107,  107,  107,
  217,  107,  107,  107,  218,  219,  102,   89,  103,  128,
  107,   89,  104,   75,   48,   56,  283,   49,   57,  284,
   75,  290,  127,  220,  292,  129,  237,  238,   82,  239,
  240,  122,  123,  107,  131,   75,   75,   75,   75,   75,
  130,   75,   75,   75,   84,   75,   75,   75,   75,  132,
   75,   75,   75,  241,  146,  147,  148,  136,  137,   75,
  128,  139,  242,  243,  269,  270,   98,   98,  133,  140,
  141,  134,  142,  102,  102,  135,   85,   86,   87,   88,
   89,   68,   75,   90,   91,  143,  144,  138,   92,  150,
  149,  168,  177,  180,  175,  176,  145,   69,  181,   93,
  192,  235,  236,   94,   95,   96,  244,  246,   97,  245,
  249,  250,  255,    6,  279,  251,  194,  194,  194,  194,
  194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
  194,  194,    8,  254,   98,  278,  276,  280,  288,  291,
  257,  191,  293,  165,  163,  256,  167,  194,   23,  259,
  161,  274,  194,  194,  194,  260,  108,  159,  262,   55,
  178,  289,    0,    0,   24,    0,    0,    0,    0,  194,
  194,  194,  194,  194,    0,  194,  194,  194,    0,  194,
  194,  194,  194,   71,  194,  194,  194,    0,    0,    0,
    0,    0,    0,  194,  196,  196,  196,  196,  196,  196,
  196,  196,  196,  196,  196,  196,  196,  196,  196,  196,
   70,    0,    0,    0,    0,    0,  194,  111,  111,  111,
  111,  111,  111,  111,  111,  111,  111,  111,  111,  111,
  111,  111,  111,   22,   22,   22,   22,   22,   22,   22,
   22,   22,   22,   22,   22,   22,   22,   22,   22,   61,
  196,    0,    0,  111,    0,  196,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   62,    0,  111,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   26,    0,   22,   82,   82,   82,   82,   82,   82,
   82,   82,   82,   82,   82,   82,   82,   82,   82,   82,
   84,   84,   84,   84,   84,   84,   84,   84,   84,   84,
   84,   84,   84,   84,   84,   84,    0,    0,    0,    0,
   82,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   84,   68,   68,   68,
   68,   68,   68,   68,   68,   68,   68,   68,   68,   68,
   68,   68,   68,   69,   69,   69,   69,   69,   69,   69,
   69,   69,   69,   69,   69,   69,   69,   69,   69,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
    6,    6,    6,    6,    6,    0,    0,    0,    8,    8,
    8,    8,    8,    8,    8,    8,    8,    8,    8,    8,
    8,    8,    8,    8,   23,   23,   23,   23,   23,   23,
   23,   23,   23,   23,   23,   23,   23,   23,   23,   23,
   24,   24,   24,   24,   24,   24,   24,   24,   24,   24,
   24,   24,   24,   24,   24,   24,    0,    0,    0,   71,
   71,   71,   71,   71,   71,   71,   71,   71,   71,   71,
   71,   71,   71,   71,   71,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   70,   70,   70,   70,
   70,   70,   70,   70,   70,   70,   70,   70,   70,   70,
   70,   70,    2,    3,    4,    5,    6,    7,    8,    9,
   10,   11,   12,   13,   14,   15,   16,   17,    0,    0,
    0,    0,    0,    0,    0,   61,   61,   61,   61,   61,
   61,   61,   61,   61,   61,   61,   61,   61,   61,   61,
   61,   62,   62,   62,   62,   62,   62,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   62,   26,   26,   26,
   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,
   26,   26,   26,  194,  195,  196,  197,  198,    0,  199,
  200,  201,    0,  202,  203,  204,  205,    0,  206,  207,
  208,    0,    0,    0,    0,    0,    0,  209,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  210,
};
static const YYINT yycheck[] = {                        129,
    0,  131,  259,  133,  174,  135,  276,  291,  138,  278,
  279,  276,  273,  274,  300,  301,  302,  303,  304,  286,
  150,  307,  308,  305,  276,  290,  312,  294,  284,  287,
  312,  287,  314,  273,  272,  273,  294,  275,  276,  309,
  310,  311,  312,  313,  283,  315,  316,  317,  330,  319,
  320,  321,  322,  312,  324,  325,  326,  312,  317,  287,
  312,  299,  292,  333,  294,  317,  294,  276,  277,  338,
  312,  355,  358,  292,  299,  357,  331,  296,    0,  334,
  335,  336,  337,  338,  339,  340,  356,  257,  292,  331,
  299,  306,  296,  335,  336,  337,  338,  339,  340,  276,
  277,    0,  319,  360,  287,  287,  287,  276,  277,  292,
  297,  294,  294,  294,  244,  287,  246,    0,  282,  249,
  284,  285,  299,  287,  254,  273,  309,  310,  311,  312,
  313,  273,  315,  316,  317,  331,  319,  320,  321,  322,
  336,  324,  325,  326,  340,  341,  312,  292,  314,  292,
  333,  296,  318,  287,  273,  273,  273,  276,  276,  276,
  294,  288,  297,  359,  291,  297,  272,  273,    0,  275,
  276,  342,  343,  356,  297,  309,  310,  311,  312,  313,
  292,  315,  316,  317,    0,  319,  320,  321,  322,  292,
  324,  325,  326,  299,  352,  353,  354,  292,  293,  333,
  292,  293,  292,  293,  280,  281,  292,  293,  297,  272,
  273,  292,  275,  292,  293,  297,  300,  301,  302,  303,
  304,    0,  356,  307,  308,  288,  289,  297,  312,  297,
  292,  286,  277,  277,  295,  295,  299,    0,  297,  323,
  272,  299,  299,  327,  328,  329,  297,  297,  332,  292,
  297,  297,  277,    0,  293,  297,  256,  257,  258,  259,
  260,  261,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,    0,  297,  358,  297,  299,  293,  292,  292,
  243,  169,  294,  134,  132,  242,  136,  287,    0,  245,
  130,  252,  292,  293,  294,  245,   45,  128,  247,   12,
  149,  286,   -1,   -1,    0,   -1,   -1,   -1,   -1,  309,
  310,  311,  312,  313,   -1,  315,  316,  317,   -1,  319,
  320,  321,  322,    0,  324,  325,  326,   -1,   -1,   -1,
   -1,   -1,   -1,  333,  256,  257,  258,  259,  260,  261,
  262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
    0,   -1,   -1,   -1,   -1,   -1,  356,  256,  257,  258,
  259,  260,  261,  262,  263,  264,  265,  266,  267,  268,
  269,  270,  271,  256,  257,  258,  259,  260,  261,  262,
  263,  264,  265,  266,  267,  268,  269,  270,  271,    0,
  312,   -1,   -1,  292,   -1,  317,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,    0,   -1,  306,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,    0,   -1,  306,  256,  257,  258,  259,  260,  261,
  262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
  256,  257,  258,  259,  260,  261,  262,  263,  264,  265,
  266,  267,  268,  269,  270,  271,   -1,   -1,   -1,   -1,
  292,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  292,  256,  257,  258,
  259,  260,  261,  262,  263,  264,  265,  266,  267,  268,
  269,  270,  271,  256,  257,  258,  259,  260,  261,  262,
  263,  264,  265,  266,  267,  268,  269,  270,  271,  256,
  257,  258,  259,  260,  261,  262,  263,  264,  265,  266,
  267,  268,  269,  270,  271,   -1,   -1,   -1,  256,  257,
  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,
  268,  269,  270,  271,  256,  257,  258,  259,  260,  261,
  262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
  256,  257,  258,  259,  260,  261,  262,  263,  264,  265,
  266,  267,  268,  269,  270,  271,   -1,   -1,   -1,  256,
  257,  258,  259,  260,  261,  262,  263,  264,  265,  266,
  267,  268,  269,  270,  271,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  256,  257,  258,  259,
  260,  261,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,  256,  257,  258,  259,  260,  261,  262,  263,
  264,  265,  266,  267,  268,  269,  270,  271,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  256,  257,  258,  259,  260,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  256,  257,  258,  259,  260,  261,  262,  263,  264,
  265,  266,  267,  268,  269,  270,  271,  256,  257,  258,
  259,  260,  261,  262,  263,  264,  265,  266,  267,  268,
  269,  270,  271,  309,  310,  311,  312,  313,   -1,  315,
  316,  317,   -1,  319,  320,  321,  322,   -1,  324,  325,
  326,   -1,   -1,   -1,   -1,   -1,   -1,  333,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  356,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 360
#define YYUNDFTOKEN 432
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"FSC_LIST","FSC_DEFINE",
"FSC_QUIT","FSC_DEBUG","FSC_CREATE","FSC_SLEEP","FSC_SET","FSC_SYSTEM",
"FSC_EVENTGEN","FSC_ECHO","FSC_RUN","FSC_PSRUN","FSC_VERSION","FSC_ENABLE",
"FSC_DOMULTISYNC","FSV_STRING","FSV_VAL_POSINT","FSV_VAL_NEGINT",
"FSV_VAL_BOOLEAN","FSV_VARIABLE","FSV_WHITESTRING","FSV_RANDUNI","FSV_RANDTAB",
"FSV_URAND","FSV_RAND48","FSE_FILE","FSE_FILES","FSE_FILESET","FSE_PROC",
"FSE_THREAD","FSE_FLOWOP","FSE_CVAR","FSE_RAND","FSE_MODE","FSE_MULTI",
"FSK_SEPLST","FSK_OPENLST","FSK_CLOSELST","FSK_OPENPAR","FSK_CLOSEPAR",
"FSK_ASSIGN","FSK_IN","FSK_QUOTE","FSA_SIZE","FSA_PREALLOC","FSA_PARALLOC",
"FSA_PATH","FSA_REUSE","FSA_MEMSIZE","FSA_RATE","FSA_READONLY","FSA_TRUSTTREE",
"FSA_IOSIZE","FSA_FILENAME","FSA_WSS","FSA_NAME","FSA_RANDOM","FSA_INSTANCES",
"FSA_DSYNC","FSA_TARGET","FSA_ITERS","FSA_NICE","FSA_VALUE","FSA_BLOCKING",
"FSA_HIGHWATER","FSA_DIRECTIO","FSA_DIRWIDTH","FSA_FD","FSA_SRCFD",
"FSA_ROTATEFD","FSA_ENTRIES","FSA_DIRDEPTHRV","FSA_DIRGAMMA","FSA_USEISM",
"FSA_TYPE","FSA_LEAFDIRS","FSA_INDEXED","FSA_RANDTABLE","FSA_RANDSRC",
"FSA_ROUND","FSA_RANDSEED","FSA_RANDGAMMA","FSA_RANDMEAN","FSA_MIN","FSA_MAX",
"FSA_MASTER","FSA_CLIENT","FSS_TYPE","FSS_SEED","FSS_GAMMA","FSS_MEAN",
"FSS_MIN","FSS_SRC","FSS_ROUND","FSA_LVAR_ASSIGN","FSA_ALLDONE","FSA_FIRSTDONE",
"FSA_TIMEOUT","FSA_LATHIST","FSA_NOREADAHEAD","FSA_IOPRIO","FSA_WRITEONLY",
"FSA_PARAMETERS","FSA_NOUSESTATS",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : commands",
"commands : commands command",
"commands : commands error",
"commands :",
"command : proc_define_command",
"command : files_define_command",
"command : flowop_define_command",
"command : debug_command",
"command : eventgen_command",
"command : create_command",
"command : echo_command",
"command : list_command",
"command : run_command",
"command : psrun_command",
"command : set_command",
"command : quit_command",
"command : sleep_command",
"command : system_command",
"command : version_command",
"command : enable_command",
"command : multisync_command",
"eventgen_command : FSC_EVENTGEN",
"eventgen_command : eventgen_command ev_attr_ops",
"system_command : FSC_SYSTEM whitevar_string_list",
"echo_command : FSC_ECHO whitevar_string_list",
"version_command : FSC_VERSION",
"enable_command : FSC_ENABLE FSE_MULTI enable_multi_ops",
"enable_command : FSC_ENABLE FSA_LATHIST",
"multisync_command : FSC_DOMULTISYNC multisync_op",
"whitevar_string : FSK_QUOTE FSV_VARIABLE",
"whitevar_string : FSK_QUOTE FSV_WHITESTRING",
"whitevar_string_list : whitevar_string FSV_WHITESTRING",
"whitevar_string_list : whitevar_string FSV_VARIABLE",
"whitevar_string_list : whitevar_string_list FSV_WHITESTRING",
"whitevar_string_list : whitevar_string_list FSV_VARIABLE",
"whitevar_string_list : whitevar_string_list FSK_QUOTE",
"whitevar_string_list : whitevar_string FSK_QUOTE",
"list_command : FSC_LIST FSE_FILESET",
"list_command : FSC_LIST FSE_FLOWOP",
"debug_command : FSC_DEBUG FSV_VAL_POSINT",
"set_command : set_variable",
"set_command : set_random_variable",
"set_command : set_custom_variable",
"set_command : set_mode",
"set_variable : FSC_SET FSV_VARIABLE FSK_ASSIGN FSV_VAL_POSINT",
"set_variable : FSC_SET FSV_VARIABLE FSK_ASSIGN FSV_VAL_BOOLEAN",
"set_variable : FSC_SET FSV_VARIABLE FSK_ASSIGN FSK_QUOTE FSV_WHITESTRING FSK_QUOTE",
"set_variable : FSC_SET FSV_VARIABLE FSK_ASSIGN FSV_STRING",
"set_random_variable : FSC_SET FSV_VARIABLE FSK_ASSIGN FSE_RAND FSK_OPENPAR randvar_attr_ops FSK_CLOSEPAR",
"set_custom_variable : FSC_SET FSV_VARIABLE FSK_ASSIGN FSE_CVAR FSK_OPENPAR cvar_attr_ops FSK_CLOSEPAR",
"set_mode : FSC_SET FSE_MODE FSC_QUIT FSA_TIMEOUT",
"set_mode : FSC_SET FSE_MODE FSC_QUIT FSA_ALLDONE",
"set_mode : FSC_SET FSE_MODE FSC_QUIT FSA_FIRSTDONE",
"set_mode : FSC_SET FSE_MODE FSA_NOUSESTATS",
"quit_command : FSC_QUIT",
"flowop_list : flowop_command",
"flowop_list : flowop_list flowop_command",
"thread : FSE_THREAD t_attr_ops FSK_OPENLST flowop_list FSK_CLOSELST",
"thread_list : thread",
"thread_list : thread_list thread",
"proc_define_command : FSC_DEFINE FSE_PROC p_attr_ops FSK_OPENLST thread_list FSK_CLOSELST",
"files_define_command : FSC_DEFINE FSE_FILE file_attr_ops",
"files_define_command : FSC_DEFINE FSE_FILESET fileset_attr_ops",
"create_command : FSC_CREATE FSE_FILES",
"sleep_command : FSC_SLEEP FSV_VAL_POSINT",
"sleep_command : FSC_SLEEP FSV_VARIABLE",
"run_command : FSC_RUN FSV_VAL_POSINT",
"run_command : FSC_RUN FSV_VARIABLE",
"run_command : FSC_RUN",
"psrun_command : FSC_PSRUN",
"psrun_command : FSC_PSRUN FSV_VAL_NEGINT",
"psrun_command : FSC_PSRUN FSV_VAL_POSINT",
"psrun_command : FSC_PSRUN FSV_VAL_NEGINT FSV_VAL_POSINT",
"psrun_command : FSC_PSRUN FSV_VAL_POSINT FSV_VAL_POSINT",
"flowop_command : FSE_FLOWOP name",
"flowop_command : flowop_command fo_attr_ops",
"name : FSV_STRING",
"file_attr_ops : file_attr_op",
"file_attr_ops : file_attr_ops FSK_SEPLST file_attr_op",
"fileset_attr_ops : fileset_attr_op",
"fileset_attr_ops : fileset_attr_ops FSK_SEPLST fileset_attr_op",
"file_attr_op : attrs_define_file FSK_ASSIGN attr_value",
"file_attr_op : attrs_define_file",
"fileset_attr_op : attrs_define_fileset FSK_ASSIGN attr_value",
"fileset_attr_op : attrs_define_fileset",
"randvar_attr_ops : randvar_attr_op",
"randvar_attr_ops : randvar_attr_ops FSK_SEPLST randvar_attr_op",
"randvar_attr_ops : randvar_attr_ops FSK_SEPLST FSA_RANDTABLE FSK_ASSIGN FSK_OPENLST probtabentry_list FSK_CLOSELST",
"randvar_attr_op : randvar_attr_name FSK_ASSIGN attr_value",
"randvar_attr_op : randvar_attr_name",
"randvar_attr_op : FSA_TYPE FSK_ASSIGN randvar_attr_typop",
"randvar_attr_op : FSA_RANDSRC FSK_ASSIGN randvar_attr_srcop",
"probtabentry : FSK_OPENLST var_int_val FSK_SEPLST var_int_val FSK_SEPLST var_int_val FSK_CLOSELST",
"probtabentry_list : probtabentry",
"probtabentry_list : probtabentry_list FSK_SEPLST probtabentry",
"p_attr_ops : p_attr_op",
"p_attr_ops : p_attr_ops FSK_SEPLST p_attr_op",
"p_attr_op : attrs_define_proc FSK_ASSIGN attr_value",
"p_attr_op : attrs_define_proc",
"t_attr_ops : t_attr_op",
"t_attr_ops : t_attr_ops FSK_SEPLST t_attr_op",
"t_attr_op : attrs_define_thread FSK_ASSIGN attr_value",
"t_attr_op : attrs_define_thread",
"fo_attr_ops : fo_attr_op",
"fo_attr_ops : fo_attr_ops FSK_SEPLST fo_attr_op",
"fo_attr_ops : fo_attr_ops FSK_SEPLST comp_lvar_def",
"fo_attr_op : attrs_flowop FSK_ASSIGN attr_value",
"fo_attr_op : attrs_flowop",
"ev_attr_ops : ev_attr_op",
"ev_attr_ops : ev_attr_ops FSK_SEPLST ev_attr_op",
"ev_attr_op : attrs_eventgen FSK_ASSIGN attr_value",
"ev_attr_op : attrs_eventgen",
"enable_multi_ops : enable_multi_op",
"enable_multi_ops : enable_multi_ops FSK_SEPLST enable_multi_op",
"enable_multi_op : em_attr_name FSK_ASSIGN attr_value",
"multisync_op : FSA_VALUE FSK_ASSIGN attr_value",
"attrs_define_proc : FSA_NAME",
"attrs_define_proc : FSA_INSTANCES",
"attrs_define_proc : FSA_NICE",
"attrs_define_file : FSA_NAME",
"attrs_define_file : FSA_PATH",
"attrs_define_file : FSA_SIZE",
"attrs_define_file : FSA_PREALLOC",
"attrs_define_file : FSA_PARALLOC",
"attrs_define_file : FSA_REUSE",
"attrs_define_file : FSA_TRUSTTREE",
"attrs_define_file : FSA_READONLY",
"attrs_define_file : FSA_WRITEONLY",
"attrs_define_fileset : FSA_NAME",
"attrs_define_fileset : FSA_PATH",
"attrs_define_fileset : FSA_ENTRIES",
"attrs_define_fileset : FSA_SIZE",
"attrs_define_fileset : FSA_PREALLOC",
"attrs_define_fileset : FSA_PARALLOC",
"attrs_define_fileset : FSA_REUSE",
"attrs_define_fileset : FSA_TRUSTTREE",
"attrs_define_fileset : FSA_READONLY",
"attrs_define_fileset : FSA_WRITEONLY",
"attrs_define_fileset : FSA_DIRWIDTH",
"attrs_define_fileset : FSA_DIRDEPTHRV",
"attrs_define_fileset : FSA_DIRGAMMA",
"attrs_define_fileset : FSA_LEAFDIRS",
"randvar_attr_name : FSA_NAME",
"randvar_attr_name : FSA_RANDSEED",
"randvar_attr_name : FSA_RANDGAMMA",
"randvar_attr_name : FSA_RANDMEAN",
"randvar_attr_name : FSA_MIN",
"randvar_attr_name : FSA_ROUND",
"randvar_attr_typop : randtype_name",
"randtype_name : FSV_RANDUNI",
"randtype_name : FSV_RANDTAB",
"randtype_name : FSA_RANDGAMMA",
"randvar_attr_srcop : randsrc_name",
"randsrc_name : FSV_URAND",
"randsrc_name : FSV_RAND48",
"cvar_attr_name : FSA_TYPE",
"cvar_attr_name : FSA_PARAMETERS",
"cvar_attr_name : FSA_MIN",
"cvar_attr_name : FSA_MAX",
"cvar_attr_name : FSA_ROUND",
"attrs_define_thread : FSA_NAME",
"attrs_define_thread : FSA_MEMSIZE",
"attrs_define_thread : FSA_USEISM",
"attrs_define_thread : FSA_INSTANCES",
"attrs_define_thread : FSA_IOPRIO",
"attrs_flowop : FSA_WSS",
"attrs_flowop : FSA_FILENAME",
"attrs_flowop : FSA_NAME",
"attrs_flowop : FSA_RANDOM",
"attrs_flowop : FSA_FD",
"attrs_flowop : FSA_SRCFD",
"attrs_flowop : FSA_ROTATEFD",
"attrs_flowop : FSA_DSYNC",
"attrs_flowop : FSA_DIRECTIO",
"attrs_flowop : FSA_INDEXED",
"attrs_flowop : FSA_TARGET",
"attrs_flowop : FSA_ITERS",
"attrs_flowop : FSA_VALUE",
"attrs_flowop : FSA_BLOCKING",
"attrs_flowop : FSA_HIGHWATER",
"attrs_flowop : FSA_IOSIZE",
"attrs_flowop : FSA_NOREADAHEAD",
"attrs_eventgen : FSA_RATE",
"em_attr_name : FSA_MASTER",
"em_attr_name : FSA_CLIENT",
"comp_attr_ops : comp_attr_op",
"comp_attr_ops : comp_attr_ops FSK_SEPLST comp_attr_op",
"comp_attr_ops : comp_attr_ops FSK_SEPLST comp_lvar_def",
"comp_attr_op : attrs_define_comp FSK_ASSIGN attr_value",
"comp_lvar_def : FSV_VARIABLE FSK_ASSIGN FSV_VAL_BOOLEAN",
"comp_lvar_def : FSV_VARIABLE FSK_ASSIGN FSV_VAL_POSINT",
"comp_lvar_def : FSV_VARIABLE FSK_ASSIGN FSK_QUOTE FSV_WHITESTRING FSK_QUOTE",
"comp_lvar_def : FSV_VARIABLE FSK_ASSIGN FSV_STRING",
"comp_lvar_def : FSV_VARIABLE FSK_ASSIGN FSV_VARIABLE",
"comp_lvar_def : FSV_VARIABLE",
"flowop_define_command : FSC_DEFINE FSE_FLOWOP comp_attr_ops FSK_OPENLST flowop_list FSK_CLOSELST",
"flowop_define_command : flowop_define_command comp_attr_ops",
"cvar_attr_ops : cvar_attr_op",
"cvar_attr_ops : cvar_attr_ops FSK_SEPLST cvar_attr_op",
"cvar_attr_op : cvar_attr_name FSK_ASSIGN attr_value",
"attrs_define_comp : FSA_NAME",
"attrs_define_comp : FSA_ITERS",
"attr_value : FSV_STRING",
"attr_value : FSK_QUOTE FSV_WHITESTRING FSK_QUOTE",
"attr_value : FSV_VAL_POSINT",
"attr_value : FSV_VAL_BOOLEAN",
"attr_value : FSV_VARIABLE",
"var_int_val : FSV_VAL_POSINT",
"var_int_val : FSV_VARIABLE",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 1283 "parser_gram.y"

/*
 * The following C routines implement the various commands defined in the above
 * yacc parser code. The yacc portion checks the syntax of the commands found
 * in a workload file and parses the commands' parameters into lists. The lists
 * are then passed in a cmd_t struct for each command to its related routine in
 * the following section for actual execution.  This section also includes a
 * few utility routines and the main entry point for the program.
 */

#define	USAGE \
"Usage: " \
"filebench {-f <wmlscript> | -h | -c [cvartype]}\n\n" \
"  Filebench version " FILEBENCH_VERSION "\n\n" \
"  Filebench is a file system and storage benchmark that interprets a script\n" \
"  written in its Workload Model Language (WML), and procees to generate the\n" \
"  specified workload. Refer to the README for more details.\n\n" \
"  Visit github.com/filebench/filebench for WML definition and tutorials.\n\n" \
"Options:\n" \
"   -f <wmlscript> generate workload from the specified file\n" \
"   -h             display this help message\n" \
"   -c             display supported cvar types\n" \
"   -c [cvartype]  display options of the specific cvar type\n\n"

static void
usage_exit(int ret, const char *msg)
{
	if (ret) {
		(void)fprintf(stderr, "Usage error: %s\n\n", msg);
		(void)fprintf(stderr, USAGE);
	} else
		printf(USAGE);
	exit(ret);
}

struct fbparams {
	char *execname;
	char *fscriptname;
	char *procname;
	char *shmaddr;
	char *shmpath;
	int instance;
	char *cvartype;
};

static void
init_fbparams(struct fbparams *fbparams)
{
	memset(fbparams, 0, sizeof(*fbparams));
	fbparams->instance = -1;
}

#define FB_MODE_NONE		0
#define FB_MODE_HELP		1
#define FB_MODE_MASTER		2
#define FB_MODE_WORKER		3
#define FB_MODE_CVARS		4

static int
parse_options(int argc, char *argv[], struct fbparams *fbparams)
{
	const char cmd_options[] = "m:s:a:i:hf:c:";
	int mode = FB_MODE_NONE;
	int opt;

	init_fbparams(fbparams);
	fbparams->execname = argv[0];

 	/*
	 * We don't want getopt() to print error messages because
	 * sometimes what it percieves as an error is actually not
	 * an error.  For example, "-c" option might have or might
	 * not have an argument.  If opterr is non-zero, getopt()
	 * prints an error message when "-c"'s argument is missing.
	 */
	opterr = 0;

	/* Either
		(-f <wmlscript>) or
		(-a and -s and -m and -i) or
		(-c [cvartype]) or
		(-h)
	   must be specified */
	while ((opt = getopt(argc, argv, cmd_options)) > 0) {
		switch (opt) {
		/* public parameters */
		case 'h':
			if (mode != FB_MODE_NONE)
				usage_exit(1, "Too many options specified");
			mode = FB_MODE_HELP;
			break;
		case 'c':
			if (mode != FB_MODE_NONE)
				usage_exit(1, "Too many options specified");
			mode = FB_MODE_CVARS;
			fbparams->cvartype = optarg;
			break;
		case 'f':
			if (mode != FB_MODE_NONE)
				usage_exit(1, "Too many options specified");
			mode = FB_MODE_MASTER;
			fbparams->fscriptname = optarg;
			break;
		/* private parameters: when filebench calls itself */
		case 'a':
			if (mode != FB_MODE_NONE &&
				(mode != FB_MODE_WORKER || fbparams->procname))
					usage_exit(1, "Too many options");
			mode = FB_MODE_WORKER;
			fbparams->procname = optarg;
			break;
		case 's':
			if (mode != FB_MODE_NONE &&
				(mode != FB_MODE_WORKER || fbparams->shmaddr))
					usage_exit(1, "Too many options");
			mode = FB_MODE_WORKER;
			sscanf(optarg, "%p", &fbparams->shmaddr);
			break;
		case 'm':
			if (mode != FB_MODE_NONE &&
				(mode != FB_MODE_WORKER || fbparams->shmpath))
					usage_exit(1, "Too many options");
			mode = FB_MODE_WORKER;
			fbparams->shmpath = optarg;
			break;
		case 'i':
			if (mode != FB_MODE_NONE &&
				(mode != FB_MODE_WORKER || fbparams->instance != -1))
					usage_exit(1, "Too many options");
			mode = FB_MODE_WORKER;
			sscanf(optarg, "%d", &fbparams->instance);
			break;
		case '?':
			if (optopt == 'c') {
				if (mode != FB_MODE_NONE)
					usage_exit(1, "Too many options");
				mode = FB_MODE_CVARS;
				break;
			}
		default:
			usage_exit(1, "Unrecognized option");
			break;
		}
	}

	if (mode == FB_MODE_NONE)
		usage_exit(1, "No runtime options specified");

	if (mode == FB_MODE_WORKER) {
		if (!fbparams->procname ||
			!fbparams->shmaddr ||
			!fbparams->shmpath ||
			fbparams->instance == -1)
			usage_exit(1, "Invalid worker settings");
	}

	return mode;
}

static void
worker_mode(struct fbparams *fbparams)
{
	int ret;

	ret = ipc_attach(fbparams->shmaddr, fbparams->shmpath);
	if (ret < 0) {
		filebench_log(LOG_FATAL, "Cannot attach shm for %s",
		    fbparams->procname);
		exit(1);
	}

	/* get correct function pointer for each working process */
	flowop_init(0);

	/* load custom variable libraries and revalidate handles */
	ret = init_cvar_libraries();
	if (ret)
		exit(1);

	ret = revalidate_cvar_handles();
	if (ret)
		exit(1);

	/* execute corresponding procflow */
	ret = procflow_exec(fbparams->procname, fbparams->instance);
	if (ret < 0) {
		filebench_log(LOG_FATAL, "Cannot startup process %s",
		    fbparams->procname);
		exit(1);
	}

	exit(0);
}

void parser_list_cvar_types(void)
{
	cvar_library_info_t *t;

	if (!filebench_shm->shm_cvar_lib_info_list) {
		printf("No custom variables supported.\n");
		return;
	}

	printf("Custom variable types supported:\n");
	for (t = filebench_shm->shm_cvar_lib_info_list; t; t = t->next)
		printf("  %s\n", t->type);

	return;
}

void parser_list_cvar_type_parameters(char *type)
{
	const char *version = NULL;
	const char *usage = NULL;

	cvar_library_info_t *t;

	for (t = filebench_shm->shm_cvar_lib_info_list; t != NULL; t = t->next) {
		if (!strcmp(type, t->type))
			break;
	}

	if (!t) {
		printf("Unknown custom variable type %s.\n", type);
		return;
	}

	printf("Custom variable type: %s\n", t->type);
	printf("Supporting library: %s\n", t->filename);

	if (cvar_libraries[t->index]->cvar_op.cvar_version)
		version = cvar_libraries[t->index]->cvar_op.cvar_version();

	if (cvar_libraries[t->index]->cvar_op.cvar_usage)
		usage = cvar_libraries[t->index]->cvar_op.cvar_usage();


	if (version)
		printf("Version: %s\n", version);
	else
		printf("Oops. No version information provided.\n");

	if (usage)
		printf("Usage:\n%s\n", usage);
	else
		printf("Oops. No usage information provided.\n");

	return;
}

static void
cvars_mode(struct fbparams *fbparams)
{
	int ret;

	ipc_init();

	ret = init_cvar_library_info(FBDATADIR "/cvars");
	if (ret)
		filebench_shutdown(1);

	ret = init_cvar_libraries();
	if (ret)
		filebench_shutdown(1);

	if (fbparams->cvartype)
		parser_list_cvar_type_parameters(fbparams->cvartype);
	else
		parser_list_cvar_types();

	ipc_fini();

	exit(0);
}

/*
 * Shutdown filebench.
 */
static void
parser_abort(int arg)
{
	(void) sigignore(SIGINT);
	filebench_log(LOG_INFO, "Aborting...");
	filebench_shutdown(1);
}

static void
master_mode(struct fbparams *fbparams) {
	int ret;

	printf("Filebench Version %s\n", FILEBENCH_VERSION);

	yyin = fopen(fbparams->fscriptname, "r");
	if (!yyin) {
		filebench_log(LOG_FATAL,
			"Cannot open file %s!", fbparams->fscriptname);
		exit(1);
	}

	execname = fbparams->execname;
	fb_set_shmmax();

	ipc_init();

	/* Below we initialize things that depend on IPC */
	(void)strcpy(filebench_shm->shm_fscriptname,
				fbparams->fscriptname);

	flowop_init(1);
	eventgen_init();

	/* Initialize custom variables. */
	ret = init_cvar_library_info(FBDATADIR "/cvars");
	if (ret)
		filebench_shutdown(1);

	ret = init_cvar_libraries();
	if (ret)
		filebench_shutdown(1);

	signal(SIGINT, parser_abort);

	/* yyparse() after it parsed complete grammar */
	yyparse();

	/* We only get here if there was no
	   run (or similar) command in the
	   end of the WML script. */
	printf("Warning: no run command in the WML script!\n");
	parser_filebench_shutdown((cmd_t *)0);
}

static void
init_common()
{
	disable_aslr();
	my_pid = getpid();
	fb_set_rlimit();
}

/*
 * Entry point for Filebench. Processes command line arguments. The -f option
 * will read in a workload file (the full name and extension must must be
 * given). The -a, -s, -m and -i options are used by the worker process to
 * receive the name, the base address of shared memory, its path, and the
 * process' instance number, respectively. This information is supplied by the
 * master process when it execs worker processes. If the worker process
 * arguments are passed then main will call the procflow_exec() routine which
 * creates worker threadflows and flowops and executes the procflow's portion of
 * the workload model until completion. If worker process arguments are not
 * passed to the process, then it becomes the master process for a filebench
 * run. It initializes the various filebench components and either executes the
 * supplied workload file, or enters interactive mode.
 */
int
main(int argc, char *argv[])
{
	struct fbparams fbparams;
	int mode;

	/* parse_options() exits if detects wrong usage */
	mode = parse_options(argc, argv, &fbparams);

	if (mode == FB_MODE_HELP)
		usage_exit(0, NULL);

	if (mode == FB_MODE_CVARS)
		cvars_mode(&fbparams);

	init_common();

	if (mode == FB_MODE_MASTER)
		master_mode(&fbparams);

	if (mode == FB_MODE_WORKER)
		worker_mode(&fbparams);

	/* We should never reach this point */
	return 0;
}

/*
 * Converts a list of var_strings or ordinary strings to a single ordinary
 * string. It returns a pointer to the string (in malloc'd memory) if found,
 * or NULL otherwise.
 */
char *
parser_list2string(list_t *list)
{
	list_t *l;
	char *string;
	char *tmp;

	string = malloc(MAXPATHLEN);
	if (!string) {
		filebench_log(LOG_ERROR, "Failed to allocate memory");
		return NULL;
	}

	*string = 0;

	/* Format args */
	for (l = list; l != NULL; l = l->list_next) {

		char *lstr = avd_get_str(l->list_string);

		filebench_log(LOG_DEBUG_SCRIPT, "converting string '%s'", lstr);

		/* see if it is a random variable */
		if (l->list_integer) {
			fbint_t param_name;

			tmp = NULL;
			param_name = avd_get_int(l->list_integer);

			switch (param_name) {
			case FSS_TYPE:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_TYPE);
				break;

			case FSS_SRC:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_SRC);
				break;

			case FSS_SEED:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_SEED);
				break;

			case FSS_MIN:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_MIN);
				break;

			case FSS_MEAN:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_MEAN);
				break;

			case FSS_GAMMA:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_GAMMA);
				break;

			case FSS_ROUND:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_ROUND);
				break;
			}

			if (tmp) {
				(void) strcat(string, tmp);
				free(tmp);
			} else {
				(void) strcat(string, lstr);
			}
		} else {
			/* perhaps a normal variable? */
			if ((tmp = var_to_string(lstr)) != NULL) {
				(void) strcat(string, tmp);
				free(tmp);
			} else {
				(void) strcat(string, lstr);
			}
		}
	}

	return string;
}

/*
 * If the list just contains a single string starting with '$', then find
 * or create the named var and return the var's var_string component.
 * Otherwise, convert the list to a string, and allocate a var_string
 * containing a copy of that string. On failure either returns NULL
 * or shuts down the run.
 */
avd_t
parser_list2varstring(list_t *list)
{
	char *lstr = avd_get_str(list->list_string);

	/* Special case - variable name */
	if ((list->list_next == NULL) && (*lstr == '$'))
		return avd_var_alloc(lstr);

	return (avd_str_alloc(parser_list2string(list)));
}

/*
 * Looks for the var named in list_string of the first element of the
 * supplied list. If found, returns the var_val portion of the var in
 * an attribute value descriptor. If the var is not found, cannot be
 * allocated, the supplied list is NULL, or the list_string filed is
 * empty, returns NULL.
 */
avd_t
parser_list2avd(list_t *list)
{
	avd_t avd;
	char *lstr;

	if (list && ((lstr = avd_get_str(list->list_string)) != NULL)) {
		avd = avd_var_alloc(lstr);
		return (avd);
	}

	return (NULL);
}

/*
 * Sets the event generator rate from the attribute supplied with the
 * command. If the attribute doesn't exist the routine does nothing.
 */
static void
parser_eventgen(cmd_t *cmd)
{
	attr_t *attr;

	/* Get the rate from attribute */
	if ((attr = get_attr(cmd, FSA_RATE))) {
		if (attr->attr_avd) {
			eventgen_setrate(attr->attr_avd);
		}
	}
}

/*
 * Lists the fileset name, path name and average size for all defined
 * filesets.
 */
static void
parser_fileset_list(cmd_t *cmd)
{
	(void) fileset_iter(fileset_print);
}

/*
 * Lists the flowop name and instance number for all flowops.
 */
static void
parser_flowop_list(cmd_t *cmd)
{
	flowop_printall();
}

/*
 * Calls procflow_define() to allocate "instances" number of  procflow(s)
 * (processes) with the supplied name. The default number of instances is
 * one. An optional priority level attribute can be supplied and is stored in
 * pf_nice. Finally the routine loops through the list of inner commands, if
 * any, which are defines for threadflows, and passes them one at a time to
 * parser_thread_define() to allocate threadflow entities for the process(es).
 */
static void
parser_proc_define(cmd_t *cmd)
{
	procflow_t *procflow;
	char *name = NULL;
	attr_t *attr;
	avd_t var_instances;
	fbint_t instances;
	cmd_t *inner_cmd;

	attr = get_attr(cmd, FSA_NAME);
	if (attr)
		name = avd_get_str(attr->attr_avd);
	else {
		filebench_log(LOG_ERROR, "process specifies no name");
		filebench_shutdown(1);
	}

	attr = get_attr(cmd, FSA_INSTANCES);
	if (attr) {
		var_instances = attr->attr_avd;
		instances = avd_get_int(var_instances);
		filebench_log(LOG_DEBUG_IMPL,
		    "Setting instances = %llu", (u_longlong_t)instances);
	} else {
		filebench_log(LOG_DEBUG_IMPL,
		    "Defaulting to instances = 1");
		var_instances = avd_int_alloc(1);
		instances = 1;
	}

	procflow = procflow_define(name, var_instances);
	if (!procflow) {
		filebench_log(LOG_ERROR,
		    "Failed to instantiate %d %s process(es)\n",
		    instances, name);
		filebench_shutdown(1);
	}

	attr = get_attr(cmd, FSA_NICE);
	if (attr) {
		filebench_log(LOG_DEBUG_IMPL, "Setting pri = %llu",
			    (u_longlong_t)avd_get_int(attr->attr_avd));
		procflow->pf_nice = attr->attr_avd;
	} else
		procflow->pf_nice = avd_int_alloc(0);

	/* Create the list of threads for this process  */
	for (inner_cmd = cmd->cmd_list; inner_cmd;
	    	inner_cmd = inner_cmd->cmd_next)
		parser_thread_define(inner_cmd, procflow);
}

/*
 * Calls threadflow_define() to allocate "instances" number of  threadflow(s)
 * (threads) with the supplied name. The default number of instances is
 * one. Two other optional attributes may be supplied, one to set the memory
 * size, stored in tf_memsize, and to select the use of Interprocess Shared
 * Memory, which sets the THREADFLOW_USEISM flag in tf_attrs. Finally
 * the routine loops through the list of inner commands, if any, which are
 * defines for flowops, and passes them one at a time to
 * parser_flowop_define() to allocate flowop entities for the threadflows.
 */
static void
parser_thread_define(cmd_t *cmd, procflow_t *procflow)
{
	threadflow_t *threadflow, template;
	attr_t *attr;
	avd_t instances;
	cmd_t *inner_cmd;
	char *name = NULL;

	memset(&template, 0, sizeof (threadflow_t));

	attr = get_attr(cmd, FSA_NAME);
	if (attr)
		name = avd_get_str(attr->attr_avd);
	else {
		filebench_log(LOG_ERROR,
		    "thread in process %s specifies no name",
		    procflow->pf_name);
		filebench_shutdown(1);
	}

	attr = get_attr(cmd, FSA_INSTANCES);
	if (attr)
		instances = attr->attr_avd;
	else
		instances = avd_int_alloc(1);

	attr = get_attr(cmd, FSA_MEMSIZE);
	if (attr)
		template.tf_memsize = attr->attr_avd;
	else /* XXX: really, memsize zero is default?.. */
		template.tf_memsize = avd_int_alloc(0);
	
	attr = get_attr(cmd, FSA_IOPRIO);
	if (attr)
		template.tf_ioprio = attr->attr_avd;
	else /* XXX: really, ioprio is 8 by default?.. */
		template.tf_ioprio = avd_int_alloc(8);


	threadflow = threadflow_define(procflow, name, &template, instances);
	if (!threadflow) {
		filebench_log(LOG_ERROR,
		    "failed to instantiate thread\n");
		filebench_shutdown(1);
	}

	attr = get_attr(cmd, FSA_USEISM);
	if (attr)
		threadflow->tf_attrs |= THREADFLOW_USEISM;

	/* create the list of flowops */
	for (inner_cmd = cmd->cmd_list; inner_cmd;
	    inner_cmd = inner_cmd->cmd_next)
		parser_flowop_define(inner_cmd, threadflow,
		    &threadflow->tf_thrd_fops, FLOW_MASTER);
}

/*
 * Fills in the attributes for a newly allocated flowop
 */
static void
parser_flowop_get_attrs(cmd_t *cmd, flowop_t *flowop)
{
	attr_t *attr;

	/* Get the filename from attribute */
	if ((attr = get_attr(cmd, FSA_FILENAME))) {
		flowop->fo_filename = attr->attr_avd;
		if (flowop->fo_filename == NULL) {
			filebench_log(LOG_ERROR,
			    "define flowop: no filename specfied");
			filebench_shutdown(1);
		}
	} else {
		/* no filename attribute specified */
		flowop->fo_filename = NULL;
	}

	/* Get the iosize of the op */
	if ((attr = get_attr(cmd, FSA_IOSIZE)))
		flowop->fo_iosize = attr->attr_avd;
	else
		flowop->fo_iosize = avd_int_alloc(0);

	/* Get the working set size of the op */
	if ((attr = get_attr(cmd, FSA_WSS)))
		flowop->fo_wss = attr->attr_avd;
	else
		flowop->fo_wss = avd_int_alloc(0);

	/* Random I/O? */
	if ((attr = get_attr(cmd, FSA_RANDOM)))
		flowop->fo_random = attr->attr_avd;
	else
		flowop->fo_random = avd_bool_alloc(FALSE);

	/* Sync I/O? */
	if ((attr = get_attr(cmd, FSA_DSYNC)))
		flowop->fo_dsync = attr->attr_avd;
	else
		flowop->fo_dsync = avd_bool_alloc(FALSE);

	/* Target, for wakeup etc */
	if ((attr = get_attr(cmd, FSA_TARGET)))
		(void) strcpy(flowop->fo_targetname,
		    avd_get_str(attr->attr_avd));

	/* Value */
	if ((attr = get_attr(cmd, FSA_VALUE)))
		flowop->fo_value = attr->attr_avd;
	else
		flowop->fo_value = avd_int_alloc(0);

	/* FD */
	if ((attr = get_attr(cmd, FSA_FD))) {
		flowop->fo_fdnumber = avd_get_int(attr->attr_avd);
		if (flowop->fo_filename != NULL)
			filebench_log(LOG_DEBUG_SCRIPT, "It is not "
			    "advisable to supply both an fd number "
			    "and a fileset name in most cases");
	}

	/* Rotatefd? */
	if ((attr = get_attr(cmd, FSA_ROTATEFD)))
		flowop->fo_rotatefd = attr->attr_avd;
	else
		flowop->fo_rotatefd = avd_bool_alloc(FALSE);

	/* SRC FD, for copies etc... */
	if ((attr = get_attr(cmd, FSA_SRCFD)))
		flowop->fo_srcfdnumber = avd_get_int(attr->attr_avd);

	/* Blocking operation? */
	if ((attr = get_attr(cmd, FSA_BLOCKING)))
		flowop->fo_blocking = attr->attr_avd;
	else
		flowop->fo_blocking = avd_bool_alloc(FALSE);

	/* Direct I/O Operation */
	if ((attr = get_attr(cmd, FSA_DIRECTIO)))
		flowop->fo_directio = attr->attr_avd;
	else
		flowop->fo_directio = avd_bool_alloc(FALSE);

	/* Highwater mark */
	if ((attr = get_attr(cmd, FSA_HIGHWATER))) {
		flowop->fo_highwater = attr->attr_avd;
		if (AVD_IS_RANDOM(attr->attr_avd)) {
			filebench_log(LOG_ERROR,
			    "define flowop: Highwater attr cannot be random");
			filebench_shutdown(1);
		}
	} else {
		flowop->fo_highwater = avd_int_alloc(1);
	}

	/* find file or leaf directory by index number */
	if ((attr = get_attr(cmd, FSA_INDEXED)))
		flowop->fo_fileindex = attr->attr_avd;
	else
		flowop->fo_fileindex = NULL;

	/* Read Ahead Diable */
	if ((attr = get_attr(cmd, FSA_NOREADAHEAD)))
		flowop->fo_noreadahead = attr->attr_avd;
	else
		flowop->fo_noreadahead = avd_bool_alloc(FALSE);


}

/*
 * defines the FLOW_MASTER flowops within a FLOW_MASTER instance of
 * a composit flowop. Default attributes from the FLOW_INNER_DEF instances
 * of the composit flowop's inner flowops are used if set. Otherwise
 * default attributes from the FLOW_MASTER instance of the composit flowop
 * are used, which may include defaults from the original FLOW_DEFINITION
 * of the composit flowop.
 */
static void
parser_inner_flowop_define(threadflow_t *thread, flowop_t *comp0_flow,
			   flowop_t *comp_mstr_flow)
{
	flowop_t *inner_flowtype, *inner_flowop;

	/* follow flowop list, creating composit names */
	inner_flowtype = comp0_flow->fo_comp_fops;
	comp_mstr_flow->fo_comp_fops = NULL;

	while (inner_flowtype) {
		char fullname[MAXPATHLEN];

		/* create composite_name.name for new flowop */
		snprintf(fullname, MAXPATHLEN, "%s.%s",
		    comp_mstr_flow->fo_name, inner_flowtype->fo_name);

		if ((inner_flowop = flowop_define(thread, fullname,
		    inner_flowtype, &comp_mstr_flow->fo_comp_fops,
		    FLOW_MASTER, 0)) == NULL) {
			filebench_log(LOG_ERROR,
			    "define flowop: Failed to instantiate flowop %s\n",
			    fullname);
			filebench_shutdown(1);
		}

		/* if applicable, update filename attribute */
		if (inner_flowop->fo_filename) {
			char *name;

			/* fix up avd_t */
			avd_update(&inner_flowop->fo_filename,
			    comp_mstr_flow->fo_lvar_list);

			/* see if ready to get the file or fileset */
			name = avd_get_str(inner_flowop->fo_filename);
			if (name) {

				inner_flowop->fo_fileset = fileset_find(name);

				if (inner_flowop->fo_fileset == NULL) {
					filebench_log(LOG_ERROR,
					    "inr flowop %s: file %s not found",
					    inner_flowop->fo_name, name);
					filebench_shutdown(1);
				}
			}
		}

		/* update attributes from local variables */
		avd_update(&inner_flowop->fo_iters,
		    comp_mstr_flow->fo_lvar_list);

		/* if the inner flowop is a composit flowop, recurse */
		if (inner_flowtype->fo_type == FLOW_TYPE_COMPOSITE) {
			var_t *newlvar, *proto_lvars, *lvar_ptr;

			proto_lvars = inner_flowop->fo_lvar_list;
			inner_flowop->fo_lvar_list = 0;

			for (lvar_ptr = inner_flowtype->fo_lvar_list; lvar_ptr;
			    lvar_ptr = lvar_ptr->var_next) {

				if ((newlvar = var_lvar_alloc_local(
				    lvar_ptr->var_name)) != NULL) {

					add_lvar_to_list(newlvar,
					    &inner_flowop->fo_lvar_list);

					var_update_comp_lvars(newlvar,
					    proto_lvars,
					    comp_mstr_flow->fo_lvar_list);
				}
			}

			parser_inner_flowop_define(thread,
			    inner_flowtype,
			    inner_flowop);

			inner_flowtype = inner_flowtype->fo_exec_next;
			continue;
		}

		avd_update(&inner_flowop->fo_iosize,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_wss,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_iters,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_value,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_random,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_dsync,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_rotatefd,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_blocking,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_directio,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_highwater,
		    comp_mstr_flow->fo_lvar_list);

		inner_flowtype = inner_flowtype->fo_exec_next;
	}
}

/*
 * Calls flowop_define() to allocate a flowop with the supplied name.
 * The allocated flowop inherits attributes from a base flowop of the
 * same type.  If the new flowop has a file or fileset attribute specified,
 * it must specify a defined fileobj or fileset or an error will be logged.
 * The new flowop may  also have the following attributes set by
 * the program:
 *  - file size (fo_iosize)
 *  - working set size (fo_wss)
 *  - do random io (fo_random)
 *  - do synchronous io (fo_dsync)
 *  - perform each operation multiple times before advancing (fo_iter)
 *  - target name (fo_targetname)
 *  - An integer value (fo_value)
 *  - a file descriptor (fo_fd)
 *  - specify to rotate file descriptors (fo_rotatefd)
 *  - a source fd (fo_srcfdnumber)
 *  - specify a blocking operation (fo_blocking)
 *  - specify a highwater mark (fo_highwater)
 *
 * After all the supplied attributes are stored in their respective locations
 * in the flowop object, the flowop's init function is called. No errors are
 * returned, but the filebench run will be terminated if the flowtype is not
 * specified, a name for the new flowop is not supplied, the flowop_define
 * call fails, or a file or fileset name is supplied but the corresponding
 * fileobj or fileset cannot be located.
 */
static void
parser_flowop_define(cmd_t *cmd, threadflow_t *thread,
    flowop_t **flowoplist_hdp, int category)
{
	flowop_t *flowop, *flowop_type;
	char *type = (char *)cmd->cmd_name;
	char *name = NULL;
	attr_t *attr;

	/* Get the inherited flowop */
	flowop_type = flowop_find(type);
	if (flowop_type == NULL) {
		filebench_log(LOG_ERROR,
		    "define flowop: flowop type %s not found",
		    type);
		filebench_shutdown(1);
	}

	/* Get the name of the flowop */
	if ((attr = get_attr(cmd, FSA_NAME))) {
		name = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "define flowop: flowop %s specifies no name",
		    flowop_type->fo_name);
		filebench_shutdown(1);
	}

	if ((flowop = flowop_define(thread, name,
	    flowop_type, flowoplist_hdp, category, 0)) == NULL) {
		filebench_log(LOG_ERROR,
		    "define flowop: Failed to instantiate flowop %s\n",
		    cmd->cmd_name);
		filebench_shutdown(1);
	}

	/* Iterations */
	if ((attr = get_attr(cmd, FSA_ITERS)))
		flowop->fo_iters = attr->attr_avd;
	else
		flowop->fo_iters = avd_int_alloc(1);


	/* if this is a use of a composit flowop, create inner FLOW MASTERS */
	if (flowop_type->fo_type == FLOW_TYPE_COMPOSITE) {
		get_attr_lvars(cmd, flowop);
		if (category == FLOW_MASTER)
			parser_inner_flowop_define(thread,
			    flowop_type, flowop);
	}
	else {
		parser_flowop_get_attrs(cmd, flowop);
	}
}

static void
parser_composite_flowop_define(cmd_t *cmd)
{
	flowop_t *flowop;
	cmd_t *inner_cmd;
	char *name = NULL;
	attr_t *attr;

	/* Get the name of the flowop */
	if ((attr = get_attr(cmd, FSA_NAME))) {
		name = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "define flowop: Composit flowop specifies no name");

		filebench_shutdown(1);
	}

	if ((flowop = flowop_new_composite_define(name)) == NULL) {
		filebench_log(LOG_ERROR,
		    "define flowop: Failed to instantiate flowop %s\n",
		    cmd->cmd_name);
		filebench_shutdown(1);
	}

	/* place any local var_t variables on the flowop's local list */
	get_attr_lvars(cmd, flowop);

	/* Iterations */
	if ((attr = get_attr(cmd, FSA_ITERS)))
		flowop->fo_iters = attr->attr_avd;
	else
		flowop->fo_iters = avd_int_alloc(1);

	/* define inner flowops */
	for (inner_cmd = cmd->cmd_list; inner_cmd != NULL;
	    inner_cmd = inner_cmd->cmd_next) {
		parser_flowop_define(inner_cmd, NULL,
		    &flowop->fo_comp_fops, FLOW_INNER_DEF);
	}
}


/*
 * First, we verify that mandatory attributes - name and path - are specified.
 * Then allocate a fileset structure and setup its fields. Notice, at this
 * point we should not verify if AVD type makes sense, because AVD type can
 * change as variables are set to other values after fileset definition.
*/
static fileset_t *
parser_fileset_define_common(cmd_t *cmd)
{
	fileset_t *fileset;
	attr_t *attr;
	avd_t name;
	avd_t path;

	attr = get_attr(cmd, FSA_NAME);
	if (attr)
		name = attr->attr_avd;
	else {
		filebench_log(LOG_ERROR, "file[set] specifies no name");
		return NULL;
	}

	attr = get_attr(cmd, FSA_PATH);
	if (attr)
		path = attr->attr_avd;
	else {
		filebench_log(LOG_ERROR, "file[set] specifies no path");
		return NULL;
	}

	fileset = fileset_define(name, path);
	if (!fileset) {
		filebench_log(LOG_ERROR, "failed to instantiate file[set] %s\n",
		    		avd_get_str(name));
		return NULL;
	}

	attr = get_attr(cmd, FSA_PREALLOC);
	if (attr)
		fileset->fs_preallocpercent = attr->attr_avd;
	else
		fileset->fs_preallocpercent = avd_int_alloc(0);

	attr = get_attr(cmd, FSA_PARALLOC);
	if (attr)
		fileset->fs_paralloc = attr->attr_avd;
	else
		fileset->fs_paralloc = avd_bool_alloc(FALSE);

	attr = get_attr(cmd, FSA_READONLY);
	if (attr)
		fileset->fs_readonly = attr->attr_avd;
	else
		fileset->fs_readonly = avd_bool_alloc(FALSE);

	attr = get_attr(cmd, FSA_WRITEONLY);
	if (attr)
		fileset->fs_writeonly = attr->attr_avd;
	else
		fileset->fs_writeonly = avd_bool_alloc(FALSE);

	attr = get_attr(cmd, FSA_REUSE);
	if (attr)
		fileset->fs_reuse = attr->attr_avd;
	else
		fileset->fs_reuse = avd_bool_alloc(FALSE);

	/* Should we check for files actual existance? */
	attr = get_attr(cmd, FSA_TRUSTTREE);
	if (attr )
		fileset->fs_trust_tree = attr->attr_avd;
	else
		fileset->fs_trust_tree = avd_bool_alloc(FALSE);

	attr = get_attr(cmd, FSA_SIZE);
	if (attr)
		fileset->fs_size = attr->attr_avd;
	else
		fileset->fs_size = avd_int_alloc(1024);

	return fileset;
}

static void
parser_file_define(cmd_t *cmd)
{
	fileset_t *fileset;

	fileset = parser_fileset_define_common(cmd);
	if (!fileset) {
		filebench_log(LOG_ERROR, "failed to instantiate file");
		filebench_shutdown(1);
		return;
	}

	/* fileset is emulating a single file */
	fileset->fs_attrs = FILESET_IS_FILE;
	fileset->fs_entries = avd_int_alloc(1);
	/* Set the mean dir width to more than 1 */
	fileset->fs_dirwidth = avd_int_alloc(10);
	fileset->fs_dirgamma = avd_int_alloc(0);
	fileset->fs_leafdirs = avd_int_alloc(0);
}

static void
parser_fileset_define(cmd_t *cmd)
{
	fileset_t *fileset;
	attr_t *attr;

	fileset = parser_fileset_define_common(cmd);
	if (!fileset) {
		filebench_log(LOG_ERROR, "failed to instantiate fileset");
		filebench_shutdown(1);
		return;
	}

	attr = get_attr(cmd, FSA_ENTRIES);
	if (attr)
		fileset->fs_entries = attr->attr_avd;
	else
		fileset->fs_entries = avd_int_alloc(0);

	attr = get_attr(cmd, FSA_LEAFDIRS);
	if (attr)
		fileset->fs_leafdirs = attr->attr_avd;
	else
		fileset->fs_leafdirs = avd_int_alloc(0);

	attr = get_attr(cmd, FSA_DIRWIDTH);
	if (attr)
		fileset->fs_dirwidth = attr->attr_avd;
	else {
		filebench_log(LOG_ERROR, "Fileset has no directory width");
		fileset->fs_dirwidth = avd_int_alloc(0);
	}

	attr = get_attr(cmd, FSA_DIRDEPTHRV);
	if (attr)
		fileset->fs_dirdepthrv = attr->attr_avd;
	else
		fileset->fs_dirdepthrv = NULL;

	attr = get_attr(cmd, FSA_DIRGAMMA);
	if (attr)
		fileset->fs_dirgamma = attr->attr_avd;
	else
		fileset->fs_dirgamma = avd_int_alloc(1500);
}

/*
 * Calls fileset_createsets() to populate all filesets and create all
 * associated, initially existant,  files and subdirectories.
 * If errors are encountered, calls filebench_shutdown() to exit Filebench.
 */
static void
parser_fileset_create(cmd_t *cmd)
{
	int ret;

	ret = fileset_createsets(); 
	if (ret) {
		filebench_log(LOG_ERROR, "Failed to create filesets");
		filebench_shutdown(1);
	}
}

/*
 * Ends filebench run after first destoring any interprocess
 * shared memory. The call to filebench_shutdown()
 * also causes filebench to exit.
 */
static void
parser_filebench_shutdown(cmd_t *cmd)
{
	int f_abort = filebench_shm->shm_f_abort;

	ipc_fini();

	if (f_abort == FILEBENCH_ABORT_ERROR)
		filebench_shutdown(1);
	else
		filebench_shutdown(0);
}

/*
 * This is used for timing runs. Pauses the master thread in one second
 * intervals until the supplied ptime runs out or the f_abort flag
 * is raised. If given a time of zero, it will pause until f_abort is raised.
 */
static int
parser_pause(int ptime)
{
	int timeslept = 0;

	if (ptime) {
		while (timeslept < ptime) {
			(void) sleep(1);
			timeslept++;
			if (filebench_shm->shm_f_abort)
				break;
		}
	} else {
		/* initial runtime of 0 means run till abort */
		/* CONSTCOND */
		while (1) {
			(void) sleep(1);
			timeslept++;
			if (filebench_shm->shm_f_abort)
				break;
		}
	}

	return (timeslept);
}

#define TIMED_RUNTIME_DEFAULT 60 /* In seconds */
#define PERIOD_DEFAULT 10 /* In seconds */

/*
 * Do a file bench run. Calls routines to create file sets, files, and
 * processes. It resets the statistics counters, then sleeps for the runtime
 * passed as an argument to it on the command line in 1 second increments.
 * When it is finished sleeping, it collects a snapshot of the statistics
 * and ends the run.
 */
static void
parser_run(cmd_t *cmd)
{
	int runtime;
	int timeslept;

	runtime = cmd->cmd_qty;

	parser_fileset_create(cmd);
	proc_create();

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Running...");
	stats_clear();

	/* If it is a timed mode and timeout is not specified use default */
	if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT && !runtime)
		runtime = TIMED_RUNTIME_DEFAULT;

	timeslept = parser_pause(runtime);

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
	stats_snap();
	proc_shutdown();
	parser_filebench_shutdown((cmd_t *)0);
}

static void
parser_psrun(cmd_t *cmd)
{
	int runtime;
	int period;
	int timeslept = 0;
	int reset_stats = 0;

	runtime = cmd->cmd_qty;

	/*
	 * If period is negative then
	 * we want to reset statistics
	 * at the end of the every period
	 */
	if (cmd->cmd_qty1 < 0) {
		period = -cmd->cmd_qty1;
		reset_stats = 1;
	} else if (cmd->cmd_qty1 > 0) {
		period = cmd->cmd_qty1;
		reset_stats = 0;
	} else { /* (cmd->cmd_qty1) == 0 */
		period = PERIOD_DEFAULT;
		reset_stats = 0;
	}

	parser_fileset_create(cmd);
	proc_create();

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Running...");
	stats_clear();

	/* If it is a timed mode and timeout is not specified use default */
	if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT && !runtime)
		runtime = TIMED_RUNTIME_DEFAULT;

	while (1) {
		/* sleep the remaining time if a period is smaller */
		if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT)
			period = period > (runtime - timeslept) ?
						(runtime - timeslept) : period;

		timeslept += parser_pause(period);

		if (filebench_shm->shm_f_abort)
			break;

		if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT &&
							timeslept >= runtime)
			break;

		stats_snap();

		if (reset_stats)
			stats_clear();
	}

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
	stats_snap();
	proc_shutdown();
	parser_filebench_shutdown((cmd_t *)0);
}

/*
 * Similar to parser_run, but gets the sleep time from a variable
 * whose name is supplied as an argument to the command.
 */
static void
parser_run_variable(cmd_t *cmd)
{
	avd_t integer = avd_var_alloc(cmd->cmd_tgt1);
	int runtime;
	int timeslept;

	if (integer == NULL) {
		filebench_log(LOG_ERROR, "Unknown variable %s",
		cmd->cmd_tgt1);
		return;
	}

	runtime = avd_get_int(integer);

	parser_fileset_create(cmd);
	proc_create();

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Running...");
	stats_clear();

	/* If it is a timed mode and timeout is not specified use default */
	if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT && !runtime)
		runtime = TIMED_RUNTIME_DEFAULT;

	timeslept = parser_pause(runtime);

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
	stats_snap();
	proc_shutdown();
	parser_filebench_shutdown((cmd_t *)0);
}

/*
 * Establishes multi-client synchronization socket with synch server.
 */
static void
parser_enable_mc(cmd_t *cmd)
{
	attr_t *attr;
	char *master;
	char *client;

	if ((attr = get_attr(cmd, FSA_MASTER))) {
		master = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "enable multi: no master specified");
		return;
	}

	if ((attr = get_attr(cmd, FSA_CLIENT))) {
		client = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "enable multi: no client specified");
		return;
	}

	mc_sync_open_sock(master, 8001, client);
}

/*
 * Exchanges multi-client synchronization message with synch server.
 */
static void
parser_domultisync(cmd_t *cmd)
{
	attr_t *attr;
	fbint_t value;

	if ((attr = get_attr(cmd, FSA_VALUE)))
		value = avd_get_int(attr->attr_avd);
	else
		value = 1;

	mc_sync_synchronize((int)value);
}

/*
 * Sleeps for cmd->cmd_qty seconds, one second at a time.
 */
static void
parser_sleep(cmd_t *cmd)
{
	int sleeptime;
	int timeslept;

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	sleeptime = cmd->cmd_qty;
	filebench_log(LOG_INFO, "Sleeping...");

	timeslept = parser_pause(sleeptime);

	filebench_log(LOG_INFO, "Slept for %d seconds...", timeslept);
}

/*
 * Same as parser_sleep, except the sleep time is obtained from a variable
 * whose name is passed to it as an argument on the command line.
 */
static void
parser_sleep_variable(cmd_t *cmd)
{
	avd_t integer = avd_var_alloc(cmd->cmd_tgt1);
	int sleeptime;
	int timeslept;

	if (integer == NULL) {
		filebench_log(LOG_ERROR, "Unknown variable %s",
		cmd->cmd_tgt1);
		return;
	}

	sleeptime = avd_get_int(integer);

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Running...");

	timeslept = parser_pause(sleeptime);

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
}

/*
 * Launches a shell to run the unix command supplied in the argument.
 * The command should be enclosed in quotes, as in:
 * 	system "rm xyz"
 * which would run the "rm" utility to delete the file "xyz".
 */
static void
parser_system(cmd_t *cmd)
{
	char *string;

	if (!cmd->cmd_param_list)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (!string)
		return;

	filebench_log(LOG_VERBOSE, "Running '%s'", string);

	if (system(string) < 0) {
		filebench_log(LOG_ERROR,
		    "system exec failed: %s",
		    strerror(errno));
		free(string);
		filebench_shutdown(1);
	}

	free(string);
}

/*
 * Echos string supplied with command to the log.
 */
static void
parser_echo(cmd_t *cmd)
{
	char *string;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	filebench_log(LOG_INFO, "%s", string);
}

/*
 * Prints out the version of Filebench.
 */
static void
parser_version(cmd_t *cmd)
{
	filebench_log(LOG_INFO, "Filebench Version: %s", FILEBENCH_VERSION);
}

static void
parser_enable_lathist(cmd_t *cmd)
{
	filebench_shm->lathist_enabled = 1;
	filebench_log(LOG_INFO, "Latency histogram enabled");
}

/*
 * define a random variable and initialize the distribution parameters
 */
static void
parser_var_assign_random(char *name, cmd_t *cmd)
{
	randdist_t	*rndp;
	attr_t		*attr;

	rndp = randdist_alloc();
	if (!rndp) {
		filebench_log(LOG_ERROR,
			"failed to alloc random distribution object\n");
		return;
	}

	rndp->rnd_type = 0;

	/* Get the source of the random numbers */
	if ((attr = get_attr(cmd, FSA_RANDSRC))) {
		int randsrc = (int)avd_get_int(attr->attr_avd);

		switch (randsrc) {
		case FSV_URAND:
			rndp->rnd_type |= RAND_SRC_URANDOM;
			break;
		case FSV_RAND48:
			rndp->rnd_type |= RAND_SRC_GENERATOR;
			break;
		}
	} else {
		/* default to rand48 random number generator */
		rndp->rnd_type |= RAND_SRC_GENERATOR;
	}

	/* Get the min value of the random distribution */
	if ((attr = get_attr(cmd, FSA_MIN)))
		rndp->rnd_min = attr->attr_avd;
	else
		rndp->rnd_min = avd_int_alloc(0);

	/* Get the roundoff value for the random distribution */
	if ((attr = get_attr(cmd, FSA_ROUND)))
		rndp->rnd_round = attr->attr_avd;
	else
		rndp->rnd_round = avd_int_alloc(0);

	/* Get a tablular probablility distribution if there is one */
	if ((attr = get_attr(cmd, FSA_RANDTABLE))) {
		rndp->rnd_probtabs = (probtabent_t *)(attr->attr_obj);
		rndp->rnd_type |= RAND_TYPE_TABLE;

		/* no need for the rest of the attributes */
		goto randdist_init;
	} else {
		rndp->rnd_probtabs = NULL;
	}

	/* Get the type for the random variable */
	if ((attr = get_attr(cmd, FSA_TYPE))) {
		int disttype = (int)avd_get_int(attr->attr_avd);

		switch (disttype) {
		case FSV_RANDUNI:
			rndp->rnd_type |= RAND_TYPE_UNIFORM;
			break;
		case FSA_RANDGAMMA:
			rndp->rnd_type |= RAND_TYPE_GAMMA;
			break;
		case FSV_RANDTAB:
			filebench_log(LOG_ERROR,
			    "Table distribution type without prob table");
			break;
		}
	} else {
		/* default to gamma distribution type */
		rndp->rnd_type |= RAND_TYPE_GAMMA;
	}

	/* Get the seed for the random variable */
	if ((attr = get_attr(cmd, FSA_RANDSEED)))
		rndp->rnd_seed = attr->attr_avd;
	else
		rndp->rnd_seed = avd_int_alloc(0);

	/* Get the gamma value of the random distribution */
	if ((attr = get_attr(cmd, FSA_RANDGAMMA)))
		rndp->rnd_gamma = attr->attr_avd;
	else
		rndp->rnd_gamma = avd_int_alloc(1500);

	/* Get the mean value of the random distribution */
	if ((attr = get_attr(cmd, FSA_RANDMEAN))) {
		rndp->rnd_mean = attr->attr_avd;
	} else if ((rndp->rnd_type & RAND_TYPE_MASK) == RAND_TYPE_GAMMA) {
		rndp->rnd_mean = NULL;
	} else {
		rndp->rnd_mean = avd_int_alloc(0);
	}

	var_assign_random(name, rndp);

randdist_init:
	randdist_init(rndp);
}

/*
 * alloc_cmd() allocates the required resources for a cmd_t. On failure, a
 * filebench_log is issued and NULL is returned.
 */
static cmd_t *
alloc_cmd(void)
{
	cmd_t *cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd) {
		filebench_log(LOG_ERROR, "Alloc cmd failed");
		return NULL;
	}

	memset(cmd, 0, sizeof (cmd_t));

	return cmd;
}

/*
 * Allocates an attr_t structure and zeros it. Returns NULL on failure, or
 * a pointer to the attr_t.
 */
static attr_t *
alloc_attr(void)
{
	attr_t *attr;

	attr = malloc(sizeof(*attr));
	if (!attr)
		return (NULL);

	(void) memset(attr, 0, sizeof(*attr));

	return (attr);
}

/*
 * Allocates a probtabent_t structure and zeros it. Returns NULL on failure, or
 * a pointer to the probtabent_t.
 */
static probtabent_t *
alloc_probtabent(void)
{
	probtabent_t *rte;

	if ((rte = malloc(sizeof (probtabent_t))) == NULL) {
		return (NULL);
	}

	(void) memset(rte, 0, sizeof (probtabent_t));
	return (rte);
}

/*
 * Allocates an attr_t structure and puts the supplied var_t into
 * its attr_avd location, and sets its name to FSA_LVAR_ASSIGN
 */
static attr_t *
alloc_lvar_attr(var_t *var)
{
	attr_t *attr;

	if ((attr = alloc_attr()) == NULL)
		return (NULL);

	attr->attr_name = FSA_LVAR_ASSIGN;
	attr->attr_avd = (avd_t)var;

	return (attr);
}

/*
 * Searches the attribute list for the command for the named attribute type.
 * The attribute list is created by the parser from the list of attributes
 * supplied with certain commands, such as the define and flowop commands.
 * Returns a pointer to the attribute structure if the named attribute is
 * found, otherwise returns NULL. If the attribute includes a parameter list,
 * the list is converted to a string and stored in the attr_avd field of
 * the returned attr_t struct.
 */
static attr_t *
get_attr(cmd_t *cmd, int64_t name)
{
	attr_t *attr;
	attr_t *rtn = NULL;

	for (attr = cmd->cmd_attr_list; attr != NULL;
	    attr = attr->attr_next) {

		filebench_log(LOG_DEBUG_IMPL,
		    "attr %d = %d %llx?",
		    attr->attr_name,
		    name,
		    attr->attr_avd);

		if (attr->attr_name == name)
			rtn = attr;
	}

	return rtn;
}

/*
 * removes the newly allocated local var from the shared local var
 * list, then puts it at the head of the private local var list
 * supplied as the second argument.
 */
static void
add_lvar_to_list(var_t *newlvar, var_t **lvar_list)
{
	var_t *prev;

	/* remove from shared local list, if there */
	if (newlvar == filebench_shm->shm_var_loc_list) {
		/* on top of list, just grap */
		filebench_shm->shm_var_loc_list = newlvar->var_next;
	} else {
		/* find newvar on list and remove */
		for (prev = filebench_shm->shm_var_loc_list; prev;
		    prev = prev->var_next) {
			if (prev->var_next == newlvar)
				prev->var_next = newlvar->var_next;
		}
	}
	newlvar->var_next = NULL;

	/* add to flowop private local list at head */
	newlvar->var_next = *lvar_list;
	*lvar_list = newlvar;
}

/*
 * Searches the attribute list for the command for any allocated local
 * variables. The attribute list is created by the parser from the list of
 * attributes supplied with certain commands, such as the define and flowop
 * commands. Places all found local vars onto the flowop's local variable
 * list.
 */
static void
get_attr_lvars(cmd_t *cmd, flowop_t *flowop)
{
	attr_t *attr;
	var_t *orig_lvar_list;

	/* save the local var list */
	orig_lvar_list = flowop->fo_lvar_list;

	for (attr = cmd->cmd_attr_list; attr != NULL;
	    attr = attr->attr_next) {

		if (attr->attr_name == FSA_LVAR_ASSIGN) {
			var_t *newvar;

			if ((newvar = (var_t *)attr->attr_avd) == NULL)
				continue;

			add_lvar_to_list(newvar, &flowop->fo_lvar_list);
			var_update_comp_lvars(newvar, orig_lvar_list, NULL);
		}
	}
}

/*
 * Allocates memory for a list_t structure, initializes it to zero, and
 * returns a pointer to it. On failure, returns NULL.
 */
static list_t *
alloc_list()
{
	list_t *list;

	if ((list = malloc(sizeof (list_t))) == NULL) {
		return (NULL);
	}

	(void) memset(list, 0, sizeof (list_t));
	return (list);
}

/*
 * Define a custom variable and validate its parameters.
 * TODO: Clean up state when things go wrong.
 */
static void
parser_var_assign_custom(char *name, cmd_t *cmd)
{
	cvar_t	*cvar;
	attr_t	*attr;
	char	*type;
	char	*parameters;
	int 	ret;

	attr = get_attr(cmd, FSA_TYPE);
	if (attr)
		type = avd_get_str(attr->attr_avd);
	else {
		filebench_log(LOG_ERROR, "define cvar: no type specified");
		filebench_shutdown(1);
		return;
	}

	cvar = cvar_alloc();
	if (!cvar) {
		filebench_log(LOG_ERROR, "Failed to allocate custom variable");
		filebench_shutdown(1);
		return;
	}

	/* Initialize the custom variable mutex. */
	(void) pthread_mutex_init(&cvar->cvar_lock,
			ipc_mutexattr(IPC_MUTEX_NORMAL));

	/* Get the min, max and round values for the custom variable. */
	if ((attr = get_attr(cmd, FSA_MIN)))
		cvar->min = avd_get_dbl(attr->attr_avd);
	else
		cvar->min = DBL_MIN;

	if ((attr = get_attr(cmd, FSA_MAX)))
		cvar->max = avd_get_dbl(attr->attr_avd);
	else
		cvar->max = DBL_MAX;

	if ((attr = get_attr(cmd, FSA_ROUND)))
		cvar->round = avd_get_dbl(attr->attr_avd);
	else
		cvar->round = 0;

	attr = get_attr(cmd, FSA_PARAMETERS);
	if (attr)
		parameters = avd_get_str(attr->attr_avd);
	else
		parameters = NULL;

	ret = init_cvar_handle(cvar, type, parameters);
	if (ret) {
		filebench_log(LOG_FATAL, "define cvar: failed for custom variable %s",
		    name);
		filebench_shutdown(1);
		return;
	}

	var_assign_custom(name, cvar);
}
#line 2775 "parser_gram.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 192 "parser_gram.y"
	{
	if (yystack.l_mark[0].cmd->cmd)
		yystack.l_mark[0].cmd->cmd(yystack.l_mark[0].cmd);

	free(yystack.l_mark[0].cmd);
}
break;
case 2:
#line 199 "parser_gram.y"
	{
	YYABORT;
}
break;
case 21:
#line 224 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = &parser_eventgen;
}
break;
case 22:
#line 230 "parser_gram.y"
	{
	yystack.l_mark[-1].cmd->cmd_attr_list = yystack.l_mark[0].attr;
}
break;
case 23:
#line 235 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;

	yyval.cmd->cmd_param_list = yystack.l_mark[0].list;
	yyval.cmd->cmd = parser_system;
}
break;
case 24:
#line 244 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;

	yyval.cmd->cmd_param_list = yystack.l_mark[0].list;
	yyval.cmd->cmd = parser_echo;
}
break;
case 25:
#line 253 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = parser_version;
}
break;
case 26:
#line 260 "parser_gram.y"
	{

	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;

	yyval.cmd->cmd = parser_enable_mc;
	yyval.cmd->cmd_attr_list = yystack.l_mark[0].attr;
}
break;
case 27:
#line 269 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;

	yyval.cmd->cmd = parser_enable_lathist;
}
break;
case 28:
#line 277 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;

	yyval.cmd->cmd = parser_domultisync;
	yyval.cmd->cmd_attr_list = yystack.l_mark[0].attr;
}
break;
case 29:
#line 286 "parser_gram.y"
	{
	if ((yyval.list = alloc_list()) == NULL)
			YYERROR;

	yyval.list->list_string = avd_str_alloc(yystack.l_mark[0].sval);
}
break;
case 30:
#line 293 "parser_gram.y"
	{
	if ((yyval.list = alloc_list()) == NULL)
			YYERROR;

	yyval.list->list_string = avd_str_alloc(yystack.l_mark[0].sval);
}
break;
case 31:
#line 301 "parser_gram.y"
	{
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add string */
	if ((yyval.list = alloc_list()) == NULL)
		YYERROR;

	yyval.list->list_string = avd_str_alloc(yystack.l_mark[0].sval);

	/* Find end of list */
	for (list = yystack.l_mark[-1].list; list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = yyval.list;
	yyval.list = yystack.l_mark[-1].list;

}
break;
case 32:
#line 319 "parser_gram.y"
	{
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add variable */
	if ((yyval.list = alloc_list()) == NULL)
		YYERROR;

	yyval.list->list_string = avd_str_alloc(yystack.l_mark[0].sval);

	/* Find end of list */
	for (list = yystack.l_mark[-1].list; list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = yyval.list;
	yyval.list = yystack.l_mark[-1].list;
}
break;
case 33:
#line 336 "parser_gram.y"
	{
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add string */
	if ((yyval.list = alloc_list()) == NULL)
		YYERROR;

	yyval.list->list_string = avd_str_alloc(yystack.l_mark[0].sval);

	/* Find end of list */
	for (list = yystack.l_mark[-1].list; list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = yyval.list;
	yyval.list = yystack.l_mark[-1].list;

}
break;
case 34:
#line 354 "parser_gram.y"
	{
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add variable */
	if ((yyval.list = alloc_list()) == NULL)
		YYERROR;

	yyval.list->list_string = avd_str_alloc(yystack.l_mark[0].sval);

	/* Find end of list */
	for (list = yystack.l_mark[-1].list; list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = yyval.list;
	yyval.list = yystack.l_mark[-1].list;
}
break;
case 35:
#line 371 "parser_gram.y"
	{
	yyval.list = yystack.l_mark[-1].list;
}
break;
case 36:
#line 374 "parser_gram.y"
	{
	yyval.list = yystack.l_mark[-1].list;
}
break;
case 37:
#line 379 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = &parser_fileset_list;
}
break;
case 38:
#line 385 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = &parser_flowop_list;
}
break;
case 39:
#line 392 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = NULL;
	filebench_shm->shm_debug_level = yystack.l_mark[0].ival;
	if (filebench_shm->shm_debug_level > 10) {
		filebench_log(LOG_ERROR, "Debug level set out of range."
					"  Adjusting to 10.");
			filebench_shm->shm_debug_level = 10;
		}
	if (filebench_shm->shm_debug_level > 9)
		yydebug = 1;
}
break;
case 44:
#line 409 "parser_gram.y"
	{
	yyval.cmd = alloc_cmd();
	if (!yyval.cmd)
		YYERROR;

	var_assign_integer(yystack.l_mark[-2].sval, yystack.l_mark[0].ival);

	yyval.cmd->cmd = NULL;
}
break;
case 45:
#line 420 "parser_gram.y"
	{
	yyval.cmd = alloc_cmd();
	if (!yyval.cmd)
		YYERROR;

	var_assign_boolean(yystack.l_mark[-2].sval, yystack.l_mark[0].bval);

	yyval.cmd->cmd = NULL;
}
break;
case 46:
#line 430 "parser_gram.y"
	{
	yyval.cmd = alloc_cmd();
	if (!yyval.cmd)
		YYERROR;

	var_assign_string(yystack.l_mark[-4].sval, yystack.l_mark[-1].sval);

	yyval.cmd->cmd = NULL;
}
break;
case 47:
#line 440 "parser_gram.y"
	{
	yyval.cmd = alloc_cmd();
	if (!yyval.cmd)
		YYERROR;

	var_assign_string(yystack.l_mark[-2].sval, yystack.l_mark[0].sval);

	yyval.cmd->cmd = NULL;
}
break;
case 48:
#line 451 "parser_gram.y"
	{
	yyval.cmd = alloc_cmd();
	if (!yyval.cmd)
		YYERROR;

	yyval.cmd->cmd_attr_list = yystack.l_mark[-1].attr;
	yyval.cmd->cmd = NULL;

	parser_var_assign_random(yystack.l_mark[-5].sval, yyval.cmd);
}
break;
case 49:
#line 463 "parser_gram.y"
	{
	yyval.cmd = alloc_cmd();
	if (!yyval.cmd)
		YYERROR;

	yyval.cmd->cmd_attr_list = yystack.l_mark[-1].attr;
	yyval.cmd->cmd = NULL;

	parser_var_assign_custom(yystack.l_mark[-5].sval, yyval.cmd);
}
break;
case 50:
#line 475 "parser_gram.y"
	{
	yyval.cmd = alloc_cmd();
	if (!yyval.cmd)
		YYERROR;

	filebench_shm->shm_rmode = FILEBENCH_MODE_TIMEOUT;

	yyval.cmd->cmd = NULL;
}
break;
case 51:
#line 485 "parser_gram.y"
	{
	yyval.cmd = alloc_cmd();
	if (!yyval.cmd)
		YYERROR;

	filebench_shm->shm_rmode = FILEBENCH_MODE_QALLDONE;

	yyval.cmd->cmd = NULL;
}
break;
case 52:
#line 495 "parser_gram.y"
	{
	yyval.cmd = alloc_cmd();
	if (!yyval.cmd)
		YYERROR;

	filebench_shm->shm_rmode = FILEBENCH_MODE_Q1STDONE;

	yyval.cmd->cmd = NULL;
}
break;
case 53:
#line 505 "parser_gram.y"
	{
	yyval.cmd = alloc_cmd();
	if (!yyval.cmd)
		YYERROR;

	filebench_log(LOG_INFO, "Disabling CPU usage statistics");
	filebench_shm->shm_mmode |= FILEBENCH_MODE_NOUSAGE;

	yyval.cmd->cmd = NULL;
}
break;
case 54:
#line 517 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = parser_filebench_shutdown;
}
break;
case 55:
#line 524 "parser_gram.y"
	{
	yyval.cmd = yystack.l_mark[0].cmd;
}
break;
case 56:
#line 527 "parser_gram.y"
	{
	cmd_t *list = NULL;
	cmd_t *list_end = NULL;

	/* Find end of list */
	for (list = yystack.l_mark[-1].cmd; list != NULL;
	    list = list->cmd_next)
		list_end = list;

	list_end->cmd_next = yystack.l_mark[0].cmd;

	filebench_log(LOG_DEBUG_IMPL,
	    "flowop_list adding cmd %zx to list %zx", yystack.l_mark[0].cmd, yystack.l_mark[-1].cmd);

	yyval.cmd = yystack.l_mark[-1].cmd;
}
break;
case 57:
#line 545 "parser_gram.y"
	{
	/*
	 * Allocate a cmd node per thread, with a
	 * list of flowops attached to the cmd_list
	 */
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd_list = yystack.l_mark[-1].cmd;
	yyval.cmd->cmd_attr_list = yystack.l_mark[-3].attr;
}
break;
case 58:
#line 557 "parser_gram.y"
	{
	yyval.cmd = yystack.l_mark[0].cmd;
}
break;
case 59:
#line 560 "parser_gram.y"
	{
	cmd_t *list = NULL;
	cmd_t *list_end = NULL;

	/* Find end of list */
	for (list = yystack.l_mark[-1].cmd; list != NULL;
	    list = list->cmd_next)
		list_end = list;

	list_end->cmd_next = yystack.l_mark[0].cmd;

	filebench_log(LOG_DEBUG_IMPL,
	    "thread_list adding cmd %zx to list %zx", yystack.l_mark[0].cmd, yystack.l_mark[-1].cmd);

	yyval.cmd = yystack.l_mark[-1].cmd;
}
break;
case 60:
#line 578 "parser_gram.y"
	{
	yyval.cmd = alloc_cmd();
	if (!yyval.cmd)
		YYERROR;
	yyval.cmd->cmd = &parser_proc_define;
	yyval.cmd->cmd_list = yystack.l_mark[-1].cmd;
	yyval.cmd->cmd_attr_list = yystack.l_mark[-3].attr;
}
break;
case 61:
#line 588 "parser_gram.y"
	{
	yyval.cmd = alloc_cmd();
	if (!yyval.cmd)
		YYERROR;

	yyval.cmd->cmd = &parser_file_define;
	yyval.cmd->cmd_attr_list = yystack.l_mark[0].attr;
}
break;
case 62:
#line 596 "parser_gram.y"
	{
	yyval.cmd = alloc_cmd();
	if (!yyval.cmd)
		YYERROR;

	yyval.cmd->cmd = &parser_fileset_define;
	yyval.cmd->cmd_attr_list = yystack.l_mark[0].attr;
}
break;
case 63:
#line 606 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;

	yyval.cmd->cmd = &parser_fileset_create;
}
break;
case 64:
#line 614 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = parser_sleep;
	yyval.cmd->cmd_qty = yystack.l_mark[0].ival;
}
break;
case 65:
#line 621 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = parser_sleep_variable;
	yyval.cmd->cmd_tgt1 = fb_stralloc(yystack.l_mark[0].sval);
}
break;
case 66:
#line 629 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = parser_run;
	yyval.cmd->cmd_qty = yystack.l_mark[0].ival;
}
break;
case 67:
#line 636 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = parser_run_variable;
	yyval.cmd->cmd_tgt1 = fb_stralloc(yystack.l_mark[0].sval);
}
break;
case 68:
#line 643 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = parser_run;
	yyval.cmd->cmd_qty = 0;
}
break;
case 69:
#line 651 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = parser_psrun;
	yyval.cmd->cmd_qty1 = 0;
	yyval.cmd->cmd_qty = 0;
}
break;
case 70:
#line 659 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = parser_psrun;
	yyval.cmd->cmd_qty1 = yystack.l_mark[0].ival;
	yyval.cmd->cmd_qty = 0;

}
break;
case 71:
#line 668 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = parser_psrun;
	yyval.cmd->cmd_qty1 = yystack.l_mark[0].ival;
	yyval.cmd->cmd_qty = 0;

}
break;
case 72:
#line 677 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = parser_psrun;
	yyval.cmd->cmd_qty1 = yystack.l_mark[-1].ival;
	yyval.cmd->cmd_qty = yystack.l_mark[0].ival;
}
break;
case 73:
#line 685 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = parser_psrun;
	yyval.cmd->cmd_qty1 = yystack.l_mark[-1].ival;
	yyval.cmd->cmd_qty = yystack.l_mark[0].ival;
}
break;
case 74:
#line 694 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd_name = fb_stralloc(yystack.l_mark[0].sval);
}
break;
case 75:
#line 700 "parser_gram.y"
	{
	yystack.l_mark[-1].cmd->cmd_attr_list = yystack.l_mark[0].attr;
}
break;
case 77:
#line 707 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
}
break;
case 78:
#line 711 "parser_gram.y"
	{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = yystack.l_mark[-2].attr; attr; attr = attr->attr_next)
		list_end = attr;

	list_end->attr_next = yystack.l_mark[0].attr;

	yyval.attr = yystack.l_mark[-2].attr;
}
break;
case 79:
#line 724 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
}
break;
case 80:
#line 728 "parser_gram.y"
	{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = yystack.l_mark[-2].attr; attr; attr = attr->attr_next)
		list_end = attr;

	list_end->attr_next = yystack.l_mark[0].attr;

	yyval.attr = yystack.l_mark[-2].attr;
}
break;
case 81:
#line 741 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
	yyval.attr->attr_name = yystack.l_mark[-2].ival;
}
break;
case 82:
#line 746 "parser_gram.y"
	{
	yyval.attr = alloc_attr();
	if (!yyval.attr)
		YYERROR;

	yyval.attr->attr_name = yystack.l_mark[0].ival;
	yyval.attr->attr_avd = avd_bool_alloc(TRUE);
}
break;
case 83:
#line 756 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
	yyval.attr->attr_name = yystack.l_mark[-2].ival;
}
break;
case 84:
#line 761 "parser_gram.y"
	{
	yyval.attr = alloc_attr();
	if (!yyval.attr)
		YYERROR;

	yyval.attr->attr_name = yystack.l_mark[0].ival;
	yyval.attr->attr_avd = avd_bool_alloc(TRUE);
}
break;
case 85:
#line 772 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
}
break;
case 86:
#line 776 "parser_gram.y"
	{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = yystack.l_mark[-2].attr; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = yystack.l_mark[0].attr;

	yyval.attr = yystack.l_mark[-2].attr;
}
break;
case 87:
#line 789 "parser_gram.y"
	{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = yystack.l_mark[-6].attr; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */


	if ((attr = alloc_attr()) == NULL)
		YYERROR;

	attr->attr_name = FSA_RANDTABLE;
	attr->attr_obj = (void *)yystack.l_mark[-1].rndtb;
	list_end->attr_next = attr;
	yyval.attr = yystack.l_mark[-6].attr;
}
break;
case 88:
#line 808 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
	yyval.attr->attr_name = yystack.l_mark[-2].ival;
}
break;
case 89:
#line 813 "parser_gram.y"
	{
	if ((yyval.attr = alloc_attr()) == NULL)
		YYERROR;
	yyval.attr->attr_name = yystack.l_mark[0].ival;
	yyval.attr->attr_avd = avd_bool_alloc(TRUE);
}
break;
case 90:
#line 820 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
	yyval.attr->attr_name = FSA_TYPE;
}
break;
case 91:
#line 825 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
	yyval.attr->attr_name = FSA_RANDSRC;
}
break;
case 92:
#line 831 "parser_gram.y"
	{
	if ((yyval.rndtb = alloc_probtabent()) == NULL)
		YYERROR;
	yyval.rndtb->pte_percent = yystack.l_mark[-5].avd;
	yyval.rndtb->pte_segmin  = yystack.l_mark[-3].avd;
	yyval.rndtb->pte_segmax  = yystack.l_mark[-1].avd;
}
break;
case 93:
#line 841 "parser_gram.y"
	{
	yyval.rndtb = yystack.l_mark[0].rndtb;
}
break;
case 94:
#line 845 "parser_gram.y"
	{
	probtabent_t *pte = NULL;
	probtabent_t *ptelist_end = NULL;

	for (pte = yystack.l_mark[-2].rndtb; pte != NULL;
	    pte = pte->pte_next)
		ptelist_end = pte; /* Find end of prob table entry list */

	ptelist_end->pte_next = yystack.l_mark[0].rndtb;

	yyval.rndtb = yystack.l_mark[-2].rndtb;
}
break;
case 95:
#line 859 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
}
break;
case 96:
#line 863 "parser_gram.y"
	{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = yystack.l_mark[-2].attr; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = yystack.l_mark[0].attr;

	yyval.attr = yystack.l_mark[-2].attr;
}
break;
case 97:
#line 877 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
	yyval.attr->attr_name = yystack.l_mark[-2].ival;
}
break;
case 98:
#line 882 "parser_gram.y"
	{
	yyval.attr = alloc_attr();
	if (!yyval.attr)
		YYERROR;
	yyval.attr->attr_name = yystack.l_mark[0].ival;
	yyval.attr->attr_avd = avd_bool_alloc(TRUE);
}
break;
case 99:
#line 892 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
}
break;
case 100:
#line 896 "parser_gram.y"
	{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = yystack.l_mark[-2].attr; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = yystack.l_mark[0].attr;

	yyval.attr = yystack.l_mark[-2].attr;
}
break;
case 101:
#line 910 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
	yyval.attr->attr_name = yystack.l_mark[-2].ival;
}
break;
case 102:
#line 915 "parser_gram.y"
	{
	if ((yyval.attr = alloc_attr()) == NULL)
		YYERROR;
	yyval.attr->attr_name = yystack.l_mark[0].ival;
	yyval.attr->attr_avd = avd_bool_alloc(TRUE);
}
break;
case 103:
#line 924 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
}
break;
case 104:
#line 928 "parser_gram.y"
	{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = yystack.l_mark[-2].attr; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = yystack.l_mark[0].attr;

	yyval.attr = yystack.l_mark[-2].attr;
}
break;
case 105:
#line 941 "parser_gram.y"
	{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = yystack.l_mark[-2].attr; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = yystack.l_mark[0].attr;

	yyval.attr = yystack.l_mark[-2].attr;
}
break;
case 106:
#line 955 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
	yyval.attr->attr_name = yystack.l_mark[-2].ival;
}
break;
case 107:
#line 960 "parser_gram.y"
	{
	if ((yyval.attr = alloc_attr()) == NULL)
		YYERROR;
	yyval.attr->attr_name = yystack.l_mark[0].ival;
	yyval.attr->attr_avd = avd_bool_alloc(TRUE);
}
break;
case 108:
#line 969 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
}
break;
case 109:
#line 973 "parser_gram.y"
	{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = yystack.l_mark[-2].attr; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = yystack.l_mark[0].attr;

	yyval.attr = yystack.l_mark[-2].attr;
}
break;
case 110:
#line 987 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
	yyval.attr->attr_name = yystack.l_mark[-2].ival;
}
break;
case 111:
#line 992 "parser_gram.y"
	{
	if ((yyval.attr = alloc_attr()) == NULL)
		YYERROR;
	yyval.attr->attr_name = yystack.l_mark[0].ival;
	yyval.attr->attr_avd = avd_bool_alloc(TRUE);
}
break;
case 112:
#line 1001 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
}
break;
case 113:
#line 1005 "parser_gram.y"
	{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = yystack.l_mark[-2].attr; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = yystack.l_mark[0].attr;

	yyval.attr = yystack.l_mark[-2].attr;
}
break;
case 114:
#line 1019 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
	yyval.attr->attr_name = yystack.l_mark[-2].ival;
}
break;
case 115:
#line 1025 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
	yyval.attr->attr_name = FSA_VALUE;
}
break;
case 116:
#line 1034 "parser_gram.y"
	{ yyval.ival = FSA_NAME;}
break;
case 117:
#line 1035 "parser_gram.y"
	{ yyval.ival = FSA_INSTANCES;}
break;
case 118:
#line 1036 "parser_gram.y"
	{ yyval.ival = FSA_NICE;}
break;
case 119:
#line 1039 "parser_gram.y"
	{ yyval.ival = FSA_NAME;}
break;
case 120:
#line 1040 "parser_gram.y"
	{ yyval.ival = FSA_PATH;}
break;
case 121:
#line 1041 "parser_gram.y"
	{ yyval.ival = FSA_SIZE;}
break;
case 122:
#line 1042 "parser_gram.y"
	{ yyval.ival = FSA_PREALLOC;}
break;
case 123:
#line 1043 "parser_gram.y"
	{ yyval.ival = FSA_PARALLOC;}
break;
case 124:
#line 1044 "parser_gram.y"
	{ yyval.ival = FSA_REUSE;}
break;
case 125:
#line 1045 "parser_gram.y"
	{ yyval.ival = FSA_TRUSTTREE;}
break;
case 126:
#line 1046 "parser_gram.y"
	{ yyval.ival = FSA_READONLY;}
break;
case 127:
#line 1047 "parser_gram.y"
	{ yyval.ival = FSA_WRITEONLY;}
break;
case 128:
#line 1050 "parser_gram.y"
	{ yyval.ival = FSA_NAME;}
break;
case 129:
#line 1051 "parser_gram.y"
	{ yyval.ival = FSA_PATH;}
break;
case 130:
#line 1052 "parser_gram.y"
	{ yyval.ival = FSA_ENTRIES;}
break;
case 131:
#line 1053 "parser_gram.y"
	{ yyval.ival = FSA_SIZE;}
break;
case 132:
#line 1054 "parser_gram.y"
	{ yyval.ival = FSA_PREALLOC;}
break;
case 133:
#line 1055 "parser_gram.y"
	{ yyval.ival = FSA_PARALLOC;}
break;
case 134:
#line 1056 "parser_gram.y"
	{ yyval.ival = FSA_REUSE;}
break;
case 135:
#line 1057 "parser_gram.y"
	{ yyval.ival = FSA_TRUSTTREE;}
break;
case 136:
#line 1058 "parser_gram.y"
	{ yyval.ival = FSA_READONLY;}
break;
case 137:
#line 1059 "parser_gram.y"
	{ yyval.ival = FSA_WRITEONLY;}
break;
case 138:
#line 1060 "parser_gram.y"
	{ yyval.ival = FSA_DIRWIDTH;}
break;
case 139:
#line 1061 "parser_gram.y"
	{ yyval.ival = FSA_DIRDEPTHRV;}
break;
case 140:
#line 1062 "parser_gram.y"
	{ yyval.ival = FSA_DIRGAMMA;}
break;
case 141:
#line 1063 "parser_gram.y"
	{ yyval.ival = FSA_LEAFDIRS;}
break;
case 142:
#line 1066 "parser_gram.y"
	{ yyval.ival = FSA_NAME;}
break;
case 143:
#line 1067 "parser_gram.y"
	{ yyval.ival = FSA_RANDSEED;}
break;
case 144:
#line 1068 "parser_gram.y"
	{ yyval.ival = FSA_RANDGAMMA;}
break;
case 145:
#line 1069 "parser_gram.y"
	{ yyval.ival = FSA_RANDMEAN;}
break;
case 146:
#line 1070 "parser_gram.y"
	{ yyval.ival = FSA_MIN;}
break;
case 147:
#line 1071 "parser_gram.y"
	{ yyval.ival = FSA_ROUND;}
break;
case 148:
#line 1074 "parser_gram.y"
	{
	if ((yyval.attr = alloc_attr()) == NULL)
		YYERROR;
	yyval.attr->attr_avd = avd_int_alloc(yystack.l_mark[0].ival);
}
break;
case 149:
#line 1081 "parser_gram.y"
	{ yyval.ival = FSV_RANDUNI;}
break;
case 150:
#line 1082 "parser_gram.y"
	{ yyval.ival = FSV_RANDTAB;}
break;
case 151:
#line 1083 "parser_gram.y"
	{ yyval.ival = FSA_RANDGAMMA;}
break;
case 152:
#line 1086 "parser_gram.y"
	{
	if ((yyval.attr = alloc_attr()) == NULL)
		YYERROR;
	yyval.attr->attr_avd = avd_int_alloc(yystack.l_mark[0].ival);
}
break;
case 153:
#line 1093 "parser_gram.y"
	{ yyval.ival = FSV_URAND;}
break;
case 154:
#line 1094 "parser_gram.y"
	{ yyval.ival = FSV_RAND48;}
break;
case 155:
#line 1097 "parser_gram.y"
	{ yyval.ival = FSA_TYPE;}
break;
case 156:
#line 1098 "parser_gram.y"
	{ yyval.ival = FSA_PARAMETERS;}
break;
case 157:
#line 1099 "parser_gram.y"
	{ yyval.ival = FSA_MIN;}
break;
case 158:
#line 1100 "parser_gram.y"
	{ yyval.ival = FSA_MAX;}
break;
case 159:
#line 1101 "parser_gram.y"
	{ yyval.ival = FSA_ROUND;}
break;
case 160:
#line 1104 "parser_gram.y"
	{ yyval.ival = FSA_NAME;}
break;
case 161:
#line 1105 "parser_gram.y"
	{ yyval.ival = FSA_MEMSIZE;}
break;
case 162:
#line 1106 "parser_gram.y"
	{ yyval.ival = FSA_USEISM;}
break;
case 163:
#line 1107 "parser_gram.y"
	{ yyval.ival = FSA_INSTANCES;}
break;
case 164:
#line 1108 "parser_gram.y"
	{ yyval.ival = FSA_IOPRIO;}
break;
case 165:
#line 1111 "parser_gram.y"
	{ yyval.ival = FSA_WSS;}
break;
case 166:
#line 1112 "parser_gram.y"
	{ yyval.ival = FSA_FILENAME;}
break;
case 167:
#line 1113 "parser_gram.y"
	{ yyval.ival = FSA_NAME;}
break;
case 168:
#line 1114 "parser_gram.y"
	{ yyval.ival = FSA_RANDOM;}
break;
case 169:
#line 1115 "parser_gram.y"
	{ yyval.ival = FSA_FD;}
break;
case 170:
#line 1116 "parser_gram.y"
	{ yyval.ival = FSA_SRCFD;}
break;
case 171:
#line 1117 "parser_gram.y"
	{ yyval.ival = FSA_ROTATEFD;}
break;
case 172:
#line 1118 "parser_gram.y"
	{ yyval.ival = FSA_DSYNC;}
break;
case 173:
#line 1119 "parser_gram.y"
	{ yyval.ival = FSA_DIRECTIO;}
break;
case 174:
#line 1120 "parser_gram.y"
	{ yyval.ival = FSA_INDEXED;}
break;
case 175:
#line 1121 "parser_gram.y"
	{ yyval.ival = FSA_TARGET;}
break;
case 176:
#line 1122 "parser_gram.y"
	{ yyval.ival = FSA_ITERS;}
break;
case 177:
#line 1123 "parser_gram.y"
	{ yyval.ival = FSA_VALUE;}
break;
case 178:
#line 1124 "parser_gram.y"
	{ yyval.ival = FSA_BLOCKING;}
break;
case 179:
#line 1125 "parser_gram.y"
	{ yyval.ival = FSA_HIGHWATER;}
break;
case 180:
#line 1126 "parser_gram.y"
	{ yyval.ival = FSA_IOSIZE;}
break;
case 181:
#line 1127 "parser_gram.y"
	{ yyval.ival = FSA_NOREADAHEAD;}
break;
case 182:
#line 1130 "parser_gram.y"
	{ yyval.ival = FSA_RATE;}
break;
case 183:
#line 1133 "parser_gram.y"
	{ yyval.ival = FSA_MASTER;}
break;
case 184:
#line 1134 "parser_gram.y"
	{ yyval.ival = FSA_CLIENT;}
break;
case 185:
#line 1137 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
}
break;
case 186:
#line 1141 "parser_gram.y"
	{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = yystack.l_mark[-2].attr; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = yystack.l_mark[0].attr;

	yyval.attr = yystack.l_mark[-2].attr;
}
break;
case 187:
#line 1154 "parser_gram.y"
	{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = yystack.l_mark[-2].attr; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = yystack.l_mark[0].attr;

	yyval.attr = yystack.l_mark[-2].attr;
}
break;
case 188:
#line 1168 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
	yyval.attr->attr_name = yystack.l_mark[-2].ival;
}
break;
case 189:
#line 1174 "parser_gram.y"
	{
	if ((yyval.attr = alloc_lvar_attr(var_lvar_assign_boolean(yystack.l_mark[-2].sval, yystack.l_mark[0].bval))) == NULL)
		YYERROR;
}
break;
case 190:
#line 1179 "parser_gram.y"
	{
	if ((yyval.attr = alloc_lvar_attr(var_lvar_assign_integer(yystack.l_mark[-2].sval, yystack.l_mark[0].ival))) == NULL)
		YYERROR;
}
break;
case 191:
#line 1184 "parser_gram.y"
	{
	if ((yyval.attr = alloc_lvar_attr(var_lvar_assign_string(yystack.l_mark[-4].sval, yystack.l_mark[-1].sval))) == NULL)
		YYERROR;
}
break;
case 192:
#line 1189 "parser_gram.y"
	{
	if ((yyval.attr = alloc_lvar_attr(var_lvar_assign_string(yystack.l_mark[-2].sval, yystack.l_mark[0].sval))) == NULL)
		YYERROR;
}
break;
case 193:
#line 1194 "parser_gram.y"
	{
	if ((yyval.attr = alloc_lvar_attr(var_lvar_assign_var(yystack.l_mark[-2].sval, yystack.l_mark[0].sval))) == NULL)
		YYERROR;
}
break;
case 194:
#line 1199 "parser_gram.y"
	{
	if ((yyval.attr = alloc_lvar_attr(var_lvar_alloc_local(yystack.l_mark[0].sval))) == NULL)
		YYERROR;
}
break;
case 195:
#line 1205 "parser_gram.y"
	{
	if ((yyval.cmd = alloc_cmd()) == NULL)
		YYERROR;
	yyval.cmd->cmd = &parser_composite_flowop_define;
	yyval.cmd->cmd_list = yystack.l_mark[-1].cmd;
	yyval.cmd->cmd_attr_list = yystack.l_mark[-3].attr;
}
break;
case 196:
#line 1213 "parser_gram.y"
	{
	yystack.l_mark[-1].cmd->cmd_attr_list = yystack.l_mark[0].attr;
}
break;
case 197:
#line 1219 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
}
break;
case 198:
#line 1223 "parser_gram.y"
	{
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = yystack.l_mark[-2].attr; attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = yystack.l_mark[0].attr;

	yyval.attr = yystack.l_mark[-2].attr;
}
break;
case 199:
#line 1237 "parser_gram.y"
	{
	yyval.attr = yystack.l_mark[0].attr;
	yyval.attr->attr_name = yystack.l_mark[-2].ival;
}
break;
case 200:
#line 1243 "parser_gram.y"
	{ yyval.ival = FSA_NAME;}
break;
case 201:
#line 1244 "parser_gram.y"
	{ yyval.ival = FSA_ITERS;}
break;
case 202:
#line 1247 "parser_gram.y"
	{
	yyval.attr = alloc_attr();
	if (!yyval.attr)
		YYERROR;
	yyval.attr->attr_avd = avd_str_alloc(yystack.l_mark[0].sval);
}
break;
case 203:
#line 1252 "parser_gram.y"
	{
	yyval.attr = alloc_attr();
	if (!yyval.attr)
		YYERROR;
	yyval.attr->attr_avd = avd_str_alloc(yystack.l_mark[-1].sval);
}
break;
case 204:
#line 1257 "parser_gram.y"
	{
	yyval.attr = alloc_attr();
	if (!yyval.attr)
		YYERROR;
	yyval.attr->attr_avd = avd_int_alloc(yystack.l_mark[0].ival);
}
break;
case 205:
#line 1262 "parser_gram.y"
	{
	yyval.attr = alloc_attr();
	if (!yyval.attr)
		YYERROR;
	yyval.attr->attr_avd = avd_bool_alloc(yystack.l_mark[0].bval);
}
break;
case 206:
#line 1267 "parser_gram.y"
	{
	yyval.attr = alloc_attr();
	if (!yyval.attr)
		YYERROR;
	yyval.attr->attr_avd = avd_var_alloc(yystack.l_mark[0].sval);
}
break;
case 207:
#line 1275 "parser_gram.y"
	{
	yyval.avd = avd_int_alloc(yystack.l_mark[0].ival);
}
break;
case 208:
#line 1278 "parser_gram.y"
	{
	yyval.avd = avd_var_alloc(yystack.l_mark[0].sval);
}
break;
#line 4410 "parser_gram.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
