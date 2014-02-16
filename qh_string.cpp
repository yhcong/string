#include "assert.h"
#include "qh_string.h"
//#include <iostream>
#include <string.h>
namespace qh
{   

    string::string()
        : data_(NULL), len_(0)
    {
    }

    string::string( const char* s )
    {
		//int len;

		if (NULL == s) {
			data_ = NULL;
			len_=0;
		}
		else{
			//len = strlen(s);
			len_=strlen(s);
			data_ = new char[len_+1];
			strcpy(data_, s);
		}

    }

    string::string( const char* s, size_t len )
    {
		if (len == 0) {
			data_ = NULL;
			len_=0;
		}
		else{
			data_ = new char[len+1];
			len_=len;
			strcpy(data_, s);
		}
    }

    string::string( const string& rhs )
    {
		//int len;
		if (rhs.size() == 0) {
			data_ = NULL;
			len_=0;
		}
		else{
			len_ = strlen(rhs.data_);
			data_ = new char[len_+1];
			strcpy(data_, rhs.data_);
		}

    }

    string& string::operator=( const string& rhs )
    {
		//int len;
		if (this == &rhs)
			return *this;
		
		delete []data_;
		len_ = strlen(rhs.data_);
		data_ = new char[len_+1];
		strcpy(data_, rhs.data_);		
		return *this;
		
    }

	string &string::operator+(const string &s)
	{
		//int len;
		string *str = new string;

		len_ = strlen(data_) + strlen(s.data_);
		SafeRelease_Array (str->data_);
		str->data_ = new char[len_+1];
		strcpy(str->data_, data_);
		strcat(str->data_, s.data_);

		return *str;
	}


	 string& string::operator+(const char *s)
	{
		int len;
		if (s == NULL)
			return *this;

		string *str = new string;

		len = strlen(data_) + strlen(s);
		str->data_ = new char[len+1];
		strcpy(str->data_, data_);
		strcat(str->data_, s);
		return *str;
	}
	 

	    string::~string()
	    { 
			if(data_!=NULL){
				delete []data_;
				data_=NULL;
			}
	
	    }
	
	    size_t string::size() const
	    {
	        return len_;
	    }
	
	    const char* string::data() const
	    {
			//cout << data_ << endl;
			return data_;
	
	        //return NULL;
	    }
	
	    const char* string::c_str() const
	    {
			return data_;
	        //return NULL;
	    }
	
		bool string::empty()
		{
			if(data_==NULL)
				return 1;
			else
				return 0;
	
		}
	
	    char string::operator[]( size_t index )
	    {
			if (index<0 || index>=len_)
			 {
				 printf("out of range!\n");
			 }
			 return this->data_[index];
	        //return NULL;
	    }
	

	
	bool string::erase( const unsigned& begin,const unsigned& end ) 
	{
	 assert( begin <= end );
	 if(end>=len_)
	  return false;
	 if( begin == end )
	 {
	  erase( begin );
	 }
	 else
	 {
	  unsigned gap = end - begin;
	  char* t = new char[len_+1];
	  strcpy_s(t,len_+1,data_);
	  SafeRelease_Array(data_);
	  int size = len_ - gap;
	  data_ = new char[size];
	  strncpy_s(data_,size,t,begin);
	  strncat_s(data_,size,t+end+1,size - end-1);

	  len_ -= (gap+1);

	  SafeRelease_Array( t );
	 }
 
	 return true;
	}

	bool string::erase( const unsigned& pos )
	{
	 /*assert( pos < m_uCount );*/
	 if( pos >= len_ )
	 {
	  return false;
	 }
	 char* t = new char[len_+1];
	 strcpy_s(t,len_+1,data_);
 
	 SafeRelease_Array(data_);

	 data_ = new char[len_];
	 strncpy_s(data_,len_,t,pos);
	 strncat_s(data_,len_,t+pos+1,len_-pos-1);
 
	 len_--;
	 SafeRelease_Array( t );

	 return true;
	}

