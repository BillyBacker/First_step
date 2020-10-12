#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/OpenGL.hpp>
#include<thread>
#include<math.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<typeinfo>
#include<random>
#include<windows.h>
#include<unordered_map> 
#include <time.h>

using namespace sf;
using namespace std;
const vector<float> getHitVector(float, float, float, float);

void Break() {
	while (true) {
		Sleep(1000);
		printf("Happyliy\n");
		continue;
	}
}


unsigned int randSeed() {
	int* i = new int;
	int* val = i;
	delete i;
	return (unsigned int)val;
}

class strDic { // string tuple for store array of string.
public:
	unordered_map<string, string> map;
	string get(string keyIn) {
		return this->map[keyIn];
	}
	void set(string keyIn, string In) {
		this->map[keyIn] = In;
	}
	void append(string keyIn, string In) {
		this->map[keyIn] = In;
	}
	void remove(string keyIn) {
		this->map.erase(keyIn);
	}
	unsigned __int64 length() {
		return this->map.size();
	}
};

class fltDic { // string tuple for store array of string.
public:
	unordered_map<string, float> map;
	float get(string keyIn) {
		return this->map[keyIn];
	}
	void set(string keyIn, float In) {
		this->map[keyIn] = In;
	}
	void append(string keyIn, float In) {
		this->map[keyIn] = In;
	}
	void remove(string keyIn) {
		this->map.erase(keyIn);
	}
	void incread(string keyIn, int In) {
		this->map[keyIn]+=In;
	}
	unsigned __int64 length() {
		return this->map.size();
	}
};

class Object {
private:
	string Type = "Dynamic";
	unsigned __int64 ID;
	string Name;
	fltDic Stat;
	float posX = 0;
	float posY = 0;
	Sprite sprite;
	float Size[2];
	int imgHeight;
	int imgWidth;

