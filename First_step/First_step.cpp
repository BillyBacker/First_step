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
#include<random>

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

class Object {
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
	float Size;
	int imgHeight;
	int imgWidth;

	int time = 0, Index = 0;
	vector<Texture*> textureArray[10];
	vector<int> duration[10];
	int slot = 0;
public:
	bool loop = false;
	Object(unsigned __int64 ID) {
		this->ID = ID;
	}
	void setAnimationSeq(int Slot) {
		this->slot = Slot;
	}
	int getImgHeight() {
		return imgHeight;
	}
	void setImgHeight(int Height) {
		this->imgHeight = Height;
	}
	void setImgWidth(int Width) {
		this->imgWidth = Width;
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
	void addTexture(string Path,int slot , int durt) {
		Texture* ptr = new Texture;
		if (!(*ptr).loadFromFile(Path)) {
			printf("Error");
		}
		this->textureArray[slot].push_back(ptr);
		this->duration[slot].push_back(durt);
		
	}
	void setSpriteTexture(unsigned long long Index, int slot) {
		this->sprite.setTexture(*this->textureArray[slot][Index]);
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
		this->offsetPosX = offx * 100;
	}
	void setOffsetPosY(float offy) {
		this->offsetPosY = offy * 100;
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
		return this->posX + this->offsetPosX;
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
	void UpdateAnimation(int speed) {
		this->time+=speed;
		if (this->loop && this->Index >= this->textureArray[this->slot].size()) {
			this->Index = 0;
		}
		if (this->Index < this->textureArray[this->slot].size() && this->time >= duration[this->slot][this->Index]) {
			this->sprite.setTexture(*(this->textureArray[this->slot][this->Index]));
			this->Index++;
			this->time = 0;
		}
	}
	void resetTimeSeq() {
		this->time == 0;
	}
	void flipTexture(int rev) {
		this->sprite.setScale(rev*this->Size, this->Size);
		this->setPosX(700 - this->imgWidth*this->Size*rev/2);
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
	int move_speed = 1;
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

		this->Field.createTemplate("Item");
		this->Field.Template("Item")->setType("Static");

		this->Field.createTemplate("Rocky");
		this->Field.Template("Rocky")->addTexture("assets\\Prop\\Rock\\Rock1.png", 0, 1000);
		this->Field.Template("Rocky")->addTexture("assets\\Prop\\Rock\\Rock2.png", 1, 1000);
		this->Field.Template("Rocky")->addTexture("assets\\Prop\\Rock\\Rock3.png", 2, 1000);
		this->Field.Template("Rocky")->setSpriteTexture(0, 0);
		this->Field.Template("Rocky")->setSpriteSize(0.1);
		this->Field.Template("Rocky")->setImgHeight(900);
		this->Field.Template("Rocky")->setType("Dynamic");

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
		this->Field.object("BG")->addTexture("assets\\graph.jpg", 0, 1000);
		this->Field.object("BG")->setSpriteTexture(0, 0);
		this->Field.object("BG")->setSpriteSize(10);

		for (int j = 0; j < 200; j++) {
			float size = rand() % 10;
			this->Field.registerObject(to_string(i) + to_string(j), "Rocky");
			this->Field.Template("Rocky")->setSpriteTexture(0, rand()%3);
			this->Field.object(to_string(i) + to_string(j))->setOffsetPosX(rand() % 50);
			this->Field.object(to_string(i) + to_string(j))->setOffsetPosY(rand() % 50);
		}

		this->Field.registerObject("Pump", "Structure");
		this->Field.object("Pump")->addTexture("assets\\Prop\\Building\\WaterPump_stage1_13.png", 0, 1000);
		this->Field.object("Pump")->setSpriteTexture(0, 0);
		this->Field.object("Pump")->setSpriteSize(0.1);
		this->Field.object("Pump")->setImgHeight(1000);
		this->Field.object("Pump")->setOffsetPosX(10);
		this->Field.object("Pump")->setOffsetPosY(10);

		this->Field.registerObject("Elon", "Blank");
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk1.png", 0, 20);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk2.png", 0, 20);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk3.png", 0, 20);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk4.png", 0, 20);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk5.png", 0, 20);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk4.png", 0, 20);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk3.png", 0, 20);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk2.png", 0, 20);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Idle.png", 1, 20);
		this->Field.object("Elon")->loop = true;
		this->Field.object("Elon")->setSpriteSize(0.1);
		this->Field.object("Elon")->setImgHeight(1500);
		this->Field.object("Elon")->setImgWidth(1000);
		this->Field.object("Elon")->addStat("Health", 100);
		this->Field.object("Elon")->addStat("Hunger", 100);
		this->Field.object("Elon")->addStat("Air", 100);
		this->Field.object("Elon")->setPosX(700 - 1000 * 0.1 * 1 / 2);
		this->Field.object("Elon")->setPosY(400);
		this->Field.object("Elon")->setType("Static");

		this->Field.registerObject("Apple", "Item");
		this->Field.object("Apple")->addTexture("assets\\Prop\\Item\\Apple.png", 0, 1000);
		this->Field.object("Apple")->setSpriteTexture(0, 0);
		this->Field.object("Apple")->setSpriteSize(0.05);
		this->Field.object("Apple")->setImgHeight(1000);
		this->Field.object("Apple")->setImgWidth(1000);
		this->Field.object("Apple")->setPosX(700 - 1000 * 0.1 * 1 / 2);
		this->Field.object("Apple")->setOffsetPosX(0.25);
		this->Field.object("Apple")->setPosY(400-5);

		for (int i = 0; i < this->Field.entityNumber(); i++) {
			if (this->Field.objectAt(i)->type() == "Static" && this->Field.objectAt(i)->nowIs() != "Elon") {
				this->DrawField_Static.push_back(this->Field.objectAt(i));
			}
		}

	}
	double ObjectDis(Object* A, Object* B) {
		return sqrt(pow((A->PosX() - B->PosX()), 2) + pow((A->PosY() - B->PosY()), 2));
	}
