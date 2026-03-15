#pragma once

#include <memory>
#include <string>
#include <vector>
#include "token.hpp"

// base class for nodes in abstract syntax tree
class Node {
 public:
  virtual ~Node() = default;
};

// base class for expr nodes
class ExprNode : public Node {
 public:
  virtual ~ExprNode() = default;
};

// literal value
class LiteralNode : public ExprNode {
 public:
  semp::Token value;  // token containing literal value

  // constructor
  explicit LiteralNode(semp::Token value) : value(value) {}
};

// variable or identifier in an expression
class IdentifierNode : public ExprNode {
 public:
  semp::Token name;  // token storing the identifier name

  // constructor
  explicit IdentifierNode(semp::Token name) : name(name) {}
};

// binary expression node
class BinaryExprNode : public ExprNode {
 public:
  std::unique_ptr<ExprNode> left;   // LHS expr
  semp::Token op;                   // operator tokens (+, -, *, /)
  std::unique_ptr<ExprNode> right;  // RHS expr

  // constructor
  BinaryExprNode(std::unique_ptr<ExprNode> left, semp::Token op,
                 std::unique_ptr<ExprNode> right)
      : left(std::move(left)), op(op), right(std::move(right)) {}
};

// base class for statement nodes
class StatementNode : public Node {
 public:
  virtual ~StatementNode() = default;
};

// return statement
class ReturnStatementNode : public StatementNode {
 public:
  std::unique_ptr<ExprNode> value;  // expression returned

  // constructor
  explicit ReturnStatementNode(std::unique_ptr<ExprNode> value)
      : value(std::move(value)) {}
};

// block of statements
class BlockStatementNode : public StatementNode {
 public:
  std::vector<std::unique_ptr<StatementNode>> statements;

  // constructor
  explicit BlockStatementNode(
      std::vector<std::unique_ptr<StatementNode>> statements)
      : statements(std::move(statements)) {}
};