	int time = 0, Index = 0;
	unordered_map<string, vector<Texture*>> textureArray;
	unordered_map<string, vector<int>> duration;
	string slot;
public:
	bool loop = false;
	bool passable = true;
	bool fliping = false;
	float offsetPosX = 0;
	float offsetPosY = 0;
	string tag = "None";
	bool usable = true;
	Object(unsigned __int64 ID) {
		this->ID = ID;
	}
	void useStat(Object In) {
		this->textureArray = In.textureArray;
		this->duration = In.duration;
		this->fliping = In.fliping;
		this->setImgDim(In.imgWidth, In.imgHeight);
		this->loop = In.loop;
		this->passable = In.passable;
		this->setPosX(In.posX);
		this->setPosY(In.posY);
		this->setSpriteSize(In.getSizeX(), In.getSizeY());
		this->Stat = In.Stat;
		this->Type = In.Type;
		this->sprite = In.sprite;
		this->slot = In.slot;
		this->tag = In.tag;
	}
	vector<float> getHitBoxData() {
		return { this->PosX() - (this->getImgWigth() * this->Size[0] / 2), this->PosY(), this->PosX() + (this->getImgWigth() * this->Size[0] / 2), this->PosY() + (this->getImgHeight() * this->Size[1] * 3 / 10) , this->PosX(), this->PosY() + (this->getImgHeight() * this->Size[1]) / 2 };
	}
	void isPassable(bool In) {
		this->passable = In;
	}
	void setAnimationSeq(string Slot) {
		this->slot = Slot;
	}
	int getImgHeight() {
		return this->imgHeight;
	}
	int getImgWigth() {
		return this->imgWidth;
	}
	void setImgDim(int Width, int Height) {
		this->imgHeight = Height;
		this->imgWidth = Width;
		const float halfW = Width / 2; // setOrigin required it.
		const float halfH = Height / 2; // setOrigin required it.
		this->sprite.setOrigin({ halfW , halfH });
	}
	string type() {
		return this->Type;
	}
	void setType(string In) {
		this->Type = In;
	}
	unsigned __int64 getID() {
		return this->ID;
	}
	void addTexture(string Path, string seqName, int durt) {
		Texture* ptr = new Texture;
		if (!(*ptr).loadFromFile(Path)) {
			printf("Error");
		}
		ptr->setSmooth(true);
		int old_size = this->textureArray.size();
		this->textureArray[seqName].push_back(ptr);
		this->duration[seqName].push_back(durt);

	}
	void setSpriteTexture(string seqName, unsigned long long Index) {
		this->sprite.setTexture(*this->textureArray[seqName][Index]);
	}
	void setSpriteSize(float scalex, float scaley) {
		this->sprite.setScale(scalex, scaley);
		this->Size[0] = scalex;
		this->Size[1] = scaley;
	}
	float getSizeX() {
		return this->Size[0];
	}
	float getSizeY() {
		return this->Size[1];
	}
	void addStat(string KeyIn, float val) {
		Stat.append(KeyIn, val);
	}
	void incread(string KeyIn, int amount) {
		this->Stat.incread(KeyIn, amount);
	}
	float getStat(string KeyIn) {
		return Stat.get(KeyIn);
	}
	void setOffsetPosX(float offx) {
		this->offsetPosX = offx;
	}
	void setOffsetPosY(float offy) {
		this->offsetPosY = offy;
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
	float OrigPosX() {
		return this->posX;
	}
	float OrigPosY() {
		return this->posY;
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
		this->time += speed;
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
		this->time = 0;
	}
	void flipTexture(int rev) {
		this->fliping = !this->fliping;
		this->sprite.setScale(rev * this->Size[0], this->Size[1]);
	}
	void setStat(string key, float value) {
		this->Stat.set(key, value);
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
	unordered_map<string, Object*> Tuple;
	unordered_map<string, Object*> Templ;
	unordered_map<unsigned __int64, string> Tuplekey, Templkey;
	void createTemplate(string name) {
		Object* p = new Object(this->Templ.size());
		p->Is(name);
		this->Templ[name] = p;
		Templkey[this->Templ.size()] = name;
	}
	void registerObject(string Name, string Template) {
		Object* p = new Object(this->Tuple.size());
		(*p).useStat(*this->Template(Template));
		(*p).Is(Name);
		this->Tuple[Name] = p;
		this->Tuplekey[this->Tuple.size() - 1] = Name;
	}
	Object* object(string keyIn) {
		return Tuple[keyIn];
	}
	Object* Template(string keyIn) {
		return Templ[keyIn];
	}
	Object* objectAt(unsigned __int64 Index) {
		return this->Tuple[Tuplekey[Index]];
	}
	void remove(string keyIn) {
		this->Tuple.erase(keyIn);
	}
	void removeObjAt(unsigned __int64 Index) {
		cout << this->Tuplekey[Index] << endl;
		this->Tuple.erase(this->Tuplekey[Index]);
	}
	unsigned __int64 entityNumber() {
		return this->Tuple.size();
	}
	string objectTypeAt(unsigned __int64 Index) {
		return this->objectAt(Index)->nowIs();
	}
	unordered_map<string, Object*> getTuple() {
		return this->Tuple;
	}

};

class strMap {
public:
	unordered_map<string, Font> font;
	unordered_map<string, Text*> Tuple;
	unordered_map<string, string> Tag;
	unordered_map<unsigned __int64, string> Tuplekey;
	void registerObject(string Name, string tag) {
		Text* p = new Text;
		this->Tuple[Name] = p;
		this->Tag[Name] = tag;
		this->Tuplekey[this->Tuple.size()-1] = Name;
	}
	void addFont(string name, string path) {
		font[name].loadFromFile(path);
	}
	Font Font(string name) {
		return this->font[name];
	}
	Text* object(string keyIn) {
		return this->Tuple[keyIn];
	}
	Text* objectAt(unsigned __int64 Index) {
		return this->Tuple[this->Tuplekey[Index]];
	}
	void remove(string keyIn) {
		this->Tuple.erase(keyIn);
	}
	string tag(string keyIn) {
		return this->Tag[keyIn];
	}
	void removeObjAt(unsigned __int64 Index) {
		cout << this->Tuplekey[Index] << endl;
		this->Tuple.erase(this->Tuplekey[Index]);
	}
	unsigned __int64 entityNumber() {
		return this->Tuple.size();
	}
	unordered_map<string, Text*> getTuple() {
		return this->Tuple;
	}

};

class gameEngine { //this a main class of this game. resposibility for render object, recieve input event, draw graphic.
private:
	//Add a variable down here.
	int h = 900;
	int w = 1600;
	bool running = true;
	Event ev;
	VideoMode mode;
	int i = 0;
	Map itemList;
	ContextSettings settings;
	void initVar() {
		this->window = nullptr;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 9; j++) {
				this->InventoryHitbox[i][j][0] = round(500 + 1100 * 0.06 * j); 
				this->InventoryHitbox[i][j][1] = round(200 + 1100 * 0.06 * i);
				this->InventoryHitbox[i][j][2] = round(560 + 1100 * 0.06 * j);
				this->InventoryHitbox[i][j][3] = round(260 + 1100 * 0.06 * i);
			}
		}
		for (int i = 0; i < 9; i++) {
			this->InventoryHitbox[3][i][0] = round(500 + 1100 * 0.06 * i);
			this->InventoryHitbox[3][i][1] = round(435 + 1100 * 0.06);
			this->InventoryHitbox[3][i][2] = round(560 + 1100 * 0.06 * i);
			this->InventoryHitbox[3][i][3] = round(495 + 1100 * 0.06);
		}
	}
	void initWindow() {
		this->mode.height = h;
		this->mode.width = w;
		this->settings.antialiasingLevel = 100;
		this->window = new RenderWindow(this->mode, "First Step", Style::Titlebar | Style::Close, this->settings);
		(*this->window).setVerticalSyncEnabled(true);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glMatrixMode(GL_PROJECTION);

	}
	void initItem() {
		for (int i = 0; i < 9; i++) {
			Object* ptr = new Object(rand() % 10000);
			ptr->setImgDim(1000, 1000);
			ptr->setPosX(503 + 1100 * 0.06 * i);
			ptr->setPosY(800);
			ptr->Is("None");
			this->DrawField["ItemUseSlot"].push_back(ptr);
			this->DrawField["InventoryUseSlot"].push_back(ptr);
			ItemUseSlotQuantity.push_back(0);
		}
		for (int i = 0; i < 3; i++) {
			Backpack.push_back({});
			BackpackQuantity.push_back({});
			for (int j = 0; j < 9; j++) {
				Object* ptr = new Object(rand() % 10000);
				ptr->setImgDim(1000, 1000);
				ptr->setPosX(200+1000*0.06*i);
				ptr->setPosY(503+1000*0.06*j);
				ptr->Is("None");
				Backpack[i].push_back(ptr);
				BackpackQuantity[i].push_back(0);
			}
		}
		this->itemList.createTemplate("Item");
		this->itemList.Template("Item")->setSpriteSize(0.06, 0.06);
		this->itemList.Template("Item")->setImgDim(1000, 1000);
		this->itemList.Template("Item")->addStat("showCount", 1);

		this->itemList.createTemplate("Tool");
		this->itemList.Template("Tool")->setSpriteSize(0.06, 0.06);
		this->itemList.Template("Tool")->setImgDim(1000, 1000);
		this->itemList.Template("Tool")->addStat("showCount", 0);

		// Item registeration section
		this->itemList.registerObject("Herb", "Item");
		this->itemList.object("Herb")->addTexture("assets\\Prop\\Item\\Herb.png", "default", 1000);
		this->itemList.object("Herb")->setSpriteTexture("default", 0);
		this->itemList.object("Herb")->tag = "Medicine";

		this->itemList.registerObject("Apple", "Item");
		this->itemList.object("Apple")->addTexture("assets\\Prop\\Item\\Apple.png", "default", 1000);
		this->itemList.object("Apple")->setSpriteTexture("default", 0);
		this->itemList.object("Apple")->tag = "Food";

		this->itemList.registerObject("Hydro Flask", "Item");
		this->itemList.object("Hydro Flask")->addTexture("assets\\Prop\\Item\\Hydro_Flask.png", "default", 1000);
		this->itemList.object("Hydro Flask")->setSpriteTexture("default", 0);
		this->itemList.object("Hydro Flask")->tag = "Drink";

		this->itemList.registerObject("Composite Metal", "Item");
		this->itemList.object("Composite Metal")->addTexture("assets\\Prop\\Item\\metalPlate.png", "default", 1000);
		this->itemList.object("Composite Metal")->setSpriteTexture("default", 0);
		this->itemList.object("Composite Metal")->tag = "Material";

		this->itemList.registerObject("Arclyic", "Item");
		this->itemList.object("Arclyic")->addTexture("assets\\Prop\\Item\\Arclyic.png", "default", 1000);
		this->itemList.object("Arclyic")->setSpriteTexture("default", 0);
		this->itemList.object("Arclyic")->tag = "Material";

		this->itemList.registerObject("Aluminium Plate", "Item");
		this->itemList.object("Aluminium Plate")->addTexture("assets\\Prop\\Item\\AluminiumPlate.png", "default", 1000);
		this->itemList.object("Aluminium Plate")->setSpriteTexture("default", 0);
		this->itemList.object("Aluminium Plate")->tag = "Material";

		this->itemList.registerObject("Bread", "Item");
		this->itemList.object("Bread")->addTexture("assets\\Prop\\Item\\Bread.png", "default", 1000);
		this->itemList.object("Bread")->setSpriteTexture("default", 0);
		this->itemList.object("Bread")->tag = "Food";

		this->itemList.registerObject("Carrot", "Item");
		this->itemList.object("Carrot")->addTexture("assets\\Prop\\Item\\Carrot.png", "default", 1000);
		this->itemList.object("Carrot")->setSpriteTexture("default", 0);
		this->itemList.object("Carrot")->tag = "Food";

		this->itemList.registerObject("Carrot Seed", "Item");
		this->itemList.object("Carrot Seed")->addTexture("assets\\Prop\\Item\\CarrotSeed.png", "default", 1000);
		this->itemList.object("Carrot Seed")->setSpriteTexture("default", 0);
		this->itemList.object("Carrot Seed")->tag = "Material";

		this->itemList.registerObject("Copper Nugget", "Item");
		this->itemList.object("Copper Nugget")->addTexture("assets\\Prop\\Item\\CopperNugget.png", "default", 1000);
		this->itemList.object("Copper Nugget")->setSpriteTexture("default", 0);
		this->itemList.object("Copper Nugget")->tag = "Material";

		this->itemList.registerObject("Copper Plate", "Item");
		this->itemList.object("Copper Plate")->addTexture("assets\\Prop\\Item\\CopperPlate.png", "default", 1000);
		this->itemList.object("Copper Plate")->setSpriteTexture("default", 0);
		this->itemList.object("Copper Plate")->tag = "Material";

		this->itemList.registerObject("Copper Wire", "Item");
		this->itemList.object("Copper Wire")->addTexture("assets\\Prop\\Item\\CopperWire.png", "default", 1000);
		this->itemList.object("Copper Wire")->setSpriteTexture("default", 0);
		this->itemList.object("Copper Wire")->tag = "Material";

		this->itemList.registerObject("Flour", "Item");
		this->itemList.object("Flour")->addTexture("assets\\Prop\\Item\\Flour.png", "default", 1000);
		this->itemList.object("Flour")->setSpriteTexture("default", 0);
		this->itemList.object("Flour")->tag = "Material";

		this->itemList.registerObject("Gold Nugget", "Item");
		this->itemList.object("Gold Nugget")->addTexture("assets\\Prop\\Item\\GoldNugget.png", "default", 1000);
		this->itemList.object("Gold Nugget")->setSpriteTexture("default", 0);
		this->itemList.object("Gold Nugget")->tag = "Material";

		this->itemList.registerObject("Gold Plate", "Item");
		this->itemList.object("Gold Plate")->addTexture("assets\\Prop\\Item\\GoldPlate.png", "default", 1000);
		this->itemList.object("Gold Plate")->setSpriteTexture("default", 0);
		this->itemList.object("Gold Plate")->tag = "Material";

		this->itemList.registerObject("Gold Wire", "Item");
		this->itemList.object("Gold Wire")->addTexture("assets\\Prop\\Item\\GoldWire.png", "default", 1000);
		this->itemList.object("Gold Wire")->setSpriteTexture("default", 0);
		this->itemList.object("Gold Wire")->tag = "Material";

		this->itemList.registerObject("Herb Seed", "Item");
		this->itemList.object("Herb Seed")->addTexture("assets\\Prop\\Item\\HerbSeed.png", "default", 1000);
		this->itemList.object("Herb Seed")->setSpriteTexture("default", 0);
		this->itemList.object("Herb Seed")->tag = "Material";

		this->itemList.registerObject("MRE", "Item");
		this->itemList.object("MRE")->addTexture("assets\\Prop\\Item\\MRE.png", "default", 1000);
		this->itemList.object("MRE")->setSpriteTexture("default", 0);
		this->itemList.object("MRE")->tag = "Food";

		this->itemList.registerObject("Plastic", "Item");
		this->itemList.object("Plastic")->addTexture("assets\\Prop\\Item\\Plastic.png", "default", 1000);
		this->itemList.object("Plastic")->setSpriteTexture("default", 0);
		this->itemList.object("Plastic")->tag = "Material";

		this->itemList.registerObject("Titanium Nugget", "Item");
		this->itemList.object("Titanium Nugget")->addTexture("assets\\Prop\\Item\\TitaniumNugget.png", "default", 1000);
		this->itemList.object("Titanium Nugget")->setSpriteTexture("default", 0);
		this->itemList.object("Titanium Nugget")->tag = "Material";

		this->itemList.registerObject("Titanium Plate", "Item");
		this->itemList.object("Titanium Plate")->addTexture("assets\\Prop\\Item\\TitaniumPlate.png", "default", 1000);
		this->itemList.object("Titanium Plate")->setSpriteTexture("default", 0);
		this->itemList.object("Titanium Plate")->tag = "Material";

		this->itemList.registerObject("Wheat Grain", "Item");
		this->itemList.object("Wheat Grain")->addTexture("assets\\Prop\\Item\\WheatGrain.png", "default", 1000);
		this->itemList.object("Wheat Grain")->setSpriteTexture("default", 0);
		this->itemList.object("Wheat Grain")->tag = "Material";

		this->itemList.registerObject("Wheat Seed", "Item");
		this->itemList.object("Wheat Seed")->addTexture("assets\\Prop\\Item\\WheatSeed.png", "default", 1000);
		this->itemList.object("Wheat Seed")->setSpriteTexture("default", 0);
		this->itemList.object("Wheat Seed")->tag = "Material";

		this->itemList.registerObject("Drill", "Tool");
		this->itemList.object("Drill")->addTexture("assets\\Prop\\Item\\drill.png", "default", 1000);
		this->itemList.object("Drill")->setSpriteTexture("default", 0);
		this->itemList.object("Drill")->tag = "Tool";

		this->itemList.registerObject("Shovel", "Tool");
		this->itemList.object("Shovel")->addTexture("assets\\Prop\\Item\\Shovel.png", "default", 1000);
		this->itemList.object("Shovel")->setSpriteTexture("default", 0);
		this->itemList.object("Shovel")->tag = "Tool";

		this->itemList.registerObject("Hammer", "Tool");
		this->itemList.object("Hammer")->addTexture("assets\\Prop\\Item\\Hammer.png", "default", 1000);
		this->itemList.object("Hammer")->setSpriteTexture("default", 0);
		this->itemList.object("Hammer")->tag = "Tool";

		// Default item
		this->DrawField["ItemUseSlot"][2] = itemList.object("Hydro Flask");
		this->ItemUseSlotQuantity[2] = 100;
		this->DrawField["ItemUseSlot"][6] = itemList.object("MRE");
		this->ItemUseSlotQuantity[6] = 10;
		this->DrawField["ItemUseSlot"][7] = itemList.object("Gold Wire");
		this->ItemUseSlotQuantity[7] = 100;
		this->DrawField["ItemUseSlot"][8] = itemList.object("Hammer");
		this->ItemUseSlotQuantity[8] = 100;
		this->DrawField["ItemUseSlot"][4] = itemList.object("Arclyic");
		this->ItemUseSlotQuantity[4] = 100;
		this->DrawField["ItemUseSlot"][5] = itemList.object("Composite Metal");
		this->ItemUseSlotQuantity[5] = 100;

		this->Backpack[0][0] = itemList.object("Wheat Grain");
		this->BackpackQuantity[0][0] = 100;

		this->Backpack[2][7] = itemList.object("Gold Nugget");
		this->BackpackQuantity[2][7] = 53;

		this->Backpack[1][5] = itemList.object("Bread");
		this->BackpackQuantity[1][5] = 53;
	}
	void intitDialog() {
		this->Dialog["Font"].addFont("Mitr-Regular", "assets\\font\\Mitr-Regular.ttf");
		this->Dialog["Font"].addFont("Mitr-Bold", "assets\\font\\Mitr-Bold.ttf");

		this->Dialog["PausedMenu"].registerObject("BackToGame", "PausedMenu");
		this->Dialog["PausedMenu"].object("BackToGame")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["PausedMenu"].object("BackToGame")->setCharacterSize(50);
		this->Dialog["PausedMenu"].object("BackToGame")->setString("Back to game");
		this->Dialog["PausedMenu"].object("BackToGame")->setPosition({ 250,200 });

		this->Dialog["PausedMenu"].registerObject("ExitGame", "PausedMenu");
		this->Dialog["PausedMenu"].object("ExitGame")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["PausedMenu"].object("ExitGame")->setCharacterSize(50);
		this->Dialog["PausedMenu"].object("ExitGame")->setString("Exit this game");
		this->Dialog["PausedMenu"].object("ExitGame")->setPosition({ 250,600 });

		this->Dialog["InGameStatus"].registerObject("ItemInHand", "InGameStatus");
		this->Dialog["InGameStatus"].object("ItemInHand")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["InGameStatus"].object("ItemInHand")->setCharacterSize(30);
		this->Dialog["InGameStatus"].object("ItemInHand")->setPosition({ 750,750 });

		for (int i = 0; i < 9; i++) {
			this->Dialog["itemCount"].registerObject("itemCountBG"+to_string(i), "itemCountBG");
			this->Dialog["itemCount"].registerObject("itemCount" + to_string(i), "itemCount");

			this->Dialog["itemCount"].object("itemCountBG" + to_string(i))->setFont(this->Dialog["Font"].font["Mitr-Bold"]);
			this->Dialog["itemCount"].object("itemCountBG" + to_string(i))->setCharacterSize(25);
			this->Dialog["itemCount"].object("itemCountBG" + to_string(i))->setString(to_string(i));
			this->Dialog["itemCount"].object("itemCountBG" + to_string(i))->setStyle(Text::Bold);
			this->Dialog["itemCount"].object("itemCountBG" + to_string(i))->setFillColor(Color::White);

			this->Dialog["itemCount"].object("itemCount" + to_string(i))->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
			this->Dialog["itemCount"].object("itemCount" + to_string(i))->setCharacterSize(25);
			this->Dialog["itemCount"].object("itemCount" + to_string(i))->setString(to_string(i));
			this->Dialog["itemCount"].object("itemCount" + to_string(i))->setFillColor(Color::Black);
			const float x = 525 + 1100.0 * 0.06 * i, y = 840;
			this->Dialog["itemCount"].object("itemCount" + to_string(i))->setPosition({ x ,y});
			this->Dialog["itemCount"].object("itemCountBG" + to_string(i))->setPosition({ x ,y});
		}

		this->Dialog["itemUse"].registerObject("metalUse_pump", "BuildingMenu");
		this->Dialog["itemUse"].object("metalUse_pump")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["itemUse"].object("metalUse_pump")->setCharacterSize(50);
		this->Dialog["itemUse"].object("metalUse_pump")->setString("10");
		this->Dialog["itemUse"].object("metalUse_pump")->setPosition({ 550,210 });

		this->Dialog["itemUse"].registerObject("metalUse_Arclyic", "BuildingMenu");
		this->Dialog["itemUse"].object("metalUse_Arclyic")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["itemUse"].object("metalUse_Arclyic")->setCharacterSize(50);
		this->Dialog["itemUse"].object("metalUse_Arclyic")->setString("5");
		this->Dialog["itemUse"].object("metalUse_Arclyic")->setPosition({ 650,210 });

		for (int i = 0; i < 9; i++) {
			this->Dialog["InventoryItem_hotbar"].registerObject("InventoryitemCountBG_hotbar" + to_string(i), "itemCountBG");
			this->Dialog["InventoryItem_hotbar"].registerObject("InventoryitemCount_hotbar" + to_string(i), "itemCount");

			this->Dialog["InventoryItem_hotbar"].object("InventoryitemCountBG_hotbar" + to_string(i))->setFont(this->Dialog["Font"].font["Mitr-Bold"]);
			this->Dialog["InventoryItem_hotbar"].object("InventoryitemCountBG_hotbar" + to_string(i))->setCharacterSize(25);
			this->Dialog["InventoryItem_hotbar"].object("InventoryitemCountBG_hotbar" + to_string(i))->setString(to_string(i));
			this->Dialog["InventoryItem_hotbar"].object("InventoryitemCountBG_hotbar" + to_string(i))->setStyle(Text::Bold);
			this->Dialog["InventoryItem_hotbar"].object("InventoryitemCountBG_hotbar" + to_string(i))->setFillColor(Color::White);

			this->Dialog["InventoryItem_hotbar"].object("InventoryitemCount_hotbar" + to_string(i))->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
			this->Dialog["InventoryItem_hotbar"].object("InventoryitemCount_hotbar" + to_string(i))->setCharacterSize(25);
			this->Dialog["InventoryItem_hotbar"].object("InventoryitemCount_hotbar" + to_string(i))->setString(to_string(i));
			this->Dialog["InventoryItem_hotbar"].object("InventoryitemCount_hotbar" + to_string(i))->setFillColor(Color::Black);
			const float x = 525 + 1100.0 * 0.06 * i, y = 533;
			this->Dialog["InventoryItem_hotbar"].object("InventoryitemCount_hotbar" + to_string(i))->setPosition({ x ,y });
			this->Dialog["InventoryItem_hotbar"].object("InventoryitemCountBG_hotbar" + to_string(i))->setPosition({ x ,y });
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 9; j++) {
				this->Dialog["InventoryItem"].registerObject("InventoryitemCountBG" + to_string(i) + to_string(j), "itemCountBG");
				this->Dialog["InventoryItem"].registerObject("InventoryitemCount" + to_string(i) + to_string(j), "itemCount");

				this->Dialog["InventoryItem"].object("InventoryitemCountBG" + to_string(i) + to_string(j))->setFont(this->Dialog["Font"].font["Mitr-Bold"]);
				this->Dialog["InventoryItem"].object("InventoryitemCountBG" + to_string(i) + to_string(j))->setCharacterSize(25);
				this->Dialog["InventoryItem"].object("InventoryitemCountBG" + to_string(i) + to_string(j))->setString(to_string(i));
				this->Dialog["InventoryItem"].object("InventoryitemCountBG" + to_string(i) + to_string(j))->setStyle(Text::Bold);
				this->Dialog["InventoryItem"].object("InventoryitemCountBG" + to_string(i) + to_string(j))->setFillColor(Color::White);

				this->Dialog["InventoryItem"].object("InventoryitemCount" + to_string(i) + to_string(j))->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
				this->Dialog["InventoryItem"].object("InventoryitemCount" + to_string(i) + to_string(j))->setCharacterSize(25);
				this->Dialog["InventoryItem"].object("InventoryitemCount" + to_string(i) + to_string(j))->setString(to_string(i));
				this->Dialog["InventoryItem"].object("InventoryitemCount" + to_string(i) + to_string(j))->setFillColor(Color::Black);
				const float x = 200 + 1100 * 0.06 * i, y = 503 + 1100 * 0.06 * j;
				this->Dialog["InventoryItem"].object("InventoryitemCount" + to_string(i) + to_string(j))->setPosition({ x ,y });
				this->Dialog["InventoryItem"].object("InventoryitemCountBG" + to_string(i) + to_string(j))->setPosition({ x ,y });
			}
		}
		

	}
	void initObject() {

		this->Field.createTemplate("Blank");

		this->Field.createTemplate("Item");
		this->Field.Template("Item")->addTexture("assets\\Prop\\Item\\Apple.png", "default", 1000);
		this->Field.Template("Item")->setSpriteTexture("default", 0);
		this->Field.Template("Item")->setSpriteSize(0.005, 0.005);
		this->Field.Template("Item")->setImgDim(1000, 1000);
		this->Field.Template("Item")->setType("Static");

		this->Field.createTemplate("Rocky");
		this->Field.Template("Rocky")->addTexture("assets\\Prop\\Rock\\Rock1.png", "default0", 1000);
		this->Field.Template("Rocky")->addTexture("assets\\Prop\\Rock\\Rock2.png", "default1", 1000);
		this->Field.Template("Rocky")->addTexture("assets\\Prop\\Rock\\Rock3.png", "default2", 1000);
		this->Field.Template("Rocky")->setSpriteTexture("default1", 0);
		this->Field.Template("Rocky")->setSpriteSize(0.1, 0.1);
		this->Field.Template("Rocky")->setImgDim(900, 900);
		this->Field.Template("Rocky")->isPassable(false);
		this->Field.Template("Rocky")->setType("Dynamic");

		this->Field.createTemplate("BG_Element");
		this->Field.Template("BG_Element")->setType("Dynamic");
		this->Field.Template("BG_Element")->setPosX(0);
		this->Field.Template("BG_Element")->setPosY(0);

		this->Field.registerObject("Anchor", "BG_Element");
		this->Field.object("Anchor")->setPosX(-3000);
		this->Field.object("Anchor")->setPosY(-3000);
		this->Field.object("Anchor")->isPassable(true);
		this->Anchor = this->Field.object("Anchor");

		this->Field.createTemplate("dropItem");
		this->Field.Template("dropItem")->addTexture("assets\\Prop\\Item\\Herb.png", "Herb", 1000);
		this->Field.Template("dropItem")->addTexture("assets\\Prop\\Item\\Apple.png", "Apple", 1000);
		this->Field.Template("dropItem")->setSpriteTexture("Apple", 0);
		this->Field.Template("dropItem")->setSpriteSize(0.1, 0.1);
		this->Field.Template("dropItem")->setImgDim(1000, 1000);
		this->Field.Template("dropItem")->setType("Dynamic");

		for (int i = 0; i < 50; i++) {
			this->Field.registerObject("Apple_" + to_string(i), "dropItem");
			this->Field.object("Apple_" + to_string(i))->setSpriteTexture("Apple", 0);
			this->Field.object("Apple_" + to_string(i))->setOffsetPosX(2000 + rand() % 2000);
			this->Field.object("Apple_" + to_string(i))->setOffsetPosY(2000 + rand() % 2000);
			this->Field.object("Apple_" + to_string(i))->tag = "fallItem";
		}
		for (int i = 0; i < 50; i++) {
			this->Field.registerObject("Herb_" + to_string(i), "dropItem");
			this->Field.object("Herb_" + to_string(i))->setSpriteTexture("Herb", 0);
			this->Field.object("Herb_" + to_string(i))->setOffsetPosX(2000 + rand() % 2000);
			this->Field.object("Herb_" + to_string(i))->setOffsetPosY(2000 + rand() % 2000);
			this->Field.object("Herb_" + to_string(i))->tag = "fallItem";
		}

		this->Field.createTemplate("Structure");
		this->Field.Template("Structure")->setPosX(this->Field.object("Anchor")->PosX());
		this->Field.Template("Structure")->setPosY(this->Field.object("Anchor")->PosY());
		this->Field.Template("Structure")->setType("Dynamic");
		this->Field.Template("Structure")->isPassable(false);

		this->Field.createTemplate("itemFrame");
		this->Field.Template("itemFrame")->addTexture("assets\\Prop\\HUD\\ItemFrameWhite.png", "default", 1000);
		this->Field.Template("itemFrame")->setSpriteTexture("default", 0);
		this->Field.Template("itemFrame")->setSpriteSize(0.06, 0.06);
		this->Field.Template("itemFrame")->setType("Static");
		this->Field.Template("itemFrame")->isPassable(false);

		this->Field.createTemplate("StatBar");
		this->Field.Template("StatBar")->addTexture("assets\\Prop\\HUD\\StatFrame.png", "frame", 1000);
		this->Field.Template("StatBar")->addTexture("assets\\Prop\\HUD\\Health.png", "Stat1", 1000);
		this->Field.Template("StatBar")->addTexture("assets\\Prop\\HUD\\Hunger.png", "Stat2", 1000);
		this->Field.Template("StatBar")->addTexture("assets\\Prop\\HUD\\Thirst.png", "Stat3", 1000);
		this->Field.Template("StatBar")->addTexture("assets\\Prop\\HUD\\Air.png", "Stat4", 1000);
		this->Field.Template("StatBar")->setSpriteTexture("frame", 0);
		this->Field.Template("StatBar")->setSpriteSize(0.06, 0.06);
		this->Field.Template("StatBar")->setType("Static");

		this->Field.createTemplate("Pump");
		this->Field.Template("Pump")->addTexture("assets\\Prop\\Building\\Pumpy.png", "pump", 1000);
		this->Field.Template("Pump")->setSpriteTexture("pump", 0);
		this->Field.Template("Pump")->setSpriteSize(0.1, 0.1);
		this->Field.Template("Pump")->setImgDim(1200, 1600);
		this->Field.Template("Pump")->setPosX(this->Field.object("Anchor")->PosX());
		this->Field.Template("Pump")->setPosY(this->Field.object("Anchor")->PosY());
		this->Field.Template("Pump")->setType("Dynamic");
		this->Field.Template("Pump")->isPassable(false);

		this->Field.createTemplate("SolarCell");
		this->Field.Template("SolarCell")->addTexture("assets\\Prop\\Building\\SolarCell.png", "SolarCell", 1000);
		this->Field.Template("SolarCell")->setSpriteTexture("SolarCell", 0);
		this->Field.Template("SolarCell")->setSpriteSize(0.1, 0.1);
		this->Field.Template("SolarCell")->setImgDim(1200, 1600);
		this->Field.Template("SolarCell")->setPosX(this->Field.object("Anchor")->PosX());
		this->Field.Template("SolarCell")->setPosY(this->Field.object("Anchor")->PosY());
		this->Field.Template("SolarCell")->setType("Dynamic");
		this->Field.Template("SolarCell")->isPassable(false);

		this->Field.createTemplate("Floor");
		this->Field.Template("Floor")->addTexture("assets\\Prop\\Floor\\Floor11.png", "default", 1000);
		this->Field.Template("Floor")->setSpriteTexture("default", 0);
		this->Field.Template("Floor")->setSpriteSize(0.1, 0.1);
		this->Field.Template("Floor")->setImgDim(5000, 5000);
		this->Field.Template("Floor")->setPosX(this->Field.object("Anchor")->PosX());
		this->Field.Template("Floor")->setPosY(this->Field.object("Anchor")->PosY());
		this->Field.Template("Floor")->setType("Dynamic");
		this->Field.Template("Floor")->isPassable(true);
		this->Field.Template("Floor")->tag = "BG";

		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				string ObjName = "Floor" + to_string(i) + "*" + to_string(j);
				this->Field.registerObject(ObjName, "Floor");
				this->Field.object(ObjName)->setOffsetPosX(i * 5000 * 0.1 / 1.1);
				this->Field.object(ObjName)->setOffsetPosY(j * 5000 * 0.1 / 1.1);
			}
		}

		for (int j = 0; j < 50; j++) {
			float size = rand() % 10;
			this->Field.registerObject(to_string(i) + to_string(j), "Rocky");
			this->Field.object(to_string(i) + to_string(j))->setSpriteTexture("default" + to_string(rand() % 3), 0);
			this->Field.object(to_string(i) + to_string(j))->setOffsetPosX(rand() % 5000);
			this->Field.object(to_string(i) + to_string(j))->setOffsetPosY(rand() % 5000);
		}

		this->Field.registerObject("Hut", "Structure");
		this->Field.object("Hut")->addTexture("assets\\Prop\\Building\\SurvivalHut.png", "default", 1000);
		this->Field.object("Hut")->setSpriteTexture("default", 0);
		this->Field.object("Hut")->setSpriteSize(0.1, 0.1);
		this->Field.object("Hut")->setOffsetPosX(2500);
		this->Field.object("Hut")->setOffsetPosY(2500);
		this->Field.object("Hut")->setImgDim(4800, 3200);

		this->Field.registerObject("power", "Structure");
		this->Field.object("power")->addTexture("assets\\Prop\\Building\\Solarcell.png", "default", 1000);
		this->Field.object("power")->setSpriteTexture("default", 0);
		this->Field.object("power")->setSpriteSize(0.1, 0.1);
		this->Field.object("power")->setOffsetPosX(1000);
		this->Field.object("power")->setOffsetPosY(500);
		this->Field.object("power")->setImgDim(1200, 1600);

		this->Field.registerObject("Elon", "Blank");
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk1.png", "walk", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk2.png", "walk", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk3.png", "walk", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk4.png", "walk", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk5.png", "walk", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk4.png", "walk", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk3.png", "walk", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Walk2.png", "walk", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Idle.png", "idle", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Dying1.png", "dying", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Dying2.png", "dying", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Dying3.png", "dying", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Dying4.png", "dying", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Dying5.png", "dying", 8);
		this->Field.object("Elon")->addTexture("assets\\Elon\\Elon_Dying5.png", "dying", 20000000);
		this->Field.object("Elon")->loop = true;
		this->Field.object("Elon")->setSpriteSize(0.1, 0.1);
		this->Field.object("Elon")->setImgDim(1000, 1600);
		this->Field.object("Elon")->addStat("Health", 100);
		this->Field.object("Elon")->addStat("Thirst", 100);
		this->Field.object("Elon")->addStat("Hunger", 100);
		this->Field.object("Elon")->addStat("Air", 100);
		this->Field.object("Elon")->addStat("Alive", 1);
		this->Field.object("Elon")->setPosX(800 - 1000 * 0.1 * 1 / 2);
		this->Field.object("Elon")->setPosY(400);
		this->Field.object("Elon")->setType("Static");
		this->Elon = this->Field.object("Elon");

		//for (int i = 0; i < 11; i++) {
			//for (int j = 0; j < 17; j++) {
				//this->Field.registerObject(to_string(i)+to_string(j), "Item");
				//this->Field.object(to_string(i) + to_string(j))->setPosX(j*100);
				//this->Field.object(to_string(i) + to_string(j))->setPosY(i*100);
			//}
		//}
		for (int i = 0; i < 9; i++) {
			this->Field.registerObject("ItemFrame" + to_string(i), "itemFrame");
			this->Field.object("ItemFrame" + to_string(i))->setPosX(503 + 1100 * 0.06 * i);
			this->Field.object("ItemFrame" + to_string(i))->setPosY(800);

		}

		this->Field.registerObject("ItemPrt", "Blank");
		this->Field.object("ItemPrt")->addTexture("assets\\Prop\\HUD\\ItemPointer.png", "default", 1000);
		this->Field.object("ItemPrt")->setSpriteTexture("default", 0);
		this->Field.object("ItemPrt")->setSpriteSize(0.06, 0.06);
		this->Field.object("ItemPrt")->setImgDim(1100, 1500);
		this->Field.object("ItemPrt")->setPosX(503 + 1100 * 0.06 / 2);
		this->Field.object("ItemPrt")->setPosY(833);
		this->Field.object("ItemPrt")->setType("Static");

		for (int i = 0; i < 4; i++) {
			this->Field.registerObject("StatBar_Fill" + to_string(i), "StatBar");
			this->Field.object("StatBar_Fill" + to_string(i))->setSpriteSize(0.06, -0.06);
			this->Field.object("StatBar_Fill" + to_string(i))->setSpriteTexture("Stat" + to_string(i + 1), 0);
			this->Field.object("StatBar_Fill" + to_string(i))->setPosX(1300 + 500 * 0.1 * i);
			this->Field.object("StatBar_Fill" + to_string(i))->setPosY(600 + 3200 * 0.06);
		}
		for (int i = 0; i < 4; i++) {
			this->Field.registerObject("StatBar" + to_string(i), "StatBar");
			this->Field.object("StatBar" + to_string(i))->setPosX(1300 + 500 * 0.1 * i);
			this->Field.object("StatBar" + to_string(i))->setPosY(600);
		}
	}
	void intitUI() {
		this->Field.createTemplate("PauseUI_BG");
		this->Field.Template("PauseUI_BG")->addTexture("assets\\Prop\\HUD\\Pause.png", "default", 1000);
		this->Field.Template("PauseUI_BG")->setSpriteSize(0.5, 0.5);
		this->Field.Template("PauseUI_BG")->setImgDim(3200, 1800);
		this->Field.Template("PauseUI_BG")->setPosX(800);
		this->Field.Template("PauseUI_BG")->setPosY(450);
		this->Field.Template("PauseUI_BG")->setType("Static");
		this->Field.Template("PauseUI_BG")->tag = "PauseUI";

		this->Field.registerObject("PauseBG", "PauseUI_BG");
		this->Field.object("PauseBG")->setSpriteTexture("default", 0);

		this->Field.createTemplate("BuildUI_BG");
		this->Field.Template("BuildUI_BG")->addTexture("assets\\Prop\\HUD\\Pause.png", "default", 1000);
		this->Field.Template("BuildUI_BG")->setSpriteSize(0.5, 0.5);
		this->Field.Template("BuildUI_BG")->setImgDim(3200, 1800);
		this->Field.Template("BuildUI_BG")->setPosX(800);
		this->Field.Template("BuildUI_BG")->setPosY(450);
		this->Field.Template("BuildUI_BG")->setType("Static");
		this->Field.Template("BuildUI_BG")->tag = "BuildUI";

		this->Field.registerObject("BuildBG", "BuildUI_BG");
		this->Field.object("BuildBG")->setSpriteTexture("default", 0);

		this->Field.createTemplate("Inventory_BG");
		this->Field.Template("Inventory_BG")->addTexture("assets\\Prop\\HUD\\Pause.png", "default", 1000);
		this->Field.Template("Inventory_BG")->setSpriteSize(0.5, 0.5);
		this->Field.Template("Inventory_BG")->setImgDim(3200, 1800);
		this->Field.Template("Inventory_BG")->setPosX(800);
		this->Field.Template("Inventory_BG")->setPosY(450);
		this->Field.Template("Inventory_BG")->setType("Static");
		this->Field.Template("Inventory_BG")->tag = "InventoryUI";

		this->Field.registerObject("InventoryBG", "Inventory_BG");
		this->Field.object("InventoryBG")->setSpriteTexture("default", 0);
		for (int i = 0; i < 9; i++) {
			this->Field.registerObject("UseSlot" + to_string(i), "itemFrame");
			this->Field.object("UseSlot" + to_string(i))->tag = "InventoryUI";
			this->Field.object("UseSlot" + to_string(i))->setPosX(503 + 1100 * 0.06 * i);
			this->Field.object("UseSlot" + to_string(i))->setPosY(500);
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 9; j++) {
				this->Field.registerObject("InventorySlot" + to_string(i) + to_string(j), "itemFrame");
				this->Field.object("InventorySlot" + to_string(i) + to_string(j))->tag = "InventoryUI";
				this->Field.object("InventorySlot" + to_string(i) + to_string(j))->setPosX(503 + 1100 * 0.06 * j);
				this->Field.object("InventorySlot" + to_string(i) + to_string(j))->setPosY(200 + 1100*0.06*i);
			}
		}
		this->Field.createTemplate("BuildingSample");
		this->Field.Template("BuildingSample")->addTexture("assets\\Prop\\Building\\Pumpy.png", "Pump", 1000);
		this->Field.Template("BuildingSample")->addTexture("assets\\Prop\\Building\\Solarcell.png", "SolarCell", 1000);
		this->Field.Template("BuildingSample")->setSpriteSize(0.1, 0.1);
		this->Field.Template("BuildingSample")->setImgDim(1200, 1600);
		this->Field.Template("BuildingSample")->setType("Static");
		this->Field.Template("BuildingSample")->tag = "BuildUI";

		this->Field.registerObject("PumpSample", "BuildingSample");
		this->Field.object("PumpSample")->setSpriteTexture("Pump", 0);
		this->Field.object("PumpSample")->setPosX(400);
		this->Field.object("PumpSample")->setPosY(200);

		this->Field.registerObject("SolarCellSample", "BuildingSample");
		this->Field.object("SolarCellSample")->setSpriteTexture("SolarCell", 0);
		this->Field.object("SolarCellSample")->setPosX(400);
		this->Field.object("SolarCellSample")->setPosY(400);

		this->Field.createTemplate("ItemUse");
		this->Field.Template("ItemUse")->addTexture("assets\\Prop\\Item\\metalPlate.png", "CompositeMetal", 1000);
		this->Field.Template("ItemUse")->addTexture("assets\\Prop\\Item\\Arclyic.png", "Arclyic", 1000);
		this->Field.Template("ItemUse")->setSpriteSize(0.1, 0.1);
		this->Field.Template("ItemUse")->setImgDim(1000, 1000);
		this->Field.Template("ItemUse")->setType("Static");
		this->Field.Template("ItemUse")->tag = "BuildUI";

		this->Field.registerObject("Pump_metal", "ItemUse");
		this->Field.object("Pump_metal")->setSpriteTexture("CompositeMetal", 0);
		this->Field.object("Pump_metal")->setPosX(550);
		this->Field.object("Pump_metal")->setPosY(220);

		this->Field.registerObject("Pump_Arclyic", "ItemUse");
		this->Field.object("Pump_Arclyic")->setSpriteTexture("Arclyic", 0);
		this->Field.object("Pump_Arclyic")->setPosX(650);
		this->Field.object("Pump_Arclyic")->setPosY(220);

	}
	void manageLayer() {
		for (int i = 0; i < this->Field.entityNumber(); i++) {
			this->Field.objectAt(i)->type();
			if (this->Field.objectAt(i)->tag == "BG") {
				this->DrawField["BG_repo"].push_back(this->Field.objectAt(i));
			}
			else if (this->Field.objectAt(i)->tag == "PauseUI") {
				this->DrawField["DrawField_pauseUI"].push_back(this->Field.objectAt(i));
			}
			else if (this->Field.objectAt(i)->tag == "BuildUI") {
				this->DrawField["DrawField_buildingUI"].push_back(this->Field.objectAt(i));
			}
			else if (this->Field.objectAt(i)->tag == "InventoryUI") {
				this->DrawField["DrawField_inventoryUI"].push_back(this->Field.objectAt(i));
			}
			else if (this->Field.objectAt(i)->type() == "Static" && this->Field.objectAt(i)->nowIs() != "Elon") {
				this->DrawField["DrawField_Static"].push_back(this->Field.objectAt(i));
			}
		}
	}
	double ObjectDis(Object* A, Object* B) {
		return sqrt(pow((A->PosX() - B->PosX()), 2) + pow((A->PosY() - B->PosY()), 2));
	}
	string charOnly(string In) {
		return In.substr(0, In.find("_"));
	}
