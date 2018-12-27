/* 2015 Frans Korhonen. University of Helsinki.
 *
 */
#ifdef TARGET_LPC1768

#include "mbed.h"
#include "rtos.h"
#include "RMCIOS-functions.h"
//#include "RMCIOS-system.h"

#include "lpc17xx_regnames.h"

//#include "USBSerial.h"

const struct context_rmcios *module_context ;

//////////////////////////////////////////////////////////////////////////////////
// Serial
/////////////////////////////////////////////////////////////////////////////////

struct serial_data {
    int id ;
    Serial _serial ;
    char *rxbuffer ;
    int bufflen ;
    int lindex ;
    int ctl_mode ;
 //   int share_register ;
} ;

gpio_t rts1 ;
/*
void serial1_rts_on(void)
{
    rts1=1 ;
}

void serial1_rts_off(void)
{
    rts1=0 ;
}*/


void serial_class_func(struct serial_data *t, const struct context_rmcios *context, int id, int function,enum type_rmcios paramtype,union param_rmcios returnv, int num_params,union param_rmcios param)
{
    //debug(serial_dbg,"serial call \r\n") ;
    switch(function) {
        case help_rmcios:
            return_string(context, paramtype, returnv,
            " Serial channel help.\r\n"
            " setup serial baud_rate data_bits parity stop_bits | rx_buff_len | ctl_mode\r\n"
            //"		 parity=(PARITY_NONE/PARIY_ODD/PARITY_EVEN)\n"
            "  ctl_mode = flow and transmit control mode bitmask: \r\n"
            "	1= DTR_ON_DURING_TRANSMIT\r\n"
            //"	2= DTR_OFF_DURING_TRANSMIT\r\n"
            " 	4= RTS_ON_DURING_TRANSMIT\r\n"
            " 	8= RTS_OFF_DURING_TRANSMIT"
            "	16= DSR_LOW_TO_TRANSMIT"
            "	32= DSR_HIGH_TO_TRANSMIT"
            "	64= CTS_LOW_TO_TRANSMIT"
            "	128= CTS_HIGH_TO_TRANSMIT"
            " link serial channel # writes all arriving bytes to channel.\r\n"
            " write serial data # Transmit data to serial. \\r=CR \\n=LF \r\n"
            " read serial # Read data in receive buffer since last write. starting at column using delimiter as \n"
            ) ;
            break ;
        case setup_rmcios:
            // 0.baud_rate 1.data_bits 2.parity 3.stop_bits | 4.rx_buff_len | 5.start_column=0 | 6.column_delimiter=' ' | 7.message_delimiter=-1
            if(num_params<1) break ;
            t->_serial.baud( param_to_int(context, paramtype,param,0) ) ; // 0.baud_rate
            if(num_params<4)  break ;

            int databits ;
            Serial::Parity parity=Serial::None ;
            int stop_bits ;
            databits=param_to_int(context, paramtype,param,1) ; // 1.data_bits
            switch( param_to_int(context, paramtype,param,2) ) { // 2.parity
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
            stop_bits=param_to_int(context, paramtype,param,3)  ; // 3.stop_bits
            t->_serial.format(databits,parity,stop_bits) ;

            if(num_params<5) break ;
            t->bufflen=param_to_int(context, paramtype,param,4)  ; //4.rx_buff_len
            if(t->rxbuffer!=NULL) free(t->rxbuffer) ; // release memory
            t->rxbuffer = (char *)malloc(sizeof(char)*t->bufflen) ; // allocate new memory
            t->rxbuffer[0]=0;
            if(num_params<6) break ;
            t->ctl_mode=param_to_int(context, paramtype,param,5) ;
            break;

        case read_rmcios:
            if(t==NULL) break ;
            //printf("st:%s\r\n",t->rxbuffer ) ;
            return_string(context, paramtype,returnv,t->rxbuffer ) ;
            break ;

        case write_rmcios:
        	//write_iv(channel_enum("memmon"), 0, NULL) ; // do mem report
            
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
                    b=param_to_buffer(context, paramtype,param, 0, plen, param_buffer) ;


					//rts1=1 ;
					
                //    request_write_resource( &t->share_register );
                 switch(t->ctl_mode) {
                        case 4 :
                        //	gpio_write(&rts1, 1);
                          //  rts1.write(1) ;
                            break ; //4= RTS_ON_DURING_TRANSMIT
                        case 8 :
                       		//gpio_write(&rts1, 0);
                          //  rts1.write(0) ;
                            break ; //8= RTS_OFF_DURING_TRANSMIT
                        default :
                            break ;
                    }
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
					
				//	__disable_irq(); // Disable interrupt for correct tramsmitter enable timing
                    //  t-
                    // t->_serial.putc( b.length+'0') ;

                    //t->_serial.printf( "length:%d\r\n" ,b.length ) ;
                   switch(t->ctl_mode) {
                        case 4 :
                          	while( ((LPC_UART2->LSR >> 6) &1) ==0) ; // wait bit 6 Transmitter Empty (TEMT)
                           // rts1=0 ;
                           //gpio_write(&rts1, 0);
                           //((rts1.write(0) ;
                            break ; //4= RTS_ON_DURING_TRANSMIT
                        case 8 :
                           	while( ((LPC_UART2->LSR >> 6)&1 ) ==0) ; // wait bit 6 Transmitter Empty (TEMT)
                            //rts1=1 ;
                           // gpio_write(&rts1, 1);
                            //((rts1.write(1) ;
                            break ; //8= RTS_OFF_DURING_TRANSMIT

                        default :
                            break ;
                    }
                //    rts1=0 ;
                    
                   // __enable_irq();
                     
                  	//stop_write_resource(&t->share_register) ;
                }
            }
            t->lindex=0 ; // reset receive buffer
            t->rxbuffer[0]=0 ; // reset receive buffer
            break;
    }
}


