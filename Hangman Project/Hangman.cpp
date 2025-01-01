#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime> // For random seed

using namespace std;

class Hangman {
public:
    vector<string> EasyLevel = {"watch","apple","beach","clock","house"};
    vector<string> MediumLevel = {"picture", "flowers","library","captain","journey"};
    vector<string> HardLevel = {"adventure", "challenge","excitement","motivation","calebration"};
    vector<char> incorrectLetters; 

    void displayHangman(int incorrectGuesses) {
        vector<string> hangmanStages = {
            R"(
   _____
  |     |
        |
        |
        |
        |
  ______|
)",
            R"(
   _____
  |     |
  O     |
        |
        |
        |
  ______|
)",
            R"(
   _____
  |     |
  O     |
  |     |
        |
        |
  ______|
)",
            R"(
   _____
  |     |
  O     |
 /|     |
        |
        |
  ______|
)",
            R"(
   _____
  |     |
  O     |
 /|\    |
        |
        |
  ______|
)",
            R"(
   _____
  |     |
  O     |
 /|\    |
 /      |
        |
  ______|
)",
            R"(
   _____
  |     |
  O     |
 /|\    |
 / \    |
        |
  ______|
)"
        };
        if (incorrectGuesses >= 0 && incorrectGuesses < hangmanStages.size()) {
            cout << hangmanStages[incorrectGuesses] << endl;
        }
    }

    string displayLevelDifficulty() {
        string LevelDifficulty;

        while (true) {
            cout << "Please Select Level: Easy, Medium" << endl;
            cin >> LevelDifficulty;

            string inputLower = LevelDifficulty;
            transform(inputLower.begin(), inputLower.end(), inputLower.begin(), ::tolower);

            if (inputLower == "easy" || inputLower == "medium") {
                cout << "You selected: " << LevelDifficulty << endl;
                return inputLower;
            } else {
                cout << "Invalid selection. Try again." << endl;
            }
        }
    }

    string getRandomWord(const string& difficulty) {
        vector<string> wordList = (difficulty == "easy") ? EasyLevel : MediumLevel;
        int randomIndex = rand() % wordList.size();
        return wordList[randomIndex];
    }

    void displayWord(const string& word, const vector<char>& correctGuesses) {
        for (char c : word) {
            if (c == ' ') {
                cout << "  ";
            } else if (find(correctGuesses.begin(), correctGuesses.end(), c) != correctGuesses.end()) {
                cout << c << " ";
            } else {
                cout << "_ ";
            }
        }
        cout << endl;
    }

    void displayIncorrectLetters() {
        cout << "\nIncorrect Letters: ";
        for (char c : incorrectLetters) {
            cout << c << " ";
        }
        cout << endl;
    }

    void PlayGame() {
        string difficulty = displayLevelDifficulty();
        string selectedWord = getRandomWord(difficulty);
        vector<char> correctGuesses;
        int incorrectGuesses = 0;
       

        while (incorrectGuesses < 7) {
            cout << "\nYour Word to Guess: " << endl;
            displayWord(selectedWord, correctGuesses);

            displayHangman(incorrectGuesses);
            displayIncorrectLetters();

            cout << "\nGuess a letter: ";
            char guess;
            cin >> guess;
            guess = tolower(guess); // Normalize to lowercase

            if (selectedWord.find(guess) != string::npos) {
                if (find(correctGuesses.begin(), correctGuesses.end(), guess) == correctGuesses.end()) {
                    correctGuesses.push_back(guess);
                } else {
                    cout << "You already guessed that letter!" << endl;
                }
            } else {
                if (find(incorrectLetters.begin(), incorrectLetters.end(), guess) == incorrectLetters.end()) {
                    incorrectLetters.push_back(guess);
                    incorrectGuesses++;
                } else {
                    cout << "You already guessed that incorrect letter!" << endl;
                }
            }

            // Check for win condition
            bool wordGuessed = true;
            for (char c : selectedWord) {
                if (c != ' ' && find(correctGuesses.begin(), correctGuesses.end(), c) == correctGuesses.end()) {
                    wordGuessed = false;
                    break;
                }
            }

            if (wordGuessed) {
                cout << "\nCongratulations! You guessed the word: " << selectedWord << endl;
                system("pause");
                return;
            }
        }

        cout << "\nGame Over! The word was: " << selectedWord << endl;

        system("pause");
    }
};

int main() {
    //srand(static_cast<unsigned>(time(0))); // Seed the random number generator
    Hangman game;
    game.PlayGame();
    return 0;
}
