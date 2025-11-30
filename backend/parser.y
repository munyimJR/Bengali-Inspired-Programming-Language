%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

void yyerror(const char *s);
int yylex(void);

extern int line_num;
extern FILE *yyin;

typedef enum { TYPE_INT, TYPE_FLOAT, TYPE_STRING } VarType;

typedef struct {
    char name[100];
    VarType type;
    union {
        int ival;
        double fval;
        char *sval;
    } value;
} Symbol;

Symbol symbol_table[1000];
int symbol_count = 0;

typedef enum {
    NODE_PROGRAM, NODE_STMT_LIST, NODE_DECLARATION, NODE_ASSIGNMENT,
    NODE_INCREMENT, NODE_DECREMENT, NODE_OUTPUT, NODE_INPUT,
    NODE_IF, NODE_WHILE, NODE_FOR, NODE_EXPRESSION, NODE_STRING_EXPR,
    NODE_CONDITION, NODE_INT_LITERAL, NODE_FLOAT_LITERAL, 
    NODE_STRING_LITERAL, NODE_IDENTIFIER, NODE_NEWLINE
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        int ival;
        double fval;
        char *sval;
    } value;
    VarType var_type;
    char op;
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;
    struct ASTNode *condition;
    struct ASTNode *body;
    struct ASTNode *else_body;
    struct ASTNode *init;
    struct ASTNode *update;
} ASTNode;

ASTNode* create_node(NodeType type);
void execute_node(ASTNode *node);
void free_tree(ASTNode *node);
Symbol* lookup_symbol(const char *name);
Symbol* declare_symbol(const char *name, VarType type);
double eval_expression(ASTNode *node);
char* eval_string_expression(ASTNode *node);
int eval_condition(ASTNode *node);

void convert_bangla_to_ascii(char *str) {
    unsigned char *p = (unsigned char *)str;
    char result[1000];
    int j = 0;
    while (*p) {
        if (p[0] == 0xE0 && p[1] == 0xA7 && p[2] >= 0xA6 && p[2] <= 0xAF) {
            result[j++] = '0' + (p[2] - 0xA6);
            p += 3;
        } else {
            result[j++] = *p++;
        }
    }
    result[j] = '\0';
    strcpy(str, result);
}

%}

%union {
    int ival;
    double fval;
    char *sval;
    struct ASTNode *node;
}

%token SHURU SHESH PURNO VOGNO SHOBDO
%token JODI NAHOLE JOTOKKHON JNY
%token DEKHAO NAO NEWLINE_KW
%token PLUS MINUS MULT DIV
%token PLUS_ASSIGN MINUS_ASSIGN MULT_ASSIGN DIV_ASSIGN
%token INCREMENT DECREMENT
%token LT GT LE GE EQ NE AND OR
%token ASSIGN LBRACE RBRACE LPAREN RPAREN SEMICOLON COMMA
%token OUTPUT_OP INPUT_OP

%token <ival> INT_LITERAL
%token <fval> FLOAT_LITERAL
%token <sval> STRING_LITERAL IDENTIFIER

%type <node> program statement_list statement declaration assignment
%type <node> increment_decrement output_statement input_statement
%type <node> if_statement while_statement for_statement
%type <node> expression term factor arithmetic_expr condition
%type <node> string_expression string_term output_list output_item
%type <node> decl_list_int decl_list_float decl_list_string
%type <node> input_list for_init for_update

%right ASSIGN
%left OR
%left AND
%left EQ NE
%left LT GT LE GE
%left PLUS MINUS
%left MULT DIV
%right UMINUS

%%

program:
    SHURU statement_list SHESH {
        $$ = $2;
        execute_node($$);
        printf("\n[প্রোগ্রাম সফলভাবে সম্পন্ন হয়েছে]\n");
        free_tree($$);
    }
    ;

statement_list:
    /* empty */ { $$ = NULL; }
    | statement_list statement {
        if ($1 == NULL) {
            $$ = $2;
        } else {
            ASTNode *temp = $1;
            while (temp->next != NULL) temp = temp->next;
            temp->next = $2;
            $$ = $1;
        }
    }
    ;

