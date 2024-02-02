#include <vector>
#include "ArrayStack.h"

namespace Winter02
{
    /* Generate full permutation of elements in {vec}:
    *   Let set E be {e_1, e_2, e_3, ..., e_n}.
    *   Define E_i as the set containing all the elements in E except e_i.
    *   Define perm(X) as the full permutation of set X.
    *   If n=1, perm(E)={e_1};
    *   If n>1, perm(E)={e_1.perm(E_1), e_2.perm(E_2), ..., e_n.perm(E_n)}, where e_i is prefix and perm(E_i) is suffix.
    *   Each suffix can keep spliting until it only contains one element.
    */
    template<class T>
    void FullPermutation(std::vector<T>& vec, int begin, int end, std::vector<std::vector<T>>& perms)
    {
        if (begin == end)  // The suffix only contains one element (indicating the end of recursion).
        {
            perms.push_back(vec);
            return;
        }

        for (int i = begin; i <= end; i++)
        {
            std::swap(vec[begin], vec[i]);  // Let list[i] be the prefix
            FullPermutation(vec, begin + 1, end, perms);
            std::swap(vec[begin], vec[i]); // Restore the original state of list.
        }
    }

    // @brief Generate all the possible stack output sequences of input.
    template<class T>
    void StackOut(const std::vector<T>& inOrder, int begin,
        MyDS::ArrayStack<T>& st, std::vector<T>& outOrder, std::vector<std::vector<T>>& outOrders)
    {
        if (outOrder.size() == inOrder.size())
        {
            outOrders.push_back(outOrder);
            return;
        }

        // Pop from the stack.
        if (!st.IsEmpty())
        {
            outOrder.push_back(st.GetTop());
            st.Pop();
            StackOut(inOrder, begin, st, outOrder, outOrders);
            st.Push(outOrder.back());
            outOrder.pop_back();
        }
        // Push new elements into the stack.
        if (begin != inOrder.size())
        {
            st.Push(inOrder[begin]);
            StackOut(inOrder, begin + 1, st, outOrder, outOrders);
            st.Pop();
        }
    }
}