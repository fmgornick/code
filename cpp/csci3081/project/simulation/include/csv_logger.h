/**
 * @file csv_logger.h
 */
#ifndef CSV_LOGGER_H_
#define CSV_LOGGER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "i_logger.h"
#include <fstream>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief logger for csv files.  Puts vector information and strategy time
 * information in a comma separated file.
 */
class CSVLogger : public iLogger {
public:
  /**
   * @brief logs position, direction, and time to csv file, along with an
   * inputted message
   */
  void Log(Vector3 *p, Vector3 *d, double t, std::string msg);
  /**
   * @brief same as the other logger command, but adds "N/A" for message
   */
  void Log(Vector3 *p, Vector3 *d, double t);

private:
  std::ofstream csv;
};

#endif // !CSV_LOGGER_H_
