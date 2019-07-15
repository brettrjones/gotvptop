//============================================================================
// Copyright (C) 2003 Brett R. Jones
//
// Issued to public domain 2013
//
// bjones.engineer@gmail.com
// http://www.gotvptop.com
//============================================================================

#include "config_corelib.h"

#include "VxChopMap.h"
#include "VxParse.h"

#include <string.h>

//============================================================================
// ascii
//============================================================================

unsigned char aucCharToCommon[] =
{
	//char  value  idx
	0x00,	//0
	100,  // 032  // 1
	101,  // 101  // 2
	102,  // 111  // 3
	103,  // 097  // 4
	104,  // 110  // 5
	105,  // 046  // 6
	106,  // 114  // 7
	107,  // 105  // 8
	 71,  // 116  // 9
	 72,  // 045  // 10
	108,  // 115  // 11
	109,  // 108  // 12
	 73,  // 104  // 13
	110,  // 084  // 14
	111,  // 100  // 15
	112,  // 117  // 16
	113,  // 121  // 17
	114,  // 103  // 18
	115,  // 109  // 19
	116,  // 083  // 20
	117,  // 099  // 21
	118,  // 065  // 22
	119,  // 076  // 23
	120,  // 066  // 24
	121,  // 077  // 25
	122,  // 048  // 26
	123,  // 067  // 27
	124,  // 107  // 28
	125,  // 073  // 29
	126,  // 068  // 30
	127,  // 087  // 31
	  1,  // 118  // 32
	 68,  // 112  // 33
	 89,  // 102  // 34
	 58,  // 071  // 35
	 84,  // 082  // 36
	 90,  // 072  // 37
	 74,  // 079  // 38
     82,  // 119  // 39
     45,  // 092  // 40
	 47,  // 049  // 41
     70,  // 089  // 42
	 91,  // 095  // 43
	 75,  // 070  // 44
	 10,  // 040  // 45
	  6,  // 069  // 46
	 92,  // 041  // 47
	 26,  // 078  // 48
	 41,  // 098  // 49
	55,  // 080  // 50
	56,  // 074  // 51
	59,  // 093  // 52
	57 ,  // 091  // 53
	60,  // 075  // 54
	63,  // 050  // 55
	62,  // 051  // 56
	61,  // 053  // 57
	67,  // 035  // 58
	85,  // 052  // 59
	93,  // 054  // 60
	86,  // 057  // 61
	94,  // 056  // 62
	69,  // 055  // 63
	95,  // 085  // 64
	22,  // 120  // 65
	24,  // 086  // 66
	27,  // 058  // 67
	30,  // 033  // 68
	46,  // 063  // 69
	44,  // 042  // 70
	35,	  // 009  // 71 - tab
	37,	  // 010, // 72 - cr
	29,	  // 013  // 73 - lf
	51,  // 038  // 74
	54,  // 044  // 75
	23,  // 122  // 76
	25,  // 106  // 77
	48,  // 081  // 78
	38,  // 090  // 79
	50,  // 113  // 80
	78,  // 088  // 81
	36,   // 039  // 82 - single quote
	20,  // 126  // 83
	14,  // 036  // 84
	64,  // 059  // 85
	66,  // 061  // 86
	31,  // 123  // 87
	81,  // 125  // 88
	42,  // 034  // 89
	79,  // 037  // 90
	53,  // 043  // 91
	40,  // 047  // 92
	52,  // 060  // 93
	96,  // 062  // 94
	43,  // 064  // 95
	97,  // 094  // 96
	 4,  // 096  // 97
	49,  // 124  // 98
    21,  //    // 99 //c
	//control codes
	15,	  //001 //100
	 2,	  //002 //101
    34,	//003 //102
	18,	//004 //103
	13,	//005 //104
	 8,	//006 //105
	77,	//007 //106
	28,	//007 //107
	12,	//011 //108
	19,	//012 //109
	 5,	//014 //110
	 3,	//015 //111
	33,	//016 //112
	80,	//017 //113
	 7,	//018 //114
	11,	//019 //115
	 9,	//020 //116
	16,	//021 //117
	32,	//022 //118
	39,	//023 //119
	65,	//024 //120
	17,	//025 //121
	76,	//026 //122
	87,	//027 //123
	98,	//028 //124	
	88,	//029 //125
	83,	//030 //126
	99,	//021 //127
//chars above 127 not allowed but here in case of programming error
	0x80,	0x81,	0x82,	0x83,	0x84,	0x85,	0x86,	0x87,	//128
	0x88,	0x89,	0x8A,	0x8B,	0x8C,	0x8D,	0x8E,	0x8F,	//136
	0x90,	0x91,	0x92,	0x93,	0x94,	0x95,	0x96,	0x97,	//144
	0x98,	0x99,	0x9A,	0x9B,	0x9C,	0x9D,	0x9E,	0x9F,	//152
	0xa0,	0xA1,	0xA2,	0xA3,	0xA4,	0xA5,	0xA6,	0xA7,	//160
	0xA8,	0xA9,	0xAA,	0xAB,	0xAC,	0xAD,	0xAE,	0xAF,	//168
	0xB0,	0xB1,	0xB2,	0xB3,	0xB4,	0xB5,	0xB6,	0xB7,	//176
	0xB8,	0xB9,	0xBA,	0xBB,	0xBC,	0xBD,	0xBE,	0xBF,	//184
	0xC0,	0xC1,	0xC2,	0xC3,	0xC4,	0xC5,	0xC6,	0xC7,	//192
	0xC8,	0xC9,	0xCA,	0xCB,	0xCC,	0xCD,	0xCE,	0xCF,	//200
	0xD0,	0xD1,	0xD2,	0xD3,	0xD4,	0xD5,	0xD6,	0xD7,	//208
	0xD8,	0xD9,	0xDA,	0xDB,	0xDC,	0xDD,	0xDE,	0xDF,	//216
	0xE0,	0xE1,	0xE2,	0xE3,	0xE4,	0xE5,	0xE6,	0xE7,	//224
	0xE8,	0xE9,	0xEA,	0xEB,	0xEC,	0xED,	0xEE,	0xEF,	//232
	0xF0,	0xF1,	0xF2,	0xF3,	0xF4,	0xF5,	0xF6,	0xF7,	//240-247
	0xF8,	0xF9,	0xfA,	0xFB,	0xFC,	0xFD,	0xfE,	0xFF	//248-256
};


