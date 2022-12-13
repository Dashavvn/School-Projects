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
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
using namespace std;

/*
struct FileHandle {

  int pos;

  int size;

  int offset;

};
*/

struct dEntry
{
	char filename[16];	
	int pos;
	int size;

 };


class TestBase;

class Filesystem {
	protected:
	friend class TestBase;
	friend class TestFormat;
	friend class TestCreate;
	friend class TestRead;
	friend class TestWrite;

	/* The name of the Linux file which the filesystem is stored inside. */
	string m_disk_filename;
	dEntry* m_dir;

	/* The internal representation of the file system is an array of m_disk_size characters named m_disk. */
	char* m_disk;
	unsigned int m_disk_size;
	
	/* Writes size bytes from the string str into m_disk starting at position pos.  
	 * Returns true if successful, false if the write would go past the end of the array. */
	bool write_string(const int pos, const string str, const int size);

	/* Reads size bytes from m_disk into the string str, starting at position pos.  
         * Returns true if successful, false if pos+size would cause reading past the end of the array. 
         * If not successful, sets str to the empty string. */
	bool read_string(const int pos, string& str, const int size) const;

	/* Writes a four-byte binary-encoded integer val from m_disk, starting
         * at position pos.  
  	 * Returns true if successful, false if writing would go past the end of the array. */
	bool write_int(const int pos, const int val);

	/* Reads a four-byte binary-encoded integer val from m_disk, starting
         * at position pos.  
	 * Returns true if successful, false if writing would go past the end of the array. 
	 * If not successful, sets val to 0. */
	bool read_int(const int pos, int& val) const;

	public:
	/* Opens the linux file named "name" and loads it into memory as a string named "m_disk" */
	Filesystem(const string name, const unsigned int size);

	/* Flushes the contents of m_disk back to the file named m_disk_filename and frees m_disk. */
	~Filesystem();	
	/***********************************/
	/* Functions you need to implement */
	/***********************************/

	/* Initializes the filesystem to be ready for use the first time it is created. */
	void format();

	/* Allocate at least one block for the file named "name" and create a directory entry for it */
	bool create(const string name);

	/* Return a string containing a directory listing. */
	string list() const;

	/* Deletes the file named "name" by removing it from the directory and
         * then marks its space as available. Returns true if successful, false if the
         * file could not be found. */
	bool rm(const string name);

	/* Renames the file "old_name" to "new_name" and returns true.  Returns false if no file with the old name can be
	   found or if a file with name "new_name" already exists. */
	bool rename(const string old_name, const string new_name);

	/* Makes a copy of the file with name old_name and calls it new_name.
         * Returns true if successful, false if no file with the old name can be found,
         * a file named "new_name" already exists,
         * or if there isn't a free block available for the new file. */

	bool copy(const string old_name, const string new_name);

	/* Create a file handle for "name" and return the file descriptor. */
	int open(const string name);
	
	/* Close the file with descriptor fd, so that the file descriptor can be reused. Also should free the file handle. 
	 * Returns true if fd is a valid descriptor, false otherwise. */	
	bool close(const int fd) const;

	/* Read size bytes from the file with descriptor fd.  Returns the bytes
         * as an array of characters or NULL if the fd is invalid.	*/
	bool read(const int fd, string &buf, const unsigned int size) const;

	/* Write size bytes from string str to the file with descriptor fd.
         * Returns true if successful, false otherwise. */
	bool write(const int fd, const string str, const unsigned int size);
};

#endif //FILESYSTEM_H
