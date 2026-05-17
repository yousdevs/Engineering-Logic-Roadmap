#pragma once

#include "doubly_linked_list.hpp"

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T, typename Container = DoublyLinkedList<T>>
class Queue {

    public:

        using value_type      = T;
        using size_type       = std::size_t;
        using reference       = T&;
        using const_reference = const T&;
        using container_type  = Container;

        Queue() = default;

        ~Queue() = default;

        explicit Queue(const Container& container) : _container(container) {}

        explicit Queue(Container&& container) : _container(std::move(container)) {}

        bool empty() const noexcept {

            return _container.empty();
        }

        size_type size() const noexcept {

            return _container.size();
        }

    protected:

        Container _container;
};