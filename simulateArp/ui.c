#include "ui.h"

char *ARP_FILE_PATH="/home/tuolei/arp.txt";
char *TEMP_ARP_FILE_PATH="/home/tuolei/temp_arp.txt";
int ARGC=0;
char **ARGV ;
char *AGING_TIME="500";








/******************************************
*name: init
*function:	Dispaly all command witch users can use,
*        	this function is called when user enter 
*		a incorrect command.
*parameter: 	void  
*return 	void
***********************************/
void init(void)
{
        printf("\r\n>>>>>显示和修改地址解析协议<ARP>使用的“IP到物理”地址转换表<<<<<\r\n");
        printf("\r\n\r\n");
//-a
        printf("-a\r\n");
        printf("    %-s","通过询问当前协议数据，显示当前ARP项。如果指定inet_addr,则只>显示指定计算机的IP地址和物理地址。如果不止一个网络接口使用ARP，则显示每个ARP表的项。\r\n\r\n");
//-g
        printf("-g\r\n");
        printf("    %-s","与-a相同。\r\n\r\n");
//-v
        printf("-v\r\n");
        printf("    %-s","在详细模式下显示当前ARP项。所有无效项和环回接口上的项都将被>显示\r\n\r\n");
//inet_addr
        printf("inet_addr\r\n");
        printf("    %-s","指定Internet地址。\r\n\r\n");
//-N if_addr
        printf("-N if_addr\r\n");
        printf("    %-s","显示if_addr指定的网络接口的ARP项\r\n\r\n");
//-d
        printf("-d\r\n");
        printf("    %-s","删除inet_addr指定的主机。inet_addr可以是通配符*，以删除所有>主机。\r\n\r\n");
//-s
        printf("-s\r\n");
        printf("    %-s","添加主机并将Internet地址、inet_addr与物理地址eth_addr相关联>。物理地址是用连字符分隔的6个十六进制的字节。该项是永久的。\r\n\r\n");
//eth_addr
        printf("eth_addr\r\n");
        printf("    %-s","指定物理地址。\r\n\r\n");
//if_addr
        printf("if_addr\r\n");
        printf("    %-s","如果存在，此项指定地址转换表应该修改的接口的Internet地址。如果不存在，则使用第一个适用的接口。\r\n\r\n");
//示例
        printf("示例\r\n");
        printf("    %-s","> arp -s 157.55.85.212  00-aa-00-66-55-22....添加静态向。\r\n\r\n");
        printf("    %-s","> arp -a                                 ....显示ARP表。\r\n\r\n");

}

/************************************************************
*name:		get_Instruction
*function:	get the number of command parameters and store it
*		in the global variable ARGC;   get the list of the
*		command parameters and store it in the gloable 
*		variable **ARGV.this function was called at the 
*		beginning of this program.
*parameter1:	number of command parameters 	
*parameter2:    list of command parameters
*return:	void
************************************************************/
void  get_Instruction(int argc,char **argv)
{
//	printf("ERTER GET INSTRUCTION!\n");
	ARGC=argc;
	ARGV=argv;
//	printf("EXIT GET INSTRUCTION!\n");
}

/***************************************************************
*name:		if_Arp_File_Exist
*function:	test if the arp file exists?
*parameter1:	the path of the arp file.
*return:		if exist return EXIST(1),else return NOTEXIST(0)
*****************************************************************/
int if_Arp_File_Exist(char *file_path)
{
//	printf("ENTER IF ARP FILE EXIST!\n");
	if(access(file_path,F_OK)==0)
	{
//		printf("EXIT IF ARP FILE EXIST!\n");
	 	return EXIST;
	}	
	else
	{
//		printf("EXIT IF ARP FILE EXIST!\n");
  		return NOTEXIST;
	}
}

/**********************************************************
*name:		creat_Arp_File
*function:	create the arp file witch can be read and writen
*parameter1:	the path of arp file
*return:  	return OK(1) when the file is created
*********************************************************/
int creat_Arp_File(char *file_path) 
{
//	printf("ENTER CREATE ARP FILE!\n");
	close(open(file_path,O_RDWR|O_CREAT,S_IRWXU|S_IRWXG|S_IRWXO) );
	int offset_time;	
	offset_time = time((time_t *)NULL) ;
	set_Offset_Time(file_path,offset_time);
//	printf("EXIT CREATE ARP FILE!\n");
	return OK;
}


