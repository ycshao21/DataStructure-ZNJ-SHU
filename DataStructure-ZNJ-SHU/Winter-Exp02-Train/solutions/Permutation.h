#include<vector>
#include"../data_structure/ArrayStack.h"

namespace W2
{
    /* Generate full permutation of elements in vec:
    *   Let set E be {e1, e2, e3, ..., en}.
    *   Define Ei as the set containing all the elements in E except ei.
    *   Define perm(X) as the full permutation of set X.
    *   If n=1, perm(E)={e1};
    *   If n>1, perm(E)={e1.perm(E1), e2.perm(E2), ..., en.perm(En)}, where ei is prefix and perm(Ei) is suffix.
    *   Each suffix can keep spliting until it only contains one element.
    */
    template<class _Ty>
    void full_permutation(std::vector<_Ty>& vec, int begin, int end, std::vector<std::vector<_Ty>>& perms) {
        if (begin == end) { // The suffix only contains one element (indicating the end of recursion).
            perms.push_back(vec);
            return;
        }
        for (int i = begin; i <= end; i++) {
            std::swap(vec[begin], vec[i]);  // Let list[i] be the prefix
            full_permutation(vec, begin + 1, end, perms);
            std::swap(vec[begin], vec[i]); // Restore the original state of list.
        }
    }

    // @brief Generate all the possible stack output sequences of input.
    template<class _Ty>
    void stack_out(const std::vector<_Ty>& inOrder, int begin,
        ArrayStack<_Ty>& st, std::vector<_Ty>& outOrder, std::vector<std::vector<_Ty>>& outOrders)
    {
        if (outOrder.size() == inOrder.size()) {
            outOrders.push_back(outOrder);
            return;
        }
        // Pop from the stack.
        if (!st.empty()) {
            outOrder.push_back(st.top());
            st.pop();
            stack_out(inOrder, begin, st, outOrder, outOrders);
            st.push(outOrder.back());
            outOrder.pop_back();
        }
        // Push new elements into the stack.
        if (begin != inOrder.size()) {
            st.push(inOrder[begin]);
            stack_out(inOrder, begin + 1, st, outOrder, outOrders);
            st.pop();
        }
    }
}