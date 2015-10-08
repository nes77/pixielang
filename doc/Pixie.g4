grammar Pixie;

goal: (statement | class_def | func_def)*;

statement: simple_stmt
         | compound_stmt;

compound_stmt: '{' simple_stmt* '}';

simple_stmt: expr_stmt
        | import_stmt
        | assert_stmt
        | selection_stmt
        ;

expr_stmt: ';'
         | expr ';'

atom:   '(' expr ')'
      | literal
      | Identifier;

literal: HexadecimalInteger
       | OctalInteger
       | BinaryInteger
       | Float
       | DecimalInteger
       | QString
       | AString;

HexadecimalInteger : '0' [xX] ('a'..'f' | 'A'..'F' | '0'..'9')+;
OctalInteger : '0' [oO] ('0'..'7')+;
BinaryInteger : '0' [oO] [01]+;
Float : ('0'..'9')+ '.' ('0'..'9')+;
DecimalInteger : ('0'..'9')+;
QString : '"' ('\\'. | [^"])* '"';
AString : '\'' ('\\'. | [^'])* '\'';

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
SemiColon : ';';
Colon : ':';
Lambda : '(\\';
LParens : '(';
RParens : ')';
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

