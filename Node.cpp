#include "Node.h"
#include "Token.h"

Node::Node(const Token &token, Node *nd) : token(token), nextNode(nd) {}


Token* Node::getToken() {
  return &this->token;
}

Node *Node::getNextNode() const {
  return this->nextNode;
}

void Node::setNextNode(Node *nd) {
  this->nextNode = nd;
}