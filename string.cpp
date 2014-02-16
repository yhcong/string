#include <stdio.h>
#include <stdlib.h>
#include "qh_string.h"
//#include <string>


int main()
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
	qh::string s="13h";	
	qh::string s1;
	qh::string s2="rw";
	size_t t=s.size();
	s1=s.operator+("abs");
	char ss=s1.at(4);
	int e=s.compare(s1);
	s.swap(s1);
	s.replace(2,3,s2);
	
#ifdef WIN32
    system("pause");
#endif

	return 0;
}
