#pragma once 

#include <iostream>

template <class T>
class Item {
  private:
    int id;
    int occur_time;
    int work_time;
    int idle_time;
    
  public:
    int get_id(){ return id; }
    int get_occut_time(){ return occur_time; }
    int get_work_time(){ return work_time; }  
    int get_idle_time(){ return idle_time; }

    Item() : id(0), occur_time(0), work_time(0), idle_time(0) {}

    Item(int id_s, int occur_time_s, int work_time_s, int idle_time_s) {
      id = id_s;
      occur_time = occur_time_s;
      work_time = work_time_s;
      idle_time = idle_time_s;
    } 

  

};