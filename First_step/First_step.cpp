#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
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
const vector<float> getVector(float, float, float, float);

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
	void increase(string keyIn, float In) {
		this->map[keyIn] += In;
	}
	unsigned __int64 length() {
		return this->map.size();
	}
};

class Object {
private:
	string Type = "Dynamic";
	unsigned __int64 ID;
	string Name = "None";
	fltDic Stat;
	float posX = 0;
	float posY = 0;
	float Size[2];
	int imgHeight;
	int imgWidth;
	unordered_map<string, vector<int>> duration;
	string slot;
public:
	bool loop = false;
	bool passable = true;
	bool fliping = false;
	float offsetPosX = 0;
	float offsetPosY = 0;
	int time = 0, Index = 0;
	string tag = "None", cat = "None";
	bool usable = true;
	Sprite sprite;
	unordered_map<string, vector<Texture*>> textureArray;
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
	void setTag(string Tag) {
		this->tag = Tag;
	}
	void useStatNoPos(Object In) {
		this->textureArray = In.textureArray;
		this->duration = In.duration;
		this->fliping = In.fliping;
		this->setImgDim(In.imgWidth, In.imgHeight);
		this->loop = In.loop;
		this->passable = In.passable;
		this->setSpriteSize(In.getSizeX(), In.getSizeY());
		this->Stat = In.Stat;
		this->Type = In.Type;
		this->sprite = In.sprite;
		this->slot = In.slot;
		this->tag = In.tag;
		this->Is(In.nowIs());
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
		Texture* a = new Texture;
		if (!(*a).loadFromFile(Path)) {
			printf("Error");
		}
		a->setSmooth(true);
		int old_size = this->textureArray.size();
		this->textureArray[seqName].push_back(a);
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
	void increase(string KeyIn, float amount) {
		this->Stat.increase(KeyIn, amount);
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
	void MovePosX(float offx) {
		this->offsetPosX += offx;
	}
	void MovePosY(float offy) {
		this->offsetPosY += offy;
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

class Map {
public:
	unordered_map<string, Object*> Tuple;
	unordered_map<string, Object*> Templ;
	unordered_map<unsigned __int64, string> Tuplekey, Templkey;
	void clear() {
		this->Templ.clear();
		this->Tuple.clear();
	}
	void createTemplate(string name) {
		Object* p = new Object(this->Templ.size());
		p->Is(name);
		this->Templ[name] = p;
		Templkey[this->Templ.size()] = name;
	}
	void registerObject(string Name, string Template, string Cat) {
		Object* p = new Object(this->Tuple.size());
		(*p).useStat(*this->Template(Template));
		(*p).Is(Name);
		p->cat = Cat;
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
	void destroy() {
		for (auto& Template : Templ) {
			for (auto TextureVec : Template.second->textureArray) {
				for (auto Texture : TextureVec.second) {
					cout << "Deleting : " << Template.first << '\t' << TextureVec.first << endl;
					delete Texture;
				}
			}
		}
		for (int i = 0; i < Tuplekey.size(); i++) {
			cout << "Delete : " << Tuple[Tuplekey[i]]->nowIs() << endl;
			delete Tuple[Tuplekey[i]];
		}
		Tuple = *new unordered_map<string, Object*>;
		Templ = *new unordered_map<string, Object*>;
		Tuplekey = *new unordered_map<unsigned __int64, string>;
		Templkey = *new unordered_map<unsigned __int64, string>;
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
		this->Tuplekey[this->Tuple.size() - 1] = Name;
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
	void destroy() {
		for (auto text : Tuple) {
			delete text.second;
		}
	}

};

class RecipeTable {
private:
	vector<string> itemNameList;
	unordered_map<string, int> itemNameIndex;
	unordered_map<string, int> outputNumber;
	unordered_map<string, vector<string>> itemRequiredName;
	unordered_map<string, vector<int>> itemRequiredQuantity;
public:
	void registerRecipe(string name, int outNum) {
		this->itemNameIndex[name] = itemNameList.size();
		this->itemNameList.push_back(name);
		this->outputNumber[name] = outNum;
	}
	void addedRequiredItem(string itemName, string materialName, int materialNumber) {
		itemRequiredName[itemName].push_back(materialName);
		itemRequiredQuantity[itemName].push_back(materialNumber);
	}
	string RecipeAt(int Index) {
		return itemNameList[Index];
	}
	string matAt(string itemName, int Index) {
		return this->itemRequiredName[itemName][Index];
	}
	int outputNum(string itemName) {
		return this->outputNumber[itemName];
	}
	int indexOf(string itemName) {
		return itemNameIndex[itemName];
	}
	int MatUseNumber(string itemName) {
		return itemRequiredName[itemName].size();
	}
	int itemUseQuantity(string itemName, int index) {
		return itemRequiredQuantity[itemName][index];
	}
	int recipeNumber() {
		return itemNameList.size();
	}
	string itemUseName(string itemName, int index) {
		return itemRequiredName[itemName][index];
	}
	bool matIsUse(string itemName, string matName) {
		for (int i = 0; i < this->itemRequiredName[itemName].size(); i++) {
			if (this->itemRequiredName[itemName][i] == matName) {
				return true;
			}
		}
		return false;
	}
	bool IsUse(int Index, string matName, int number) {
		for (int i = 0; i < this->itemRequiredName[RecipeAt(Index)].size(); i++) {
			if (this->itemRequiredName[RecipeAt(Index)][i] == matName && this->itemRequiredQuantity[RecipeAt(Index)][i] <= number) {
				return true;
			}
		}
		return false;
	}
	bool _IsUse(int Index, int matIndex, string matName, int number) {
		if (this->itemRequiredName[RecipeAt(Index)][matIndex] == matName && this->itemRequiredQuantity[RecipeAt(Index)][matIndex] <= number) {
			return true;
		}
		return false;
	}
	bool matIsReady(int itemIndex, vector<vector<Object*>> Crafting, vector<vector<int>> CraftingQuantity) {
		int foundCount = 0;
		bool foundOther = false;
		for (int i = 0; i < this->itemRequiredName[RecipeAt(itemIndex)].size(); i++) { // for every material required list element
			cout << this->RecipeAt(itemIndex) << " Have to use " << this->itemRequiredName[RecipeAt(itemIndex)].size() << " material. " << " Now search for : " << this->itemRequiredName[RecipeAt(itemIndex)][i] << endl;
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) { // for every item on crafting slot
					if (Crafting[j][k]->nowIs() != "None" && this->_IsUse(itemIndex, i, Crafting[j][k]->nowIs(), CraftingQuantity[j][k])) {
						foundCount++;
						cout << this->RecipeAt(itemIndex) << " -> Found : " << Crafting[j][k]->nowIs() << endl;
					}
					else if (Crafting[j][k]->nowIs() != "None" && !IsUse(itemIndex, Crafting[j][k]->nowIs(), CraftingQuantity[j][k])) {
						foundOther = true;
					}
				}
			}
		}
		cout << this->RecipeAt(itemIndex) << " is craftable : " << ((this->itemRequiredName[RecipeAt(itemIndex)].size() == foundCount) && !foundOther) << endl << endl;
		return (this->itemRequiredName[RecipeAt(itemIndex)].size() == foundCount) && !foundOther;
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
	RecipeTable Recipe;
	ContextSettings settings;
	template<typename T>
	inline void freeContainer(T& p_container)
	{
		T empty;
		using std::swap;
		swap(p_container, empty);
	}
	void addItem(int x, int y, int amount, string name) {
		*this->Backpack[x][y] = *itemList.object(name);
		this->BackpackQuantity[x][y] = amount;
	}
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
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->CraftingHitbox[i][j][0] = round(1200 + 1100 * 0.06 * j);
				this->CraftingHitbox[i][j][1] = round(200 + 1100 * 0.06 * i);
				this->CraftingHitbox[i][j][2] = round(1260 + 1100 * 0.06 * j);
				this->CraftingHitbox[i][j][3] = round(260 + 1100 * 0.06 * i);
			}
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
	void initSound() {
		this->SoundRepo["POP"].loadFromFile("sound\\a.ogg");
		this->SoundRepo["metalHit"].loadFromFile("sound\\crafting.ogg");
		this->SoundRepo["metalHit2"].loadFromFile("sound\\building.ogg");
		this->SoundRepo["Beep"].loadFromFile("sound\\BEEP_01.ogg");
		this->SoundRepo["Pick"].loadFromFile("Sound\\b.ogg");
		this->SoundRepo["Digging"].loadFromFile("Sound\\digging.ogg");
		this->SoundRepo["Drink"].loadFromFile("Sound\\drink.ogg");
		this->SoundRepo["Eat"].loadFromFile("Sound\\Eat.ogg");
		this->SoundRepo["Fill"].loadFromFile("Sound\\Fill.ogg");
		this->SoundRepo["Charge"].loadFromFile("Sound\\charge.ogg");

		this->SoundFX["Click"].setBuffer(this->SoundRepo["POP"]);
		this->SoundFX["Crafting"].setBuffer(this->SoundRepo["metalHit"]);
		this->SoundFX["Building"].setBuffer(this->SoundRepo["metalHit2"]);
		this->SoundFX["Open"].setBuffer(this->SoundRepo["Beep"]);
		this->SoundFX["Pick"].setBuffer(this->SoundRepo["Pick"]);
		this->SoundFX["Walking"].setBuffer(this->SoundRepo["Walk"]);
		this->SoundFX["Digging"].setBuffer(this->SoundRepo["Digging"]);
		this->SoundFX["Drinking"].setBuffer(this->SoundRepo["Drink"]);
		this->SoundFX["Eat"].setBuffer(this->SoundRepo["Eat"]);
		this->SoundFX["Fill"].setBuffer(this->SoundRepo["Fill"]);
		this->SoundFX["Charge"].setBuffer(this->SoundRepo["Charge"]);

		this->MusicFX["Walking"].openFromFile("Sound\\Walking.wav");
		this->MusicFX["Walking"].setLoop(true);
		this->MusicFX["Running"].openFromFile("Sound\\Running.ogg");
		this->MusicFX["Running"].setLoop(true);
		this->MusicFX["Wind"].openFromFile("Sound\\Wind.ogg");
		this->MusicFX["Wind"].setLoop(true);
	}
	void initItem() {

		this->itemList.createTemplate("Item");
		this->itemList.Template("Item")->setSpriteSize(0.06, 0.06);
		this->itemList.Template("Item")->setImgDim(1000, 1000);
		this->itemList.Template("Item")->addStat("showCount", 1);

		this->itemList.createTemplate("Tool");
		this->itemList.Template("Tool")->setSpriteSize(0.06, 0.06);
		this->itemList.Template("Tool")->setImgDim(1000, 1000);
		this->itemList.Template("Tool")->addStat("showCount", 0);

		// Item registeration section
		this->itemList.registerObject("Herb", "Item", "Herb");
		this->itemList.object("Herb")->addTexture("assets\\Prop\\Item\\Herb.png", "default", 1000);
		this->itemList.object("Herb")->setSpriteTexture("default", 0);
		this->itemList.object("Herb")->addStat("healAmount", 20);
		this->itemList.object("Herb")->tag = "Medicine";

		this->itemList.registerObject("Apple", "Item", "Apple");
		this->itemList.object("Apple")->addTexture("assets\\Prop\\Item\\Apple.png", "default", 1000);
		this->itemList.object("Apple")->setSpriteTexture("default", 0);
		this->itemList.object("Apple")->addStat("healAmount", 10);
		this->itemList.object("Apple")->tag = "Food";

		this->itemList.registerObject("Hydro Flask", "Tool", "Hydro Flask");
		this->itemList.object("Hydro Flask")->addTexture("assets\\Prop\\Item\\Hydro_Flask.png", "default", 1000);
		this->itemList.object("Hydro Flask")->addTexture("assets\\Prop\\Item\\Hydro_Flask_Empty.png", "Empty", 1000);
		this->itemList.object("Hydro Flask")->setSpriteTexture("Empty", 0);
		this->itemList.object("Hydro Flask")->addStat("healAmount", 10);
		this->itemList.object("Hydro Flask")->addStat("durability", 0);
		this->itemList.object("Hydro Flask")->addStat("MaxDurability", 10);
		this->itemList.object("Hydro Flask")->tag = "Tool";

		this->itemList.registerObject("Composite Metal", "Item", "Composite Metal");
		this->itemList.object("Composite Metal")->addTexture("assets\\Prop\\Item\\metalPlate.png", "default", 1000);
		this->itemList.object("Composite Metal")->setSpriteTexture("default", 0);
		this->itemList.object("Composite Metal")->tag = "Material";

		this->itemList.registerObject("Arclyic", "Item", "Arclyic");
		this->itemList.object("Arclyic")->addTexture("assets\\Prop\\Item\\Arclyic.png", "default", 1000);
		this->itemList.object("Arclyic")->setSpriteTexture("default", 0);
		this->itemList.object("Arclyic")->tag = "Material";

		this->itemList.registerObject("Aluminium Plate", "Item", "Aluminium Plate");
		this->itemList.object("Aluminium Plate")->addTexture("assets\\Prop\\Item\\AluminiumPlate.png", "default", 1000);
		this->itemList.object("Aluminium Plate")->setSpriteTexture("default", 0);
		this->itemList.object("Aluminium Plate")->tag = "Material";

		this->itemList.registerObject("Aluminium Nugget", "Item", "Aluminium Plate");
		this->itemList.object("Aluminium Nugget")->addTexture("assets\\Prop\\Item\\AluminiumNugget.png", "default", 1000);
		this->itemList.object("Aluminium Nugget")->setSpriteTexture("default", 0);
		this->itemList.object("Aluminium Nugget")->tag = "Material";

		this->itemList.registerObject("Bread", "Item", "Bread");
		this->itemList.object("Bread")->addTexture("assets\\Prop\\Item\\Bread.png", "default", 1000);
		this->itemList.object("Bread")->setSpriteTexture("default", 0);
		this->itemList.object("Bread")->addStat("healAmount", 20);
		this->itemList.object("Bread")->tag = "Food";

		this->itemList.registerObject("Carrot", "Item", "Carrot");
		this->itemList.object("Carrot")->addTexture("assets\\Prop\\Item\\Carrot.png", "default", 1000);
		this->itemList.object("Carrot")->setSpriteTexture("default", 0);
		this->itemList.object("Carrot")->addStat("healAmount", 10);
		this->itemList.object("Carrot")->tag = "Food";

		this->itemList.registerObject("Carrot Seed", "Item", "Carrot Seed");
		this->itemList.object("Carrot Seed")->addTexture("assets\\Prop\\Item\\CarrotSeed.png", "default", 1000);
		this->itemList.object("Carrot Seed")->setSpriteTexture("default", 0);
		this->itemList.object("Carrot Seed")->tag = "Material";

		this->itemList.registerObject("Copper Nugget", "Item", "Copper Nugget");
		this->itemList.object("Copper Nugget")->addTexture("assets\\Prop\\Item\\CopperNugget.png", "default", 1000);
		this->itemList.object("Copper Nugget")->setSpriteTexture("default", 0);
		this->itemList.object("Copper Nugget")->tag = "Material";

		this->itemList.registerObject("Copper Plate", "Item", "Copper Plate");
		this->itemList.object("Copper Plate")->addTexture("assets\\Prop\\Item\\CopperPlate.png", "default", 1000);
		this->itemList.object("Copper Plate")->setSpriteTexture("default", 0);
		this->itemList.object("Copper Plate")->tag = "Material";

		this->itemList.registerObject("Copper Wire", "Item", "Copper Wire");
		this->itemList.object("Copper Wire")->addTexture("assets\\Prop\\Item\\CopperWire.png", "default", 1000);
		this->itemList.object("Copper Wire")->setSpriteTexture("default", 0);
		this->itemList.object("Copper Wire")->tag = "Material";

		this->itemList.registerObject("Flour", "Item", "Flour");
		this->itemList.object("Flour")->addTexture("assets\\Prop\\Item\\Flour.png", "default", 1000);
		this->itemList.object("Flour")->setSpriteTexture("default", 0);
		this->itemList.object("Flour")->tag = "Material";

		this->itemList.registerObject("Gold Nugget", "Item", "Gold Nugget");
		this->itemList.object("Gold Nugget")->addTexture("assets\\Prop\\Item\\GoldNugget.png", "default", 1000);
		this->itemList.object("Gold Nugget")->setSpriteTexture("default", 0);
		this->itemList.object("Gold Nugget")->tag = "Material";

		this->itemList.registerObject("Gold Plate", "Item", "Gold Plate");
		this->itemList.object("Gold Plate")->addTexture("assets\\Prop\\Item\\GoldPlate.png", "default", 1000);
		this->itemList.object("Gold Plate")->setSpriteTexture("default", 0);
		this->itemList.object("Gold Plate")->tag = "Material";

		this->itemList.registerObject("Gold Wire", "Item", "Gold Wire");
		this->itemList.object("Gold Wire")->addTexture("assets\\Prop\\Item\\GoldWire.png", "default", 1000);
		this->itemList.object("Gold Wire")->setSpriteTexture("default", 0);
		this->itemList.object("Gold Wire")->tag = "Material";

		this->itemList.registerObject("Herb Seed", "Item", "Herb Seed");
		this->itemList.object("Herb Seed")->addTexture("assets\\Prop\\Item\\HerbSeed.png", "default", 1000);
		this->itemList.object("Herb Seed")->setSpriteTexture("default", 0);
		this->itemList.object("Herb Seed")->tag = "Material";

		this->itemList.registerObject("MRE", "Item", "MRE");
		this->itemList.object("MRE")->addTexture("assets\\Prop\\Item\\MRE.png", "default", 1000);
		this->itemList.object("MRE")->setSpriteTexture("default", 0);
		this->itemList.object("MRE")->addStat("healAmount", 80);
		this->itemList.object("MRE")->tag = "Food";

		this->itemList.registerObject("Plastic", "Item", "Plastic");
		this->itemList.object("Plastic")->addTexture("assets\\Prop\\Item\\Plastic.png", "default", 1000);
		this->itemList.object("Plastic")->setSpriteTexture("default", 0);
		this->itemList.object("Plastic")->tag = "Material";

		this->itemList.registerObject("Titanium Nugget", "Item", "Titanium Nugget");
		this->itemList.object("Titanium Nugget")->addTexture("assets\\Prop\\Item\\TitaniumNugget.png", "default", 1000);
		this->itemList.object("Titanium Nugget")->setSpriteTexture("default", 0);
		this->itemList.object("Titanium Nugget")->tag = "Material";

		this->itemList.registerObject("Titanium Plate", "Item", "Titanium Plate");
		this->itemList.object("Titanium Plate")->addTexture("assets\\Prop\\Item\\TitaniumPlate.png", "default", 1000);
		this->itemList.object("Titanium Plate")->setSpriteTexture("default", 0);
		this->itemList.object("Titanium Plate")->tag = "Material";

		this->itemList.registerObject("Wheat Grain", "Item", "Wheat Grain");
		this->itemList.object("Wheat Grain")->addTexture("assets\\Prop\\Item\\WheatGrain.png", "default", 1000);
		this->itemList.object("Wheat Grain")->setSpriteTexture("default", 0);
		this->itemList.object("Wheat Grain")->tag = "Material";

		this->itemList.registerObject("Wheat Seed", "Item", "Wheat Seed");
		this->itemList.object("Wheat Seed")->addTexture("assets\\Prop\\Item\\WheatSeed.png", "default", 1000);
		this->itemList.object("Wheat Seed")->setSpriteTexture("default", 0);
		this->itemList.object("Wheat Seed")->tag = "Material";

		this->itemList.registerObject("Wiring Kit", "Item", "Wiring Kit");
		this->itemList.object("Wiring Kit")->addTexture("assets\\Prop\\Item\\WiringKit.png", "default", 1000);
		this->itemList.object("Wiring Kit")->setSpriteTexture("default", 0);
		this->itemList.object("Wiring Kit")->tag = "Material";

		this->itemList.registerObject("Drill", "Tool", "Drill");
		this->itemList.object("Drill")->addTexture("assets\\Prop\\Item\\drill.png", "default", 1000);
		this->itemList.object("Drill")->setSpriteTexture("default", 0);
		this->itemList.object("Drill")->addStat("durability", 200);
		this->itemList.object("Drill")->tag = "Tool";

		this->itemList.registerObject("Shovel", "Tool", "Shovel");
		this->itemList.object("Shovel")->addTexture("assets\\Prop\\Item\\Shovel.png", "default", 1000);
		this->itemList.object("Shovel")->setSpriteTexture("default", 0);
		this->itemList.object("Shovel")->addStat("durability", 200);
		this->itemList.object("Shovel")->tag = "Tool";

		this->itemList.registerObject("Hammer", "Tool", "Hammer");
		this->itemList.object("Hammer")->addTexture("assets\\Prop\\Item\\Hammer.png", "default", 1000);
		this->itemList.object("Hammer")->setSpriteTexture("default", 0);
		this->itemList.object("Hammer")->addStat("durability", 200);
		this->itemList.object("Hammer")->tag = "Tool";

		this->itemList.registerObject("Power Pack", "Tool", "Power Pack");
		this->itemList.object("Power Pack")->addTexture("assets\\Prop\\Item\\Battery_100.png", "default", 1000);
		this->itemList.object("Power Pack")->addTexture("assets\\Prop\\Item\\Battery_75.png", "default", 1000);
		this->itemList.object("Power Pack")->addTexture("assets\\Prop\\Item\\Battery_50.png", "default", 1000);
		this->itemList.object("Power Pack")->addTexture("assets\\Prop\\Item\\Battery_25.png", "default", 1000);
		this->itemList.object("Power Pack")->addTexture("assets\\Prop\\Item\\Battery_0.png", "default", 1000);
		this->itemList.object("Power Pack")->setSpriteTexture("default", 0);
		this->itemList.object("Power Pack")->addStat("durability", 200);
		this->itemList.object("Power Pack")->addStat("MaxDurability", 200);
		this->itemList.object("Power Pack")->tag = "Tool";

		this->itemList.registerObject("Research Document", "Item", "Research Document");
		this->itemList.object("Research Document")->addTexture("assets\\Prop\\Item\\Doc.png", "default", 1000);
		this->itemList.object("Research Document")->setSpriteTexture("default", 0);
		this->itemList.object("Research Document")->tag = "QuestItem";

		// Default item
		addItem(0, 0, 8, "MRE");
		addItem(0, 1, 8, "Hydro Flask");
		addItem(0, 2, 8, "Hammer");
		addItem(0, 3, 1, "Drill");
		addItem(0, 4, 8, "Composite Metal");
		addItem(0, 5, 8, "Composite Metal");
		addItem(0, 6, 8, "Arclyic");
		addItem(1, 0, 8, "Arclyic");
		addItem(1, 1, 8, "Power Pack");
		addItem(1, 2, 8, "Power Pack");
		addItem(1, 3, 8, "Titanium Plate");
		addItem(1, 4, 8, "Titanium Plate");
		addItem(1, 5, 8, "Wiring Kit");
		addItem(2, 1, 8, "Titanium Plate");
		addItem(2, 2, 8, "Titanium Plate");
		addItem(2, 3, 8, "Aluminium Plate");
		addItem(2, 4, 8, "Aluminium Plate");
		addItem(2, 5, 8, "Aluminium Plate");
		addItem(2, 6, 8, "Gold Plate");
		addItem(2, 7, 8, "Gold Plate");
		addItem(0, 7, 1, "Shovel");
		addItem(0, 8, 8, "Carrot");
	}
	void intiRecipe() {
		this->Recipe.registerRecipe("Copper Wire", 1);
		this->Recipe.addedRequiredItem("Copper Wire", "Copper Plate", 1);

		this->Recipe.registerRecipe("Gold Wire", 1);
		this->Recipe.addedRequiredItem("Gold Wire", "Gold Plate", 1);

		this->Recipe.registerRecipe("Flour", 1);
		this->Recipe.addedRequiredItem("Flour", "Wheat Grain", 4);

		this->Recipe.registerRecipe("Bread", 1);
		this->Recipe.addedRequiredItem("Bread", "Flour", 4);

		this->Recipe.registerRecipe("Carrot Seed", 4);
		this->Recipe.addedRequiredItem("Carrot Seed", "Carrot", 1);

		this->Recipe.registerRecipe("Wheat Seed", 4);
		this->Recipe.addedRequiredItem("Wheat Seed", "Wheat", 1);

		this->Recipe.registerRecipe("Wheat Grain", 1);
		this->Recipe.addedRequiredItem("Wheat Grain", "Wheat Grain", 1);

		this->Recipe.registerRecipe("Herb Seed", 4);
		this->Recipe.addedRequiredItem("Herb Seed", "Herb", 1);

		this->Recipe.registerRecipe("Copper Plate", 4);
		this->Recipe.addedRequiredItem("Copper Plate", "Copper Nugget", 4);
		this->Recipe.addedRequiredItem("Copper Plate", "Hammer", 1);

		this->Recipe.registerRecipe("Aluminium Plate", 4);
		this->Recipe.addedRequiredItem("Aluminium Plate", "Aluminium Nugget", 4);
		this->Recipe.addedRequiredItem("Aluminium Plate", "Hammer", 1);

		this->Recipe.registerRecipe("Gold Plate", 4);
		this->Recipe.addedRequiredItem("Gold Plate", "Gold Nugget", 4);
		this->Recipe.addedRequiredItem("Gold Plate", "Hammer", 1);

		this->Recipe.registerRecipe("Titanium Plate", 4);
		this->Recipe.addedRequiredItem("Titanium Plate", "Titanium Nugget", 4);
		this->Recipe.addedRequiredItem("Titanium Plate", "Hammer", 1);

		this->Recipe.registerRecipe("Composite Metal", 4);
		this->Recipe.addedRequiredItem("Composite Metal", "Copper Plate", 8);
		this->Recipe.addedRequiredItem("Composite Metal", "Aluminium Plate", 4);
		this->Recipe.addedRequiredItem("Composite Metal", "Titanium Plate", 4);
		this->Recipe.addedRequiredItem("Composite Metal", "Gold Plate", 1);
		this->Recipe.addedRequiredItem("Composite Metal", "Hammer", 1);

		this->Recipe.registerRecipe("Wiring Kit", 1);
		this->Recipe.addedRequiredItem("Wiring Kit", "Copper Wire", 8);
		this->Recipe.addedRequiredItem("Wiring Kit", "Gold Wire", 4);
		this->Recipe.addedRequiredItem("Wiring Kit", "Gold Plate", 1);

		this->Recipe.registerRecipe("Power Pack", 1);
		this->Recipe.addedRequiredItem("Power Pack", "Wiring Kit", 1);
		this->Recipe.addedRequiredItem("Power Pack", "Aluminium Plate", 4);
		this->Recipe.addedRequiredItem("Power Pack", "Composite Metal", 2);
		this->Recipe.addedRequiredItem("Power Pack", "Gold Plate", 1);

		this->Recipe.registerRecipe("Hydro Flask", 1);
		this->Recipe.addedRequiredItem("Hydro Flask", "Aluminium Plate", 4);
		this->Recipe.addedRequiredItem("Hydro Flask", "Hammer", 1);

		printf("Recipe Number = %d\n", this->Recipe.recipeNumber());
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
			this->Dialog["itemCount"].registerObject("itemCountBG" + to_string(i), "itemCountBG");
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
			this->Dialog["itemCount"].object("itemCount" + to_string(i))->setPosition({ x ,y });
			this->Dialog["itemCount"].object("itemCountBG" + to_string(i))->setPosition({ x ,y });
		}

		this->Dialog["itemUse"].registerObject("metalUse_pump", "BuildingMenu");
		this->Dialog["itemUse"].object("metalUse_pump")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["itemUse"].object("metalUse_pump")->setCharacterSize(50);
		this->Dialog["itemUse"].object("metalUse_pump")->setString("10");
		this->Dialog["itemUse"].object("metalUse_pump")->setPosition({ 550,210 });

		this->Dialog["itemUse"].registerObject("ArclyicUse_pump", "BuildingMenu");
		this->Dialog["itemUse"].object("ArclyicUse_pump")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["itemUse"].object("ArclyicUse_pump")->setCharacterSize(50);
		this->Dialog["itemUse"].object("ArclyicUse_pump")->setString("5");
		this->Dialog["itemUse"].object("ArclyicUse_pump")->setPosition({ 650,210 });

		this->Dialog["itemUse"].registerObject("metalUse_Solar", "BuildingMenu");
		this->Dialog["itemUse"].object("metalUse_Solar")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["itemUse"].object("metalUse_Solar")->setCharacterSize(50);
		this->Dialog["itemUse"].object("metalUse_Solar")->setString("10");
		this->Dialog["itemUse"].object("metalUse_Solar")->setPosition({ 550,410 });

		this->Dialog["itemUse"].registerObject("ArclyicUse_Solar", "BuildingMenu");
		this->Dialog["itemUse"].object("ArclyicUse_Solar")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["itemUse"].object("ArclyicUse_Solar")->setCharacterSize(50);
		this->Dialog["itemUse"].object("ArclyicUse_Solar")->setString("2");
		this->Dialog["itemUse"].object("ArclyicUse_Solar")->setPosition({ 650,410 });

		this->Dialog["itemUse"].registerObject("WiringKitUse_Solar", "BuildingMenu");
		this->Dialog["itemUse"].object("WiringKitUse_Solar")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["itemUse"].object("WiringKitUse_Solar")->setCharacterSize(50);
		this->Dialog["itemUse"].object("WiringKitUse_Solar")->setString("1");
		this->Dialog["itemUse"].object("WiringKitUse_Solar")->setPosition({ 750,410 });

		this->Dialog["itemUse"].registerObject("TitaniumPlateUse_Rocket", "BuildingMenu");
		this->Dialog["itemUse"].object("TitaniumPlateUse_Rocket")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["itemUse"].object("TitaniumPlateUse_Rocket")->setCharacterSize(50);
		this->Dialog["itemUse"].object("TitaniumPlateUse_Rocket")->setString("30");
		this->Dialog["itemUse"].object("TitaniumPlateUse_Rocket")->setPosition({ 1150,210 });

		this->Dialog["itemUse"].registerObject("AluminiumPlateUse_Rocket", "BuildingMenu");
		this->Dialog["itemUse"].object("AluminiumPlateUse_Rocket")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["itemUse"].object("AluminiumPlateUse_Rocket")->setCharacterSize(50);
		this->Dialog["itemUse"].object("AluminiumPlateUse_Rocket")->setString("20");
		this->Dialog["itemUse"].object("AluminiumPlateUse_Rocket")->setPosition({ 1250,210 });

		this->Dialog["itemUse"].registerObject("GoldPlateUse_Rocket", "BuildingMenu");
		this->Dialog["itemUse"].object("GoldPlateUse_Rocket")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["itemUse"].object("GoldPlateUse_Rocket")->setCharacterSize(50);
		this->Dialog["itemUse"].object("GoldPlateUse_Rocket")->setString("10");
		this->Dialog["itemUse"].object("GoldPlateUse_Rocket")->setPosition({ 1350,210 });

		this->Dialog["itemUse"].registerObject("WiringKitUse_Rocket", "BuildingMenu");
		this->Dialog["itemUse"].object("WiringKitUse_Rocket")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["itemUse"].object("WiringKitUse_Rocket")->setCharacterSize(50);
		this->Dialog["itemUse"].object("WiringKitUse_Rocket")->setString("5");
		this->Dialog["itemUse"].object("WiringKitUse_Rocket")->setPosition({ 1450,210 });

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
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->Dialog["CraftingItem"].registerObject("CraftingItemCountBG" + to_string(i) + to_string(j), "itemCountBG");
				this->Dialog["CraftingItem"].registerObject("CraftingItemCount" + to_string(i) + to_string(j), "itemCount");

				this->Dialog["CraftingItem"].object("CraftingItemCountBG" + to_string(i) + to_string(j))->setFont(this->Dialog["Font"].font["Mitr-Bold"]);
				this->Dialog["CraftingItem"].object("CraftingItemCountBG" + to_string(i) + to_string(j))->setCharacterSize(25);
				this->Dialog["CraftingItem"].object("CraftingItemCountBG" + to_string(i) + to_string(j))->setString(to_string(i));
				this->Dialog["CraftingItem"].object("CraftingItemCountBG" + to_string(i) + to_string(j))->setStyle(Text::Bold);
				this->Dialog["CraftingItem"].object("CraftingItemCountBG" + to_string(i) + to_string(j))->setFillColor(Color::White);

				this->Dialog["CraftingItem"].object("CraftingItemCount" + to_string(i) + to_string(j))->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
				this->Dialog["CraftingItem"].object("CraftingItemCount" + to_string(i) + to_string(j))->setCharacterSize(25);
				this->Dialog["CraftingItem"].object("CraftingItemCount" + to_string(i) + to_string(j))->setString(to_string(i));
				this->Dialog["CraftingItem"].object("CraftingItemCount" + to_string(i) + to_string(j))->setFillColor(Color::Black);
				const float x = 1230 + 1100 * 0.06 * i, y = 263 + 1100 * 0.06 * j;
				this->Dialog["CraftingItem"].object("CraftingItemCount" + to_string(i) + to_string(j))->setPosition({ x ,y });
				this->Dialog["CraftingItem"].object("CraftingItemCountBG" + to_string(i) + to_string(j))->setPosition({ x ,y });
			}
		}

		this->Dialog["Victory"].registerObject("Retry", "Victory");
		this->Dialog["Victory"].object("Retry")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["Victory"].object("Retry")->setString("Retry");
		this->Dialog["Victory"].object("Retry")->setFillColor(Color::White);
		this->Dialog["Victory"].object("Retry")->setCharacterSize(75);
		this->Dialog["Victory"].object("Retry")->setPosition({ 300,750 });

		this->Dialog["Victory"].registerObject("Exit", "Victory");
		this->Dialog["Victory"].object("Exit")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["Victory"].object("Exit")->setString("Exit");
		this->Dialog["Victory"].object("Exit")->setFillColor(Color::White);
		this->Dialog["Victory"].object("Exit")->setCharacterSize(75);
		this->Dialog["Victory"].object("Exit")->setPosition({ 1200,750 });

		this->Dialog["Victory"].registerObject("Victory", "Victory");
		this->Dialog["Victory"].object("Victory")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["Victory"].object("Victory")->setString("Mission Completed");
		this->Dialog["Victory"].object("Victory")->setFillColor(Color::White);
		this->Dialog["Victory"].object("Victory")->setCharacterSize(100);
		this->Dialog["Victory"].object("Victory")->setPosition({ 350,50 });

		this->Dialog["Victory"].registerObject("Score", "Victory");
		this->Dialog["Victory"].object("Score")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["Victory"].object("Score")->setString("0");
		this->Dialog["Victory"].object("Score")->setFillColor(Color::White);
		this->Dialog["Victory"].object("Score")->setCharacterSize(100);
		this->Dialog["Victory"].object("Score")->setPosition({ 800,450 });

		this->Dialog["GameOver"].registerObject("Retry", "GameOver");
		this->Dialog["GameOver"].object("Retry")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["GameOver"].object("Retry")->setString("Retry");
		this->Dialog["GameOver"].object("Retry")->setFillColor(Color::White);
		this->Dialog["GameOver"].object("Retry")->setCharacterSize(75);
		this->Dialog["GameOver"].object("Retry")->setPosition({ 300,750 });

		this->Dialog["GameOver"].registerObject("Exit", "GameOver");
		this->Dialog["GameOver"].object("Exit")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["GameOver"].object("Exit")->setString("Exit");
		this->Dialog["GameOver"].object("Exit")->setFillColor(Color::White);
		this->Dialog["GameOver"].object("Exit")->setCharacterSize(75);
		this->Dialog["GameOver"].object("Exit")->setPosition({ 1200,750 });

		this->Dialog["GameOver"].registerObject("GameOver", "GameOver");
		this->Dialog["GameOver"].object("GameOver")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["GameOver"].object("GameOver")->setString("Mission Failed");
		this->Dialog["GameOver"].object("GameOver")->setFillColor(Color::White);
		this->Dialog["GameOver"].object("GameOver")->setCharacterSize(100);
		this->Dialog["GameOver"].object("GameOver")->setPosition({ 450,50 });

	}
	void initObject() {
		Object* ptr = new Object(54862);
		this->DrawField["ItemOnMouse"].push_back(ptr);
		this->DrawField["ItemOnMouse"][0]->Is("None");
		for (int i = 0; i < 9; i++) {
			Object* ptr = new Object(rand() % 10000);
			ptr->setImgDim(1000, 1000);
			ptr->setPosX(503 + 1100 * 0.06 * i);
			ptr->setPosY(800);
			ptr->Is("None");
			this->DrawField["ItemUseSlot"].push_back(ptr); //old
			this->DrawField["InventoryUseSlot"].push_back(ptr); //old
			this->DrawField["Hotbar"].push_back(ptr);
			this->DrawField["Hotbar_HUD"].push_back(ptr);
			ItemUseSlotQuantity.push_back(0); //old
			HotbarQuantity.push_back(0);
		}
		for (int i = 0; i < 3; i++) {
			Backpack.push_back({});
			BackpackQuantity.push_back({});
			for (int j = 0; j < 9; j++) {
				Object* ptr = new Object(rand() % 10000);
				ptr->setImgDim(1000, 1000);
				ptr->setPosX(200 + 1000 * 0.06 * i);
				ptr->setPosY(503 + 1000 * 0.06 * j);
				ptr->Is("None");
				Backpack[i].push_back(ptr);
				BackpackQuantity[i].push_back(0);
			}
		}
		for (int i = 0; i < 3; i++) {
			Crafting.push_back({});
			CraftingQuantity.push_back({});
			for (int j = 0; j < 3; j++) {
				Object* ptr = new Object(rand() % 10000);
				ptr->setImgDim(1000, 1000);
				ptr->setPosX(1230 + 1100 * 0.06 * i);
				ptr->setPosY(233 + 1100 * 0.06 * j);
				ptr->Is("None");
				Crafting[i].push_back(ptr);
				CraftingQuantity[i].push_back(0);
			}
		}
		this->itemOutput.setPosX(503 + 1100 * 0.06 * 9 + 100 + 1100 * 0.06);
		this->itemOutput.setPosX(200 + 1100 * 0.06 * 4);

		this->Field["Dynamic"].createTemplate("Blank");

		this->Field["Dynamic"].createTemplate("Item");
		this->Field["Dynamic"].Template("Item")->addTexture("assets\\Prop\\Item\\Apple.png", "default", 1000);
		this->Field["Dynamic"].Template("Item")->setSpriteTexture("default", 0);
		this->Field["Dynamic"].Template("Item")->setSpriteSize(0.005, 0.005);
		this->Field["Dynamic"].Template("Item")->setImgDim(1000, 1000);
		this->Field["Dynamic"].Template("Item")->setType("Static");

		this->Field["Dynamic"].createTemplate("Rocky");
		this->Field["Dynamic"].Template("Rocky")->addTexture("assets\\Prop\\Rock\\Rock1.png", "default0", 1000);
		this->Field["Dynamic"].Template("Rocky")->addTexture("assets\\Prop\\Rock\\Rock2.png", "default1", 1000);
		this->Field["Dynamic"].Template("Rocky")->addTexture("assets\\Prop\\Rock\\Rock3.png", "default2", 1000);
		this->Field["Dynamic"].Template("Rocky")->setSpriteTexture("default1", 0);
		this->Field["Dynamic"].Template("Rocky")->setSpriteSize(0.1, 0.1);
		this->Field["Dynamic"].Template("Rocky")->setImgDim(900, 900);
		this->Field["Dynamic"].Template("Rocky")->isPassable(false);
		this->Field["Dynamic"].Template("Rocky")->setType("Dynamic");

		this->Field["Dynamic"].createTemplate("Doc");
		this->Field["Dynamic"].Template("Doc")->addTexture("assets\\Prop\\Building\\DocumentCase.png", "default", 1000);
		this->Field["Dynamic"].Template("Doc")->setSpriteTexture("default", 0);
		this->Field["Dynamic"].Template("Doc")->setSpriteSize(0.1, 0.1);
		this->Field["Dynamic"].Template("Doc")->setImgDim(1200, 1600);
		this->Field["Dynamic"].Template("Doc")->isPassable(false);
		this->Field["Dynamic"].Template("Doc")->setType("Dynamic");
		this->Field["Dynamic"].Template("Doc")->tag = "Building";

		this->Field["Dynamic"].createTemplate("BG_Element");
		this->Field["Dynamic"].Template("BG_Element")->setType("Dynamic");
		this->Field["Dynamic"].Template("BG_Element")->setPosX(0);
		this->Field["Dynamic"].Template("BG_Element")->setPosY(0);

		this->Field["Dynamic"].registerObject("Anchor", "BG_Element", "Anchor");
		this->Field["Dynamic"].object("Anchor")->setPosX(-3000);
		this->Field["Dynamic"].object("Anchor")->setPosY(-3000);
		this->Field["Dynamic"].object("Anchor")->isPassable(true);
		this->Anchor = this->Field["Dynamic"].object("Anchor");

		this->Field["Dynamic"].createTemplate("dropItem");
		this->Field["Dynamic"].Template("dropItem")->addTexture("assets\\Prop\\Item\\Herb.png", "Herb", 1000);
		this->Field["Dynamic"].Template("dropItem")->addTexture("assets\\Prop\\Item\\Apple.png", "Apple", 1000);
		this->Field["Dynamic"].Template("dropItem")->setSpriteTexture("Apple", 0);
		this->Field["Dynamic"].Template("dropItem")->setSpriteSize(0.1, 0.1);
		this->Field["Dynamic"].Template("dropItem")->setImgDim(1000, 1000);
		this->Field["Dynamic"].Template("dropItem")->setType("Dynamic");
		/*
		for (int i = 0; i < 50; i++) {
			this->Field["Dynamic"].registerObject("Apple_" + to_string(i), "dropItem", "Apple");
			this->Field["Dynamic"].object("Apple_" + to_string(i))->setSpriteTexture("Apple", 0);
			this->Field["Dynamic"].object("Apple_" + to_string(i))->setOffsetPosX(2000 + rand() % 2000);
			this->Field["Dynamic"].object("Apple_" + to_string(i))->setOffsetPosY(2000 + rand() % 2000);
			this->Field["Dynamic"].object("Apple_" + to_string(i))->tag = "fallItem";
		}
		for (int i = 0; i < 50; i++) {
			this->Field["Dynamic"].registerObject("Herb_" + to_string(i), "dropItem", "Herb");
			this->Field["Dynamic"].object("Herb_" + to_string(i))->setSpriteTexture("Herb", 0);
			this->Field["Dynamic"].object("Herb_" + to_string(i))->setOffsetPosX(2000 + rand() % 2000);
			this->Field["Dynamic"].object("Herb_" + to_string(i))->setOffsetPosY(2000 + rand() % 2000);
			this->Field["Dynamic"].object("Herb_" + to_string(i))->tag = "fallItem";
		}
		*/
		this->Field["Dynamic"].createTemplate("Structure");
		this->Field["Dynamic"].Template("Structure")->setPosX(this->Field["Dynamic"].object("Anchor")->PosX());
		this->Field["Dynamic"].Template("Structure")->setPosY(this->Field["Dynamic"].object("Anchor")->PosY());
		this->Field["Dynamic"].Template("Structure")->setType("Dynamic");
		this->Field["Dynamic"].Template("Structure")->isPassable(false);

		this->Field["Dynamic"].createTemplate("Rocket");
		this->Field["Dynamic"].Template("Rocket")->addTexture("assets\\Prop\\Building\\Rocket.png", "Rocket", 1000);
		this->Field["Dynamic"].Template("Rocket")->setSpriteTexture("Rocket", 0);
		this->Field["Dynamic"].Template("Rocket")->setSpriteSize(0.1, 0.1);
		this->Field["Dynamic"].Template("Rocket")->setImgDim(2400, 3200);
		this->Field["Dynamic"].Template("Rocket")->setPosX(this->Field["Dynamic"].object("Anchor")->PosX());
		this->Field["Dynamic"].Template("Rocket")->setPosY(this->Field["Dynamic"].object("Anchor")->PosY());
		this->Field["Dynamic"].Template("Rocket")->setType("Dynamic");
		this->Field["Dynamic"].Template("Rocket")->isPassable(false);
		this->Field["Dynamic"].Template("Rocket")->tag = "Building";

		this->Field["Dynamic"].createTemplate("Pump");
		this->Field["Dynamic"].Template("Pump")->addTexture("assets\\Prop\\Building\\Pumpy.png", "pump", 1000);
		this->Field["Dynamic"].Template("Pump")->setSpriteTexture("pump", 0);
		this->Field["Dynamic"].Template("Pump")->setSpriteSize(0.1, 0.1);
		this->Field["Dynamic"].Template("Pump")->setImgDim(1200, 1600);
		this->Field["Dynamic"].Template("Pump")->setPosX(this->Field["Dynamic"].object("Anchor")->PosX());
		this->Field["Dynamic"].Template("Pump")->setPosY(this->Field["Dynamic"].object("Anchor")->PosY());
		this->Field["Dynamic"].Template("Pump")->setType("Dynamic");
		this->Field["Dynamic"].Template("Pump")->isPassable(false);
		this->Field["Dynamic"].Template("Pump")->tag = "Building";

		this->Field["Dynamic"].createTemplate("SolarCell");
		this->Field["Dynamic"].Template("SolarCell")->addTexture("assets\\Prop\\Building\\SolarCell.png", "SolarCell", 1000);
		this->Field["Dynamic"].Template("SolarCell")->setSpriteTexture("SolarCell", 0);
		this->Field["Dynamic"].Template("SolarCell")->setSpriteSize(0.1, 0.1);
		this->Field["Dynamic"].Template("SolarCell")->setImgDim(1200, 1600);
		this->Field["Dynamic"].Template("SolarCell")->setPosX(this->Field["Dynamic"].object("Anchor")->PosX());
		this->Field["Dynamic"].Template("SolarCell")->setPosY(this->Field["Dynamic"].object("Anchor")->PosY());
		this->Field["Dynamic"].Template("SolarCell")->setType("Dynamic");
		this->Field["Dynamic"].Template("SolarCell")->isPassable(false);
		this->Field["Dynamic"].Template("SolarCell")->tag = "Building";

		this->Field["GameBG"].createTemplate("Floor");
		this->Field["GameBG"].Template("Floor")->addTexture("assets\\Prop\\Floor\\Floor11.png", "default", 1000);
		this->Field["GameBG"].Template("Floor")->setSpriteTexture("default", 0);
		this->Field["GameBG"].Template("Floor")->setSpriteSize(0.1, 0.1);
		this->Field["GameBG"].Template("Floor")->setImgDim(5000, 5000);
		this->Field["GameBG"].Template("Floor")->setPosX(this->Field["Dynamic"].object("Anchor")->PosX());
		this->Field["GameBG"].Template("Floor")->setPosY(this->Field["Dynamic"].object("Anchor")->PosY());
		this->Field["GameBG"].Template("Floor")->setType("Dynamic");
		this->Field["GameBG"].Template("Floor")->isPassable(true);
		this->Field["GameBG"].Template("Floor")->tag = "BG";

		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				string ObjName = "Floor" + to_string(i) + "*" + to_string(j);
				this->Field["GameBG"].registerObject(ObjName, "Floor", "Floor");
				this->Field["GameBG"].object(ObjName)->setOffsetPosX(i * 5000 * 0.1 / 1.1);
				this->Field["GameBG"].object(ObjName)->setOffsetPosY(j * 5000 * 0.1 / 1.1);
			}
		}

