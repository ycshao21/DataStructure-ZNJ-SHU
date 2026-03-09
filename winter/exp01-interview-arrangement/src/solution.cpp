#include <format>
#include <iostream>
#include <ostream>
#include <string>

template <class T>
struct Node
{
    T data;
    Node<T>* prior = nullptr;  // Clockwise
    Node<T>* next = nullptr;   // Counter-clockwise
};

Node<int>* initResumes(int n)
{
    Node<int>* resumes = nullptr;
    Node<int>* curNode = nullptr;

    for (int i = 0; i < n; ++i) {
        auto* newNode = new Node<int>{.data = i + 1};
        if (resumes == nullptr) {
            resumes = newNode;
            curNode = resumes;
        } else {
            curNode->next = newNode;
            newNode->prior = curNode;
        }
        curNode = newNode;
    }

    curNode->next = resumes;
    resumes->prior = curNode;

    return resumes;
}

void cleanupResumes(Node<int>*& resumes)
{
    if (resumes != nullptr) {
        Node<int>* lastNode = resumes->prior;
        while (resumes != lastNode) {
            Node<int>* nextNode = resumes->next;
            delete resumes;
            resumes = nextNode;
        }
        // Delete the last node.
        delete resumes;
    }
}

void updatePosition(Node<int>*& position, int n, int count, bool clockwise)
{
    int steps = (count - 1) % n;

    // Move in the more efficient direction.
    if (steps > n / 2) {
        clockwise = !clockwise;
        steps = n - steps;
    }

    if (clockwise) {
        for (int i = 0; i < steps; ++i) {
            position = position->prior;
        }
    } else {
        for (int i = 0; i < steps; ++i) {
            position = position->next;
        }
    }
}

void takeResumesForTask01(Node<int>*& x, Node<int>*& y)
{
    if (x->next == y) {
        // Convert to the case where y->next == x.
        x = x->next;
        y = y->prior;
    }

    Node<int>* xNext = x->next;
    Node<int>* yPrior = y->prior;

    // Remove the node(s)
    if (x == y) {
        x->prior->next = x->next;
        x->next->prior = x->prior;
    } else if (y->next == x) {
        y->prior->next = x->next;
        x->next->prior = y->prior;

        delete y;
    } else {
        x->prior->next = x->next;
        x->next->prior = x->prior;

        y->prior->next = y->next;
        y->next->prior = y->prior;

        delete y;
    }

    delete x;

    x = xNext;
    y = yPrior;
}

void takeResumesForTask02(Node<int>*& x, Node<int>*& y, int newResume)
{
    Node<int>* yPrior = y->prior;

    if (x != y) {
        // Remove Y.
        y->prior->next = y->next;
        y->next->prior = y->prior;

        delete y;
    }

    x->data = newResume;
    y = yPrior;
}

void runTask01(int n, int k, int m, std::ostream* out)
{
    Node<int>* x = initResumes(n);
    Node<int>* y = x->prior;

    while (true) {
        updatePosition(x, n, k, false);
        updatePosition(y, n, m, true);

        if (x == y) {
            if (out != nullptr) {
                (*out) << std::format("{}", x->data);
            }
            --n;
        } else {
            if (out != nullptr) {
                (*out) << std::format("{}, {}", x->data, y->data);
            }
            n -= 2;
        }

        // All resumes have been taken.
        if (n == 0) {
            break;
        }

        if (out != nullptr) {
            (*out) << "; ";
        }
        takeResumesForTask01(x, y);
    }

    if (out != nullptr) {
        (*out) << '\n';
    }
    cleanupResumes(x);
}

void runTask02(int n, int k, int m, std::ostream* out)
{
    Node<int>* x = initResumes(n);
    Node<int>* y = x->prior;

    int newResume = n + 1;

    while (true) {
        updatePosition(x, n, k, false);
        updatePosition(y, n, m, true);

        if (x == y) {
            // Check if it is an endless loop.
            if ((k + m) % n == 1) {
                if (out != nullptr) {
                    (*out) << "...Unable to take all the resumes!";
                }
                break;
            }

            if (out != nullptr) {
                (*out) << std::format("{}", x->data);
            }
        } else {
            if (out != nullptr) {
                (*out) << std::format("{}, {}", x->data, y->data);
            }
            --n;
        }

        // All resumes have been taken.
        if (n == 1) {
            break;
        }

        if (out != nullptr) {
            (*out) << "; ";
        }
        takeResumesForTask02(x, y, newResume);
        ++newResume;
    }

    if (out != nullptr) {
        (*out) << '\n';
    }
    cleanupResumes(x);
}
