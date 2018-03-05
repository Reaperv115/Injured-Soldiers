#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer theMatrices
// {
//
//   row_major float4x4 worldMat;       // Offset:    0 Size:    64
//   row_major float4x4 perspectiveMat; // Offset:   64 Size:    64
//   row_major float4x4 viewMat;        // Offset:  128 Size:    64
//   row_major float4x4 projection;     // Offset:  192 Size:    64 [unused]
//   row_major float4x4 cam;            // Offset:  256 Size:    64 [unused]
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// theMatrices                       cbuffer      NA          NA            cb2      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// POSITION                 0   xyzw        0     NONE   float   xyzw
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_POSITION              0   xyzw        0      POS   float   xyzw
// RGBVal                   0   xyzw        1     NONE   float   xyzw
// theNORMAL                0   xyz         2     NONE   float   xyz 
// dir                      0   xyz         3     NONE   float   xyz 
// POSITION                 0   xyz         4     NONE   float   xyz 
//
vs_4_0
dcl_constantbuffer CB2[12], immediateIndexed
dcl_input v0.xyzw
dcl_output_siv o0.xyzw, position
dcl_output o1.xyzw
dcl_output o2.xyz
dcl_output o3.xyz
dcl_output o4.xyz
dcl_temps 2
mul r0.xyzw, v0.yyyy, cb2[1].xyzw
mad r0.xyzw, v0.xxxx, cb2[0].xyzw, r0.xyzw
mad r0.xyzw, v0.zzzz, cb2[2].xyzw, r0.xyzw
mad r0.xyzw, v0.wwww, cb2[3].xyzw, r0.xyzw
mul r1.xyzw, r0.yyyy, cb2[9].xyzw
mad r1.xyzw, r0.xxxx, cb2[8].xyzw, r1.xyzw
mad r1.xyzw, r0.zzzz, cb2[10].xyzw, r1.xyzw
mad r0.xyzw, r0.wwww, cb2[11].xyzw, r1.xyzw
mul r1.xyzw, r0.yyyy, cb2[5].xyzw
mad r1.xyzw, r0.xxxx, cb2[4].xyzw, r1.xyzw
mad r1.xyzw, r0.zzzz, cb2[6].xyzw, r1.xyzw
mad o0.xyzw, r0.wwww, cb2[7].xyzw, r1.xyzw
mov o1.xyzw, l(0,0,0,0)
mov o2.xyz, l(0,0,0,0)
mov o3.xyz, l(0,0,0,0)
mov o4.xyz, v0.xyzx
ret 
// Approximately 17 instruction slots used
#endif

