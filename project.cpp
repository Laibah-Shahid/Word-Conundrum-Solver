#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <limits>
#include <conio.h>

#define MAX_AlPHABETS 9

using namespace std;

const int Default = 7;
const int yellow = 14;

void clearScreen(){
    system("cls");
}

class UserInfo {
    string name;
    int score;

public:
    UserInfo() : score(0),name("unknown"){}

    void setName(string &n) {
        name = n;
    }

    void setScore(int s) {
        score = s;
    }

    string getName() const {
        return name;
    }

    int getScore() const {
        return score;
    }

    void displayUserInfo() const{
        cout << getName() << " your final score is:"<<getScore() << endl;
    }

};

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

class Game {
protected:
    UserInfo userinfo;

public:
    virtual void gameIntro() = 0;

    virtual void startGame() = 0;
};

class GameOne : public Game {
private:
    int tries, hint;
    int wordCount;
    string level;
    string letter;
    vector<string> wordsAddedByUser;
    vector<string> fileContents;

public:
    GameOne(string &n) : tries(3), wordCount(0), level("easy"), hint(3){
        userinfo.setName(n);
    }

    void startGame() override {
        int choice;
        gameIntro();
        try{
            putDataInVector("C:/Users/fariy/OneDrive/Desktop/WordList.txt");
        }
        catch (const char *message) {
            cout << message << endl;
            exit(0);
        }

        while (true) {
            if (level == "easy") {
                generateLetters();
                cout <<"\t\t\t\t\t" << "Welcome to Easy Level" << endl << endl;
                playLevel(5);

                if (wordsAddedByUser.size() == 5) {
                    choice=continueLevel();
                    if (choice==1){
                    level = "medium";
                    clearScreen();
                    continue;
                    } else{
                        abandonJourneyMessage();
                        break;
                    }
                }

            } else if (level == "medium") {
                clearScreen();
                generateLetters();
                cout <<"\t\t\t\t\t" <<"Welcome to Medium Level" << endl << endl;
                playLevel(10);

                if (wordsAddedByUser.size() == 15) {
                    choice=continueLevel();
                    if (choice==1){
                    level = "difficult";
                    clearScreen();
                    continue;
                    } else {
                        abandonJourneyMessage();
                        break;
                    }
                }
            } else if (level == "difficult") {
                clearScreen();
                generateLetters();
                cout << "\t\t\t\t\t" << "Welcome to Difficult Level" << endl << endl;
                playLevel(15);
                if (wordsAddedByUser.size() == 30) {
                    cout << "Good job! You have passed through all the doors!" << endl;
                    cout << "The princess has been rescued!" <<  endl;
                    userinfo.displayUserInfo();
                    break;
                }
            } else if (level == "lose") {
                cout<<"GAME OVER!"<<endl<<"You failed to save the princess!"<<endl;
                userinfo.displayUserInfo();
                break;
            }
        }
    }


private:
     void putDataInVector(string fileName) {
        ifstream inputFile(fileName);
        if (inputFile.is_open()) {
            string line;
            while (getline(inputFile, line)) {
                fileContents.push_back(line);
            }
            inputFile.close();
        } else {
            throw "Unable to open file.";
        }
    }

    void abandonJourneyMessage(){
        cout << "You choose to abandon your journey and accept the gold!" << endl;
        userinfo.displayUserInfo();
    }

    void generateLetters() {
        letter.clear();
        int i=0;

        char arrayVowels[] = "aeiou";
        char arrayConsonants[] = "bcdfghjklmnpqrstvwxyz";

        srand((unsigned) time(NULL));

        vector<char> uniqueLetters;

        while(true) {

            char temp;

            if (i % 2 == 0) {
                temp = arrayConsonants[rand() % 21];
            } else {
                temp = arrayVowels[rand() % 5];
            }

            if (find(uniqueLetters.begin(), uniqueLetters.end(), temp) == uniqueLetters.end()) {
            letter.push_back(temp);
            uniqueLetters.push_back(temp);
            i++;
                if (i == MAX_AlPHABETS){
                    break;
                }
            }

            else {
                continue;
            }


        }
    }