public:
	RenderWindow* window;
	Map Field;
	unordered_map<string, vector<Object*>> DrawField;
	vector<int> ItemUseSlotQuantity;
	vector<vector<Object*>> Backpack;
	vector<vector<int>> BackpackQuantity;
	unordered_map<string, strMap> Dialog;
	vector<int> mousePos = { 0,0 };
	Object* Anchor;
	Object* Elon;
	int InventoryHitbox[4][9][4];
	bool _time = true;
	bool pass = true;
	bool movable = true;
	float move_speed = 3;
	bool W = false, A = false, S = false, D = false, E = false, shift = false;
	bool W_moveable = true, A_moveable = true, S_moveable = true, D_moveable = true;
	bool pause = false;
	bool escPressed = false, escToggle = false, EToggle = false;
	bool paused = false, building = false, inventory = false;
	int selectingSlot = 0;
	gameEngine() {
		unsigned int time_ui = unsigned int(time(NULL));
		srand(time_ui);
		this->initItem();
		this->initVar();
		this->initWindow();
		this->intitDialog();
		this->initObject();
		this->intitUI();
		this->manageLayer();
	}
	virtual ~gameEngine() {
		delete this->window;
	}
	const bool ObjIsOnSight(Object* charactor, Object* B, double range) {
		if (pow(charactor->PosX() - B->PosX(), 2) + pow(charactor->PosY() - B->PosY(), 2) < pow(range, 2)) {
			return true;
		}
		else {
			return false;
		}
	}
	const bool isRuning() {
		return this->window->isOpen();
	}
	void W_key() {
		if (this->W_moveable) {
			Anchor->moveY(1 * this->move_speed);
		}
	}
	void A_key(bool Flip) {
		if (this->A_moveable) {
			Anchor->moveX(1 * this->move_speed);
			if (Flip) {
				Elon->flipTexture(-1);
			}
		}
	}
	void S_key() {
		if (this->S_moveable) {
			Anchor->moveY(-1 * this->move_speed);
		}
	}
	void D_key(bool Flip) {
		if (this->D_moveable) {
			Anchor->moveX(-1 * this->move_speed);
			if (Flip) {
				Elon->flipTexture(1);
			}
		}
	}
	void Idle() {
		Elon->setSpriteTexture("idle", 0);
	}
	void pollEvents() {
		while (this->window->pollEvent(this->ev)) {
			if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Escape) {
				this->escPressed = true;
			}
			if (ev.type == Event::KeyReleased && ev.key.code == Keyboard::Escape) {
				this->escPressed = false;
			}
			if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::E) {
				this->E = true;
			}
			if (ev.type == Event::KeyReleased && ev.key.code == Keyboard::E) {
				this->E = false;
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
				shift = true;
				this->move_speed = 3 * 2;

			}
			if (ev.type == Event::KeyReleased && ev.key.code == Keyboard::LShift) {
				shift = false;
				this->move_speed = 3;

			}
			if (ev.type == Event::MouseMoved) {
				this->mousePos[0] = ev.mouseMove.x;
				this->mousePos[1] = ev.mouseMove.y;
			}
			if (ev.type == Event::MouseButtonPressed) {
				if (ev.mouseButton.button == Mouse::Middle) {
					//for (int i = 0; i < this->Field.entityNumber(); i++) {
						//cout << this->Field.objectAt(i)->nowIs() << endl;
					//}
					printf("\n");
					string ObjName = "Pumpy" + to_string(rand() % 100000);
					this->Field.registerObject(ObjName, "Pump");
					this->Field.object(ObjName)->setOffsetPosX(this->Field.object("Elon")->PosX() - this->Field.object("Anchor")->PosX());
					this->Field.object(ObjName)->setOffsetPosY(this->Field.object("Elon")->PosY() - this->Field.object("Anchor")->PosY());
					vector<float> data = this->Field.object(ObjName)->getHitBoxData();
					cout << this->Field.object(ObjName)->nowIs() << endl;
					for (int i = 0; i < 6; i++) {
						printf("%.1f ", data[i]);
					}
					printf("\n");

				}
				if (ev.mouseButton.button == Mouse::Right) {
					cout << this->DrawField["ItemUseSlot"][this->selectingSlot]->tag << endl;
					if (this->Elon->getStat("Alive") == 1) {
						if (this->DrawField["ItemUseSlot"][this->selectingSlot]->tag == "Medicine" && this->ItemUseSlotQuantity[this->selectingSlot] > 0 && Elon->getStat("Health") < 100) {
							Elon->setStat("Health", Elon->getStat("Health") + 10);
							if (Elon->getStat("Health") > 100) {
								Elon->setStat("Health", 100);
							}
						}
						else if (this->DrawField["ItemUseSlot"][this->selectingSlot]->tag == "Food" && this->ItemUseSlotQuantity[this->selectingSlot] > 0 && Elon->getStat("Hunger") < 100) {
							Elon->setStat("Hunger", Elon->getStat("Hunger") + 10);
							if (Elon->getStat("Hunger") > 100) {
								Elon->setStat("Hunger", 100);
							}
						}
						else if (this->DrawField["ItemUseSlot"][this->selectingSlot]->tag == "Drink" && this->ItemUseSlotQuantity[this->selectingSlot] > 0 && Elon->getStat("Thirst") < 100) {
							Elon->setStat("Thirst", Elon->getStat("Thirst") + 10);
							if (Elon->getStat("Thirst") > 100) {
								Elon->setStat("Thirst", 100);
							}
						}
						else if (this->DrawField["ItemUseSlot"][this->selectingSlot]->tag == "Tool" && this->ItemUseSlotQuantity[this->selectingSlot] > 0) {
							if (this->DrawField["ItemUseSlot"][this->selectingSlot]->nowIs() == "Hammer") {
								this->building = true;
								/*
								string ObjName = "Pump_" + to_string(rand() % 100000);
								this->Field.registerObject(ObjName, "Pump");
								this->Field.object(ObjName)->setOffsetPosX(this->Elon->PosX() - this->Field.object("Anchor")->PosX());
								this->Field.object(ObjName)->setOffsetPosY(this->Elon->PosY() - this->Field.object("Anchor")->PosY());
								printf("+\n");
								this->DrawField_Dynamic.push_back(this->Field.object(ObjName));
								*/
							}
						}
						else {
							continue;
						}
						if (this->ItemUseSlotQuantity[this->selectingSlot] > 0) {
							this->ItemUseSlotQuantity[this->selectingSlot]--;
						}
						if (this->ItemUseSlotQuantity[this->selectingSlot] <= 0) {
							this->DrawField["ItemUseSlot"][this->selectingSlot]->Is("None");
							this->DrawField["ItemUseSlot"][this->selectingSlot]->tag = "None";
							this->DrawField["ItemUseSlot"][this->selectingSlot]->setSpriteSize(0, 0);
						}
					}
				}
				if (ev.mouseButton.button == Mouse::Left) {
					printf("%d %d ||\n", this->mousePos[0], this->mousePos[1]);
					if (this->Elon->getStat("Alive") == 1) {
						if (this->paused) {
							int BacktoGameHitBox[] = { 250, 200, 600, 250 };
							int ExitHitBox[] = { 250, 600, 600, 650 };
							if (clickHit(BacktoGameHitBox)) {
								printf("Hit");
								this->paused = false;
							}
							if(clickHit(ExitHitBox)) {
								printf("Hit");
								this->window->close();
								this->running = false;
							}
						}
						else if (this->building) {
							int PumpHitBox[] = { 330, 100, 470, 280 };
							int SlolarHitBox[] = { 330, 340, 460, 480 };
							if (clickHit(PumpHitBox) && hasEnoughItem("Composite Metal", 10) && hasEnoughItem("Arclyic", 5)) {
								string ObjName = "Pump_" + to_string(rand() % 100000);
								this->Field.registerObject(ObjName, "Pump");
								this->Field.object(ObjName)->setOffsetPosX(this->Field.object("Elon")->PosX() - this->Field.object("Anchor")->PosX());
								this->Field.object(ObjName)->setOffsetPosY(this->Field.object("Elon")->PosY() - this->Field.object("Anchor")->PosY());
								this->DrawField["DrawField_Dynamic"].push_back(this->Field.object(ObjName));
								this->building = false;
							}
							if (clickHit(SlolarHitBox)) {
								string ObjName = "Solar_" + to_string(rand() % 100000);
								this->Field.registerObject(ObjName, "SolarCell");
								this->Field.object(ObjName)->setOffsetPosX(this->Field.object("Elon")->PosX() - this->Field.object("Anchor")->PosX());
								this->Field.object(ObjName)->setOffsetPosY(this->Field.object("Elon")->PosY() - this->Field.object("Anchor")->PosY());
								this->DrawField["DrawField_Dynamic"].push_back(this->Field.object(ObjName));
								this->building = false;
							}
						}
						else if (this->inventory) {
							for (int i = 0; i < 4; i++) {
								for (int j = 0; j < 9; j++) {
									if (clickHit(this->InventoryHitbox[i][j])) {
										printf("ClickHit %d,%d\n", i, j);
									}
								}
							}
						}
					}
				}
			}
			if (ev.type == Event::MouseWheelMoved) {
				if (ev.mouseWheel.delta > 0) {
					this->selectingSlot -= 1;
					if (this->selectingSlot < 0) {
						this->selectingSlot = 8;
					}
				}
				else {
					this->selectingSlot += 1;
					if (this->selectingSlot > 8) {
						this->selectingSlot = 0;
					}
				}
				cout << this->DrawField["ItemUseSlot"][this->selectingSlot]->tag << "     " << this->ItemUseSlotQuantity[this->selectingSlot] << endl;
			}
		}

	}
	bool hasEnoughItem(string item, int quantity) {
		for (int i = 0; i < 9; i++) {
			if (this->DrawField["ItemUseSlot"][i]->nowIs() == item && this->ItemUseSlotQuantity[i] >= quantity) {
				this->ItemUseSlotQuantity[i] -= quantity;
				return true;
			}
		}
		return false;
	}
	void DecStat(string Stat, float amount) {
		if (Elon->getStat(Stat) > 1) {
			Elon->setStat(Stat, Elon->getStat(Stat) - amount);
		}
	}
	bool clickHit(int hitboxData[4]) {
		int Mx = this->mousePos[0], My = this->mousePos[1];
		return Mx < hitboxData[2] && Mx > hitboxData[0] && My < hitboxData[3] && My >hitboxData[1];
	}
	int IntDigit(int In) {
		int i = floor(log10(In))+1;
		return i;
	}
	void updateHUD() {
		if (Elon->getStat("Health") > 0) {
			this->Field.object("StatBar_Fill0")->setSpriteSize(0.06, -0.06 * Elon->getStat("Health") / 100);
		}
		if (Elon->getStat("Hunger") > 0) {
			this->Field.object("StatBar_Fill1")->setSpriteSize(0.06, -0.06 * Elon->getStat("Hunger") / 100);
		}
		if (Elon->getStat("Thirst")) {
			this->Field.object("StatBar_Fill2")->setSpriteSize(0.06, -0.06 * Elon->getStat("Thirst") / 100);
		}
		if (Elon->getStat("Air")) {
			this->Field.object("StatBar_Fill3")->setSpriteSize(0.06, -0.06 * Elon->getStat("Air") / 100);
		}
		this->Field.object("ItemPrt")->setPosX(503 + 1100 * 0.06 / 2 + (this->selectingSlot * 1100 * 0.06));
		for (int i = 0; i < 9; i++) {
			if (this->DrawField["ItemUseSlot"][i]->nowIs() != "None" && find(this->DrawField["DrawField_Static"].begin(), this->DrawField["DrawField_Static"].end(), this->DrawField["ItemUseSlot"][i]) == this->DrawField["DrawField_Static"].end()) {
				this->DrawField["ItemUseSlot"][i]->setPosX(503 + 1100 * 0.06 / 2 + (1100 * 0.06 * i));
				this->DrawField["ItemUseSlot"][i]->setPosY(833);
				this->DrawField["DrawField_Static"].push_back(this->DrawField["ItemUseSlot"][i]);
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 9; j++) {
				if(this->Backpack[i][j]->nowIs() != "None")
				this->Backpack[i][j]->setPosY(233 + 1100 * 0.06 * i);
				this->Backpack[i][j]->setPosX(536 + 1100 * 0.06 * j);
			}
		}
	}
	void update() {
		int updated = false;
		this->pollEvents();
		this->updateHUD();
		if (this->escPressed && !this->escToggle) {
			if (this->paused || this->building || this->inventory) {
				this->paused = false;
				this->building = false;
				this->inventory = false;
			}
			else {
				this->paused = true;
			}
			this->escToggle = true;
		}
		else if(!this->escPressed) {
			this->escToggle = false;
		}
		if (this->E && !this->EToggle) {
			if (this->inventory) {
				this->inventory = false;
			}
			else {
				this->inventory = true;
			}
			this->EToggle = true;
		}
		else if (!this->E) {
			this->EToggle = false;
		}
		if ((W || A || S || D || shift) && this->Elon->getStat("Alive") == 1 && !this->paused) {
			Elon->setAnimationSeq("walk");
			DecStat("Hunger", 0.0002);
			DecStat("Thirst", 0.0003);
			DecStat("Air", 0.005);
			if (shift) {
				this->Elon->UpdateAnimation(2);
				DecStat("Hunger", 0.002);
				DecStat("Thirst", 0.003);
			}
			if (S && !W) {
				if (!updated) {
					updated = true;
					this->Elon->UpdateAnimation(1);
				}
				if (S_moveable) {
					S_key();
				}
			}
			if (W && !S) {
				if (!updated) {
					updated = true;
					this->Elon->UpdateAnimation(1);
				}
				if (W_moveable) {
					W_key();
				}
			}
			if (D && !A) {
				if (!updated) {
					updated = true;
					this->Elon->UpdateAnimation(1);
				}
				if (D_moveable) {
					D_key(true);
				}
			}
			if (A && !D) {
				if (!updated) {
					updated = true;
					this->Elon->UpdateAnimation(1);
				}
				if (A_moveable) {
					A_key(true);
				}
			}
			if (W && S || A && D) {
				if (!updated) {
					updated = true;
					Idle();
				}
			}
		}
		else if (Elon->getStat("Alive") == 1) {
			Idle();
			this->Elon->resetTimeSeq();
		}
		//printf("%d | %.0llf, %.0llf | %.0llf, %.0llf |  \n", this->DrawField.size(), Elon->PosX(), Elon->PosY(), this->Field.object("0")->PosX(), this->Field.object("0")->PosY());
		try {
			for (int i = 0; i < Field.entityNumber(); i++) {
				if (this->Field.objectAt(i)->type() == "Dynamic" && i < this->Field.entityNumber() && this->Field.objectAt(i)->usable) {
					this->Field.objectAt(i)->setPosX(this->Anchor->PosX());
					this->Field.objectAt(i)->setPosY(this->Anchor->PosY());
				}
			}
		}
		catch (const std::out_of_range& e) {
			printf("%d\n", e);
		}
		if (!this->paused) {
			DecStat("Health", 0.00025);
			DecStat("Hunger", 0.0005);
			DecStat("Thirst", 0.0007);
			DecStat("Air", 0.005);

			if (Elon->getStat("Hunger") <= 1) {
				DecStat("Health", 0.005);
			}
			if (Elon->getStat("Thirst") <= 1) {
				DecStat("Health", 0.007);
			}
			if (Elon->getStat("Air") <= 1) {
				DecStat("Health", 0.05);
			}
			if (Elon->getStat("Health") <= 1) {
				if (_time) {
					this->Elon->resetTimeSeq();
					_time = false;
				}
				Elon->setStat("Alive", 0);
				Elon->setAnimationSeq("dying");
				Elon->UpdateAnimation(1);
			}
		}
		int maxParam = 0;
		for (int i = 0; i < this->DrawField["DrawField_Dynamic"].size(); i++) {
			Object* A = this->DrawField["DrawField_Dynamic"][i];
			if (A->usable && A->tag == "fallItem" && ObjectDis(this->Field.object("Elon"), A) <= 50) {
				this->DrawField["DrawField_Dynamic"][i]->usable = false;
				bool found = false;
				for (int i = 0; i < 9; i++) {
					if (this->DrawField["ItemUseSlot"][i]->nowIs() == charOnly(A->nowIs())) {
						this->ItemUseSlotQuantity[i]++;
						found = true;
						break;
					}
				}
				if (!found) {
					for (int i = 0; i < 9; i++) {
						if (this->DrawField["ItemUseSlot"][i]->nowIs() == "None") {
							this->DrawField["ItemUseSlot"][i]->tag = this->itemList.object(charOnly(A->nowIs()))->tag;
							//cout << this->ItemUseSlot[i]->tag  << " = " << this->itemList.object(charOnly(A->nowIs()))->tag << endl;
							this->DrawField["ItemUseSlot"][i]->Is(charOnly(A->nowIs()));
							this->DrawField["ItemUseSlot"][i] = this->itemList.object(charOnly(A->nowIs()));
							this->ItemUseSlotQuantity[i] = 1;
							this->DrawField["ItemUseSlot"][i]->setSpriteSize(0.06, 0.06);
							//this->ItemUseSlot[i]->setPosX(503 + 1100 * 0.06 * i);
							break;
						}
					}
				}
			}
			if (A->usable && A->tag == "fallItem" && ObjectDis(this->Field.object("Elon"), A) <= 200) {
				const vector<float> moveVec = getHitVector(this->Field.object("Elon")->PosX(), this->Field.object("Elon")->PosY(), A->PosX(), A->PosY());
				A->setOffsetPosX(A->offsetPosX + 7*moveVec[0]/abs(moveVec[0]+1));
				A->setOffsetPosY(A->offsetPosY + 7*moveVec[1] / abs(moveVec[1]+1));
				//A->setSpriteSize(0, 0);
				//this->DrawField_Dynamic.erase(this->DrawField_Dynamic.begin() + i);
				//this->Field.remove(A->nowIs());
			}
		}
		for (int i = 0; i < 9; i++) {
			if (this->ItemUseSlotQuantity[i] <= 0) {
				this->DrawField["ItemUseSlot"][i]->Is("None");
				this->DrawField["ItemUseSlot"][i]->tag = "None";
				this->DrawField["ItemUseSlot"][i]->setSpriteSize(0, 0);
				
				this->DrawField["InventoryUseSlot"][i]->Is("None");
				this->DrawField["InventoryUseSlot"][i]->tag = "None";
				this->DrawField["InventoryUseSlot"][i]->setSpriteSize(0, 0);
			}
			if (this->DrawField["ItemUseSlot"][i]->nowIs() != "None" && this->DrawField["ItemUseSlot"][i]->getStat("showCount") == 1 && this->ItemUseSlotQuantity[i] > 0) {
				const float x = (535 + 1100.0 * 0.06 * i) - this->Dialog["itemCount"].object("itemCount" + to_string(i))->getLocalBounds().width/2, y = 830, x1 = x-0.7*IntDigit(this->ItemUseSlotQuantity[i]);
				this->Dialog["itemCount"].object("itemCount" + to_string(i))->setPosition({x,y});
				this->Dialog["itemCount"].object("itemCount" + to_string(i))->setString(to_string(this->ItemUseSlotQuantity[i]));
				this->Dialog["itemCount"].object("itemCountBG" + to_string(i))->setPosition({x1,y});
				this->Dialog["itemCount"].object("itemCountBG" + to_string(i))->setString(to_string(this->ItemUseSlotQuantity[i]));
				
				this->Dialog["InventoryItem_hotbar"].object("InventoryitemCountBG_hotbar" + to_string(i))->setPosition({ x,533 });
				this->Dialog["InventoryItem_hotbar"].object("InventoryitemCountBG_hotbar" + to_string(i))->setString(to_string(this->ItemUseSlotQuantity[i]));
				this->Dialog["InventoryItem_hotbar"].object("InventoryitemCount_hotbar" + to_string(i))->setPosition({ x1,533 });
				this->Dialog["InventoryItem_hotbar"].object("InventoryitemCount_hotbar" + to_string(i))->setString(to_string(this->ItemUseSlotQuantity[i]));
			}
			else {
				this->Dialog["itemCount"].object("itemCount" + to_string(i))->setString(" ");
				this->Dialog["itemCount"].object("itemCountBG" + to_string(i))->setString(" ");

				this->Dialog["InventoryItem_hotbar"].object("InventoryitemCount_hotbar" + to_string(i))->setString(" ");
				this->Dialog["InventoryItem_hotbar"].object("InventoryitemCountBG_hotbar" + to_string(i))->setString(" ");
			}
			*this->DrawField["InventoryUseSlot"][i] = *this->DrawField["ItemUseSlot"][i];
			this->DrawField["InventoryUseSlot"][i]->setPosY(533);
		}
		if (this->DrawField["ItemUseSlot"][this->selectingSlot]->nowIs() != "None") {
			const float x = 800 - this->Dialog["InGameStatus"].object("ItemInHand")->getLocalBounds().width / 2, y = 750;
			this->Dialog["InGameStatus"].object("ItemInHand")->setPosition({ x,y });
			this->Dialog["InGameStatus"].object("ItemInHand")->setString(this->DrawField["ItemUseSlot"][this->selectingSlot]->nowIs());
		}

		for (int i = 0; i < 3; i++) {
			for(int j = 0; j < 9; j++){
				if (this->BackpackQuantity[i][j] <= 0) {
					this->Backpack[i][j]->Is("None");
					this->Backpack[i][j]->tag = "None";
					this->Backpack[i][j]->setSpriteSize(0, 0);
				}

				if (this->Backpack[i][j]->nowIs() != "None" && this->Backpack[i][j]->getStat("showCount") == 1 && this->BackpackQuantity[i][j] > 0) {
					const float x = (535 + 1100.0 * 0.06 * j) - this->Dialog["InventoryItem"].object("InventoryitemCount" + to_string(i) + to_string(j))->getLocalBounds().width / 2, y = 233 + 1100 * 0.06 * i, x1 = x - 0.7 * IntDigit(this->BackpackQuantity[i][j]);
					this->Dialog["InventoryItem"].object("InventoryitemCount" + to_string(i) + to_string(j))->setPosition({ x,y });
					this->Dialog["InventoryItem"].object("InventoryitemCount" + to_string(i) + to_string(j))->setString(to_string(this->BackpackQuantity[i][j]));
					this->Dialog["InventoryItem"].object("InventoryitemCountBG" + to_string(i) + to_string(j))->setPosition({ x1,y });
					this->Dialog["InventoryItem"].object("InventoryitemCountBG" + to_string(i) + to_string(j))->setString(to_string(this->BackpackQuantity[i][j]));
				}
				else {
					this->Dialog["InventoryItem"].object("InventoryitemCount" + to_string(i) + to_string(j))->setString(" ");
					this->Dialog["InventoryItem"].object("InventoryitemCountBG" + to_string(i) + to_string(j))->setString(" ");
				}
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
		try {
			for (int i = 0; i < this->DrawField["DrawField_BG"].size(); i++) {
				this->window->draw(this->DrawField["DrawField_BG"][i]->getSprite());
			}
			for (int i = 0; i < this->DrawField["DrawField_Dynamic"].size() && this->DrawField["DrawField_Dynamic"][i]->tag != "BG"; i++) {
				this->window->draw(this->DrawField["DrawField_Dynamic"][i]->getSprite());
			}
			for (int i = 0; i < this->DrawField["DrawField_Static"].size() && DrawField["DrawField_Static"][i]; i++) {
				this->window->draw(this->DrawField["DrawField_Static"][i]->getSprite());
			}
			for (int i = 0; i < Dialog["itemCount"].entityNumber(); i++) {
				this->window->draw(*this->Dialog["itemCount"].objectAt(i));
			}
			if (this->DrawField["ItemUseSlot"][this->selectingSlot]->nowIs() != "None") {
				this->window->draw(*this->Dialog["InGameStatus"].object("ItemInHand"));
			}
			if (this->paused) {
				for (int i = 0; i < this->DrawField["DrawField_pauseUI"].size(); i++) {
					this->window->draw(this->DrawField["DrawField_pauseUI"][i]->getSprite());
				}
				for (int i = 0; i < Dialog["PausedMenu"].entityNumber(); i++) {
					this->window->draw(*this->Dialog["PausedMenu"].objectAt(i));
				}
			}
			else if (this->building) {
				for (int i = 0; i < this->DrawField["DrawField_buildingUI"].size(); i++) {
					this->window->draw(this->DrawField["DrawField_buildingUI"][i]->getSprite());
				}
				for (int i = 0; i < this->Dialog["itemUse"].entityNumber(); i++) {
					this->window->draw(*this->Dialog["itemUse"].objectAt(i));
				}
			}
			else if (this->inventory) {
				for (int i = 0; i < DrawField["DrawField_inventoryUI"].size(); i++) {
					this->window->draw(this->DrawField["DrawField_inventoryUI"][i]->getSprite());
				}
				for (int i = 0; i < this->DrawField["InventoryUseSlot"].size(); i++) {
					this->window->draw(this->DrawField["InventoryUseSlot"][i]->getSprite());
				}
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 9; j++) {
						this->window->draw(this->Backpack[i][j]->getSprite());
					}
				}
				for (int i = 0; i < this->Dialog["InventoryItem_hotbar"].entityNumber(); i++) {
					this->window->draw(*this->Dialog["InventoryItem_hotbar"].objectAt(i));
				}
				for (int i = 0; i < this->Dialog["InventoryItem"].entityNumber(); i++) {
					this->window->draw(*this->Dialog["InventoryItem"].objectAt(i));
				}

			}
		}
		catch (int e) {
			printf("%d\n", e);
		}
		//printf("%f, %f\n", this->dui.getPosX(), this->dui.getPosY());

		this->window->display();
	}
	void sort() {

	}
};

