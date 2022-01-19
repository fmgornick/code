#include "console_logger.h"

void ConsoleLogger::Log(Vector3 *p, Vector3 *d, double t) {
  std::cout << "position: (" << p->GetX() << ", " << p->GetY() << ", "
            << p->GetZ() << ")\t";

  std::cout << "direction: (" << d->GetX() << ", " << d->GetY() << ", "
            << d->GetZ() << ")\t";

  std::cout << "time: " << t << std::endl;
}
