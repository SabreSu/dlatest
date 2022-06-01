/*
* Copyright [2022] <USTC-CSS lab>
*/

#ifndef RUNTIME_DLA_DRIVER_H_
#define RUNTIME_DLA_DRIVER_H_

#include "./dla_register.h"

/*
* SXDLA registers reset value.
*/
#define RESET_CTRL          0x00000000
#define RESET_START         0x00000000
#define RESET_INTREN        0x00000000
#define RESET_INTR          0x00000000
#define RESET_CMDADDR       0x00000000
#define RESET_MAXCMD        0xFFFFFFFF
#define RESET_OFFSETADDR    0x00000000
#define RESET_MAXTIME       0xFFFFFFFF
#define RESET_COUNT0        0x00000000
#define RESET_COUNT1        0x00000000
#define RESET_COUNT2        0x00000000
#define RESET_COUNT3        0x00000000
#define RESET_COUNT4        0x00000000
#define RESET_COUNT5        0x00000000
#define RESET_SUMCOUNT      0x00000000
#define RESET_LAYERCOUNT    0x00000000
#define RESET_RUNCMD        0x00000000
#define RESET_VERSION       0x00000100

void RESET_REGISTER(enum SX_REGISTER reg) {
    switch (reg) {
        case CTRL:
            SXDLA_CTRL = RESET_CTRL;
            break;
        case START:
            SXDLA_START = RESET_START;
            break;
        case INTRE:
            SXDLA_INTREN = RESET_INTREN;
            break;
        case INTR:
            SXDLA_INTR = RESET_INTR;
            break;
        case CMDAD:
            SXDLA_CMDADDR = RESET_CMDADDR;
            break;
        case MAXCM:
            SXDLA_MAXCMD = RESET_MAXCMD;
            break;
        case OFFSE:
            SXDLA_OFFSETADDR = RESET_OFFSETADDR;
            break;
        case MAXTI:
            SXDLA_MAXTIME = RESET_MAXTIME;
            break;
        case COUNT0:
            SXDLA_COUNT0 = RESET_COUNT0;
            break;
        case COUNT1:
            SXDLA_COUNT1 = RESET_COUNT1;
            break;
        case COUNT2:
            SXDLA_COUNT2 = RESET_COUNT2;
            break;
        case COUNT3:
            SXDLA_COUNT3 = RESET_COUNT3;
            break;
        case COUNT4:
            SXDLA_COUNT4 = RESET_COUNT4;
            break;
        case COUNT5:
            SXDLA_COUNT5 = RESET_COUNT5;
            break;
        case SUMCO:
            SXDLA_SUMCOUNT = RESET_SUMCOUNT;
            break;
        case LAYER:
            SXDLA_LAYERCOUNT = RESET_LAYERCOUNT;
            break;
        case RUNCM:
            SXDLA_RUNCMD = RESET_RUNCMD;
            break;
        case VERSI:
            SXDLA_VERSION = RESET_VERSION;
            break;
    }
}

/*
* Set the value of each register.
*/
inline void SET_CTRL_ENABLE() { SXDLA_CTRL |= (1 << 0);}

inline void SET_CTRL_SWRST() { SXDLA_CTRL |= (1 << 1);}

inline void SET_START() { SXDLA_START |= (1 << 0);}

inline void SET_INTREN_DONEEN() { SXDLA_INTREN |= (1 << 0);}
inline void SET_INTREN_TOEN() { SXDLA_INTREN |= (1 << 1);}
inline void SET_INTREN_CMDOVREN() { SXDLA_INTREN |= (1 << 2);}
inline void SET_INTREN_CMDERREN() { SXDLA_INTREN |= (1 << 3);}

inline void SET_INTR_DONE() { SXDLA_INTR |= (1 << 0);}
inline void SET_INTR_TO() { SXDLA_INTR |= (1 << 1);}
inline void SET_INTR_CMDOVR() { SXDLA_INTR |= (1 << 2);}
inline void SET_INTR_CMDERR() { SXDLA_INTR |= (1 << 3);}

