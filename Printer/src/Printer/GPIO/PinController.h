#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/ioctl.h>
#include <linux/gpio.h>
#include <unistd.h>

/* root@stm32mp1:/dev# gpiodetect                                                  
gpiochip0 [GPIOA] (16 lines)                                                    
gpiochip1 [GPIOB] (16 lines)                                                    
gpiochip2 [GPIOC] (16 lines)                                                    
gpiochip3 [GPIOD] (16 lines)                                                    
gpiochip4 [GPIOE] (16 lines)                                                    
gpiochip5 [GPIOF] (16 lines)                                                    
gpiochip6 [GPIOG] (16 lines)                                                    
gpiochip7 [GPIOH] (16 lines)                                                    
gpiochip8 [GPIOI] (12 lines)                                                    
gpiochip9 [GPIOZ] (8 lines)     */                                                 
                                             
/* root@stm32mp1:/dev# gpioinfo                                                    
gpiochip0 - 16 lines:                                                           
        line   0:       "PA0"                   input consumer="wake-up pin"    
        line   1:       "PA1"                   input consumer="kernel"         
        line   2:       "PA2"                   input consumer="kernel"         
        line   3:       "PA3"                   input consumer="kernel"         
        line   4:       "PA4"                   input consumer="kernel"         
        line   5:       "PA5"                   input consumer="kernel"         
        line   6:       "PA6"                   input                           
        line   7:       "PA7"                   input consumer="kernel"         
        line   8:       "PA8"                   input                           
        line   9:       "PA9"                   input consumer="kernel"         
        line  10:       "PA10"                  output active-low consumer="res"
        line  11:       "PA11"                  input                           
        line  12:       "PA12"                  input                           
        line  13:       "PA13"                  output                          
        line  14:       "PA14"                  output                          
        line  15:       "PA15"                  input                           
gpiochip1 - 16 lines:                                                           
        line   0:       "PB0"                   input consumer="kernel"         
        line   1:       "PB1"                   input consumer="kernel"         
        line   2:       "PB2"                   input consumer="kernel"         
        line   3:       "PB3"                   input consumer="kernel"         
        line   4:       "PB4"                   input consumer="kernel"         
        line   5:       "PB5"                   input                           
        line   6:       "PB6"                   input consumer="kernel"         
        line   7:       "PB7"                   input active-low bias=pull-up c"
        line   8:       "PB8"                   input consumer="kernel"         
        line   9:       "PB9"                   input consumer="kernel"         
        line  10:       "PB10"                  input                           
        line  11:       "PB11"                  input consumer="kernel"         
        line  12:       "PB12"                  input                           
        line  13:       "PB13"                  input                           
        line  14:       "PB14"                  input consumer="kernel"         
        line  15:       "PB15"                  input consumer="kernel"         
gpiochip2 - 16 lines:                                                           
        line   0:       "PC0"                   input consumer="kernel"         
        line   1:       "PC1"                   input consumer="kernel"         
        line   2:       "PC2"                   input consumer="kernel"         
        line   3:       "PC3"                   input                           
        line   4:       "PC4"                   input consumer="kernel"         
        line   5:       "PC5"                   input consumer="kernel"         
        line   6:       "PC6"                   input                           
        line   7:       "PC7"                   input                           
        line   8:       "PC8"                   input consumer="kernel"         
        line   9:       "PC9"                   input consumer="kernel"         
        line  10:       "PC10"                  input consumer="kernel"         
        line  11:       "PC11"                  input consumer="kernel"         
        line  12:       "PC12"                  input consumer="kernel"         
        line  13:       "PC13"                  input                           
        line  14:       "PC14"                  input                           
        line  15:       "PC15"                  input                           
gpiochip3 - 16 lines:                                                           
        line   0:       "PD0"                   input consumer="interrupt"      
        line   1:       "PD1"                   input                           
        line   2:       "PD2"                   input consumer="kernel"         
        line   3:       "PD3"                   input consumer="kernel"         
        line   4:       "PD4"                   input consumer="kernel"         
        line   5:       "PD5"                   input consumer="kernel"         
        line   6:       "PD6"                   input consumer="kernel"         
        line   7:       "PD7"                   input                           
        line   8:       "PD8"                   input consumer="kernel"         
        line   9:       "PD9"                   input consumer="kernel"         
        line  10:       "PD10"                  input consumer="kernel"         
        line  11:       "PD11"                  output consumer="heartbeat"     
        line  12:       "PD12"                  input consumer="kernel"         
        line  13:       "PD13"                  input                           
        line  14:       "PD14"                  input                           
        line  15:       "PD15"                  input                           
gpiochip4 - 16 lines:                                                           
        line   0:       "PE0"                   input consumer="kernel"         
        line   1:       "PE1"                   input                           
        line   2:       "PE2"                   input consumer="kernel"         
        line   3:       "PE3"                   input consumer="kernel"         
        line   4:       "PE4"                   output active-low consumer="res"
        line   5:       "PE5"                   input consumer="kernel"         
        line   6:       "PE6"                   input consumer="kernel"         
        line   7:       "PE7"                   input                           
        line   8:       "PE8"                   input                           
        line   9:       "PE9"                   input                           
        line  10:       "PE10"                  input                           
        line  11:       "PE11"                  input                           
        line  12:       "PE12"                  input                           
        line  13:       "PE13"                  input                           
        line  14:       "PE14"                  input                           
        line  15:       "PE15"                  input consumer="kernel"         
gpiochip5 - 16 lines:                                                           
        line   0:       "PF0"                   input                           
        line   1:       "PF1"                   input                           
        line   2:       "PF2"                   input consumer="interrupt"      
        line   3:       "PF3"                   input                           
        line   4:       "PF4"                   input                           
        line   5:       "PF5"                   input                           
        line   6:       "PF6"                   input                           
        line   7:       "PF7"                   input                           
        line   8:       "PF8"                   input                           
        line   9:       "PF9"                   input                           
        line  10:       "PF10"                  input consumer="kernel"         
        line  11:       "PF11"                  input consumer="kernel"         
        line  12:       "PF12"                  input                           
        line  13:       "PF13"                  input                           
        line  14:       "PF14"                  input                           
        line  15:       "PF15"                  input consumer="kernel"         
gpiochip6 - 16 lines:                                                           
        line   0:       "PG0"                   input                           
        line   1:       "PG1"                   input consumer="interrupt"      
        line   2:       "PG2"                   input                           
        line   3:       "PG3"                   input                           
        line   4:       "PG4"                   input consumer="kernel"         
        line   5:       "PG5"                   input consumer="kernel"         
        line   6:       "PG6"                   input consumer="kernel"         
        line   7:       "PG7"                   input consumer="kernel"         
        line   8:       "PG8"                   input                           
        line   9:       "PG9"                   output active-low consumer="res"
        line  10:       "PG10"                  input consumer="kernel"         
        line  11:       "PG11"                  input consumer="kernel"         
        line  12:       "PG12"                  input consumer="kernel"         
        line  13:       "PG13"                  input consumer="kernel"         
        line  14:       "PG14"                  input consumer="kernel"         
        line  15:       "PG15"                  input                           
gpiochip7 - 16 lines:                                                           
        line   0:       "PH0"                   input                           
        line   1:       "PH1"                   input                           
        line   2:       "PH2"                   input consumer="kernel"         
        line   3:       "PH3"                   input consumer="kernel"         
        line   4:       "PH4"                   output active-low consumer="res"
        line   5:       "PH5"                   input                           
        line   6:       "PH6"                   input                           
        line   7:       "PH7"                   input                           
        line   8:       "PH8"                   input consumer="kernel"         
        line   9:       "PH9"                   input consumer="kernel"         
        line  10:       "PH10"                  input consumer="kernel"         
        line  11:       "PH11"                  input                           
        line  12:       "PH12"                  input consumer="kernel"         
        line  13:       "PH13"                  input consumer="kernel"         
        line  14:       "PH14"                  input consumer="kernel"         
        line  15:       "PH15"                  input consumer="kernel"         
gpiochip8 - 12 lines:                                                           
        line   0:       "PI0"                   input consumer="kernel"         
        line   1:       "PI1"                   input consumer="kernel"         
        line   2:       "PI2"                   input consumer="kernel"         
        line   3:       "PI3"                   input consumer="kernel"         
        line   4:       "PI4"                   input consumer="kernel"         
        line   5:       "PI5"                   input consumer="kernel"         
        line   6:       "PI6"                   input consumer="kernel"         
        line   7:       "PI7"                   input consumer="kernel"         
        line   8:       "PI8"                   input consumer="kernel"         
        line   9:       "PI9"                   input consumer="kernel"         
        line  10:       "PI10"                  input consumer="kernel"         
        line  11:       "PI11"                  input consumer="interrupt"      
gpiochip9 - 8 lines:                                                            
        line   0:       "PZ0"                   input                           
        line   1:       "PZ1"                   input                           
        line   2:       "PZ2"                   input                           
        line   3:       "PZ3"                   input                           
        line   4:       "PZ4"                   input consumer="kernel"         
        line   5:       "PZ5"                   input consumer="kernel"         
        line   6:       "PZ6"                   output consumer="shutdown"      
        line   7:       "PZ7"                   input                           
 */
