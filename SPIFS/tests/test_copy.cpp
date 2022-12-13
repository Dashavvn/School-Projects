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

TestCopy::TestCopy(const string test_name) : BaseTest(test_name)
{
	bool result;
	fs->format();
	result = fs->copy("FirstFile", "SecondFile");
	if (result) {
		fail_out << "Should not be able to copy a file that doesn't exist.";
		goto done;
	}
	result = fs->create("FirstFile");
	if (!result) {
		fail_out << "Create failed in TestCopy";
		goto done;	
	}
	result = fs->copy("FirstFile", "SecondFile");
	if (!result) {
		fail_out << "Copying FirstFile to SecondFile should succeed.";
		goto done;
	}
	result = fs->rm("FirstFile");
	if (!result) {
		fail_out << "Deleting original failed in TestCopy.";
		goto done;
	}
	result = fs->rm("SecondFile");
	if (!result) {
		fail_out << "Deleting copy failed in TestCopy.";
		goto done;
	}

	done:;
}
