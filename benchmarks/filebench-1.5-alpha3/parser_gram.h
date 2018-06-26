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
extern YYSTYPE yylval;
