/*
* Copyright [2022] <USTC-CSS lab>
*/

#ifndef RUNTIME_DLA_REGISTER_H_
#define RUNTIME_DLA_REGISTER_H_

/*
* SXDLA register address
*/
#define SXDLA_CTRL                  *((volatile unsigned int *)0x41006000)
#define SXDLA_START                 *((volatile unsigned int *)0x41006004)
#define SXDLA_INTREN                *((volatile unsigned int *)0x41006008)
#define SXDLA_INTR                  *((volatile unsigned int *)0x4100600c)
#define SXDLA_CMDADDR               *((volatile unsigned int *)0x41006010)
#define SXDLA_MAXCMD                *((volatile unsigned int *)0x41006014)
#define SXDLA_OFFSETADDR            *((volatile unsigned int *)0x41006018)
#define SXDLA_MAXTIME               *((volatile unsigned int *)0x4100601c)
#define SXDLA_COUNT0                *((volatile unsigned int *)0x41006020)
#define SXDLA_COUNT1                *((volatile unsigned int *)0x41006024)
#define SXDLA_COUNT2                *((volatile unsigned int *)0x41006028)
#define SXDLA_COUNT3                *((volatile unsigned int *)0x4100602c)
#define SXDLA_COUNT4                *((volatile unsigned int *)0x41006030)
#define SXDLA_COUNT5                *((volatile unsigned int *)0x41006034)
#define SXDLA_SUMCOUNT              *((volatile unsigned int *)0x41006038)
#define SXDLA_LAYERCOUNT            *((volatile unsigned int *)0x4100603c)
#define SXDLA_RUNCMD                *((volatile unsigned int *)0x41006040)
#define SXDLA_VERSION               *((volatile unsigned int *)0x41006044)

enum SX_REGISTER {
    CTRL = 0,
    START,
    INTRE,
    INTR ,
    CMDAD,
    MAXCM,
    OFFSE,
    MAXTI,
    COUNT0,
    COUNT1,
    COUNT2,
    COUNT3,
    COUNT4,
    COUNT5,
    SUMCO,
    LAYER,
    RUNCM,
    VERSI,
};

#endif  // RUNTIME_DLA_REGISTER_H_

