/* Jayanth Rakshith K
 * 25017A   */
   

#include<stdio.h>
#include<stdlib.h>
#include <string.h>   
#include "functions.h" 

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage:\n");
        printf("  %s -v <mp3_file>         : View MP3 tags\n", argv[0]);
        printf("  %s -e <mp3_file> <option> <new_value> : Edit MP3 tag\n", argv[0]);
        printf("Options: -t Title, -a Artist, -A Album, -y Year, -c Genre, -C Comment\n");
        return 1;
    }

    if (strcmp(argv[1], "-v") == 0) {
        if (argc < 3) {
            printf("Please provide an MP3 file to view.\n");
            return 1;
        }
        view_mp3();
    } 
    else if (strcmp(argv[1], "-e") == 0) {
        if (argc < 5) {
            printf("Usage: %s -e <mp3_file> <option> <new_value>\n", argv[0]);
            return 1;
        }
        edit_mp3(argc, argv);
    } 
    else {
        printf("Invalid option. Use -v to view or -e to edit.\n");
        return 1;
    }

    return 0;
}
			


