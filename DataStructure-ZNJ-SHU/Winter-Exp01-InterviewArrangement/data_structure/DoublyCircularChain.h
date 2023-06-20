#pragma once
#include<iostream>
#include<unordered_set>
#include"../../Tools/MyExceptions.h"

template<class _Ty>
struct DoublyCircularChainNode
{
    _Ty data;
    DoublyCircularChainNode<_Ty>* prior = nullptr;
    DoublyCircularChainNode<_Ty>* next = nullptr;
};

template<class _Ty>
class DoublyCircularChain
{
    using Chain = DoublyCircularChain<_Ty>;
    using Node = DoublyCircularChainNode<_Ty>;
    using sizet = size_t;
    using indext = size_t;
public:
    // @brief Construct a doubly circular chain with no element.
    DoublyCircularChain() : firstNode(nullptr), listSize(0) {}
    /**
     * @brief Copy constructor.
     * @param list Another doubly circular chain.
    */
    DoublyCircularChain(const Chain& theChain);
    // @brief Destructor.
    ~DoublyCircularChain();

    // @brief Check if the chain is empty.
    bool empty() const { return listSize == 0; }
    // @brief Get the number of elements in the chain.
    sizet size() const { return listSize; }

    // @brief Get the pointer to the first node (non-const version).
    Node* begin() { return firstNode; }  //
    // @brief Get the pointer to the first node (const version).
    const Node* begin() const { return firstNode; }
    /**
     * @brief Erase the given node from the chain if it exists.
     * @param node The node to be erased.
    */
    void erase(Node*& Node);
    /**
     * @brief Insert a node at the end of the chain.
     * @param element The element to be inserted.
    */
    void push_back(const _Ty& element);
    // @brief Clear the chain.
    void clear();

    /**
     * @brief Output every element in the chain to the given output stream.
     * @param out The output stream.
    */
    void output(std::ostream& out) const;
    /**
     * @brief Check if the chain is equal to another chain.
     * @param right Another chain.
    */
    bool operator==(const Chain& right) const;
    /**
     * @brief Check if the chain is unequal to another chain.
     * @param right Another chain.
    */
    bool operator!=(const Chain& right) const { return !(*this == right); }
protected:
    // @brief Check if the index is legal.
    void checkIndex(indext to) const {
        if (to >= listSize) {
            throw IllegalIndex("Illegal Index!");
        }
    }
    // @brief Check if the list contains the node.
    void checkNode(Node*& Node) const {
        if (nodePtrs.find(Node) == nodePtrs.end()) {
            throw IllegalParameterValue("Node not exists!");
        }
    }

    sizet listSize = 0;  // Size of the chain.
    Node* firstNode = nullptr;  // Pointer to the first node.
    std::unordered_set<Node*> nodePtrs;  // For checking the existence of a node.
};

template<class _Ty>
DoublyCircularChain<_Ty>::DoublyCircularChain(const Chain& theChain)
    :listSize(theChain.listSize), firstNode(nullptr) {
    if (theChain.listSize == 0) { return; }

    // Copy the first node.
    firstNode = new Node{ theChain.firstNode->data };
    nodePtrs.emplace(firstNode);
    Node* srcNode = theChain.firstNode->next;
    Node* curNode = firstNode;

    // Copy the rest nodes
    while (srcNode != theChain.firstNode) {
        curNode->next = new Node{ srcNode->data, curNode };
        curNode = curNode->next;
        srcNode = srcNode->next;
        nodePtrs.emplace(curNode);
    }
    curNode->next = firstNode;
    firstNode->prior = curNode;
}

template<class _Ty>
DoublyCircularChain<_Ty>::~DoublyCircularChain() {
    if (firstNode == nullptr) { return; }
    Node* endNode = firstNode->prior;
    while (firstNode != endNode) {
        Node* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
    delete firstNode;
}

template<class _Ty>
void DoublyCircularChain<_Ty>::erase(Node*& node) {
    // Check if the node exists.
    checkNode(node);
    // Erase the first node if the chain has only one node
    // (since the node to be erased must be the only one in the chain).
    if (listSize == 1) {
        delete firstNode;
        firstNode = nullptr;
        listSize = 0;
        nodePtrs.clear();
        return;
    }
    // Erase the node in a regular way.
    if (node == firstNode) { firstNode = firstNode->next; }
    node->prior->next = node->next;
    node->next->prior = node->prior;
    nodePtrs.erase(nodePtrs.find(node));
    delete node;
    --listSize;
}

template<class _Ty>
void DoublyCircularChain<_Ty>::push_back(const _Ty& element) {
    // Make element the first node if the chain is empty.
    if (listSize == 0) {
        firstNode = new Node{ element };
        firstNode->prior = firstNode;
        firstNode->next = firstNode;
        nodePtrs.emplace(firstNode);
        ++listSize;
        return;
    }
    // Insert the node at the end of the chain.
    Node* insertNode = new Node{ element, firstNode->prior, firstNode };
    firstNode->prior->next = insertNode;
    firstNode->prior = insertNode;
    nodePtrs.emplace(insertNode);
    ++listSize;
}

template<class _Ty>
void DoublyCircularChain<_Ty>::clear() {
    listSize = 0;
    nodePtrs.clear();
    if (firstNode == nullptr) { return; }
    Node* endNode = firstNode->prior;
    while (firstNode != endNode) {
        Node* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
    delete firstNode;
    firstNode = nullptr;
}

template<class _Ty>
void DoublyCircularChain<_Ty>::output(std::ostream& out) const {
    if (listSize == 0) { return; }
    out << firstNode->data << " ";
    for (Node* curNode = firstNode->next; curNode != firstNode; curNode = curNode->next) {
        out << curNode->data << " ";
    }
}

// @brief Output every element in the chain to the given output stream.
template<class _Ty>
std::ostream& operator<<(std::ostream& out, const DoublyCircularChain<_Ty>& chain) {
    chain.output(out);
    return out;
}

template<class _Ty>
bool DoublyCircularChain<_Ty>::operator==(const Chain& right) const {
    if (listSize != right.listSize) { return false; }
    Node* l_curNode = firstNode;
    Node* r_curNode = right.firstNode;
    for (indext i = 0; i < listSize; ++i) {
        if (l_curNode->data != r_curNode->data) { return false; }
        l_curNode = l_curNode->next;
        r_curNode = r_curNode->next;
    }
    return true;
}