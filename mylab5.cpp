//Author: Shane Wilkerson
//9-15-2024

//This program calculates how many users are logged into a linux server at one time and how many times each user is logged in. 

#include <iostream>
#include <fstream>
#include <time.h>
#include <cstring>
#include <string>
#include <stdio.h>

using namespace std;

const char fname[] = "myfile.txt";
char Usernames[2000][200];

//processes login counts
void processLoginCounts(int i) 
{
    time_t T;
    time(&T); 
    int count[i] = {0}; //set each index to 0
    int counter = 0;
    
    for (int a = 0; a < i; a++) {
        for (int b = 0; b < i; b++) {
            if (strcmp(Usernames[a], Usernames[b]) == 0) {
                counter += 1;
            }
        }
        count[counter] += 1;
        counter = 0;
    }
    
    for (int c = 0; c < i; c++) {
        if (count[c] != 0) {
            count[c] /= c;
        }
    }
    
    printf("Odin current login statistics\n");
    printf("Time: %s\n", ctime(&T));
    for (int d = 0; d < i; d++) {
        if (count[d] != 0) {
            printf("%i logins: %i Users\n", d, count[d]);
        }
    }
}

int main(int argc, char* argv[]) 
{   
 ifstream fin; //added this

    
     
      #ifdef UNIT_TEST  //Unit test to test for custom made files
      if (argc > 1) {
         printf("Running a Unit Test\n");
         fin.open(argv[1]);     
      
         } else {
         printf("Error - Unit test requires a file name.\n");
         printf("Example: ./utest testfile.txt\n");

         exit (0);
         }
       if (!fin.good()) {
             printf("Error - that file does not exist.\n");
           exit (0);
         }

      #else //UNIT_TEST
         system("PROCPS_USERLEN=15 w -h > myfile.txt");
         fin.open("myfile.txt");
      #endif //UNIT_TEST 
             
    char inp[200];
    fin.getline(inp, 200);
    int i = 0;
    
    while (!fin.eof()) {
        char *p = strstr(inp, " ");
        if (p)
            *p = '\0';

        strcpy(Usernames[i], inp);
        i++;
        fin.getline(inp, 200);
    }
    fin.close();

    //call sorting process
    processLoginCounts(i);

    return 0;
}
