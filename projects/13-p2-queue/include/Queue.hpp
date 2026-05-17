#pragma once

#include "doubly_linked_list.hpp"

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T, typename Container = DoublyLinkedList<T>>
class Queue {

    public:

        using value_type      = typename Container::value_type;
        using size_type       = typename Container::size_type;
        using reference       = typename Container::reference;
        using const_reference = typename Container::const_reference;
        using container_type  = Container;

        static_assert(std::is_same_v<typename Container::value_type, T>,
                      "Container value_type must match Queue value_type");

        Queue() = default;

        Queue(const Queue&)     = default;
        Queue(Queue&&) noexcept = default;

        Queue& operator=(const Queue&)     = default;
        Queue& operator=(Queue&&) noexcept = default;

        ~Queue() = default;

        explicit Queue(const Container& container) : _container(container) {}

        explicit Queue(Container&& container) : _container(std::move(container)) {}

        bool empty() const noexcept {

            return _container.empty();
        }

        size_type size() const noexcept {

            return _container.size();
        }

        const_reference front() const {

            if (empty())
                throw std::runtime_error("Queue is empty");

            return _container.front();
        }

        void enqueue(const T& value) {

            _container.push_back(value);
        }

        void enqueue(T&& value) {

            _container.push_back(std::move(value));
        }

        void dequeue() {

            if (empty())
                throw std::runtime_error("Queue is empty");

            _container.pop_front();
        }

        void swap(Queue& other) noexcept {

            std::swap(_container, other._container);
        }

    protected:

        Container _container;
};