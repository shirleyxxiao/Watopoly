#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <string>
#include <vector>

class Observer {
 public:
  virtual void notify() = 0;
  virtual ~Observer() = default;
};

#endif
