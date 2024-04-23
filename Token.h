#ifndef TOKEN_H
#define TOKEN_H

#include "Enums.h"

class Token {
  TokenType tokenType;
  FunctionType functionType = FunctionType::NO_FUNCTION;
  OperatorType operatorType = OperatorType::NO_OPERATOR;
  int arguments = 0;
  int value = 0;

public:
  explicit Token(int value);
  explicit Token(TokenType tokenType);
  Token(TokenType tokenType, OperatorType operatorType);
  Token(TokenType tokenType, FunctionType functionType, int args);

  TokenType getTokenType() const;
  FunctionType getFunctionType() const;
  OperatorType getOperatorType() const;
  int getArguments() const;
  int getValue() const;
  void setArguments(int args);
};



#endif