/******************************************************************************/
// Bullfrog Engine Emulation Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet or Dungeon Keeper.
/******************************************************************************/
/** @file bflib_render_gpoly.c
 *     Rendering function draw_gpoly() for drawing 3D view elements.
 * @par Purpose:
 *     Function for rendering 3D elements.
 * @par Comment:
 *     Go away from here, you bad optimizer! Do not compile this with optimizations.
 * @author   Tomasz Lis
 * @date     20 Mar 2009 - 14 Feb 2010
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "poly.h"

#include "bfendian.h"

#include "globals.h"
#include "swlog.h"

/******************************************************************************/
struct gpoly_state {
    int var_1B0;
    int var_1AC;
    int var_1A8;
    int var_1A4;
    int var_1A0;
    int var_19C;
    int var_198;
    int var_194;
    int var_190;
    int var_18C;
    int var_188;
    int var_184;
    int var_180;
    int var_17C;
    int var_178;
    int var_174;
    int var_170;
    int var_16C;
    int var_168;
    int var_164;
    int var_160;
    int var_15C;
    int var_158;
    int var_154;
    int var_150;
    int var_14C;
    int var_148;
    int var_144;
    int var_140;
    int var_13C;
    int var_138;
    int var_134;
    int var_130;
    int var_12C;
    int var_128;
    int var_124;
    int var_120;
    int var_11C;
    int var_118;
    int var_114;
    int var_110;
    int var_10C;
    int var_108;
    int var_104;
    int var_100;
    int var_0FC;
    int var_0F8;
    int var_0F4;
    int var_0F0;
    int var_0EC;
    int var_0E8;
    int var_0E4;
    int var_0E0;
    int var_0DC;
    int var_0D8;
    int var_0D4;
    int var_0D0;
    int var_0CC;
    int var_0C8;
    int var_0C4;
    int var_0C0;
    int var_0BC;
    int var_0B8;
    int var_0B4;
    int var_0B0;
    int var_0AC;
    int var_0A8;
    int var_0A4;
    int var_0A0;
    int var_09C;
    int var_098;
    int var_094;
    int var_090;
    int var_08C;
    int var_088;
    int var_084;
    int var_080;
    int var_07C;
    int var_078;
    int var_074;
    int var_070;
    int var_06C;
    int var_068;
    int var_064;
    int var_060;
    int var_05C;
    int var_058;
    int var_054;
    int var_050;
    int var_04C;
    int var_048;
    int var_044;
    int var_040;
    int var_03C;
    int var_038;
    int var_034;
    int var_030;
    int var_02C;
    int var_028;
    int var_024;
};


const long gpoly_countdown[] = { 0,-15,-14,-13,-12,-11,-10, -9,  -8, -7, -6, -5, -4, -3, -2, -1 };

const long gpoly_reptable[] = {
         0x0,0x7FFFFFFF,0x3FFFFFFF,0x2AAAAAAA,0x1FFFFFFF,0x19999999,0x15555555,0x12492492,
  0x0FFFFFFF,0x0E38E38E,0x0CCCCCCC,0x0BA2E8BA,0x0AAAAAAA, 0x9D89D89, 0x9249249, 0x8888888,
   0x7FFFFFF, 0x7878787, 0x71C71C7, 0x6BCA1AF, 0x6666666, 0x6186186, 0x5D1745D, 0x590B216,
   0x5555555, 0x51EB851, 0x4EC4EC4, 0x4BDA12F, 0x4924924, 0x469EE58, 0x4444444, 0x4210842,
   0x3FFFFFF, 0x3E0F83E, 0x3C3C3C3, 0x3A83A83, 0x38E38E3, 0x3759F22, 0x35E50D7, 0x3483483,
   0x3333333, 0x31F3831, 0x30C30C3, 0x2FA0BE8, 0x2E8BA2E, 0x2D82D82, 0x2C8590B, 0x2B93105,
   0x2AAAAAA, 0x29CBC14, 0x28F5C28, 0x2828282, 0x2762762, 0x26A439F, 0x25ED097, 0x253C825,
   0x2492492, 0x23EE08F, 0x234F72C, 0x22B63CB, 0x2222222, 0x2192E29, 0x2108421, 0x2082082,
   0x1FFFFFF, 0x1F81F81, 0x1F07C1F, 0x1E9131A, 0x1E1E1E1, 0x1DAE607, 0x1D41D41, 0x1CD8568,
   0x1C71C71, 0x1C0E070, 0x1BACF91, 0x1B4E81B, 0x1AF286B, 0x1A98EF6, 0x1A41A41, 0x19EC8E9,
   0x1999999, 0x1948B0F, 0x18F9C18, 0x18ACB90, 0x1861861, 0x1818181, 0x17D05F4, 0x178A4C8,
   0x1745D17, 0x1702E05, 0x16C16C1, 0x1681681, 0x1642C85, 0x1605816, 0x15C9882, 0x158ED23,
   0x1555555, 0x151D07E, 0x14E5E0A, 0x14AFD6A, 0x147AE14, 0x1446F86, 0x1414141, 0x13E22CB,
   0x13B13B1, 0x1381381, 0x13521CF, 0x1323E34, 0x12F684B, 0x12C9FB4, 0x129E412, 0x127350B,
   0x1249249, 0x121FB78, 0x11F7047, 0x11CF06A, 0x11A7B96, 0x1181181, 0x115B1E5, 0x1135C81,
   0x1111111, 0x10ECF56, 0x10C9714, 0x10A6810, 0x1084210, 0x10624DD, 0x1041041, 0x1020408,
   0x0FFFFFF, 0x0FE03F8, 0x0FC0FC0, 0x0FA232C, 0x0F83E0F, 0x0F6603D, 0x0F4898D, 0x0F2B9D6,
   0x0F0F0F0, 0x0EF2EB7, 0x0ED7303, 0x0EBBDB2, 0x0EA0EA0, 0x0E865AC, 0x0E6C2B4, 0x0E52598,
   0x0E38E38, 0x0E1FC78, 0x0E07038, 0x0DEE95C, 0x0DD67C8, 0x0DBEB61, 0x0DA740D, 0x0D901B2,
   0x0D79435, 0x0D62B80, 0x0D4C77B, 0x0D3680D, 0x0D20D20, 0x0D0B69F, 0x0CF6474, 0x0CE168A,
   0x0CCCCCC, 0x0CB8727, 0x0CA4587, 0x0C907DA, 0x0C7CE0C, 0x0C6980C, 0x0C565C8, 0x0C4372F,
   0x0C30C30, 0x0C1E4BB, 0x0C0C0C0, 0x0BFA02F, 0x0BE82FA, 0x0BD6910, 0x0BC5264, 0x0BB3EE7,
   0x0BA2E8B, 0x0B92143, 0x0B81702, 0x0B70FBB, 0x0B60B60, 0x0B509E6, 0x0B40B40, 0x0B30F63,
   0x0B21642, 0x0B11FD3, 0x0B02C0B, 0x0AF3ADD, 0x0AE4C41, 0x0AD602B, 0x0AC7691, 0x0AB8F69,
   0x0AAAAAA, 0x0A9C84A, 0x0A8E83F, 0x0A80A80, 0x0A72F05, 0x0A655C4, 0x0A57EB5, 0x0A4A9CF,
   0x0A3D70A, 0x0A3065E, 0x0A237C3, 0x0A16B31, 0x0A0A0A0, 0x09FD809, 0x09F1165, 0x09E4CAD,
   0x09D89D8, 0x09CC8E1, 0x09C09C0, 0x09B4C6F, 0x09A90E7, 0x099D722, 0x0991F1A, 0x09868C8,
   0x097B425, 0x097012E, 0x0964FDA, 0x095A025, 0x094F209, 0x0944580, 0x0939A85, 0x092F113,
   0x0924924, 0x091A2B3, 0x090FDBC, 0x0905A38, 0x08FB823, 0x08F1779, 0x08E7835, 0x08DDA52,
   0x08D3DCB, 0x08CA29C, 0x08C08C0, 0x08B7034, 0x08AD8F2, 0x08A42F8, 0x089AE40, 0x0891AC7,
   0x0888888, 0x087F780, 0x08767AB, 0x086D905, 0x0864B8A, 0x085BF37, 0x0853408, 0x084A9F9,
   0x0842108, 0x0839930, 0x083126E, 0x0828CBF, 0x0820820, 0x081848D, 0x0810204, 0x0808080,
         0x0,       0x0 };

