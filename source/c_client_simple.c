//---------------------------------------------------------------------------
//---  c_client.c
//---  Author:    Steve Oliver
//---  Date:      June 19, 2012
//---  Purpose:   Simple C application to test calling libgeo.so 
//---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

//below is not needed - it is holdover from other application
#if defined(WIN32) 
#define ROLE __declspec(dllimport) __stdcall
//#define ROLE __declspec(dllimport) 
#elif defined(x64)
#define ROLE __declspec(dllimport) __stdcall
#elif defined(__linux__)
#define ROLE __stdcall
#endif

#define DELIMITERS    ";,‘"


//contains definition for geo in libgeo.so 
//#include "geo.h"
//contains the wa1 and wa2 layouts 
#include "pac.h"

#pragma hdrstop

void call_func_1a();
void call_func_ap();

extern void geo(char *ptr_wa1, char *ptr_wa2);

char fakevar;
int idx = 0;
time_t t;
char dash_line[120];

char exit_sw;
char function_sw[3];
char *pfunction_sw;
int result;
char input_str[80]; 

int i;
char conv_num[3];

int in_cnt, out_cnt, err_cnt = 0;

union {
        C_WA1 wa1;
        char cwa1[1200];
      } uwa1;
union {
        C_WA2_F1 wa2_f1;
        char cwa2f1[sizeof(C_WA2_F1)];
      } uwa2f1;
union {
        C_WA2_F1EX wa2_f1ex;
        char cwa2f1ex[sizeof(C_WA2_F1EX)];
      } uwa2f1ex;
union {
        C_WA2_FAP wa2_fap;
        char cwa2fap[sizeof(C_WA2_FAP)];
      } uwa2fap;
union {
        C_WA2_FAPX wa2_fapx;
        char cwa2fapx[sizeof(C_WA2_FAPX)];
      } uwa2fapx;
union {
        C_WA2_F1A wa2_f1a;
        char cwa2f1a[sizeof(C_WA2_F1A)];
      } uwa2f1a;
union {
        C_WA2_F1AX wa2_f1ax;
        char cwa2f1ax[sizeof(C_WA2_F1AX)];
      } uwa2f1ax;
union {
        C_WA2_F1B wa2_f1B;
        char cwa2f1b[sizeof(C_WA2_F1B)];
      } uwa2f1b;
union {
        C_WA2_F2 wa2_f2;
        char cwa2f2[sizeof(C_WA2_F2)];
      } uwa2f2;
union {
        C_WA2_F2W wa2_f2w;
        char cwa2f2w[sizeof(C_WA2_F2W)];
      } uwa2f2w;
union {
        C_WA2_F3 wa2_f3;
        char cwa2f3[sizeof(C_WA2_F3)];
      } uwa2f3;
union {
        C_WA2_F3C wa2_f3c;
        char cwa2f3c[sizeof(C_WA2_F3C)];
      } uwa2f3c;
union {
        C_WA2_F3_AUXSEG wa2_f3as;
        char cwa2f3as[sizeof(C_WA2_F3_AUXSEG)];
      } uwa2f3as;
union {
        C_WA2_F3C_AUXSEG wa2_f3cas;
        char cwa2f3cas[sizeof(C_WA2_F3C_AUXSEG)];
      } uwa2f3cas;
union {
        C_WA2_F3X wa2_f3x;
        char cwa2f3x[sizeof(C_WA2_F3X)];
      } uwa2f3x;
union {
        C_WA2_F3CX wa2_f3cx;
        char cwa2f3cx[sizeof(C_WA2_F3CX)];
      } uwa2f3cx;
union {
        C_WA2_F3X_AUXSEG wa2_f3xas;
        char cwa2f3xas[sizeof(C_WA2_F3X_AUXSEG)];
      } uwa2f3xas;
union {
        C_WA2_F3CX_AUXSEG wa2_f3cxas;
        char cwa2f3xcas[sizeof(C_WA2_F3CX_AUXSEG)];
      } uwa2f3cxas;
