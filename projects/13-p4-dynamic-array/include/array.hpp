#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <new>
#include <stdexcept>
#include <type_traits>
#include <utility>

template<typename T>
class DynamicArray {

    public:

        using value_type      = T;
        using size_type       = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference       = T&;
        using const_reference = const T&;
        using pointer         = T*;
        using const_pointer   = const T*;

        DynamicArray() noexcept : _data(nullptr), _size(0), _capacity(0) {}

        explicit DynamicArray(size_type count) {

            _reallocate(count);

            for (size_type i = 0; i < count; ++i) {

                new (_data + i) T();
            }
            _size = count;
        }

        DynamicArray(size_type count, const_reference value) {

            _reallocate(count);

            for (size_type i = 0; i < count; ++i) {

                new (_data + i) T(value);
            }

            _size = count;
        }

        DynamicArray(std::initializer_list<value_type> init) {

            _reallocate(init.size());

            size_type i = 0;
            for (auto it = init.begin(); it != init.end(); ++it, ++i) {

                new (_data + i) T(*it);
            }
            _size = init.size();
        }

        ~DynamicArray() noexcept {

            _destroyAll();
            ::operator delete(_data);
        }

        DynamicArray(const DynamicArray& other) {

            _reallocate(other._size);

            for (size_type i = 0; i < other.size(); ++i) {

                new (_data + i) T(other._data[i]);
            }

            _size = other._size;
        }

        DynamicArray(DynamicArray&& other) noexcept {

            _data     = other._data;
            _size     = other._size;
            _capacity = other._capacity;

            other._data     = nullptr;
            other._size     = 0;
            other._capacity = 0;
        }

        DynamicArray& operator=(const DynamicArray& other) {

            DynamicArray temp(other);

            swap(temp);

            return *this;
        }

        DynamicArray& operator=(DynamicArray&& other) noexcept {

            if (this == &other)
                return *this;

            _destroyAll();

            ::operator delete(_data);

            _data     = other._data;
            _size     = other._size;
            _capacity = other._capacity;

            other._data     = nullptr;
            other._size     = 0;
            other._capacity = 0;

            return *this;
        }

        DynamicArray& operator=(std::initializer_list<T> init) {

            DynamicArray t(init);
            swap(t);
            return *this;
        }

        reference operator[](size_type index) noexcept {

            return _data[index];
        }

        const_reference operator[](size_type index) const noexcept {

            return _data[index];
        }

        reference at(size_type index) {

            if (index >= _size)
                throw std::out_of_range("index out of range");

            return _data[index];
        }

        const_reference at(size_type index) const {

            if (index >= _size)
                throw std::out_of_range("index out of range");

            return _data[index];
        }

        reference front() {

            if (empty())
                throw std::out_of_range("array is empty");

            return _data[0];
        }

        const_reference front() const {

            if (empty())
                throw std::runtime_error("array is empty");

            return _data[0];
        }

        reference back() {

            if (empty())
                throw std::runtime_error("array is empty");

            return _data[_size - 1];
        }

        const_reference back() const {

            if (empty())
                throw std::runtime_error("array is empty");

            return _data[_size - 1];
        }

        pointer data() noexcept {

            return _data;
        }

        const_pointer data() const noexcept {

            return _data;
        }

        class iterator {

            public:

                using iterator_category = std::random_access_iterator_tag;
                using value_type        = T;
                using difference_type   = std::ptrdiff_t;
                using pointer           = T*;
                using reference         = T&;

                iterator() noexcept : _ptr(nullptr) {}

                explicit iterator(pointer ptr) noexcept : _ptr(ptr) {}

                reference operator*() const noexcept {

                    return *_ptr;
                }

                pointer operator->() const noexcept {

                    return _ptr;
                }

                reference operator[](difference_type n) const noexcept {

                    return _ptr[n];
                }

                iterator& operator++() noexcept {

                    ++_ptr;
                    return *this;
                }

                iterator operator++(int) noexcept {

                    iterator temp(*this);
                    ++(*this);
                    return temp;
                }

                iterator& operator--() noexcept {

                    --_ptr;
                    return *this;
                }

                iterator operator--(int) noexcept {

                    iterator temp(*this);
                    --(*this);
                    return temp;
                }

                iterator& operator+=(difference_type n) noexcept {

                    _ptr += n;
                    return *this;
                }

                iterator& operator-=(difference_type n) noexcept {

                    _ptr -= n;
                    return *this;
                }

                iterator operator+(difference_type n) const noexcept {

                    return iterator(_ptr + n);
                }

                iterator operator-(difference_type n) const noexcept {

                    return iterator(_ptr - n);
                }

                difference_type operator-(const iterator& other) const noexcept {

                    return _ptr - other._ptr;
                }

                bool operator==(const iterator& other) const noexcept {

                    return _ptr == other._ptr;
                }

                bool operator!=(const iterator& other) const noexcept {

                    return _ptr != other._ptr;
                }

                bool operator<(const iterator& other) const noexcept {

                    return _ptr < other._ptr;
                }

