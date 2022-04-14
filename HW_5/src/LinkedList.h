#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_


#include "LinkedList.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;


template <class T>
class LLNode;

template <class T>
class LLNode
{
private:
    class LLNode<T>* PNext;
	class LLNode<T>* PPrev;
	T* PointerToElm;

public:

LLNode() {
    PNext = (LLNode*) 0;
    PPrev = (LLNode*) 0;
    PointerToElm = (T*) 0;
}
~LLNode() {
	if(this->isEmpty()){	}
	else {  delete PointerToElm;
            delete PNext;}
}

LLNode(T* LP) {
    PNext = (LLNode*) 0;
    PPrev = (LLNode*) 0;
    PointerToElm = LP;
}
LLNode(LLNode* nextP, T* LP) {
    PNext = (LLNode*)nextP;
    PPrev = (LLNode*) 0;
    PointerToElm = LP;
}
LLNode(LLNode* nextP, LLNode* prevP, T* LP) {
    PNext = (LLNode*)nextP;
    PPrev = (LLNode*)prevP;
    PointerToElm = LP;
}

T* getElementP() {
    return PointerToElm;
}
LLNode<T>* getPrevP() {
    return (LLNode*)PPrev;
}
LLNode<T>* getNextP() {
    return (LLNode*)PNext;
}
void setElementP(T* elementP) {PointerToElm = elementP;}
void setNextP(LLNode<T>* nextP) {PNext = nextP;}
void setPrevP(LLNode<T>* prevP) {PPrev = prevP;}
void SavePayload(T* LP) {
    LLNode<T>* temp = this;

	if(this->isEmpty())
	{
		PointerToElm = LP;
	}
	else if(temp->getNextP())
    {
        temp=(LLNode*)temp->getNextP();
        temp->SavePayload(LP);
    }

    else
	{
	    LLNode* newListP = new LLNode(LP);
		this->PNext = (class LLNode*) newListP;
		newListP->PPrev =(class LLNode*) this;
	}
}
bool isEmpty() {
    bool ok = false;
    if (this == (LLNode*)0) {ok = true;}
    else if (PointerToElm == (T*) 0) {ok = true;}
    return ok;
}
bool SearchList(T* LP) {
    LLNode* temp = this;

      if(this->isEmpty())
	{
            return false;
    }
	else if (this->getElementP() == LP)
    {
        //we found the T
        return true;
    }

    else if(temp->getNextP()) {     // otherwise continue searching
        temp=(LLNode*)temp->getNextP();
        temp->SearchList(LP);
    }

    else    // if not found return false
	{
		return false;
    }
}
LLNode<T>* getL() {

    LLNode* temp = this;

      if(this->isEmpty())
	{
            return (LLNode*) 0;
    }
	else if (this->getNextP())
    {
        temp = temp->getNextP();
        temp ->getL();
    }

    else    // if not found return false
	{
		return temp;
    }
}

int Length() {
    if (this->isEmpty()) {return 0;} //list was empty;

    int lenght = 1;
    LLNode<T>* temp = this;
    while (temp->getNextP())
    {
        ++lenght;
        temp = temp -> getNextP();
    }

    return lenght;
}
void addLL(LLNode<T>* OriginalList) {
    if (OriginalList->isEmpty()) {} //nothing to do

    else {
        int length = OriginalList->Length();

        LLNode<T>* temp = OriginalList;
        for (int i = 0; i< length; ++i) {
            this->SavePayload(temp->getElementP());
            temp = temp->getNextP();
        }
    }
}
void removeItemFromLL(T* LP) {
	if(this->isEmpty())
	{}      // nothing to do
	else

	{
        if(this->PointerToElm == LP)
        {
            if(this->Length() == 1) // if the list is a single node
            {
                this->setElementP((T*) 0);
            }
            else {
            LLNode<T>* temp = getNextP();
            this->setElementP(temp->getElementP());
            this->setNextP(temp->getNextP());
            temp->setNextP((LLNode<T>*) 0);
            //delete temp;
            }
            }
        else {
        LLNode* temp = this->getNextP();

        while (temp->getNextP())// iterate through
        {
             LLNode* curr = temp->getNextP();
             LLNode* prev = temp->getPrevP();
            // if we find the thing we are looking for
            if(temp -> PointerToElm == LP) {

                    // we skip that element when returning
                prev->setNextP((class LLNode*) curr);
                curr->setPrevP((class LLNode*) prev);
                temp->setNextP((LLNode<T>*) 0);
                return;
            }
            // otherwise continue searching
            else {
                temp = temp->getNextP();
            }
        }

        //check if last is the thing we are looking for
        if (temp->PointerToElm == LP) {

            LLNode* prev = temp->getPrevP();
            prev->setNextP((LLNode<T>*) 0);
            //delete temp;
        }
        }
    }
}

T* getRandom() {

    int randomNumber = rand();
    int length = this->Length();
    int randomIndex = randomNumber % length;

    LLNode<T>* temp = this;
    for (int i = 0; i<randomIndex; ++i ) {
        temp = temp ->getNextP();
    }

    return temp ->getElementP();
}

};



#endif // LINKEDLIST_H_