union {
        C_WA2_F3S wa2_f3s;
        char cwa2f3s[sizeof(C_WA2_F3S)];
      } uwa2f3s;

// We don't have WA2 for function HR so use this 
char cwa2fhr[5000]; 

//---------------------------------------------------------------------------
//#pragma argsused

/*
https://stackoverflow.com/questions/12911299/read-csv-file-in-c
*/
char* getfield(char* line, int num)
{
     char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}



//---------------------------------------------------------------------------
void clearInput()
{
	int ch;
	for(ch=getchar();isspace(ch);ch=getchar());
	ungetc(ch, stdin);
	
}


void display1A(C_WA2_F1A uwa2_f1a){
	/*fflush(stdout);
	close(1);
	int fd;
	fd = open("sample.txt", O_RDWR, O_WRONLY| O_CREAT | O_TRUNC, 0644);

	if(fd==-1){
		printf("open failed");
		exit(1);
	}
	if(dup2(fd,1)==-1){
		printf("dup2 failed");
		exit(1);
	}*/

	FILE *fp;
	fp = fopen("sample.txt", "w+");
	fprintf(fp, "Latitude %.9s", uwa2f1a.wa2_f1a.latitude);

	fclose(fp);

	//write(fd, "test", strlen("test"));

	printf("Latitude %.9s", uwa2f1a.wa2_f1a.latitude);
	printf("\t");
	printf("Longitude %.9s", uwa2f1a.wa2_f1a.longitude);printf("\t");
	
printf("filler01 %.21s", uwa2f1a.wa2_f1a.filler01);printf("\t");

printf("cont_parity_ind %c", uwa2f1a.wa2_f1a.cont_parity_ind);printf("\t");
printf("lo_hse_nbr  %.11s", uwa2f1a.wa2_f1a.lo_hse_nbr);printf("\t");

//printf("bbl %.9s", uwa2f1a.wa2_f1a.bbl);printf("\t");
printf("filler02 %c", uwa2f1a.wa2_f1a.filler02);printf("\t");
printf("RPAD_scc %c", uwa2f1a.wa2_f1a.RPAD_scc);printf("\t");
printf("filler03 %c", uwa2f1a.wa2_f1a.filler03);printf("\t");
printf("RPAD_lucc[2] %.2s", uwa2f1a.wa2_f1a.RPAD_lucc);printf("\t");
printf("corner[2] %.2s", uwa2f1a.wa2_f1a.corner);printf("\t");
printf("nbr_blds[4] %.4s", uwa2f1a.wa2_f1a.nbr_blds);printf("\t");
printf("nbr_str[2] %.2s", uwa2f1a.wa2_f1a.nbr_str);printf("\t");
printf("inter_flag %c", uwa2f1a.wa2_f1a.inter_flag);printf("\t");
printf("vacant_flag %c", uwa2f1a.wa2_f1a.vacant_flag);printf("\t");
printf("irreg_flag %c", uwa2f1a.wa2_f1a.irreg_flag);printf("\t");
printf("mh_ri_flag %c", uwa2f1a.wa2_f1a.mh_ri_flag);printf("\t");
printf("adr_range_overflow %c", uwa2f1a.wa2_f1a.adr_range_overflow);printf("\t");
printf("stroll_key[18] %.18s", uwa2f1a.wa2_f1a.stroll_key);printf("\t");
printf("filler04 %c", uwa2f1a.wa2_f1a.filler04);printf("\t");
printf("res_internal_use %c", uwa2f1a.wa2_f1a.res_internal_use);printf("\t");
printf("bld_id[7] %.7s", uwa2f1a.wa2_f1a.bld_id);printf("\t");
printf("condo_flag %c", uwa2f1a.wa2_f1a.condo_flag);printf("\t");
printf("filler05 %c", uwa2f1a.wa2_f1a.filler05);printf("\t");
printf("condo_id[4] %.4s", uwa2f1a.wa2_f1a.condo_id);printf("\t");
printf("condo_unit_id[7] %.7s", uwa2f1a.wa2_f1a.condo_unit_id);printf("\t");
//printf("condo_bill_bbl %.9s", uwa2f1a.wa2_f1a.condo_bill_bbl);printf("\t");
printf("filler06 %c", uwa2f1a.wa2_f1a.filler06);printf("\t");
printf("condo_scc %c", uwa2f1a.wa2_f1a.condo_scc);printf("\t");
//printf("condo_lo_bbl %.9s", uwa2f1a.wa2_f1a.condo_lo_bbl);printf("\t");
printf("filler07 %c", uwa2f1a.wa2_f1a.filler07);printf("\t");
//printf("condo_hi_bbl %.9s", uwa2f1a.wa2_f1a.condo_hi_bbl);printf("\t");
printf("filler08 %c", uwa2f1a.wa2_f1a.filler08);printf("\t");
printf("filler09[15] %.15s", uwa2f1a.wa2_f1a.filler09);printf("\t");
printf("co_op_nbr[4] %.4s", uwa2f1a.wa2_f1a.co_op_nbr);printf("\t");
//printf("San %.9s", uwa2f1a.wa2_f1a.San);printf("\t");
printf("business_area[5] %.5s", uwa2f1a.wa2_f1a.business_area);printf("\t");
printf("tax_map_nbr[5] %.5s", uwa2f1a.wa2_f1a.tax_map_nbr);printf("\t");
printf("filler10[4] %.4s", uwa2f1a.wa2_f1a.filler10);printf("\t");
printf("filler11[3] %.3s", uwa2f1a.wa2_f1a.filler11);printf("\t");
printf("latitude[9] %.9s", uwa2f1a.wa2_f1a.latitude);printf("\t");
printf("longitude[11] %.11s", uwa2f1a.wa2_f1a.longitude);printf("\t");
//printf("coord[2][7] %.9s", uwa2f1a.wa2_f1a.coord[2][7]);printf("\t");
printf("bid_id[6] %.6s", uwa2f1a.wa2_f1a.bid_id);printf("\t");
printf("TPAD_bin_status %c", uwa2f1a.wa2_f1a.TPAD_bin_status);printf("\t");
printf("TPAD_new_bin[7] %.7s", uwa2f1a.wa2_f1a.TPAD_new_bin);printf("\t");
printf("TPAD_new_bin_status %c", uwa2f1a.wa2_f1a.TPAD_new_bin_status);printf("\t");
printf("TPAD_conflict_flag %c", uwa2f1a.wa2_f1a.TPAD_conflict_flag);printf("\t");
printf("filler12[9] %.9s", uwa2f1a.wa2_f1a.filler12);printf("\t");
printf("int_use[8] %.8s", uwa2f1a.wa2_f1a.int_use);printf("\t");
printf("nbr_addr[4] %.4s", uwa2f1a.wa2_f1a.nbr_addr);printf("\t");
//close(fd);


}

