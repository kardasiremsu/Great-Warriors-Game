#include <iostream>
#include <cstring>
#include "GreatWarrior.h"

using namespace std;

Land::Land(string name, string holding){ //constructor with parameter
    this->name = name;
    this->holding = holding;
}

Land::Land(const Land &land){ //copy constructor
    this->name = land.name;
    this->holding = land.holding;
}

Character::Character(string name, int manpower, int gold, int numOfLands){ ///constructor with parameter
    this->name = name;
    this->manpower = manpower;
    this->gold = gold;
    this->numOfLands = numOfLands;
    this->lands = NULL;
}

Character::Character(const Character &character){ //copy constructor
    this->name = character.name;
    this->manpower = character.manpower;
    this->gold = character.gold;
    this->numOfLands = character.numOfLands;
    this->lands = character.lands;
}

Character::~Character(){ //destructor
    Land *ptr = this->lands;
    while(ptr !=NULL){
        Land *deleted = ptr;
        ptr = ptr->getNext();
        delete deleted;
    }    
}

int Character::getTaxes(){ //collect taxes from lands which character has
    int village =0, castle =0, city=0;
    Land *ptr = lands;
    while(ptr !=NULL){
        if(ptr->getHolding() == "village" ){village +=1;}
        else if(ptr->getHolding() == "castle"){castle +=1;}
        else if(ptr->getHolding() == "city"){city +=1;}
        ptr = ptr->getNext();
    }
    int add_gold = (village *5) +  (castle*7) + (city*10);
    return add_gold;
}

void Character::addLand(string landname, string landholding){ //add land to first element in linkedlist for the character
    if(lands == NULL){
        lands = new Land;
        lands->setName(landname);
        lands->setHolding(landholding);
        lands->setNext(NULL);
    }
    else{
        Land *temp = new Land;
        temp->setName(landname);
        temp->setHolding(landholding);
        temp->setNext(lands);
        lands = temp;
    }
    numOfLands +=1;
}

void Character::removeLand(string land_name){
    Land *ptr = lands;
    if(ptr->getName() == land_name)
    {
        Land *temp = lands;
        ptr = ptr->getNext();
        delete temp;
    }
    else{
        while(ptr->getNext() != NULL){
            if(ptr->getNext()->getName() == land_name){
                Land  *temp = ptr->getNext();
                ptr->setNext(ptr->getNext()->getNext());
                delete temp;
                return;
            }
            ptr = ptr->getNext();
        }
    }
}

CharacterList::CharacterList(){ //default constructor
    size = 0;
}

CharacterList::~CharacterList(){ //deconstructor
    for (int i = 0; i < size; i++) {
        delete characters[i];
    }
    delete [] characters;
}

void CharacterList::addCharacter(Character *character){ //add character to charlist
    if(size == 0){
        size ++;
        characters = new Character*[size];
        characters[0] = character;
        return;
    }
    else if(size >= 1){
        size ++;
        Character **temp = new Character*[size];
        for(int i=0; i<size-1; i++){
            temp[i] = characters[i];
        }
        temp[size-1] = character;
        delete [] characters;
        characters = new Character*[size];
        for(int i=0; i<size; i++){
            characters[i] = temp[i]; 
        }
    }
}

void CharacterList::removeCharacter(Character *character){ //remove character from charlist
    int index = 0;
    while(characters[index]->getName() != character->getName()){
        index++;
    }

    delete characters[index];

    for (int i = index ; i < size - 1; i++){
        characters[i] = characters[i+1]; //delete with swip element
    }

    size -=1;
    Character **temp = new Character*[size];

    for(int k = 0; k<size; k++){
        temp[k] = characters[k];
    }

    delete [] characters;
    characters = temp;
}

Character* CharacterList::getPlayer(int index){ 
    return characters[index]; //return reference to character which is given index
}

int CharacterList::getLandOwner(string land){//return character index which has spesific land
    int i=0;
    for(; i<size; i++){
        Land *ptr = getPlayer(i)->getLands();
        while(ptr != NULL){
            if(ptr->getName() == land){
                return i;
                break;
            }
            else{
                ptr = ptr->getNext();
            }
        }
    }
    return -1;
}