const BYTE Trivial_VS[] =
{
     68,  88,  66,  67, 107, 133, 
    175,   4,  14, 174,  11, 191, 
    153, 148,  98, 153, 190, 142, 
    192, 152,   1,   0,   0,   0, 
    152,   5,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    128,   1,   0,   0, 180,   1, 
      0,   0, 104,   2,   0,   0, 
     28,   5,   0,   0,  82,  68, 
     69,  70,  68,   1,   0,   0, 
      1,   0,   0,   0,  72,   0, 
      0,   0,   1,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    254, 255,   0,   1,   0,   0, 
     26,   1,   0,   0,  60,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    116, 104, 101,  77,  97, 116, 
    114, 105,  99, 101, 115,   0, 
     60,   0,   0,   0,   5,   0, 
      0,   0,  96,   0,   0,   0, 
     64,   1,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    216,   0,   0,   0,   0,   0, 
      0,   0,  64,   0,   0,   0, 
      2,   0,   0,   0, 228,   0, 
      0,   0,   0,   0,   0,   0, 
    244,   0,   0,   0,  64,   0, 
      0,   0,  64,   0,   0,   0, 
      2,   0,   0,   0, 228,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   1,   0,   0, 128,   0, 
      0,   0,  64,   0,   0,   0, 
      2,   0,   0,   0, 228,   0, 
      0,   0,   0,   0,   0,   0, 
     11,   1,   0,   0, 192,   0, 
      0,   0,  64,   0,   0,   0, 
      0,   0,   0,   0, 228,   0, 
      0,   0,   0,   0,   0,   0, 
     22,   1,   0,   0,   0,   1, 
      0,   0,  64,   0,   0,   0, 
      0,   0,   0,   0, 228,   0, 
      0,   0,   0,   0,   0,   0, 
    119, 111, 114, 108, 100,  77, 
     97, 116,   0, 171, 171, 171, 
      2,   0,   3,   0,   4,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 112, 101, 
    114, 115, 112, 101,  99, 116, 
    105, 118, 101,  77,  97, 116, 
      0, 118, 105, 101, 119,  77, 
     97, 116,   0, 112, 114, 111, 
    106, 101,  99, 116, 105, 111, 
    110,   0,  99,  97, 109,   0, 
     77, 105,  99, 114, 111, 115, 
    111, 102, 116,  32,  40,  82, 
     41,  32,  72,  76,  83,  76, 
     32,  83, 104,  97, 100, 101, 
    114,  32,  67, 111, 109, 112, 
    105, 108, 101, 114,  32,  49, 
     48,  46,  49,   0, 171, 171, 
     73,  83,  71,  78,  44,   0, 
      0,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,  15,   0,   0,  80,  79, 
     83,  73,  84,  73,  79,  78, 
      0, 171, 171, 171,  79,  83, 
     71,  78, 172,   0,   0,   0, 
      5,   0,   0,   0,   8,   0, 
      0,   0, 128,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0, 140,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  15,   0, 
      0,   0, 147,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   7,   8, 
      0,   0, 157,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,   7,   8, 
      0,   0, 161,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0,   7,   8, 
      0,   0,  83,  86,  95,  80, 
     79,  83,  73,  84,  73,  79, 
     78,   0,  82,  71,  66,  86, 
     97, 108,   0, 116, 104, 101, 
     78,  79,  82,  77,  65,  76, 
      0, 100, 105, 114,   0,  80, 
     79,  83,  73,  84,  73,  79, 
     78,   0, 171, 171,  83,  72, 
     68,  82, 172,   2,   0,   0, 
     64,   0,   1,   0, 171,   0, 
      0,   0,  89,   0,   0,   4, 
     70, 142,  32,   0,   2,   0, 
      0,   0,  12,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   0,   0,   0,   0, 
    103,   0,   0,   4, 242,  32, 
     16,   0,   0,   0,   0,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 114,  32,  16,   0, 
      2,   0,   0,   0, 101,   0, 
      0,   3, 114,  32,  16,   0, 
      3,   0,   0,   0, 101,   0, 
      0,   3, 114,  32,  16,   0, 
      4,   0,   0,   0, 104,   0, 
      0,   2,   2,   0,   0,   0, 
     56,   0,   0,   8, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     86,  21,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      2,   0,   0,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   0,   0, 
      0,   0,   6,  16,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   0,   0,   0,   0, 
    166,  26,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      2,   0,   0,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      0,   0,   0,   0, 246,  31, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   2,   0, 
      0,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   8, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  86,   5,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   2,   0,   0,   0, 
      9,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   2,   0, 
      0,   0,   8,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0, 166,  10,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   2,   0,   0,   0, 
     10,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   0,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      2,   0,   0,   0,  11,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   8, 242,   0,  16,   0, 
      1,   0,   0,   0,  86,   5, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   1,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      2,   0,   0,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0, 166,  10, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   2,   0, 
      0,   0,   6,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,  32,  16,   0,   0,   0, 
      0,   0, 246,  15,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   2,   0,   0,   0, 
      7,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     54,   0,   0,   8, 242,  32, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  54,   0,   0,   8, 
    114,  32,  16,   0,   2,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   8, 114,  32,  16,   0, 
      3,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     54,   0,   0,   5, 114,  32, 
     16,   0,   4,   0,   0,   0, 
     70,  18,  16,   0,   0,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 116,   0, 
      0,   0,  17,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   6,   0,   0,   0, 
     12,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0
};
