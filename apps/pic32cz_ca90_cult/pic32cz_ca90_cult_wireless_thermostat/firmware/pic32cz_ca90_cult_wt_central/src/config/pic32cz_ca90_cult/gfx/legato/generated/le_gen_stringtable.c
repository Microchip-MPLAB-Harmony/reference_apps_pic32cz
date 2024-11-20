#include "gfx/legato/generated/le_gen_assets.h"

/*****************************************************************************
 * Legato String Table
 * Encoding        ASCII
 * Language Count: 1
 * String Count:   10
 *****************************************************************************/

/*****************************************************************************
 * string table data
 * 
 * this table contains the raw character data for each string
 * 
 * unsigned short - number of indices in the table
 * unsigned short - number of languages in the table
 * 
 * index array (size = number of indices * number of languages
 * 
 * for each index in the array:
 *   unsigned byte - the font ID for the index
 *   unsigned byte[3] - the offset of the string codepoint data in
 *                      the table
 * 
 * string data is found by jumping to the index offset from the start
 * of the table
 * 
 * string data entry:
 *     unsigned short - length of the string in bytes (encoding dependent)
 *     codepoint data - the string data
 ****************************************************************************/

const uint8_t stringTable_data[146] =
{
    0x0A,0x00,0x01,0x00,0x01,0x2C,0x00,0x00,0x02,0x3C,0x00,0x00,0x01,0x52,0x00,0x00,
    0x01,0x56,0x00,0x00,0x05,0x6C,0x00,0x00,0x02,0x72,0x00,0x00,0x02,0x7E,0x00,0x00,
    0x06,0x86,0x00,0x00,0x04,0x8A,0x00,0x00,0x04,0x8E,0x00,0x00,0x0D,0x00,0x43,0x6F,
    0x6E,0x6E,0x65,0x63,0x74,0x69,0x6E,0x67,0x2E,0x2E,0x2E,0x00,0x13,0x00,0x57,0x69,
    0x72,0x65,0x6C,0x65,0x73,0x73,0x20,0x54,0x68,0x65,0x72,0x6D,0x6F,0x73,0x74,0x61,
    0x74,0x00,0x02,0x00,0x32,0x35,0x13,0x00,0x50,0x72,0x65,0x73,0x73,0x20,0x74,0x6F,
    0x20,0x47,0x6F,0x20,0x62,0x61,0x63,0x6B,0x2E,0x2E,0x2E,0x00,0x04,0x00,0x48,0x6F,
    0x6D,0x65,0x0A,0x00,0x53,0x45,0x54,0x20,0x20,0x4C,0x49,0x4D,0x49,0x54,0x05,0x00,
    0x53,0x54,0x41,0x52,0x54,0x00,0x01,0x00,0x6F,0x00,0x01,0x00,0x31,0x00,0x01,0x00,
    0x32,0x00,
};

/* font asset pointer list */
leFont* fontList[6] =
{
    (leFont*)&Font0,
    (leFont*)&Font1,
    (leFont*)&Font2,
    (leFont*)&Font3,
    (leFont*)&Font4,
    (leFont*)&Font5,
};

const leStringTable stringTable =
{
    {
        LE_STREAM_LOCATION_ID_INTERNAL, // data location id
        (void*)stringTable_data, // data address pointer
        146, // data size
    },
    (void*)stringTable_data, // string table data
    fontList, // font lookup table
    LE_STRING_ENCODING_ASCII // encoding standard
};


// string list
leTableString string_Connecting;
leTableString string_Thermostat_demo;
leTableString string_Default_Temp;
leTableString string_Go_back;
leTableString string_Home;
leTableString string_SetThreshold;
leTableString string_Start;
leTableString string_degree;
leTableString string_Node1;
leTableString string_Node2;

void initializeStrings(void)
{
    leTableString_Constructor(&string_Connecting, stringID_Connecting);
    leTableString_Constructor(&string_Thermostat_demo, stringID_Thermostat_demo);
    leTableString_Constructor(&string_Default_Temp, stringID_Default_Temp);
    leTableString_Constructor(&string_Go_back, stringID_Go_back);
    leTableString_Constructor(&string_Home, stringID_Home);
    leTableString_Constructor(&string_SetThreshold, stringID_SetThreshold);
    leTableString_Constructor(&string_Start, stringID_Start);
    leTableString_Constructor(&string_degree, stringID_degree);
    leTableString_Constructor(&string_Node1, stringID_Node1);
    leTableString_Constructor(&string_Node2, stringID_Node2);
}
