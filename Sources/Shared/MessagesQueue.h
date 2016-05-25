//
// Created by Kacper Harasim on 21.05.2016.
//

#ifndef TIN_MESSAGESQUEUE_H
#define TIN_MESSAGESQUEUE_H

#include <condition_variable>
#include <queue>
#include <iostream>
#include <memory>


template <typename T>

/*
 * Generic class that provides synchronized access to queue.
 */
class MessagesQueue {

 private:
  std::queue<std::shared_ptr<T>> queue;
  std::condition_variable conditionVariable;
  std::mutex mutex;

  int safeSize() {
    return queue.size();
  }

 public:
  /*
   * This operation is non blocking. When it's called for empty queue and someone was waiting on pop operation he'll be awaken
   */
  void push(std::shared_ptr<T> object) {
    std::unique_lock<std::mutex> lock(mutex);
    queue.push(object);
    conditionVariable.notify_one();
  }

  std::shared_ptr<T> pop() {
    std::unique_lock<std::mutex> lock(mutex);
    if(safeSize() == 0) {
      std::cout << "queue is empty!" << std::endl;
      conditionVariable.wait(lock);
    }
    std::shared_ptr<T> receivedObject = queue.front();
    queue.pop();
    return receivedObject;
  }

  unsigned long size() {
    return queue.size();
  }
};


#endif //TIN_MESSAGESQUEUE_H
