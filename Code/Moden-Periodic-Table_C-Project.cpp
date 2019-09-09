/********************
Modern Periodic Table
**********************/

/**************************************************
******************* DIRECTIVES ********************
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define fileName "elements.csv" // Set file name and path containing elements





/**************************************************
******************** VARIABLES ********************
***************************************************/

// Used when the user chooses a feature / action
int choice;


// Used in For Loops
int i = 0;


// Define a structure for the properties of an element
struct Element_Properties { 
	char name[50], symbol[50], elclass[50];
	int group, atomicNumber;
	float atomicMass, electronegativity, density;
};


// For file I/O
FILE *fp; // Declare file pointer


// For adding new element
struct Element_Properties elementsTable[500], temp; // Used to store the properties of an element
int elementsTable_size = 0; // Used to update size of elementsTable whenever the file is read
char elementArr[10][50]; // Used to hold read lines from elements file before converting to struct


// For searching elements
char sSearch[50], *ptr; // to hold search term/value
int iSearch, found[500], foundCount = 0; // to track which matching results found
float fSearch, range[5]; // array for range to be searched





/**************************************************
******************** FUNCTIONS ********************
***************************************************/
/*****************************
Function to UPPERCASE a STRING
******************************/
void upper_string(char s[]) {
   int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      c++;
   }
}




/****************************
Function to PRINT an element
*****************************/
void printElement( struct Element_Properties element ) {
	printf("Name: %s\n", element.name);
	printf("Symbol: %s\n", element.symbol);
	printf("Atomic Number: %d\n", element.atomicNumber);
	printf("Atomic Mass: %f\n", element.atomicMass);
	printf("Electronegativity: %f\n", element.electronegativity);
	printf("Group Number: %d\n", element.group);
	printf("Class: %s\n", element.elclass);
	printf("Density: %f\n", element.density);
}




/***************************
Functions to ADD NEW ELEMENT
****************************/

/***** ADD the NEW ELEMENT to the FILE *****/
void addToFile( struct Element_Properties element ) {
	
	if (!(fp = fopen(fileName, "r"))) { // If file does not exist, create the file
		fclose(fp);
		
		printf("Creating a file named %s...\n", fileName);
		
		fp = fopen(fileName, "w"); // Create the file, then write("w") the header on it
		fprintf(fp, "Name,Symbol,Atomic Number,Atomic Mass,Electronegativity,Group,Class,Density\n"); // Add header
		fclose(fp);
	}
	
	fp = fopen(fileName, "a"); // Open file to append("a") entry
    
    upper_string(element.name); // Calls the upper_string() function to capitalize the characters within the string
    upper_string(element.symbol);
    upper_string(element.elclass);
    
    fprintf(fp, "%s,%s,%d,%f,%f,%d,%s,%f\n",  
			element.name,
			element.symbol,
			element.atomicNumber,
			element.atomicMass,
			element.electronegativity, 
			element.group,
			element.elclass,
			element.density
			);
    fclose(fp);
}


/**** ADD an element (Primary) *****/
int main();
void addElement() {
	int again = 1;
	do { 
		printf("Enter the properties of the new element. \n(Note: All text entries will be stored in uppercase.)\n\n");
	
		// Let the user input properties
		printf("| Name: ");
		scanf("%s", temp.name);
		
		printf("| Symbol: ");
		scanf("%s", temp.symbol);
		
		printf("| Atomic Number: ");
		scanf("%d", &temp.atomicNumber);
		
		printf("| Atomic Mass: ");
		scanf("%f", &temp.atomicMass);
		
		printf("| Electronegativity: ");
		scanf("%f", &temp.electronegativity);
		
		printf("| Group Number: ");
		scanf("%d", &temp.group);
		
		printf("| Class: ");
		scanf("%s", temp.elclass);
		
		printf("| Density: ");
		scanf("%f", &temp.density);
		
		printf("\n-----------------------------------------------------\n");
		
		// Let the user confirm if the properties are correctly typed		
		printf("Proceed with adding this element?\n");
		printf("| [1] - Yes, add this new element. \n");
		printf("| [2] - No, re-enter information. \n");
		printf("| [3] - No, go back to main screen. \n");
		printf("| Choice: ");
		scanf("%d", &choice);
		printf("\n-----------------------------------------------------\n");
		
		
		switch(choice) {
			/*** Confirmed to ADD the new element ***/
			case 1:
				again = 0;
				
				addToFile(temp); // Append the element properties to the file
				
				printf("Successfully added the element at `%s` file!\n", fileName);
				printf("Going back to main screen...\n");
				
				system("pause");
				main(); // Go back to main screen
				
				break;
			
			/*** RE-ENTER the new element's properties ***/
			case 2:
				again = 1;
				break;
				
			/*** Go BACK to main screen WITHOUT SAVING the new element ***/
			case 3:
				printf("Going back to main screen...\n");
				
				system("pause");
				main();
				break;
				
			/*** If invalid input / input not among the choices ***/
			default:
				printf("Invalid input. Going back to main screen...\n");
				system("pause");
				main();
				break;
		}

	} while(again == 1); // Loop as long as the user wanted to re-enter info 
}




