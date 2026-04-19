#pragma once

#include <cstddef>
#include <utility>

template<typename T>
class DoublyLinkedList {

    private:

        struct Node {

                T     data;
                Node* prev = nullptr;
                Node* next = nullptr;

                explicit Node(const T& value) : data(value) {}

                explicit Node(T&& value) : data(std::move(value)) {}
        };

        Node*       _head;
        Node*       _tail;
        std::size_t _size;
};