/**
    Copyright 2015-2020 Red Anchor Trading Co. Ltd.

    Distributed under the Boost Software License, Version 1.0.
    See <http://www.boost.org/LICENSE_1_0.txt>
 */


#pragma once

#include <memory>


namespace f5 {


    inline namespace threading {


        /// Policy which returns the values held in the container
        template<typename V>
        struct container_by_value_policy {
            using found_type = V;
            using reference_type = std::add_lvalue_reference_t<found_type>;
            using value_return_type = V;

            static found_type found_from_V(const V &v) { return v; }
            static value_return_type value_from_V(V &v) { return v; }
            static reference_type reference_from_V(V &v) { return v; }
        };

        /// Policy dereferences the pointer when appropriate
        template<typename V>
        struct pointer_dereference_policy {
            using found_type = decltype(&*std::declval<V>());
            using reference_type = std::add_lvalue_reference_t<V>;
            using value_return_type = decltype(*std::declval<V>()) &;

            static found_type found_from_V(V const &v) { return &*v; }
            static value_return_type value_from_V(V &v) { return *v; }
            static reference_type reference_from_V(V &v) { return v; }
        };

        /// Policy that promotes held weak_ptr instances to their shared_ptr
        /// counterpart.
        template<typename V>
        struct weak_ptr_promotion_policy {
            using found_type = decltype(std::declval<V>().lock());
            using reference_type = std::add_lvalue_reference_t<found_type>;
            using value_return_type = decltype(std::declval<V>().lock());

            static found_type found_from_V(V v) { return v.lock(); }
            static value_return_type value_from_V(V v) { return v.lock(); }
            static reference_type reference_from_V(V v) { return v.lock(); }
        };

        /// Use the values by default in the container interface
        template<typename V>
        struct container_default_policy {
            using type = container_by_value_policy<V>;
        };
        /// Dereference std::unique_ptr by default
        template<typename V>
        struct container_default_policy<std::unique_ptr<V>> {
            using type = pointer_dereference_policy<std::unique_ptr<V>>;
        };
        /// Promote weak_ptr by default
        template<typename V>
        struct container_default_policy<std::weak_ptr<V>> {
            using type = weak_ptr_promotion_policy<std::weak_ptr<V>>;
        };


    }


}
