
#ifndef __UI_H__
#define __UI_H__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#ifndef EXIST
#define EXIST 1
#define NOTEXIST 0
#define OK 1
#define NO 0
#define ERROR -1
#define SAME 1
#define NOTSAME -1
#endif


char *ARP_FILE_PATH;
char *TEMP_ARP_FILE_PATH;
int ARGC;
char **ARGV;
char *AGING_TIME;

void inttoa(unsigned int val, char *buf, unsigned int radix);

void init(void);
void get_Instruction(int argc,char  **argv); 
int  if_Arp_File_Exist(char *file_path);
int  creat_Arp_File(char *file_path);
int  read_Arp_File(char *file_path,char *content);
int  write_Arp_File(char *file_path,char *content);
int  clear_Arp_file(char *file_path);
int  command_Table(char *command);
int  compare_Command(char *COM1,char *COM2);
int  uodate_Arp_File_Rows(char *file_path);
void response_To_Command(char *command);


int char_To_Int(char Byte);
int if_Legal_Input_IP(char *IP);
int if_Legal_Input_MAC(char *MAC);
int if_Legal_Input_Status(char *STATUS);
int if_Legal_Input_Aging_Time(char *Aging_Tiime);
int if_Legal_Input(char *IP, char *MAC, char *STATUS);

void set_Offset_Time(char *file_Path, int Offset_Time);
int  read_Offset_Time(char *file_Path);
char *update_Left_Time(char *file_Path,char Status, char *old_Left_Time_String);


int command_a();
int command_g();
//int command_v();
int command_d();
int command_s();

#endif
