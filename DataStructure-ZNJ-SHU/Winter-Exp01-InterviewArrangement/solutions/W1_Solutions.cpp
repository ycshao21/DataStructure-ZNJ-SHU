#include<sstream>
#include"../data_structure/DoublyCircularChain.h"

namespace W1
{
    using Chain = DoublyCircularChain<int>;
    using Node = DoublyCircularChainNode<int>;

    void move(Node*& X, Node*& Y, int N, int K, int M) {
        // Calculate the fewest moves in X's positive direction (within one lap).
        int Xmoves = (K - 1) % N;
        // Move X in the more efficient direction.
        if (Xmoves <= N / 2) {
            for (int i = 0; i < Xmoves; ++i) {
                X = X->next;
            }
        } else {
            for (int i = 0; i < N - Xmoves; ++i) {
                X = X->prior;
            }
        }

        // Do the same for Y.
        int Ymoves = (M - 1) % N;
        if (Ymoves <= N / 2) {
            for (int i = 0; i < Ymoves; ++i) {
                Y = Y->prior;
            }
        } else {
            for (int i = 0; i < N - Ymoves; ++i) {
                Y = Y->next;
            }
        }
    }

    void Question1(int N, int K, int M, std::ostream* out) {
        if (N == 0) {
            if (out) {
                (*out) << "没有简历！" << std::endl;
            }
            return;
        }
        if (N == 1) {
            if (out) {
                (*out) << 1 << std::endl;
            }
            return;
        }
        // Initialize resumes, X and Y.
        Chain resumes;
        for (int i = 1; i <= N; ++i) {
            resumes.push_back(i);
        }
        Node* X = resumes.begin();
        Node* Y = X->prior;

        std::ostringstream process;
        while (resumes.size() > 0) {
            move(X, Y, resumes.size(), K, M);
            Node* nextX = X->next;
            Node* priorY = Y->prior;
            if (X == Y) {
                // Y does not have to take the resume, since X will take it.
                process << X->data << "; ";
            } else {
                process << X->data << ", " << Y->data << "; ";
                // Move one step further if X and Y are adjacent.
                if (nextX == Y) { nextX = nextX->next; }
                if (priorY == X) { priorY = priorY->prior; }
                resumes.erase(Y);
            }
            resumes.erase(X);
            X = nextX;
            Y = priorY;
        }

        std::string ans = process.str();
        if (out) {
            (*out) << ans.substr(0, ans.size() - 2) << std::endl;
        }
    }

    void Question2(int N, int K, int M, std::ostream* out) {
        if (N == 0) {
            if (out) {
                (*out) << "没有简历！" << std::endl;
            }
            return;
        }
        if (N == 1) {
            if (out) {
                (*out) << 1 << std::endl;
            }
            return;
        }
        // Initialize resumes, X and Y.
        Chain resumes;
        for (int i = 1; i <= N; ++i) {
            resumes.push_back(i);
        }
        Node* X = resumes.begin();
        Node* Y = X->prior;

        std::ostringstream process;
        while (resumes.size() > 1) {
            move(X, Y, resumes.size(), K, M);
            Node* priorY = Y->prior;
            if (X == Y) {
                // Check if it is an endless loop.
                if ((K + M) % resumes.size() == 1) {
                    if (out) {
                        (*out) << "简历取不尽！" << std::endl;
                    }
                    return;
                }
                process << X->data << "; ";
            } else {
                process << X->data << ", " << Y->data << "; ";
                resumes.erase(Y);
            }
            X->data = ++N;  // Insert the new resume.
            Y = priorY;
        }

        std::string ans = process.str();
        if (out) {
            (*out) << ans.substr(0, ans.size() - 2) << std::endl;
        }
    }
}