statement:
    declaration SEMICOLON { $$ = $1; }
    | assignment SEMICOLON { $$ = $1; }
    | increment_decrement SEMICOLON { $$ = $1; }
    | output_statement SEMICOLON { $$ = $1; }
    | input_statement SEMICOLON { $$ = $1; }
    | if_statement { $$ = $1; }
    | while_statement { $$ = $1; }
    | for_statement { $$ = $1; }
    | SEMICOLON { $$ = NULL; }
    ;

declaration:
    PURNO decl_list_int { $$ = $2; $$->var_type = TYPE_INT; }
    | VOGNO decl_list_float { $$ = $2; $$->var_type = TYPE_FLOAT; }
    | SHOBDO decl_list_string { $$ = $2; $$->var_type = TYPE_STRING; }
    ;

decl_list_int:
    IDENTIFIER {
        $$ = create_node(NODE_DECLARATION);
        $$->value.sval = $1;
    }
    | IDENTIFIER COMMA decl_list_int {
        $$ = create_node(NODE_DECLARATION);
        $$->value.sval = $1;
        $$->next = $3;
    }
    | IDENTIFIER ASSIGN expression {
        $$ = create_node(NODE_DECLARATION);
        $$->value.sval = $1;
        $$->right = $3;
    }
    | IDENTIFIER ASSIGN expression COMMA decl_list_int {
        $$ = create_node(NODE_DECLARATION);
        $$->value.sval = $1;
        $$->right = $3;
        $$->next = $5;
    }
    ;

decl_list_float:
    IDENTIFIER {
        $$ = create_node(NODE_DECLARATION);
        $$->value.sval = $1;
    }
    | IDENTIFIER COMMA decl_list_float {
        $$ = create_node(NODE_DECLARATION);
        $$->value.sval = $1;
        $$->next = $3;
    }
    | IDENTIFIER ASSIGN expression {
        $$ = create_node(NODE_DECLARATION);
        $$->value.sval = $1;
        $$->right = $3;
    }
    | IDENTIFIER ASSIGN expression COMMA decl_list_float {
        $$ = create_node(NODE_DECLARATION);
        $$->value.sval = $1;
        $$->right = $3;
        $$->next = $5;
    }
    ;

decl_list_string:
    IDENTIFIER {
        $$ = create_node(NODE_DECLARATION);
        $$->value.sval = $1;
    }
    | IDENTIFIER COMMA decl_list_string {
        $$ = create_node(NODE_DECLARATION);
        $$->value.sval = $1;
        $$->next = $3;
    }
    | IDENTIFIER ASSIGN string_expression {
        $$ = create_node(NODE_DECLARATION);
        $$->value.sval = $1;
        $$->right = $3;
    }
    | IDENTIFIER ASSIGN string_expression COMMA decl_list_string {
        $$ = create_node(NODE_DECLARATION);
        $$->value.sval = $1;
        $$->right = $3;
        $$->next = $5;
    }
    ;

assignment:
    IDENTIFIER ASSIGN expression {
        $$ = create_node(NODE_ASSIGNMENT);
        $$->value.sval = $1;
        $$->op = '=';
        $$->right = $3;
    }
    | IDENTIFIER ASSIGN string_expression {
        $$ = create_node(NODE_ASSIGNMENT);
        $$->value.sval = $1;
        $$->op = '=';
        $$->right = $3;
    }
    | IDENTIFIER PLUS_ASSIGN expression {
        $$ = create_node(NODE_ASSIGNMENT);
        $$->value.sval = $1;
        $$->op = '+';
        $$->right = $3;
    }
    | IDENTIFIER MINUS_ASSIGN expression {
        $$ = create_node(NODE_ASSIGNMENT);
        $$->value.sval = $1;
        $$->op = '-';
        $$->right = $3;
    }
    | IDENTIFIER MULT_ASSIGN expression {
        $$ = create_node(NODE_ASSIGNMENT);
        $$->value.sval = $1;
        $$->op = '*';
        $$->right = $3;
    }
    | IDENTIFIER DIV_ASSIGN expression {
        $$ = create_node(NODE_ASSIGNMENT);
        $$->value.sval = $1;
        $$->op = '/';
        $$->right = $3;
    }
    ;

