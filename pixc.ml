let load_file f =
  let ic = open_in f in
  let n = in_channel_length ic in
  let s = String.create n in
  really_input ic s 0 n;
  close_in ic;
  (s)

let parse s =
  let lexbuf = Lexing.from_string s in
  Parser.modul Lexer.read lexbuf

let parse_file f =
  load_file f |> parse
