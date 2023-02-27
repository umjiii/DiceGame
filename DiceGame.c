/*
Author: Stephen Arel
Class: CSC 240
Assignment: DiceGame
Description:   Turns are taken using the playerTurn() method, and two dice are rolled. If snake-eyes (1 & 1) are rolled,
            then add 25 points to that player. If they roll doubles otherwise, then add points equal to twice the number of the two
            dice rolls summed. Otherwise, just add the points equal to the sum of the two rolls to the current player's point total.
            If they roll only a single one, then their turn ends, their score is turned to 0, and it is the next player's turn.
            Keep switching turns between players, and calculating points until one of the players reaches a score of at least 100. Then,
            then game ends.
*/
#include <stdio.h>
#include <stdlib.h> //NULL constant, srand(), & rand() functions
#include <time.h> //access your computer's clock time

/*------------ variables ------------*/
static int diceOne;
static int diceTwo;
static int p1Points;
static int p2Points;
static char again;
int turnCount = 0;
int one = 0;

static int playerNum;
struct die;
time_t t;

//pointers
int* pdo = &diceOne;
int* pdt = &diceTwo;

int* pPlay1 = &p1Points;
int* pPlay2 = &p2Points;

//declare methods used
void rollDice();
int calcPoints(int* pdo, int* pdt);
void playerTurn();

/*------------ main ------------*/
int main(){

 //initialize random number generator
 srand((unsigned) time(&t)); //seed is computer time to "randomize" as much as possible

 playerTurn();

 return 0; //terminate process
}


/*------------ methods (defined) ------------*/

//player turn
void playerTurn()
{
    one = 0; //is
    if(turnCount == 0) //if this is the first turn. if it is, don't add any new lines (spaces).
    {
        printf("Player 1 score: %d\nPlayer 2 score: %d\n+========================================+\n", *pPlay1, *pPlay2);
    }
    else //not the first turn, add a space between lines.
    {
        printf("\nPlayer 1 score: %d\nPlayer 2 score: %d\n+========================================+\n", *pPlay1,
               *pPlay2);
    }
        do { //do/while loop to roll the dice until the user decides to end the turn (again != 'Y' || 'y')
            rollDice();
            if (*pdo != *pdt && (*pdo == 1 || *pdt ==1)) { //is only one of the dice are equal to 1
                *pPlay1 = 0; //score is now equal to 0
                again = 'n'; //don't roll again

            }
            else
                *pPlay1 += calcPoints(pdo, pdt); //if only one of dice are not 1, then calculate points based on dice.

            printf("Player 1 rolls %d and %d. Your total for this turn is %d.",*pdo, *pdt, *pPlay1); //display the dice rolls and points for player 1.

            if (*pPlay1 != 0) //if the score is not 0 (if only one of the dice are not 1)
            {
                printf("\n\tDo you want to roll again (Y/N)?");
                scanf(" %c", &again);
            }

            printf("\r\n"); //new lines to improve readability

            //player 1 do/while is identical to player 2 with minor changes.

        } while (again == 'Y' | again =='y');

        do {
            rollDice();
            if (*pdo != *pdt && (*pdo == 1 || *pdt ==1)) {
                *pPlay2 = 0;
                again = 'n';
                one = 1; //if the turn for player 2 is over, return a binary boolean 1.
            }
            else
                *pPlay2 += calcPoints(pdo, pdt);

            if(one == 1) //if the turn for player 2 is over, then add a space after the score and rolls are displayed.
            {
                printf("\nPlayer 2 rolls %d and %d. Your total for this turn is %d.\n",*pdo, *pdt, *pPlay2);
            }
            else //if not, then don't add a space but still display the rolls and turn score.
               printf("\nPlayer 2 rolls %d and %d. Your total for this turn is %d.",*pdo, *pdt, *pPlay2);

            if (*pPlay2 != 0)
            {
                printf("\n\tDo you want to roll again (Y/N)? ");
                scanf(" %c", &again);
            }

        } while (again == 'Y' | again =='y');

        if (*pPlay1 < 100 || *pPlay2 < 100) //if one of the players have not reached a score of at least 100, then keep taking turns (recursively)
        {
            turnCount++; //return the count of turns for the purpose of deciding whether it is the first turn or not.
            playerTurn();
        }
}

//calcPoints - returns value given dice numbers
int calcPoints(int* pdo, int* pdt)
{
    if (*pdo == *pdt && *pdo == 1) //if double-ones
        return 25; //add 25 points

    else if(*pdo == *pdt) //if rolling doubles but not ones, then return double the number rolled between the two dice
        return 2 * (*pdt + *pdo);

    else
        return *pdo + *pdt; //return the points as the sum of the numbers rolled between each die
}

//rollDice ------ pointers passed to assign random numbers to the value of their addresses
void rollDice()
{
    //1 added to exclude 0. 5 chosen as max such that adding one creates a max value of 6.
    *pdt = 1 + (rand() % 5);
    *pdo = 1 + (rand() & 5);
}