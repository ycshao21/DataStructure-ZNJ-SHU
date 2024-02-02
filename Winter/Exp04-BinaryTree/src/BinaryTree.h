#pragma once
#include<queue>
#include<unordered_map>
#include<ranges>
#include<sstream>

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
        BinaryTree() :rt(nullptr), treeSize(0) {}
        /**
         * @brief Copy constructor.
         * @param tree Another tree to be copied.
        */
        BinaryTree(const Tree& Tree) : rt(copyTree(Tree.rt)), treeSize(Tree.treeSize) {}
        // @brief Destructor.
        ~BinaryTree() { clear(); }

        // @brief Check if the tree is empty.
        bool empty() const { return treeSize == 0; }
        // @brief Get the number of elements in the tree.
        int size() const { return treeSize; }
        // @brief Get the height of the tree.
        int height() const { return height(rt); }
        // @brief Get the pointer to the root element.
        T* root() const { return rt ? &rt->element : nullptr; }

        /**
         * @brief Combine two subtrees and an element to make a new tree.
         * @param element Parent of the two subtrees.
         * @param left Left subtree.
         * @param right Right subtree.
        */
        void makeTree(const T& element, const Tree& left, const Tree& right);
        // @brief Swap all the left and right children in the tree.
        void revolute() { revolute(rt); }
        // @brief Remove all the elements in the tree.
        void clear();

        /**
         * @brief Traverse the tree in preorder.
         * @param v A function to be called on each node.
        */
        void preOrder(void (*v)(Node*)) { visit = v; preOrder(rt); }
        /**
         * @brief Traverse the tree in inorder.
         * @param v A function to be called on each node.
        */
        void inOrder(void (*v)(Node*)) { visit = v; inOrder(rt); }
        /**
         * @brief Traverse the tree in postorder.
         * @param v A function to be called on each node.
        */
        void postOrder(void (*v)(Node*)) { visit = v; postOrder(rt); }
        /**
         * @brief Traverse the tree in levelorder.
         * @param v A function to be called on each node.
        */
        void levelOrder(void (*v)(Node*)) { visit = v; levelOrder(rt); }
        void output(std::ostream& out) const { output(rt, out); }
    protected:
        BinaryTreeNode<T>* rt = nullptr;  // Pointer to the root.
        int treeSize = 0;  // Number of elements.

        static void (*visit)(BinaryTreeNode<T>*);  // Function to be called on each node.
        /**
         * @brief Get the height of a binary tree.
         * @param r Root of the tree.
        */
        static int height(BinaryTreeNode<T>* r);
        /**
         * @brief Copy all the nodes in a tree.
         * @param r Root of the tree.
        */
        BinaryTreeNode<T>* copyTree(BinaryTreeNode<T>* r);
        /**
         * @brief Swap all the left and right children in a tree.
         * @param r Root of the tree.
        */
        static void revolute(BinaryTreeNode<T>* r);

        /**
         * @brief Traverse the tree in preorder.
         * @param r Root of the tree.
        */
        static void preOrder(BinaryTreeNode<T>* r);
        /**
         * @brief Traverse the tree in inorder.
         * @param r Root of the tree.
        */
        static void inOrder(BinaryTreeNode<T>* r);
        /**
         * @brief Traverse the tree and get the inorder sequence (for output function).
         * @param r Root of the tree.
        */
        static void inOrder(BinaryTreeNode<T>* r, std::vector<BinaryTreeNode<T>*>& nodePtrVec);
        /**
         * @brief Traverse the tree in postorder.
         * @param r Root of the tree.
        */
        static void postOrder(BinaryTreeNode<T>* r);
        /**
         * @brief Traverse the tree in levelorder.
         * @param r Root of the tree.
        */
        static void levelOrder(BinaryTreeNode<T>* r);
        /**
         * @brief Remove the node.
         * @param node The node to be removed.
        */
        static void dispose(Node* node) { delete node; }
        /**
         * @brief Print the tree vertically.
         * @param r Root of the tree.
         * @param out Output stream.
        */
        static void output(BinaryTreeNode<T>* r, std::ostream& out = std::cout);
    };

    template<class T>
    void (*BinaryTree<T>::visit)(Node*) = nullptr;

    /*** public methods ***/

    template<class T>
    auto BinaryTree<T>::operator=(const Tree& tree) -> Tree& {
        if (this != &tree) {
            rt = copyTree(tree.rt);
            treeSize = tree.treeSize;
        }
        return *this;
    }

    template<class T>
    void BinaryTree<T>::makeTree(const T& element, const Tree& left, const Tree& right) {
        clear();
        rt = new Node{ element, copyTree(left.rt), copyTree(right.rt) };
        treeSize = left.treeSize + right.treeSize + 1;
    }

    template<class T>
    void BinaryTree<T>::clear() {
        postOrder(dispose);
        rt = nullptr;
        treeSize = 0;
    }

    /*** protected methods ***/

    template<class T>
    auto BinaryTree<T>::height(Node* r) -> sizet {
        if (!r) { return 0; }
        return 1 + std::max(height(r->leftChild), height(r->rightChild));
    }

    template<class T>
    auto BinaryTree<T>::copyTree(Node* r) -> Node* {
        if (!r) { return nullptr; }
        Node* lChild = copyTree(r->leftChild);
        Node* rChild = copyTree(r->rightChild);
        Node* root = new Node{ r->element, lChild, rChild };
        return root;
    }

    template<class T>
    void BinaryTree<T>::revolute(Node* r) {
        if (!r) { return; }
        Node* temp = r->leftChild;
        r->leftChild = r->rightChild;
        r->rightChild = temp;
        revolute(r->leftChild);
        revolute(r->rightChild);
    }

    template<class T>
    void BinaryTree<T>::preOrder(Node* r) {
        if (!r) { return; }
        visit(r);
        preOrder(r->leftChild);
        preOrder(r->rightChild);
    }

    template<class T>
    void BinaryTree<T>::inOrder(Node* r) {
        if (!r) { return; }
        inOrder(r->leftChild);
        visit(r);
        inOrder(r->rightChild);
    }

    template<class T>
    void BinaryTree<T>::inOrder(Node* r, std::vector<Node*>& nodePtrVec) {
        if (!r) { return; }
        inOrder(r->leftChild, nodePtrVec);
        nodePtrVec.push_back(r);
        inOrder(r->rightChild, nodePtrVec);
    }

    template<class T>
    void BinaryTree<T>::postOrder(Node* r) {
        if (!r) { return; }
        postOrder(r->leftChild);
        postOrder(r->rightChild);
        visit(r);
    }

    template<class T>
    void BinaryTree<T>::levelOrder(Node* r) {
        std::queue<Node*> q;
        while (r) {
            visit(r);
            if (r->leftChild) { q.push(r->leftChild); }
            if (r->rightChild) { q.push(r->rightChild); }
            if (q.empty()) { return; }
            r = q.front();
            q.pop();
        }
    }

    template<class T>
    void BinaryTree<T>::output(Node* r, std::ostream& out) {
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

    // @brief Output the tree to the output stream.
    template<class T>
    std::ostream& operator<<(std::ostream& out, BinaryTree<T>& tree) {
        tree.output(out);
        return out;
    }
}