unsigned char aucCommonToChar[] =
{
	//char  value  idx
	0x00,	//0
	' ',  // 032  // 1
	'e',  // 101  // 2
	'o',  // 111  // 3
	'a',  // 097  // 4
	'n',  // 110  // 5
	'.',  // 046  // 6
	'r',  // 114  // 7
	'i',  // 105  // 8
	't',  // 116  // 9
	'-',  // 045  // 10
	's',  // 115  // 11
	'l',  // 108  // 12
	'h',  // 104  // 13
	'T',  // 066  // 14
	'd',  // 100  // 15
	'u',  // 117  // 16
	'y',  // 121  // 17
	'g',  // 103  // 18
	'm',  // 109  // 19
	'S',  // 083  // 20
	'c',  // 099  // 21
	'A',  // 065  // 22
	'L',  // 076  // 23
	'B',  // 084  // 24
	'M',  // 077  // 25
	'0',  // 048  // 26
	'C',  // 067  // 27
	'k',  // 107  // 28
	'I',  // 073  // 29
	'D',  // 068  // 30
	'W',  // 087  // 31
	'v',  // 118  // 32
	'p',  // 112  // 33
	'f',  // 102  // 34
	'G',  // 071  // 35
	'R',  // 082  // 36
	'H',  // 072  // 37
	'O',  // 079  // 38
	'w',  // 119  // 39
   '\\',  // 092  // 40
	'1',  // 049  // 41
	'Y',  // 089  // 42
	'_',  // 095  // 43
	'F',  // 070  // 44
	'(',  // 040  // 45
	'E',  // 069  // 46
	')',  // 041  // 47
	'N',  // 078  // 48
	'b',  // 098  // 49
	'P',  // 080  // 50
	'J',  // 074  // 51
	']',  // 093  // 52
	'[',  // 091  // 53
	'K',  // 075  // 54
	'2',  // 050  // 55
	'3',  // 051  // 56
	'5',  // 053  // 57
	'#',  // 035  // 58
	'4',  // 052  // 59
	'6',  // 054  // 60
	'9',  // 057  // 61
	'8',  // 056  // 62
	'7',  // 055  // 63
	'U',  // 085  // 64
	'x',  // 120  // 65
	'V',  // 086  // 66
	':',  // 058  // 67
	'!',  // 033  // 68
	'?',  // 063  // 69
	'*',  // 042  // 70
	9,	  // 009  // 71 - tab
	10,	  // 010, // 72 - cr
	13,	  // 013  // 73 - lf
	'&',  // 038  // 74
	',',  // 044  // 75
	'z',  // 122  // 76
	'j',  // 106  // 77
	'Q',  // 081  // 78
	'Z',  // 090  // 79
	'q',  // 113  // 80
	'X',  // 088  // 81
	39,   // 039  // 82 - single quote
	'~',  // 126  // 83
	'$',  // 036  // 84
	';',  // 059  // 85
	'=',  // 061  // 86
	'{',  // 123  // 87
	'}',  // 125  // 88
	'"',  // 034  // 89
	'%',  // 037  // 90
	'+',  // 043  // 91
	'/',  // 047  // 92
	'<',  // 060  // 93
	'>',  // 062  // 94
	'@',  // 064  // 95
	'^',  // 094  // 96
	'`',  // 096  // 97
	'|',  // 124  // 98
	127,  // 127  // 99
	//control codes
	0x01,	//001 //100
	0x02,	//002 //101
	0x03,	//003 //102
	0x04,	//004 //103
	0x05,	//005 //104
	0x06,	//006 //105
	0x07,	//007 //106
	0x08,	//007 //107
	0x0b,	//011 //108
	0x0c,	//012 //109
	0x0e,	//014 //110
	0x0f,	//015 //111
	0x10,	//016 //112
	0x11,	//017 //113
	0x12,	//018 //114
	0x13,	//019 //115
	0x14,	//020 //116
	0x15,	//021 //117
	0x16,	//022 //118
	0x17,	//023 //119
	0x18,	//024 //120
	0x19,	//025 //121
	0x1a,	//026 //122
	0x1b,	//027 //123
	0x1c,	//028 //124	
	0x1d,	//029 //125
	0x1e,	//030 //126
	0x1f,	//031 //127
//chars above 127 not allowed but here in case of programming error
	0x80,	0x81,	0x82,	0x83,	0x84,	0x85,	0x86,	0x87,	//128
	0x88,	0x89,	0x8A,	0x8B,	0x8C,	0x8D,	0x8E,	0x8F,	//136
	0x90,	0x91,	0x92,	0x93,	0x94,	0x95,	0x96,	0x97,	//144
	0x98,	0x99,	0x9A,	0x9B,	0x9C,	0x9D,	0x9E,	0x9F,	//152
	0xa0,	0xA1,	0xA2,	0xA3,	0xA4,	0xA5,	0xA6,	0xA7,	//160
	0xA8,	0xA9,	0xAA,	0xAB,	0xAC,	0xAD,	0xAE,	0xAF,	//168
	0xB0,	0xB1,	0xB2,	0xB3,	0xB4,	0xB5,	0xB6,	0xB7,	//176
	0xB8,	0xB9,	0xBA,	0xBB,	0xBC,	0xBD,	0xBE,	0xBF,	//184
	0xC0,	0xC1,	0xC2,	0xC3,	0xC4,	0xC5,	0xC6,	0xC7,	//192
	0xC8,	0xC9,	0xCA,	0xCB,	0xCC,	0xCD,	0xCE,	0xCF,	//200
	0xD0,	0xD1,	0xD2,	0xD3,	0xD4,	0xD5,	0xD6,	0xD7,	//208
	0xD8,	0xD9,	0xDA,	0xDB,	0xDC,	0xDD,	0xDE,	0xDF,	//216
	0xE0,	0xE1,	0xE2,	0xE3,	0xE4,	0xE5,	0xE6,	0xE7,	//224
	0xE8,	0xE9,	0xEA,	0xEB,	0xEC,	0xED,	0xEE,	0xEF,	//232
	0xF0,	0xF1,	0xF2,	0xF3,	0xF4,	0xF5,	0xF6,	0xF7,	//240-247
	0xF8,	0xF9,	0xfA,	0xFB,	0xFC,	0xFD,	0xfE,	0xFF	//248-255
};

