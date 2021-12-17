#ifndef GREATWARRIOR_H_
#define GREATWARRIOR_H_
#include <iostream>
#include <cstring>

using namespace std;

class Land {

    private:
        string name;
        string holding;
        Land *next;

    public:
        Land(string = "Gotham", string = "village"); //constructor that optionally take attributes
        Land(const Land &land); //copy constructor

        string getName() {return name;}  //getter for name
        string getHolding() {return holding;} //getter for holding
        Land* getNext() {return next;} //getter for next
        
        void setName(string name) {this->name = name;} //setter for name
        void setHolding(string holding) {this->holding = holding;} //setter for holding
        void setNext(Land* next) {this->next = next;} //setter for holding
};

class Character {

    private:
        string name;
        int manpower;
        int gold;
        int numOfLands;
        Land *lands;

    public:
        Character(string = "", int = 3, int= 20, int = 0); //constructor that optionally take attributes
        Character(const Character &character); //copy constructor
        ~Character(); //destructor

        string getName() const {return name;} //this is constant objects (actually general object)
        string getName() {return name;} //getter for name
        int getManpower() {return manpower;} //getter for manpower
        int getGold() {return gold;} //getter for gold
        int getNumOfLands() {return numOfLands;} //getter for numoflands
        Land * getLands() {return lands;} //getter for head of lands
        
        void setName(string name) {this->name = name;} //setter for name
        void setManpower(int manpower) {this->manpower = manpower;} //setter for manpower
        void setGold (int gold) {this->gold = gold;} //setter for gold
        void setNumOfLands(int numOfLands) {this->numOfLands = numOfLands;} //setter for numoflands
        void setLands(Land *lands) {this->lands = lands;} //setter for head of lands
        
        int getTaxes(); //collect taxes from lands which character has
        void addLand(string, string); //add a land to the character
        void removeLand(string); //remove a land from the character
};

class CharacterList{
    
    private:
        Character* *characters;
        int size;

    public:
        CharacterList(); //constructor
        ~CharacterList(); //destructor
        
        int getsize() {return size;} //getter for size
        Character ** getcharacters() {return characters;} //getter for characters
        
        friend void listLands(CharacterList &); //list all lands inside of all charlist
        friend void listCharacters(CharacterList&); //list all characters inside of all charlist

        void addCharacter(Character*); //add character to charlist
        void removeCharacter(Character*); //remove character from charlist
        Character* getPlayer(int); //return reference to character which is given index
        int getLandOwner(string); //return character index which has spesific land      
};

#endif
