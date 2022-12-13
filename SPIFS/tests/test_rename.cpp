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

TestRename::TestRename(const string test_name) : BaseTest(test_name)
{
	bool result;
	fs->format();
	result = fs->rename("FirstFile", "SecondFile");
	if (result) {
		fail_out << "Renaming non-existent file should not return true.";
		goto done;
	}
	result = fs->create("FirstFile");
	if (!result) {
		fail_out << "Create failed in TestRename.";
		goto done;
	}
	result = fs->rename("FirstFile", "ThirdFile");
	if (!result) {
		fail_out << "Rename of \"FirstFile\" to \"ThirdFile\" failed.";
		goto done;
	}

	result = fs->rm("FirstFile");
	if (result) {
		fail_out << "Removing renamed file should not succeed.";	
		goto done;
	}

	result = fs->rm("ThirdFile");
	if (!result) {
		fail_out << "Removing new filename should work after renaming.";
		goto done;
	}

	done:;
}
