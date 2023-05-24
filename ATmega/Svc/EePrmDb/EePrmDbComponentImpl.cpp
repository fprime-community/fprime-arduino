// ======================================================================
// \title  EePrmDbComponentImpl.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Parameter database for storing changes that persist across reboots, in the ATmega internal EEPROM.
// ======================================================================


#include <ATmega/Svc/EePrmDb/EePrmDbComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <Fw/Types/Assert.hpp>
#include <ATmega/Svc/EePrmDb/paramTest.h>
U16 paramSaveCounter = 0;


// NOTE: This will fail if debug printing is enabled for non-Arduino platforms.
#ifdef DEBUG_EE_PRM_DB
  #ifdef ARDUINO
    #include <Arduino.h>
  #endif
  #ifndef DEBUG_Serial
    #define DEBUG_Serial Serial
  #endif
#endif

namespace ATmega {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  EePrmDbComponentImpl ::
#if FW_OBJECT_NAMES == 1
    EePrmDbComponentImpl(
        const char *const compName
    ) :
      EePrmDbComponentBase(compName)
#else
    EePrmDbComponentImpl(void)
#endif
  {
  }

  void EePrmDbComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance,
        const NATIVE_INT_TYPE startAddr, /*!< Bottom of database*/
        const NATIVE_INT_TYPE endAddr /*!< Top of database*/
    )
  {
    EePrmDbComponentBase::init(instance);
    this->m_startAddr = startAddr;
    this->m_endAddr = endAddr;
    this->m_totalSlotCount = (endAddr - startAddr) / SlotSize;
#ifdef DEBUG_EE_PRM_DB
    DEBUG_Serial.print("EE Start: ");
    DEBUG_Serial.println(m_startAddr);
    DEBUG_Serial.print("EE Stop: ");
    DEBUG_Serial.println(m_endAddr);
    DEBUG_Serial.print("EE Slot Count: ");
    DEBUG_Serial.println(m_totalSlotCount);
#endif
  }

  EePrmDbComponentImpl ::
    ~EePrmDbComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  Fw::ParamValid EePrmDbComponentImpl ::
    getPrm_handler(
        const NATIVE_INT_TYPE portNum,
        FwPrmIdType id,
        Fw::ParamBuffer &val
    )
  {
#ifdef DEBUG_EE_PRM_DB
    DEBUG_Serial.print(F("Get port call was made, looking for ID: "));
    DEBUG_Serial.println(id);
#endif
    // search for entry
    Fw::ParamValid stat = Fw::PARAM_INVALID;
    // NATIVE_UINT_TYPE length;

    for (NATIVE_INT_TYPE entry = 0; entry < m_totalSlotCount; entry++) {
      if (isUsed(entry)) {
#ifdef DEBUG_EE_PRM_DB
        DEBUG_Serial.print(F("checking entry index: "));
        DEBUG_Serial.println(entry);
#endif
        // if the slot is used, the m_idCache variable holds the ID already
        if (this->m_idCache == id) {
          loadEeSlotContents(entry);
          U8* buf = val.getBuffAddr();
#ifdef DEBUG_EE_PRM_DB
          DEBUG_Serial.print(F("Retrieved Param: "));
          DEBUG_Serial.println(m_prmBufCache.entry.id);
          DEBUG_Serial.print(F("Value: 0x"));
#endif
          for(NATIVE_UINT_TYPE i = 0; i<m_prmBufCache.entry.length; i++)
          {
            buf[i] = m_prmBufCache.entry.buffer[i];
#ifdef DEBUG_EE_PRM_DB
            DEBUG_Serial.print(buf[i], HEX);
#endif
          }
          val.setBuffLen(m_prmBufCache.entry.length);
#ifdef DEBUG_EE_PRM_DB
          DEBUG_Serial.println();
#endif
          stat = Fw::PARAM_VALID;
          break;
        }
#ifdef DEBUG_EE_PRM_DB
        else
        {
          DEBUG_Serial.print(F("entry ID was: "));
          DEBUG_Serial.println(this->m_idCache);
        }
#endif
      }
    }

    // if unable to find parameter, send error message
    if (Fw::PARAM_INVALID == stat) {
      this->log_WARNING_LO_PrmIdNotFound(id);
    }

    return stat;
  }

  void EePrmDbComponentImpl ::
    setPrm_handler(
        const NATIVE_INT_TYPE portNum,
        FwPrmIdType id,
        Fw::ParamBuffer &val
    )
  {
    //Increment the param save counter
    paramSaveCounter++;

    this->lock();

#ifdef DEBUG_EE_PRM_DB
    DEBUG_Serial.println(F("Got set param request"));
    DEBUG_Serial.print(F("Param ID: "));
    DEBUG_Serial.println(id);
    DEBUG_Serial.print(F("Capacity: "));
    DEBUG_Serial.println(val.getBuffLength());
    DEBUG_Serial.print(F("Buff Contents: 0x"));
#endif
    U8* val_arr = reinterpret_cast<U8*>(val.getBuffAddr());
#ifdef DEBUG_EE_PRM_DB
    for(NATIVE_UINT_TYPE i=0; i<val.getBuffLength(); i++)
    {
      DEBUG_Serial.print(val_arr[i], HEX);
    }
    DEBUG_Serial.println();
#endif

    // 0xFF out the buffer
    for(NATIVE_UINT_TYPE i=0; i<EE_PRM_DB_SLOT_SIZE; i++)
    {
      m_prmBufCache.buffer[i] = 0xFF;
    }

    m_prmBufCache.entry.id = id;
    m_prmBufCache.entry.length = val.getBuffLength();

    FW_ASSERT(  // If its too big to fit, somebody did something wrong
      (val.getBuffLength()+3) <= EE_PRM_DB_SLOT_SIZE,
      (val.getBuffLength()+3)
    );

    for(NATIVE_UINT_TYPE i=0; i<val.getBuffLength(); i++)
    {
      m_prmBufCache.entry.buffer[i] = val_arr[i];
    }

    // search for existing entry
    // NATIVE_UINT_TYPE length = SlotSize - 2;
    bool existingEntry = false;
    bool noSlots = true;

    for (NATIVE_INT_TYPE entry = 0; entry < m_totalSlotCount; entry++) {
      if (isUsed(entry) && (this->m_idCache == id)) {
        // val.serialize(m_prmBufCache, length, false);
        saveEeSlotContents(entry);
        existingEntry = true;
        break;
      }
    }

    // if there is no existing entry, add one
    if (!existingEntry) {
      for (NATIVE_INT_TYPE entry = 0; entry < m_totalSlotCount; entry++) {
        if (!(isUsed(entry))) {
          // val.serialize(m_prmBufCache, length, false);
          saveEeSlotContents(entry);
          // setDbEntryId(entry, (NATIVE_INT_TYPE)id);
          noSlots = false;
          break;
        }
      }
    }

    this->unLock();

    if (existingEntry) {
      this->log_ACTIVITY_HI_PrmIdUpdated(id);
    } else if (noSlots) {
      this->log_FATAL_PrmDbFull(id);
    } else {
      this->log_ACTIVITY_HI_PrmIdAdded(id);
    }

  }

  NATIVE_INT_TYPE EePrmDbComponentImpl ::
    getEeAddr(NATIVE_INT_TYPE slotIndex)
  {
    return (slotIndex * SlotSize + m_startAddr);
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void EePrmDbComponentImpl ::
    PARAMETER_FACTORY_RESET_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    clearDb();
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
    // TODO: make sure this somehow allows the response to get out
    FW_ASSERT(0); // Must restart to force defaults refresh
  }

} // end namespace ATmega
