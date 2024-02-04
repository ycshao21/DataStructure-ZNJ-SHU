#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <iomanip>
#include "BinarySearchTreeNode.h"

namespace MyDS
{
    template<class K, class E>
    class BinarySearchTree
    {
        using Node = BinarySearchTreeNode<K, E>;
        using Pair = std::pair<K, E>;
    public:
        BinarySearchTree() : m_Root(nullptr), m_Size(0) {}
        BinarySearchTree(const BinarySearchTree<K, E>& tree) :m_Root(_CopyTree(tree.m_Root)), m_Size(tree.m_Size) {}
        BinarySearchTree(const std::vector<Pair>& pairs);
        ~BinarySearchTree() { this->Clear(); }

        bool IsEmpty() const { return m_Size == 0; }
        int GetSize() const { return m_Size; }
        int GetHeight() const { return _GetHeight(m_Root); }
        Pair* GetRootElement() const { return m_Root ? &m_Root->data : nullptr; }

        Pair* Find(const K& key) const;

        void Clear();
        void Insert(const K& key, const E& element);
        // Replace it with the maximum node in its left subtree.
        void Erase_Ver1(const K& key);
        // Replace it with the minimum node in its right subtree.
        void Erase_Ver2(const K& key);
        // Move its left subtree to the left subtree of the minimum node in its right subtree.
        void Erase_Ver3(const K& key);
        // Move its right subtree to the right subtree of the maximum node in its left subtree.
        void Erase_Ver4(const K& key);

        void PreOrder(void (*v)(Node*)) { s_Visit = v; _PreOrder(m_Root); }
        void InOrder(void (*v)(Node*)) { s_Visit = v; _InOrder(m_Root); }
        void PostOrder(void (*v)(Node*)) { s_Visit = v; _PostOrder(m_Root); }

        void PrintElements(std::ostream& out = std::cout) const { InOrder(Print); }
        void PrintKeyTree(std::ostream& out = std::cout) const { _PrintKeyTree(m_Root, out); }
    private:
        Node* _CopyTree(Node* r);
        static int _GetHeight(Node* r);
        static void _PreOrder(Node* r);
        static void _InOrder(Node* r);
        static void _InOrder(Node* r, std::vector<Node*>& nodePtrVec);  // For outputTree function.
        static void _PostOrder(Node* r);
        static void _PrintKeyTree(Node* r, std::ostream& out = std::cout);
        static void Print(Node* r) { std::cout << r->data.second << " "; }
        static void Dispose(Node* node) { delete node; }
    private:
        Node* m_Root;
        int m_Size;
        static void (*s_Visit)(Node*);
    };

    template<class K, class E>
    void (*BinarySearchTree<K, E>::s_Visit)(Node*) = nullptr;

    template<class K, class E>
    auto BinarySearchTree<K, E>::_GetHeight(Node* r) -> int
    {
        if (!r)
            return 0;
        return 1 + std::max(_GetHeight(r->leftChild), _GetHeight(r->rightChild));
    }

    template<class K, class E>
    auto BinarySearchTree<K, E>::_CopyTree(Node* r) -> Node*
    {
        if (!r)
            return nullptr;
        Node* lChild = _CopyTree(r->leftChild);
        Node* rChild = _CopyTree(r->rightChild);
        Node* root = new Node{ r->data, lChild, rChild };
        return root;
    }

    template<class K, class E>
    BinarySearchTree<K, E>::BinarySearchTree(const std::vector<Pair>& pairs)
    {
        m_Root = nullptr;
        m_Size = 0;
        for (const auto& pair : pairs)
            Insert(pair.first, pair.second);
    }

    template<class K, class E>
    auto BinarySearchTree<K, E>::Find(const K& key) const -> Pair*
    {
        Node* cur = m_Root;
        while (cur)
        {
            if (key < cur->data.first)
                cur = cur->leftChild;
            else if (key > cur->data.first)
                cur = cur->rightChild;
            else
                return &cur->data;
        }
        return nullptr;
    }

    template<class K, class E>
    void BinarySearchTree<K, E>::Clear()
    {
        PostOrder(Dispose);
        m_Root = nullptr;
        m_Size = 0;
    }

    template<class K, class E>
    void BinarySearchTree<K, E>::Insert(const K& key, const E& element)
    {
        Node* cur = m_Root;
        Node* parent = nullptr;
        while (cur)
        {
            parent = cur;
            // Move cur to one of its child.
            if (key < cur->data.first)
            {
                cur = cur->leftChild;
            }
            else if (key > cur->data.first)
            {
                cur = cur->rightChild;
            }
            else
            {
                // If the key is already in the tree, cover the old value.
                cur->data.second = element;
                return;
            }
        }

        // Create a new node.
        cur = new Node{ Pair{key, element} };
        if (!m_Root)
        {
            m_Root = cur;
        }
        else
        {
            if (key < parent->data.first)
                parent->leftChild = cur;
            else
                parent->rightChild = cur;
        }
        m_Size++;
    }