//////////////////////////////////////////////////////////////////////////////////
// USB Serial
/////////////////////////////////////////////////////////////////////////////////
/*struct usb_serial_data {
    int id ;
    USBSerial _serial ;
    char *rxbuffer ;
    int bufflen ;
    int lindex ;
} ;

void usb_serial_class_func(struct usb_serial_data *t, int function,enum type_rmcios paramtype,union param_rmcios returnv, int num_params,union param_rmcios param)
{
    //debug(serial_dbg,"serial call \r\n") ;
    switch(function) {
        case help_rmcios:
            return_string(paramtype,returnv,
            " Serial channel help.\r\n"
            " setup serial baud_rate data_bits parity stop_bits | rx_buff_len\r\n"
            //"		 parity=(PARITY_NONE/PARIY_ODD/PARITY_EVEN)\n"
            " link serial channel # writes all arriving bytes to channel.\r\n"
            " write serial data # Transmit data to serial. \\r=CR \\n=LF \r\n"
            " read serial # Read data in receive buffer since last write. starting at column using delimiter as \n"
            ) ;
            break ;
        case setup_rmcios:*/
// 0.baud_rate 1.data_bits 2.parity 3.stop_bits | 4.rx_buff_len | 5.start_column=0 | 6.column_delimiter=' ' | 7.message_delimiter=-1
/*if(num_params<1) break ;
 t->_serial.baud( param_to_int(paramtype,param,0) ) ; // 0.baud_rate
 if(num_params<4)  break ;

 int databits ;
 Serial::Parity parity=Serial::None ;
 int stop_bits ;
 databits=param_to_int(paramtype,param,1) ; // 1.data_bits
 switch( param_to_int(paramtype,param,2) ) { // 2.parity
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
 stop_bits=param_to_int(paramtype,param,3)  ; // 3.stop_bits
 t->_serial.format(databits,parity,stop_bits) ;
*/
/*
if(num_params<5) break ;
t->bufflen=param_to_int(paramtype,param,4)  ; //4.rx_buff_len
if(t->rxbuffer!=NULL) free(t->rxbuffer) ; // release memory
t->rxbuffer = (char *)malloc(sizeof(char)*t->bufflen) ; // allocate new memory
t->rxbuffer[0]=0;
break;

case read_rmcios:
if(t==NULL) break ;
//printf("st:%s\r\n",t->rxbuffer ) ;
return_string(paramtype,returnv,t->rxbuffer ) ;
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
    int plen = param_buffer_length(paramtype,param,0) ;
    {
        char param_buffer[ plen ] ;
        param_to_buffer(paramtype,param, 0, sizeof(param_buffer), param_buffer) ;
        for(i=0; i<plen ; i++) {
            t->_serial.putc(param_buffer[i]) ;
        }
    }
}
t->lindex=0 ; // reset receive buffer
t->rxbuffer[0]=0 ; // reset receive buffer
break;


default:
debug(serial_dbg,"Undefined function:%d\r\n",function) ;
break ;
}
}
*/
static struct serial_data _serial1= {0,Serial(p28,p27),NULL,0,0,4}, // tx,rx, RTS on during transmit.
       _serial2= {0,Serial(p9,p10) ,NULL,0,0,0}, // tx,rx
       _serial3= {0,Serial(p13,p14),NULL,0,0,0}, // tx,rx
       _serial4= {0,Serial(USBTX,USBRX),NULL,0,0,0}; // tx,rx Programming interface serial

