#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <signal.h>
#include<sys/wait.h> 
using namespace std;

string text = "For years, stomachs across Long Beach lamented the city’s lack of a proper ramen house. Be it Hakata or Onomichi ramen, tsukemen ramen or all the other ramen varieties that create the rainbow arch of Japan’s staple dish, there was a culinary hole in the local Asian cuisine scene that has long been dominated by Thai food, sushi and fast Chinese. Sure, a Thai joint here or a random sushi bar there would offer a ramen option—Bamboo Teri House in Bixby Knolls immediately comes to mind—but it was toward the back of the menu, typically hidden in a corner. However, true ramen lovers would have to trek beyond the borders of Long Beach to experience a solid bowl. You could venture to L.A.’s Little Tokyo and wait in line to experience the Hokkaido-based Hakata ramen stylings of Daikokuya, where creamy bowls of tonkotsu pork broth—where pork bones bounce around in boiling liquids for hours and sometimes days on end, their bits of marrow melted into minuscule grains that create a cloudy bowl of broth—cook egg noodles to al dente perfection. Or, if you wanted to travel a bit less, there was an almost-as-good Hakata bowl at Shin Sen Gumi, which has locations throughout the Southland, including a ramen drive-thru. Or go to Gardena for a bowl of shoyu ramen at Asa or Sapporo ramen at Mottainai, two additional styles also based out Japan’s Hokkaido region. The larger point here is Long Beach lacked restaurants whose main focus was the art of Ramen. It’s an art that has garnered a Michelin star. That star belongs to Chef Onishi Yuki’s Tsuta ramen shop, offering Tokyo-style ramen, long considered the country’s standard definition of ramen with its seafood-meets-chicken broth—and it will soon be opening a location in Glendale. It’s an art that provides comfort to Japanese citizens and immigrants and descendants across the world. And now, Long Beach has four houses to share this experience with (with a fifth on the way: Mr. Makoto, the new ramen joint from the owners of Seoulmate, will be opening this fall at 2741 E 4th Street where Yummy Garden used to be). Let’s begin with what I consider to be the best and we’ll count down from there.";


int main(){
	int enteredLength;
	bool keepGoing = true;	//continue looping?
	bool repeating = false; //go into infnite loop?

	//Get user input
	cout << endl << "Enter an integer and I will tell you how many words in the document are that many letters!" << endl <<endl;
	
	//Loop keeps program running until user enters "0"
	while(keepGoing == true){
		cout << "Enter integer: ";
		cin >> enteredLength;

		//Terminate program if user enters "0"
		if(enteredLength == 0){
			cout << "Terminating...goodbye!" << endl;
			break;
		}
		
		//Spawn child process
		//fork() returns NEGATIVE number if failed to spawn child, 0 to new child, and the child PID to parent
		long childPID = fork();

		//Parent
		if(childPID > 0) {
			wait(0);
		//Child - process counts and outputs number of words of length enteredLength
		} else if (childPID == 0) {
			while(true) { //creates infinite loop if there are no words of desired length
				if(repeating == true){
					cout << "." << endl;			
				}	
				int wordLength = 0; //current word length
				int numMatches = 0; //number of words that are of length enteredLength
				
				//Iterate through text
				for(int i = 0; i < text.size(); i++){
					if(isalpha(text[i]) != 0){ //if character is a letter, increment wordLength
						wordLength++;
					} else if (text[i] = ' ') { //if there is a space, word length goes back to zero
						if(wordLength == enteredLength) {
							numMatches++; //increment number of matches
						}
						wordLength = 0; //reinitiate wordLength for the new word
					}
				}
			
				//If there are matches, output will display and child process will terminate
				if(numMatches != 0) {
					cout << "Number of words of length " << enteredLength << ": " << numMatches << endl << endl;
					kill(getpid(), SIGKILL); //terminate child process
					break; //break infinite loop
				}
				else if(numMatches == 0){
					repeating = true;
				} 
			}
			
		} else {
			cout << "Spawn error - no child process" << endl;
		}
	}
	
	return 0;
}
