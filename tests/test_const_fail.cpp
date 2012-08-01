// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "gof_classes.hpp"

struct failvisitor {
    void operator()(Base&) {}
};

int main() {
    Derived_A a;
    Base const& b=a;
    
    failvisitor v;
    accept(b,v); 
}
