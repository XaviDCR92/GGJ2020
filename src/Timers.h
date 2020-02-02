#ifndef TIMERS_H
#define TIMERS_H

/*******************************************************************//**
*
* @file     Timers.h
*
* @author   Xavier Del Campo
*
* @brief    Include file for Timers module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

/* *************************************
 * Defines
 * *************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/* *************************************
 * Public types definition
 * *************************************/

/* *************************************
 * Public variables declaration
 * *************************************/

/* *************************************
 * Public functions declaration
 * *************************************/

void TimersInit(void);
unsigned int RootCounter1Get(void);
unsigned int RootCounter2Get(void);

#ifdef __cplusplus
}
#endif

#endif /* TIMERS_H */
