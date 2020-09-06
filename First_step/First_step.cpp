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
#include<windows.h>

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
		string Type;
		unsigned __int64 ID;
		string Name;
		fltDic Stat;
		float posX = 0;
		float posY = 0;
		float offsetPosX = 0;
		float offsetPosY = 0;
		Sprite sprite;
		Texture texture;
		float Size;
		int imgHeight;
	public:
		Object(unsigned __int64 ID) {
			this->ID = ID;
		}
		int getImgHeight() {
			return imgHeight;
		}
		void setImgHeight(int Height) {
			this->imgHeight = Height;
		}
		string type() {
			return Type;
		}
		void setType(string In) {
			this->Type = In;
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
			this->Size = scale;
		}
		float getSize() {
			return this->Size;
		}
		void addStat(string KeyIn, float val) {
			Stat.append(KeyIn, val);
		}
		float getStat(string KeyIn) {
			return Stat.get(KeyIn);
		}
		void setOffsetPosX(float offx) {
			this->offsetPosX = offx*100;
		}
		void setOffsetPosY(float offy) {
			this->offsetPosY = offy*100;
		}
		void setPosX(float x) {
			this->posX = x;
			this->sprite.setPosition(this->posX + this->offsetPosX, this->posY + this->offsetPosY);
		}
		void setPosY(float y) {
			this->posY = y;
			this->sprite.setPosition(this->posX + this->offsetPosX, this->posY + this->offsetPosY);
		}
		void moveX(float amount) {
			this->sprite.setPosition(this->posX + amount + this->offsetPosX, this->posY + this->offsetPosY);
			this->posX += amount;
		}
		void moveY(float amount) {
			this->sprite.setPosition(this->posX + this->offsetPosX, this->posY + amount + this->offsetPosY);
			this->posY += amount;
		}
		float PosX() {
			return this->posX+this->offsetPosX;
		}
		float PosY() {
			return this->posY + this->offsetPosY;
		}
		void Is(string name) {
			this->Name = name;
		}
		string nowIs() {
			return this->Name;
		}
		Sprite getSprite() {
			return this->sprite;
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
	void insert(unsigned __int64 pos, Object* In) {
		this->Tuple.insert(Tuple.begin() + pos, In);
	}
};

class Map {
public:
	objPtrTuple Tuple;
	void registerObject(string Name) {
		Object* p = new Object(this->Tuple.length());
		p->Is(Name);
		this->Tuple.append(p);
	}
	Object* object(string keyIn) {
		for (int i = 0; i < this->Tuple.length(); i++) {
			if (Tuple.var(i)->nowIs() == keyIn) {
				return Tuple.var(i);
			}
		}
	}
	Object* objectAt(unsigned __int64 Index) {
		return this->Tuple.var(Index);
	}
	void append(Object* In) {
		this->Tuple.append(In);
	}
	void remove(string keyIn) {
		Object* ptr = this->Tuple.var(0);
		for (int i = 0; i < this->Tuple.length(); i++) {
			if ((ptr + i)->nowIs() == keyIn) {
				this->Tuple.popOut(i);
			}
		}
	}
	void removeObjAt(unsigned __int64 Index) {
		this->Tuple.popOut(Index);
	}
	void insertQuene(unsigned __int64 Index, Object* In) {
		this->Tuple.insert(Index, In);
	}
	unsigned __int64 entityNumber() {
		return this->Tuple.length();
	}
	string objectTypeAt(unsigned __int64 Index) {
		return this->Tuple.var(Index)->nowIs();
	}
	vector<Object*> getTuple() {
		return this->Tuple.Tuple;
	}

};

class gameEngine { //this a main class of this game. resposibility for render object, recieve input event, draw graphic.
private:
	//Add a variable down here.
	Map Field;
	int move_speed = 5;
	int h = 900;
	int w = 1600;
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
	RenderWindow* window;
	Event ev;
	VideoMode mode;
	Map Mars;
	int i = 0;

