#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"


class Queue {
  Node* firstNode = nullptr;
  Node* lastNode = nullptr;
  int queueSize = 0;

  Node* getLastNode() const;

public:
  void push(Token token);
  void pop();
  Token* first() const;
  bool empty() const;
  int size() const;
  void displayQueue() const;
};



#endif