		for (int j = 0; j < 50; j++) {
			float size = rand() % 10;
			this->Field["Dynamic"].registerObject(to_string(i) + to_string(j), "Rocky", "Rock");
			this->Field["Dynamic"].object(to_string(i) + to_string(j))->setSpriteTexture("default" + to_string(rand() % 3), 0);
			this->Field["Dynamic"].object(to_string(i) + to_string(j))->setOffsetPosX(rand() % 5000);
			this->Field["Dynamic"].object(to_string(i) + to_string(j))->setOffsetPosY(rand() % 5000);
		}

		for (int j = 0; j < 50; j++) {
			float size = rand() % 10;
			this->Field["Dynamic"].registerObject("Doc" + to_string(j), "Doc", "Doc");
			this->Field["Dynamic"].object("Doc" + to_string(j))->setOffsetPosX(rand() % 13000);
			this->Field["Dynamic"].object("Doc" + to_string(j))->setOffsetPosY(rand() % 13000);
		}

		this->Field["Dynamic"].registerObject("Hut", "Structure", "Hut");
		this->Field["Dynamic"].object("Hut")->addTexture("assets\\Prop\\Building\\SurvivalHut.png", "default", 1000);
		this->Field["Dynamic"].object("Hut")->setSpriteTexture("default", 0);
		this->Field["Dynamic"].object("Hut")->setSpriteSize(0.1, 0.1);
		this->Field["Dynamic"].object("Hut")->setOffsetPosX(2500);
		this->Field["Dynamic"].object("Hut")->setOffsetPosY(2500);
		this->Field["Dynamic"].object("Hut")->setImgDim(4800, 3200);

