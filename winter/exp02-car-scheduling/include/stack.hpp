#pragma once

#include <memory>
#include <stdexcept>

namespace myds
{

template <class T>
class Stack
{
public:
    /**
     * @brief Construct a stack with a given capacity.
     * @param capacity The capacity of the stack.
     */
    Stack(std::size_t capacity = 0);
    /**
     * @brief Copy constructor.
     * @param other The stack to be copied.
     */
    Stack(const Stack<T>& other);
    /**
     * @brief Move constructor.
     * @param other The stack to be moved.
     */
    Stack(Stack<T>&& other) noexcept;
    /**
     * @brief Copy assignment operator.
     * @param other The stack to be copied.
     * @return The copied stack.
     */
    Stack<T>& operator=(const Stack<T>& other);
    /**
     * @brief Move assignment operator.
     * @param other The stack to be moved.
     * @return The moved stack.
     */
    Stack<T>& operator=(Stack<T>&& other) noexcept;
    /**
     * @brief Destructor.
     */
    ~Stack();

    /**
     * @brief Push an element to the top of the stack.
     * @param element The element to be pushed.
     */
    void push(const T& element);
    /**
     * @brief Push an element to the top of the stack.
     * @param element The element to be pushed.
     */
    void push(T&& element);
    /**
     * @brief Pop the top element of the stack.
     */
    void pop();

    /**
     * @brief Check if the stack is empty.
     * @return True if the stack is empty, false otherwise.
     */
    bool isEmpty() const
    {
        return m_topIndex == static_cast<std::size_t>(-1);
    };
    /**
     * @brief Check if the stack is full.
     * @return True if the stack is full, false otherwise.
     */
    bool isFull() const
    {
        return m_topIndex == m_capacity - 1;
    };
    /**
     * @brief Get the size of the stack.
     * @return The size of the stack.
     */
    int getSize() const
    {
        return m_topIndex + 1;
    };
    /**
     * @brief Get the capacity of the stack.
     * @return The capacity of the stack.
     */
    int getCapacity() const
    {
        return m_capacity;
    };

    /**
     * @brief Get the top element of the stack (non-const version).
     * @return The top element of the stack.
     */
    T& getTop();
    /**
     * @brief Get the top element of the stack (const version).
     * @return The top element of the stack.
     */
    const T& getTop() const;

private:
    void checkEmpty() const
    {
        if (m_topIndex == static_cast<std::size_t>(-1)) {
            throw std::runtime_error("Stack is empty!");
        }
    }

    T* m_data = nullptr;  // Elements in the stack.
    std::size_t m_topIndex =
        static_cast<std::size_t>(-1);  // Index of the top element (-1 if empty).
    std::size_t m_capacity = 0;        // Current capacity of the stack.
};

////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of member functions
////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
Stack<T>::Stack(std::size_t capacity) : m_capacity(capacity)
{
    if (capacity == 0) {
        m_data = nullptr;
    } else {
        m_data = (T*) ::operator new(capacity * sizeof(T));
    }
}

template <class T>
Stack<T>::Stack(const Stack<T>& other)
    : m_capacity(other.m_capacity), m_topIndex(other.m_topIndex)
{
    // Allocate memory for the new stack.
    m_data = (T*) ::operator new(other.m_capacity * sizeof(T));
    // Copy construct the elements from the other stack to the new stack.
    std::uninitialized_copy(other.m_data, other.m_data + other.getSize(), m_data);
}

template <class T>
Stack<T>::Stack(Stack<T>&& other) noexcept
    : m_data(other.m_data), m_topIndex(other.m_topIndex), m_capacity(other.m_capacity)
{
    other.m_data = nullptr;
    other.m_topIndex = static_cast<size_t>(-1);
    other.m_capacity = 0;
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if (this != &other) {
        // Delete the old stack.
        if (m_data != nullptr) {
            std::size_t size = getSize();
            for (std::size_t i = 0; i < size; ++i) {
                m_data[i].~T();
            }
            ::operator delete(m_data, m_capacity * sizeof(T));
        }
        // Allocate a new block of memory.
        m_data = (T*) ::operator new(other.m_capacity * sizeof(T));
        // Copy construct the elements from the other stack to the new stack.
        std::uninitialized_copy(other.m_data, other.m_data + other.getSize(), m_data);
        m_topIndex = other.m_topIndex;
        m_capacity = other.m_capacity;
    }
    return *this;
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept
{
    if (this != &other) {
        // Delete the old stack.
        if (m_data != nullptr) {
            std::size_t size = getSize();
            for (std::size_t i = 0; i < size; ++i) {
                m_data[i].~T();
            }
            ::operator delete(m_data, m_capacity * sizeof(T));
        }

        m_data = other.m_data;
        m_topIndex = other.m_topIndex;
        m_capacity = other.m_capacity;

        other.m_data = nullptr;
        other.m_topIndex = static_cast<size_t>(-1);
        other.m_capacity = 0;
    }
    return *this;
}

template <class T>
Stack<T>::~Stack()
{
    if (m_data != nullptr) {
        std::size_t size = getSize();
        for (std::size_t i = 0; i < size; ++i) {
            m_data[i].~T();
        }
        ::operator delete(m_data, m_capacity * sizeof(T));
    }
}

template <class T>
T& Stack<T>::getTop()
{
    checkEmpty();
    return m_data[m_topIndex];
}

template <class T>
const T& Stack<T>::getTop() const
{
    checkEmpty();
    return m_data[m_topIndex];
}

template <class T>
void Stack<T>::push(const T& element)
{
    // If the stack is full, expand the capacity by 50%.
    if (isFull()) {
        std::size_t increment = std::max((m_capacity >> 1), static_cast<std::size_t>(1));
        std::size_t newCapacity = m_capacity + increment;

        T* newData = (T*) ::operator new(newCapacity * sizeof(T));
        if (m_data != nullptr) {
            std::uninitialized_move(m_data, m_data + m_capacity, newData);
            ::operator delete(m_data, m_capacity * sizeof(T));
        }
        m_data = newData;
        m_capacity = newCapacity;
    }

    ++m_topIndex;
    new (&m_data[m_topIndex]) T(element);
}

template <class T>
void Stack<T>::push(T&& element)
{
    // If the stack is full, expand the capacity by 50%.
    if (isFull()) {
        std::size_t increment = std::max((m_capacity >> 1), static_cast<std::size_t>(1));
        std::size_t newCapacity = m_capacity + increment;

        T* newData = (T*) ::operator new(newCapacity * sizeof(T));
        if (m_data != nullptr) {
            std::uninitialized_move(m_data, m_data + m_capacity, newData);
            ::operator delete(m_data, m_capacity * sizeof(T));
        }
        m_data = newData;
        m_capacity = newCapacity;
    }

    ++m_topIndex;
    new (&m_data[m_topIndex]) T(std::move(element));
}

template <class T>
void Stack<T>::pop()
{
    checkEmpty();
    m_data[m_topIndex].~T();
    --m_topIndex;
}

}  // namespace myds