gameEngine First_step;
bool change = false;

bool SortObj() {
	bool swaped = false;
	for (int i = 0; i < First_step.DrawField["DrawField_Dynamic"].size() - 1; i++) {
		if (i < First_step.DrawField["DrawField_Dynamic"].size() - 1 && (First_step.DrawField["DrawField_Dynamic"][i]->PosY() + (First_step.DrawField["DrawField_Dynamic"][i]->getImgHeight() * First_step.DrawField["DrawField_Dynamic"][i]->getSizeY()) / 2 > First_step.DrawField["DrawField_Dynamic"][i + 1]->PosY() + (First_step.DrawField["DrawField_Dynamic"][i + 1]->getImgHeight() * First_step.DrawField["DrawField_Dynamic"][i + 1]->getSizeY()) / 2)) {
			//First_step.pause = true;
			iter_swap(&First_step.DrawField["DrawField_Dynamic"][i], &First_step.DrawField["DrawField_Dynamic"][i + 1]);
			//First_step.pause = false;
			swaped = true;
		}
	}
	return swaped;
}

void CheckInsight() {
	bool swaping = true;
	try {
		for (int i = 0; i < First_step.Field.entityNumber(); i++) {
			if (First_step.Field.objectAt(i)->usable && !First_step.pause && i < First_step.Field.entityNumber() - 1 && (First_step.Field.objectAt(i)->type() != "Static" && First_step.Field.objectAt(i)->tag != "BG" || First_step.Field.objectAt(i)->nowIs() == "Elon") && !(std::find(First_step.DrawField["DrawField_Dynamic"].begin(), First_step.DrawField["DrawField_Dynamic"].end(), First_step.Field.objectAt(i)) != First_step.DrawField["DrawField_Dynamic"].end()) && (First_step.ObjIsOnSight(First_step.Field.object("Elon"), First_step.Field.objectAt(i), 1100) || First_step.Field.objectAt(i)->nowIs() == "Anchor" || First_step.Field.objectAt(i)->nowIs() == "BG" || First_step.Field.objectAt(i)->nowIs() == "Elon")) {
				First_step.DrawField["DrawField_Dynamic"].push_back(First_step.Field.objectAt(i));
			}
			change = true;
		}
		for (int i = 0; i < First_step.DrawField["DrawField_Dynamic"].size(); i++) {
			if (First_step.DrawField["DrawField_Dynamic"][i]->nowIs() != "Elon" && (!First_step.DrawField["DrawField_Dynamic"][i]->usable || (First_step.pause && i < First_step.Field.entityNumber() - 1 && !(First_step.ObjIsOnSight(First_step.Field.object("Elon"), First_step.DrawField["DrawField_Dynamic"][i], 1100) || First_step.DrawField["DrawField_Dynamic"][i]->nowIs() == "Anchor" || First_step.DrawField["DrawField_Dynamic"][i]->nowIs() == "BG" || First_step.DrawField["DrawField_Dynamic"][i]->nowIs() == "Elon")))) {
				First_step.DrawField["DrawField_Dynamic"].erase(First_step.DrawField["DrawField_Dynamic"].begin() + i);
			}
			change = true;
		}
		while (swaping){
			swaping = SortObj();
		} 
	}
	catch (int e) {
		printf("%d\n", e);
	}
}

