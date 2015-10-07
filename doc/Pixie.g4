grammar Pixie;

pixieFile
    :   (stmt ';' | class_def | named_func_def)*
    ;

stmt
    :   import_stmt
    |   assert_stmt
    |   assign_stmt
    |   return_stmt
    |   expr
    ;

scope
    :   '{' (stmt | scope)* '}'
    ;

import_stmt
    :   'import' dotted_name
    ;

assert_stmt
    :   'assert' expr
    ;

return_stmt
    :   'return' expr
    ;

assign_stmt
    :   lhs_expr AssignmentOperator expr
    ;

lhs_expr
    :   subscription_expr
    |   dotted_name
    ;

expr
    :   '(' expr ')'
    |   expr '**' expr
    |   '+' expr
    |   '-' expr 
    |   '~' expr
    |   expr '*' expr 
    |   expr '/' expr 
    |   expr '%' expr
    |   expr '+' expr
    |   expr '-' expr
    |   expr '<<' expr
    |   expr '>>' expr
    |   expr '&' expr
    |   expr '^' expr
    |   expr '|' expr
    |   expr ComparisonOperator expr
    |   'not' expr
    |   expr 'and' expr
    |   expr 'or' expr
    |   func_def
    |   literal_expr
    |   (subscription_expr
        |slice_expr
        |call_expr
        |dotted_name
        )
    ;

subscription_expr
    :   dotted_name '[' expr ']'
    ;

slice_expr
    :   dotted_name '[' expr ':' expr ']'
    ;

highest_expr
    :   literal_expr
    ;

call_expr
    :   dotted_name '(' func_args? ')'
    ;

literal_expr
    :   list_literal
    |   tuple_literal
    |   set_literal
    |   dict_literal
    |   Literal
    ;

list_literal
    :   '[' expr (',' expr)* ']'
    ;

tuple_literal
    :   '(' expr (',' expr)* ')'
    ;

set_literal
    :   '{' expr (',' expr)* '}'
    ;

dict_literal
    :   '{' Literal ':' expr (',' Literal ':' expr)* '}'
    ;

class_def
    :   'class' Name scope
    ;

named_func_def
    :   'def' Name func_def
    ;

func_def
    :   parameter_list '->' ( expr ';' | scope )
    ;

parameter_list
    : '[>' func_def_args? '<]'
    ;

func_def_args
    :   Name (',' Name)* 
        (',' 
         ('*' Name (',' '**' Name)? 
                    |'**' Name
         )
        )?
    |   '*' Name (',' '**' Name)? 
    |   '**' Name
    ;

func_args
    :   expr (',' func_args)*
    ;
        
dotted_name : Name ('.' Name)*;

Literal
    :   NumberLiteral
    |   StringLiteral
    ;

NumberLiteral
    :   FloatLiteral
    |   IntegerLiteral
    ;

IntegerLiteral
    :   HexIntegerLiteral
    |   DecimalIntegerLiteral
    |   BinaryIntegerLiteral
    ;

HexIntegerLiteral
    :   '0' [xX] HexDigit+
    ;

DecimalIntegerLiteral
    :   Digit+
    ;

BinaryIntegerLiteral
    :   '0' [bB] BinDigit+
    ;

OctalIntegerLiteral
    :   '0' [oO] OctalDigit+
    ;

FloatLiteral
    :   Digit+ '.' Digit+
    ;

StringLiteral
    :   NonRawStringLiteral
    |   RawStringLiteral
    ;

NonRawStringLiteral
    :   '"' Char* '"'
    ;

RawStringLiteral
    :   '"""' RawChar* '"""'
    ;

fragment Char
    :   ~["\\\r\n]
    |   CharEscapeSequence
    ;

fragment RawChar
    :   .
    ;

fragment CharEscapeSequence
    :   SimpleEscapeSequence
    ;

fragment SimpleEscapeSequence
    :   '\\' ["?abfnrtv\\]
    ;

Comma : ',';
SemiColon : ';';
Colon : ':';
Arrow : '->';
Dot : '.';
Space : ' ' -> skip;
LParens : '(';
RParens : ')';
LBrace : '{';
RBrace : '}';
LBracket : '[';
RBracket : ']';
LBarrow : '[>';
RBarrow : '<]';

Def : 'def';
Class : 'class';
Import : 'import';
Return : 'return';
Assert : 'assert';

Name : ('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*;

BinaryOperator
    :   Plus
    |   Minus
    |   Star
    |   Slash
    |   RightShift
    |   LeftShift
    |   Percent
    |   VBar
    |   Amper
    |   Caret
    |   DoubleStar
    ;

// Binary operations
Plus : '+'; // __plus__
Minus : '-'; // __minus__
Star : '*'; // __mul__
Slash : '/'; // __div__
RightShift : '>>'; // __rshf__
LeftShift : '<<'; // __lshf__
Percent : '%'; // __mod__
VBar : '|'; // __or__
Amper : '&'; //__and__
Caret : '^'; // __xor__
DoubleStar : '**'; // __pow__

// Boolean operators
And : 'and';
Or : 'or';
Xor : 'xor';
Not : 'not';

// Comparison operations

ComparisonOperator
    :   Less
    |   Greater
    |   LessEqual
    |   GreaterEqual
    |   StructuralEquality
    |   StructuralInequality
    |   ReferentialEquality
    |   In
    |   Not In
    |   ReferentialEquality Not
    |   InstanceOf
    ;

Less : '<'; // __lt__
Greater : '>'; // __gt__
LessEqual : '<='; // __leq__
GreaterEqual : '>='; // __geq__
StructuralEquality : '=='; // __eq__
StructuralInequality : '!='; // __neq__
ReferentialEquality : 'is'; // built-in
In : 'in'; // __contains__
InstanceOf : 'is a'; // type(LHS) is subtype or type of RHS

// Unary Operators
Tilde : '~'; // __neg__

// Assignment Operators

AssignmentOperator
    :   Equals
    |   PlusEquals
    |   MinusEquals
    |   StarEquals
    |   SlashEquals
    |   RightShiftEquals
    |   LeftShiftEquals
    |   PercentEquals
    |   VBarEquals
    |   AmperEquals
    |   CaretEquals
    |   DoubleStarEquals
    |   TildeEquals
    ;

Equals : '=';
PlusEquals : '+='; // __aplus__
MinusEquals : '-='; // __aminus__
StarEquals : '*='; // __amul__
SlashEquals : '/='; // __adiv__
RightShiftEquals : '>>='; // __arshf__
LeftShiftEquals : '<<='; // __alshf__
PercentEquals : '%='; // __amod__
VBarEquals : '|='; // __aor__
AmperEquals : '&='; //__aand__
CaretEquals : '^='; // __axor__
DoubleStarEquals : '**='; // __apow__
TildeEquals : '~='; // __aneg__

LineComment
    : '#' ~[\r\n]*? '\n'
    ;

HS : [ \t]+ -> skip;
WS : (' ' | '\t' | '\r' | '\n') -> skip;

fragment HexDigit : ([0-9]|'a'..'f'|'A'..'F');
fragment BinDigit : [0-1];
fragment OctalDigit : [0-7];
fragment Digit : [0-9];



