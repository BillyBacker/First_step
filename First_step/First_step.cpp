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
	objPtrTuple Templ;
	unsigned __int64 getIndex(string name) {
		return this->Tuple.index(this->object(name));
	}
	void createTemplate(string name) {
		Object* p = new Object(this->Templ.length());
		p->Is(name);
		this->Templ.append(p);
	}
	void registerObject(string Name, string Template) {
		Object* p = new Object(this->Tuple.length());
		*p = *this->Template(Template);
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
	Object* Template(string keyIn) {
		for (int i = 0; i < this->Templ.length(); i++) {
			if (Templ.var(i)->nowIs() == keyIn) {
				return Templ.var(i);
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
		vector<Object*> ptr = this->Tuple.Tuple;
		for (int i = 0; i < this->Tuple.length(); i++) {
			if ((ptr[i])->nowIs() == keyIn) {
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
	int move_speed = 5;
	int h = 900;
	int w = 1600;
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
	bool running = true;
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
		this->window->setFramerateLimit(240);
	}
	void initObject() {
		this->Field.createTemplate("Blank");
		
		this->Field.createTemplate("BG_Element");
		this->Field.Template("BG_Element")->setType("Dynamic");
		this->Field.Template("BG_Element")->setPosX(0);
		this->Field.Template("BG_Element")->setPosY(0);
		
		this->Field.registerObject("Anchor", "BG_Element");
		
		this->Field.createTemplate("Structure");
		this->Field.Template("Structure")->setPosX(this->Field.object("Anchor")->PosX());
		this->Field.Template("Structure")->setPosY(this->Field.object("Anchor")->PosY());
		this->Field.Template("Structure")->setType("Dynamic");

		this->Field.registerObject("BG", "BG_Element");
		this->Field.object("BG")->setSpriteTexture("assets\\graph.jpg");
		this->Field.object("BG")->setSpriteSize(10);

		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < 10; i++) {
				this->Field.registerObject(to_string(i) + to_string(j), "Structure");
				this->Field.object(to_string(i) + to_string(j))->setSpriteTexture("assets\\alien\\PNG\\alien_armor\\armor__0001_idle_2.png");
				this->Field.object(to_string(i) + to_string(j))->setSpriteSize(0.6);
				this->Field.object(to_string(i) + to_string(j))->setImgHeight(428);
				this->Field.object(to_string(i) + to_string(j))->setOffsetPosX(10+i*2);
				this->Field.object(to_string(i) + to_string(j))->setOffsetPosY(10+j*2);
			}
		}

		this->Field.registerObject("Elon", "Blank");
		this->Field.object("Elon")->setSpriteTexture("assets\\alien\\PNG\\alien_armor\\armor__0001_idle_2.png");
		this->Field.object("Elon")->setSpriteSize(0.3);
		this->Field.object("Elon")->setImgHeight(428);
		this->Field.object("Elon")->addStat("Health", 100);
		this->Field.object("Elon")->addStat("Hunger", 100);
		this->Field.object("Elon")->addStat("Air", 100);
		this->Field.object("Elon")->setPosX(750);
		this->Field.object("Elon")->setPosY(450);
		this->Field.object("Elon")->setType("Static");

		this->Field.registerObject("Health_Bar", "Blank");
		this->Field.object("Health_Bar")->addStat("Value", 100);
		this->Field.object("Health_Bar")->setSpriteTexture("assets\\red.jpg");
		this->Field.object("Health_Bar")->setSpriteSize(0.01);
		this->Field.object("Health_Bar")->setPosX(this->Field.object("Elon")->PosX());
		this->Field.object("Health_Bar")->setPosY(this->Field.object("Elon")->PosY());
		this->Field.object("Health_Bar")->getSprite().scale(100, 1);
		this->Field.object("Health_Bar")->setType("Static");

	}
	double ObjectDis(Object* A, Object* B) {
		return sqrt(pow((A->PosX() - B->PosX()), 2) + pow((A->PosY() - B->PosY()), 2));
	}
	const bool ObjIsOnSight(Object* charactor, Object* B, double range) {
		if (sqrt(pow(charactor->PosX()-B->PosX(),2)+pow(charactor->PosY() - B->PosY(),2)) < range) {
			return true;
		}
		else {
			return false;
		}
	}
public:
	Map Field;
	vector<Object*> DrawField;
	bool pass = true;
	gameEngine() {
		this->initVar();
		this->initWindow();
		this->initObject();
		
	}
	virtual ~gameEngine() { 
		delete this->window;
	}
	void Swap(unsigned __int64 ID1, unsigned __int64 ID2) {
		Object* ptr1 = this->Field.objectAt(ID1);
		Object* ptr2 = this->Field.objectAt(ID2);
		this->Field.removeObjAt(ID1);
		this->Field.insertQuene(ID1, ptr2);
		this->Field.removeObjAt(ID2);
		this->Field.insertQuene(ID2, ptr1);
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
				running = false;
			}
			if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Q && pass) {
				pass = false;
				for (int i = 1; i < 40; i++) {
					this->Field.remove(to_string(i));
				}
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
		for (int i = 0; i < this->Field.entityNumber(); i++) {
			if (!(std::find(DrawField.begin(), DrawField.end(), this->Field.objectAt(i)) != DrawField.end()) && (ObjIsOnSight(this->Field.object("Elon"), this->Field.objectAt(i), 1000) || this->Field.objectAt(i)->nowIs() == "Anchor" || this->Field.objectAt(i)->nowIs() == "BG" || this->Field.objectAt(i)->nowIs() == "Elon")) {
				printf("Added ");
				cout << this->Field.objectAt(i)->nowIs() << '\n';
				this->DrawField.push_back(this->Field.objectAt(i));
			}
			if (this->Field.objectAt(i)->type() == "Dynamic") {
				this->Field.objectAt(i)->setPosX(this->Field.object("Anchor")->PosX());
				this->Field.objectAt(i)->setPosY(this->Field.object("Anchor")->PosY());
			}
		}
		//printf("%d | %.0llf, %.0llf | %.0llf, %.0llf |  \n", this->DrawField.size(), this->Field.object("Elon")->PosX(), this->Field.object("Elon")->PosY(), this->Field.object("0")->PosX(), this->Field.object("0")->PosY());
		for (int i = 0; i < this->DrawField.size()-1; i++) {
			if (!(ObjIsOnSight(this->Field.object("Elon"), this->DrawField[i], 1000) || this->DrawField[i]->nowIs() == "Anchor" || this->DrawField[i]->nowIs() == "BG" || this->DrawField[i]->nowIs() == "Elon")) {
				printf("removed ");
				cout << this->DrawField[i]->nowIs() << '\n';
				this->DrawField.erase(this->DrawField.begin() + i);
			}
		}
		for (int i = 0; i < this->DrawField.size()-1; i++) {
			if ((this->DrawField[i]->PosY() + (this->DrawField[i]->getImgHeight() * this->DrawField[i]->getSize()) > this->DrawField[i + 1]->PosY() + (this->DrawField[i + 1]->getImgHeight() * this->DrawField[i + 1]->getSize()))) {
				printf("++++++++++++++++++++++++++++++++++ Swap		");
				cout << this->DrawField[i]->nowIs() << '\t';
				cout << this->DrawField[i + 1]->nowIs() << '\n';
				iter_swap(DrawField.begin() + i, DrawField.begin() + i + 1);
			}
		}
		for (int i = 0; i < Field.entityNumber(); i++) {
			if (this->Field.objectAt(i)->type() == "Dynamic") {
				this->Field.objectAt(i)->setPosX(this->Field.object("Anchor")->PosX());
				this->Field.objectAt(i)->setPosY(this->Field.object("Anchor")->PosY());
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
		//for (int i = 0; i < Field.entityNumber(); i++) {
			//cout << i << '\t';
			//cout << this->Field.objectAt(i)->nowIs() << '\n';
		//}
		//cout << "---------------------------------\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << '\n';
		for (int i = 0; i < DrawField.size(); i++) {
			//printf("%d; %f, %f\n", i, this->Field.objectAt(i)->PosX(), this->Field.objectAt(i)->PosY());
				this->window->draw(this->DrawField[i]->getSprite());
		}
		//printf("%f, %f\n", this->dui.getPosX(), this->dui.getPosY());

		this->window->display();
	}
};

gameEngine First_step;

int main() { // Game loop
	while (First_step.isRuning()) {
		First_step.update();
		First_step.render();
	}
	return 0;
}

