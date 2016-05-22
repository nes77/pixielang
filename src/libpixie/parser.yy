%{
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <vector>
#include <cinttypes>
#include "ast.hpp"
using namespace pixie::compile;
%}

%require "2.3"

%debug

%start program

%defines

%skeleton "lalr1.cc"

%define "parser_class_name" "Parser"

%locations

%parse-param { class ASTProgram& driver }

%error-verbose

%union {

    int64_t int_val;
    double float_val;
    std::string* val;
    class ASTNode* node;
    class ASTStatement* stmt;
    class ASTStatementBlock* stmt_block;
    class ASTExpression* expr;
}

%token END 0 "end of file"
%token EOL "end of line"
%token <int_val> INTEGER "integer"
%token <float_val> FLOAT "float"
%token <val> STRING "string"
%token <val> IDENTIFIER "identifier"
%type <node> program
%type <node> class_def func_def
%type <stmt_block> statement_block
%type <stmt> statment expr_stmt assert_stmt import_stmt export_stmt hides_stmt assign_stmt return_stmt
%type <expr> expr call_expr lambda_expr lit_expr id

%destructor {delete $$; } STRING
%destructor {delete $$; } program class_def func_def 
%destructor {delete $$;} statement_block
%destructor {delete $$; } statment expr_stmt assert_stmt import_stmt export_stmt hides_stmt assign_stmt return_stmt
%destructor {delete $$; } expr call_expr lambda_expr id lit_expr
%destructor {delete $$; } stmt_block

%nonassoc LABMDA
%left "or"
%left "and"
%left NOT
%left "<" "<=" ">" ">=" "==" "!="
%left '|'
%left '^'
%left '&'
%left "<<" ">>"
%left '+' '-'
%left '*' '/' '%'
%left UMINUS NEG
%right "**"
%left '.'
%nonassoc PARENEXPR

%{

#undef yylex
#define yylex driver.lexer->lex

%}

%%

lit_expr : INTEGER
         | FLOAT
         | STRING
         ;

id : IDENTIFIER;

expr : lambda_expr %prec LAMBDA
     | expr "or" expr
     | expr "and" expr
     | "not" expr %prec NOT
     | expr '<' expr
     | expr "<=" expr
     | expr '>' expr
     | expr ">=" expr
     | expr "==" expr
     | expr "!=" expr
     | expr '|' expr
     | expr '^' expr
     | expr '&' expr
     | expr "<<" expr
     | expr ">>" expr
     | expr '+' expr
     | expr '-' expr
     | expr '*' expr
     | expr '/' expr
     | expr '%' expr
     | '-' expr %prec UMINUS
     | '~' expr %prec NEG
     | expr '.' expr
     | '(' expr ')' %prec PARENEXPR
     ;

lambda_expr : "(\\" decl_args "->" expr ')'
            | "(\\" decl_args "->" '{' stmt_block '}' ')'
            ;

program : stmt_block;

stmt : '{' stmt_block '}'
     | expr_stmt ';'
     | assert_stmt ';'
     | import_stmt ';'
     | export_stmt ';'
     | hides_stmt ';'
     | assign_stmt ';'
     | return_stmt ';'
     ;

stmt_block :
           | stmt_block stmt
           ;

assert_stmt : "assert" expr
