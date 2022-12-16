#include <stdint.h>

const uint8_t LTV[] = {0b00000000, 0b01110011, 0b00000000, 0b00000000}; // ça existe?

const uint8_t eteint[] = {0b00000000, 0b00000000, 0b00000000,
                          0b00000000, 0b00000000, 0b00000000
                         };      // 0.0
const uint8_t tirets[] = {0b01000000, 0b01000000, 0b01000000,
                          0b01000000, 0b01000000, 0b01000000
                         };      // 1.0
const uint8_t zeroZeroAux[] = {0b00000000, 0b00000000, 0b00000000,
                               0b00000000, 0b00111111, 0b00111111
                              };   // 2.0
const uint8_t zeroZeroPrincipal[] = {0b00000000, 0b00111111, 0b00111111,
                                     0b00000000, 0b00000000, 0b00000000
                                    }; // 3.0
const uint8_t tripleZeroAux[] = {0b00000000, 0b00000000, 0b00000000,
                                 0b00111111, 0b00111111, 0b00111111
                                };   // 4.0
const uint8_t preannonce[] = {0b00000000, 0b01110011, 0b00000000,
                              0b00000000, 0b00000000, 0b00000000
                             };    // 5.0
const uint8_t preannonceAux[] = {0b00000000, 0b00000000, 0b00000000,
                                 0b00000000, 0b01011110, 0b00000000
                                };   // 6.0
const uint8_t vitesseSup160[] = {0b00000000, 0b01111100, 0b00000000,
                                  0b00000000, 0b00000000, 0b00000000
                                 };  // 7.0
const uint8_t autotest[] = {0b01111111, 0b01111111, 0b01111111,
                            0b01111111, 0b01111111, 0b01111111
                           };      // 8.0
const uint8_t faute[] = {0b00000000, 0b11110001, 0b00000000,
                         0b00000000, 0b00000000, 0b00000000
                        };       // 9.0
// autotest
const uint8_t PA400[] = {0b01100110, 0b00111111, 0b00111111,
                         0b00000000, 0b01110011, 0b01110111
                        };       // 1.0

const uint8_t UC512[] = {0b01101101, 0b00000110, 0b01011011,
                         0b00000000, 0b00111110, 0b00111001
                        };       // 2.0

// ^_^
const uint8_t uwu[] =   {0b00100011, 0b00001000, 0b00100011,
                         0b00100011, 0b00001000, 0b00100011
                        };       // 16