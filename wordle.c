


#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct announcement{
	char ending1[20];
  char ending2[20];
}announcement;
	

void secretshh(char *secretWord); //random word selector
int startup(void); //prints starting messages
void guess(char *currentGuess, int numGuesses); //stores user's guess
void evaluation(char *green, char * yellow, char *secretWord, char *guessList, int numGuesses); //checks for correct letters
int printing(char *green, char *yellow, char *guessList, int numGuesses); //prints out word

int main(){
	//compile with gcc FinalProject.c -o FinalProject
	//run with ./FinalProject < words.txt
	
	char secretWord[6]; //Initializing the secret word

  announcement message; //Initializes the structure
  
  strcpy(message.ending1, "YOU WIN!!");  //assigns the arrays within the function
  strcpy(message.ending2, "YOU LOSE!!");

  
	secretshh(secretWord); //calling function to import txt file and randomly select a word
	
	int duckies = startup(); //calls function that prints the introductory message
	
	char *guessList = calloc(30, sizeof(char)); //dynamically allocates a guess list for user's words
	
	int numGuesses = 0;
	
	int end = 0;
	
	int g;
	
	char *green= calloc(30, sizeof(char)); //dyanmically allocates an array for correct letters in correct spaces
	char *yellow= calloc(30, sizeof(char)); //dyanmically allocates an array for correct letters in incorrect spaces
	
	while(end == 0){
		
		guess(guessList, numGuesses); //calls function to store the next guess
		
		evaluation(green, yellow, secretWord, guessList, numGuesses); //evaluates the user's guess
		
		end = printing(green, yellow, guessList, numGuesses); //prints the line
    
    numGuesses += 1; //counts how many times user has made a guess
	}
	
	if(end == 1){ //announces winning condition
		
		printf("\n_______________________________________\n");
		printf("\n%s\n", message.ending1);
	}
	else if(end ==2){ //announces losing condition
		printf("\n_______________________________________\n");
		printf("\n%s\n", message.ending2);
		printf("\nThe secret word was %s.\n", secretWord);
	}
		
	return 0;
}

///////////////////////////////////////
//User Defined Functions' Definition//
/////////////////////////////////////
void secretshh(char *secretWord){
	FILE* ptr; //ptr to a file variable
	
	if((ptr = fopen("words.txt", "r"))==NULL){ //opens the file and checks if it was opened
		printf("Error reading file.");
	}
	
	char c; //temporary character variable
	
	int counter = 0;
	
	for (int g = getc(ptr); g != EOF; g = getc(ptr)){
		
		counter +=1; //finds number of characters within the file
	}
	
	char *words = calloc((counter+1), sizeof(char));  //dynamically allocates memory of array
	
	for(int j =0; j<counter; j++){ 
	
	fscanf(ptr, "%c", &c); //scans where cursor is on txt file
	
	fseek(ptr, j, SEEK_SET); //moves cursor to the next spot
	
	words[j]=c; //assigns the temporary character to the words array
	}
	
	words[counter+1]='\0'; //assigns the last value in the array to null
	
	fclose(ptr); //closes the file
	
	srand(time(NULL)); //initializing random
		
	int randy = rand() % 5757 * 6; //selects random line
		
	
	for(int i = 0; i < 5; i++){ //sets the secret word 
		secretWord[i] = words[(randy) + i+1];
	}
	secretWord[5] = '\0';
}	

