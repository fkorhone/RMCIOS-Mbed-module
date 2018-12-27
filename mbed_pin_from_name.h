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