		this->Field["Dynamic"].registerObject("Elon", "Blank", "Elon");
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Walk1.png", "walk", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Walk2.png", "walk", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Walk3.png", "walk", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Walk4.png", "walk", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Walk5.png", "walk", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Walk4.png", "walk", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Walk3.png", "walk", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Walk2.png", "walk", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Idle.png", "idle", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Dying1.png", "dying", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Dying2.png", "dying", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Dying3.png", "dying", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Dying4.png", "dying", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Dying5.png", "dying", 8);
		this->Field["Dynamic"].object("Elon")->addTexture("assets\\Elon\\Elon_Dying5.png", "dying", 20000000);
		this->Field["Dynamic"].object("Elon")->loop = true;
		this->Field["Dynamic"].object("Elon")->setSpriteSize(0.1, 0.1);
		this->Field["Dynamic"].object("Elon")->setImgDim(1000, 1600);
		this->Field["Dynamic"].object("Elon")->addStat("Health", 100);
		this->Field["Dynamic"].object("Elon")->addStat("Thirst", 100);
		this->Field["Dynamic"].object("Elon")->addStat("Hunger", 100);
		this->Field["Dynamic"].object("Elon")->addStat("Air", 10000);
		this->Field["Dynamic"].object("Elon")->addStat("Alive", 1);
		this->Field["Dynamic"].object("Elon")->setPosX(800 - 1000 * 0.1 * 1 / 2);
		this->Field["Dynamic"].object("Elon")->setPosY(400);
		this->Field["Dynamic"].object("Elon")->setType("Static");
		this->Elon = this->Field["Dynamic"].object("Elon");

		this->Field["MiniElon"].createTemplate("Blank");

		this->Field["Dynamic"].registerObject("MiniElon", "Blank", "MiniElon");
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Walk1.png", "walk", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Walk2.png", "walk", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Walk3.png", "walk", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Walk4.png", "walk", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Walk5.png", "walk", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Walk4.png", "walk", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Walk3.png", "walk", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Walk2.png", "walk", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Idle.png", "idle", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Dying1.png", "dying", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Dying2.png", "dying", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Dying3.png", "dying", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Dying4.png", "dying", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Dying5.png", "dying", 8);
		this->Field["Dynamic"].object("MiniElon")->addTexture("assets\\Elon\\Elon_Dying5.png", "dying", 20000000);
		this->Field["Dynamic"].object("MiniElon")->loop = true;
		this->Field["Dynamic"].object("MiniElon")->setSpriteSize(0.05, 0.05);
		this->Field["Dynamic"].object("MiniElon")->setImgDim(1000, 1600);
		this->Field["Dynamic"].object("MiniElon")->setPosX(800 - 1000 * 0.1 * 1 / 2);
		this->Field["Dynamic"].object("MiniElon")->setPosY(400);
		this->Field["Dynamic"].object("MiniElon")->setType("Dynamic");
		this->MiniElon = this->Field["Dynamic"].object("MiniElon");

	}
	void intitHUD() {
		this->Field["HUD"].createTemplate("Blank");

		this->Field["HUD"].createTemplate("StatBar");
		this->Field["HUD"].Template("StatBar")->addTexture("assets\\Prop\\HUD\\StatFrame.png", "frame", 1000);
		this->Field["HUD"].Template("StatBar")->addTexture("assets\\Prop\\HUD\\Health.png", "Stat1", 1000);
		this->Field["HUD"].Template("StatBar")->addTexture("assets\\Prop\\HUD\\Hunger.png", "Stat2", 1000);
		this->Field["HUD"].Template("StatBar")->addTexture("assets\\Prop\\HUD\\Thirst.png", "Stat3", 1000);
		this->Field["HUD"].Template("StatBar")->addTexture("assets\\Prop\\HUD\\Air.png", "Stat4", 1000);
		this->Field["HUD"].Template("StatBar")->setSpriteTexture("frame", 0);
		this->Field["HUD"].Template("StatBar")->setSpriteSize(0.06, 0.06);
		this->Field["HUD"].Template("StatBar")->setType("Static");

		this->Field["HUD"].createTemplate("itemFrame");
		this->Field["HUD"].Template("itemFrame")->addTexture("assets\\Prop\\HUD\\ItemFrameWhite.png", "default", 1000);
		this->Field["HUD"].Template("itemFrame")->setSpriteTexture("default", 0);
		this->Field["HUD"].Template("itemFrame")->setSpriteSize(0.06, 0.06);
		this->Field["HUD"].Template("itemFrame")->setType("Static");
		this->Field["HUD"].Template("itemFrame")->isPassable(false);

		for (int i = 0; i < 9; i++) {
			this->Field["HUD"].registerObject("ItemFrame" + to_string(i), "itemFrame", "ItemFrame");
			this->Field["HUD"].object("ItemFrame" + to_string(i))->setPosX(503 + 1100 * 0.06 * i);
			this->Field["HUD"].object("ItemFrame" + to_string(i))->setPosY(800);

		}

		this->Field["HUD"].registerObject("ItemPrt", "Blank", "ItemPrt");
		this->Field["HUD"].object("ItemPrt")->addTexture("assets\\Prop\\HUD\\ItemPointer.png", "default", 1000);
		this->Field["HUD"].object("ItemPrt")->setSpriteTexture("default", 0);
		this->Field["HUD"].object("ItemPrt")->setSpriteSize(0.06, 0.06);
		this->Field["HUD"].object("ItemPrt")->setImgDim(1100, 1500);
		this->Field["HUD"].object("ItemPrt")->setPosX(503 + 1100 * 0.06 / 2);
		this->Field["HUD"].object("ItemPrt")->setPosY(833);
		this->Field["HUD"].object("ItemPrt")->setType("Static");

		for (int i = 0; i < 4; i++) {
			this->Field["HUD"].registerObject("StatBar_Fill" + to_string(i), "StatBar", "StatBar_Fill");
			this->Field["HUD"].object("StatBar_Fill" + to_string(i))->setSpriteSize(0.06, -0.06);
			this->Field["HUD"].object("StatBar_Fill" + to_string(i))->setSpriteTexture("Stat" + to_string(i + 1), 0);
			this->Field["HUD"].object("StatBar_Fill" + to_string(i))->setPosX(1300 + 500 * 0.1 * i);
			this->Field["HUD"].object("StatBar_Fill" + to_string(i))->setPosY(600 + 3200 * 0.06);
		}
		for (int i = 0; i < 4; i++) {
			this->Field["HUD"].registerObject("StatBar" + to_string(i), "StatBar", "StatBar");
			this->Field["HUD"].object("StatBar" + to_string(i))->setPosX(1300 + 500 * 0.1 * i);
			this->Field["HUD"].object("StatBar" + to_string(i))->setPosY(600);
		}
	}
	void intitUI() {
		this->Field["PauseUI"].createTemplate("PauseUI_BG");
		this->Field["PauseUI"].Template("PauseUI_BG")->addTexture("assets\\Prop\\HUD\\Pause.png", "default", 1000);
		this->Field["PauseUI"].Template("PauseUI_BG")->setSpriteSize(0.5, 0.5);
		this->Field["PauseUI"].Template("PauseUI_BG")->setImgDim(3200, 1800);
		this->Field["PauseUI"].Template("PauseUI_BG")->setPosX(800);
		this->Field["PauseUI"].Template("PauseUI_BG")->setPosY(450);
		this->Field["PauseUI"].Template("PauseUI_BG")->setType("Static");
		this->Field["PauseUI"].Template("PauseUI_BG")->tag = "PauseUI";

		this->Field["PauseUI"].registerObject("PauseBG", "PauseUI_BG", "PauseBG");
		this->Field["PauseUI"].object("PauseBG")->setSpriteTexture("default", 0);

		this->Field["BuildUI"].createTemplate("BuildUI_BG");
		this->Field["BuildUI"].Template("BuildUI_BG")->addTexture("assets\\Prop\\HUD\\Pause.png", "default", 1000);
		this->Field["BuildUI"].Template("BuildUI_BG")->setSpriteSize(0.5, 0.5);
		this->Field["BuildUI"].Template("BuildUI_BG")->setImgDim(3200, 1800);
		this->Field["BuildUI"].Template("BuildUI_BG")->setPosX(800);
		this->Field["BuildUI"].Template("BuildUI_BG")->setPosY(450);
		this->Field["BuildUI"].Template("BuildUI_BG")->setType("Static");
		this->Field["BuildUI"].Template("BuildUI_BG")->tag = "BuildUI";

		this->Field["BuildUI"].registerObject("BuildBG", "BuildUI_BG", "BuiledBG");
		this->Field["BuildUI"].object("BuildBG")->setSpriteTexture("default", 0);

		this->Field["InventoryUI"].createTemplate("Inventory_BG");
		this->Field["InventoryUI"].Template("Inventory_BG")->addTexture("assets\\Prop\\HUD\\Pause.png", "default", 1000);
		this->Field["InventoryUI"].Template("Inventory_BG")->setSpriteSize(0.5, 0.5);
		this->Field["InventoryUI"].Template("Inventory_BG")->setImgDim(3200, 1800);
		this->Field["InventoryUI"].Template("Inventory_BG")->setPosX(800);
		this->Field["InventoryUI"].Template("Inventory_BG")->setPosY(450);
		this->Field["InventoryUI"].Template("Inventory_BG")->setType("Static");
		this->Field["InventoryUI"].Template("Inventory_BG")->tag = "InventoryUI";

		this->Field["InventoryUI"].createTemplate("itemFrame");
		this->Field["InventoryUI"].Template("itemFrame")->addTexture("assets\\Prop\\HUD\\ItemFrameWhite.png", "default", 1000);
		this->Field["InventoryUI"].Template("itemFrame")->setSpriteTexture("default", 0);
		this->Field["InventoryUI"].Template("itemFrame")->setSpriteSize(0.06, 0.06);
		this->Field["InventoryUI"].Template("itemFrame")->setType("Static");
		this->Field["InventoryUI"].Template("itemFrame")->isPassable(false);
		this->Field["InventoryUI"].Template("itemFrame")->tag = "InventoryUI";

		this->Field["InventoryUI"].registerObject("InventoryBG", "Inventory_BG", "InventoryBG");
		this->Field["InventoryUI"].object("InventoryBG")->setSpriteTexture("default", 0);

		for (int i = 0; i < 9; i++) {
			this->Field["InventoryUI"].registerObject("UseSlot" + to_string(i), "itemFrame", "UseSlot");
			this->Field["InventoryUI"].object("UseSlot" + to_string(i))->tag = "InventoryUI";
			this->Field["InventoryUI"].object("UseSlot" + to_string(i))->setPosX(503 + 1100 * 0.06 * i);
			this->Field["InventoryUI"].object("UseSlot" + to_string(i))->setPosY(500);
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 9; j++) {
				this->Field["InventoryUI"].registerObject("InventorySlot" + to_string(i) + to_string(j), "itemFrame", "InventorySlot");
				this->Field["InventoryUI"].object("InventorySlot" + to_string(i) + to_string(j))->tag = "InventoryUI";
				this->Field["InventoryUI"].object("InventorySlot" + to_string(i) + to_string(j))->setPosX(503 + 1100 * 0.06 * j);
				this->Field["InventoryUI"].object("InventorySlot" + to_string(i) + to_string(j))->setPosY(200 + 1100 * 0.06 * i);
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->Field["InventoryUI"].registerObject("CraftingSlot" + to_string(i) + to_string(j), "itemFrame", "CraftingSlot");
				this->Field["InventoryUI"].object("CraftingSlot" + to_string(i) + to_string(j))->tag = "InventoryUI";
				this->Field["InventoryUI"].object("CraftingSlot" + to_string(i) + to_string(j))->setPosX(503 + 1100 * 0.06 * 9 + 100 + 1100 * 0.06 * j);
				this->Field["InventoryUI"].object("CraftingSlot" + to_string(i) + to_string(j))->setPosY(200 + 1100 * 0.06 * i);
			}
		}

		this->Field["InventoryUI"].registerObject("craftingOutput", "itemFrame", "craftingOutput");
		this->Field["InventoryUI"].object("craftingOutput")->tag = "InventoryUI";
		this->Field["InventoryUI"].object("craftingOutput")->setPosX(503 + 1100 * 0.06 * 9 + 100 + 1100 * 0.06);
		this->Field["InventoryUI"].object("craftingOutput")->setPosY(200 + 1100 * 0.06 * 4);

		this->Field["BuildUI"].createTemplate("BuildingSample");
		this->Field["BuildUI"].Template("BuildingSample")->addTexture("assets\\Prop\\Building\\Pumpy.png", "Pump", 1000);
		this->Field["BuildUI"].Template("BuildingSample")->addTexture("assets\\Prop\\Building\\Solarcell.png", "SolarCell", 1000);
		this->Field["BuildUI"].Template("BuildingSample")->addTexture("assets\\Prop\\Building\\Rocket.png", "Rocket", 1000);
		this->Field["BuildUI"].Template("BuildingSample")->setSpriteSize(0.1, 0.1);
		this->Field["BuildUI"].Template("BuildingSample")->setImgDim(1200, 1600);
		this->Field["BuildUI"].Template("BuildingSample")->setType("Static");
		this->Field["BuildUI"].Template("BuildingSample")->tag = "BuildUI";

		this->Field["BuildUI"].registerObject("PumpSample", "BuildingSample", "PumpSample");
		this->Field["BuildUI"].object("PumpSample")->setSpriteTexture("Pump", 0);
		this->Field["BuildUI"].object("PumpSample")->setPosX(400);
		this->Field["BuildUI"].object("PumpSample")->setPosY(200);

		this->Field["BuildUI"].registerObject("SolarCellSample", "BuildingSample", "SolarSample");
		this->Field["BuildUI"].object("SolarCellSample")->setSpriteTexture("SolarCell", 0);
		this->Field["BuildUI"].object("SolarCellSample")->setPosX(400);
		this->Field["BuildUI"].object("SolarCellSample")->setPosY(400);

		this->Field["BuildUI"].registerObject("RocketSample", "BuildingSample", "RocketSample");
		this->Field["BuildUI"].object("RocketSample")->setSpriteTexture("Rocket", 0);
		this->Field["BuildUI"].object("RocketSample")->setPosX(1000);
		this->Field["BuildUI"].object("RocketSample")->setPosY(200);
		this->Field["BuildUI"].object("RocketSample")->setSpriteSize(0.05, 0.05);
		this->Field["BuildUI"].object("RocketSample")->setImgDim(2400, 3200);



		this->Field["BuildUI"].createTemplate("ItemUse");
		this->Field["BuildUI"].Template("ItemUse")->addTexture("assets\\Prop\\Item\\metalPlate.png", "CompositeMetal", 1000);
		this->Field["BuildUI"].Template("ItemUse")->addTexture("assets\\Prop\\Item\\Arclyic.png", "Arclyic", 1000);
		this->Field["BuildUI"].Template("ItemUse")->addTexture("assets\\Prop\\Item\\WiringKit.png", "WiringKit", 1000);
		this->Field["BuildUI"].Template("ItemUse")->addTexture("assets\\Prop\\Item\\GoldPlate.png", "GoldPlate", 1000);
		this->Field["BuildUI"].Template("ItemUse")->addTexture("assets\\Prop\\Item\\titaniumPlate.png", "TitaniumPlate", 1000);
		this->Field["BuildUI"].Template("ItemUse")->addTexture("assets\\Prop\\Item\\AluminiumPlate.png", "AluminiumPlate", 1000);
		this->Field["BuildUI"].Template("ItemUse")->setSpriteSize(0.1, 0.1);
		this->Field["BuildUI"].Template("ItemUse")->setImgDim(1000, 1000);
		this->Field["BuildUI"].Template("ItemUse")->setType("Static");
		this->Field["BuildUI"].Template("ItemUse")->tag = "BuildUI";

		this->Field["BuildUI"].registerObject("Pump_metal", "ItemUse", "Pump_metal");
		this->Field["BuildUI"].object("Pump_metal")->setSpriteTexture("CompositeMetal", 0);
		this->Field["BuildUI"].object("Pump_metal")->setPosX(550);
		this->Field["BuildUI"].object("Pump_metal")->setPosY(220);

		this->Field["BuildUI"].registerObject("Pump_Arclyic", "ItemUse", "Pump_Arclyic");
		this->Field["BuildUI"].object("Pump_Arclyic")->setSpriteTexture("Arclyic", 0);
		this->Field["BuildUI"].object("Pump_Arclyic")->setPosX(650);
		this->Field["BuildUI"].object("Pump_Arclyic")->setPosY(220);

		this->Field["BuildUI"].registerObject("Solar_metal", "ItemUse", "Solar_metal");
		this->Field["BuildUI"].object("Solar_metal")->setSpriteTexture("CompositeMetal", 0);
		this->Field["BuildUI"].object("Solar_metal")->setPosX(550);
		this->Field["BuildUI"].object("Solar_metal")->setPosY(420);

		this->Field["BuildUI"].registerObject("Solar_Arclyic", "ItemUse", "Solar_Arclyic");
		this->Field["BuildUI"].object("Solar_Arclyic")->setSpriteTexture("Arclyic", 0);
		this->Field["BuildUI"].object("Solar_Arclyic")->setPosX(650);
		this->Field["BuildUI"].object("Solar_Arclyic")->setPosY(420);

		this->Field["BuildUI"].registerObject("Solar_WiringKit", "ItemUse", "Solar_WiringKit");
		this->Field["BuildUI"].object("Solar_WiringKit")->setSpriteTexture("WiringKit", 0);
		this->Field["BuildUI"].object("Solar_WiringKit")->setPosX(750);
		this->Field["BuildUI"].object("Solar_WiringKit")->setPosY(420);

		this->Field["BuildUI"].registerObject("Rocket_TitanuiumPlate", "ItemUse", "Rocket_TitanuiumPlate");
		this->Field["BuildUI"].object("Rocket_TitanuiumPlate")->setSpriteTexture("TitaniumPlate", 0);
		this->Field["BuildUI"].object("Rocket_TitanuiumPlate")->setPosX(1150);
		this->Field["BuildUI"].object("Rocket_TitanuiumPlate")->setPosY(220);

		this->Field["BuildUI"].registerObject("Rocket_AluminiumPlate", "ItemUse", "Rocket_AluminiumPlate");
		this->Field["BuildUI"].object("Rocket_AluminiumPlate")->setSpriteTexture("AluminiumPlate", 0);
		this->Field["BuildUI"].object("Rocket_AluminiumPlate")->setPosX(1250);
		this->Field["BuildUI"].object("Rocket_AluminiumPlate")->setPosY(220);

		this->Field["BuildUI"].registerObject("Rocket_GoldPlate", "ItemUse", "Rocket_GoldPlate");
		this->Field["BuildUI"].object("Rocket_GoldPlate")->setSpriteTexture("GoldPlate", 0);
		this->Field["BuildUI"].object("Rocket_GoldPlate")->setPosX(1350);
		this->Field["BuildUI"].object("Rocket_GoldPlate")->setPosY(220);

		this->Field["BuildUI"].registerObject("Rocket_WiringKit", "ItemUse", "Rocket_WiringKit");
		this->Field["BuildUI"].object("Rocket_WiringKit")->setSpriteTexture("WiringKit", 0);
		this->Field["BuildUI"].object("Rocket_WiringKit")->setPosX(1450);
		this->Field["BuildUI"].object("Rocket_WiringKit")->setPosY(220);

		this->Field["Victory"].createTemplate("Blank");

		this->Field["Victory"].registerObject("VictoryBG", "Blank", "VictoryBG");
		this->Field["Victory"].object("VictoryBG")->addTexture("assets\\Prop\\UI\\Victory.png", "BG", 1000);
		this->Field["Victory"].object("VictoryBG")->setSpriteTexture("BG", 0);
		this->Field["Victory"].object("VictoryBG")->setImgDim(1920, 1080);
		this->Field["Victory"].object("VictoryBG")->setPosX(960 * 0.83);
		this->Field["Victory"].object("VictoryBG")->setPosY(540 * 0.83);
		this->Field["Victory"].object("VictoryBG")->setSpriteSize(0.83, 0.83);

		this->Field["GameOver"].createTemplate("GameOver");
		this->Field["GameOver"].Template("GameOver")->addTexture("assets\\Prop\\HUD\\Pause.png", "default", 1000);
		this->Field["GameOver"].Template("GameOver")->setSpriteSize(0.5, 0.5);
		this->Field["GameOver"].Template("GameOver")->setImgDim(3200, 1800);
		this->Field["GameOver"].Template("GameOver")->setPosX(800);
		this->Field["GameOver"].Template("GameOver")->setPosY(450);
		this->Field["GameOver"].Template("GameOver")->setType("Static");
		this->Field["GameOver"].Template("GameOver")->tag = "GameOverUI";

		this->Field["GameOver"].registerObject("BG", "GameOver", "BG");
		this->Field["GameOver"].object("BG")->setSpriteTexture("default", 0);



	}
	void initMainMenu() {
		this->Dialog["Font"].addFont("Mitr-Regular", "assets\\font\\Mitr-Regular.ttf");
		this->Dialog["Font"].addFont("Mitr-Bold", "assets\\font\\Mitr-Bold.ttf");

		this->Dialog["MainMenuButton"].registerObject("Play", "MainMenu");
		this->Dialog["MainMenuButton"].object("Play")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["MainMenuButton"].object("Play")->setString("Play");
		this->Dialog["MainMenuButton"].object("Play")->setFillColor(Color::White);
		this->Dialog["MainMenuButton"].object("Play")->setCharacterSize(100);
		this->Dialog["MainMenuButton"].object("Play")->setPosition({ 350,230 });

		this->Dialog["MainMenuButton"].registerObject("Exit", "MainMenu");
		this->Dialog["MainMenuButton"].object("Exit")->setFont(this->Dialog["Font"].font["Mitr-Regular"]);
		this->Dialog["MainMenuButton"].object("Exit")->setString("Exit");
		this->Dialog["MainMenuButton"].object("Exit")->setFillColor(Color::White);
		this->Dialog["MainMenuButton"].object("Exit")->setCharacterSize(100);
		this->Dialog["MainMenuButton"].object("Exit")->setPosition({ 350,600 });

		this->Field["MainMenu"].createTemplate("MainMenuBG");
		this->Field["MainMenu"].Template("MainMenuBG")->addTexture("assets\\Prop\\UI\\MainMenu.png", "MainMenuBG", 1000);
		this->Field["MainMenu"].Template("MainMenuBG")->setImgDim(1920, 1080);
		this->Field["MainMenu"].Template("MainMenuBG")->setPosX(960*0.83);
		this->Field["MainMenu"].Template("MainMenuBG")->setPosY(540*0.83);
		this->Field["MainMenu"].Template("MainMenuBG")->setSpriteSize(0.83, 0.83);

		this->Field["MainMenu"].createTemplate("MainMenuMask");
		this->Field["MainMenu"].Template("MainMenuMask")->addTexture("assets\\Prop\\UI\\mask.png", "Mask", 1000);
		this->Field["MainMenu"].Template("MainMenuMask")->setImgDim(576, 1080);
		this->Field["MainMenu"].Template("MainMenuMask")->setPosX(288 * 0.83);
		this->Field["MainMenu"].Template("MainMenuMask")->setPosY(540 * 0.83);
		this->Field["MainMenu"].Template("MainMenuMask")->setSpriteSize(1.3, 0.83);

		this->Field["MainMenu"].registerObject("_MainMenuBG", "MainMenuBG", "_MainMenuBG");
		this->Field["MainMenu"].object("_MainMenuBG")->setSpriteTexture("MainMenuBG", 0);

		this->Field["MainMenu"].registerObject("_MainMenuMask", "MainMenuMask", "_MainMenuMask");
		this->Field["MainMenu"].object("_MainMenuMask")->setSpriteTexture("Mask", 0);

		for (int i = 0; i < this->Field["MainMenu"].entityNumber(); i++) {
			this->DrawField["MainMenu"].push_back(this->Field["MainMenu"].objectAt(i));
		}
	}
	void manageLayer() {
		for (int i = 0; i < this->Field["GameBG"].entityNumber(); i++) {
			this->DrawField["BG_repo"].push_back(this->Field["GameBG"].objectAt(i));
		}
		for (int i = 0; i < this->Field["PauseUI"].entityNumber(); i++) {
			this->DrawField["DrawField_pauseUI"].push_back(this->Field["PauseUI"].objectAt(i));
		}
		for (int i = 0; i < this->Field["BuildUI"].entityNumber(); i++) {
			this->DrawField["DrawField_buildingUI"].push_back(this->Field["BuildUI"].objectAt(i));
		}
		for (int i = 0; i < this->Field["Victory"].entityNumber(); i++) {
			this->DrawField["Victory"].push_back(this->Field["Victory"].objectAt(i));
		}
		for (int i = 0; i < this->Field["GameOver"].entityNumber(); i++) {
			this->DrawField["GameOver"].push_back(this->Field["GameOver"].objectAt(i));
		}
		for (int i = 0; i < this->Field["InventoryUI"].entityNumber(); i++) {
			this->DrawField["DrawField_inventoryUI"].push_back(this->Field["InventoryUI"].objectAt(i));
		}
		for (int i = 0; i < this->Field["HUD"].entityNumber(); i++) {
			this->DrawField["DrawField_HUD"].push_back(this->Field["HUD"].objectAt(i));
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
	unordered_map<string, Map> Field;
	unordered_map<string, vector<Object*>> DrawField;
	vector<int> ItemUseSlotQuantity, HotbarQuantity;
	vector<vector<Object*>> Backpack, Crafting;
	vector<vector<int>> BackpackQuantity, CraftingQuantity;
	unordered_map<string, strMap> Dialog;
	vector<int> mousePos = { 0,0 };
	Object* Anchor;
	Object* Elon;
	Object* MiniElon;
	Object* NoneItem = new Object(45678);
	Object itemOutput = *NoneItem;
	Object* Rocket;
	unordered_map<string, Sound> SoundFX;
	unordered_map<string, Music> MusicFX;
	unordered_map<string, SoundBuffer> SoundRepo;
	int itemOutoutQuantity = 0;
	int InventoryHitbox[4][9][4], CraftingHitbox[3][3][4], CraftingOutputHitbox[4] = { 1260,460,1330,530 };
	int maxItemStack = 8;
	int Rockettime = 0;
	bool _time = true;
	bool pass = true;
	bool movable = true;
	float move_speed = 3;
	bool W = false, A = false, S = false, D = false, E = false, shift = false;
	bool W_moveable = true, A_moveable = true, S_moveable = true, D_moveable = true;
	bool pause = false;
	bool escPressed = false, escToggle = false, EToggle = false;
	bool paused = false, building = false, inventory = false, Victory = false, GameOver = false;
	int selectingSlot = 0, ItemOnMouseQuantity = 0;
	bool OnMainMenu = true;
	bool DynamicAck = false, FloorAck = false;
	bool walk = true, idle = true, canMove = true, onRocket = false;
	gameEngine() {
		unsigned int time_ui = unsigned int(time(NULL));
		srand(time_ui);
		this->initSound();
		this->initVar();
		this->initWindow();
		this->intitDialog();
		this->intiRecipe();
		this->initMainMenu();
	}
	void construct() {
		this->pause = true;
		Sleep(500);
		unsigned int time_ui = unsigned int(time(NULL));
		srand(time_ui);
		printf("Initialing Object...\t");
		this->DrawField["ItemOnMouse"].push_back(new Object(1216543));
		this->DrawField["CraftingOutput"].push_back(new Object(1216543));
		this->initObject();
		this->initItem();
		printf("Done\n");
		printf("Initialing UI...\t");
		this->intitUI();
		printf("Done\n");
		printf("Initialing HUD...\t");
		this->intitHUD();
		printf("Done\n");
		printf("Initialing Layer...\t");
		this->manageLayer();
		printf("Done\n");
		this->pause = false;
		this->MusicFX["Wind"].play();
	}
	void constructMainMenu() {
		this->initMainMenu();
	}
	void destroy() {
		this->MusicFX["Wind"].stop();
		this->pause = true;
		while (!FloorAck && !DynamicAck) {
			Sleep(1);
		}

		Field["Dynamic"].destroy();
		Field["GameBG"].destroy();
		Field["HUD"].destroy();
		Field["MiniElon"].destroy();
		Field["PauseUI"].destroy();
		Field["BuildUI"].destroy();
		Field["InventoryUI"].destroy();
		itemList.destroy();
		freeContainer(DrawField["Hotbar"]);
		freeContainer(DrawField["ItemOnMouse"]);
		freeContainer(DrawField["InventoryUseSlot"]);
		freeContainer(DrawField["Hotbar_HUD"]);
		freeContainer(DrawField["BG_repo"]);
		freeContainer(DrawField["DrawField_BG"]);
		freeContainer(DrawField["DrawField_Dynamic"]);
		freeContainer(DrawField["CraftingOutput"]);
		Backpack.clear();
		Crafting.clear();
		ItemUseSlotQuantity.clear();
		HotbarQuantity.clear();
		BackpackQuantity.clear();
		CraftingQuantity.clear();
		for (auto field : DrawField) {
			field.second.clear();
		}
		itemOutoutQuantity = 0;
		maxItemStack = 8;
		Rockettime = 0;
		_time = true;
		pass = true;
		movable = true;
		move_speed = 3;
		W = false, A = false, S = false, D = false, E = false, shift = false;
		W_moveable = true, A_moveable = true, S_moveable = true, D_moveable = true;
		pause = false;
		escPressed = false, escToggle = false, EToggle = false;
		paused = false, building = false, inventory = false;
		selectingSlot = 0, ItemOnMouseQuantity = 0;
		OnMainMenu = true;
		DynamicAck = false, FloorAck = false;
		walk = true, idle = true, canMove = true, onRocket = false;
		this->initMainMenu();
		this->pause = false;
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
	void giveItem(string itemName) {
		bool found = false;
		bool placed = false;
		for (int i = 0; i < 9; i++) {
			if (this->DrawField["Hotbar"][i]->nowIs() == itemName && this->HotbarQuantity[i] < this->maxItemStack) {
				this->HotbarQuantity[i]++;
				found = true;
				break;
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 9; j++) {
				if (this->Backpack[i][j]->nowIs() == itemName && this->BackpackQuantity[i][j] < this->maxItemStack) {
					this->BackpackQuantity[i][j]++;
					found = true;
					break;
				}
			}
		}
		if (!found) {
			for (int i = 0; i < 9; i++) {
				if (this->DrawField["Hotbar"][i]->nowIs() == "None") {
					*DrawField["Hotbar"][i] = *itemList.object(itemName);
					(*DrawField["Hotbar"][i]).setPosX(503 + 1100 * 0.06 / 2 + (1100 * 0.06 * i));
					this->DrawField["Hotbar"][i]->Is(itemName);
					this->HotbarQuantity[i] = 1;
					this->DrawField["Hotbar"][i]->setSpriteSize(0.06, 0.06);
					placed = true;
					break;
				}
			}
			if (!placed) {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 9; j++) {
						if (this->Backpack[i][j]->nowIs() == "None") {
							float Pos[] = { Backpack[i][j]->PosX(), Backpack[i][j]->PosY() };
							*Backpack[i][j] = *itemList.object(itemName);
							Backpack[i][j]->Is(itemName);
							Backpack[i][j]->setPosX(Pos[0]);
							Backpack[i][j]->setPosY(Pos[1]);
							BackpackQuantity[i][j] = 1;
							Backpack[i][j]->setSpriteSize(0.06, 0.06);
							placed = true;
							break;
						}
					}
					if (placed) {
						break;
					}
				}
			}
		}
	}
	bool boolRandTen() {
		return rand() % 10 == 0;
	}
	bool boolRandOne() {
		return rand() % 100 == 0;
	}
	bool boolRand(int chance) {
		for (int i = 0; i < (int)chance % 10; i++) {
			if (boolRandOne()) {
				return true;
			}
		}
		chance /= 10;
		for (int i = 0; i < (int)chance; i++) {
			if (boolRandTen()) {
				return true;
			}
		}
		return false;
	}
	void pollEvents() {
		while (this->window->pollEvent(this->ev)) {
			if (!this->OnMainMenu) {
				if (this->canMove) {
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
				}
				if (ev.type == Event::MouseMoved) {
					this->mousePos[0] = ev.mouseMove.x;
					this->mousePos[1] = ev.mouseMove.y;
					this->DrawField["ItemOnMouse"][0]->setPosX(this->mousePos[0]);
					this->DrawField["ItemOnMouse"][0]->setPosY(this->mousePos[1]);
				}
				if (ev.type == Event::MouseButtonPressed) {
					if (ev.mouseButton.button == Mouse::Middle) {
						this->DrawField["ItemOnMouse"][0]->Is("None");
						this->DrawField["ItemOnMouse"][0]->tag = "None";
						this->DrawField["ItemOnMouse"][0]->setSpriteSize(0, 0);
						this->ItemOnMouseQuantity = 0;
					}
					else if (ev.mouseButton.button == Mouse::Right) {
						cout << this->DrawField["Hotbar"][this->selectingSlot]->tag << endl;
						if (this->Elon->getStat("Alive") == 1) {
							if (this->inventory) {
								for (int i = 0; i < 4; i++) {
									for (int j = 0; j < 9; j++) {
										if (clickHit(this->InventoryHitbox[i][j]) && i < 3 && this->DrawField["ItemOnMouse"][0]->nowIs() == "None") {
											this->SoundFX["Pick"].play();
											this->DrawField["ItemOnMouse"][0]->useStatNoPos(*this->Backpack[i][j]);
											this->ItemOnMouseQuantity = ceil(this->BackpackQuantity[i][j] / 2.0);
											this->BackpackQuantity[i][j] = floor(this->BackpackQuantity[i][j] / 2.0);
											cout << this->DrawField["ItemOnMouse"][0]->nowIs() << endl;
										}
										else if (clickHit(this->InventoryHitbox[3][j]) && i == 3 && this->DrawField["ItemOnMouse"][0]->nowIs() == "None") {
											this->SoundFX["Pick"].play();
											cout << DrawField["Hotbar"][j]->tag << ">>" << this->DrawField["ItemOnMouse"][0]->tag << endl;
											*DrawField["ItemOnMouse"][0] = *DrawField["Hotbar"][j];
											this->ItemOnMouseQuantity = ceil(this->HotbarQuantity[j] / 2.0);
											this->HotbarQuantity[j] = floor(this->HotbarQuantity[j] / 2.0);
										}
										else if (clickHit(this->InventoryHitbox[i][j]) && i < 3 && this->DrawField["ItemOnMouse"][0]->nowIs() != "None" && (this->Backpack[i][j]->nowIs() == "None" || this->Backpack[i][j]->nowIs() == this->DrawField["ItemOnMouse"][0]->nowIs()) && this->BackpackQuantity[i][j] < this->maxItemStack) {
											printf("6++6+6+6+6+6++6+6+6\n");
											this->SoundFX["Pick"].play();
											if (this->BackpackQuantity[i][j] < this->maxItemStack) {

												printf("%d,%d\n", 3, j);
												cout << this->DrawField["ItemOnMouse"][0]->nowIs() << endl;
												this->Backpack[i][j]->useStatNoPos(*this->DrawField["ItemOnMouse"][0]);
												printf("++");
												this->Backpack[i][j]->setPosX(200 + 1000 * 0.06 * i);
												this->Backpack[i][j]->setPosY(503 + 1000 * 0.06 * j);
												this->Backpack[i][j]->setSpriteSize(0.06, 0.06);
												this->BackpackQuantity[i][j] += 1;
												this->ItemOnMouseQuantity--;
												printf("---");
												cout << this->Backpack[i][j]->nowIs() << endl;
												if (this->ItemOnMouseQuantity == 0) {
													this->DrawField["ItemOnMouse"][0]->Is("None");
													this->DrawField["ItemOnMouse"][0]->tag = "None";
													this->DrawField["ItemOnMouse"][0]->setSpriteSize(0, 0);
												}
											}
										}
										else if (clickHit(this->InventoryHitbox[3][j]) && i == 3 && this->DrawField["ItemOnMouse"][0]->nowIs() != "None" && (this->DrawField["Hotbar"][j]->nowIs() == "None" || this->DrawField["Hotbar"][j]->nowIs() == this->DrawField["ItemOnMouse"][0]->nowIs()) && this->HotbarQuantity[j] < this->maxItemStack) {
											this->SoundFX["Pick"].play();
											if (this->HotbarQuantity[j] < this->maxItemStack) {
												cout << DrawField["Hotbar"][j]->tag << "<<" << this->DrawField["ItemOnMouse"][0]->tag << endl;
												Object A = *this->DrawField["ItemOnMouse"][0];
												*DrawField["Hotbar"][j] = A;
												(*DrawField["Hotbar"][j]).setPosX(503 + 1100 * 0.06 / 2 + (1100 * 0.06 * j));
												(*DrawField["Hotbar"][j]).setTag(A.tag);
												this->DrawField["Hotbar"][j]->Is(charOnly(A.nowIs()));
												this->HotbarQuantity[j] += 1;
												this->DrawField["Hotbar"][j]->setSpriteSize(0.06, 0.06);
												this->ItemOnMouseQuantity--;
												if (this->ItemOnMouseQuantity == 0) {
													this->DrawField["ItemOnMouse"][0]->Is("None");
													this->DrawField["ItemOnMouse"][0]->tag = "None";
													this->DrawField["ItemOnMouse"][0]->setSpriteSize(0, 0);
												}
											}
										}
									}
								}
								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < 3; j++) {
										if (clickHit(this->CraftingHitbox[j][i])) {
											if (this->DrawField["ItemOnMouse"][0]->nowIs() != "None" && this->Crafting[i][j]->nowIs() == "None") {
												this->SoundFX["Pick"].play();
												printf("Click Hit Crafting %d,%d\n", i, j);
												float pos[] = { Crafting[i][j]->PosX(), Crafting[i][j]->PosY() };
												*Crafting[i][j] = *this->DrawField["ItemOnMouse"][0];
												this->Crafting[i][j]->setPosX(pos[0]);
												this->Crafting[i][j]->setPosY(pos[1]);
												this->Crafting[i][j]->setSpriteSize(0.06, 0.06);
												this->CraftingQuantity[i][j] = 1;
												this->ItemOnMouseQuantity--;
												if (this->ItemOnMouseQuantity == 0) {
													this->DrawField["ItemOnMouse"][0]->Is("None");
													this->DrawField["ItemOnMouse"][0]->tag = "None";
													this->DrawField["ItemOnMouse"][0]->setSpriteSize(0, 0);
												}
											}
											else if (this->DrawField["ItemOnMouse"][0]->nowIs() == "None" && this->Crafting[i][j]->nowIs() != "None") {
												this->SoundFX["Pick"].play();
												*this->DrawField["ItemOnMouse"][0] = *Crafting[i][j];
												this->DrawField["ItemOnMouse"][0]->setSpriteSize(0.06, 0.06);
												this->ItemOnMouseQuantity = ceil(this->CraftingQuantity[i][j] / 2.0);
												this->CraftingQuantity[i][j] = floor(this->CraftingQuantity[i][j] / 2.0);
												if (this->CraftingQuantity[i][j] == 0) {
													this->Crafting[i][j]->Is("None");
													this->Crafting[i][j]->tag = "None";
													this->Crafting[i][j]->setSpriteSize(0, 0);
												}
											}
											else if (this->DrawField["ItemOnMouse"][0]->nowIs() == this->Crafting[i][j]->nowIs() && this->CraftingQuantity[i][j] < this->maxItemStack) {
												this->SoundFX["Pick"].play();
												if (this->ItemOnMouseQuantity < this->maxItemStack) {
													this->CraftingQuantity[i][j] += 1;
													this->ItemOnMouseQuantity--;
												}
												if (this->ItemOnMouseQuantity == 0) {
													this->DrawField["ItemOnMouse"][0]->Is("None");
													this->DrawField["ItemOnMouse"][0]->tag = "None";
													this->DrawField["ItemOnMouse"][0]->setSpriteSize(0, 0);
												}
											}
											bool foundAnyRecipe = false;
											for (int i = 0; i < this->Recipe.recipeNumber(); i++) {
												if (this->Recipe.matIsReady(i, this->Crafting, this->CraftingQuantity)) {
													*this->DrawField["CraftingOutput"][0] = *itemList.object(this->Recipe.RecipeAt(i));
													this->DrawField["CraftingOutput"][0]->setPosX(this->Field["InventoryUI"].object("craftingOutput")->PosX() + 1100 * 0.06 / 2);
													this->DrawField["CraftingOutput"][0]->setPosY(this->Field["InventoryUI"].object("craftingOutput")->PosY() + 1100 * 0.06 / 2);
													this->DrawField["CraftingOutput"][0]->setSpriteSize(0.06, 0.06);
													foundAnyRecipe = true;
													break;
												}
											}
											if (!foundAnyRecipe) {
												this->DrawField["CraftingOutput"][0]->setSpriteSize(0, 0);
											}
										}
									}
								}
								if (clickHit(CraftingOutputHitbox) && this->DrawField["CraftingOutput"][0]->nowIs() != "None" && (this->DrawField["ItemOnMouse"][0]->nowIs() == "None" || this->DrawField["CraftingOutput"][0]->nowIs() == this->DrawField["ItemOnMouse"][0]->nowIs()) && this->ItemOnMouseQuantity + this->Recipe.outputNum(this->DrawField["CraftingOutput"][0]->nowIs()) <= this->maxItemStack) {
									this->SoundFX["Pick"].play();
									cout << "Craftable : " << this->DrawField["CraftingOutput"][0]->nowIs() << '\t' << "X" << this->Recipe.outputNum(this->DrawField["CraftingOutput"][0]->nowIs()) << endl;
									*this->DrawField["ItemOnMouse"][0] = *this->DrawField["CraftingOutput"][0];
									this->ItemOnMouseQuantity += this->Recipe.outputNum(this->DrawField["CraftingOutput"][0]->nowIs());
									bool foundAnyRecipe = false;
									for (int i = 0; i < this->Recipe.MatUseNumber(this->DrawField["CraftingOutput"][0]->nowIs()); i++) {
										for (int j = 0; j < 3; j++) {
											for (int k = 0; k < 3; k++) {
												if (this->DrawField["CraftingOutput"][0]->nowIs() == "None" || this->Crafting[j][k]->nowIs() == "None") {
													continue;
												}
												if (this->Crafting[j][k]->nowIs() == this->Recipe.matAt(this->DrawField["CraftingOutput"][0]->nowIs(), i) && this->Crafting[j][k]->tag != "Tool") {
													this->CraftingQuantity[j][k] -= this->Recipe.itemUseQuantity(this->DrawField["CraftingOutput"][0]->nowIs(), i);
												}
											}
										}
									}
									for (int i = 0; i < this->Recipe.recipeNumber(); i++) {
										if (this->Recipe.matIsReady(i, this->Crafting, this->CraftingQuantity)) {
											*this->DrawField["CraftingOutput"][0] = *itemList.object(this->Recipe.RecipeAt(i));
											this->DrawField["CraftingOutput"][0]->setPosX(this->Field["InventoryUI"].object("craftingOutput")->PosX() + 1100 * 0.06 / 2);
											this->DrawField["CraftingOutput"][0]->setPosY(this->Field["InventoryUI"].object("craftingOutput")->PosY() + 1100 * 0.06 / 2);
											this->DrawField["CraftingOutput"][0]->setSpriteSize(0.06, 0.06);
											foundAnyRecipe = true;
											break;
										}
									}
									if (!foundAnyRecipe) {
										this->DrawField["CraftingOutput"][0]->setSpriteSize(0, 0);
										*this->DrawField["CraftingOutput"][0] = *NoneItem;
									}
								}
							}
							else {
								if (this->DrawField["Hotbar"][this->selectingSlot]->tag == "Medicine" && this->HotbarQuantity[this->selectingSlot] > 0 && Elon->getStat("Health") < 100) {
									Elon->setStat("Health", Elon->getStat("Health") + this->DrawField["Hotbar"][this->selectingSlot]->getStat("healAmount"));
									if (Elon->getStat("Health") > 100) {
										Elon->setStat("Health", 100);
									}
								}
								else if (this->DrawField["Hotbar"][this->selectingSlot]->tag == "Food" && this->HotbarQuantity[this->selectingSlot] > 0 && Elon->getStat("Hunger") < 100) {
									this->SoundFX["Eat"].play();
									Elon->setStat("Hunger", Elon->getStat("Hunger") + this->DrawField["Hotbar"][this->selectingSlot]->getStat("healAmount"));
									if (Elon->getStat("Hunger") > 100) {
										Elon->setStat("Hunger", 100);
									}
								}
								else if (this->DrawField["Hotbar"][this->selectingSlot]->tag == "Tool" && this->HotbarQuantity[this->selectingSlot] > 0 && this->DrawField["Hotbar"][this->selectingSlot]->getStat("durability") > 0) {
									if (this->DrawField["Hotbar"][this->selectingSlot]->nowIs() == "Hammer") {
										this->SoundFX["Open"].play();
										this->building = true;
									}
									else if (this->DrawField["Hotbar"][this->selectingSlot]->nowIs() == "Hydro Flask") {
										this->SoundFX["Drinking"].play();
										Elon->setStat("Thirst", Elon->getStat("Thirst") + this->DrawField["Hotbar"][this->selectingSlot]->getStat("healAmount"));
										if (Elon->getStat("Thirst") > 100) {
											Elon->setStat("Thirst", 100);
										}
									}
									else if (this->DrawField["Hotbar"][this->selectingSlot]->nowIs() == "Shovel") {
										this->SoundFX["Digging"].play();
										int num = rand() % 100;
										if (Elon->getStat("Hunger") - 5 > 0) {
											Elon->increase("Hunger", -5);
										}
										else {
											Elon->setStat("Hunger", 0);
											Elon->increase("Health", -5);
										}
										if (Elon->getStat("Thirst") - 7 > 0) {
											Elon->increase("Thirst", -7);
										}
										else {
											Elon->setStat("Thirst", 0);
											Elon->increase("Health", -7);
										}
										if (boolRand(20)) {
											int quant = rand() % 3 + 1;
											for (int i = 0; i < 1; i++) {
												giveItem("Gold Nugget");
											}
										}
										if (boolRand(50)) {
											int quant = rand() % 5 + 1;
											for (int i = 0; i < 1; i++) {
												giveItem("Titanium Nugget");
											}
										}
										if (boolRand(100)) {
											int quant = rand() % 7 + 1;
											for (int i = 0; i < 1; i++) {
												giveItem("Aluminium Nugget");
											}
										}
										if (boolRand(200)) {
											int quant = rand() % 10 + 1;
											for (int i = 0; i < 1; i++) {
												giveItem("Copper Nugget");
											}
										}
									}
								}
								else {
									continue;
								}
								if (this->DrawField["Hotbar"][this->selectingSlot]->tag != "Tool") {
									if (this->HotbarQuantity[this->selectingSlot] > 0) {
										this->HotbarQuantity[this->selectingSlot]--;
									}
									if (this->HotbarQuantity[this->selectingSlot] <= 0) {
										this->DrawField["Hotbar"][this->selectingSlot]->Is("None");
										this->DrawField["Hotbar"][this->selectingSlot]->tag = "None";
										this->DrawField["Hotbar"][this->selectingSlot]->setSpriteSize(0, 0);
									}
								}
								else {
									this->DrawField["Hotbar"][this->selectingSlot]->increase("durability", -1);
									if (this->DrawField["Hotbar"][this->selectingSlot]->nowIs() == "Hydro Flask" && this->DrawField["Hotbar"][this->selectingSlot]->getStat("durability") <= 0) {
										this->DrawField["Hotbar"][this->selectingSlot]->setSpriteTexture("Empty", 0);
									}
								}
							}
						}
					}
					if (ev.mouseButton.button == Mouse::Left) {
						printf("%d %d ||\n", this->mousePos[0], this->mousePos[1]);
						if (this->GameOver) {
							int RetryHitBox[] = { 300,760,500,850 }, ExitHitBox[] = { 1180,760,1360,850 };
							if (clickHit(RetryHitBox)) {
								this->SoundFX["Click"].play();
								printf("Hit");
								this->Victory = false;
								this->destroy();
								this->construct();
								this->OnMainMenu = false;
							}
							if (clickHit(ExitHitBox)) {
								this->SoundFX["Click"].play();
								printf("Hit");
								this->destroy();
								this->Victory = false;
								this->constructMainMenu();
							}
						}
						else if (this->Elon->getStat("Alive") == 1) {
							if (this->Victory) {
								int RetryHitBox[] = { 300,760,500,850 }, ExitHitBox[] = { 1180,760,1360,850 };
								if (clickHit(RetryHitBox)) {
									this->SoundFX["Click"].play();
									printf("Hit");
									this->Victory = false;
									this->destroy();
									this->construct();
									this->OnMainMenu = false;
								}
								if (clickHit(ExitHitBox)) {
									this->SoundFX["Click"].play();
									printf("Hit");
									this->destroy();
									this->Victory = false;
									this->constructMainMenu();
								}
							}
							else if (this->paused) {
								int BacktoGameHitBox[] = { 250, 200, 600, 250 };
								int ExitHitBox[] = { 250, 600, 600, 650 };
								if (clickHit(BacktoGameHitBox)) {
									this->SoundFX["Click"].play();
									printf("Hit");
									this->paused = false;
								}
								if (clickHit(ExitHitBox)) {
									this->SoundFX["Click"].play();
									printf("Hit");
									this->destroy();
									this->OnMainMenu = true;
									this->paused = false;
									this->constructMainMenu();
									break;
								}
							}
							else if (this->building) {
								int PumpHitBox[] = { 330, 100, 470, 280 };
								int SlolarHitBox[] = { 330, 340, 460, 480 };
								int RocketHitBox[] = { 940, 100, 1060,300 };
								if (clickHit(PumpHitBox) && hasEnoughItem("Composite Metal", 10, false) && hasEnoughItem("Arclyic", 5, false)) {
									this->SoundFX["Building"].play();
									hasEnoughItem("Composite Metal", 10, true);
									hasEnoughItem("Arclyic", 5, true);
									string ObjName = "Pump_" + to_string(rand() % 100000);
									this->pause = true;
									while (!FloorAck && !DynamicAck) {
										Sleep(1);
									}
									this->Field["Dynamic"].registerObject(ObjName, "Pump", "Pump");
									this->Field["Dynamic"].object(ObjName)->setOffsetPosX(this->Field["Dynamic"].object("Elon")->PosX() - this->Field["Dynamic"].object("Anchor")->PosX());
									this->Field["Dynamic"].object(ObjName)->setOffsetPosY(this->Field["Dynamic"].object("Elon")->PosY() - this->Field["Dynamic"].object("Anchor")->PosY());
									this->DrawField["DrawField_Dynamic"].push_back(this->Field["Dynamic"].object(ObjName));
									this->pause = false;
									this->building = false;
								}
								if (clickHit(SlolarHitBox) && hasEnoughItem("Composite Metal", 10, false) && hasEnoughItem("Arclyic", 2, false) && hasEnoughItem("Wiring Kit", 1, false)) {
									this->SoundFX["Building"].play();
									hasEnoughItem("Composite Metal", 10, true);
									hasEnoughItem("Arclyic", 2, true);
									hasEnoughItem("Wiring Kit", 1, true);
									string ObjName = "Solar_" + to_string(rand() % 100000);
									this->pause = true;
									while (!FloorAck && !DynamicAck) {
										Sleep(1);
									}
									this->Field["Dynamic"].registerObject(ObjName, "SolarCell", "Solar");
									this->Field["Dynamic"].object(ObjName)->setOffsetPosX(this->Field["Dynamic"].object("Elon")->PosX() - this->Field["Dynamic"].object("Anchor")->PosX());
									this->Field["Dynamic"].object(ObjName)->setOffsetPosY(this->Field["Dynamic"].object("Elon")->PosY() - this->Field["Dynamic"].object("Anchor")->PosY());
									this->DrawField["DrawField_Dynamic"].push_back(this->Field["Dynamic"].object(ObjName));
									this->pause = false;
									this->building = false;
								}
								if (clickHit(RocketHitBox) && hasEnoughItem("Composite Metal", 15, false)
									&& hasEnoughItem("Titanium Plate", 30, false)
									&& hasEnoughItem("Aluminium Plate", 20, false)
									&& hasEnoughItem("Gold Plate", 10, false)
									&& hasEnoughItem("Wiring Kit", 5, false)) {
									this->SoundFX["Building"].play();
									hasEnoughItem("Composite Metal", 15, true);
									hasEnoughItem("Titanium Plate", 30, true);
									hasEnoughItem("Aluminium Plate", 20, true);
									hasEnoughItem("Gold Plate", 10, true);
									hasEnoughItem("Wiring Kit", 5, true);
									string ObjName = "Rocket_" + to_string(rand() % 100000);
									this->pause = true;
									while (!FloorAck && !DynamicAck) {
										Sleep(1);
									}
									this->Field["Dynamic"].registerObject(ObjName, "Rocket", "Rocket");
									this->Field["Dynamic"].object(ObjName)->setOffsetPosX(this->Field["Dynamic"].object("Elon")->PosX() - this->Field["Dynamic"].object("Anchor")->PosX());
									this->Field["Dynamic"].object(ObjName)->setOffsetPosY(this->Field["Dynamic"].object("Elon")->PosY() - this->Field["Dynamic"].object("Anchor")->PosY());
									this->DrawField["DrawField_Dynamic"].push_back(this->Field["Dynamic"].object(ObjName));
									this->pause = false;
									this->building = false;
								}
							}
							else if (this->inventory) {
								for (int i = 0; i < 4; i++) {
									for (int j = 0; j < 9; j++) {
										if (clickHit(this->InventoryHitbox[i][j]) && i < 3 && this->DrawField["ItemOnMouse"][0]->nowIs() == "None" && this->Backpack[i][j]->nowIs() != "None") {
											this->SoundFX["Pick"].play();
											this->DrawField["ItemOnMouse"][0]->useStatNoPos(*this->Backpack[i][j]);
											this->ItemOnMouseQuantity = this->BackpackQuantity[i][j];
											this->BackpackQuantity[i][j] = 0;
											this->Backpack[i][j]->useStatNoPos(*NoneItem);
											this->Backpack[i][j]->Is("None");
											this->Backpack[i][j]->tag = "None";
											this->Backpack[i][j]->setSpriteSize(0, 0);
											cout << this->DrawField["ItemOnMouse"][0]->nowIs() << endl;
										}
										else if (clickHit(this->InventoryHitbox[3][j]) && i == 3 && this->DrawField["ItemOnMouse"][0]->nowIs() == "None") {
											this->SoundFX["Pick"].play();
											cout << DrawField["Hotbar"][j]->tag << ">>" << this->DrawField["ItemOnMouse"][0]->tag << endl;
											*DrawField["ItemOnMouse"][0] = *DrawField["Hotbar"][j];
											this->ItemOnMouseQuantity = this->HotbarQuantity[j];
											this->HotbarQuantity[j] = 0;
											this->DrawField["Hotbar"][j]->Is("None");
											this->DrawField["Hotbar"][j]->tag = "None";
											this->DrawField["Hotbar"][j]->setSpriteSize(0, 0);
										}
										else if (clickHit(this->InventoryHitbox[i][j]) && i < 3 && this->DrawField["ItemOnMouse"][0]->nowIs() != "None" && (this->Backpack[i][j]->nowIs() == "None" || this->Backpack[i][j]->nowIs() == this->DrawField["ItemOnMouse"][0]->nowIs()) && this->BackpackQuantity[i][j] < this->maxItemStack) {
											this->SoundFX["Pick"].play();
											printf("6++6+6+6+6+6++6+6+6\n");
											if (this->ItemOnMouseQuantity + this->BackpackQuantity[i][j] <= this->maxItemStack) {
												printf("%d,%d\n", 3, j);
												cout << this->DrawField["ItemOnMouse"][0]->nowIs() << endl;
												this->Backpack[i][j]->useStatNoPos(*this->DrawField["ItemOnMouse"][0]);
												printf("++");
												this->Backpack[i][j]->setPosX(200 + 1000 * 0.06 * i);
												this->Backpack[i][j]->setPosY(503 + 1000 * 0.06 * j);
												this->Backpack[i][j]->setSpriteSize(0.06, 0.06);
												this->BackpackQuantity[i][j] += this->ItemOnMouseQuantity;
												this->DrawField["ItemOnMouse"][0]->Is("None");
												this->DrawField["ItemOnMouse"][0]->tag = "None";
												this->DrawField["ItemOnMouse"][0]->setSpriteSize(0, 0);
												this->ItemOnMouseQuantity = 0;
												printf("---");
												cout << this->Backpack[i][j]->nowIs() << endl;
											}
											else {
												this->ItemOnMouseQuantity -= this->maxItemStack - this->BackpackQuantity[i][j];
												this->BackpackQuantity[i][j] = this->maxItemStack;
											}
										}
										else if (clickHit(this->InventoryHitbox[3][j]) && i == 3 && this->DrawField["ItemOnMouse"][0]->nowIs() != "None" && (this->DrawField["Hotbar"][j]->nowIs() == "None" || this->DrawField["Hotbar"][j]->nowIs() == this->DrawField["ItemOnMouse"][0]->nowIs()) && this->HotbarQuantity[j] < this->maxItemStack) {
											this->SoundFX["Pick"].play();
											if (this->ItemOnMouseQuantity + this->HotbarQuantity[j] <= this->maxItemStack) {
												cout << DrawField["Hotbar"][j]->tag << "<<" << this->DrawField["ItemOnMouse"][0]->tag << endl;
												Object A = *this->DrawField["ItemOnMouse"][0];
												*DrawField["Hotbar"][j] = A;
												this->DrawField["ItemOnMouse"][0]->Is("None");
												this->DrawField["ItemOnMouse"][0]->tag = "None";
												this->DrawField["ItemOnMouse"][0]->setSpriteSize(0, 0);
												(*DrawField["Hotbar"][j]).setPosX(503 + 1100 * 0.06 / 2 + (1100 * 0.06 * j));
												(*DrawField["Hotbar"][j]).setTag(A.tag);
												this->DrawField["Hotbar"][j]->Is(charOnly(A.nowIs()));
												this->HotbarQuantity[j] += this->ItemOnMouseQuantity;
												this->DrawField["Hotbar"][j]->setSpriteSize(0.06, 0.06);
											}
											else {
												this->ItemOnMouseQuantity -= this->maxItemStack - this->HotbarQuantity[j];
												this->HotbarQuantity[j] = this->maxItemStack;
											}
										}
										else if (i < 3 && clickHit(this->InventoryHitbox[i][j]) && this->Backpack[i][j]->nowIs() != "None" && this->DrawField["ItemOnMouse"][0]->nowIs() != "None") {
											Object Buffer = *this->Backpack[i][j];
											int BufferQ = this->BackpackQuantity[i][j];
											this->SoundFX["Pick"].play();
											*this->Backpack[i][j] = *this->DrawField["ItemOnMouse"][0];
											*this->DrawField["ItemOnMouse"][0] = Buffer;
											this->BackpackQuantity[i][j] = this->ItemOnMouseQuantity;
											this->ItemOnMouseQuantity = BufferQ;
										}
										else if (i == 3 && clickHit(this->InventoryHitbox[3][j]) && DrawField["Hotbar"][j]->nowIs() != "None" && this->DrawField["ItemOnMouse"][0]->nowIs() != "None") {
											Object Buffer = *DrawField["Hotbar"][j];
											int BufferQ = this->HotbarQuantity[j];
											this->SoundFX["Pick"].play();
											*DrawField["Hotbar"][j] = *this->DrawField["ItemOnMouse"][0];
											*this->DrawField["ItemOnMouse"][0] = Buffer;
											this->HotbarQuantity[j] = this->ItemOnMouseQuantity;
											this->ItemOnMouseQuantity = BufferQ;
										}
									}
								}
								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < 3; j++) {
										if (clickHit(this->CraftingHitbox[j][i])) {
											if (this->DrawField["ItemOnMouse"][0]->nowIs() != "None" && this->Crafting[i][j]->nowIs() == "None") {
												this->SoundFX["Pick"].play();
												printf("Click Hit Crafting %d,%d\n", i, j);
												float pos[] = { Crafting[i][j]->PosX(), Crafting[i][j]->PosY() };
												*Crafting[i][j] = *this->DrawField["ItemOnMouse"][0];
												this->Crafting[i][j]->setPosX(pos[0]);
												this->Crafting[i][j]->setPosY(pos[1]);
												this->Crafting[i][j]->setSpriteSize(0.06, 0.06);
												this->CraftingQuantity[i][j] += this->ItemOnMouseQuantity;
												this->DrawField["ItemOnMouse"][0]->Is("None");
												this->DrawField["ItemOnMouse"][0]->tag = "None";
												this->DrawField["ItemOnMouse"][0]->setSpriteSize(0, 0);
												this->ItemOnMouseQuantity = 0;
											}
											else if (this->DrawField["ItemOnMouse"][0]->nowIs() == "None" && this->Crafting[i][j]->nowIs() != "None") {
												this->SoundFX["Pick"].play();
												*this->DrawField["ItemOnMouse"][0] = *Crafting[i][j];
												this->DrawField["ItemOnMouse"][0]->setSpriteSize(0.06, 0.06);
												this->Crafting[i][j]->Is("None");
												this->Crafting[i][j]->tag = "None";
												this->Crafting[i][j]->setSpriteSize(0, 0);
												this->ItemOnMouseQuantity = this->CraftingQuantity[i][j];
												this->CraftingQuantity[i][j] = 0;
											}
											else if (this->DrawField["ItemOnMouse"][0]->nowIs() == this->Crafting[i][j]->nowIs() && this->CraftingQuantity[i][j] < this->maxItemStack) {
												this->SoundFX["Pick"].play();
												if (this->CraftingQuantity[i][j] + this->ItemOnMouseQuantity <= 8) {
													this->CraftingQuantity[i][j] += this->ItemOnMouseQuantity;
													this->ItemOnMouseQuantity = 0;
													this->DrawField["ItemOnMouse"][0]->Is("None");
													this->DrawField["ItemOnMouse"][0]->tag = "None";
													this->DrawField["ItemOnMouse"][0]->setSpriteSize(0, 0);
												}
												else {
													this->ItemOnMouseQuantity -= this->maxItemStack - this->CraftingQuantity[i][j];
													this->CraftingQuantity[i][j] = this->maxItemStack;
													if (this->ItemOnMouseQuantity == 0) {
														this->DrawField["ItemOnMouse"][0]->Is("None");
														this->DrawField["ItemOnMouse"][0]->tag = "None";
														this->DrawField["ItemOnMouse"][0]->setSpriteSize(0, 0);
													}
												}
											}
											bool foundAnyRecipe = false;
											for (int i = 0; i < this->Recipe.recipeNumber(); i++) {
												if (this->Recipe.matIsReady(i, this->Crafting, this->CraftingQuantity)) {
													*this->DrawField["CraftingOutput"][0] = *itemList.object(this->Recipe.RecipeAt(i));
													this->DrawField["CraftingOutput"][0]->setPosX(this->Field["InventoryUI"].object("craftingOutput")->PosX() + 1100 * 0.06 / 2);
													this->DrawField["CraftingOutput"][0]->setPosY(this->Field["InventoryUI"].object("craftingOutput")->PosY() + 1100 * 0.06 / 2);
													this->DrawField["CraftingOutput"][0]->setSpriteSize(0.06, 0.06);
													foundAnyRecipe = true;
													break;
												}
											}
											if (!foundAnyRecipe) {
												this->DrawField["CraftingOutput"][0]->setSpriteSize(0, 0);
											}
										}
									}
								}
								if (clickHit(CraftingOutputHitbox) && this->DrawField["CraftingOutput"][0]->nowIs() != "None" && (this->DrawField["ItemOnMouse"][0]->nowIs() == "None" || this->DrawField["CraftingOutput"][0]->nowIs() == this->DrawField["ItemOnMouse"][0]->nowIs()) && this->ItemOnMouseQuantity + this->Recipe.outputNum(this->DrawField["CraftingOutput"][0]->nowIs()) <= this->maxItemStack) {
									this->SoundFX["Crafting"].play();
									cout << "Craftable : " << this->DrawField["CraftingOutput"][0]->nowIs() << '\t' << "X" << this->Recipe.outputNum(this->DrawField["CraftingOutput"][0]->nowIs()) << endl;
									*this->DrawField["ItemOnMouse"][0] = *this->DrawField["CraftingOutput"][0];
									this->ItemOnMouseQuantity += this->Recipe.outputNum(this->DrawField["CraftingOutput"][0]->nowIs());
									bool foundAnyRecipe = false;
									for (int i = 0; i < this->Recipe.MatUseNumber(this->DrawField["CraftingOutput"][0]->nowIs()); i++) {
										for (int j = 0; j < 3; j++) {
											for (int k = 0; k < 3; k++) {
												if (this->DrawField["CraftingOutput"][0]->nowIs() == "None" || this->Crafting[j][k]->nowIs() == "None") {
													continue;
												}
												if (this->Crafting[j][k]->nowIs() == this->Recipe.matAt(this->DrawField["CraftingOutput"][0]->nowIs(), i) && this->Crafting[j][k]->tag != "Tool") {
													this->CraftingQuantity[j][k] -= this->Recipe.itemUseQuantity(this->DrawField["CraftingOutput"][0]->nowIs(), i);
												}
											}
										}
									}
									for (int i = 0; i < this->Recipe.recipeNumber(); i++) {
										if (this->Recipe.matIsReady(i, this->Crafting, this->CraftingQuantity)) {
											*this->DrawField["CraftingOutput"][0] = *itemList.object(this->Recipe.RecipeAt(i));
											this->DrawField["CraftingOutput"][0]->setPosX(this->Field["InventoryUI"].object("craftingOutput")->PosX() + 1100 * 0.06 / 2);
											this->DrawField["CraftingOutput"][0]->setPosY(this->Field["InventoryUI"].object("craftingOutput")->PosY() + 1100 * 0.06 / 2);
											this->DrawField["CraftingOutput"][0]->setSpriteSize(0.06, 0.06);
											foundAnyRecipe = true;
											break;
										}
									}
									if (!foundAnyRecipe) {
										this->DrawField["CraftingOutput"][0]->setSpriteSize(0, 0);
										*this->DrawField["CraftingOutput"][0] = *NoneItem;
									}
								}
							}
							else {
								for (int i = 0; i < this->DrawField["DrawField_Dynamic"].size(); i++) {
									if (this->DrawField["DrawField_Dynamic"][i]->tag == "Building") {
										printf("66\n");
										Object* building = this->DrawField["DrawField_Dynamic"][i];
										int buildingHitbox[4] = { building->getHitBoxData()[0],
																	building->getHitBoxData()[1] - building->getImgHeight() * building->getSizeY() / 2,
																	building->getHitBoxData()[2],
																	building->getHitBoxData()[3] + building->getImgHeight() * building->getSizeY() * 0.2, };
										for (int j = 0; j < 4; j++) {
											printf("%d ", building->getHitBoxData()[j]);
										}
										printf("\n");
										if (clickHit(buildingHitbox) && ObjectDis(this->Elon, building) <= 200) {
											cout << "Click hit : " << building->nowIs() << endl;
											if (building->cat == "Pump") {
												if (this->DrawField["Hotbar"][this->selectingSlot]->nowIs() == "Hydro Flask" && this->DrawField["Hotbar"][this->selectingSlot]->getStat("durability") < this->itemList.object("Hydro Flask")->getStat("MaxDurability")) {
													this->SoundFX["Fill"].play();
													this->DrawField["Hotbar"][this->selectingSlot]->setStat("durability", this->itemList.object("Hydro Flask")->getStat("MaxDurability"));
													this->DrawField["Hotbar"][this->selectingSlot]->setSpriteTexture("default", 0);
													cout << this->DrawField["Hotbar"][this->selectingSlot]->getStat("durability") << endl;
												}
											}
											else if (building->cat == "Solar") {
												this->SoundFX["Charge"].play();
												if (this->DrawField["Hotbar"][this->selectingSlot]->nowIs() == "Power Pack" && this->DrawField["Hotbar"][this->selectingSlot]->getStat("durability") < this->itemList.object("Power Pack")->getStat("MaxDurability")) {
													this->DrawField["Hotbar"][this->selectingSlot]->setStat("durability", this->itemList.object("Power Pack")->getStat("MaxDurability"));
													this->DrawField["Hotbar"][this->selectingSlot]->setSpriteTexture("default", 0);
													cout << this->DrawField["Hotbar"][this->selectingSlot]->getStat("durability") << endl;
												}
											}
											else if (building->cat == "Doc") {
												building->usable = false;
												building->setSpriteSize(0, 0);
												giveItem("Research Document");
											}
											else if (building->cat == "Rocket") {
												this->Dialog["Victory"].object("Score")->setString(to_string(int(itemNumber("Research Document") * 20 + ceil(Elon->getStat("Health"))*10)));
												this->Elon->setSpriteSize(0, 0);
												this->MiniElon->setSpriteSize(0, 0);
												this->canMove = false;
												this->onRocket = true;
												this->Rocket = building;
											}
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
					cout << this->DrawField["Hotbar"][this->selectingSlot]->tag << "     " << this->HotbarQuantity[this->selectingSlot] << endl;
				}
			}
			else {
				int PlayHitBox[] = { 335,240,580,360 }, ExitHitBox[] = { 335,600,580,720 };
				if (ev.type == Event::MouseMoved) {
					this->mousePos[0] = ev.mouseMove.x;
					this->mousePos[1] = ev.mouseMove.y;
				}
				if (ev.type == Event::MouseButtonPressed) {
					if (ev.mouseButton.button == Mouse::Left) {
						printf("%d %d ||\n", this->mousePos[0], this->mousePos[1]);
						if (clickHit(PlayHitBox)) {
							this->SoundFX["Click"].play();
							this->construct();
							this->OnMainMenu = false;
						}
						else if (clickHit(ExitHitBox)) {
							this->SoundFX["Click"].play();
							this->window->close();
							this->running = false;
						}
					}
				}
			}
		}

	}
	bool hasEnoughItem(string item, int quantity, bool remove) {
		int itemcount = 0;
		int itemPickCount = quantity;
		for (int i = 0; i < 9; i++) {
			if (this->DrawField["Hotbar"][i]->nowIs() == item) {
				itemcount += this->HotbarQuantity[i];
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 9; j++) {
				if (this->Backpack[i][j]->nowIs() == item) {
					itemcount += this->BackpackQuantity[i][j];
				}
			}
		}
		if (remove) {
			if (itemcount >= quantity) {
				for (int i = 0; i < 9; i++) {
					if (this->DrawField["Hotbar"][i]->nowIs() == item) {
						if (itemPickCount <= this->HotbarQuantity[i]) {
							this->HotbarQuantity[i] -= itemPickCount;
						}
						else {
							this->HotbarQuantity[i] = 0;
							itemPickCount -= this->maxItemStack;
						}
					}
					if (itemPickCount == 0) {
						return true;
					}
				}
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 9; j++) {
						if (this->Backpack[i][j]->nowIs() == item) {
							if (itemPickCount <= this->BackpackQuantity[i][j]) {
								this->BackpackQuantity[i][j] -= itemPickCount;
								return true;
							}
							else {
								this->BackpackQuantity[i][j] = 0;
								itemPickCount -= this->maxItemStack;
							}
						}
						if (itemPickCount == 0) {
							return true;
						}
					}
				}
			}
		}
		else {
			if (itemcount >= quantity) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}
	int itemNumber(string item) {
		int itemcount = 0;
		for (int i = 0; i < 9; i++) {
			if (this->DrawField["Hotbar"][i]->nowIs() == item) {
				itemcount += this->HotbarQuantity[i];
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 9; j++) {
				if (this->Backpack[i][j]->nowIs() == item) {
					itemcount += this->BackpackQuantity[i][j];
				}
			}
		}
		return itemcount;
	}
	vector<vector<int>> searchFor(string item) {
		vector<vector<int>> out;
		for (int i = 0; i < 9; i++) {
			if (this->DrawField["Hotbar"][i]->nowIs() == item) {
				out.push_back({ 1,0,i });
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 9; j++) {
				if (this->Backpack[i][j]->nowIs() == item) {
					out.push_back({ 0,i,j });
				}
			}
		}
		return out;
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
		int i = floor(log10(In)) + 1;
		return i;
	}
	void updateHUD() {
		if (this->Elon->getStat("Health") > 0) {
			this->Field["HUD"].object("StatBar_Fill0")->setSpriteSize(0.06, -0.06 * this->Elon->getStat("Health") / 100);
		}
		else {
			this->Field["HUD"].object("StatBar_Fill0")->setSpriteSize(0.06, 0);
		}
		if (this->Elon->getStat("Hunger") > 0) {
			this->Field["HUD"].object("StatBar_Fill1")->setSpriteSize(0.06, -0.06 * this->Elon->getStat("Hunger") / 100);
		}
		else {
			this->Field["HUD"].object("StatBar_Fill1")->setSpriteSize(0.06, 0);
		}
		if (this->Elon->getStat("Thirst") > 0) {
			this->Field["HUD"].object("StatBar_Fill2")->setSpriteSize(0.06, -0.06 * this->Elon->getStat("Thirst") / 100);
		}
		else {
			this->Field["HUD"].object("StatBar_Fill2")->setSpriteSize(0.06, 0);
		}
		if (this->Elon->getStat("Air") > 0) {
			this->Field["HUD"].object("StatBar_Fill3")->setSpriteSize(0.06, -0.06 * this->Elon->getStat("Air") / 100);
		}
		else {
			this->Field["HUD"].object("StatBar_Fill3")->setSpriteSize(0.06, 0);
		}
		this->Field["HUD"].object("ItemPrt")->setPosX(503 + 1100 * 0.06 / 2 + (this->selectingSlot * 1100 * 0.06));
		for (int i = 0; i < 9; i++) {
			if (this->DrawField["Hotbar"][i]->nowIs() != "None" && find(this->DrawField["Hotbar_HUD"].begin(), this->DrawField["Hotbar_HUD"].end(), this->DrawField["Hotbar"][i]) == this->DrawField["Hotbar_HUD"].end()) {
				*DrawField["Hotbar_HUD"][i] = *DrawField["Hotbar"][i];
				(*DrawField["Hotbar_HUD"][i]).setPosX(503 + 1100 * 0.06 / 2 + (1100 * 0.06 * i));
				(*DrawField["Hotbar_HUD"][i]).setSpriteSize(0.06, 0.06);
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 9; j++) {
				if (this->Backpack[i][j]->nowIs() != "None")
					this->Backpack[i][j]->setPosY(233 + 1100 * 0.06 * i);
				this->Backpack[i][j]->setPosX(536 + 1100 * 0.06 * j);
			}
		}
	}
	bool pickable(Object* A) {
		bool found = false;
		for (int i = 0; i < 9; i++) {
			if (this->DrawField["Hotbar"][i]->nowIs() == charOnly(A->nowIs()) && this->HotbarQuantity[i] < this->maxItemStack) {
				return true;
			}
		}
		if (!found) {
			for (int i = 0; i < 9; i++) {
				if (this->DrawField["Hotbar"][i]->nowIs() == "None") {
					return true;
				}
			}
		}
		return false;
	}
	void update() {
		int updated = false;
		this->pollEvents();
		if (!this->OnMainMenu) {
			this->updateHUD();
			if (this->escPressed && !this->escToggle) {
				if (this->paused || this->building || this->inventory) {
					this->SoundFX["Open"].play();
					this->paused = false;
					this->building = false;
					this->inventory = false;
				}
				else {
					this->SoundFX["Open"].play();
					this->paused = true;
				}
				this->escToggle = true;
			}
			else if (!this->escPressed) {
				this->escToggle = false;
			}
			if (this->E && !this->EToggle) {
				if (this->inventory) {
					this->SoundFX["Open"].play();
					this->inventory = false;
				}
				else {
					this->SoundFX["Open"].play();
					this->inventory = true;
					this->building = false;
				}
				this->EToggle = true;
			}
			else if (!this->E) {
				this->EToggle = false;
			}
			if ((W || A || S || D || shift) && this->Elon->getStat("Alive") == 1 && !this->paused && canMove) {
				Elon->setAnimationSeq("walk");
				DecStat("Hunger", 0.0002);
				DecStat("Thirst", 0.0003);
				DecStat("Air", 0.005);
				if (shift) {
					this->MusicFX["Walking"].stop();
					this->MusicFX["Running"].pause();
					if (walk || idle) {
						this->MusicFX["Running"].setPlayingOffset(Time(seconds(rand() % 10)));
						walk = false;
						idle = false;
					}
					this->MusicFX["Running"].play();
					printf("Running\n");
					this->Elon->UpdateAnimation(2);
					DecStat("Hunger", 0.002);
					DecStat("Thirst", 0.003);
				}
				else {
					this->MusicFX["Running"].stop();
					this->MusicFX["Walking"].pause();
					if (!walk || idle) {
						this->MusicFX["Walking"].setPlayingOffset(Time(seconds(rand() % 10)));
						walk = true;
						idle = false;
					}
					this->MusicFX["Walking"].play();
					printf("Walking\n");
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
				this->MusicFX["Running"].stop();
				this->MusicFX["Walking"].stop();
				Idle();
				idle = true;
				this->Elon->resetTimeSeq();
			}
			//printf("%d | %.0llf, %.0llf | %.0llf, %.0llf |  \n", this->DrawField.size(), Elon->PosX(), Elon->PosY(), this->Field.object("0")->PosX(), this->Field.object("0")->PosY());
			try {
				for (int i = 0; i < this->Field["Dynamic"].entityNumber(); i++) {
					if (this->Field["Dynamic"].objectAt(i)->type() == "Dynamic" && i < this->Field["Dynamic"].entityNumber() && this->Field["Dynamic"].objectAt(i)->usable) {
						this->Field["Dynamic"].objectAt(i)->setPosX(this->Anchor->PosX());
						this->Field["Dynamic"].objectAt(i)->setPosY(this->Anchor->PosY());
					}
				}
				for (int i = 0; i < this->Field["GameBG"].entityNumber(); i++) {
					this->Field["GameBG"].objectAt(i)->setPosX(this->Anchor->PosX());
					this->Field["GameBG"].objectAt(i)->setPosY(this->Anchor->PosY());
				}
			}
			catch (const std::out_of_range& e) {
				printf("%d\n", e);
			}
			MiniElon->setPosX(this->Anchor->PosX());
			MiniElon->setPosY(this->Anchor->PosY());
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
				if (Elon->getStat("Health") <= 1 && !GameOver) {
					if (_time) {
						this->Elon->resetTimeSeq();
						_time = false;
					}
					if (Elon->time > 40) {
						Sleep(1000);
						printf("Die\n");
						GameOver = true;
					}
					Elon->setStat("Alive", 0);
					Elon->setAnimationSeq("dying");
					Elon->UpdateAnimation(1);
				}
				vector<vector<int>> power = searchFor("Power Pack");
				bool foundPowerPack = false;
				for (int i = 0; i < power.size(); i++) {
					if (power[i][0] == 1 && this->DrawField["Hotbar"][power[i][2]]->getStat("durability") > 0) {
						float powerPercent = 100 * this->DrawField["Hotbar"][power[i][2]]->getStat("durability") / this->itemList.object("Power Pack")->getStat("MaxDurability");
						this->DrawField["Hotbar"][power[i][2]]->increase("durability", -0.01);
						if (powerPercent > 75) {
							this->DrawField["Hotbar"][power[i][2]]->setSpriteTexture("default", 0);
						}
						else if (powerPercent > 50 && powerPercent <= 75) {
							this->DrawField["Hotbar"][power[i][2]]->setSpriteTexture("default", 1);
						}
						else if (powerPercent > 25 && powerPercent <= 50) {
							this->DrawField["Hotbar"][power[i][2]]->setSpriteTexture("default", 2);
						}
						else if (powerPercent > 0.1 && powerPercent <= 25) {
							this->DrawField["Hotbar"][power[i][2]]->setSpriteTexture("default", 3);
						}
						else if (powerPercent <= 0.1) {
							this->DrawField["Hotbar"][power[i][2]]->setSpriteTexture("default", 4);
						}
						foundPowerPack = true;
						//printf("Power Pack (1,0,%d) : %f\n", power[i][2], powerPercent);
						break;
					}
					else if (power[i][0] == 0 && this->Backpack[power[i][1]][power[i][2]]->getStat("durability") > 0) {
						this->Backpack[power[i][1]][power[i][2]]->increase("durability", -0.01);
						float powerPercent = 100 * this->Backpack[power[i][1]][power[i][2]]->getStat("durability") / this->itemList.object("Power Pack")->getStat("MaxDurability");
						if (powerPercent > 75) {
							this->Backpack[power[i][1]][power[i][2]]->setSpriteTexture("default", 0);
						}
						else if (powerPercent > 50 && powerPercent <= 75) {
							this->Backpack[power[i][1]][power[i][2]]->setSpriteTexture("default", 1);
						}
						else if (powerPercent > 25 && powerPercent <= 50) {
							this->Backpack[power[i][1]][power[i][2]]->setSpriteTexture("default", 2);
						}
						else if (powerPercent > 0.1 && powerPercent <= 25) {
							this->Backpack[power[i][1]][power[i][2]]->setSpriteTexture("default", 3);
						}
						else if (powerPercent <= 0.1) {
							this->Backpack[power[i][1]][power[i][2]]->setSpriteTexture("default", 4);
						}
						foundPowerPack = true;
						//printf("Power Pack (0,%d,%d) : %f\n", power[i][1], power[i][2], powerPercent);
						break;
					}
				}
				if (!foundPowerPack) {
					Elon->setStat("Air", 0);
				}
			}
			int maxParam = 0;
			for (int i = 0; i < this->DrawField["DrawField_Dynamic"].size(); i++) { // repeate for every object on the ground
				Object* Obj = this->DrawField["DrawField_Dynamic"][i]; // get object to check
				if (Obj->usable && Obj->tag == "fallItem" && ObjectDis(this->Field["Dynamic"].object("Elon"), Obj) <= 50 && pickable(Obj)) { // check if this object is item and it came close enough to pick
					this->DrawField["DrawField_Dynamic"][i]->usable = false; // tell game engine that this item have been picked.
					giveItem(charOnly(Obj->nowIs())); // give item to player.
				}
				if (Obj->usable && Obj->tag == "fallItem" && ObjectDis(this->Field["Dynamic"].object("Elon"), Obj) <= 200 && pickable(Obj)) { // check if this object is item and it came close enough
					const vector<float> moveVec = getVector(this->Field["Dynamic"].object("Elon")->PosX(), this->Field["Dynamic"].object("Elon")->PosY(), Obj->PosX(), Obj->PosY()); // get vector from item to player
					Obj->setOffsetPosX(Obj->offsetPosX + 7 * moveVec[0] / abs(moveVec[0] + 1)); // use vector to move item along x axis.
					Obj->setOffsetPosY(Obj->offsetPosY + 7 * moveVec[1] / abs(moveVec[1] + 1)); // use vector to move item along y axis.
				}
			}
			MiniElon->setAnimationSeq("idle");
			//////////////////////////////////////////////////////////////////////
			if (ObjectDis(this->Field["Dynamic"].object("Elon"), MiniElon) > 100) { // check if this object is item and it came close enough
				const vector<float> moveVec = getVector(this->Field["Dynamic"].object("Elon")->PosX(), this->Field["Dynamic"].object("Elon")->PosY(), MiniElon->PosX(), MiniElon->PosY()); // get vector from item to player
				MiniElon->setAnimationSeq("walk");
				if (abs(moveVec[0]) > 10) {
					if (moveVec[0] / abs(moveVec[0]) > 0) {
						MiniElon->flipTexture(1);
					}
					else if (moveVec[0] / abs(moveVec[0]) < 0) {
						MiniElon->flipTexture(-1);
					}
					MiniElon->setOffsetPosX(MiniElon->offsetPosX + moveVec[0] * 0.03); // use vector to move item along x axis.
				}
				if (abs(moveVec[1]) > 10) {
					MiniElon->setOffsetPosY(MiniElon->offsetPosY + moveVec[1] * 0.03); // use vector to move item along y axis.
				}
				if (sqrt(pow(moveVec[0], 2) + pow(moveVec[1], 2)) > 150) {
					MiniElon->UpdateAnimation(7);
				}
			}
			else {
				MiniElon->setAnimationSeq("idle");
			}
			///////////////////////////////////////////////////////////////////////
			MiniElon->UpdateAnimation(1);
			for (int i = 0; i < 9; i++) {
				if (this->HotbarQuantity[i] == 0 && this->DrawField["Hotbar"][i]->nowIs() != "None") {
					printf("Remove slot %d\n", i);
					this->DrawField["Hotbar"][i]->Is("None");
					this->DrawField["Hotbar"][i]->tag = "None";
					this->DrawField["Hotbar"][i]->setSpriteSize(0, 0);

				}
				if (this->DrawField["Hotbar"][i]->nowIs() != "None" && this->DrawField["Hotbar"][i]->getStat("showCount") == 1 && this->HotbarQuantity[i] > 0) {
					const float x = (535 + 1100.0 * 0.06 * i) - this->Dialog["itemCount"].object("itemCount" + to_string(i))->getLocalBounds().width / 2, y = 830, x1 = x - 0.7 * IntDigit(this->HotbarQuantity[i]);
					this->Dialog["itemCount"].object("itemCount" + to_string(i))->setPosition({ x,y });
					this->Dialog["itemCount"].object("itemCount" + to_string(i))->setString(to_string(this->HotbarQuantity[i]));
					this->Dialog["itemCount"].object("itemCountBG" + to_string(i))->setPosition({ x1,y });
					this->Dialog["itemCount"].object("itemCountBG" + to_string(i))->setString(to_string(this->HotbarQuantity[i]));

					this->Dialog["InventoryItem_hotbar"].object("InventoryitemCountBG_hotbar" + to_string(i))->setPosition({ x,533 });
					this->Dialog["InventoryItem_hotbar"].object("InventoryitemCountBG_hotbar" + to_string(i))->setString(to_string(this->HotbarQuantity[i]));
					this->Dialog["InventoryItem_hotbar"].object("InventoryitemCount_hotbar" + to_string(i))->setPosition({ x1,533 });
					this->Dialog["InventoryItem_hotbar"].object("InventoryitemCount_hotbar" + to_string(i))->setString(to_string(this->HotbarQuantity[i]));
				}
				else {
					this->Dialog["itemCount"].object("itemCount" + to_string(i))->setString(" ");
					this->Dialog["itemCount"].object("itemCountBG" + to_string(i))->setString(" ");

					this->Dialog["InventoryItem_hotbar"].object("InventoryitemCount_hotbar" + to_string(i))->setString(" ");
					this->Dialog["InventoryItem_hotbar"].object("InventoryitemCountBG_hotbar" + to_string(i))->setString(" ");
				}
				*DrawField["InventoryUseSlot"][i] = *DrawField["Hotbar"][i];
			}
			if (this->DrawField["Hotbar"][this->selectingSlot]->nowIs() != "None") {
				const float x = 800 - this->Dialog["InGameStatus"].object("ItemInHand")->getLocalBounds().width / 2, y = 750;
				this->Dialog["InGameStatus"].object("ItemInHand")->setPosition({ x,y });
				this->Dialog["InGameStatus"].object("ItemInHand")->setString(this->DrawField["Hotbar"][this->selectingSlot]->nowIs());
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 9; j++) {
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
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (this->CraftingQuantity[i][j] <= 0) {
						this->Crafting[i][j]->Is("None");
						this->Crafting[i][j]->tag = "None";
						this->Crafting[i][j]->setSpriteSize(0, 0);
					}
					if (this->Crafting[i][j]->nowIs() != "None" && this->Crafting[i][j]->getStat("showCount") == 1 && this->CraftingQuantity[i][j] > 0) {
						const float x = (1230 + 1100.0 * 0.06 * i) - this->Dialog["InventoryItem"].object("InventoryitemCount" + to_string(i) + to_string(j))->getLocalBounds().width / 2, y = 233 + 1100 * 0.06 * j, x1 = x - 0.7 * IntDigit(this->CraftingQuantity[i][j]);
						this->Dialog["CraftingItem"].object("CraftingItemCount" + to_string(i) + to_string(j))->setPosition({ x,y });
						this->Dialog["CraftingItem"].object("CraftingItemCount" + to_string(i) + to_string(j))->setString(to_string(this->CraftingQuantity[i][j]));
						this->Dialog["CraftingItem"].object("CraftingItemCountBG" + to_string(i) + to_string(j))->setPosition({ x1,y });
						this->Dialog["CraftingItem"].object("CraftingItemCountBG" + to_string(i) + to_string(j))->setString(to_string(this->CraftingQuantity[i][j]));
					}
					else {
						this->Dialog["CraftingItem"].object("CraftingItemCount" + to_string(i) + to_string(j))->setString(" ");
						this->Dialog["CraftingItem"].object("CraftingItemCountBG" + to_string(i) + to_string(j))->setString(" ");
					}
				}
			}
			if (onRocket) {
				this->Rocket->MovePosY(-400 / (1 + pow(1.1, 150 - Rockettime++)));
				if (this->Rocket->PosY() < -1000) {
					Sleep(3000);
					this->Victory = true;
					this->onRocket = false;
					this->pause = true;
				}
			}
			//end
		}
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
			if (!this->OnMainMenu) {
				for (int i = 0; i < this->DrawField["DrawField_BG"].size(); i++) {
					//cout << this->DrawField["DrawField_BG"][i]->nowIs() << '\t' << this->DrawField["DrawField_BG"][i]->PosX() << ','<< this->DrawField["DrawField_BG"][i]->PosY() << '\t' << Elon->PosX() << ',' << Elon->PosY() << endl;
					this->window->draw(this->DrawField["DrawField_BG"][i]->getSprite());
				}
				for (int i = 0; i < this->DrawField["DrawField_Dynamic"].size() && this->DrawField["DrawField_Dynamic"][i]->tag != "BG"; i++) {
					this->window->draw(this->DrawField["DrawField_Dynamic"][i]->getSprite());
				}
				MiniElon->UpdateAnimation(2);
				if (!this->onRocket) {
					for (int i = 0; i < this->DrawField["DrawField_HUD"].size() && DrawField["DrawField_HUD"][i]; i++) {
						this->window->draw(this->DrawField["DrawField_HUD"][i]->getSprite());
					}
					for (int i = 0; i < this->DrawField["Hotbar_HUD"].size() && DrawField["Hotbar_HUD"][i]; i++) {
						this->DrawField["Hotbar_HUD"][i]->setPosY(833);
						this->window->draw(this->DrawField["Hotbar_HUD"][i]->getSprite());
					}
					for (int i = 0; i < Dialog["itemCount"].entityNumber(); i++) {
						this->window->draw(*this->Dialog["itemCount"].objectAt(i));
					}
					if (this->DrawField["Hotbar"][this->selectingSlot]->nowIs() != "None") {
						this->window->draw(*this->Dialog["InGameStatus"].object("ItemInHand"));
					}
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
						this->DrawField["InventoryUseSlot"][i]->setPosY(533);
						this->window->draw(this->DrawField["InventoryUseSlot"][i]->getSprite());
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 9; j++) {
							this->window->draw(this->Backpack[i][j]->getSprite());
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							this->window->draw(this->Crafting[i][j]->getSprite());
						}
					}
					for (int i = 0; i < this->Dialog["InventoryItem_hotbar"].entityNumber(); i++) {
						this->window->draw(*this->Dialog["InventoryItem_hotbar"].objectAt(i));
					}
					for (int i = 0; i < this->Dialog["InventoryItem"].entityNumber(); i++) {
						this->window->draw(*this->Dialog["InventoryItem"].objectAt(i));
					}
					for (int i = 0; i < this->Dialog["CraftingItem"].entityNumber(); i++) {
						this->window->draw(*this->Dialog["CraftingItem"].objectAt(i));
					}
					this->window->draw(this->DrawField["ItemOnMouse"][0]->getSprite());
					this->window->draw(this->DrawField["CraftingOutput"][0]->getSprite());
				}
				else if (this->Victory) {
					for (auto obj : this->DrawField["Victory"]) {
						this->window->draw(obj->getSprite());
					}
					for (int i = 0; i < this->Dialog["Victory"].entityNumber(); i++) {
						this->window->draw(*this->Dialog["Victory"].objectAt(i));
					}
				}
				else if (this->GameOver) {
					for (auto obj : DrawField["GameOver"]) {
						this->window->draw(obj->getSprite());
					}
					for (int i = 0; i < this->Dialog["GameOver"].entityNumber(); i++) {
						this->window->draw(*this->Dialog["GameOver"].objectAt(i));
					}
				}
			}
			else {
				for (int i = 0; i < this->DrawField["MainMenu"].size(); i++) {
					this->window->draw(this->DrawField["MainMenu"][i]->getSprite());
				}
				for (int i = 0; i < this->Dialog["MainMenuButton"].entityNumber(); i++) {
					this->window->draw(*this->Dialog["MainMenuButton"].objectAt(i));
				}
			}
		}
		catch (int e) {
			printf("%d\n", e);
		}
		//printf("%f, %f\n", this->dui.getPosX(), this->dui.getPosY());

		this->window->display();
		/*
				for (int i = 0; i < 8; i++) {
					cout << this->DrawField["ItemUseSlot"][i]->nowIs() << '\t';
				}
				cout << endl;
				*/
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
		for (int i = 0; i < First_step.Field["Dynamic"].entityNumber(); i++) {
			if (First_step.Field["Dynamic"].objectAt(i)->usable && !First_step.pause && (First_step.Field["Dynamic"].objectAt(i)->type() != "Static" && First_step.Field["Dynamic"].objectAt(i)->tag != "BG" || First_step.Field["Dynamic"].objectAt(i)->nowIs() == "Elon") && !(std::find(First_step.DrawField["DrawField_Dynamic"].begin(), First_step.DrawField["DrawField_Dynamic"].end(), First_step.Field["Dynamic"].objectAt(i)) != First_step.DrawField["DrawField_Dynamic"].end()) && (First_step.ObjIsOnSight(First_step.Elon, First_step.Field["Dynamic"].objectAt(i), 1100) || First_step.Field["Dynamic"].objectAt(i)->nowIs() == "Anchor" || First_step.Field["Dynamic"].objectAt(i)->nowIs() == "BG")) {
				First_step.DrawField["DrawField_Dynamic"].push_back(First_step.Field["Dynamic"].objectAt(i));
			}
			change = true;
		}
		for (int i = 0; i < First_step.DrawField["DrawField_Dynamic"].size(); i++) {
			if (First_step.DrawField["DrawField_Dynamic"][i]->nowIs() != "Elon" && (!First_step.DrawField["DrawField_Dynamic"][i]->usable || (First_step.pause && i < First_step.Field["Dynamic"].entityNumber() - 1 && !(First_step.ObjIsOnSight(First_step.Elon, First_step.DrawField["DrawField_Dynamic"][i], 1100) || First_step.DrawField["DrawField_Dynamic"][i]->nowIs() == "Anchor" || First_step.DrawField["DrawField_Dynamic"][i]->nowIs() == "BG" || First_step.DrawField["DrawField_Dynamic"][i]->nowIs() == "Elon")))) {
				First_step.DrawField["DrawField_Dynamic"].erase(First_step.DrawField["DrawField_Dynamic"].begin() + i);
			}
			change = true;
		}
		while (swaping) {
			swaping = SortObj();
		}
	}
	catch (int e) {
		printf("%d\n", e);
	}
}
void checkFloorInsight() {
	while (First_step.isRuning()) {
		First_step.FloorAck = false;
		Sleep(1);
		while (First_step.isRuning() && (First_step.DrawField["BG_repo"].size() == 0 || First_step.pause || First_step.OnMainMenu)) {
			Sleep(1);
			First_step.FloorAck = true;
		}
		if (!First_step.isRuning()) {
			break;
		}
		for (int i = 0; i < First_step.DrawField["BG_repo"].size(); i++) {
			if (!First_step.pause && !(find(First_step.DrawField["DrawField_BG"].begin(), First_step.DrawField["DrawField_BG"].end(), First_step.DrawField["BG_repo"][i]) != First_step.DrawField["DrawField_BG"].end()) && First_step.ObjIsOnSight(First_step.Field["Dynamic"].object("Elon"), First_step.DrawField["BG_repo"][i], 1500)) {
				First_step.DrawField["DrawField_BG"].push_back(First_step.DrawField["BG_repo"][i]);
			}
		}
		for (int i = 0; i < First_step.DrawField["DrawField_BG"].size(); i++) {
			if (!First_step.pause && !(First_step.ObjIsOnSight(First_step.Field["Dynamic"].object("Elon"), First_step.DrawField["DrawField_BG"][i], 1500))) {
				First_step.DrawField["DrawField_BG"].erase(First_step.DrawField["DrawField_BG"].begin() + i);
			}
		}
	}
	printf("checkFloor closed\n");
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
////////////////////////////////////////////////////////////////////////////////
const vector<float> getVector(float x1O, float y1O, float x2O, float y2O) {
	return { x1O - x2O, y1O - y2O };
}
///////////////////////////////////////////////////////////////////////////////

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
		First_step.DynamicAck = false;
		Sleep(1);
		bump = false;
		while (First_step.isRuning() && (First_step.Field["Dynamic"].entityNumber() == 0 || First_step.pause || First_step.onRocket)) {
			Sleep(1);
			First_step.DynamicAck = true;
		}
		if (!First_step.isRuning()) {
			break;
		}
		CheckInsight();
		for (int i = 0; i < First_step.DrawField["DrawField_Dynamic"].size(); i++) {
			try {
				ElonHitBox = First_step.Elon->getHitBoxData();
				ObjHitBox = First_step.DrawField["DrawField_Dynamic"][i]->getHitBoxData();
			}
			catch (const std::out_of_range& e) {
				cout << "Out of Range error.";
			}
			if (!First_step.pause && First_step.DrawField["DrawField_Dynamic"][i]->usable && !First_step.DrawField["DrawField_Dynamic"][i]->passable && hitBoxhit(ElonHitBox[0] + hitBoxXoffset, ElonHitBox[1], ElonHitBox[2] - hitBoxXoffset, ElonHitBox[3], ObjHitBox[0], ObjHitBox[1], ObjHitBox[2], ObjHitBox[3])) {
				HitVec = getVector(ObjHitBox[4], ObjHitBox[5], ElonHitBox[4], ElonHitBox[5]);
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
	printf("checkBump closed\n");
}

void ShowDrawingStat() {
	while (First_step.isRuning()) {
		while (First_step.Field["Dynamic"].entityNumber() == 0 || First_step.pause) {
			Sleep(1);
		}
		if (First_step.OnMainMenu) {
			First_step.DrawField["DrawField_Dynamic"] = *new vector<Object*>;
			First_step.DrawField["DrawField_Static"] = *new vector<Object*>;
			while (First_step.OnMainMenu) {
				Sleep(1);
			}
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
		while (First_step.Field["Dynamic"].entityNumber() == 0 || First_step.pause) {
			Sleep(1);
		}
		printf("BG : %d, Dynamic : %d, Static %d, Overall %d\n", First_step.DrawField["DrawField_BG"].size(), First_step.DrawField["DrawField_Dynamic"].size(), First_step.DrawField["DrawField_Static"].size(), First_step.Field["Dynamic"].entityNumber());
	}
}

void ShowDrawingStat2() {
	while (First_step.isRuning()) {
		while (First_step.Field["Dynamic"].entityNumber() == 0 || First_step.pause) {
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
		while (First_step.Field["Dynamic"].entityNumber() == 0 || First_step.paused) {
			Sleep(1);
		}
		for (int i = 0; i < 8; i++) {
			cout << First_step.DrawField["ItemUseSlot"][i]->nowIs() << '\t';
		}
		cout << endl;
	}
}
int main() { // Game loop
	Thread CheckInsight_Thread1(&CheckInsight), CheckBump(&isMovable), CheckFloor(&checkFloorInsight), monitor(&ShowDrawingStat3);
	CheckBump.launch();
	CheckFloor.launch();
	while (First_step.isRuning()) {
		First_step.update();
		First_step.render();
		Sleep(1);
	}
	printf("Exit\n");
	return 0;
}