    template<class K, class E>
    void BinarySearchTree<K, E>::Erase_Ver1(const K& key)
    {
        Node* del = m_Root;
        Node* delParent = nullptr;

        // Find the node to delete.
        while (del && del->data.first != key)
        {
            delParent = del;
            if (key < del->data.first)
                del = del->leftChild;
            else
                del = del->rightChild;
        }
        // The key is not in the tree.
        if (!del)
            return;

        // If del has no left child, replace it with its right child.
        if (!del->leftChild)
        {
            if (del == m_Root)
            {
                m_Root = del->rightChild;
            }
            else
            {
                if (delParent->leftChild == del)
                    delParent->leftChild = del->rightChild;
                else
                    delParent->rightChild = del->rightChild;
            }
            delete del;
        }
        else
        {  // Otherwise, replace it with the maximum node in its left subtree.
            Node* maxNode = del->leftChild;
            Node* maxParent = del;
            // Find the maximum node in the left subtree.
            while (maxNode->rightChild)
            {
                maxParent = maxNode;
                maxNode = maxNode->rightChild;
            }
            del->data = std::move(maxNode->data);
            if (maxParent->leftChild == maxNode)
                maxParent->leftChild = maxNode->leftChild;
            else
                maxParent->rightChild = maxNode->leftChild;
            delete maxNode;
        }
        m_Size--;
    }

    template<class K, class E>
    void BinarySearchTree<K, E>::Erase_Ver2(const K& key)
    {
        Node* del = m_Root;
        Node* delParent = nullptr;
        // Find the node to delete.
        while (del && del->data.first != key)
        {
            delParent = del;
            if (key < del->data.first)
                del = del->leftChild;
            else
                del = del->rightChild;
        }
        // The key is not in the tree.
        if (!del)
            return;

        // If del has no right child, replace it with its left child.
        if (!del->rightChild)
        {
            if (del == m_Root)
            {
                m_Root = del->leftChild;
            }
            else
            {
                if (delParent->leftChild == del)
                    delParent->leftChild = del->leftChild;
                else
                    delParent->rightChild = del->leftChild;
            }
            delete del;
        }
        else
        {  // Otherwise, replace it with the minimum node in its right subtree.
            Node* minNode = del->rightChild;
            Node* minParent = del;
            // Find the minimum node in the right subtree.
            while (minNode->leftChild)
            {
                minParent = minNode;
                minNode = minNode->leftChild;
            }
            del->data = std::move(minNode->data);

            if (minParent->rightChild == minNode)
                minParent->rightChild = minNode->rightChild;
            else
                minParent->leftChild = minNode->rightChild;
            delete minNode;
        }
        m_Size--;
    }

    template<class K, class E>
    void BinarySearchTree<K, E>::Erase_Ver3(const K& key)
    {
        Node* del = m_Root;
        Node* delParent = nullptr;
        // Find the node to delete.
        while (del && del->data.first != key)
        {
            delParent = del;
            if (key < del->data.first)
                del = del->leftChild;
            else
                del = del->rightChild;
        }
        // The key is not in the tree.
        if (!del)
            return;

        // If del has no right child, replace it with its left child.
        if (!del->rightChild)
        {
            if (del == m_Root)
            {
                m_Root = del->leftChild;
            }
            else
            {
                if (delParent->leftChild == del)
                    delParent->leftChild = del->leftChild;
                else
                    delParent->rightChild = del->leftChild;
            }
            delete del;
            m_Size--;
            return;
        }
        // If del has left subtree, move it to the left subtree of the minimum node in del's right subtree.
        if (del->leftChild)
        {
            Node* minNode = del->rightChild;
            // Find the minimum node in the right subtree.
            while (minNode->leftChild)
            {
                minNode = minNode->leftChild;
            }
            minNode->leftChild = del->leftChild;
        }
        if (del == m_Root)
        {
            m_Root = del->rightChild;
        }
        else
        {
            if (delParent->leftChild == del)
                delParent->leftChild = del->rightChild;
            else
                delParent->rightChild = del->rightChild;
        }
        delete del;
        m_Size--;
    }

