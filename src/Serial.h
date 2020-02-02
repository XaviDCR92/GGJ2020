#ifndef SERIAL_HEADER__
#define SERIAL_HEADER__

/* *************************************
 *  Includes
 * *************************************/

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* *************************************
 *  Defines
 * *************************************/

#define SERIAL_DATA_PACKET_SIZE 8
#define ACK_BYTE_STRING "b"

/* *************************************
 *  Global prototypes
 * *************************************/

void SerialInit(void);
void SerialRead(uint8_t *ptrArray, size_t nBytes);
void SerialWrite(const void* ptrArray, size_t nBytes);

#ifdef SERIAL_INTERFACE
void Serial_printf(const char* str, ...);
#endif // SERIAL_INTERFACE

#ifdef __cplusplus
}
#endif

#endif // SERIAL_HEADER__