const long gpoly_divtable[][64] = {
   {-8388607,-8388607,-8388607,-8388607,-8388607,-8388607,-8388607,-8388607,
    -8388607,-8388607,-8388607,-8388607,-8388607,-8388607,-8388607,-8388607,
    -8388607,-8388607,-8388607,-8388607,-8388607,-8388607,-8388607,-8388607,
    -8388607,-8388607,-8388607,-8388607,-8388607,-8388607,-8388607,-8388607,
           0, 8388607, 8388607, 8388607, 8388607, 8388607, 8388607, 8388607,
     8388607, 8388607, 8388607, 8388607, 8388607, 8388607, 8388607, 8388607,
     8388607, 8388607, 8388607, 8388607, 8388607, 8388607, 8388607, 8388607,
     8388607, 8388607, 8388607, 8388607, 8388607, 8388607, 8388607, 8388607,},
   {-2097152,-2031616,-1966080,-1900544,-1835008,-1769472,-1703936,-1638400,
    -1572864,-1507328,-1441792,-1376256,-1310720,-1245184,-1179648,-1114112,
    -1048576, -983040, -917504, -851968, -786432, -720896, -655360, -589824,
     -524288, -458752, -393216, -327680, -262144, -196608, -131072,  -65536,
           0,   65536,  131072,  196608,  262144,  327680,  393216,  458752,
      524288,  589824,  655360,  720896,  786432,  851968,  917504,  983040,
     1048576, 1114112, 1179648, 1245184, 1310720, 1376256, 1441792, 1507328,
     1572864, 1638400, 1703936, 1769472, 1835008, 1900544, 1966080, 2031616,},
   {-1048576,-1015808, -983040, -950272, -917504, -884736, -851968, -819200,
     -786432, -753664, -720896, -688128, -655360, -622592, -589824, -557056,
     -524288, -491520, -458752, -425984, -393216, -360448, -327680, -294912,
     -262144, -229376, -196608, -163840, -131072,  -98304,  -65536,  -32768,
           0,   32768,   65536,   98304,  131072,  163840,  196608,  229376,
      262144,  294912,  327680,  360448,  393216,  425984,  458752,  491520,
      524288,  557056,  589824,  622592,  655360,  688128,  720896,  753664,
      786432,  819200,  851968,  884736,  917504,  950272,  983040, 1015808,},
   { -699050, -677205, -655360, -633514, -611669, -589824, -567978, -546133,
     -524288, -502442, -480597, -458752, -436906, -415061, -393216, -371370,
     -349525, -327680, -305834, -283989, -262144, -240298, -218453, -196608,
     -174762, -152917, -131072, -109226,  -87381,  -65536,  -43690,  -21845,
           0,   21845,   43690,   65536,   87381,  109226,  131072,  152917,
      174762,  196608,  218453,  240298,  262144,  283989,  305834,  327680,
      349525,  371370,  393216,  415061,  436906,  458752,  480597,  502442,
      524288,  546133,  567978,  589824,  611669,  633514,  655360,  677205,},
   { -524288, -507904, -491520, -475136, -458752, -442368, -425984, -409600,
     -393216, -376832, -360448, -344064, -327680, -311296, -294912, -278528,
     -262144, -245760, -229376, -212992, -196608, -180224, -163840, -147456,
     -131072, -114688,  -98304,  -81920,  -65536,  -49152,  -32768,  -16384,
           0,   16384,   32768,   49152,   65536,   81920,   98304,  114688,
      131072,  147456,  163840,  180224,  196608,  212992,  229376,  245760,
      262144,  278528,  294912,  311296,  327680,  344064,  360448,  376832,
      393216,  409600,  425984,  442368,  458752,  475136,  491520,  507904,},
   { -419430, -406323, -393216, -380108, -367001, -353894, -340787, -327680,
     -314572, -301465, -288358, -275251, -262144, -249036, -235929, -222822,
     -209715, -196608, -183500, -170393, -157286, -144179, -131072, -117964,
     -104857,  -91750,  -78643,  -65536,  -52428,  -39321,  -26214,  -13107,
           0,   13107,   26214,   39321,   52428,   65536,   78643,   91750,
      104857,  117964,  131072,  144179,  157286,  170393,  183500,  196608,
      209715,  222822,  235929,  249036,  262144,  275251,  288358,  301465,
      314572,  327680,  340787,  353894,  367001,  380108,  393216,  406323,},
   { -349525, -338602, -327680, -316757, -305834, -294912, -283989, -273066,
     -262144, -251221, -240298, -229376, -218453, -207530, -196608, -185685,
     -174762, -163840, -152917, -141994, -131072, -120149, -109226,  -98304,
      -87381,  -76458,  -65536,  -54613,  -43690,  -32768,  -21845,  -10922,
           0,   10922,   21845,   32768,   43690,   54613,   65536,   76458,
       87381,   98304,  109226,  120149,  131072,  141994,  152917,  163840,
      174762,  185685,  196608,  207530,  218453,  229376,  240298,  251221,
      262144,  273066,  283989,  294912,  305834,  316757,  327680,  338602,},
   { -299593, -290230, -280868, -271506, -262144, -252781, -243419, -234057,
     -224694, -215332, -205970, -196608, -187245, -177883, -168521, -159158,
     -149796, -140434, -131072, -121709, -112347, -102985,  -93622,  -84260,
      -74898,  -65536,  -56173,  -46811,  -37449,  -28086,  -18724,   -9362,
           0,    9362,   18724,   28086,   37449,   46811,   56173,   65536,
       74898,   84260,   93622,  102985,  112347,  121709,  131072,  140434,
      149796,  159158,  168521,  177883,  187245,  196608,  205970,  215332,
      224694,  234057,  243419,  252781,  262144,  271506,  280868,  290230,},
   { -262144, -253952, -245760, -237568, -229376, -221184, -212992, -204800,
     -196608, -188416, -180224, -172032, -163840, -155648, -147456, -139264,
     -131072, -122880, -114688, -106496,  -98304,  -90112,  -81920,  -73728,
      -65536,  -57344,  -49152,  -40960,  -32768,  -24576,  -16384,   -8192,
           0,    8192,   16384,   24576,   32768,   40960,   49152,   57344,
       65536,   73728,   81920,   90112,   98304,  106496,  114688,  122880,
      131072,  139264,  147456,  155648,  163840,  172032,  180224,  188416,
      196608,  204800,  212992,  221184,  229376,  237568,  245760,  253952,},
   { -233016, -225735, -218453, -211171, -203889, -196608, -189326, -182044,
     -174762, -167480, -160199, -152917, -145635, -138353, -131072, -123790,
     -116508, -109226, -101944,  -94663,  -87381,  -80099,  -72817,  -65536,
      -58254,  -50972,  -43690,  -36408,  -29127,  -21845,  -14563,   -7281,
           0,    7281,   14563,   21845,   29127,   36408,   43690,   50972,
       58254,   65536,   72817,   80099,   87381,   94663,  101944,  109226,
      116508,  123790,  131072,  138353,  145635,  152917,  160199,  167480,
      174762,  182044,  189326,  196608,  203889,  211171,  218453,  225735,},
   { -209715, -203161, -196608, -190054, -183500, -176947, -170393, -163840,
     -157286, -150732, -144179, -137625, -131072, -124518, -117964, -111411,
     -104857,  -98304,  -91750,  -85196,  -78643,  -72089,  -65536,  -58982,
      -52428,  -45875,  -39321,  -32768,  -26214,  -19660,  -13107,   -6553,
           0,    6553,   13107,   19660,   26214,   32768,   39321,   45875,
       52428,   58982,   65536,   72089,   78643,   85196,   91750,   98304,
      104857,  111411,  117964,  124518,  131072,  137625,  144179,  150732,
      157286,  163840,  170393,  176947,  183500,  190054,  196608,  203161,},
   { -190650, -184692, -178734, -172776, -166818, -160861, -154903, -148945,
     -142987, -137029, -131072, -125114, -119156, -113198, -107240, -101282,
      -95325,  -89367,  -83409,  -77451,  -71493,  -65536,  -59578,  -53620,
      -47662,  -41704,  -35746,  -29789,  -23831,  -17873,  -11915,   -5957,
           0,    5957,   11915,   17873,   23831,   29789,   35746,   41704,
       47662,   53620,   59578,   65536,   71493,   77451,   83409,   89367,
       95325,  101282,  107240,  113198,  119156,  125114,  131072,  137029,
      142987,  148945,  154903,  160861,  166818,  172776,  178734,  184692,},
   { -174762, -169301, -163840, -158378, -152917, -147456, -141994, -136533,
     -131072, -125610, -120149, -114688, -109226, -103765,  -98304,  -92842,
      -87381,  -81920,  -76458,  -70997,  -65536,  -60074,  -54613,  -49152,
      -43690,  -38229,  -32768,  -27306,  -21845,  -16384,  -10922,   -5461,
           0,    5461,   10922,   16384,   21845,   27306,   32768,   38229,
       43690,   49152,   54613,   60074,   65536,   70997,   76458,   81920,
       87381,   92842,   98304,  103765,  109226,  114688,  120149,  125610,
      131072,  136533,  141994,  147456,  152917,  158378,  163840,  169301,},
   { -161319, -156278, -151236, -146195, -141154, -136113, -131072, -126030,
     -120989, -115948, -110907, -105865, -100824,  -95783,  -90742,  -85700,
      -80659,  -75618,  -70577,  -65536,  -60494,  -55453,  -50412,  -45371,
      -40329,  -35288,  -30247,  -25206,  -20164,  -15123,  -10082,   -5041,
           0,    5041,   10082,   15123,   20164,   25206,   30247,   35288,
       40329,   45371,   50412,   55453,   60494,   65536,   70577,   75618,
       80659,   85700,   90742,   95783,  100824,  105865,  110907,  115948,
      120989,  126030,  131072,  136113,  141154,  146195,  151236,  156278,},
   { -149796, -145115, -140434, -135753, -131072, -126390, -121709, -117028,
     -112347, -107666, -102985,  -98304,  -93622,  -88941,  -84260,  -79579,
      -74898,  -70217,  -65536,  -60854,  -56173,  -51492,  -46811,  -42130,
      -37449,  -32768,  -28086,  -23405,  -18724,  -14043,   -9362,   -4681,
           0,    4681,    9362,   14043,   18724,   23405,   28086,   32768,
       37449,   42130,   46811,   51492,   56173,   60854,   65536,   70217,
       74898,   79579,   84260,   88941,   93622,   98304,  102985,  107666,
      112347,  117028,  121709,  126390,  131072,  135753,  140434,  145115,},
   { -139810, -135441, -131072, -126702, -122333, -117964, -113595, -109226,
     -104857, -100488,  -96119,  -91750,  -87381,  -83012,  -78643,  -74274,
      -69905,  -65536,  -61166,  -56797,  -52428,  -48059,  -43690,  -39321,
      -34952,  -30583,  -26214,  -21845,  -17476,  -13107,   -8738,   -4369,
           0,    4369,    8738,   13107,   17476,   21845,   26214,   30583,
       34952,   39321,   43690,   48059,   52428,   56797,   61166,   65536,
       69905,   74274,   78643,   83012,   87381,   91750,   96119,  100488,
      104857,  109226,  113595,  117964,  122333,  126702,  131072,  135441,},
   { -131072, -126976, -122880, -118784, -114688, -110592, -106496, -102400,
      -98304,  -94208,  -90112,  -86016,  -81920,  -77824,  -73728,  -69632,
      -65536,  -61440,  -57344,  -53248,  -49152,  -45056,  -40960,  -36864,
      -32768,  -28672,  -24576,  -20480,  -16384,  -12288,   -8192,   -4096,
           0,    4096,    8192,   12288,   16384,   20480,   24576,   28672,
       32768,   36864,   40960,   45056,   49152,   53248,   57344,   61440,
       65536,   69632,   73728,   77824,   81920,   86016,   90112,   94208,
       98304,  102400,  106496,  110592,  114688,  118784,  122880,  126976,},
   { -123361, -119506, -115651, -111796, -107941, -104086, -100231,  -96376,
      -92521,  -88666,  -84811,  -80956,  -77101,  -73246,  -69391,  -65536,
      -61680,  -57825,  -53970,  -50115,  -46260,  -42405,  -38550,  -34695,
      -30840,  -26985,  -23130,  -19275,  -15420,  -11565,   -7710,   -3855,
           0,    3855,    7710,   11565,   15420,   19275,   23130,   26985,
       30840,   34695,   38550,   42405,   46260,   50115,   53970,   57825,
       61680,   65536,   69391,   73246,   77101,   80956,   84811,   88666,
       92521,   96376,  100231,  104086,  107941,  111796,  115651,  119506,},
   { -116508, -112867, -109226, -105585, -101944,  -98304,  -94663,  -91022,
      -87381,  -83740,  -80099,  -76458,  -72817,  -69176,  -65536,  -61895,
      -58254,  -54613,  -50972,  -47331,  -43690,  -40049,  -36408,  -32768,
      -29127,  -25486,  -21845,  -18204,  -14563,  -10922,   -7281,   -3640,
           0,    3640,    7281,   10922,   14563,   18204,   21845,   25486,
       29127,   32768,   36408,   40049,   43690,   47331,   50972,   54613,
       58254,   61895,   65536,   69176,   72817,   76458,   80099,   83740,
       87381,   91022,   94663,   98304,  101944,  105585,  109226,  112867,},
   { -110376, -106927, -103477, -100028,  -96579,  -93130,  -89680,  -86231,
      -82782,  -79333,  -75883,  -72434,  -68985,  -65536,  -62086,  -58637,
      -55188,  -51738,  -48289,  -44840,  -41391,  -37941,  -34492,  -31043,
      -27594,  -24144,  -20695,  -17246,  -13797,  -10347,   -6898,   -3449,
           0,    3449,    6898,   10347,   13797,   17246,   20695,   24144,
       27594,   31043,   34492,   37941,   41391,   44840,   48289,   51738,
       55188,   58637,   62086,   65536,   68985,   72434,   75883,   79333,
       82782,   86231,   89680,   93130,   96579,  100028,  103477,  106927,},
   { -104857, -101580,  -98304,  -95027,  -91750,  -88473,  -85196,  -81920,
      -78643,  -75366,  -72089,  -68812,  -65536,  -62259,  -58982,  -55705,
      -52428,  -49152,  -45875,  -42598,  -39321,  -36044,  -32768,  -29491,
      -26214,  -22937,  -19660,  -16384,  -13107,   -9830,   -6553,   -3276,
           0,    3276,    6553,    9830,   13107,   16384,   19660,   22937,
       26214,   29491,   32768,   36044,   39321,   42598,   45875,   49152,
       52428,   55705,   58982,   62259,   65536,   68812,   72089,   75366,
       78643,   81920,   85196,   88473,   91750,   95027,   98304,  101580,},
   {  -99864,  -96743,  -93622,  -90502,  -87381,  -84260,  -81139,  -78019,
      -74898,  -71777,  -68656,  -65536,  -62415,  -59294,  -56173,  -53052,
      -49932,  -46811,  -43690,  -40569,  -37449,  -34328,  -31207,  -28086,
      -24966,  -21845,  -18724,  -15603,  -12483,   -9362,   -6241,   -3120,
           0,    3120,    6241,    9362,   12483,   15603,   18724,   21845,
       24966,   28086,   31207,   34328,   37449,   40569,   43690,   46811,
       49932,   53052,   56173,   59294,   62415,   65536,   68656,   71777,
       74898,   78019,   81139,   84260,   87381,   90502,   93622,   96743,},
   {  -95325,  -92346,  -89367,  -86388,  -83409,  -80430,  -77451,  -74472,
      -71493,  -68514,  -65536,  -62557,  -59578,  -56599,  -53620,  -50641,
      -47662,  -44683,  -41704,  -38725,  -35746,  -32768,  -29789,  -26810,
      -23831,  -20852,  -17873,  -14894,  -11915,   -8936,   -5957,   -2978,
           0,    2978,    5957,    8936,   11915,   14894,   17873,   20852,
       23831,   26810,   29789,   32768,   35746,   38725,   41704,   44683,
       47662,   50641,   53620,   56599,   59578,   62557,   65536,   68514,
       71493,   74472,   77451,   80430,   83409,   86388,   89367,   92346,},
   {  -91180,  -88331,  -85481,  -82632,  -79782,  -76933,  -74084,  -71234,
      -68385,  -65536,  -62686,  -59837,  -56987,  -54138,  -51289,  -48439,
      -45590,  -42740,  -39891,  -37042,  -34192,  -31343,  -28493,  -25644,
      -22795,  -19945,  -17096,  -14246,  -11397,   -8548,   -5698,   -2849,
           0,    2849,    5698,    8548,   11397,   14246,   17096,   19945,
       22795,   25644,   28493,   31343,   34192,   37042,   39891,   42740,
       45590,   48439,   51289,   54138,   56987,   59837,   62686,   65536,
       68385,   71234,   74084,   76933,   79782,   82632,   85481,   88331,},
   {  -87381,  -84650,  -81920,  -79189,  -76458,  -73728,  -70997,  -68266,
      -65536,  -62805,  -60074,  -57344,  -54613,  -51882,  -49152,  -46421,
      -43690,  -40960,  -38229,  -35498,  -32768,  -30037,  -27306,  -24576,
      -21845,  -19114,  -16384,  -13653,  -10922,   -8192,   -5461,   -2730,
           0,    2730,    5461,    8192,   10922,   13653,   16384,   19114,
       21845,   24576,   27306,   30037,   32768,   35498,   38229,   40960,
       43690,   46421,   49152,   51882,   54613,   57344,   60074,   62805,
       65536,   68266,   70997,   73728,   76458,   79189,   81920,   84650,},
   {  -83886,  -81264,  -78643,  -76021,  -73400,  -70778,  -68157,  -65536,
      -62914,  -60293,  -57671,  -55050,  -52428,  -49807,  -47185,  -44564,
      -41943,  -39321,  -36700,  -34078,  -31457,  -28835,  -26214,  -23592,
      -20971,  -18350,  -15728,  -13107,  -10485,   -7864,   -5242,   -2621,
           0,    2621,    5242,    7864,   10485,   13107,   15728,   18350,
       20971,   23592,   26214,   28835,   31457,   34078,   36700,   39321,
       41943,   44564,   47185,   49807,   52428,   55050,   57671,   60293,
       62914,   65536,   68157,   70778,   73400,   76021,   78643,   81264,},
   {  -80659,  -78139,  -75618,  -73097,  -70577,  -68056,  -65536,  -63015,
      -60494,  -57974,  -55453,  -52932,  -50412,  -47891,  -45371,  -42850,
      -40329,  -37809,  -35288,  -32768,  -30247,  -27726,  -25206,  -22685,
      -20164,  -17644,  -15123,  -12603,  -10082,   -7561,   -5041,   -2520,
           0,    2520,    5041,    7561,   10082,   12603,   15123,   17644,
       20164,   22685,   25206,   27726,   30247,   32768,   35288,   37809,
       40329,   42850,   45371,   47891,   50412,   52932,   55453,   57974,
       60494,   63015,   65536,   68056,   70577,   73097,   75618,   78139,},
   {  -77672,  -75245,  -72817,  -70390,  -67963,  -65536,  -63108,  -60681,
      -58254,  -55826,  -53399,  -50972,  -48545,  -46117,  -43690,  -41263,
      -38836,  -36408,  -33981,  -31554,  -29127,  -26699,  -24272,  -21845,
      -19418,  -16990,  -14563,  -12136,   -9709,   -7281,   -4854,   -2427,
           0,    2427,    4854,    7281,    9709,   12136,   14563,   16990,
       19418,   21845,   24272,   26699,   29127,   31554,   33981,   36408,
       38836,   41263,   43690,   46117,   48545,   50972,   53399,   55826,
       58254,   60681,   63108,   65536,   67963,   70390,   72817,   75245,},
   {  -74898,  -72557,  -70217,  -67876,  -65536,  -63195,  -60854,  -58514,
      -56173,  -53833,  -51492,  -49152,  -46811,  -44470,  -42130,  -39789,
      -37449,  -35108,  -32768,  -30427,  -28086,  -25746,  -23405,  -21065,
      -18724,  -16384,  -14043,  -11702,   -9362,   -7021,   -4681,   -2340,
           0,    2340,    4681,    7021,    9362,   11702,   14043,   16384,
       18724,   21065,   23405,   25746,   28086,   30427,   32768,   35108,
       37449,   39789,   42130,   44470,   46811,   49152,   51492,   53833,
       56173,   58514,   60854,   63195,   65536,   67876,   70217,   72557,},
   {  -72315,  -70055,  -67795,  -65536,  -63276,  -61016,  -58756,  -56496,
      -54236,  -51976,  -49716,  -47457,  -45197,  -42937,  -40677,  -38417,
      -36157,  -33897,  -31638,  -29378,  -27118,  -24858,  -22598,  -20338,
      -18078,  -15819,  -13559,  -11299,   -9039,   -6779,   -4519,   -2259,
           0,    2259,    4519,    6779,    9039,   11299,   13559,   15819,
       18078,   20338,   22598,   24858,   27118,   29378,   31638,   33897,
       36157,   38417,   40677,   42937,   45197,   47457,   49716,   51976,
       54236,   56496,   58756,   61016,   63276,   65536,   67795,   70055,},
   {  -69905,  -67720,  -65536,  -63351,  -61166,  -58982,  -56797,  -54613,
      -52428,  -50244,  -48059,  -45875,  -43690,  -41506,  -39321,  -37137,
      -34952,  -32768,  -30583,  -28398,  -26214,  -24029,  -21845,  -19660,
      -17476,  -15291,  -13107,  -10922,   -8738,   -6553,   -4369,   -2184,
           0,    2184,    4369,    6553,    8738,   10922,   13107,   15291,
       17476,   19660,   21845,   24029,   26214,   28398,   30583,   32768,
       34952,   37137,   39321,   41506,   43690,   45875,   48059,   50244,
       52428,   54613,   56797,   58982,   61166,   63351,   65536,   67720,},
   {  -67650,  -65536,  -63421,  -61307,  -59193,  -57079,  -54965,  -52851,
      -50737,  -48623,  -46509,  -44395,  -42281,  -40167,  -38053,  -35939,
      -33825,  -31710,  -29596,  -27482,  -25368,  -23254,  -21140,  -19026,
      -16912,  -14798,  -12684,  -10570,   -8456,   -6342,   -4228,   -2114,
           0,    2114,    4228,    6342,    8456,   10570,   12684,   14798,
       16912,   19026,   21140,   23254,   25368,   27482,   29596,   31710,
       33825,   35939,   38053,   40167,   42281,   44395,   46509,   48623,
       50737,   52851,   54965,   57079,   59193,   61307,   63421,   65536,},
};

