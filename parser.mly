
%{
open Ast
%}



%token <string> INT
%token <string> FLOAT
%token <string> IDENT
%token <string> STRING
%token <char> CHAR
%token TRUE
%token FALSE
%token NIL

%token LPAREN
%token RPAREN
%token LBRACE
%token RBRACE
%token LBRACK
%token RBRACK
%token DICTBEGIN
%token ARROW

%token COMMA
%token COLON

%token ASSIGN

%token ATTRASSIGN

%token NOT
%token TILDE

%token PLUS
%token MINUS
%token STAR
%token SLASH
%token CARET
%token AMPERSAND
%token VBAR
%token LSHF
%token RSHF
%token AND
%token OR
%token IS
%token ISNOT
%token NOTIN
%token IN
%token ISA
%token DOT
%token DOUBLESTAR
%token EQ
%token NEQ
%token LEQ
%token GEQ
%token LT
%token GT
%token MOD

%token ELIPSIS

%token FUNC
%token AFUN

%token ASSERT
%token RAISE
%token TRY
%token CATCH
%token FINALLY
%token WITH
%token IMPORT
%token TYPE
%token RETURN
%token SWITCH
%token CASE
%token IF
%token ELSE
%token FOR
%token WHILE
%token CALL
%token DEFAULT

%token EOF

%nonassoc THEN
%nonassoc ELSE

%left OR AND
%right NOT
%left IN NOTIN
%left IS ISNOT ISA
%left EQ NEQ
%left LEQ GEQ GT LT
%left CARET VBAR
%left AMPERSAND
%left LSHF RSHF
%left PLUS MINUS
%left STAR SLASH MOD
%right TILDE UN_MINUS
%right DOUBLESTAR

%start <Ast.pix_module> modul
%%

modul:
    s = list(stmt); EOF { {name=ref ""; contents=s} }
    | EOF { {name=ref "";contents=[]} };

stmt:
    LBRACE; s = ioption(list(stmt)); RBRACE { StatementBlock (match s with Some l -> l | _ -> []) }
    | IMPORT; imps = separated_nonempty_list(COMMA, IDENT) { ImportStmt (imps) }
    | FUNC; recv = ioption(delimited(LPAREN, recv_arg, RPAREN));
     n = IDENT; args = delimited(LPAREN, darg_list, RPAREN); ARROW; s = stmt
    {FuncDecl (recv,n,args,s)}
    | TYPE; n = IDENT; args = delimited(LPAREN, darg_list, RPAREN);
    sups = ioption(preceded(COLON, separated_list(COMMA, expr))); ARROW; s = stmt
    {TypeDecl (n,args,(match sups with Some e -> e | None -> []),s)}
    | ASSERT; e = expr { AssertStmt e }
    | e = expr; ASSIGN; e2 = expr { AssignStmt (e, e2)}
    | RAISE; e = expr; { RaiseStmt e }
    | RETURN; e = expr; { ReturnStmt e }
    | e = expr; ATTRASSIGN; e2 = expr { AttrAssignStmt (e, e2) }
    | SWITCH; e = delimited(LPAREN, expr, RPAREN);
        cases = delimited(LBRACE, list(switch_case), RBRACE);
        { SwitchStmt (e, cases) }
    | IF; LPAREN; e = expr; RPAREN; s = stmt { IfElseStmt (e,s,None) } %prec THEN
    | IF; LPAREN; e = expr; RPAREN; s = stmt; ELSE; s2 = stmt { IfElseStmt (e, s, (Some s2))}
    | TRY; s1 = stmt; c = list(catch_block); s2 = option(finally_block) { TryCatchFinallyStmt (s1,c,s2) }
    | CALL; f = expr; LPAREN; al = farg_list; RPAREN { CallStmt (f,al) }
    | FOR; LPAREN; i = IDENT; IN; e = expr; RPAREN; s = stmt; { ForStmt (Var (i), e, s) }
    | WHILE; LPAREN; e = expr; RPAREN; s = stmt; { WhileStmt (e,s) }
    | WITH; LPAREN; e = expr; RPAREN; s = stmt; { WithStmt (e,s) }

darg_list: s = separated_list(COMMA, decl_arg) {s}
farg_list: s = separated_list(COMMA, func_arg) {s}

catch_block:
    CATCH; LPAREN; i = IDENT; COLON; ty = IDENT; RPAREN; s = stmt;
        { ((i,ty), s) }

finally_block:
    FINALLY; s = stmt;
        {s}

