#ifndef NODE_H
#define NODE_H

#include "Token.h"


class Node {
  Token token;
  Node* nextNode = nullptr;

public:
  Node (const Token &token, Node* nd);

  Token* getToken();
  Node* getNextNode() const;
  void setNextNode(Node* nd);
};



#endif
