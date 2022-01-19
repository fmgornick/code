#include "csv_logger.h"

void CSVLogger::Log(Vector3 *p, Vector3 *d, double t, std::string msg) {
  csv.open("data/log/log.csv", std::ios::app);
  csv << "p=[" << p->GetX() << ";" << p->GetY() << ";" << p->GetZ() << "],";
  csv << "d=[" << d->GetX() << ";" << d->GetY() << ";" << d->GetZ() << "],";
  csv << "t=" << t;
  csv << "msg=" << msg << std::endl;
  csv.close();
}

void CSVLogger::Log(Vector3 *p, Vector3 *d, double t) { Log(p, d, t, "N/A"); }
