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
		void set(unsigned __int64 Index, string In) {
			this->Tuple.at(Index) = In;
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

class fltTuple { // string tuple for store array of string.
public:
	vector<float> Tuple;
	float var(int i) {
		return this->Tuple[i];
	}
	void set(unsigned __int64 Index, float In) {
		this->Tuple.at(Index) = In;
	}
	void append(float In) {
		this->Tuple.push_back(In);
	}
	void remove(float In) {
		this->Tuple.erase(std::remove(this->Tuple.begin(), this->Tuple.end(), In), this->Tuple.end());
	}
	void popOut(int index) {
		this->Tuple.erase(Tuple.begin() + index);
	}
	unsigned __int64 length() {
		return this->Tuple.size();
	}
	unsigned __int64 index(float In) {
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
	void set(string keyIn, string In) {
		this->Tuple.set(Key.index(keyIn), In);
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

class fltDic { // string tuple for store array of string.
	public:
		strTuple Key;
		fltTuple Tuple;
		float get(string keyIn) {
			return this->Tuple.var(Key.index(keyIn));
		}
		void set(string keyIn, float In) {
			this->Tuple.set(Key.index(keyIn), In);
		}
		void append(string keyIn, float In) {
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

class Object{
	private:
		string Type;
		fltDic Stat;
		float posX;
		float posY;
		Sprite sprite;
		Texture texture;
	public:
		void addStat(string KeyIn, float val) {
			Stat.append(KeyIn, val);
		}
		float getStat(string KeyIn) {
			return Stat.get(KeyIn);
		}
		string type() {
			return this->Type;
		}
		void Is(string type) {
			this->Type = type;
		}
		string nowIs() {
			return this->Type;
		}
};

int main(){
	Object Billy, Pump;
	Billy.Is("Human");
	Billy.addStat("Health", 100);
	Billy.addStat("Mana", 500);
	cout << Billy.getStat("Health") << '\n';
	Pump.Is("Building");
	Pump.addStat("Durability", 128);
	cout << Pump.getStat("Durability") << '\n';
	
	return 0;
}
