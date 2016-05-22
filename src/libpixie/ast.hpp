/* 
 * File:   ast.hpp
 * Author: nsamson
 *
 * Created on September 17, 2015, 8:05 PM
 */

#ifndef PIXIE_PARSER_HPP
#define PIXIE_PARSER_HPP

#include "common.hpp"
#include <string>
#include <vector>

namespace pixie {
    namespace compile {

        class ASTNode {

        public:

            int startLine;
            int startColumn;

            ASTNode(int startLine, int startColumn) : startLine(startLine), startColumn(startColumn) {}

            virtual std::string toString() = 0;

            virtual ~ASTNode() {}

        };

        enum class ControlFlowType {
            FLOWS,
            BREAKS
        };

        class ASTStatement : public ASTNode {
        public:

            ControlFlowType flowType;

            ASTStatement(int startLine, int startColumn, ControlFlowType type) : ASTNode(startLine, startColumn),
                                                                                 flowType(type) {}

            virtual ~ASTStatement() {}

        };

        class ASTExpression : public ASTNode {

        public:
            ASTExpression(int startLine, int startColumn) : ASTNode(startLine, startColumn) { }

            virtual ~ASTExpression() {}
        };

        enum class UnaryOperator {
            NOT,
            NEG
        };

        enum class BinaryOperator {
            PLUS,
            MINUS,
            STAR,
            SLASH,
            DOUBLESTAR,
            OR,
            AND,
            CARET,
            AMPER,
            VBAR,
            LEQ,
            LT,
            GEQ,
            GT,
            EQ,
            NEQ,
            LSHF,
            RSHF,
            MOD,
            EXP,
            DOT
        };

        class ASTBinaryExpression : public ASTExpression {

        public:

            BinaryOperator op;
            ASTExpression* lhs;
            ASTExpression* rhs;

            ASTBinaryExpression(int startLine, int startColumn,
                BinaryOperator op,
                ASTExpression* lhs,
                ASTExpression* rhs) : ASTExpression(startLine, startColumn),
                    lhs(lhs), rhs(rhs), op(op)
                { }

            ~ASTBinaryExpression() {
                delete lhs;
                delete rhs;
            }

            std::string toString();

        };

        class ASTUnaryExpression : public ASTExpression {

        public:

            ASTExpression* expr;
            UnaryOperator op;

            ASTUnaryExpression(int startLine, int startColumn,
                               UnaryOperator op,
                               ASTExpression* expr) : ASTExpression(startLine, startColumn),
                                                    op(op),
                                                     expr(expr)
            { }

            std::string toString();

            ~ASTUnaryExpression() {
                delete expr;
            }
        };

        class ASTStatementBlock : public ASTStatement {

        public:

            std::vector<ASTStatement*> contents;

            ASTStatementBlock(int startLine, int startColumn, ControlFlowType type) : ASTStatement(startLine,
                                                                                                   startColumn,
                                                                                                   type) { }

            void addStatement(ASTStatement* stmt) {
                this->contents.push_back(stmt);
            }

            std::string toString();

            ~ASTStatementBlock() {
                for (auto&& stmtPtr : contents) {
                    delete stmtPtr;
                }
            }
        };

        class ASTAssertStatement : public ASTStatement {

        public:
            ASTExpression* expr;

            ASTAssertStatement(int startLine, int startColumn, ControlFlowType type, ASTExpression* expr) : ASTStatement(startLine,
                                                                                                    startColumn,
                                                                                                    type) { }

            ~ASTAssertStatement() {
                delete expr;
            }
        };



        class ASTProgram {

            std::vector<ASTStatement*> statements;

            ~ASTProgram() {
                for (auto&& stmtPtr : statements) {
                    delete stmtPtr;
                }
            }
        };

    }
}

#endif


