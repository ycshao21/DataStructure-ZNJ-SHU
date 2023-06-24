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

    void inOrder(void (*v)(Node*)) { visit = v; inOrder(rt); }

    /* Others */

    void outputElements(std::ostream& out = std::cout) const { inOrder(print); }
    void outputTree(std::ostream& out = std::cout) const { outputTree(rt, out); }
private:
    Node* rt;
    sizet treeSize;
    static void (*visit)(Node*);

    Node* copyTree(Node* r);
    static sizet height(Node* r);
    static void inOrder(Node* r);
    static void inOrder(Node* r, std::vector<Node*>& nodePtrVec);  // For outputTree function.
    static void postOrder(Node* r);
    static void outputTree(Node* r, std::ostream& out = std::cout);
    static void print(Node* r) { std::cout << r->data.second << " "; }
    static void dispose(Node* node) { delete node; }
};

template<class K, class E>
static void (*BinarySearchTree<K, E>::visit)(Node*) = nullptr;

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
    if (rt != nullptr) {
        if (key < parent->data.first) {
            parent->leftChild = cur;
        } else {
            parent->rightChild = cur;
        }
    }
    treeSize++;
}

//template<class K, class E>
//bool BinarySearchTree<K, E>::EraseR_lr(const K& key) {
//    if (rt == nullptr) {
//        throw(MyException("Erase empty tree!"));
//    }
//    return _EraseR_lr(rt, key);
//}
//
//template<class K, class E>
//bool BinarySearchTree<K, E>::EraseR_ll(const K& key) {
//    if (rt == nullptr) {
//        throw(MyException("Erase empty tree!"));
//    }
//    return _EraseR_ll(rt, key);
//}

//template<class K, class E>
//bool BinarySearchTree<K, E>::Erase_lr(const K& key) {
//    if (rt == nullptr) throw(MyException("Erase empty tree!"));
//    Node* cur = rt;
//    Node* parent = nullptr;
//    while (cur) {
//        if (cur->_key > key) {
//            parent = cur;
//            cur = cur->leftChild;
//        } else if (cur->_key < key) {
//            parent = cur;
//            cur = cur->rightChild;
//        } else {
//            if (cur->leftChild == nullptr)
//            {
//                if (cur == rt) {
//                    rt = cur->rightChild;
//                } else {
//                    if (parent->leftChild == cur) {
//                        parent->leftChild = cur->rightChild;
//                    } else {
//                        parent->rightChild = cur->rightChild;
//                    }
//                }
//                delete cur;
//            } else if (cur->rightChild == nullptr)
//            {
//                if (cur == rt) {
//                    rt = cur->leftChild;
//                } else {
//                    if (parent->leftChild == cur) {
//                        parent->leftChild = cur->leftChild;
//                    } else {
//                        parent->rightChild = cur->leftChild;
//                    }
//                }
//                delete cur;
//            } else {
//                Node* child = cur->leftChild;
//                parent = cur;
//                while (child->rightChild)//寻找左子树的最大节点
//                {
//                    parent = child;
//                    child = child->rightChild;
//                }
//                cur->_key = child->_key;
//                cur->_value = child->_value;
//                //删除child
//                if (parent->leftChild == child) {
//                    parent->leftChild = child->leftChild;
//                } else {
//                    parent->rightChild = child->leftChild;
//                }
//                delete child;
//            }
//            return true;
//        }
//    }
//    return false;
//}
//
//template<class K, class E>
//bool BinarySearchTree<K, E>::Erase_rl(const K& key) {
//    if (rt == nullptr) throw(MyException("Erase empty tree!"));
//    Node* cur = rt;
//    Node* parent = nullptr;
//    while (cur) {
//        if (cur->_key > key) {
//            parent = cur;
//            cur = cur->leftChild;
//        } else if (cur->_key < key) {
//            parent = cur;
//            cur = cur->rightChild;
//        } else {
//            if (cur->leftChild == nullptr)
//            {
//                if (cur == rt) {
//                    rt = cur->rightChild;
//                } else {
//                    if (parent->leftChild == cur) {
//                        parent->leftChild = cur->rightChild;
//                    } else {
//                        parent->rightChild = cur->rightChild;
//                    }
//                }
//                delete cur;
//            } else if (cur->rightChild == nullptr)
//            {
//                if (cur == rt) {
//                    rt = cur->leftChild;
//                } else {
//                    if (parent->leftChild == cur) {
//                        parent->leftChild = cur->leftChild;
//                    } else {
//                        parent->rightChild = cur->leftChild;
//                    }
//                }
//                delete cur;
//            } else
//            {
//                Node* child = cur->rightChild;
//                parent = cur;
//                while (child->leftChild)
//                {
//                    parent = child;
//                    child = child->leftChild;
//                }
//                cur->_key = child->_key;
//                cur->_value = child->_value;
//                //删除child
//                if (parent->leftChild == child) {
//                    parent->leftChild = child->leftChild;
//                } else {
//                    parent->rightChild = child->leftChild;
//                }
//                delete child;
//            }
//            return true;
//        }
//    }
//    return false;
//}
//
//template<class K, class E>
//bool BinarySearchTree<K, E>::Erase_ll(const K& key) {
//    if (rt == nullptr) throw(MyException("Erase empty tree!"));
//    Node* cur = rt;
//    Node* parent = nullptr;
//    while (cur) {
//        if (cur->_key > key) {
//            parent = cur;
//            cur = cur->leftChild;
//        } else if (cur->_key < key) {
//            parent = cur;
//            cur = cur->rightChild;
//        } else {
//            if (cur->leftChild == nullptr)
//            {
//                if (cur == rt) {
//                    rt = cur->rightChild;
//                } else {
//                    if (parent->leftChild == cur) {
//                        parent->leftChild = cur->rightChild;
//                    } else {
//                        parent->rightChild = cur->rightChild;
//                    }
//                }
//                delete cur;
//            } else if (cur->rightChild == nullptr)
//            {
//                if (cur == rt) {
//                    rt = cur->leftChild;
//                } else {
//                    if (parent->leftChild == cur) {
//                        parent->leftChild = cur->leftChild;
//                    } else {
//                        parent->rightChild = cur->leftChild;
//                    }
//                }
//                delete cur;
//            } else
//            {
//                Node* child = cur->rightChild;
//                while (child->leftChild)
//                {
//                    child = child->leftChild;
//                }
//                child->leftChild = cur->leftChild;
//                if (cur == rt) {
//                    rt = cur->rightChild;
//                } else if (parent->leftChild == cur) {
//                    parent->leftChild = cur->rightChild;
//                } else {
//                    parent->rightChild = cur->rightChild;
//                }
//                delete cur;
//            }
//            return true;
//        }
//    }
//    return false;
//}
//
//template<class K, class E>
//bool BinarySearchTree<K, E>::Erase_rr(const K& key) {
//    if (rt == nullptr) throw(MyException("Erase empty tree!"));
//    Node* cur = rt;
//    Node* parent = nullptr;
//    while (cur) {
//        if (cur->_key > key) {
//            parent = cur;
//            cur = cur->leftChild;
//        } else if (cur->_key < key) {
//            parent = cur;
//            cur = cur->rightChild;
//        } else {
//            if (cur->leftChild == nullptr)
//            {
//                if (cur == rt) {
//                    rt = cur->rightChild;
//                } else {
//                    if (parent->leftChild == cur) {
//                        parent->leftChild = cur->rightChild;
//                    } else {
//                        parent->rightChild = cur->rightChild;
//                    }
//                }
//                delete cur;
//            } else if (cur->rightChild == nullptr)
//            {
//                if (cur == rt) {
//                    rt = cur->leftChild;
//                } else {
//                    if (parent->leftChild == cur) {
//                        parent->leftChild = cur->leftChild;
//                    } else {
//                        parent->rightChild = cur->leftChild;
//                    }
//                }
//                delete cur;
//            } else
//            {
//                Node* child = cur->leftChild;
//                while (child->rightChild)//寻找左子树的最大节点
//                {
//                    child = child->rightChild;
//                }
//                child->rightChild = cur->rightChild;
//                if (cur == rt) {
//                    rt = cur->leftChild;
//                } else if (parent->leftChild == cur) {
//                    parent->leftChild = cur->leftChild;
//                } else {
//                    parent->rightChild = cur->leftChild;
//                }
//                delete cur;
//            }
//            return true;
//        }
//    }
//    return false;
//}

