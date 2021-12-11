#include <stdio.h>
#include <string.h>
#include <math.h>

int counting(int type, char * fileName){
  //Declaring Variables
  FILE * F;
  int counter = 0;
  char word[20];

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

int max_dot(double * array, int nWord, double scale){
  //Setting intial value
  int cMax = 0;

  //Lopping over all the values in the array
  for(int i = 0; i < nWord/2; i++){
    //Looking for the indexes that contains the value and not the label
    int index = i * 2 + 1;
    //Making it the new max if it is greater than the current max value
    if(array[index]/scale > cMax) cMax = array[index]/scale;
  }

  return cMax;
}

void scan_file(char * fileName, double * words){
  //Declaring Variables
  FILE * F;
  int counter = 0;

  if((F=fopen(fileName, "r")) != NULL){
    //Scan each word until EOF
    while((fscanf(F, "%lf", &words[counter])) != EOF) counter++;

    //Closing the file
    fclose(F);
  } else printf("No such file %s", fileName);
}

void print_hist(int type, int nData, double * data, double scale){
  /* Type 1 is horizontal histogram and type 2 is vertical histogram */
  // Printing out the scale
  printf("One * = %lf units\n", scale);

  switch(type){
    //Horizontal
    case 1:
      // Looping over the amount of data
      for(int i = 0; i < nData; i++){
        int dp = 2*i;
        //Printing out the label
        printf("%.1lf/%.1lf  ", data[dp], data[dp + 1]);
        //Printing out the corresponding amount of "*" according to scale
        for(int j = 0; j <= data[dp + 1]/scale; j++){
          printf("*");
        }
        //Printing out a new line
        printf("\n");
      }
      break;

    //Vertical
    case 2:
      int dots = max_dot(data, nData * 2, scale);
      // Looping for the max amount of dots (rows)
      for(int i = 0; i < dots; i++){
        // Looping over all the data
        for(int j = 0; j < nData; j++){
          // Print a "*" if it is more than the max amount of dot - the current row otherwise print blank
          if(ceil(data[j*2 + 1])/scale >= dots - i){
            printf(" * ");
          } else printf("   ");
        }
        //Printing out a new line
        printf("\n");
      }

      //Printing out the labels
      for(int i = 0; i < nData; i++){
        printf(" %.0lf ", data[i*2]);
      }
      printf("\n");
      break;

    // Default
    default:
      printf("Unknown histogram type, please check your code");
      break;
  }
}

int main(int argc, char ** argv){
  // Getting Data From File
  char * file = "input.txt";
  int nWord = counting(2, file);
  double data[nWord];
  scan_file(file, data);
  int nLine = counting(1, file);

  //Printing Vertical Histogram
  printf("Vertical\n");
  print_hist(2, nLine, data, 1);

  return 0;
}
