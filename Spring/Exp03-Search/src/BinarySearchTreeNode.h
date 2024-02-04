#pragma once

namespace MyDS
{
    template<class K, class E>
    struct BinarySearchTreeNode
    {
        std::pair<K, E> data; // { key, element }
        BinarySearchTreeNode<K, E>* leftChild = nullptr;
        BinarySearchTreeNode<K, E>* rightChild = nullptr;
    };
}
