#include <stdio.h>
#include <stdlib.h> //NULL constant, srand(), & rand() functions
#include <time.h> //access your computer's clock time

/*------------ variables ------------*/
static int diceOne;
static int diceTwo;
static int p1Points;
static int p2Points;
static char again;

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

 printf("Player 1 score: %d\nPlayer 2 score: %d", *pPlay1, *pPlay2);

 return 0;

}


/*------------ methods (defined) ------------*/

//player turn
void playerTurn()
{
    printf("Player 1 score: %d\nPlayer 2 score: %d\n+========================================+\n", *pPlay1, *pPlay2);
        do {
            rollDice();
            if (*pdo != *pdt && (*pdo == 1 || *pdt ==1)) {
                *pPlay1 = 0;
                again = 'n';
            }
            else
                *pPlay1 += calcPoints(pdo, pdt);

            printf("Player 1 rolls %d and %d. Your total for this turn is %d.",*pdo, *pdt, *pPlay1);

            if (*pPlay1 != 0)
            {
                printf("\n\tDo you want to roll again (Y/N)?");
                scanf(" %c", &again);
            }

            printf("\r\n");

        } while (again == 'Y' | again =='y');

        do {
            rollDice();
            if (*pdo != *pdt && (*pdo == 1 || *pdt ==1)) {
                *pPlay2 = 0;
                again = 'n';
            }
            else
                *pPlay2 += calcPoints(pdo, pdt);

            printf("Player 2 rolls %d and %d. Your total for this turn is %d.",*pdo, *pdt, *pPlay2);

            if (*pPlay2 != 0)
            {
                printf("\n\tDo you want to roll again (Y/N)? ");
                scanf(" %c", &again);
            }

            printf("\r\n");
        } while (again == 'Y' | again =='y');

        if (*pPlay1 < 100 || *pPlay2 < 100)
        {
            playerTurn();
        }
}

//calcPoints - returns value given dice numbers
int calcPoints(int* pdo, int* pdt)
{
    if (*pdo == *pdt && *pdo == 1) //if double-ones
        return 25;

    else if(*pdo == *pdt)
        return 2 * (*pdt + *pdo);

    else
        return *pdo + *pdt;
}

//rollDice ------ pointers passed to assign random numbers to the value of their addresses
void rollDice()
{
    //1 added to exclude 0. 5 chosen as max such that adding one creates a max value of 6.
    *pdt = 1 + (rand() % 5);
    *pdo = 1 + (rand() & 5);
}