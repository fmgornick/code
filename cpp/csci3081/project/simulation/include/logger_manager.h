/**
 * @file logger_manager.h
 */
#ifndef LOGGER_MANAGER_H_
#define LOGGER_MANAGER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "composite_logger.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief logger singleton class.
 */
class LoggerManager {
public:
  /**
   * @brief singletons should not be cloneable.
   */
  LoggerManager(LoggerManager &other) = delete;
  /**
   * @brief singletons should not be cloneable.
   */
  void operator=(const LoggerManager &) = delete;
  /**
   * @brief controls access to the singleton instance.  On first run, it creates
   * the singleton object and places it into the static field.  Any call after
   * just returns the existing instance.
   */
  static LoggerManager *GetInstance() {
    if (instance == nullptr)
      instance = new LoggerManager();
    return instance;
  }
  /**
   * @brief for logger extention, we call this function to add a new logger
   * class keeping low coupling.
   */
  void AddLogger(iLogger *newLogger) { cl->AddLogger(newLogger); }
  /**
   * @brief log position of drone with message about it.  Called every time we
   * update.
   */
  void Log(Vector3 *p, Vector3 *d, double t) { cl->Log(p, d, t); }

private:
  /**
   * @brief private constructor for our singleton
   */
  LoggerManager() : cl(new CompositeLogger) {}
  /**
   * @brief instance of LoggerManager
   */
  static LoggerManager *instance;
  /**
   * @brief CompositeLogger variable we use to actually log our data
   */
  CompositeLogger *cl;
};
#endif // !LOGGER_MANAGER_H_
