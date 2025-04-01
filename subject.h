#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"

#include <iostream>
#include <string>
#include <vector>

class Subject {
  std::vector<Observer*> observers;

 public:
  Subject();
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers();
  virtual ~Subject()=0;
};

#endif
