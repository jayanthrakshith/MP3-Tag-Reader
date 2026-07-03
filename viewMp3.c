#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"functions.h"
void view_mp3()
{
	//open mp3 file
	FILE *fp = fopen("sample.mp3", "rb");
	if(!fp)
	{
		printf("Error while file opening!\n");
		exit(1);
	}
	//to check weather the signature of file id ID3 if not not an mp3 file
	char signature[4] = "ID3";
	char buffer1[4];
	fread(buffer1, 1, 3, fp);
	if(strncmp(buffer1, signature,3) != 0)
	{
		printf("It is not a Mp3 file!\n");
		fclose(fp);
		exit(0);
	}
	//skip 10 bytes of header
	fseek(fp, 10, SEEK_SET);
	char tag[5] = {0};
	
	while(fread(tag, 1, 4, fp) == 4)
	{

		tag[4]='\0';
		if(strcmp(tag,"TIT2") == 0)
		{
			read_text(fp,"TITle");
		}
		else if(strcmp(tag, "TYER") == 0)
		{
			read_text(fp, "YEAR");
		}
		else if(strcmp(tag, "TPE1") == 0)
		{
			read_text(fp, "ARTIST");
		}
		else if(strcmp(tag,"TALB") == 0)
		{
			read_text(fp, "ALBUM");
		}
		else if(strcmp(tag,"TCON") == 0)
		{
			read_text(fp, "GENRE");
		}
		else if(strcmp(tag,"TCOM") == 0)
		{
			read_text(fp, "COMPOSER");
		}
		else
		{
			//to convert big endian to little endian
			char sizeb[4];
            		fread(sizeb, 1, 4, fp);
            		int size = (sizeb[0] << 24) |
			       	(sizeb[1] << 16) |
			       	(sizeb[2] << 8) |
			       	sizeb[3];
            		fseek(fp, 2 + size, SEEK_CUR); // skip flags + data
			//fseek(fp, size, SEEK_CUR);
		}
	}
	fclose(fp);
}

void read_text(FILE *fp,char *str)
{
	char sizeb[4];
	fread(sizeb,1,4,fp);

	int size = (sizeb[0] << 24) |
           (sizeb[1] << 16) |
           (sizeb[2] << 8)  |
            sizeb[3];
	//skip 2 bytes of flag
	fseek(fp,2,SEEK_CUR);
        
	//to copy the remaining bytes
	char *Info = (char *)malloc(size + 1);
	if (!Info)
	{
    	printf("Memory allocation failed\n");
    	return;
	}

	fread(Info, 1, size, fp);
	Info[size] = '\0';
	printf("%s: %s", str,Info+1);
	printf("\n");
	free(Info);
}





