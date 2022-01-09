//
// Created by Nykyta Ostapliuk on 17.10.2021 AD.
//

#ifndef XOPTIMIZER_PARSER_H
#define XOPTIMIZER_PARSER_H

#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <map>
#include "assumptions.h"


namespace XOptimizer {
    using namespace Assumptions;
    namespace Parser {
        class ParserException: public std::exception {
            std::string message, codeDemonstration;
        public:
            ParserException(std::string message, std::string codeDemonstration)
            : message(std::move(message)),
            codeDemonstration(std::move(codeDemonstration)) {}
            const char* what() const noexcept override {
                std::stringstream res;
                res << codeDemonstration;
                res << "Error";
                if (!message.empty()) res << ": " << message;
                res << "\n";
                auto *str = new std::string(res.str());
                return str->c_str();
            }
        };
        enum TokenType {
            UNKNOWN = -1,
            EOF_MARKER,
            VAR_KEYWORD,
            IDENTIFIER,
            COMMA,
            SEMICOLON,
            MAXIMIZE_KEYWORD,
            MINIMIZE_KEYWORD,
            LPAREN,
            RPAREN,
            EQUALS_OP,
            NUMBER_LITERAL,
            MINUS_OP,
            PLUS_OP,
            MUL_OP,
            DIV_OP,
            SUBJECT_KEYWORD,
            TO_KEYWORD,
            LBRACE,
            RBRACE,
            COLON,
            LESS_THAN_OP,
            LESS_EQUALS_OP,
            GREATER_EQUALS_OP,
            GREATER_THAN_OP,
            AND_KEYWORD,
            OR_KEYWORD,
            NAT_KEYWORD,
            INT_KEYWORD,
            REAL_KEYWORD,
            IMG_KEYWORD,
        };
        std::vector<TokenType> getOperatorTokenTypes();
        TokenType charToTokenType(char c);
        bool isIdentifierStart(char c);
        bool isIdentifier(char c);
        bool isWhitespace(char c);
        TokenType keywordToTokenType(std::string_view s);
        int getOpPrecedence(const std::string& op);
        std::string displayCodeRegion(std::shared_ptr<std::string> code, std::string filename, size_t start, size_t end);
        std::string displayError(std::shared_ptr<std::string> code, std::string filename, size_t start, size_t end, std::string reason = "");
        [[ noreturn ]] void error(std::shared_ptr<std::string> code, std::string filename, size_t start, size_t end, std::string reason = "");

        class Token {
            TokenType type;
            std::string filename;
            std::shared_ptr<std::string> code;
            size_t start, end;
        public:
            Token(TokenType type, std::string filename, std::shared_ptr<std::string> code, size_t start, size_t anEnd);

            TokenType getType() const;

            std::shared_ptr<std::string> getCode() const;

            size_t getStart() const;

            size_t getEnd() const;

            std::string_view getValue() const;

            std::string getFilename() const {
                return filename;
            }

            std::string toString() const {
                std::stringstream res;
                res << "Token " << type << " '" << getValue() << "' (" << start << ":" << end << ")";
                return res.str();
            }
        };

        class Node {
            std::shared_ptr<std::vector<Token>> tokens;
            size_t tokenStart, tokenEnd;
        public:
            Node(std::shared_ptr<std::vector<Token>> tokens, size_t tokenStart, size_t tokenEnd)
            : tokens(std::move(tokens)), tokenStart(tokenStart), tokenEnd(tokenEnd) {}

            size_t getTokenStart() const {
                return tokenStart;
            }

            size_t getTokenEnd() const {
                return tokenEnd;
            }

            size_t getCharStart() const {
                return tokens->at(tokenStart).getStart();
            }

            size_t getCharEnd() const {
                return tokens->at(tokenEnd-1).getEnd();
            }

            std::shared_ptr<std::vector<Token>> getTokens() const {
                return tokens;
            }

