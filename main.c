#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

extern char *yytext;
extern FILE *yyin;
extern int running;
extern int lineNumber;
extern void initMe();

// imports
int yylex();
void initMe(void);
void hashPrint();
int isRunning(void);
int getLineNumber(void);

int main(int argc, char **argv)
{
    int tok = 0;
    if (argc < 2)
    {
        fprintf(stderr, "Call: ./a.out file_name\n");
        exit(1);
    }
    if ((yyin = fopen(argv[1], "r")) == 0)
    {
        printf("Could not open file %s... \n", argv[1]);
        exit(1);
    }
    initMe();
    while (isRunning())
    {
        tok = yylex();
        if (!isRunning())
            break;
        switch (tok)
        {
        case KW_CHAR:
            printf("char\n");
            break;
        case KW_INT:
            printf("int\n");
            break;
        case KW_BOOL:
            printf("bool\n");
            break;
        case KW_POINTER:
            printf("pointer\n");
            break;
        case KW_IF:
            printf("if\n");
            break;
        case KW_THEN:
            printf("then\n");
            break;
        case KW_ELSE:
            printf("else\n");
            break;
        case KW_WHILE:
            printf("while\n");
            break;
        case KW_READ:
            printf("read\n");
            break;
        case KW_PRINT:
            printf("print\n");
            break;
        case KW_RETURN:
            printf("return\n");
            break;
        case OPERATOR_LE:
            printf("LE(<=)\n");
            break;
        case OPERATOR_GE:
            printf("GE(>=)\n");
            break;
        case OPERATOR_EQ:
            printf("EQ(==)\n");
            break;
        case OPERATOR_DIF:
            printf("DIF(!=)\n");
            break;
        case LEFT_ASSIGN:
            printf("LEFT_ASSIGN(<-)\n");
            break;
        case RIGHT_ASSIGN:
            printf("RIGHT_ASSIGN(->)\n");
            break;
        case TK_IDENTIFIER:
            printf("IDENT %s\n", yytext);
            break;
        case LIT_INTEGER:
            printf("INT %s\n", yytext);
            break;
        case LIT_TRUE:
            printf("true\n");
            break;
        case LIT_FALSE:
            printf("false\n");
            break;
        case LIT_CHAR:
            printf("CHAR %s\n", yytext);
            break;
        case LIT_STRING:
            printf("STRING %s\n", yytext);
            break;
        case ',':
        case ';':
        case ':':
        case '(':
        case ')':
        case '[':
        case ']':
        case '{':
        case '}':
        case '+':
        case '-':
        case '*':
        case '/':
        case '<':
        case '>':
        case '|':
        case '&':
        case '~':
        case '$':
        case '#':
            printf("SPECIAL: %c [%d]\n", yytext[0], yytext[0]);
            break;
        case TOKEN_ERROR:
            printf("ERROR | Unexpected Token: %c [%s]\n", yytext[0], yytext);
            break;
        }
    }
    printf("End of main\n");
    printf("[%d] lines processed\n", getLineNumber());
    hashPrint();
    exit(0);
}