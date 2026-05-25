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

        ~DynamicArray() {

            _destroyAll();
            ::operator delete(_data);
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