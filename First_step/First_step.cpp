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
		string var(unsigned __int64 i){
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
		unsigned __int64 ID;
		string Name;
		fltDic Stat;
		float posX = 1;
		float posY = 1;
		Sprite sprite;
		Texture texture;
	public:
		Object(unsigned __int64 ID) {
			this->ID = ID;
		}
		unsigned __int64 getID() {
			return this->ID;
		}
		void setSpriteTexture(string Path) {
			if (!this->texture.loadFromFile(Path)) {
				printf("Error");
			}
			this->sprite.setTexture(this->texture);
		}
		void setSpriteSize(float scale) {
			this->sprite.setScale(scale, scale);
		}
		void addStat(string KeyIn, float val) {
			Stat.append(KeyIn, val);
		}
		float getStat(string KeyIn) {
			return Stat.get(KeyIn);
		}
		void setPosX(float x) {
			this->posX = x;
		}
		void setPosY(float y) {
			this->posY = y;
		}
		void moveX(float amount) {
			this->posX += amount;
		}
		void moveY(float amount) {
			this->posY += amount;
		}
		float PosX() {
			return this->posX;
		}
		float PosY() {
			return this->posY;
		}
		void Is(string name) {
			this->Name = name;
		}
		string nowIs() {
			return this->Name;
		}
};

class objPtrTuple {
public:
	vector<Object*> Tuple;
	Object* var(unsigned __int64 i) {
		return this->Tuple[i];
	}
	void set(unsigned __int64 Index, Object* In) {
		this->Tuple.at(Index) = In;
	}
	void append(Object* In) {
		this->Tuple.push_back(In);
	}
	void remove(Object* In) {
		this->Tuple.erase(std::remove(this->Tuple.begin(), this->Tuple.end(), In), this->Tuple.end());
	}
	void popOut(unsigned __int64 index) {
		this->Tuple.erase(Tuple.begin() + index);
	}
	unsigned __int64 length() {
		return this->Tuple.size();
	}
	unsigned __int64 index(Object* In) {
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

class Map {
public:
	strTuple Key;
	objPtrTuple Tuple;
	void registerObject(string Type) {
		Object* p = new Object(this->Tuple.length());
		this->Key.append(Type);
		this->Tuple.append(p);
	}
	Object* object(string keyIn) {
		return this->Tuple.var(Key.index(keyIn));
	}
	Object* objectAt(unsigned __int64 Index) {
		return this->Tuple.var(Index);
	}
	void set(string keyIn, Object* In) {
		this->Tuple.set(Key.index(keyIn), In);
	}
	void append(string keyIn, Object* In) {
		this->Key.append(keyIn);
		this->Tuple.append(In);
	}
	void remove(string keyIn) {
		this->Tuple.popOut(Key.index(keyIn));
		this->Key.popOut(Key.index(keyIn));
	}
	unsigned __int64 entityNumber() {
		return this->Tuple.length();
	}
	string objectNameAt(int Index) {
		return this->Key.var(Index);
	}
	string objectTypeAt(int Index) {
		return this->Tuple.var(Index)->nowIs();
	}
};

int main(){
	Map Field;

	Field.registerObject("Billy");
	Field.object("Billy")->Is("Human");
	Field.object("Billy")->addStat("Health", 100);


	cout << Field.object("Billy")->getStat("Health") << '\n';
	cout << Field.object("Billy")->nowIs() << '\n';
	cout << Field.entityNumber() << '\n';
	cout << Field.objectNameAt(0) << '\n';
	cout << Field.objectTypeAt(0) << '\n';
	return 0;
}
