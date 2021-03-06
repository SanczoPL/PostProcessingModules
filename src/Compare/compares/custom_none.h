#ifndef COMPARES_CUSTOM_NONE_H
#define COMPARES_CUSTOM_NONE_H

#include "basecompare.h"

class QJsonObject;

namespace Compares
{
class None : public BaseCompare
{
 public:
  None();

  void process(std::vector<_postData> &_data);
  void endProcess(std::vector<_postData> &_data);

 private:
};
} // namespace Compares

#endif // COMPARES_CUSTOM_NONE_H