int read_Arp_File(char *file_path,char *content)
{
//	printf("ENTER READ ARP FILE!\n");
	FILE *fp;
	int i = 0 ;
	fp=fopen(file_path,"r");
	if(fp==NULL)  return NO;
	else
	{
			fgets(content,100,fp);
		while(feof(fp)!=1)
		{
			printf("%s",content);
			fgets(content,100,fp);
		}
		fclose(fp);
//		printf("EXIT READ ARP FILE!\n");
		return OK;
	}
}

int write_Arp_File_Rows(char *file_path,char *content)
{
//	printf("ENTER WRITE ARP FILE!\n");
	FILE *fp;
	fp=fopen(file_path,"a+");
	if(fp==NULL)
	{
		fclose(fp);
//		printf("EXIT WRITE ARP FILE!\n");
		return NO;
	}
	else
	{
		fprintf(fp,"%s",content);
		fclose(fp);
//		printf("EXIT WRITE ARP FILE!\n");
	}
}




int clear_Arp_File(char *file_path)
{
//	printf("ENTER CLERN ARP FILE\r\n");
	remove(file_path);
	close(open(file_path,O_RDWR|O_CREAT,S_IRWXU|S_IRWXG|S_IRWXO));
   	int offset_time;
       	offset_time=time((time_t *)NULL);
        set_Offset_Time(file_path,offset_time);
//	printf("EXIT CLERN ARP FILE\n");
	return OK;
}


int compare_Command(char *COM1,char *COM2)
{
//	printf("ENTER COMPARE COMMAND!\r\n");
	int index=0;
	while(1)
	{
		if(COM1[index] == COM2[index])
		{
			if(COM1[index] == '\0')
			{
//				printf("EXIT COMPARE COMMAND!\r\n");
				return SAME;
			}
			else
			{
				index++;
			}
		}
		else
		{	
			
//			printf("EXIT COMPARE COMMAND!\r\n");
			return NOTSAME;
		}
	}
}

void response_To_Command(char *command)
{
//	printf("ENTER RESPONSE TO COMMAND!\n");
	if(compare_Command(command,"-a") == SAME)	
	{
		command_a();
	}
	else if(compare_Command(command,"-g") == SAME)	
	{
		command_g();
	}
	else if(compare_Command(command,"-d") == SAME)	
	{
		command_d();
	}
	else if(compare_Command(command,"-s") == SAME)	
	{
		command_s();
	}
	else
	{
		init();
	}	
//	printf("EXIT RESPONSE TO COMMAND!\n");
}






int command_a()
{
	int old_time = read_Offset_Time(ARP_FILE_PATH);
	int now_time = time( (time_t *)NULL);
	int d_time = now_time - old_time;
	update_Arp_File_Rows(ARP_FILE_PATH);
	
//	printf("ENTER COMMAND A!\n");
	char content[100];
	if(if_Arp_File_Exist(ARP_FILE_PATH)==NOTEXIST)
	{
		if(creat_Arp_File(ARP_FILE_PATH)!=OK) 
		{
			printf("ERROR:>>>Arp_File not exist and faild to create it！！\r\n");
//			printf("EXIT COMMAND A!\n");
			return ERROR;
		}
	}
	if(read_Arp_File(ARP_FILE_PATH,content) == OK) 
	{
//		printf("EXIT COMMAND A!\n");
		return OK;
	}
	else 
	{
//		printf("EXIT COMMAND A!\n");
		return NO;
	}
}



//same as -a
int command_g()
{
//	printf("ENTER COMMAND G!\n");
        char content[100];
        if(if_Arp_File_Exist(ARP_FILE_PATH)==NOTEXIST)
        {
                if(creat_Arp_File(ARP_FILE_PATH)!=OK) 
                {
                        printf("ERROR:>>>Arp_File not exist and faild to create it!!\r\n");
//			printf("EXIT COMMAND G!\n");
	                return ERROR;
       		}
	}
        if(read_Arp_File(ARP_FILE_PATH,content) == OK)
        {
//		printf("EXIT COMMAND G!\n");
                return OK;
        }
        else
        {
//		printf("EXIT COMMAND G!\n");
                return NO;
        }
}



