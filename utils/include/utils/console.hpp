#pragma once
#include <print>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>
#include <functional>


namespace utils
{

inline void clearBuffer(char end = '\n')
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), end);
}

class Menu {
public:
    struct MenuItem {
        std::string title;
        std::function<void()> action;
    };

    explicit Menu(std::string title, 
                  bool isPersistent = true, 
                  std::string exitTitle = "Exit") 
        : m_title(std::move(title)), m_isPersistent(isPersistent), m_exitTitle(std::move(exitTitle)) {}
    
    void setHeader(std::function<void()> header) {
        m_header = std::move(header);
    }

    void addItem(std::string title, std::function<void()> action = [](){}) {
        m_items.push_back({std::move(title), std::move(action)});
    }

    std::size_t ask() const {
        show();
        std::size_t choice = getChoice();
        std::println();
        return choice;
    }

    void run() const {
        while (true) {
            std::size_t choice = ask();
            if (choice == 0) { 
                return;
            }

            const MenuItem& item = m_items[choice - 1];
            std::println("[{}]", item.title);
            item.action();
            std::println();

            if (!m_isPersistent) {
                return;
            }

            if (m_showLoopSeparator) {
                std::println("{}", std::string(60, '#'));
                std::println();
            }
        }
    }

private:
    void show() const {
        if (!m_title.empty()) {
            std::println("{}", m_title);
        }

        if (m_header) {
            m_header();
            std::println();
        }

        for (std::size_t i = 0; i < m_items.size(); ++i) {
            std::println("[{}] {}", i + 1, m_items[i].title);
        }
        if (m_isPersistent) {
            std::println("[0] {}", m_exitTitle);
        }
    }

    std::size_t getChoice(
        const std::string& prompt = "Your choice: ",
        const std::string& err = "Invalid choice! Please try again: ") const
    {
        if (!prompt.empty()) {
            std::print("{}", prompt);
        }
        
        std::size_t choice;
        while (true) {
            if (std::cin >> choice) {
                if (choice == 0 && m_isPersistent) {
                    return 0;
                }
                if (choice >= 1 && choice <= m_items.size()) {
                    return choice;
                }
            }
            clearBuffer();
            if (!err.empty()) {
                std::print("{}", err);
            }
        }
        return 0; // Unreachable, but avoids compiler warning.
    }

    std::string m_title;
    std::function<void()> m_header;
    std::vector<MenuItem> m_items;
    bool m_isPersistent = true;
    std::string m_exitTitle;
    bool m_showLoopSeparator = true;
};

}  // namespace utils