            virtual std::string toString() const = 0;
            virtual bool operator==(std::shared_ptr<Node> other) const {
                return this == other.get();
            }
            bool operator!=(std::shared_ptr<Node> other) const {
                return !(operator==(std::move(other)));
            }
        };
        std::string displayCodeRegion(std::shared_ptr<Node> node);
        [[ noreturn ]] void error(std::shared_ptr<Node> node, std::string reason = "");
        std::string displayError(std::shared_ptr<Node> node, std::string reason = "");
        class TopLevelNode: public Node {
        public:
            TopLevelNode(std::shared_ptr<std::vector<Token>> tokens, size_t tokenStart, size_t tokenEnd)
            : Node(std::move(tokens), tokenStart, tokenEnd) {}
        };
        class ExpressionNode: public Node {
        public:
            ExpressionNode(std::shared_ptr<std::vector<Token>> tokens, size_t tokenStart, size_t tokenEnd)
                    : Node(std::move(tokens), tokenStart, tokenEnd) {}
        };
        class ConditionNode: public Node {
        public:
            ConditionNode(std::shared_ptr<std::vector<Token>> tokens, size_t tokenStart, size_t tokenEnd)
                    : Node(std::move(tokens), tokenStart, tokenEnd) {}
        };
        class TypeNode: public Node {
        public:
            TypeNode(std::shared_ptr<std::vector<Token>> tokens, size_t tokenStart, size_t tokenEnd)
                    : Node(std::move(tokens), tokenStart, tokenEnd) {}
            virtual bool canCastTo(std::shared_ptr<TypeNode> other) const = 0;
        };
        class KeywordTypeNode: public TypeNode {
            std::string keyword;
        public:
            KeywordTypeNode(std::shared_ptr<std::vector<Token>> tokens,
                            size_t tokenStart, size_t tokenEnd,
                            std::string keyword)
                            : TypeNode(std::move(tokens), tokenStart, tokenEnd),
                            keyword(std::move(keyword)) {}

            std::string getKeyword() const {
                return keyword;
            }

            std::string toString() const override {
                std::stringstream res;
                res << "KeywordTypeNode{";
                res << keyword;
                res << "}";
                return res.str();
            }

            bool canCastTo(std::shared_ptr<TypeNode> other) const override {
                if (auto type = std::dynamic_pointer_cast<KeywordTypeNode>(other)) {
                    if (keyword == "nat") {
                        return true;
                    } else if (keyword == "int") {
                        return type->keyword == "int" || type->keyword == "real" || type->keyword == "img";
                    } else if (keyword == "real") {
                        return type->keyword == "real" || type->keyword == "img";
                    } else if (keyword == "img") {
                        return type->keyword == "img";
                    } else throw std::exception();
                } else return false;
            }

            bool operator==(std::shared_ptr<Node> other) const override {
                auto keywordTypeNode = std::dynamic_pointer_cast<KeywordTypeNode>(other);
                return keywordTypeNode && keywordTypeNode->keyword == keyword;
            }
        };
        class ProgramNode: public Node {
            std::vector<std::shared_ptr<TopLevelNode>> nodes;
        public:
            ProgramNode(std::shared_ptr<std::vector<Token>> tokens,
                        size_t tokenStart, size_t tokenEnd, std::vector<std::shared_ptr<TopLevelNode>> nodes)
                    : Node(std::move(tokens), tokenStart, tokenEnd), nodes(std::move(nodes)) {}

            const std::vector<std::shared_ptr<TopLevelNode>> &getNodes() const {
                return nodes;
            }

            std::string toString() const override {
                std::stringstream res;
                res << "ProgramNode{";
                for (auto it = nodes.begin(); it < nodes.end(); it++) {
                    if (it != nodes.begin()) res << ", ";
                    res << (*it)->toString();
                }
                res << "}";
                return res.str();
            }
        };
        class VariableDeclarator: public Node {
            std::string name;
            std::shared_ptr<TypeNode> type;
            std::shared_ptr<ExpressionNode> init;
        public:
            VariableDeclarator(std::shared_ptr<std::vector<Token>> tokens, size_t tokenStart, size_t tokenEnd,
                               std::string name, std::shared_ptr<TypeNode> type,
                               std::shared_ptr<ExpressionNode> init)
                               : Node(std::move(tokens), tokenStart, tokenEnd),
                               name(std::move(name)), type(std::move(type)), init(std::move(init)) {}

            std::string getName() const {
                return name;
            }

            std::shared_ptr<TypeNode> getType() const {
                return type;
            }

