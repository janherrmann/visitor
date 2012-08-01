#ifndef VISITOR_DISPATCH
#define VISITOR_DISPATCH

// Copyright (c) 2012 Jan Herrmann
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace visitor {

	/*  
	
	* here will be a function of the form:
	
	template<class Sig,class StaticVisitor>
	res dispatch(StaticVisitor);
	
	* res will be a function object with an operator() with signatur sig
	* it will take all arguments pack them into members of a (internaly created)
	* static visitor and will repeatedly call accept on all visitable arguments 
	* to recover their type information an store references to them.
	* At the end it will call operator() form StaticVisitor with the references
	* the compiler has to choose the right overload (or compilation will fail).
	* The result is transported back.
	* static visitor is not responsible to transport arguments and result
	* (it is accepted by value in contrast to accept where it is accepted 
	* by reference)
	* It should be usable this way:
	
	T1 myfun(T2 const& t2, T3& aT3) {
		StaticVisitor sv;
		return dispatch<T1(T2 const&,T3&)>(sv)(aT2, aT3);
	}
	
	T1 result1 = myfun(aT2, aT3);
	
	* or:
	
	StaticVisitor sv;
	T1 result2 = dispatch<T1(T2 const&,T3&)>(sv)(aT2, aT3);

	* or:
	
	T1 result3 = dispatch<T1(T2 const&,T3&)>(StaticVisitor())(aT2, aT3);
	
	* or:
	
	auto fun = bind(dispatch<T1(T2 const&,T3&)>(StaticVisitor())(_2,_1));
	T1 result4 ) fun(aT3, aT2);
	
	
	* all types implementing non-member accept will work
	
	* look at accept_n.hpp for a proof of concept that multimethods
	* can be implemented this way
	
	*/

} // NS visitor
#endif
