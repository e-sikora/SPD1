#pragma once 

#include <iostream>

template <class T>
class Item {
  private:
    int id;
    int occur_time; // r
    int work_time; // j
    int idle_time; // q
    
  public:
    int get_id(){ return id; }
    int get_id() const { return id; }
    int get_occur_time(){ return occur_time; }
    int get_work_time(){ return work_time; }  
    int get_idle_time(){ return idle_time; }

    Item() : id(0), occur_time(0), work_time(0), idle_time(0) {}

    Item(int id_s, int occur_time_s, int work_time_s, int idle_time_s){
      id = id_s;
      occur_time = occur_time_s;
      work_time = work_time_s;
      idle_time = idle_time_s;
    } 

    bool operator<(const Item& other) const {
      return id < other.id;
    }

    bool compareByOccurTime(const Item& other) const {
      return occur_time < other.occur_time;
    }

    bool compareByIdleTime(const Item& other) const {
      return idle_time < other.idle_time;
    }
};