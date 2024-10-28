#ifndef ARDUINOTIMEIMPL_HPP_
#define ARDUINOTIMEIMPL_HPP_

#include <Arduino/ArduinoTime/ArduinoTimeComponentAc.hpp>
#include <Arduino/Os/RawTime.hpp>

namespace Arduino {

class ArduinoTime : public ArduinoTimeComponentBase {
  public:
    ArduinoTime(const char* compName);
    virtual ~ArduinoTime();
    void init(NATIVE_INT_TYPE instance);

  protected:
    void timeGetPort_handler(NATIVE_INT_TYPE portNum, /*!< The port number*/
                             Fw::Time& time           /*!< The U32 cmd argument*/
    );

  private:
    Os::Arduino::RawTime::ArduinoRawTime rawTime;
};

}  // namespace Arduino

#endif /* ARDUINOTIMEIMPL_HPP_ */