//---------------------------------------------------------------------------
void call_func_1a ()
{
	char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "1A", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a boro code:  ");
	clearInput();
	//gets(input_str);
	fgets(input_str,80,stdin);
	uwa1.wa1.input.sti[0].boro = input_str[0]; 

	printf("\n\n*****  Enter a housenumber:  ");
	//gets(input_str);
	clearInput();
	fgets(input_str,80,stdin);
	//memcpy(uwa1.wa1.input.hse_nbr_disp, "22", 2); 
	memcpy(uwa1.wa1.input.hse_nbr_disp, input_str, strlen(input_str)-1); 
	printf("\n value of hse nbr: %s", input_str); 

	printf("\n\n*****  Enter a street name:  ");
	//gets(input_str);
	clearInput();
	fgets(input_str,80,stdin);
	memcpy(uwa1.wa1.input.sti[0].Street_name, input_str, strlen(input_str)); 
	printf("\n value of street name: %s", input_str); 

	printf("\n\n*****  Do you want TPAD data:  ");
	//gets(input_str);
	clearInput();
	fgets(input_str,80,stdin);
	if (input_str[0]== 'Y' || input_str[0] == 'y') 
	{
		uwa1.wa1.input.tpad_switch = input_str[0]; 
	}

	printf("\n\n*****  Enter 'X' for Extended Work Area:  ");
	//gets(input_str);
	clearInput();
	fgets(input_str,80,stdin);
	if (input_str[0]== 'X' || input_str[0] == 'x') 
	{
		uwa1.wa1.input.mode_switch = input_str[0]; 
	}

	if (input_str[0]== 'X' || input_str[0] == 'x') 
	{
		geo(uwa1.cwa1, uwa2f1ax.cwa2f1ax);
	}
	else
	{
		geo(uwa1.cwa1, uwa2f1a.cwa2f1a);
	}

	printf("\n\nFunction 1A GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
		if (input_str[0]== 'X' || input_str[0] == 'x') 
		{
			// displays the first 80 bytes of wa2 
			printf("uwa2f1ax.cwa2f1ax = %.80s\n", uwa2f1ax.cwa2f1ax);
		}
		else 
		{
			// displays the first 80 bytes of wa2 
			printf("uwa2f1a.cwa2f1a = %.80s\n", uwa2f1a.cwa2f1a);
			//printf("Latitude %.9s", uwa2f1a.wa2_f1a.latitude);
			display1A(uwa2f1a.wa2_f1a);
	
		}
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}
}  // end of call_func_1a () 