//============================================================================
void VxMapStr( char * pStr )
{
	int iLen = (int)strlen( pStr );
	for( int i = 0; i < iLen; i++ )
	{
		pStr[i] = (unsigned char )aucCharToCommon[ (unsigned char )pStr[i] ];
	}
}

//============================================================================
void VxUnMapStr( char * pStr )
{
	int iLen = (int)strlen( pStr );
	for( int i = 0; i < iLen; i++ )
	{
		pStr[i] = aucCommonToChar[ ( unsigned char )pStr[i]];
	}
}

//============================================================================
// wide char
//============================================================================
uint16_t aucWCharToCommon[] =
{
	//char  value  idx
	0x00,	//0
	100,  // 032  // 1
	101,  // 101  // 2
	102,  // 111  // 3
	103,  // 097  // 4
	104,  // 110  // 5
	105,  // 046  // 6
	106,  // 114  // 7
	107,  // 105  // 8
	71,  // 116  // 9
	72,  // 045  // 10
	108,  // 115  // 11
	109,  // 108  // 12
	73,  // 104  // 13
	110,  // 084  // 14
	111,  // 100  // 15
	112,  // 117  // 16
	113,  // 121  // 17
	114,  // 103  // 18
	115,  // 109  // 19
	116,  // 083  // 20
	117,  // 099  // 21
	118,  // 065  // 22
	119,  // 076  // 23
	120,  // 066  // 24
	121,  // 077  // 25
	122,  // 048  // 26
	123,  // 067  // 27
	124,  // 107  // 28
	125,  // 073  // 29
	126,  // 068  // 30
	127,  // 087  // 31
	1,  // 118  // 32
	68,  // 112  // 33
	89,  // 102  // 34
	58,  // 071  // 35
	84,  // 082  // 36
	90,  // 072  // 37
	74,  // 079  // 38
	82,  // 119  // 39
	45,  // 092  // 40
	47,  // 049  // 41
	70,  // 089  // 42
	91,  // 095  // 43
	75,  // 070  // 44
	10,  // 040  // 45
	6,  // 069  // 46
	92,  // 041  // 47
	26,  // 078  // 48
	41,  // 098  // 49
	55,  // 080  // 50
	56,  // 074  // 51
	59,  // 093  // 52
	57 ,  // 091  // 53
	60,  // 075  // 54
	63,  // 050  // 55
	62,  // 051  // 56
	61,  // 053  // 57
	67,  // 035  // 58
	85,  // 052  // 59
	93,  // 054  // 60
	86,  // 057  // 61
	94,  // 056  // 62
	69,  // 055  // 63
	95,  // 085  // 64
	22,  // 120  // 65
	24,  // 086  // 66
	27,  // 058  // 67
	30,  // 033  // 68
	46,  // 063  // 69
	44,  // 042  // 70
	35,	  // 009  // 71 - tab
	37,	  // 010, // 72 - cr
	29,	  // 013  // 73 - lf
	51,  // 038  // 74
	54,  // 044  // 75
	23,  // 122  // 76
	25,  // 106  // 77
	48,  // 081  // 78
	38,  // 090  // 79
	50,  // 113  // 80
	78,  // 088  // 81
	36,   // 039  // 82 - single quote
	20,  // 126  // 83
	14,  // 036  // 84
	64,  // 059  // 85
	66,  // 061  // 86
	31,  // 123  // 87
	81,  // 125  // 88
	42,  // 034  // 89
	79,  // 037  // 90
	53,  // 043  // 91
	40,  // 047  // 92
	52,  // 060  // 93
	96,  // 062  // 94
	43,  // 064  // 95
	97,  // 094  // 96
	4,  // 096  // 97
	49,  // 124  // 98
	21,  //    // 99 //c
	//control codes
	15,	  //001 //100
	2,	  //002 //101
	34,	//003 //102
	18,	//004 //103
	13,	//005 //104
	8,	//006 //105
	77,	//007 //106
	28,	//007 //107
	12,	//011 //108
	19,	//012 //109
	5,	//014 //110
	3,	//015 //111
	33,	//016 //112
	80,	//017 //113
	7,	//018 //114
	11,	//019 //115
	9,	//020 //116
	16,	//021 //117
	32,	//022 //118
	39,	//023 //119
	65,	//024 //120
	17,	//025 //121
	76,	//026 //122
	87,	//027 //123
	98,	//028 //124	
	88,	//029 //125
	83,	//030 //126
	99,	//021 //127
	//chars above 127 not allowed but here in case of programming error
	0x80,	0x81,	0x82,	0x83,	0x84,	0x85,	0x86,	0x87,	//128
	0x88,	0x89,	0x8A,	0x8B,	0x8C,	0x8D,	0x8E,	0x8F,	//136
	0x90,	0x91,	0x92,	0x93,	0x94,	0x95,	0x96,	0x97,	//144
	0x98,	0x99,	0x9A,	0x9B,	0x9C,	0x9D,	0x9E,	0x9F,	//152
	0xa0,	0xA1,	0xA2,	0xA3,	0xA4,	0xA5,	0xA6,	0xA7,	//160
	0xA8,	0xA9,	0xAA,	0xAB,	0xAC,	0xAD,	0xAE,	0xAF,	//168
	0xB0,	0xB1,	0xB2,	0xB3,	0xB4,	0xB5,	0xB6,	0xB7,	//176
	0xB8,	0xB9,	0xBA,	0xBB,	0xBC,	0xBD,	0xBE,	0xBF,	//184
	0xC0,	0xC1,	0xC2,	0xC3,	0xC4,	0xC5,	0xC6,	0xC7,	//192
	0xC8,	0xC9,	0xCA,	0xCB,	0xCC,	0xCD,	0xCE,	0xCF,	//200
	0xD0,	0xD1,	0xD2,	0xD3,	0xD4,	0xD5,	0xD6,	0xD7,	//208
	0xD8,	0xD9,	0xDA,	0xDB,	0xDC,	0xDD,	0xDE,	0xDF,	//216
	0xE0,	0xE1,	0xE2,	0xE3,	0xE4,	0xE5,	0xE6,	0xE7,	//224
	0xE8,	0xE9,	0xEA,	0xEB,	0xEC,	0xED,	0xEE,	0xEF,	//232
	0xF0,	0xF1,	0xF2,	0xF3,	0xF4,	0xF5,	0xF6,	0xF7,	//240-247
	0xF8,	0xF9,	0xfA,	0xFB,	0xFC,	0xFD,	0xfE,	0xFF	//248-256
};