increment_decrement:
    IDENTIFIER INCREMENT {
        $$ = create_node(NODE_INCREMENT);
        $$->value.sval = $1;
    }
    | IDENTIFIER DECREMENT {
        $$ = create_node(NODE_DECREMENT);
        $$->value.sval = $1;
    }
    ;

output_statement:
    DEKHAO output_list { $$ = $2; }
    ;

output_list:
    OUTPUT_OP output_item {
        $$ = create_node(NODE_OUTPUT);
        $$->left = $2;
    }
    | output_list OUTPUT_OP output_item {
        ASTNode *temp = $1;
        while (temp->next != NULL) temp = temp->next;
        ASTNode *new_output = create_node(NODE_OUTPUT);
        new_output->left = $3;
        temp->next = new_output;
        $$ = $1;
    }
    ;

output_item:
    expression { $$ = $1; }
    | string_expression { $$ = $1; }
    | NEWLINE_KW { $$ = create_node(NODE_NEWLINE); }
    ;

input_statement:
    NAO input_list { $$ = $2; }
    ;

input_list:
    INPUT_OP IDENTIFIER {
        $$ = create_node(NODE_INPUT);
        $$->value.sval = $2;
    }
    | input_list INPUT_OP IDENTIFIER {
        ASTNode *temp = $1;
        while (temp->next != NULL) temp = temp->next;
        ASTNode *new_input = create_node(NODE_INPUT);
        new_input->value.sval = $3;
        temp->next = new_input;
        $$ = $1;
    }
    ;

if_statement:
    JODI LPAREN condition RPAREN LBRACE statement_list RBRACE {
        $$ = create_node(NODE_IF);
        $$->condition = $3;
        $$->body = $6;
    }
    | JODI LPAREN condition RPAREN LBRACE statement_list RBRACE NAHOLE LBRACE statement_list RBRACE {
        $$ = create_node(NODE_IF);
        $$->condition = $3;
        $$->body = $6;
        $$->else_body = $10;
    }
    ;

while_statement:
    JOTOKKHON LPAREN condition RPAREN LBRACE statement_list RBRACE {
        $$ = create_node(NODE_WHILE);
        $$->condition = $3;
        $$->body = $6;
    }
    ;

for_statement:
    JNY LPAREN for_init SEMICOLON condition SEMICOLON for_update RPAREN LBRACE statement_list RBRACE {
        $$ = create_node(NODE_FOR);
        $$->init = $3;
        $$->condition = $5;
        $$->update = $7;
        $$->body = $10;
    }
    ;

for_init:
    /* empty */ { $$ = NULL; }
    | assignment { $$ = $1; }
    | PURNO IDENTIFIER ASSIGN expression {
        $$ = create_node(NODE_DECLARATION);
        $$->value.sval = $2;
        $$->var_type = TYPE_INT;
        $$->right = $4;
    }
    ;

for_update:
    /* empty */ { $$ = NULL; }
    | assignment { $$ = $1; }
    | increment_decrement { $$ = $1; }
    ;