//---------------------------------------------------------------------------
void func_1a_call_param (char* hsnbr, char* sname, char* bcode, char* tpad_switch, char* extended_work_area)
{
	char *pmode_switch;



			printf("in param Field 2 is House Number %s\t", hsnbr);
			printf("Field 3 is Street Name %s\t", sname);
			printf("Field 4 is Borough Code %s\n", bcode);
			printf("bjb %ld", strlen(bcode));

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "1A", 2);
	uwa1.wa1.input.platform_ind = 'C';

	//printf("\n\n*****  Enter a boro code:  ");
	//clearInput();
	//gets(input_str);
	//fgets(input_str,80,stdin);
	uwa1.wa1.input.sti[0].boro = bcode[1]; 
	printf("\n value of boro code : %c", uwa1.wa1.input.sti[0].boro); 
	//printf("\n\n*****  Enter a housenumber:  ");
	//gets(input_str);
	//clearInput();
	//fgets(input_str,80,stdin);
	//memcpy(uwa1.wa1.input.hse_nbr_disp, "22", 2); 
	memcpy(uwa1.wa1.input.hse_nbr_disp, hsnbr, strlen(hsnbr)); 
		printf("\n value of shsnbr %s", hsnbr); 

	printf("\n value of hse nbr: %s", uwa1.wa1.input.hse_nbr_disp); 

	//printf("\n\n*****  Enter a street name:  ");
	//gets(input_str);
	//clearInput();
	//fgets(input_str,80,stdin);
	memcpy(uwa1.wa1.input.sti[0].Street_name, sname, strlen(sname)); 
	printf("\n value of street name: %s", sname); 

	printf("\n value of street name: %s", uwa1.wa1.input.sti[0].Street_name); 

	//printf("\n\n*****  Do you want TPAD data:  ");
	//gets(input_str);
	//clearInput();
	//fgets(input_str,80,stdin);
	if (tpad_switch[0] == 'Y' || tpad_switch[0] == 'y') 
	{
		uwa1.wa1.input.tpad_switch = input_str[0]; 
	}

