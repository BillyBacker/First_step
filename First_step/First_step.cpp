#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <typeinfo>

using namespace sf;
using namespace std;

class strTuple { // string tuple for store array of string.
	public:
		vector<string> Tuple;
		string var(int i){
			return this->Tuple[i];
		}
		void append(string In) {
			this->Tuple.push_back(In);
		}
		void remove(string In) {
			this->Tuple.erase(std::remove(this->Tuple.begin(), this->Tuple.end(), In), this->Tuple.end());
		}
		void popOut(int index) {
			this->Tuple.erase(Tuple.begin() + index);
		}
		unsigned __int64 length() {
			return this->Tuple.size();
		}
		unsigned __int64 index(string In) {
			unsigned __int64 num = 0;
			auto pos = find(this->Tuple.begin(), this->Tuple.end(), In);
			if (pos != this->Tuple.end()) {
				unsigned __int64 index = distance(this->Tuple.begin(), pos);
				return index;
			}
			else {
				return -1;
			}
		}
};

class strDic { // string tuple for store array of string.
public:
	strTuple Key;
	strTuple Tuple;
	string get(string keyIn) {
		return this->Tuple.var(Key.index(keyIn));
	}
	void append(string keyIn, string In) {
		this->Key.append(keyIn);
		this->Tuple.append(In);
	}
	void remove(string keyIn) {
		this->Tuple.popOut(Key.index(keyIn));
		this->Key.popOut(Key.index(keyIn));
	}
	unsigned __int64 length() {
		return this->Tuple.length();
	}
};

int main(){
	strDic A;
	A.append("Name", "Billy");
	A.append("Age", "18");
	cout << A.get("Age") << '\n';
	A.remove("Age");
	A.append("Gender", "Male");
	cout << A.get("Gender") << '\n';
	return 0;
}
