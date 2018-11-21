#pragma once 
#include <string> 
#include <vector> 
#include <exception> 
#include <sstream> 
#include <iostream> 

using namespace std;

template<class T>
string args_to_str(T&& val)
{
	stringstream out;
	out << val;
	return out.str();
}

template<class... ArgsT>
string format(const string& str, ArgsT&&... args) {
	vector<string> Args = { args_to_str(forward<ArgsT>(args))... };
	stringstream ans;
	int left = 0;
	int right = 0;
	int pos = 0;
	while (1) {
		while (left < str.length() && str[left] != '{') {
			if (str[left] == '}') {
				throw runtime_error("");
			} else {
				ans << str[left];
			}
			left++;
		}
	     
		if (left + 1 >= str.length()) {
			if (left < str.length() && str[left] == '{') {
				throw runtime_error("");
			}
			break;
		} else {
			right = str.find("}", left);
			if (right != -1 && right - left == 2) {
				pos = str[left + 1];
				if (!isdigit(pos)) {
					throw runtime_error("");
				}
				if (pos - '0' >= Args.size()) {
					throw runtime_error("");
				}
				ans << Args[pos - '0'];
				left = right + 1;
			} else {
				throw runtime_error("");
			}
		}
	}
	return ans.str();
}