	void initVar() {
		this->window = nullptr;
	}
	void initWindow() {
		this->mode.height = h;
		this->mode.width = w;
		this->window = new RenderWindow(this->mode, "First Step", Style::Titlebar | Style::Close);
		this->window->setFramerateLimit(75);
	}
	void initObject() {
		this->Field.registerObject("Anchor");
		this->Field.object("Anchor")->setPosX(0);
		this->Field.object("Anchor")->setPosY(0);
		this->Field.object("Anchor")->setType("Dynamic");

		this->Field.registerObject("BG");
		this->Field.object("BG")->setSpriteTexture("assets\\graph.jpg");
		this->Field.object("BG")->setSpriteSize(10);
		this->Field.object("BG")->setPosX(this->Field.object("Anchor")->PosX());
		this->Field.object("BG")->setPosY(this->Field.object("Anchor")->PosY());
		this->Field.object("BG")->setType("Dynamic");

		this->Field.registerObject("Stone1");
		this->Field.object("Stone1")->setSpriteTexture("assets\\alien\\PNG\\alien_armor\\armor__0001_idle_2.png");
		this->Field.object("Stone1")->setSpriteSize(0.6);
		this->Field.object("Stone1")->setImgHeight(428);
		this->Field.object("Stone1")->setPosX(this->Field.object("Anchor")->PosX());
		this->Field.object("Stone1")->setPosY(this->Field.object("Anchor")->PosY());
		this->Field.object("Stone1")->setType("Dynamic");
		this->Field.object("Stone1")->setOffsetPosX(10);
		this->Field.object("Stone1")->setOffsetPosY(10);

		this->Field.registerObject("Stone2");
		this->Field.object("Stone2")->setSpriteTexture("assets\\alien\\PNG\\alien_armor\\armor__0001_idle_2.png");
		this->Field.object("Stone2")->setSpriteSize(0.4);
		this->Field.object("Stone2")->setImgHeight(428);
		this->Field.object("Stone2")->setPosX(this->Field.object("Anchor")->PosX());
		this->Field.object("Stone2")->setPosY(this->Field.object("Anchor")->PosY());
		this->Field.object("Stone2")->setType("Dynamic");
		this->Field.object("Stone2")->setOffsetPosX(15);
		this->Field.object("Stone2")->setOffsetPosY(10);

		this->Field.registerObject("Stone3");
		this->Field.object("Stone3")->setSpriteTexture("assets\\alien\\PNG\\alien_armor\\armor__0001_idle_2.png");
		this->Field.object("Stone3")->setSpriteSize(0.3);
		this->Field.object("Stone3")->setImgHeight(428);
		this->Field.object("Stone3")->setPosX(this->Field.object("Anchor")->PosX());
		this->Field.object("Stone3")->setPosY(this->Field.object("Anchor")->PosY());
		this->Field.object("Stone3")->setType("Dynamic");
		this->Field.object("Stone3")->setOffsetPosX(20);
		this->Field.object("Stone3")->setOffsetPosY(10);

		this->Field.registerObject("Stone4");
		this->Field.object("Stone4")->setSpriteTexture("assets\\stone.jpg");
		this->Field.object("Stone4")->setSpriteSize(1);
		this->Field.object("Stone4")->setImgHeight(1365);
		this->Field.object("Stone4")->setPosX(this->Field.object("Anchor")->PosX());
		this->Field.object("Stone4")->setPosY(this->Field.object("Anchor")->PosY());
		this->Field.object("Stone4")->setType("Dynamic");
		this->Field.object("Stone4")->setOffsetPosX(30);
		this->Field.object("Stone4")->setOffsetPosY(10);

		this->Field.registerObject("Elon");
		this->Field.object("Elon")->setSpriteTexture("assets\\alien\\PNG\\alien_armor\\armor__0001_idle_2.png");
		this->Field.object("Elon")->setSpriteSize(0.3);
		this->Field.object("Elon")->setImgHeight(428);
		this->Field.object("Elon")->addStat("Health", 100);
		this->Field.object("Elon")->addStat("Hunger", 100);
		this->Field.object("Elon")->addStat("Air", 100);
		this->Field.object("Elon")->setPosX(750);
		this->Field.object("Elon")->setPosY(450);
		this->Field.object("Elon")->setType("Static");

		this->Field.registerObject("Health_Bar");
		this->Field.object("Health_Bar")->addStat("Value", 100);
		this->Field.object("Health_Bar")->setSpriteTexture("assets\\red.jpg");
		this->Field.object("Health_Bar")->setSpriteSize(0.01);
		this->Field.object("Health_Bar")->setPosX(this->Field.object("Elon")->PosX());
		this->Field.object("Health_Bar")->setPosY(this->Field.object("Elon")->PosY());
		this->Field.object("Health_Bar")->getSprite().scale(100, 1);
		this->Field.object("Health_Bar")->setType("Static");

	}
	void Swap(unsigned __int64 ID1, unsigned __int64 ID2) {
		Object* ptr1 = this->Field.objectAt(ID1);
		Object* ptr2 = this->Field.objectAt(ID2);
		this->Field.removeObjAt(ID1);
		this->Field.insertQuene(ID1, ptr2);
		this->Field.removeObjAt(ID2);
		this->Field.insertQuene(ID2, ptr1);
	}
public:
	gameEngine() {
		this->initVar();
		this->initWindow();
		this->initObject();
	}
	virtual ~gameEngine() {
		delete this->window;
	}
	const bool isRuning() {
		return this->window->isOpen();
	}
	void W_key() {
		this->Field.object("Elon")->setSpriteTexture("assets\\alien\\PNG\\alien_armor\\armor__0016_run_5.png");
		this->Field.object("Anchor")->moveY(1 * this->move_speed);
	}
	void A_key() {
		this->Field.object("Elon")->setSpriteTexture("assets\\alien\\PNG\\alien_armor\\armor__0016_run_5reverse.png");
		this->Field.object("Anchor")->moveX(1 * this->move_speed);
	}
	void S_key() {
		this->Field.object("Elon")->setSpriteTexture("assets\\alien\\PNG\\alien_armor\\armor__0016_run_5.png");
		this->Field.object("Anchor")->moveY(-1 * this->move_speed);
	}
	void D_key() {
		this->Field.object("Elon")->setSpriteTexture("assets\\alien\\PNG\\alien_armor\\armor__0016_run_5.png");
		this->Field.object("Anchor")->moveX(-1 * this->move_speed);
	}
	void Idle() {
		this->Field.object("Elon")->setSpriteTexture("assets\\alien\\PNG\\alien_armor\\armor__0000_idle_1.png");
	}
	void pollEvents() {
		while (this->window->pollEvent(this->ev)) {
			if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Escape) {
				this->window->close();
			}
			if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::W) {
				W = true;
			}
			if (ev.type == Event::KeyReleased && ev.key.code == Keyboard::W) {
				W = false;
			}
			if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::A) {
				A = true;
			}
			if (ev.type == Event::KeyReleased && ev.key.code == Keyboard::A) {
				A = false;
			}
			if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::S) {
				S = true;
			}
			if (ev.type == Event::KeyReleased && ev.key.code == Keyboard::S) {
				S = false;
			}
			if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::D) {
				D = true;
			}
			if (ev.type == Event::KeyReleased && ev.key.code == Keyboard::D) {
				D = false;
			}
			if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::LShift) {
				this->move_speed = 8*1.5;
			}
			if (ev.type == Event::KeyReleased && ev.key.code == Keyboard::LShift) {
				this->move_speed = 8;
			}
		}
		
	}
	void update() {
		this->pollEvents();
		if (W || A || S || D) {
			if (S) {
				S_key();
			}
			if (W) {
				W_key();
			}
			if (D) {
				D_key();
			}
			if (A) {
				A_key();
			}
		}
		else {
			Idle();
		}
		for (int i = 0; i < Field.entityNumber(); i++) {
			if (this->Field.objectAt(i)->type() == "Dynamic") {
				this->Field.objectAt(i)->setPosX(this->Field.object("Anchor")->PosX());
				this->Field.objectAt(i)->setPosY(this->Field.object("Anchor")->PosY());
			}
		}
		for (int i = 2; i < this->Field.entityNumber()-2; i++) {
			if (this->Field.objectAt(i)->PosY() + (this->Field.objectAt(i)->getImgHeight() * this->Field.objectAt(i)->getSize()) > this->Field.objectAt(i + 1)->PosY() + (this->Field.objectAt(i + 1)->getImgHeight()* this->Field.objectAt(i + 1)->getSize())) {
				printf("++++++++++++++++++++++++++++++++++ Swap 1 %d %d\n", i, i + 1);
				this->Swap(i, i + 1);
			}
		}
		/*
		This part is for update game event.
		*/
	}
	void render() {
		this->window->clear();
		/*
		This part is for drawing graphic.
		1. clear old frame
		2. render object
		3. draw
		*/
		for (int i = 0; i < Field.entityNumber(); i++) {
			cout << i << '\t';
			cout << this->Field.objectAt(i)->nowIs() << '\n';
		}
		cout << "---------------------------------\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << '\n';
		for (int i = 0; i < Field.entityNumber(); i++) {
			//printf("%d; %f, %f\n", i, this->Field.objectAt(i)->PosX(), this->Field.objectAt(i)->PosY());
			this->window->draw(this->Field.objectAt(i)->getSprite());
		}
		//printf("%f, %f\n", this->dui.getPosX(), this->dui.getPosY());

		this->window->display();
	}
};

int main() { // Game loop
	gameEngine First_step;
	while (First_step.isRuning()) {
		First_step.update();
		First_step.render();
	}
}

