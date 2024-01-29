#include "PinController.h"
#include "Core/Log.h"

namespace Printer::GPIO{

  void Controller::InitializeBoardPinConfigMapFromArduinoConnectorConfiguration(){

    for (const auto &entry : m_ArdiunoConnectorPinConfiguration){
        
      std::string  arduinoPin = entry.second.first;
      PinDirection direction  = entry.second.second;
      Stm32mp157f board;
      auto stm32name = board.GetStm32PinArduinoConnectorPin(arduinoPin);
      auto chipAndLine = board.GetChipAndLineFromArduinoConnectorPin(arduinoPin);
      PinConfig config{};
      config.name = stm32name;
      config.chip = chipAndLine.first;
      // config.line = chipAndLine.second;
      config.direction = direction;    
      m_PinConfigMap[entry.first] = config;
    }
  }

  void PinController::OpenFileDescriptors(){

    for (const auto &entry : m_PinConfigMap){

      const std::string& chipName = entry.second.chip;

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

  void PinController::ConfigurePins(){

    for (const auto &entry : m_PinConfigMap){

      const std::string& label = entry.first;
      const std::string& chipName = entry.second.chip;

      struct gpiohandle_request req;
      struct gpiohandle_data data;

      req.lineoffsets[0] = entry.second.offset;
      PinDirection dir = entry.second.direction;

      if (dir == Output) {
        req.flags = GPIOHANDLE_REQUEST_OUTPUT;
      } else{
        req.flags = GPIOHANDLE_REQUEST_INPUT;
      }

      memcpy(req.default_values, &data, sizeof(req.default_values));
      strcpy(req.consumer_label, label.c_str());
      req.lines  = 1;

      auto fd = m_GpioChipFileDescriptors.at(chipName);

      auto ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);

	    if (ret == -1) {
		    ret = -errno;
		    fprintf(stderr, "Failed to issue GET LINEHANDLE IOCTL (%d)\n", ret);
	    }

      m_PinHandleRequests[label] = req;
      m_PinData[label] = data;
    }
  }

  void PinController::TogglePin(const std::string& label){

    auto req = m_PinHandleRequests.at(label);
    auto data = m_PinData.at(label);

    data.values[0] = !data.values[0];

    auto ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		if (ret == -1) {
			ret = -errno;
			fprintf(stderr, "Failed to issue %s (%d)\n", "GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret);
		}
  }

  void PinController::SendPulse(const std::string& label){

    TogglePin(label);
    TogglePin(label);
  }

   bool PinController::ReadPin(const std::string& label){

     auto req = m_PinHandleRequests.at(label);
     bool data;  // Assuming the pin value is boolean

     auto ret = ioctl(req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);

     if (ret != -1) {
      return data;
    } else {
       ret = -errno;
       throw std::runtime_error("Failed to read pin value");
    }
   }

  void PinController::SetPin(const std::string& label){

    auto req = m_PinHandleRequests.at(label);
    auto data = true;

    auto ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		if (ret == -1) {
			ret = -errno;
			fprintf(stderr, "Failed to issue %s (%d)\n", "GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret);
		}
  }

  void PinController::ResetPin(const std::string& label){

    auto req = m_PinHandleRequests.at(label);
    auto data = false;

    auto ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		if (ret == -1) {
			ret = -errno;
			fprintf(stderr, "Failed to issue %s (%d)\n", "GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret);
		}
  }

  void PinController::WriteValueToPin(const std::string& label, const bool value){

    auto req = m_PinHandleRequests.at(label);
    auto data = value;

    auto ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		if (ret == -1) {
			ret = -errno;
			fprintf(stderr, "Failed to issue %s (%d)\n", "GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret);
		}
  }

  PinController::PinController() {

    InitializeBoardPinConfigMapFromArduinoConnectorConfiguration();
    OpenFileDescriptors();
    ConfigurePins();  
  }
    
  PinController::~PinController() {

    for (const auto &entry : m_GpioChipFileDescriptors){
      close(entry.second);
    }
  }

}
