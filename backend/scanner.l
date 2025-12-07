%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
int line_num = 1;

// Hash sets for tracking unique keywords and identifiers
#define MAX_KEYWORDS 100
#define MAX_IDENTIFIERS 1000

char *unique_keywords[MAX_KEYWORDS];
char *unique_identifiers[MAX_IDENTIFIERS];
int keyword_count = 0;
int identifier_count = 0;

// Helper function to check if keyword already exists
int keyword_exists(const char *keyword) {
    for (int i = 0; i < keyword_count; i++) {
        if (strcmp(unique_keywords[i], keyword) == 0) {
            return 1;
        }
    }
    return 0;
}

// Helper function to check if identifier already exists
int identifier_exists(const char *identifier) {
    for (int i = 0; i < identifier_count; i++) {
        if (strcmp(unique_identifiers[i], identifier) == 0) {
            return 1;
        }
    }
    return 0;
}

// Helper function to add unique keyword
void add_unique_keyword(const char *keyword) {
    if (!keyword_exists(keyword) && keyword_count < MAX_KEYWORDS) {
        unique_keywords[keyword_count] = strdup(keyword);
        keyword_count++;
    }
}

// Helper function to add unique identifier
void add_unique_identifier(const char *identifier) {
    if (!identifier_exists(identifier) && identifier_count < MAX_IDENTIFIERS) {
        unique_identifiers[identifier_count] = strdup(identifier);
        identifier_count++;
    }
}

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

"শুরু"                          { add_unique_keyword("শুরু"); return SHURU; }
"শেষ"                           { add_unique_keyword("শেষ"); return SHESH; }
"পূর্ণ"                           { add_unique_keyword("পূর্ণ"); return PURNO; }
"দশমিক"                         { add_unique_keyword("দশমিক"); return VOGNO; }
"শব্দ"                         { add_unique_keyword("শব্দ"); return SHOBDO; }
"যদি"                           { add_unique_keyword("যদি"); return JODI; }
"নাহলে"                         { add_unique_keyword("নাহলে"); return NAHOLE; }
"যতক্ষণ"                        { add_unique_keyword("যতক্ষণ"); return JOTOKKHON; }
"জন্য"                          { add_unique_keyword("জন্য"); return JNY; }
"দেখাও"                         { add_unique_keyword("দেখাও"); return DEKHAO; }
"নাও"                           { add_unique_keyword("নাও"); return NAO; }
"নতুনলাইন"                     { add_unique_keyword("নতুনলাইন"); return NEWLINE_KW; }

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
    add_unique_identifier(yytext);
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