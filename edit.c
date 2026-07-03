#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"functions.h"
void edit_mp3(int argc,char *argv[])
{
	//to pass arguments for editting tags
	if (argc < 5) {
        printf("Usage: %s -e <filename> <-t|-a|-A|-y|-c|-C> <new_value>\n", argv[0]);
        exit(1);
    }
	//open mp3 file
	FILE *fp1 = fopen(argv[2],"rb");
	if(!fp1)
        {
                printf("Error\n");
                exit(1);
        }

	//create and open output1.mp3 file 
	FILE *fp2 = fopen("output1.mp3","wb");
	if(!fp2)
	{
		printf("Error\n");
		exit(1);
	}
	
	unsigned char signature[4]="ID3";
	unsigned char buffer[4];

	fread(buffer,1,3,fp1);
	buffer[3] = '\0';
	//to compare signature is ID3 and if yes copy to output
	if(strncmp(buffer,signature,3)!=0)
	{
		printf("Not mp3 file\n");
		fclose(fp1);
		fclose(fp2);
		exit(0);
	}
	//write signature of mp3 file to output1.mp3
	fwrite(buffer,1,3,fp2);

	unsigned char buffer1[7];
	fread(buffer1,1,7,fp1);
	fwrite(buffer1,1,7,fp2);
	int edited = 1;
	unsigned char tag[5]={0};
	//loop through and get the tags
	while(fread(tag,1,4,fp1) == 4)
	{

		tag[4]='\0';
		if((strcmp(tag,"TIT2") == 0) && (strcmp(argv[3], "-t") == 0))
		{
			edited = 0;
			edit(tag,fp1,fp2,argv[4]);
		}
		else if((strcmp(tag,"TYER") == 0)  && (strcmp(argv[3], "-y") == 0))
                {
			 edited = 0;
                        edit(tag,fp1,fp2,argv[4]);
                }
		else if((strcmp(tag,"TPE1") == 0)  && (strcmp(argv[3], "-a") == 0))
                {
			 edited = 0;
                        edit(tag,fp1,fp2,argv[4]);
                }
		else if((strcmp(tag,"TALB") == 0)  && (strcmp(argv[3], "-A") == 0))
                {
			 edited = 0;
                        edit(tag,fp1,fp2,argv[4]);
                }
		else if((strcmp(tag,"TCON") == 0)  && (strcmp(argv[3], "-c") == 0))
                {
			 edited = 0;
                        edit(tag,fp1,fp2,argv[4]);
                }
		else if((strcmp(tag,"TCOMM") == 0)  && (strcmp(argv[3], "-C") == 0))
                {
			 edited = 0;
                        edit(tag,fp1,fp2,argv[4]);
                }
	
	else
	{
		fwrite(tag,1,4,fp2);
		unsigned char sizeb[4];

		fread(sizeb,1,4,fp1);
		 fwrite(sizeb,1,4,fp2);
		int size = ((sizeb[0] & 0x7F) << 21) |
                         ((sizeb[1] & 0x7F) << 14) |
                       ((sizeb[2] & 0x7F) << 7)  |
                       (sizeb[3] & 0x7F);
		
			
		 unsigned char flag[2];
		 fread(flag, 1, 2, fp1);
		 fwrite(flag, 1, 2, fp2);

		 //to copy the info from mp3 to output file
		unsigned char *info = malloc(size+1);
                 if (!info) {
                     printf("Memory allocation failed!\n");
                      exit(1);
                   }
                   fread(info, 1, size, fp1);
                   fwrite(info, 1, size, fp2);
                    free(info);
		
	}
	}	
	 unsigned char copy_buffer[1024];
    size_t n;
    while ((n = fread(copy_buffer, 1, sizeof(copy_buffer), fp1)) > 0) {
        fwrite(copy_buffer, 1, n, fp2);
    }

    fclose(fp1);
    fclose(fp2);

    // Replace original file
    if (remove(argv[2]) != 0 || rename("output1.mp3", argv[2]) != 0) 
    	{
    		perror("Error updating original file");
    		exit(1);
	}
    printf("MP3 updated successfully!\n");
}
	
void edit(const char *tag, FILE *fp1, FILE *fp2, const char *new_value)
{
	unsigned char sizeb[4];
    fread(sizeb, 1, 4, fp1);

    int old_size = ((sizeb[0] & 0x7F) << 21) |
                   ((sizeb[1] & 0x7F) << 14) |
                   ((sizeb[2] & 0x7F) << 7)  |
                   (sizeb[3] & 0x7F);

    unsigned char old_flags[2];
    fread(old_flags, 1, 2, fp1);

    // New frame payload = encoding byte + string length
    int new_size = strlen(new_value) + 1;

    // --- Write header ---
    fwrite(tag, 1, 4, fp2);

    unsigned char new_sizeb[4];
    new_sizeb[0] = (new_size >> 21) & 0x7F;
    new_sizeb[1] = (new_size >> 14) & 0x7F;
    new_sizeb[2] = (new_size >> 7) & 0x7F;
    new_sizeb[3] = new_size & 0x7F;

    fwrite(new_sizeb, 1, 4, fp2);
    fwrite(old_flags, 1, 2, fp2);

    // --- Write new tag data ---
    fputc(0, fp2); // encoding byte
    fwrite(new_value, 1, strlen(new_value), fp2);

    // --- Skip old payload in input ---
    fseek(fp1, old_size, SEEK_CUR);

    printf("%s updated successfully!\n", tag);
}


        




		 



	
