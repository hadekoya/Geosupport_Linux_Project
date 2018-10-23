#include "wa_fields.h"

//--FIELDENTRY consists of:  
//--	field name, field length, start position, 
//--	number of array entries, length of array entry, 
//--	start of structure, end of structure, [in FIELDENTRY array]
//--	data type (only for msw), entry type (' ', 'S' for structure)

FIELDENTRY wa2_fap_fld_strs[] = { 
{ "ACCESS KEY                      ", 21, 1, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONTINUOUS PARITY INDICATOR     ", 1, 22, 0, 0, 0, 0, ' ', ' ' }, 
{ "LOW HOUSENUM OF KEY             ", 11, 23, 0, 0, 0, 0, ' ', ' ' }, 
{ "BBL                             ", 10, 34, 0, 0, 0, 0, ' ', ' ' }, 
{ "   BOROUGH CODE                 ", 1, 34, 0, 0, 0, 0, ' ', ' ' }, 
{ "   TAX BLOCK                    ", 5, 35, 0, 0, 0, 0, ' ', ' ' }, 
{ "   TAX LOT                      ", 4, 40, 0, 0, 0, 0, ' ', ' ' }, 
{ "NUMBER OF STRUCTURES            ", 4, 51, 0, 0, 0, 0, ' ', ' ' }, 
{ "BIN KEY PREFIX FIELD            ", 1, 81, 0, 0, 0, 0, ' ', ' ' }, 
{ "BIN OF INPUT ADDRESS            ", 7, 82, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONDOMINIUM FLAG                ", 1, 89, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONDOMINIUM ID NUMBER           ", 4, 91, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONDOMINIUM BILLING BBL         ", 10, 102, 0, 0, 0, 0, ' ', ' ' }, 
{ "LOW BBL                         ", 10, 114, 0, 0, 0, 0, ' ', ' ' }, 
{ "HIGH BBL                        ", 10, 125, 0, 0, 0, 0, ' ', ' ' }, 
{ "COOPERATIVE ID NUMBER           ", 4, 151, 0, 0, 0, 0, ' ', ' ' }, 
{ "LATITUDE                        ", 9, 180, 0, 0, 0, 0, ' ', ' ' }, 
{ "LONGITUDE                       ", 11, 189, 0, 0, 0, 0, ' ', ' ' }, 
{ "X-COORDINATE OF LOT             ", 7, 200, 0, 0, 0, 0, ' ', ' ' }, 
{ "Y-COORDINATE OF LOT             ", 7, 207, 0, 0, 0, 0, ' ', ' ' }, 
{ "ADDRESS POINT ID                ", 9, 230, 0, 0, 0, 0, ' ', ' ' }, 
{ "ACCEPTABLE LGC'S                ", 8, 239, 0, 0, 0, 0, ' ', ' ' }, 
{ "NUMBER OF ENTRIES IN LIST       ", 4, 247, 0, 0, 0, 0, ' ', ' ' }, 
{ "LIST OF GEOGRAPHIC IDENTIFIERS  ", 1113, 251, 1, 53, 25, 31, ' ', ' ' }, 
{ "     LOW HOUSE NUMBER           ", 16, 251, 0, 0, 0, 0, ' ', 'S' }, 
{ "     HIGH HOUSE NUMBER          ", 16, 267, 0, 0, 0, 0, ' ', 'S' }, 
{ "     B7SC                       ", 8, 283, 0, 0, 0, 0, ' ', 'S' }, 
{ "     BIN                        ", 7, 291, 0, 0, 0, 0, ' ', 'S' }, 
{ "     SIDE OF STREET             ", 1, 298, 0, 0, 0, 0, ' ', 'S' }, 
{ "     ADDRESS TYPE CODE          ", 1, 299, 0, 0, 0, 0, ' ', 'S' }, 
{ "     FILLER                     ", 4, 300, 0, 0, 0, 0, ' ', 'S' }, 
}; 

int n_wa2_fap_field_recs = sizeof(wa2_fap_fld_strs) / sizeof(FIELDENTRY); 
//PFIELDENTRY wa2_f1a_flds = &wa2_f1a_fld_strs; 
PFIELDENTRY wa2_fap_flds = (PFIELDENTRY)wa2_fap_fld_strs; 
