%{
#include "lexer.hpp"
%}

DIGIT = [0-9]
HEXADIGIT = [0-9a-fA-F]
BINDIGIT = [0-1]
OCTDIGIT = [0-7]

IDENTIFIER = [a-zA-Z_][a-zA-Z0-9_]

WHITESPACE = [\t\b ]
EOL = [\n\r]

%%

{DIGIT}+

0x{HEXADIGIT}+

0b{BINDIGIT}+

0o{OCTDIGIT}+




