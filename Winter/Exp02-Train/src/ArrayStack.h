#pragma once

namespace MyDS
{
    template<class T>
    class ArrayStack
    {
    public:
        /**
         * @brief Construct an empty stack with initial capacity.
         * @param initCapacity The initial capacity of the stack (default 0).
        */
        ArrayStack(int initCapacity = 0);
        /**
         * @brief Copy constructor.
         * @param stack The stack to be copied.
        */
        ArrayStack(const ArrayStack<T>& stack);
        // @brief Destructor.
        ~ArrayStack() { delete[] m_Data; }

        // @brief Check if the stack is empty.
        bool IsEmpty() const { return m_Top == -1; };
        // @brief Get the size of the stack.
        int GetSize() const { return m_Top + 1; };
        int GetCapacity() const { return m_Capacity; };

        // @brief Get the top element of the stack (non-const version).
        T& GetTop();
        // @brief Get the top element of the stack (const version).
        const T& GetTop() const;

        // @brief Push an element to the top of the stack.
        void Push(const T& element);
        // @brief Pop the top element of the stack.
        void Pop();
    private:
        void CheckEmpty() const
        {
            if (m_Top == -1)
                throw "Stack empty!";
        }
    private:
        int m_Top = -1;  // Index of the top element (-1 if empty).
        int m_Capacity = 0;  // Current capacity of the stack.
        T* m_Data = nullptr;  // Elements in the stack.
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Implementation of member functions
    ////////////////////////////////////////////////////////////////////////////////////////////////

    template<class T>
    ArrayStack<T>::ArrayStack(int initCapacity)
    {
        if (initCapacity < 0)
            throw "Invalid initial capacity!";

        m_Top = -1;
        m_Capacity = initCapacity;
        m_Data = initCapacity == 0 ? nullptr : new T[initCapacity];
    }

    template<class T>
    ArrayStack<T>::ArrayStack(const ArrayStack<T>& theStack)
        : m_Capacity(theStack.m_Capacity), m_Top(theStack.m_Top)
    {
        m_Data = new T[theStack.m_Capacity];
        std::copy(theStack.m_Data, theStack.m_Data + theStack.m_Top + 1, m_Data);
    }

    template<class T>
    T& ArrayStack<T>::GetTop()
    {
        CheckEmpty();
        return m_Data[m_Top];
    }

    template<class T>
    const T& ArrayStack<T>::GetTop() const
    {
        CheckEmpty();
        return m_Data[m_Top];
    }

    template<class T>
    void ArrayStack<T>::Push(const T& element)
    {
        // If the stack is full, double the capacity.
        if (m_Top == m_Capacity - 1)
        {
            if (m_Capacity == 0)
            {
                m_Capacity = 1;
                m_Data = new T[1];
            }
            else
            {
                int increment = (m_Capacity >= 4) ? (m_Capacity >> 1) : 1;
                int newCapacity = m_Capacity + increment;
                T* newData = new T[newCapacity];
                std::move(m_Data, m_Data + m_Capacity, newData);
                delete[] m_Data;
                m_Data = newData;
                m_Capacity = newCapacity;
            }
        }
        m_Data[++m_Top] = element;
    }

    template<class T>
    void ArrayStack<T>::Pop()
    {
        CheckEmpty();
        m_Data[m_Top--].~T();
    }
}
