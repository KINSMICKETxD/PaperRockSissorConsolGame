#include <iostream>
using namespace std;

enum enChoices { Stone = 1, Paper = 2, Scissors = 3 };
enum enColors {Red=1,Green=2,Yellow=3};
enum enRoundWinner{player=1,computer=2,draw=3};

struct stRoundDetails
{
    short roundNumber;
    enChoices playerChoice;
    enChoices computerChoice;
    enRoundWinner roundWinner;
    string winnerName;

};
struct stGameResult
{
    short gameRounds;
    short playerWinCount;
    short computerWinCount;
    short drawTime;
    string finalWinner;
};

string getWinnerName(int index) {
    string names[3] = { "[player]","[computer]","[No Winner]" };
    return names[index - 1];
}
string choiceName(int index) {
    string choices[3] = { "Stone","Paper","Scissors" };
    return choices[index - 1];
}
enRoundWinner whoIsTheRoundWinner(stRoundDetails roundDetails) {
    if (roundDetails.playerChoice == roundDetails.computerChoice) {
        return enRoundWinner::draw;
    }
    switch (roundDetails.computerChoice)
    {
    case enChoices::Paper:
        if (roundDetails.playerChoice == enChoices::Stone) {
            return enRoundWinner::computer;
        }
        break;
    case enChoices::Scissors:
        if (roundDetails.playerChoice == enChoices::Paper) {
            return enRoundWinner::computer;
        }
        break;
    case enChoices::Stone:
        if (roundDetails.playerChoice == enChoices::Scissors) {
            return enRoundWinner::computer;
        }
        break;
    }
    return enRoundWinner::player;

}
int readAPositiveNumber(string message) {
    int number = 0;
    do {
        cout << message << endl;
        cin >> number;
    }while (number <= 0);
    return number;
}
enChoices readPlayerChoice() {
    int choice;
    cout << "Your Choice:[1]:Stone, [2]:Paper, [3]:scissors ?\n";
    cin >> choice;
    return (enChoices)choice;
}
enChoices readComputerChoice(int from, int to) {
    int number = rand() % (to - from + 1) + from;
    return (enChoices)number;
}
stRoundDetails fillInRoundDetails(int roundNumber) {
    stRoundDetails roundDetails;
    roundDetails.roundNumber = roundNumber;
    roundDetails.playerChoice = readPlayerChoice();
    roundDetails.computerChoice = (enChoices)readComputerChoice(1, 3);
    roundDetails.roundWinner = whoIsTheRoundWinner(roundDetails);
    roundDetails.winnerName = getWinnerName((int)roundDetails.roundWinner);
    return roundDetails;
}
void printRoundDetails(stRoundDetails roundDetails) {
    cout << "_______________Round[" << roundDetails.roundNumber << "]______________\n";
    cout << endl;
    cout << "Player1 Choice  :" << choiceName(roundDetails.playerChoice) << endl;
    cout << "Computer Choice :" << choiceName(roundDetails.computerChoice) << endl;
    cout << "Round Winner    :" << getWinnerName(roundDetails.roundWinner) << endl;
    cout << endl;
    cout << "_____________________________________\n";
}
string getGameWinner(int playerWonCount,int computerWonCount) {
    if (playerWonCount == computerWonCount) {
        return "No winner";
    }
    else if (playerWonCount > computerWonCount) {
        return "Player";
    }
    else {
        return "computer";

    }
}
stGameResult fillInGameResult(int roundCount, int playerWonCount, int computerWonCount, int drawTime) {
    stGameResult gameResult;
    gameResult.gameRounds = roundCount;
    gameResult.computerWinCount = computerWonCount;
    gameResult.playerWinCount = playerWonCount;
    gameResult.drawTime = drawTime;
    gameResult.finalWinner = getGameWinner(playerWonCount, computerWonCount);
    return gameResult;
}
string tabs(int x) {
    string t = "";
    for (int i = 0; i <x ; i++) {
        t += "\t";
    }
    return t;
}
void printGameResult(stGameResult gameResult) {
    cout << tabs(3) << "_______________________[Game Result]_______________________\n";
    cout << tabs(3) << "Game Rounds         : " << gameResult.gameRounds << endl;
    cout << tabs(3) << "Player won times    : " << gameResult.playerWinCount << endl;
    cout << tabs(3) << "Computer won Times  : " << gameResult.computerWinCount << endl;
    cout << tabs(3) << "Draw Times          : " << gameResult.drawTime << endl;
    cout << tabs(3) << "Final Winner        : " << gameResult.finalWinner << endl;
    cout << endl;
    cout << tabs(3) << "___________________________________________________________\n";
}
void printGameOver() {
    cout << endl;
    cout << tabs(3) << "____________________________________________\n";
    cout << endl;
    cout << tabs(5) << "+++ G a m e  O v e r +++";
    cout << endl;
    cout << tabs(3) << "____________________________________________\n";
    cout << endl;
}
stGameResult playAGame(int roundNumber) {
    int playerWonCount = 0;
    int computerWonCount = 0;
    int drawTime = 0;
    stRoundDetails roundDetails;
    for (int i = 1; i <= roundNumber; i++) {
        roundDetails = fillInRoundDetails(i);
        if (roundDetails.roundWinner == enRoundWinner::computer) {
            computerWonCount++;
        }
        else if (roundDetails.roundWinner == enRoundWinner::player) {
            playerWonCount++;
        }
        else {
            drawTime++;

        }
        printRoundDetails(roundDetails);
    }
    return fillInGameResult(roundNumber, playerWonCount, computerWonCount, drawTime);
}
void resetScreen() {
    system("cls");
    system("color 0F");
}
void startGame() {
    char yn = 'Y';
    do {
        resetScreen();
        int roundNumber = readAPositiveNumber("please enter how many round?");
        stGameResult GameResult = playAGame(roundNumber);
        printGameOver();
        printGameResult(GameResult);
        cout << endl;
        cout<<tabs(3) << "Do you want to play again Y/N?";
        cin >> yn;
    } while (toupper(yn) == 'Y');
}
int main()
{
    srand((unsigned)time(NULL));
    startGame();
    
    return 0;
}
