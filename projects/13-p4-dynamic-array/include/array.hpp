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
            _size = 0;
        }

        pointer   _data     = nullptr;
        size_type _size     = 0;
        size_type _capacity = 0;
};