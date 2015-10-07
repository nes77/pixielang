/* 
 * File:   lexer.hpp
 * Author: nsamson
 *
 * Created on September 17, 2015, 10:10 PM
 */

#ifndef PIXIE_LEXER_HPP
#define PIXIE_LEXER_HPP

#include "common.hpp"
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <exception>

//PIXIE_TOKEN(Then, R"(then)")

// <editor-fold desc="Token Definitions" defaultstate="collapsed"> 
#define PIXIE_TOKENS \
PIXIE_TOKEN(HexadecimalInteger, R"(0[xX][0-9a-zA-Z]+)") \
PIXIE_TOKEN(BinaryInteger, R"(0[bB][0-1]+)") \
PIXIE_TOKEN(OctalInteger, R"(0[oO][0-7]+)") \
PIXIE_TOKEN(Float, R"(\d+\.\d+)") \
PIXIE_TOKEN(DecimalInteger, R"(\d+)") \
PIXIE_TOKEN(QString, R"("(\\.|[^"])*")")\
PIXIE_TOKEN(AString, R"('(\\.|[^'])*')")\
PIXIE_TOKEN(Return, R"(return)")\
PIXIE_TOKEN(Assert, R"(assert)")\
PIXIE_TOKEN(Def, R"(def)")\
PIXIE_TOKEN(Class, R"(class)")\
PIXIE_TOKEN(If, R"(if)")\
PIXIE_TOKEN(Else, R"(else)")\
PIXIE_TOKEN(Elif, R"(elif)")\
PIXIE_TOKEN(Is, R"(is)")\
PIXIE_TOKEN(InstanceOf, R"(is a)")\
PIXIE_TOKEN(In, R"(in)")\
PIXIE_TOKEN(LessThan, R"(<)")\
PIXIE_TOKEN(LessEquals, R"(<=)")\
PIXIE_TOKEN(GreaterThan, R"(>)")\
PIXIE_TOKEN(GreaterEquals, R"(>=)")\
PIXIE_TOKEN(Equals, R"(==)")\
PIXIE_TOKEN(NotEquals, R"(!=)")\
PIXIE_TOKEN(Not, R"(not)")\
PIXIE_TOKEN(And, R"(and)")\
PIXIE_TOKEN(Or, R"(or)")\
PIXIE_TOKEN(Arrow, R"(->)")\
PIXIE_TOKEN(Import, R"(import)")\
PIXIE_TOKEN(For, R"(for)")\
PIXIE_TOKEN(While, R"(while)")\
PIXIE_TOKEN(Break, R"(break)")\
PIXIE_TOKEN(Continue, R"(continue)")\
PIXIE_TOKEN(SemiColon, R"(;)")\
PIXIE_TOKEN(Colon, R"(:)")\
PIXIE_TOKEN(Lambda, R"(\(\\)")\
PIXIE_TOKEN(LParens, R"(\()")\
PIXIE_TOKEN(RParens, R"(\))")\
PIXIE_TOKEN(LBrace, R"(\{)")\
PIXIE_TOKEN(RBrace, R"(\})")\
PIXIE_TOKEN(LBracket, R"(\[)")\
PIXIE_TOKEN(RBracket, R"(\])")\
PIXIE_TOKEN(LShift, R"(<<)")\
PIXIE_TOKEN(RShift, R"(>>)")\
PIXIE_TOKEN(Assign, R"(=)")\
PIXIE_TOKEN(PlusAssign, R"(\+=)")\
PIXIE_TOKEN(MinusAssign, R"(-=)")\
PIXIE_TOKEN(StarAssign, R"(\*=)")\
PIXIE_TOKEN(SlashAssign, R"(/=)")\
PIXIE_TOKEN(DoubleStarAssign, R"(\*\*=)")\
PIXIE_TOKEN(PercentAssign, R"(%=)")\
PIXIE_TOKEN(VBarAssign, R"(\|=)")\
PIXIE_TOKEN(AmperAssign, R"(&=)")\
PIXIE_TOKEN(LShiftAssign, R"(<<=)")\
PIXIE_TOKEN(RShiftAssign, R"(>>=)")\
PIXIE_TOKEN(CaretAssign, R"(\^=)") \
PIXIE_TOKEN(Plus, R"(\+)")\
PIXIE_TOKEN(Minus, R"(-)")\
PIXIE_TOKEN(DoubleStar, R"(\*\*)")\
PIXIE_TOKEN(Star, R"(\*)")\
PIXIE_TOKEN(Slash, R"(/)")\
PIXIE_TOKEN(Tilde, R"(~)")\
PIXIE_TOKEN(Percent, R"(%)")\
PIXIE_TOKEN(VBar, R"(\|)")\
PIXIE_TOKEN(Amper, R"(&)")\
PIXIE_TOKEN(Dot, R"(\.)")\
PIXIE_TOKEN(Caret, R"(\^)")\
PIXIE_TOKEN(Comma, R"(,)")\
PIXIE_TOKEN(True, R"(True)")\
PIXIE_TOKEN(False, R"(False)")\
PIXIE_TOKEN(None, R"(None)")\
PIXIE_TOKEN(Del, R"(del)")\
PIXIE_TOKEN(Identifier, R"([a-zA-Z][a-zA-Z0-9_]*)")\
PIXIE_TOKEN(Space, R"([ \r\t])")\
PIXIE_TOKEN(Comment, R"(#[^\r\n]*)")\
PIXIE_TOKEN(EOL, R"(\n)")
// </editor-fold>

namespace pixie {

    namespace compile {
        
        enum class PixieTokenType {
        #define PIXIE_TOKEN(x, y) x,
            PIXIE_TOKENS
        #undef PIXIE_TOKEN
        };
        
        std::string stringify(PixieTokenType);
        
        struct PixieToken {
            PixieTokenType type;
            std::string value;
            bool has_value;
            size_t line;
            size_t column;
            
            PixieToken(PixieTokenType, size_t, size_t, std::string);
            PixieToken(PixieTokenType, size_t, size_t);
            
            std::string to_string();
        };
        
        typedef std::vector<PixieToken> token_vec;
        
        class PixieTokenizer {
            
            size_t line;
            size_t column;
            std::vector<PixieToken> tokens;
            
        public:
            PixieTokenizer(std::string);
            
            token_vec::iterator begin();
            token_vec::iterator end();
            token_vec::const_iterator cbegin();
            token_vec::const_iterator cend();
        };
        
        class UnrecognizedTokenException : public std::exception {
            size_t line;
            size_t column;
            
        public:
            UnrecognizedTokenException(size_t line, size_t column);
            
            const char* what() const noexcept;
        };

        void _test_tokenizer(std::string);

    }
}

#endif