                bool operator>(const iterator& other) const noexcept {

                    return _ptr > other._ptr;
                }

                bool operator<=(const iterator& other) const noexcept {

                    return _ptr <= other._ptr;
                }

                bool operator>=(const iterator& other) const noexcept {

                    return _ptr >= other._ptr;
                }

            private:

                pointer _ptr;
                friend class DynamicArray<T>;
                friend class const_iterator;
        };

        class const_iterator {

            public:

                using iterator_category = std::random_access_iterator_tag;
                using value_type        = T;
                using difference_type   = std::ptrdiff_t;
                using pointer           = const T*;
                using reference         = const T&;

                const_iterator() noexcept : _ptr(nullptr) {}

                explicit const_iterator(const_pointer ptr) noexcept : _ptr(ptr) {}

                const_iterator(const iterator& it) noexcept : _ptr(it._ptr) {}

                reference operator*() const noexcept {

                    return *_ptr;
                }

                pointer operator->() const noexcept {

                    return _ptr;
                }

                reference operator[](difference_type n) const noexcept {

                    return _ptr[n];
                }

                const_iterator& operator++() noexcept {

                    ++_ptr;
                    return *this;
                }

                const_iterator operator++(int) noexcept {

                    const_iterator temp(*this);
                    ++(*this);
                    return temp;
                }

                const_iterator& operator--() noexcept {

                    --_ptr;
                    return *this;
                }

                const_iterator operator--(int) noexcept {

                    const_iterator temp(*this);
                    --(*this);
                    return temp;
                }

                const_iterator& operator+=(difference_type n) noexcept {

                    _ptr += n;
                    return *this;
                }

                const_iterator& operator-=(difference_type n) noexcept {

                    _ptr -= n;
                    return *this;
                }

                const_iterator operator+(difference_type n) const noexcept {

                    return const_iterator(_ptr + n);
                }

                const_iterator operator-(difference_type n) const noexcept {

                    return const_iterator(_ptr - n);
                }

                difference_type operator-(const const_iterator& other) const noexcept {

                    return _ptr - other._ptr;
                }

                bool operator==(const const_iterator& other) const noexcept {

                    return _ptr == other._ptr;
                }
                bool operator!=(const const_iterator& other) const noexcept {

                    return _ptr != other._ptr;
                }

                bool operator<(const const_iterator& other) const noexcept {

                    return _ptr < other._ptr;
                }

                bool operator>(const const_iterator& other) const noexcept {

                    return _ptr > other._ptr;
                }
                bool operator<=(const const_iterator& other) const noexcept {

                    return _ptr <= other._ptr;
                }
                bool operator>=(const const_iterator& other) const noexcept {

                    return _ptr >= other._ptr;
                }

            private:

                const_pointer _ptr;
        };

        iterator begin() noexcept {

            return iterator(_data);
        }

        const_iterator begin() const noexcept {

            return const_iterator(_data);
        }

        const_iterator cbegin() const noexcept {

            return const_iterator(_data);
        }

        iterator end() noexcept {

            return iterator(_data + _size);
        }

        const_iterator end() const noexcept {

            return const_iterator(_data + _size);
        }

        const_iterator cend() const noexcept {

            return const_iterator(_data + _size);
        }

        void push_back(const T& value) {

            if (_size == _capacity) {
                size_t new_capacity = (_capacity == 0) ? 1 : _capacity * _GROWTH_FACTOR;

                _reallocate(new_capacity);
            }

            new (_data + _size) T(value);
            ++_size;
        }

        void push_back(T&& value) {

            if (_size == _capacity) {
                size_t new_capacity = (_capacity == 0) ? 1 : _capacity * _GROWTH_FACTOR;

                _reallocate(new_capacity);
            }

            new (_data + _size) T(std::move(value));
            ++_size;
        }

        template<typename... Args>
        reference emplace_back(Args&&... args) {

            if (_size == _capacity) {
                size_t new_capacity = (_capacity == 0) ? 1 : _capacity * _GROWTH_FACTOR;

                _reallocate(new_capacity);
            }

            T* place = _data + _size;

            ::new (place) T(std::forward<Args>(args)...);

            ++_size;

            return *place;
        }

        void pop_back() {

            _data[_size - 1].~T();
            --_size;
        }

        void reserve(size_type new_capacity) {

            if (new_capacity <= _capacity)
                return;

            _reallocate(new_capacity);
        }

        void shrink_to_fit() {

            if (_size == 0) {

                ::operator delete(_data);
                _data     = nullptr;
                _capacity = 0;
                return;
            }

            _reallocate(_size);
        }

        void resize(size_type new_size) {

            if (new_size < _size) {

                for (size_type i = new_size; i < _size; ++i) {

                    _data[i].~T();
                }

                _size = new_size;
                return;
            }

            if (new_size > _size) {

                if (_capacity < new_size)
                    reserve(new_size);

                for (size_type i = _size; i < new_size; ++i) {

                    new (_data + i) T();
                }

                _size = new_size;
            }
        }

