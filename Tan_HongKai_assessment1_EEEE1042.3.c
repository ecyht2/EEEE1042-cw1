#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define N 50

int counting(int type, char * fileName){
  //Declaring Variables
  FILE * F;
  int counter = 0;
  char word[N];

  /* Type 1 gets the number of lines and type 2 gets the number of words */
  if((F=fopen(fileName, "r")) != NULL){
    // Logic for type 1
    if(type == 1){
      //Add one to counter if the character is a newline
      while((word[0] = fgetc(F))!= EOF){
        if(word[0] == '\n') counter++;
      }
    } else if(type == 2){ //Logic for type 2
      //Adding one to counter for each word until end of file
      while(fscanf(F, "%s", word) != EOF) counter++;
    }
    //Closing the file
    fclose(F);
  } else printf("No such file %s", fileName);

  //returning counter
  return counter;
}

int array_max(int array[], int nData, double scale){
  //Setting intial value
  int cMax = 0;

  //Lopping over all the values in the array
  for(int i = 0; i < nData; i++){
    //Making it the new max if it is greater than the current max value
    if(array[i]/scale > cMax) cMax = array[i]/scale;
  }

  return cMax;
}

void scan_file(char * fileName, char words[][N]){
  //Declaring Variables
  FILE * F;
  int counter = 0;

  if((F=fopen(fileName, "r")) != NULL){
    //Scan each word until EOF
    while((fscanf(F, "%s", words[counter])) != EOF) counter++;

    //Closing the file
    fclose(F);
  } else printf("No such file %s", fileName);
}

void find_char_length(int nWord, char data[][N], int data_length[]){
  //Looping over every word in array
  for(int i = 0; i < nWord; i++){
   // Setting the string length for the specific word
    data_length[i] = strlen(data[i]);
  }
}

void find_uniq(int maxChar, int nWord, int data_length[], int outdata[][maxChar]){
  //Setting up the labels (number of charcters)
  for(int i = 0; i < maxChar; i++){
    outdata[0][i] = i + 1;
    outdata[1][i] = 0;
  }

  // Looping over all the word length array
  for(int i = 0; i < nWord; i++){
    // Looping over all the labels
    for(int j = 0; j < maxChar; j++){
      // Adding 1 to the specific number of character if the length are the same
      if(outdata[0][j] == data_length[i]){
        outdata[1][j] = outdata[1][j] + 1;
        break;
      }
    }
  }
}

void print_hist(int type, int nData, int data[][nData], double scale){
  /* Type 1 is horizontal histogram and type 2 is vertical histogram */
  // Printing out the scale
  printf("One * = %lf units\n", scale);

  switch(type){
    //Horizontal
    case 1:
      // Looping over the amount of data
      for(int i = 0; i < nData; i++){
        // Only printing if the value is > 0
        if(data[1][i]/scale != 0){
          //Printing out the label
          printf("%5d/%-5d  ", data[0][i], data[1][i]);
          //Printing out the corresponding amount of "*" according to scale
          for(int j = 0; j < data[1][i]/scale ; j++){
            printf("*");
          }
          //Printing out a new line
          printf("\n");
        }
      }
      break;

    //Vertical
    case 2:
      int dots = array_max(data[1], nData, scale);
      // Looping for the max amount of dots (rows)
      for(int i = 0; i < dots; i++){
        // Looping over all the data
        for(int j = 0; j < nData; j++){
          if(data[1][j] == 0) continue;
          // Print a "*" if it is more than the max amount of dot - the current row otherwise print blank
          if(ceil(data[1][j]/scale) >= dots - i){
            printf(" * ");
          } else{
            if(data[j*2 + 1] != 0) printf("   ");
          }
        }
        //Printing out a new line
        printf("\n");
      }

      //Printing out the labels
      for(int i = 0; i < nData; i++){
        if(data[1][i]/scale != 0) printf("%3.0d", data[0][i]);
      }
      //Printing out new line
      printf("\n");
      break;

    // Default
    default:
      printf("Unknown histogram type, please check your code");
      break;
  }
}


int main(int argc, char ** argv){
  // Global Variable N defines the max amount of character a word can have
  // Getting data from the file
  char * file = argv[1];
  int nWord = counting(2, file);
  char data[nWord][N];
  scan_file(file, data);

  // Finding the length of each string
  int numChar[nWord];
  find_char_length(nWord, data, numChar);

  //Finding the amount of word that have the same amount of character and put it in an array that is suitable for printing
  int maxChar = array_max(numChar, nWord, 1);
  int data_formatted[2][maxChar];
  find_uniq(maxChar, nWord, numChar, data_formatted);

  //Printing Horizontal Histogram
  printf("Horizontal\n");
  print_hist(1, maxChar, data_formatted, 10);
  printf("\n");
  //Printing Vertical Histogram
  printf("Vertical\n");
  print_hist(2, maxChar, data_formatted, 10);

  return 0;
}
