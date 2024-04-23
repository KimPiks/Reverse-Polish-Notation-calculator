#include "Queue.h"

#include <cstdio>

void Queue::push(Token token) {
  if (this->empty()) {
    this->firstNode = new Node(token, nullptr);
    this->lastNode = this->firstNode;
    this->queueSize = 1;
    return;
  }

  Node* lLastNode = this->getLastNode();
  lLastNode->setNextNode(new Node(token, nullptr));
  this->lastNode = lLastNode->getNextNode();
  this->queueSize++;
}

void Queue::pop() {
  if (this->size() == 1) {
    delete this->firstNode;
    this->firstNode = nullptr;
    this->queueSize = 0;
    return;
  }

  Node* secondNode = this->firstNode->getNextNode();
  delete this->firstNode;
  this->firstNode = secondNode;
  this->queueSize--;
}

Token* Queue::first() const {
  return this->firstNode->getToken();
}

bool Queue::empty() const {
  return this->queueSize == 0;
}

int Queue::size() const {
  return this->queueSize;
}

Node* Queue::getLastNode() const {
  return this->lastNode;
}

void Queue::displayQueue() const {
  Node* nextNode = this->firstNode;
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
