/*Yjang Wynter
 *Project 7
 */

//Replace or modify header to include your information


//pre-processor directives
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Function Prototypes - do not change these
void greeting();

void setParameters(int * length, int * difficulty);

int * createHideList(int length, int difficulty);

int * createShowList(int length);

void display(int showlist[], int length);

void getGuess(int guess[], int length);

void processGuess(int hidelist[], int showlist[], int length, int guess[]);

int solved(int hidelist[], int guess[], int length);

int PerfectMatches(int hidelist[], int guess[], int length);

int ImperfectMatches(int hidelist[], int guess[], int length);

void copyArray(int dest[], int source[], int length);

//Main function - This is the final version of main.  Any changes you make while
//creating the functions should be removed prior to submission.
int main() {

    //Length determines the number of hidden values that must be guessed
    //Difficulty determines the range of the hidden values
    int length, difficulty;

    //Answer, revealed, and guess are all integer arrays
    //Since length is undefined at this point, no sizes have been assigned.
    //This will be done in the create...List functions.
    //Answer is the correct answer of the hidden values
    //Revealed is the list that is shown to the user
    //Guess is the user's guess
    int * answer, * revealed, * guess;

    //seed the random number generator
    srand(time(0));

    //Begin the program by showing the initial greeting to the user
    greeting();

    //Ask the user for the length and difficulty
    setParameters(&length, &difficulty);

    //Create the initial arrays of size length
    answer = createHideList(length, difficulty);
    revealed = createShowList(length);
    guess = createShowList(length);

    printf("\nThere are %d numbers ranging from 1 to %d.\n\n", length, difficulty*3);

    //Loop until the user solves the puzzle
    while (!solved(answer, guess, length)) {
        //Show the information gathered so far and prompt the user for their next guess
        display(revealed, length);
        getGuess(guess, length);
        processGuess(answer, revealed, length, guess);
    }

    printf("Congratulations! You guessed all the values!\n\n");


    //These functions are necessary because we are using memory allocation functions in create...List
    free(answer);
    free(revealed);
    free(guess);

    return 0;
}

//Functions
//Pre-conditions:  none
//Post-conditions: Prints a welcome message to the screen
void greeting() {
    printf("Welcome to Codebreaker Training!\n\n");
    printf("You will be presented with a set of hidden values.  Your job is to guess these\n");
    printf("values and their correct order. After each guess you will be given feedback.\n\n");
    printf("Values that are correct in magnitude and in the correct location\nwill be revealed.  These are ");
    printf("perfect matches.\n\nThen you will be told how many other numbers are correct in magnitude only.\n");
    printf("These are imperfect matches. No additional information will be revealed.\n\n");
    return;
}

//Pre-conditions:  length and difficulty are valid values established by the setParameters function
//Post-conditions: create an array of size length and populate it with random
//                 values based on the difficulty
int * createHideList(int length, int difficulty) {
    //i is a counter
    //array is an integer array, allocated "length" integers
    int i;
    int * array = (int *)malloc(sizeof(int) * length);

    //traverse the valid indices of the array
    //assign each index a random value from 1 - difficulty*3
    for(i=0; i<length; i++)
        array[i] = rand() % (difficulty*3) + 1;

    //return the beginning of the array to the main function
    return array;
}

//Pre-conditions:  length has a valid value established by the setParameters function
//Post-conditions: create an array of size length and initialize to zero
int * createShowList(int length){
    //i is a counter
    //array is an integer array, allocated "length" integers
    int i;
    int * array = (int *)malloc(sizeof(int) * length);

    //traverse the valid indices of the array
    //assign each index an initial value of 0
    for(i=0; i<length; i++)
        array[i] = 0;

    //return the beginning of the array to the main function
    return array;
}

//Pre-conditions:  length and difficulty are integer pointers
//Post-conditions: length and difficulty will be set by the user
//                 Function should verify that these values are valid

//What to do in this function: Prompt the user for the length of the code.  Remember
//that the parameter length is a pointer, so it cannot store an integer value.  You may need additional
//variables.  Ensure that the user gives you a value between 5 and 10, inclusive.  If their
//value is invalid, continue to prompt them until they provide a valid one.  Assign this value to the location
//that length is pointing at.  Repeat this process for the difficulty parameter.  Difficulty
//must be 1, 2, or 3 to continue.
void setParameters(int * length, int * difficulty) {
int tempVar;

//prompting user for length
printf("Choose a length for the code (5-10 numbers).\n");

scanf("%d", &tempVar);
//while loop statement to validate whether input is between 5-10 inclusive
    while (tempVar > 10 || tempVar< 5){
        printf("Choose a length for the code (5-10 numbers).\n");

        scanf("%d", &tempVar);
    }
    *length = tempVar;

//while loop statement to validate whether input is between 1,2, or 3
printf("Choose a difficulty (1, 2, or 3).\n");

scanf("%d", &tempVar);

    while (tempVar < 1 || tempVar> 3){

        printf("Choose a difficulty (1, 2, or 3).\n");

        scanf("%d", &tempVar);
    }
    *difficulty = tempVar;

//Find out how to return values from void functions
}

//Pre-conditions:  showlist is an integer array of size length
//Post-conditions: displays the contents of showlist using - for 0

//What to do in this function: Traverse the showlist array and print a - whenever the value is 0
//If the value is not zero, print the actual value.  For example, if the code is 12311 and the
//user has identified the location of the 1s, the showlist/revealed array will contain 10011
//and you should display 1--11
void display(int showlist[], int length) {
int i;// delcare index counter

    for (i = 0; i<length; i++){

        if (showlist[i] == 0){
            //Printing the dashes
            printf("-");

            } else {
                // Prints regular numbers
                printf("%d",showlist[i]);
            }

    }
    //A space so the promt is not too close to result
    printf(" ");

}

