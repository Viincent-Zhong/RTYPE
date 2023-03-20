/*
** EPITECH PROJECT, 2022
** bs
** File description:
** Registry
*/

#pragma once

#include <unordered_map>
#include <typeindex>
#include <functional>
#include <utility>
#include <queue>
#include <list>
#include <mutex>
#include "Sparse.hpp"
#include "TextureCache.hpp"
#include "TextCache.hpp"
#include "EntityCache.hpp"

/** This class represent an array of array of components X with functions to manage it
 */
class Registry {
    public :
        template <class Component>
        SparseArray<Component> &registerComponent()
        {
            if(_componentsArrays.find(typeid(Component)) == _componentsArrays.end()) {
                std::lock_guard<std::mutex> lock(_mutex);
                SparseArray<Component> comp;
                _componentsArrays[std::type_index(typeid(Component))] = comp;

                _eraseComponents[std::type_index(typeid(Component))] = [](Registry &r, std::size_t const &e) {
                    auto comp = r._componentsArrays.find(typeid(Component));
                    if (comp == r._componentsArrays.end())
                        return;
                    std::any_cast<SparseArray<Component>&>(comp->second).erase(e);
                };

                _printComponents[std::type_index(typeid(Component))] = [](Registry &r) {
                    auto comp = r._componentsArrays.find(typeid(Component));
                    if (comp == r._componentsArrays.end())
                        return;
                };
            }
            return std::any_cast<SparseArray<Component>&>(_componentsArrays.find(typeid(Component))->second);
        }

        template <class Component>
        /** Return the array of the given components */
        SparseArray <Component> &getComponents()
        {
            std::lock_guard<std::mutex> lock(_mutex);
            return std::any_cast<SparseArray<Component>&>(_componentsArrays.find(typeid(Component))->second);
        }

        /** Return the array of the given components */
        template <class Component>
        SparseArray <Component> const &getComponents() const
        {
            std::lock_guard<std::mutex> lock(_mutex);
            return std::any_cast<SparseArray<Component>&>(_componentsArrays.find(typeid(Component))->second);
        }

        /** Give an available id */
        std::size_t const &spawnEntity()
        {
            std::lock_guard<std::mutex> lock(_mutex);
            if (_availableId.size() != 0) {
                std::size_t &id = _availableId.front();

                if (id) {
                    _availableId.pop();
                    return id;
                }
            }

            for (auto except = std::find(_exceptionId.begin(), _exceptionId.end(), _index);
            except != _exceptionId.end();) {
                _index++;
                except = std::find(except, _exceptionId.end(), _index);
            }
            _index++;
            return _index;
        }

        std::size_t entityFromIndex(std::size_t idx)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            std::size_t id(idx);

            _exceptionId.push_front(idx);
            killEntity(id);
            _exceptionId.push_front(idx);
            return id;
        }

        /** Remove a whole entity (all its components)
         */
        void killEntity(std::size_t const &e)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            std::size_t id = e;

            // This loop cause a crash on Mac <--
            for (auto it : _eraseComponents) {
                it.second(*this, e);
            }
            // This loop cause a crash on Mac -->

            auto except = std::find(_exceptionId.begin(), _exceptionId.end(), id);
            if (except != _exceptionId.end())
                _exceptionId.erase(except);
            else
                _availableId.push(id);
        }

        /** Insert by move a given component, in the array at a given index */
        template <typename Component>
        typename SparseArray<Component>::reference_type addComponent(std::size_t const &to, Component &&c)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            auto comp = _componentsArrays.find(typeid(Component));
            return std::any_cast<SparseArray<Component>&>(comp->second).insertAt(to, std::forward<Component>(c));
        }

        /** Insert by copy a given component, in the array at a given index */
        template <typename Component>
        typename SparseArray<Component>::reference_type addComponent(std::size_t const &to, Component const &c)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            auto comp = _componentsArrays.find(typeid(Component));
            return std::any_cast<SparseArray<Component>&>(comp->second).insertAt(to, c);
        }

        /** Insert by constructing in place a given component with given parameters, in the array at a given index
         * 
         * Params p : parameter with which your component will be constructed with
        */
        template <typename Component, typename ... Params>
        typename SparseArray<Component>::reference_type emplaceComponent(std::size_t const &to, Params &&...p)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            auto comp = _componentsArrays.find(typeid(Component));
            return std::any_cast<SparseArray<Component>&>(comp->second).emplaceAt(to, std::forward<Params>(p)...);
        }

        template <typename Component>
        void removeComponent(std::size_t const &from)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            auto comp = _componentsArrays.find(typeid(Component));
            std::any_cast<SparseArray<Component>&>(comp->second).erase(from);
        }
        Engine::TextureCache textureCache;
        Engine::TextCache textCache;
        EngineEntity::EntityCache entityCache;
    private:
        mutable std::mutex _mutex;
        std::unordered_map<std::type_index, std::any> _componentsArrays;
        std::unordered_map<std::type_index, std::function<void(Registry &, std::size_t const &)>> _eraseComponents;
        std::unordered_map<std::type_index, std::function<void(Registry &)>> _printComponents;
        std::queue<std::size_t> _availableId;
        std::list<std::size_t> _exceptionId;
        std::size_t _index = 0;
};