long gpoly_pro_enable_mode_ofs;
// Static variables used only inside draw_gpoly().
// These don't really have to be global; but this helps
// in using these inside assembly code
long gpoly_mode;

/******************************************************************************/
void gpoly_enable_pentium_pro(TbBool state)
{
  LOGSYNC("Pentium Pro polygon rendering %s",state?"on":"off");
  if (state)
    gpoly_pro_enable_mode_ofs = (1<<6);
  else
    gpoly_pro_enable_mode_ofs = 0;
}

void draw_trigpoly(struct PolyPoint *point_a, struct PolyPoint *point_b, struct PolyPoint *point_c)
{
    switch (vec_mode)
    {
    case 5:
    case 27:
      draw_gpoly(point_a, point_b, point_c);
      break;
    default:
      trig(point_a, point_b, point_c);
      break;
    }
}

int gpoly_mul_rot_1(int a1, int a2)
{
    int ret;
    asm volatile (
      "call ASM_gpoly_mul_rot_1\n"
        : "=r" (ret) : "a" (a1), "d" (a2));
    return ret;
}

int gpoly_mul_rot_2(int a1, int a2)
{
    int ret;
    asm volatile (
      "call ASM_gpoly_mul_rot_2\n"
        : "=r" (ret) : "a" (a1), "d" (a2));
    return ret;
}

