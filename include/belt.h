#pragma once

#include "object.h"
class Belt : public Object {
public:
  Belt()                       = default;
  Belt(Belt&&)                 = default;
  Belt(const Belt&)            = default;
  Belt& operator=(Belt&&)      = default;
  Belt& operator=(const Belt&) = default;
  ~Belt()                      = default;

private:
};
