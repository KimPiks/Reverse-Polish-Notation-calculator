#ifndef ENUMS_H
#define ENUMS_H

enum TokenType {
  NUMBER,
  LEFT_BRACKET,
  RIGHT_BRACKET,
  COMMA,
  OPERATOR,
  FUNCTION
};

enum OperatorType {
  NO_OPERATOR,
  ADDING,
  SUBTRACTING,
  MULTIPLYING,
  DIVIDING
};

enum FunctionType {
  NO_FUNCTION,
  IF,
  N,
  MIN,
  MAX
};

#endif
