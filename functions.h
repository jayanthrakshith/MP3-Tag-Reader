#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void view_mp3();
void read_text(FILE *fp,char *str);
void edit_mp3(int argc,char *argv[]);
void edit(const char *tag,FILE *fp1,FILE *fp2,const char *new_value);
#endif