int command_s()
{
//	printf("ENTER COMMAND S!\n");
	update_Arp_File_Rows(ARP_FILE_PATH);
	if(ARGC < 5 || ARGC > 6)
	{
		printf("ERROR:>>>Wrong Parameters![reference:-s IP MAC STATUS <time>,only the status is D/d(dynamic),the time is valued,if status is D/d without the parameter time,default set time 500 secconds.]\r\n");
		printf("EXIT COMMAND S!\n");
		return ERROR;
	}
	else if(ARGC == 5)
	{
		if(if_Legal_Input(ARGV[2],ARGV[3],ARGV[4])!=OK )
		{
//			printf("EXIT COMMAND S!\n");
			return ERROR;
		}
		
	}
	else if(ARGC == 6)
	{
		if(if_Legal_Input(ARGV[2],ARGV[3],ARGV[4])!=OK 
		|| if_Legal_Input_Aging_Time(ARGV[5]) != OK)
		{
//			printf("EXIT COMMAND S!\n");
			return ERROR;
		}
		
	}
 	if(if_Arp_File_Exist(ARP_FILE_PATH)==NOTEXIST)
        {
                if(creat_Arp_File(ARP_FILE_PATH)!=OK) 
                {
                        printf("ERROR:>>>Arp_File not exist and faild to create it!!\r\n");
//			printf("EXIT COMMAND S!\n");
			return ERROR;
        	}
	}
	else
	{
		if(compare_Command(ARGV[4],"D") == SAME
		|| compare_Command(ARGV[4],"d") == SAME)
		{

	                FILE *fp;
        	        int ch;
                	fp=fopen(ARP_FILE_PATH,"a+");
                	if(fp==NULL)
			{ 
//				printf("EXIT COMMAND S!\n");
				return NO;
			}
                	else
                	{
                        	ch = fgetc(fp);
                	}
                	if(ch != EOF)
			{
				printf("\n");
				printf("%c\n",ch);
				printf("%d\n",ch);
                        //	write_Arp_File_Rows(ARP_FILE_PATH,"\r\n");
                	}
                	else
                	{
				printf("%c",ch);
                        	;
                	}
			write_Arp_File_Rows(ARP_FILE_PATH,ARGV[2]);
			write_Arp_File_Rows(ARP_FILE_PATH," ");
			write_Arp_File_Rows(ARP_FILE_PATH,ARGV[3]);
			write_Arp_File_Rows(ARP_FILE_PATH," ");
			write_Arp_File_Rows(ARP_FILE_PATH,ARGV[4]);
			write_Arp_File_Rows(ARP_FILE_PATH," ");
			if(ARGC==5)
			{
				write_Arp_File_Rows(ARP_FILE_PATH,AGING_TIME);
				write_Arp_File_Rows(ARP_FILE_PATH," ");
				write_Arp_File_Rows(ARP_FILE_PATH,"\r\n");
				printf("%s",AGING_TIME);
			}
			else 
			{		
				write_Arp_File_Rows(ARP_FILE_PATH,ARGV[5]);
				if(strlen( (char *)(ARGV[5]) )==3)
                                {
                                }
				else if(strlen( (char *)(ARGV[5]) )==2)
				{
					write_Arp_File_Rows(ARP_FILE_PATH," ");
				}
				else if( strlen( (char *)(ARGV[6]) )==1)
				{
					write_Arp_File_Rows(ARP_FILE_PATH,"  ");
				}
				write_Arp_File_Rows(ARP_FILE_PATH," ");
				write_Arp_File_Rows(ARP_FILE_PATH,"\r\n");
			}
			fclose(fp);
//			printf("EXIT COMMAND S!\n");
			return OK;
		}	
		else if(compare_Command(ARGV[4],"S") == SAME
                || compare_Command(ARGV[4],"s") == SAME)
		{
                	FILE *fp;
                	int ch;
                	fp=fopen(ARP_FILE_PATH,"r");
                	if(fp==NULL)
	  		{	
//				printf("EXIT COMMAND S!\n");
				return NO;
			}
                	else
                	{
                        	ch = fgetc(fp);
                	}
                	if(ch != EOF)
                	{
                        //	write_Arp_File_Rows(ARP_FILE_PATH,"\r\n");
                	}
                	else
                	{
                       		;
                	}
                	write_Arp_File_Rows(ARP_FILE_PATH,ARGV[2]);
                	write_Arp_File_Rows(ARP_FILE_PATH," ");
                	write_Arp_File_Rows(ARP_FILE_PATH,ARGV[3]);
                	write_Arp_File_Rows(ARP_FILE_PATH," ");
                	write_Arp_File_Rows(ARP_FILE_PATH,ARGV[4]);
			write_Arp_File_Rows(ARP_FILE_PATH," ");
			write_Arp_File_Rows(ARP_FILE_PATH,"\r\n");
			fclose(fp);		
		}
		else 
		{
			printf("ERROR:>>>Status error.");
//			printf("EXIT COMMAND S!\n");
			return ERROR;
		}
	}
}
int command_d()
{
//	printf("ENTER COMMAND D!\n");
        if(if_Arp_File_Exist(ARP_FILE_PATH)==NOTEXIST)
        {
                if(creat_Arp_File(ARP_FILE_PATH)!=OK) 
                {
                        printf("ERROR:>>>Arp_File not exist and faild to create it!!\r\n");
//			printf("EXIT COMMAND D!\n");
                	return ERROR;
       		}
	}
	else
	{
		clear_Arp_File(ARP_FILE_PATH);
//		printf("EXIT COMMAND D!\n");
		return OK;
	}	
}



