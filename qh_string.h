#ifndef QIHOO_STRING_H_
#define QIHOO_STRING_H_

#include <stdlib.h>

namespace qh
{
    class string {
    public:
        //ctor
        string();
        string(const char* s);
        string(const char* s, size_t len);
        string(const string& rhs);

        string& operator=(const string& rhs);
		string& operator+(const string &s);
		string& operator+(const char *s);
		
		//Trim(string &str, const string &drop)

        //dtor
        ~string();

        //get
        size_t size() const;
        const char* data() const;
        const char* c_str() const;

        // set & get
        char operator[](size_t index);
		bool empty();
		bool erase( const unsigned& begin,const unsigned& end );
		bool erase( const unsigned& pos );
		inline void SafeRelease_Array(  char* s );
		void clear();
		void insert( unsigned pos, const char& ch );
		void insert( unsigned pos, const string& ss );
		void push_back( const char& ch );
		void push_front( const char& ch );
		void append (const string& str);
		void assign (const string& str);
		int compare (const string& str) const;
		char at (size_t pos);
		char* substr (size_t pos , size_t len )const;
		void swap (string& str);
		void replace (size_t pos,  size_t len,  const string& str);
		
		
	
		//void strcat(const char *s1,const char *s2);


    private:
        char*  data_;
        size_t len_;
    };
}

#endif
