

%{
#include "tokens.h"
int running = 1;
int lineNumber = 1;
%}

%x COMMENT
%%

int { return KW_INT; }
[0-9]+ {return 2;}
"\n" { ++lineNumber; }

[-;{}+] {return yytext[0];}


"//".*
"/*" { BEGIN(COMMENT);}
<COMMENT>"*/" { BEGIN (INITIAL);}
<COMMENT>"\n"  { ++lineNumber; }
<COMMENT>.

. { return TOKEN_ERROR;}

%%

// c code to be included

#include "main.c"
#include "hash.c"

int yywrap(void) {
    running = 0;
    return 1;
}