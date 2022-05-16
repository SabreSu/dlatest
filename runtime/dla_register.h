/*
* Copyright [2022] <USTC-CSS lab>
*/

#ifndef RUNTIME_DLA_REGISTER_H_
#define RUNTIME_DLA_REGISTER_H_

/*
* SXDLA register address
*/
#define SXDLA_CTRL                  *((volatile unsigned int *)0X00)
#define SXDLA_START                 *((volatile unsigned int *)0X04)
#define SXDLA_INTREN                *((volatile unsigned int *)0X08)
#define SXDLA_INTR                  *((volatile unsigned int *)0X0c)
#define SXDLA_CMDADDR               *((volatile unsigned int *)0X10)
#define SXDLA_MAXCMD                *((volatile unsigned int *)0X14)
#define SXDLA_OFFSETADDR            *((volatile unsigned int *)0X18)
#define SXDLA_MAXTIME               *((volatile unsigned int *)0X1c)
#define SXDLA_COUNT0                *((volatile unsigned int *)0X20)
#define SXDLA_COUNT1                *((volatile unsigned int *)0X24)
#define SXDLA_COUNT2                *((volatile unsigned int *)0X28)
#define SXDLA_COUNT3                *((volatile unsigned int *)0X2c)
#define SXDLA_COUNT4                *((volatile unsigned int *)0X30)
#define SXDLA_COUNT5                *((volatile unsigned int *)0X34)
#define SXDLA_SUMCOUNT              *((volatile unsigned int *)0X38)
#define SXDLA_LAYERCOUNT            *((volatile unsigned int *)0X3c)
#define SXDLA_RUNCMD                *((volatile unsigned int *)0X40)
#define SXDLA_VERSION               *((volatile unsigned int *)0X44)

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

