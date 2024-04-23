#include "Stack.h"

#include <cstdio>

void Stack::push(Token token) {
  if (this->empty()) {
    this->topNode = new Node(token, nullptr);
    this->stackSize = 1;
    return;
  }

  Node* latestNode = this->topNode;
  this->topNode = new Node(token, latestNode);
  this->stackSize++;
}

void Stack::pop() {
  if (this->size() == 1) {
    delete this->topNode;
    this->topNode = nullptr;
    this->stackSize = 0;
    return;
  }

  const Node* latestNode = this->topNode;
  this->topNode = this->topNode->getNextNode();
  delete latestNode;
  this->stackSize--;
}

Token* Stack::top() const {
  return this->topNode->getToken();
}

bool Stack::empty() const {
  return this->stackSize == 0;
}

int Stack::size() const {
  return this->stackSize;
}

void Stack::displayStack() const {
  Node* nextNode = this->topNode;
  while (nextNode != nullptr) {
    switch (nextNode->getToken()->getTokenType()) {
      case TokenType::NUMBER:
        printf("%d ", nextNode->getToken()->getValue());
        break;
      case TokenType::OPERATOR:
        switch (nextNode->getToken()->getOperatorType()) {
          case OperatorType::ADDING:
            printf("+ ");
            break;
          case OperatorType::SUBTRACTING:
            printf("- ");
            break;
          case OperatorType::MULTIPLYING:
            printf("* ");
            break;
          case OperatorType::DIVIDING:
            printf("/ ");
            break;
          default:
            break;
        }
        break;
        case TokenType::FUNCTION: {
          switch (nextNode->getToken()->getFunctionType()) {
            case FunctionType::MIN:
              printf("MIN%d ", nextNode->getToken()->getArguments());
              break;
            case FunctionType::MAX:
              printf("MAX%d ", nextNode->getToken()->getArguments());
              break;
            case FunctionType::IF:
              printf("IF ");
              break;
            case FunctionType::N:
              printf("N ");
              break;
            default:
              break;
          }
        }
      default:
        break;
    }
    nextNode = nextNode->getNextNode();
  }
}
