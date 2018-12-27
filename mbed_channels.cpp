/* 
RMCIOS - Reactive Multipurpose Control Input Output System
Copyright (c) 2018 Frans Korhonen

RMCIOS was originally developed at Institute for Atmospheric 
and Earth System Research / Physics, Faculty of Science, 
University of Helsinki, Finland

Assistance, experience and feedback from following persons have been 
critical for development of RMCIOS: Erkki Siivola, Juha Kangasluoma, 
Lauri Ahonen, Ella Häkkinen, Pasi Aalto, Joonas Enroth, Runlong Cai, 
Markku Kulmala and Tuukka Petäjä.

This file is part of RMCIOS. This notice was encoded using utf-8.

RMCIOS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RMCIOS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public Licenses
along with RMCIOS.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef mbed_channels_h
#define mbed_channels_h

#include "mbed.h"
#include "rtos.h"
#include "RMCIOS-functions.h"
#include "mbed_pin_from_name.h"
#include "shared_resource.h"

//#include "SDFileSystem.h"

extern const struct context_rmcios *module_context ;

////////////////////////////////////////////////////////////////////
// AD channels																		//
////////////////////////////////////////////////////////////////////

//! adc data
struct ad_data {
    AnalogIn *adc ;
    float value ;
    int mux_channel ;
    int samples ;
} ;

FILE *ad_dbg=NULL ; // Debug stream

void ad_class_func(struct ad_data *t, 
                   const struct context_rmcios *context, 
                   int id, 
                   enum function_rmcios function,
                   enum type_rmcios paramtype,
                   union param_rmcios returnv, 
                   int num_params,
                   const union param_rmcios param)
{
 switch(function) 
 {
    case help_rmcios:
       return_string(context, paramtype, returnv,
             "Analog input channel help\n\r"
             " create ai newname pin # create analog input to specified pin.\n\r"
             " setup ai samples(16) # set ammount of samples to average\n\r"
             " write ad1 # do single ad conversion.\n\r"
             " read ad1 # read last conversion value.\n\r"
             " link channel # write conversion results when done to channel.\n\r"
             ) ;
       break ;
    case create_rmcios:
       if(num_params<2) break ;
       else {
          char pin_name[20] ;
          PinName pin ;
          param_to_string(context, paramtype, param,1,
                          sizeof(pin_name),pin_name) ;

          pin=mbed_pin_from_name(pin_name) ;
          if(pin!=NC) {
             // allocate new ad data
             t= new ad_data ; 
             if(t==NULL) break ;

             // create new Analog In object
             t->adc= new AnalogIn(pin) ; 
             t->value=NAN ;
             t->mux_channel=0 ;
             t->samples=16 ;

             // create channel
             create_channel_param(context, paramtype,param,0, 
                                  (class_rmcios)ad_class_func , t) ; 
          } else {
             printf("Could not create analog input: unknown pin.\r\n") ;
          }
       }
       break ;
    case setup_rmcios:
       if(num_params<1) break ;
       t->samples=param_to_int(context, paramtype,param,0) ;
       break ;
    case write_rmcios:
       if(t==NULL) break ;
       else {
          float sum=0 ;
          int i ;
          for(i=0 ; i<t->samples ; i++) sum+=(*t->adc) ;
          t->value=sum/t->samples ;
          write_f(context, linked_channels(context,id),t->value) ;
       }
       break ;
    case read_rmcios:
       if(t==NULL) break ;
       if(returnv.p==NULL) break;
       return_float(context, paramtype,returnv,t->value) ;
       break ;
 }
}

///////////////////////////////////////////////////////////////////////
// Pwm channels																		//
///////////////////////////////////////////////////////////////////////
struct pwm_data {
    pwm_data(const PinName pin) : pwm(pin), maxclamp(1.0), minclamp(0.0) {} ;
    PwmOut pwm ;
    float maxclamp ;
    float minclamp ;
} ;

void pwm_class_func(struct pwm_data *t,
                    const struct context_rmcios *context, 
                    int id, 
                    enum function_rmcios function, 
                    enum type_rmcios paramtype, 
                    union param_rmcios returnv, 
                    int num_params,
                    const union param_rmcios param)
{
 switch(function) 
 {
    case help_rmcios:
       return_string(context, paramtype, returnv,
             "PWM channel help\r\n"
             " create pwm newname pin\r\n"
             " setup newname frequency | maxclamp(1) | minclamp(0)\r\n"
             "    # set pwm channel frequency and clamping limits\r\n"
             " write pwm duty_cycle #(0..1)\r\n"
             ) ;
       break ;

    case create_rmcios:
       if(num_params<1) break ;
       else {
          char pin_name[20] ;
          PinName pin ;
          param_to_string(context, paramtype, param, 1, 
                          sizeof(pin_name), pin_name) ;
          pin=mbed_pin_from_name(pin_name) ;
          if(pin!=NC) {
             t= new pwm_data(pin) ;
             create_channel_param(context, paramtype, param, 0, 
                                  (class_rmcios)pwm_class_func, t) ; 
          }
       }
       break ;

    case setup_rmcios:
       if(num_params<1) break ;
       if(t==NULL) break ;
       t->pwm.period(1.0f / param_to_float(context, paramtype, param, 0)) ;
       if(num_params<2) break ;
       t->maxclamp = param_to_float(context, paramtype, param, 1) ;
       if(num_params<3) break ;
       t->minclamp = param_to_float(context, paramtype, param, 2) ;
       break ;

    case write_rmcios:
       if(t==NULL) break ;
       if(num_params<1) break ;
       else {
          float value = param_to_float(context, paramtype, param, 0) ;
          if(value > t->maxclamp ) value=t->maxclamp ;
          if(value < t->minclamp ) value=t->minclamp ;
          t->pwm = value  ;
       }
       break ;
    case read_rmcios:
       if(t==NULL) break ;
       return_float(context, paramtype, returnv, t->pwm.read()) ;
       break ;
 }
}


///////////////////////////////////////////////////////////////////////
// Digital Out channel																//
///////////////////////////////////////////////////////////////////////
void do_class_func(DigitalOut *t,
                   const struct context_rmcios *context, 
                   int id, 
                   enum function_rmcios function, 
                   enum type_rmcios paramtype,
                   union param_rmcios returnv, 
                   int num_params,
                   const union param_rmcios param)
{
    switch(function) {
        case help_rmcios:
            return_string(context, paramtype,returnv,
            "Digital out channel\r\n"
            " create do newname pin\r\n"
            " write newname state #(0/1)\r\n"
            " read newname # read state (0/1)\r\n"
            );
            break;

        case create_rmcios:
            if(num_params<1) break;
            else {
                char pin_name[20] ;
                PinName pin ;
                param_to_string(context, paramtype, param,1,
                                sizeof(pin_name),pin_name);
                pin=mbed_pin_from_name(pin_name) ;
                if(pin!=NC) {
                    t= new DigitalOut(pin) ;
                    create_channel_param(context, paramtype,param,0, 
                                         (class_rmcios)do_class_func ,t) ; 
                }
            }
            break ;

        case write_rmcios:
            if(t==NULL) break ;
            if(num_params<1) break ;
            else {
                *t = param_to_int(context, paramtype,param, 0) ;
            }
            break ;
        case read_rmcios:
            if(t==NULL) break ;
            return_int(context, paramtype, returnv, *t ) ;
            break ;
    }
}


//////////////////////////////////////////////////////////////////////
// RTC timer
//////////////////////////////////////////////////////////////////////
Queue<void,5> rtc_execute_queue ;
FILE *rtc_timer_dbg=NULL ; // Debug stream

void executer_thread(void const *data) 
{
    if(data==NULL) return ;

    int channel;
    write_i(module_context, channel_enum(module_context, "memmon"),
            (int)&channel) ;
    
    Queue<void,5> *p_queue=((Queue<void,5> *)data) ;
    while(1) {
        osEvent evt = p_queue->get() ;
        if (evt.status == osEventMessage) {
            channel = ((int) evt.value.p);

            // execute channel (empty write)
            write_iv(module_context, channel, 0, NULL) ; 
        }
    }
}

struct rtc_timer_data {
    int offset ;
    int period ;
    time_t prevtime ;
    int linked_channel ;
    rtc_timer_data *nextimer ; 
    int wait ;
} ;

Ticker rtc_ticker ;
struct rtc_timer_data *first_timer=NULL;

void rtc_ticker_func(void) 
{
    time_t seconds ;

    seconds=time(NULL) ; // time now
    struct rtc_timer_data *t=first_timer ;

    while(t!=NULL) {
        if(t->period==0) return ; // timer not active

        // Time has changed -> change prevtime to lastest possible:
        if(t->prevtime > seconds || (seconds-t->prevtime) >= t->period*2 ) {
            t->prevtime= seconds 
            + (t->offset % t->period) 
            - (seconds % t->period) ;
        }
        if(seconds >= (t->prevtime+t->period) ) { 
            t->wait=0 ;
            rtc_execute_queue.put( ((void*)t->linked_channel) ) ; 
            
            // Update calculated current trigger time
            t->prevtime= seconds + (t->offset % t->period) 
                       - (seconds % t->period) ;

        }
        t=t->nextimer ;
    }
}
//RtosTimer rtc_ticker(rtc_ticker_func,osTimerPeriodic,NULL) ;

void rtc_timer_class_func(struct rtc_timer_data *t,
                          const struct context_rmcios *context, 
                          int id, enum function_rmcios function,
                          enum type_rmcios paramtype,
                          union param_rmcios returnv, 
                          int num_params,
                          const union param_rmcios param)
{
 switch(function) 
 {
    case help_rmcios:
       return_string(context, paramtype,returnv,
             "rtc timer channel help\r\n"
             "perioidic realtime clock timer\r\n"
             " create rtc_timer name\r\n"
             " setup rtc_timer period \r\n"
             " setup rtc_timer period day month year hour minute second\r\n"
             " link rtc_timer execute_channel\r\n"
             ) ;
       break ;

    case create_rmcios:

       if(num_params<1) break ;

       t= new struct rtc_timer_data ; // allocate new data
       if(t==NULL) printf("Could not create rtc timer!\r\n") ;

       // Default values:
       t->offset=0 ;
       t->period=0 ;
       t->prevtime=0 ;
       t->nextimer=NULL ; 

       id= create_channel_param(context, paramtype,param, 0, 
                                (class_rmcios)rtc_timer_class_func, t); 
       t->linked_channel=linked_channels(context,id) ;

       // Attach timer to executing timers:
       if(first_timer==NULL) first_timer=t ;
       else {
          struct rtc_timer_data *p_iter=first_timer;
          while(p_iter->nextimer!=NULL) {
             p_iter=p_iter->nextimer ;
          }
          p_iter->nextimer=t ; 
       }
       break ;

    case setup_rmcios:
       if(t==NULL) break ;
       {
          time_t seconds ;
          seconds=time(NULL) ;
          if(num_params<1) break ; 
          {

             time_t sync_time=0 ;
             t->period= param_to_int(context, paramtype,param, 0 ) ;
             t->offset= sync_time % t->period ;
          }
          t->prevtime= seconds + (t->offset % t->period) 
                               - (seconds % t->period) ;

          if(num_params<7) break ;
          else {
             struct tm newtime ;
             time_t sync_time ;
             // day of the month
             newtime.tm_mday=param_to_int(context, paramtype, param, 1); 
             // months since January
             newtime.tm_mon=param_to_int(context, paramtype, param, 2); 
             // years since 1900
             newtime.tm_year=param_to_int(context, paramtype, param, 3)-1900 ; 
             newtime.tm_hour=param_to_int(context, paramtype, param, 4 ) ;
             newtime.tm_min=param_to_int(context, paramtype, param, 5 )  ;
             newtime.tm_sec=param_to_int(context, paramtype, param, 6 )  ;
             newtime.tm_isdst=0  ;
             sync_time=mktime(&newtime) ;
             t->offset= sync_time % t->period ;
          }

          t->prevtime= seconds + (t->offset % t->period) 
                               - (seconds % t->period);
       }
       break ;

    case read_rmcios:
       if(t==NULL) break ;
       t->wait=1 ;
       while(t->wait!=0) Thread::wait(50) ;
       break ;

    default:
       break ;
 }
}

///////////////////////////////////////////////////////////
// timer																	//
///////////////////////////////////////////////////////////
FILE *timer_dbg=NULL ; // Debug stream

struct timer_data {
    RtosTimer *_timer ;
    int linked_channel ;
    float perioid ;
    unsigned int looping ;
} ;

void timer_func(const void *data)
{
    struct timer_data *p_timer= ((struct timer_data *)data) ;
    if(p_timer==NULL) return ;
    module_context->run_channel(module_context, p_timer->linked_channel, 
                                write_rmcios, int_rmcios, 
                                (union param_rmcios){0}, 0, 
                                (union param_rmcios){0}) ;


    if(p_timer->looping==0) {
        p_timer->_timer->stop() ; // Stop if timer not looping
    }
}

void timer_class_func(struct timer_data *t,
                      const struct context_rmcios *context, 
                      int id, 
                      enum function_rmcios function, 
                      enum type_rmcios paramtype,
                      union param_rmcios returnv, 
                      int num_params,
                      const union param_rmcios param)
{
    switch(function) {
        case help_rmcios:
            return_string(context, paramtype, returnv,
            "timer channel help\r\n"
            " create timer channel_name # create timer channel\r\n"
            " setup timer period \r\n"
            " write timer period # set timer time and run timer.\r\n"
            " link timer link_channel # link timer called on match.\r\n"
            " reset timer # reset timer\r\n"
            ) ;
            break ;

        case create_rmcios:
            if(num_params<1) break ;
            // allocate new data
            t=  new struct timer_data ; 
            if(t==NULL) break ;

            //default values :
            t->looping=1 ;
            t->_timer= new RtosTimer(timer_func,osTimerPeriodic,(void *)t);

            id=create_channel_param(context, paramtype,param, 0, 
                                    (class_rmcios)timer_class_func, t) ;
            
            t->linked_channel=linked_channels(context,id) ;
            break ;

        case setup_rmcios:
            if(t==NULL) break ;
            if(num_params<1) break ;
            t->perioid=param_to_float(context, paramtype, param, 0)  ;

            if(num_params>1){
               t->looping=param_to_int(context, paramtype, param, 1);
            }
            if(t->looping) {
                int period=t->perioid*1000 ;
                return_int(context, paramtype, returnv, period) ;
                t->_timer->stop()  ;
                t->_timer->start( period ) ;
            }
            break;

        case write_rmcios:
            if(t==NULL) break ;
            if(num_params>0) { // reset
                t->perioid=param_to_float(context, paramtype, param, 0)  ;
            }
            t->_timer->stop() ;
            t->_timer->start( ((int)( (t->perioid)*1000) ) ) ;
            break ;

        default:
            break ;
    }
}

/////////////////////////////////////////////////////////////////
// static channel for medium wait times (ms resolution 32 bit) //
/////////////////////////////////////////////////////////////////
void wait_class_func(void *data,
                     const struct context_rmcios *context, 
                     int id, enum function_rmcios function,
                     enum type_rmcios paramtype,
                     union param_rmcios returnv, 
                     int num_params,
                     const union param_rmcios param)
{
    float wait_time;
    switch(function) {
        case help_rmcios:
            return_string(context, paramtype,returnv,
            "wait channel help\r\n"
            " write wait time # waits time (s)\r\n"
            ) ;
            break;

        case write_rmcios:
            if(num_params<1) break ;
            wait_time= param_to_float(context, paramtype,param,0) ;
            // wait in ms
            Thread::wait( wait_time*1000 ) ; 
            break ;
    }
}

/////////////////////////////////////////////////////////
// Clock to get elapsed time                           //
/////////////////////////////////////////////////////////
void clock_class_func(void *data, 
                      const struct context_rmcios *context, 
                      int id, 
                      enum function_rmcios function,
                      enum type_rmcios paramtype,
                      union param_rmcios returnv, 
                      int num_params,
                      const union param_rmcios param)
{
 Timer *t= (Timer *)data ;
 switch(function) 
 {
    case help_rmcios:
       return_string(context, paramtype,returnv,
             "clock channel help\r\n"
             " create clock newname \r\n"
             " read newname #read elapsed time (s)\r\n"
             " write newname # read and set time=0 \r\n"
             ) ;
       break ;

    case create_rmcios :
       if(num_params<1) break ;
       t= new Timer ;
       if(t==NULL) break ;
       create_channel_param(context, paramtype,param, 0, 
                            (class_rmcios)clock_class_func, t) ; 
       t->start() ;
       break ;

    case read_rmcios:
       if(t==NULL) break ;
       return_float(context, paramtype,returnv,t->read() ) ;
       break ;

    case write_rmcios:
       if(t==NULL) break ;
       return_float(context, paramtype, returnv, t->read() ) ;
       t->reset();
       break ;

    default:
       break ;
 }
}

///////////////////////////////////////////////////////////////////
// RTC - Real time clock
///////////////////////////////////////////////////////////////////

// Timezone offset(hours) from UTC
int timezone_offset=0 ; 
void rtc_class_func(void *data, 
                    const struct context_rmcios *context, 
                    int id, 
                    enum function_rmcios function,
                    enum type_rmcios paramtype,
                    union param_rmcios returnv, 
                    int num_params,
                    :const union param_rmcios param)
{
 time_t seconds=time(NULL) ;
 switch(function) 
 {
    case help_rmcios:
       return_string(context, paramtype,returnv,
             "rtc channel help\r\n"
             "rtc - realtime clock\r\n"
             " setup rtc timezone_offset(hours)\r\n" 
             "      | year month day hour minute second\r\n"
             " read rtc \r\n"
             "      #read UTC time in unix time\r\n"
             " write rtc unixtime\r\n"
             "      #set UTC time in unix time\r\n"
             ) ;
       break ;

    case setup_rmcios :

       if(num_params<1)  break ;
       timezone_offset=param_to_int(context, paramtype,param, 0 )*60*60 ;

       if(num_params<6)  break ;
       {
          printf("setting rtc time\r\n") ;
          struct tm newtime ;
          // years since 1900
          newtime.tm_year=param_to_int(context, paramtype,param, 1 )-1900 ; 
          // months since January -1
          newtime.tm_mon=param_to_int(context, paramtype,param, 2 )-1  ; 
          // day of the month
          newtime.tm_mday=param_to_int(context, paramtype,param, 3 ) ; 
          newtime.tm_hour=param_to_int(context, paramtype,param, 4 ) ;
          newtime.tm_min=param_to_int(context, paramtype,param, 5 )  ;
          newtime.tm_sec=param_to_int(context, paramtype,param, 6 )  ;
          newtime.tm_isdst=0  ;
          // set new time
          set_time( mktime( &newtime )-timezone_offset ) ; 
       }
       break ;

    case read_rmcios :
       return_int(context, paramtype,returnv,seconds) ;
       break ;

    case write_rmcios :
       if(num_params<1) break ;
       set_time( param_to_int(context, paramtype, param, 0 ) ) ;
       break ;
 }
}


struct rtc_str_data {
    int linked_channel ;
    char rtc_str_format[21] ;
    int second_decimals ;
} default_rtc_str_data= {0,"%Y-%m-%dT%H:%M:%S%z",0} ;

void rtc_str_class_func(struct rtc_str_data *data, 
                        const struct context_rmcios *context, 
                        int id, 
                        enum function_rmcios function,
                        enum type_rmcios paramtype,
                        union param_rmcios returnv, 
                        int num_params,
                        const union param_rmcios param)
{
 int i;
 int writelen ;
 char buffer[32] ;
 time_t seconds=time(NULL)+timezone_offset ;
 switch(function) 
 {
    case help_rmcios:
       return_string(context, paramtype,returnv,
             "rtc string representation subchannel help\r\n"
             " setup rtc_str formatstring \r\n"
             "    # Configure time string (C strftime format)\r\n"
             " read rtc_str #Read formatted string \r\n"
             ) ;
       break ;

    case create_rmcios:
       if(num_params<1) break ;
       int id;
       data= (struct rtc_str_data *) malloc( sizeof(struct rtc_str_data) ) ;
       if(data==NULL) printf("Could not allocate memory for channel!\r\n") ;
       
       //default values :
       data->linked_channel=0 ;
       strcpy(data->rtc_str_format,"%Y-%m-%dT%H:%M:%S%z") ;
       data->second_decimals=0 ;

       id=create_channel_param(context, paramtype, param, 0 ,
                               (class_rmcios) rtc_str_class_func, data); 
       break ;

    case setup_rmcios :
       if(num_params<1) break ;
       param_to_string(context, paramtype, param, 0, 20, data->rtc_str_format);
       for(i=1 ; i<num_params; i++) {
          data->rtc_str_format[strlen(data->rtc_str_format)]=' ' ;
          writelen=20-strlen(data->rtc_str_format)+1 ;
          if(writelen<=0) break ;
          param_to_string(context, paramtype, param, i, writelen, 
                          data->rtc_str_format+strlen(data->rtc_str_format));
       }
       data->rtc_str_format[19]=0 ;
       break ;

    case read_rmcios : 
       {
          char tzone[10] ;
          int len;
          strftime(buffer, 32, data->rtc_str_format, localtime(&seconds));
          len=strlen(data->rtc_str_format) ;
          if(buffer[len-1]=='z' && buffer[len-2]=='%') {
             sprintf(tzone,"%+03d:00", timezone_offset/60/60) ;
             strcat(buffer,tzone);
          }
          return_string(context, paramtype,returnv,buffer) ;
          break ;
       }
 }
}

//////////////////////////////////////////////////////
// Standard C file flass
///////////////////////////////////////////////////////

struct file_data {
    FILE *f ;
    unsigned int id;
    int keep_open ;
    char *filename ;
    char mode[5];
} ;

void file_class_func(struct file_data *pthis, 
      const struct context_rmcios *context, 
      int id, 
      enum function_rmcios function,
      enum type_rmcios paramtype,
      union param_rmcios returnv, 
      int num_params,
      const union param_rmcios param)
{
 const char *s ;
 int plen ;
 switch(function) 
 {
    case help_rmcios :
       return_string(context, paramtype,returnv,
             "file channel help\r\n"
             " create file ch_name\r\n"
             " setup ch_name filename | mode=a | keep_open=1\r\n"
             "    #open and read data from file to linked channel.\r\n"
             " read file name # read file\r\n"
             " write ch_name file data # write data to file\r\n"
             " link ch_name filename\r\n"
             " read file filename\r\n"
             ) ;
       break ;

    case create_rmcios :
       if(num_params<1) break ;
       pthis=  (struct file_data *) malloc(sizeof( struct file_data)) ; 

       //default values :
       pthis->f=NULL ;
       pthis->keep_open=1 ;
       pthis->filename=NULL ;
       pthis->mode[0]='a' ;
       pthis->mode[1]=0 ;
       pthis->id=create_channel_param(context, paramtype, param, 0,
                                      (class_rmcios)file_class_func, pthis);
       break ;

    case setup_rmcios:
       if(pthis==NULL) break ;
       return_string(context, paramtype, returnv, "setup file\r\n");
       if(pthis->f!=NULL) {
          fflush(pthis->f) ;
          fclose(pthis->f) ;
          pthis->f=NULL ;
       }
       if(num_params>0) {
          int namelen=param_string_length(context, paramtype, param, 0);
          if(pthis->filename!=NULL) free(pthis->filename) ;
          pthis->filename= (char *)malloc(namelen+1) ;
          pthis->filename[0]=0 ;
          if(pthis->filename==NULL) printf("ERROR! could not allocate mem!\n");
          const char *s=param_to_string(context, paramtype, param, 0, 
                                        namelen+1, pthis->filename) ;

          if(num_params>1) {
             param_to_string(context, paramtype,param,1, 
                             sizeof(pthis->mode), pthis->mode ) ;
          }

          if(num_params>2) {
             pthis->keep_open= param_to_int(context, paramtype,param,2) ;
          }
          return_string(context, paramtype,returnv,pthis->filename);
          pthis->f=fopen( pthis->filename , pthis->mode ) ;
          if(pthis->keep_open==0 && pthis->f!=NULL) {
             fclose(pthis->f) ;
             pthis->f=NULL ;
          } else if(pthis->f==NULL) {
              printf("Could not open file %s\r\n", pthis->filename ) ;
          }
       }
       break ;

    case write_rmcios :
       if(pthis==NULL) break ;
       
       if(pthis->f==NULL ) {
          return_string(context, paramtype,returnv,"open\r\n");
          return_string(context, paramtype,returnv,pthis->filename);
          pthis->f=fopen( pthis->filename , pthis->mode ) ;
          if(pthis->f==NULL ) {
             printf("Could not open file %s\r\n", pthis->filename ) ;
             break ;
          }
       }

       if(num_params<1) {
          fflush(pthis->f) ;
       } else {
          plen= param_buffer_alloc_size(context, paramtype,param, 0) ;
          {
             char buffer[plen] ;
             struct buffer_rmcios b ;
             int i;
             b=param_to_buffer(context, paramtype,param, 0, plen, buffer) ;
             return_buffer(context, paramtype,returnv,b.data,b.length);
             for(i=0; i<b.length; i++) {

                fputc(b.data[i],pthis->f) ;
             }

          }
       }
       if(pthis->keep_open==0 && pthis->f!=NULL) {
          fflush(pthis->f) ;
          fclose(pthis->f) ;
          pthis->f=NULL ;
       }

       break ;
    case read_rmcios:
       if(pthis==NULL) {
          int namelen;
          namelen=param_string_alloc_size(context, paramtype,param, 0) ;
          {
             char namebuffer[namelen] ;
             s=param_to_string(context, paramtype, param, 0, 
                               namelen, namebuffer) ;
             FILE *f ;
             int fsize ;
             
             f=fopen(s,"r") ;
             if(f!=NULL) {
                int c ;
                while((c=fgetc(f))!=EOF) {
                   char cc=c ;
                   return_buffer(context, paramtype,returnv,&cc,1) ;
                }
                fclose(f) ;
             } else printf("Could not open file:%s\r\n",s) ;

          }
       }
       break ;
 }
}

///////////////////////////////////////////////////////////////////
// Ticker channel
///////////////////////////////////////////////////////////////////
int ticker_linked=0 ;
Ticker *ticker1=NULL ;

void ticker1_callback()
{
    if(ticker_linked!=0) write_i(module_context, ticker_linked,0) ; 
}

void ticker_class_func(struct ticker_data *t, 
                       const struct context_rmcios *context, 
                       int id, 
                       enum function_rmcios function,
                       enum type_rmcios paramtype,
                       union param_rmcios returnv, 
                       int num_params,
                       const union param_rmcios param)
{
    switch(function) {
        case help_rmcios:
            return_string(context, paramtype,returnv,
            "ticker channel help\r\n"
            " Repeative ineterrupts at 1ms multiple periods\r\n"
            " Execution is performed from ISR\r\n"
            " linkability to channels is limited!\r\n"
            " No blocking code in linked channel code!\r\n"
            " No printf, malloc, or new linked channel execution allowed!\r\n"
            " create ticker\r\n"
            " setup newnam period # set ticker period in seconds\r\n"
            " link ticker linked_channels\r\n"
            ) ;
            break ;
        case create_rmcios:
            ticker1 = new Ticker ;
            id = create_channel_str(context, "ticker", 
                                  (class_rmcios)ticker_class_func, ticker1);
            ticker_linked = linked_channels(context, id) ;
            break ;

        case setup_rmcios:
            if(num_params<1) break ;

            if(ticker1==NULL) break ;
            float period = param_to_float(context, paramtype,param, 0) ;
            ticker1->attach(&ticker1_callback, period) ; 
            break ;
    }
}

// Driver for "digole" LCD
struct digole_lcd_data {
    digole_lcd_data(PinName mosi, PinName miso, PinName sck, PinName cs)
        : spi(mosi,miso,sck), rs(cs) {
        _row=0;
        _column=0;
        // Transmit enable
        rs = 1;         
        writeCommand(0x30);
        wait_us(100);
        writeCommand(0x30);
        wait_us(47);
        writeCommand(0x28);
        writeCommand(0x0c);
        wait_us(100);
        writeCommand(0x06);
        writeCommand(0x01);
        wait_ms(10);
    };

    int putc(int value) {
        if (value == '\n' || _column >= 16) {
            _column = 0;
            _row++;
            if (_row >= 4) _row = 0;
            switch(_row) {
                case 0:
                    writeCommand(0x80) ;
                    break ;
                case 1:
                    writeCommand(0x90) ;
                    break ;
                case 2:
                    writeCommand(0x88) ;
                    break ;
                case 3:
                    writeCommand(0x98) ;
                    break ;
            }
        }
        if(value != '\n') {
            writeData(value);
            _column++ ;
        }
        return value;
    }

    void writeCommand(uint8_t command) {
        spi.write(0xf8);        // Sync.    - 1  1  1  1  1  0  0  0
        spi.write(command & 0xf0); // HighData - D7 D6 D5 D4 0  0  0  0
        spi.write(command << 4);   // LowData  - D3 D2 D1 D0 0  0  0  0
        // According to table "Instruction Set 1: 
        // (RE=0: Basic Instruction)" on p.10
        if (command == 0x01) {
            wait_ms(1.6);
        } else {
            wait_us(72);
        }
    }

    void writeData(uint8_t data) {
        spi.write(0xfa);        // Sync.    - 1  1  1  1  1  0  1  0
        spi.write(data & 0xf0); // HighData - D7 D6 D5 D4 0  0  0  0
        spi.write(data << 4);   // LowData  - D3 D2 D1 D0 0  0  0  0
        wait_us(72);
    }

    SPI spi ;
    DigitalOut rs;
    int _row ;
    int _column ;
} ;

void digole_lcd_class_func(struct digole_lcd_data *t, 
                           const struct context_rmcios *context, 
                           int id, 
                           enum function_rmcios function,
                           enum type_rmcios paramtype,
                           union param_rmcios returnv, 
                           int num_params,
                           const union param_rmcios param)
{
 switch(function)
 {
    case help_rmcios:
       return_string(context, paramtype,returnv,
             "Digole 12864ZW LCD display (serial communication mode)\r\n"
             "create lcd_digole newname mosi_pin miso_pin sck_pin cs_pin\r\n"
             "write newname data\r\n"
             " -Write data to display\r\n"
             "write newname\r\n"
             " -Clear display\r\n"
             ) ;
       break ;

    case create_rmcios :
       if(num_params<5) break ;
       char pin_name[20] ;

       PinName mosi_pin, miso_pin, sck_pin, cs_pin ;
       param_to_string(context, paramtype, param, 1,
             sizeof(pin_name), pin_name
             );
       mosi_pin=mbed_pin_from_name(pin_name) ;
       param_to_string(context, paramtype, param, 2,
             sizeof(pin_name), pin_name
             );
       miso_pin=mbed_pin_from_name(pin_name) ;
       param_to_string(context, paramtype, param, 3,
             sizeof(pin_name), pin_name
             );
       sck_pin=mbed_pin_from_name(pin_name) ;
       param_to_string(context, paramtype, param, 4,
             sizeof(pin_name), pin_name
             );
       cs_pin=mbed_pin_from_name(pin_name) ;

       if(mosi_pin!=NC && miso_pin!=NC && sck_pin!=NC && cs_pin!=NC) {
          t= new digole_lcd_data(mosi_pin,miso_pin,sck_pin,cs_pin) ;
          create_channel_param(context, paramtype,param,0, 
                (class_rmcios)digole_lcd_class_func , t); 
       }
       break;

    case write_rmcios:

       if(t==NULL) break ;
       if(num_params==0) { 
          // clear screen
          // cls, and set cursor to 0
          t->writeCommand(0x01); 
          // This command takes 1.64 ms
          wait(0.00164f);     
          //locate(0, 0);
          t->_row=0 ;
          t->_column=0 ;
          break ;
       }
       int blen=param_string_alloc_size(context, paramtype,param,0) ;
       {
          char buffer[blen] ;
          const char *s ;
          s=param_to_string(context, paramtype,param,0,blen,buffer) ;
          while(*s!=0) {
             if(*s==2) {
                // cls, and set cursor to 0
                t->writeCommand(0x01); 
                // This command takes 1.64 ms
                wait(0.00164f);     
                // Clear display
                t->_row=0 ;
                t->_column=0 ;
             } else t->putc(*s) ;
             s++ ;
          }
       }
       break ;
 }
}

struct co2_mh_data {
    int conc ;
    int serial_channel ;
} ;

void co2_mh_class_func(struct co2_mh_data *t, 
                       const struct context_rmcios *context, 
                       int id, 
                       enum function_rmcios function,
                       enum type_rmcios paramtype,
                       union param_rmcios returnv, 
                       int num_params,
                       const union param_rmcios param)
{
 switch(function)
 {
    case help_rmcios:
       return_string(context, paramtype, returnv,
             "MH-Z14A CO2 sensor channel\r\n"
             "create CO2mh newname\r\n"
             "setup newname serial_channel\r\n"
             "write newname\r\n"
             " -update value\r\n"
             "read newname\r\n"
             " -read latest value\r\n"
             ) ;
       break ;

    case create_rmcios :
       if(num_params<1) break ;
       t= new co2_mh_data ;
       t->serial_channel=0 ;
       t->conc=0;;
       create_channel_param(context, paramtype, param, 0, 
                            (class_rmcios)co2_mh_class_func, t) ;
       break;

    case setup_rmcios:
       if(num_params<1) break ;
       if(t==NULL) break ;
       t->serial_channel= param_to_int(context, paramtype,param,0);
       break;

    case write_rmcios:
       if(t==NULL) break ;
       // read latest data from receive buffer and send data to linked
       char data[6] ;
       data[2]=0;
       data[3]=0;
       read_str(context, t->serial_channel,data,sizeof(data)) ;
       t->conc=data[2]<<8 ;
       t->conc|=data[3] ;
       write_i(context, linked_channels(context,id), t->conc) ;

       // Send poll command
       const char buffer[]= {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79} ;
       write_buffer(context, t->serial_channel, buffer ,9,0) ;
       break;

    case read_rmcios:
       if(t==NULL) break;
       return_int(context, paramtype,returnv,t->conc) ;
       break ;
 }
}


//////////////////////////////////////////////////////
// AM2315 RH and temperature probe (I2C)
//////////////////////////////////////////////////////
struct am2315_data {
    am2315_data(PinName sda, PinName scl) : i2c(sda,scl) {}
    I2C i2c;
    float RH ;
    float temp ;
    int rh_linked_channels;
    int temp_linked_channels;
};

void am2315_RH_class_func(struct am2315_data *t, 
                          const struct context_rmcios *context, 
                          int id, 
                          enum function_rmcios function,
                          enum type_rmcios paramtype,
                          union param_rmcios returnv, 
                          int num_params,
                          const union param_rmcios param)
{
 switch(function) 
 {
    case help_rmcios:
       return_string(context, paramtype,returnv,
             "AM2315 RH&temp i2c sensor RH subchannel\r\n"
             ) ;
       break ;

    case read_rmcios:
       if(t==NULL) break;
       return_float(context, paramtype,returnv,t->RH) ;
       break ;
 }
}

void am2315_T_class_func(struct context_rmcios *context, 
                         struct am2315_data *t, 
                         enum function_rmcios function,
                         enum type_rmcios paramtype,
                         union param_rmcios returnv,
                         int num_params,
                         const union param_rmcios param)
{
 switch(function) 
 {
    case help_rmcios:
       return_string(context, paramtype,returnv,
             "AM2315 RH&temp i2c sensor T subchannel\r\n"
             ) ;
       break;

    case read_rmcios:
       if(t==NULL) break;
       return_float(context, paramtype,returnv,t->temp) ;
       break ;
 }
}

void am2315_class_func(struct am2315_data *t, 
                       const struct context_rmcios *context, 
                       int id, 
                       enum function_rmcios function,
                       enum type_rmcios paramtype,
                       union param_rmcios returnv, 
                       int num_params,
                       const union param_rmcios param)
{
    switch(function) {
        case help_rmcios:
            return_string(context, paramtype,returnv,
            "AM2315 RH&temp i2c sensor channel\r\n"
            "create am2315 newname SDA_pin SCL_pin\r\n"
            "create newname RH RHname\r\n"
            "create newname T Tname\r\n"
            "write newname\r\n"
            " -update values\r\n"
            "read newname\r\n"
            "read RHname\r\n"
            "read Tname\r\n"
            " -read latest values\r\n"
            "link RHname channel\r\n"
            "link Tname channel\r\n"
            ) ;
            break ;

        case create_rmcios : {
            if(num_params==2 && t!=NULL) { 
                char buf[3] ;
                param_to_string(context, paramtype,param, 0, 3, buf);
                if(buf[0]=='R' && buf[1]=='H') {
                    id=create_channel_param(context, paramtype,param, 1,
                                            (class_rmcios)am2315_RH_class_func,
                                            t) ;
                    t->rh_linked_channels=linked_channels(context,id);
   
                    
                } else if(buf[0]=='T') {

                    id=create_channel_param(context, paramtype,param,1,
                                            (class_rmcios)am2315_T_class_func,
                                            t) ;
                    t->temp_linked_channels=linked_channels(context,id);;
                }
                break ;
            }

            if(num_params<3) break ;
            char pin_name[20] ;

            PinName SDA_pin, SCL_pin ;
            param_to_string(context, paramtype, param,1,
                            sizeof(pin_name), pin_name
                            );
            SDA_pin=mbed_pin_from_name(pin_name) ;
            param_to_string(context, paramtype, param,2,
                            sizeof(pin_name), pin_name
                            );
            SCL_pin=mbed_pin_from_name(pin_name) ;

            if(SDA_pin!=NC && SCL_pin!=NC) {
                t= new am2315_data(SDA_pin, SCL_pin) ;
        		t->rh_linked_channels = 0;
                t->temp_linked_channels = 0;
                t->RH = 0;
                t->temp = 0;
                create_channel_param(context, paramtype, param, 0,
                                     (class_rmcios)am2315_class_func, t); 
            }
        }
        break;

        case write_rmcios:
            if(t == NULL) break ;

            char cmd[8];
            // Wake up the sensor
            // write single byte twice to wake up
            // single write is not enough
            cmd[0] = 0x00;
            t->i2c.write(0xB8,cmd,1,0);
            t->i2c.write(0xB8,cmd,1,0);

            // Read data
            cmd[0] = 0x03; // Read register data
            cmd[1] = 0x00; // start register address
            cmd[2] = 0x04; // Number of registers to read
            t->i2c.write(0xB8, cmd, 3,0); // with stop

            cmd[0] = 0x00;
            cmd[1] = 0x00;
            t->i2c.read(0xB8, cmd, 8,1);

            if (cmd[0] != 0x03) break ;
            else {
                t->RH = 0.1*(((int)cmd[2]<<8) | cmd[3]) ;
                t->temp = 0.1*((((int)cmd[4]&0x7F)<<8) | cmd[5]) ;
                if (cmd[4] >> 7) t->temp = -(t->temp);
            }
            break ;
        case read_rmcios :
            return_float(context, paramtype,returnv,t->RH) ;
            break;
    }
}


struct delay_data {
    float delay ; // in ms
} ;

void delay_class_func(struct delay_data *t, 
                      const struct context_rmcios *context, 
                      int id, 
                      enum function_rmcios function,
                      enum type_rmcios paramtype,
                      union param_rmcios returnv, 
                      int num_params,
                      const union param_rmcios param)
{
    switch(function) {
        case help_rmcios:
            return_string(context, paramtype, returnv, 
            "delay channel help - Delay signals\r\n"
            " create delay newname\r\n"
            " setup newname s # set the delay time in seconds.\r\n"
            " write newname | data | ...\r\n"
            "       # Waits delay and sends data to linked channels \r\n"
            " link newname linked \r\n"
            );
            break;

        case create_rmcios :
            if(num_params<1) break ;
            t = (struct delay_data *) malloc(sizeof( struct delay_data)) ; 
            if(t == NULL) break ;
            t->delay = 0 ;
            create_channel_param(context, paramtype,param,0 ,
                                 (class_rmcios) delay_class_func, t) ; 
            break ;

        case setup_rmcios :
            if(t == NULL) break ;
            if(num_params<1) break ;
            t->delay = param_to_float(context, paramtype, param, 0 ) ;
            break ;

        case write_rmcios :
            if(t == NULL) break ;
            wait( t->delay ) ; // wait in ms
            context->run_channel(context, linked_channels(context,id), 
                                 function, paramtype, returnv, 
                                 num_params, param
                                 ) ;
            break ;
    }
}

void init_mbed_channels(const struct context_rmcios *context)
{
    module_context = context;
    //debug("init hardware\r\n") ;
    create_channel_str(context, "pwm",(class_rmcios) pwm_class_func, NULL);
    create_channel_str(context, "ai",(class_rmcios) ad_class_func, NULL);
    create_channel_str(context, "do",(class_rmcios) do_class_func, NULL);
    create_channel_str(context, "timer",(class_rmcios) timer_class_func, NULL);
    create_channel_str(context, "rtc_timer",(class_rmcios)rtc_timer_class_func, 
                       NULL 
                      );
    
    create_channel_str(context, "clock",(class_rmcios) clock_class_func, NULL);
    create_channel_str(context, "rtc",(class_rmcios) rtc_class_func, NULL ) ;
    create_channel_str(context, "rtc_str",(class_rmcios) rtc_str_class_func, 
                       (void *)&default_rtc_str_data
                      );

    create_channel_str(context, "wait",(class_rmcios) wait_class_func, NULL ) ;
    create_channel_str(context, "file", (class_rmcios)file_class_func, NULL) ;
    create_channel_str(context, "ticker", (class_rmcios)ticker_class_func, 
                       NULL) ;
    create_channel_str(context, "lcd_digole", 
                       (class_rmcios)digole_lcd_class_func, NULL
                       );
    create_channel_str(context, "co2mh", (class_rmcios)co2_mh_class_func, NULL);
    create_channel_str(context, "am2315", (class_rmcios)am2315_class_func, 
                       NULL);
    create_channel_str(context, "delay", (class_rmcios)delay_class_func, NULL) ;

    // rtc_ticker.start(1000) ;
    rtc_ticker.attach( rtc_ticker_func, 1.0) ;
    
    // Start rtc executer thread
    new Thread(executer_thread, ((void *)(&rtc_execute_queue)) );
}

#endif


