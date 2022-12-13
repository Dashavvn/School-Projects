/*
 *  Copyright 2012-2016 Robert Marmorstein
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef TEST_H
#define TEST_H

#include "../filesys.h"

#include <sstream>

class BaseTest {
	protected:

	std::string m_test_name;
	std::ostringstream fail_out;
	
	Filesystem* fs;

	unsigned int m_disk_size;

	public:

	BaseTest(const std::string test_name, unsigned int disk_size=4194304);
	~BaseTest();
};

class TestFormat : public BaseTest {
	public:
	TestFormat(const std::string test_name);
};

class TestCreate: public BaseTest {
	public:
	TestCreate(const std::string test_name);
};

class TestList: public BaseTest {
	public:
	TestList(const std::string test_name);
};

class TestSimpleList: public BaseTest {
	public:
	TestSimpleList(const std::string test_name);
};

class TestDelete: public BaseTest {
	public:
	TestDelete(const std::string test_name);
};

class TestRename: public BaseTest {
	public:
	TestRename(const std::string test_name);
};

class TestCopy: public BaseTest {
	public:
	TestCopy(const std::string test_name);
};

class TestOpen: public BaseTest {
	public:
	TestOpen(const std::string test_name);
};

class TestClose: public BaseTest {
	public:
	TestClose(const std::string test_name);
};

class TestWrite: public BaseTest {
	public:
	TestWrite(const std::string test_name);
};

class TestRead: public BaseTest {
	public:
	TestRead(const std::string test_name);
};

#endif //TEST_H
