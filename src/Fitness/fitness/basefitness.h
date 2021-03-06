#ifndef BASE_FITNESS_H
#define BASE_FITNESS_H

#include "../fitness.h"

#include <opencv2/imgproc.hpp>

class BaseFitness
{
 public:
  BaseFitness();
  virtual ~BaseFitness();

  virtual void process(std::vector<_postData> &_data) = 0;
  virtual void endProcess(std::vector<_postData> &_data) = 0;
};
#endif // BASE_FITNESS_H
