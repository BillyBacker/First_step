#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>

using namespace sf;

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

class objectSlot { //This is a class for item keeping slot in player backpack or chest.
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

class map { //This a class that will store every object that on the ground in game.
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

class player { //This is a class of player stat, position, and player's inventory.
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
		void setPos(float Pos[2]) {
			setPosX(Pos[0]);
			setPosY(Pos[1]);
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

class resource { //class that store quantity of each resource. now unused.
	private:
		int power = 0;
		int water = 0;
		int food = 0;

		int metal = 0;
		int mineral = 0;
		int concrete = 0;
		int composite_metal = 0;
		int PLA = 0;
		int ABS = 0;
		int rock = 0;
		int dirt = 0;

	public:
		int get_power() {
			return power;
		}
		int get_water() {
			return water;
		}
		int get_food() {
			return food;
		}
		int get_metal() {
			return metal;
		}
		int get_mineral() {
			return mineral;
		}
		int get_concrete() {
			return concrete;
		}
		int get_composite_metal() {
			return composite_metal;
		}
		int get_PLA() {
			return PLA;
		}
		int get_ABS() {
			return ABS;
		}
		int get_rock() {
			return rock;
		}
		int get_dirt() {
			return dirt;
		}
		void loss_power(int amount) {
			power -= amount;
		}
		void loss_water(int amount) {
			water -= amount;
		}
		void loss_food(int amount) {
			food -= amount;
		}
		void loss_metal(int amount) {
			metal -= amount;
		}
		void loss_mineral(int amount) {
			mineral -= amount;
		}
		void loss_concrete(int amount) {
			concrete -= amount;
		}
		void loss_composite_metal(int amount) {
			composite_metal -= amount;
		}
		void loss_PLA(int amount) {
			PLA -= amount;
		}
		void loss_ABS(int amount) {
			ABS -= amount;
		}
		void loss_rock(int amount) {
			rock -= amount;
		}
		void loss_dirt(int amount) {
			dirt -= amount;
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
			RectangleShape monster;
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
			while (this->window->pollEvent(this->ev)) {
				switch (this->ev.type) {
				case Event::Closed:
					this->window->close();
					break;
				case Event::KeyPressed:
					if (ev.key.code == Keyboard::Escape) {
						this->window->close();
					}
					break;
				}
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
			this->window->draw(this->monster);
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
