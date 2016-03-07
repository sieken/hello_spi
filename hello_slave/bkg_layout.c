/* bkg_layout.c

   This file written by David J.
   Contains the graphical layout for the background drawn on gameboy screen. */



/*
BKG table
tl:  sym   tl:  sym  tl:  sym  tl:  sym  tl:  sym  tl:   sym tl:   sym
------------------------------------------------------------------
0: (spc) 21: 5    42: J    63: _    84: t       105: q3.1   126: q8.4    147: q14.2   168: b9
1: !     22: 6    43: K    64: `    85: u       106: q3.4   127: q9.2    148: q14.3   169: b10
2: "     23: 7    44: L    65: a    86: v       107: q4.2   128: q9.3    149: q14.1   170: b11
3: #     24: 8    45: M    66: b    87: w       108: q4.3   129: q9.1    150: q14.4   171: .
4: $     25: 9    46: N    67: c    88: x       109: q4.1   130: q9.4    151: q15.2   172: .
5: %     26: :    47: O    68: d    89: y       110: q4.4   131: q10.2   152: q15.3   173: .
6: &     27: ;    48: P    69: e    90: z       111: q5.2   132: q10.3   153: q15.1   174: .
7: '     28: <    49: Q    70: f    91: {       112: q5.3   133: q10.1   154: q15.4   175: .
8. (     29: =    50: R    71: g    92: |       113: q5.1   134: q10.4   155: q16.2   176: .
9: )     30: >    51: S    72: h    93: }       114: q5.4   135: q11.2   156: q16.3   177: .
10 *     31: ?    52: T    73: i    94: ~       115: q6.2   136: q11.3   157: q16.1   178: .
11 +     32: @    53: U    74: j    95: q1.2    116: q6.3   137: q11.1   158: q16.4   179: .
12 ,     33: A    54: V    75: k    96: q1.3    117: q6.1   138: q11.4   159: b0      180: .
13 -     34: B    55: W    76: l    97: q1.1    118: q6.4   139: q12.2   160: b1      181: .
14 .     35: C    56: X    77: m    98: q1.4    119: q7.2   140: q12.3   161: b2      182: .
15 /     36: D    57: Y    78: n    99: q2.2    120: q7.3   141: q12.1   162: b3      183: .
16 0     37: E    58: Z    79: o    100:q2.3    121: q7.1   142: q12.4   163: b4      184: .
17 1     38: F    59: [    80: p    101:q2.1    122: q7.4   143: q13.2   164: b5      185: .
18 2     39: G    60: \    81: q    102:q2.4    123: q8.2   144: q13.3   165: b6      186: .
19 3     40: H    61: ]    82: r    103:q3.2    124: q8.3   145: q13.1   166: b7      187: .
20 4     41: I    62: ^    83: s    104:q3.3    125: q8.1   146: q13.4   167: b8      188: .
14

SPRITE
--------------------------------
0:  pointer


*/

/* placement (in tiles) of bkg_data on screen
   18 rows of 20 tiles each, numbers representing tile number
   in bkg_data table */
const unsigned char tweetboy_bkg[] = {
159,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,161,  //ind 0-19
166,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,162,  //ind 20-39
166,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,162,  //ind 40-59
166,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,162,  //ind 60-79
166,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,162,  //ind 80-99
166,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,162,  //ind 100-119
166,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,162,  //ind 120-139
166,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,162,  //ind 140-159
166,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,162,  //ind 160-179
165,164,164,164,164,164,164,164,167,169,164,164,164,164,164,164,164,164,164,163,  //ind 180-199

 95, 97,103,105,127,129,135,137,168,170,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  //ind 200-219
 96, 98,104,106,128,130,136,138,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  //ind 220-239
 99,101,107,109,131,133,139,141,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  //ind 240-259
100,102,108,110,132,134,140,142,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  //ind 260-279
111,113,119,121,143,145,151,153,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  //ind 280-299
112,114,120,122,144,146,152,154,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  //ind 300-319
115,117,123,125,147,149,155,157,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  //ind 320-339
116,118,124,126,148,150,156,158,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  //ind 340-359
};
/*
 01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20*/
