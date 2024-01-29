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

namespace Printer::GPIO{

  class PinController{

    enum PinDirection{
      Input,
      Output
    };

    struct PinConfig{
        std::string name;
        std::string chip;
        unsigned int offset;
        PinDirection direction;
    };

  public:
    explicit PinController();
    virtual ~PinController();
    void TogglePin(const std::string& label);
    void SendPulse(const std::string& label);
    bool ReadPin(const std::string& label);
    void SetPin(const std::string& label); // Pin high
    void ResetPin(const std::string& label); // Pin low
    void WriteValueToPin(const std::string& label, const bool value); 

  private:
    void OpenFileDescriptors();
    void InitializeBoardPinConfigMapFromArduinoConnectorConfiguration(); 
    void ConfigurePins();

  private:
    std::map<std::string, PinConfig>          m_PinConfigMap;
    std::map<std::string, int>                m_GpioChipFileDescriptors;
    std::map<std::string, gpiohandle_request> m_PinHandleRequests;
    std::map<std::string, gpiohandle_data>    m_PinData;

  private:
    std::map<std::string, std::pair<std::string, PinDirection>> m_ArdiunoConnectorPinConfiguration = { {"Led1",     {"PA14", Output}}
                                                                                                      // {"X-Pulse",     {"ARD_D2", Output}},
                                                                                                      // {"Y-Pulse",     {"ARD_D3", Output}},
                                                                                                      // {"Z-Pulse",     {"ARD_D4", Output}}, 
                                                                                                      // {"X-Direction", {"ARD_D5", Output}}, 
                                                                                                      // {"Y-Direction", {"ARD_D6", Output}}, 
                                                                                                      // {"Z-Direction", {"ARD_D7", Output}}, 
                                                                                                      // {"DriveEnable", {"ARD_D8", Output}}, 
                                                                                                      // {"X-Limit",     {"ARD_D9", Input}},  
                                                                                                      // {"Y-Limit",     {"ARD_D10", Input}}, 
                                                                                                      // {"Z-Limit",     {"ARD_D11", Input}}  
                                                                                                      };
  };
}