/* 
 Connector Pin name Signal name STM32 pin Comment
CN16
1 NC - NC (reserved for test)
2 3V3 - IOREF 3V3
3 NRST NRST NRST
4 3V3 - 3V3
5 5V - 5V
6 GND - GND
7 GND - GND
8 VIN Not connected
CN17
1 A0 PF14 ADC1_IN0
2 A1 PF13 ADC1_IN1
3 A2 ANA0 ADC1_IN6
4 A3 ANA1 ADC1_IN2
5 A4 PC3/PA12 ADC1_IN13
6 A5 PF12/PA11
CN14
1 ARD_D0 PE7 USART7_RX
2 ARD_D1 PE8 USART7_TX
3 ARD_D2 PE1 IO
4 ARD_D3 PD14 TIM4_CH3
5 ARD_D4 PE10 IO
6 ARD_D5 PD15 TIM4_CH4
7 ARD_D6 PE9 TIM1_CH1
8 ARD_D7 PD1 IO
UM2534
Arduino™ connectors
UM2534 - Rev 1 page 29/47
Connector Pin name Signal name STM32 pin Comment
CN13
1 ARD_D8 PG3 IO
2 ARD_D9 PH6 TIM12_CH1
3 ARD_D10 PE11 SPI4_NSS and TIM1_CH2
4 ARD_D11 PE14 SPI4_MOSI and TIM1_CH4
5 ARD_D12 PE13 SPI4_MISO
6 ARD_D13 PE12 SPI4_SCK
7 GND - GND
8 VREFP - VREF+
9 ARD_D14 PA12 I2C5_SDA
10 ARD_D15 PA11 I2C5_SCL */

namespace Printer {

  class PinController {

    struct gpiohandle_request req;
    struct gpiohandle_data data;

  public:
    explicit PinController();
    virtual ~PinController();
  private:
    
  };

}