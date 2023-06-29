#pragma once
#include<iostream>
#include<sstream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<string>
#include<iomanip>
#include"BinarySearchTreeNode.h"
#include"../../Tools/myExceptions.h"

template<class K, class E>
class BinarySearchTree
{
    using Node = BinarySearchTreeNode<K, E>;
    using Pair = std::pair<K, E>;
    using sizet = size_t;
    using indext = size_t;
public:
    /* Constructors and Destructor. */

    BinarySearchTree() : rt(nullptr), treeSize(0) {}
    BinarySearchTree(const BinarySearchTree<K, E>& tree) :rt(copyTree(tree.rt)), treeSize(tree.treeSize) {}
    BinarySearchTree(const std::vector<Pair>& pairs);
    ~BinarySearchTree() { this->clear(); }

    /* Status */

    bool empty() const { return treeSize == 0; }
    sizet size() const { return treeSize; }
    sizet height() const { return height(rt); }
    Pair* root() const { return rt ? &rt->data : nullptr; }

    /* Element Access */

    Pair* find(const K& key) const;

    /* Modifier */

    void clear();
    void insert(const K& key, const E& element);
    // Replace it with the maximum node in its left subtree.
    void erase_ver1(const K& key);
    // Replace it with the minimum node in its right subtree.
    void erase_ver2(const K& key);
    // Move its left subtree to the left subtree of the minimum node in its right subtree.
    void erase_ver3(const K& key);
    // Move its right subtree to the right subtree of the maximum node in its left subtree.
    void erase_ver4(const K& key);

    /* Traversal */

    void preOrder(void (*v)(Node*)) { visit = v; preOrder(rt); }
    void inOrder(void (*v)(Node*)) { visit = v; inOrder(rt); }
    void postOrder(void (*v)(Node*)) { visit = v; postOrder(rt); }

    /* Others */

    void outputElements(std::ostream& out = std::cout) const { inOrder(print); }
    void outputTree(std::ostream& out = std::cout) const { outputTree(rt, out); }
private:
    Node* rt;
    sizet treeSize;
    static void (*visit)(Node*);

    Node* copyTree(Node* r);
    static sizet height(Node* r);
    static void preOrder(Node* r);
    static void inOrder(Node* r);
    static void inOrder(Node* r, std::vector<Node*>& nodePtrVec);  // For outputTree function.
    static void postOrder(Node* r);
    static void outputTree(Node* r, std::ostream& out = std::cout);
    static void print(Node* r) { std::cout << r->data.second << " "; }
    static void dispose(Node* node) { delete node; }
};

template<class K, class E>
void (*BinarySearchTree<K, E>::visit)(Node*) = nullptr;

template<class K, class E>
auto BinarySearchTree<K, E>::height(Node* r) -> sizet {
    if (r == nullptr) { return 0; }
    return 1 + std::max(height(r->leftChild), height(r->rightChild));
}

template<class K, class E>
auto BinarySearchTree<K, E>::copyTree(Node* r) -> Node* {
    if (r == nullptr) { return nullptr; }
    Node* lChild = copyTree(r->leftChild);
    Node* rChild = copyTree(r->rightChild);
    Node* root = new Node{ r->element, lChild, rChild };
    return root;
}

template<class K, class E>
BinarySearchTree<K, E>::BinarySearchTree(const std::vector<Pair>& pairs) {
    rt = nullptr;
    treeSize = 0;
    for (const auto& pair : pairs) {
        this->insert(pair.first, pair.second);
    }
}

template<class K, class E>
auto BinarySearchTree<K, E>::find(const K& key) const -> Pair* {
    Node* cur = rt;
    while (cur != nullptr) {
        if (key < cur->data.first) {
            cur = cur->leftChild;
        } else if (key > cur->data.first) {
            cur = cur->rightChild;
        } else {
            return &(cur->data);
        }
    }
    return nullptr;
}

template<class K, class E>
void BinarySearchTree<K, E>::clear() {
    postOrder(dispose);
    rt = nullptr;
    treeSize = 0;
}