            std::shared_ptr<ExpressionNode> getInit() const {
                return init;
            }
            std::string toString() const override {
                std::stringstream res;
                res << name;
                if (type) {
                    res << ": " << type->toString();
                }
                if (init) {
                    res << " = " << init->toString();
                }
                return res.str();
            }
        };
        class VariableDeclarationNode: public TopLevelNode {
            std::vector<std::shared_ptr<VariableDeclarator>> declarators;
        public:
            VariableDeclarationNode(std::shared_ptr<std::vector<Token>> tokens,
                                    size_t tokenStart, size_t tokenEnd,
                                    std::vector<std::shared_ptr<VariableDeclarator>> declarators)
                : TopLevelNode(std::move(tokens), tokenStart, tokenEnd), declarators(std::move(declarators)) {}

            const std::vector<std::shared_ptr<VariableDeclarator>> &getDeclarators() const {
                return declarators;
            }
            std::string toString() const override {
                std::stringstream res;
                res << "VariableDeclaration{";
                for (auto it = declarators.begin(); it < declarators.end(); it++) {
                    if (it != declarators.begin()) res << ", ";
                    res << (*it)->toString();
                }
                res << "}";
                return res.str();
            }
        };
        class OptimizationTaskNode: public TopLevelNode {
            std::string task;
            std::shared_ptr<ExpressionNode> expression;
        public:
            OptimizationTaskNode(std::shared_ptr<std::vector<Token>> tokens,
                                 size_t tokenStart, size_t tokenEnd, std::string task,
                                 std::shared_ptr<ExpressionNode> expression) :
                    TopLevelNode(std::move(tokens), tokenStart, tokenEnd), task(std::move(task)), expression(std::move(expression)) {}

            std::string getTask() const {
                return task;
            }

            std::shared_ptr<ExpressionNode> getExpression() const {
                return expression;
            }
            std::string toString() const override {
                std::stringstream res;
                res << "OptimizationTaskNode{";
                res << task;
                res << " ";
                res << expression->toString();
                res << "}";
                return res.str();
            }
        };
        class NumberLiteralNode: public ExpressionNode {
            std::string value;
        public:
            NumberLiteralNode(std::shared_ptr<std::vector<Token>> tokens,
                              size_t tokenStart, size_t tokenEnd, std::string value)
                              : ExpressionNode(std::move(tokens), tokenStart, tokenEnd), value(std::move(value)) {}

            std::string getValue() const {
                return value;
            }
            std::string toString() const override {
                std::stringstream res;
                res << "NumberLiteralNode{";
                res << value;
                res << "}";
                return res.str();
            }
            bool operator==(std::shared_ptr<Node> other) const override {
                auto numberLiteral = std::dynamic_pointer_cast<NumberLiteralNode>(other);
                return numberLiteral && value == numberLiteral->value;
            }
        };
        class IdentifierNode: public ExpressionNode {
            std::string name;
        public:
            IdentifierNode(std::shared_ptr<std::vector<Token>> tokens,
                           size_t tokenStart, size_t tokenEnd, std::string name)
                : ExpressionNode(std::move(tokens), tokenStart, tokenEnd),
                name(std::move(name)) {}

            std::string getName() const {
                return name;
            }
            std::string toString() const override {
                std::stringstream res;
                res << "IdentifierNode{";
                res << name;
                res << "}";
                return res.str();
            }
            bool operator==(std::shared_ptr<Node> other) const override {
                auto identifier = std::dynamic_pointer_cast<IdentifierNode>(other);
                return identifier && identifier->name == name;
            }
        };
        class UnaryOperatorNode: public ExpressionNode {
            std::shared_ptr<ExpressionNode> operand;
            std::string op;
        public:
            UnaryOperatorNode(std::shared_ptr<std::vector<Token>> tokens, size_t tokenStart, size_t tokenEnd,
                              std::shared_ptr<ExpressionNode> operand, std::string op) :
                              ExpressionNode(std::move(tokens), tokenStart, tokenEnd),
                              operand(std::move(operand)), op(std::move(op)) {}

            std::shared_ptr<ExpressionNode> getOperand() const {
                return operand;
            }

            std::string getOp() const {
                return op;
            }


