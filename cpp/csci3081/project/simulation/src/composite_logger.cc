#include "composite_logger.h"

CompositeLogger::CompositeLogger() {
  loggers.push_back(new ConsoleLogger);
  loggers.push_back(new CSVLogger);
}

void CompositeLogger::Log(Vector3 *p, Vector3 *d, double t) {
  for (iLogger *x : loggers)
    x->Log(p, d, t);
}

void CompositeLogger::AddLogger(iLogger *logger) { loggers.push_back(logger); }
