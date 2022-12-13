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

TestDelete::TestDelete(const string test_name) : BaseTest(test_name)
{
	bool result = false;
	fs->format();
	result = fs->rm("FirstFile");
	if (result) {
		fail_out << "Deleting non-existent file should fail.";
		goto done;
	}
	result = fs->create("SecondFile");
	if (!result) {
		fail_out << "CREATE failed in TestDelete.";
		goto done;
	}
	result = fs->rm("SecondFile");
	if (!result) {
		fail_out << "Deleting a file you just created should not fail.";
		goto done;
	}

	result = fs->rm("SecondFile");
	if (result) {
		fail_out << "Deleting a file you just deleted should fail.";
		goto done;
	}

	done:;
}