condition:
    arithmetic_expr LT arithmetic_expr {
        $$ = create_node(NODE_CONDITION);
        $$->op = '<';
        $$->left = $1;
        $$->right = $3;
    }
    | arithmetic_expr GT arithmetic_expr {
        $$ = create_node(NODE_CONDITION);
        $$->op = '>';
        $$->left = $1;
        $$->right = $3;
    }
    | arithmetic_expr LE arithmetic_expr {
        $$ = create_node(NODE_CONDITION);
        $$->op = 'l';
        $$->left = $1;
        $$->right = $3;
    }
    | arithmetic_expr GE arithmetic_expr {
        $$ = create_node(NODE_CONDITION);
        $$->op = 'g';
        $$->left = $1;
        $$->right = $3;
    }
    | arithmetic_expr EQ arithmetic_expr {
        $$ = create_node(NODE_CONDITION);
        $$->op = 'e';
        $$->left = $1;
        $$->right = $3;
    }
    | arithmetic_expr NE arithmetic_expr {
        $$ = create_node(NODE_CONDITION);
        $$->op = 'n';
        $$->left = $1;
        $$->right = $3;
    }
    | condition AND condition {
        $$ = create_node(NODE_CONDITION);
        $$->op = '&';
        $$->left = $1;
        $$->right = $3;
    }
    | condition OR condition {
        $$ = create_node(NODE_CONDITION);
        $$->op = '|';
        $$->left = $1;
        $$->right = $3;
    }
    | LPAREN condition RPAREN { $$ = $2; }
    ;

arithmetic_expr:
    expression { $$ = $1; }
    ;

expression:
    term { $$ = $1; }
    | expression PLUS term {
        $$ = create_node(NODE_EXPRESSION);
        $$->op = '+';
        $$->left = $1;
        $$->right = $3;
    }
    | expression MINUS term {
        $$ = create_node(NODE_EXPRESSION);
        $$->op = '-';
        $$->left = $1;
        $$->right = $3;
    }
    ;

term:
    factor { $$ = $1; }
    | term MULT factor {
        $$ = create_node(NODE_EXPRESSION);
        $$->op = '*';
        $$->left = $1;
        $$->right = $3;
    }
    | term DIV factor {
        $$ = create_node(NODE_EXPRESSION);
        $$->op = '/';
        $$->left = $1;
        $$->right = $3;
    }
    ;

factor:
    INT_LITERAL {
        $$ = create_node(NODE_INT_LITERAL);
        $$->value.ival = $1;
    }
    | FLOAT_LITERAL {
        $$ = create_node(NODE_FLOAT_LITERAL);
        $$->value.fval = $1;
    }
    | IDENTIFIER {
        $$ = create_node(NODE_IDENTIFIER);
        $$->value.sval = strdup($1);
        free($1);
    }
    | LPAREN expression RPAREN { $$ = $2; }
    | MINUS factor {
        $$ = create_node(NODE_EXPRESSION);
        $$->op = 'u';
        $$->right = $2;
    }
    ;

string_expression:
    string_term { $$ = $1; }
    | string_expression PLUS string_term {
        $$ = create_node(NODE_STRING_EXPR);
        $$->op = '+';
        $$->left = $1;
        $$->right = $3;
    }
    ;

string_term:
    STRING_LITERAL {
        $$ = create_node(NODE_STRING_LITERAL);
        $$->value.sval = $1;
    }
    | IDENTIFIER {
        $$ = create_node(NODE_IDENTIFIER);
        $$->value.sval = strdup($1);
        free($1);
    }
    ;

%%

ASTNode* create_node(NodeType type) {
    ASTNode *node = (ASTNode*)calloc(1, sizeof(ASTNode));
    node->type = type;
    return node;
}

