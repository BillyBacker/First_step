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

class strTuple {
	public:
		vector<string> Tuple;
		string var(int i){
			return Tuple[i];
		}
		void append(string In) {
			Tuple.push_back(In);
		}
		void remove(string In) {
			Tuple.erase(std::remove(Tuple.begin(), Tuple.end(), In), Tuple.end());
		}
		unsigned __int64 length() {
			return Tuple.size();
		}
		unsigned __int64 index(string In) {
			unsigned __int64 num = 0;
			auto pos = find(Tuple.begin(), Tuple.end(), In);
			if (pos != Tuple.end()) {
				unsigned __int64 index = distance(Tuple.begin(), pos);
				return index;
			}
			else {
				return -1;
			}
		}
};



int main(){
	strTuple A;
	A.append("Hello");
	A.append("Hi");
	A.append("How are you");
	printf("%d\n", A.index("Hi"));
	A.remove("Hi");
	printf("%d\n", A.index("Hi"));
	return 0;
}
