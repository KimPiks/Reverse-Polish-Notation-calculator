#include <cstdio>
#include <cstdlib>

#include "Queue.h"
#include "Stack.h"
#include "Token.h"

Token* convertToToken(const char input[13]) {
  if (input[0] >= '0' && input[0] <= '9')
    return new Token(atoi(input));

  switch (input[0]) {
    case '(':
      return new Token(TokenType::LEFT_BRACKET);
    case ')':
      return new Token(TokenType::RIGHT_BRACKET);
    case ',':
      return new Token(TokenType::COMMA);
    case '*':
      return new Token(TokenType::OPERATOR, OperatorType::MULTIPLYING);
    case '/':
      return new Token(TokenType::OPERATOR, OperatorType::DIVIDING);
    case '+':
      return new Token(TokenType::OPERATOR, OperatorType::ADDING);
    case '-':
      return new Token(TokenType::OPERATOR, OperatorType::SUBTRACTING);
    case 'I':
      return new Token(TokenType::FUNCTION, FunctionType::IF, 3);
    case 'N':
      return new Token(TokenType::FUNCTION, FunctionType::N, 1);
    case 'M':
      if (input[1] == 'I')
        return new Token(TokenType::FUNCTION, FunctionType::MIN, 0);
      return new Token(TokenType::FUNCTION, FunctionType::MAX, 0);
    default:
      break;
  }
  return new Token(-1);
}

bool isTopStackOperatorMoreOrEqualsImportant(const Token* topOperator, const Token* token) {
  if (topOperator->getTokenType() == TokenType::FUNCTION && token->getTokenType() == TokenType::OPERATOR)
    return true;

  if (topOperator->getTokenType() == TokenType::FUNCTION &&
    (topOperator->getFunctionType() == FunctionType::MIN || topOperator->getFunctionType() == FunctionType::MAX))
    return true;

  if (topOperator->getTokenType() == TokenType::FUNCTION && token->getTokenType() == TokenType::FUNCTION)
    return topOperator->getFunctionType() >= token->getFunctionType();

  if (topOperator->getTokenType() == TokenType::OPERATOR && token->getTokenType() == TokenType::OPERATOR) {
    switch (token->getOperatorType()) {
      case OperatorType::ADDING: case OperatorType::SUBTRACTING:
        return true;
      case OperatorType::MULTIPLYING: case OperatorType::DIVIDING:
        return topOperator->getOperatorType() != OperatorType::ADDING &&
               topOperator->getOperatorType() != OperatorType::SUBTRACTING;
      default:
        return false;
    }
  }

  return false;
}

void processPostfix(Stack* operators, Stack* arguments, Queue* postfix, Token* token) {
    switch (token->getTokenType()) {
        case TokenType::LEFT_BRACKET:
            operators->push(*token);
            break;
        case TokenType::RIGHT_BRACKET:
            while (operators->top()->getTokenType() != TokenType::LEFT_BRACKET) {
                if (operators->top()->getTokenType() == TokenType::FUNCTION) {
                    operators->top()->setArguments(arguments->top()->getValue());
                    arguments->pop();
                }
                postfix->push(*operators->top());
                operators->pop();
            }
            operators->pop();
            if (!operators->empty() && operators->top()->getTokenType() == TokenType::FUNCTION) {
                operators->top()->setArguments(arguments->top()->getValue());
                arguments->pop();
                postfix->push(*operators->top());
                operators->pop();
            }
            break;
        case TokenType::COMMA: {
            while (operators->top()->getTokenType() != TokenType::LEFT_BRACKET) {
                if (operators->top()->getTokenType() == TokenType::FUNCTION &&
                    operators->top()->getFunctionType() == FunctionType::N) {
                    arguments->pop();
                }
                postfix->push(*operators->top());
                operators->pop();
            }

            const int args = arguments->top()->getValue();
            arguments->pop();
            arguments->push(Token(args + 1));
            break;
        }
        case TokenType::NUMBER:
            postfix->push(*token);
            break;
        case TokenType::FUNCTION:
            arguments->push(Token(1));
            operators->push(*token);
            break;
        case TokenType::OPERATOR:
            while (!operators->empty() && isTopStackOperatorMoreOrEqualsImportant(operators->top(), token)) {
                if (operators->top()->getTokenType() == TokenType::FUNCTION) {
                    operators->top()->setArguments(arguments->top()->getValue());
                    arguments->pop();
                }
                postfix->push(*operators->top());
                operators->pop();
            }
            operators->push(*token);
            break;
        default:
            break;
    }
}

