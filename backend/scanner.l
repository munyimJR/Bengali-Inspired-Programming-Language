%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
int line_num = 1;
int keyword_count = 0;
int identifier_count = 0;

/* Helper function to convert Bangla digits to ASCII in lexer */
int convert_bangla_digit_to_int(const char *str) {
    unsigned char *p = (unsigned char *)str;
    char result[1000];
    int j = 0;
    
    while (*p) {
        // Bangla digits: ০-৯ (UTF-8: 0xE0 0xA7 0xA6 to 0xE0 0xA7 0xAF)
        if (p[0] == 0xE0 && p[1] == 0xA7 && p[2] >= 0xA6 && p[2] <= 0xAF) {
            result[j++] = '0' + (p[2] - 0xA6);
            p += 3;
        } else if (*p >= '0' && *p <= '9') {
            result[j++] = *p++;
        } else {
            p++; // Skip invalid characters
        }
    }
    result[j] = '\0';
    return atoi(result);
}

double convert_bangla_digit_to_float(const char *str) {
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

"//".*                          { /* Single line comment */ }
"/*"([^*]|\*+[^*/])*\*+"/"      {
    int i;
    for(i = 0; yytext[i]; i++) {
        if(yytext[i] == '\n') line_num++;
    }
}

"শুরু"                          { keyword_count++; return SHURU; }
"শেষ"                           { keyword_count++; return SHESH; }
"পূর্ণ"                           { keyword_count++; return PURNO; }
"দশমিক"                         { keyword_count++; return VOGNO; }
"শব্দ"                         { keyword_count++; return SHOBDO; }
"যদি"                           { keyword_count++; return JODI; }
"নাহলে"                         { keyword_count++; return NAHOLE; }
"যতক্ষণ"                        { keyword_count++; return JOTOKKHON; }
"জন্য"                          { keyword_count++; return JNY; }
"দেখাও"                         { keyword_count++; return DEKHAO; }
"নাও"                           { keyword_count++; return NAO; }
"নতুনলাইন"                     { keyword_count++; return NEWLINE_KW; }

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
    yylval.ival = convert_bangla_digit_to_int(yytext);
    return INT_LITERAL;
}

{FLOAT}                         {
    yylval.fval = convert_bangla_digit_to_float(yytext);
    return FLOAT_LITERAL;
}

{STRING}                        {
    int len = strlen(yytext);
    char *temp = (char*)malloc(len - 1);
    char *src;
    char *dst;
    strncpy(temp, yytext + 1, len - 2);
    temp[len - 2] = '\0';
    src = temp;
    dst = temp;
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
    return STRING_LITERAL;
}

{ID}                            {
    yylval.sval = strdup(yytext);
    identifier_count++;
    return IDENTIFIER;
}

[ \t\r]+                        { /* Ignore whitespace */ }
\n                              { line_num++; }

.                               {
    fprintf(stderr, "Error at line %d: Unknown character '%s'\n",
            line_num, yytext);
    exit(1);
}

%%