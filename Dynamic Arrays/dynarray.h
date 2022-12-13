#ifndef DYNARRAY_H
#define DYNARRAY_H
#include <iostream>
#include <cstring>

template <typename T>
class Dynarray {

  private:
    T* m_list;
    int m_size;
    void resize(const int new_size)
    { 
      T* new_list=new T[new_size];
      if(new_size < m_size)
      {				
	for(int i = 0; i < new_size; ++i)
	{
	  new_list[i] = m_list[i];
	}
      }	
      else
      {
	for(int i = 0; i < m_size; ++i)
	{
	  new_list[i] = m_list[i];
	}

	for(int i = m_size; i < new_size-1; ++i)
	{
	  new_list[i] = 0;
	}


      }
      delete[] m_list;
     m_list = new_list;
      m_size=new_size;
    }
  public:
    Dynarray():m_list(new T[10]), m_size(10)
  {} 

    ~Dynarray()
    { 
      delete[] m_list;
    }
    //Mutators
    T& operator[](const int pos)
    { 
      if(pos >= m_size)
      {
	resize(pos + 1);
	return m_list[pos];
      }
      else	  
	return m_list[pos];
    }
    void shrink(int size)
    {
      if(size < m_size)
      {
	resize(size);
      }  
    }
    //Accessor
    int size() const
    { 
      return m_size;
    }
};
#endif
