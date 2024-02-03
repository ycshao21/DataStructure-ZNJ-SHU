#pragma once
#include <queue>
#include <unordered_map>
#include <ranges>
#include <format>

namespace MyDS
{
    template<class T>
    struct BinaryTreeNode
    {
        T element;
        BinaryTreeNode<T>* leftChild = nullptr;
        BinaryTreeNode<T>* rightChild = nullptr;
    };

    template<class T>
    class BinaryTree
    {
    public:
        // @brief Construct an empty binary tree.
        BinaryTree()
            :m_Root(nullptr), m_Size(0)
        {
        }
        /**
         * @brief Copy constructor.
         * @param tree Another tree to be copied.
        */
        BinaryTree(const BinaryTree<T>& tree)
            : m_Root(_CopyTree(tree.m_Root)), m_Size(tree.m_Size)
        {
        }
        /**
         * @brief Copy assignment.
         * @param tree Another tree to be copied.
        */
        BinaryTree<T>& operator=(const BinaryTree<T>& tree);
        // @brief Destructor.
        ~BinaryTree() { Clear(); }

        // @brief Return if the tree is empty.
        bool IsEmpty() const { return m_Size == 0; }
        // @brief Get the number of elements in the tree.
        int GetSize() const { return m_Size; }
        // @brief Get the height of the tree.
        int GetHeight() const { return _GetHeight(m_Root); }
        // @brief Get the pointer to the root element.
        T* GetRootElement() const { return m_Root ? &m_Root->element : nullptr; }

        /**
         * @brief Combine two subtrees and an element to make a new tree.
         * @param element Parent of the two subtrees.
         * @param left Left subtree.
         * @param right Right subtree.
        */
        void MakeTree(const T& element, const BinaryTree<T>& left, const BinaryTree<T>& right);
        // @brief Swap all the left and right children in the tree.
        void Revolute() { _Revolute(m_Root); }
        // @brief Remove all the elements in the tree.
        void Clear();

        /**
         * @brief Traverse the tree in preorder.
         * @param v A function to be called on each node.
        */
        void PreOrder(void (*visit)(BinaryTreeNode<T>*)) { s_Visit = visit; _PreOrder(m_Root); }
        /**
         * @brief Traverse the tree in inorder.
         * @param v A function to be called on each node.
        */
        void InOrder(void (*visit)(BinaryTreeNode<T>*)) { s_Visit = visit; _InOrder(m_Root); }
        /**
         * @brief Traverse the tree in postorder.
         * @param v A function to be called on each node.
        */
        void PostOrder(void (*v)(BinaryTreeNode<T>*)) { s_Visit = v; _PostOrder(m_Root); }
        /**
         * @brief Traverse the tree in levelorder.
         * @param v A function to be called on each node.
        */
        void LevelOrder(void (*v)(BinaryTreeNode<T>*)) { s_Visit = v; _LevelOrder(m_Root); }
        void Output(std::ostream& out) const { _Output(m_Root, out); }
    private:
        /**
         * @brief Get the height of a binary tree.
         * @param r Root of the tree.
        */
        static int _GetHeight(BinaryTreeNode<T>* r);
        /**
         * @brief Copy all the nodes in a tree.
         * @param r Root of the tree.
        */
        BinaryTreeNode<T>* _CopyTree(BinaryTreeNode<T>* r);
        /**
         * @brief Swap all the left and right children in a tree.
         * @param r Root of the tree.
        */
        static void _Revolute(BinaryTreeNode<T>* r);

        /**
         * @brief Traverse the tree in preorder.
         * @param r Root of the tree.
        */
        static void _PreOrder(BinaryTreeNode<T>* r);
        /**
         * @brief Traverse the tree in inorder.
         * @param r Root of the tree.
        */
        static void _InOrder(BinaryTreeNode<T>* r);
        /**
         * @brief Traverse the tree and get the inorder sequence (for output function).
         * @param r Root of the tree.
        */
        static void _InOrder(BinaryTreeNode<T>* r, std::vector<BinaryTreeNode<T>*>& nodePtrVec);
        /**
         * @brief Traverse the tree in postorder.
         * @param r Root of the tree.
        */
        static void _PostOrder(BinaryTreeNode<T>* r);
        /**
         * @brief Traverse the tree in levelorder.
         * @param r Root of the tree.
        */
        static void _LevelOrder(BinaryTreeNode<T>* r);
        /**
         * @brief Print the tree vertically.
         * @param r Root of the tree.
         * @param out Output stream.
        */
        static void _Output(BinaryTreeNode<T>* r, std::ostream& out = std::cout);
        /**
         * @brief Remove the node.
         * @param node The node to be removed.
        */
        static void Dispose(BinaryTreeNode<T>* node) { delete node; }
    private:
        BinaryTreeNode<T>* m_Root = nullptr;  // Pointer to the root.
        int m_Size = 0;  // Number of elements.

        static void (*s_Visit)(BinaryTreeNode<T>*);  // Function to be called on each node.
    };

