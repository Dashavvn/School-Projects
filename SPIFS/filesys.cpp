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
#include "filesys.h"
#include <sys/stat.h>
#include <fstream>
#include <iostream>

using namespace std;

Filesystem::Filesystem(string name, const unsigned int size=4194304) : m_disk_filename(name) {

	//Check whether the file already exists in Linux
	struct stat file_info;
	int exists = stat(m_disk_filename.c_str(), &file_info);

	//If not, create a file.
	if (exists < 0) {
		//Allocate size (by default 4Mb) bytes of space 
		m_disk_size = size;
		m_disk = new char[m_disk_size];

		//Write 0's to the file.
		ofstream disk_stream(m_disk_filename.c_str());
		for (int i=0;i<m_disk_size;++i){
			disk_stream.put((char)0);
			m_disk[i] = (char)0;
		}	

		//All done.  Close the file.
		disk_stream.close();
	}
	else {
		//Open the file.
		ifstream disk_stream(m_disk_filename.c_str());

		//Set m_disk_size to be the file's size.
		m_disk_size = file_info.st_size;

		//Allocate space
		m_disk = new char[m_disk_size];

		//Read in the data
		for (int i=0; i<m_disk_size; ++i) {
			m_disk[i] = disk_stream.get();
		}
		//All done.  Close the file.
		disk_stream.close();
	}
	m_dir = (struct dEntry*) m_disk; 
}

Filesystem::~Filesystem()
{
		//Before deleting, save the array to disk.
		ofstream disk_stream(m_disk_filename.c_str());
		for (int i=0; i<m_disk_size; ++i) {
			disk_stream << m_disk[i];
		}
		disk_stream.close();

		//Then deallocate.
		delete[] m_disk;
}

bool Filesystem::write_string(int pos, string str, int size)
{
	//Size is a maximum value.  If the string is smaller, adjust the size.
	if (size > str.length())
		size = str.length();

	//Accomodate the NULL character.
	size = size + 1; 


	if (size <=0 )
		return false;

	//Check to see if writing would go past the end of the array.
	if (pos > m_disk_size || size > m_disk_size || (pos + size) > m_disk_size)
		return false;

	//Write the bytes into the array
	for (int i=pos; i<pos+size-1; ++i)
	{
		m_disk[i] = str.at(i-pos);
	}

	//Append a NULL character
	m_disk[pos+size-1] = 0;

	return true;
}

bool Filesystem::read_string(const int pos, string &str, const int size) const
{

	if (size <= 0)
		return false;

	if (pos > m_disk_size || size > m_disk_size || (pos + size) > m_disk_size)
		return false;

	str = "";
	for (int i=pos; i<pos+size; ++i)
	{
		str += m_disk[i];
	}
	return true;
}

bool Filesystem::write_int(const int pos, const int val)
{
	if (pos+4 > m_disk_size)
		return false;

	char* val_as_char = (char *)&val;
	for (int i=0; i<4; ++i)
	{	
		m_disk[pos+i] = val_as_char[i];
	}
	return true;
}

bool Filesystem::read_int(const int pos, int &val) const
{
	val = 0;
	if (pos+4 > m_disk_size)
		return false;

	char* val_as_char = (char *)&val;
	for (int i=0; i<4; ++i)
	{	
		val_as_char[i] = m_disk[pos+i];
	}
	return true;
}
