/***************************************************|
|            MEGACORE 100-PIN AVR PINOUT            |
|        https://github.com/MCUdude/MegaCore        |
|                                                   |
| This file is used when compiling for:             |
| ATmega2560/V                                      |
| ATmega1280/V                                      |
| ATmega640/V                                       |
|                                                   |
|***************************************************/


#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>


// Current pinout
#define MEGACORE_100_PIN_AVR_PINOUT


// Digital pins
#define NUM_DIGITAL_PINS            (86)

// PWM pins
#define digitalPinHasPWM(p)         (((p) >= 3 && (p) <= 5) || ((p) >= 11 && (p)<= 14) || ((p) >= 19 && (p)<= 22) || ((p) >= 29 && (p)<= 31) || ((p) == 85))

// Builtin LED
#define LED_BUILTIN   (22)
static const uint8_t LED = LED_BUILTIN;

// SPI defs
#define PIN_SPI_SS    (15)
#define PIN_SPI_SCK   (16)
#define PIN_SPI_MOSI  (17)
#define PIN_SPI_MISO  (18)
static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t SCK  = PIN_SPI_SCK;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;

// i2c defs
#define PIN_WIRE_SDA  35
#define PIN_WIRE_SCL  34
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

// Analog pin defs
#define PIN_A0   (69)
#define PIN_A1   (70)
#define PIN_A2   (71)
#define PIN_A3   (72)
#define PIN_A4   (73)
#define PIN_A5   (74)
#define PIN_A6   (75)
#define PIN_A7   (76)
#define PIN_A8   (77)
#define PIN_A9   (78)
#define PIN_A10  (79)
#define PIN_A11  (80)
#define PIN_A12  (81)
#define PIN_A13  (82)
#define PIN_A14  (83)
#define PIN_A15  (84)
static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;
static const uint8_t A8 = PIN_A8;
static const uint8_t A9 = PIN_A9;
static const uint8_t A10 = PIN_A10;
static const uint8_t A11 = PIN_A11;
static const uint8_t A12 = PIN_A12;
static const uint8_t A13 = PIN_A13;
static const uint8_t A14 = PIN_A14;
static const uint8_t A15 = PIN_A15;
#define NUM_ANALOG_INPUTS           (16)
#define analogInputToDigitalPin(p)  ((p < 16) ? (p) + 69 : -1)
#define analogPinToChannel(p)       ((p) < NUM_ANALOG_INPUTS ? (p) : (p) >= 69 ? (p) - 69 : -1)

// Interrupts
#define EXTERNAL_NUM_INTERRUPTS     (8)
#define digitalPinToInterrupt(p)    (((p) >= 4 && (p) <= 7) ? (p) : ((p) >= 34 && (p) <= 37) ? (p) - 34 : NOT_AN_INTERRUPT)

// PCINT defs
#define digitalPinToPCICR(p)    ((((p) >= 15) && ((p) <= 22)) || (((p) >= 52) && ((p) <= 58)) || (((p) >= 77) && ((p) <= 84)) || ((p) == 0) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) ((((p) >= 15) && ((p) <= 22)) ? 0 : ((((p) >= 52) && ((p) <= 58)) || (((p) == 0) ? 1 : ((((p) >= 77) && ((p) <= 84)) ? 2 : 0))))
#define digitalPinToPCMSK(p)    ((((p) >= 15) && ((p) <= 22)) ? (&PCMSK0) : ((((p) >= 52) && ((p) <= 58)) || ((p) == 0) ? (&PCMSK1) : ((((p) >= 77) && ((p) <= 84)) ? (&PCMSK2) : ((uint8_t *)0))))
#define digitalPinToPCMSKbit(p) ((((p) >= 15) && ((p) <= 22)) ? ((p) - 15) : ((((p) >= 52) && ((p) <= 58)) ? ((p) - 51) : (((p) ==  85) ? 0 : ((((p) >= 77) && ((p) <= 84)) ? ((p) - 77) : 0))))