template<class K, class E>
void BinarySearchTree<K, E>::insert(const K& key, const E& element) {
    Node* cur = rt;
    Node* parent = nullptr;
    while (cur != nullptr) {
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
    cur = new Node{ Pair{key, element} };
    if (rt == nullptr) {
        rt = cur;
    } else {
        if (key < parent->data.first) {
            parent->leftChild = cur;
        } else {
            parent->rightChild = cur;
        }
    }
    treeSize++;
}

template<class K, class E>
void BinarySearchTree<K, E>::erase_ver1(const K& key) {
    Node* del = rt;
    Node* delParent = nullptr;
    // Find the node to delete.
    while (del != nullptr && del->data.first != key) {
        delParent = del;
        if (key < del->data.first) {
            del = del->leftChild;
        } else {
            del = del->rightChild;
        }
    }
    // The key is not in the tree.
    if (del == nullptr) { return; }
    // If del has no left child, replace it with its right child.
    if (del->leftChild == nullptr) {
        if (del == rt) {
            rt = del->rightChild;
        } else {
            if (delParent->leftChild == del) {
                delParent->leftChild = del->rightChild;
            } else {
                delParent->rightChild = del->rightChild;
            }
        }
        delete del;
    } else {  // Otherwise, replace it with the maximum node in its left subtree.
        Node* maxNode = del->leftChild;
        Node* maxParent = del;
        // Find the maximum node in the left subtree.
        while (maxNode->rightChild != nullptr) {
            maxParent = maxNode;
            maxNode = maxNode->rightChild;
        }
        del->data = std::move(maxNode->data);
        if (maxParent->leftChild == maxNode) {  // maxParent == del
            maxParent->leftChild = maxNode->leftChild;
        } else {
            maxParent->rightChild = maxNode->leftChild;
        }
        delete maxNode;
    }
}

template<class K, class E>
void BinarySearchTree<K, E>::erase_ver2(const K& key) {
    Node* del = rt;
    Node* delParent = nullptr;
    // Find the node to delete.
    while (del != nullptr && del->data.first != key) {
        delParent = del;
        if (key < del->data.first) {
            del = del->leftChild;
        } else {
            del = del->rightChild;
        }
    }
    // The key is not in the tree.
    if (del == nullptr) { return; }
    // If del has no right child, replace it with its left child.
    if (del->rightChild == nullptr) {
        if (del == rt) {
            rt = del->leftChild;
        } else {
            if (delParent->leftChild == del) {
                delParent->leftChild = del->leftChild;
            } else {
                delParent->rightChild = del->leftChild;
            }
        }
        delete del;
    } else {  // Otherwise, replace it with the minimum node in its right subtree.
        Node* minNode = del->rightChild;
        Node* minParent = del;
        // Find the minimum node in the right subtree.
        while (minNode->leftChild != nullptr) {
            minParent = minNode;
            minNode = minNode->leftChild;
        }
        del->data = std::move(minNode->data);
        if (minParent->rightChild == minNode) {  // minParent == del
            minParent->rightChild = minNode->rightChild;
        } else {
            minParent->leftChild = minNode->rightChild;
        }
        delete minNode;
    }
}

template<class K, class E>
void BinarySearchTree<K, E>::erase_ver3(const K& key) {
    Node* del = rt;
    Node* delParent = nullptr;
    // Find the node to delete.
    while (del != nullptr && del->data.first != key) {
        delParent = del;
        if (key < del->data.first) {
            del = del->leftChild;
        } else {
            del = del->rightChild;
        }
    }
    // The key is not in the tree.
    if (del == nullptr) { return; }
    // If del has no right child, replace it with its left child.
    if (del->rightChild == nullptr) {
        if (del == rt) {
            rt = del->leftChild;
        } else {
            if (delParent->leftChild == del) {
                delParent->leftChild = del->leftChild;
            } else {
                delParent->rightChild = del->leftChild;
            }
        }
        delete del;
        return;
    }
    // If del has left subtree, move it to the left subtree of the minimum node in del's right subtree.
    if (del->leftChild != nullptr) {
        Node* minNode = del->rightChild;
        // Find the minimum node in the right subtree.
        while (minNode->leftChild != nullptr) {
            minNode = minNode->leftChild;
        }
        minNode->leftChild = del->leftChild;
    }
    if (del == rt) {
        rt = del->rightChild;
    } else {
        if (delParent->leftChild == del) {
            delParent->leftChild = del->rightChild;
        } else {
            delParent->rightChild = del->rightChild;
        }
    }
    delete del;
}

template<class K, class E>
void BinarySearchTree<K, E>::erase_ver4(const K& key) {
    Node* del = rt;
    Node* delParent = nullptr;
    // Find the node to delete.
    while (del != nullptr && del->data.first != key) {
        delParent = del;
        if (key < del->data.first) {
            del = del->leftChild;
        } else {
            del = del->rightChild;
        }
    }
    // The key is not in the tree.
    if (del == nullptr) { return; }
    // If del has no left child, replace it with its right child.
    if (del->leftChild == nullptr) {
        if (del == rt) {
            rt = del->rightChild;
        } else {
            if (delParent->leftChild == del) {
                delParent->leftChild = del->rightChild;
            } else {
                delParent->rightChild = del->rightChild;
            }
        }
        delete del;
        return;
    }
    // If del has right subtree, move it to the right subtree of the maximum node in del's left subtree.
    if (del->rightChild != nullptr) {
        Node* maxNode = del->leftChild;
        // Find the minimum node in the right subtree.
        while (maxNode->rightChild != nullptr) {
            maxNode = maxNode->rightChild;
        }
        maxNode->rightChild = del->rightChild;
    }
    if (del == rt) {
        rt = del->leftChild;
    } else {
        if (delParent->leftChild == del) {
            delParent->leftChild = del->leftChild;
        } else {
            delParent->rightChild = del->leftChild;
        }
    }
    delete del;
}

template<class K, class E>
void BinarySearchTree<K, E>::preOrder(Node* r) {
    if (r == nullptr) { return; }
    preOrder(r->leftChild);
    visit(r);
    preOrder(r->rightChild);
}

template<class K, class E>
void BinarySearchTree<K, E>::inOrder(Node* r) {
    if (r == nullptr) { return; }
    inOrder(r->leftChild);
    visit(r);
    inOrder(r->rightChild);
}

template<class K, class E>
void BinarySearchTree<K, E>::inOrder(Node* r, std::vector<Node*>& nodePtrVec) {
    if (r == nullptr) { return; }
    inOrder(r->leftChild, nodePtrVec);
    nodePtrVec.push_back(r);
    inOrder(r->rightChild, nodePtrVec);
}

template<class K, class E>
void BinarySearchTree<K, E>::postOrder(Node* r) {
    if (r == nullptr) { return; }
    inOrder(r->leftChild);
    inOrder(r->rightChild);
    visit(r);
}

template<class K, class E>
void BinarySearchTree<K, E>::outputTree(Node* r, std::ostream& out) {
    if (r == nullptr) { return; }
    // Get the width of the tree.
    std::vector<Node*> ptrs;
    inOrder(r, ptrs);
    std::ostringstream ss;  // For type conversion.
    std::unordered_map<Node*, indext> pos; // Position of each node.
    for (const auto& p : ptrs) {
        pos[p] = ss.str().size();
        ss << p->data.first << ": " << p->data.second << " ";
    }
    sizet width = ss.str().size();
    ss.str("");
    // Levelorder traversal to print the tree.
    std::queue<Node*> q;
    q.push(r);
    while (!q.empty()) {
        std::string firstLine(width, ' ');
        std::string secondLine(width, ' ');
        // Traverse the current level.
        sizet curLevelSize = q.size();
        for (indext i = 0; i < curLevelSize; ++i) {
            Node* curNodePtr = q.front();
            q.pop();
            indext elemPos = pos[curNodePtr];
            // If the node has a left child, connect them with '\' on the second line and '_'s on the first line.
            if (curNodePtr->leftChild) {
                q.push(curNodePtr->leftChild);
                indext slashPos = pos[curNodePtr->leftChild] + 1;
                secondLine[slashPos] = '/';
                for (indext j = slashPos + 1; j < elemPos; j++) {
                    firstLine[j] = '_';
                }
            }
            // Print the element on the first line.
            ss << curNodePtr->data.first << ": " << curNodePtr->data.second;
            std::string elemStr = ss.str();
            ss.str("");
            for (indext j = 0; j < elemStr.size(); ++j, ++elemPos) {
                firstLine[elemPos] = elemStr[j];
            }
            // If the node has a right child, connect them with '\' on the second line and '_'s on the first line.
            if (curNodePtr->rightChild) {
                q.push(curNodePtr->rightChild);
                indext backSlashPos = pos[curNodePtr->rightChild] - 1;
                secondLine[backSlashPos] = '\\';
                for (indext j = backSlashPos - 1; j > elemPos; j--) {
                    firstLine[j] = '_';
                }
            }
        }
        // Print the current level.
        out << firstLine << "\n"
            << secondLine << std::endl;
    }
}
