#if !defined(_RADIOLIB_H)
#define _RADIOLIB_H

/*!
  \mainpage RadioLib Documentation

  Universal wireless communication library for Arduino.

  \par Currently Supported Wireless Modules and Protocols
  - CC1101 FSK module
  - RF69 FSK module
  - Si443x FSK module
  - SX126x LoRa/FSK module
  - SX127x LoRa/FSK module
  - SX128x LoRa/GFSK/BLE/FLRC module
  - SX1231 FSK module
  - PhysicalLayer protocols
    - RTTY (RTTYClient)
    - Morse Code (MorseClient)
    - AX.25 (AX25Client)
    - SSTV (SSTVClient)
    - Hellschreiber (HellClient)
    - 4-FSK (FSK4Client)
    - APRS (APRSClient)

  \par Quick Links
  Documentation for most common methods can be found in its reference page (see the list above).\n
  Some methods (mainly configuration) are also overridden in derived classes, such as SX1272, SX1278, RFM96 etc. for SX127x.\n
  \ref status_codes have their own page.\n
  Some modules implement methods of one or more compatibility layers, loosely based on the ISO/OSI model:
  - PhysicalLayer - FSK and LoRa radio modules

  \see https://github.com/jgromes/RadioLib

  \copyright  Copyright (c) 2019 Jan Gromes
*/

#include "TypeDef.h"
#include "Module.h"

// warnings are printed in this file since BuildOpt.h is compiled in multiple places

// check God mode
#if defined(RADIOLIB_GODMODE)
  #warning "God mode active, I hope it was intentional. Buckle up, lads."
#endif

// print debug info
#if defined(RADIOLIB_DEBUG)
  #define RADIOLIB_VALUE_TO_STRING(x) #x
  #define RADIOLIB_VALUE(x) RADIOLIB_VALUE_TO_STRING(x)
  #define RADIOLIB_VAR_NAME_VALUE(var) #var "="  RADIOLIB_VALUE(var)
  #pragma message(RADIOLIB_VAR_NAME_VALUE(RADIOLIB_PLATFORM))
  #pragma message(RADIOLIB_VAR_NAME_VALUE(RADIOLIB_VERSION_MAJOR))
  #pragma message(RADIOLIB_VAR_NAME_VALUE(RADIOLIB_VERSION_MINOR))
  #pragma message(RADIOLIB_VAR_NAME_VALUE(RADIOLIB_VERSION_PATCH))
  #pragma message(RADIOLIB_VAR_NAME_VALUE(RADIOLIB_VERSION_EXTRA))
#endif

// check unknown/unsupported platform
#if defined(RADIOLIB_UNKNOWN_PLATFORM)
  #warning "RadioLib might not be compatible with this Arduino board - check supported platforms at https://github.com/jgromes/RadioLib!"
#endif

//#include "modules/SX126x/SX1261.h"
#include "modules/SX126x/SX1262.h"

// physical layer protocols
#include "protocols/PhysicalLayer/PhysicalLayer.h"

// only create Radio class when using RadioShield
#if defined(RADIOLIB_RADIOSHIELD)

// RadioShield pin definitions
#define RADIOSHIELD_CS_A    10
#define RADIOSHIELD_IRQ_A   2
#define RADIOSHIELD_RST_A   9
#define RADIOSHIELD_GPIO_A  8
#define RADIOSHIELD_CS_B    5
#define RADIOSHIELD_IRQ_B   3
#define RADIOSHIELD_RST_B   7
#define RADIOSHIELD_GPIO_B  6

/*!
  \class Radio

  \brief Library control object when using RadioShield.
  Contains two pre-configured "modules", which correspond to the slots on shield.
*/
class Radio {
  public:

    Module* ModuleA;
    Module* ModuleB;

    /*!
      \brief Default constructor. Only used to set ModuleA and ModuleB configuration.
    */
    Radio() {
      ModuleA = new Module(RADIOSHIELD_CS_A, RADIOSHIELD_IRQ_A, RADIOSHIELD_RST_A, RADIOSHIELD_GPIO_A);
      ModuleB = new Module(RADIOSHIELD_CS_B, RADIOSHIELD_IRQ_B, RADIOSHIELD_RST_B, RADIOSHIELD_GPIO_B);
    }

#if defined(RADIOLIB_GODMODE)
  private:
#endif

};

Radio RadioShield;
#endif

#endif
