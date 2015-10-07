#include "lexer.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <boost/bind/placeholders.hpp>
#include <iostream>

namespace lex = boost::spirit::lex;

void pixie::compile::_test_tokenizer(std::string filename) {

    std::ifstream fin;
    fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::stringstream ss;
    
    try {
        fin.open(filename.c_str(), std::ios::in);
        ss << fin.rdbuf();
        fin.close();
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Could not read file " << filename << "\n";
        throw;
    }

    std::string f_contents;
    
    f_contents = ss.str();
    
    pixie::compile::pixie_lexer tokens;
    pixie::compile::PixieLexerPrinter pprinter(tokens.id_map());
    
    std::string::iterator it = f_contents.begin();
    try {
        bool r = lex::tokenize(it, f_contents.end(), tokens,
                pprinter);

        if(r) {
            std::cout << "SUCCESS!" << "\n";
            std::cout << tokens.line << "\n";
        } else {
            std::cerr << "FAILURE." << "\n";

            std::string rest(it, f_contents.end());

            std::cerr << "Lexing failed\nstopped at: \n"
                    << rest << "\n";
        }
    }
    catch (...) {
        std::string rest(it, f_contents.end());

        std::cerr << "Lexing failed\nstopped at: \n"
                << rest << "\n";
        throw;
    }
    
}