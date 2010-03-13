/***************************************************************************
*                   Hamming Encoding and Decoding Headers
*
*   File    : hamming.h
*   Purpose : Header for Hamming encode and decode routines.  Contains the
*             prototypes to be used by programs linking to the Hamming
*             library.
*   Author  : Michael Dipperstein
*   Date    : December 29, 2004
*
****************************************************************************
*   UPDATES
*
*   $Id: hamming.h,v 1.2 2007/09/19 13:08:15 michael Exp $
*   $Log: hamming.h,v $
*   Revision 1.2  2007/09/19 13:08:15  michael
*   Licensed under LGPL V3.
*
*   Revision 1.1.1.1  2005/01/02 05:06:45  michael
*   Initial version
*
*
****************************************************************************
*
* Hamming: A collection of ANSI C Hamming Encoding/Decoding routines
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
#ifndef _HAMMING_H
#define _HAMMING_H

/***************************************************************************
*                             INCLUDED FILES
***************************************************************************/
#include <limits.h>

/***************************************************************************
*                                CONSTANTS
***************************************************************************/
/* number of uncoded data bits and data values */
#define DATA_BITS       4
#define DATA_VALUES     (1 << DATA_BITS)

/* number of parity bits and data values */
#define PARITY_BITS     3
#define PARITY_VALUES   (1 << PARITY_BITS)

/* number of code bits (data + parity) and data values */
#define CODE_BITS       (DATA_BITS + PARITY_BITS)
#define CODE_VALUES     (1 << CODE_BITS)

#if (CODE_BITS > CHAR_BIT)
#error Encoded data must fit in an unsigned char
#endif

/***************************************************************************
*                               PROTOTYPES
***************************************************************************/
/* compute left justified 7 bit Hamming code from 4 bit data */
unsigned char HammingMatrixEncode(unsigned char data);
unsigned char HammingTableEncode(unsigned char data);

/* compute left justified 4 bit data value from 7 bit Hamming code */
unsigned char HammingMatrixDecode(unsigned char code);
unsigned char HammingTableDecode(unsigned char code);
unsigned char HammingPackedTableDecode(unsigned char code);

#endif      /* ndef _HAMMING_H */
