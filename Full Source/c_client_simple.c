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

//below is not needed - it is holdover from other application
#if defined(WIN32) 
#define ROLE __declspec(dllimport) __stdcall
//#define ROLE __declspec(dllimport) 
#elif defined(x64)
#define ROLE __declspec(dllimport) __stdcall
#elif defined(__linux__)
#define ROLE __stdcall
#endif

//contains definition for geo in libgeo.so 
#include "geo.h"

//contains the wa1 and wa2 layouts 
#include "pac.h"

#pragma hdrstop

void call_func_1();
void call_func_1e();
void call_func_1a();
void call_func_2();
void call_func_2w();
void call_func_3();
void call_func_3c();
void call_func_ap();
void call_func_bl();
void call_func_bn();
void call_func_d();
void call_func_dg();
void call_func_dn();
void call_func_hr();
void call_func_1n();

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

int main(int argc, char* argv[])
{

        time(&t);
        memset(dash_line, '-', sizeof(dash_line));
		dash_line[120] = '\0';

		//_strset(dash_line, '-'); 
		exit_sw = 'N';
        while(exit_sw != 'X')
        {
			printf("\n\n%.90s", dash_line);
			printf("\n*****  Enter a function code or 'X' to exit:  ");
			gets(function_sw);
			
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
			else if (strcmp(function_sw, "1N") == 0 || strcmp(function_sw, "1n") == 0)
			{
				call_func_1n();
			}
			else if (strcmp(function_sw, "D") == 0)
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
	char *pmode_switch;

	memset(uwa1.cwa1, ' ', 1200);
	memcpy(uwa1.wa1.input.func_code, "HR", 2);
	uwa1.wa1.input.platform_ind = 'C';

	geo(uwa1.cwa1, cwa2fhr);

	printf("\n\nFunction 1A GRC = %.2s\n"
		   "Error Message = %.80s\n", uwa1.wa1.output.ret_code, uwa1.wa1.output.msg);

	if ((memcmp(uwa1.wa1.output.ret_code, "00", 2) == 0)  || 
		(memcmp(uwa1.wa1.output.ret_code, "01", 2) == 0))
	{
		// displays the first 80 bytes of wa2 
		printf("cwa2fhr = %.80s\n", cwa2fhr);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_hr () 

//---------------------------------------------------------------------------
void call_func_ap ()
{
	char *pmode_switch;

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
			// displays the first 80 bytes of wa2 
			printf("uwa2fapx.cwa2fapx = %.80s\n", uwa2fapx.cwa2fapx);
		}
		else
		{
			// displays the first 80 bytes of wa2 
			printf("uwa2fap.cwa2fap = %.80s\n", uwa2fap.cwa2fap);
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
	char *pmode_switch;

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
			// displays the first 80 bytes of wa2 
			printf("uwa2f1ax.cwa2f1ax = %.80s\n", uwa2f1ax.cwa2f1ax);
		}
		else 
		{
			// displays the first 80 bytes of wa2 
			printf("uwa2f1a.cwa2f1a = %.80s\n", uwa2f1a.cwa2f1a);
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
	char *pmode_switch;

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
				// displays the first 80 bytes of wa2 
				printf("uwa2f1ax.cwa2f1ax = %.80s\n", uwa2f1ax.cwa2f1ax);
			else
				// displays the first 80 bytes of wa2 
				printf("uwa2f1a.cwa2f1a = %.80s\n", uwa2f1a.cwa2f1a);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_bl () 

//---------------------------------------------------------------------------
void call_func_bn ()
{
	char *pmode_switch;

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
				// displays the first 80 bytes of wa2 
				printf("uwa2f1ax.cwa2f1ax = %.80s\n", uwa2f1ax.cwa2f1ax);
			else
				// displays the first 80 bytes of wa2 
				printf("uwa2f1a.cwa2f1a = %.80s\n", uwa2f1a.cwa2f1a);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_bn () 

//---------------------------------------------------------------------------
void call_func_1 ()
{
	char *pmode_switch;

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
				// displays the first 80 bytes of wa2 
				printf("uwa2f1ex.cwa2f1ex = %.80s\n", uwa2f1ex.cwa2f1ex);
			else
				// displays the first 80 bytes of wa2 
				printf("uwa2f1.cwa2f1 = %.80s\n", uwa2f1.cwa2f1);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}
}  // end of call_func_1 () 

//---------------------------------------------------------------------------
void call_func_1e ()
{
	char *pmode_switch;

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
				// displays the first 80 bytes of wa2 
				printf("uwa2f1ex.cwa2f1ex = %.80s\n", uwa2f1ex.cwa2f1ex);
			else
				// displays the first 80 bytes of wa2 
				printf("uwa2f1.cwa2f1 = %.80s\n", uwa2f1.cwa2f1);
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
		// displays the first 80 bytes of wa2 
		printf("uwa2f2.cwa2f2 = %.80s\n", uwa2f2.cwa2f2);
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
		// displays the first 80 bytes of wa2 
		printf("uwa2f2w.cwa2f2w = %.80s\n", uwa2f2w.cwa2f2w);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
		if (memcmp(uwa1.wa1.output.ret_code, "03", 2) == 0) 
		{
			// displays the first 80 bytes of wa2 
			printf("uwa2f2w.cwa2f2w = %.80s\n", uwa2f2w.cwa2f2w);
		}
	}

}  // end of call_func_2w () 

//---------------------------------------------------------------------------
void call_func_3 ()
{
	char *pmode_switch;

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
				// displays the first 80 bytes of wa2 
				printf("uwa2f3x.cwa2f3x = %.80s\n", uwa2f3x.cwa2f3x);
			else
				// displays the first 80 bytes of wa2 
				printf("uwa2f3.cwa2f3 = %.80s\n", uwa2f3.cwa2f3);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_3 () 

void call_func_3c ()
{
	char *pmode_switch;

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
				// displays the first 80 bytes of wa2 
				printf("uwa2f3cx.cwa2f3cx = %.80s\n", uwa2f3cx.cwa2f3cx);
			else
				// displays the first 80 bytes of wa2 
				printf("uwa2f3c.cwa2f3c = %.80s\n", uwa2f3c.cwa2f3c);
	}
	else
	{
		printf("\n\nwa1_input = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_3c () 

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
		// displays the first 80 bytes of wa1
		printf("uwa1.cwa1 = %.80s\n", uwa1.cwa1);
	}
	else
	{
		// displays the first 80 bytes of wa1
		printf("uwa1.cwa1 = %.80s\n", uwa1.cwa1);
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
		// displays the first 80 bytes of wa1 
		printf("uwa1.cwa1 = %.80s\n", );
	}
	else
	{
		// displays the first 80 bytes of wa1
		printf("uwa1.cwa1 = %.80s\n", );
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
		// displays the first 80 bytes of wa2 
		printf("uwa1.cwa1 = %.80s\n", uwa1.cwa1);
	}
	else
	{
		// displays the first 80 bytes of wa2 
		printf("uwa1.cwa1 = %.80s\n", uwa1.cwa1);
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
		// displays the first 80 bytes of wa2 
		printf("uwa1.cwa1 = %.80s\n", uwa1.cwa1);
	}
	else
	{
		// displays the first 80 bytes of wa2 
		printf("uwa1.cwa1 = %.80s\n", uwa1.cwa1);
	}

}  // end of call_func_dn () 

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

