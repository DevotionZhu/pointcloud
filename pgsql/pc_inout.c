
#include "pc_pgsql.h"      /* Common PgSQL support for our type */

/* In/out functions */
Datum pcpoint_in(PG_FUNCTION_ARGS);
Datum pcpoint_out(PG_FUNCTION_ARGS);

/* Other SQL functions */
Datum PC_SchemaIsValid(PG_FUNCTION_ARGS);



// PG_FUNCTION_INFO_V1(pcpoint_in);
// Datum pcpoint_in(PG_FUNCTION_ARGS)
// {
// 	char *str = PG_GETARG_CSTRING(0);
// 	/* Datum geog_oid = PG_GETARG_OID(1); Not needed. */
// 	int32 pc_typmod = -1;
// 	PCPOINT *pt;
// 
// 	if ( (PG_NARGS()>2) && (!PG_ARGISNULL(2)) ) 
// 	{
// 		pc_typmod = PG_GETARG_INT32(2);
// 	}
// 
// 	/* Empty string. */
// 	if ( str[0] == '\0' )
// 	{
// 		ereport(ERROR,(errmsg("parse error - invalid pcpoint")));
// 	}
// 
// 	/* Binary or text form? Let's find out. */
// 	if ( str[0] == '0' )
// 	{
// 		pt = pc_point_from_hexbytes(
// 		size_t strsize = strlen(str);
// 		uint8_t *bytes = bytes_from_hexbytes(str, 
// 	}
// 	else
// 	{
// 		ereport(ERROR,(errmsg("parse error - support for text format not yet implemented")));
// 	}
// 

PG_FUNCTION_INFO_V1(PC_SchemaIsValid);
Datum PC_SchemaIsValid(PG_FUNCTION_ARGS)
{
	bool valid;
	text *xml = PG_GETARG_TEXT_P(0);
	char *xmlstr = text_to_cstring(xml);
	PCSCHEMA *schema;
	int err = pc_schema_from_xml(xmlstr, &schema);
	pfree(xmlstr);
	
	if ( ! err )
	{
		PG_RETURN_BOOL(FALSE);
	}

	valid = pc_schema_is_valid(schema);
	PG_RETURN_BOOL(valid);
}