/**************************** 
Functions to SEARCH ELEMENT/S 
*****************************/

/***** Store READ LINE from FILE to STRUCT *****/
void lineToStruct( int lineNum, char line[] ) {
	
	// Get the element properties by splitting the line based on delimiter ","
	char *token; // to be used for strtok() to split the line
	int colNum = 0;
	
	
    token = strtok(line, ","); // First split/token
    while( token != NULL ) { // This iteration is specified on the documentation to get the other splits/tokens
    	strcpy(elementArr[colNum], token); // store token on elementArr
    	colNum++;
    	token = strtok(NULL, ",");
    }
    
        
    // From elementArr store on elements struct
    upper_string(elementArr[0]);
    upper_string(elementArr[1]);
    upper_string(elementArr[6]);
    
    strcpy(elementsTable[lineNum].name, elementArr[0]); // upper_string() converts all characters of string into uppercase, needed string directive
    strcpy(elementsTable[lineNum].symbol, elementArr[1]); // strcpy(a, b) copies string b over string a, needed string directive
    elementsTable[lineNum].atomicNumber = atoi(elementArr[2]); // atoi() converts string to int, needed stdlib directive
    elementsTable[lineNum].atomicMass = atof(elementArr[3]); // atof() converts string to float, needed stdlib directive
    elementsTable[lineNum].electronegativity = atof(elementArr[4]);
    elementsTable[lineNum].group = atoi(elementArr[5]);
    strcpy(elementsTable[lineNum].elclass, elementArr[6]);
    elementsTable[lineNum].density = atof(elementArr[7]);
    
    //printElement(elementsTable[lineNum]);
}


/***** READ FILE *****/
void readFile() {
	printf("Reading file... \n");
	int lineNum = 0;

	char line[1000];

	fp = fopen(fileName, "r"); // open and read("r") file
	fgets ( line, sizeof line, fp ); // read first line and do not store; the first line contains the headers
	
	// read the consequent lines to store the elements to the elementsTable struct
	while ( fgets ( line, sizeof line, fp ) != NULL ) {
		lineToStruct(lineNum, line); // Calls the function to store read line to struct
	    lineNum++;
	}
		
	fclose(fp);	
	
	elementsTable_size = sizeof(elementsTable)/sizeof(elementsTable[0]);
	printf("Total elements in memory: %d\n", elementsTable_size);
}


/***** SHOW FOUND ELEMENTS *****/
void showFound( int found[], int foundCount ) {		
	printf("Searching...");
		
	// Print the search results based on the found array
	if (foundCount > 0) {
		for (i=0; i < foundCount; i++) {
			printf("\n-----------------------------------------------------\n\n");
			printElement(elementsTable[ found[i] ]); // Print the element from the elementsTable using the index stored on found array
		}
		
		printf("\n-----------------------------------------------------\n");
		printf("Found %d element/s!", foundCount);
		
	} else {
		printf("\nNo match found.\n");
	}
}


