/* 
 * File:   lexer.hpp
 * Author: nsamson
 *
 * Created on September 17, 2015, 10:10 PM
 */

#pragma once

#include "common.hpp"
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_algorithm.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

namespace lex = boost::spirit::lex;
using namespace std;

namespace pixie {

    namespace compile {

        template <typename Lexer>
        struct PixieLexer : lex::lexer<Lexer> {

            size_t line;
            lex::token_def<std::string> HexadecimalInteger, BinaryInteger, OctalInteger,
                    DecimalInteger, Float, Identifier,
                    QString, AString;
            lex::token_def<> Return, Assert, Def, Class, If, Then, Else,
                    Elif, Is, InstanceOf, In,
                    LessThan, LessEquals, GreaterThan, GreaterEquals,
                    Equals, NotEquals,
                    Not, And, Or,
                    Plus, Minus, Star, Slash, DoubleStar, Tilde, Percent,
                    VBar, Amper, Dot,
                    Import,
                    For, While, Break, Continue,
                    SemiColon, Colon,
                    LParens, RParens,
                    LBrace, RBrace,
                    LBracket, RBracket,
                    LShift, RShift,
                    Assign, PlusAssign, MinusAssign, StarAssign,
                    SlashAssign, DoubleStarAssign, PercentAssign,
                    VBarAssign, AmperAssign, 
                    LShiftAssign, RShiftAssign,
                    Arrow, Comma;
            lex::token_def<lex::omit> Space, Comment, EOL;
            
            PixieLexer() :
                        line(1),
                        HexadecimalInteger("0[xX][0-9a-zA-Z]+"),
                        BinaryInteger("0[bB][01]+"),
                        OctalInteger("0[0-7]+"),
                        DecimalInteger("[0-9]+"),
                        Float("[0-9]+\\.[0-9]+"),
                        QString("\\\"([^\\\"\\r\\n]|\\\\\\\")*\\\""),
                        AString("'([^'\\r\\n]|\\\\')*'"),
                        Comment("#[^\\r\\n]*"),
                        Def("def"),
                        Assert("assert"),
                        Return("return"),
                        Class("class"),
                        Import("import"),
                        For("for"),
                        While("while"),
                        Break("break"),
                        Continue("continue"),
                        If("if"),
                        Then("then"),
                        Else("else"),
                        Elif("elif"),
                        Is("is"),
                        InstanceOf("instanceof"),
                        In("in"),
                        LessThan("<"),
                        LessEquals("<="),
                        GreaterThan(">"),
                        GreaterEquals(">="),
                        Equals("=="),
                        NotEquals("!="),
                        Not("not"),
                        And("and"),
                        Or("or"),
                        Comma(","),
                        Dot("[.]"),
                        Plus("[+]"),
                        Minus("-"),
                        Star("[*]"),
                        Slash("[/]"),
                        DoubleStar("[*][*]"),
                        Tilde("[~]"),
                        Percent("[%]"),
                        VBar("[|]"),
                        Amper("[&]"),
                        LShift("<<"),
                        RShift(">>"),
                        Assign("="),
                        PlusAssign("[+]="),
                        MinusAssign("-="),
                        StarAssign("[*]="),
                        SlashAssign("[/]="),
                        DoubleStarAssign("[*][*]="),
                        PercentAssign("[%]="),
                        VBarAssign("[|]="),
                        AmperAssign("&="),
                        LShiftAssign("<<="),
                        RShiftAssign(">>="),
                        Arrow("->"),
                        SemiColon(";"),
                        Colon("[:]"),
                        LParens("[(]"),
                        RParens("[)]"),
                        RBrace("[{]"),
                        LBrace("[}]"),
                        LBracket("\\["),
                        RBracket("\\]"),
                        Identifier("[a-zA-Z_][a-zA-Z0-9_]*"),
                        EOL("\\n"),
                        Space("[ \\t\\r]")
            {
                using lex::_pass;
                using lex::pass_flags;
                using boost::phoenix::ref;
                
                this->self
                        =   HexadecimalInteger
                        |   BinaryInteger
                        |   OctalInteger
                        |   DecimalInteger
                        |   Float
                        |   QString
                        |   AString
                        |   Comment            [_pass = pass_flags::pass_ignore]
                        |   Def
                        |   Assert
                        |   Return
                        |   Class
                        |   For
                        |   While
                        |   Break
                        |   Import              
                        |   Continue
                        |   If
                        |   Then
                        |   Else
                        |   Elif
                        |   Is
                        |   InstanceOf
                        |   In
                        |   LessThan
                        |   LessEquals
                        |   GreaterThan
                        |   GreaterEquals
                        |   Equals
                        |   NotEquals
                        |   Not
                        |   And
                        |   Or
                        |   Comma
                        |   Dot
                        |   Plus
                        |   Minus
                        |   Star
                        |   Slash
                        |   DoubleStar
                        |   Tilde
                        |   Percent
                        |   VBar
                        |   Amper
                        |   LShift
                        |   RShift
                        |   Assign
                        |   PlusAssign
                        |   MinusAssign
                        |   StarAssign
                        |   SlashAssign
                        |   DoubleStarAssign
                        |   PercentAssign
                        |   VBarAssign
                        |   AmperAssign
                        |   LShiftAssign
                        |   RShiftAssign
                        |   Arrow               
                        |   SemiColon
                        |   Colon
                        |   LParens
                        |   RParens
                        |   RBrace
                        |   LBrace
                        |   LBracket
                        |   RBracket
                        |   Identifier
                        |   EOL                [++ref(line),
                                                _pass = pass_flags::pass_ignore]
                        |   Space              [_pass = pass_flags::pass_ignore]
                        ;
            }
        };
        
        typedef lex::lexertl::token<
            std::string::iterator, boost::mpl::vector<std::string>
        > token_type;
        typedef lex::lexertl::actor_lexer<token_type> lexer_type;
        
        typedef PixieLexer<lexer_type> pixie_lexer;
        
        typedef pixie_lexer::iterator_type pixie_lexer_iterator;
        
        void _test_tokenizer(std::string);

    }
}

