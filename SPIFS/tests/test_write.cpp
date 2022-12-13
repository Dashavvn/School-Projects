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

TestWrite::TestWrite(const string test_name) : BaseTest(test_name)
{
	bool result = false;
	int fd = 0;
	string str = "This is a simple string.";
	string new_str;
	int pos;
	int size;

	fs->format();
	result = fs->create("MyFile");
	if (!result) {
		fail_out << "Create failed in TestWrite.";
		goto done;
	}
	fd = fs->open("MyFile");
	if (!result) {
		fail_out << "Open failed in TestWrite.";
		goto done;
	}

	result = fs->write(fd, str, str.length());
	if (!result) {
		fail_out << "Writing \"This is a simple string.\" to file descriptor " << fd << "failed.";
		goto done;
	}
	//Check that it's really written.
	pos =  * ((int *) &fs->m_disk[16]);			//First lookup the position of the block in the directory.
	fs->read_string(pos, new_str, str.length());	//Then read in the string.

	if (new_str != str) {
		fail_out << "Written string \"" << new_str << "\" does not match \"" << str << "\".";
		goto done;
	}

	//Check that size was updated.
	size =  * ((int *) &fs->m_disk[20]);			//First lookup the size of the block in the directory.
	if (size != 24) {
		fail_out << "Size of string is " << size << " not 24.";
		goto done;
	}		

	//Does writing pick up from where it left off?
	result = fs->write(fd, str, str.length());
	if (!result) {
		fail_out << "Writing a second \"This is a simple string.\" to file descriptor " << fd << "failed.";
		goto done;
	}

	//Check that it's really written.
	fs->read_string(pos+size, new_str, str.length());	//Then read in the string.

	if (new_str != str) {
		fail_out << "Second written string \"" << new_str << "\" does not match \"" << str << "\".";
		goto done;
	}

	fs->close(fd);

	done:;
}
