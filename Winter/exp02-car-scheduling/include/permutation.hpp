#include <algorithm>
#include <vector>

#include "stack.hpp"

namespace algorithm
{
/* Generate full permutation of elements in {vec}:
 *   Let set E be {e_1, e_2, e_3, ..., e_n}.
 *   Define E_i as the set containing all the elements in E except e_i.
 *   Define perm(X) as the full permutation of set X.
 *   If n=1, perm(E)={e_1};
 *   If n>1, perm(E)={e_1.perm(E_1), e_2.perm(E_2), ..., e_n.perm(E_n)}, where
 * e_i is prefix and perm(E_i) is suffix. Each suffix keeps splitting until it only
 * contains one element (indicating the end of recursion).
 */
template <class T>
[[deprecated]] void fullPermutation(std::vector<T>& vec, int begin, int end,
                                    std::vector<std::vector<T>>& perms)
{
    if (begin == end) {
        perms.push_back(vec);
        return;
    }

    for (int i = begin; i <= end; i++) {
        std::swap(vec[begin], vec[i]);  // Let vec[i] be the prefix
        fullPermutation(vec, begin + 1, end, perms);
        std::swap(vec[begin], vec[i]);  // Restore the original state of vec.
    }
}

namespace internal
{
/*
 * @brief Generate all the possible stack output sequences of input.
 * @param inputOrder The input sequence.
 * @param begin The index of the current element to be processed.
 * @param st The stack.
 * @param outputOrder The output sequence.
 * @param outputOrders All the possible stack output sequences.
 */
template <class T>
void generateAllStackOutput(const std::vector<T>& inputOrder, std::size_t begin,
                            myds::Stack<T>& st, std::vector<T>& outputOrder,
                            std::vector<std::vector<T>>& outputOrders)
{
    // End of recursion.
    if (outputOrder.size() == inputOrder.size()) {
        outputOrders.push_back(outputOrder);
        return;
    }

    // Pop from the stack.
    if (!st.isEmpty()) {
        T top = st.getTop();
        outputOrder.push_back(top);
        st.pop();
        generateAllStackOutput(inputOrder, begin, st, outputOrder, outputOrders);
        st.push(top);
        outputOrder.pop_back();
    }

    // Push new elements into the stack.
    if (begin != inputOrder.size()) {
        st.push(inputOrder[begin]);
        generateAllStackOutput(inputOrder, begin + 1, st, outputOrder, outputOrders);
        st.pop();
    }
}

}  // namespace internal

template <class T>
void generateAllStackOutput(const std::vector<T>& inputOrder,
                            std::vector<std::vector<T>>& outOrders)
{
    myds::Stack<T> st;
    std::vector<T> outOrder;
    internal::generateAllStackOutput(inputOrder, 0, st, outOrder, outOrders);
}

}  // namespace algorithm