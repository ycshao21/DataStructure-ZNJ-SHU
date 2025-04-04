#pragma once
#include "BinarySearchTreeNode.h"
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace myds {

template <class K, class E> struct BinarySearchTreeNode {
  std::pair<K, E> data; // { key, element }
  BinarySearchTreeNode<K, E> *leftChild = nullptr;
  BinarySearchTreeNode<K, E> *rightChild = nullptr;
};

template <class K, class E> class BinarySearchTree {
  using Node = BinarySearchTreeNode<K, E>;
  using Pair = std::pair<K, E>;

public:
  BinarySearchTree() : m_root(nullptr), m_size(0) {}
  BinarySearchTree(const BinarySearchTree<K, E> &tree)
      : m_root(_CopyTree(tree.m_root)), m_size(tree.m_size) {}
  BinarySearchTree(const std::vector<Pair> &pairs);
  ~BinarySearchTree() { this->Clear(); }

  bool isEmpty() const { return m_size == 0; }
  int getSize() const { return m_size; }
  int getHeight() const { return _getHeight(m_root); }
  Pair *getRootElement() const { return m_root ? &m_root->data : nullptr; }

  Pair *find(const K &key) const;

  void clear();
  void insert(const K &key, const E &element);
  // Replace it with the maximum node in its left subtree.
  void erase_ver1(const K &key);
  // Replace it with the minimum node in its right subtree.
  void erase_ver2(const K &key);
  // Move its left subtree to the left subtree of the minimum node in its right
  // subtree.
  void erase_ver3(const K &key);
  // Move its right subtree to the right subtree of the maximum node in its left
  // subtree.
  void erase_ver4(const K &key);

  void preOrder(void (*v)(Node *)) {
    s_visit = v;
    _preOrder(m_root);
  }
  void inOrder(void (*v)(Node *)) {
    s_visit = v;
    _inOrder(m_root);
  }
  void postOrder(void (*v)(Node *)) {
    s_visit = v;
    _postOrder(m_root);
  }

  void printElements(std::ostream &out = std::cout) const { inOrder(Print); }
  void printKeyTree(std::ostream &out = std::cout) const {
    _printKeyTree(m_root, out);
  }

private:
  Node *_copyTree(Node *r);
  static int _getHeight(Node *r);
  static void _preOrder(Node *r);
  static void _inOrder(Node *r);
  static void
  _inOrder(Node *r,
           std::vector<Node *> &nodePtrVec); // For outputTree function.
  static void _postOrder(Node *r);
  static void _printKeyTree(Node *r, std::ostream &out = std::cout);
  static void print(Node *r) { std::cout << r->data.second << " "; }
  static void dispose(Node *node) { delete node; }

private:
  Node *m_root;
  int m_size;
  static void (*s_visit)(Node *);
};

template <class K, class E>
void (*BinarySearchTree<K, E>::s_visit)(Node *) = nullptr;

template <class K, class E>
auto BinarySearchTree<K, E>::_getHeight(Node *r) -> int {
  if (!r) {
    return 0;
  }
  return 1 + std::max(_getHeight(r->leftChild), _getHeight(r->rightChild));
}

template <class K, class E>
auto BinarySearchTree<K, E>::_copyTree(Node *r) -> Node * {
  if (!r) {
    return nullptr;
  }
  Node *lChild = _copyTree(r->leftChild);
  Node *rChild = _copyTree(r->rightChild);
  Node *root = new Node{r->data, lChild, rChild};
  return root;
}

template <class K, class E>
BinarySearchTree<K, E>::BinarySearchTree(const std::vector<Pair> &pairs) {
  m_root = nullptr;
  m_size = 0;
  for (const auto &pair : pairs) {
    insert(pair.first, pair.second);
  }
}

template <class K, class E>
auto BinarySearchTree<K, E>::find(const K &key) const -> Pair * {
  Node *cur = m_root;
  while (cur) {
    if (key < cur->data.first)
      cur = cur->leftChild;
    else if (key > cur->data.first)
      cur = cur->rightChild;
    else
      return &cur->data;
  }
  return nullptr;
}

template <class K, class E> void BinarySearchTree<K, E>::clear() {
  postOrder(dispose);
  m_root = nullptr;
  m_size = 0;
}

template <class K, class E>
void BinarySearchTree<K, E>::insert(const K &key, const E &element) {
  Node *cur = m_root;
  Node *parent = nullptr;
  while (cur) {
    parent = cur;
    // Move cur to one of its child.
    if (key < cur->data.first) {
      cur = cur->leftChild;
    } else if (key > cur->data.first) {
      cur = cur->rightChild;
    } else {
      // If the key is already in the tree, cover the old value.
      cur->data.second = element;
      return;
    }
  }

  // Create a new node.
  cur = new Node{Pair{key, element}};
  if (m_root == nullptr) {
    m_root = cur;
  } else {
    if (key < parent->data.first) {
      parent->leftChild = cur;
    } else {
      parent->rightChild = cur;
    }
  }
  m_size++;
}

template <class K, class E>
void BinarySearchTree<K, E>::erase_ver1(const K &key) {
  Node *del = m_root;
  Node *delParent = nullptr;

  // Find the node to delete.
  while (del && del->data.first != key) {
    delParent = del;
    if (key < del->data.first) {
      del = del->leftChild;
    } else {
      del = del->rightChild;
    }
  }
  // The key is not in the tree.
  if (del == nullptr) {
    return;
  }

  // If del has no left child, replace it with its right child.
  if (del->leftChild == nullptr) {
    if (del == m_root) {
      m_root = del->rightChild;
    } else {
      if (delParent->leftChild == del) {
        delParent->leftChild = del->rightChild;
      } else {
        delParent->rightChild = del->rightChild;
      }
    }
    delete del;
  } else { // Otherwise, replace it with the maximum node in its left subtree.
    Node *maxNode = del->leftChild;
    Node *maxParent = del;
    // Find the maximum node in the left subtree.
    while (maxNode->rightChild) {
      maxParent = maxNode;
      maxNode = maxNode->rightChild;
    }
    del->data = std::move(maxNode->data);
    if (maxParent->leftChild == maxNode) {
      maxParent->leftChild = maxNode->leftChild;
    } else {
      maxParent->rightChild = maxNode->leftChild;
    }
    delete maxNode;
  }
  m_size--;
}

template <class K, class E>
void BinarySearchTree<K, E>::erase_ver2(const K &key) {
  Node *del = m_root;
  Node *delParent = nullptr;
  // Find the node to delete.
  while (del && del->data.first != key) {
    delParent = del;
    if (key < del->data.first) {
      del = del->leftChild;
    } else {
      del = del->rightChild;
    }
  }
  // The key is not in the tree.
  if (del == nullptr) {
    return;
  }

  // If del has no right child, replace it with its left child.
  if (del->rightChild == nullptr) {
    if (del == m_root) {
      m_root = del->leftChild;
    } else {
      if (delParent->leftChild == del) {
        delParent->leftChild = del->leftChild;
      } else {
        delParent->rightChild = del->leftChild;
      }
    }
    delete del;
  } else { // Otherwise, replace it with the minimum node in its right subtree.
    Node *minNode = del->rightChild;
    Node *minParent = del;
    // Find the minimum node in the right subtree.
    while (minNode->leftChild) {
      minParent = minNode;
      minNode = minNode->leftChild;
    }
    del->data = std::move(minNode->data);

    if (minParent->rightChild == minNode) {
      minParent->rightChild = minNode->rightChild;
    } else {
      minParent->leftChild = minNode->rightChild;
    }
    delete minNode;
  }
  m_size--;
}

template <class K, class E>
void BinarySearchTree<K, E>::erase_ver3(const K &key) {
  Node *del = m_root;
  Node *delParent = nullptr;
  // Find the node to delete.
  while (del && del->data.first != key) {
    delParent = del;
    if (key < del->data.first) {
      del = del->leftChild;
    } else {
      del = del->rightChild;
    }
  }
  // The key is not in the tree.
  if (del == nullptr) {
    return;
  }

  // If del has no right child, replace it with its left child.
  if (del->rightChild == nullptr) {
    if (del == m_root) {
      m_root = del->leftChild;
    } else {
      if (delParent->leftChild == del) {
        delParent->leftChild = del->leftChild;
      } else {
        delParent->rightChild = del->leftChild;
      }
    }
    delete del;
    m_size--;
    return;
  }
  // If del has left subtree, move it to the left subtree of the minimum node in
  // del's right subtree.
  if (del->leftChild) {
    Node *minNode = del->rightChild;
    // Find the minimum node in the right subtree.
    while (minNode->leftChild) {
      minNode = minNode->leftChild;
    }
    minNode->leftChild = del->leftChild;
  }
  if (del == m_root) {
    m_root = del->rightChild;
  } else {
    if (delParent->leftChild == del) {
      delParent->leftChild = del->rightChild;
    } else {
      delParent->rightChild = del->rightChild;
    }
  }
  delete del;
  m_size--;
}

template <class K, class E>
void BinarySearchTree<K, E>::erase_ver4(const K &key) {
  Node *del = m_root;
  Node *delParent = nullptr;
  // Find the node to delete.
  while (del && del->data.first != key) {
    delParent = del;
    if (key < del->data.first)
      del = del->leftChild;
    else
      del = del->rightChild;
  }
  // The key is not in the tree.
  if (!del) {
    return;
}

  // If del has no left child, replace it with its right child.
  if (!del->leftChild) {
    if (del == m_root) {
      m_root = del->rightChild;
    } else {
      if (delParent->leftChild == del) {
        delParent->leftChild = del->rightChild;
      } else {
        delParent->rightChild = del->rightChild;
      }
    }
    delete del;
    m_size--;
    return;
  }
  // If del has right subtree, move it to the right subtree of the maximum node
  // in del's left subtree.
  if (del->rightChild) {
    Node *maxNode = del->leftChild;
    // Find the minimum node in the right subtree.
    while (maxNode->rightChild) {
      maxNode = maxNode->rightChild;
    }
    maxNode->rightChild = del->rightChild;
  }
  if (del == m_root) {
    m_root = del->leftChild;
  } else {
    if (delParent->leftChild == del) {
      delParent->leftChild = del->leftChild;
    } else {
      delParent->rightChild = del->leftChild;
    }
  }
  delete del;
  m_size--;
}

template <class K, class E> void BinarySearchTree<K, E>::_preOrder(Node *r) {
  if (r == nullptr) {
    return;
  }

  _preOrder(r->leftChild);
  s_visit(r);
  _preOrder(r->rightChild);
}

template <class K, class E> void BinarySearchTree<K, E>::_inOrder(Node *r) {
  if (r == nullptr) {
    return;
  }

  _inOrder(r->leftChild);
  s_visit(r);
  _inOrder(r->rightChild);
}

template <class K, class E>
void BinarySearchTree<K, E>::_inOrder(Node *r,
                                      std::vector<Node *> &nodePtrVec) {
  if (r == nullptr) {
    return;
  }

  _inOrder(r->leftChild, nodePtrVec);
  nodePtrVec.push_back(r);
  _inOrder(r->rightChild, nodePtrVec);
}

template <class K, class E> void BinarySearchTree<K, E>::_postOrder(Node *r) {
  if (r == nullptr) {
    return;
  }

  _postOrder(r->leftChild);
  _postOrder(r->rightChild);
  s_visit(r);
}

template <class K, class E>
void BinarySearchTree<K, E>::_printKeyTree(Node *r, std::ostream &out) {
  if (r == nullptr) {
    return;
  }

  // Get the width of the tree.
  std::vector<Node *> ptrs;
  _inOrder(r, ptrs);
  std::ostringstream ss;               // For type conversion.
  std::unordered_map<Node *, int> pos; // Position of each node.
  for (const auto &p : ptrs) {
    pos[p] = (int)ss.str().size();
    ss << p->data.first << " ";
  }
  int width = (int)ss.str().size();
  ss.str("");
  // Levelorder traversal to print the tree.
  std::queue<Node *> q;
  q.push(r);
  while (!q.empty()) {
    std::string firstLine(width, ' ');
    std::string secondLine(width, ' ');
    // Traverse the current level.
    int curLevelSize = (int)q.size();
    for (int i = 0; i < curLevelSize; ++i) {
      Node *curNodePtr = q.front();
      q.pop();
      int elemPos = pos[curNodePtr];
      // If the node has a left child, connect them with '\' on the second line
      // and '_'s on the first line.
      if (curNodePtr->leftChild) {
        q.push(curNodePtr->leftChild);
        int slashPos = pos[curNodePtr->leftChild] + 1;
        secondLine[slashPos] = '/';
        for (int j = slashPos + 1; j < elemPos; j++) {
          firstLine[j] = '_';
        }
      }
      // Print the element on the first line.
      ss << curNodePtr->data.first;
      std::string elemStr = ss.str();
      ss.str("");
      for (int j = 0; j < (int)elemStr.size(); ++j, ++elemPos) {
        firstLine[elemPos] = elemStr[j];
      }

      // If the node has a right child, connect them with '\' on the second line
      // and '_'s on the first line.
      if (curNodePtr->rightChild) {
        q.push(curNodePtr->rightChild);
        int backSlashPos = pos[curNodePtr->rightChild] - 1;
        secondLine[backSlashPos] = '\\';
        for (int j = backSlashPos - 1; j > elemPos; j--) {
          firstLine[j] = '_';
        }
      }
    }
    // Print the current level.
    out << firstLine << "\n" << secondLine << '\n';
  }
}
} // namespace myds
