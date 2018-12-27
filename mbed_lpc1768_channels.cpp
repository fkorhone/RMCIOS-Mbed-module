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

#ifdef TARGET_LPC1768

#include "mbed.h"
#include "rtos.h"
#include "RMCIOS-functions.h"
//#include "RMCIOS-system.h"

#include "lpc17xx_regnames.h"

//#include "USBSerial.h"

const struct context_rmcios *module_context ;

///////////////////////////////////////////////////////////
// Serial
///////////////////////////////////////////////////////////
struct serial_data {
    int id ;
    Serial _serial ;
    char *rxbuffer ;
    int bufflen ;
    int lindex ;
    int ctl_mode ;
} ;

gpio_t rts1 ;

void serial_class_func(struct serial_data *t, 
                       const struct context_rmcios *context, int id, 
                       int function, 
                       enum type_rmcios paramtype,
                       union param_rmcios returnv, 
                       int num_params, union param_rmcios param)
{
 switch(function) 
 {
    case help_rmcios:
       return_string(context, paramtype, returnv,
             " Serial channel help.\r\n"
             " setup serial baud_rate data_bits parity stop_bits"
             "              | rx_buff_len | ctl_mode\r\n"
             "  ctl_mode = flow and transmit control mode bitmask: \r\n"
             " link serial channel # writes all arriving bytes to channel.\r\n"
             " write serial data # Transmit data to serial. \\r=CR \\n=LF \r\n"
             " read serial\r\n"
             "      # Read data in receive buffer since last write.\r\n"
             "      # Starting at column using delimiter as \n"
             ) ;
       break ;

    case setup_rmcios:
       if(num_params<1) break ;
       t->_serial.baud( param_to_int(context, paramtype,param,0) ) ; 
       if(num_params<4)  break ;

       int databits ;
       Serial::Parity parity=Serial::None ;
       int stop_bits ;
       databits=param_to_int(context, paramtype,param,1) ; 
       
       switch( param_to_int(context, paramtype,param,2) ) { 
          case 0 :
             parity=Serial::None ;
             break ;
          case 1 :
             parity=Serial::Odd ;
             break ;
          case 2 :
             parity=Serial::Even ;
             break ;
       }
       stop_bits=param_to_int(context, paramtype,param,3)  ; 
       t->_serial.format(databits,parity,stop_bits) ;

       if(num_params<5) break ;
       t->bufflen=param_to_int(context, paramtype,param,4)  ; 
       if(t->rxbuffer!=NULL) free(t->rxbuffer) ;
       t->rxbuffer = (char *)malloc(sizeof(char)*t->bufflen) ; 
       
       t->rxbuffer[0]=0;
       if(num_params<6) break ;
       t->ctl_mode=param_to_int(context, paramtype,param,5) ;
       break;

    case read_rmcios:
       if(t==NULL) break ;
       return_string(context, paramtype,returnv,t->rxbuffer ) ;
       break ;

    case write_rmcios:
       if(num_params<1) {
          t->lindex=0 ;
          t->rxbuffer[0]=0 ;
          break ;
       }
       if(t==NULL) break ;
       else {

          int i;
          int plen = param_buffer_alloc_size(context, paramtype,param,0) ;
          {
             struct buffer_rmcios b;
             char param_buffer[ plen ] ;
             b=param_to_buffer(context, paramtype,param, 0, plen, param_buffer);

             if(b.length>1)
             {
                for(i=0; i<b.length-1 ; i++) 
                {     	 
                   t->_serial.putc( b.data[i]) ;
                }
             }
             if(b.length>0) 
             {
                t->_serial.putc( b.data[b.length-1] ) ;
             }
          }
       }
       // reset receive buffer:
       t->lindex=0 ; 
       t->rxbuffer[0]=0 ; 
       break;
 }
}


static struct serial_data _serial1= {0,Serial(p28,p27),NULL,0,0,4},
       _serial2= {0,Serial(p9,p10) ,NULL,0,0,0}, 
       _serial3= {0,Serial(p13,p14),NULL,0,0,0}, 
       _serial4= {0,Serial(USBTX,USBRX),NULL,0,0,0}; 

Thread *p_serial_thread=0 ;
#define SERIAL_EXEC_QUEUE_LEN 200
char serial_exec_queue[SERIAL_EXEC_QUEUE_LEN][2]= {0} ;
int serial_queue_index=0 ;