	inline void string::SafeRelease_Array( char* s )
	{
	 if( s != NULL )
	 {
		  delete []s;
		  s = NULL;
	 }
	}

	void string::clear()
	{
	 SafeRelease_Array(data_);
	 len_ = 0;
	}

	void string::insert( unsigned pos, const char& ch )
	{
	 assert( pos <= len_ );

	 char* t = new char[len_]; 
	 strcpy_s( t,len_+1,data_ ); 

	 data_ = new char[len_ +2]; 

	 strncpy_s(data_,len_+2,t,pos);  

	 *(data_+pos) = ch;  // insert

	 *(data_+pos+1) = '\0';
	 /*strcat_s(m_str,m_uCount+2,tmp+pos);*/
	 strncat_s(data_,len_+2,t,len_ - pos );

	 len_++;

	 SafeRelease_Array(t);
	}

	void string::insert( unsigned pos, const string& ss )
	{
	 assert( pos <= len_ );

	 char* t1 = new char[ pos +1 ];
	 strncpy_s(t1,pos+1,data_,pos);

	 char* t2 = new char[ len_ - pos + 1 ];
	 strncpy_s(t2,len_-pos+1,data_+pos,len_ - pos );
 
	 data_ = new char[len_ + ss.len_ + 1];
	 strcpy_s(data_,pos+1,t1);
	 SafeRelease_Array( t1 );

	 strcat_s(data_,ss.len_ + len_ + 1,ss.data_);
	 strcat_s(data_,ss.len_ + len_ + 1,t2 );
	 len_ += ss.len_;

	 SafeRelease_Array( t2 );
	}

	void string::push_back( const char& ch )
	{
	 insert( len_, ch );
	}
	void string::push_front( const char& ch )
	{
	 insert( 0, ch );
	}
	void string::append (const string& str)
	{
		const char* ch = str.c_str();
		insert( len_, ch );
	}

	void string::assign(const string& str)
	{
		SafeRelease_Array(data_);
		data_= new char [str.size()+1];
		strcpy(data_,str.data_);
	}

	char string::at (size_t pos)
	{
		if(pos>len_)
			printf("out of range!\n");
		char ch;
		ch=data_[pos-1];
		return ch;
	}

	int string::compare (const string& str) const
	{
		if(data_== str.data_)
			return 1;
		else
			return 0;
	}

	char* string::substr (size_t pos , size_t len )const
	{
		if(pos> len_ || (pos+len) >len_)
			printf("out of range!\n");
		 
		char *t = new char[len]; 
		strncpy_s(t,len_-pos+1,data_+pos,len_ - pos );
		return t;
	}

	void string::swap (string& str)
	{
		int len;
		char *t = new char [len_];
		strcpy(t,data_);
		len=len_;
		SafeRelease_Array(data_);	
		data_= new char [str.size()];
		strcpy(data_,str.data_);
		len_=str.size();
		SafeRelease_Array(str.data_);
		str.data_= new char [len_];
		strcpy(str.data_,t);
		str.len_=len;
		

	}

	void string::replace (size_t pos,  size_t len,  const string& str)
	{
		if(pos>len_ || (pos+len)> len_)
			printf("out of range!\n");
		//strncpy_s(data_+pos-1,len, str.data_,str.len_);
	
		char* t1 = new char[ pos  ];
		 strncpy_s(t1,pos,data_,pos-1);

		 char* t2 = new char[ len_ - pos-len +2 ];
		 strncpy_s(t2,len_-pos-len+2,data_+pos+len-1,len_ - pos -len+1);
 
		 data_ = new char[len_ + str.len_ + 1];
		 strcpy_s(data_,pos,t1);
		 SafeRelease_Array( t1 );

		 strcat_s(data_,str.len_ + len_ + 1,str.data_);
		 strcat_s(data_,str.len_ + len_ + 1,t2 );
		 len_ = len_-len+str.len_;
		 SafeRelease_Array( t2 );

	
		

	}

}