//
//template<class K, class E>
//bool BinarySearchTree<K, E>::_EraseR_lr(Node*& rt, const K& key) {
//    if (rt == nullptr) return false;
//    if (rt->_key < key) {
//        _EraseR(rt->rightChild, key);
//    } else if (rt->_key > key) {
//        _EraseR(rt->leftChild, key);
//    } else {
//        if (rt->leftChild == nullptr) {
//            Node* del = rt;
//            rt = rt->rightChild;
//            delete del;
//        } else if (rt->rightChild == nullptr) {
//            Node* del = rt;
//            rt = rt->leftChild;
//            delete del;
//        } else {
//            Node* child = rt->leftChild;
//            while (child->rightChild) {
//                child = child->rightChild;
//            }
//            K keymax = child->_key;
//            E valuemax = child->_value;
//            _EraseR(rt->leftChild, keymax);
//            rt->_key = keymax;
//            rt->_value = valuemax;
//        }
//        return true;
//    }
//}
//
//template<class K, class E>
//bool BinarySearchTree<K, E>::_EraseR_ll(Node*& rt, const K& key) {
//    if (rt == nullptr) return false;
//    if (rt->_key < key) {
//        _EraseR1(rt->rightChild, key);
//    } else if (rt->_key > key) {
//        _EraseR1(rt->leftChild, key);
//    } else {
//        if (rt->leftChild == nullptr) {
//            Node* del = rt;
//            rt = rt->rightChild;
//            delete del;
//        } else if (rt->rightChild == nullptr) {
//            Node* del = rt;
//            rt = rt->leftChild;
//            delete del;
//        } else {
//            Node* child = rt->rightChild;
//            while (child->leftChild) {
//                child = child->leftChild;
//            }
//            child->leftChild = rt->leftChild;
//            Node* del = rt;
//            rt = rt->rightChild;
//            delete del;
//        }
//        return true;
//    }
//}

template<class K, class E>
void BinarySearchTree<K, E>::inOrder(Node* r) {
    if (r == nullptr) { return; }
    inOrder(r->leftChild, v);
    visit(r);
    inOrder(r->rightChild, v);
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
    inOrder(r->leftChild, v);
    inOrder(r->rightChild, v);
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
    for (auto& p : ptrs) {
        pos[p] = ss.str().size();
        ss << p->element << " ";
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
            ss << curNodePtr->element;
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
