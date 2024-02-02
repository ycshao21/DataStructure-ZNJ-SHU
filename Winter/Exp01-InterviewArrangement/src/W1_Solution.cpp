#include "W1_Solution.h"

#include "DoublyCircularChain.h"

#include <string>
#include <format>
#include <iostream>

namespace Winter01
{
    using Chain = MyDS::DoublyCircularChain<int>;
    using Node = MyDS::DoublyCircularChainNode<int>;

    void MoveForward(Node*& X, Node*& Y, int N, int K, int M)
    {
        // Calculate the fewest moves in X's positive direction (within one round).
        int XMoves = (K - 1) % N;
        // Move X in the more efficient direction.
        if (XMoves <= N / 2)
        {
            for (int i = 0; i < XMoves; ++i)
                X = X->next;
        }
        else
        {
            for (int i = 0; i < N - XMoves; ++i)
                X = X->prior;
        }

        // Do the same for Y.
        int YMoves = (M - 1) % N;
        if (YMoves <= N / 2)
        {
            for (int i = 0; i < YMoves; ++i)
                Y = Y->prior;
        }
        else
        {
            for (int i = 0; i < N - YMoves; ++i)
                Y = Y->next;
        }
    }

    void Task01(int N, int K, int M)
    {
        if (N == 1)
        {
            std::cout << 1 << std::endl;
            return;
        }

        // Initialize resumes, X and Y.
        Chain resumes;
        for (int i = 1; i <= N; ++i) {
            resumes.PushBack(i);
        }
        Node* X = resumes.GetFirstNode();
        Node* Y = X->prior;

        std::string ans;
        while (!resumes.IsEmpty())
        {
            MoveForward(X, Y, resumes.GetSize(), K, M);
            Node* nextX = X->next;
            Node* priorY = Y->prior;
            if (X == Y)
            {
                // Y does not have to take the resume, because X will take it.
                ans += std::format("{}; ", X->data);
            }
            else {
                ans += std::format("{0}, {1}; ", X->data, Y->data);
                // Move one step further if X and Y are adjacent.
                if (nextX == Y)
                    nextX = nextX->next;
                if (priorY == X)
                    priorY = priorY->prior;

                resumes.EraseNode(Y);
            }
            resumes.EraseNode(X);
            X = nextX;
            Y = priorY;
        }

        ans = ans.substr(0, ans.size() - 2);  // Remove the last "; ".
        std::cout << ans << std::endl;
    }

    void Task02(int N, int K, int M)
    {
        if (N == 1)
        {
            std::cout << 1 << std::endl;
            return;
        }
        // Initialize resumes, X and Y.
        Chain resumes;
        for (int i = 1; i <= N; ++i)
            resumes.PushBack(i);

        Node* X = resumes.GetFirstNode();
        Node* Y = X->prior;

        std::string ans;
        while (resumes.GetSize() > 1)
        {
            MoveForward(X, Y, resumes.GetSize(), K, M);
            Node* priorY = Y->prior;
            if (X == Y)
            {
                // Check if it is an endless loop.
                if ((K + M) % resumes.GetSize() == 1)
                {
                    std::cout << "¼òÀúÈ¡²»¾¡£¡" << std::endl;
                    return;
                }
                ans += std::format("{}; ", X->data);
            }
            else
            {
                ans += std::format("{0}, {1}; ", X->data, Y->data);
                resumes.EraseNode(Y);
            }
            X->data = ++N;  // Insert the new resume.
            Y = priorY;
        }

        ans = ans.substr(0, ans.size() - 2);  // Remove the last "; ".
        std::cout << ans << std::endl;
    }
}