void checkFloorInsight() {
	while (First_step.isRuning()) {
		Sleep(1);
		while (First_step.DrawField["BG_repo"].size() == 0 || First_step.pause) {
			Sleep(1);
		}
		for (int i = 0; i < First_step.DrawField["BG_repo"].size(); i++) {
			if (!First_step.pause && !(find(First_step.DrawField["DrawField_BG"].begin(), First_step.DrawField["DrawField_BG"].end(), First_step.DrawField["BG_repo"][i]) != First_step.DrawField["DrawField_BG"].end()) && First_step.ObjIsOnSight(First_step.Field.object("Elon"), First_step.DrawField["BG_repo"][i], 1500)) {
				First_step.DrawField["DrawField_BG"].push_back(First_step.DrawField["BG_repo"][i]);
			}
		}
		for (int i = 0; i < First_step.DrawField["DrawField_BG"].size(); i++) {
			if (!First_step.pause && !(First_step.ObjIsOnSight(First_step.Field.object("Elon"), First_step.DrawField["DrawField_BG"][i], 1500))) {
				First_step.DrawField["DrawField_BG"].erase(First_step.DrawField["DrawField_BG"].begin() + i);
			}
		}
	}
}

bool anyBetween(float* x1, float* x2) {
	bool ans = false;
	for (int i = 0; i < 2; i++) {
		if ((x1[i] < x2[1] && x1[i] > x2[0])) {
			ans = true;
		}
	}
	return ans;
}

