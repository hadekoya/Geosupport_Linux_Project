//---------------------------------------------------------------------------
//---  c_client.c
//---  Author:    Steve Oliver
//---  Date:      June 19, 2012
//---  Purpose:   C client application to test wa_display dll
//---------------------------------------------------------------------------
//---  SPO(2017-11-03): Added new fields for release 17D
//--                    Speed Limit Functions 1EX, 1B
//--                    and 3, 3C, 3X, 3CX
//--                    DCP Zoning Map - 1A, 1AX, 1B

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#if defined(WIN32) 
#define ROLE __declspec(dllimport) __stdcall
//#define ROLE __declspec(dllimport) 
#elif defined(x64)
#define ROLE __declspec(dllimport) __stdcall
#elif defined(__linux__)
#define ROLE __stdcall
#endif

#include "geo.h"
#include "pac.h"
//#include "wa_display.h"
#include "wa_fields.h"

#pragma hdrstop


//union {
//	struct {
//		char rectype;
//		char boro;
//		char stname[32];
//		char primary_flag;
//		char principal_flag;
//		char b10sc[11];
//		char filler1[2];
//		char numeric_ind;
//		char attr_flag;
//		char full_name_len[2];
//		char full_name[32];
//		char min_snl[2];
//		char min_name[32];
//		char lgc_snl[2];
//		char lgc_name[32];
//		char filler2[47];
//		char crlf[2];
//	} fin_rec;
//	char fin[202];
//} ufin;
//
//union {
//	struct {
//		char rectype;
//		char boro;
//		char stname[32];
//		char primary_flag;
//		char principal_flag;
//		char b10sc[11];
//		char filler1[2];
//		char numeric_ind;
//		char attr_flag;
//		char full_name_len[2];
//		char full_name[32];
//		char min_snl[2];
//		char min_name[32];
//		char lgc_snl[2];
//		char lgc_name[32];
//		char filler2[47];
//		char crlf[2];
//	} fout_rec;
//	char fout[202];
//} ufout;

void call_func_1();
void call_func_1e();
void call_func_1a();
void call_func_2();
void call_func_2w();
void call_func_3();
void call_func_3c();
void call_func_3s();
void call_func_ap();
void call_func_bl();
void call_func_bn();
void call_func_d();
void call_func_dg();
void call_func_dn();
void call_func_hr();
void call_func_1n();

//int const ROWS = 400;
//int const COLS = 80;
#define ROWS 400
#define COLS 80 

void disp_wa2_parms(char *wa2_string, PFIELDENTRY wa2_flds, 
	 int number_of_fields, int *start_row, char disp[ROWS][COLS]); 
void column_map1(char *line);
void column_map2(char *line);

void disp_wa2_f3s_stnames(char *wa2_string, PFIELDENTRY wa2_flds,
	int number_of_fields, int *start_row, char disp[ROWS][COLS]);

void disp_wa2_f3s_b7scs(char *wa2_string, PFIELDENTRY wa2_flds,
	int number_of_fields, int *start_row, char disp[ROWS][COLS]);

void fdg(char, char sc7[], char compact);
void open_files();

//FILE *insnd, *outsnd, *errsnd, *logsnd;

char fakevar;
int idx = 0;
time_t t;
char dash_line[120];

char exit_sw;
char function_sw[3];
char *pfunction_sw;
int result;
char input_str[80]; 

char lo_stns[5][32];
char hi_stns[5][32];
char lo_hnd[16];
char hi_hnd[16];

char error;
char found;
char const FALSE = '0';
char const TRUE = '1';
char const NO = '0';
char const YES = '1';
int charread;
int charwritten;
char smallest_stname[32];
char smallest_b10sc[11];
int smallest_change_cnt = 0;
char hold_boro;
char hold_stname[32];
char temp_boro;
char temp_stname[32];
char temp_b10sc[11];
int i;
char conv_num[3];
int similar_names_cnt;
char check_stname[33];

int f1n_ok_cnt, f1n_err_cnt = 0;
int fdg_ok_cnt, fdg_err_cnt = 0;
int smallest_ok_cnt, smallest_err_cnt = 0;
int smallest_sort_ok_cnt, smallest_sort_err_cnt = 0;

int in_cnt, out_cnt, err_cnt = 0;

//int const ROWS = 400; 
//int const COLS = 80; 

//#define ROWS 400
//#define COLS 80 
//#define COLS 120 

int array_start, *p_array_start; 

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

//char my_array[400][80];
char my_array[ROWS][COLS];

//
void clear_display(char *array, char c)
{
	memset(array, c, COLS*ROWS);

}  //end of clear_display 

//

//---------------------------------------------------------------------------
//#pragma argsused


int main(int argc, char* argv[])
{

		array_start = 0;
		p_array_start = &array_start;

        //time(&t);
        memset(dash_line, '-', sizeof(dash_line));
		dash_line[119] = '\0';

		//_strset(dash_line, '-'); 
		exit_sw = 'N';
        while(exit_sw != 'X')
        {
			printf("\n\n%.90s", dash_line);
			printf("\n*****  Enter a function code or 'X' to exit:  ");
			gets(function_sw);

			clear_display((char*)my_array, ' ');
			*p_array_start = 0;
			
			if (function_sw[0] == 'X' || function_sw[0] == 'x') 
			{
				exit_sw = 'X';
				continue;
			}
			else
			{
				printf("You entered %s\n", function_sw); 
			}

			if (strcmp(function_sw, "AP") == 0 || strcmp(function_sw, "ap") == 0)
			{
				call_func_ap();
			}
			else if (strcmp(function_sw, "1A") == 0 || strcmp(function_sw, "1a") == 0)
			{
				call_func_1a();
			}
			else if (strcmp(function_sw, "BL") == 0 || strcmp(function_sw, "bl") == 0)
			{
				call_func_bl();
			}
			else if (strcmp(function_sw, "BN") == 0 || strcmp(function_sw, "bn") == 0)
			{
				call_func_bn();
			}
			else if (strcmp(function_sw, "1") == 0)
			{
				call_func_1();
			}
			else if (strcmp(function_sw, "1E") == 0 || strcmp(function_sw, "1e") == 0)
			{
				call_func_1e();
			}
			else if (strcmp(function_sw, "2") == 0)
			{
				call_func_2();
			}
			else if (strcmp(function_sw, "2w") == 0)
			{
				call_func_2w();
			}
			else if (strcmp(function_sw, "3") == 0)
			{
				call_func_3();
			}
			else if (strcmp(function_sw, "3C") == 0 || strcmp(function_sw, "3c") == 0)
			{
				call_func_3c();
			}
			else if (strcmp(function_sw, "3S") == 0 || strcmp(function_sw, "3s") == 0)
			{
				call_func_3s();
			}
			else if (strcmp(function_sw, "1N") == 0 || strcmp(function_sw, "1n") == 0)
			{
				call_func_1n();
			}
			else if (strcmp(function_sw, "D") == 0 || strcmp(function_sw, "d") == 0)
			{
				call_func_d();
			}
			else if (strcmp(function_sw, "DG") == 0 || strcmp(function_sw, "dg") == 0)
			{
				call_func_dg();
			}
			else if (strcmp(function_sw, "DN") == 0 || strcmp(function_sw, "dn") == 0)
			{
				call_func_dn();
			}
			else if (strcmp(function_sw, "HR") == 0 || strcmp(function_sw, "hr") == 0)
			{
				call_func_hr();
			}
			else
			{
				printf("\nPlease use:  1, 1E, 2, 3, 3C, AP, 1A, BL, BN, 1N, D, DG, DN, HR or X\n");
				continue;
			}

			printf("\n\n");
			//for (i = 0; i < 200; i++)
			for (i = 0; i < *p_array_start; i++)
			{
				printf("[%3d]: %.80s\n", i, my_array[i]);
			}

		}  // end of while(exit_sw = 'N') loop

        return 0;

}  // end of main

