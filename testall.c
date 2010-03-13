/***************************************************************************
*                 Hamming Encoding and Decoding Test Program
*
*   File    : testall.c
*   Purpose : Test program for Hamming encode and decode routines.  This
*             module tests the Hamming encode and decode routines, ensuring
*             they produce correct results.  Two special run-time options
*             have been added.  When called with the E option, this program
*             will write a table of encoded values to stdout.  When called
*             with the D option this program will write standard and packed
*             tables of decode values to stdout.
*   Author  : Michael Dipperstein
*   Date    : December 29, 2004
*
****************************************************************************
*   UPDATES
*
*   $Id: testall.c,v 1.5 2007/09/19 13:08:15 michael Exp $
*   $Log: testall.c,v $
*   Revision 1.5  2007/09/19 13:08:15  michael
*   Licensed under LGPL V3.
*
*   Revision 1.4  2007/02/13 05:12:37  michael
*   trimmed lines.
*
*   Revision 1.3  2005/10/24 12:48:48  michael
*   Add test to verify that all single bitr errors are corrected.
*
*   Revision 1.2  2005/10/24 12:33:12  michael
*   corrected errors in decode matrices pointed out by Ivan Piasini
*   <furettoo@gmail.com>
*
*   Revision 1.1.1.1  2005/01/02 05:06:45  michael
*   Initial version
*
*
****************************************************************************
*
* Testall: ANSI C Test prorgam for Hamming Encoding/Decoding routines
* Copyright (C) 2004, 2007 by Michael Dipperstein (mdipper@cs.ucsb.edu)
*
* This file is part of the Hamming library.
*
* The Hamming library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation; either version 3 of the
* License, or (at your option) any later version.
*
* The Hamming library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
* General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
***************************************************************************/

/***************************************************************************
*                             INCLUDED FILES
***************************************************************************/
#include <stdio.h>
#include "hamming.h"

/***************************************************************************
*                               PROTOTYPES
***************************************************************************/
void TestAll(void);
void BuildCodeTable(void);
void BuildDecodeTables(void);

/***************************************************************************
*                                FUNCTIONS
***************************************************************************/

/***************************************************************************
*   Function   : main
*   Description: This function is the enterance point for the testall
*                program.  The default mode of operation for this function
*                is to verify that the Hamming decode function works on the
*                results of the Hamming encode function.  It then verifies
*                that each version of the encode and decode functions
*                produce identical results.  When called with the E option,
*                this function will call a routine that writes a table of
*                encoded values to stdout.  When called with the D option
*                this functions will call a routine that writes standard
*                and packed tables of decode values to stdout.
*   Parameters : argc - number of command line arguements
*                argv - command line arguments.
*                       argv[1][0] == 'E' outputs encode table
*                       argv[1][0] == 'D' outputs decode table
*   Effects    : Results of verify are written to stdout
*   Returned   : This function always returns 0.
***************************************************************************/
int main(int argc, char *argv[])
{
    /* determine how to behave */
    if (2 == argc)
    {
        if (('e' == argv[1][0]) || ('E' == argv[1][0]))
        {
            /* use matrix to dump code table to stdout */
            BuildCodeTable();
        }
        else if (('d' == argv[1][0]) || ('D' == argv[1][0]))
        {
            /* use matrix to dump decode tables to stdout */
            BuildDecodeTables();
        }

        return 0;
    }

    /* test every function */
    TestAll();

    return 0;
}