//struct usb_serial_data _serial5= {0,USBSerial(),0,NULL,0 ,0} ; // tx,rx
// Serial test(p28,p27) ;

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
        //  test.printf("r\n") ;
        if(wait_signal) {
            Thread::signal_wait(0x1); // wait for receive signal
            //Thread::wait(10); // wait for receive signal
            wait_signal=0 ;
        }

        c=serial_exec_queue[i][1] ;
        serial_ch=serial_exec_queue[i][0] ;

        switch( serial_ch ) { // check which serial
            case 1: // serial 1
                write_buffer(module_context, linked_channels(module_context, _serial1.id), &c,1,_serial1.id) ;
                i++ ;
                break ;
            case 2:
                write_buffer(module_context, linked_channels(module_context, _serial2.id), &c,1,_serial2.id) ;
                i++ ;
                break ;
            case 3:
                write_buffer(module_context, linked_channels(module_context, _serial3.id), &c,1,_serial3.id) ;
                i++ ;
                break ;
            case 4:
                write_buffer(module_context, linked_channels(module_context, _serial4.id), &c,1,_serial4.id) ;
                i++ ;
                break;
                /*case 5:
                    
                        while (_serial5._serial.readable()) {
                            c=_serial5._serial.getc() ;
                            write_buffer(module_context, linked_channels(module_context, _serial5.id, &c, 1, _serial5.id) ;
                        }
                    
                    i++ ;

                    break ;*/
            default: // not received anything
                wait_signal=1 ;
                break ;
        }
        if(i > (SERIAL_EXEC_QUEUE_LEN-1) ) i=0 ; // go round
    }
}

void serial1_interrupt(void)
{

    unsigned int c = LPC_UART2->RBR ; // Cant use getc with rtos in interrupt!

    serial_exec_queue[serial_queue_index][0]=1 ; // serial port
    serial_exec_queue[serial_queue_index][1]=c ; // data
    if(serial_queue_index > (SERIAL_EXEC_QUEUE_LEN-2) ) serial_queue_index=0 ; // go round
    else serial_queue_index++ ;
    serial_exec_queue[serial_queue_index][0]=0 ; // reset next
    p_serial_thread->signal_set(0x1); // Signal for reception

    // write_i(module_context, linked_channels(module_context,_serial1.id), c) ;
    if(_serial1.lindex >= _serial1.bufflen-1 ) {
        _serial1.lindex=_serial1.bufflen-2 ;
    }
    _serial1.rxbuffer[_serial1.lindex++]=c ;
    _serial1.rxbuffer[_serial1.lindex]=0 ;
}

