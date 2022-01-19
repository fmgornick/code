/**
 * @file i_logger.h
 */
#ifndef I_LOGGER_H_
#define I_LOGGER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "drone.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief data logger interface.  Used to log data on our drone for reasons
 * unbenounced to me.  If we wanted to further optimize our drone search and
 * rescue system, we could use a machine learning algorithm to go through our
 * data output files to find the optimal search pattern.  This is a composite
 * pattern and has two main logger methods.  One for outputing to the terminal
 * screen, and one for saving in a CSV file.
 */
class iLogger {
public:
  /**
   * @brief log position, direction, and elapsed time of drone.  Called every
   * time we update.
   */
  virtual void Log(Vector3 *p, Vector3 *d, double t) = 0;
};

#endif // !I_LOGGER_H_