/***** SEARCH for an element (Primary) *****/
void searchElement(int choice) {
	
	foundCount = 0; // Reset the count of found elements
	
	switch(choice) {
		
		/*** Search by NAME ***/
		case 1:
			// Let the user enter the term/value to be searched	
			printf("| Enter the NAME to be searched: ");
			scanf("%s", sSearch);
			
			// Search for the element
			for (i=0; i < elementsTable_size; i++) {
				upper_string(sSearch);
				ptr = strstr(elementsTable[i].name, sSearch); // strstr() compares two strings
				if (ptr != NULL) { // If the element name contains the search term, add the element's index in the found array
					found[foundCount] = i;
					foundCount++;
				}
			}
			
			break;
		
		/*** Search by SYMBOL ***/
		case 2:
			// Let the user enter the term/value to be searched
			printf("| Enter the SYMBOL to be searched: ");
			scanf("%s", sSearch);
			
			// Search for the element
			for (i=0; i < elementsTable_size; i++) {
				upper_string(sSearch);
				ptr = strstr(elementsTable[i].symbol, sSearch); // strstr() compares two strings
				if (ptr != NULL) { // If the element symbol contains the search term, add the element's index in the found array
					found[foundCount] = i;
					foundCount++;
				}
			}
						
			break;	
		
		
		/*** Search by ATOMIC NUMBER ***/
		case 3:
			// Let the user enter the term/value to be searched	
			printf("| Enter the ATOMIC NUMBER to be searched: ");
			scanf("%d", &iSearch);
			
			// Search for the element
			for (i=0; i < elementsTable_size; i++) {
				if ( (iSearch== elementsTable[i].atomicNumber) && // If the atomic number searching for is found, add the element's index in the found array
					 (strlen(elementsTable[i].name) > 0) ) { // Ensures that the element found is not null 
					found[foundCount] = i;
					foundCount++;
				}
			}
			
			break;
		
			
		/*** Search by ATOMIC MASS ***/
		case 4:
			// Let the user enter the term/value to be searched	
			printf("| Enter the ATOMIC MASS to be searched: ");
			scanf("%f", &fSearch);
			
			// Search for the element
			for (i=0; i < elementsTable_size; i++) {
				if ( (fSearch == elementsTable[i].atomicMass) && // If the atomic mass searching for is found, add the element's index in the found array
					 (strlen(elementsTable[i].name) > 0) ) {   // Ensures that the element found is not null 
					found[foundCount] = i;
					foundCount++;
				}
			}
			
			break;
		
		
		/*** Search by ELECTRONEGATIVITY ***/
		case 5:
			// Let the user enter the term/value to be searched	
			printf("| Enter the ELECTRONEGATIVITY to be searched: ");
			scanf("%f", &fSearch);
			
			// Search for the element
			for (i=0; i < elementsTable_size; i++) {
				if ( (fSearch == elementsTable[i].electronegativity) &&
					 (strlen(elementsTable[i].name) > 0) ) { // If the electronegativity searching for is found, add the element's index in the found array
					found[foundCount] = i;
					foundCount++;
				}
			}
			
			break;
		
		
		/*** Search by GROUP NUMBER ***/
		case 6:
			// Let the user enter the term/value to be searched	
			printf("| Enter the GROUP NUMBER to be searched: ");
			scanf("%d", &iSearch);
			
			// Search for the element
			for (i=0; i < elementsTable_size; i++) {
				if ( (iSearch == elementsTable[i].group) &&
					 (strlen(elementsTable[i].name) > 0) ) { // If the group number searching for is found, add the element's index in the found array
					found[foundCount] = i;
					foundCount++;
				}
			}
			
			break;
		
		
		/*** Search by CLASS ***/
		case 7:
			// Let the user enter the term/value to be searched	
			printf("| Enter the CLASS/CATEGORY to be searched: ");
			scanf("%s", sSearch);
			
			// Search for the element
			for (i=0; i < elementsTable_size; i++) {
				upper_string(sSearch);
				ptr = strstr(elementsTable[i].elclass, sSearch);
				if (ptr != NULL) { // If the element class contains the search term, add the element's index in the found array
					found[foundCount] = i;
					foundCount++;
				}
			}
			
			break;	
		
		
		/*** Search by DENSITY ***/
		case 8:
			// Let the user enter the term/value to be searched	
			printf("| Enter the DENSITY to be searched: ");
			scanf("%f", &fSearch);
			
			// Search for the element
			for (i=0; i < elementsTable_size; i++) {
				if ( (fSearch == elementsTable[i].density) && // If the density searching for is found, add the element's index in the found array
					 (strlen(elementsTable[i].name) > 0) ) {  // Ensures that the element found is not null
					found[foundCount] = i; // Add the element's index in the found array
					foundCount++;
				}
			}
			
			break;
		
			
		/*** Search by RANGE of GROUP NUMBER and DENSITY ***/
		case 9:
			// Let the user enter the values to be searched	
			// then store the range values on the corresponding array
			printf("| Enter the range of GROUP NUMBER \n");
			printf("|  > MIN: ");
			scanf("%f", &fSearch);
			range[0] = fSearch; 
						
			printf("|  > MAX: ");
			scanf("%f", &fSearch);
			range[1] = fSearch;
			
			printf("|\n| Enter range of DENSITY \n");
			printf("|  > MIN: ");
			scanf("%f", &fSearch);
			range[2] = fSearch;		
				
			printf("|  > MAX: ");
			scanf("%f", &fSearch);
			range[3] = fSearch;
			
			// Search for the element
			for (i=0; i < elementsTable_size; i++) {
				if ( (elementsTable[i].group >= range[0] && elementsTable[i].group <= range[1]) &&	// Checks if the group and density of the element
					 (elementsTable[i].density >= range[2] && elementsTable[i].density <= range[3]) &&	// is within the range entered
					 (strlen(elementsTable[i].name) > 0) ) { // Ensures that the element found is not null
					found[foundCount] = i;
					foundCount++;
				}
			}
			
			break;
		
		/*** If invalid input / input not among the choices ***/
		default:
			printf("Invalid input. Going back to main screen...\n");
			
			system("pause"); // Pauses the program until the user presses any key to continue
			system("cls"); // Clears the screen of the console window
			main(); // Go back to main screen
			break;
	}
	
	// Print the search results using the showFound() function
	printf("\n-----------------------------------------------------\n");
	showFound( found, foundCount );
	printf("\n-----------------------------------------------------\n");
}





