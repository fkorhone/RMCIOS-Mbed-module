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

#ifndef mbed_pin_from_name_h
#define mbed_pin_from_name_h

#include <mbed.h>

struct str_pin_pair
{
    const char *name ;
    PinName pin ;
} ;

#define NAME_ENUM_PAIR(PIN) {#PIN,PIN}

#ifdef TARGET_LPC1768
#include "lpc1768_pin_strings.h"
#endif

#ifdef TARGET_K64F
#include "frdmk64f_pin_strings.h"
#endif

#ifdef TARGET_KL25Z
#include "frdmkl25z_pin_strings.h"
#endif

#ifdef TARGET_DISCO_F746NG
#include "disco_f746ng_pin_strings.h"
#endif

//#ifdef TARGET_

PinName mbed_pin_from_name(const char *name)
{
    int i ,j;
    int namelen=strlen(name) ;
    int names=sizeof(pin_pairs)/sizeof(struct str_pin_pair) ; // Get number of pinnames in the system
    for(i=0; i<names ; i++)
    {
        for(j=0;j<namelen;j++) // check char by char 
        {
            if(name[j]!=pin_pairs[i].name[j] || name[j]==0 || pin_pairs[i].name[j]==0) break ;
        }
        if(j==namelen && name[j]==0 ) return pin_pairs[i].pin ; // MATCH -> return the desired pin
    }
    return NC ;
}

#endif

