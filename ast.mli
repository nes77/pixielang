type ident = string

type pix_int = Big_int.big_int
type pix_num = float

type annotated_arg = ident * ident

type statement =
  | StatementBlock of statement list
  | ImportStmt of ident list
  | FuncDecl of annotated_arg option * ident * decl_arg list * statement
  | TypeDecl of ident * decl_arg list * expr list * statement
  | AssertStmt of expr
  | AssignStmt of expr * expr
  | RaiseStmt of expr
  | ReturnStmt of expr
  | AttrAssignStmt of expr * expr
  | SwitchStmt of expr * switch_case list
  | IfElseStmt of expr * statement * statement option
  | TryCatchFinallyStmt of statement * catch_block list * statement option
  | CallStmt of expr * func_arg list
  | ForStmt of expr * expr * statement
  | WhileStmt of expr * statement
  | WithStmt of expr * statement
and switch_case = Case of expr * statement | Default of statement
and expr =
  | Var of ident
  | AFun of decl_arg list * statement
  | IntLit of pix_int
  | FloatLit of pix_num
  | BoolLit of bool
  | CharLit of char
  | StrLit of string
  | NilLit
  | BinOp of expr * operator * expr
  | UnOp of unary_op * expr
  | CallExpr of expr * func_arg list
  | IndexExpr of expr * expr
  | ListLiteral of expr list
  | DictLiteral of (expr * expr) list
and decl_arg =
  | Arg of ident
  | AnnotArg of annotated_arg
  | DefaultArg of ident * expr
  | ElipsisDeclArg of ident
and func_arg =
  | ExprArg of expr
  | NamedArg of ident * expr
  | ElipsisArg of expr
and operator =
  | Plus
  | Minus
  | Star
  | Slash
  | Caret
  | Ampersand
  | Mod
  | VBar
  | LShf
  | RShf
  | And
  | Or
  | Is
  | IsNot
  | NotIn
  | In
  | IsA
  | Dot
  | DoubleStar
  | Eq
  | Neq
  | Leq
  | Geq
  | Lt
  | Gt
and unary_op =
  | Not
  | Neg
  | Tilde
and catch_block = (annotated_arg * statement)

type pix_module = {
  name : string ref;
  contents : statement list;
}

val is_lexpr : expr -> bool

(* val format_module : Format.formatter -> pix_module -> unit
val format_switch_case : Format.formatter -> switch_case -> unit
val format_expr : Format.formatter -> expr -> unit
val format_decl_arg : Format.formatter -> decl_arg -> unit
val format_func_arg : Format.formatter -> func_arg -> unit
val format_operator : Format.formatter -> operator -> unit
val format_unary_op : Format.formatter -> unary_op -> unit
val format_catch_block : Format.formatter -> catch_block -> unit

val string_of_module : pix_module -> string
val string_of_switch_case : switch_case -> string
val string_of_expr : expr -> string
val string_of_decl_arg : decl_arg -> string
val string_of_func_arg : func_arg -> string
val string_of_operator : operator -> string
val string_of_unary_op : unary_op -> string
val string_of_catch_block : catch_block -> string *)
