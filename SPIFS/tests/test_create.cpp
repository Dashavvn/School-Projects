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

#include <cstring>

using namespace std;

TestCreate::TestCreate(string test_name) : BaseTest(test_name)
{

	bool result = false;
	int pos, size;
	int *pos_ptr, *size_ptr;
	int dir_size;

	//Format the disk
	fs->format();

	//Create a file
	result = fs->create("FirstFile");

	if (!result) {
		fail_out << "Adding first file returned false.";
		goto done;
	}

	//Make sure the name is correctly stored in the directory.
	char name[16];
	strncpy(name, fs->m_disk, 16);
	if (strncmp(name, "FirstFile", 16) != 0) {
		fail_out << "Name \"" << name << "\" not correct.  Should be: \"FirstFile\"."; 
		goto done;
	}

	dir_size = (fs->m_disk_size / 1048) * 24;

	//Make sure it has position dir_size and size 0.
	pos_ptr = (int *)&fs->m_disk[16];
	pos = *pos_ptr;
	if (pos != dir_size) {
 		fail_out << "Position of FirstFile is " << pos << ", not " << dir_size <<".";
		goto done;
	}  
	
	//Make sure it has size 0 (initially).
	size_ptr = (int *)&fs->m_disk[20];
	size = *size_ptr;
	if (size != 0) {
		fail_out << "Size is " << size << ", not 0.";
		goto done;
	}

	//Create a second file with a different name.
	result = fs->create("SecondFile");
	if (!result) {
		fail_out << "Could not create second file.";
		goto done;
	}

	//Check that the first file is still in the directory.	
	strncpy(name, fs->m_disk, 16);
	if (strncmp(name, "FirstFile", 16) != 0) {
		fail_out << "Filename \"" << name << "\" not correct.  Should be \"FirstFile\".";
		goto done;
	}

	//Check that the second file has been successfully added to the directory.
	strncpy(name, &fs->m_disk[24], 16);
	if (strncmp(name, "SecondFile", 16) != 0) {
		fail_out << "Filename \"" << name << "\" not correct.  Should be \"SecondFile\"";
		goto done;
	}

	result = fs->create("FirstFile");
	if (result){
		fail_out << "Creating file with same name as first file did not return false.";
	}	

	done: ;
}