void execute_node(ASTNode *node) {
    if (node == NULL) return;
    
    switch (node->type) {
        case NODE_DECLARATION: {
            Symbol *sym = declare_symbol(node->value.sval, node->var_type);
            if (node->right) {
                if (node->var_type == TYPE_STRING) {
                    sym->value.sval = eval_string_expression(node->right);
                } else {
                    double val = eval_expression(node->right);
                    if (node->var_type == TYPE_INT) {
                        sym->value.ival = (int)val;
                    } else {
                        sym->value.fval = val;
                    }
                }
            }
            break;
        }
        case NODE_ASSIGNMENT: {
            Symbol *sym = lookup_symbol(node->value.sval);
            if (sym) {
                if (sym->type == TYPE_STRING && node->right->type == NODE_STRING_LITERAL) {
                    if (sym->value.sval) free(sym->value.sval);
                    sym->value.sval = eval_string_expression(node->right);
                } else if (sym->type == TYPE_STRING) {
                    if (sym->value.sval) free(sym->value.sval);
                    sym->value.sval = eval_string_expression(node->right);
                } else {
                    double val = eval_expression(node->right);
                    if (node->op == '=') {
                        if (sym->type == TYPE_INT) sym->value.ival = (int)val;
                        else sym->value.fval = val;
                    } else if (node->op == '+') {
                        if (sym->type == TYPE_INT) sym->value.ival += (int)val;
                        else sym->value.fval += val;
                    } else if (node->op == '-') {
                        if (sym->type == TYPE_INT) sym->value.ival -= (int)val;
                        else sym->value.fval -= val;
                    } else if (node->op == '*') {
                        if (sym->type == TYPE_INT) sym->value.ival *= (int)val;
                        else sym->value.fval *= val;
                    } else if (node->op == '/') {
                        if (sym->type == TYPE_INT) sym->value.ival /= (int)val;
                        else sym->value.fval /= val;
                    }
                }
            }
            break;
        }
        case NODE_INCREMENT: {
            Symbol *sym = lookup_symbol(node->value.sval);
            if (sym) {
                if (sym->type == TYPE_INT) sym->value.ival++;
                else sym->value.fval++;
            }
            break;
        }
        case NODE_DECREMENT: {
            Symbol *sym = lookup_symbol(node->value.sval);
            if (sym) {
                if (sym->type == TYPE_INT) sym->value.ival--;
                else sym->value.fval--;
            }
            break;
        }
        case NODE_OUTPUT: {
            if (node->left) {
                if (node->left->type == NODE_NEWLINE) {
                    printf("\n");
                } else if (node->left->type == NODE_STRING_LITERAL || 
                           node->left->type == NODE_STRING_EXPR ||
                           (node->left->type == NODE_IDENTIFIER && 
                            lookup_symbol(node->left->value.sval) &&
                            lookup_symbol(node->left->value.sval)->type == TYPE_STRING)) {
                    char *str = eval_string_expression(node->left);
                    printf("%s", str);
                    free(str);
                } else {
                    double val = eval_expression(node->left);
                    if (fmod(val, 1.0) == 0) {
                        printf("%d", (int)val);
                    } else {
                        printf("%g", val);
                    }
                }
            }
            break;
        }
        case NODE_INPUT: {
            Symbol *sym = lookup_symbol(node->value.sval);
            if (sym) {
                if (sym->type == TYPE_INT) {
                    char buffer[100];
                    if(scanf("%99s", buffer) == 1) {
                        convert_bangla_to_ascii(buffer);
                        sym->value.ival = atoi(buffer);
                    }
                } else if (sym->type == TYPE_FLOAT) {
                    char buffer[100];
                    if(scanf("%99s", buffer) == 1) {
                        convert_bangla_to_ascii(buffer);
                        sym->value.fval = atof(buffer);
                    }
                } else if (sym->type == TYPE_STRING) {
                    char buffer[1000];
                    if(fgets(buffer, sizeof(buffer), stdin)) {
                        size_t len = strlen(buffer);
                        if (len > 0 && buffer[len-1] == '\n') {
                            buffer[len-1] = '\0';
                        }
                        if (sym->value.sval) free(sym->value.sval);
                        sym->value.sval = strdup(buffer);
                    }
                }
            }
            break;
        }
        case NODE_IF: {
            if (eval_condition(node->condition)) {
                execute_node(node->body);
            } else if (node->else_body) {
                execute_node(node->else_body);
            }
            break;
        }
        case NODE_WHILE: {
            while (eval_condition(node->condition)) {
                execute_node(node->body);
            }
            break;
        }
        case NODE_FOR: {
            if (node->init) execute_node(node->init);
            while (eval_condition(node->condition)) {
                execute_node(node->body);
                if (node->update) execute_node(node->update);
            }
            break;
        }
    }
    
    if (node->next) execute_node(node->next);
}

