#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <iostream>

using namespace sf;
using namespace std;

class Object {
	private:
		Object* memAdress;
		int objectIndex = -1;
		int objectID = -1;
		float posX;
		float posY;
	public:
		float getPosX() {
			return this->posX;
		}
		float getPosY() {
			return this->posY;
		}
		int ID() {
			return this->objectID;
		}
		int getIndex() {
			return this->objectIndex;
		}
		void setID(int ID) {
			this->objectID = ID;
		}
		void setPosX(float X) {
			this->posX = X;
		}
		void setPosY(float Y) {
			this->posX = Y;
		}
		void setPos(float X, float Y) {
			setPosX(X);
			setPosY(Y);
		}
		void setIndex(int Index) {
			this->objectIndex = Index;
		}
		void clear() {
			this->objectIndex = -1;
			this->objectID = -1;
		}
		void setMemAdress(Object* adress) {
			this->memAdress = adress;
		}
		Object* getAdress() {
			return memAdress;
		}
};

class objectSlot { //This is a class for Object that will display on the ground.
private:
	int slotNum = 1024;
	Object objectSlot[1024];

public:
	void create(int ID, float X, float Y) {
		for (int index = 0; index < 1024; index++) {
			if (this->objectSlot[index].getIndex() == -1) {
				this->objectSlot[index].setPos(X, Y);
				this->objectSlot[index].setID(ID);
				this->objectSlot[index].setIndex(index);
				this->objectSlot[index].setMemAdress(&this->objectSlot[index]);
				break;
			}
		}
	}
	void remove(int Index) {
		objectSlot[Index].clear();
	}
	Object* getMemoryAddress(int Index) {
		return objectSlot[Index].getAdress();
	}
	Object Object_at(int Index) {
		return objectSlot[Index];
	}
	void print_to_console() {
		for (int index = 0; index < 1024; index++) {
			printf("Slot : %d, object ID : %d\n", index, this->objectSlot[index].ID());
		}
	}
};

class Map { //This a class that will store every object that on the ground in game.
	private:
		objectSlot Object_on_ground;
		int objectNumber = 0;

	public:
		void createObject(int ID, float X, float Y) {
			this->Object_on_ground.create(ID, X, Y);
			this->objectNumber++;

		}
		void removeObject(int Index) {
			this->Object_on_ground.remove(Index);
			this->objectNumber -= 1;
		}
		objectSlot ObjectSlot(int Index) {
			return this->Object_on_ground;
		 }
};

class itemStack { //This is a class of a stack of item in inventory or on a floor.
	private:
		int itemID = -1;
		int itemAmount = 0;

	public:
		int getAmount() {
			return this->itemAmount;
		}
		int ID() {
			return this->itemID;
		}
		void getItem(int amount) {
			this->itemAmount += amount;
		}
		void lossItem(int amount) {
			this->itemAmount -= amount;
		}
		void setID(int ID) {
			this->itemID = ID;
		}
};

class inventory { //This is a class for item keeping slot in player backpack or chest.
	private:
		int slotNum = 9;
		itemStack itemSlot[9];

	public:
		void quickStore(int ID, int amount) {
			bool stacked = false;
			for (int index = 0; index < 9; index++) {
				if (ID == this->itemSlot[index].ID()) {
					this->itemSlot[index].getItem(amount);
					stacked = true;
					break;
				}
			}
			for (int index = 0; index < 9; index++) {
				if (this->itemSlot[index].ID() == -1 && !stacked) {
					this->itemSlot[index].setID(ID);
					this->itemSlot[index].getItem(amount);
					break;
				}
			}
		}
		void manualStore(int ID, int amount, int index){
			if (this->itemSlot[index].ID() == -1) {
				this->itemSlot[index].setID(ID);
				this->itemSlot[index].getItem(amount);
			}
			else if (ID == this->itemSlot[index].ID()) {
				this->itemSlot[index].getItem(amount);
			}
		}
		void print_to_console() {
			for (int index = 0; index < 9; index++) {
				printf("Slot : %d, Item ID : %d, %d EA\n", index, this->itemSlot[index].ID(), this->itemSlot[index].getAmount());
			}
		}
};

class Charactor { //This is a class of player stat, position, and player's inventory.
	private:
		inventory backpack;
		char action = 'I';
		int interacting_object_ID = -1;

		int health = 100;
		int hunger = 100;
		int thirst = 100;

