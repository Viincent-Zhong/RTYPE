/*
** EPITECH PROJECT, 2022
** bs
** File description:
** Sparse
*/

#pragma once

#include <vector>
#include <memory>
#include <optional>
#include <type_traits>
#include <iostream>
#include <algorithm>
#include <any>

template <typename Component>
/** This class represent an array of a Component X with functions to manage it
 *  Example: SparseArray<int>
*/
class SparseArray {
    public:
        using value_type = std::optional<Component>; // optional component type
        using reference_type = value_type &;
        using const_reference_type = value_type const &;
        template <typename Type>
        using allocator = std::allocator_traits<Type>;
        using container_t = std::vector<value_type>; // optionally add your allocator template here .
        using size_type = typename container_t::size_type;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;
    public:
        SparseArray() {}; // You can add more constructors .
        SparseArray(SparseArray const &) {}; // copy constructor
        SparseArray(SparseArray &&) noexcept {}; // move constructor
        ~SparseArray() {}
        SparseArray & operator=(SparseArray const &) // copy assignment operator
        {
            return *this;
        }

        SparseArray & operator=(SparseArray &&) noexcept // move assignment operator
        {
            return *this;
        }
        reference_type operator[](size_t idx)
        {
            return _data[idx];
        }
        const_reference_type operator[](size_t idx) const
        {
            return _data[idx];
        }
        iterator begin()
        {
            return _data.begin();
        }
        const_iterator begin() const
        {
            return _data.begin();
        }
        const_iterator cbegin() const
        {
            return _data.cbegin();
        }
        iterator end()
        {
            return _data.end();
        }
        const_iterator end() const
        {
            return _data.end();
        }
        const_iterator cend() const
        {
            return _data.cend();
        }
        size_type size() const
        {
            return _data.size();
        }

        /** Insert by copy a given component, in the array at a given index */
        reference_type insertAt(size_type pos, Component const &comp)
        {
            if (pos >= _data.size())
                _data.resize(pos + 1);
            auto &value = _data.at(pos);
            if (_data.size() != 0) {
                _data.get_allocator().destroy(&(value));
                value = {};
            }
            value = comp;
            return value;
        }
        /** Insert by move a given component, in the array at a given index */
        reference_type insertAt(size_type pos, Component &&comp)
        {
            if (pos >= _data.size())
                _data.resize(pos + 1);
            auto &value = _data.at(pos);
            if (_data.size() != 0) {
                _data.get_allocator().destroy(&(value));
                value = {};
            }
            value = std::move(comp);
            return value;
        }

        /** Insert by constructing in place a given component with given parameters, in the array at a given index
         * Params : parameter with which your component will be constructed with
        */
        template <class ... Params>
        reference_type emplaceAt(size_type pos, Params &&...params)
        {
            if (pos >= _data.size())
                _data.resize(pos + 1);
            auto &value = _data.at(pos);
            if (value) {
                _data.get_allocator().destroy(&(value));
            }
            _data.get_allocator().construct(&(value), Component(params...));
            return value;
        }

        /**
         * @brief 
         * Erase all the data
         * 
         * @param pos 
         */
        void erase(size_type pos)
        {
            auto size = _data.size();
            if (size != 0 && pos < size) {
                auto &value = _data.at(pos);
                _data.get_allocator().destroy(&(value));
                value = {};
            }
        }

        /**
         * @brief 
         * Get the Index of an object
         * 
         * @param value 
         * @return size_type 
         */
        size_type getIndex(value_type const &value) const // a faire
        {
            if (!value)
                return 0;
            for (int i = 0; i != _data.size(); ++i) {
                if (std::addressof(_data.at(i)) == std::addressof(value))
                    return i;
            }
            return 0;
        }
    private:
        container_t _data;
};