void serial_thread(void const *data_q)
{
    char c ;
    write_i(module_context, channel_enum(module_context, "memmon"),(int)&c) ;

    char wait_signal=0 ;
    int i=0 ;
    char serial_ch ;

    while(1) {
        if(wait_signal) {
            // wait for receive signal :
            Thread::signal_wait(0x1); 
            wait_signal=0;
        }
        c=serial_exec_queue[i][1];
        serial_ch=serial_exec_queue[i][0];

        // check which serial
        switch( serial_ch ) { 
            case 1: 
                // serial 1
                write_buffer(module_context, 
                             linked_channels(module_context, _serial1.id), 
                             &c, 1 ,_serial1.id);
                i++ ;
                break ;
            case 2:
                write_buffer(module_context, 
                             linked_channels(module_context, _serial2.id), 
                             &c, 1, _serial2.id);
                i++ ;
                break ;
            case 3:
                write_buffer(module_context, 
                             linked_channels(module_context, _serial3.id), 
                             &c, 1, _serial3.id);
                i++ ;
                break ;
            case 4:
                write_buffer(module_context, 
                             linked_channels(module_context, _serial4.id), 
                             &c, 1, _serial4.id);
                i++ ;
                break;
            default:
                // not received anything
                wait_signal=1 ;
                break ;
        }
        if(i > (SERIAL_EXEC_QUEUE_LEN-1) ) i=0 ; // go round
    }
}

void serial1_interrupt(void)
{
    // Cant use getc with rtos in interrupt!
    unsigned int c = LPC_UART2->RBR ; 

    // serial port:
    serial_exec_queue[serial_queue_index][0]=1 ; 
    // data :
    serial_exec_queue[serial_queue_index][1]=c ; 
    
    // circular buffer:
    if(serial_queue_index > (SERIAL_EXEC_QUEUE_LEN-2) ) serial_queue_index=0 ;
    else serial_queue_index++ ;
    
    // reset next:
    serial_exec_queue[serial_queue_index][0]=0 ; 
    // Signal for reception:
    p_serial_thread->signal_set(0x1); 

    if(_serial1.lindex >= _serial1.bufflen-1 ) {
        _serial1.lindex=_serial1.bufflen-2 ;
    }

    _serial1.rxbuffer[_serial1.lindex++]=c ;
    _serial1.rxbuffer[_serial1.lindex]=0 ;
}

void serial2_interrupt(void)
{
    // Cant use getc with rtos in interrupt!
    unsigned int c = LPC_UART3->RBR ; 

    // serial port
    serial_exec_queue[serial_queue_index][0]=2 ; 
    // data
    serial_exec_queue[serial_queue_index][1]=c ; 
    
    // Circular buffer
    if(serial_queue_index > (SERIAL_EXEC_QUEUE_LEN-2) ) serial_queue_index=0 ; 
    else serial_queue_index++ ;
    
    // reset next
    serial_exec_queue[serial_queue_index][0]=0 ; 
    // Signal for reception
    p_serial_thread->signal_set(0x1); 

    if(_serial2.lindex >= _serial2.bufflen-1 ) {
        _serial2.lindex=_serial2.bufflen-2 ;
    }
    _serial2.rxbuffer[_serial2.lindex++]=c ;
    _serial2.rxbuffer[_serial2.lindex]=0 ;

}
void serial3_interrupt(void)
{
    // Cant use getc with rtos in interrupt!
    unsigned int c= LPC_UART1->RBR ; 

    // serial port
    serial_exec_queue[serial_queue_index][0]=3 ; 
    // data
    serial_exec_queue[serial_queue_index][1]=c ; 
    
    // Circular buffer
    if(serial_queue_index > (SERIAL_EXEC_QUEUE_LEN-2) ) serial_queue_index=0;
    else serial_queue_index++ ;
    // reset next
    serial_exec_queue[serial_queue_index][0]=0 ; 
    // Signal for reception
    p_serial_thread->signal_set(0x1); 

    if(_serial3.lindex >= _serial3.bufflen-1 ) {
        _serial3.lindex= _serial3.bufflen-2 ;
    }

    _serial3.rxbuffer[_serial3.lindex++]=c ;
    _serial3.rxbuffer[_serial3.lindex]=0 ;
}

PwmOut led(LED3) ;
void serial4_interrupt(void)
{ 
    // Cant use getc with rtos in interrupt!
    unsigned int c = LPC_UART0->RBR ; 
    
    // serial port
    serial_exec_queue[serial_queue_index][0]=4 ; 
    // data
    serial_exec_queue[serial_queue_index][1]=c ; 

    // go round
    if(serial_queue_index > (SERIAL_EXEC_QUEUE_LEN-2) ) serial_queue_index=0 ; 
    else serial_queue_index++ ;
    // reset next
    serial_exec_queue[serial_queue_index][0]=0 ; 

    // Signal for reception
    p_serial_thread->signal_set(0x1); 

    if(_serial4.lindex >= _serial4.bufflen-1 ) {
        _serial4.lindex=_serial4.bufflen-2 ;
    }
    _serial4.rxbuffer[_serial4.lindex++]=c ;
    _serial4.rxbuffer[_serial4.lindex]=0 ;
}

