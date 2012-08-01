#ifndef VISITOR_VISITABLE_CLASSES_HPP
#define VISITOR_VISITABLE_CLASSES_HPP

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

namespace visitor {

    template<class base_visitable>
    struct visitable_classes;
} // NS visitor

#   define VISITOR_CREATE_VISITABLE_CLASSES_TRAIT(basevisitable,visitableclasses)   \
namespace visitor {                                                                 \
    template<>                                                                      \
    struct visitable_classes<basevisitable>                                         \
        : visitableclasses                                                          \
    {};                                                                             \
}

#endif
