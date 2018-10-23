#include "wa_fields.h"

//--FIELDENTRY consists of:  
//--	field name, field length, start position, 
//--	number of array entries, length of array entry, 
//--	start of structure, end of structure, [in FIELDENTRY array]
//--	data type (only for msw), entry type (' ', 'S' for structure)

FIELDENTRY wa2_f2_fld_strs[] = { 
{ "ACCESS KEY                      ", 21, 1, 0, 0, 0, 0, ' ', ' ' }, 
{ "INTERSECTION REPLICATION COUNTER", 1, 22, 0, 0, 0, 0, ' ', ' ' }, 
{ "DCP-PREFERRED LGC FOR STREET 1  ", 2, 23, 0, 0, 0, 0, ' ', ' ' }, 
{ "DCP-PREFERRED LGC FOR STREET 2  ", 2, 25, 0, 0, 0, 0, ' ', ' ' }, 
{ "NUMBER OF INTERSECTING STREETS  ", 1, 27, 0, 0, 0, 0, ' ', ' ' }, 
{ "LIST OF INTERSECTING STREETS    ", 30, 28, 5, 6, 0, 0, ' ', ' ' }, 
{ "COMP DIR FOR INTERSECTION KEY   ", 1, 58, 0, 0, 0, 0, ' ', ' ' }, 
{ "ATOMIC POLYGON                  ", 3, 59, 0, 0, 0, 0, ' ', ' ' }, 
{ "LION NODE NUMBER                ", 7, 64, 0, 0, 0, 0, ' ', ' ' }, 
{ "X COORDINATE                    ", 7, 71, 0, 0, 0, 0, ' ', ' ' }, 
{ "Y COORDINATE                    ", 7, 78, 0, 0, 0, 0, ' ', ' ' }, 
{ "Z COORDINATE                    ", 7, 85, 0, 0, 0, 0, ' ', ' ' }, 
{ "SBVP1 (SANBORN MAP IDENTIFIERS):", 8, 92, 0, 0, 0, 0, ' ', ' ' }, 
{ "     SANBORN BOROUGH CODE       ", 1, 92, 0, 0, 0, 0, ' ', ' ' }, 
{ "     SANBORN VOL & VOL SUF      ", 3, 93, 0, 0, 0, 0, ' ', ' ' }, 
{ "     SANBORN PAGE & PAGE SUF    ", 4, 96, 0, 0, 0, 0, ' ', ' ' }, 
{ "SBVP2 (SANBORN MAP SECOND MAP)  ", 8, 100, 0, 0, 0, 0, ' ', ' ' }, 
{ "     SANBORN BOROUGH CODE       ", 1, 100, 0, 0, 0, 0, ' ', ' ' }, 
{ "     SANBORN VOLUME & VOL SUF   ", 3, 101, 0, 0, 0, 0, ' ', ' ' }, 
{ "     SANBORN PAGE & PAGE SUF    ", 4, 104, 0, 0, 0, 0, ' ', ' ' }, 
{ "MARBLE HILL/RIKERS ISLAND FLAG  ", 1, 108, 0, 0, 0, 0, ' ', ' ' }, 
{ "DOT STREET LIGHT AREA           ", 1, 109, 0, 0, 0, 0, ' ', ' ' }, 
{ "COMMUNITY DISCTRICT             ", 3, 110, 0, 0, 0, 0, ' ', ' ' }, 
{ "   COMMUNITY DISTRICT BOROUGH   ", 1, 110, 0, 0, 0, 0, ' ', ' ' }, 
{ "   COMMUNITY DISTRICT NUMBER    ", 2, 111, 0, 0, 0, 0, ' ', ' ' }, 
{ "ZIP CODE                        ", 5, 113, 0, 0, 0, 0, ' ', ' ' }, 
{ "HEALTH AREA                     ", 4, 118, 0, 0, 0, 0, ' ', ' ' }, 
{ "POLICE PATROL BOROUGH COMMAND   ", 1, 122, 0, 0, 0, 0, ' ', ' ' }, 
{ "POLICE PRECINCT                 ", 3, 123, 0, 0, 0, 0, ' ', ' ' }, 
{ "FIRE SECTOR                     ", 2, 126, 0, 0, 0, 0, ' ', ' ' }, 
{ "FIRE BATTALION                  ", 2, 128, 0, 0, 0, 0, ' ', ' ' }, 
{ "FIRE COMPANY TYPE               ", 1, 130, 0, 0, 0, 0, ' ', ' ' }, 
{ "FIRE COMPANY NUMBER             ", 3, 131, 0, 0, 0, 0, ' ', ' ' }, 
{ "COMMUNITY SCHOOL DISTRICT       ", 2, 134, 0, 0, 0, 0, ' ', ' ' }, 
{ "2010 CENSUS TRACT               ", 6, 136, 0, 0, 0, 0, ' ', ' ' }, 
{ "1990 CENSUS TRACT               ", 6, 142, 0, 0, 0, 0, ' ', ' ' }, 
{ "LEVEL CODES                     ", 10, 148, 0, 0, 0, 0, ' ', ' ' },
{ "POLICE PATROL BOROUGH           ", 2, 158, 0, 0, 0, 0, ' ', ' ' },
{ "ASSEMBLY DISTRICT               ", 2, 160, 0, 0, 0, 0, ' ', ' ' }, 
{ "CONGRESSIONAL DISTRICT          ", 2, 162, 0, 0, 0, 0, ' ', ' ' }, 
{ "STATE SENATE DISTRICT           ", 2, 164, 0, 0, 0, 0, ' ', ' ' }, 
{ "CIVIL COURT DISTRICT            ", 2, 166, 0, 0, 0, 0, ' ', ' ' }, 
{ "CITY COUNCIL DISTRICT           ", 2, 168, 0, 0, 0, 0, ' ', ' ' }, 
{ "CD ELIGIBILITY                  ", 1, 170, 0, 0, 0, 0, ' ', ' ' }, 
{ "DUP INTERSECT DISTANCE          ", 5, 171, 0, 0, 0, 0, ' ', ' ' }, 
{ "HEALTH CENTER DISTRICT          ", 2, 182, 0, 0, 0, 0, ' ', ' ' }, 
{ "SANITATION DISTRICT             ", 3, 184, 0, 0, 0, 0, ' ', ' ' }, 
{ "SANIT SUB SECTION               ", 2, 187, 0, 0, 0, 0, ' ', ' ' }, 
{ "FILLER                          ", 12, 189, 0, 0, 0, 0, ' ', ' ' }, 
}; 

int n_wa2_f2_field_recs = sizeof(wa2_f2_fld_strs) / sizeof(FIELDENTRY); 
//PFIELDENTRY wa2_f2_flds = &wa2_f2_fld_strs; 
PFIELDENTRY wa2_f2_flds = (PFIELDENTRY)wa2_f2_fld_strs; 
