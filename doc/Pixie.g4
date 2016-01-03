grammar Pixie;

goal: (statement | class_def | func_def)*;

statement: simple_stmt
         | compound_stmt;

compound_stmt: '{' simple_stmt* '}';

simple_stmt: expr_stmt
        | import_stmt
        | assert_stmt
        | return_stmt
        | assign_stmt
        ;

dotted_identifier: Identifier ('.' Identifier)*;

class_def: 'class' Identifier '(' class_def_args? ')' class_def_body;

class_def_args:
                  dotted_identifier (',' dotted_identifier)*;
                  
class_def_body: '{' ('static' compound_stmt)? ('static'? func_def)* '};';

func_def:
            'def' Identifier '(' func_def_args ')' compound_stmt;

func_call_args: expr (',' expr);

lambda:
          '(\\' func_def_args '->' expr ')';

func_def_args: (Identifier
             | '*' Identifier
             | '**' Identifier)(',' func_def_args)*;

import_stmt:
           'import' dotted_identifier (',' dotted_identifier)* ';'
           | 'import' dotted_identifier 'as' Identifier ';'
           | 'from' dotted_identifier import_stmt
           | 'from' ('.')+ import_stmt;

assert_stmt: 'assert' expr ';';

return_stmt: 'return' expr ';';

assign_stmt: dotted_identifier assignment_operator expr ';';

expr_stmt: ';'
         | expr ';';

expr: 
        or_expr ('if' or_expr 'else' expr)?
    |   lambda;
        
or_expr: and_expr ('or' and_expr)*;

and_expr: not_expr ('and' not_expr)*;

not_expr: 'not' not_expr
        | comp_expr;

comp_expr: star_expr (comp_operator star_expr)*;

star_expr: '*'? vbar_expr;

vbar_expr: xor_expr ('|' xor_expr)*;

xor_expr: amper_expr ('^' amper_expr)*;

amper_expr: shift_expr ('&' shift_expr)*;

shift_expr: arith_expr (( '<<' | '>>' ) arith_expr)*;

arith_expr: mult_expr (( '+' | '-' ) mult_expr)*;

mult_expr: unary_expr (( '*' | '/' | '%' ) unary_expr)*;

unary_expr: ('+' | '-' | '~') unary_expr
            | dbl_star_expr
          ;

dbl_star_expr: atom trailer* ('**' unary_expr)?;
               
atom: dotted_identifier
    | literal
    | None
    | True
    | False
    ;

trailer: '(' func_call_args? ')'
       | '[' subscript_list ']';

subscript_list: subscript (',' subscript)*;

subscript: expr
         | expr? ':' expr? slice_op?
         ;

slice_op: ':' expr?
        ;

comp_operator: Is
       | In
       | Not In
       | Is Not
       | LessThan
       | LessEquals
       | GreaterThan
       | GreaterEquals
       | Equals
       | NotEquals;
        

literal: HexadecimalInteger
       | OctalInteger
       | BinaryInteger
       | Float
       | DecimalInteger
       | QString
       | AString;

assignment_operator:
                     Assign
                   | PlusAssign
                   | MinusAssign
                   | StarAssign
                   | SlashAssign
                   | DoubleStarAssign
                   | PercentAssign
                   | VBarAssign
                   | AmperAssign
                   | LShiftAssign
                   | RShiftAssign
                   | CaretAssign;

HexadecimalInteger : '0' [xX] ('a'..'f' | 'A'..'F' | '0'..'9')+;
OctalInteger : '0' [oO] ('0'..'7')+;
BinaryInteger : '0' [oO] [01]+;
Float : ('0'..'9')+ '.' ('0'..'9')+;
DecimalInteger : ('0'..'9')+;
QString : '"' ('\\'. | [^"\\\r\n])* '"';
AString : '\'' ('\\'. | [^'\\\r\n])* '\'';

Return : 'return';
Assert : 'assert';
Def : 'def';
Class : 'class';
If : 'if';
Else : 'else';
Elif : 'elif';
Is : 'is';
In : 'in';
LessThan : '<';
LessEquals : '<=';
GreaterThan : '>';
GreaterEquals : '>=';
Equals : '==';
NotEquals : '!=';
Not : 'not';
And : 'and';
Or : 'or';
Arrow : '->';
Import : 'import';
For : 'for';
While : 'while';
Break : 'break';
Continue : 'continue';
From: 'from';
Static: 'static';
As: 'as';
SemiColon : ';';
Colon : ':';
Lambda : '(\\';
LParens : '(';
RParens : ')';
LBraceSemi : '};';
LBrace : '{';
RBrace : '}';
LBracket : '[';
RBracket : ']';
LShift : '<<';
RShift : '>>';
Assign : '=';
PlusAssign : '+=';
MinusAssign : '-=';
StarAssign : '*=';
SlashAssign : '/=';
DoubleStarAssign : '**=';
PercentAssign : '%=';
VBarAssign : '|=';
AmperAssign : '&=';
LShiftAssign : '<<=';
RShiftAssign : '>>=';
CaretAssign : '^=';
Plus : '+';
Minus : '-';
DoubleStar : '**';
Star : '*';
Slash : '/';
Tilde : '~';
Percent : '%';
VBar : '|';
Amper : '&';
Dot : '.';
Caret : '^';
Comma : ',';
True : 'True';
False : 'False';
None : 'None';
Del : 'del';
Identifier : ('a'..'z' | 'A'..'Z'| '_')('a'..'z' | 'A'..'Z'| '_' | '0'..'9')*;
Space : [ \r\t] -> skip;
Comment : '#' [^\r\n]* -> skip;
EOL : '\n' -> skip;
