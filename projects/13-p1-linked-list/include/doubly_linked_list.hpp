#pragma once

#include <cstddef>
#include <utility>

template<typename T>
class DoublyLinkedList {

    public:

        DoublyLinkedList() noexcept : _head(nullptr), _tail(nullptr), _size(0) {}

        DoublyLinkedList(const DoublyLinkedList& other) {

            _head = nullptr;
            _tail = nullptr;
            _size = 0;

            _copyFrom(other);
        }

        DoublyLinkedList(DoublyLinkedList&& other) noexcept
            : _head(other._head), _tail(other._tail), _size(other._size) {

            other._head = nullptr;
            other._tail = nullptr;
            other._size = 0;
        }

        ~DoublyLinkedList() {

            _destroyAll();
        }

        DoublyLinkedList& operator=(DoublyLinkedList other) {

            swap(other);
            return *this;
        }

        DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {

            if (this == &other)
                return *this;

            _destroyAll();

            _head = other._head;
            _tail = other._tail;
            _size = other._size;

            other._head = nullptr;
            other._tail = nullptr;
            other._size = 0;

            return *this;
        }

        std::size_t size() const noexcept {
            return _size;
        }

        bool empty() const noexcept {
            return _head == nullptr;
        }

        void swap(DoublyLinkedList& other) noexcept {

            using std::swap;

            swap(_head, other._head);
            swap(_tail, other._tail);
            swap(_size, other._size);
        }

    private:

        struct Node {

                T     data;
                Node* prev = nullptr;
                Node* next = nullptr;

                explicit Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}

                explicit Node(T&& value) : data(std::move(value)), prev(nullptr), next(nullptr) {}
        };

        Node*       _head;
        Node*       _tail;
        std::size_t _size;

        void _destroyAll() noexcept {

            while (_head != nullptr) {

                Node* temp = _head;
                _head      = _head->next;
                delete temp;
            }

            _tail = nullptr;
            _size = 0;
        }

        // tail insertion O(n)
        void _copyFrom(const DoublyLinkedList& other) {

            Node* cur = other._head;

            while (cur != nullptr) {

                Node* n = new Node(cur->data);

                n->prev = _tail;
                n->next = nullptr;

                if (_tail) {
                    // there is a previously created node
                    _tail->next = n;
                } else {
                    // this is the first node being created
                    _head = n;
                }

                _tail = n;
                ++_size;

                cur = cur->next;
            }
        }
};