#pragma once

template<class K, class E>
struct BinarySearchTreeNode  // For Binary Search Tree
{
    std::pair<K, E> data; // { key, element }
    BinarySearchTreeNode<K, E>* leftChild = nullptr;
    BinarySearchTreeNode<K, E>* rightChild = nullptr;
};
