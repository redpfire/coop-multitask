#pragma once
#include "task.hpp"
#include <stdexcept>
#include <map>

// Caution: TaskQueue is not complete and will break in some instances
// it's just a makeshift implementation of a double linked list for this
// specific use case. Also this should be broken up into cpp and hpp but i was lazy
namespace Task {
    struct Node {
        Task& task;

        Node *prev;
        Node *next;
    };

    class TaskQueue {
        public:
            explicit TaskQueue()
                : head_{nullptr}
                , tail_{nullptr}
                , current_{nullptr}
                , items_{0}
            {
            }

            ~TaskQueue() {
                if (!tail_) {
                    return;
                }

                Node *temp = tail_;
                while (temp != head_) {
                    Node *current = temp;
                    temp = current->prev;

                    delete current;
                }
                delete head_;

                // paranoic use after free corner case?
                head_ = nullptr;
                tail_ = nullptr;
                current_ = nullptr;
            }

            void addTask(Task& task) {
                Node *temp = new Node{task, nullptr, nullptr};

                if (head_ == nullptr) {
                    temp->next = temp;
                    temp->prev = temp;
                    head_ = temp;
                    current_ = temp;
                    tail_ = temp;
                }
                else {
                    temp->next = head_;
                    temp->prev = tail_;
                    tail_->next = temp;
                    tail_ = temp;
                }

                items_++;
            }

            int removeTask(int id) {
                if (head_ != nullptr) {
                    Node *prev = nullptr;
                    Node *temp = head_;

                    do {
                        if (temp->task.getID() == id) {
                            if (prev == nullptr) {
                                if (current_ == head_) {
                                    current_ = temp->next;
                                }

                                temp->next->prev = tail_;
                                head_ = temp->next;
                                items_--;
                                return 1;
                            }

                            if (current_ == temp) {
                                current_ = temp->next;
                            }

                            temp->next->prev = prev;
                            prev->next = temp->next;
                            items_--;
                            return 1;
                        }

                        prev = temp;
                        temp = temp->next;
                    } while (temp != head_);

                    return 0;
                }
                
                return -1;
            }

            Task& peekHead() {
                return head_->task;
            }

            Task& popHead() {
                if (!head_) {
                    throw new std::out_of_range("No tasks to pick from");
                }

                current_ = head_;
                return current_->task;
            }

            Task& peekTail() {
                return tail_->task;
            }

            Task& peekNext() {
                return current_->task;
            }

            Task& peekPrev() {
                return current_->prev->task;
            }

            Task& popNext() {
                if (!current_) {
                    throw new std::out_of_range("No tasks to pick from");
                }

                Task& nextTask = current_->task;
                current_ = current_->next;

                return nextTask;
            }

            const int itemsNum() const {
                return items_;
            }

            const std::map<int, TaskState> getStates() const {
                if (!head_) {
                    throw new std::out_of_range("No tasks to pick from");
                }

                std::map<int, TaskState> ret;

                Node *temp = head_;
                do {
                    ret.insert({ temp->task.getID(), temp->task.getState() });

                    temp = temp->next;
                } while (temp != head_);

                return ret;
            }

        private:
            Node *head_;
            Node *tail_;

            Node *current_;

            int items_;
    };
}
