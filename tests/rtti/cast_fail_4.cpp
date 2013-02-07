// Copyright (c) 2013 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "rtti/cast.hpp"

#include "../basic_polymorphic.hpp"


extern Base * B;

void do_it() {
	visitor::rtti::cast<Derived_A&>(B);
}