int char_To_Int(char Byte)
{
//	printf("ENTER CHAR TO INT!\n");
	if( (Byte >= '0' && Byte <= '9') 
	|| (Byte >= 'a' && Byte <= 'f') 
	|| (Byte >= 'A' && Byte <= 'F') )
	{
		if( Byte >= '0' && Byte <= '9')
		{
//			printf("EXIT CHAR TO INT!\n");
			return (Byte-48);
		}
		else if( Byte >= 'a' && Byte <= 'f' )
		{
//			printf("EXIT CHAR TO INT!\n");
			return (Byte-87);
		}
		else if( Byte >= 'A' && Byte <= 'F' )
		{
//			printf("EXIT CHAR TO INT!\n");
			return (Byte-55);
		}
	}
	else
	{
		return ERROR;
	}
}


int string_To_Int(char *str)
{
//	printf("ENTER STRING TO INT!\n");
	switch(strlen(str))
	{
	case 1:
		if(char_To_Int(str[0]) >= 0 && char_To_Int(str[0]) <= 9)
		{
//			printf("EXIT STRING TO INT!\n");
			return ( char_To_Int(str[0]) );
		}
		else
		{
//			printf("EXIT STRING TO INT!\n");
			return ERROR;
		}
	case 2:
		if( (char_To_Int(str[0]) >= 0 && char_To_Int(str[0]) <= 9)
		&& ( char_To_Int(str[1]) >= 0 && char_To_Int(str[1]) <= 9) )
		{
//			printf("EXIT STRING TO INT!\n");
			return ( char_To_Int(str[0])*10 + char_To_Int(str[1]) );
		}
		else
		{
//			printf("EXIT STRING TO INT!\n");
			return ERROR;
		}
	case 3:
		if( (char_To_Int(str[0]) >= 0 && char_To_Int(str[0]) <= 9)
		&& ( char_To_Int(str[1]) >= 0 && char_To_Int(str[1]) <= 9)
		&& ( char_To_Int(str[2]) >= 0 && char_To_Int(str[2]) <= 9) )
		{
//			printf("EXIT STRING TO INT!\n");
			return ( char_To_Int(str[0])*100 + char_To_Int(str[0])*10 + char_To_Int(str[1]) );
		}
		else 
		{
//			printf("EXIT STRING TO INT!\n");
			return ERROR;
		}
	default:
//		printf("EXIT STRING TO INT!\n");
		return ERROR;
	}
}

