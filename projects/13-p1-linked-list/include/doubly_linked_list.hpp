#pragma once

#include <cstddef>
#include <initializer_list>
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

        DoublyLinkedList(std::initializer_list<T> init) : _head(nullptr), _tail(nullptr), _size(0) {

            for (const T& v : init)
                push_back(v);
        }

        DoublyLinkedList& operator=(std::initializer_list<T> init) {

            DoublyLinkedList temp;

            for (const T& v : init)
                temp.push_back(v);

            swap(temp);
            return *this;
        }

        DoublyLinkedList& operator=(DoublyLinkedList other) {

            swap(other);
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
                friend class const_iterator;
        };

        class const_iterator {

            public:

                using iterator_category = std::bidirectional_iterator_tag;
                using value_type        = T;
                using difference_type   = std::ptrdiff_t;
                using pointer           = const T*;
                using reference         = const T&;

                const_iterator(const iterator& it) noexcept : _current(it._current) {}

                const_iterator() noexcept : _current(nullptr) {}

                explicit const_iterator(const Node* node) noexcept : _current(node) {}

                reference operator*() const {

                    return _current->data;
                }

                pointer operator->() const {

                    return &(_current->data);
                }

                const_iterator& operator++() noexcept {

                    _current = _current->next;
                    return *this;
                }

                const_iterator operator++(int) noexcept {

                    const_iterator temp = *this;
                    _current            = _current->next;
                    return temp;
                }

                const_iterator& operator--() noexcept {

                    _current = _current->prev;
                    return *this;
                }

                const_iterator operator--(int) noexcept {

                    const_iterator temp = *this;
                    _current            = _current->prev;
                    return temp;
                }

                bool operator==(const const_iterator& other) const noexcept {

                    return _current == other._current;
                }

                bool operator==(const iterator& other) const noexcept {

                    return _current == other._current;
                }

                bool operator!=(const const_iterator& other) const noexcept {

                    return _current != other._current;
                }

                bool operator!=(const iterator& other) const noexcept {

                    return _current != other._current;
                }

            private:

                const Node* _current;
                friend class DoublyLinkedList<T>;
                friend class iterator;
        };

        iterator begin() noexcept {

            return iterator(_head);
        }

        iterator end() noexcept {

            return iterator(nullptr);
        }

        const_iterator begin() const noexcept {

            return const_iterator(_head);
        }

        const_iterator end() const noexcept {

            return const_iterator(nullptr);
        }

        const_iterator cbegin() const noexcept {

            return const_iterator(_head);
        }

        const_iterator cend() const noexcept {

            return const_iterator(nullptr);
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

        iterator insert(const_iterator pos, const T& value) {

            Node* node = new Node(value);

            Node* inserted = _insertBefore(const_cast<Node*>(pos._current), node);

            return iterator(inserted);
        }

        iterator insert(const_iterator pos, T&& value) {

            Node* node = new Node(std::move(value));

            Node* inserted = _insertBefore(const_cast<Node*>(pos._current), node);

            return iterator(inserted);
        }

        iterator erase(const_iterator pos) {

            Node* current = const_cast<Node*>(pos._current);
            Node* next    = current->next;

            Node* node = _unlink(current);

            delete node;
            return iterator(next);
        }

        iterator erase(const_iterator first, const_iterator last) {

            Node* current = const_cast<Node*>(first._current);

            while (current != last._current) {

                Node* next = current->next;

                Node* node = _unlink(current);
                delete node;

                current = next;
            }

            return iterator(const_cast<Node*>(last._current));
        }

        void clear() noexcept {

            _destroyAll();
        }

        // swaps prev/next on every node plus swaps _head/_tail
        void reverse() noexcept {

            Node* current = _head;

            while (current != nullptr) {

                Node* next = current->next;

                std::swap(current->next, current->prev);

                current = next;
            }

            std::swap(_head, _tail);
        }

        // remove all matching elements
        template<typename UnaryPredicate>
        size_t remove_if(UnaryPredicate pred) {

            std::size_t count = 0;

            Node* current = _head;

            while (current != nullptr) {

                Node* next = current->next;

                if (pred(current->data)) {

                    Node* node = _unlink(current);
                    delete node;
                    ++count;
                }
                current = next;
            }

            return count;
        }

        std::size_t remove(const T& value) {

            return remove_if([&](const T& v) { return v == value; });
        }

        template<typename Compare>
        void sort(Compare comp) {

            if (!_head || !_head->next)
                return;

            _head = _mergeSort(_head, comp);

            // restore tail
            _tail = _head;
            while (_tail && _tail->next)
                _tail = _tail->next;
        }

        // merge sort - ascending
        void sort() {

            sort([&](T& a, T& b) { return a <= b; });
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

        template<typename Compare>
        static Node* _mergeSort(Node* head, Compare comp) {

            if (!head || !head->next)
                return head;

            Node* second = _split(head);

            Node* left  = _mergeSort(head, comp);
            Node* right = _mergeSort(second, comp);

            return _merge(left, right, comp);
        }

        static Node* _split(Node* head) {

            if (!head || !head->next)
                return nullptr;

            Node* slow = head;
            Node* fast = head;

            while (fast->next && fast->next->next) {
                slow = slow->next;
                fast = fast->next->next;
            }

            Node* second = slow->next;

            slow->next = nullptr;
            if (second)
                second->prev = nullptr;

            return second;
        }

        template<typename Compare>
        static Node* _merge(Node* a, Node* b, Compare comp) {

            if (!a)
                return b;
            if (!b)
                return a;

            Node* head = nullptr;
            Node* tail = nullptr;

            auto attach = [&](Node* node) {
                Node* next = node->next;

                node->prev = tail;
                node->next = nullptr;

                if (!head) {
                    head = tail = node;
                } else {
                    tail->next = node;
                    tail       = node;
                }

                return next;
            };

            while (a && b) {
                if (comp(a->data, b->data))
                    a = attach(a);
                else
                    b = attach(b);
            }

            while (a)
                a = attach(a);

            while (b)
                b = attach(b);

            return head;
        }
};