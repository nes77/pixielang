#include "lexer.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include <boost/regex.hpp>

using namespace pixie::compile;

typedef std::pair<PixieTokenType, boost::regex> pair_type;
typedef std::vector<pair_type> token_regex_list;

token_regex_list regex_map() {
    token_regex_list out;

#define PIXIE_TOKEN(x, y) out.push_back(pair_type(PixieTokenType::x, boost::regex(std::string(y))));
    PIXIE_TOKENS
#undef PIXIE_TOKEN

    return out;
}

void pixie::compile::_test_tokenizer(std::string filename) {

    std::ifstream fin;
    fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::stringstream ss;

    try {
        fin.open(filename.c_str(), std::ios::in);
        ss << fin.rdbuf();
        fin.close();
    } catch (std::ifstream::failure e) {
        std::cerr << "Could not read file " << filename << "\n";
        throw;
    }

    std::string f_contents;

    f_contents = ss.str();

    PixieTokenizer tokenizer(f_contents);
    
    for (auto& token : tokenizer) {
        std::cout << token.to_string() << "\n";
    }
    
}

token_vec::iterator PixieTokenizer::begin() {
    return this->tokens.begin();
}

token_vec::iterator PixieTokenizer::end() {
    return this->tokens.end();
}

token_vec::const_iterator PixieTokenizer::cbegin() {
    return this->tokens.cbegin();
}

token_vec::const_iterator PixieTokenizer::cend() {
    return this->tokens.cend();
}


std::string pixie::compile::stringify(PixieTokenType type) {
    switch (type) {
#define PIXIE_TOKEN(x, y) case PixieTokenType::x: return #x;
            PIXIE_TOKENS
#undef PIXIE_TOKEN
                default:
            throw;
    }
}

PixieToken::PixieToken(
        PixieTokenType type, size_t line,
        size_t column, std::string value)
: type(type), line(line), column(column),
value(value), has_value(true) {
}

PixieToken::PixieToken(PixieTokenType type, size_t line, size_t column)
: type(type), line(line), column(column), has_value(false) {
}

std::string PixieToken::to_string() {
    std::stringstream ss;

    ss << "[" << stringify(this->type) << ":"
            << line << ":" << column;

    if (this->has_value) {
        ss << ":" << value;
    }

    ss << "]";

    return ss.str();
}

UnrecognizedTokenException::UnrecognizedTokenException(size_t line, size_t column)
: line(line), column(column) {
}

const char* UnrecognizedTokenException::what() const noexcept {
    std::stringstream oss;

    oss << "Could not recognize input at " << line << ":" << column << "\n";

    return oss.str().c_str();
}

PixieTokenizer::PixieTokenizer(std::string code) : line(1), column(1) {

    std::string remaining_code(code);

    auto regexes = regex_map();

    while (remaining_code.length() > 0) {
        boost::match_results<std::string::const_iterator> match;
        bool found = false;
        for (auto &pair : regexes) {
            if (boost::regex_search(remaining_code, match, pair.second, boost::match_continuous)) {
                found = true;
                switch (pair.first) {
                    case PixieTokenType::AString:
                    case PixieTokenType::BinaryInteger:
                    case PixieTokenType::DecimalInteger:
                    case PixieTokenType::HexadecimalInteger:
                    case PixieTokenType::Identifier:
                    case PixieTokenType::OctalInteger:
                    case PixieTokenType::Float:
                    case PixieTokenType::QString:
                    {
                        std::string value = match.str();
                        PixieToken tok(pair.first, this->line, this->column, value);
                        this->tokens.push_back(tok);
                        this->column += value.length();
                        remaining_code = remaining_code.substr(value.length());
                    }
                        break;

                    case PixieTokenType::Space:
                    {
                        this->column += 1;
                        remaining_code = remaining_code.substr(1);
                    }
                        break;

                    case PixieTokenType::EOL:
                    {
                        this->column = 1;
                        this->line++;
                        remaining_code = remaining_code.substr(1);
                    }
                        break;

                    case PixieTokenType::Comment:
                    {
                        remaining_code = remaining_code.substr(match.str().length());
                    }
                        break;

                    default:
                    {
                        PixieToken tok(pair.first, this->line, this->column);
                        this->tokens.push_back(tok);
                        this->column += match.str().length();
                        remaining_code = remaining_code.substr(match.str().length());
                    }
                        break;

                }
                break;
            }
        }

        if (!found) {
            throw UnrecognizedTokenException(this->line, this->column);
        }
    }

}