int startup(void){
	
	char userQuestion;
	char userQuestion2;
	
	int duckies = 0;

	printf("\n_______________________________________\n");
	printf("\nWelcome to Wordle! \nWould you like to hear the rules? \nEnter y for yes or n for no.\n");
	
	while(1){
		scanf(" %c", &userQuestion); //scans keyboard for user input
		
		if((userQuestion != 'y') && (userQuestion != 'n')){ //checks if its a valid entry
			
			printf("\n_______________________________________\n");
			printf("\nInvalid Entry, please enter y for yes and n for no\n");
			
			
			continue; //starts the line of questioning again
			
		}
		break; //breaks out of loop since user put in a valid entry
	}
	
	if(userQuestion == 'y'){  //tests whether or not rules should be shown
	
		printf("\n_______________________________________\n");
		printf("\nYou'll have 6 attempts to correctly guess a random 5 letter word. ");
		printf("\nEnter a guess and press enter when done.\nYour guess will be displayed. ");
		printf("\nBoxed letters show you guessed a correct letter in a correct spot.");
		printf("\nUnderlined letters show a correct letter in an incorrect spot.\n");
		
	}
	
	printf("\n_______________________________________\n");
	printf("\nAre you ready to play?");
	printf("\nEnter y for yes or n for no.\n");
	
	while(1){	
		
		scanf(" %c", &userQuestion2); //scans keyboard for user input
		
		if((userQuestion2 != 'y') && (userQuestion2 != 'n')){ //checks if its a valid entry
				
			printf("\n_______________________________________\n");
			printf("\nInvalid Entry, please enter y for yes and n for no\n");
			
			continue; //starts the line of questioning again
				
		}
	
		if(userQuestion2 == 'n'){  //tests whether or not user is ready
		
			duckies += 1;
			
			printf("\n_______________________________________\n");
			printf("\nA nearby duck joined you for support.");
			for(int i =0; i < duckies; i++){ //ducky display
				
				//print duckies
				printf("\n               __\n             <(o )___\n              ( ._> /\n               `---'  \n"); 
			}
			printf("\nAre you now ready?\n");
			
			continue; //starts line of questioning again
		}
		break; //breaks out of loops since user is ready
	}
	
	printf("\n_______________________________________\n");
	printf("\nGOOD LUCK!");
	printf("\n");
	return duckies;
}

void guess(char *guessList, int numGuesses){
	
	int invalid = 0;
	
	int startingVal = numGuesses * 5;
	
	char temp[6];
	
	int g;
	
	while(invalid == 0){ //runs until a valid guess is made
		
		invalid = 1;
		
		printf("\n_______________________________________\n");
		printf("\nEnter your guess.\n");
		printf("\n\n");
		
		scanf("%s", temp); //takes in guess to an array
		for(int i = 0; i < 5; i++){
			if((isalpha(temp[i]) == 0) || (strlen(temp)!=5)){ //checks to see if the input contained 5 alphabet characters
				
				invalid = 0; //sets conditional to run the loop again 
			}
			
		}

		if(invalid ==0){ //runs if the entry was invalid
			
		printf("\n_______________________________________\n");
		printf("\nInvalid entry.\nPlease type a 5 letter word.\n");
		printf("\n\n");
		
		}
	}
	for(int i = 0; i< 5; i++){ 
		g = startingVal+i;
		guessList[g] = temp[i]; //set temp into guessList
	}
	g=startingVal+5;
	guessList[g] = '\0';
}

void evaluation(char *green, char *yellow, char *secretWord, char *guessList, int numGuesses){
  
	int g;

	for(int i = 0; i < 5; i++){ //loop iterated for each letter of guessed word
    
		g = numGuesses * 5 + i;
    
		if(guessList[g] == secretWord[i]){ //checking for a correct letter in correct spot

			green[g] = 't'; //set the green item to true 
		}
		else{
			green[g] = 'f';
		}
			
		for(int j = 0; j < 5; j++){
			if((guessList[g] == secretWord[j]) && (guessList[g] != secretWord[i])){ //checking for a correct letter in wrong spot

				yellow[g] = 't';//set the yellow item to true 
        break;
			}
			else{
				yellow[g] = 'f';
		}
		}
	}
}

int printing(char *green, char *yellow, char *guessList, int numGuesses){
	int end = 0;
	int g;
	int i;
  char c;
	for(int j = 0; j < (numGuesses + 1); j++){
		
		for(int i = 0; i < 8; i++){ //prints indent
			
			printf(" ");
		}
		
		
		for(int i = 0; i < 5; i++){
			g = j * 5 + i;
      
			if(green[g] == 't') { //turns font green and prints letter if green value is true
			
				printf(" ");
				printf("\e[32;1m%c", toupper(guessList[g]));
				printf("\e[0;1m ");
			}
			
			else if(yellow[g] == 't'){ //turns font yellow and prints letter if yellow value is true
			
				printf(" ");
				printf("\e[33;1m%c", toupper(guessList[g]));
				printf("\e[0;1m ");
			}
				
			else{ //prints letter if not green or yellow
			
				printf(" ");
				printf("%c", toupper(guessList[g]));
				printf(" ");
			}
		}
		
		printf("\n\n");
	}

  //check for winning and losing conditions
	if((green[numGuesses * 5] == 't') && (green[numGuesses * 5 + 1] == 't') && (green[numGuesses * 5 + 2] == 't') && (green[numGuesses * 5 + 3] == 't') && (green[numGuesses * 5 + 4] == 't')){
		end = 1;
	}
	else if(numGuesses == 5){
		end = 2;
	}
	return end;
}