void serial5_interrupt(void)
{
    // Signal for data in the port
    // serial port
    serial_exec_queue[serial_queue_index][0]=5 ; 
    // data
    serial_exec_queue[serial_queue_index][1]=0 ; 
    // Signal for reception
    p_serial_thread->signal_set(0x1); 
}

///////////////////////////////////////////////////////////////////
// Counter                                                       //
///////////////////////////////////////////////////////////////////

// Hard coded counter implementation on mbed pin p30
void counter_class_func(void *data, const struct context_rmcios *context, 
                        int id, int function,
                        enum type_rmcios paramtype,
                        union param_rmcios returnv, 
                        int num_params,union param_rmcios param)
{
 switch(function) 
 {
    case help_rmcios:
       return_string(context, paramtype,returnv,
             "counter channel help.\r\n"
             " setup counter \r\n"
             "   # Configure mbed p30 to be used as a counter input \r\n"
             " setup counter p29\r\n"
             "   # Configure mbed p29 to be used as a counter input \r\n"
             " setup counter p30\r\n" 
             "   # Configure mbed p30 to be used as a counter input \r\n"
             " read counter \r\n"
             " write counter"
             "   # reset and read\r\n"
             ) ;
       break;
    case setup_rmcios:
       // timer 2 power
       LPC_SC->PCONP|=(1<<22); 
       if(num_params>1) {
          char pin_name[20] ;
          param_to_string(context, paramtype, param,
                0, sizeof(pin_name), pin_name) ;
          if( strcmp(pin_name,"p29")==0 ) {
             // MBED P29 CAP2.1 as counter
             LPC_PINCON->PINSEL0|= ((1<<10) | (1<<11)) ;
             // MBED P29 CAP2.1 as counter
             LPC_PINCON->PINSEL0&= ~((1<<8) | (1<<9)) ;
          } else if( strcmp(pin_name,"p30")== 0) {
             // P30 p0.4 CAP2.0 as counter
             LPC_PINCON->PINSEL0|= ((1<<8) | (1<<9)) ;
             // MBED P29 CAP2.1 as counter
             LPC_PINCON->PINSEL0&= ~((1<<10) | (1<<11)) ;
          }
          // P30 p0.4 CAP2.0 as counter
       } else LPC_PINCON->PINSEL0|= ((1<<8) | (1<<9)) ; 

       //counter disable
       LPC_TIM2->TCR   =0x2; 
       //counter mode,increments on rising edges
       LPC_TIM2->CTCR  =0x1; 
       //set prescaler
       LPC_TIM2->PR    =0x0; 
       //counter enable
       LPC_TIM2->TCR   =0x1; 
       break ;
    case read_rmcios:
       return_int(context, paramtype,returnv, LPC_TIM2->TC) ;
       break;
    case write_rmcios:
       return_int(context, paramtype,returnv, LPC_TIM2->TC) ;
       LPC_TIM2->TC=0 ;
       break;
 }
}

SPI spi(p5, p6, p7); // mosi, miso, sclk
DigitalOut shift_load(p11);
unsigned char mux_pos=0 ;
unsigned char relays_pos=0 ;

void admux_class_rmcios(void *data, 
                        const struct context_rmcios *context,
                        int id, 
                        int function,
                        enum type_rmcios paramtype,
                        union param_rmcios returnv, 
                        int num_params,
                        union param_rmcios param)
{
 switch(function) 
 {
    case help_rmcios:
       return_string(context, paramtype,returnv,
             "analog multiplexer channel help.\r\n"
             " write mux # read current mux postition\r\n"
             " write mux pos # set mux postition\r\n"
             ) ;
       break;
    case write_rmcios:
       if(num_params<1) {
          return_int(context, paramtype,returnv, mux_pos ) ;
          break;
       }
       mux_pos=param_to_int(context, paramtype,param,0) ;
       spi.frequency(100000);
       shift_load = 0;
       spi.write(mux_pos<<5 | relays_pos);
       shift_load = 1;
       break ;
    case read_rmcios:
       return_int(context, paramtype,returnv, mux_pos ) ;
       break ;
 }
}
void do_class_rmcios(void *data, 
                     const struct context_rmcios *context, 
                     int id, 
                     int function,
                     enum type_rmcios paramtype,
                     union param_rmcios returnv, 
                     int num_params,
                     union param_rmcios param)
{
    unsigned int n = (unsigned int )data ;