    void displayLetters(){
        setConsoleColor(Default);
        cout<<"\t\t\t\t\t\t---DISPLAYING LETTERS---"<<endl<<endl;
        setConsoleColor(yellow);
        cout<<"\t\t  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<endl;
        cout<<"\t\t / "<<"  \\ "<<"   / "<<"  \\ "<<"   / "<<"  \\ "<<"   / "<<"  \\ "<<"   / "<<"  \\ "<<"   / "<<"  \\ "<<"   / "<<"  \\ "<<"   / "<<"  \\ "<<"   / "<<"  \\ "<<endl;
        cout<<"\t\t   "<<letter[0]<<"   ---"<<"  "<<letter[1]<<"  ---"<<"   "<<letter[2]<<"   ---"<<"  "<<letter[3]<<"   ---"<<"  "<<letter[4]<<"   ---"<<"  "<<letter[5]<<"   ---"<<"  "<<letter[6]<<"   ---"<<"  "<<letter[7]<<"   ---"<<"  "<<letter[8]<<endl;
        cout<<"\t\t \\   "<<"/ "<<"   \\   "<<"/ "<<"   \\   "<<"/ "<<"   \\   "<<"/ "<<"   \\   "<<"/ "<<"   \\   "<<"/ "<<"   \\   "<<"/ "<<"   \\   "<<"/ "<<"   \\   "<<"/ "<<endl;
        cout<<"\t\t  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<"  ---"<<"    "<<endl;
        setConsoleColor(Default);
    }



    void letterCase(string &word) {
        for (int i = 0; i < word.size(); i++) {
            if (isupper(word[i])) {
                word[i] = char(tolower(word[i]));
            }
        }
    }