void serial2_interrupt(void)
{
    unsigned int c = LPC_UART3->RBR ; // Cant use getc with rtos in interrupt!

    serial_exec_queue[serial_queue_index][0]=2 ; // serial port
    serial_exec_queue[serial_queue_index][1]=c ; // data
    if(serial_queue_index > (SERIAL_EXEC_QUEUE_LEN-2) ) serial_queue_index=0 ; // go round
    else serial_queue_index++ ;
    serial_exec_queue[serial_queue_index][0]=0 ; // reset next
    p_serial_thread->signal_set(0x1); // Signal for reception

    if(_serial2.lindex >= _serial2.bufflen-1 ) {
        _serial2.lindex=_serial2.bufflen-2 ;
    }
    //printf("%c",*c) ;
    _serial2.rxbuffer[_serial2.lindex++]=c ;
    _serial2.rxbuffer[_serial2.lindex]=0 ;

}
void serial3_interrupt(void)
{
    unsigned int c= LPC_UART1->RBR ; // Cant use getc with rtos in interrupt!

    serial_exec_queue[serial_queue_index][0]=3 ; // serial port
    serial_exec_queue[serial_queue_index][1]=c ; // data
    if(serial_queue_index > (SERIAL_EXEC_QUEUE_LEN-2) ) serial_queue_index=0 ; // go round
    else serial_queue_index++ ;
    serial_exec_queue[serial_queue_index][0]=0 ; // reset next
    p_serial_thread->signal_set(0x1); // Signal for reception

    if(_serial3.lindex >= _serial3.bufflen-1 ) {
        _serial3.lindex= _serial3.bufflen-2 ;
    }

    _serial3.rxbuffer[_serial3.lindex++]=c ;
    _serial3.rxbuffer[_serial3.lindex]=0 ;
}

PwmOut led(LED3) ;
void serial4_interrupt(void)
{ 
    unsigned int c = LPC_UART0->RBR ; // Cant use getc with rtos in interrupt!
    
    serial_exec_queue[serial_queue_index][0]=4 ; // serial port
    serial_exec_queue[serial_queue_index][1]=c ; // data

    if(serial_queue_index > (SERIAL_EXEC_QUEUE_LEN-2) ) serial_queue_index=0 ; // go round
    else serial_queue_index++ ;
    serial_exec_queue[serial_queue_index][0]=0 ; // reset next

    p_serial_thread->signal_set(0x1); // Signal for reception

    if(_serial4.lindex >= _serial4.bufflen-1 ) {
        _serial4.lindex=_serial4.bufflen-2 ;
    }
    _serial4.rxbuffer[_serial4.lindex++]=c ;
    _serial4.rxbuffer[_serial4.lindex]=0 ;
}

void serial5_interrupt(void)
{
    // Signal for data in the port
    serial_exec_queue[serial_queue_index][0]=5 ; // serial port
    serial_exec_queue[serial_queue_index][1]=0 ; // data
    p_serial_thread->signal_set(0x1); // Signal for reception
}

///////////////////////////////////////////////////////////////////
// Counter                                                       //
///////////////////////////////////////////////////////////////////