bool hitBoxhit(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	float setX1[2] = { x1,x2 };
	float setX2[2] = { x3,x4 };
	float setY1[2] = { y1,y2 };
	float setY2[2] = { y3,y4 };
	return (anyBetween(setX1, setX2) || anyBetween(setX2, setX1)) && (anyBetween(setY1, setY2) || anyBetween(setY2, setY1));
}

const vector<float> getHitVector(float x1O, float y1O, float x2O, float y2O) {
	return { x1O - x2O, y1O - y2O };
}

float Distance(Object* A, Object* B) {
	return sqrt(pow(A->PosX() - B->PosX(), 2) + pow(A->PosY() - B->PosY(), 2));
}

void isMovable() {
	Event ev;
	vector<float> HitVec;
	float AnchorX, AnchorY;
	vector<float>ElonHitBox;
	vector<float>ObjHitBox;
	bool bump = false;
	bool W_isbump = false, A_isbump = false, S_isbump = false, D_isbump = false;
	float hitBoxXoffset = 30;
	while (First_step.isRuning()) {
		Sleep(1);
		bump = false;
		while (First_step.Field.entityNumber() == 0 || First_step.pause) {
			Sleep(1);
		}
		CheckInsight();
		for (int i = 0; i < First_step.DrawField["DrawField_Dynamic"].size(); i++) {
			try {
				ElonHitBox = First_step.Field.object("Elon")->getHitBoxData();
				ObjHitBox = First_step.DrawField["DrawField_Dynamic"][i]->getHitBoxData();
			}
			catch (const std::out_of_range& e) {
				cout << "Out of Range error.";
			}
			if (!First_step.pause && First_step.DrawField["DrawField_Dynamic"][i]->usable && !First_step.DrawField["DrawField_Dynamic"][i]->passable && hitBoxhit(ElonHitBox[0] + hitBoxXoffset, ElonHitBox[1], ElonHitBox[2] - hitBoxXoffset, ElonHitBox[3], ObjHitBox[0], ObjHitBox[1], ObjHitBox[2], ObjHitBox[3])) {
				HitVec = getHitVector(ObjHitBox[4], ObjHitBox[5], ElonHitBox[4], ElonHitBox[5]);
				printf("%.2f, %.2f\n", HitVec[0], HitVec[1]);
				if (HitVec[1] < 0) {
					W_isbump = true;
					First_step.move_speed /= 5;
					First_step.S_key();
					First_step.move_speed *= 5;
				}
				else if (HitVec[1] > 0) {
					S_isbump = true;
					First_step.move_speed /= 5;
					First_step.W_key();
					First_step.move_speed *= 5;
				}
				if (HitVec[0] < 0) {
					A_isbump = true;
					First_step.move_speed /= 5;
					First_step.D_key(false);
					First_step.move_speed *= 5;
				}

				else if (HitVec[0] > 0) {
					D_isbump = true;
					First_step.move_speed /= 5;
					First_step.A_key(false);
					First_step.move_speed *= 5;
				}
				printf("************************************ with ");
				cout << First_step.DrawField["DrawField_Dynamic"][i]->nowIs() << endl;
				break;
			}
		}
		if (W_isbump) {
			First_step.W_moveable = false;
		}
		else {
			First_step.W_moveable = true;
		}
		if (A_isbump) {
			First_step.A_moveable = false;
		}
		else {
			First_step.A_moveable = true;
		}
		if (S_isbump) {
			First_step.S_moveable = false;
		}
		else {
			First_step.S_moveable = true;
		}
		if (D_isbump) {
			First_step.D_moveable = false;
		}
		else {
			First_step.D_moveable = true;
		}
		W_isbump = false;
		A_isbump = false;
		S_isbump = false;
		D_isbump = false;
		//printf("****************************\n");
	}
}

