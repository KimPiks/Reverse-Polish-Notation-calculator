#include "Token.h"

Token::Token (const int value) : tokenType(TokenType::NUMBER), value(value) {}
Token::Token(const TokenType tokenType) : tokenType(tokenType) {}
Token::Token(const TokenType tokenType, const OperatorType operatorType) : tokenType(tokenType), operatorType(operatorType) {}
Token::Token(const TokenType tokenType, const FunctionType functionType, const int args) : tokenType(tokenType), functionType(functionType), arguments(args) {}


TokenType Token::getTokenType() const {
  return this->tokenType;
}

OperatorType Token::getOperatorType() const {
  return this->operatorType;
}

FunctionType Token::getFunctionType() const {
  return this->functionType;
}

int Token::getArguments() const {
  return this->arguments;
}

int Token::getValue() const {
  return this->value;
}

void Token::setArguments(const int args) {
  this->arguments = args;
}
