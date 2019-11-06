#ifndef UTIL_RANGE_H
#define UTIL_RANGE_H
#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
namespace util{
	using namespace std;
	template<class T=int, class U=int>
	std::vector<T> rangeE(T start, T stop, U step=1){
		std::vector<T> v;
		while(1) {
			if (start >= stop) {
				break;
			}
			v.push_back(start);
			start += step;
		}
		return v;
	}
	template<class T=int, class U=int>
	std::vector<T> rangeI(T start, T stop, U step=1){
		std::vector<T> v;
		while(1) {
			if (start >= stop+1) {
				break;
			}
			v.push_back(start);
			start += step;
		}
		return v;
	}
}
#endif