/***************************************************************************
*   Function   : TestAll
*   Description: This function verifies that the Hamming encode function
*                produces resutls which are correctly decoded by the decode
*                function.  Then it verifies that all versions of the encode
*                function produce identical results and all versions of the
*                decode function produce identical results.  The results of
*                each operation and any error that may occur are written
*                to stdout.
*   Parameters : None
*   Effects    : Results of verify are written to stdout
*   Returned   : None
***************************************************************************/
void TestAll(void)
{
    unsigned char testValue;
    unsigned char result1, result2, result3;
    unsigned char error;

    /* verify that decode is the reverse of encode */
    printf("Verifying Matched Encode/Decode ...\n");
    printf("Value\tEncoded\tDecoded\n");
    for (testValue = 0x00; testValue < DATA_VALUES; testValue++)
    {
        result1 = HammingMatrixEncode(testValue);
        result2 = HammingMatrixDecode(result1);

        if (testValue != result2)
        {
            printf("*** Error Decoding: %02X ****\n", testValue);
        }

        printf("%02X\t%02X\t%02X\n", testValue, result1, result2);
    }

    /* verify that all versions of encode produce the same results */
    printf("\nVerifying Encodes Match ...\n");
    printf("Value\tMatrix\tTable\n");
    for (testValue = 0x00; testValue < DATA_VALUES; testValue++)
    {
        result1 = HammingMatrixEncode(testValue);
        result2 = HammingTableEncode(testValue);

        if (result1 != result2)
        {
            printf("*** Error Encoding: %02X ****\n", testValue);
        }

        printf("%02X\t%02X\t%02X\n", testValue, result1, result2);
    }

    /* verify that all versions of decode produce the same results */
    printf("\nVerifying Decodes Match ...\n");
    printf("Value\tMatrix\tTable\tPacked\n");
    for (testValue = 0x00; testValue < CODE_VALUES; testValue++)
    {
        result1 = HammingMatrixDecode(testValue);
        result2 = HammingTableDecode(testValue);
        result3 = HammingPackedTableDecode(testValue);

        if ((result1 != result2) || (result1 != result3))
        {
            printf("*** Error Decoding: %02X ****\n", testValue);
        }

        printf("%02X\t%02X\t%02X\t%02X\n",
            testValue, result1, result2, result3);
    }

    /* verify that all single bit errors are corrected */
    printf("Verifying Single Bit Errors Are Corrected ...\n");
    printf("Value\tEncoded\tError\tDecoded\n");
    for (testValue = 0x00; testValue < DATA_VALUES; testValue++)
    {
        result1 = HammingMatrixEncode(testValue);

        for (error = 0x01; error < 0x80; error <<= 1)
        {
            result2 = result1 ^ error;
            result3 = HammingMatrixDecode(result2);

            if (testValue != result3)
            {
                printf("*** Error Decoding: %02X ****\n", result2);
            }

            printf("%02X\t%02X\t%02X\t%02X\n",
                testValue, result1, result2, result3);
        }
    }
}

/***************************************************************************
*   Function   : BuildCodeTable
*   Description: This function uses HammingMatrixEncode to output text
*                suitable to be used for replacing the array hammingCodes
*                in hamming.c.
*   Parameters : None
*   Effects    : Table in format sutibale for replacing hammingCodes in
*                hamming.c is written to stdout.
*   Returned   : None
***************************************************************************/
void BuildCodeTable(void)
{
    unsigned char value;
    unsigned char result;

    printf("Dumping Encode Table ...\n");
    printf("const unsigned char hammingCodes[DATA_VALUES] =\n");
    printf("{\n    ");
    for (value = 0x00; value < (DATA_VALUES - 1); value++)
    {
        result = HammingMatrixEncode(value);
        printf("0x%02X,  /* %X */\n    ", result, value);
    }

    result = HammingMatrixEncode(value);
    printf("0x%02X   /* %X */\n};\n", result, value);
}

/***************************************************************************
*   Function   : BuildDecodeTables
*   Description: This function uses HammingMatrixDecode to output text
*                suitable to be used for replacing the arrays
*                hammingDecodeValues and hammingPackedDecodeValues in
*                hamming.c.
*   Parameters : None
*   Effects    : Tables in format sutibale for replacing
*                hammingDecodeValues and hammingPackedDecodeValues in
*                hamming.c are written to stdout.
*   Returned   : None
***************************************************************************/
void BuildDecodeTables(void)
{
    unsigned char value;
    unsigned char result;

    printf("Dumping Decode Table ...\n");
    printf("const unsigned char hammingDecodeValues[CODE_VALUES] =\n");
    printf("{\n    ");
    for (value = 0x00; value < (CODE_VALUES - 1); value++)
    {
        result = HammingMatrixDecode(value);
        printf("0x%02X, ", result);

        if (7 == (value % 8))
        {
            printf("    /* 0x%02X to 0x%02X */\n    ", (value - 7), value);
        }
    }

    result = HammingMatrixDecode(value);
    printf("0x%02X      /* 0x%02X to 0x%02X */\n};\n",
        result, (value - 7), value);

    printf("\nDumping Packed Decode Table ...\n");
    printf("const unsigned char hammingPackedDecodeValues[CODE_VALUES] =\n");
    printf("{\n    ");
    for (value = 0x00; value < (CODE_VALUES - 2);)
    {
        result = HammingMatrixDecode(value++);
        printf("0x%1X", result);

        result = HammingMatrixDecode(value++);
        printf("%1X, ", result);

        if (0 == (value % 8))
        {
            printf("    /* 0x%02X to 0x%02X */\n    ",
                (value - 8), (value - 1));
        }
    }

    result = HammingMatrixDecode(value++);
    printf("0x%1X", result);

    result = HammingMatrixDecode(value);
    printf("%1X      /* 0x%02X to 0x%02X */\n};\n", result, (value - 7), value);
}
