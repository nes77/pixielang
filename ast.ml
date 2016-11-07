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

let is_lexpr = function
  | Var _
  | IndexExpr (_, _) -> true
  | _ -> false

(*
val format_module : Format.formatter -> pix_module -> unit
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
val string_of_catch_block : catch_block -> string
*)

let string_repeat s n =
  let len = Bytes.length s in
  let res = Bytes.create(n * len) in
  for i = 0 to pred n do
    Bytes.blit s 0 res (i * len) len
  done;
  Bytes.to_string res (* not stricly necessary, the bytes type is equivalent to string except mutability *)
;;

let plevel l =
  string_repeat " " (l*4)

let string_of_unary_op = function
  | Not -> "not"
  | Neg -> "-"
  | Tilde -> "~"

let string_of_operator = function
  | Plus -> "+"
  | Minus -> "-"
  | Star -> "*"
  | Slash -> "/"
  | Caret -> "^"
  | Ampersand -> "&"
  | Mod -> "%"
  | VBar -> "|"
  | LShf -> "<<"
  | RShf -> ">>"
  | And -> "and"
  | Or -> "or"
  | Is -> "is"
  | IsNot -> "is not"
  | NotIn -> "not in"
  | In -> "in"
  | IsA -> "instanceof"
  | Dot -> "."
  | Eq -> "=="
  | Neq -> "!="
  | Leq -> "<="
  | Geq -> ">="
  | Lt -> "<"
  | Gt -> ">"
  | DoubleStar -> "**"

let rec smod m =
  Printf.sprintf "Module %s\n%s" !(m.name) (sstmt 0 (StatementBlock (m.contents)))
and sstmt l = function
  | StatementBlock sb ->
      begin
        let stmt_strs = List.map (sstmt (l+1)) sb in
        let stmt_str = String.concat ("\n") stmt_strs in
        (plevel l) ^ (Printf.sprintf "(%s)" stmt_str)
      end
  | ImportStmt il ->
      begin
        let stmt_str = String.concat " " il in
        (plevel l) ^ (Printf.sprintf "(import %s)" stmt_str)
      end
  | FuncDecl (r,n,ar,st) ->
      begin
        let recv = match r with
          | None -> ""
          | Some (a,t) -> Printf.sprintf " (%s %s) " t a in
        let argsl = List.map (sdecl_arg (l+1)) ar in
        let args_str = String.concat " " argsl in
        (plevel l) ^ (Printf.sprintf "(func%s%s %s\n%s)" recv n args_str (sstmt (l+1) st))
      end
  | AssertStmt e ->
      (plevel l) ^ (Printf.sprintf "(assert %s)" (sexpr (l+1) e))
  | AssignStmt (e1,e2) ->
      (plevel l) ^ (Printf.sprintf "(= %s %s)" (sexpr (l+1) e1) (sexpr (l+1) e2))
  | RaiseStmt e ->
      (plevel l) ^ (Printf.sprintf "(raise %s)" (sexpr (l+1) e))
  | ReturnStmt e ->
      (plevel l) ^ (Printf.sprintf "(return %s)" (sexpr (l+1) e))
  | AttrAssignStmt (e1, e2) ->
      (plevel l) ^ (Printf.sprintf "(:= %s %s)" (sexpr (l+1) e1) (sexpr (l+1) e2))

and sdecl_arg l = function
  | Arg x -> x
  | AnnotArg (a,t) -> Printf.sprintf "(%s %s)" t a
  | DefaultArg (a,e) -> Printf.sprintf "(default %s %s)" a (sexpr (l+1) e)
  | ElipsisDeclArg a -> Printf.sprintf "(%s ...)" a
and sexpr l = function
  | Var v -> v
  | IntLit i -> Big_int.string_of_big_int i
  | FloatLit f -> string_of_float f
  | BoolLit b -> string_of_bool b
  | CharLit c -> Char.escaped c
  | StrLit s -> String.escaped s
  | NilLit -> "nil"
  | ListLiteral ls ->
      begin
        let strs = List.map (sexpr (l+1)) ls in
        let s = String.concat " " strs in
        Printf.sprintf "(%s)" s
      end
  | DictLiteral dl ->
      begin
        let s1, s2 = List.split dl in
        let c = List.map (sexpr (l+1)) in
        let ls1, ls2 = c s1, c s2 in
        let dl = List.combine ls1 ls2 in
        let strls = List.map (fun (k,v) -> Printf.sprintf "(%s -> %s)" k v) dl in
        let s = String.concat " " strls in
        Printf.sprintf "(%s)" s
      end
  | IndexExpr (e,i) ->
      begin
        let es = sexpr (l+1) e in
        let is = sexpr (l+1) i in
        Printf.sprintf "([] %s %s)" es is
      end
  | CallExpr (e, al) ->
      begin
        let es = sexpr (l+1) e in
        let als = List.map (sfunc_arg (l+1)) al in
        let a = String.concat " " als in
        Printf.sprintf "(%s %s)" es a
      end
  | BinOp (e1,o,e2) ->
      begin
        let spaces = plevel l in
        let os = string_of_operator o in
        let e1s = sexpr (l+1) e1 in
        let e2s = sexpr (l+1) e2 in
        Printf.sprintf "(%s\n%s%s\n%s%s)" os spaces e1s spaces e2s
      end
  | UnOp (o,e) ->
      begin
        let os = string_of_unary_op o in
        let es = sexpr (l+1) e in
        Printf.sprintf "(%s %s)" os es
      end
  | AFun (dl, s) ->
      begin
        let argsl = List.map (sdecl_arg (l+1)) dl in
        let args_str = String.concat " " argsl in
        let ss = sstmt (l+1) s in
        Printf.sprintf "(lambda (%s) %s)" args_str ss
      end
and sfunc_arg l = function
  | ExprArg a -> sexpr (l+1) a
  | NamedArg (nam,a) -> Printf.sprintf "(= %s %s)" nam (sexpr (l+1) a)
  | ElipsisArg a -> Printf.sprintf "(%s ...)" (sexpr (l+1) a)