    switch(function) {
        case help_rmcios:
            return_string(context, paramtype,returnv,
            "digital out channel help.\r\n"
            " write do # read current value\r\n"
            " write do pos # set digital output state\r\n"
            ) ;
            break;
        case write_rmcios:
            if(num_params<1) {
                return_int(context, paramtype,returnv, 
                           ((relays_pos >> n) &1));
                break;
            }
            relays_pos= (relays_pos&(~(1<<n))) 
                        | ((param_to_int(context, paramtype,param,0)&1)<<n);

            spi.frequency(100000);
            shift_load = 0;
            spi.write(mux_pos<<5 | relays_pos);
            shift_load = 1;
            break ;
        case read_rmcios:
            return_int(context, paramtype,returnv, ((relays_pos >> n) & 1));
            break ;
    }
}

extern "C" void mbed_reset();

void system_class_func(const struct context_rmcios *context, 
                       void *data, 
                       int function,
                       enum type_rmcios paramtype,
                       union param_rmcios returnv, 
                       int num_params,
                       union param_rmcios param)
{
    switch(function) {
        case write_rmcios:
            mbed_reset() ; // RESET The system
            break;
    }
}

void pwm_edges_class_rmcios(void *data, 
                            const struct context_rmcios *context, 
                            int id, 
                            int function,
                            enum type_rmcios paramtype,
                            union param_rmcios returnv, 
                            int num_params,
                            union param_rmcios param)
{
    switch(function) {
        case help_rmcios:
            return_string(context, paramtype,returnv,
            "pwm_edges. Set pwm channels into single or double edge mode.\r\n"
            "    See lpc17xx manual for more info on double edge mode\r\n"
            "setup pwm_edges pwm2_mode(0) | pwm3_mode(0) | pwm4_mode(0)\r\n"
            "              | pwm5_mode(0) | pwm6_mode(0) \r\n"
            ) ;
            break ;
        case setup_rmcios:
            int value ;
            if(num_params<1) break ;
            value=(param_to_int(context, paramtype,param,0)&1) << 1;

            if(num_params>=2) { 
               value |= (param_to_int(context, paramtype,param,1)&1) << 2;
            }
            if(num_params>=3) { 
               value |= (param_to_int(context, paramtype,param,2)&1) << 3;
            }
            if(num_params>=4) {
               value |= (param_to_int(context, paramtype,param,3)&1) << 4;
            }
            if(num_params>=5) {
               value |= (param_to_int(context, paramtype,param,4)&1) << 5;
            }
            // Reset edge select bits
            LPC_PWM1->PCR &= ~0x3e ; 
            // Set the edge mode
            LPC_PWM1->PCR |= value ; 
            // Set the pwm prescaler value
            LPC_PWM1->PR = 0 ;
            // PCLKSEL0 13:12 PCLK_PWM1 Peripheral clock selection for PWM1.
            LPC_SC->PCLKSEL0 |= 1<<12 ; 
            break;
    }
}

void watchdog_class_rmcios(void *data,
                           const struct context_rmcios *context, 
                           int id, 
                           int function,
                           enum type_rmcios paramtype, 
                           union param_rmcios returnv, 
                           int num_params,
                           union param_rmcios param)
{
    switch(function) {
  		case help_rmcios:
    			return_string(context, paramtype,returnv,
    			              "watchdog channel\r\n"
    			              "setup watchdog time\r\n"
                          "   -setup watchdog reset time\r\n"
    			              "write watchdog\r\n"
                          "   -kick/feed the dog -> reset timer\r\n"
    			);
    		break ;
    		
    	case setup_rmcios:
    		if(num_params<1) break ;
    		float s=param_to_float(context, paramtype,param,0 ) ;
         // WD has a fixed /4 prescaler, PCLK default is /4
    		uint32_t clk = SystemCoreClock / 16;    
       		
         // Set CLK src to PCLK
         LPC_WDT->WDCLKSEL = 0x1;                
        	LPC_WDT->WDTC = s * (float)clk;
         // Enabled and Reset
        	LPC_WDT->WDMOD = 0x3;                   
    
    	case write_rmcios: 
         // Feed the dog
        	LPC_WDT->WDFEED = 0xAA;
       	LPC_WDT->WDFEED = 0x55;
    		break ;
    }
}

