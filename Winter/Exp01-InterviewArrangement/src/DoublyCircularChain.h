#pragma once
#include <unordered_set>

namespace MyDS
{
    template <class T>
    struct DoublyCircularChainNode
    {
        T data;
        DoublyCircularChainNode<T>* prior = nullptr;
        DoublyCircularChainNode<T>* next = nullptr;
    };

    template <class T>
    class DoublyCircularChain
    {
    public:
        // @brief Construct a doubly circular chain with no element.
        DoublyCircularChain() = default;
        /**
         * @brief Copy constructor.
         * @param chain The chain to be copied.
        */
        DoublyCircularChain(const DoublyCircularChain<T>& chain);
        // @brief Destructor.
        ~DoublyCircularChain();

        // @brief Return if the chain is empty.
        bool IsEmpty() const { return m_Size == 0; }
        // @brief Get the number of elements in the chain.
        int GetSize() const { return m_Size; }

        // @brief Get the pointer to the first node (non-const version).
        DoublyCircularChainNode<T>* GetFirstNode() { return m_FirstNode; }
        // @brief Get the pointer to the first node (const version).
        const DoublyCircularChainNode<T>* GetFirstNode() const { return m_FirstNode; }
        /**
         * @brief Erase the given node from the chain if it exists.
         * @param node The node to be erased.
        */
        void EraseNode(DoublyCircularChainNode<T>*& node);
        /**
         * @brief Insert a node at the end of the chain.
         * @param element The element to be inserted.
        */
        void PushBack(const T& element);
        // @brief Clear the chain.
        void Clear();
    private:
        // @brief Check if {index} is legal.
        void CheckIndex(int index) const
        {
            if (index >= m_Size)
                throw "Illegal index!";
        }
        // @brief Check if the chain contains {node}.
        void CheckNode(DoublyCircularChainNode<T>*& node) const
        {
            if (m_NodePtrs.find(node) == m_NodePtrs.end())
                throw "Node not exists!";
        }

        int m_Size = 0;  // Size of the chain.
        DoublyCircularChainNode<T>* m_FirstNode = nullptr;  // Pointer to the first node.
        std::unordered_set<DoublyCircularChainNode<T>*> m_NodePtrs{};  // For checking the existence of a node.
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Implementation of member functions
    ////////////////////////////////////////////////////////////////////////////////////////////////

    template<class T>
    DoublyCircularChain<T>::DoublyCircularChain(const DoublyCircularChain<T>& chain)
        : m_Size(chain.m_Size), m_FirstNode(nullptr)
    {
        if (chain.m_Size == 0)
            return;

        // Copy the first node.
        m_FirstNode = new DoublyCircularChainNode<T>{ chain.m_FirstNode->data };
        m_NodePtrs.emplace(m_FirstNode);
        DoublyCircularChainNode<T>* srcNode = chain.m_FirstNode->next;
        DoublyCircularChainNode<T>* curNode = m_FirstNode;

        // Copy the rest nodes
        while (srcNode != chain.m_FirstNode)
        {
            curNode->next = new DoublyCircularChainNode<T>{ srcNode->data, curNode };
            curNode = curNode->next;
            srcNode = srcNode->next;
            m_NodePtrs.emplace(curNode);
        }

        curNode->next = m_FirstNode;
        m_FirstNode->prior = curNode;
    }

    template<class T>
    DoublyCircularChain<T>::~DoublyCircularChain()
    {
        if (m_FirstNode)
        {
            DoublyCircularChainNode<T>* lastNode = m_FirstNode->prior;
            while (m_FirstNode != lastNode)
            {
                DoublyCircularChainNode<T>* nextNode = m_FirstNode->next;
                delete m_FirstNode;
                m_FirstNode = nextNode;
            }
            delete m_FirstNode;
        }
    }

    template<class T>
    void DoublyCircularChain<T>::EraseNode(DoublyCircularChainNode<T>*& node)
    {
        CheckNode(node);

        // Erase the first node if the chain has only one node,
        // since {node} is the first node.
        if (m_Size == 1)
        {
            delete m_FirstNode;
            m_FirstNode = nullptr;
            m_Size = 0;
            m_NodePtrs.clear();
            return;
        }

        // If the node to be erased is the first node, make the next node the first node.
        if (node == m_FirstNode)
            m_FirstNode = m_FirstNode->next;

        // Relink the chain.
        node->prior->next = node->next;
        node->next->prior = node->prior;

        // Erase the node.
        m_NodePtrs.erase(m_NodePtrs.find(node));
        delete node;
        --m_Size;
    }

    template<class T>
    void DoublyCircularChain<T>::PushBack(const T& element)
    {
        // Make {element} the first node if the chain is empty.
        if (m_Size == 0)
        {
            m_FirstNode = new DoublyCircularChainNode<T>{ element };
            m_FirstNode->prior = m_FirstNode;
            m_FirstNode->next = m_FirstNode;
            m_NodePtrs.emplace(m_FirstNode);
            ++m_Size;
            return;
        }
        // Insert the node at the end of the chain.
        DoublyCircularChainNode<T>* insertNode = new DoublyCircularChainNode<T>{ element, m_FirstNode->prior, m_FirstNode };
        m_FirstNode->prior->next = insertNode;
        m_FirstNode->prior = insertNode;
        m_NodePtrs.emplace(insertNode);
        ++m_Size;
    }

    template<class T>
    void DoublyCircularChain<T>::Clear()
    {
        m_Size = 0;
        m_NodePtrs.clear();

        if (m_FirstNode)
        {
            DoublyCircularChainNode<T>* endNode = m_FirstNode->prior;
            while (m_FirstNode != endNode)
            {
                DoublyCircularChainNode<T>* nextNode = m_FirstNode->next;
                delete m_FirstNode;
                m_FirstNode = nextNode;
            }
            delete m_FirstNode;
            m_FirstNode = nullptr;
        }
    }
}
