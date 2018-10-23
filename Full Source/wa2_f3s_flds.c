#include "wa_fields.h"

//--FIELDENTRY consists of:  
//--	field name, field length, start position, 
//--	number of array entries, length of array entry, 
//--	start of structure, end of structure, [in FIELDENTRY array]
//--	data type (only for msw), entry type (' ', 'S' for structure)

FIELDENTRY wa2_f3s_fld_strs[] = { 
{ "FILLER                          ", 21, 1, 0, 0, 0, 0, ' ', ' ' }, 
{ "NUMBER OF XSTREETS IN STRETCH   ", 3, 22, 0, 0, 0, 0, ' ', ' ' }, 
{ "LIST OF XSTREETS IN STRETCH     ", 19250, 25, 350, 55, 4, 13, ' ', ' ' }, 
{ "  MARBLE HILL/RIKERS ISLAND FLAG", 1, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "  DISTANCE FROM PREDECESSOR (FT)", 5, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "  GAP FLAG                      ", 1, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "  NODE NUMBER                   ", 7, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "  NUM OF STREETS AT INTERSECTION", 1, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "  B7SC1                         ", 8, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "  B7SC2                         ", 8, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "  B7SC3                         ", 8, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "  B7SC4                         ", 8, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "  B7SC5                         ", 8, 0, 0, 0, 0, 0, ' ', 'S' }, 
}; 

int n_wa2_f3s_field_recs = sizeof(wa2_f3s_fld_strs) / sizeof(FIELDENTRY); 
//PFIELDENTRY wa2_f3s_flds = &wa2_f3s_fld_strs; 
PFIELDENTRY wa2_f3s_flds = (PFIELDENTRY)wa2_f3s_fld_strs; 
