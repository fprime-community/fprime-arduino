// ======================================================================
// \title  EePrmDbComponentImpl.hpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Parameter database for storing changes that persist across reboots, in the ATmega internal EEPROM.
// ======================================================================

#ifndef EePrmDb_HPP
#define EePrmDb_HPP

#include "ATmega/Svc/EePrmDb/EePrmDbComponentAc.hpp"
#include <Os/Mutex.hpp>

namespace ATmega {

#ifndef EE_PRM_DB_SLOT_SIZE
#define EE_PRM_DB_SLOT_SIZE 8
#endif
    const U8 SlotSize = EE_PRM_DB_SLOT_SIZE;
    const U16 EE_VACANT_SLOT = 0xFFFF;
    const int EE_SLOT_METADATA_SIZE = 3; // must be in snyc with EE_PRM_DB_SLOT_T
    const int EE_MAX_PARAM_SIZE = EE_PRM_DB_SLOT_SIZE - EE_SLOT_METADATA_SIZE;

    //! Struct defining layout of paramter slot bytes
    struct EE_PRM_DB_SLOT_T{
      U16 id;
      U8 length;
      U8 buffer[EE_MAX_PARAM_SIZE];
    }__attribute__((__packed__));

    //! Union for easy EEPROM serialization and deserialization
    union EE_PRM_DB_SER {
      EE_PRM_DB_SLOT_T entry;
      U8 buffer[EE_PRM_DB_SLOT_SIZE];
    };

    //! \class EePrmDbComponentImpl
    //! \brief Component class for managing parameters
    //!
    //! This component supports storing, setting and saving of serialized parameters
    //! for components.

  class EePrmDbComponentImpl :
    public EePrmDbComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      // friend class PrmDbImplTester; // future work

      //!  EePrmDb constructor
      //!
      //!  The constructor for the PrmDbImpl class.
      //!   The constructor clears the database and stores
      //!   the file name for opening later.
      //!
      //!  \param name component instance name
      //!  \param file file where parameters are stored.
      //!
      EePrmDbComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //!  EePrmDb initialization function
      //!
      //!  The initialization function for the component initializes the
      //!   component base classes, and configures the designated
      //!   EEPROM address space for the database.
      //!
      //!  \param instance instance of component, if more than one is needed.
      //!  \param lowest memory address of the contiguous alotted EEPROM memory.
      //!  \param highest memory address of the contiguous alloted EEPROM memory.
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0, /*!< The instance number*/
          const NATIVE_INT_TYPE startAddr = 32, /*!< Bottom of database*/
          const NATIVE_INT_TYPE endAddr = 1024 /*!< Top of database*/
      );

      //! Destroy object EePrmDb
      //!
      ~EePrmDbComponentImpl(void);

    PRIVATE:

      NATIVE_INT_TYPE m_startAddr;
      NATIVE_INT_TYPE m_endAddr;
      NATIVE_INT_TYPE m_totalSlotCount;
      NATIVE_UINT_TYPE m_idCache;
      EE_PRM_DB_SER m_prmBufCache;

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //!  PrmDb parameter get handler
      //!
      //!  This function retrieves a parameter value from the loaded set of stored parameters
      //!
      //!  \param portNum input port number. Should always be zero
      //!  \param id identifier for parameter being used.
      //!  \param val buffer where value is placed.
      //!  \return status of retrieval. PARAM_VALID = successful read, PARAM_INVALID = unsuccessful read
      //!
      Fw::ParamValid getPrm_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwPrmIdType id, /*!< Parameter ID*/
          Fw::ParamBuffer &val /*!< Buffer containing serialized parameter value*/
      );

      //!  PrmDb parameter set handler
      //!
      //!  This function updates the value of the parameter stored in RAM. The PRM_SAVE_FILE
      //!  must be called to save the value to a file.
      //!
      //!  \param portNum input port number. Should always be zero
      //!  \param id identifier for parameter being used.
      //!  \param val buffer where value to be saved is stored.
      //!
      void setPrm_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwPrmIdType id, /*!< Parameter ID*/
          Fw::ParamBuffer &val /*!< Buffer containing serialized parameter value*/
      );

      //!  EePrmDb clear database function
      //!
      //!  This function clears all entries from the EEPROM database
      //!
      void clearDb(void); //!< clear the parameter database

      //!  EePrmDb used slot function
      //!
      //!  This function to determines if a slot is used or vacant.
      //!
      bool isUsed(NATIVE_INT_TYPE slotIndex);

      //!  EePrmDb address conversion function
      //!
      //!  This function converts a slot index to an EEPROM address.
      //!
      NATIVE_INT_TYPE getEeAddr(NATIVE_INT_TYPE slotIndex);

      //!  EePrmDb entry id function
      //!
      //!  This function saves the paramter ID to a database slot.
      //!
      void setDbEntryId(NATIVE_INT_TYPE slotIndex, NATIVE_INT_TYPE id);

      //!  EePrmDb parameter buffer extraction function
      //!
      //!  This function gets the serialized parameter from the database.
      //!
      void loadEeSlotContents(NATIVE_INT_TYPE slotIndex);

      //!  EePrmDb parameter buffer save function
      //!
      //!  This function puts the serialized parameter into the database.
      //!
      void saveEeSlotContents(NATIVE_INT_TYPE slotIndex);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for PARAMETER_FACTORY_RESET command handler
      //! Reset all parameters to factory default values.
      //!
      void PARAMETER_FACTORY_RESET_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      // struct t_dbStruct {
      //     bool used; //!< whether slot is being used
      //     FwPrmIdType id; //!< the id being stored in the slot
      //     Fw::ParamBuffer val; //!< the serialized value of the parameter
      // } m_db[PRMDB_NUM_DB_ENTRIES];

    };

} // end namespace ATmega

#endif /* EePrmDb_HPP */
