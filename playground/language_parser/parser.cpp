//
// Created by Nykyta Ostapliuk on 17.10.2021 AD.
//

#include "parser.h"
#include "assumptions.h"

#include <utility>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <map>
using namespace XOptimizer::Parser;
using namespace XOptimizer::Assumptions;

Token::Token(TokenType type, std::string filename, std::shared_ptr<std::string> code, size_t start, size_t anEnd)
    : type(type),
    filename(std::move(filename)),
    code(std::move(code)),
    start(start),
    end(anEnd) {}

TokenType Token::getType() const {
    return type;
}

std::shared_ptr<std::string> Token::getCode() const {
    return code;
}

size_t Token::getStart() const {
    return start;
}

size_t Token::getEnd() const {
    return end;
}

std::string_view Token::getValue() const {
    return {code->data() + start, end - start};
}

TokenType XOptimizer::Parser::charToTokenType(char c) {
    switch (c) {
        case ',': return COMMA;
        case ';': return SEMICOLON;
        case '(': return LPAREN;
        case ')': return RPAREN;
        case '{': return LBRACE;
        case '}': return RBRACE;
        case '+': return PLUS_OP;
        case '-': return MINUS_OP;
        case '=': return EQUALS_OP;
        case ':': return COLON;
        case '*': return MUL_OP;
        case '/': return DIV_OP;
        default: return UNKNOWN;
    }
}

std::vector<TokenType> XOptimizer::Parser::getOperatorTokenTypes() {
    return {MINUS_OP, PLUS_OP, MUL_OP, DIV_OP};
}