    template<class K, class E>
    void BinarySearchTree<K, E>::Erase_Ver4(const K& key)
    {
        Node* del = m_Root;
        Node* delParent = nullptr;
        // Find the node to delete.
        while (del && del->data.first != key)
        {
            delParent = del;
            if (key < del->data.first)
                del = del->leftChild;
            else
                del = del->rightChild;
        }
        // The key is not in the tree.
        if (!del)
            return;

        // If del has no left child, replace it with its right child.
        if (!del->leftChild)
        {
            if (del == m_Root)
            {
                m_Root = del->rightChild;
            }
            else
            {
                if (delParent->leftChild == del)
                    delParent->leftChild = del->rightChild;
                else
                    delParent->rightChild = del->rightChild;
            }
            delete del;
            m_Size--;
            return;
        }
        // If del has right subtree, move it to the right subtree of the maximum node in del's left subtree.
        if (del->rightChild)
        {
            Node* maxNode = del->leftChild;
            // Find the minimum node in the right subtree.
            while (maxNode->rightChild)
            {
                maxNode = maxNode->rightChild;
            }
            maxNode->rightChild = del->rightChild;
        }
        if (del == m_Root)
        {
            m_Root = del->leftChild;
        }
        else
        {
            if (delParent->leftChild == del)
                delParent->leftChild = del->leftChild;
            else
                delParent->rightChild = del->leftChild;
        }
        delete del;
        m_Size--;
    }

    template<class K, class E>
    void BinarySearchTree<K, E>::_PreOrder(Node* r)
    {
        if (!r)
            return;

        _PreOrder(r->leftChild);
        s_Visit(r);
        _PreOrder(r->rightChild);
    }

    template<class K, class E>
    void BinarySearchTree<K, E>::_InOrder(Node* r)
    {
        if (!r)
            return;

        inOrder(r->leftChild);
        s_Visit(r);
        inOrder(r->rightChild);
    }

    template<class K, class E>
    void BinarySearchTree<K, E>::_InOrder(Node* r, std::vector<Node*>& nodePtrVec)
    {
        if (!r)
            return;

        _InOrder(r->leftChild, nodePtrVec);
        nodePtrVec.push_back(r);
        _InOrder(r->rightChild, nodePtrVec);
    }

    template<class K, class E>
    void BinarySearchTree<K, E>::_PostOrder(Node* r)
    {
        if (!r)
            return;

        _PostOrder(r->leftChild);
        _PostOrder(r->rightChild);
        s_Visit(r);
    }

    template<class K, class E>
    void BinarySearchTree<K, E>::_PrintKeyTree(Node* r, std::ostream& out)
    {
        if (!r)
            return;

        // Get the width of the tree.
        std::vector<Node*> ptrs;
        _InOrder(r, ptrs);
        std::ostringstream ss;  // For type conversion.
        std::unordered_map<Node*, int> pos; // Position of each node.
        for (const auto& p : ptrs)
        {
            pos[p] = (int)ss.str().size();
            ss << p->data.first << " ";
        }
        int width = (int)ss.str().size();
        ss.str("");
        // Levelorder traversal to print the tree.
        std::queue<Node*> q;
        q.push(r);
        while (!q.empty())
        {
            std::string firstLine(width, ' ');
            std::string secondLine(width, ' ');
            // Traverse the current level.
            int curLevelSize = (int)q.size();
            for (int i = 0; i < curLevelSize; ++i)
            {
                Node* curNodePtr = q.front();
                q.pop();
                int elemPos = pos[curNodePtr];
                // If the node has a left child, connect them with '\' on the second line and '_'s on the first line.
                if (curNodePtr->leftChild)
                {
                    q.push(curNodePtr->leftChild);
                    int slashPos = pos[curNodePtr->leftChild] + 1;
                    secondLine[slashPos] = '/';
                    for (int j = slashPos + 1; j < elemPos; j++)
                        firstLine[j] = '_';
                }
                // Print the element on the first line.
                ss << curNodePtr->data.first;
                std::string elemStr = ss.str();
                ss.str("");
                for (int j = 0; j < elemStr.size(); ++j, ++elemPos)
                    firstLine[elemPos] = elemStr[j];

                // If the node has a right child, connect them with '\' on the second line and '_'s on the first line.
                if (curNodePtr->rightChild)
                {
                    q.push(curNodePtr->rightChild);
                    int backSlashPos = pos[curNodePtr->rightChild] - 1;
                    secondLine[backSlashPos] = '\\';
                    for (int j = backSlashPos - 1; j > elemPos; j--)
                        firstLine[j] = '_';
                }
            }
            // Print the current level.
            out << firstLine << "\n"
                << secondLine << std::endl;
        }
    }
}
