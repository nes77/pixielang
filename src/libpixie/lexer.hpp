/* 
 * File:   lexer.hpp
 * Author: nsamson
 *
 * Created on September 17, 2015, 10:10 PM
 */

#ifndef PIXIE_LEXER_HPP
#define PIXIE_LEXER_HPP

#include "common.hpp"
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_algorithm.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <string>
#include <map>
#include <iostream>

#define COMP_TOK(x, name) case x: {print_token(name, t.value());} break
#define COMP_TOK_N(x, name) case x: {print_token(name);} break

namespace pixie {

    namespace compile {

        namespace lex = boost::spirit::lex;

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
            VBar, Amper, Dot, Caret,
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
            Arrow, Comma, LBracketArrow, RBracketArrow,
            True, False, None, Del;
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
            True("true"),
            False("false"),
            None("none"),
            Del("del"),
            Comma(","),
            Dot("[.]"),
            Caret(R"(\^)"),
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
            Space("[ \\t\\r]") {
                using lex::_pass;
                using lex::pass_flags;
                using boost::phoenix::ref;

                this->self
                        = HexadecimalInteger
                        | BinaryInteger
                        | OctalInteger
                        | DecimalInteger
                        | Float
                        | QString
                        | AString
                        | Comment [_pass = pass_flags::pass_ignore]
                        | Def
                        | Assert
                        | Return
                        | Class
                        | For
                        | While
                        | Break
                        | Import
                        | Continue
                        | If
                        | Then
                        | Else
                        | Elif
                        | Is
                        | InstanceOf
                        | In
                        | LessThan
                        | LessEquals
                        | GreaterThan
                        | GreaterEquals
                        | Equals
                        | NotEquals
                        | Not
                        | And
                        | Or
                        | True
                        | False
                        | None
                        | Del
                        | Comma
                        | Dot
                        | Caret
                        | Plus
                        | Minus
                        | Star
                        | Slash
                        | DoubleStar
                        | Tilde
                        | Percent
                        | VBar
                        | Amper
                        | LShift
                        | RShift
                        | Assign
                        | PlusAssign
                        | MinusAssign
                        | StarAssign
                        | SlashAssign
                        | DoubleStarAssign
                        | PercentAssign
                        | VBarAssign
                        | AmperAssign
                        | LShiftAssign
                        | RShiftAssign
                        | Arrow
                        | SemiColon
                        | Colon
                        | LParens
                        | RParens
                        | RBrace
                        | LBrace
                        | LBracket
                        | RBracket
                        | Identifier
                        | EOL [++ref(line),
                        _pass = pass_flags::pass_ignore]
                        | Space [_pass = pass_flags::pass_ignore]
                        ;
                
            }
            
            std::map<long unsigned int, std::pair<std::string, bool> > id_map() {
                std::map<long unsigned int, std::pair<std::string, bool> > out;
                
#define insert_val(x) out[x.id()] = std::pair<std::string, bool>(#x, true)
#define insert(x) out[x.id()] = std::pair<std::string, bool>(#x, false)
                
                insert_val(HexadecimalInteger);
                insert_val(BinaryInteger);
                insert_val(OctalInteger);
                insert_val(DecimalInteger);
                insert_val(Float);
                insert_val(Identifier);
                insert_val(QString);
                insert_val(AString);
                
                insert(Return);
                insert(Assert);
                insert(Def);
                insert(Class);
                insert(If);
                insert(Then);
                insert(Else);
                insert(Elif);
                insert(Is);
                insert(InstanceOf);
                insert(In);
                insert(LessThan);
                insert(LessEquals);
                insert(GreaterThan);
                insert(GreaterEquals);
                insert(Equals);
                insert(NotEquals);
                insert(Not);
                insert(And);
                insert(Or);
                insert(Plus);
                insert(Minus);
                insert(Star);
                insert(Slash);
                insert(DoubleStar);
                insert(Tilde);
                insert(Percent);
                insert(VBar);
                insert(Amper);
                insert(Dot);
                insert(Caret);
                insert(Import);
                insert(For);
                insert(While);
                insert(Break);
                insert(Continue);
                insert(SemiColon);
                insert(Colon);
                insert(LParens);
                insert(RParens);
                insert(LBrace);
                insert(RBrace);
                insert(LBracket);
                insert(RBracket);
                insert(LShift);
                insert(RShift);
                insert(Assign);
                insert(PlusAssign);
                insert(MinusAssign);
                insert(StarAssign);
                insert(SlashAssign);
                insert(DoubleStarAssign);
                insert(PercentAssign);
                insert(VBarAssign);
                insert(AmperAssign);
                insert(LShiftAssign);
                insert(RShiftAssign);
                insert(Arrow);
                insert(Comma);
                insert(True);
                insert(False);
                insert(None);
                insert(Del);
                
                insert(Space);
                insert(Comment);
                insert(EOL);
                
                return out;
            }
        };

        struct PixieLexerPrinter {
            
            std::map<long unsigned int, std::pair<std::string, bool> > id_map;

            PixieLexerPrinter(
                std::map<long unsigned int, std::pair<std::string, bool> > map)
                : id_map(map) {}
            
            template <typename Token>
            bool operator()(Token const& t) {
                std::pair<std::string, bool> name_val = id_map[t.id()];
                
                if (name_val.second) {
                    print_token(name_val.first, t.value());
                } else {
                    print_token(name_val.first);
                }
                
                return true;
            }
            
            template <typename T>
            void print_token(std::string token, T value) {
                std::cout << "[" << token << ":" << value << "]\n";
            }
            
            void print_token(std::string token) {
                std::cout << "[" << token << "]\n";
            }
            
        };

        typedef lex::lexertl::token<
        std::string::iterator, boost::mpl::vector<std::string>
        > token_type;
        typedef lex::lexertl::actor_lexer<token_type> lexer_type;

        typedef PixieLexer<lexer_type> pixie_lexer;

        typedef pixie_lexer::iterator_type pixie_lexer_iterator;
        
        enum PixieTokenType {
            HexadecimalInteger, BinaryInteger, OctalInteger,
            DecimalInteger, Float, Identifier,
            QString, AString, // Value
            Return, Assert, Def, Class, If, Then, Else,
            Elif, Is, InstanceOf, In,
            LessThan, LessEquals, GreaterThan, GreaterEquals,
            Equals, NotEquals,
            Not, And, Or,
            Plus, Minus, Star, Slash, DoubleStar, Tilde, Percent,
            VBar, Amper, Dot, Caret,
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
            Arrow, Comma, LBracketArrow, RBracketArrow,
            True, False, None, Del, // No Value
            Space, Comment, EOL //Skipped
        };
        
        struct PixieToken {
            PixieTokenType type;
            std::string value;
            size_t line;
            size_t column;
        };
        
        class PixieTokenizer {
            
        };

        void _test_tokenizer(std::string);

    }
}

#endif