//Pre-conditions:  guess is an integer array of size length
//Post-conditions: reads in the guess from a user as a string and converts it to an integer array

//What to do in this function: The user will enter their values all together.  For example: 12311
//Read this in as a string and then store each individual integer value in the guess array.
//Since the elements of the input will be characters, you will need to convert to integers.  For example
//you  would need to convert from '1' to 1. Character representations of digits start with '0' with ASCII value 48.
void getGuess(int guess[], int length) {
    int i;// Delcare index counter

   char str[10];
   //string character with the ma length necessary for all scenarios

   printf("Enter your guess: ");

    scanf("%s", &*str);

   for(i=0; i < length; i++){

        guess[i] = str[i] - '0';
        //ASCII value of 48

    }

}

//Pre-conditions:  both hidelist and guess are integer arrays of size length
//                 hidelist represents the answer the user is looking for
//                 guess represents the user's current guess
//Post-conditions: determines if the user has found all of the hidden values

//What to do in this function: Traverse the arrays and check to see if all of the values
//in hidelist are the same as the values in guess.  If they are return 1 for true,
//return 0 for false otherwise.
int solved(int hidelist[], int guess[], int length) {
// Declare index counter
int i;

    for (i =0; i < length; i++){

        if (guess[i] == hidelist[i]){
        //if equal true, else false
           return 1;

        } else {

            return 0;
        }
    }

}

//Pre-conditions:  hidelist, showlist, and guess are integer arrays of size length
//                 hidelist represents the answer the user is looking for
//                 showlist shows the values the user has already discovered
//                 guess is the user's current guess
//Post-conditions: evaluates the current guess and updates showlist

//What to do in this function: Compare hidelist to guess.  If any values match exactly,
//update the showlist to reflect the information the user has discovered.  Then, print out
//the number of perfect matches the user has by calling the PerfectMatches function.  Print
//out the number of imperfect matches the user has by calling the ImperfectMatches function.
//Use the statement from the samples for your printf control string.
void processGuess(int hidelist[], int showlist[], int length, int guess[]) {
int i;
    for (i = 0 ; i < length; i++){

        if (guess[i] == hidelist[i]){

        showlist[i] = hidelist[i];
            }
        }
   printf("You have %d perfect matches and %d imperfect matches.\n", PerfectMatches(hidelist, guess, length), ImperfectMatches(hidelist, guess, length) );

}

//Pre-conditions:  hidelist and guess are integer arrays of size length
//                 hidelist represents the answer the user is looking for
//                 guess is the user's current guess
//Post-conditions: evaluates the current guess and returns the number of perfect matches

//What to do in this function: Compare hidelist to guess. Return the number of times
//the value in guess exactly matches the corresponding value in hidelist.
int PerfectMatches(int hidelist[], int guess[], int length) {
    int i, perfect=0;

    for (i=0; i< length; i++){

        if (hidelist[i]==guess[i]){
            perfect++;
            // a simple counter for the perfect matches per run

            }
        }
    return perfect;

}

//Pre-conditions:  hidelist and guess are integer arrays of size length
//                 hidelist represents the answer the user is looking for
//                 guess is the user's current guess
//Post-conditions: evaluates the current guess and returns the number of imperfect matches

//What to do in this function: Create temporary copies of both arrays by calling the copyArray function
//twice.  This is necessary because we'll need to make changes to both arrays without modifying the
//originals.  Mark out the spots on the arrays that match exactly.  They will be counted in the perfect
//matches instead.  Use any value that won't be present in the hidelist.

//Go through the hidelist array and look for matches in the guess array.  Anytime a value matches,
//regardless of location, count it as an imperfect match and mark it so it won't get counted again.

//Return the number of imperfect matches
//Hint: you will need a nested for loop.
int ImperfectMatches(int hidelist[], int guess[], int length) {
// variables
   int i, j, imperfect = 0, hidelistTemp[length], guessTemp[length];
        //Copies the 2nd variable in params to 1st variable in params for both temp vars
   copyArray(hidelistTemp, hidelist, length);
   copyArray(guessTemp, guess, length);


    for (i = 0; i <length; i++){
        //
        if (hidelistTemp[i] == guessTemp[i]){
            // -100 is impossible for this program to read as as valid
            hidelistTemp[i] =  -100;
            guessTemp[i] = -100;



 //nested loop 2: find imperfect matches
     for(i = 0; i < length; i++){

        for(j=0; j < length; j++){

            if(guessTemp[i] != -100 &&  guessTemp[i] == hidelistTemp[j] && i != j ){
            //prevents impsosible answers and makes sure not the same indices and are equal for both loops
                imperfect++;
                // sets temp var index to an impossible value so computer does not repeat itself
                hidelistTemp[j] = -100;
                }

            }
        }
    }
}


    return imperfect;

}

//Pre-conditions:  dest and source are integer arrays of size length
//                 source represents a source array: an array to be copied
//                 dest represents a destination array: the location of the copy
//Post-conditions: dest will contain a copy of source

//What to do in this function: traverse the source array and copy each element into
//the corresponding location of the destination array
void copyArray(int dest[], int source[], int length) {
int i;

   for(i=0; i < length; i++){
//sets the destination array to source value
        dest[i] = source[i];

   }

}
