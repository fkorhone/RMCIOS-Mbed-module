#ifndef mbed_channels_h
#define mbed_channels_h

extern void init_mbed_channels(const struct context_rmcios *context) ; // Initialize & add generic mbed channels
extern void init_mbed_platform_channels(const struct context_rmcios *context) ; // initialize & add mbed platform specific channels
extern void init_mbed_ethernet_channels(const struct context_rmcios *context) ; // initialize & add ethernet channels

#endif