void gpoly_sta_md03(struct gpoly_state *st)
{
    asm volatile (
      "call ASM_gpoly_sta_md03\n"
        : : "a" (st));
    return;
}

void gpoly_sta_md04(struct gpoly_state *st)
{
    asm volatile (
      "call ASM_gpoly_sta_md04\n"
        : : "a" (st));
    return;
}

void gpoly_sta_md05(struct gpoly_state *st)
{
#if 0
    asm volatile (
      "call ASM_gpoly_sta_md05\n"
        : : "a" (st));
    return;
#endif
    {
        int dist_c1, dist_c2, dist_c3, dist_c4;
        int fctr_a, fctr_d;

        dist_c1 = st->var_160 - st->var_178;
        dist_c2 = st->var_148 - st->var_178;
        dist_c3 = st->var_164 - st->var_17C;
        dist_c4 = st->var_14C - st->var_17C;
        fctr_a = dist_c1 * dist_c4;
        if (st->var_134 >= 0)
            fctr_a = fctr_a - dist_c4 - dist_c4;
        fctr_d = dist_c2 * dist_c3 - (dist_c4 + fctr_a);
        if (fctr_d != 0)
        {
            st->var_038 = st->var_14C - st->var_17C;
            st->var_03C = st->var_164 - st->var_17C;
            st->var_0A8 = gpoly_mul_rot_1(0x7FFFFFFF / fctr_d,
                            st->var_03C * (st->var_140 - st->var_170) - st->var_038 * (st->var_158 - st->var_170));
            st->var_0B0 = gpoly_mul_rot_1(0x7FFFFFFF / fctr_d,
                            st->var_03C * (st->var_13C - st->var_16C) - st->var_038 * (st->var_154 - st->var_16C));
            st->var_0AC = gpoly_mul_rot_1(0x7FFFFFFF / fctr_d,
                            st->var_03C * (st->var_138 - st->var_168) - st->var_038 * (st->var_150 - st->var_168));
        }
        else
        {
            st->var_0A8 = 0;
            st->var_0B0 = 0;
            st->var_0AC = 0;
        }
    }
    if (st->var_134 < 0)
    {
        int dist_c5, mag_a1;

        dist_c5 = st->var_14C - st->var_17C;
        if (dist_c5 > 255)
          mag_a1 = 0x7FFFFFFF / dist_c5;
        else
          mag_a1 = gpoly_reptable[dist_c5];
        st->var_1A4 = gpoly_mul_rot_2(mag_a1, 2 * (st->var_140 - st->var_170));
        st->var_194 = gpoly_mul_rot_2(mag_a1, 2 * (st->var_13C - st->var_16C));
        st->var_188 = gpoly_mul_rot_2(mag_a1, 2 * (st->var_138 - st->var_168));
    }
    else
    {
        int dist_c5, mag_a1;

        dist_c5 = st->var_164 - st->var_17C;
        if (dist_c5 > 255)
          mag_a1 = 0x7FFFFFFF / dist_c5;
        else
          mag_a1 = gpoly_reptable[dist_c5];
        st->var_1A4 = gpoly_mul_rot_2(mag_a1, 2 * (st->var_158 - st->var_170));
        st->var_194 = gpoly_mul_rot_2(mag_a1, 2 * (st->var_154 - st->var_16C));
        st->var_188 = gpoly_mul_rot_2(mag_a1, 2 * (st->var_150 - st->var_168));

        dist_c5 = st->var_14C - st->var_164;
        if (dist_c5 > 255)
          mag_a1 = 0x7FFFFFFF / dist_c5;
        else
          mag_a1 = gpoly_reptable[dist_c5];
        st->var_1A0 = gpoly_mul_rot_2(mag_a1, 2 * (st->var_140 - st->var_158));
        st->var_198 = gpoly_mul_rot_2(mag_a1, 2 * (st->var_13C - st->var_154));
        st->var_18C = gpoly_mul_rot_2(mag_a1, 2 * (st->var_138 - st->var_150));
    }
    st->var_058 = st->var_170 << 16;
    st->var_054 = st->var_16C << 16;
    st->var_050 = st->var_168 << 16;
    st->var_04C = st->var_158 << 16;
    st->var_048 = st->var_154 << 16;
    st->var_044 = st->var_150 << 16;

    {
        bool mone;
        int fctr_e, fctr_s;
        unsigned int fctr_f;

        fctr_e = st->var_0B0 >> 16;
        fctr_f = ((st->var_0B0 << 16) & 0xFFFF0000) | ((st->var_0A8 >> 8) & 0xFFFF);
        if ((fctr_f & 0x8000) != 0) {
            mone = fctr_f < 0xFFFF;
            fctr_f -= 0xFFFF;
            fctr_e = ((fctr_e) & 0xFFFFFF00) | ((fctr_e - mone) & 0xFF);
        }
        st->var_0BC = fctr_f;
        st->var_0B8 = fctr_e;

        fctr_e = st->var_0AC >> 16;
        fctr_f = ((st->var_0AC << 16) & 0xFFFFFF00) | (st->var_0B8 & 0xFF);
        if ((fctr_f & 0x80u) != 0) {
            mone = fctr_f < 0x100;
            fctr_f -= 0x100;
            fctr_e = ((fctr_e) & 0xFFFFFF00) | ((fctr_e - mone) & 0xFF);
        }
        st->var_0B8 = fctr_f;
        st->var_0B4 = fctr_e;

        fctr_e = st->var_194 >> 16;
        fctr_f = ((st->var_194 << 16) & 0xFFFF0000) | ((st->var_1A4 >> 8) & 0xFFFF);
        if ((fctr_f & 0x8000) != 0) {
            mone = fctr_f < 0x10000;
            fctr_f -= 0x10000;
            fctr_e = ((fctr_e) & 0xFFFFFF00) | ((fctr_e - mone) & 0xFF);
        }
        st->var_0A4 = fctr_f;
        st->var_0A0 = fctr_e;

        fctr_e = st->var_188 >> 16;
        fctr_f = ((st->var_188 << 16) & 0xFFFFFF00) | (st->var_0A0 & 0xFF);
        if ((fctr_f & 0x80) != 0) {
            mone = fctr_f < 0x100;
            fctr_f -= 0x100;
            fctr_e = ((fctr_e) & 0xFFFFFF00) | ((fctr_e - mone) & 0xFF);
        }
        st->var_0A0 = fctr_f;
        st->var_09C = fctr_e;

        st->var_084 = ((st->var_084) & 0xFFFFFF00) | (st->var_058 & 0xFF);
        st->var_08C = ((st->var_054 << 16) & 0xFFFF0000) | ((st->var_058 >> 8) & 0xFFFF);
        fctr_s = (unsigned int)(st->var_050 << 8) >> 24 << 8;
        st->var_088 = ((st->var_050 << 16) & 0xFFFFFF00) | ((st->var_054 >> 16) & 0xFF);
        st->var_084 = ((fctr_s) & 0xFFFFFF00) | (st->var_084 & 0xFF);
    }

    if (st->var_134 >= 0)
    {
        bool mone;
        int fctr_e, fctr_s;
        unsigned int fctr_f;

        fctr_e = st->var_198 >> 16;
        fctr_f = ((st->var_198 << 16) & 0xFFFF0000) | ((st->var_1A0 >> 8) & 0xFFFF);
        if ((fctr_f & 0x8000) != 0) {
          mone = fctr_f < 0x10000;
          fctr_f -= 0x10000;
          fctr_e = ((fctr_e) & 0xFFFFFF00) | ((fctr_e - mone) & 0xFF);
        }
        st->var_098 = fctr_f;
        st->var_094 = fctr_e;

        fctr_e = st->var_18C >> 16;
        fctr_f = ((st->var_18C << 16) & 0xFFFFFF00) | (st->var_094 & 0xFF);
        if ((fctr_f & 0x80) != 0) {
          mone = fctr_f < 0x100;
          fctr_f -= 0x100;
          fctr_e = ((fctr_e) & 0xFFFFFF00) | ((fctr_e - mone) & 0xFF);
        }
        st->var_094 = fctr_f;
        st->var_090 = fctr_e;

        st->var_078 = (st->var_078 & 0xFFFFFF00) | (st->var_04C & 0xFF);
        st->var_080 = ((st->var_048 << 16) & 0xFFFF0000) | ((st->var_04C >> 8) & 0xFFFF);
        fctr_s = (unsigned int)(st->var_044 << 8) >> 24 << 8;
        st->var_07C = ((st->var_044 << 16) & 0xFFFFFF00) | ((st->var_048 >> 16) & 0xFF);
        st->var_078 = (fctr_s & 0xFFFFFF00) | (st->var_078 & 0xFF);
    }
}