    template<class T>
    void (*BinaryTree<T>::s_Visit)(BinaryTreeNode<T>*) = nullptr;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Implementation of public member functions.
    ////////////////////////////////////////////////////////////////////////////////////////////////

    template<class T>
    BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& tree)
    {
        if (this != &tree)
        {
            m_Root = _CopyTree(tree.m_Root);
            m_Size = tree.m_Size;
        }
        return *this;
    }

    template<class T>
    void BinaryTree<T>::MakeTree(const T& element, const BinaryTree<T>& left, const BinaryTree<T>& right)
    {
        Clear();
        m_Root = new BinaryTreeNode<T>{ element, _CopyTree(left.m_Root), _CopyTree(right.m_Root) };
        m_Size = left.m_Size + right.m_Size + 1;
    }

    template<class T>
    void BinaryTree<T>::Clear()
    {
        PostOrder(Dispose);
        m_Root = nullptr;
        m_Size = 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Implementation of private member functions.
    ////////////////////////////////////////////////////////////////////////////////////////////////

    template<class T>
    int BinaryTree<T>::_GetHeight(BinaryTreeNode<T>* r)
    {
        if (!r)
            return 0;
        return 1 + std::max(_GetHeight(r->leftChild), _GetHeight(r->rightChild));
    }

    template<class T>
    BinaryTreeNode<T>* BinaryTree<T>::_CopyTree(BinaryTreeNode<T>* r)
    {
        if (!r)
            return nullptr;
        return new BinaryTreeNode<T>{ r->element, _CopyTree(r->leftChild), _CopyTree(r->rightChild) };
    }

    template<class T>
    void BinaryTree<T>::_Revolute(BinaryTreeNode<T>* r)
    {
        if (!r)
            return;

        // Swap the left and right children.
        BinaryTreeNode<T>* temp = r->leftChild;
        r->leftChild = r->rightChild;
        r->rightChild = temp;

        // Revolute the left and right subtrees.
        _Revolute(r->leftChild);
        _Revolute(r->rightChild);
    }

    template<class T>
    void BinaryTree<T>::_PreOrder(BinaryTreeNode<T>* r)
    {
        if (!r)
            return;

        s_Visit(r);
        _PreOrder(r->leftChild);
        _PreOrder(r->rightChild);
    }

    template<class T>
    void BinaryTree<T>::_InOrder(BinaryTreeNode<T>* r)
    {
        if (!r)
            return;

        _InOrder(r->leftChild);
        s_Visit(r);
        _InOrder(r->rightChild);
    }

    template<class T>
    void BinaryTree<T>::_InOrder(BinaryTreeNode<T>* r, std::vector<BinaryTreeNode<T>*>& nodePtrVec)
    {
        if (!r)
            return;

        _InOrder(r->leftChild, nodePtrVec);
        nodePtrVec.push_back(r);
        _InOrder(r->rightChild, nodePtrVec);
    }

    template<class T>
    void BinaryTree<T>::_PostOrder(BinaryTreeNode<T>* r)
    {
        if (!r)
            return;

        _PostOrder(r->leftChild);
        _PostOrder(r->rightChild);
        s_Visit(r);
    }

    template<class T>
    void BinaryTree<T>::_LevelOrder(BinaryTreeNode<T>* r)
    {
        std::queue<BinaryTreeNode<T>*> q;
        while (r)
        {
            s_Visit(r);
            if (r->leftChild)
                q.push(r->leftChild);
            if (r->rightChild)
                q.push(r->rightChild);

            if (q.empty())
                return;
            r = q.front();
            q.pop();
        }
    }

    template<class T>
    void BinaryTree<T>::_Output(BinaryTreeNode<T>* r, std::ostream& out)
    {
        if (!r)
            return;

        // Get the width of the tree.
        std::vector<BinaryTreeNode<T>*> ptrs;
        _InOrder(r, ptrs);

        std::string widthStr;
        std::unordered_map<BinaryTreeNode<T>*, int> pos; // Position of each node.
        for (auto& p : ptrs)
        {
            pos[p] = (int)widthStr.size();  // Record the position of the node.
            widthStr += std::format("{} ", p->element);  // Convert the element to string and append it to the result.
        }
        int width = (int)widthStr.size();

        // Levelorder traversal to print the tree.
        std::queue<BinaryTreeNode<T>*> q;
        q.push(r);
        while (!q.empty())
        {
            std::string firstLine(width, ' '), secondLine(width, ' ');
            // Traverse the current level.
            int curLevelSize = (int)q.size();
            for (int i = 0; i < curLevelSize; ++i)
            {
                BinaryTreeNode<T>* curNodePtr = q.front();
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
                std::string elemStr = std::format("{}", curNodePtr->element);
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

    // @brief Output the tree to the output stream.
    template<class T>
    std::ostream& operator<<(std::ostream& out, BinaryTree<T>& tree)
    {
        tree.Output(out);
        return out;
    }
}