/**************************************************
*********************** MAIN **********************
***************************************************/

int main() {
	
	system("cls");
	
	printf("\n\n*****************************************************\n*************** MODERN PERIODIC TABLE ***************\n*****************************************************\n\n");
	printf("\n--------------------- WELCOME! ----------------------\n");
	
	printf("Choose an action and enter its corresponding number: \n");
	printf("| [1] - Add New Element \n");
	printf("| [2] - Search for an Element \n");
	printf("| [3] - Exit \n| \n");	
	printf("| Choice: ");
	scanf("%d", &choice);
	
	system("cls"); // Clears the screen of the console window
	
	switch(choice) {
		
		/*** Add element ***/
		case 1:
			printf("\n\n*****************************************************\n*************** MODERN PERIODIC TABLE ***************\n*****************************************************\n\n");
			printf("\n------------------ ADD NEW ELEMENT ------------------\n");
			
			addElement(); // Calls the function for adding an element
			
			break;
		
		/*** Search element ***/
		case 2:
			printf("\n\n*****************************************************\n*************** MODERN PERIODIC TABLE ***************\n*****************************************************\n\n");
			printf("\n------------------- SEARCH ELEMENT ------------------\n");
			
			// Read file and update the elementsTable struct
			readFile();
			
			// Let user choose different options to search
			printf("Searching options: \n");
			printf("| [1] - Name               [6] - Group Number \n");
			printf("| [2] - Symbol             [7] - Class  \n");
			printf("| [3] - Atomic Number      [8] - Density \n");
			printf("| [4] - Atomic Mass        [9] - Group Number and Density \n");
			printf("| [5] - Electronegativity \n|\n");
			printf("| Choice: ");
			scanf("%d", &choice);
			
			printf("|\n");
			
			searchElement(choice); // Calls the function for searching for an element
			system("pause"); // Pauses the program until the user presses any key to continue
			main(); // Go back to main screen
						
			break;
			
		/*** EXIT the program ***/
		case 3:
			printf("Goodbye.\n");
			return 0;
			break;
			
		/*** If invalid input / input not among the choices ***/
		default:
			printf("Invalid input. Going back to main screen...\n");
			
			system("pause"); // Pauses the program until the user presses any key to continue
			system("cls"); // Clears the screen of the console window
			main(); // Go back to main screen
			break;
	}
	
	return 0;
}


