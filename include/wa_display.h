//---------------------------------------------------------------------------

#ifndef waDISPLAY
#define waDISPLAY
//---------------------------------------------------------------------------
#include "wa_fields.h"
////////////////////////////////////////////////////////////////////////////////
//ROLE = __declspec(dllexport) when creating DLL
//ROLE = __declspec(dllimport) when using DLL 
////////////////////////////////////////////////////////////////////////////////
#if defined(CREATE_DLL) && defined(WIN32)
# define ROLE __declspec(dllexport)
#else
# define ROLE
# define ROLE __declspec(dllimport)
#endif

#ifdef __cplusplus                                                      
extern "C" {                                                            
#endif

void ROLE __cdecl disp_wa2_parms(char *wa2_string, PFIELDENTRY wa2_flds, 
								 int number_of_fields, int *start_row, char disp[400][80]); 
void ROLE __cdecl disp_wa2_f1(C_WA2_F1 c_wa2_f1e, int *start_row, 
							  char disp[400][80]);
void ROLE __cdecl disp_wa2_f1e(C_WA2_F1 c_wa2_f1, int *start_row, 
							   char disp[400][80]);
void ROLE __cdecl test1_disp_wa2_f1e_char(char *wa2_string);
void ROLE __cdecl test2_disp_wa2_f1e_char(char *wa2_string, int *start_row);
void ROLE __cdecl test3_disp_wa2_f1e_char(char *wa2_string, int *start_row, char disp[400][80]);
void ROLE __cdecl test4_disp_wa2_f1e_char(char *wa2_string, int *start_row, char *disp);
void ROLE __cdecl disp_wa2_f1e_char(char *disp_string, int *start_row, char *wa2_string);
void ROLE __cdecl disp_wa2_f1ex(C_WA2_F1EX c_wa2_f1ex, int *start_row, 
							   char disp[400][80]);
#ifdef __cplusplus
       }
#endif
//---------------------------------------------------------------------------
#endif
 
