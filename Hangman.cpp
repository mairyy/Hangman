#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

const int MAX_BAD_GUESS = 7;

void start();
string chooseTopic();
string chooseWord(const string& fileName);
string toLowerCase(const string& word);
void renderGame(string guessedWord, int badGuessCount, string guessChars);
char readAGuess();
bool contains(string secretWord, char guess);
void update(string& guessedWord, const string& secretWord, char guess);
void clearScreen();
int main(){
	cout << "Hello! Do you want to play Hangman?\n"
		 << "Enter 'y' to start!\n";
	string playerChoice;
	cin >> playerChoice;
	playerChoice = toLowerCase(playerChoice);
	while (playerChoice == "y"){
		start();
		cout << "Do you want to play again? Enter 'y' to play or 'n' to stop!\n";
		cin >> playerChoice;
	}
	clearScreen();
	cout << "End game!";
	return 0;
}

void start(){
	string topic = chooseTopic();
	string secretWord = chooseWord(topic);
	string guessedWord = string(secretWord.length(), '-');
	int badGuessCount = 0;
	string guessChars = "";
	do{
		renderGame(guessedWord, badGuessCount, guessChars);
		char guess = readAGuess();
		guessChars += guess;
		guessChars += " ";
		if (contains(secretWord, guess)){
			update(guessedWord, secretWord, guess);
		} else{
			badGuessCount++;
		}
	}while(badGuessCount < MAX_BAD_GUESS && guessedWord != secretWord);
	renderGame(guessedWord, badGuessCount, guessChars);
	if (badGuessCount < MAX_BAD_GUESS){
		cout << "Congratulation! You win!" << endl;
	} else{
		cout << "You lost. The correct word is " << secretWord << endl;
	}
}

string chooseTopic(){
	cout << "Choose topic:\n"
		 << "1. General\n"
		 << "2. School\n"
		 << "3. Sports\n"
		 << "4. Country Name\n"
		 << "Enter '1' '2' '3' '4' to choose!\n";
	int num;
	cin >> num;
	string topicLists[] = {
		"general.txt",
		"school.txt",
		"sports.txt",
		"countryName.txt"
	};
	return topicLists[num-1];
}

string chooseWord(const string& fileName){
	vector <string> wordList;
	ifstream file(fileName);
	if (file.is_open()){
		string word;
		while (file >> word){
			wordList.push_back(word);
		}
	}
	if (wordList.size() > 0){
		srand(time(0));
		return toLowerCase(wordList[rand() % wordList.size()]);
	}else{
		return "";
	}
}

string toLowerCase(const string& word){
	string newWord = word;
	for (int i = 0; i < newWord.length(); i++){
		if (newWord[i] >= 'A' && newWord[i] <= 'Z')
			newWord[i] += 32;
	}
	return newWord;
}

const string figure[] = {
	"  -------------   \n"
	"  |               \n"
	"  |               \n"
	"  |               \n"
	"  |               \n"
	"  |               \n"
	"-----             \n",
	
	"  -------------   \n"
	"  |           |   \n"
	"  |               \n"
	"  |               \n"
	"  |               \n"
	"  |               \n"
	"-----             \n",
	
	"  -------------   \n"
	"  |           |   \n"
	"  |           0   \n"
	"  |               \n"
	"  |               \n"
	"  |               \n"
	"-----             \n",
	
	"  -------------   \n"
	"  |           |   \n"
	"  |           0   \n"
	"  |           |   \n"
	"  |               \n"
	"  |               \n"
	"-----             \n",
	
	"  -------------   \n"
	"  |           |   \n"
	"  |           0   \n"
	"  |          /|   \n"
	"  |               \n"
	"  |               \n"
	"-----             \n",
	
	"  -------------   \n"
	"  |           |   \n"
	"  |           0   \n"
	"  |          /|\\ \n"
	"  |               \n"
	"  |               \n"
	"-----             \n",
	
	"  -------------   \n"
	"  |           |   \n"
	"  |           0   \n"
	"  |          /|\\ \n"
	"  |          /    \n"
	"  |               \n"
	"-----             \n",
	
	"  -------------   \n"
	"  |           |   \n"
	"  |           0   \n"
	"  |          /|\\ \n"
	"  |          / \\ \n"
	"  |               \n"
	"-----             \n"
};
void renderGame(string guessedWord, int badGuessCount, string guessChars){
	clearScreen();
	cout << figure[badGuessCount] << endl
		 << guessedWord << endl
		 << "Number of wrong guesses: " << badGuessCount << endl
		 << "Guessed letters: " << guessChars << endl;
}

char readAGuess(){
	char c;
	cout << "Your guess: ";
	cin >> c;
	return c;
}

bool contains(string secretWord, char guess){
	for (int i = 0; i < secretWord.length(); i++){
		if (secretWord[i] == guess){
			return true;
		}
	}
	return false;
}

void update(string& guessedWord, const string& secretWord, char guess){
	for (int i = 0; i < secretWord.length(); i++){
		if (secretWord[i] == guess){
			guessedWord[i] = guess;
		}
	}
}

void clearScreen(){
	#ifdef _WIN32
		system("cls");
	#else 
		system("clear");
	#endif 
}