int hex_To_Int( char *hex)
{	
//	printf("ENTER HEX TO INT!\n");
	if(strlen(hex)!=2)
	{
//		printf("EXIT HEX TO INT!\n");
		return ERROR;
	}
	else
	{
//		printf("EXIT HEX TO INT!\n");
		return ( char_To_Int(hex[0])*16 + char_To_Int(hex[1]) );
	}
}

int if_Legal_Input_IP(char *IP)
{
//	printf("ENTER IF LEGAL INPUT IP!\n");
	char temp_IP[20];
	int k=0;
	int dot_Count=0;
	if(IP[0] == '.')
	{
		printf("ERROR:>>>You entered a illegal IP address.\n");
//		printf("EXIT IF LEGAL INPUT IP!\n");
		return ERROR;
	}
	char last_Char=NULL;
	while(1)
	{
		if(IP[k]!='\0')
		{
			if(IP[k] == '.')
			{
				if(last_Char == '.')
				{
					printf("ERROR:>>>You entered a illegal IP address.\n");
//					printf("EXIT IF LEGAL INPUT IP!\n");
					return ERROR;
				}
				else
				{	
					dot_Count++;
					last_Char = IP[k];
				}
			}
			else
			{
				last_Char = IP[k];
			}	
			temp_IP[k]=IP[k];
			k++;
		}
		else
		{
			if(last_Char == '.')
			{
				printf("ERROR:>>>You entered a illegal IP address.\n");
//				printf("EXIT IF LEGAL INPUT IP!\n");
				return ERROR;
			}
			else if( dot_Count != 3 )
			{
				printf("ERROR:>>>You entered a illegal IP address.\n");
//				printf("EXIT IF LEGAL INPUT IP!\n");
				return ERROR;	
			}
			temp_IP[k]='\0';
			break; 
		}	

	}
	char *result;
	result=strtok(temp_IP,".");
	if(string_To_Int(result) != ERROR && string_To_Int(result) < 256)
	{
		;
	}
	else
	{	
		printf("ERROR:>>>You entered a illegal IP address.\n");
//		printf("EXIT IF LEGAL INPUT IP!\n");
		return ERROR;
	}
	while(result=strtok(NULL,"."))
	{ 
	       	if(string_To_Int(result) != ERROR && string_To_Int(result) < 256)
       		{
			;
		}
        	else
        	{
			printf("ERROR:>>>You entered a illegal IP address.\n");
//			printf("EXIT IF LEGAL INPUT IP!\n");
                	return ERROR;
        	}
	}

//	printf("EXIT IF LEGAL INPUT IP!\n");
	return OK;
}


int if_Legal_Input_MAC(char *MAC)
{
	return OK;
}

int if_Legal_Input_Status(char *STATUS)
{
	return OK;
}

int if_Legal_Input_Aging_Time(char *Aging_Time)
{
//	printf("ENTER IF LEGAL INPUT AGING TIME!");
	int i = 0;
	for(i = 0; i < strlen(Aging_Time); i++)
	{
		if(Aging_Time[i] >'9' || Aging_Time[i] < '0')
		{
//			printf("ENTER IF LEGAL INPUT AGING TIME!");
			return ERROR;
		}
	}
//	printf("ENTER IF LEGAL INPUT AGING TIME!");
	return OK;
}

int if_Legal_Input(char *IP,char *MAC,char *STATUS)
{
//	printf("ENTER IF LEGAL INPUT!");
	if(if_Legal_Input_IP(IP) != OK) 
	{
//		printf("EXIT IF LEGAL INPUT!");
		return ERROR;
	}	
	else if(if_Legal_Input_MAC(MAC) != OK)
 	{
//		printf("EXIT IF LEGAL INPUT!");
		return ERROR;
	}
	else if(if_Legal_Input_Status(STATUS) != OK) 
	{
//		printf("EXIT IF LEGAL INPUT!");
		return ERROR;
	}
	else
	{ 	
//		printf("EXIT IF LEGAL INPUT!");
		return OK;
	}
}