    int isValid(string &word) {
        letterCase(word);

        int flag = 0;

        for (int i = 0; i < word.size(); i++) {
            bool found = false;
            for (int j = 0; j < letter.size(); ++j) {
                if (word[i] == letter[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                flag = 0;
                break;
            }
            flag = 1;
        }

        if (flag == 1) {
            flag = 0;
            for (int i = 0; i < fileContents.size(); i++) {
                if (word == fileContents[i]) {
                    flag = 1;
                    break;
                }
            }
        }

        return flag;
    }

    void validityMessage(int flag) const {
        if (flag == 1) {
            cout << "Correct." << endl;
        } else {
            cout << "Incorrect." << endl;
        }
    }

    void displayWordsAddedByUser() {
        cout << "Words added: ";
        for (int i = 0; i < wordsAddedByUser.size(); i++) {
            cout << wordsAddedByUser[i] << " ";
            if (i == 4 || i == 14 ){
                cout<<endl;
            }
        }
        cout << endl;
    }

    bool isWordAdded(string word) {
        return find(wordsAddedByUser.begin(), wordsAddedByUser.end(), word) != wordsAddedByUser.end();
    }

    void updateWordCount() {
        wordCount++;
    }

    string generateHint() {
        string word;

        while (true) {
            vector<char> availableLetters;
            for (int i = 0; i < letter.size(); ++i) {
                availableLetters.push_back(letter[i]);
            }

            random_shuffle(availableLetters.begin(), availableLetters.end());

            int wordLength = rand() % MAX_AlPHABETS + 1;

            word = string(availableLetters.begin(), availableLetters.begin() + wordLength);

            if (isValid(word) && !isWordAdded(word)){
                break;
            } else {
                continue;
            }
        }

        return word;
    }

    void updateScore(string &word) {
        int len = word.length() / 2;
        userinfo.setScore(userinfo.getScore() + len);
        cout << "+" << len << endl;
    }

    void handleHint() {
        if (hint > 0) {
            string hintWord = generateHint();
            cout << "Hint: " << hintWord << endl;
            wordsAddedByUser.push_back(hintWord);
            updateScore(hintWord);
            updateWordCount();
            hint--;
        } else {
            cout << "No more hints left!" << endl;
        }
        cout << "Press any key to continue" << endl;
         _getch();
        clearScreen();
    }

    void handleValidWord(string word) {
        validityMessage(1);
        wordsAddedByUser.push_back(word);
        updateScore(word);
        updateWordCount();
        cout << "Press any key to continue" << endl;
         _getch();
        clearScreen();
    }

    void handleInvalidWord() {
        validityMessage(0);
        tries--;
        cout << "Press any key to continue" << endl;
         _getch();
        clearScreen();
    }

    void displayGameInfo(int levelWords) {
        cout << "Generate " << levelWords <<" words to proceed."<<endl<<endl;
        cout << "Lives: " << tries << "\t\t\t\t" << "Level:" << level << "\t\t\t\t" << "(Press h)Hints:" << hint << endl << endl;
        cout << "Score: " << userinfo.getScore() << "\t\t\t\t\t\t\t\t\t" << "Words Formed:" << wordCount << endl << endl;
        displayWordsAddedByUser();
        cout << endl;
        displayLetters();
        cout << endl;
    }

    void playLevel(int levelMaxWordCount) {
        wordCount=0;

        while (wordCount < levelMaxWordCount && tries != 0) {
            displayGameInfo(levelMaxWordCount);
            string word;
            cout << "Enter word: ";
            cin >> word;
            letterCase(word);

            if (word == "h" || word == "H") {
                handleHint();
            } else if (isValid(word) && !isWordAdded(word)) {
                handleValidWord(word);
            } else {
                handleInvalidWord();
            }

            if (tries == 0) {
                level = "lose";
                break;
            }
        }
    }

    int continueLevel(){
    int choice;

    cout<< "A member from the villian's team has appeared before you!" << endl;
    cout<< "He promises you gold if you turn back!" << endl;
    cout<< "1-Continue Ahead\t2-Turn Back"<<endl;
    cin>>choice;

    return choice;
    }

    void gameIntro() override{
    clearScreen();
    cout << "\t\t\t\tWelcome to the world of WordLandia Adventures!"<<endl;
    cout << "\t-----------------------------------------------------------------------------------------"<<endl;
    cout << "\t\tYou've been given a quest to embark on a mission to save the missing princess!" << endl <<endl;
    cout << "\tYou've found the villian's liar but to save the princess you must go through three set of doors!"<<endl<<endl;
    cout << "\tEach door consists of 9 letters and you must generate valid english words of minimum length 3." << endl<<endl;
    cout << "\t\t\tThe number of words depends on the difficulty of level."<<endl<<endl;
    cout << "\t\t\t\tGood Luck! The princess is waiting for you!"<<endl<<endl;
    cout << "Press any key to continue" << endl << endl;
    _getch();
    clearScreen();
    }
};

class GameTwo : public Game {
private:
    int difficultyLevel;
    vector<string> wordPool;

public:
    GameTwo(string & n) :difficultyLevel(1) {
        userinfo.setName(n);
        userinfo.setScore(0);
    }

    void startGame() override {
        gameIntro();
        char choice;
        do {
            clearScreen();  // Clear the screen (for Windows, change to "clear" for Linux/Mac)
            display();
            userinfo.setScore(userinfo.getScore()+call());
            cout << "Do you want to play again? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
        } while (choice != 'n');

        userinfo.displayUserInfo();
    }

private:
    int getRandomNumber(int min, int max) {
        static bool initialized = false;
        if (!initialized) {
            srand(time(nullptr));
            initialized = true;
        }
        return rand() % (max - min + 1) + min;
    }

    int call() {
        int hint;
        string output;
        string wordPool[10] = {"Efficient", "Learning", "World", "Hello", "Name", "Share", "Complete", "Global", "Comment"};
        char arr[10][10];

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                char c;
                int r;
                r = rand() % 26;   // generate a random number
                c = 'a' + r;            // Convert to a character from a-z
                arr[i][j] = c;
            }
        }

        int index = rand() % 10;
        setConsoleColor(yellow);
        output = wordPool[index];

        if (output.length() % 2 == 0) {
            // for even string length case
            int row = rand() % 10;
            int col = rand() % 3;
            for (int i = 0; output[i] != '\0'; i++, col++) {
                arr[row][col] = output[i];
            }
        } else {
            // for odd string length case
            int row = rand() % 3;
            int col = rand() % 10;
            for (int i = 0; output[i] != '\0'; i++, row++) {
                arr[row][col] = output[i];
            }
        }

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                cout << " " << arr[i][j];
                Sleep(90);
            }
            cout << endl;
        }

        string guess;
        setConsoleColor(Default);
        cout << "Press 1 for directly guessing the word." << endl;
        cout << "Press 2 to see the word length hint and then guess." << endl;

        label1:
        cout << "Enter your choice: ";
        cin >> hint;
        cout << endl;

        if (cin.fail()) {
            // Clear the error flag
            cin.clear();

            // Clear the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter a valid numeric choice." << endl;
            goto label1;
        }

        if (hint == 1) {
            // Do nothing
        } else if (hint == 2) {
            cout << "The guessed word in the puzzle has a size of: " << output.size() << endl;
        } else {
            cout << "Invalid input. Please enter a valid choice." << endl;
            goto label1;
        }

        cout << "Enter the word you guess: ";
        cin >> guess;
        cout << endl;

        if (guess == output) {
            cout << "Congratulations! You have guessed the correct word." << endl;
            cout << "You were able to get out of the Pharaoh's room alive!" << endl;
            return 1;
        } else {
            cout << "Game over! You died." << endl;
            return 0;
        }
    }

    void display() {
        setConsoleColor(yellow);
        cout << "\t*Word Puzzle Adventure*\n\n" << endl;
        setConsoleColor(Default);
        cout << "You have to guess the word in this puzzle." << endl;
        cout << "For example, the word in this puzzle can be 'world', 'Efficient', etc." << endl;
        cout << "You can also take help by requesting a hint." << endl << endl;
    }

     void updateScore(int timeTaken) {
        userinfo.setScore(userinfo.getScore()+((100 - timeTaken) * difficultyLevel));
    }

    void gameIntro() override{
        clearScreen();
        cout << "\t\t\t\tWelcome to Word Puzzle Adventure!" << endl;
        cout << "\t\t--------------------------------------------------------------"<<endl <<endl;
        cout << "\t\t   You are an adventurer traveling through the pyramids of Egypt!"<<endl<<endl;
        cout << "\t\tYou were in a Pharaoh's crypt when suddenly the door to the room shuts!"<<endl<<endl;
        cout << "\t\t\tYou see a jumble of words on the wall of the crypt!"<<endl<<endl;
        cout << "\t\t\tTo open the door and get out you must the hidden word!" << endl<<endl;
        cout << "\t\t\tYou have only one try to guess the correct word!" << endl<<endl;
        cout << "Press any key to continue" << endl << endl;
        _getch();
        clearScreen();
    }

};

