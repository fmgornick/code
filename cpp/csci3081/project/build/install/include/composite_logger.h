/**
 * @file composite_logger.h
 */
#ifndef COMPOSITE_LOGGER_H_
#define COMPOSITE_LOGGER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "console_logger.h"
#include "csv_logger.h"
#include "i_logger.h"
#include <list>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief composite logger that uses our other two terminal / csv loggers to
 * record data
 */
class CompositeLogger : public iLogger {
public:
  /**
   * @brief constructor. Adds loggers to our list member variable
   */
  CompositeLogger();
  /**
   * @brief log position of drone with message about it.  Called every time we
   * update.
   */
  void Log(Vector3 *p, Vector3 *d, double t);
  /**
   * @brief adds a new logger to our list member variable
   */
  void AddLogger(iLogger *logger);

private:
  /**
   * @brief list of loggers used to record data
   */
  std::list<iLogger *> loggers;
};

#endif // !COMPOSITE_LOGGER_H_
