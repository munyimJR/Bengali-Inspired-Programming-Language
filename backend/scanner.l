%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
int line_num = 1;

char *keywords[100];
char *identifiers[1000];
int keyword_count = 0;
int identifier_count = 0;

int has_keyword(const char *word) {
    for (int i = 0; i < keyword_count; i++) {
        if (strcmp(keywords[i], word) == 0) return 1;
    }
    return 0;
}

int has_identifier(const char *word) {
    for (int i = 0; i < identifier_count; i++) {
        if (strcmp(identifiers[i], word) == 0) return 1;
    }
    return 0;
}

void add_keyword(const char *word) {
    if (!has_keyword(word) && keyword_count < 100) {
        keywords[keyword_count++] = strdup(word);
    }
}

void add_identifier(const char *word) {
    if (!has_identifier(word) && identifier_count < 1000) {
        identifiers[identifier_count++] = strdup(word);
    }
}

int to_int(const char *str) {
    unsigned char *p = (unsigned char *)str;
    char result[1000];
    int j = 0;
    
    while (*p) {
        if (p[0] == 0xE0 && p[1] == 0xA7 && p[2] >= 0xA6 && p[2] <= 0xAF) {
            result[j++] = '0' + (p[2] - 0xA6);
            p += 3;
        } else if (*p >= '0' && *p <= '9') {
            result[j++] = *p++;
        } else {
            p++;
        }
    }
    result[j] = '\0';
    return atoi(result);
}

double to_float(const char *str) {
    unsigned char *p = (unsigned char *)str;
    char result[1000];
    int j = 0;
    
    while (*p) {
        if (p[0] == 0xE0 && p[1] == 0xA7 && p[2] >= 0xA6 && p[2] <= 0xAF) {
            result[j++] = '0' + (p[2] - 0xA6);
            p += 3;
        } else if ((*p >= '0' && *p <= '9') || *p == '.') {
            result[j++] = *p++;
        } else {
            p++;
        }
    }
    result[j] = '\0';
    return atof(result);
}
%}

%option noyywrap

DIGIT       [0-9]
BANGLA_DIGIT    [\xE0][\xA7][\xA6-\xAF]
LETTER      [a-zA-Z_]
BANGLA      [\x80-\xFF]+
ID          ({LETTER}|{BANGLA})({LETTER}|{DIGIT}|{BANGLA})*
INTEGER     ({DIGIT}|{BANGLA_DIGIT})+
FLOAT       ({DIGIT}|{BANGLA_DIGIT})+\.({DIGIT}|{BANGLA_DIGIT})+
STRING      \"([^\\\"]|\\.)*\"

%%

"//".*                          { }
"/*"([^*]|\*+[^*/])*\*+"/"      {
    for(int i = 0; yytext[i]; i++) {
        if(yytext[i] == '\n') line_num++;
    }
}

"শুরু"                          { add_keyword("শুরু"); return SHURU; }
"শেষ"                           { add_keyword("শেষ"); return SHESH; }
"পূর্ণ"                           { add_keyword("পূর্ণ"); return PURNO; }
"দশমিক"                         { add_keyword("দশমিক"); return VOGNO; }
"শব্দ"                         { add_keyword("শব্দ"); return SHOBDO; }
"যদি"                           { add_keyword("যদি"); return JODI; }
"নাহলে"                         { add_keyword("নাহলে"); return NAHOLE; }
"যতক্ষণ"                        { add_keyword("যতক্ষণ"); return JOTOKKHON; }
"জন্য"                          { add_keyword("জন্য"); return JNY; }
"দেখাও"                         { add_keyword("দেখাও"); return DEKHAO; }
"নাও"                           { add_keyword("নাও"); return NAO; }
"নতুনলাইন"                     { add_keyword("নতুনলাইন"); return NEWLINE_KW; }

"+"                             { return PLUS; }
"-"                             { return MINUS; }
"*"                             { return MULT; }
"/"                             { return DIV; }
"+="                            { return PLUS_ASSIGN; }
"-="                            { return MINUS_ASSIGN; }
"*="                            { return MULT_ASSIGN; }
"/="                            { return DIV_ASSIGN; }
"++"                            { return INCREMENT; }
"--"                            { return DECREMENT; }
"<"                             { return LT; }
">"                             { return GT; }
"<="                            { return LE; }
">="                            { return GE; }
"=="                            { return EQ; }
"!="                            { return NE; }
"&&"                            { return AND; }
"||"                            { return OR; }
"="                             { return ASSIGN; }
"{"                             { return LBRACE; }
"}"                             { return RBRACE; }
"("                             { return LPAREN; }
")"                             { return RPAREN; }
";"                             { return SEMICOLON; }
","                             { return COMMA; }
"<<"                            { return OUTPUT_OP; }
">>"                            { return INPUT_OP; }

{INTEGER}                       {
    yylval.ival = to_int(yytext);
    return INT_LITERAL;
}

{FLOAT}                         {
    yylval.fval = to_float(yytext);
    return FLOAT_LITERAL;
}

{STRING}                        {
    int len = strlen(yytext);
    char *temp = (char*)malloc(len - 1);
    strncpy(temp, yytext + 1, len - 2);
    temp[len - 2] = '\0';
    
    char *src = temp, *dst = temp;
    while (*src) {
        if (*src == '\\') {
            src++;
            switch (*src) {
                case 'n': *dst++ = '\n'; break;
                case 't': *dst++ = '\t'; break;
                case '\\': *dst++ = '\\'; break;
                case '"': *dst++ = '"'; break;
                default: *dst++ = *src; break;
            }
            src++;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
    yylval.sval = temp;
    add_identifier(yytext);
    return STRING_LITERAL;
}

{ID}                            {
    yylval.sval = strdup(yytext);
    add_identifier(yytext);
    return IDENTIFIER;
}

[ \t\r]+                        { }
\n                              { line_num++; }

.                               {
    fprintf(stderr, "Error at line %d: Unknown character '%s'\n",
            line_num, yytext);
    exit(1);
}

%%