public:
	Map Field;
	vector<Object*> DrawField_Dynamic;
	vector<Object*> DrawField_Static;
	bool pass = true;
	gameEngine() {
		this->initVar();
		this->initWindow();
		this->initObject();

	}
	virtual ~gameEngine() {
		delete this->window;
	}
	const bool ObjIsOnSight(Object* charactor, Object* B, double range) {
		if (abs(charactor->PosX() - B->PosX()) < range && abs(charactor->PosY() - B->PosY()) < range) {
			return true;
		}
		else {
			return false;
		}
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
		this->Field.object("Anchor")->moveY(1 * this->move_speed);
	}
	void A_key() {
		this->Field.object("Anchor")->moveX(1 * this->move_speed);
		this->Field.object("Elon")->flipTexture(-1);
	}
	void S_key() {
		this->Field.object("Anchor")->moveY(-1 * this->move_speed);
	}
	void D_key() {
		this->Field.object("Anchor")->moveX(-1 * this->move_speed);
		this->Field.object("Elon")->flipTexture(1);
	}
	void Idle() {
		this->Field.object("Elon")->setSpriteTexture(0,1);
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
				this->move_speed = 1 * 2;

			}
			if (ev.type == Event::KeyReleased && ev.key.code == Keyboard::LShift) {
				this->move_speed = 1;

			}
		}

	}
	void update() {
		int updated = false;
		this->pollEvents();
		if (W || A || S || D) {
			if (this->move_speed == 1 * 2) {
				this->Field.object("Elon")->UpdateAnimation(2);
			}
			if (S) {
				S_key();
				if (!updated) {
					updated = true;
					this->Field.object("Elon")->UpdateAnimation(1);
				}
			}
			if (W) {
				W_key();
				if (!updated) {
					updated = true;
					this->Field.object("Elon")->UpdateAnimation(1);
				}
			}
			if (D) {
				D_key();
				if (!updated) {
					updated = true;
					this->Field.object("Elon")->UpdateAnimation(1);
				}
			}
			if (A) {
				A_key();
				if (!updated) {
					updated = true;
					this->Field.object("Elon")->UpdateAnimation(1);
				}
			}
		}
		else {
			Idle();
			this->Field.object("Elon")->resetTimeSeq();
		}
		//printf("%d | %.0llf, %.0llf | %.0llf, %.0llf |  \n", this->DrawField.size(), this->Field.object("Elon")->PosX(), this->Field.object("Elon")->PosY(), this->Field.object("0")->PosX(), this->Field.object("0")->PosY());
		for (int i = 0; i < Field.entityNumber(); i++) {
				if (this->Field.objectAt(i)->type() == "Dynamic" && i < Field.entityNumber()) {
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
		for (int i = 0; i < DrawField_Dynamic.size() && DrawField_Dynamic[i]; i++) {
			this->window->draw(this->DrawField_Dynamic[i]->getSprite());
		}
		for (int i = 0; i < DrawField_Static.size() && DrawField_Static[i]; i++) {
			this->window->draw(this->DrawField_Static[i]->getSprite());
		}
		//printf("%f, %f\n", this->dui.getPosX(), this->dui.getPosY());

		this->window->display();
	}
	void sort() {

	}
};

gameEngine First_step;

void SortObj() {
	while (First_step.isRuning()) {
		while (First_step.DrawField_Dynamic.size() == 0) {
			Sleep(1);
		}
		for (int i = 0; i < First_step.DrawField_Dynamic.size() - 1; i++) {
			if ( i < First_step.DrawField_Dynamic.size() - 1 && (First_step.DrawField_Dynamic[i]->PosY() + (First_step.DrawField_Dynamic[i]->getImgHeight() * First_step.DrawField_Dynamic[i]->getSize()) > First_step.DrawField_Dynamic[i + 1]->PosY() + (First_step.DrawField_Dynamic[i + 1]->getImgHeight() * First_step.DrawField_Dynamic[i + 1]->getSize()))) {
				iter_swap(&First_step.DrawField_Dynamic[i], &First_step.DrawField_Dynamic[i + 1]);
			}
		}
	}
}

void CheckInsight() {
	while (First_step.isRuning()) {
		while (First_step.Field.entityNumber() == 0) {
			Sleep(1);
		}
		for (int i = 0; i < First_step.Field.entityNumber(); i++) {
			if ((First_step.Field.objectAt(i)->type() != "Static" || First_step.Field.objectAt(i)->nowIs() == "Elon") && !(std::find(First_step.DrawField_Dynamic.begin(), First_step.DrawField_Dynamic.end(), First_step.Field.objectAt(i)) != First_step.DrawField_Dynamic.end()) && (First_step.ObjIsOnSight(First_step.Field.object("Elon"), First_step.Field.objectAt(i), 1500) || First_step.Field.objectAt(i)->nowIs() == "Anchor" || First_step.Field.objectAt(i)->nowIs() == "BG" || First_step.Field.objectAt(i)->nowIs() == "Elon")) {
				First_step.DrawField_Dynamic.push_back(First_step.Field.objectAt(i));
			}
		}
		for (int i = 0; i < First_step.DrawField_Dynamic.size(); i++) {
			if (!(First_step.ObjIsOnSight(First_step.Field.object("Elon"), First_step.DrawField_Dynamic[i], 1500) || First_step.DrawField_Dynamic[i]->nowIs() == "Anchor" || First_step.DrawField_Dynamic[i]->nowIs() == "BG" || First_step.DrawField_Dynamic[i]->nowIs() == "Elon")) {
				First_step.DrawField_Dynamic.erase(First_step.DrawField_Dynamic.begin() + i);
			}
		}
		for (int i = 0; i < First_step.DrawField_Dynamic.size() - 1; i++) {
			if (i < First_step.DrawField_Dynamic.size() - 1 && (First_step.DrawField_Dynamic[i]->PosY() + (First_step.DrawField_Dynamic[i]->getImgHeight() * First_step.DrawField_Dynamic[i]->getSize()) > First_step.DrawField_Dynamic[i + 1]->PosY() + (First_step.DrawField_Dynamic[i + 1]->getImgHeight() * First_step.DrawField_Dynamic[i + 1]->getSize()))) {
				iter_swap(&First_step.DrawField_Dynamic[i], &First_step.DrawField_Dynamic[i + 1]);
			}
		}
	}
}

int main() { // Game loop
	Thread CheckInsight_Thread1(&CheckInsight);
	CheckInsight_Thread1.launch();
	//CheckInsight_Thread2.launch();
	while (First_step.isRuning()) {
		First_step.update();
		First_step.render();
	}
	return 0;
}
