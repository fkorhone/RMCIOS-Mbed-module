/* Copyright (c) 2018 Frans Korhonen, MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// These register descriptions have been extracted from lpc17xx datasheet.

#ifndef lpc17xx_regnames_h
#define lpc17xx_regnames_h

struct lpc17xx_register_names { const char *name; uint32_t *reg; const char *description;} ;
const struct lpc17xx_register_names regnames[]= {
//system control registers
//External InterruptsExternal Interrupts
{"EXTINT",(uint32_t *)0x400FC140UL,"External Interrupt Flag Register"},//0x400F C140
{"EXTMODE",(uint32_t *)0x400FC148UL,"External Interrupt Mode register"},//0x400F C148
{"EXTPOLAR",(uint32_t *)0x400FC14CUL,"External Interrupt Polarity Register"},//0x400F C14C
//Reset",(uint32_t *)UL,""},//
{"RSID",(uint32_t *)0x400FC180UL,"Reset Source Identification Register"},//0x400F C180
{"SCS",(uint32_t *)0x400FC1A0UL,"System Control and Status"},//0x400F C1A0
{"CLKSRCSEL",(uint32_t *)0x400FC10CUL,"Clock Source Select Register"},//0x400F C10C
//Phase Locked Loop (PLL0, Main PLL){"",(uint32_t *)UL,""},//
{"PLL0CON",(uint32_t *)0x400FC080UL,"PLL0 Control Register"},//0x400F C080
{"PLL0CFG",(uint32_t *)0x400FC084UL,"PLL0 Configuration Register"},//0x400F C084
{"PLL0STAT",(uint32_t *)0x400FC088UL,"PLL0 Status Register"},//0x400F C088
{"PLL0FEED",(uint32_t *)0x400FC08CUL,"PLL0 Feed Register"},//0x400F C08C
//Phase Locked Loop (PLL1, USB PLL){"",(uint32_t *)UL,""},//
{"PLL1CON",(uint32_t *)0x400FC0A0UL,"PLL1 Control Register"},//0x400F C0A0
{"PLL1CFG",(uint32_t *)0x400FC0A4UL,"PLL1 Configuration Register"},//0x400F C0A4
{"PLL1STAT",(uint32_t *)0x400FC0A8UL,"PLL1 Status Register"},//0x400F C0A8
{"PLL1FEED",(uint32_t *)0x400FC0ACUL,"PLL1 Feed Register"},//0x400F C0AC
//Clock dividers{"",(uint32_t *)UL,""},//
{"CCLKCFG",(uint32_t *)0x400FC104UL,"CPU Clock Configuration Register"},//0x400F C104
{"USBCLKCFG",(uint32_t *)0x400FC108UL,"USB Clock Configuration Register"},//0x400F C108
{"PCLKSEL0",(uint32_t *)0x400FC1A8UL,"Peripheral Clock Selection register 0."},//0x400F C1A8
{"PCLKSEL1",(uint32_t *)0x400FC1ACUL,"Peripheral Clock Selection register 1."},//0x400F C1AC
//Power control{"",(uint32_t *)UL,""},//
{"PCON",(uint32_t *)0x400FC0C0UL,"Power Control Register"},//0x400F C0C0
{"PCONP",(uint32_t *)0x400FC0C4UL,"Power Control for Peripherals Register"},//0x400F C0C4
//Utility{"",(uint32_t *)UL,""},//
{"CLKOUTCFG",(uint32_t *)0x400FC1C8UL,"Clock Output Configuration Register"},//0x400F C1C8
//PLL0 registers{"",(uint32_t *)UL,""},//
{"PLL0CON",(uint32_t *)0x400FC080UL,"PLL0 Control Register. "},//0x400F C080
{"PLL0CFG",(uint32_t *)0x400FC084UL,"PLL0 Configuration Register."},//0x400F C084
{"PLL0STAT",(uint32_t *)0x400FC088UL,"PLL0 Status Register"},//0x400F C088
{"PLL0FEED",(uint32_t *)0x400FC08CUL,"PLL0 Feed Register."},//0x400F C08C
//PLL1 registers{"",(uint32_t *)UL,""},//
{"PLL1CON",(uint32_t *)0x400FC0A0UL,"PLL1 Control Register"},//0x400F C0A0
//Power Control registers{"",(uint32_t *)UL,""},//
{"PCON",(uint32_t *)0x400FC0C0UL,"Power Control Register. "},//0x400F C0C0
{"PCONP",(uint32_t *)0x400FC0C4UL," Power Control for Peripherals Register."},//0x400F C0C4
//flash accelerator registers{"",(uint32_t *)UL,""},//
{"FLASHCFG",(uint32_t *)0x400FC000UL,"Flash Accelerator Configuration Register."},//0x400F C000
//NVIC register map{"",(uint32_t *)UL,""},//
{"ISER0",(uint32_t *)0xE000E100UL,"Interrupt Set-Enable Register."},//0xE000 E100
{"ISER1",(uint32_t *)0xE000E104UL,"Interrupt Set-Enable Register."},//0xE000 E104
{"ICER0",(uint32_t *)0xE000E180UL,"Interrupt Clear-Enable Register."},//0xE000 E180
{"ICER1",(uint32_t *)0xE000E184UL,"Interrupt Clear-Enable Register."},//0xE000 E184
{"ISPR0",(uint32_t *)0xE000E200UL,"Interrupt Set-Pending Register."},//0xE000 E200
{"ISPR1",(uint32_t *)0xE000E204UL,"Interrupt Set-Pending Register."},//0xE000 E204
{"ICPR0",(uint32_t *)0xE000E280UL,"Interrupt Clear-Pending Register."},//0xE000 E280
{"ICPR1",(uint32_t *)0xE000E284UL,"Interrupt Clear-Pending Register."},//0xE000 E284
{"IABR0",(uint32_t *)0xE000E300UL,"Interrupt Active Bit Register."},//0xE000 E300
{"IABR1",(uint32_t *)0xE000E304UL,"Interrupt Active Bit Register."},//0xE000 E304
{"IPR0",(uint32_t *)0xE000E400UL,"Interrupt Priority Register."},//0xE000 E400
{"IPR1",(uint32_t *)0xE000E404UL,"Interrupt Priority Register."},//0xE000 E404
{"IPR2",(uint32_t *)0xE000E408UL,"Interrupt Priority Register."},//0xE000 E408
{"IPR3",(uint32_t *)0xE000E40CUL,"Interrupt Priority Register."},//0xE000 E40C
{"IPR4",(uint32_t *)0xE000E410UL,"Interrupt Priority Register."},//0xE000 E410
{"IPR5",(uint32_t *)0xE000E414UL,"Interrupt Priority Register."},//0xE000 E414
{"IPR6",(uint32_t *)0xE000E418UL,"Interrupt Priority Register."},//0xE000 E418
{"IPR7",(uint32_t *)0xE000E41CUL,"Interrupt Priority Register."},//0xE000 E41C
{"IPR8",(uint32_t *)0xE000E420UL,"Interrupt Priority Register."},//0xE000 E420
{"STIR",(uint32_t *)0xE000EF00UL,"Software Trigger Interrupt Register. "},//0xE000 EF00
//PINSEL registers{"",(uint32_t *)UL,""},//
{"PINSEL0",(uint32_t *)0x4002C000UL," Pin function select register 0."},//0x4002 C000
{"PINSEL1",(uint32_t *)0x4002C004UL," Pin function select register 1."},//0x4002 C004
{"PINSEL2",(uint32_t *)0x4002C008UL," Pin function select register 2."},//0x4002 C008
{"PINSEL3",(uint32_t *)0x4002C00CUL," Pin function select register 3."},//0x4002 C00C
{"PINSEL4",(uint32_t *)0x4002C010UL," Pin function select register 4"},//0x4002 C010
{"PINSEL7",(uint32_t *)0x4002C01CUL," Pin function select register 7"},//0x4002 C01C
{"PINSEL8",(uint32_t *)0x4002C020UL," Pin function select register 8"},//0x4002 C020
{"PINSEL9",(uint32_t *)0x4002C024UL," Pin function select register 9"},//0x4002 C024
{"PINSEL10",(uint32_t *)0x4002C028UL," Pin function select register 10"},//0x4002 C028
{"PINMODE0",(uint32_t *)0x4002C040UL," Pin mode select register 0"},//0x4002 C040
{"PINMODE1",(uint32_t *)0x4002C044UL," Pin mode select register 1"},//0x4002 C044
{"PINMODE2",(uint32_t *)0x4002C048UL," Pin mode select register 2"},//0x4002 C048
{"PINMODE3",(uint32_t *)0x4002C04CUL," Pin mode select register 3."},//0x4002 C04C
{"PINMODE4",(uint32_t *)0x4002C050UL," Pin mode select register 4"},//0x4002 C050
{"PINMODE5",(uint32_t *)0x4002C054UL," Pin mode select register 5"},//0x4002 C054
{"PINMODE6",(uint32_t *)0x4002C058UL," Pin mode select register 6"},//0x4002 C058
{"PINMODE7",(uint32_t *)0x4002C05CUL," Pin mode select register 7"},//0x4002 C05C
{"PINMODE9",(uint32_t *)0x4002C064UL," Pin mode select register 9"},//0x4002 C064
{"PINMODE_OD0",(uint32_t *)0x4002C068UL," Open drain mode control register 0"},//0x4002 C068
{"PINMODE_OD1",(uint32_t *)0x4002C06CUL," Open drain mode control register 1"},//0x4002 C06C
{"PINMODE_OD2",(uint32_t *)0x4002C070UL," Open drain mode control register 2"},//0x4002 C070
{"PINMODE_OD3",(uint32_t *)0x4002C074UL," Open drain mode control register 3"},//0x4002 C074
{"PINMODE_OD4",(uint32_t *)0x4002C078UL," Open drain mode control register 4"},//0x4002 C078
{"I2CPADCFG",(uint32_t *)0x4002C07CUL," I2C Pin Configuration register"},//0x4002 C07C
//GPIO registers{"",(uint32_t *)UL,""},//
{"FIO0DIR ",(uint32_t *)0x2009C000UL,"Fast GPIO Port Direction control register."},// 0x2009 C000
{"FIO1DIR ",(uint32_t *)0x2009C020UL,"Fast GPIO Port Direction control register."},// 0x2009 C020
{"FIO2DIR ",(uint32_t *)0x2009C040UL,"Fast GPIO Port Direction control register."},// 0x2009 C040
{"FIO3DIR ",(uint32_t *)0x2009C060UL,"Fast GPIO Port Direction control register."},// 0x2009 C060
{"FIO4DIR ",(uint32_t *)0x2009C080UL,"Fast GPIO Port Direction control register."},// 0x2009 C080
{"FIO0MASK ",(uint32_t *)0x2009C010UL,"Fast Mask register for port"},// 0x2009 C010
{"FIO1MASK ",(uint32_t *)0x2009C030UL,"Fast Mask register for port"},// 0x2009 C030
{"FIO2MASK ",(uint32_t *)0x2009C050UL,"Fast Mask register for port"},// 0x2009 C050
{"FIO3MASK ",(uint32_t *)0x2009C070UL,"Fast Mask register for port"},// 0x2009 C070
{"FIO4MASK ",(uint32_t *)0x2009C090UL,"Fast Mask register for port"},// 0x2009 C090
{"FIO0PIN ",(uint32_t *)0x2009C014UL,"Fast Port Pin value register using FIOMASK."},// 0x2009 C014
{"FIO1PIN ",(uint32_t *)0x2009C034UL,"Fast Port Pin value register using FIOMASK."},// 0x2009 C034
{"FIO2PIN ",(uint32_t *)0x2009C054UL,"Fast Port Pin value register using FIOMASK."},// 0x2009 C054
{"FIO3PIN ",(uint32_t *)0x2009C074UL,"Fast Port Pin value register using FIOMASK."},// 0x2009 C074
{"FIO4PIN ",(uint32_t *)0x2009C094UL,"Fast Port Pin value register using FIOMASK."},// 0x2009 C094
{"FIO0SET ",(uint32_t *)0x2009C018UL,"Fast Port Output Set register using FIOMASK."},// 0x2009 C018
{"FIO1SET ",(uint32_t *)0x2009C038UL,"Fast Port Output Set register using FIOMASK."},// 0x2009 C038
{"FIO2SET ",(uint32_t *)0x2009C058UL,"Fast Port Output Set register using FIOMASK."},// 0x2009 C058
{"FIO3SET ",(uint32_t *)0x2009C078UL,"Fast Port Output Set register using FIOMASK."},// 0x2009 C078
{"FIO4SET ",(uint32_t *)0x2009C098UL,"Fast Port Output Set register using FIOMASK."},// 0x2009 C098
{"FIO0CLR ",(uint32_t *)0x2009C01CUL,"Fast Port Output Clear register using FIOMASK."},// 0x2009 C01C
{"FIO1CLR ",(uint32_t *)0x2009C03CUL,"Fast Port Output Clear register using FIOMASK."},// 0x2009 C03C
{"FIO2CLR ",(uint32_t *)0x2009C05CUL,"Fast Port Output Clear register using FIOMASK."},// 0x2009 C05C
{"FIO3CLR ",(uint32_t *)0x2009C07CUL,"Fast Port Output Clear register using FIOMASK."},// 0x2009 C07C
{"FIO4CLR ",(uint32_t *)0x2009C09CUL,"Fast Port Output Clear register using FIOMASK."},// 0x2009 C09C
//GPIO interrupt registers{"",(uint32_t *)UL,""},//
{"IO0IntEnR ",(uint32_t *)0x40028090UL,"IntEnR GPIO Interrupt Enable for Rising edge."},// 0x4002 8090
{"IO2IntEnR ",(uint32_t *)0x400280B0UL,"IntEnR GPIO Interrupt Enable for Rising edge."},// 0x4002 80B0
{"IO0IntEnR ",(uint32_t *)0x40028094UL,"IntEnF GPIO Interrupt Enable for Falling edge."},// 0x4002 8094
{"IO2IntEnR ",(uint32_t *)0x400280B4UL,"IntEnF GPIO Interrupt Enable for Falling edge."},// 0x4002 80B4
{"IO0IntStatR ",(uint32_t *)0x40028084UL,"IntStatR GPIO Interrupt Status for Rising edge."},// 0x4002 8084
{"IO2IntStatR ",(uint32_t *)0x400280A4UL,"IntStatR GPIO Interrupt Status for Rising edge."},// 0x4002 80A4
{"IO0IntStatF ",(uint32_t *)0x40028088UL,"IntStatF GPIO Interrupt Status for Falling edge."},// 0x4002 8088
{"IO2IntStatF ",(uint32_t *)0x400280A8UL,"IntStatF GPIO Interrupt Status for Falling edge."},// 0x4002 80A8
{"IO0IntClr ",(uint32_t *)0x4002808CUL,"IntClr GPIO Interrupt Clear."},// 0x4002 808C
{"IO2IntClr ",(uint32_t *)0x400280ACUL,"IntClr GPIO Interrupt Clear."},// 0x4002 80AC
{"IOIntStatus ",(uint32_t *)0x40028080UL,"IntStatus GPIO overall Interrupt Status."},// 0x4002 8080
//Fast GPIO port Direction control byte and half-word accessible registers{"",(uint32_t *)UL,""},//
{"FIO0DIR0",(uint32_t *)0x2009C000UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C000
{"FIO1DIR0",(uint32_t *)0x2009C020UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C020
{"FIO2DIR0",(uint32_t *)0x2009C040UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C040
{"FIO3DIR0",(uint32_t *)0x2009C060UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C060
{"FIO4DIR0",(uint32_t *)0x2009C080UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C080
{"FIO0DIR1",(uint32_t *)0x2009C001UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C001
{"FIO1DIR1",(uint32_t *)0x2009C021UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C021
{"FIO2DIR1",(uint32_t *)0x2009C041UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C041
{"FIO3DIR1",(uint32_t *)0x2009C061UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C061
{"FIO4DIR1",(uint32_t *)0x2009C081UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C081
{"FIO0DIR2",(uint32_t *)0x2009C002UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C002
{"FIO1DIR2",(uint32_t *)0x2009C022UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C022
{"FIO2DIR2",(uint32_t *)0x2009C042UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C042
{"FIO3DIR2",(uint32_t *)0x2009C062UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C062
{"FIO4DIR2",(uint32_t *)0x2009C082UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C082
{"FIO0DIR3",(uint32_t *)0x2009C003UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C003
{"FIO1DIR3",(uint32_t *)0x2009C023UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C023
{"FIO2DIR3",(uint32_t *)0x2009C043UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C043
{"FIO3DIR3",(uint32_t *)0x2009C063UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C063
{"FIO4DIR3",(uint32_t *)0x2009C083UL,"Fast GPIO Port x Direction 8 (byte)"},// 0x2009 C083
{"FIO0DIRL ",(uint32_t *)0x2009C000UL,"Fast GPIO Port x Direction 16 "},// 0x2009 C000
{"FIO1DIRL ",(uint32_t *)0x2009C020UL,"Fast GPIO Port x Direction 16 "},// 0x2009 C020
{"FIO2DIRL ",(uint32_t *)0x2009C040UL,"Fast GPIO Port x Direction 16 "},// 0x2009 C040
{"FIO3DIRL ",(uint32_t *)0x2009C060UL,"Fast GPIO Port x Direction 16 "},// 0x2009 C060
{"FIO4DIRL ",(uint32_t *)0x2009C080UL,"Fast GPIO Port x Direction 16 "},// 0x2009 C080
{"FIO0DIRU ",(uint32_t *)0x2009C002UL,"Fast GPIO Port x Direction 16 "},// 0x2009 C002
{"FIO1DIRU ",(uint32_t *)0x2009C022UL,"Fast GPIO Port x Direction 16 "},// 0x2009 C022
{"FIO2DIRU",(uint32_t *)0x2009C042UL,"Fast GPIO Port x Direction 16 "},// 0x2009 C042
{"FIO2DIRU ",(uint32_t *)0x2009C062UL,"Fast GPIO Port x Direction 16 "},// 0x2009 C062
{"FIO3DIRU ",(uint32_t *)0x2009C082UL,"Fast GPIO Port x Direction 16 "},// 0x2009 C082
//Fast GPIO port output Set byte and half word accessible registers{"",(uint32_t *)UL,""},//
{"FIO0SET0",(uint32_t *)0x2009C018UL,"Fast GPIO Port x output Set 8 (byte)"},// 0x2009 C018
{"FIO1SET0",(uint32_t *)0x2009C038UL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C038
{"FIO2SET0",(uint32_t *)0x2009C058UL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C058
{"FIO3SET0",(uint32_t *)0x2009C078UL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C078
{"FIO4SET0",(uint32_t *)0x2009C098UL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C098
{"FIO0SET1",(uint32_t *)0x2009C019UL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C019
{"FIO1SET1",(uint32_t *)0x2009C039UL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C039
{"FIO2SET1",(uint32_t *)0x2009C059UL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C059
{"FIO3SET1",(uint32_t *)0x2009C079UL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C079
{"FIO4SET1",(uint32_t *)0x2009C099UL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C099
{"FIO0SET2",(uint32_t *)0x2009C01AUL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C01A
{"FIO1SET2",(uint32_t *)0x2009C03AUL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C03A
{"FIO2SET2",(uint32_t *)0x2009C05AUL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C05A
{"FIO3SET2",(uint32_t *)0x2009C07AUL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C07A
{"FIO4SET2",(uint32_t *)0x2009C09AUL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C09A
{"FIO0SET3",(uint32_t *)0x2009C01BUL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C01B
{"FIO1SET3",(uint32_t *)0x2009C03BUL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C03B
{"FIO2SET3",(uint32_t *)0x2009C05BUL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C05B
{"FIO3SET3",(uint32_t *)0x2009C07BUL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C07B
{"FIO4SET3",(uint32_t *)0x2009C09BUL,"Fast GPIO Port x output Set 8 (byte) "},// 0x2009 C09B
{"FIO0SETL",(uint32_t *)0x2009C018UL,"Fast GPIO Port x output Set 16"},// 0x2009 C018
{"FIO1SETL",(uint32_t *)0x2009C038UL,"Fast GPIO Port x output Set 16"},// 0x2009 C038
{"FIO2SETL",(uint32_t *)0x2009C058UL,"Fast GPIO Port x output Set 16"},// 0x2009 C058
{"FIO3SETL",(uint32_t *)0x2009C078UL,"Fast GPIO Port x output Set 16"},// 0x2009 C078
{"FIO4SETL",(uint32_t *)0x2009C098UL,"Fast GPIO Port x output Set 16"},// 0x2009 C098
{"FIO0SETU",(uint32_t *)0x2009C01AUL,"Fast GPIO Port x output Set 16"},// 0x2009 C01A
{"FIO1SETU",(uint32_t *)0x2009C03AUL,"Fast GPIO Port x output Set 16"},// 0x2009 C03A
{"FIO2SETU",(uint32_t *)0x2009C05AUL,"Fast GPIO Port x output Set 16"},// 0x2009 C05A
{"FIO3SETU",(uint32_t *)0x2009C07AUL,"Fast GPIO Port x output Set 16"},// 0x2009 C07A
{"FIO4SETU",(uint32_t *)0x2009C09AUL,"Fast GPIO Port x output Set 16"},// 0x2009 C09A
//Fast GPIO port output Clear byte and half word accessible register{"",(uint32_t *)UL,""},//
{"FIO0CLR0",(uint32_t *)0x2009C01CUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C01C
{"FIO1CLR0",(uint32_t *)0x2009C03CUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C03C
{"FIO2CLR0",(uint32_t *)0x2009C05CUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C05C
{"FIO3CLR0",(uint32_t *)0x2009C07CUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C07C
{"FIO4CLR0",(uint32_t *)0x2009C09CUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C09C
{"FIO0CLR1",(uint32_t *)0x2009C01DUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C01D
{"FIO1CLR1",(uint32_t *)0x2009C03DUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C03D
{"FIO2CLR1",(uint32_t *)0x2009C05DUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C05D
{"FIO3CLR1",(uint32_t *)0x2009C07DUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C07D
{"FIO4CLR1",(uint32_t *)0x2009C09DUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C09D
{"FIO0CLR2",(uint32_t *)0x2009C01EUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C01E
{"FIO1CLR2",(uint32_t *)0x2009C03EUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C03E
{"FIO2CLR2",(uint32_t *)0x2009C05EUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C05E
{"FIO3CLR2",(uint32_t *)0x2009C07EUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C07E
{"FIO4CLR2",(uint32_t *)0x2009C09EUL,"Fast GPIO Port x output 8 (byte) "},// 0x2009 C09E
{"FIO0CLR3",(uint32_t *)0x2009C01FUL,"Fast GPIO Port x output 8 (byte)"},// 0x2009 C01F
{"FIO1CLR3",(uint32_t *)0x2009C03FUL,"Fast GPIO Port x output 8 (byte)"},// 0x2009 C03F
{"FIO2CLR3",(uint32_t *)0x2009C05FUL,"Fast GPIO Port x output 8 (byte)"},// 0x2009 C05F
{"FIO3CLR3",(uint32_t *)0x2009C07FUL,"Fast GPIO Port x output 8 (byte)"},// 0x2009 C07F
{"FIO4CLR3",(uint32_t *)0x2009C09FUL,"Fast GPIO Port x output 8 (byte)"},// 0x2009 C09F
{"FIO0CLRL",(uint32_t *)0x2009C01CUL,"Fast GPIO Port x output 16."},// 0x2009 C01C
{"FIO1CLRL",(uint32_t *)0x2009C03CUL,"Fast GPIO Port x output 16."},// 0x2009 C03C
{"FIO2CLRL",(uint32_t *)0x2009C05CUL,"Fast GPIO Port x output 16."},// 0x2009 C05C
{"FIO3CLRL",(uint32_t *)0x2009C07CUL,"Fast GPIO Port x output 16."},// 0x2009 C07C
{"FIO4CLRL",(uint32_t *)0x2009C09CUL,"Fast GPIO Port x output 16."},// 0x2009 C09C
{"FIO0CLRU",(uint32_t *)0x2009C01EUL,"Fast GPIO Port x output 16."},// 0x2009 C01E
{"FIO1CLRU",(uint32_t *)0x2009C03EUL,"Fast GPIO Port x output 16."},// 0x2009 C03E
{"FIO2CLRU",(uint32_t *)0x2009C05EUL,"Fast GPIO Port x output 16."},// 0x2009 C05E
{"FIO3CLRU",(uint32_t *)0x2009C07EUL,"Fast GPIO Port x output 16."},// 0x2009 C07E
{"FIO4CLRU",(uint32_t *)0x2009C09EUL,"Fast GPIO Port x output 16."},// 0x2009 C09E
//Fast GPIO port Pin value byte and half word accessible registers{"",(uint32_t *)UL,""},//
{"FIO0PIN0",(uint32_t *)0x2009C014UL,"Fast GPIO Port x Pin value 8 (byte)"},// 0x2009 C014
{"FIO1PIN0",(uint32_t *)0x2009C034UL,"Fast GPIO Port x Pin value 8 (byte)"},// 0x2009 C034
{"FIO2PIN0",(uint32_t *)0x2009C054UL,"Fast GPIO Port x Pin value 8 (byte) "},// 0x2009 C054
{"FIO3PIN0",(uint32_t *)0x2009C074UL,"Fast GPIO Port x Pin value 8 (byte) "},// 0x2009 C074
{"FIO4PIN0",(uint32_t *)0x2009C094UL,"Fast GPIO Port x Pin value 8 (byte) "},// 0x2009 C094
{"FIO0PIN1",(uint32_t *)0x2009C015UL,"Fast GPIO Port x Pin value 8 (byte) "},// 0x2009 C015
{"FIO1PIN1",(uint32_t *)0x2009C035UL,"Fast GPIO Port x Pin value 8 (byte) "},// 0x2009 C035
{"FIO2PIN1",(uint32_t *)0x2009C055UL,"Fast GPIO Port x Pin value 8 (byte) "},// 0x2009 C055
{"FIO3PIN1",(uint32_t *)0x2009C075UL,"Fast GPIO Port x Pin value 8 (byte) "},// 0x2009 C075
{"FIO4PIN1",(uint32_t *)0x2009C095UL,"Fast GPIO Port x Pin value 8 (byte) "},// 0x2009 C095
{"FIO0PIN2",(uint32_t *)0x2009C016UL,"Fast GPIO Port x Pin value 8 (byte) "},// 0x2009 C016
{"FIO1PIN2",(uint32_t *)0x2009C036UL,"Fast GPIO Port x Pin value 8 (byte) "},// 0x2009 C036
{"FIO2PIN2",(uint32_t *)0x2009C056UL,"Fast GPIO Port x Pin value 8 (byte) "},// 0x2009 C056
{"FIO3PIN2",(uint32_t *)0x2009C076UL,"Fast GPIO Port x Pin value 8 (byte) "},// 0x2009 C076
{"FIO4PIN2 ",(uint32_t *)0x2009C096UL,"Fast GPIO Port x Pin value 8 (byte) "},// 0x2009 C096
{"FIO0PIN3",(uint32_t *)0x2009C017UL,"Fast GPIO Port x Pin value 8 (byte)"},// 0x2009 C017
{"FIO1PIN3",(uint32_t *)0x2009C037UL,"Fast GPIO Port x Pin value 8 (byte)"},// 0x2009 C037
{"FIO2PIN3",(uint32_t *)0x2009C057UL,"Fast GPIO Port x Pin value 8 (byte)"},// 0x2009 C057
{"FIO3PIN3",(uint32_t *)0x2009C077UL,"Fast GPIO Port x Pin value 8 (byte)"},// 0x2009 C077
{"FIO4PIN3",(uint32_t *)0x2009C097UL,"Fast GPIO Port x Pin value 8 (byte)"},// 0x2009 C097
{"FIO0PINL",(uint32_t *)0x2009C014UL,"Fast GPIO Port x Pin value 16."},// 0x2009 C014
{"FIO1PINL",(uint32_t *)0x2009C034UL,"Fast GPIO Port x Pin value 16."},// 0x2009 C034
{"FIO2PINL",(uint32_t *)0x2009C054UL,"Fast GPIO Port x Pin value 16."},// 0x2009 C054
{"FIO3PINL",(uint32_t *)0x2009C074UL,"Fast GPIO Port x Pin value 16."},// 0x2009 C074
{"FIO4PINL",(uint32_t *)0x2009C094UL,"Fast GPIO Port x Pin value 16."},// 0x2009 C094
{"FIO0PINU",(uint32_t *)0x2009C016UL,"Fast GPIO Port x Pin value 16."},// 0x2009 C016
{"FIO1PINU",(uint32_t *)0x2009C036UL,"Fast GPIO Port x Pin value 16."},// 0x2009 C036
{"FIO2PINU",(uint32_t *)0x2009C056UL,"Fast GPIO Port x Pin value 16."},// 0x2009 C056
{"FIO3PINU",(uint32_t *)0x2009C076UL,"Fast GPIO Port x Pin value 16."},// 0x2009 C076
{"FIO4PINU",(uint32_t *)0x2009C096UL,"Fast GPIO Port x Pin value 16."},// 0x2009 C096
//Fast GPIO port Mask byte and half word accessible registers{"",(uint32_t *)UL,""},//
{"FIO0MASK0",(uint32_t *)0x2009C010UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C010
{"FIO1MASK0",(uint32_t *)0x2009C030UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C030
{"FIO2MASK0",(uint32_t *)0x2009C050UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C050
{"FIO3MASK0",(uint32_t *)0x2009C070UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C070
{"FIO4MASK0",(uint32_t *)0x2009C090UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C090
{"FIO0MASK1",(uint32_t *)0x2009C011UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C011
{"FIO1MASK1",(uint32_t *)0x2009C031UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C031
{"FIO2MASK1",(uint32_t *)0x2009C051UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C051
{"FIO3MASK1",(uint32_t *)0x2009C071UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C071
{"FIO4MASK1",(uint32_t *)0x2009C091UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C091
{"FIO0MASK2",(uint32_t *)0x2009C012UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C012
{"FIO1MASK2",(uint32_t *)0x2009C032UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C032
{"FIO2MASK2",(uint32_t *)0x2009C052UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C052
{"FIO3MASK2",(uint32_t *)0x2009C072UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C072
{"FIO4MASK2",(uint32_t *)0x2009C092UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C092
{"FIO0MASK3",(uint32_t *)0x2009C013UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C013
{"FIO1MASK3",(uint32_t *)0x2009C033UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C033
{"FIO2MASK3",(uint32_t *)0x2009C053UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C053
{"FIO3MASK3",(uint32_t *)0x2009C073UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C073
{"FIO4MASK3",(uint32_t *)0x2009C093UL,"Fast GPIO Port x Mask 8 (byte) "},// 0x2009 C093
{"FIO0MASKL",(uint32_t *)0x2009C010UL,"Fast GPIO Port x Mask 16."},// 0x2009 C010
{"FIO1MASKL",(uint32_t *)0x2009C030UL,"Fast GPIO Port x Mask 16."},// 0x2009 C030
{"FIO2MASKL",(uint32_t *)0x2009C050UL,"Fast GPIO Port x Mask 16."},// 0x2009 C050
{"FIO3MASKL",(uint32_t *)0x2009C070UL,"Fast GPIO Port x Mask 16."},// 0x2009 C070
{"FIO4MASKL",(uint32_t *)0x2009C090UL,"Fast GPIO Port x Mask 16."},// 0x2009 C090
{"FIO0MASKU",(uint32_t *)0x2009C012UL,"Fast GPIO Port x Mask 16."},// 0x2009 C012
{"FIO1MASKU",(uint32_t *)0x2009C032UL,"Fast GPIO Port x Mask 16."},// 0x2009 C032
{"FIO2MASKU",(uint32_t *)0x2009C052UL,"Fast GPIO Port x Mask 16."},// 0x2009 C052
{"FIO3MASKU",(uint32_t *)0x2009C072UL,"Fast GPIO Port x Mask 16."},// 0x2009 C072
{"FIO4MASKU",(uint32_t *)0x2009C092UL,"Fast GPIO Port x Mask 16."},// 0x2009 C092
//Ethernet registers.{"",(uint32_t *)UL,""},//
//MAC registers{"",(uint32_t *)UL,""},//
{"MAC1",(uint32_t *)0x50000000UL,"MAC configuration register 1."},//0x5000 0000
{"MAC2",(uint32_t *)0x50000004UL,"MAC configuration register 2."},//0x5000 0004
{"IPGT",(uint32_t *)0x50000008UL,"Gap register."},//0x5000 0008
{"IPGR",(uint32_t *)0x5000000CUL,"Non Back Gap register."},//0x5000 000C
{"CLRT",(uint32_t *)0x50000010UL,"Collision window / Retry register."},//0x5000 0010
{"MAXF",(uint32_t *)0x50000014UL,"Maximum Frame register."},//0x5000 0014
{"SUPP",(uint32_t *)0x50000018UL,"PHY Support register."},//0x5000 0018
{"TEST",(uint32_t *)0x5000001CUL,"Test register."},//0x5000 001C
{"MCFG",(uint32_t *)0x50000020UL,"MII Mgmt Configuration register."},//0x5000 0020
{"MCMD",(uint32_t *)0x50000024UL,"MII Mgmt Command register."},//0x5000 0024
{"MADR",(uint32_t *)0x50000028UL,"MII Mgmt Address register."},//0x5000 0028
{"MWTD",(uint32_t *)0x5000002CUL,"MII Mgmt Write Data register."},//0x5000 002C
{"MRDD",(uint32_t *)0x50000030UL,"MII Mgmt Read Data register."},//0x5000 0030
{"MIND",(uint32_t *)0x50000034UL,"MII Mgmt Indicators register."},//0x5000 0034
{"SA0",(uint32_t *)0x50000040UL,"Station Address 0 register."},//0x5000 0040
{"SA1",(uint32_t *)0x50000044UL,"Station Address 1 register."},//0x5000 0044
{"SA2",(uint32_t *)0x50000048UL,"Station Address 2 register."},//0x5000 0048
//Control registers{"",(uint32_t *)UL,""},//
{"Status",(uint32_t *)0x50000104UL,"Status register."},//0x5000 0104
{"RxDescriptor",(uint32_t *)0x50000108UL,"Receive descriptor base address register."},//0x5000 0108
{"RxStatus",(uint32_t *)0x5000010CUL,"Receive status base address register."},//0x5000 010C
{"RxDescriptorNumber",(uint32_t *)0x50000110UL,"Receive number of descriptors register."},//0x5000 0110
{"RxProduceIndex",(uint32_t *)0x50000114UL,"Receive produce index register."},//0x5000 0114
{"RxConsumeIndex",(uint32_t *)0x50000118UL,"Receive consume index register."},//0x5000 0118
{"TxDescriptor",(uint32_t *)0x5000011CUL,"Transmit descriptor base address register."},//0x5000 011C
{"TxStatus",(uint32_t *)0x50000120UL,"Transmit status base address register."},//0x5000 0120
{"TxDescriptorNumber",(uint32_t *)0x50000124UL,"Transmit number of descriptors register."},//0x5000 0124
{"TxProduceIndex",(uint32_t *)0x50000128UL,"Transmit produce index register."},//0x5000 0128
{"TxConsumeIndex",(uint32_t *)0x5000012CUL,"Transmit consume index register."},//0x5000 012C
{"TSV0",(uint32_t *)0x50000158UL,"Transmit status vector 0 register."},//0x5000 0158
{"TSV1",(uint32_t *)0x5000015CUL,"Transmit status vector 1 register."},//0x5000 015C
{"RSV",(uint32_t *)0x50000160UL,"Receive status vector register."},//0x5000 0160
{"FlowControlCounter",(uint32_t *)0x50000170UL,"Flow control counter register."},//0x5000 0170
{"FlowControlStatus",(uint32_t *)0x50000174UL,"Flow control status register."},//0x5000 0174
//Rx filter registers{"",(uint32_t *)UL,""},//
{"RxFliterCtrl",(uint32_t *)0x50000200UL,"Receive filter control register."},//0x5000 0200
{"RxFilterWoLStatus",(uint32_t *)0x50000204UL,"Receive filter WoL status register."},//0x5000 0204
{"RxFilterWoLClear",(uint32_t *)0x50000208UL,"Receive filter WoL clear register."},//0x5000 0208
{"HashFilterL",(uint32_t *)0x50000210UL,"Hash filter table LSBs register."},//0x5000 0210
{"HashFilterH",(uint32_t *)0x50000214UL,"Hash filter table MSBs register."},//0x5000 0214
//Module control registers{"",(uint32_t *)UL,""},//
{"IntStatus",(uint32_t *)0x50000FE0UL,"Interrupt status register."},//0x5000 0FE0
{"IntEnable",(uint32_t *)0x50000FE4UL,"Interrupt enable register."},//0x5000 0FE4
{"IntClear",(uint32_t *)0x50000FE8UL,"Interrupt clear register."},//0x5000 0FE8
{"IntSet",(uint32_t *)0x50000FECUL,"Interrupt set register."},//0x5000 0FEC
{"PowerDown",(uint32_t *)0x50000FF4UL,"Power"},//0x5000 0FF4
//USB device register map{"",(uint32_t *)UL,""},//
//Clock control registers{"",(uint32_t *)UL,""},//
{"USBClkCtrl",(uint32_t *)0x5000CFF4UL,"USB Clock Control"},//0x5000 CFF4
{"USBClkSt",(uint32_t *)0x5000CFF8UL,"USB Clock Status"},//0x5000 CFF8
//Device interrupt registers{"",(uint32_t *)UL,""},//
{"USBIntSt",(uint32_t *)0x400FC1C0UL,"USB Interrupt Status"},//0x400F C1C0
{"USBDevIntSt",(uint32_t *)0x5000C200UL,"USB Device Interrupt Status"},//0x5000 C200
{"USBDevIntEn",(uint32_t *)0x5000C204UL,"USB Device Interrupt Enable"},//0x5000 C204
{"USBDevIntClr",(uint32_t *)0x5000C208UL,"USB Device Interrupt Clear"},//0x5000 C208
{"USBDevIntSet",(uint32_t *)0x5000C20CUL,"USB Device Interrupt Set"},//0x5000 C20C
{"USBDevIntPri",(uint32_t *)0x5000C22CUL,"USB Device Interrupt Priority"},//0x5000 C22C
//Endpoint interrupt registers{"",(uint32_t *)UL,""},//
{"USBEpIntSt",(uint32_t *)0x5000C230UL,"USB Endpoint Interrupt Status"},//0x5000 C230
{"USBEpIntEn",(uint32_t *)0x5000C234UL,"USB Endpoint Interrupt Enable"},//0x5000 C234
{"USBEpIntClr",(uint32_t *)0x5000C238UL,"USB Endpoint Interrupt Clear"},//0x5000 C238
{"USBEpIntSet",(uint32_t *)0x5000C23CUL,"USB Endpoint Interrupt Set"},//0x5000 C23C
{"USBEpIntPri",(uint32_t *)0x5000C240UL,"USB Endpoint Priority"},//0x5000 C240
//Endpoint realization registers{"",(uint32_t *)UL,""},//
{"USBReEp",(uint32_t *)0x5000C244UL,"USB Realize Endpoint"},//0x5000 C244
{"USBEpIn",(uint32_t *)0x5000C248UL,"USB Endpoint Index"},//0x5000 C248
{"USBMaxPSize",(uint32_t *)0x5000C24CUL,"USB MaxPacketSize"},//0x5000 C24C
//USB transfer registers{"",(uint32_t *)UL,""},//
{"USBRxData",(uint32_t *)0x5000C218UL,"USB Receive Data"},//0x5000 C218
{"USBRxPLen",(uint32_t *)0x5000C220UL,"USB Receive Packet Length"},//0x5000 C220
{"USBTxData",(uint32_t *)0x5000C21CUL,"USB Transmit Data"},//0x5000 C21C
{"USBTxPLen",(uint32_t *)0x5000C224UL,"USB Transmit Packet Length"},//0x5000 C224
{"USBCtrl",(uint32_t *)0x5000C228UL,"USB Control"},//0x5000 C228
//SIE Command registers{"",(uint32_t *)UL,""},//
{"USBCmdCode",(uint32_t *)0x5000C210UL,"USB Command Code"},//0x5000 C210
{"USBCmdData",(uint32_t *)0x5000C214UL,"USB Command Data"},//0x5000 C214
//DMA registers{"",(uint32_t *)UL,""},//
{"USBDMARSt",(uint32_t *)0x5000C250UL,"USB DMA Request Status"},//0x5000 C250
{"USBDMARClr",(uint32_t *)0x5000C254UL,"USB DMA Request Clear"},//0x5000 C254
{"USBDMARSet",(uint32_t *)0x5000C258UL,"USB DMA Request Set"},//0x5000 C258
{"USBUDCAH",(uint32_t *)0x5000C280UL,"USB UDCA Head"},//0x5000 C280
{"USBEpDMASt",(uint32_t *)0x5000C284UL,"USB Endpoint DMA Status"},//0x5000 C284
{"USBEpDMAEn",(uint32_t *)0x5000C288UL,"USB Endpoint DMA Enable"},//0x5000 C288
{"USBEpDMADis",(uint32_t *)0x5000C28CUL,"USB Endpoint DMA Disable"},//0x5000 C28C
{"USBDMAIntSt",(uint32_t *)0x5000C290UL,"USB DMA Interrupt Status"},//0x5000 C290
{"USBDMAIntEn",(uint32_t *)0x5000C294UL,"USB DMA Interrupt Enable"},//0x5000 C294
{"USBEoTIntSt",(uint32_t *)0x5000C2A0UL,"USB End of Transfer Interrupt Status"},//0x5000 C2A0
{"USBEoTIntClr",(uint32_t *)0x5000C2A4UL,"USB End of Transfer Interrupt Clear"},//0x5000 C2A4
{"USBEoTIntSet",(uint32_t *)0x5000C2A8UL,"USB End of Transfer Interrupt Set"},//0x5000 C2A8
{"USBNDDRIntSt",(uint32_t *)0x5000C2ACUL,"USB New DD Request Interrupt Status"},//0x5000 C2AC
{"USBNDDRIntClr",(uint32_t *)0x5000C2B0UL,"USB New DD Request Interrupt Clear"},//0x5000 C2B0
{"USBNDDRIntSet",(uint32_t *)0x5000C2B4UL,"USB New DD Request Interrupt Set"},//0x5000 C2B4
{"USBSysErrIntSt",(uint32_t *)0x5000C2B8UL,"USB System Error Interrupt Status"},//0x5000 C2B8
{"USBSysErrIntClr",(uint32_t *)0x5000C2BCUL,"USB System Error Interrupt Clear"},//0x5000 C2BC
{"USBSysErrIntSet",(uint32_t *)0x5000C2C0UL,"USB System Error Interrupt Set"},//0x5000 C2C0
//USB Host register address definitions{"",(uint32_t *)UL,""},//
{"HcRevision",(uint32_t *)0x5000C000UL,"BCD representation of the version of the HCI specification that is implemented by the Host Controller."},//0x5000 C000
{"HcControl",(uint32_t *)0x5000C004UL,"Defines the operating modes of the HC."},//0x5000 C004
{"HcCommandStatus",(uint32_t *)0x5000C008UL,"This register is used to receive the commands from the Host Controller Driver (HCD)."},//0x5000 C008
{"HcInterruptStatus",(uint32_t *)0x5000C00CUL,"Indicates the status on various events that cause hardware interrupts by setting the appropriate bits."},//0x5000 C00C
{"HcInterruptEnable",(uint32_t *)0x5000C010UL,"Controls the bits in the HcInterruptStatus register and indicates which events will generate a hardware interrupt."},//0x5000 C010
{"HcInterruptDisable",(uint32_t *)0x5000C014UL,"The bits in this register are used to disable corresponding bits in the HCInterruptStatus register and in turn disable that event leading to hardware interrupt."},//0x5000 C014
{"HcHCCA",(uint32_t *)0x5000C018UL,"Contains the physical address of the host controller communication area."},//0x5000 C018
{"HcPeriodCurrentED",(uint32_t *)0x5000C01CUL,"Contains the physical address of the current isochronous or interrupt endpoint descriptor."},//0x5000 C01C
{"HcControlHeadED",(uint32_t *)0x5000C020UL,"Contains the physical address of the first endpoint descriptor of the control list."},//0x5000 C020
{"HcControlCurrentED",(uint32_t *)0x5000C024UL,"Contains the physical address of the current endpoint descriptor of the control list"},//0x5000 C024
{"HcBulkHeadED",(uint32_t *)0x5000C028UL,"Contains the physical address of the first endpoint descriptor of the bulk list."},//0x5000 C028
{"HcBulkCurrentED",(uint32_t *)0x5000C02CUL,"Contains the physical address of the current endpoint descriptor of the bulk list."},//0x5000 C02C
{"HcDoneHead",(uint32_t *)0x5000C030UL,"Contains the physical address of the last transfer descriptor added to the ‘Done’ queue."},//0x5000 C030
{"HcFmInterval",(uint32_t *)0x5000C034UL,"Defines the bit time interval in a frame and the full speed maximum packet size which would not cause an overrun."},//0x5000 C034
{"HcFmRemaining",(uint32_t *)0x5000C038UL,"A 14-bit counter showing the bit time remaining in the current frame."},//0x5000 C038
{"HcFmNumber",(uint32_t *)0x5000C03CUL,"Contains a 16-bit counter and provides the timing reference among events happening in the HC and the HCD."},//0x5000 C03C
{"HcPeriodicStart",(uint32_t *)0x5000C040UL,"Contains a programmable 14-bit value which determines the earliest time HC should start processing a periodic list."},//0x5000 C040
{"HcLSThreshold",(uint32_t *)0x5000C044UL,"Contains 11-bit value which is used by the HC to determine whether to commit to transfer a maximum of 8-byte LS packet before EOF."},//0x5000 C044
{"HcRhDescriptorA",(uint32_t *)0x5000C048UL,"First of the two registers which describes the characteristics of the root hub."},//0x5000 C048
{"HcRhDescriptorB",(uint32_t *)0x5000C04CUL,"Second of the two registers which describes the characteristics of the Root Hub."},//0x5000 C04C
{"HcRhStatus",(uint32_t *)0x5000C050UL,"This register is divided into two parts."},//0x5000 C050
{"HcRhPortStatus[1]",(uint32_t *)0x5000C054UL,"Controls and reports the port events on a per-port basis."},//0x5000 C054
{"HcRhPortStatus[2]",(uint32_t *)0x5000C058UL,"Controls and reports the port events on a per port basis."},//0x5000 C058
{"Module_ID/Ver_Rev_ID",(uint32_t *)0x5000C0FCUL,"IP number, where yy (0x00) is unique version number"},//0x5000 C0FC
//Interrupt register{"",(uint32_t *)UL,""},//
{"USBIntSt",(uint32_t *)0x400FC1C0UL,"USB Interrupt Status"},//0x400F C1C0
//OTG registers{"",(uint32_t *)UL,""},//
{"OTGIntSt",(uint32_t *)0x5000C100UL,"OTG Interrupt Status"},//0x5000 C100
{"OTGIntEn",(uint32_t *)0x5000C104UL,"OTG Interrupt Enable"},//0x5000 C104
{"OTGIntSet",(uint32_t *)0x5000C108UL,"OTG Interrupt Set"},//0x5000 C108
{"OTGIntClr",(uint32_t *)0x5000C10CUL,"OTG Interrupt Clear"},//0x5000 C10C
{"OTGStCtrl",(uint32_t *)0x5000C110UL,"OTG Status and Control"},//0x5000 C110
{"OTGTmr",(uint32_t *)0x5000C114UL,"OTG Timer"},//0x5000 C114
//I2C registers{"",(uint32_t *)UL,""},//
{"I2C_RX",(uint32_t *)0x5000C300UL,"I2C Receive"},//0x5000 C300
{"I2C_TX",(uint32_t *)0x5000C300UL,"I2C Transmit"},//0x5000 C300
{"I2C_STS",(uint32_t *)0x5000C304UL,"I2C Status"},//0x5000 C304
{"I2C_CTL",(uint32_t *)0x5000C308UL,"I2C Control"},//0x5000 C308
{"I2C_CLKHI",(uint32_t *)0x5000C30CUL,"I2C Clock High"},//0x5000 C30C
{"I2C_CLKLO",(uint32_t *)0x5000C310UL,"I2C Clock Low"},//0x5000 C310
//Clock control registers{"",(uint32_t *)UL,""},//
{"OTGClkCtrl",(uint32_t *)0x5000CFF4UL,"OTG clock controller"},//0x5000 CFF4
{"OTGClkSt",(uint32_t *)0x5000CFF8UL,"OTG clock status"},//0x5000 CFF8
//UART1 register map{"",(uint32_t *)UL,""},//
{"U1RBR",(uint32_t *)0x40010000UL,"Receiver Buffer Register."},//0x4001 0000
{"U1THR",(uint32_t *)0x40010000UL,"Transmit Holding Register. "},//0x4001 0000
{"U1DLL",(uint32_t *)0x40010000UL,"Divisor Latch LSB. "},//0x4001 0000
{"U1DLM",(uint32_t *)0x40010004UL,"Divisor Latch MSB. "},//0x4001 0004
{"U1IER",(uint32_t *)0x40010004UL,"Interrupt enable register."},//0x4001 0004
{"U1IIR",(uint32_t *)0x40010008UL,"Interrupt ID Register."},//0x4001 0008
{"U1FCR",(uint32_t *)0x40010008UL,"FIFO Control Register. "},//0x4001 0008
{"U1LCR",(uint32_t *)0x4001000CUL,"Line Control Register. "},//0x4001 000C
{"U1MCR",(uint32_t *)0x40010010UL,"Modem Control Register. "},//0x4001 0010
{"U1LSR",(uint32_t *)0x40010014UL,"Line Status Register. "},//0x4001 0014
{"U1MSR",(uint32_t *)0x40010018UL,"Modem Status Register. "},//0x4001 0018
{"U1SCR",(uint32_t *)0x4001001CUL,"Scratch Pad Register."},//0x4001 001C
{"U1ACR",(uint32_t *)0x40010020UL,"Auto-baud Control Register. ."},//0x4001 0020
{"U1FDR",(uint32_t *)0x40010028UL,"Fractional Divider Register. "},//0x4001 0028
{"U1TER",(uint32_t *)0x40010030UL,"Transmit Enable Register. "},//0x4001 0030
{"U1RS485CTRL",(uint32_t *)0x4001004CUL,"RS-485/EIA-485 Control. "},//0x4001 004C
{"U1ADRMATCH",(uint32_t *)0x40010050UL,"RS-485/EIA-485 address match. "},//0x4001 0050
{"U1RS485DLY",(uint32_t *)0x40010054UL,"RS-485/EIA-485 direction control delay."},//0x4001 0054
//CAN acceptance filter and central CAN registers{"",(uint32_t *)UL,""},//
{"AFMR",(uint32_t *)0x4003C000UL,"Acceptance Filter Register"},//0x4003 C000
{"SFF_sa",(uint32_t *)0x4003C004UL,"Standard Frame Individual Start Address Register"},//0x4003 C004
{"SFF_GRP_sa",(uint32_t *)0x4003C008UL,"Standard Frame Group Start Address Register"},//0x4003 C008
{"EFF_sa",(uint32_t *)0x4003C00CUL,"Extended Frame Start Address Register"},//0x4003 C00C
{"EFF_GRP_sa",(uint32_t *)0x4003C010UL,"Extended Frame Group Start Address Register"},//0x4003 C010
{"ENDofTable",(uint32_t *)0x4003C014UL,"End of AF Tables register"},//0x4003 C014
{"LUTerrAd",(uint32_t *)0x4003C018UL,"LUT Error Address register"},//0x4003 C018
{"LUTerr",(uint32_t *)0x4003C01CUL,"LUT Error Register"},//0x4003 C01C
{"CANTxSR",(uint32_t *)0x40040000UL,"CAN Central Transmit Status Register"},//0x4004 0000
{"CANRxSR",(uint32_t *)0x40040004UL,"CAN Central Receive Status Register"},//0x4004 0004
{"CANMSR",(uint32_t *)0x40040008UL,"CAN Central Miscellaneous Register"},//0x4004 0008
{"CAN1MOD",(uint32_t *)0x40044000UL,"MOD Controls the operating mode of the CAN Controller."},//0x4004 4000
{"CAN2MOD",(uint32_t *)0x40048000UL,"MOD Controls the operating mode of the CAN Controller."},//0x4004 8000
{"CAN1CMR",(uint32_t *)0x40044004UL,"CMR Command bits that affect the state of the CAN Controller"},//0x4004 4004
{"CAN2CMR",(uint32_t *)0x40048004UL,"CMR Command bits that affect the state of the CAN Controller"},//0x4004 8004
{"CAN1GSR",(uint32_t *)0x40044008UL,"GSR Global Controller Status and Error Counters"},//0x4004 4008
{"CAN2GSR",(uint32_t *)0x40048008UL,"GSR Global Controller Status and Error Counters"},//0x4004 8008
{"CAN1ICR",(uint32_t *)0x4004400CUL,"ICR Interrupt status, Arbitration Lost Capture, Error Code Capture"},//0x4004 400C
{"CAN2ICR",(uint32_t *)0x4004800CUL,"ICR Interrupt status, Arbitration Lost Capture, Error Code Capture"},//0x4004 800C
{"CAN1IER",(uint32_t *)0x40044010UL,"IER Interrupt Enable"},//0x4004 4010
{"CAN2IER",(uint32_t *)0x40048010UL,"IER Interrupt Enable"},//0x4004 8010
{"CANSLEEPCLR",(uint32_t *)0x400FC110UL,"Allows clearing the current CAN channel sleep state as well as reading that state."},//0x400F C110
{"CANWAKEFLAGS",(uint32_t *)0x400FC114UL,"Allows reading the wake-up state of the CAN channels."},//0x400F C114
{"CAN1BTR",(uint32_t *)0x40044014UL,"Bus Timing"},//0x4004 4014
{"CAN2BTR",(uint32_t *)0x40048014UL,"Bus Timing"},//0x4004 8014
{"CAN1EWL",(uint32_t *)0x40044018UL,"Error Warning Limit"},//0x4004 4018
{"CAN2EWL",(uint32_t *)0x40048018UL,"Error Warning Limit"},//0x4004 8018
{"CAN1SR",(uint32_t *)0x4004401CUL,"Status Register"},//0x4004 401C
{"CAN2SR",(uint32_t *)0x4004801CUL,"Status Register"},//0x4004 801C
{"CAN1RFS",(uint32_t *)0x40044020UL,"Receive frame status"},//0x4004 4020
{"CAN2RFS",(uint32_t *)0x40048020UL,"Receive frame status"},//0x4004 8020
{"CAN1RID",(uint32_t *)0x40044024UL,"Received Identifier"},//0x4004 4024
{"CAN2RID",(uint32_t *)0x40048024UL,"Received Identifier"},//0x4004 8024
{"CAN1RDA",(uint32_t *)0x40044028UL,"Received data bytes 1-4"},//0x4004 4028
{"CAN2RDA",(uint32_t *)0x40048028UL,"Received data bytes 1-4"},//0x4004 8028
{"CAN1RDB",(uint32_t *)0x4004402CUL,"Received data bytes 5-8"},//0x4004 402C
{"CAN2RDB",(uint32_t *)0x4004802CUL,"Received data bytes 5-8"},//0x4004 802C
{"CAN1TFI1",(uint32_t *)0x40044030UL,"Transmit frame info (Tx Buffer 1)"},//0x4004 4030
{"CAN2TFI1",(uint32_t *)0x40048030UL,"Transmit frame info (Tx Buffer 1)"},//0x4004 8030
{"CAN1TID1",(uint32_t *)0x40044034UL,"Transmit Identifier (Tx Buffer 1)"},//0x4004 4034
{"CAN2TID1",(uint32_t *)0x40048034UL,"Transmit Identifier (Tx Buffer 1)"},//0x4004 8034
{"CAN1TDA1",(uint32_t *)0x40044038UL,"TDA1 Transmit data bytes 1-4 (Tx Buffer 1)"},//0x4004 4038
{"CAN1TDB1",(uint32_t *)0x4004403CUL,"TDB1 Transmit data bytes 5-8 (Tx Buffer 1)"},//0x4004 403C
{"CAN2TDA1",(uint32_t *)0x40048038UL,"TDA1 Transmit data bytes 1-4 (Tx Buffer 1) "},//0x4004 8038
{"CAN2TDB1",(uint32_t *)0x4004803CUL,"TDB1 Transmit data bytes 5-8 (Tx Buffer 1) "},//0x4004 803C
{"CAN1TFI2",(uint32_t *)0x40044040UL,"Transmit frame info (Tx Buffer 2)"},//0x4004 4040
{"CAN2TFI2",(uint32_t *)0x40048040UL,"Transmit frame info (Tx Buffer 2)"},//0x4004 8040
{"CAN1TID2",(uint32_t *)0x40044044UL,"Transmit Identifier (Tx Buffer 2)"},//0x4004 4044
{"CAN2TID2",(uint32_t *)0x40048044UL,"Transmit Identifier (Tx Buffer 2)"},//0x4004 8044
{"CAN1TDA2",(uint32_t *)0x40044048UL,"TDA2 Transmit data bytes 1-4 (Tx Buffer 2)"},//0x4004 4048
{"CAN1TDB2",(uint32_t *)0x4004404CUL,"TDB2 Transmit data bytes 5-8 (Tx Buffer 2) "},//0x4004 404C
{"CAN2TDA2",(uint32_t *)0x40048048UL,"TDA2 Transmit data bytes 1-4 (Tx Buffer 2)"},//0x4004 8048
{"CAN2TDB2",(uint32_t *)0x4004804CUL,"TDB2 Transmit data bytes 5-8 (Tx Buffer 2) "},//0x4004 804C
{"CAN1TFI3",(uint32_t *)0x40044050UL,"Transmit frame info (Tx Buffer 3)"},//0x4004 4050
{"CAN2TFI3",(uint32_t *)0x40048050UL,"Transmit frame info (Tx Buffer 3)"},//0x4004 8050
{"CAN1TID3",(uint32_t *)0x40044054UL,"Transmit Identifier (Tx Buffer 3)"},//0x4004 4054
{"CAN2TID3",(uint32_t *)0x40048054UL,"Transmit Identifier (Tx Buffer 3)"},//0x4004 8054
{"CAN1TDA3",(uint32_t *)0x40044058UL,"TDA3 Transmit data bytes 1-4 (Tx Buffer 3)"},//0x4004 4058
{"CAN1TDB3",(uint32_t *)0x4004405CUL,"TDB3 Transmit data bytes 5-8 (Tx Buffer 3)"},//0x4004 405C
{"CAN2TDA3",(uint32_t *)0x40048058UL,"TDA3 Transmit data bytes 1-4 (Tx Buffer 3)"},//0x4004 8058
{"CAN2TDB3",(uint32_t *)0x4004805CUL,"TDB3 Transmit data bytes 5-8 (Tx Buffer 3)"},//0x4004 805C
//SPI register map{"",(uint32_t *)UL,""},//
{"S0SPCR",(uint32_t *)0x40020000UL,"SPI Control Register. "},//0x4002 0000
{"S0SPSR",(uint32_t *)0x40020004UL,"SPI Status Register."},//0x4002 0004
{"S0SPDR",(uint32_t *)0x40020008UL,"SPI Data Register. "},//0x4002 0008
{"S0SPCCR",(uint32_t *)0x4002000CUL,"SPI Clock Counter Register."},//0x4002 000C
{"S0SPINT",(uint32_t *)0x4002001CUL,"SPI Interrupt Flag."},//0x4002 001C
//SSP Register Map{"",(uint32_t *)UL,""},//
{"SSP0CR0",(uint32_t *)0x40088000UL,"CR0 Control Register 0. Selects the serial clock rate, bus type, and data size."},//0x4008 8000
{"SSP1CR0",(uint32_t *)0x40030000UL,"CR0 Control Register 0. Selects the serial clock rate, bus type, and data size."},//0x4003 0000
{"SSP0CR1",(uint32_t *)0x40088004UL,"CR1 Control Register 1. Selects master/slave and other modes."},//0x4008 8004
{"SSP1CR1",(uint32_t *)0x40030004UL,"CR1 Control Register 1. Selects master/slave and other modes."},//0x4003 0004
{"SSP0DR",(uint32_t *)0x40088008UL,"DR Data Register. Writes fill the transmit FIFO, and reads empty the receive FIFO."},//0x4008 8008
{"SSP1DR",(uint32_t *)0x40030008UL,"DR Data Register. Writes fill the transmit FIFO, and reads empty the receive FIFO."},//0x4003 0008
{"SSP0SR",(uint32_t *)0x4008800CUL,"SR Status Register"},//0x4008 800C
{"SSP1SR",(uint32_t *)0x4003000CUL,"SR Status Register"},//0x4003 000C
{"SSP0CPSR",(uint32_t *)0x40088010UL,"CPSR Clock Prescale Register"},//0x4008 8010
{"SSP1CPSR",(uint32_t *)0x40030010UL,"CPSR Clock Prescale Register"},//0x4003 0010
{"SSP0IMSC",(uint32_t *)0x40088014UL,"IMSC Interrupt Mask Set and Clear Register"},//0x4008 8014
{"SSP1IMSC",(uint32_t *)0x40030014UL,"IMSC Interrupt Mask Set and Clear Register"},//0x4003 0014
{"SSP0RIS",(uint32_t *)0x40088018UL,"RIS Raw Interrupt Status Register"},//0x4008 8018
{"SSP1RIS",(uint32_t *)0x40030018UL,"RIS Raw Interrupt Status Register"},//0x4003 0018
{"SSP0MIS",(uint32_t *)0x4008801CUL,"MIS Masked Interrupt Status Register"},//0x4008 801C
{"SSP1MIS",(uint32_t *)0x4003001CUL,"MIS Masked Interrupt Status Register"},//0x4003 001C
{"SSP0ICR",(uint32_t *)0x40088020UL,"ICR SSPICR Interrupt Clear Register"},//0x4008 8020
{"SSP1ICR",(uint32_t *)0x40030020UL,"ICR SSPICR Interrupt Clear Register"},//0x4003 0020
{"SSP0DMACR",(uint32_t *)0x40088024UL,"DMACR DMA Control Register"},//0x4008 8024
{"SSP1DMACR",(uint32_t *)0x40030024UL,"DMACR DMA Control Register"},//0x4003 0024
//I2C register map{"",(uint32_t *)UL,""},//
{"I2C0CONSET",(uint32_t *)0x4001C000UL,"I2C Control Set Register. "},//0x4001 C000
{"I2C1CONSET",(uint32_t *)0x4005C000UL,"I2C Control Set Register. "},//0x4005 C000
{"I2C2CONSET",(uint32_t *)0x400A0000UL,"I2C Control Set Register. "},//0x400A 0000
{"I2C0STAT",(uint32_t *)0x4001C004UL,"I2C Status Register. "},//0x4001 C004
{"I2C1STAT",(uint32_t *)0x4005C004UL,"I2C Status Register. "},//0x4005 C004
{"I2C2STAT",(uint32_t *)0x400A0004UL,"I2C Status Register. "},//0x400A 0004
{"I2C0DAT",(uint32_t *)0x4001C008UL,"I2C Data Register. "},//0x4001 C008
{"I2C1DAT",(uint32_t *)0x4005C008UL,"I2C Data Register. "},//0x4005 C008
{"I2C2DAT",(uint32_t *)0x400A0008UL,"I2C Data Register. "},//0x400A 0008
{"I2C0ADR0",(uint32_t *)0x4001C00CUL,"I2C Slave Address Register 0."},//0x4001 C00C
{"I2C1ADR0",(uint32_t *)0x4005C00CUL,"I2C Slave Address Register 0."},//0x4005 C00C
{"I2C2ADR0",(uint32_t *)0x400A000CUL,"I2C Slave Address Register 0."},//0x400A 000C
{"I2C0SCLH",(uint32_t *)0x4001C010UL,"SCH Duty Cycle Register High Half Word."},//0x4001 C010
{"I2C1SCLH",(uint32_t *)0x4005C010UL,"SCH Duty Cycle Register High Half Word."},//0x4005 C010
{"I2C2SCLH",(uint32_t *)0x400A0010UL,"SCH Duty Cycle Register High Half Word."},//0x400A 0010
{"I2C0SCLL",(uint32_t *)0x4001C014UL,"SCL Duty Cycle Register Low Half Word."},//0x4001 C014
{"I2C1SCLL",(uint32_t *)0x4005C014UL,"SCL Duty Cycle Register Low Half Word."},//0x4005 C014
{"I2C2SCLL",(uint32_t *)0x400A0014UL,"SCL Duty Cycle Register Low Half Word."},//0x400A 0014
{"I2C0CONCLR",(uint32_t *)0x4001C018UL,"I2C Control Clear Register. "},//0x4001 C018
{"I2C1CONCLR",(uint32_t *)0x4005C018UL,"I2C Control Clear Register. "},//0x4005 C018
{"I2C2CONCLR",(uint32_t *)0x400A0018UL,"I2C Control Clear Register. "},//0x400A 0018
{"I2C0MMCTRL",(uint32_t *)0x4001C01CUL,"Monitor mode control register."},//0x4001 C01C
{"I2C1MMCTRL",(uint32_t *)0x4005C01CUL,"Monitor mode control register."},//0x4005 C01C
{"I2C2MMCTRL",(uint32_t *)0x400A001CUL,"Monitor mode control register."},//0x400A 001C
{"I2C0ADR1",(uint32_t *)0x4001C020UL,"I2C Slave Address Register 1. "},//0x4001 C020
{"I2C1ADR1",(uint32_t *)0x4005C020UL,"I2C Slave Address Register 1. "},//0x4005 C020
{"I2C2ADR1",(uint32_t *)0x400A0020UL,"I2C Slave Address Register 1. "},//0x400A 0020
//I2S register map{"",(uint32_t *)UL,""},//
{"I2SDAO",(uint32_t *)0x400A8000UL,"Digital Audio Output Register. "},//0x400A 8000
{"I2SDAI",(uint32_t *)0x400A8004UL,"Digital Audio Input Register. "},//0x400A 8004
{"I2STXFIFO",(uint32_t *)0x400A8008UL,"Transmit FIFO. "},//0x400A 8008
{"I2SRXFIFO",(uint32_t *)0x400A800CUL,"Receive FIFO. "},//0x400A 800C
{"I2SSTATE",(uint32_t *)0x400A8010UL,"Status Feedback Register. "},//0x400A 8010
{"I2SDMA1",(uint32_t *)0x400A8014UL,"DMA Configuration Register 1."},//0x400A 8014
{"I2SDMA2",(uint32_t *)0x400A8018UL,"DMA Configuration Register 2. "},//0x400A 8018
{"I2SIRQ",(uint32_t *)0x400A801CUL,"Interrupt Request Control Register. "},//0x400A 801C
{"I2STXRATE",(uint32_t *)0x400A8020UL,"Transmit MCLK divider. "},//0x400A 8020
{"I2SRXRATE",(uint32_t *)0x400A8024UL,"Receive MCLK divider. "},//0x400A 8024
{"I2STXBITRATE",(uint32_t *)0x400A8028UL,"Transmit bit rate divider. "},//0x400A 8028
{"I2SRXBITRATE",(uint32_t *)0x400A802CUL,"Receive bit rate divider. "},//0x400A 802C
{"I2STXMODE",(uint32_t *)0x400A8030UL,"Transmit mode control. R/W"},//0x400A 8030
{"I2SRXMODE",(uint32_t *)0x400A8034UL,"Receive mode control. R/W"},//0x400A 8034
//TIMER/COUNTER0-3 register map{"",(uint32_t *)UL,""},//
{"T0IR",(uint32_t *)0x40004000UL,"IR Interrupt Register. "},//0x4000 4000
{"T1IR",(uint32_t *)0x40008000UL,"IR Interrupt Register. "},//0x4000 8000
{"T2IR",(uint32_t *)0x40090000UL,"IR Interrupt Register. "},//0x4009 0000
{"T3IR",(uint32_t *)0x40094000UL,"IR Interrupt Register. "},//0x4009 4000
{"T0TCR",(uint32_t *)0x40004004UL,"TCR Timer Control Register. "},//0x4000 4004
{"T1TCR",(uint32_t *)0x40008004UL,"TCR Timer Control Register. "},//0x4000 8004
{"T2TCR",(uint32_t *)0x40090004UL,"TCR Timer Control Register. "},//0x4009 0004
{"T3TCR",(uint32_t *)0x40094004UL,"TCR Timer Control Register. "},//0x4009 4004
{"T0TC",(uint32_t *)0x40004008UL,"TC Timer Counter. "},//0x4000 4008
{"T1TC",(uint32_t *)0x40008008UL,"TC Timer Counter. "},//0x4000 8008
{"T2TC",(uint32_t *)0x40090008UL,"TC Timer Counter. "},//0x4009 0008
{"T3TC",(uint32_t *)0x40094008UL,"TC Timer Counter. "},//0x4009 4008
{"T0PR",(uint32_t *)0x4000400CUL,"PR Prescale Register. "},//0x4000 400C
{"T1PR",(uint32_t *)0x4000800CUL,"PR Prescale Register. "},//0x4000 800C
{"T2PR",(uint32_t *)0x4009000CUL,"PR Prescale Register. "},//0x4009 000C
{"T3PR",(uint32_t *)0x4009400CUL,"PR Prescale Register. "},//0x4009 400C
{"T0PC",(uint32_t *)0x40004010UL,"PC Prescale Counter. "},//0x4000 4010
{"T1PC",(uint32_t *)0x40008010UL,"PC Prescale Counter. "},//0x4000 8010
{"T2PC",(uint32_t *)0x40090010UL,"PC Prescale Counter. "},//0x4009 0010
{"T3PC",(uint32_t *)0x40094010UL,"PC Prescale Counter. "},//0x4009 4010
{"T0MCR",(uint32_t *)0x40004014UL,"MCR Match Control Register. "},//0x4000 4014
{"T1MCR",(uint32_t *)0x40008014UL,"MCR Match Control Register. "},//0x4000 8014
{"T2MCR",(uint32_t *)0x40090014UL,"MCR Match Control Register. "},//0x4009 0014
{"T3MCR",(uint32_t *)0x40094014UL,"MCR Match Control Register. "},//0x4009 4014
{"T0MR0",(uint32_t *)0x40004018UL,"MR0 Match Register 0.  "},//0x4000 4018
{"T1MR0",(uint32_t *)0x40008018UL,"MR0 Match Register 0.  "},//0x4000 8018
{"T2MR0",(uint32_t *)0x40090018UL,"MR0 Match Register 0.  "},//0x4009 0018
{"T3MR0",(uint32_t *)0x40094018UL,"MR0 Match Register 0.  "},//0x4009 4018
{"T0MR1",(uint32_t *)0x4000401CUL,"MR1 Match Register 1. "},//0x4000 401C
{"T1MR1",(uint32_t *)0x4000801CUL,"MR1 Match Register 1. "},//0x4000 801C
{"T2MR1",(uint32_t *)0x4009001CUL,"MR1 Match Register 1. "},//0x4009 001C
{"T3MR1",(uint32_t *)0x4009401CUL,"MR1 Match Register 1. "},//0x4009 401C
{"T0MR2",(uint32_t *)0x40004020UL,"MR2 Match Register 2. "},//0x4000 4020
{"T1MR2",(uint32_t *)0x40008020UL,"MR2 Match Register 2. "},//0x4000 8020
{"T2MR2",(uint32_t *)0x40090020UL,"MR2 Match Register 2. "},//0x4009 0020
{"T3MR2",(uint32_t *)0x40094020UL,"MR2 Match Register 2. "},//0x4009 4020
{"T0MR3",(uint32_t *)0x40004024UL,"MR3 Match Register 3. "},//0x4000 4024
{"T1MR3",(uint32_t *)0x40008024UL,"MR3 Match Register 3. "},//0x4000 8024
{"T2MR3",(uint32_t *)0x40090024UL,"MR3 Match Register 3. "},//0x4009 0024
{"T3MR3",(uint32_t *)0x40094024UL,"MR3 Match Register 3. "},//0x4009 4024
{"T0CCR",(uint32_t *)0x40004028UL,"CCR Capture Control Register. "},//0x4000 4028
{"T1CCR",(uint32_t *)0x40008028UL,"CCR Capture Control Register. "},//0x4000 8028
{"T2CCR",(uint32_t *)0x40090028UL,"CCR Capture Control Register. "},//0x4009 0028
{"T3CCR",(uint32_t *)0x40094028UL,"CCR Capture Control Register. "},//0x4009 4028
{"T0CR0",(uint32_t *)0x4000402CUL,"CR0 Capture Register 0. "},//0x4000 402C
{"T1CR0",(uint32_t *)0x4000802CUL,"CR0 Capture Register 0. "},//0x4000 802C
{"T2CR0",(uint32_t *)0x4009002CUL,"CR0 Capture Register 0. "},//0x4009 002C
{"T3CR0",(uint32_t *)0x4009402CUL,"CR0 Capture Register 0. "},//0x4009 402C
{"T0CR1",(uint32_t *)0x40004030UL,"CR1 Capture Register 1. "},//0x4000 4030
{"T1CR1",(uint32_t *)0x40008030UL,"CR1 Capture Register 1. "},//0x4000 8030
{"T2CR1",(uint32_t *)0x40090030UL,"CR1 Capture Register 1. "},//0x4009 0030
{"T3CR1",(uint32_t *)0x40094030UL,"CR1 Capture Register 1. "},//0x4009 4030
{"T0EMR",(uint32_t *)0x4000403CUL,"EMR External Match Register. "},//0x4000 403C
{"T1EMR",(uint32_t *)0x4000803CUL,"EMR External Match Register. "},//0x4000 803C
{"T2EMR",(uint32_t *)0x4009003CUL,"EMR External Match Register. "},//0x4009 003C
{"T3EMR",(uint32_t *)0x4009403CUL,"EMR External Match Register. "},//0x4009 403C
{"T0CTCR",(uint32_t *)0x40004070UL,"CTCR Count Control Register. "},//0x4000 4070
{"T1CTCR",(uint32_t *)0x40008070UL,"CTCR Count Control Register. "},//0x4000 8070
{"T2CTCR",(uint32_t *)0x40090070UL,"CTCR Count Control Register. "},//0x4009 0070
{"T3CTCR",(uint32_t *)0x40094070UL,"CTCR Count Control Register. "},//0x4009 4070
//Repetitive Interrupt Timer register map{"",(uint32_t *)UL,""},//
{"RICOMPVAL",(uint32_t *)0x400B0000UL,"Compare register"},//0x400B 0000
{"RIMASK",(uint32_t *)0x400B0004UL,"Mask register."},//0x400B 0004
{"RICTRL",(uint32_t *)0x400B0008UL,"Control register."},//0x400B 0008
{"RICOUNTER",(uint32_t *)0x400B000CUL,"32-bit counter"},//0x400B 000C
//System Tick Timer register map{"",(uint32_t *)UL,""},//
{"STCTRL",(uint32_t *)0xE000E010UL," System Timer Control and status register"},//0xE000 E010
{"STRELOAD",(uint32_t *)0xE000E014UL," System Timer Reload value register"},//0xE000 E014
{"STCURR",(uint32_t *)0xE000E018UL," System Timer Current value register"},//0xE000 E018
{"STCALIB",(uint32_t *)0xE000E01CUL," System Timer Calibration value register"},//0xE000 E01C
//PWM1 register map{"",(uint32_t *)UL,""},//
{"PWM1IR",(uint32_t *)0x40018000UL,"IR Interrupt Register."},//0x4001 8000
{"PWM1TCR",(uint32_t *)0x40018004UL,"TCR Timer Control Register."},//0x4001 8004
{"PWM1TC",(uint32_t *)0x40018008UL,"TC Timer Counter. "},//0x4001 8008
{"PWM1PR",(uint32_t *)0x4001800CUL,"PR Prescale Register. "},//0x4001 800C
{"PWM1PC",(uint32_t *)0x40018010UL,"PC Prescale Counter. "},//0x4001 8010
{"PWM1MCR",(uint32_t *)0x40018014UL,"MCR Match Control Register. "},//0x4001 8014
{"PWM1MR0",(uint32_t *)0x40018018UL,"MR0 Match Register 0. "},//0x4001 8018
{"PWM1MR1",(uint32_t *)0x4001801CUL,"MR1 Match Register 1. "},//0x4001 801C
{"PWM1MR2",(uint32_t *)0x40018020UL,"MR2 Match Register 2."},//0x4001 8020
{"PWM1MR3",(uint32_t *)0x40018024UL,"MR3 Match Register 3. "},//0x4001 8024
{"PWM1CCR",(uint32_t *)0x40018028UL,"CCR Capture Control Register."},//0x4001 8028
{"PWM1CR0",(uint32_t *)0x4001802CUL,"CR0 Capture Register 0."},//0x4001 802C
{"PWM1CR1",(uint32_t *)0x40018030UL,"CR1 Capture Register 1."},//0x4001 8030
{"PWM1CR2",(uint32_t *)0x40018034UL,"CR2 Capture Register 2."},//0x4001 8034
{"PWM1CR3",(uint32_t *)0x40018038UL,"CR3 Capture Register 3."},//0x4001 8038
{"PWM1MR4",(uint32_t *)0x40018040UL,"MR4 Match Register 4."},//0x4001 8040
{"PWM1MR5",(uint32_t *)0x40018044UL,"MR5 Match Register 5. "},//0x4001 8044
{"PWM1MR6",(uint32_t *)0x40018048UL,"MR6 Match Register 6."},//0x4001 8048
{"PWM1PCR",(uint32_t *)0x4001804CUL,"PCR PWM Control Register."},//0x4001 804C
{"PWM1LER",(uint32_t *)0x40018050UL,"LER Load Enable Register."},//0x4001 8050
{"PWM1CTCR",(uint32_t *)0x40018070UL,"CTCR Count Control Register."},//0x4001 8070
//Motor Control Pulse Width Modulator (MCPWM) register map.{"",(uint32_t *)UL,""},//
{"MCCON",(uint32_t *)0x400B8000UL,"PWM Control read address "},//0x400B 8000
{"MCCON_SET",(uint32_t *)0x400B8004UL,"PWM Control set address "},//0x400B 8004
{"MCCON_CLR",(uint32_t *)0x400B8008UL,"PWM Control clear address "},//0x400B 8008
{"MCCAPCON",(uint32_t *)0x400B800CUL,"Capture Control read address "},//0x400B 800C
{"MCCAPCON_SET",(uint32_t *)0x400B8010UL,"Capture Control set address "},//0x400B 8010
{"MCCAPCON_CLR",(uint32_t *)0x400B8014UL,"Event Control clear address "},//0x400B 8014
{"MCTC0",(uint32_t *)0x400B8018UL,"Timer Counter register, channel 0 "},//0x400B 8018
{"MCTC1",(uint32_t *)0x400B801CUL,"Timer Counter register, channel 1"},//0x400B 801C
{"MCTC2",(uint32_t *)0x400B8020UL,"Timer Counter register, channel 2"},//0x400B 8020
{"MCLIM0",(uint32_t *)0x400B8024UL,"Limit register, channel 0"},//0x400B 8024
{"MCLIM1",(uint32_t *)0x400B8028UL,"Limit register, channel 1"},//0x400B 8028
{"MCLIM2",(uint32_t *)0x400B802CUL,"Limit register, channel 2"},//0x400B 802C
{"MCMAT0",(uint32_t *)0x400B8030UL,"Match register, channel 0"},//0x400B 8030
{"MCMAT1",(uint32_t *)0x400B8034UL,"Match register, channel 1"},//0x400B 8034
{"MCMAT2",(uint32_t *)0x400B8038UL,"Match register, channel 2"},//0x400B 8038
{"MCDT",(uint32_t *)0x400B803CUL,"Dead time register"},//0x400B 803C
{"MCCP",(uint32_t *)0x400B8040UL,"Commutation Pattern register"},//0x400B 8040
{"MCCAP0",(uint32_t *)0x400B8044UL,"Capture register, channel 0 "},//0x400B 8044
{"MCCAP1",(uint32_t *)0x400B8048UL,"Capture register, channel 1"},//0x400B 8048
{"MCCAP2",(uint32_t *)0x400B804CUL,"Capture register, channel 2"},//0x400B 804C
{"MCINTEN",(uint32_t *)0x400B8050UL,"Interrupt Enable read address"},//0x400B 8050
{"MCINTEN_SET",(uint32_t *)0x400B8054UL,"Interrupt Enable set address"},//0x400B 8054
{"MCINTEN_CLR",(uint32_t *)0x400B8058UL,"Interrupt Enable clear address"},//0x400B 8058
{"MCCNTCON",(uint32_t *)0x400B805CUL,"Count Control read address"},//0x400B 805C
{"MCCNTCON_SET",(uint32_t *)0x400B8060UL,"Count Control set address"},//0x400B 8060
{"MCCNTCON_CLR",(uint32_t *)0x400B8064UL,"Count Control clear address"},//0x400B 8064
{"MCINTF",(uint32_t *)0x400B8068UL,"Interrupt flags read address"},//0x400B 8068
{"MCINTF_SET",(uint32_t *)0x400B806CUL,"Interrupt flags set address"},//0x400B 806C
{"MCINTF_CLR",(uint32_t *)0x400B8070UL,"Interrupt flags clear address"},//0x400B 8070
{"MCCAP_CLR",(uint32_t *)0x400B8074UL,"Capture clear address"},//0x400B 8074
//QEI Register summary{"",(uint32_t *)UL,""},//
//Control registers{"",(uint32_t *)UL,""},//
{"QEICON",(uint32_t *)0x400BC000UL,"Control register"},//0x400B C000
{"QEICONF",(uint32_t *)0x400BC008UL,"Configuration register"},//0x400B C008
{"QEISTAT",(uint32_t *)0x400BC004UL,"Encoder status register"},//0x400B C004
//Position, index, and timer registers{"",(uint32_t *)UL,""},//
{"QEIPOS",(uint32_t *)0x400BC00CUL,"Position register"},//0x400B C00C
{"QEIMAXPOS",(uint32_t *)0x400BC010UL,"Maximum position register"},//0x400B C010
{"CMPOS0",(uint32_t *)0x400BC014UL,"position compare register 0"},//0x400B C014
{"CMPOS1",(uint32_t *)0x400BC018UL,"position compare register 1"},//0x400B C018
{"CMPOS2",(uint32_t *)0x400BC01CUL,"position compare register 2"},//0x400B C01C
{"INXCNT",(uint32_t *)0x400BC020UL,"Index count register"},//0x400B C020
{"INXCMP",(uint32_t *)0x400BC024UL,"Index compare register"},//0x400B C024
{"QEILOAD",(uint32_t *)0x400BC028UL,"Velocity timer reload register"},//0x400B C028
{"QEITIME",(uint32_t *)0x400BC02CUL,"Velocity timer register"},//0x400B C02C
{"QEIVEL",(uint32_t *)0x400BC030UL,"Velocity counter register"},//0x400B C030
{"QEICAP",(uint32_t *)0x400BC034UL,"Velocity capture register"},//0x400B C034
{"VELCOMP",(uint32_t *)0x400BC038UL,"Velocity compare register"},//0x400B C038
{"FILTER",(uint32_t *)0x400BC03CUL,"Digital filter register"},//0x400B C03C
//Interrupt registers{"",(uint32_t *)UL,""},//
{"QEIINTSTAT",(uint32_t *)0x400BCFE0UL,"Interrupt status register"},//0x400B CFE0
{"QEISET",(uint32_t *)0x400BCFECUL,"Interrupt status set register"},//0x400B CFEC
{"QEICLR",(uint32_t *)0x400BCFE8UL,"Interrupt status clear register"},//0x400B CFE8
{"QEIIE",(uint32_t *)0x400BCFE4UL,"Interrupt enable register"},//0x400B CFE4
{"QEIIES",(uint32_t *)0x400BCFDCUL,"Interrupt enable set register"},//0x400B CFDC
{"QEIIEC",(uint32_t *)0x400BCFD8UL,"Interrupt enable clear register"},//0x400B CFD8
//Real-Time Clock register map{"",(uint32_t *)UL,""},//
//Miscellaneous registers{"",(uint32_t *)UL,""},//
{"ILR",(uint32_t *)0x40024000UL,"Interrupt Location Register"},//0x4002 4000
{"CCR",(uint32_t *)0x40024008UL,"Clock Control Register"},//0x4002 4008
{"CIIR",(uint32_t *)0x4002400CUL,"Counter Increment Interrupt Register"},//0x4002 400C
{"AMR",(uint32_t *)0x40024010UL,"Alarm Mask Register"},//0x4002 4010
{"RTC_AUX",(uint32_t *)0x4002405CUL,"RTC Auxiliary control register"},//0x4002 405C
{"RTC_AUXEN",(uint32_t *)0x40024058UL,"RTC Auxiliary Enable register"},//0x4002 4058
//Consolidated time registers{"",(uint32_t *)UL,""},//
{"CTIME0",(uint32_t *)0x40024014UL,"Consolidated Time Register 0"},//0x4002 4014
{"CTIME1",(uint32_t *)0x40024018UL,"Consolidated Time Register 1"},//0x4002 4018
{"CTIME2",(uint32_t *)0x4002401CUL,"Consolidated Time Register 2"},//0x4002 401C
//Time counter registers{"",(uint32_t *)UL,""},//
{"SEC",(uint32_t *)0x40024020UL,"Seconds Counter"},//0x4002 4020
{"MIN",(uint32_t *)0x40024024UL,"Minutes Register"},//0x4002 4024
{"HOUR",(uint32_t *)0x40024028UL,"Hours Register"},//0x4002 4028
{"DOM",(uint32_t *)0x4002402CUL,"Day of Month Register"},//0x4002 402C
{"DOW",(uint32_t *)0x40024030UL,"Day of Week Register"},//0x4002 4030
{"DOY",(uint32_t *)0x40024034UL,"Day of Year Register"},//0x4002 4034
{"MONTH",(uint32_t *)0x40024038UL,"Months Register"},//0x4002 4038
{"YEAR",(uint32_t *)0x4002403CUL,"Years Register"},//0x4002 403C
{"CALIBRATION",(uint32_t *)0x40024040UL,"Calibration Value Register"},//0x4002 4040
//General purpose registers{"",(uint32_t *)UL,""},//
{"GPREG0",(uint32_t *)0x40024044UL,"General Purpose Register 0"},//0x4002 4044
{"GPREG1",(uint32_t *)0x40024048UL,"General Purpose Register 1"},//0x4002 4048
{"GPREG2",(uint32_t *)0x4002404CUL,"General Purpose Register 2"},//0x4002 404C
{"GPREG3",(uint32_t *)0x40024050UL,"General Purpose Register 3"},//0x4002 4050
{"GPREG4",(uint32_t *)0x40024054UL,"General Purpose Register 4"},//0x4002 4054
//Alarm register group{"",(uint32_t *)UL,""},//
{"ALSEC",(uint32_t *)0x40024060UL,"Alarm value for Seconds"},//0x4002 4060
{"ALMIN",(uint32_t *)0x40024064UL,"Alarm value for Minutes"},//0x4002 4064
{"ALHOUR",(uint32_t *)0x40024068UL,"Alarm value for Hours"},//0x4002 4068
{"ALDOM",(uint32_t *)0x4002406CUL,"Alarm value for Day of Month"},//0x4002 406C
{"ALDOW",(uint32_t *)0x40024070UL,"Alarm value for Day of Week"},//0x4002 4070
{"ALDOY",(uint32_t *)0x40024074UL,"Alarm value for Day of Year"},//0x4002 4074
{"ALMON",(uint32_t *)0x40024078UL,"Alarm value for Months"},//0x4002 4078
{"ALYEAR",(uint32_t *)0x4002407CUL,"Alarm value for Year"},//0x4002 407C
//Watchdog register map{"",(uint32_t *)UL,""},//
{"WDMOD",(uint32_t *)0x40000000UL,"Watchdog mode register."},//0x4000 0000
{"WDTC",(uint32_t *)0x40000004UL,"Watchdog timer constant register."},//0x4000 0004
{"WDFEED",(uint32_t *)0x40000008UL,"Watchdog feed sequence register."},//0x4000 0008
{"WDTV",(uint32_t *)0x4000000CUL,"Watchdog timer value register."},//0x4000 000C
{"WDCLKSEL",(uint32_t *)0x40000010UL,"Watchdog clock source selection register."},//0x4000 0010
//ADC registers{"",(uint32_t *)UL,""},//
{"AD0CR -",(uint32_t *)0x40034000UL,"A/D Control Register."},//0x4003 4000
{"AD0GDR -",(uint32_t *)0x40034004UL,"A/D Global Data Register."},//0x4003 4004
{"AD0INTEN -",(uint32_t *)0x4003400CUL,"A/D Interrupt Enable Register."},//0x4003 400C
{"AD0DR0 -",(uint32_t *)0x40034010UL,"A/D Channel 0 Data Register."},//0x4003 4010
{"AD0DR1 -",(uint32_t *)0x40034014UL,"A/D Channel 1 Data Register."},//0x4003 4014
{"AD0DR2 -",(uint32_t *)0x40034018UL,"A/D Channel 2 Data Register."},//0x4003 4018
{"AD0DR3 -",(uint32_t *)0x4003401CUL,"A/D Channel 3 Data Register."},//0x4003 401C
{"AD0DR4 -",(uint32_t *)0x40034020UL,"A/D Channel 4 Data Register."},//0x4003 4020
{"AD0DR5 -",(uint32_t *)0x40034024UL,"A/D Channel 5 Data Register."},//0x4003 4024
{"AD0DR6 -",(uint32_t *)0x40034028UL,"A/D Channel 6 Data Register."},//0x4003 4028
{"AD0DR7 -",(uint32_t *)0x4003402CUL,"A/D Channel 7 Data Register."},//0x4003 402C
{"AD0STAT -",(uint32_t *)0x40034030UL,"A/D Status Register."},//0x4003 4030
{"AD0TRM -",(uint32_t *)0x40034034UL,"ADC trim register."},//0x4003 4034
//DAC registers{"",(uint32_t *)UL,""},//
{"DACR",(uint32_t *)0x4008C000UL,"D/A Converter Register."},//0x4008 C000
{"DACCTRL",(uint32_t *)0x4008C004UL,"DAC Control register."},//0x4008 C004
{"DACCNTVAL",(uint32_t *)0x4008C008UL,"DAC Counter Value register."},//0x4008 C008
//GPDMA register map{"",(uint32_t *)UL,""},//
//General registers{"",(uint32_t *)UL,""},//
{"DMACIntStat",(uint32_t *)0x50004000UL,"DMA Interrupt Status Register"},//0x5000 4000
{"DMACIntTCStat",(uint32_t *)0x50004004UL,"DMA Interrupt Terminal Count Request Status Register"},//0x5000 4004
{"DMACIntTCClear",(uint32_t *)0x50004008UL,"DMA Interrupt Terminal Count Request Clear Register"},//0x5000 4008
{"DMACIntErrStat",(uint32_t *)0x5000400CUL,"DMA Interrupt Error Status Register"},//0x5000 400C
{"DMACIntErrClr",(uint32_t *)0x50004010UL,"DMA Interrupt Error Clear Register"},//0x5000 4010
{"DMACRawIntTCStat",(uint32_t *)0x50004014UL,"DMA Raw Interrupt Terminal Count Status Register"},//0x5000 4014
{"DMACRawIntErrStat",(uint32_t *)0x50004018UL,"DMA Raw Error Interrupt Status Register"},//0x5000 4018
{"DMACEnbldChns",(uint32_t *)0x5000401CUL,"DMA Enabled Channel Register"},//0x5000 401C
{"DMACSoftBReq",(uint32_t *)0x50004020UL,"DMA Software Burst Request Register"},//0x5000 4020
{"DMACSoftSReq",(uint32_t *)0x50004024UL,"DMA Software Single Request Register"},//0x5000 4024
{"DMACSoftLBReq",(uint32_t *)0x50004028UL,"DMA Software Last Burst Request Register"},//0x5000 4028
{"DMACSoftLSReq",(uint32_t *)0x5000402CUL,"DMA Software Last Single Request Register"},//0x5000 402C
{"DMACConfig",(uint32_t *)0x50004030UL,"DMA Configuration Register"},//0x5000 4030
{"DMACSync",(uint32_t *)0x50004034UL,"DMA Synchronization Register"},//0x5000 4034
{"DMAREQSEL",(uint32_t *)0x400FC1C4UL,"Selects between UART and timer DMA requests on channels 8 through 15"},//0x400F C1C4
//Channel 0 registers{"",(uint32_t *)UL,""},//
{"DMACC0SrcAddr",(uint32_t *)0x50004100UL,"DMA Channel 0 Source Address Register"},//0x5000 4100
{"DMACC0DestAddr",(uint32_t *)0x50004104UL,"DMA Channel 0 Destination Address Register"},//0x5000 4104
{"DMACC0LLI",(uint32_t *)0x50004108UL,"DMA Channel 0 Linked List Item Register"},//0x5000 4108
{"DMACC0Control",(uint32_t *)0x5000410CUL,"DMA Channel 0 Control Register"},//0x5000 410C
{"DMACC0Config",(uint32_t *)0x50004110UL,"DMA Channel 0 Configuration Register"},//0x5000 4110
//Channel 1 registers{"",(uint32_t *)UL,""},//
{"DMACC1SrcAddr",(uint32_t *)0x50004120UL,"DMA Channel 1 Source Address Register"},//0x5000 4120
{"DMACC1DestAddr",(uint32_t *)0x50004124UL,"DMA Channel 1 Destination Address Register"},//0x5000 4124
{"DMACC1LLI",(uint32_t *)0x50004128UL,"DMA Channel 1 Linked List Item Register"},//0x5000 4128
{"DMACC1Control",(uint32_t *)0x5000412CUL,"DMA Channel 1 Control Register"},//0x5000 412C
{"DMACC1Config",(uint32_t *)0x50004130UL,"DMA Channel 1 Configuration Register"},//0x5000 4130
//Channel 2 registers{"",(uint32_t *)UL,""},//
{"DMACC2SrcAddr",(uint32_t *)0x50004140UL,"DMA Channel 2 Source Address Register"},//0x5000 4140
{"DMACC2DestAddr",(uint32_t *)0x50004144UL,"DMA Channel 2 Destination Address Register"},//0x5000 4144
{"DMACC2LLI",(uint32_t *)0x50004148UL,"DMA Channel 2 Linked List Item Register"},//0x5000 4148
{"DMACC2Control",(uint32_t *)0x5000414CUL,"DMA Channel 2 Control Register"},//0x5000 414C
//GPDMA register map{"",(uint32_t *)UL,""},//
{"DMACC2Config",(uint32_t *)0x50004150UL,"DMA Channel 2 Configuration Register"},//0x5000 4150
//Channel 3 registers{"",(uint32_t *)UL,""},//
{"DMACC3SrcAddr",(uint32_t *)0x50004160UL,"DMA Channel 3 Source Address Register"},//0x5000 4160
{"DMACC3DestAddr",(uint32_t *)0x50004164UL,"DMA Channel 3 Destination Address Register"},//0x5000 4164
{"DMACC3LLI",(uint32_t *)0x50004168UL,"DMA Channel 3 Linked List Item Register"},//0x5000 4168
{"DMACC3Control",(uint32_t *)0x5000416CUL,"DMA Channel 3 Control Register"},//0x5000 416C
{"DMACC3Config",(uint32_t *)0x50004170UL,"DMA Channel 3 Configuration Register"},//0x5000 4170
//Channel 4 registers{"",(uint32_t *)UL,""},//
{"DMACC4SrcAddr",(uint32_t *)0x50004180UL,"DMA Channel 4 Source Address Register"},//0x5000 4180
{"DMACC4DestAddr",(uint32_t *)0x50004184UL,"DMA Channel 4 Destination Address Register"},//0x5000 4184
{"DMACC4LLI",(uint32_t *)0x50004188UL,"DMA Channel 4 Linked List Item Register"},//0x5000 4188
{"DMACC4Control",(uint32_t *)0x5000418CUL,"DMA Channel 4 Control Register"},//0x5000 418C
{"DMACC4Config",(uint32_t *)0x50004190UL,"DMA Channel 4 Configuration Register"},//0x5000 4190
//Channel 5 registers{"",(uint32_t *)UL,""},//
{"DMACC5SrcAddr",(uint32_t *)0x500041A0UL,"DMA Channel 5 Source Address Register"},//0x5000 41A0
{"DMACC5DestAddr",(uint32_t *)0x500041A4UL,"DMA Channel 5 Destination Address Register"},//0x5000 41A4
{"DMACC5LLI",(uint32_t *)0x500041A8UL,"DMA Channel 5 Linked List Item Register"},//0x5000 41A8
{"DMACC5Control",(uint32_t *)0x500041ACUL,"DMA Channel 5 Control Register"},//0x5000 41AC
{"DMACC5Config",(uint32_t *)0x500041B0UL,"DMA Channel 5 Configuration Register"},//0x5000 41B0
//Channel 6 registers{"",(uint32_t *)UL,""},//
{"DMACC6SrcAddr",(uint32_t *)0x500041C0UL,"DMA Channel 6 Source Address Register"},//0x5000 41C0
{"DMACC6DestAddr",(uint32_t *)0x500041C4UL,"DMA Channel 6 Destination Address Register"},//0x5000 41C4
{"DMACC6LLI",(uint32_t *)0x500041C8UL,"DMA Channel 6 Linked List Item Register"},//0x5000 41C8
{"DMACC6Control",(uint32_t *)0x500041CCUL,"DMA Channel 6 Control Register"},//0x5000 41CC
{"DMACC6Config",(uint32_t *)0x500041D0UL,"DMA Channel 6 Configuration Register"},//0x5000 41D0
//Channel 7 registers{"",(uint32_t *)UL,""},//
{"DMACC7SrcAddr",(uint32_t *)0x500041E0UL,"DMA Channel 7 Source Address Register"},//0x5000 41E0
{"DMACC7DestAddr",(uint32_t *)0x500041E4UL,"DMA Channel 7 Destination Address Register"},//0x5000 41E4
{"DMACC7LLI",(uint32_t *)0x500041E8UL,"DMA Channel 7 Linked List Item Register"},//0x5000 41E8
{"DMACC7Control",(uint32_t *)0x500041ECUL,"DMA Channel 7 Control Register"},//0x5000 41EC
{"DMACC7Config",(uint32_t *)0x500041F0UL,"DMA Channel 7 Configuration Register"},//0x5000 41F0
//FMC{"",(uint32_t *)UL,""},//
{"FMSSTART",(uint32_t *)0x40084020UL,"Signature start address register "},//0x4008 4020
{"FMSSTOP",(uint32_t *)0x40084024UL,"Signature stop-address register"},//0x4008 4024
{"FMSW0",(uint32_t *)0x4008402CUL,"128-bit signature Word 0"},//0x4008 402C
{"FMSW1",(uint32_t *)0x40084030UL,"128-bit signature Word 1"},//0x4008 4030
{"FMSW2",(uint32_t *)0x40084034UL,"128-bit signature Word 2"},//0x4008 4034
{"FMSW3",(uint32_t *)0x40084038UL,"128-bit signature Word 3"},//0x4008 4038
{"FMSTAT",(uint32_t *)0x40084FE0UL,"Signature generation status register"},//0x4008 4FE0
{"FMSTATCLR",(uint32_t *)0x40084FE8UL,"Signature generation status clear register"}//0x4008 4FE8
} ;
#endif

