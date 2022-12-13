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
#include "base_test.h"

#include <iostream>
#include <string>

using namespace std;

TestClose::TestClose(const string test_name) : BaseTest(test_name)
{
	bool result = false;
	int fd;

	fs->format();
	result = fs->create("HelloWorld");
	if (!result) {
		fail_out << "Could not create file in TestClose.";
		goto done;
	}
		
	fd = fs->open("HelloWorld");
	if (fd <0) {
		fail_out << "Invalid file descriptor returned by open in TestClose.";
		goto done;
	}
	result = fs->close(fd);
	if (!result) {
		fail_out << "Close failed.";
		goto done;
	}

	result = fs->close(fd);
	if (result) {
		fail_out << "Closing an already closed file should fail.";
		goto done;
	}

	done: ;
}
