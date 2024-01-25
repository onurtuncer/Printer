#include "PinController.h"
#include "Core/Log.h"

namespace Printer{

    void PinController::InitializeBoardPinConfigMapFromArduinoConnectorConfiguration(){

        PinConfig config{};
    }

  PinController::PinController() {

    InitializeBoardPinConfigMapFromArduinoConnectorConfiguration();

    for (const auto &entry : m_PinConfigMap){

          const std::string &chipName = entry.second.chip;

          // Check if the GPIO chip is already opened
          if (m_GpioChipFileDescriptors.find(chipName) == m_GpioChipFileDescriptors.end()){

              int fd = open(("/dev/" + chipName).c_str(), O_RDWR);

              if (fd < 0) {
                  perror(("Error opening GPIO character device " + chipName).c_str());
                  // Handle error as needed
              }
              else {

                  std::cout << "Successfully opened GPIO character device " << chipName << ". File descriptor: " << fd << std::endl;
                  m_GpioChipFileDescriptors[chipName] = fd;
              }
          }
      }
    }
    
    PinController::~PinController() {

        for (const auto &entry : m_GpioChipFileDescriptors){
            close(entry.second);
        }
    }

    void PinController::ConfigureGPIOLine(const PinConfig &pinConfig, int fd, unsigned int flags) {

        struct gpiohandle_request req =
        {
            .flags = flags,
            .lines = 1,
            .default_values = NULL,
            .consumer_label = ("gpio_" + pinConfig.chip + "_" + std::to_string(pinConfig.offset)).c_str(),
            .fd = -1,
            .gpiooffset = pinConfig.offset,

            if (ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req) < 0){
                perror(("Error configuring GPIO line for " + pinConfig.chip + " offset " + std::to_string(pinConfig.offset)).c_str());
    }
    else
    {
        std::cout << "Successfully configured GPIO line for " << pinConfig.chip << " offset " << pinConfig.offset << ". File descriptor: " << req.fd << std::endl;
        // Perform additional GPIO operations using req.fd
        close(req.fd); // Close the file descriptor when done
    }
}
}

    int PinController::GetGPIOLineValue(int fd, unsigned int offset){

        struct gpiohandle_data data = {
            .values = {0}, // Initialize all elements to 0
            .mask = 1 << offset};

        if (ioctl(fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data) < 0)
        {
            perror(("Error getting GPIO line value for file descriptor " + std::to_string(fd) + " offset " + std::to_string(offset)).c_str());
            return -1; // Error
        }

        return data.values[0];
    }

    void PinController::SetGPIOLineValue(int fd, unsigned int offset, int value){

        struct gpiohandle_data data = {
            .values = &value,
            .mask = 1 << offset,
        };

        if (ioctl(fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data) < 0){
            perror(("Error setting GPIO line value for file descriptor " + std::to_string(fd) + " offset " + std::to_string(offset)).c_str());
        }
    }
}