#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

extern char *yytext;
extern FILE *yyin;
extern int running;
extern int lineNumber;
extern void initMe();

int yylex();
void initMe(void);
void hashPrint();

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
        printf("Cannot open file %s... \n", argv[1]);
        exit(1);
    }
    initMe();
    while (running)
    {
        tok = yylex();
        if (!running)
            break;
        switch (tok)
        {
            case KW_CHAR:       printf("char\n"); break;
            case KW_INT:        printf("int\n"); break;
            case KW_BOOL:       printf("bool\n"); break;
            case KW_POINTER:    printf("pointer\n"); break;
            case KW_IF:         printf("if\n"); break;
            case KW_THEN:       printf("then\n"); break;
            case KW_ELSE:       printf("else\n"); break;
            case KW_WHILE:      printf("while\n"); break;
            case KW_READ:       printf("read\n"); break;
            case KW_PRINT:      printf("print\n"); break;
            case KW_RETURN:     printf("return\n"); break;
            case OPERATOR_LE:   printf("LE(<=)\n"); break;
            case OPERATOR_GE:   printf("GE(>=)\n"); break;
            case OPERATOR_EQ:   printf("EQ(==)\n"); break;
            case OPERATOR_DIF:  printf("DIF(!=)\n"); break;
            case LEFT_ASSIGN:   printf("LEFT_ASSIGN(<-)\n"); break;
            case RIGHT_ASSIGN:  printf("RIGHT_ASSIGN(->)\n"); break;
            case TK_IDENTIFIER: printf("IDENT %s\n", yytext); break;
            case LIT_INTEGER:   printf("INT %s\n", yytext); break;
            case LIT_TRUE:      printf("TRUE\n"); break;
            case LIT_FALSE:     printf("FALSE\n"); break;
            case LIT_CHAR:      printf("CHAR %s\n", yytext); break;
            case LIT_STRING:    printf("STRING %s\n", yytext); break;
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
            case '#':           printf("SPECIAL: %c [%d]\n", yytext[0], yytext[0]); break;
            case TOKEN_ERROR:   printf("Unexpected Token: %c [%d]\n", yytext[0], yytext[0]); break;
        }
    }
    printf("End of main\n");
    printf("[%d] lines processed\n", lineNumber);
    hashPrint();
    exit(0);
}