//---------------------------------------------------------------------------
void call_func_hr ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "HR", 2);
	uwa1.wa1.input.platform_ind = 'C';

	geo(uwa1.cwa1, cwa2fhr);

	printf("\n\nFunction HR GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
		disp_wa2_parms(cwa2fhr, wa2_fhr_flds, n_wa2_fhr_field_recs, 
						 p_array_start, my_array);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_hr () 

//---------------------------------------------------------------------------
void call_func_ap ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "AP", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a boro code:  ");
	gets(input_str);
	uwa1.wa1.input.sti[0].boro = input_str[0]; 

	printf("\n\n*****  Enter a housenumber:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.hse_nbr_disp, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter a street name:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].Street_name, input_str, strlen(input_str)); 

	printf("\n\n*****  Do you want TPAD data:  ");
	gets(input_str);
	if (input_str[0]== 'Y' || input_str[0] == 'y') 
	{
		uwa1.wa1.input.tpad_switch = input_str[0]; 
	}

	printf("\n\n*****  Enter 'X' for Extended Work Area:  ");
	gets(input_str);
	if (input_str[0]== 'X' || input_str[0] == 'x') 
	{
		uwa1.wa1.input.mode_switch = input_str[0]; 
	}

	if (input_str[0]== 'X' || input_str[0] == 'x') 
	{
		geo(uwa1.cwa1, uwa2fapx.cwa2fapx);
	}
	else
	{
		geo(uwa1.cwa1, uwa2fap.cwa2fap);
	}

	printf("\n\nFunction AP GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
		if (input_str[0]== 'X' || input_str[0] == 'x') 
		{
			disp_wa2_parms(uwa2fapx.cwa2fapx, wa2_fapx_flds, n_wa2_fapx_field_recs, 
						 p_array_start, my_array);
		}
		else
		{
			disp_wa2_parms(uwa2fap.cwa2fap, wa2_fap_flds, n_wa2_fap_field_recs, 
						 p_array_start, my_array);
		}
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_ap () 

//---------------------------------------------------------------------------
void call_func_1a ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "1A", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a boro code:  ");
	gets(input_str);
	uwa1.wa1.input.sti[0].boro = input_str[0]; 

	printf("\n\n*****  Enter a housenumber:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.hse_nbr_disp, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter a street name:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].Street_name, input_str, strlen(input_str)); 

	printf("\n\n*****  Do you want TPAD data:  ");
	gets(input_str);
	if (input_str[0]== 'Y' || input_str[0] == 'y') 
	{
		uwa1.wa1.input.tpad_switch = input_str[0]; 
	}

	printf("\n\n*****  Enter 'X' for Extended Work Area:  ");
	gets(input_str);
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
			disp_wa2_parms(uwa2f1ax.cwa2f1ax, wa2_f1ax_flds, n_wa2_f1ax_field_recs, 
						 p_array_start, my_array);
		}
		else 
		{
			disp_wa2_parms(uwa2f1a.cwa2f1a, wa2_f1a_flds, n_wa2_f1a_field_recs, 
						 p_array_start, my_array);
		}
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_1a () 

//---------------------------------------------------------------------------
void call_func_bl ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "BL", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a boro code:  ");
	gets(input_str);
	uwa1.wa1.input.bbli.cas.boro = input_str[0]; 

	printf("\n\n*****  Enter a tax block number:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.bbli.cas.block, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter a tax lot number:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.bbli.cas.lot, input_str, strlen(input_str)); 

	printf("\n\n*****  Do you want TPAD data:  ");
	gets(input_str);
	if (input_str[0]== 'Y' || input_str[0] == 'y') 
	{
		uwa1.wa1.input.tpad_switch = input_str[0]; 
	}

	printf("\n\n*****  Enter 'X' for Extended Work Area:  ");
	gets(input_str);
	if (input_str[0]== 'X' || input_str[0] == 'x') 
	//pmode_switch = _strupr(gets(input_str));
	//if (pmode_switch[0] == 'X') 
	{
		uwa1.wa1.input.mode_switch = input_str[0]; 
	}

	if (input_str[0]== 'X' || input_str[0] == 'x') 
	//if (*pmode_switch == 'X')
	{
		geo(uwa1.cwa1, uwa2f1ax.cwa2f1ax);
	}
	else
	{
		geo(uwa1.cwa1, uwa2f1a.cwa2f1a);
	}

	printf("\n\nFunction BL GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
			if (input_str[0]== 'X' || input_str[0] == 'x') 
			//if (*pmode_switch == 'X')
			disp_wa2_parms(uwa2f1ax.cwa2f1ax, wa2_f1ax_flds, n_wa2_f1ax_field_recs, 
						 p_array_start, my_array);
		else
			disp_wa2_parms(uwa2f1a.cwa2f1a, wa2_f1a_flds, n_wa2_f1a_field_recs, 
						 p_array_start, my_array);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_bl () 

//---------------------------------------------------------------------------
void call_func_bn ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "BN", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a BIN:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.bld_id, input_str, strlen(input_str)); 

	printf("\n\n*****  Do you want TPAD data:  ");
	gets(input_str);
	if (input_str[0]== 'Y' || input_str[0] == 'y') 
	{
		uwa1.wa1.input.tpad_switch = input_str[0]; 
	}

	printf("\n\n*****  Enter 'X' for Extended Work Area:  ");
	gets(input_str);
	if (input_str[0]== 'X' || input_str[0] == 'x') 
	//pmode_switch = _strupr(gets(input_str));
	//if (pmode_switch[0] == 'X') 
	{
		uwa1.wa1.input.mode_switch = input_str[0]; 
	}

	if (input_str[0]== 'X' || input_str[0] == 'x') 
	//if (*pmode_switch == 'X')
	{
		geo(uwa1.cwa1, uwa2f1ax.cwa2f1ax);
	}
	else
	{
		geo(uwa1.cwa1, uwa2f1a.cwa2f1a);
	}

	printf("\n\nFunction BN GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
			if (input_str[0]== 'X' || input_str[0] == 'x') 
			//if (*pmode_switch == 'X')
			disp_wa2_parms(uwa2f1ax.cwa2f1ax, wa2_f1ax_flds, n_wa2_f1ax_field_recs, 
						 p_array_start, my_array);
		else
			disp_wa2_parms(uwa2f1a.cwa2f1a, wa2_f1a_flds, n_wa2_f1a_field_recs, 
						 p_array_start, my_array);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_bn () 

//---------------------------------------------------------------------------
void call_func_1 ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "1 ", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a boro code:  ");
	gets(input_str);
	uwa1.wa1.input.sti[0].boro = input_str[0]; 

	printf("\n\n*****  Enter a housenumber:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.hse_nbr_disp, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter a street name:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].Street_name, input_str, strlen(input_str)); 

    printf("\n\n*****  Enter 'R' for Roadbed Data:  ");
    gets(input_str);
    if (input_str[0] == 'R' || input_str[0] == 'r')
    {
        uwa1.wa1.input.roadbedrequest = input_str[0];
    }
    
    printf("\n\n*****  Enter 'X' for Extended Work Area:  ");
	gets(input_str);
	if (input_str[0]== 'X' || input_str[0] == 'x') 
	//pmode_switch = _strupr(gets(input_str));
	//if (pmode_switch[0] == 'X') 
	{
		uwa1.wa1.input.mode_switch = input_str[0]; 
	}

	if (input_str[0]== 'X' || input_str[0] == 'x') 
	//if (*pmode_switch == 'X')
	{
		geo(uwa1.cwa1, uwa2f1ex.cwa2f1ex);
	}
	else
	{
		geo(uwa1.cwa1, uwa2f1.cwa2f1);
	}

	printf("\n\nFunction 1 GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
			if (input_str[0]== 'X' || input_str[0] == 'x') 
			//if (*pmode_switch == 'X')
			//disp_wa2_f1ex(uwa2f1ex.wa2_f1ex, p_array_start, my_array);
			disp_wa2_parms(uwa2f1ex.cwa2f1ex, wa2_f1ex_flds, n_wa2_f1ex_field_recs, 
						 p_array_start, my_array);
		else
			//disp_wa2_f1(uwa2f1.wa2_f1, p_array_start, my_array);
			disp_wa2_parms(uwa2f1.cwa2f1, wa2_f1e_flds, n_wa2_f1e_field_recs, 
						 p_array_start, my_array);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}
}  // end of call_func_1 () 

//---------------------------------------------------------------------------
void call_func_1e ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "1E", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a boro code:  ");
	gets(input_str);
	uwa1.wa1.input.sti[0].boro = input_str[0]; 

	printf("\n\n*****  Enter a housenumber:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.hse_nbr_disp, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter a street name:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].Street_name, input_str, strlen(input_str)); 

    printf("\n\n*****  Enter 'R' for Roadbed Data:  ");
    gets(input_str);
    if (input_str[0] == 'R' || input_str[0] == 'r')
    {
        uwa1.wa1.input.roadbedrequest = input_str[0];
    }

    printf("\n\n*****  Enter 'X' for Extended Work Area:  ");
	gets(input_str);
	if (input_str[0]== 'X' || input_str[0] == 'x') 
	//pmode_switch = _strupr(gets(input_str));
	//if (pmode_switch[0] == 'X') 
	{
		uwa1.wa1.input.mode_switch = input_str[0]; 
	}

	if (input_str[0]== 'X' || input_str[0] == 'x') 
	//if (*pmode_switch == 'X')
	{
		geo(uwa1.cwa1, uwa2f1ex.cwa2f1ex);
	}
	else
	{
		geo(uwa1.cwa1, uwa2f1.cwa2f1);
	}

	printf("\n\nFunction 1E GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
			if (input_str[0]== 'X' || input_str[0] == 'x') 
			//if (*pmode_switch == 'X')
			//disp_wa2_f1ex(uwa2f1ex.wa2_f1ex, p_array_start, my_array);
			disp_wa2_parms(uwa2f1ex.cwa2f1ex, wa2_f1ex_flds, n_wa2_f1ex_field_recs, 
						 p_array_start, my_array);
		else
			//disp_wa2_f1e(uwa2f1.wa2_f1, p_array_start, my_array);
			disp_wa2_parms(uwa2f1.cwa2f1, wa2_f1e_flds, n_wa2_f1e_field_recs, 
						 p_array_start, my_array);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}
}  // end of call_func_1e () 

//---------------------------------------------------------------------------
void call_func_2 ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "2 ", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter 'y' for Node Input:  ");
	gets(input_str);
	if (input_str[0]== 'y' || input_str[0] == 'y') 
	{
		printf("\n\n*****  Enter a Node ID:  ");
		gets(input_str);
		memcpy(uwa1.wa1.input.node, input_str, strlen(input_str)); 
	}
	else 
	{
		printf("\n\n*****  Enter a boro code:  ");
		gets(input_str);
		uwa1.wa1.input.sti[0].boro = input_str[0]; 

		printf("\n\n*****  Enter the first cross-street:  ");
		gets(input_str);
		memcpy(uwa1.wa1.input.sti[0].Street_name, input_str, strlen(input_str)); 

		printf("\n\n*****  Enter the second cross-street:  ");
		gets(input_str);
		memcpy(uwa1.wa1.input.sti[1].Street_name, input_str, strlen(input_str)); 

		printf("\n\n*****  Enter a compass direction (if needed):  ");
		gets(input_str);
		uwa1.wa1.input.comp_direction = input_str[0];
	}

	geo(uwa1.cwa1, uwa2f2.cwa2f2);

	printf("\n\nFunction 2 GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
		disp_wa2_parms(uwa2f2.cwa2f2, wa2_f2_flds, n_wa2_f2_field_recs, 
						 p_array_start, my_array);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_2 () 

//---------------------------------------------------------------------------
void call_func_2w ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "2W", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter 'y' for Node Input:  ");
	gets(input_str);
	if (input_str[0]== 'y' || input_str[0] == 'y') 
	{
		printf("\n\n*****  Enter a Node ID:  ");
		gets(input_str);
		memcpy(uwa1.wa1.input.node, input_str, strlen(input_str)); 
	}
	else 
	{
		printf("\n\n*****  Enter a boro code:  ");
		gets(input_str);
		uwa1.wa1.input.sti[0].boro = input_str[0]; 

		printf("\n\n*****  Enter the first cross-street:  ");
		gets(input_str);
		memcpy(uwa1.wa1.input.sti[0].Street_name, input_str, strlen(input_str)); 

		printf("\n\n*****  Enter the second cross-street:  ");
		gets(input_str);
		memcpy(uwa1.wa1.input.sti[1].Street_name, input_str, strlen(input_str)); 

		printf("\n\n*****  Enter a compass direction (if needed):  ");
		gets(input_str);
		uwa1.wa1.input.comp_direction = input_str[0];
	}

	geo(uwa1.cwa1, uwa2f2w.cwa2f2w);

	printf("\n\nFunction 2 GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
		disp_wa2_parms(uwa2f2w.cwa2f2w, wa2_f2w_flds, n_wa2_f2w_field_recs, 
						 p_array_start, my_array);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
		if (memcmp(uwa1.wa1.output.ret_code, "03", 2) == 0) 
		{
			disp_wa2_parms(uwa2f2w.cwa2f2w, wa2_f2w_flds, n_wa2_f2w_field_recs, 
							 p_array_start, my_array);
		}
	}

}  // end of call_func_2w () 

//---------------------------------------------------------------------------
void call_func_3 ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "3 ", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a boro code:  ");
	gets(input_str);
	uwa1.wa1.input.sti[0].boro = input_str[0]; 

	printf("\n\n*****  Enter the on-street:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].Street_name, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter the first cross-street:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[1].Street_name, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter the second cross-street:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[2].Street_name, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter 'X' for Extended Work Area:  ");
	gets(input_str);
	if (input_str[0]== 'X' || input_str[0] == 'x') 
	//pmode_switch = _strupr(gets(input_str));
	//if (pmode_switch[0] == 'X') 
	{
		uwa1.wa1.input.mode_switch = input_str[0]; 
	}

	if (input_str[0]== 'X' || input_str[0] == 'x') 
	//if (*pmode_switch == 'X')
	{
		geo(uwa1.cwa1, uwa2f3x.cwa2f3x);
	}
	else
	{
		geo(uwa1.cwa1, uwa2f3.cwa2f3);
	}

	printf("\n\nFunction 3 GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
			if (input_str[0]== 'X' || input_str[0] == 'x') 
			//if (*pmode_switch == 'X')
			disp_wa2_parms(uwa2f3x.cwa2f3x, wa2_f3x_flds, n_wa2_f3x_field_recs, 
						 p_array_start, my_array);
		else
			disp_wa2_parms(uwa2f3.cwa2f3, wa2_f3_flds, n_wa2_f3_field_recs, 
						 p_array_start, my_array);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_3 () 

//---------------------------------------------------------------------------
void call_func_3c ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "3C", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a boro code:  ");
	gets(input_str);
	uwa1.wa1.input.sti[0].boro = input_str[0]; 

	printf("\n\n*****  Enter the on-street:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].Street_name, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter the first cross-street:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[1].Street_name, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter the second cross-street:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[2].Street_name, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter a compass direction:  ");
	gets(input_str);
	uwa1.wa1.input.comp_direction = input_str[0]; 

	printf("\n\n*****  Enter 'X' for Extended Work Area:  ");
	gets(input_str);
	if (input_str[0]== 'X' || input_str[0] == 'x') 
	//pmode_switch = _strupr(gets(input_str));
	//if (pmode_switch[0] == 'X') 
	{
		uwa1.wa1.input.mode_switch = input_str[0]; 
	}

	if (input_str[0]== 'X' || input_str[0] == 'x') 
	//if (*pmode_switch == 'X')
	{
		geo(uwa1.cwa1, uwa2f3cx.cwa2f3cx);
	}
	else
	{
		geo(uwa1.cwa1, uwa2f3c.cwa2f3c);
	}

	printf("\n\nFunction 3C GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
			if (input_str[0]== 'X' || input_str[0] == 'x') 
			//if (*pmode_switch == 'X')
			disp_wa2_parms(uwa2f3cx.cwa2f3cx, wa2_f3cx_flds, n_wa2_f3cx_field_recs, 
						 p_array_start, my_array);
		else
			disp_wa2_parms(uwa2f3c.cwa2f3c, wa2_f3c_flds, n_wa2_f3c_field_recs, 
						 p_array_start, my_array);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_3c () 

//---------------------------------------------------------------------------
void call_func_3s()
{
	printf("inside call_func_3s\n");

	char display_street_names = 'Y';

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "3S", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a boro code:  ");
	gets(input_str);
	uwa1.wa1.input.sti[0].boro = input_str[0];

	printf("\n\n*****  Enter the on-street:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].Street_name, input_str, strlen(input_str));

	printf("\n\n*****  Enter the first cross-street:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[1].Street_name, input_str, strlen(input_str));

	printf("\n\n*****  Enter the second cross-street:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[2].Street_name, input_str, strlen(input_str));

	printf("\n\n*****  Enter a compass direction for first cross street:  ");
	gets(input_str);
	uwa1.wa1.input.comp_direction = input_str[0];

    printf("\n\n*****  Enter a compass direction for second cross street:  ");
    gets(input_str);
    uwa1.wa1.input.comp_direction2 = input_str[0];
    
    printf("\n\n*****  Enter 'R' for Real Streets Only:  ");
	gets(input_str);
	if (input_str[0] == 'R' || input_str[0] == 'r')
		//pmode_switch = _strupr(gets(input_str));
		//if (pmode_switch[0] == 'X') 
	{
		uwa1.wa1.input.real_street_only = input_str[0];
	}

	printf("\n\n*****  Display Street Names (Y/N):  ");
	gets(input_str);
	if (input_str[0] == 'Y' || input_str[0] == 'y')
	{
		display_street_names = 'Y';
	}
	else if (input_str[0] == 'N' || input_str[0] == 'n')
	{
		display_street_names = 'N';
	}

	//printf("inside call_func_3s:  before geo 3s call \n");

	//printf("inside call_func_3s:  sizeof(C_WA2_F3S) = %i\n", sizeof(C_WA2_F3S));

	geo(uwa1.cwa1, uwa2f3s.cwa2f3s);
	//if (input_str[0] == 'X' || input_str[0] == 'x')
	//	//if (*pmode_switch == 'X')
	//{
	//	geo(uwa1.cwa1, uwa2f3cx.cwa2f3cx);
	//}
	//else
	//{
	//	geo(uwa1.cwa1, uwa2f3c.cwa2f3c);
	//}

	printf("\n\nFunction 3S GRC = %.2s\n"
		"Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0) ||
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
		if (display_street_names == 'Y')
		{
			disp_wa2_f3s_stnames(uwa2f3s.cwa2f3s, wa2_f3s_flds, n_wa2_f3s_field_recs,
				p_array_start, my_array);
		}
		else
		{
			disp_wa2_f3s_b7scs(uwa2f3s.cwa2f3s, wa2_f3s_flds, n_wa2_f3s_field_recs,
				p_array_start, my_array);
		}

		//disp_wa2_parms(uwa2f3s.cwa2f3s, wa2_f3s_flds, n_wa2_f3s_field_recs,
		//	p_array_start, my_array);

		//		p_array_start, my_array);//if (input_str[0] == 'X' || input_str[0] == 'x')
		//	//if (*pmode_switch == 'X')
		//	disp_wa2_parms(uwa2f3cx.cwa2f3cx, wa2_f3cx_flds, n_wa2_f3cx_field_recs,
		//		p_array_start, my_array);
		//else
		//	disp_wa2_parms(uwa2f3c.cwa2f3c, wa2_f3c_flds, n_wa2_f3c_field_recs,
		//		p_array_start, my_array);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_3s () 

//---------------------------------------------------------------------------
void call_func_1n ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "1N", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a boro code:  ");
	gets(input_str);
	uwa1.wa1.input.sti[0].boro = input_str[0]; 

	printf("\n\n*****  Enter a street name:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].Street_name, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter 'C' for Compact Format:  ");
	gets(input_str);
	uwa1.wa1.input.st_name_norm = input_str[0]; 

	printf("\n\n*****  Enter 'P' or 'F' for Browse Flag Type:  ");
	gets(input_str);
	uwa1.wa1.input.browse_flag = input_str[0]; 

	geo(uwa1.cwa1, NULL);

	printf("\n\nFunction 1N GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
		disp_wa2_parms(uwa1.cwa1, wa1_flds, n_wa1_field_recs, 
						 p_array_start, my_array);
	}
	else
	{
		disp_wa2_parms(uwa1.cwa1, wa1_flds, n_wa1_field_recs, 
						 p_array_start, my_array);
	}
}  // end of call_func_1n () 

//---------------------------------------------------------------------------
void call_func_d ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "D ", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a boro code:  ");
	gets(input_str);
	uwa1.wa1.input.sti[0].boro = input_str[0]; 

	printf("\n\n*****  Enter a 5-byte street code:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].SC10, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter 'C' for Compact Format:  ");
	gets(input_str);
	uwa1.wa1.input.st_name_norm = input_str[0]; 

	geo(uwa1.cwa1, NULL);

	printf("\n\nFunction 1N GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
		disp_wa2_parms(uwa1.cwa1, wa1_flds, n_wa1_field_recs, 
						 p_array_start, my_array);
	}
	else
	{
		disp_wa2_parms(uwa1.cwa1, wa1_flds, n_wa1_field_recs, 
						 p_array_start, my_array);
	}

}  // end of function_d () 

//---------------------------------------------------------------------------
void call_func_dg ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "DG", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a boro code:  ");
	gets(input_str);
	uwa1.wa1.input.sti[0].boro = input_str[0]; 

	printf("\n\n*****  Enter a 5-byte street code:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].SC10, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter a 2-byte LGC:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].SC10+5, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter 'C' for Compact Format:  ");
	gets(input_str);
	uwa1.wa1.input.st_name_norm = input_str[0]; 

	geo(uwa1.cwa1, NULL);

	printf("\n\nFunction 1N GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
		disp_wa2_parms(uwa1.cwa1, wa1_flds, n_wa1_field_recs, 
						 p_array_start, my_array);
	}
	else
	{
		disp_wa2_parms(uwa1.cwa1, wa1_flds, n_wa1_field_recs, 
						 p_array_start, my_array);
	}

}  // end of call_func_dg () 

//---------------------------------------------------------------------------
void call_func_dn ()
{
	//char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "DN", 2);
	uwa1.wa1.input.platform_ind = 'C';

	printf("\n\n*****  Enter a boro code:  ");
	gets(input_str);
	uwa1.wa1.input.sti[0].boro = input_str[0]; 

	printf("\n\n*****  Enter a 5-byte street code:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].SC10, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter a 2-byte LGC:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].SC10+5, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter a 3-byte SPV:  ");
	gets(input_str);
	memcpy(uwa1.wa1.input.sti[0].SC10+7, input_str, strlen(input_str)); 

	printf("\n\n*****  Enter 'C' for Compact Format:  ");
	gets(input_str);
	uwa1.wa1.input.st_name_norm = input_str[0]; 

	geo(uwa1.cwa1, NULL);

	printf("\n\nFunction 1N GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
		disp_wa2_parms(uwa1.cwa1, wa1_flds, n_wa1_field_recs, 
						 p_array_start, my_array);
	}
	else
	{
		disp_wa2_parms(uwa1.cwa1, wa1_flds, n_wa1_field_recs, 
						 p_array_start, my_array);
	}

}  // end of call_func_dn () 

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void fdg(char boro, char sc7[], char compact)
{
		//#include "NYCgeo.h"
        //printf("\n\tinside fdg");
        //memset(uwa1.cwa1,' ',sizeof(uwa1.wa1));
        memset(uwa1.cwa1,' ',sizeof(uwa1.wa1.input));
		uwa1.wa1.input.platform_ind = 'C';
        memcpy(uwa1.wa1.input.func_code, "DG", 2);
		//uwa1.wa1.input.sti[0].b10sc.boro = boro;
        //memcpy(uwa1.wa1.input.sti[0].b10sc.st_code, sc7, 7);
		uwa1.wa1.input.st_name_norm = compact;

		//NYCgeo(uwa1.cwa1, NULL);
		geo(uwa1.cwa1, NULL);

        //*******************************************
        //*** need to move normalized fields here
        //*******************************************

        //if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0) |
        //    (memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
        //{
        //        ++fdg_ok_cnt;
        //}
        //else
        //{
        //        ++fdg_err_cnt;
        //}

}  // end of fdg()

//---------------------------------------------------------------------------

//------------------------------------------------------------------------
//-- display wa2 using qag control cards (exported) 
//------------------------------------------------------------------------
void disp_wa2_parms(char *wa2_string, PFIELDENTRY wa2_flds, int number_of_fields, 
						  int *start_row, char disp[ROWS][COLS]) 
{

	int i,j,k;
	char *ptr_line;
	int col_start;
	char blank_line[80];
	//char label_str[80];
	//char value_str[80];
	int pad_value; 

	int array_offset = 0;

    char prt_fld_name[32];
	int prt_entry = 0;      
	char prt_val[33];                                                  
	int prt_start = 0;                                                      
	int prt_length = 0;                                                     
	int prt_matrix_entry = 0;                                               
	char prt_type = ' ';                                                    
	
	int start_struct;
	int end_struct; 

	memset(prt_fld_name, ' ', sizeof(prt_fld_name));      

	memset(blank_line, ' ', 80);
	//set the spacing between columns 
	pad_value = 2; 
	//pad_value = 5; 

	//sprintf(disp[*start_row], "Test of Wa2 Display using Parms .....");
	//
	////add a blank line 
	//(*start_row)++;

	////add 1st row of column markers 
	//(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp+*start_row)+col_start;
	memset(ptr_line, ' ', 80);
	column_map1(ptr_line);

	//add 2nd row of column markers 
	(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp+*start_row)+col_start;
	memset(ptr_line, ' ', 80);
	column_map2(ptr_line);

	//add a blank line 
	(*start_row)++;

	//printf("\nStart of print fields loop \n");
	//for (i = 0; i < number_of_fields; i++)
	i = 0; 
	while (i < number_of_fields)
	{
		if (wa2_flds[i].data_type == ' ')
		{
	        memcpy(prt_fld_name, wa2_flds[i].fld_name, sizeof(wa2_flds[i].fld_name));   
			prt_entry = 0; 
			if (wa2_flds[i].arr_entries > 0)
			{
				if (wa2_flds[i].start_structure > 0)   //structure in array
				{
					start_struct = wa2_flds[i].start_structure - 1;
					end_struct = wa2_flds[i].end_structure; 
					prt_start = wa2_flds[i].fld_start - 1; 
					for (k = 0; k < wa2_flds[i].arr_entries; k++)
					{
						//add a dashed line to separate new array structures 
						(*start_row)++;
						col_start = 0;
						ptr_line = (char*)(disp+*start_row)+col_start;
						memset(ptr_line, '-', 75);
						for (j = start_struct; j < end_struct; j++)
						{
					        memcpy(prt_fld_name, wa2_flds[j].fld_name, 
								   sizeof(wa2_flds[j].fld_name));   
							prt_entry = k + 1; 
							prt_length = wa2_flds[j].fld_len;
							if (prt_length > 32) prt_length = 32; 
							memcpy(prt_val, wa2_string+prt_start, prt_length);  
							prt_val[prt_length] = '\0';

							//add to array for later printing 
							(*start_row)++;
							col_start = 0;
							ptr_line = (char*)(disp+*start_row)+col_start;
							sprintf(ptr_line, "%.32s[%2d] \t %.32s",                            
								   prt_fld_name, prt_entry, prt_val); 

							prt_start += wa2_flds[j].fld_len;

							if (*start_row > 390)
							{
								//printf("First break because number of rows > 390\n");
								break;
							}
						}
						if (*start_row > 390)
						{
							//printf("Second break because number of rows > 390\n");
							break;
						}
					}
					// spo(2016-05-18):	I think we are skipping the field entry 
					//					just after a structured array 
					//					Try subtracting 1 for j 
					// i = j;  //this starts list after last structured array entry 
					i = j - 1;  //this starts list after last structured array entry 
					if (*start_row > 390)
					{
						//printf("Third break because number of rows > 390\n");
						break;
					}
				}
				else  //not a structure 
				{
			        memcpy(prt_fld_name, wa2_flds[i].fld_name, sizeof(wa2_flds[i].fld_name));   
					for (j = 0; j < wa2_flds[i].arr_entries; j++)
					{
						prt_start = (wa2_flds[i].fld_start - 1) + (wa2_flds[i].arr_len * j);
						prt_length = wa2_flds[i].arr_len;
						prt_entry = j + 1;
						if (prt_length > 32) prt_length = 32; 
						memcpy(prt_val, wa2_string+prt_start, prt_length);  
						prt_val[prt_length] = '\0';

						//add to array for later printing 
						(*start_row)++;
						col_start = 0;
						ptr_line = (char*)(disp+*start_row)+col_start;
						sprintf(ptr_line, "%.32s[%2d] \t %.32s",                            
							   prt_fld_name, prt_entry, prt_val); 

					}
				}
			}
			else // arr_entries = 0 i.e. not an array
			{
				memcpy(prt_fld_name, wa2_flds[i].fld_name, sizeof(wa2_flds[i].fld_name));   
				prt_start = wa2_flds[i].fld_start - 1;
				prt_length = wa2_flds[i].fld_len;
				if (prt_length > 32) prt_length = 32;
		        memcpy(prt_val, wa2_string+prt_start, prt_length);  
				prt_val[prt_length] = '\0';
				//printf("%.32s \t %.32s\n",                            
				//	   prt_fld_name, prt_val);           

				//add to array for later printing 
				(*start_row)++;
				col_start = 0;
				ptr_line = (char*)(disp+*start_row)+col_start;
				sprintf(ptr_line, "%.32s \t %.32s",                            
					   prt_fld_name, prt_val); 
			}
		}
		else // data_type <> ' ' i.e. hni or packed decimal (only for msw version) 
		{
		}

		i++;

		if (*start_row > 390)
		{
			//printf("Fourth break because number of rows > 390\n");
			break;
		}

	}  // end of for (i < number_of_fields)

	//add a blank line 
	(*start_row)++;

	//printf("leaving disp_elections\n");

}  //end of disp_wa2_parms


 //------------------------------------------------------------------------
 //-- display wa2 for f3s using workarea 2 (returns street names) 
 //------------------------------------------------------------------------
void disp_wa2_f3s_stnames(char *wa2_string, PFIELDENTRY wa2_flds, int number_of_fields,
	int *start_row, char disp[ROWS][COLS])
{
	printf("inside disp_wa2_f3s_stnames\n"); 

	int i, j, k;
	char *ptr_line;
	int col_start;
	char blank_line[80];
	//char label_str[80];
	//char value_str[80];
	int pad_value;

	int array_offset = 0;

	char prt_fld_name[32];
	int prt_entry = 0;
	char prt_val[33];
	int prt_start = 0;
	int prt_length = 0;
	int prt_matrix_entry = 0;
	char prt_type = ' ';

	int start_struct;
	int end_struct;

	memset(prt_fld_name, ' ', sizeof(prt_fld_name));

	memset(blank_line, ' ', 80);
	//set the spacing between columns 
	pad_value = 2;
	//pad_value = 5; 

	//sprintf(disp[*start_row], "Test of Wa2 Display using Parms .....");
	//
	////add a blank line 
	//(*start_row)++;

	////add 1st row of column markers 
	//(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	memset(ptr_line, ' ', 80);
	column_map1(ptr_line);

	//add 2nd row of column markers 
	(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	memset(ptr_line, ' ', 80);
	column_map2(ptr_line);

	//add a blank line 
	(*start_row)++;

	//printf("\nStart of print fields loop \n");
	//for (i = 0; i < number_of_fields; i++)
	i = 0;

	//Add Key and Number of Intersections 
	(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	sprintf(ptr_line, "FILLER                                    %.21s ", uwa2f3s.wa2_f3s.filler01);

	(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	sprintf(ptr_line, "NUMBER OF XSTREETS IN STRETCH             %.3s ", uwa2f3s.wa2_f3s.nbr_x_str);

	//add a dashed line to separate new array structures 
	(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	memset(ptr_line, '-', 78);

	//add a header line 
	(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	sprintf(ptr_line, "M DIST  G NODE-ID N FIRST INTERSECTING STREET      SECOND INTERSECTION STREET");

	//add a dash line for header line 
	(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	sprintf(ptr_line, "- ----- - ------- - ------------------------------ -------------------------------");

	//Use this to convert integer to character array so we can always display 3 characters
	char i_char[4];
	int idx_plus1 = 0; 
	size_t idx;

	//printf("inside disp_wa2_f3s_stnames:  before for loop\n");

	for (idx = 0; idx < 350; idx++)
	{
		(*start_row)++;
		col_start = 0;
		ptr_line = (char*)(disp + *start_row) + col_start;

		//add 1 to zero based idx 
		idx_plus1 = idx;
		idx_plus1++;

		//Use this to convert integer to character array so we can always display 3 characters
		sprintf(i_char, "%d", idx_plus1);
		i_char[3] = '\0';

		////Use this to convert integer to character array so we can always display 3 characters
		//sprintf(i_char, "%d", idx);
		//i_char[3] = '\0';

		memset(uwa1.cwa1, ' ', 1200);
		memcpy(uwa1.wa1.input.func_code, "DG", 2);
		uwa1.wa1.input.platform_ind = 'C';
		memcpy(uwa1.wa1.input.snl, "30", 2);
		// first intersecting street 
		uwa1.wa1.input.sti[0].boro = uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[0][0];
		memcpy(uwa1.wa1.input.sti[0].SC10, uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[0] + 1, 7);
		// second intersecting street 
		uwa1.wa1.input.sti[1].boro = uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[1][0];
		memcpy(uwa1.wa1.input.sti[1].SC10, uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[1] + 1, 7);

		//printf("\ninput boro = %c   input 7sc = %.6s\n", uwa1.wa1.input.sti[0].boro, uwa1.wa1.input.sti[0].SC10);

		//printf("inside disp_wa2_f3s_stnames:  before fdg inside for loop\n");

		geo(uwa1.cwa1, NULL);

		//printf("inside disp_wa2_f3s_stnames:  after fdg inside for loop\n");


		// Test of printing out street names 
		sprintf(ptr_line, "%c %.5s %c %.7s %c %.30s %.30s",
			uwa2f3s.wa2_f3s.cross_strs[idx].mh_ri_flag, uwa2f3s.wa2_f3s.cross_strs[idx].len,
			uwa2f3s.wa2_f3s.cross_strs[idx].gap_flag, uwa2f3s.wa2_f3s.cross_strs[idx].node_nbr, uwa2f3s.wa2_f3s.cross_strs[idx].nbr_streets,
			uwa1.wa1.output.sto[0].Street_name,
			uwa1.wa1.output.sto[1].Street_name
		);

		// This will print out just B7SCs 
		//sprintf(ptr_line, "[%3s] %c    %.5s     %c  %.7s %c %.8s %.8s %.8s %.8s %.8s",
		//	i_char, uwa2f3s.wa2_f3s.cross_strs[idx].mh_ri_flag, uwa2f3s.wa2_f3s.cross_strs[idx].len,
		//	uwa2f3s.wa2_f3s.cross_strs[idx].gap_flag, uwa2f3s.wa2_f3s.cross_strs[idx].node_nbr, uwa2f3s.wa2_f3s.cross_strs[idx].nbr_streets,
		//	uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[0],
		//	uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[1],
		//	uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[2],
		//	uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[3],
		//	uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[4]
		//);

	}

	//add a blank line 
	(*start_row)++;

	printf("inside disp_wa2_f3s_stnames:  leaving\n");


}  //end of disp_wa2_f3s_stnames 

//------------------------------------------------------------------------
//-- display wa2 for f3s using workarea 2 (returns b7scs) 
//------------------------------------------------------------------------
void disp_wa2_f3s_b7scs(char *wa2_string, PFIELDENTRY wa2_flds, int number_of_fields,
	int *start_row, char disp[ROWS][COLS])
{

	int i, j, k;
	char *ptr_line;
	int col_start;
	char blank_line[80];
	//char label_str[80];
	//char value_str[80];
	int pad_value;

	int array_offset = 0;

	char prt_fld_name[32];
	int prt_entry = 0;
	char prt_val[33];
	int prt_start = 0;
	int prt_length = 0;
	int prt_matrix_entry = 0;
	char prt_type = ' ';

	int start_struct;
	int end_struct;

	memset(prt_fld_name, ' ', sizeof(prt_fld_name));

	memset(blank_line, ' ', 80);
	//set the spacing between columns 
	pad_value = 2;
	//pad_value = 5; 

	//sprintf(disp[*start_row], "Test of Wa2 Display using Parms .....");
	//
	////add a blank line 
	//(*start_row)++;

	////add 1st row of column markers 
	//(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	memset(ptr_line, ' ', 80);
	column_map1(ptr_line);

	//add 2nd row of column markers 
	(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	memset(ptr_line, ' ', 80);
	column_map2(ptr_line);

	//add a blank line 
	(*start_row)++;

	//printf("\nStart of print fields loop \n");
	//for (i = 0; i < number_of_fields; i++)
	i = 0;

	//Add Key and Number of Intersections 
	(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	sprintf(ptr_line, "FILLER                                    %.21s ", uwa2f3s.wa2_f3s.filler01);

	(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	sprintf(ptr_line, "NUMBER OF XSTREETS IN STRETCH             %.3s ", uwa2f3s.wa2_f3s.nbr_x_str);

	//add a dashed line to separate new array structures 
	(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	memset(ptr_line, '-', 78);

	//add a header line 
	(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	sprintf(ptr_line, "INDEX MHRI DISTANCE GAP NODE-ID N B7SC1    B7SC2    B7SC3    B7SC4    B7SC5   ");

	//add a dash line for header line 
	(*start_row)++;
	col_start = 0;
	ptr_line = (char*)(disp + *start_row) + col_start;
	sprintf(ptr_line, "----- ---- -------- --- ------- - -------- -------- -------- -------- --------");

	//Use this to convert integer to character array so we can always display 3 characters
	char i_char[4];
	int idx_plus1 = 0; 
	size_t idx;

	for (idx = 0; idx < 350; idx++)
	{
		(*start_row)++;
		col_start = 0;
		ptr_line = (char*)(disp + *start_row) + col_start;
	
		//add 1 to zero based idx 
		idx_plus1 = idx;
		idx_plus1++;

		//Use this to convert integer to character array so we can always display 3 characters
		sprintf(i_char, "%d", idx_plus1);
		i_char[3] = '\0';

		////Use this to convert integer to character array so we can always display 3 characters
		//sprintf(i_char, "%d", idx);
		//i_char[3] = '\0';

		//memset(uwa1.cwa1, ' ', 1200);
		//memcpy(uwa1.wa1.input.func_code, "DG", 2);
		//uwa1.wa1.input.platform_ind = 'C';
		//memcpy(uwa1.wa1.input.snl, "30", 2);
		//// first intersecting street 
		//uwa1.wa1.input.sti[0].boro = uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[0][0];
		//memcpy(uwa1.wa1.input.sti[0].SC10, uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[0]+1, 7);
		//// second intersecting street 
		//uwa1.wa1.input.sti[1].boro = uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[1][0];
		//memcpy(uwa1.wa1.input.sti[1].SC10, uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[1] + 1, 7);

		////printf("\ninput boro = %c   input 7sc = %.6s\n", uwa1.wa1.input.sti[0].boro, uwa1.wa1.input.sti[0].SC10);

		//geo(uwa1.cwa1, NULL);
		//
		//// Test of printing out street names 
		//sprintf(ptr_line, "%c %.5s %c %.7s %c %.30s %.30s",
		//	uwa2f3s.wa2_f3s.cross_strs[idx].mh_ri_flag, uwa2f3s.wa2_f3s.cross_strs[idx].len,
		//	uwa2f3s.wa2_f3s.cross_strs[idx].gap_flag, uwa2f3s.wa2_f3s.cross_strs[idx].node_nbr, uwa2f3s.wa2_f3s.cross_strs[idx].nbr_streets,
		//	uwa1.wa1.output.sto[0].Street_name, 
		//	uwa1.wa1.output.sto[1].Street_name
		//	);

		// This will print out just B7SCs 
		sprintf(ptr_line, "[%3s] %c    %.5s     %c  %.7s %c %.8s %.8s %.8s %.8s %.8s",
			i_char, uwa2f3s.wa2_f3s.cross_strs[idx].mh_ri_flag, uwa2f3s.wa2_f3s.cross_strs[idx].len,
			uwa2f3s.wa2_f3s.cross_strs[idx].gap_flag, uwa2f3s.wa2_f3s.cross_strs[idx].node_nbr, uwa2f3s.wa2_f3s.cross_strs[idx].nbr_streets,
			uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[0],
			uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[1],
			uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[2],
			uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[3],
			uwa2f3s.wa2_f3s.cross_strs[idx].B7SC[4]
		);

	}

   //add a blank line 
	(*start_row)++;

	//printf("leaving disp_elections\n");

}  //end of disp_wa2_f3s_b7scs

//---------------------------------------------------------------------------

void column_map1(char *line)
{
	int i;
	char i_char[4];
	for (i = 0; i < 8; i++) 
	{
		memcpy(line+(i*10), "---------", 9);
		sprintf(i_char,"%d",i); 
		//itoa(i+1, i_char, 10);
		*(line+((i*10)+9)) = i_char[0];
	}

}  //end of column_map1 

//---------------------------------------------------------------------------

void column_map2(char *line)
{
	int i;
	for (i = 0; i < 8; i++) 
	{
		memcpy(line+(i*10), "1234567890", 10);
	}

}  //end of column_map2 

//---------------------------------------------------------------------------



