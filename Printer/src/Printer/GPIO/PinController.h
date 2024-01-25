#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/ioctl.h>
#include <linux/gpio.h>
#include <unistd.h>
#include <fcntl.h>
#include <map>
#include <set>
#include "STM32MP157F-DK2.h"

namespace Printer{

  class PinController{

    enum PinDirection{
      Input,
      Output
    };

    struct PinConfig{
        std::string chip;
        unsigned int offset;
        PinDirection direction;
    };

  public:
    explicit PinController();
    virtual ~PinController();

  private:
    void ConfigureGPIOLine(const PinConfig &pinConfig, int fd, unsigned int flags);
    void SetGPIOLineValue(int fd, unsigned int offset, int value);
    int  GetGPIOLineValue(int fd, unsigned int offset);
    void InitializeBoardPinConfigMapFromArduinoConnectorConfiguration(); 

  private:
   /*  std::map<std::string, PinConfig> m_PinConfigMap = {
                                                        {"LED1", {"gpiochip0", 0, Output}},
                                                        {"LED2", {"gpiochip0", 1, Output}},
                                                        {"BUTTON1", {"gpiochip1", 2, Input}},
                                                        {"BUTTON2", {"gpiochip1", 3, Input}}
                                                       }; */
    std::map<std::string, PinConfig> m_PinConfigMap;

    std::map<std::string, int> m_GpioChipFileDescriptors;

  private:
    std::map<std::string, std::pair<std::string, PinDirection>> m_ArdiunoConnectorPinConfiguration = {
                                                                                                      {"X-Pulse",     {"ARD_D2", Output}},
                                                                                                      {"Y-Pulse",     {"ARD_D3", Output}},
                                                                                                      {"Z-Pulse",     {"ARD_D4", Output}}, 
                                                                                                      {"X-Direction", {"ARD_D5", Output}}, 
                                                                                                      {"Y-Direction", {"ARD_D6", Output}}, 
                                                                                                      {"Z-Direction", {"ARD_D7", Output}}, 
                                                                                                      {"DriveEnable", {"ARD_D8", Output}}, 
                                                                                                      {"X-Limit",     {"ARD_D9", Input}},  
                                                                                                      {"Y-Limit",     {"ARD_D10", Input}}, 
                                                                                                      {"Z-Limit",     {"ARD_D11", Input}}  
                                                                                                      };

  };

}
