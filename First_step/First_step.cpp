#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include<thread>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include<windows.h>

using namespace sf;
using namespace std;

class strTuple { // string tuple for store array of string.
public:
	vector<string> Tuple;
	string var(unsigned __int64 i) {
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
	void popOut(unsigned __int64 index) {
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
	float var(unsigned __int64 i) {
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
	void popOut(unsigned __int64 index) {
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

class mapTuple { // string tuple for store array of string.
public:
	vector<Map> Tuple;
	Map var(unsigned __int64 i) {
		return this->Tuple[i];
	}
	void set(unsigned __int64 Index, Map In) {
		this->Tuple.at(Index) = In;
	}
	void append(Map In) {
		this->Tuple.push_back(In);
	}
	void remove(float In) {
		this->Tuple.erase(std::remove(this->Tuple.begin(), this->Tuple.end(), In), this->Tuple.end());
	}
	void popOut(unsigned __int64 index) {
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

class Object {
private:
	fltDic Stat;
	vector<float> Pos;

public:
	void addStat(string KeyIn, float val) {
		Stat.append(KeyIn, val);
	}
	float getStat(string KeyIn) {
		return Stat.get(KeyIn);
	}

};

struct Map {
	vector<Object*> object;
	vector<Object*> objectOnscreen;
	void createNewObject() {
		Object* ptr = new Object();
		object.push_back(ptr);
	}
	unsigned long long entitiesNumber() {
		return object.size();
	}
};

class dataBase {
private:
	vector<Map*> Field;
	unsigned long long currentFieldIndex;
public:
	void updator(Object* obj) {

	}
	void loadMap(int Index) {
		currentFieldIndex = Index;
		for (int entitiesNumber = 0; entitiesNumber < (*Field[currentFieldIndex]).entitiesNumber(); entitiesNumber++) {

		}
	}
};

int main() { // Game loop
	
	return 0;
}