// hard coded counter implementation on mbed pin p30
void counter_class_func(void *data, const struct context_rmcios *context, int id, int function,enum type_rmcios paramtype,union param_rmcios returnv, int num_params,union param_rmcios param)
{
    switch(function) {
        case help_rmcios:
            return_string(context, paramtype,returnv,
            "counter channel help.\r\n"
            " setup counter # Configure mbed p30 to be used as a counter input \r\n"
            " setup counter p29 # Configure mbed p29 to be used as a counter input \r\n"
            " setup counter p30 # Configure mbed p30 to be used as a counter input \r\n"
            " read counter \r\n"
            " write counter #reset and read\r\n"
            ) ;
            break;
        case setup_rmcios:
            LPC_SC->PCONP|=(1<<22); // timer 2 power

            if(num_params>1) {
                char pin_name[20] ;
                param_to_string(context, paramtype, param,0,sizeof(pin_name),pin_name) ;
                if( strcmp(pin_name,"p29")==0 ) {
                    LPC_PINCON->PINSEL0|= ((1<<10) | (1<<11)) ;// MBED P29 CAP2.1 as counter
                    LPC_PINCON->PINSEL0&= ~((1<<8) | (1<<9)) ;// MBED P29 CAP2.1 as counter
                } else if( strcmp(pin_name,"p30")== 0) {
                    LPC_PINCON->PINSEL0|= ((1<<8) | (1<<9)) ;// P30 p0.4 CAP2.0 as counter
                    LPC_PINCON->PINSEL0&= ~((1<<10) | (1<<11)) ;// MBED P29 CAP2.1 as counter
                }
            } else LPC_PINCON->PINSEL0|= ((1<<8) | (1<<9)) ; // P30 p0.4 CAP2.0 as counter

            LPC_TIM2->TCR   =0x2; //counter disable
            LPC_TIM2->CTCR  =0x1; //counter mode,increments on rising edges
            LPC_TIM2->PR    =0x0; //set prescaler
            LPC_TIM2->TCR   =0x1; //counter enable
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

void admux_class_rmcios(void *data, const struct context_rmcios *context, int id, int function,enum type_rmcios paramtype,union param_rmcios returnv, int num_params,union param_rmcios param)
{
    switch(function) {
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
void do_class_rmcios(void *data, const struct context_rmcios *context, int id, int function,enum type_rmcios paramtype,union param_rmcios returnv, int num_params,union param_rmcios param)
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
                return_int(context, paramtype,returnv, ((relays_pos >> n) & 1) ) ;
                break;
            }
            relays_pos= (relays_pos&(~(1<<n))) | ((param_to_int(context, paramtype,param,0)&1)<<n) ;

            spi.frequency(100000);
            shift_load = 0;
            spi.write(mux_pos<<5 | relays_pos);
            shift_load = 1;
            break ;
        case read_rmcios:
            return_int(context, paramtype,returnv, ((relays_pos >> n) & 1) ) ;
            break ;
    }
}

extern "C" void mbed_reset();

void system_class_func(const struct context_rmcios *context, void *data, int function,enum type_rmcios paramtype,union param_rmcios returnv, int num_params,union param_rmcios param)
{
    switch(function) {
        case write_rmcios:
            mbed_reset() ; // RESET The system
            break;
    }
}

void pwm_edges_class_rmcios(void *data, const struct context_rmcios *context, int id, int function,enum type_rmcios paramtype,union param_rmcios returnv, int num_params,union param_rmcios param)
{
    switch(function) {
        case help_rmcios:
            return_string(context, paramtype,returnv,
            "pwm_edges. Set pwm channels into single or double edge mode. \r\n"
            " See lpc17xx manual for more info on double edge mode\r\n"
            "setup pwm_edges pwm2_mode(0) | pwm3_mode(0) | pwm4_mode(0) | pwm5_mode(0) | pwm6_mode(0) \r\n"
            ) ;
            break ;
        case setup_rmcios:
            int value ;
            if(num_params<1) break ;
            value=(param_to_int(context, paramtype,param,0)&1)<<1 ;
            if(num_params>=2) value|=(param_to_int(context, paramtype,param,1)&1)<<2 ;
            if(num_params>=3) value|=(param_to_int(context, paramtype,param,2)&1)<<3 ;
            if(num_params>=4) value|=(param_to_int(context, paramtype,param,3)&1)<<4 ;
            if(num_params>=5) value|=(param_to_int(context, paramtype,param,4)&1)<<5 ;
            LPC_PWM1->PCR &= ~0x3e ; // Reset edge select bits
            LPC_PWM1->PCR |= value ; // Set the edge mode
            LPC_PWM1->PR = 0 ; // Set the pwm prescaler value
            LPC_SC->PCLKSEL0 |= 1<<12 ; // PCLKSEL0 13:12 PCLK_PWM1 Peripheral clock selection for PWM1. 00
            break;
    }
}

void watchdog_class_rmcios(void *data, const struct context_rmcios *context, int id, int function,enum type_rmcios paramtype, union param_rmcios returnv, int num_params,union param_rmcios param)
{
    switch(function) {
  		case help_rmcios:
    			return_string(context, paramtype,returnv,
    			"watchdog channel\r\n"
    			"setup watchdog time\r\n   -setup watchdog reset time\r\n"
    			"write watchdog\r\n   -kick/feed the dog -> reset timer\r\n"
    			);
    		break ;
    		
    	case setup_rmcios:
    		if(num_params<1) break ;
    		float s=param_to_float(context, paramtype,param,0 ) ;
    		uint32_t clk = SystemCoreClock / 16;    // WD has a fixed /4 prescaler, PCLK default is /4
       		
       		LPC_WDT->WDCLKSEL = 0x1;                // Set CLK src to PCLK
        	LPC_WDT->WDTC = s * (float)clk;
        	LPC_WDT->WDMOD = 0x3;                   // Enabled and Reset
    
    	case write_rmcios: // Feed the dog
        	LPC_WDT->WDFEED = 0xAA;
       		LPC_WDT->WDFEED = 0x55;
    		break ;
    }
}

void init_mbed_platform_channels(const struct context_rmcios *context)
{
    printf("Initalizing mbed platform channels\r\n") ;
    module_context= context ;
    
    create_channel_str(context, "system",(class_rmcios) system_class_func, NULL ) ;
    // Create ad channels ;
    write_str(context, context->control, "create ai ad1 p20\n", 0) ;
    write_str(context, context->control, "create ai ad2 p19\n", 0) ;
    write_str(context, context->control, "create ai ad3 p18\n", 0) ;
    write_str(context, context->control, "create ai ad4 p17\n", 0) ;
    write_str(context, context->control, "create ai ad5 p16\n", 0) ;
    write_str(context, context->control, "create ai ad6 p15\n", 0) ;

    // Analog input timing:
    write_str(context, context->control, "create timer ad\n", 0) ;
    write_str(context, context->control, "setup ad 1\n", 0) ; // set analog input refresh rate
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
    create_channel_str(context, "pwm_edges",(class_rmcios)pwm_edges_class_rmcios , NULL ) ;

    // Initialize serial port data:
    _serial1.rxbuffer=new char[20] ;
    _serial2.rxbuffer=new char[20] ;
    _serial3.rxbuffer=new char[20] ;
    _serial4.rxbuffer=new char[20] ;
    //  _serial5.rxbuffer=new char[20] ;
    _serial1.bufflen=20 ;
    _serial2.bufflen=20 ;
    _serial3.bufflen=20 ;
    _serial4.bufflen=20 ;
    //_serial5.bufflen=20 ;
    _serial1.rxbuffer[0]=0;
    _serial2.rxbuffer[0]=0;
    _serial3.rxbuffer[0]=0;
    _serial4.rxbuffer[0]=0;
    //_serial5.rxbuffer[0]=0;

    _serial1.id=create_channel_str(context, "serial1",(class_rmcios)serial_class_func , &_serial1 ) ;
    _serial2.id=create_channel_str(context, "serial2",(class_rmcios)serial_class_func , &_serial2 ) ;
    _serial3.id=create_channel_str(context, "serial3",(class_rmcios)serial_class_func , &_serial3 ) ;
    //create_channel_str(context, "serialUSB",(class_rmcios)serial_class_func , &_serial4 ) ;
    _serial4.id=create_channel_str(context, "serial4",(class_rmcios)serial_class_func , &_serial4 ) ;
    // _serial5.id=create_channel_str("serial5",(class_rmcios)usb_serial_class_func , &_serial5 ) ;

    _serial1._serial.attach(&serial1_interrupt) ;
    _serial2._serial.attach(&serial2_interrupt) ;
    _serial3._serial.attach(&serial3_interrupt) ;
    _serial4._serial.attach(&serial4_interrupt) ;
    //  _serial5._serial.attach(&serial5_interrupt) ;

	// RTS
	/* GPIO object */
	gpio_init(&rts1,p12);

    // Start serial executer thread
    p_serial_thread = new Thread(serial_thread);

    // Counter (Uses mbed timer 2)
    create_channel_str(context, "counter",(class_rmcios)counter_class_func , NULL ) ;
    write_str(context, context->control, "setup counter\n", 0) ; // Configure pin as counter

    // Admux and digital out channels through a shift register in SPI at the self built card.
    create_channel_str(context, "admux", (class_rmcios)admux_class_rmcios, NULL ) ;

    // Relay outputs at shift register outputs :
    create_channel_str(context, "do0", (class_rmcios)do_class_rmcios, (void *)0 ) ;
    create_channel_str(context, "do1", (class_rmcios)do_class_rmcios, (void *)1 ) ;
    create_channel_str(context, "do2", (class_rmcios)do_class_rmcios, (void *)2 ) ;
    create_channel_str(context, "do3", (class_rmcios)do_class_rmcios, (void *)3 ) ;
    create_channel_str(context, "do4", (class_rmcios)do_class_rmcios, (void *)4 ) ;

	create_channel_str(context, "watchdog", (class_rmcios) watchdog_class_rmcios, NULL) ;
}

#endif
