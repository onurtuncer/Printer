#pragma once

#include <map>
#include <string>
#include <unordered_map>

struct Stm32mp157f{

  static const std::map<std::string, std::pair<std::string, int>> GpioMap;
  static const std::map<std::string, std::string> arduinoConnectorToBoardPinMap;

  static std::pair<std::string, int> GetChipAndLineFromArduinoConnectorPin(const std::string &arduinoPin){
      auto stm32pin = arduinoConnectorToBoardPinMap.at(arduinoPin); 
      return GpioMap.at(stm32pin);
  }

   static std::string GetStm32PinArduinoConnectorPin(const std::string& arduinoPin){
      auto stm32pin = arduinoConnectorToBoardPinMap.at(arduinoPin); 
      return stm32pin;
  }
};

const std::map<std::string, std::pair<std::string, int>> Stm32mp157f::GpioMap = {
                                                                                 {"PA0", {"gpiochip0", 0}},
                                                                                 {"PA1", {"gpiochip0", 1}},
                                                                                 {"PA2", {"gpiochip0", 2}},
                                                                                 {"PA3", {"gpiochip0", 3}},
                                                                                 {"PA4", {"gpiochip0", 4}},
                                                                                 {"PA5", {"gpiochip0", 5}},
                                                                                 {"PA6", {"gpiochip0", 6}},
                                                                                 {"PA7", {"gpiochip0", 7}},
                                                                                 {"PA8", {"gpiochip0", 8}},
                                                                                 {"PA9", {"gpiochip0", 9}},
                                                                                 {"PA10", {"gpiochip0", 10}},
                                                                                 {"PA11", {"gpiochip0", 11}},
                                                                                 {"PA12", {"gpiochip0", 12}},
                                                                                 {"PA13", {"gpiochip0", 13}},
                                                                                 {"PA14", {"gpiochip0", 14}},
                                                                                 {"PA15", {"gpiochip0", 15}},
                                                                                 {"PB0", {"gpiochip1", 0}},
                                                                                 {"PB1", {"gpiochip1", 1}},
                                                                                 {"PB2", {"gpiochip1", 2}},
                                                                                 {"PB3", {"gpiochip1", 3}},
                                                                                 {"PB4", {"gpiochip1", 4}},
                                                                                 {"PB5", {"gpiochip1", 5}},
                                                                                 {"PB6", {"gpiochip1", 6}},
                                                                                 {"PB7", {"gpiochip1", 7}},
                                                                                 {"PB8", {"gpiochip1", 8}},
                                                                                 {"PB9", {"gpiochip1", 9}},
                                                                                 {"PB10", {"gpiochip1", 10}},
                                                                                 {"PB11", {"gpiochip1", 11}},
                                                                                 {"PB12", {"gpiochip1", 12}},
                                                                                 {"PB13", {"gpiochip1", 13}},
                                                                                 {"PB14", {"gpiochip1", 14}},
                                                                                 {"PB15", {"gpiochip1", 15}},
                                                                                 {"PC0", {"gpiochip2", 0}},
                                                                                 {"PC1", {"gpiochip2", 1}},
                                                                                 {"PC2", {"gpiochip2", 2}},
                                                                                 {"PC3", {"gpiochip2", 3}},
                                                                                 {"PC4", {"gpiochip2", 4}},
                                                                                 {"PC5", {"gpiochip2", 5}},
                                                                                 {"PC6", {"gpiochip2", 6}},
                                                                                 {"PC7", {"gpiochip2", 7}},
                                                                                 {"PC8", {"gpiochip2", 8}},
                                                                                 {"PC9", {"gpiochip2", 9}},
                                                                                 {"PC10", {"gpiochip2", 10}},
                                                                                 {"PC11", {"gpiochip2", 11}},
                                                                                 {"PC12", {"gpiochip2", 12}},
                                                                                 {"PC13", {"gpiochip2", 13}},
                                                                                 {"PC14", {"gpiochip2", 14}},
                                                                                 {"PC15", {"gpiochip2", 15}},
                                                                                 {"PD0", {"gpiochip3", 0}},
                                                                                 {"PD1", {"gpiochip3", 1}},
                                                                                 {"PD2", {"gpiochip3", 2}},
                                                                                 {"PD3", {"gpiochip3", 3}},
                                                                                 {"PD4", {"gpiochip3", 4}},
                                                                                 {"PD5", {"gpiochip3", 5}},
                                                                                 {"PD6", {"gpiochip3", 6}},
                                                                                 {"PD7", {"gpiochip3", 7}},
                                                                                 {"PD8", {"gpiochip3", 8}},
                                                                                 {"PD9", {"gpiochip3", 9}},
                                                                                 {"PD10", {"gpiochip3", 10}},
                                                                                 {"PD11", {"gpiochip3", 11}},
                                                                                 {"PD12", {"gpiochip3", 12}},
                                                                                 {"PD13", {"gpiochip3", 13}},
                                                                                 {"PD14", {"gpiochip3", 14}},
                                                                                 {"PD15", {"gpiochip3", 15}},
                                                                                 {"PE0", {"gpiochip4", 0}},
                                                                                 {"PE1", {"gpiochip4", 1}},
                                                                                 {"PE2", {"gpiochip4", 2}},
                                                                                 {"PE3", {"gpiochip4", 3}},
                                                                                 {"PE4", {"gpiochip4", 4}},
                                                                                 {"PE5", {"gpiochip4", 5}},
                                                                                 {"PE6", {"gpiochip4", 6}},
                                                                                 {"PE7", {"gpiochip4", 7}},
                                                                                 {"PE8", {"gpiochip4", 8}},
                                                                                 {"PE9", {"gpiochip4", 9}},
                                                                                 {"PE10", {"gpiochip4", 10}},
                                                                                 {"PE11", {"gpiochip4", 11}},
                                                                                 {"PE12", {"gpiochip4", 12}},
                                                                                 {"PE13", {"gpiochip4", 13}},
                                                                                 {"PE14", {"gpiochip4", 14}},
                                                                                 {"PE15", {"gpiochip4", 15}},
                                                                                 {"PF0", {"gpiochip5", 0}},
                                                                                 {"PF1", {"gpiochip5", 1}},
                                                                                 {"PF2", {"gpiochip5", 2}},
                                                                                 {"PF3", {"gpiochip5", 3}},
                                                                                 {"PF4", {"gpiochip5", 4}},
                                                                                 {"PF5", {"gpiochip5", 5}},
                                                                                 {"PF6", {"gpiochip5", 6}},
                                                                                 {"PF7", {"gpiochip5", 7}},
                                                                                 {"PF8", {"gpiochip5", 8}},
                                                                                 {"PF9", {"gpiochip5", 9}},
                                                                                 {"PF10", {"gpiochip5", 10}},
                                                                                 {"PF11", {"gpiochip5", 11}},
                                                                                 {"PF12", {"gpiochip5", 12}},
                                                                                 {"PF13", {"gpiochip5", 13}},
                                                                                 {"PF14", {"gpiochip5", 14}},
                                                                                 {"PF15", {"gpiochip5", 15}},
                                                                                 {"PG0", {"gpiochip6", 0}},
                                                                                 {"PG1", {"gpiochip6", 1}},
                                                                                 {"PG2", {"gpiochip6", 2}},
                                                                                 {"PG3", {"gpiochip6", 3}},
                                                                                 {"PG4", {"gpiochip6", 4}},
                                                                                 {"PG5", {"gpiochip6", 5}},
                                                                                 {"PG6", {"gpiochip6", 6}},
                                                                                 {"PG7", {"gpiochip6", 7}},
                                                                                 {"PG8", {"gpiochip6", 8}},
                                                                                 {"PG9", {"gpiochip6", 9}},
                                                                                 {"PG10", {"gpiochip6", 10}},
                                                                                 {"PG11", {"gpiochip6", 11}},
                                                                                 {"PG12", {"gpiochip6", 12}},
                                                                                 {"PG13", {"gpiochip6", 13}},
                                                                                 {"PG14", {"gpiochip6", 14}},
                                                                                 {"PG15", {"gpiochip6", 15}},
                                                                                 {"PH0", {"gpiochip7", 0}},
                                                                                 {"PH1", {"gpiochip7", 1}},
                                                                                 {"PH2", {"gpiochip7", 2}},
                                                                                 {"PH3", {"gpiochip7", 3}},
                                                                                 {"PH4", {"gpiochip7", 4}},
                                                                                 {"PH5", {"gpiochip7", 5}},
                                                                                 {"PH6", {"gpiochip7", 6}},
                                                                                 {"PH7", {"gpiochip7", 7}},
                                                                                 {"PH8", {"gpiochip7", 8}},
                                                                                 {"PH9", {"gpiochip7", 9}},
                                                                                 {"PH10", {"gpiochip7", 10}},
                                                                                 {"PH11", {"gpiochip7", 11}},
                                                                                 {"PH12", {"gpiochip7", 12}},
                                                                                 {"PH13", {"gpiochip7", 13}},
                                                                                 {"PH14", {"gpiochip7", 14}},
                                                                                 {"PH15", {"gpiochip7", 15}},
                                                                                 {"PI0", {"gpiochip8", 0}},
                                                                                 {"PI1", {"gpiochip8", 1}},
                                                                                 {"PI2", {"gpiochip8", 2}},
                                                                                 {"PI3", {"gpiochip8", 3}},
                                                                                 {"PI4", {"gpiochip8", 4}},
                                                                                 {"PI5", {"gpiochip8", 5}},
                                                                                 {"PI6", {"gpiochip8", 6}},
                                                                                 {"PI7", {"gpiochip8", 7}},
                                                                                 {"PI8", {"gpiochip8", 8}},
                                                                                 {"PI9", {"gpiochip8", 9}},
                                                                                 {"PI10", {"gpiochip8", 10}},
                                                                                 {"PI11", {"gpiochip8", 11}},
                                                                                 {"PZ0", {"gpiochip9", 0}},
                                                                                 {"PZ1", {"gpiochip9", 1}},
                                                                                 {"PZ2", {"gpiochip9", 2}},
                                                                                 {"PZ3", {"gpiochip9", 3}},
                                                                                 {"PZ4", {"gpiochip9", 4}},
                                                                                 {"PZ5", {"gpiochip9", 5}},
                                                                                 {"PZ6", {"gpiochip9", 6}},
                                                                                 {"PZ7", {"gpiochip9", 7}}};

const std::map<std::string, std::string> Stm32mp157f::arduinoConnectorToBoardPinMap = {
                                                                                        {"ARD_D0", "PE7"},
                                                                                        {"ARD_D1", "PE8"},
                                                                                        {"ARD_D2", "PE1"},
                                                                                        {"ARD_D3", "PD14"},
                                                                                        {"ARD_D4", "PE10"},
                                                                                        {"ARD_D5", "PD15"},
                                                                                        {"ARD_D6", "PE9"},
                                                                                        {"ARD_D7", "PD1"},
                                                                                        {"ARD_D8", "PG3"},
                                                                                        {"ARD_D9", "PH6"},
                                                                                        {"ARD_D10", "PE11"},
                                                                                        {"ARD_D11", "PE14"},
                                                                                        {"ARD_D12", "PE13"},
                                                                                        {"ARD_D13", "PE12"},
                                                                                        {"ARD_D14", "PA12"},
                                                                                        {"ARD_D15", "PA11"},
                                                                                        {"PA14",    "PA14"}};

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