
// "$Id: Bound.h 8500 2011-03-03 09:20:46Z bgbnbigben $"
//
// Copyright 1998-2006 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//    http://www.fltk.org/str.php

#ifndef fltk_Bound_h
#define fltk_Bound_h

#include "FL_API.h"

#include <array>

namespace fltk {

template <typename Type>
struct FL_API Bound {
	std::array<Type, 2> begend{Type(0), Type(0)};

	/*
	operator std::array<Type, 2> const &() const
	{
		return begend;
	}
	*/

	// value constuctor
	Bound(Type const beg, Type const end)
		: begend{beg, end}
	{}

	// size constructor
	Bound(Type const size=0)
		: begend{0, size}
	{}

	bool empty() const
	{ return begend[1] <= begend[0]; }

	Type size() const
	{ return begend[1] - begend[0]; }

	void translate(Type const delta)
	{ begend[0] += delta; begend[1] += delta; }

	Bound translated(Type const delta) const
	{
		Bound bound(*this);
		bound.translate(delta);
		return bound;
	}

	Type center() const
	{ return begend[0] + (size() / Type(2)); }

	void recenter(Type const newcenter)
	{
		translate(newcenter - center());
	}

	Bound recentered(Type const newcenter) const
	{
		Bound bound(*this);
		bound.recenter(newcenter);
		return bound;
	}

	void scaleFromCenter(Type const mult)
	{
		*this = scaledFromCenter(mult);
	}

	Bound scaledFromCenter(Type const mult) const
	{
		return Bound(0, size() * mult).recenter(center());
	}

	bool intersects(Bound const & rhs) const
	{
		return begend[0] < rhs.begend[1] && rhs.begend[0] < begend[1];
	}

	void intersectWith(Bound const & rhs)
	{
		begend[0] = std::max(begend[0], rhs.begend[0]);
		begend[1] = std::min(begend[1], rhs.begend[1]);
	}

	Bound intersectedWith(Bound const & rhs) const
	{
		return Bound
			( std::max(begend[0], rhs.begend[0])
			, std::min(begend[1], rhs.begend[1]) );
	}

	void uniteWith(Bound const & rhs)
	{
		begend[0] = std::min(begend[0], rhs.begend[0]);
		begend[1] = std::max(begend[1], rhs.begend[1]);
	}

	Bound unitedWith(Bound const & rhs) const
	{
		return Bound
			( std::min(begend[0], rhs.begend[0])
			, std::max(begend[1], rhs.begend[1]) );
	}

	// half open check
	bool contains(Type const val) const
	{
		return begend[0] <= val && val < begend[1];
	}

	// fully closed check
	bool containsClosed(Type const val) const
	{
		return begend[0] <= val && val <= begend[1];
	}

	bool operator==(Bound const & rhs) const
	{
		return rhs.begend == begend;
	}

	bool operator!=(Bound const & rhs) const
	{
		return rhs.begend != begend;
	}

};

}

#endif
