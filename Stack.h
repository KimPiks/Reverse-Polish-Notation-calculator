#ifndef STACK_H
#define STACK_H

#include "Node.h"


class Stack {
  Node* topNode = nullptr;
  int stackSize = 0;

public:
  void push(Token token);
  void pop();
  Token* top() const;
  bool empty() const;
  int size() const;
  void displayStack() const;
};



#endif