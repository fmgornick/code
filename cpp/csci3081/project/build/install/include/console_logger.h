/**
 * @file console_logger.h
 */
#ifndef CONSOLE_LOGGER_H_
#define CONSOLE_LOGGER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "i_logger.h"
#include <iostream>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief
 */
class ConsoleLogger : public iLogger {
public:
  /**
   * @brief prints position and direction vector data to terminal screen
   */
  void Log(Vector3 *p, Vector3 *d, double t);
};

#endif // !CONSOLE_LOGGER_H_