void ShowDrawingStat() {
	while (First_step.isRuning()) {
		while (First_step.Field.entityNumber() == 0 || First_step.pause) {
			Sleep(1);
		}
		try {
			for (int num = 0; num < First_step.DrawField["DrawField_Dynamic"].size(); num++) {
				vector<float> data = First_step.DrawField["DrawField_Dynamic"][num]->getHitBoxData();
				cout << First_step.DrawField["DrawField_Dynamic"][num]->nowIs() << '\t';
				for (int i = 0; i < 6; i++) {
					printf("%.1f ", data[i]);
				}
				printf("\n");
			}
			for (int num = 0; num < First_step.DrawField["DrawField_Static"].size(); num++) {
				vector<float> data = First_step.DrawField["DrawField_Static"][num]->getHitBoxData();
				cout << First_step.DrawField["DrawField_Static"][num]->nowIs() << '\t';
				for (int i = 0; i < 6; i++) {
					printf("%.1f ", data[i]);
				}
				printf("\n");
			}
		}
		catch (const std::out_of_range& e) {
			printf("%d\n", e);
		}
	}
}

void ShowDrawingStat1() {
	while (First_step.isRuning()) {
		while (First_step.Field.entityNumber() == 0 || First_step.pause) {
			Sleep(1);
		}
		printf("BG : %d, Dynamic : %d, Static %d, Overall %d\n", First_step.DrawField["DrawField_BG"].size(), First_step.DrawField["DrawField_Dynamic"].size(), First_step.DrawField["DrawField_Static"].size(), First_step.Field.entityNumber());
	}
}

void ShowDrawingStat2() {
	while (First_step.isRuning()) {
		while (First_step.Field.entityNumber() == 0 || First_step.pause) {
			Sleep(1);
		}
		for (int i = 0; i < 9; i++) {
			printf("%d ", First_step.DrawField["ItemUseSlot"][i]->getStat("Quantity"));
		}
		printf("\n");
	}
}
void ShowDrawingStat3() {
	while (First_step.isRuning()) {
		while (First_step.Field.entityNumber() == 0 || First_step.paused) {
			Sleep(1);
		}
		printf("%d\n", First_step.escPressed);
	}
}
int main() { // Game loop
	Thread CheckInsight_Thread1(&CheckInsight), ChechFloor(&checkFloorInsight), CheckBump(&isMovable), monitor(&ShowDrawingStat3);
	CheckBump.launch();
	ChechFloor.launch();
	//monitor.launch();
	while (First_step.isRuning()) {
		First_step.update();
		First_step.render();
		Sleep(1);
	}
	return 0;
}