		float Position[2] = {10,10};

		void setPosX(float X) {
			Position[0] = X;
		}
		void setPosY(float Y) {
			Position[1] = Y;
		}
		

	public:
		void listBackpack() {
			this->backpack.print_to_console();
		}
		char getAction() {
			return this->action;
		}
		int now_interact_with() {
			return this->interacting_object_ID;
		}
		float* getPos() {
			return this->Position;
		}
		float getPosX() {
			return this->Position[0];
		}
		float getPosY() {
			return this->Position[1];
		}
		int getHP() {
			return this->health;
		}
		int getHG() {
			return this->hunger;
		}
		int getTS() {
			return this->thirst;
		}
		void interact_with(int ID) {
			this->interacting_object_ID = ID;
		}
		void Action(char act) {
			this->action = act;
		}
		void setPos(int X, int Y) {
			setPosX(X);
			setPosY(Y);
		}
		void lossHP(int amount) {
			this->health -= amount;
		}
		void lossHG(int amount) {
			this->hunger -= amount;
		}
		void lossTS(int amount) {
			this->thirst -= amount;
		}
		void healHP(int amount) {
			this->health += amount;
		}
		void healHG(int amount) {
			this->hunger += amount;
		}
		void healTS(int amount) {
			this->thirst += amount;
		}
		void recieveItem(int ID, int amount) {
			this->backpack.quickStore(ID, amount);
		}
};

class Player {
	private:
		Charactor action;
		Sprite body;
		Texture texture;
		float posX;
		float posY;
		int step = 0;

		void Init() {
			if (!texture.loadFromFile("assets\\alien\\PNG\\alien_red\\red__0000_idle_1.png")) {
				printf("Error");
			}
			this->body.setScale(0.2, 0.2);
			this->body.setTexture(texture);
			
		}
	public:
		Player() {
			this->Init();
		}
		Sprite Body() {
			return body;
		}
		void setPos(float X, float Y) {
			this->body.setPosition(X, Y);
			this->posX = X;
			this->posY = Y;
		}
		void move(float X, float Y) {
			setPos(this->posX + X, this->posY + Y);
		}
		Charactor Action() {
			return action;
		}
		float getPosX() {
			return this->posX;
		}
		float getPosY() {
			return this->posY;
		}
};

class gameEngine { //this a main class of this game. resposibility for render object, recieve input event, draw graphic.
	private:
		//Add a variable down here.

		int h = 900;
		int w = 1600;
		RenderWindow* window;
		Event ev;
		VideoMode mode;
		RectangleShape monster;
		Player Billy;
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
		void initMonster() {
			this->monster.setPosition(50, 50);
			this->monster.setSize(Vector2f(1000.f, 1000.f));
			this->monster.setFillColor(Color::Green);
			this->monster.setOutlineColor(Color::Green);
			this->monster.setOutlineThickness(1.f);
		}
		float distance_between_object_object(Object a, Object b) {
			return (sqrt(pow((a.getPosX() - b.getPosX()), 2) + pow((a.getPosY() - b.getPosY()), 2)));
		}
		float distance_between_object_point(Object a, int X, int Y) {
			return (sqrt(pow((a.getPosX() - X), 2) + pow((a.getPosY() - Y), 2)));
		}

	public:
		gameEngine() {
			this->initVar();
			this->initMonster();
			this->initWindow();
		}
		virtual ~gameEngine() {
			delete this->window;
		}
		const bool isRuning() {
			return this->window->isOpen();
		}
		void pollEvents() {
			int move_speed = 10;
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				this->window->close();
			}
			else if (Keyboard::isKeyPressed(Keyboard::W)) {
				Billy.move(0, -1* move_speed);
			}
			else if (Keyboard::isKeyPressed(Keyboard::S)) {
				Billy.move(0, 1* move_speed);
			}
			else if (Keyboard::isKeyPressed(Keyboard::A)) {
				Billy.move(-1* move_speed, 0);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D)) {
				Billy.move(1* move_speed, 0);
			}
		}
		void update() {
			this->pollEvents();
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
			this->window->draw(this->Billy.Body());
			//printf("%f, %f\n", this->dui.getPosX(), this->dui.getPosY());
	
			this->window->display();
		}
};

int main(){ // Game loop
	gameEngine First_step;
	while (First_step.isRuning()){
		First_step.update();
		First_step.render();
	}
}
