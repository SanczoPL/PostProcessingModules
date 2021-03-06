#ifndef BASE_TRACKER_H
#define BASE_TRACKER_H

#include <opencv2/imgproc.hpp>

#include "../tracker.h"

class BaseTracker {
public:
  BaseTracker();
  virtual ~BaseTracker();

  virtual void process(std::vector<_postData> &_data) = 0;
  virtual void endProcess(std::vector<_postData> &_data) = 0;
};

#endif // BASE_TRACKER_H