void calculateExpression(Queue* postfix) {
    Stack* calculations = new Stack();
    bool error = false;

    while (!postfix->empty()) {
        switch (postfix->first()->getTokenType()) {
            case TokenType::NUMBER:
                calculations->push(Token(postfix->first()->getValue()));
                break;
            case TokenType::OPERATOR: {
                switch (postfix->first()->getOperatorType()) {
                    case OperatorType::MULTIPLYING: {
                        printf("* ");
                        calculations->displayStack();
                        int a = calculations->top()->getValue();
                        calculations->pop();
                        int b = calculations->top()->getValue();
                        calculations->pop();
                        calculations->push(Token(b * a));
                        printf("\n");
                        break;
                    }
                    case OperatorType::DIVIDING: {
                        printf("/ ");
                        calculations->displayStack();
                        int a = calculations->top()->getValue();
                        calculations->pop();
                        int b = calculations->top()->getValue();
                        calculations->pop();
                        if (a == 0) {
                            error = true;
                            printf("\n");
                            break;
                        }
                        calculations->push(Token(b / a));
                        printf("\n");
                        break;
                    }
                    case OperatorType::ADDING: {
                        printf("+ ");
                        calculations->displayStack();
                        int a = calculations->top()->getValue();
                        calculations->pop();
                        int b = calculations->top()->getValue();
                        calculations->pop();
                        calculations->push(Token(b + a));
                        printf("\n");
                        break;
                    }
                    case OperatorType::SUBTRACTING: {
                        printf("- ");
                        calculations->displayStack();
                        int a = calculations->top()->getValue();
                        calculations->pop();
                        int b = calculations->top()->getValue();
                        calculations->pop();
                        calculations->push(Token(b - a));
                        printf("\n");
                        break;
                    }
                    default:
                        break;
                }
            }
            case TokenType::FUNCTION: {
                switch (postfix->first()->getFunctionType()) {
                    case FunctionType::IF: {
                        printf("IF ");
                        calculations->displayStack();
                        int a = calculations->top()->getValue();
                        calculations->pop();
                        int b = calculations->top()->getValue();
                        calculations->pop();
                        int c = calculations->top()->getValue();
                        calculations->pop();
                        calculations->push(Token(c > 0 ? b : a));
                        printf("\n");
                        break;
                    }
                    case FunctionType::N: {
                        printf("N ");
                        calculations->displayStack();
                        int a = calculations->top()->getValue();
                        calculations->pop();
                        calculations->push(Token(-a));
                        printf("\n");
                        break;
                    }
                    case FunctionType::MIN: {
                        printf("MIN%d ", postfix->first()->getArguments());
                        calculations->displayStack();
                        int min = 0;
                        bool start = true;
                        int y;
                        for (y = 0; y < postfix->first()->getArguments(); y++) {
                            if (start) {
                                min = calculations->top()->getValue();
                                start = false;
                            } else {
                                if (calculations->top()->getValue() < min) {
                                    min = calculations->top()->getValue();
                                }
                            }
                            calculations->pop();
                        }
                        calculations->push(Token(min));
                        printf("\n");
                        break;
                    }
                    case FunctionType::MAX: {
                        printf("MAX%d ", postfix->first()->getArguments());
                        calculations->displayStack();
                        int max = 0;
                        bool start = true;
                        int y;
                        for (y = 0; y < postfix->first()->getArguments(); y++) {
                            if (start) {
                                max = calculations->top()->getValue();
                                start = false;
                            } else {
                                if (calculations->top()->getValue() > max) {
                                    max = calculations->top()->getValue();
                                }
                            }
                            calculations->pop();
                        }
                        calculations->push(Token(max));
                        printf("\n");
                        break;
                    }
                    default:
                        break;
                }
            }

            default:
                break;
        }

        if (error) break;
        postfix->pop();
    }

    if (!error) {
        printf("%d", calculations->top()->getValue());
        calculations->pop();
    } else {
        printf("ERROR\n");
    }

    while (!calculations->empty()) {
        calculations->pop();
    }
    delete calculations;
}

void addRemainingOperators(Stack* operators, Stack* arguments, Queue* postfix) {
    while (!operators->empty()) {
        if (operators->top()->getTokenType() == TokenType::FUNCTION) {
            operators->top()->setArguments(arguments->top()->getValue());
            arguments->pop();
        }
        postfix->push(*operators->top());
        operators->pop();
    }
}

int main() {
  int n;
  scanf("%d", &n);

  // Iteration over n formulas
  int i;
  for (i = 0; i < n; i++) {
    Stack* operators = new Stack();
    Stack* arguments = new Stack();
    Queue* postfix = new Queue();

    // Iteration over formula
    char input[13] = "\0"; 
    while (true) {
      scanf("%13s", &input);
      if (input[0] == '.') break;

      Token* token = convertToToken(input);
      processPostfix(operators, arguments, postfix, token);
      delete token;
    }

    // Add all remaining operators to the postfix notation
    addRemainingOperators(operators, arguments, postfix);

    // Display postfix notation
    postfix->displayQueue();
    printf("\n");

    // Calculate expression
    calculateExpression(postfix);
    printf("\n");

    // Clear memory
    while (!postfix->empty()) {
      postfix->pop();
    }

    delete operators;
    delete arguments;
    delete postfix;
  }

  return 0;
}
