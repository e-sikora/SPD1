#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "item.h"

template<class Item>
class Problem{
  private:
    std::vector<Item> main_list;
    int list_size;

  public:
    Problem() : list_size(0) {}

    size_t get_size(){ return list_size; }
    Item& get_item(size_t index){ return main_list[index]; }

    void loadFromFile(const std::string& file_name);  
};

template<class Item>
void Problem<Item>::loadFromFile(const std::string& file_name){
  std::ifstream file(file_name);

  if(!file.is_open()){
    std::cerr << "Nie udało się otworzyć pliku: " << file_name << "!\n";
    exit(EXIT_FAILURE); 
  }

  std::string temp;
  
  if(!std::getline(file,temp)){
    std::cerr << "Plik " << file_name << " jest pusty!\n";
    exit(EXIT_FAILURE);
  }
  else{
    list_size = std::stoi(temp);
  }

  Item new_item;
  int counter=0, o_time, w_time, i_time; 
  while(std::getline(file, temp)){
    counter++;
    std::istringstream divide(temp);
    if(divide >> o_time >> w_time >> i_time){
      new_item = Item(counter, o_time, w_time, i_time);
    }
    else{
      std::cerr << "Dane zostały źle podzielone!\n";
      exit(EXIT_FAILURE); 
    }
    main_list.push_back(new_item);
  }
  if(counter!=list_size){
    std::cerr << "Liczba wczytanych zadań nie zgadza się z zadeklarowaną ilośćią!\n";
    exit(EXIT_FAILURE);
  }
}