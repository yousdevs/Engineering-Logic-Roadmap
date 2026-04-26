#pragma once

#include <cstddef>
#include <iterator>
#include <utility>

template<typename T>
class DoublyLinkedList {

    public:

        using reference       = T&;
        using const_reference = const T&;

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
            return _size == 0;
        }

        void swap(DoublyLinkedList& other) noexcept {

            using std::swap;

            swap(_head, other._head);
            swap(_tail, other._tail);
            swap(_size, other._size);
        }

        struct Node;

        class iterator {

            public:

                using iterator_category = std::bidirectional_iterator_tag;
                using value_type        = T;
                using difference_type   = std::ptrdiff_t;
                using pointer           = T*;
                using reference         = T&;

                iterator() noexcept : _current(nullptr) {}

                explicit iterator(Node* node) noexcept : _current(node) {}

                reference operator*() const {

                    return _current->data;
                }

                pointer operator->() const {

                    return &(_current->data);
                }

                iterator& operator++() noexcept {

                    _current = _current->next;
                    return *this;
                }

                iterator operator++(int) noexcept {

                    iterator temp = *this;
                    _current      = _current->next;
                    return temp;
                }

                iterator& operator--() noexcept {

                    _current = _current->prev;
                    return *this;
                }

                iterator operator--(int) noexcept {

                    iterator temp = *this;
                    _current      = _current->prev;
                    return temp;
                }

                bool operator==(const iterator& other) const noexcept {

                    return _current == other._current;
                }

                bool operator!=(const iterator& other) const noexcept {

                    return _current != other._current;
                }

            private:

                Node* _current;
                friend class DoublyLinkedList<T>;
        };

        iterator begin() noexcept {

            return iterator(_head);
        }

        iterator end() noexcept {

            return iterator(nullptr);
        }

        void push_front(const T& value) {

            Node* node = new Node(value);
            _insertBefore(_head, node);
        }

        void push_front(T&& value) {

            Node* node = new Node(std::move(value));
            _insertBefore(_head, node);
        }

        void pop_front() {

            if (empty())
                return;

            Node* node = _unlink(_head);
            delete node;
        }

        void push_back(const T& value) {

            Node* node = new Node(value);
            _insertBefore(nullptr, node);
        }

        void push_back(T&& value) {

            Node* node = new Node(std::move(value));
            _insertBefore(nullptr, node);
        }

        void pop_back() {

            if (empty())
                return;

            Node* node = _unlink(_tail);
            delete node;
        }

        reference front() {

            return _head->data;
        }

        const_reference front() const {

            return _head->data;
        }

        reference back() {

            return _tail->data;
        }

        const_reference back() const {

            return _tail->data;
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

        // inserts newNode before next
        Node* _insertBefore(Node* next, Node* newNode) noexcept {

            // empty list
            if (_head == nullptr) {

                _head = _tail = newNode;
                ++_size;
                return newNode;
            }

            // insert at front
            if (_head == next) {

                newNode->prev = nullptr;
                newNode->next = _head;
                _head->prev   = newNode;
                _head         = newNode;

                ++_size;
                return newNode;
            }

            // insert at end
            if (next == nullptr) {

                newNode->next = nullptr;
                newNode->prev = _tail;
                _tail->next   = newNode;
                _tail         = newNode;
                ++_size;
                return newNode;
            }

            // insert at middle
            newNode->prev = next->prev;
            newNode->next = next;

            next->prev->next = newNode;
            next->prev       = newNode;
            ++_size;

            return newNode;
        }

        // detach the node from the list without deleting it
        // returns the unlinked node
        Node* _unlink(Node* node) noexcept {

            // single element
            if (_head == node && _tail == node) {

                _head = _tail = nullptr;
                --_size;
                return node;
            }

            // removing head
            if (_head == node) {

                _head       = _head->next;
                _head->prev = nullptr;
                node->next  = nullptr;
                --_size;
                return node;
            }

            // removing tail
            if (_tail == node) {

                _tail       = _tail->prev;
                _tail->next = nullptr;
                node->prev  = nullptr;
                --_size;
                return node;
            }

            // removing middle
            node->prev->next = node->next;
            node->next->prev = node->prev;

            node->prev = node->next = nullptr;
            --_size;
            return node;
        }
};