void init_mbed_platform_channels(const struct context_rmcios *context)
{
   printf("Initalizing mbed platform channels\r\n") ;
   module_context= context ;

   create_channel_str(context, "system",(class_rmcios)system_class_func, NULL);

   // Create ad channels ;
   write_str(context, context->control, "create ai ad1 p20\n", 0) ;
   write_str(context, context->control, "create ai ad2 p19\n", 0) ;
   write_str(context, context->control, "create ai ad3 p18\n", 0) ;
   write_str(context, context->control, "create ai ad4 p17\n", 0) ;
   write_str(context, context->control, "create ai ad5 p16\n", 0) ;
   write_str(context, context->control, "create ai ad6 p15\n", 0) ;

   // Analog input timing:
   write_str(context, context->control, "create timer ad\n", 0) ;

   // set analog input refresh rate :
   write_str(context, context->control, "setup ad 1\n", 0) ; 
   write_str(context, context->control, "link ad ad1\n", 0) ;
   write_str(context, context->control, "link ad ad2\n", 0) ;
   write_str(context, context->control, "link ad ad3\n", 0) ;
   write_str(context, context->control, "link ad ad4\n", 0) ;
   write_str(context, context->control, "link ad ad5\n", 0) ;
   write_str(context, context->control, "link ad ad6\n", 0) ;

   // Create pwm channels
   write_str(context, context->control, "create pwm pwm1 p26\n", 0) ;
   write_str(context, context->control, "create pwm pwm2 p25\n", 0) ;
   write_str(context, context->control, "create pwm pwm3 p24\n", 0) ;
   write_str(context, context->control, "create pwm pwm4 p23\n", 0) ;
   write_str(context, context->control, "create pwm pwm5 p22\n", 0) ;
   write_str(context, context->control, "create pwm pwm6 p21\n", 0) ;

   write_str(context, context->control, "create pwm led1 LED1\n", 0) ;
   write_str(context, context->control, "create pwm led2 LED2\n", 0) ;
   write_str(context, context->control, "create pwm led3 LED3\n", 0) ;
   write_str(context, context->control, "create pwm led4 LED4\n", 0) ;

   // Channel for selecting double edge pwm
   create_channel_str(context, "pwm_edges",
         (class_rmcios)pwm_edges_class_rmcios, NULL);

   // Initialize serial port data:
   _serial1.rxbuffer=new char[20] ;
   _serial2.rxbuffer=new char[20] ;
   _serial3.rxbuffer=new char[20] ;
   _serial4.rxbuffer=new char[20] ;
   _serial1.bufflen=20 ;
   _serial2.bufflen=20 ;
   _serial3.bufflen=20 ;
   _serial4.bufflen=20 ;
   _serial1.rxbuffer[0]=0;
   _serial2.rxbuffer[0]=0;
   _serial3.rxbuffer[0]=0;
   _serial4.rxbuffer[0]=0;

   _serial1.id=create_channel_str(context, "serial1",
         (class_rmcios)serial_class_func, &_serial1);
   _serial2.id=create_channel_str(context, "serial2",
         (class_rmcios)serial_class_func, &_serial2);
   _serial3.id=create_channel_str(context, "serial3",
         (class_rmcios)serial_class_func, &_serial3);
   _serial4.id=create_channel_str(context, "serial4",
         (class_rmcios)serial_class_func, &_serial4);

   _serial1._serial.attach(&serial1_interrupt) ;
   _serial2._serial.attach(&serial2_interrupt) ;
   _serial3._serial.attach(&serial3_interrupt) ;
   _serial4._serial.attach(&serial4_interrupt) ;

   // RTS
   /* GPIO object */
   gpio_init(&rts1,p12);

   // Start serial executer thread
   p_serial_thread = new Thread(serial_thread);

   // Counter (Uses mbed timer 2)
   create_channel_str(context, "counter",
         (class_rmcios)counter_class_func , NULL);

   // Configure pin as counter
   write_str(context, context->control, "setup counter\n", 0); 

   // Admux and digital out channels through a shift register in SPI.
   create_channel_str(context, "admux", 
         (class_rmcios)admux_class_rmcios, NULL);

   // Relay outputs at shift register outputs :
   create_channel_str(context, "do0", 
         (class_rmcios)do_class_rmcios, (void *)0);
   create_channel_str(context, "do1", 
                      (class_rmcios)do_class_rmcios, (void *)1);
   create_channel_str(context, "do2", 
                      (class_rmcios)do_class_rmcios, (void *)2);
   create_channel_str(context, "do3", 
                      (class_rmcios)do_class_rmcios, (void *)3);
   create_channel_str(context, "do4",
                      (class_rmcios)do_class_rmcios, (void *)4);

   create_channel_str(context, "watchdog", 
                      (class_rmcios)watchdog_class_rmcios, NULL);
}
#endif