            std::string toString() const override {
                std::stringstream res;
                res << "UnaryOperatorNode{";
                res << op << " ";
                res << operand->toString();
                res << "}";
                return res.str();
            }
            bool operator==(std::shared_ptr<Node> other) const override {
                auto unaryOperator = std::dynamic_pointer_cast<UnaryOperatorNode>(other);
                return unaryOperator && unaryOperator->op == op && unaryOperator->operand->operator==(operand);
            }
        };
        class BinaryOperatorNode: public ExpressionNode {
            std::shared_ptr<ExpressionNode> left, right;
            std::string op;
        public:
            BinaryOperatorNode(std::shared_ptr<std::vector<Token>> tokens,
                               size_t tokenStart, size_t tokenEnd, std::shared_ptr<ExpressionNode> left,
                               std::shared_ptr<ExpressionNode> right, std::string op)
                               : ExpressionNode(std::move(tokens), tokenStart, tokenEnd),
                               left(std::move(left)), right(std::move(right)),
                                 op(std::move(op)) {}

            std::shared_ptr<ExpressionNode> getLeft() const {
                return left;
            }

            std::shared_ptr<ExpressionNode> getRight() const {
                return right;
            }

            std::string getOp() const {
                return op;
            }
            std::string toString() const override {
                std::stringstream res;
                res << "BinaryOperatorNode{";
                res << left->toString();
                res << " " << op << " ";
                res << right->toString();
                res << "}";
                return res.str();
            }
            bool operator==(std::shared_ptr<Node> other) const override {
                auto binaryOperator = std::dynamic_pointer_cast<BinaryOperatorNode>(other);
                return binaryOperator && binaryOperator->op == op &&
                    binaryOperator->left->operator==(left) &&
                    binaryOperator->right->operator==(right);
            }
        };
        class LogicalNode: public ConditionNode {
            std::shared_ptr<ConditionNode> left;
            std::shared_ptr<ConditionNode> right;
            std::string op;
        public:
            LogicalNode(std::shared_ptr<std::vector<Token>> tokens,
                        size_t tokenStart, size_t tokenEnd, std::shared_ptr<ConditionNode> left,
                        std::shared_ptr<ConditionNode> right, std::string op)
                    : ConditionNode(std::move(tokens), tokenStart, tokenEnd), left(std::move(left)), right(std::move(right)),
                      op(std::move(op)) {}

            std::shared_ptr<ConditionNode> getLeft() const {
                return left;
            }

            std::shared_ptr<ConditionNode> getRight() const {
                return right;
            }

            std::string getOp() const {
                return op;
            }
            std::string toString() const override {
                std::stringstream res;
                res << "LogicalNode{";
                res << left->toString();
                res << " " << op << " ";
                res << right->toString();
                res << "}";
                return res.str();
            }
        };
        class ComparisonNode: public ConditionNode {
            std::shared_ptr<ExpressionNode> left;
            std::shared_ptr<ExpressionNode> right;
            std::string op;
        public:
            ComparisonNode(std::shared_ptr<std::vector<Token>> tokens,
                           size_t tokenStart, size_t tokenEnd, std::shared_ptr<ExpressionNode> left,
                           std::shared_ptr<ExpressionNode> right, std::string op)
                    : ConditionNode(std::move(tokens), tokenStart, tokenEnd), left(std::move(left)), right(std::move(right)),
                      op(std::move(op)) {}

            std::shared_ptr<ExpressionNode> getLeft() const {
                return left;
            }

            std::shared_ptr<ExpressionNode> getRight() const {
                return right;
            }

            std::string getOp() const {
                return op;
            }
            std::string toString() const override {
                std::stringstream res;
                res << "ComparisonNode{";
                res << left->toString();
                res << " " << op << " ";
                res << right->toString();
                res << "}";
                return res.str();
            }
        };
        class ConstraintNode: public Node {
            std::string name;
            std::shared_ptr<ConditionNode> condition;
        public:
            ConstraintNode(std::shared_ptr<std::vector<Token>> tokens,
                           size_t tokenStart, size_t tokenEnd, std::string name,
                           std::shared_ptr<ConditionNode> condition) :
                    Node(std::move(tokens), tokenStart, tokenEnd),
                    name(std::move(name)), condition(std::move(condition)) {}

            std::string getName() const {
                return name;
            }

            std::shared_ptr<ConditionNode> getCondition() const {
                return condition;
            }