bool XOptimizer::Parser::isIdentifierStart(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool XOptimizer::Parser::isIdentifier(char c) {
    return isIdentifierStart(c) || (c >= '0' && c <= '9') || c == '_' || c == '\'';
}

bool XOptimizer::Parser::isWhitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

TokenType XOptimizer::Parser::keywordToTokenType(std::string_view s) {
    if (s == "var") {
        return VAR_KEYWORD;
    } else if (s == "maximize" || s == "maximise") {
        return MAXIMIZE_KEYWORD;
    } else if (s == "minimize" || s == "minimise") {
        return MINIMIZE_KEYWORD;
    } else if (s == "subject") {
        return SUBJECT_KEYWORD;
    } else if (s == "to") {
        return TO_KEYWORD;
    } else if (s == "and") {
        return AND_KEYWORD;
    } else if (s == "or") {
        return OR_KEYWORD;
    } else if (s == "nat") {
        return NAT_KEYWORD;
    } else if (s == "int") {
        return INT_KEYWORD;
    } else if (s == "real") {
        return REAL_KEYWORD;
    } else if (s == "img") {
        return IMG_KEYWORD;
    } else return UNKNOWN;
}

#define PRINT_LINE(n) res << std::left << std::setfill(' ') << std::setw(pad_length) << ((n)+1) << "|" << lines[(n)] << "\n"
std::string XOptimizer::Parser::displayCodeRegion(std::shared_ptr<std::string> code, std::string filename, size_t start, size_t end) {
    end--;
    size_t line_start = 0;
    std::vector<std::string_view> lines;
    size_t start_line = -1, end_line = -1;
    size_t start_line_idx = -1, end_line_idx = -1;
    for (size_t i = 0; i < code->length(); i++) {
        if (code->at(i) == '\n' || code->at(i) == '\r') {
            if (start >= line_start && start < i) {
                start_line = lines.size();
                start_line_idx = start - line_start;
            }
            if (end >= line_start && end < i) {
                end_line = lines.size();
                end_line_idx = end - line_start;
            }
            lines.emplace_back(code->data() + line_start, i - line_start);
            if (code->at(i) == '\r' && i+1 < start && code->at(i+1) == '\n') i++;
            line_start = i+1;
        }
    }
    if (start >= line_start && start < code->length()) start_line = lines.size();
    if (end >= line_start && end < code->length()) end_line = lines.size();
    if (start_line == (size_t)-1 || end_line == (size_t)-1) {
        std::cerr << "Cound not display code" << std::endl;
        throw std::exception();
    }
    lines.emplace_back(code->data() + line_start, code->length() - line_start);
    size_t pad_length = std::to_string(end_line + 2).size() + 1;
    std::stringstream res;
    res << "In " << filename << ":\n";
    if (start_line > 0) {
        PRINT_LINE(start_line-1);
    }
    if (start_line == end_line) {
        PRINT_LINE(start_line);
        for (int i = 0; i < start_line_idx + pad_length + 1; i++) res << ' ';
        res << '^';
        if (start_line_idx < end_line_idx) {
            for (int i = 0; i < end_line_idx - start_line_idx - 1; i++) res << '~';
            res << '^';
        }
        res << '\n';
    } else {
        for (size_t i = start_line; i <= end_line; i++) {
            if (i == start_line + 2 && i < end_line - 1) {
                res << "...\n";
                continue;
            } else if (i > start_line + 2 && i < end_line - 1) continue;
            PRINT_LINE(i);
            if (i == start_line) {
                for (size_t j = 0; j < start_line_idx + pad_length + 1; j++) {
                    res << ' ';
                }
                res << '^';
                for (size_t j = start_line_idx+1; j < lines[start_line].size(); j++) {
                    res << '~';
                }
                res << "\n";
            } else if (i == end_line) {
                for (size_t j = 0; j < pad_length + 1; j++) {
                    res << ' ';
                }
                for (size_t j = 0; j < end_line_idx; j++) {
                    res << '~';
                }
                res << "^\n";
            } else {
                for (size_t j = 0; j < pad_length + 1; j++) {
                    res << ' ';
                }
                for (size_t j = 0; j < lines[i].size(); j++) {
                    res << '~';
                }
                res << '\n';
            }
        }
    }
    if (start_line+1 < lines.size()) PRINT_LINE(start_line+1);
    return res.str();
}
#undef PRINT_LINE

std::string XOptimizer::Parser::displayCodeRegion(std::shared_ptr<Node> node) {
    Token tok = node->getTokens()->at(0);
    return displayCodeRegion(tok.getCode(), tok.getFilename(),
                        node->getCharStart(), node->getCharEnd());
}

std::string XOptimizer::Parser::displayError(std::shared_ptr<std::string> code, std::string filename, size_t start, size_t end, std::string reason) {
    std::stringstream res;
    res << displayCodeRegion(code, filename, start, end);
    res << "Error";
    if (!reason.empty()) {
        res << ": " << reason;
    }
    res << "\n";
    return res.str();
}

std::string XOptimizer::Parser::displayError(std::shared_ptr<Node> node, std::string reason) {
    Token tok = node->getTokens()->at(0);
    return displayError(tok.getCode(), tok.getFilename(),
          node->getCharStart(), node->getCharEnd(), std::move(reason));
}

[[ noreturn ]] void XOptimizer::Parser::error(std::shared_ptr<std::string> code, std::string filename, size_t start, size_t end, std::string reason) {
    std::string display = displayCodeRegion(std::move(code), std::move(filename), start, end);
    throw ParserException(std::move(reason), display);
}
[[ noreturn ]] void XOptimizer::Parser::error(std::shared_ptr<Node> node, std::string reason) {
    Token tok = node->getTokens()->at(0);
    error(tok.getCode(), tok.getFilename(),
          node->getCharStart(), node->getCharEnd(),
          std::move(reason));
}
int XOptimizer::Parser::getOpPrecedence(const std::string &op) {
    if (op == "+" || op == "-") return 10;
    if (op == "*" || op == "/") return 20;
    throw std::exception();
}

Token Parser::parseToken() const {
    while (lexer_ptr < code->size() && isWhitespace(code->at(lexer_ptr))) lexer_ptr++;
    if (lexer_ptr >= code->size()) return Token(EOF_MARKER, filename, code, code->size(), code->size());
    char c = code->at(lexer_ptr);
    size_t start = lexer_ptr;
    TokenType tokenType = charToTokenType(c);
    if (tokenType != UNKNOWN) {
        lexer_ptr++;
        Token res(tokenType, filename, code, start, lexer_ptr);
        tokens->emplace_back(res);
        return res;
    } else if (isIdentifierStart(c)) {
        lexer_ptr++;
        while (lexer_ptr < code->length() && isIdentifier(code->at(lexer_ptr))) lexer_ptr++;
        TokenType t = keywordToTokenType(std::string_view(code->data() + start, lexer_ptr - start));
        Token res(t != UNKNOWN ? t : IDENTIFIER, filename, code, start, lexer_ptr);
        tokens->emplace_back(res);
        return res;
    } else if (c >= '0' && c <= '9') {
        lexer_ptr++;
        while (lexer_ptr < code->length() && (
                (code->at(lexer_ptr) >= '0' && code->at(lexer_ptr) <= '9') ||
                code->at(lexer_ptr) == '_')) lexer_ptr++;
        if (lexer_ptr < code->length() && code->at(lexer_ptr) == '.') {
            lexer_ptr++;
            while (lexer_ptr < code->length() &&
                code->at(lexer_ptr) >= '0' && code->at(lexer_ptr) <= '9') lexer_ptr++;
        }
        Token res(NUMBER_LITERAL, filename, code, start, lexer_ptr);
        tokens->emplace_back(res);
        return res;
    } else if (c == '<') {
        lexer_ptr++;
        if (lexer_ptr < code->length() && code->at(lexer_ptr) == '=') {
            lexer_ptr++;
            Token res(LESS_EQUALS_OP, filename, code, start, lexer_ptr);
            tokens->emplace_back(res);
            return res;
        } else {
            Token res(LESS_THAN_OP, filename, code, start, lexer_ptr);
            tokens->emplace_back(res);
            return res;
        }
    } else if (c == '>') {
        lexer_ptr++;
        if (lexer_ptr < code->length() && code->at(lexer_ptr) == '=') {
            lexer_ptr++;
            Token res(GREATER_EQUALS_OP, filename, code, start, lexer_ptr);
            tokens->emplace_back(res);
            return res;
        } else {
            Token res(GREATER_THAN_OP, filename, code, start, lexer_ptr);
            tokens->emplace_back(res);
            return res;
        }
    }
    error(code, filename, lexer_ptr, lexer_ptr+1, "Unexpected char");
}

Token Parser::consumeToken() {
    Token res = nextToken();
    parser_ptr++;
    return res;
}

Token Parser::consumeToken(TokenType type) {
    Token res = nextToken();
    if (res.getType() != type) {
        error(code, filename, res.getStart(), res.getEnd(), "Unexpected token");
    }
    parser_ptr++;
    return res;
}

Token Parser::consumeToken(std::initializer_list<TokenType> types) {
    return consumeToken(std::vector<TokenType>(types));
}

Token Parser::consumeToken(std::vector<TokenType> types) {
    Token res = nextToken();
    for (auto it = types.begin(); it < types.end(); it++) if (res.getType() == *it) {
        parser_ptr++;
        return res;
    }
    error(code, filename, res.getStart(), res.getEnd(), "Unexpected token");
}

Token Parser::nextToken(int offset) const {
    while (tokens->size() <= parser_ptr + offset) {
        Token t = parseToken();
        if (t.getType() == EOF_MARKER) throw std::exception();
    }
    return tokens->at(parser_ptr + offset);
}

bool Parser::hasNextToken(int offset) const {
    while (tokens->size() <= parser_ptr + offset) {
        Token t = parseToken();
        if (t.getType() == EOF_MARKER) return false;
    }
    return true;
}

std::shared_ptr<ProgramNode> Parser::parseProgram() {
    size_t start = parser_ptr;
    std::vector<std::shared_ptr<TopLevelNode>> res;
    while (hasNextToken()) res.push_back(parseTopLevel());
    auto program = std::make_shared<ProgramNode>(tokens, start, parser_ptr, res);
    auto analyzer = std::make_shared<Analyzer>();
    analyzer->analyze(program);
    return program;
}

std::shared_ptr<TopLevelNode> Parser::parseTopLevel() {
    Token token = nextToken();
    if (token.getType() == VAR_KEYWORD) {
        return parseVariableDeclaration();
    } else if (token.getType() == MAXIMIZE_KEYWORD || token.getType() == MINIMIZE_KEYWORD) {
        return parseOptimizationTask();
    } else if (token.getType() == SUBJECT_KEYWORD) {
        return parseSubjectTo();
    }
    error(code, filename, token.getStart(), token.getEnd(), "Expected top-level statement");
}

std::shared_ptr<VariableDeclarationNode> Parser::parseVariableDeclaration() {
    size_t start = parser_ptr;
    consumeToken(VAR_KEYWORD);
    std::vector<std::shared_ptr<VariableDeclarator>> res;
    do {
        size_t declaratorStart = parser_ptr;
        std::string name(consumeToken(IDENTIFIER).getValue());
        std::shared_ptr<TypeNode> type;
        if (nextToken().getType() == COLON) {
            consumeToken(COLON);
            type = parseType();
        }
        std::shared_ptr<ExpressionNode> expr;
        if (nextToken().getType() == EQUALS_OP) {
            consumeToken(EQUALS_OP);
            expr = parseExpression();
        }
        res.emplace_back(std::make_shared<VariableDeclarator>(tokens, declaratorStart, parser_ptr, name, type, expr));
        if (nextToken().getType() == SEMICOLON) break;
        consumeToken(COMMA);
    } while (true);
    consumeToken(SEMICOLON);
    return std::make_shared<VariableDeclarationNode>(tokens, start, parser_ptr, res);
}

std::shared_ptr<ExpressionNode> Parser::parseExpression(int precedence) {
    std::shared_ptr<ExpressionNode> res;
    Token next = nextToken();
    if (next.getType() == LPAREN) {
        consumeToken(LPAREN);
        res = parseExpression();
        consumeToken(RPAREN);
    } else {
        res = parseAtomic();
    }
    while (true) {
        auto new_res = tryParseBinary(res, precedence);
        if (res == new_res) break;
        res = new_res;
    }
    return res;
}

std::shared_ptr<ExpressionNode> Parser::tryParseBinary(std::shared_ptr<ExpressionNode> left, int precedence) {
    Token tok = nextToken();
    auto operatorTokenTypes = getOperatorTokenTypes();
    if (std::find(operatorTokenTypes.begin(), operatorTokenTypes.end(), tok.getType()) != operatorTokenTypes.end()) {
        int next_precedence = getOpPrecedence(std::string(tok.getValue()));
        if (next_precedence <= precedence) return left;
        consumeToken(operatorTokenTypes);
        auto right = parseExpression(next_precedence);
        return std::make_shared<BinaryOperatorNode>(tokens,
            left->getTokenStart(), parser_ptr,
            left, right,
            std::string(tok.getValue())
        );
    }
    size_t start = parser_ptr;
    auto next = tryParseAtomic();
    parser_ptr = start;
    if (!next) {
        return left;
    }
    int next_precedence = getOpPrecedence("*");
    if (next_precedence <= precedence) return left;
    auto right = parseExpression(next_precedence);
    return std::make_shared<BinaryOperatorNode>(tokens, left->getTokenStart(), parser_ptr, left, right, "*");
}

std::shared_ptr<ExpressionNode> Parser::tryParseAtomic() {
    size_t start = parser_ptr;
    Token tok = nextToken();
    if (tok.getType() == NUMBER_LITERAL) {
        consumeToken(NUMBER_LITERAL);
        return std::make_shared<NumberLiteralNode>(tokens, start, parser_ptr, std::string(tok.getValue()));
    } else if (tok.getType() == IDENTIFIER) {
        consumeToken(IDENTIFIER);
        return std::make_shared<IdentifierNode>(tokens, start, parser_ptr, std::string(tok.getValue()));
    }
    return {};
}

std::shared_ptr<ExpressionNode> Parser::parseAtomic() {
    auto res = tryParseAtomic();
    if (res) return res;
    Token tok = nextToken();
    error(code, filename, tok.getStart(), tok.getEnd(), "Expected expression");
}

std::shared_ptr<OptimizationTaskNode> Parser::parseOptimizationTask() {
    size_t start = parser_ptr;
    Token first = consumeToken({MAXIMIZE_KEYWORD, MINIMIZE_KEYWORD});
    std::string task(first.getValue().substr(0, 3));
    auto expr = parseExpression();
    consumeToken(SEMICOLON);
    return std::make_shared<OptimizationTaskNode>(tokens, start, parser_ptr, task, expr);
}

std::shared_ptr<SubjectToNode> Parser::parseSubjectTo() {
    size_t start = parser_ptr;
    consumeToken(SUBJECT_KEYWORD);
    consumeToken(TO_KEYWORD);
    consumeToken(LBRACE);
    std::vector<std::shared_ptr<ConstraintNode>> result;
    while (true) {
        size_t constraint_start = parser_ptr;
        Token next = nextToken();
        std::string name;
        if (next.getType() == RBRACE) break;
        if (next.getType() == IDENTIFIER && hasNextToken(1) && nextToken(1).getType() == COLON) {
            name = consumeToken(IDENTIFIER).getValue();
            consumeToken(COLON);
        }
        std::shared_ptr<ConditionNode> condition = parseCondition();
        consumeToken(SEMICOLON);
        result.emplace_back(std::make_shared<ConstraintNode>(tokens, constraint_start, parser_ptr, name, condition));
    }
    consumeToken(RBRACE);
    return std::make_shared<SubjectToNode>(tokens, start, parser_ptr, result);
}

std::shared_ptr<ConditionNode> Parser::parseConditionAtomic() {
    size_t start = nextToken().getStart();
    auto left = parseExpression();
    std::shared_ptr<ConditionNode> result;
    int direction = 0;
    Token op = nextToken();
    while (op.getType() == LESS_THAN_OP || op.getType() == LESS_EQUALS_OP ||
           op.getType() == EQUALS_OP ||
           op.getType() == GREATER_EQUALS_OP || op.getType() == GREATER_THAN_OP) {
        int newdirection;
        if (op.getType() == LESS_THAN_OP || op.getType() == LESS_EQUALS_OP) {
            newdirection = -1;
        } else if (op.getType() == GREATER_EQUALS_OP || op.getType() == GREATER_THAN_OP) {
            newdirection = 1;
        } else newdirection = 0;
        if (direction == 0) {
            direction = newdirection;
        } else if (newdirection != 0 && direction != newdirection) {
            error(code, filename, op.getStart(), op.getEnd(), "Bad comparison operator sequence");
        }
        consumeToken();
        auto right = parseExpression();
        auto comp = std::make_shared<ComparisonNode>(
                tokens,
                left->getTokenStart(), right->getTokenEnd(),
                left, right, std::string(op.getValue())
        );
        if (result) {
            result = std::make_shared<LogicalNode>(
                    tokens,
                    result->getTokenStart(), comp->getTokenEnd(),
                    result, comp, "and"
            );
        } else {
            result = comp;
        }
        op = nextToken();
        left = right;
    }
    if (!result) error(
            code, filename,
            tokens->at(left->getTokenStart()).getStart(),
            tokens->at(left->getTokenEnd()-1).getEnd(),
            "Bad condition"
    );
    return result;
}

std::shared_ptr<ConditionNode> Parser::tryParseLogicalCondition(std::shared_ptr<ConditionNode> left, int precedence) {
    Token tok = nextToken();
    if (tok.getType() == AND_KEYWORD || tok.getType() == OR_KEYWORD) {
        int newprecedence = tok.getType() == AND_KEYWORD ? 20 : 10;
        if (newprecedence <= precedence) return left;
        consumeToken();
        auto right = parseCondition(newprecedence);
        return std::make_shared<LogicalNode>(
                tokens,
                left->getTokenStart(), right->getTokenEnd(),
                left, right, std::string(tok.getValue())
        );
    } else return left;
}

std::shared_ptr<ConditionNode> Parser::parseCondition(int precedence) {
    std::shared_ptr<ConditionNode> res;
    Token next = nextToken();
    if (next.getType() == LPAREN) {
        consumeToken(LPAREN);
        res = parseCondition();
        consumeToken(RPAREN);
    } else {
        res = parseConditionAtomic();
    }
    while (true) {
        auto new_res = tryParseLogicalCondition(res, precedence);
        if (res == new_res) break;
        res = new_res;
    }
    return res;
}

std::shared_ptr<TypeNode> Parser::parseType() {
    size_t start = parser_ptr;
    Token token = nextToken();
    if (token.getType() == NAT_KEYWORD || token.getType() == INT_KEYWORD
    || token.getType() == REAL_KEYWORD || token.getType() == IMG_KEYWORD) {
        consumeToken();
        std::string keyword =
                token.getType() == NAT_KEYWORD ? "nat" :
                token.getType() == INT_KEYWORD ? "int" :
                token.getType() == REAL_KEYWORD? "real" : "img";
        return std::make_shared<KeywordTypeNode>(tokens, start, parser_ptr, keyword);
    }
    error(code, filename, token.getStart(), token.getEnd(), "Type expected");
}

void Analyzer::analyze(std::shared_ptr<ProgramNode> program) {
    for (const auto &node: program->getNodes()) {
        if (auto variableDeclaration = std::dynamic_pointer_cast<VariableDeclarationNode>(node)) {
            for (auto variableDeclarator: variableDeclaration->getDeclarators()) {
                auto name = variableDeclarator->getName();
                auto dupVal = std::find_if(vars.begin(), vars.end(), [&](auto var){
                    return variableDeclarator->getName() == std::get<0>(var)->getName();
                });
                if (dupVal != vars.end()) {
                    std::cerr << "Note: here\n" << displayError(std::get<0>(*dupVal)) << std::endl;
                    error(variableDeclarator, "Variable redeclaration");
                }
                auto type = variableDeclarator->getType();
                if (auto init = variableDeclarator->getInit()) {
                    auto inferredType = deriveType(init);
                    if (type) {
                        if (!inferredType->canCastTo(type)) {
                            error(init, "Cannot cast " + inferredType->toString() + " to " + type->toString());
                        }
                    } else {
                        type = inferredType;
                    }
                }
                if (!type) {
                    error(variableDeclarator, "A variable declaration should have a type or an initialization expression");
                }
                auto assumption = variableDeclarator->getInit() ?
                                  assumptionFromExpression(variableDeclarator->getInit())
                                  : assumptionFromType(variableDeclarator->getType());
                vars.emplace_back(
                        std::make_shared<VariableDeclarator>(
                                variableDeclarator->getTokens(),
                                variableDeclarator->getTokenStart(),
                                variableDeclarator->getTokenEnd(),
                                name, type, variableDeclarator->getInit()
                        ),
                        assumption,
                        false
                );
            }
        } else if (auto optimizationTask = std::dynamic_pointer_cast<OptimizationTaskNode>(node)) {
            auto type = deriveType(optimizationTask->getExpression());
            if (auto keywordType = std::dynamic_pointer_cast<KeywordTypeNode>(type)) {
                if (keywordType->getKeyword() != "img") {
                    continue;
                }
            }
            error(optimizationTask->getExpression(), "Cannot optimize expression of type " + type->toString());
        } else if (auto subjectTo = std::dynamic_pointer_cast<SubjectToNode>(node)) {
            for (const auto &constraint: subjectTo->getConstraints()) {
                processCondition(constraint->getCondition());
            }
        } else {
            error(node, "Unknown node type");
        }
    }
    for (auto var: vars) {
        if (!std::get<2>(var)) {
            std::cerr << displayCodeRegion(std::get<0>(var));
            std::cerr << "Warning: unused variable " + std::get<0>(var)->getName() << std::endl;
        }
    }
}

std::string maxKeywordType(std::string t1, std::string t2) {
    if (t1 == "nat") {
        return t2;
    } else if (t1 == "int") {
        return t2 == "nat" ? t1 : t2;
    } else if (t1 == "real") {
        return t2 == "img" ? t2 : t1;
    } else return t1;
}

std::shared_ptr<TypeNode> Analyzer::deriveType(std::shared_ptr<ExpressionNode> expr) {
    if (auto numericLiteral = std::dynamic_pointer_cast<NumberLiteralNode>(expr)) {
        return std::make_shared<KeywordTypeNode>(
                expr->getTokens(),
                expr->getTokenStart(), expr->getTokenEnd(),
                numericLiteral->getValue().find('.') == -1 ? "nat" : "real");
    } else if (auto identifier = std::dynamic_pointer_cast<IdentifierNode>(expr)) {
        auto res = std::find_if(vars.begin(), vars.end(), [&](auto var){
            return identifier->getName() == std::get<0>(var)->getName();
        });
        if (res == vars.end()) {
            error(identifier, "Variable not declared");
        }
        std::get<2>(*res) = true;
        return std::get<0>(*res)->getType();
    } else if (auto unaryOperator = std::dynamic_pointer_cast<UnaryOperatorNode>(expr)) {
        auto type = deriveType(unaryOperator->getOperand());
        if (auto keywordType = std::dynamic_pointer_cast<KeywordTypeNode>(type)) {
            return std::make_shared<KeywordTypeNode>(
                    expr->getTokens(),
                    expr->getTokenStart(), expr->getTokenEnd(),
                    unaryOperator->getOp() == "-" && keywordType->getKeyword() == "nat" ? "int" : keywordType->getKeyword());
        }
    } else if (auto binaryOperator = std::dynamic_pointer_cast<BinaryOperatorNode>(expr)) {
        auto leftType = deriveType(binaryOperator->getLeft());
        auto rightType = deriveType(binaryOperator->getRight());
        if (auto leftKeywordType = std::dynamic_pointer_cast<KeywordTypeNode>(leftType)) {
            if (auto rightKeywordType = std::dynamic_pointer_cast<KeywordTypeNode>(rightType)) {
                if (binaryOperator->getOp() == "+" || binaryOperator->getOp() == "*") {
                    return std::make_shared<KeywordTypeNode>(
                            expr->getTokens(),
                            expr->getTokenStart(), expr->getTokenEnd(),
                            maxKeywordType(leftKeywordType->getKeyword(), rightKeywordType->getKeyword()));
                } else if (binaryOperator->getOp() == "-") {
                    return std::make_shared<KeywordTypeNode>(
                            expr->getTokens(),
                            expr->getTokenStart(), expr->getTokenEnd(),
                            maxKeywordType(
                                    "int",
                                    maxKeywordType(
                                            leftKeywordType->getKeyword(),
                                            rightKeywordType->getKeyword()
                                    )
                            ));
                } else if (binaryOperator->getOp() == "/") {
                    return std::make_shared<KeywordTypeNode>(
                            expr->getTokens(),
                            expr->getTokenStart(), expr->getTokenEnd(),
                            maxKeywordType(
                                    "real",
                                    maxKeywordType(
                                            leftKeywordType->getKeyword(),
                                            rightKeywordType->getKeyword()
                                    )
                            ));
                }
            }
        }
    }
    error(expr, "Cannot deduct type of " + expr->toString());
}



std::shared_ptr<double> Analyzer::tryEvaluateToNumber(std::shared_ptr<ExpressionNode> expr) {
    if (auto numericLiteral = std::dynamic_pointer_cast<NumberLiteralNode>(expr)) {
        return std::make_shared<double>(std::stod(numericLiteral->getValue()));
    } else if (auto identifier = std::dynamic_pointer_cast<IdentifierNode>(expr)) {
        auto res = getVariable(identifier);
        auto init = std::get<0>(res)->getInit();
        return init ? tryEvaluateToNumber(init) : std::shared_ptr<double>();
    } else if (auto unaryOperator = std::dynamic_pointer_cast<UnaryOperatorNode>(expr)) {
        auto res = tryEvaluateToNumber(unaryOperator->getOperand());
        if (res) {
            return std::make_shared<double>(-*res);
        } else return {};
    } else if (auto binaryOperator = std::dynamic_pointer_cast<BinaryOperatorNode>(expr)) {
        auto left = tryEvaluateToNumber(binaryOperator->getLeft());
        if (!left) return {};
        auto right = tryEvaluateToNumber(binaryOperator->getRight());
        if (!right) return {};
        if (binaryOperator->getOp() == "+") {
            return std::make_shared<double>(*left + *right);
        } else if (binaryOperator->getOp() == "-") {
            return std::make_shared<double>(*left - *right);
        } else if (binaryOperator->getOp() == "*") {
            return std::make_shared<double>(*left * *right);
        } else if (binaryOperator->getOp() == "/") {
            return std::make_shared<double>(*left / *right);
        }
    }
    return {};
}

std::shared_ptr<Assumption> Analyzer::assumptionFromExpression(std::shared_ptr<ExpressionNode> expr) {
    auto savedAssumption = std::find_if(assumptionMap.begin(), assumptionMap.end(), [&](auto t){
        return std::get<0>(t)->operator==(expr);
    });
    if (savedAssumption != assumptionMap.end()) return std::get<1>(*savedAssumption);
    if (auto numericLiteral = std::dynamic_pointer_cast<NumberLiteralNode>(expr)) {
        return Assumption::equals(std::stod(numericLiteral->getValue()));
    } else if (auto identifier = std::dynamic_pointer_cast<IdentifierNode>(expr)) {
        return std::get<1>(getVariable(identifier));
    } else if (auto unaryOperator = std::dynamic_pointer_cast<UnaryOperatorNode>(expr)) {
        return assumptionFromExpression(unaryOperator->getOperand())->neg();
    } else if (auto binaryOperator = std::dynamic_pointer_cast<BinaryOperatorNode>(expr)) {
        auto leftAssumption = assumptionFromExpression(binaryOperator->getLeft());
        auto rightAssumption = assumptionFromExpression(binaryOperator->getRight());
        if (binaryOperator->getOp() == "+") {
            return leftAssumption->add(rightAssumption);
        } else if (binaryOperator->getOp() == "-") {
            return leftAssumption->sub(rightAssumption);
        } else if (binaryOperator->getOp() == "*") {
            return leftAssumption->mul(rightAssumption);
        } else if (binaryOperator->getOp() == "/") {
            return leftAssumption->div(rightAssumption);
        } else error(binaryOperator, "Unknown operator");
    }
    error(expr, "Cannot deduct assumptions of " + expr->toString());
}

std::tuple<std::shared_ptr<VariableDeclarator>, std::shared_ptr<Assumption>, bool>&
Analyzer::getVariable(std::shared_ptr<IdentifierNode> identifier) {
    auto res = std::find_if(vars.begin(), vars.end(), [&](auto var){
        return identifier->getName() == std::get<0>(var)->getName();
    });
    if (res == vars.end()) {
        error(identifier, "Variable not declared");
    }
    return *res;
}

std::shared_ptr<Assumption> Analyzer::assumptionFromType(std::shared_ptr<TypeNode> type) {
    if (auto keywordType = std::dynamic_pointer_cast<KeywordTypeNode>(type)) {
        if (keywordType->getKeyword() == "nat") {
            return Assumption::greaterEquals(0)->makeInteger(true);
        } else if (keywordType->getKeyword() == "int") {
            return Assumption::real()->makeInteger(true);
        } else if (keywordType->getKeyword() == "real") {
            return Assumption::real();
        } else if (keywordType->getKeyword() == "img") {
            return Assumption::any();
        }
    }
    return Assumption::any();
}

void Analyzer::processCondition(std::shared_ptr<ConditionNode> condition) {

}


