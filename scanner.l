

%{
// 00243463 - Vanessa Coelho
#include "tokens.h"
#include "hash.h"
int running = 1;
int lineNumber = 1;
%}

%x COMMENT
%%
"char"                                  return KW_CHAR;
"int"                                   return KW_INT;
"bool"                                  return KW_BOOL;
"pointer"                               return KW_POINTER;

"if"                                    return KW_IF;
"then"                                  return KW_THEN;
"else"                                  return KW_ELSE;
"while"                                 return KW_WHILE;
"read"                                  return KW_READ;
"print"                                 return KW_PRINT;
"return"                                return KW_RETURN;

"<="                                    return OPERATOR_LE;
">="                                    return OPERATOR_GE;
"=="                                    return OPERATOR_EQ;
"!="                                    return OPERATOR_DIF;
"<-"                                    return LEFT_ASSIGN;
"->"                                    return RIGHT_ASSIGN;

"true"                                  return LIT_TRUE;
"false"                                 return LIT_FALSE;

[0-9]+                                  { hashInsert(LIT_INTEGER, yytext);   return LIT_INTEGER; }


\'[^\']\'                               { hashInsert(LIT_CHAR, yytext);      return LIT_CHAR; }

[\"].+[\']                              return TOKEN_ERROR;
[\'].+[\"]                              return TOKEN_ERROR;

[\"](\\\"|[^\"\n])*[^(\\|\n)][\"]       { hashInsert(LIT_STRING, yytext);    return LIT_STRING; }
[\'](\\\'|[^\'\n])*[^(\\|\n)][\']       return TOKEN_ERROR;

[\"].*[\\\"]*.*[\"]                     return TOKEN_ERROR;
[\'].*[\\\']*.*[\']                     return TOKEN_ERROR;

[A-Za-z_][A-Za-z_0-9]*                  { hashInsert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER; }


[-,;:()\[\]{}+*/<>|&~$#]                return yytext[0];

[0-9][A-Za-z_0-9]*                      return TOKEN_ERROR;

"\n"                                    { ++lineNumber; }

"//".*
"/*"                                    { BEGIN(COMMENT); }
<COMMENT>"*/"                           { BEGIN (INITIAL); }
<COMMENT>"\n"                           { ++lineNumber; }
<COMMENT>.

[ \t\r]
.                                       { return TOKEN_ERROR; }
%%

// c code to be included

#include "main.c"
#include "hash.c"

int yywrap(void) {
    running = 0;
    return 1;
}

// functionality needed
int isRunning(void) { return running; }
int getLineNumber(void) { return lineNumber; }