string getPlayerinfo(){
    string playername;
    cout<<"Enter your name:"<<endl;
    getline(cin,playername);
    cout<<endl;
    return playername;
}

void userInterface() {
    cout<<endl;
    setConsoleColor(yellow);
    cout << "\t-----------------------------------Word Conundrum Solver-------------------------------\n\n" << endl;
    setConsoleColor(Default);

    while(true){
        int gameChoice;
        string name;

        cout << "Enter 1 to embark on an adventure to the world of 'WordLandia'." << endl;
        cout << "Enter 2 to solve 'Word Puzzle Adventure' ." << endl;
        cout  <<"Enter 3 to exit the game."<<endl;
        cout << "Your choice: ";
        cin >> gameChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        if (gameChoice!=3){
        name=getPlayerinfo();

        if (gameChoice == 1) {

            GameOne gameOne(name);
            cout<<endl;
            gameOne.startGame();

        } else if (gameChoice == 2) {

            cout << endl;
            GameTwo gameTwo(name);
            gameTwo.startGame();
        }}
        else {
            cout << "Exiting the program." << endl;
            exit(0);
        }
        int choice;
        cout<<"Would you like to play again?\n4-yes\n5-no"<<endl;
        cin>>choice;
        if(choice!=4){
            cout<<"Thanks for playing:)"<<endl;
            break;
        }
        else{
            continue;
        }


    }
    cout << "\n\n\t----------------------------------------------------------------------------\n\n" << endl;
}

int main() {
    userInterface();

    return 0;
}
