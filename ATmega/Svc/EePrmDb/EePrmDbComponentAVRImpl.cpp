// ======================================================================
// \title  EePrmDbComponentAVRImpl
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Parameter database for storing changes that persist across reboots, in the ATmega internal EEPROM.
// ======================================================================

#include <ATmega/Svc/EePrmDb/EePrmDbComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <avr/eeprom.h>
#include <avr/wdt.h>


namespace ATmega {

  void EePrmDbComponentImpl ::
    clearDb(void) {
      // loop through all the EEPROM cells and set to 0xFF, the value
      //  that would be in the virgin cells.
      // TODO: This should check for bad cells and report them.
      for (NATIVE_INT_TYPE cell = this->m_startAddr; cell < this->m_endAddr; cell++) {
        eeprom_update_byte((uint8_t*)cell, 0xFF);
        wdt_reset();
      }
    }

  bool EePrmDbComponentImpl ::
    isUsed(NATIVE_INT_TYPE slotIndex) {
      NATIVE_INT_TYPE addr = getEeAddr(slotIndex);
      m_idCache = eeprom_read_word((uint16_t *)addr);
      if(m_idCache == EE_VACANT_SLOT){return false;}
      return true;
    }

  void EePrmDbComponentImpl ::
    setDbEntryId(NATIVE_INT_TYPE slotIndex, NATIVE_INT_TYPE id) {
      eeprom_update_word((uint16_t *)getEeAddr(slotIndex), id);
    }

  void  EePrmDbComponentImpl ::
    loadEeSlotContents(NATIVE_INT_TYPE slotIndex) {
      eeprom_read_block ((void *) &m_prmBufCache, (const void *)getEeAddr(slotIndex), EE_PRM_DB_SLOT_SIZE);
    }

  void  EePrmDbComponentImpl ::
    saveEeSlotContents(NATIVE_INT_TYPE slotIndex) {
      eeprom_update_block((const void *) &m_prmBufCache, (void *)getEeAddr(slotIndex), EE_PRM_DB_SLOT_SIZE);
    }

} // end namespace ATmega
