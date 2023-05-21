//ben imwald
//5/21/2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *  Input filename in argv[1] for file to process, such as:
 *    ./dvds Spiderman.mp4
 *    ./dvds 'Spiderman_ No Way Home.mp4'
 *  Outputs file titled <argv[1]>trim.
 */
int main(int argc, char *argv[]) {
  char lengthcommand[256] = "";
  char executecommand[256] = "";
  char filename[128] = "";
  char buffer[20];
  FILE *fp;
  
  if(argc == 1) {
    fprintf(stderr, "Usuage error: ./dvds <filename.type>\n");
    exit(1);
  } else {
    filename[0] = '\''; //combines filename into string
    for(int i = 1; i < argc; i++ ) {
      strcat(filename, argv[i]);
      if(i < (argc-1)) {
        strcat(filename, " ");
      }
    }
    strcat(filename, "'");
    
    //gets duration of string
    strcat(lengthcommand, "ffprobe -v error -select_streams v:0 -show_entries stream=duration -of default=noprint_wrappers=1:nokey=1 ");
    strcat(lengthcommand, filename);
    printf("%s\n", lengthcommand);
    
    //captures this to variable duration.
    double duration = 10;
    //system(lengthcommand);
    fp = popen(lengthcommand, "r");
    if (fp == NULL) {
        printf("Failed to execute length command\n"); exit(1);
    }
    fgets(buffer, sizeof(buffer), fp); // Read the output into a buffer
    duration = atof(buffer); // Convert the buffer to an integer
    pclose(fp);
    printf("The duration is: %f\n", duration);
    duration -= 10;
    printf("The shortened duration is: %f\n", duration);

    //ffmpeg -ss 00:00:05 -i 'Spider-Man_ No Way Home.mp4' -to 8889 -c:v copy -c:a copy trim_ipseek_copy.mp4
    //sets execution command
    strcat(executecommand, "ffmpeg -ss 00:00:05 -i ");
    strcat(executecommand, filename);
    strcat(executecommand, " -to ");

    char temp[512]; // Temporary buffer to hold the formatted string
    sprintf(temp, "%s%f", executecommand, duration);
    strcpy(executecommand, temp);

    strcat(executecommand, " -c:v copy -c:a copy 'trim ");
    strcat(executecommand, filename + 1); //does recopy the ' character
    printf("%s\n", executecommand);

    system(executecommand);
  }
  return 0;
}