            std::string toString() const override {
                std::stringstream res;
                res << "ConstraintNode{";
                if (!name.empty()) res << name << ": ";
                res << condition->toString();
                res << "}";
                return res.str();
            }
        };
        class SubjectToNode: public TopLevelNode {
            std::vector<std::shared_ptr<ConstraintNode>> constraints;
        public:
            SubjectToNode(std::shared_ptr<std::vector<Token>> tokens,
                          size_t tokenStart, size_t tokenEnd,
                          std::vector<std::shared_ptr<ConstraintNode>> constraints)
                          : TopLevelNode(std::move(tokens), tokenStart, tokenEnd),
                          constraints(std::move(constraints)) {}
            SubjectToNode(std::shared_ptr<std::vector<Token>> tokens,
                          size_t tokenStart, size_t tokenEnd,
                          std::initializer_list<std::shared_ptr<ConstraintNode>> constraints)
                          : TopLevelNode(std::move(tokens), tokenStart, tokenEnd),
                          constraints(constraints) {}

            const std::vector<std::shared_ptr<ConstraintNode>> &getConstraints() const {
                return constraints;
            }

            std::string toString() const override {
                std::stringstream res;
                res << "SubjectToNode{";
                for (auto it = constraints.begin(); it < constraints.end(); it++) {
                    if (it != constraints.begin()) res << ", ";
                    res << (*it)->toString();
                }
                res << "}";
                return res.str();
            }
        };

        class Parser {
            std::string filename;
            std::shared_ptr<std::string> code;
            mutable std::shared_ptr<std::vector<Token>> tokens;
            mutable size_t lexer_ptr = 0;
            size_t parser_ptr = 0;
            Token parseToken() const;
            Token consumeToken();
            Token consumeToken(TokenType type);
            Token consumeToken(std::initializer_list<TokenType> types);
            Token consumeToken(std::vector<TokenType> types);
            Token nextToken(int offset = 0) const;
            bool hasNextToken(int offset = 0) const;
            std::shared_ptr<TopLevelNode> parseTopLevel();
            std::shared_ptr<VariableDeclarationNode> parseVariableDeclaration();
            std::shared_ptr<OptimizationTaskNode> parseOptimizationTask();
            std::shared_ptr<SubjectToNode> parseSubjectTo();
            std::shared_ptr<ConditionNode> parseCondition(int precedence = -1);
            std::shared_ptr<ConditionNode> parseConditionAtomic();
            std::shared_ptr<ConditionNode> tryParseLogicalCondition(std::shared_ptr<ConditionNode> left, int precedence = -1);
            std::shared_ptr<ExpressionNode> tryParseAtomic();
            std::shared_ptr<ExpressionNode> parseAtomic();
            std::shared_ptr<ExpressionNode> parseExpression(int precedence = -1);
            std::shared_ptr<ExpressionNode> tryParseBinary(std::shared_ptr<ExpressionNode> left, int precedence = -1);
            std::shared_ptr<TypeNode> parseType();
        public:
            explicit Parser(std::shared_ptr<std::string> code, std::string filename = "<unknown>"):
                code(std::move(code)), filename(std::move(filename)),
                tokens(std::make_shared<std::vector<Token>>()) {}
            explicit Parser(const std::string &code, std::string filename = "<unknown>"):
                Parser(std::make_shared<std::string>(code), std::move(filename)) {}
            explicit Parser(std::string &&code, std::string filename = "<unknown>"):
                Parser(std::make_shared<std::string>(code), std::move(filename)) {}
            std::shared_ptr<ProgramNode> parseProgram();
        };

        class Analyzer {
            std::vector<std::tuple<std::shared_ptr<VariableDeclarator>, std::shared_ptr<Assumption>, bool>> vars;
            std::vector<std::tuple<std::shared_ptr<ExpressionNode>, std::shared_ptr<Assumption>>> assumptionMap;

            std::tuple<std::shared_ptr<VariableDeclarator>, std::shared_ptr<Assumption>, bool>&
            getVariable(std::shared_ptr<IdentifierNode> identifier);
            std::shared_ptr<TypeNode> deriveType(std::shared_ptr<ExpressionNode> expr);
            void processCondition(std::shared_ptr<ConditionNode> condition);
            std::shared_ptr<double> tryEvaluateToNumber(std::shared_ptr<ExpressionNode> expr);
            std::shared_ptr<Assumption> assumptionFromExpression(std::shared_ptr<ExpressionNode> expr);
            std::shared_ptr<Assumption> assumptionFromType(std::shared_ptr<TypeNode> type);
        public:
            void analyze(std::shared_ptr<ProgramNode> program);
        };
    }
}

#endif //XOPTIMIZER_PARSER_H