void set_Offset_Time(char *file_Path, int offset_Time)
{
//	printf("ENTER SET OFFSET TIME!\n");
	FILE *fp =fopen(file_Path,"r+");
	int first_Line_Len=0;
	char first_line[15];
	char new_First_Line[15];
	int res;
	if(fp == NULL)
	{
		printf("ERRORFP\n");
//		printf("EXIT SET OFFSET TIME!\n");
	}
	else
	{
		fgets(first_line,15,fp);
		if(ftell(fp)==0)
		{
			inttoa(offset_Time,new_First_Line,10);
                        fprintf(fp,"%s",new_First_Line);
                        fprintf(fp,"%s","\r\n");
                        fclose(fp);
//			printf("EXIT SET OFFSET TIME!\n");
		}
  		else
        	{
                	first_Line_Len = strlen(first_line);
			res = fseek(fp,-first_Line_Len,SEEK_CUR);
                	if(res<0)
                	{
//				printf("EXIT SET OFFSET TIME!\n");
                	}
                	else
                	{
                        	inttoa(offset_Time,new_First_Line,10);
                        	fprintf(fp,"%s",new_First_Line);
                        	fprintf(fp,"%s","\r\n");
                        	fclose(fp);
//                        	printf("EXIT SET OFFSET TIME!\n");
                	}
        	}
	}
}

int read_Offset_Time(char *file_Path)
{
//	printf("ENTER READ OFFSET TIME!\n");
        if(if_Arp_File_Exist(file_Path)==NOTEXIST)
        {
                if(creat_Arp_File(file_Path)!=OK)
                {
                        printf("ERROR:>>>Arp_File not exist and faild to create it!!\r\n");
//			printf("EXIT READ OFFSET TIME!");
                        return ERROR;
                }
        }

        FILE *fp =fopen(file_Path,"r+");
        char first_Line[15];
        int offset_Time=0;
        if(fp == NULL)
        {
//		printf("EXIT READ OFFSET TIME!");
		return ERROR;
        }
        fgets(first_Line,15,fp);
        fclose(fp);
	offset_Time = atoi(first_Line);
//	printf("EXIT READ OFFSET TIME!\n");
	return offset_Time;
}