switch_case:
    CASE; LPAREN; e = expr; RPAREN; s = stmt { Case (e,s) }
    | DEFAULT; s = stmt { Default s }

expr:
    i = IDENT { Var i }
    | AFUN; args = delimited(LPAREN, darg_list, RPAREN); ARROW; s = stmt { AFun (args, s) }
    | i = INT; { IntLit (Big_int.big_int_of_string i) }
    | f = FLOAT; { FloatLit (float_of_string f) }
    | TRUE; { BoolLit (true) }
    | FALSE; { BoolLit (false) }
    | c = CHAR; { CharLit (c) }
    | s = STRING; { StrLit (s) }
    | NIL; { NilLit }
    | LPAREN; e = expr; RPAREN { e }
    | e1 = expr; PLUS; e2 = expr { BinOp(e1, Plus, e2) }
    | e1 = expr; MINUS; e2 = expr { BinOp(e1, Minus, e2) }
    | e1 = expr; STAR; e2 = expr { BinOp(e1, Star, e2) }
    | e1 = expr; SLASH; e2 = expr { BinOp(e1, Slash, e2) }
    | e1 = expr; CARET; e2 = expr { BinOp(e1, Caret, e2) }
    | e1 = expr; AMPERSAND; e2 = expr { BinOp(e1, Ampersand, e2) }
    | e1 = expr; MOD; e2 = expr { BinOp(e1, Mod, e2) }
    | e1 = expr; VBAR; e2 = expr { BinOp(e1, VBar, e2) }
    | e1 = expr; LSHF; e2 = expr { BinOp(e1, LShf, e2) }
    | e1 = expr; RSHF; e2 = expr { BinOp(e1, RShf, e2) }
    | e1 = expr; AND; e2 = expr { BinOp(e1, And, e2) }
    | e1 = expr; OR; e2 = expr { BinOp(e1, Or, e2) }
    | e1 = expr; IS; e2 = expr { BinOp(e1, Is, e2) }
    | e1 = expr; ISNOT; e2 = expr { BinOp(e1, IsNot, e2) }
    | e1 = expr; ISA; e2 = expr { BinOp(e1, IsA, e2) }
    | e1 = expr; IN; e2 = expr { BinOp(e1, In, e2) }
    | e1 = expr; NOTIN; e2 = expr { BinOp(e1, NotIn, e2) }
    | e1 = expr; DOT; e2 = IDENT { BinOp(e1, Dot, (Var e2)) }
    | e1 = expr; DOUBLESTAR; e2 = expr { BinOp(e1, DoubleStar, e2) }
    | e1 = expr; EQ; e2 = expr { BinOp(e1, Eq, e2) }
    | e1 = expr; NEQ; e2 = expr { BinOp(e1, Neq, e2) }
    | e1 = expr; LEQ; e2 = expr { BinOp(e1, Leq, e2) }
    | e1 = expr; GEQ; e2 = expr { BinOp(e1, Geq, e2) }
    | e1 = expr; LT; e2 = expr { BinOp(e1, Lt, e2) }
    | e1 = expr; GT; e2 = expr { BinOp(e1, Gt, e2) }
    | NOT; e = expr; { UnOp (Not,e) }
    | TILDE; e = expr; { UnOp (Tilde,e) }
    | MINUS; e = expr; { UnOp (Neg,e) } %prec UN_MINUS
    | LBRACK; ls = separated_list(COMMA, expr); RBRACK { ListLiteral (ls) }
    | DICTBEGIN; ds = separated_list(COMMA, dict_entry); RBRACE { DictLiteral (ds) }
    | f = expr; LPAREN; al = farg_list; RPAREN { CallExpr (f,al) }
    | e = expr; LBRACK; index = expr; RBRACK; { IndexExpr (e, index) }

dict_entry:
    e1 = expr; COLON; e2 = expr { (e1, e2) }

decl_arg:
    i = IDENT; { Arg i }
    | i = IDENT; COLON; ty = IDENT; { AnnotArg ((i,ty)) }
    | i = IDENT; ASSIGN; e = expr; { DefaultArg (i, e) }
    | i = IDENT; ELIPSIS {ElipsisDeclArg (i)}

func_arg:
    e = expr; { ExprArg (e) }
    | i = IDENT; ASSIGN; e = expr; { NamedArg (i,e) }
    | e = expr; ELIPSIS { ElipsisArg (e) }

recv_arg:
    i = IDENT; COLON; ty = IDENT; { (i,ty) }
