#include "wa_fields.h"

//--FIELDENTRY consists of:  
//--	field name, field length, start position, 
//--	number of array entries, length of array entry, 
//--	start of structure, end of structure, [in FIELDENTRY array]
//--	data type (only for msw), entry type (' ', 'S' for structure)

FIELDENTRY wa2_f1a_fld_strs[] = { 
{ "ACCESS KEY                      ", 21, 1, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONTINUOUS PARITY INDICATOR     ", 1, 22, 0, 0, 0, 0, ' ', ' ' }, 
{ "LOW HOUSENUM OF KEY             ", 11, 23, 0, 0, 0, 0, ' ', ' ' }, 
{ "BBL                             ", 10, 34, 0, 0, 0, 0, ' ', ' ' }, 
{ "   BOROUGH CODE                 ", 1, 34, 0, 0, 0, 0, ' ', ' ' }, 
{ "   TAX BLOCK                    ", 5, 35, 0, 0, 0, 0, ' ', ' ' }, 
{ "   TAX LOT                      ", 4, 40, 0, 0, 0, 0, ' ', ' ' }, 
{ "TAX LOT VERSION NUMBER (NYI)    ", 1, 44, 0, 0, 0, 0, ' ', ' ' }, 
{ "RPAD SELF-CHECK CODE (SCC) - BBL", 1, 45, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER                          ", 1, 46, 0, 0, 0, 0, ' ', ' ' }, 
{ "RPAD BLDG CLASS                 ", 2, 47, 0, 0, 0, 0, ' ', ' ' }, 
{ "CORNER CODE                     ", 2, 49, 0, 0, 0, 0, ' ', ' ' }, 
{ "NUMBER OF STRUCTURES            ", 4, 51, 0, 0, 0, 0, ' ', ' ' }, 
{ "NUMBER OF STREET FRONT OF LOT   ", 2, 55, 0, 0, 0, 0, ' ', ' ' }, 
{ "INTERIOR LOT FLAG               ", 1, 57, 0, 0, 0, 0, ' ', ' ' }, 
{ "VACANT LOT FLAG                 ", 1, 58, 0, 0, 0, 0, ' ', ' ' }, 
{ "IRREGULARLY-SHAPED LOT FLAG     ", 1, 59, 0, 0, 0, 0, ' ', ' ' }, 
{ "ALTERNATIVE BOROUGH FLAG        ", 1, 60, 0, 0, 0, 0, ' ', ' ' }, 
{ "ADDRESS LIST OVERFLOW FLAG      ", 1, 61, 0, 0, 0, 0, ' ', ' ' }, 
{ "STROLLING KEY                   ", 19, 62, 0, 0, 0, 0, ' ', ' ' }, 
{ "BIN KEY PREFIX FIELD            ", 1, 81, 0, 0, 0, 0, ' ', ' ' }, 
{ "BIN OF INPUT ADDRESS            ", 7, 82, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONDOMINIUM FLAG                ", 1, 89, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER                          ", 1, 90, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONDOMINIUM ID NUMBER           ", 4, 91, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER                          ", 7, 95, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONDOMINIUM BILLING BBL         ", 10, 102, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER                          ", 1, 112, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONDOMINIUM BILLING BBL SCC     ", 1, 113, 0, 0, 0, 0, ' ', ' ' }, 
{ "LOW BBL                         ", 10, 114, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER                          ", 1, 124, 0, 0, 0, 0, ' ', ' ' }, 
{ "HIGH BBL                        ", 10, 125, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER                          ", 1, 135, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER                          ", 15, 136, 0, 0, 0, 0, ' ', ' ' }, 
{ "COOPERATIVE ID NUMBER           ", 4, 151, 0, 0, 0, 0, ' ', ' ' }, 
{ "SBVP (SANBORN MAP IDENTIFIERS)  ", 8, 155, 0, 0, 0, 0, ' ', ' ' }, 
{ "   SANBORN BOROUGH CODE         ", 1, 155, 0, 0, 0, 0, ' ', ' ' }, 
{ "   SANBORN VOLUME AND VOLUME SUF", 3, 156, 0, 0, 0, 0, ' ', ' ' }, 
{ "   SANBORN PAGE AND PAGE SUFFIX ", 4, 159, 0, 0, 0, 0, ' ', ' ' }, 
{ "DCP COMMERCIAL AREA             ", 5, 163, 0, 0, 0, 0, ' ', ' ' }, 
{ "TAX MAP IDENTIFIERS:            ", 9, 168, 0, 0, 0, 0, ' ', ' ' }, 
{ "     BOROUGH CODE               ", 1, 168, 0, 0, 0, 0, ' ', ' ' }, 
{ "     TAX MAP SECTION            ", 2, 169, 0, 0, 0, 0, ' ', ' ' }, 
{ "     TAX MAP VOLUME             ", 2, 171, 0, 0, 0, 0, ' ', ' ' }, 
{ "     TAX MAP PAGE (NYI)         ", 4, 173, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER                          ", 3, 177, 0, 0, 0, 0, ' ', ' ' }, 
{ "LATITUDE                        ", 9, 180, 0, 0, 0, 0, ' ', ' ' }, 
{ "LONGITUDE                       ", 11, 189, 0, 0, 0, 0, ' ', ' ' }, 
{ "X-COORDINATE OF LOT             ", 7, 200, 0, 0, 0, 0, ' ', ' ' }, 
{ "Y-COORDINATE OF LOT             ", 7, 207, 0, 0, 0, 0, ' ', ' ' }, 
{ "BID ID                          ", 6, 214, 0, 0, 0, 0, ' ', ' ' },
{ "TPAD BIN STATUS                 ", 1, 220, 0, 0, 0, 0, ' ', ' ' },
{ "TPAD NEW BIN                    ", 7, 221, 0, 0, 0, 0, ' ', ' ' },
{ "TPAD NEW BIN STATUS             ", 1, 228, 0, 0, 0, 0, ' ', ' ' },
{ "TPAD CONFLICT FLAG              ", 1, 229, 0, 0, 0, 0, ' ', ' ' },
{ "DCP ZONING MAP                  ", 3, 230, 0, 0, 0, 0, ' ', ' ' },
{ "FILLER                          ", 6, 233, 0, 0, 0, 0, ' ', ' ' },
{ "ACCEPTABLE LGC'S                ", 8, 239, 0, 0, 0, 0, ' ', ' ' },
{ "NUMBER OF ENTRIES IN LIST       ", 4, 247, 0, 0, 0, 0, ' ', ' ' }, 
{ "LIST OF GEOGRAPHIC IDENTIFIERS  ", 1113, 251, 21, 53, 61, 67, ' ', ' ' }, 
{ "     LOW HOUSE NUMBER           ", 16, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "     HIGH HOUSE NUMBER          ", 16, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "     B7SC                       ", 8, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "     BIN                        ", 7, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "     SIDE OF STREET             ", 1, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "     ADDRESS TYPE CODE          ", 1, 0, 0, 0, 0, 0, ' ', 'S' }, 
{ "     FILLER                     ", 4, 0, 0, 0, 0, 0, ' ', 'S' }, 
}; 

//--FIELDENTRY consists of:  
//--	field name, field length, start position, 
//--	number of array entries, length of array entry, 
//--	start of structure [in list of fields], end of structure, [in FIELDENTRY array]
//--	data type (only for msw), entry type (' ', 'S' for structure)

int n_wa2_f1a_field_recs = sizeof(wa2_f1a_fld_strs) / sizeof(FIELDENTRY);
//PFIELDENTRY wa2_f1a_flds = &wa2_f1a_fld_strs; 
PFIELDENTRY wa2_f1a_flds = (PFIELDENTRY)wa2_f1a_fld_strs; 