inline void SET_CMDADDR(void* addr) { SXDLA_CMDADDR = (unsigned int)addr;}

inline void SET_MAXCMD(unsigned int num) {SXDLA_MAXCMD = num;}

inline void SET_OFFSETADDR(void* addr) { SXDLA_OFFSETADDR = (unsigned int)addr;}

inline void SET_MAXTIME(unsigned int cycles) { SXDLA_MAXTIME = cycles;}

inline void SET_COUNT0(unsigned int qwords) { SXDLA_COUNT0 = qwords;}

inline void SET_COUNT1(unsigned int qwords) { SXDLA_COUNT1 = qwords;}

inline void SET_COUNT2(unsigned int qwords) { SXDLA_COUNT2 = qwords;}

inline void SET_COUNT3(unsigned int qwords) { SXDLA_COUNT3 = qwords;}

inline void SET_COUNT4(unsigned int qwords) { SXDLA_COUNT4 = qwords;}

inline void SET_COUNT5(unsigned int qwords) { SXDLA_COUNT5 = qwords;}

inline void SET_SUMCOUNT(unsigned int qwords) { SXDLA_SUMCOUNT = qwords;}

inline void SET_LAYERCOUNT(unsigned int channels) { SXDLA_LAYERCOUNT = channels;}

/*
* Get the value of each register.
*/

#define GET_BIT(REG, bit) ((REG & (1 << bit)) >> bit)

inline unsigned int GET_CTRL_ENABLE() { return GET_BIT(SXDLA_CTRL, 0);}
inline unsigned int GET_CTRL_SWRST() { return GET_BIT(SXDLA_CTRL, 1);}
inline unsigned int GET_CTRL_BUSY() { return GET_BIT(SXDLA_CTRL, 7);}

inline unsigned int GET_START() { return GET_BIT(SXDLA_START, 0);}

inline unsigned int GET_INTREN_DONEEN() { return GET_BIT(SXDLA_INTREN, 0);}
inline unsigned int GET_INTREN_TOEN() { return GET_BIT(SXDLA_INTREN, 1);}
inline unsigned int GET_INTREN_CMDOVREN() { return GET_BIT(SXDLA_INTREN, 2);}
inline unsigned int GET_INTREN_CMDERREN() { return GET_BIT(SXDLA_INTREN, 3);}

inline unsigned int GET_INTR_DONE() { return GET_BIT(SXDLA_INTR, 0);}
inline unsigned int GET_INTR_TO() { return GET_BIT(SXDLA_INTR, 1);}
inline unsigned int GET_INTR_CMDOVR() { return GET_BIT(SXDLA_INTR, 2);}
inline unsigned int GET_INTR_CMDERR() { return GET_BIT(SXDLA_INTR, 3);}

inline void* GET_CMDADDR() { return (void*)SXDLA_CMDADDR;}

inline unsigned int GET_MAXCMD() { return SXDLA_MAXCMD;}

inline void* GET_OFFSETADDR() { return (void*)SXDLA_OFFSETADDR;}

inline unsigned int GET_MAXTIME() { return SXDLA_MAXTIME;}

inline unsigned int GET_COUNT0() { return SXDLA_COUNT0;}

inline unsigned int GET_COUNT1() { return SXDLA_COUNT1;}

inline unsigned int GET_COUNT2() { return SXDLA_COUNT2;}

inline unsigned int GET_COUNT3() { return SXDLA_COUNT3;}

inline unsigned int GET_COUNT4() { return SXDLA_COUNT4;}

inline unsigned int GET_COUNT5() { return SXDLA_COUNT5;}

inline unsigned int GET_SUMCOUNT() {return SXDLA_SUMCOUNT;}

inline unsigned int GET_LAYERCOUNT() { return SXDLA_LAYERCOUNT;}

inline unsigned int GET_RUNCMD() { return SXDLA_RUNCMD;}

inline unsigned int GET_VERSION() { return SXDLA_VERSION;}

#endif  // RUNTIME_DLA_DRIVER_H_
