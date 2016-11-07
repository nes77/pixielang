{
open Lexing
open Parser

exception SyntaxError of string

let next_line lexbuf =
  let pos = lexbuf.lex_curr_p in
  lexbuf.lex_curr_p <-
    { pos with pos_bol = lexbuf.lex_curr_pos;
               pos_lnum = pos.pos_lnum + 1
    }
}

let bin_digit = '0' | '1'
let oct_digit = bin_digit | ['2'-'7']
let digit = oct_digit | '8' | '9'
let hex_digit = digit | ['a'-'f' 'A'-'F']

let int = digit+ |"0x" hex_digit+ | "0b" bin_digit+ | "0o" oct_digit+

let frac = '.' digit+
let exp = ['e' 'E']['-' '+']? digit+

let float = digit+ frac? exp?

let white_space = [' ']+
let newline = 'r' | '\n' | "\r\n"
let ident = ['a'-'z' 'A'-'Z' '_'] ['a'-'z' 'A'-'Z' '0'-'9' '_']*
let comment = "#" [^ '\r' '\n']*

rule read =
    parse
    | white_space { read lexbuf }
    | comment { read lexbuf }
    | newline {next_line lexbuf; read lexbuf }
    | int { INT (Lexing.lexeme lexbuf) }
    | float { FLOAT (Lexing.lexeme lexbuf) }
    | "'" { read_char (Buffer.create 1) lexbuf }
    | '"' { read_string (Buffer.create 16) lexbuf }
    | "true" { TRUE }
    | "false" { FALSE }
    | "nil" { NIL }
    | "d{" { DICTBEGIN }
    | "->" { ARROW }
    | "(" { LPAREN }
    | ")" { RPAREN }
    | "{" { LBRACE }
    | "}" { RBRACE }
    | "[" { LBRACK }
    | "]" { RBRACK }
    | "," { COMMA }
    | ":=" { ATTRASSIGN }
    | "not" { NOT }
    | "~" { TILDE }
    | "+" { PLUS }
    | "-" { MINUS }
    | "*" { STAR }
    | "/" { SLASH }
    | "^" { CARET }
    | "%" { MOD }
    | "&" { AMPERSAND }
    | "|" { VBAR }
    | "<<" { LSHF }
    | ">>" { RSHF }
    | "and" { AND }
    | "or" { OR }
    | "is" { IS }
    | "is not" { ISNOT }
    | "not in" { NOTIN }
    | "in" { IN }
    | "isinstance" { ISA }
    | "." { DOT }
    | "**" { DOUBLESTAR }
    | "==" { EQ }
    | "!=" { NEQ }
    | "<=" { LEQ }
    | ">=" { GEQ }
    | "<" { LT }
    | ">" { GT }
    | ":" { COLON }
    | "=" { ASSIGN }
    | "..." { ELIPSIS }
    | "call" { CALL }
    | "func" { FUNC }
    | "function" { AFUN }
    | "assert" { ASSERT }
    | "raise" { RAISE }
    | "try" { TRY }
    | "catch" { CATCH }
    | "finally" { FINALLY }
    | "with" { WITH }
    | "import" { IMPORT }
    | "type" { TYPE }
    | "return" { RETURN }
    | "switch" { SWITCH }
    | "case" { CASE }
    | "if" { IF }
    | "else" { ELSE }
    | "default" { DEFAULT }
    | "for" { FOR }
    | "while" { WHILE }
    | ident { IDENT (Lexing.lexeme lexbuf) }
    | _ { raise (SyntaxError ("Unexpected char: " ^ Lexing.lexeme lexbuf))}
    | eof { EOF }
and read_string buf =
    parse
    | '"' { STRING (Buffer.contents buf) }
    | '\\' '/' { Buffer.add_char buf '/'; read_string buf lexbuf }
    | '\\' '\\' { Buffer.add_char buf '\\'; read_string buf lexbuf }
    | '\\' 'b' { Buffer.add_char buf '\b'; read_string buf lexbuf }
    | '\\' 'f' { Buffer.add_char buf '\012'; read_string buf lexbuf }
    | '\\' 'n' { Buffer.add_char buf '\n'; read_string buf lexbuf }
    | '\\' 't' { Buffer.add_char buf '\t'; read_string buf lexbuf }
    | [^ '"' '\\']+
     {
         Buffer.add_string buf (Lexing.lexeme lexbuf);
         read_string buf lexbuf
     }
    | _ { raise (SyntaxError ("Illegal string character: " ^ Lexing.lexeme lexbuf)) }
    | eof { raise (SyntaxError ("String is not terminated at end of file."))}
and read_char buf =
    parse
    | "'" {
        if Buffer.length buf = 1 then CHAR (Buffer.nth buf 0)
        else raise (SyntaxError ("Illegal string literal: " ^ (Buffer.contents buf)))
    }
    | '\\' '/' { Buffer.add_char buf '/'; read_char buf lexbuf }
    | '\\' '\\' { Buffer.add_char buf '\\'; read_char buf lexbuf }
    | '\\' 'b' { Buffer.add_char buf '\b'; read_char buf lexbuf }
    | '\\' 'f' { Buffer.add_char buf '\012'; read_char buf lexbuf }
    | '\\' 'n' { Buffer.add_char buf '\n'; read_char buf lexbuf }
    | '\\' 't' { Buffer.add_char buf '\t'; read_char buf lexbuf }
    | _ { raise (SyntaxError ("Illegal char character: " ^ Lexing.lexeme lexbuf)) }
    | eof { raise (SyntaxError ("Character is not terminated at end of file."))}