double eval_expression(ASTNode *node) {
    if (node == NULL) return 0;
    
    switch (node->type) {
        case NODE_INT_LITERAL:
            return (double)node->value.ival;
        case NODE_FLOAT_LITERAL:
            return node->value.fval;
        case NODE_IDENTIFIER: {
            Symbol *sym = lookup_symbol(node->value.sval);
            if (sym->type == TYPE_INT) return (double)sym->value.ival;
            if (sym->type == TYPE_FLOAT) return sym->value.fval;
            return 0;
        }
        case NODE_EXPRESSION: {
            double left = node->left ? eval_expression(node->left) : 0;
            double right = eval_expression(node->right);
            switch (node->op) {
                case '+': return left + right;
                case '-': return left - right;
                case '*': return left * right;
                case '/': return right != 0 ? left / right : 0;
                case 'u': return -right;
            }
        }
    }
    return 0;
}

char* eval_string_expression(ASTNode *node) {
    if (node == NULL) return strdup("");
    
    switch (node->type) {
        case NODE_STRING_LITERAL:
            return strdup(node->value.sval);
        case NODE_IDENTIFIER: {
            Symbol *sym = lookup_symbol(node->value.sval);
            if (sym && sym->type == TYPE_STRING) {
                return strdup(sym->value.sval);
            }
            return strdup("");
        }
        case NODE_STRING_EXPR: {
            char *left = eval_string_expression(node->left);
            char *right = eval_string_expression(node->right);
            char *result = malloc(strlen(left) + strlen(right) + 1);
            strcpy(result, left);
            strcat(result, right);
            free(left);
            free(right);
            return result;
        }
    }
    return strdup("");
}

int eval_condition(ASTNode *node) {
    if (node == NULL) return 1;
    
    double left = eval_expression(node->left);
    double right = eval_expression(node->right);
    
    switch (node->op) {
        case '<': return left < right;
        case '>': return left > right;
        case 'l': return left <= right;
        case 'g': return left >= right;
        case 'e': return left == right;
        case 'n': return left != right;
        case '&': return eval_condition(node->left) && eval_condition(node->right);
        case '|': return eval_condition(node->left) || eval_condition(node->right);
    }
    return 0;
}

void free_tree(ASTNode *node) {
    if (node == NULL) return;
    free_tree(node->left);
    free_tree(node->right);
    free_tree(node->next);
    free_tree(node->condition);
    free_tree(node->body);
    free_tree(node->else_body);
    free_tree(node->init);
    free_tree(node->update);
    if (node->value.sval && (node->type == NODE_STRING_LITERAL || 
        node->type == NODE_IDENTIFIER || node->type == NODE_DECLARATION ||
        node->type == NODE_ASSIGNMENT || node->type == NODE_INPUT ||
        node->type == NODE_INCREMENT || node->type == NODE_DECREMENT)) {
        free(node->value.sval);
    }
    free(node);
}

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", line_num, s);
}

Symbol* lookup_symbol(const char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return &symbol_table[i];
        }
    }
    fprintf(stderr, "Error: Undeclared variable '%s'\n", name);
    exit(1);
}

Symbol* declare_symbol(const char *name, VarType type) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            fprintf(stderr, "Error: Variable '%s' already declared\n", name);
            exit(1);
        }
    }
    
    if (symbol_count >= 1000) {
        fprintf(stderr, "Error: Symbol table full\n");
        exit(1);
    }
    
    Symbol *sym = &symbol_table[symbol_count++];
    strcpy(sym->name, name);
    sym->type = type;
    
    if (type == TYPE_INT) sym->value.ival = 0;
    else if (type == TYPE_FLOAT) sym->value.fval = 0.0;
    else if (type == TYPE_STRING) sym->value.sval = strdup("");
    
    return sym;
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "en_US.UTF-8");
    
    printf("=== বাংলা প্রোগ্রামিং ভাষা কম্পাইলার ===\n\n");
    
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Error: Cannot open file '%s'\n", argv[1]);
            return 1;
        }
    } else {
        yyin = fopen("code.txt", "r");
        if (!yyin) {
            fprintf(stderr, "Error: Cannot open 'code.txt'\n");
            return 1;
        }
    }
    
    yyparse();
    fclose(yyin);
    return 0;
}