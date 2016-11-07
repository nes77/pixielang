all:
	ocamlbuild -use-menhir -pkgs num pixc.byte

clean:
	ocamlbuild -clean
