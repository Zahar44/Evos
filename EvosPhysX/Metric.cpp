#include "Metric.h"

std::map<const char*, MetricSnapshot> Metric::snapshots1;
std::map<const char*, MetricSnapshot> Metric::snapshots2;
bool Metric::snapshotsSwapped;
float Metric::swapInterval = 1.0f / 15.0f;
double Metric::lastTimeSwapped = 0.0;
