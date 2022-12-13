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
#include "handle.h"
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

vector<FileHandle*> file_list;

void Filesystem::format()
{
  unsigned int MAX_SIZE = (m_disk_size/1048) * 24; // Each block takes 1024 bytes and each m_dir needs 1024 bytes and takes 24 additional bytes

  for(unsigned int i = 0; i < m_disk_size; ++i)
  {
    m_disk[i] = '*'; //set a '*' sentinel for m_disk[]
  }
}

bool Filesystem::create(const string name)
{

  unsigned int MAX_SIZE = 0; // Each block takes 1024 bytes and each m_dir needs 1024 bytes and takes 24 additional bytes
  unsigned int d_size = m_disk_size/1048;

  //loop and check that the file name i'snt a filename already inside m_dir
  for(unsigned int a = 0; a < d_size; ++a){
    if(strncmp(m_dir[a].filename,name.c_str(),16) == 0)
      return false;
  }

  for(unsigned int i = 0; i < d_size; ++i){ 
    //make sure the sentinel is in the mdir filename
    if(m_dir[i].filename[0]== '*'){
      for(unsigned int j = 0; j < d_size; ++j){ 
	if(MAX_SIZE < m_dir[j].pos and m_dir[j].filename[0] != '*')
	  MAX_SIZE = m_dir[j].pos;
      }
      //copy the filename in
      strncpy(m_dir[i].filename,name.c_str(),16);
      m_dir[i].size = 0;
      if(MAX_SIZE == 0)
	m_dir[i].pos = (m_disk_size/1048) *24;
      else
	m_dir[i].pos = MAX_SIZE + 1024;
      return true;
    }
  }
  return false;
}

string Filesystem::list() const
{
  unsigned int d_size = m_disk_size/1048;
  ostringstream s;

  for(unsigned int i = 0; i < d_size; ++i){
    //make sure the sentinel is in the mdir filename
    if(m_dir[i].filename[0] != '*')
    {
      //format the list output
      s << left << setw(16) << m_dir[i].filename << left << setw(8) << m_dir[i].size << endl;
    }
  }
  //return the list
  return s.str();
}

bool Filesystem::rm(const string name)
{
  unsigned int d_size = m_disk_size/1048;

  for(unsigned int i = 0; i < d_size; ++i){
    //make sure that the filename you are removing matches the filename in mdir
    if(strncmp(m_dir[i].filename,name.c_str(),16) == 0){

      for(unsigned int j = 0; j < sizeof(m_dir); ++j){
	//set the m_dir filename to sentinel characters
	m_dir[i].filename[j] = '*';
      }
      return true;
    }
  }
  return false;

}

bool Filesystem::rename(const string old_name, const string new_name) 
{
  int dirsize = m_disk_size/1048;

  for(int i = 0; i < dirsize; ++i)
  {
    //make sure the mdir filename is the same as old name
    if(strncmp(m_dir[i].filename,old_name.c_str(),16) == 0)
    {
      //change the filename to the new name
      strncpy(m_dir[i].filename, new_name.c_str(),16);
      return true;
    }

  }
  return false;

}

bool Filesystem::copy(const string old_name, const string new_name)
{
  unsigned int MAX_SIZE = (m_disk_size/1048) * 24; 
  unsigned int d_size = m_disk_size/1048;


  for(unsigned int a = 0; a < d_size; ++a){
    //check that the filename doesnt already exist
    if(strncmp(m_dir[a].filename,new_name.c_str(),16) == 0)
      return false;
  }



  for(unsigned int i = 0; i < d_size; ++i){
    //check that the mdir filename and the old name are the same
    if(strncmp(m_dir[i].filename,old_name.c_str(),16) == 0){
      for(unsigned int j = 0; j < d_size; ++j){ 
	//make sure the m_dir[j] filename is filled with the sentinel characters
	if(m_dir[j].filename[0]=='*'){
	  for(unsigned int k = 0; k < d_size; ++k){ 

	    if(MAX_SIZE < m_dir[k].pos and m_dir[k].filename[0] != '*')
	      MAX_SIZE = m_dir[k].pos + 1024;
	  }
	  //copy the new name into m_dir filename
	  strncpy(m_dir[j].filename,new_name.c_str(),16);
	  m_dir[j].size = m_dir[i].size;
	  m_dir[j].pos = MAX_SIZE;
	  return true;
	}
      }
    }
  }
  return false;

}

int Filesystem::open(const string name)
{
  unsigned int d_size = m_disk_size/1048;

  FileHandle* handler = new FileHandle();

  for(unsigned int i = 0; i < d_size; ++i){
    //make sure the filename in m_dir is the same as the one you want to open
    if(strncmp(m_dir[i].filename,name.c_str(),16) == 0){

      handler->size = m_dir[i].size;
      handler->pos = m_dir[i].pos;
      handler->offset = 0;
      file_list.push_back(handler);
      int descriptor = file_list.size() - 1;
      return descriptor;
    }
  }
  return -1;
}


bool Filesystem::close(const int fd) const
{
  //make sure the file_list isnt already empty at fd
  if(file_list[fd] != 0){
    //delete the filehandler at fd in file list
    delete file_list[fd];
    file_list[fd] = NULL;
    return true;
  }
  return false;

}


bool Filesystem::read(const int fd, string &buffer, const unsigned int size) const
{

  if(fd>=0 and fd < 255){
    FileHandle* handler = file_list[fd];

    int location = handler->offset + handler->pos;

    if(file_list[fd] == NULL or location + size > m_disk_size){  //file descriptor is invalid or over reads virtual disk
      return false;
    }
    else{
      for(unsigned int i = 0; i < size; ++i){
	//read from the buffer
	buffer += m_disk[handler->pos+i];
      }
      return true;

    }  
  }
  return false;

}


bool Filesystem::write(const int fd, const string str, const unsigned int size){

  unsigned int d_size = m_disk_size/1048;
  if(fd >= 0 and fd < 255){
    FileHandle* handler = file_list[fd];
    int location = handler->offset + handler->pos;

    if(file_list[fd] == NULL or location + size > m_disk_size){  //file descriptor is invalid or over reads virtual disk
      return false;
    }
    else{
      for(unsigned int k = 0; k < d_size; ++k)
      {
	if(m_dir[k].pos == handler->pos and m_dir[k].filename[0] != '*'){
	  for(unsigned int i = 0; i < size; ++i){
	    ++handler->size;
	    //write the character at str[i] into m_disk[location]
	    m_disk[location] = str[i]; 
	    ++handler->offset;
	    location = handler->pos + handler->offset;
	    if(location > m_disk_size)
	      return false;
	  }
	  m_dir[k].size = handler->size;
	  return true;
	}
      }  
    }
  }
  return false;

}
