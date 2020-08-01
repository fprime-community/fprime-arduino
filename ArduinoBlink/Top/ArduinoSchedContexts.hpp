/*
 * ArduinoSchedContexts.hpp
 *
 *  Created on: Mar 2, 2019
 *      Author: lestarch
 */

#ifndef RPI_TOP_ARDUINOSCHEDCONTEXTS_HPP_
#define RPI_TOP_ARDUINOSCHEDCONTEXTS_HPP_

namespace Arduino {
    // A list of contexts for the rate groups
    enum {
        CONTEXT_RPI_DEMO_1Hz = 10, // 10Hz cycle
        CONTEXT_RPI_DEMO_10Hz = 11 // 1 Hz cycle
    };
}



#endif /* ARDUINO_TOP_RPISCHEDCONTEXTS_HPP_ */
