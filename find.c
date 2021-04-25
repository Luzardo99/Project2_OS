/*
 * This program shows how to list all the files in a directory.
 * You can follow the routine, but the code may not work prefectly.
 *
 * Input: ./reddir testdir
 * Output: print all the files
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
char * full_path;


void read_sub(char* sub_dir, char **argv)
{
  DIR *sub_dp=opendir(sub_dir);
  struct dirent * sub_dirp;

  if(sub_dp!=NULL)
    {
       while((sub_dirp=readdir(sub_dp))!=NULL)
        {
         //printf("%s\n",sub_dirp->d_name);
         //if(stat(sub_dirp->d_name,&buf)==0)
         //printf("%d ", (int)buf.st_size);
	 char * temp =sub_dirp->d_name;
         char temp1[]=".";
	 char temp2[]="..";

        if(strcmp(temp,temp1)!=0&&strcmp(temp,temp2)!=0)//recurcively loop into the sub-directory
        {
	char temp3[]="/";
	char *temp_sub=temp3;
	temp_sub=strcat(temp_sub,temp);
	char * temp_full_path=malloc(sizeof(char)*2000);
	temp_full_path=strcpy(temp_full_path,sub_dir);
	strcat(temp_full_path,temp_sub);
    int retname = strcmp(argv[2],"-name");
    int retmin = strcmp(argv[2],"-mmin"); 
    int retnode = strcmp(argv[2],"-inum");
    int retfile;

    struct stat buffer;
    stat(temp_full_path, &buffer); 
    long iNode;
    time_t lastmod;
    time_t now = time(0);

    if(stat(temp_full_path, &buffer) == 0){
        lastmod = buffer.st_mtime;
        iNode = buffer.st_ino;
    }else{
        printf("Unable to get the stats of the file: %s", temp_full_path);
        }
    
    differenceTime = diffTime(now,lastmod);
    printf("%s\n", differenceTime);



    
    // if( retname == 0 ){
    //    retfile = strcmp(argv[3],temp_sub);
    //    if(retfile == 0){
    //        printf("%s\n", temp_full_path);
    //    }
    // }
    if( retmin == 0 ){
       retfile = strcmp(argv[3],temp_sub);
       if(retfile == 0){
           printf("%s\n", temp_full_path);
       }
    }
    // else if( retnode == 0 ){
    //     int id = atoi(argv[3]);
    //    if( id == iNode){
    //        printf("%s\n", temp_full_path);
    //    }
    // }else{
    //     printf("%s\n", temp_full_path);
    // }
    
    



    //printf("%s\n", temp_full_path);
 	DIR * subsubdp=opendir(temp_full_path);
	if(subsubdp!=NULL){
	closedir(subsubdp);
        read_sub(temp_full_path,argv);
        }
        }
        }
       closedir(sub_dp);
    }
    else
    {
        printf("cannot open directory\n");
        exit(2);
    }

}

int main(int argc, char **argv)
{
    char * dir;
    if(argc <2)
    {
	dir=".";
    }
    else
    {
	dir=argv[1];	
    }
    read_sub(dir,argv);

    exit(0);
}