uint16_t aucCommonToWChar[] =
{
	//char  value  idx
	0x00,	//0
	' ',  // 032  // 1
	'e',  // 101  // 2
	'o',  // 111  // 3
	'a',  // 097  // 4
	'n',  // 110  // 5
	'.',  // 046  // 6
	'r',  // 114  // 7
	'i',  // 105  // 8
	't',  // 116  // 9
	'-',  // 045  // 10
	's',  // 115  // 11
	'l',  // 108  // 12
	'h',  // 104  // 13
	'T',  // 066  // 14
	'd',  // 100  // 15
	'u',  // 117  // 16
	'y',  // 121  // 17
	'g',  // 103  // 18
	'm',  // 109  // 19
	'S',  // 083  // 20
	'c',  // 099  // 21
	'A',  // 065  // 22
	'L',  // 076  // 23
	'B',  // 084  // 24
	'M',  // 077  // 25
	'0',  // 048  // 26
	'C',  // 067  // 27
	'k',  // 107  // 28
	'I',  // 073  // 29
	'D',  // 068  // 30
	'W',  // 087  // 31
	'v',  // 118  // 32
	'p',  // 112  // 33
	'f',  // 102  // 34
	'G',  // 071  // 35
	'R',  // 082  // 36
	'H',  // 072  // 37
	'O',  // 079  // 38
	'w',  // 119  // 39
	'\\',  // 092  // 40
	'1',  // 049  // 41
	'Y',  // 089  // 42
	'_',  // 095  // 43
	'F',  // 070  // 44
	'(',  // 040  // 45
	'E',  // 069  // 46
	')',  // 041  // 47
	'N',  // 078  // 48
	'b',  // 098  // 49
	'P',  // 080  // 50
	'J',  // 074  // 51
	']',  // 093  // 52
	'[',  // 091  // 53
	'K',  // 075  // 54
	'2',  // 050  // 55
	'3',  // 051  // 56
	'5',  // 053  // 57
	'#',  // 035  // 58
	'4',  // 052  // 59
	'6',  // 054  // 60
	'9',  // 057  // 61
	'8',  // 056  // 62
	'7',  // 055  // 63
	'U',  // 085  // 64
	'x',  // 120  // 65
	'V',  // 086  // 66
	':',  // 058  // 67
	'!',  // 033  // 68
	'?',  // 063  // 69
	'*',  // 042  // 70
	9,	  // 009  // 71 - tab
	10,	  // 010, // 72 - cr
	13,	  // 013  // 73 - lf
	'&',  // 038  // 74
	',',  // 044  // 75
	'z',  // 122  // 76
	'j',  // 106  // 77
	'Q',  // 081  // 78
	'Z',  // 090  // 79
	'q',  // 113  // 80
	'X',  // 088  // 81
	39,   // 039  // 82 - single quote
	'~',  // 126  // 83
	'$',  // 036  // 84
	';',  // 059  // 85
	'=',  // 061  // 86
	'{',  // 123  // 87
	'}',  // 125  // 88
	'"',  // 034  // 89
	'%',  // 037  // 90
	'+',  // 043  // 91
	'/',  // 047  // 92
	'<',  // 060  // 93
	'>',  // 062  // 94
	'@',  // 064  // 95
	'^',  // 094  // 96
	'`',  // 096  // 97
	'|',  // 124  // 98
	127,  // 127  // 99
	//control codes
	0x01,	//001 //100
	0x02,	//002 //101
	0x03,	//003 //102
	0x04,	//004 //103
	0x05,	//005 //104
	0x06,	//006 //105
	0x07,	//007 //106
	0x08,	//007 //107
	0x0b,	//011 //108
	0x0c,	//012 //109
	0x0e,	//014 //110
	0x0f,	//015 //111
	0x10,	//016 //112
	0x11,	//017 //113
	0x12,	//018 //114
	0x13,	//019 //115
	0x14,	//020 //116
	0x15,	//021 //117
	0x16,	//022 //118
	0x17,	//023 //119
	0x18,	//024 //120
	0x19,	//025 //121
	0x1a,	//026 //122
	0x1b,	//027 //123
	0x1c,	//028 //124	
	0x1d,	//029 //125
	0x1e,	//030 //126
	0x1f,	//031 //127
	//chars above 127 not allowed but here in case of programming error
	0x80,	0x81,	0x82,	0x83,	0x84,	0x85,	0x86,	0x87,	//128
	0x88,	0x89,	0x8A,	0x8B,	0x8C,	0x8D,	0x8E,	0x8F,	//136
	0x90,	0x91,	0x92,	0x93,	0x94,	0x95,	0x96,	0x97,	//144
	0x98,	0x99,	0x9A,	0x9B,	0x9C,	0x9D,	0x9E,	0x9F,	//152
	0xa0,	0xA1,	0xA2,	0xA3,	0xA4,	0xA5,	0xA6,	0xA7,	//160
	0xA8,	0xA9,	0xAA,	0xAB,	0xAC,	0xAD,	0xAE,	0xAF,	//168
	0xB0,	0xB1,	0xB2,	0xB3,	0xB4,	0xB5,	0xB6,	0xB7,	//176
	0xB8,	0xB9,	0xBA,	0xBB,	0xBC,	0xBD,	0xBE,	0xBF,	//184
	0xC0,	0xC1,	0xC2,	0xC3,	0xC4,	0xC5,	0xC6,	0xC7,	//192
	0xC8,	0xC9,	0xCA,	0xCB,	0xCC,	0xCD,	0xCE,	0xCF,	//200
	0xD0,	0xD1,	0xD2,	0xD3,	0xD4,	0xD5,	0xD6,	0xD7,	//208
	0xD8,	0xD9,	0xDA,	0xDB,	0xDC,	0xDD,	0xDE,	0xDF,	//216
	0xE0,	0xE1,	0xE2,	0xE3,	0xE4,	0xE5,	0xE6,	0xE7,	//224
	0xE8,	0xE9,	0xEA,	0xEB,	0xEC,	0xED,	0xEE,	0xEF,	//232
	0xF0,	0xF1,	0xF2,	0xF3,	0xF4,	0xF5,	0xF6,	0xF7,	//240-247
	0xF8,	0xF9,	0xfA,	0xFB,	0xFC,	0xFD,	0xfE,	0xFF	//248-255
};

//============================================================================
void VxMapStr( wchar_t * pStr )
{
	int iLen = (int)wstrlen( pStr );
	for( int i = 0; i < iLen; i++ )
	{
		pStr[i] = (wchar_t)aucWCharToCommon[ (uint16_t)pStr[i] ];
	}
}

//============================================================================
void VxUnMapStr( wchar_t * pStr )
{
	int iLen = (int)wstrlen( pStr );
	for( int i = 0; i < iLen; i++ )
	{
		pStr[i] = aucCommonToWChar[ ( wchar_t )pStr[i] ];
	}
}
