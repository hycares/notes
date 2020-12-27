#include <iostream>
#include <list>
#include <thread>
#include <chrono>
#include "observer.hpp"

class Subject {
private:
  std::list<Observer *> observerList;
public:
  void addObserver(Observer *observer) {
    observerList.push_back(observer);
  }
  void removeObserver(Observer *observer) {
    observerList.remove(observer);
  }
protected:
  void notify(int val) {
    for (auto& ob : observerList) {
      ob->update(val);
    }
  }
};

class DownloadStatus : public Subject {
public:
  DownloadStatus() {};
  void download() {
    for (int i=1; i<=10; ++i) {
      this->notify(i);
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
};