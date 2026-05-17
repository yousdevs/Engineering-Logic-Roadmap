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

        ~Stack() = default;

    protected:

        Container _container;
};