int update_Arp_File_Rows(char *file_path)
{
//	printf("ENTER UPDATE ARP FILE ROWS!\n");
	FILE *fp;
	char content[100];
	int old_time=0;
        int new_time=0;
        int d_time=0;
        int old_Left_Time_Int=0;
        int new_Left_Time_Int=0;
	char new_Left_Time_String[15];
	int res=0;
	char *result;
	old_time = read_Offset_Time(file_path);
	new_time = time((time_t *)NULL);
	d_time = new_time - old_time;
        fp=fopen(file_path,"r+");
	fgets(content,100,fp);
	res = fseek(fp,-strlen(content),SEEK_CUR);
	inttoa(new_time,new_Left_Time_String,10);
	res = fseek(fp,0,SEEK_SET);
	fgets(content,100,fp);
	set_Offset_Time(file_path,new_time);
       	if(fp==NULL)
  	{	
		return NO;
	}
        else
	{
        	while(!feof(fp))
	       	{
	        	fgets(content,100,fp);
        		result=strtok(content," ");
        		while(result=strtok(NULL," "))
        		{
				if(compare_Command(result,"D")==SAME
 				|| compare_Command(result,"d")==SAME)		
				{
					result=strtok(NULL," ");
                		        old_Left_Time_Int=atoi(result);
					new_Left_Time_Int = old_Left_Time_Int - d_time;
					if(new_Left_Time_Int <= 0)
					{
						new_Left_Time_Int = 0;
					}
					else
					{
					}
						//instead
					res = fseek(fp,-6,SEEK_CUR);
					if(res<0)
					{
						return ERROR;
					}
					inttoa(new_Left_Time_Int,new_Left_Time_String,10);
					fprintf(fp,"%s",new_Left_Time_String);
					if( strlen(result)==3 )
					{
						if(strlen(new_Left_Time_String)==3)
						{
							//do null
						}
						else if(strlen(new_Left_Time_String)==2)
                                                {
							//insert a space
							fprintf(fp,"%s"," ");
                                                }
						else if(strlen(new_Left_Time_String)==1)
                                                {
							//insert two spaces
							fprintf(fp,"%s","  ");
                                                }
					}					
					else if( strlen(result)==2 )
                                        {
                                                if(strlen(new_Left_Time_String)==2)
                                                {
                                                        //do null
                                                }
                                                else if(strlen(new_Left_Time_String)==1)
                                                {
                                                        //insert a spaces
                                                        fprintf(fp,"%s"," ");
                                                }
                                        }	
					else if( strlen(result)==1 )
                                        {
                                                if(strlen(new_Left_Time_String)==1)
                                                {
                                                        //do null
                                                }
                                        }
					break;
				}
				else
				{
					;
				}
			}
	        }
//		printf("EXIT UPDATE ARP FILE ROWS!\n");
        	fclose(fp);
	}//update finished.next delete overdue list;
/*
	creat_Arp_File(TEMP_ARP_FILE_PATH);
	FILE *temp_arp_fp;
	FILE *arp_fp;
	char temp_content[100];
	int i = 0;
	temp_arp_fp=fopen(TEMP_ARP_FILE_PATH,"w");
	arp_fp = fopen(ARP_FILE_PATH,"r");
	fgets(content,100,arp_fp);
	fprintf(fp,"%s",content);
	while(!feof(arp_fp))
	{
		printf("offset:%ld\n",ftell(arp_fp));
		fgets(content,100,arp_fp);
		for(i = 0;i<100;i++)
		{
			temp_content[i] = content[i];
		}
                result=strtok(content," ");
		printf("temp_content:%s\n",temp_content);
                while(result=strtok(NULL," "))
		{
		printf("result:%s\n",result);
			if(compare_Command(result,"D")==SAME
                        || compare_Command(result,"d")==SAME)
                        {
				result=strtok(NULL," ");
				if(compare_Command(result,"0")==SAME)
				{
					printf("delete line:%s!!!\n",temp_content);
					//ignore this line
					break;
				}
				else
				{
					printf("insert line:%s!!!\n",temp_content);
					fputs(temp_content,temp_arp_fp);
					//fprint(temp_arp_fp,"%s","\r\n");
					break;
				}
			}
			else 
			{
			}
		}

	}
	fclose(arp_fp);
	fclose(temp_arp_fp);
	remove(file_path);
	rename(TEMP_ARP_FILE_PATH,ARP_FILE_PATH);
	printf("EXIT UPDATE ARP FILE ROWS!\n");
	return OK;
*/
} 






char * update_Left_Time(char *file_Path,char Status,char *old_Left_Time_String)
{
//	printf("ENTER *UNDATE LEFT TIME!");
	if(Status='D'||Status=='d')
	{
		int old_time=0;
		int new_time;
		int d_time=0;
		int old_Left_Time_Int=0;
		int new_Left_Time_Int=0;
		char *new_Left_Time_String;
		old_time = read_Offset_Time(file_Path);
		new_time = time((time_t *)NULL);
		d_time = new_time-old_time;	
		old_Left_Time_Int = atoi(old_Left_Time_String);
		new_Left_Time_Int = old_Left_Time_Int - d_time;
		if(new_Left_Time_Int < 0)
		{
			new_Left_Time_Int = 0;
		}
		else
		{
			;
		}
		inttoa(new_Left_Time_Int,new_Left_Time_String,10);
//		printf("EXIT *UNDATE LEFT TIME!");
		return new_Left_Time_String;
	}
	else
	{	
//		printf("EXIT *UNDATE LEFT TIME!");
		return NULL;
	}
}



void inttoa(unsigned int val,char *buf, unsigned int radix)   
{  
	
//	printf("ENTER INT TO CHAR ARRAY!\n");
	char   reverse[15];               
	unsigned char index=0;
	unsigned char remainder;
	unsigned int quotient;               
	quotient = val;  
	while(1)
	{
		remainder = quotient % radix;
		quotient = quotient / radix;
		reverse[index]=remainder+'0';
		if(quotient == 0)
		{	
			reverse[index+1] = '\0';
			break;
		}
		else
		{
			index++;
		}
	}
	int i=0;	
	for(i=0; i<index+1; i++)
	{
		*(buf+i)=reverse[index-i];
	}
	*(buf+index+1)= '\0';
//	printf("EXIT INT TO CHAR ARRAY!\n");
}

