// "$Id: Test.h 8500 2011-03-03 09:20:46Z bgbnbigben $"
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

#ifndef fltk_Test_h
#define fltk_Test_h

#include "FL_API.h"

#include <iostream>
#include <string>
#include <vector>

namespace fltk
{

struct Tests
{
	std::string name;
	typedef std::string(*TestFunc)();
	std::vector<std::pair<std::string, TestFunc> > functions;

	Tests(std::string iname) : name(std::move(iname)) { }

	void
	add
		( TestFunc const & func
		, std::string name
		)
	{
		functions.push_back(std::make_pair(std::move(name), func));
	}

	int
	run
		()
	{
		int badcnt=0;
		for (auto itf = functions.cbegin() ; functions.cend() != itf ; ++itf)
		{
			std::string const & name = itf->first;
			TestFunc const & func = itf->second;
			std::string const res = func();
			if (! res.empty())
			{
				++badcnt;
				std::cerr << "Errors found in: " << name << '\n'
					<< res
					<< std::endl;
			}

		}
		return badcnt;
	}
};

}

#endif