void gpoly_sta_md27(struct gpoly_state *st)
{
    asm volatile (
      "call ASM_gpoly_sta_md27\n"
        : : "a" (st));
    return;
}

void gpoly_sta_md28(struct gpoly_state *st)
{
    asm volatile (
      "call ASM_gpoly_sta_md28\n"
        : : "a" (st));
    return;
}

void gpoly_stb_md05uni(struct gpoly_state *st)
{
    asm volatile (
      "call ASM_gpoly_stb_md05uni\n"
        : : "a" (st));
    return;
}

void gpoly_stb_md05p64(struct gpoly_state *st)
{
    asm volatile (
      "call ASM_gpoly_stb_md05p64\n"
        : : "a" (st));
    return;
}

void draw_gpoly(struct PolyPoint *point_a, struct PolyPoint *point_b, struct PolyPoint *point_c)
{
#if 0
    asm volatile (
      "call ASM_draw_gpoly_\n"
        : : "a" (point_a), "d" (point_b), "b" (point_c));
    return;
#endif
    int dist_ca_x, dist_ca_y;
    struct gpoly_state st;

    gpoly_mode = vec_mode;
    st.var_040 = (point_c->X | point_b->X | point_a->X) < 0
             || point_a->X > vec_window_width
             || point_b->X > vec_window_width
             || point_c->X > vec_window_width;
    {
        int min_y;
        struct PolyPoint *tmp;

        min_y = point_a->Y;
        if (min_y > point_b->Y) {
            min_y = point_b->Y;
            tmp = point_a;
            point_a = point_b;
            point_b = tmp;
        }
        if (min_y > point_c->Y) {
            tmp = point_a;
            point_a = point_c;
            point_c = tmp;
        }
        if (point_b->Y > point_c->Y) {
            tmp = point_b;
            point_b = point_c;
            point_c = tmp;
        }
    }

    if (point_a->Y == point_c->Y) {
        return;
    }

    st.var_178 = point_a->X;
    st.var_17C = point_a->Y;
    st.var_174 = st.var_178 << 16;
    st.var_160 = point_b->X;
    st.var_164 = point_b->Y;
    st.var_15C = st.var_160 << 16;
    st.var_148 = point_c->X;
    st.var_14C = point_c->Y;
    st.var_144 = st.var_148 << 16;
    st.var_170 = (point_a->S >> 16);
    st.var_158 = (point_b->S >> 16);
    st.var_140 = (point_c->S >> 16);
    st.var_16C = (point_a->U >> 16);
    st.var_168 = (point_a->V >> 16);
    st.var_154 = (point_b->U >> 16);
    st.var_150 = (point_b->V >> 16);
    st.var_13C = (point_c->U >> 16);
    st.var_138 = (point_c->V >> 16);

    dist_ca_y = st.var_14C - st.var_17C;
    if (dist_ca_y != 0)
    {
        int dist_ba_x, dist_ba_y;
        int dist_cb_x, dist_cb_y;

        dist_ca_x = st.var_148 - st.var_178;
        if ((dist_ca_y & ~0x1Fu) != 0 || dist_ca_x < -32 || dist_ca_x > 31)
            st.var_1B0 = (dist_ca_x << 16) / dist_ca_y;
        else
            st.var_1B0 = gpoly_divtable[dist_ca_y][32 + dist_ca_x];

        dist_ba_y = st.var_164 - st.var_17C;
        if (dist_ba_y != 0)
        {
            dist_ba_x = st.var_160 - st.var_178;
            if ((dist_ba_y & ~0x1Fu) != 0 || dist_ba_x < -32 || dist_ba_x > 31)
                st.var_1AC = (dist_ba_x << 16) / dist_ba_y;
            else
                st.var_1AC = gpoly_divtable[dist_ba_y][32 + dist_ba_x];
        }

        dist_cb_y = st.var_14C - st.var_164;
        if (dist_cb_y != 0)
        {
            dist_cb_x = st.var_148 - st.var_160;
            if ((dist_cb_y & ~0x1Fu) != 0 || dist_cb_x < -32 || dist_cb_x > 31)
                st.var_1A8 = (dist_cb_x << 16) / dist_cb_y;
            else
                st.var_1A8 = gpoly_divtable[dist_cb_y][32 + dist_cb_x];
        }
    }
    st.var_134 = (st.var_164 - st.var_17C) * st.var_1B0 + st.var_174 - st.var_15C;

    switch (gpoly_mode)
    {
    case 2u:
    case 3u:
    case 0xCu:
    case 0xDu:
    case 0x12u:
    case 0x13u:
    case 0x16u:
    case 0x17u:
        gpoly_sta_md03(&st);
        break;
    case 4u:
    case 0x10u:
    case 0x11u:
        gpoly_sta_md04(&st);
        break;
    case 5u:
    case 6u:
    case 0x14u:
    case 0x15u:
    case 0x18u:
    case 0x19u:
        gpoly_sta_md05(&st);
        break;
    case 0x1Bu:
    case 0x1Du:
    case 0x1Fu:
    case 0x20u:
    case 0x21u:
    case 0x22u:
    case 0x25u:
    case 0x26u:
        gpoly_sta_md27(&st);
        break;
    case 0x1Cu:
    case 0x1Eu:
    case 0x23u:
    case 0x24u:
    case 0x27u:
    case 0x28u:
        gpoly_sta_md28(&st);
        break;
    }

    switch (gpoly_mode)
    {
    case 5:
        gpoly_stb_md05uni(&st);
        break;
    case 27:
        gpoly_stb_md05p64(&st);
        break;
    }
}

/******************************************************************************/
