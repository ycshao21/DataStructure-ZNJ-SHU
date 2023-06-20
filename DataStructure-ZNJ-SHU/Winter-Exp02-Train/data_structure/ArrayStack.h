#pragma once
#include"../../Tools/MyExceptions.h"

template<class _Ty>
class ArrayStack
{
public:
    using sizet = size_t;
    using indext = long long;
    /**
     * @brief Construct an empty stack with initial capacity.
     * @param initCapacity The initial capacity of the stack (default value = 10).
    */
    ArrayStack(sizet initCapacity = 0);
    /**
     * @brief Copy constructor.
     * @param theStack The stack to be copied.
    */
    ArrayStack(const ArrayStack<_Ty>& theStack);
    /**
     * @brief Assignment operator.
     * @param theStack The stack to be assigned.
    */
    ArrayStack<_Ty>& operator=(const ArrayStack<_Ty>& theStack);
    // @brief Destructor.
    ~ArrayStack() { delete[] data; }

    // @brief Check if the stack is empty.
    bool empty() const { return stackTop == -1; };
    // @brief Get the size of the stack.
    sizet size() const { return stackTop + 1; };
    sizet capacity() const { return arrCapacity; };

    // @brief Get the top element of the stack (non-const version).
    _Ty& top();
    // @brief Get the top element of the stack (const version).
    const _Ty& top() const;

    // @brief Pop the top element of the stack.
    void pop();
    // @brief Push an element to the top of the stack.
    void push(const _Ty& element);
protected:
    indext stackTop;  // Index of the top element (-1 if empty).
    sizet arrCapacity;  // Current capacity of the stack.
    _Ty* data;  // Elements in the stack.
};

template<class _Ty>
ArrayStack<_Ty>::ArrayStack(sizet initialCapacity) {
    stackTop = -1;
    arrCapacity = initialCapacity;
    data = initialCapacity == 0 ? nullptr : new _Ty[initialCapacity];
}

template<class _Ty>
ArrayStack<_Ty>::ArrayStack(const ArrayStack<_Ty>& theStack)
    : arrCapacity(theStack.arrCapacity), stackTop(theStack.stackTop) {
    data = new _Ty[theStack.arrCapacity];
    std::copy(theStack.data, theStack.data + theStack.stackTop + 1, data);
}

template<class _Ty>
ArrayStack<_Ty>& ArrayStack<_Ty>::operator=(const ArrayStack<_Ty>& theStack) {
    if (this != &theStack) {
        stackTop = theStack.stackTop;
        arrCapacity = theStack.arrCapacity;
        delete[] data;
        data = new _Ty[theStack.arrCapacity];
        std::copy(theStack.data, theStack.data + theStack.stackTop + 1, data);
    }
    return *this;
}

template<class _Ty>
const _Ty& ArrayStack<_Ty>::top() const {
    if (stackTop == -1) {
        throw StackEmpty();
    }
    return data[stackTop];
}

template<class _Ty>
_Ty& ArrayStack<_Ty>::top() {
    auto const_this = const_cast<const ArrayStack<_Ty>*>(this);
    return const_cast<_Ty&>(const_this->top());
}

template<class _Ty>
void ArrayStack<_Ty>::pop() {
    if (stackTop == -1) {
        throw StackEmpty();
    }
    data[stackTop--].~_Ty();
}

template<class _Ty>
void ArrayStack<_Ty>::push(const _Ty& element) {
    // If the stack is full, double the capacity.
    if (stackTop == arrCapacity - 1) {
        if (arrCapacity == 0) {
            arrCapacity = 1;
            data = new _Ty[1];
        } else {
            sizet increment = (arrCapacity >= 4) ? (arrCapacity >> 1) : 1;
            sizet newCapacity = arrCapacity + increment;
            _Ty* newData = new _Ty[newCapacity];
            std::move(data, data + arrCapacity, newData);
            delete[] data;
            data = newData;
            arrCapacity = newCapacity;
        }
    }
    data[++stackTop] = element;
}
