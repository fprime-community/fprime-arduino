// ======================================================================
// \title  EePrmDbComponentLinuxImpl.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Parameter database for storing changes that persist across reboots, in the ATmega internal EEPROM.
// ======================================================================

#include <ATmega/Svc/EePrmDb/EePrmDbComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace ATmega {

  void EePrmDbComponentImpl ::
    clearDb(void) {
      // TODO...
    }

  bool EePrmDbComponentImpl ::
    isUsed(NATIVE_INT_TYPE slotIndex) {
      // TODO...
      return false;
    }

  void EePrmDbComponentImpl ::
    setDbEntryId(NATIVE_INT_TYPE slotIndex, NATIVE_INT_TYPE id) {
      // TODO...
    }

  void  EePrmDbComponentImpl ::
    loadEeSlotContents(NATIVE_INT_TYPE slotIndex) {
      // TODO...
    }

  void  EePrmDbComponentImpl ::
    saveEeSlotContents(NATIVE_INT_TYPE slotIndex) {
      // TODO...
    }

} // end namespace ATmega
