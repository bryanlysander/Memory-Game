#ifndef _MEMORY_GAME
#define _MEMORY_GAME
#include <string>
using namespace std;
class MemoryGame
{
public: //public method member, any class can use these methods
    MemoryGame(); 
       //default constructor, with 3 pairs of numbers 
       //randomly located in 8 blocks (two blocks are empty).
    //MemoryGame(int n); 
       //with n >= 3 pairs of numbers randomly located
    //MemoryGame(int n, int m);
       //with n >= 3 pairs of numbers randomly located in m space
    //MemoryGame(string *words, int size);
       //instead of randomly generated numbers,
       //pairs with words
    ~MemoryGame();
    void play();
    void display(bool* bShown); 
         //display array values, if bShown[i] is true,
         //then values[i] is displayed, where i is the index.

private: //private data members, private means that
         //only methods in this class, not other class,
         //can access or modify these data members.
    int numPairs; //numPairs of identical twin items
    int numSpaces; 
        //size of array value, besides identical twins, 
        //may contain empty string to 
        //make the problem more challenging
    string *values; 
        //a string to represent the layout of data,
        //mixed with possible empty strings.
        //Use array to access each element in const time.
};
#endif
