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

TestFormat::TestFormat(const string test_name) : BaseTest(test_name)
{
	unsigned int num_files = m_disk_size/1048;
	fs->format();
	for (unsigned int i=0; i < num_files; ++i) {
		for (unsigned int j=0; j < 15; ++j) {
			unsigned int byte = i*24 + j;
			if (fs->m_disk[byte] != '*') {
				fail_out << "Byte " << byte << " is not a * character." << endl;
				return;
			}
		}
	}
}