        void resize(size_type new_size, const T& value) {

            if (new_size < _size) {

                for (size_type i = new_size; i < _size; ++i) {

                    _data[i].~T();
                }

                _size = new_size;
                return;
            }

            if (new_size > _size) {

                if (_capacity < new_size)
                    reserve(new_size);

                for (size_type i = _size; i < new_size; ++i) {

                    new (_data + i) T(value);
                }

                _size = new_size;
            }
        }

        iterator insert(const_iterator pos, const T& value) {

            size_type index = pos - cbegin();

            if (_size == _capacity) {
                size_type new_capacity = (_capacity == 0) ? 1 : _capacity * _GROWTH_FACTOR;

                _reallocate(new_capacity);
            }

            iterator it_pos = begin() + index;

            new (_data + _size) T(std::move(_data[_size - 1]));

            for (size_type i = _size - 1; i > index; --i)
                _data[i] = std::move(_data[i - 1]);

            new (_data + index) T(value);

            ++_size;

            return iterator(_data + index);
        }

        iterator insert(const_iterator pos, T&& value) {

            size_type index = pos - cbegin();

            if (_size == _capacity) {
                size_type new_capacity = (_capacity == 0) ? 1 : _capacity * _GROWTH_FACTOR;

                _reallocate(new_capacity);
            }

            iterator it_pos = begin() + index;

            // construct the last element into uninitialized memory
            new (_data + _size) T(std::move(_data[_size - 1]));

            for (size_type i = _size - 1; i > index; --i)
                _data[i] = std::move(_data[i - 1]);

            new (_data + index) T(std::move(value));

            ++_size;

            return iterator(_data + index);
        }

        iterator insert(const_iterator pos, size_type count, const T& value) {

            size_type index = pos - cbegin();
            if (count == 0)
                return begin() + index;

            if (_size + count > _capacity)
                _reallocate(std::max(_capacity * _GROWTH_FACTOR, _size + count));

            // shift right by count
            for (size_type i = _size; i > index; --i)
                new (_data + i + count - 1) T(std::move(_data[i - 1]));

            for (size_type i = 0; i < count; ++i)
                new (_data + index + i) T(value);

            _size += count;
            return iterator(_data + index);
        }

        template<typename... Args>
        iterator emplace(const_iterator pos, Args&&... args) {

            size_type index = pos - cbegin();

            if (_size == _capacity) {
                size_type new_capacity = (_capacity == 0) ? 1 : _capacity * _GROWTH_FACTOR;
                _reallocate(new_capacity);
            }

            iterator it_pos = begin() + index;
            for (iterator it = end(); it != it_pos; --it)
                *it = std::move(*(it - 1));

            ::new (_data + index) T(std::forward<Args>(args)...);
            ++_size;

            return iterator(_data + index);
        }

        iterator erase(const_iterator first, const_iterator last) {

            if (first == last)
                return iterator(const_cast<T*>(_data) + (first - cbegin()));

            size_type start = first - cbegin();
            size_type end   = last - cbegin();
            size_type count = end - start;

            size_type new_size = _size - count;

            for (size_type i = start; i < new_size; ++i) {

                _data[i] = std::move(_data[i + count]);
            }

            for (size_type i = new_size; i < _size; ++i) {

                _data[i].~T();
            }

            _size = new_size;

            return iterator(_data + start);
        }

        iterator erase(const_iterator pos) {

            return erase(pos, pos + 1);
        }

        void clear() noexcept {

            _destroyAll();
            _size = 0;
        }

        void swap(DynamicArray& other) noexcept {

            std::swap(_data, other._data);
            std::swap(_size, other._size);
            std::swap(_capacity, other._capacity);
        }

        size_type size() const noexcept {

            return _size;
        }

        bool empty() const noexcept {

            return _size == 0;
        }

        size_type capacity() const noexcept {

            return _capacity;
        }

    private:

        void _destroyRange(pointer buffer, size_type count) noexcept {

            if constexpr (!std::is_trivially_destructible_v<T>) {

                for (size_type i = count; i > 0; --i) {

                    buffer[i - 1].~T();
                }
            }
        }

        void _reallocate(size_type new_capacity) {

            pointer   buffer = static_cast<pointer>(::operator new(new_capacity * sizeof(T)));
            size_type constructed_count = 0;

            try {

                for (size_type i = 0; i < _size; ++i) {

                    new (buffer + i) T(std::move_if_noexcept(_data[i]));
                    ++constructed_count;
                }
            } catch (...) {

                _destroyRange(buffer, constructed_count);
                ::operator delete(buffer);
                throw;
            }

            _destroyRange(_data, _size);
            ::operator delete(_data);

            _data     = buffer;
            _capacity = new_capacity;
        }

        void _destroyAll() noexcept {

            _destroyRange(_data, _size);
        }

        pointer                    _data          = nullptr;
        size_type                  _size          = 0;
        size_type                  _capacity      = 0;
        static constexpr size_type _GROWTH_FACTOR = 2;
};