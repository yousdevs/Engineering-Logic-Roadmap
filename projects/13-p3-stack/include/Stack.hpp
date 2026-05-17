#pragma once

#include "doubly_linked_list.hpp"

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T, typename Container = DoublyLinkedList<T>>
class Stack {

    public:

        using value_type      = typename Container::value_type;
        using reference       = typename Container::reference;
        using const_reference = typename Container::const_reference;
        using size_type       = typename Container::size_type;
        using container_type  = Container;

        static_assert(std::is_same_v<typename Container::value_type, T>,
                      "Container value_type must match stack value_type");

        Stack() = default;

        Stack(const Stack&) = default;

        Stack(Stack&&) noexcept = default;

        Stack& operator=(const Stack&)     = default;
        Stack& operator=(Stack&&) noexcept = default;

        ~Stack() = default;

        bool empty() const noexcept {

            return _container.empty();
        }

        size_type size() const noexcept {

            return _container.size();
        }

        // throws if empty
        const_reference top() const {

            if (empty())
                throw std::runtime_error("Stack is empty");

            return _container.back();
        }

        void push(const T& value) {

            _container.push_back(value);
        }

        void push(T&& value) {

            _container.push_back(std::move(value));
        }

        void pop() {

            if (empty())
                throw std::runtime_error("Stack is empty");

            _container.pop_back();
        }

    protected:

        Container _container;
};