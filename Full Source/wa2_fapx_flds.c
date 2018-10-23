#include "wa_fields.h"

//--FIELDENTRY consists of:  
//--	field name, field length, start position, 
//--	number of array entries, length of array entry, 
//--	start of structure, end of structure, [in FIELDENTRY array]
//--	data type (only for msw), entry type (' ', 'S' for structure)

FIELDENTRY wa2_fapx_fld_strs[] = { 
{ "ACCESS KEY                      ", 21, 1, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONTINUOUS PARITY INDICATOR     ", 1, 22, 0, 0, 0, 0, ' ', ' ' }, 
{ "LOW HOUSENUM OF KEY             ", 11, 23, 0, 0, 0, 0, ' ', ' ' }, 
{ "BBL                             ", 10, 34, 0, 0, 0, 0, ' ', ' ' }, 
{ "   BOROUGH CODE                 ", 1, 34, 0, 0, 0, 0, ' ', ' ' }, 
{ "   TAX BLOCK                    ", 5, 35, 0, 0, 0, 0, ' ', ' ' }, 
{ "   TAX LOT                      ", 4, 40, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER OF 7                     ", 7, 44, 0, 0, 0, 0, ' ', ' ' }, 
{ "NUMBER OF STRUCTURES            ", 4, 51, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER OF 26                    ", 26, 55, 0, 0, 0, 0, ' ', ' ' }, 
{ "BIN KEY PREFIX                  ", 1, 81, 0, 0, 0, 0, ' ', ' ' }, 
{ "BIN OF INPUT ADDRESS OR NAP     ", 7, 82, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONDOMINIUM FLAG                ", 1, 89, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER OF 1                     ", 1, 90, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONDOMINIUM ID NUMBER           ", 4, 91, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER OF 7                     ", 7, 95, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONDOMINIUM BILLING BBL         ", 10, 102, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER OF 2                     ", 2, 112, 0, 0, 0, 0, ' ', ' ' }, 
{ "LOW BBL                         ", 10, 114, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER OF 1                     ", 1, 124, 0, 0, 0, 0, ' ', ' ' }, 
{ "HIGH BBL                        ", 10, 125, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER OF 16                    ", 16, 135, 0, 0, 0, 0, ' ', ' ' }, 
{ "COOPERATIVE ID NUMBER           ", 4, 151, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER OF 25                    ", 25, 155, 0, 0, 0, 0, ' ', ' ' }, 
{ "LATITUDE                        ", 9, 180, 0, 0, 0, 0, ' ', ' ' }, 
{ "LONGITUDE                       ", 11, 189, 0, 0, 0, 0, ' ', ' ' }, 
{ "X COORDINATE	                   ", 7, 200, 0, 0, 0, 0, ' ', ' ' }, 
{ "Y COORDINATE                    ", 7, 207, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER OF 18                    ", 16, 214, 0, 0, 0, 0, ' ', ' ' }, 
{ "ADDRESS POINT ID                ", 9, 230, 0, 0, 0, 0, ' ', ' ' }, 
{ "ACCEPTABLE LGC'S                ", 8, 239, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER OF 114                   ", 114, 247, 0, 0, 0, 0, ' ', ' ' }, 
{ "NUMBER OF ENTRIES IN LIST       ", 4, 361, 0, 0, 0, 0, ' ', ' ' }, 
{ "LIST OF GEOGRAPHIC IDENTIFIERS  ", 2436, 365, 1, 116, 35, 43, ' ', ' ' }, 
{ "     LOW HOUSE NUMBER           ", 16, 365, 0, 0, 0, 0, ' ', 'S' }, 
{ "     HIGH HOUSE NUMBER          ", 16, 381, 0, 0, 0, 0, ' ', 'S' }, 
{ "     B7SC                       ", 8, 397, 0, 0, 0, 0, ' ', 'S' }, 
{ "     BIN                        ", 7, 405, 0, 0, 0, 0, ' ', 'S' }, 
{ "     SIDE OF STREET             ", 1, 412, 0, 0, 0, 0, ' ', 'S' }, 
{ "     ADDRESS TYPE CODE          ", 1, 413, 0, 0, 0, 0, ' ', 'S' }, 
{ "     TPAD BIN STATUS            ", 1, 414, 0, 0, 0, 0, ' ', 'S' }, 
{ "     STREET NAME                ", 32, 415, 0, 0, 0, 0, ' ', 'S' }, 
{ "     FILLER                     ", 34, 447, 0, 0, 0, 0, ' ', 'S' }, 
}; 

int n_wa2_fapx_field_recs = sizeof(wa2_fapx_fld_strs) / sizeof(FIELDENTRY); 
//PFIELDENTRY wa2_f1ax_flds = &wa2_f1ax_fld_strs; 
PFIELDENTRY wa2_fapx_flds = (PFIELDENTRY)wa2_fapx_fld_strs; 