#ifdef ARDUINO_MAIN

const uint16_t PROGMEM port_to_mode_PGM[] = {
  NOT_A_PORT,
  (uint16_t) &DDRA,
  (uint16_t) &DDRB,
  (uint16_t) &DDRC,
  (uint16_t) &DDRD,
  (uint16_t) &DDRE,
  (uint16_t) &DDRF,
  (uint16_t) &DDRG,
  (uint16_t) &DDRH,
  NOT_A_PORT,
  (uint16_t) &DDRJ,
  (uint16_t) &DDRK,
  (uint16_t) &DDRL,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
  NOT_A_PORT,
  (uint16_t) &PORTA,
  (uint16_t) &PORTB,
  (uint16_t) &PORTC,
  (uint16_t) &PORTD,
  (uint16_t) &PORTE,
  (uint16_t) &PORTF,
  (uint16_t) &PORTG,
  (uint16_t) &PORTH,
  NOT_A_PORT,
  (uint16_t) &PORTJ,
  (uint16_t) &PORTK,
  (uint16_t) &PORTL,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
  NOT_A_PIN,
  (uint16_t) &PINA,
  (uint16_t) &PINB,
  (uint16_t) &PINC,
  (uint16_t) &PIND,
  (uint16_t) &PINE,
  (uint16_t) &PINF,
  (uint16_t) &PING,
  (uint16_t) &PINH,
  NOT_A_PIN,
  (uint16_t) &PINJ,
  (uint16_t) &PINK,
  (uint16_t) &PINL,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
  // PORTLIST
  // -------------------------------------------
  PE, // PE 0 ** 0 ** RXD0
  PE, // PE 1 ** 1 ** TXD0
  PE, // PE 2 ** 2
  PE, // PE 3 ** 3
  PE, // PE 4 ** 4
  PE, // PE 5 ** 5
  PE, // PE 6 ** 6
  PE, // PE 7 ** 7
  PH, // PH 0 ** 8 ** RXD2
  PH, // PH 1 ** 9 ** TXD2
  PH, // PH 2 ** 10
  PH, // PH 3 ** 11
  PH, // PH 4 ** 12
  PH, // PH 5 ** 13
  PH, // PH 6 ** 14
  PB, // PB 0 ** 15 ** SS
  PB, // PB 1 ** 16 ** SCK
  PB, // PB 2 ** 17 ** MOSI
  PB, // PB 3 ** 18 ** MISO
  PB, // PB 4 ** 19
  PB, // PB 5 ** 20
  PB, // PB 6 ** 21
  PB, // PB 7 ** 22
  PH, // PH 7 ** 23
  PG, // PG 3 ** 24
  PG, // PG 4 ** 25
  PL, // PL 0 ** 26
  PL, // PL 1 ** 27
  PL, // PL 2 ** 28
  PL, // PL 3 ** 29
  PL, // PL 4 ** 30
  PL, // PL 5 ** 31
  PL, // PL 6 ** 32
  PL, // PL 7 ** 33
  PD, // PD 0 ** 34 ** SCL
  PD, // PD 1 ** 35 ** SDA
  PD, // PD 2 ** 36 ** RXD1
  PD, // PD 3 ** 37 ** TXD1
  PD, // PD 4 ** 38
  PD, // PD 5 ** 39
  PD, // PD 6 ** 40
  PD, // PD 7 ** 41
  PG, // PG 0 ** 42
  PG, // PG 1 ** 43
  PC, // PC 0 ** 44
  PC, // PC 1 ** 45
  PC, // PC 2 ** 46
  PC, // PC 3 ** 47
  PC, // PC 4 ** 48
  PC, // PC 5 ** 49
  PC, // PC 6 ** 50
  PC, // PC 7 ** 51
  PJ, // PJ 0 ** 52 ** RXD3
  PJ, // PJ 1 ** 53 ** TXD3
  PJ, // PJ 2 ** 54
  PJ, // PJ 3 ** 55
  PJ, // PJ 4 ** 56
  PJ, // PJ 5 ** 57
  PJ, // PJ 6 ** 58
  PG, // PG 2 ** 59
  PA, // PA 7 ** 60
  PA, // PA 6 ** 61
  PA, // PA 5 ** 62
  PA, // PA 4 ** 63
  PA, // PA 3 ** 64
  PA, // PA 2 ** 65
  PA, // PA 1 ** 66
  PA, // PA 0 ** 67
  PJ, // PJ 7 ** 68
  PF, // PF 0 ** 69 ** A0
  PF, // PF 1 ** 70 ** A1
  PF, // PF 2 ** 71 ** A2
  PF, // PF 3 ** 72 ** A3
  PF, // PF 4 ** 73 ** A4
  PF, // PF 5 ** 74 ** A5
  PF, // PF 6 ** 75 ** A6
  PF, // PF 7 ** 76 ** A7
  PK, // PK 0 ** 77 ** A8
  PK, // PK 1 ** 78 ** A9
  PK, // PK 2 ** 79 ** A10
  PK, // PK 3 ** 80 ** A11
  PK, // PK 4 ** 81 ** A12
  PK, // PK 5 ** 82 ** A13
  PK, // PK 6 ** 83 ** A14
  PK, // PK 7 ** 84 ** A15
  PG, // PG 5 ** 85
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
  // PIN IN PORT
  // -------------------------------------------
  _BV(0), // PE 0 ** 0 ** RXD0
  _BV(1), // PE 1 ** 1 ** TXD0
  _BV(2), // PE 2 ** 2
  _BV(3), // PE 3 ** 3
  _BV(4), // PE 4 ** 4
  _BV(5), // PE 5 ** 5
  _BV(6), // PE 6 ** 6
  _BV(7), // PE 7 ** 7
  _BV(0), // PH 0 ** 8 ** RXD2
  _BV(1), // PH 1 ** 9 ** TXD2
  _BV(2), // PH 2 ** 10
  _BV(3), // PH 3 ** 11
  _BV(4), // PH 4 ** 12
  _BV(5), // PH 5 ** 13
  _BV(6), // PH 6 ** 14
  _BV(0), // PB 0 ** 15 ** SS
  _BV(1), // PB 1 ** 16 ** SCK
  _BV(2), // PB 2 ** 17 ** MOSI
  _BV(3), // PB 3 ** 18 ** MISO
  _BV(4), // PB 4 ** 19
  _BV(5), // PB 5 ** 20
  _BV(6), // PB 6 ** 21
  _BV(7), // PB 7 ** 22
  _BV(7), // PH 7 ** 23
  _BV(3), // PG 3 ** 24
  _BV(4), // PG 4 ** 25
  _BV(0), // PL 0 ** 26
  _BV(1), // PL 1 ** 27
  _BV(2), // PL 2 ** 28
  _BV(3), // PL 3 ** 29
  _BV(4), // PL 4 ** 30
  _BV(5), // PL 5 ** 31
  _BV(6), // PL 6 ** 32
  _BV(7), // PL 7 ** 33
  _BV(0), // PD 0 ** 34 ** SDA
  _BV(1), // PD 1 ** 35 ** SCL
  _BV(2), // PD 2 ** 36 ** RXD1
  _BV(3), // PD 3 ** 37 ** TXD1
  _BV(4), // PD 4 ** 38
  _BV(5), // PD 5 ** 39
  _BV(6), // PD 6 ** 40
  _BV(7), // PD 7 ** 41
  _BV(0), // PG 0 ** 42
  _BV(1), // PG 1 ** 43
  _BV(0), // PC 0 ** 44
  _BV(1), // PC 1 ** 45
  _BV(2), // PC 2 ** 46
  _BV(3), // PC 3 ** 47
  _BV(4), // PC 4 ** 48
  _BV(5), // PC 5 ** 49
  _BV(6), // PC 6 ** 50
  _BV(7), // PC 7 ** 51
  _BV(0), // PJ 0 ** 52 ** RXD3
  _BV(1), // PJ 1 ** 53 ** TXD3
  _BV(2), // PJ 2 ** 54
  _BV(3), // PJ 3 ** 55
  _BV(4), // PJ 4 ** 56
  _BV(5), // PJ 5 ** 57
  _BV(6), // PJ 6 ** 58
  _BV(2), // PG 2 ** 59
  _BV(7), // PA 7 ** 60
  _BV(6), // PA 6 ** 61
  _BV(5), // PA 5 ** 62
  _BV(4), // PA 4 ** 63
  _BV(3), // PA 3 ** 64
  _BV(2), // PA 2 ** 65
  _BV(1), // PA 1 ** 66
  _BV(0), // PA 0 ** 67
  _BV(7), // PJ 7 ** 68
  _BV(0), // PF 0 ** 69 ** A0
  _BV(1), // PF 1 ** 70 ** A1
  _BV(2), // PF 2 ** 71 ** A2
  _BV(3), // PF 3 ** 72 ** A3
  _BV(4), // PF 4 ** 73 ** A4
  _BV(5), // PF 5 ** 74 ** A5
  _BV(6), // PF 6 ** 75 ** A6
  _BV(7), // PF 7 ** 76 ** A7
  _BV(0), // PK 0 ** 77 ** A8
  _BV(1), // PK 1 ** 78 ** A9
  _BV(2), // PK 2 ** 79 ** A10
  _BV(3), // PK 3 ** 80 ** A11
  _BV(4), // PK 4 ** 81 ** A12
  _BV(5), // PK 5 ** 82 ** A13
  _BV(6), // PK 6 ** 83 ** A14
  _BV(7), // PK 7 ** 84 ** A15
  _BV(5), // PG 5 ** 85
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
  // TIMERS
  // -------------------------------------------
  NOT_ON_TIMER, // PE 0 ** 0 ** RXD0
  NOT_ON_TIMER, // PE 1 ** 1 ** TXD0
  NOT_ON_TIMER, // PE 2 ** 2
  TIMER3A,      // PE 3 ** 3
  TIMER3B,      // PE 4 ** 4
  TIMER3C,      // PE 5 ** 5
  NOT_ON_TIMER, // PE 6 ** 6
  NOT_ON_TIMER, // PE 7 ** 7
  NOT_ON_TIMER, // PH 0 ** 8 ** RXD2
  NOT_ON_TIMER, // PH 1 ** 9 ** TXD2
  NOT_ON_TIMER, // PH 2 ** 10
  TIMER4A,      // PH 3 ** 11
  TIMER4B,      // PH 4 ** 12
  TIMER4C,      // PH 5 ** 13
  TIMER2B,      // PH 6 ** 14
  NOT_ON_TIMER, // PB 0 ** 15 ** SS
  NOT_ON_TIMER, // PB 1 ** 16 ** SCK
  NOT_ON_TIMER, // PB 2 ** 17 ** MOSI
  NOT_ON_TIMER, // PB 3 ** 18 ** MISO
  TIMER2A,      // PB 4 ** 19
  TIMER1A,      // PB 5 ** 20
  TIMER1B,      // PB 6 ** 21
  TIMER1C,      // PB 7 ** 22
  NOT_ON_TIMER, // PH 7 ** 23
  NOT_ON_TIMER, // PG 3 ** 24
  NOT_ON_TIMER, // PG 4 ** 25
  NOT_ON_TIMER, // PL 0 ** 26
  NOT_ON_TIMER, // PL 1 ** 27
  NOT_ON_TIMER, // PL 2 ** 28
  TIMER5A,      // PL 3 ** 29
  TIMER5B,      // PL 4 ** 30
  TIMER5C,      // PL 5 ** 31
  NOT_ON_TIMER, // PL 6 ** 32
  NOT_ON_TIMER, // PL 7 ** 33
  NOT_ON_TIMER, // PD 0 ** 34 ** SCL
  NOT_ON_TIMER, // PD 1 ** 35 ** SDA
  NOT_ON_TIMER, // PD 2 ** 36 ** RXD1
  NOT_ON_TIMER, // PD 3 ** 37 ** TXD1
  NOT_ON_TIMER, // PD 4 ** 38
  NOT_ON_TIMER, // PD 5 ** 39
  NOT_ON_TIMER, // PD 6 ** 40
  NOT_ON_TIMER, // PD 7 ** 41
  NOT_ON_TIMER, // PG 0 ** 42
  NOT_ON_TIMER, // PG 1 ** 43
  NOT_ON_TIMER, // PC 0 ** 44
  NOT_ON_TIMER, // PC 1 ** 45
  NOT_ON_TIMER, // PC 2 ** 46
  NOT_ON_TIMER, // PC 3 ** 47
  NOT_ON_TIMER, // PC 4 ** 48
  NOT_ON_TIMER, // PC 5 ** 49
  NOT_ON_TIMER, // PC 6 ** 50
  NOT_ON_TIMER, // PC 7 ** 51
  NOT_ON_TIMER, // PJ 0 ** 52 ** RXD3
  NOT_ON_TIMER, // PJ 1 ** 53 ** TXD3
  NOT_ON_TIMER, // PJ 2 ** 54
  NOT_ON_TIMER, // PJ 3 ** 55
  NOT_ON_TIMER, // PJ 4 ** 56
  NOT_ON_TIMER, // PJ 5 ** 57
  NOT_ON_TIMER, // PJ 6 ** 58
  NOT_ON_TIMER, // PG 2 ** 59
  NOT_ON_TIMER, // PA 7 ** 60
  NOT_ON_TIMER, // PA 6 ** 61
  NOT_ON_TIMER, // PA 5 ** 62
  NOT_ON_TIMER, // PA 4 ** 63
  NOT_ON_TIMER, // PA 3 ** 64
  NOT_ON_TIMER, // PA 2 ** 65
  NOT_ON_TIMER, // PA 1 ** 66
  NOT_ON_TIMER, // PA 0 ** 67
  NOT_ON_TIMER, // PJ 7 ** 68
  NOT_ON_TIMER, // PF 0 ** 69 ** A0
  NOT_ON_TIMER, // PF 1 ** 70 ** A1
  NOT_ON_TIMER, // PF 2 ** 71 ** A2
  NOT_ON_TIMER, // PF 3 ** 72 ** A3
  NOT_ON_TIMER, // PF 4 ** 73 ** A4
  NOT_ON_TIMER, // PF 5 ** 74 ** A5
  NOT_ON_TIMER, // PF 6 ** 75 ** A6
  NOT_ON_TIMER, // PF 7 ** 76 ** A7
  NOT_ON_TIMER, // PK 0 ** 77 ** A8
  NOT_ON_TIMER, // PK 1 ** 78 ** A9
  NOT_ON_TIMER, // PK 2 ** 79 ** A10
  NOT_ON_TIMER, // PK 3 ** 80 ** A11
  NOT_ON_TIMER, // PK 4 ** 81 ** A12
  NOT_ON_TIMER, // PK 5 ** 82 ** A13
  NOT_ON_TIMER, // PK 6 ** 83 ** A14
  NOT_ON_TIMER, // PK 7 ** 84 ** A15
  TIMER0B,      // PG 5 ** 85
};

#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR         Serial
#define SERIAL_PORT_HARDWARE        Serial
#define SERIAL_PORT_HARDWARE1       Serial1
#define SERIAL_PORT_HARDWARE2       Serial2
#define SERIAL_PORT_HARDWARE3       Serial3
#define SERIAL_PORT_HARDWARE_OPEN   Serial1
#define SERIAL_PORT_HARDWARE_OPEN1  Serial2
#define SERIAL_PORT_HARDWARE_OPEN2  Serial3

#endif