//	printf("\n\n*****  Enter 'X' for Extended Work Area:  ");
	//gets(input_str);
	//clearInput();
	//fgets(input_str,80,stdin);
	
	
	if (extended_work_area[0]== 'X' || extended_work_area[0]== 'x') 
	{
		uwa1.wa1.input.mode_switch = extended_work_area[0]; 
	}

	if (extended_work_area[0]== 'X' || extended_work_area[0] == 'x') 
	{
		geo(uwa1.cwa1, uwa2f1ax.cwa2f1ax);
	}
	else
	{
		geo(uwa1.cwa1, uwa2f1a.cwa2f1a);
	}

	printf("\n\nFunction 1A GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
		if (input_str[0]== 'X' || input_str[0] == 'x') 
		{
			// displays the first 80 bytes of wa2 
			printf("uwa2f1ax.cwa2f1ax = %.80s\n", uwa2f1ax.cwa2f1ax);
		}
		else 
		{
			// displays the first 80 bytes of wa2 
			printf("uwa2f1a.cwa2f1a = %.80s\n", uwa2f1a.cwa2f1a);
			//printf("Latitude %.9s", uwa2f1a.wa2_f1a.latitude);
			display1A(uwa2f1a.wa2_f1a);
	
		}
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}
}  // end of call_func_1a () 


int main(int argc, char* argv[])
{

	    FILE* stream = fopen("input.txt", "r");

		char line[1024];
		char hsnbr_arr[10];
		char sname_arr[10];
		char bcode_arr[10];

		while (fgets(line, 1024, stream))
		{

			char* token = strtok(line, DELIMITERS);
			int cnt = 0;
			while(token != NULL)
			{    // While there are tokens in "string"
				// ...
				// doing some thing with token
				// ...
				// Get next token
				if(cnt==1)
					strcpy(hsnbr_arr, token);
				if(cnt==2)
					strcpy(sname_arr, token);
				if(cnt==3){
					//strcpy(bcode_arr, token);
					//bcode_arr[strlen(token)]=
					strncpy(bcode_arr, token, sizeof token - 1);
					bcode_arr[sizeof token - 1]='\0';
				}
				token = strtok(NULL, DELIMITERS);
				cnt++;
			}

			puts(hsnbr_arr);
/*
			char* hsnbr = strdup(line);
			char* sname = strdup(line);
			char* bcode = strdup(line);

			printf("Field 2 is House Number %s\t", getfield(hsnbr, 2));
			char chsnbr=malloc(strlen(hsnbr) + 1);
			memcpy(chsnbr, hsnbr, strlen(hsnbr));
			printf("Field 3 is Street Name %s\t", getfield(sname, 3));
			printf("Field 4 is Borough Code %s\n", getfield(bcode, 4));
			// NOTE strtok clobbers tmp
			//const char* chsnbr = getfield(hsnbr, 2);*/

					
	

			func_1a_call_param(hsnbr_arr, sname_arr, bcode_arr, "n", "n");

		/*	free(hsnbr);
			free(sname);
			free(bcode);*/
		}
/*
        time(&t);
        memset(dash_line, '-', sizeof(dash_line));
		dash_line[120] = '\0';

		//_strset(dash_line, '-'); 
		exit_sw = 'N';
        while(exit_sw != 'X')
        {
			printf("\n\n%.90s", dash_line);
			printf("\n*****  Enter a function code or 'X' to exit:  ");
			fgets(function_sw,3,stdin);
			
			if (function_sw[0] == 'X' || function_sw[0] == 'x') 
			{
				exit_sw = 'X';
				continue;
			}
			else
			{
				printf("You entered %s\n", function_sw); 
			}
			
			if (strcmp(function_sw, "1A") == 0 || strcmp(function_sw, "1a") == 0)
			{
				call_func_1a();
			}
			else
			{
				printf("\nPlease use:  1, 1E, 2, 3, 3C, AP, 1A, BL, BN, 1N, D, DG, DN, HR or X\n");
				continue;
			}

			printf("\n\n");

		}  // end of while(exit_sw = 'N') loop
*/
        return 0;

}  // end of main