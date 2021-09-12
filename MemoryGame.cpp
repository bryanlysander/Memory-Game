#include "MemoryGame.hpp"
#include <cstdlib> //srand, rand
#include <ctime>
#include <iomanip> //setw
#include <iostream> //std
#include <vector>
using namespace std;

int* randomize(int numSpaces); //function to randomize layout
void swap(int* arr, int i, int j);
void displaySeparateLine(int numSpaces);

MemoryGame::MemoryGame() //default constructor, 

{
    srand(time(0)); //Using srand to randomize the number on the flipping card everytime the game is played

    numPairs = 3; 
    numSpaces = 8;

    int * random_numbers = new int[numPairs];
 
   //in order to get the random numbers in pairs we need to use loop
    for (int i = 0; i < numPairs; i++){
       random_numbers[i] = rand() % 1000; //we fill the array random_numbers with random numbers in the range of 1-1000, no more no less.
    }

    values = new string[numSpaces];

    int *randomize_result = randomize(numSpaces);

    for(int i = 0; i < numSpaces; i+=2){
        if (i < numSpaces-2){
            values[randomize_result[i]] = to_string(random_numbers[i/2]);
            values[randomize_result[i +1]] = to_string(random_numbers[i/2]);

        }
        else{
            values[randomize_result[i]] = "";
        }
    }

    delete[] random_numbers;
    random_numbers = nullptr;
    delete randomize_result;
    randomize_result = nullptr;

}
 
MemoryGame::~MemoryGame()
{
    delete[] values;
    //When an object is no longer in need,
    //release dynamically allocated memory by 
    //data members of the current object.

}

int* randomize(int size)
{
    int* array = new int[size];
    for (int i =0; i < size; i++){
        array[i] = i;
    }

    int element; //declaring a variable named element which will hold the value of rand & size
    int swap_holder;

    while(size > 0){
        element = rand() % size;
        swap_holder = size -1;
        swap(array, element, swap_holder); //we will call our swap function to swap our values
        size --; //reduce size by 1, decrement it
    }

    return array;

    //idea to randomize 0, 1, 2, 3, 4, 5,
    //generate a random int in [0, 6), say 3,
    //then move arr[3] to the end,
    //say, 0, 1, 2, 5, 4, 3
    //generate a random int in [0, 5), say 3 again,
    //then swap arr[3], which is 5 now, with arr[4], 
    //get 0, 1, 2, 4, 5, 3
    //generate a random int in [0, 4), say 2,
    //swap arr[2] with the current arr[3]
    //get 0, 1, 4, 2, 5, 3
    //continue to randomize arr[0..2].
    //afterwards, continue to randomize arr[0..1].

}


void swap(int *arr, int i, int j)
{
    int temporary = arr[i];
    arr[i] = arr[j];
    arr[j] = temporary;
}

//Display -----+ for numSpaces times.
//Add an extra + when for the first block (when index i is 0).
//So suppose numSpaces is 8, we get
//+-----+-----+-----+-----+-----+-----+-----+-----+
//followed by a new line.
void displaySeparateLine(int numSpaces)
{
    for (int i = 0; i < numSpaces; i++)
    {
        if (i == 0)
           cout << "+";
        cout << "-----+";
    }
    cout << endl;
}

//display the items in values array where bShown is true.
void MemoryGame::display(bool* bShown)
{
    cout << " ";
    for (int i = 0; i < numSpaces; i++){
        cout << setw(3) << i; // so that the first 3 step are empty then prints the number i
        cout << setw(3) << " "; //after printing i print another 3 empty space
    }

    cout << endl; //make sure to end the line or else it will still be on the same line

    displaySeparateLine(numSpaces); //call the function displaySeperateline which is our void function that will prints out the "+-----" for the roof of our game box

    for (int i = 0; i < numSpaces; i++){ //loop for the inside of our game box
        cout << "|"; 
        if (bShown[i]){ //if our bollean function is true with i, returns or open the value
            cout << setw(5) << values[i];
        }
        else{ //if not then just set 5 speace space
            cout << setw(5) << " ";
        }

    }

    cout << "|"; //for mid and closing of the box
    cout << endl; //make sure to end the line or else it will be on the same line as our gamebox

    displaySeparateLine(numSpaces); //call the function displaySeperateline which will print "+---" for the floor of our game
}

//picking difficulty
//depending on the difficulty the user picked, we will have the same amount of pair but we will have more empty spaces
//this way it will make it more challenging for the user
//rules for a round
//(1) pick a number, flip it
//(2) pick a second number, if the number is the same as
//    previous pick, display the second number,
//    otherwise, unflip the previous pick.
//(3) Finish until every pair are chosen correctly.
void MemoryGame::play()
{   
    cout << "Please select a level difficulty between 1 to 3" << endl;
    int difficulty;
    cin >> difficulty;
    while(difficulty < 1 || difficulty > 3){
        cout << "Level of difficulty has to be in range 1 to 3" << endl;
        cout << "Re-enter levele of difficulty: ";
        cin >> difficulty; 
    }

    if (difficulty == 2){
        numSpaces = 10;    
    }
    else if (difficulty == 3){
        numSpaces = 12;
    }

    bool* bShown = new bool[numSpaces]; 
    for (int i = 0; i < numSpaces; i++){
        bShown[i] = false;
    }

    display(bShown);

    int index;
    int first;
    int numFlips = 0;
    int pairsFound = 0;

    

    while (pairsFound < numPairs){
        cout << "Pick a cell to flip: ";
        cin >> index;
        while (index < 0 || index >= numSpaces || bShown[index]){
            if (index < 0 || index >= numSpaces){
                cout << "index needs to be in range [0, " << numSpaces - 1 << "]." << endl;
            }
            else{
                cout << "The cell indexed at " << index << " is shown." << endl;
            }
            cout << "Re-enter an index: ";
            cin >> index;
        }

        if (numFlips % 2 ==0){
            bShown[index] = true;
            first = index;
        }
        else{
            if (values[first] == values[index] && values[first] != ""){
                bShown[index] = true;
                pairsFound++;
            }
            else{
                bShown[first] = false; 
            }
        }
        display(bShown);
        numFlips++;
    }

    cout << "Congratulations! Take " << numFlips << " steps to find all matched pairs." << endl;

    delete[] bShown;
    bShown = nullptr;

}
