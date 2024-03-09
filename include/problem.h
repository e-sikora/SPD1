#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

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
    int workTime();
    void createOrClearFile(const std::string file_name);
    void savePermResult(const std::vector<Item> best_order, const int best_time, std::string result_file);
    void permutationSort();
    void occurTimeSort();
    void idleTimeSort();
};

template<class Item>
void Problem<Item>::loadFromFile(const std::string& file_name){
  std::ifstream input_file(file_name);

  if(!input_file.is_open()){
    std::cerr << "Nie udało się otworzyć pliku: " << file_name << "!\n";
    exit(EXIT_FAILURE); 
  }

  std::string temp;
  
  if(!std::getline(input_file,temp)){
    std::cerr << "Plik " << file_name << " jest pusty!\n";
    exit(EXIT_FAILURE);
  }
  else{
    list_size = std::stoi(temp);
  }

  Item new_item;
  int counter=0, o_time, w_time, i_time; 
  while(std::getline(input_file, temp)){
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
  input_file.close();
}

template<class Item>
int Problem<Item>::workTime(){
  int total_work_time = 0;

    for (int i=0; i<this->list_size; i++) { 
      if(total_work_time<this->get_item(i).get_occur_time()){
        total_work_time += (this->get_item(i).get_occur_time() - total_work_time);
      } 
      total_work_time += this->get_item(i).get_work_time();
      total_work_time += this->get_item(i).get_idle_time();
    }

  return total_work_time;
}

template<class Item>
void Problem<Item>::createOrClearFile(const std::string file_name){
  std::ofstream output_file(file_name);

  if(output_file.is_open()){
    output_file.close();
    output_file.open(file_name, std::ios::out | std::ios::trunc);
  }
  else{
    std::ofstream file(file_name);
    if (!file.is_open()) {
      std::cout << "Plik nie został poprawnie utworzony!\n";
      exit(EXIT_FAILURE);
    }
  }
  output_file.close();
}

template<class Item>
void Problem<Item>::savePermResult(const std::vector<Item> best_order, int best_time, std::string result_file){
  std::ofstream output_file(result_file, std::ios::app);

  if (!output_file.is_open()) {
    std::cerr << "Nie udało się otworzyć pliku do zapisu!" << std::endl;
    exit(EXIT_FAILURE);
  }

  for (const Item& item : best_order) {
    output_file << item.get_id() << " ";
  }

  output_file << "  Czas: "<< best_time << std::endl;
  output_file.close();
}

template<class Item>
void Problem<Item>::permutationSort(){
  std::string file_destination = ("data/perm_result.txt");
  std::vector<Item> original = main_list;
  int perm_work_time = 0;
  int best_time;
  std::vector<Item> best_order;
  bool first_iteration = true;

    do{
    perm_work_time = this->workTime();
    if(first_iteration == true){
      best_time = perm_work_time;
      best_order.assign(main_list.begin(), main_list.end());
      this->createOrClearFile(file_destination);
      first_iteration = false;
    }
    if(perm_work_time<best_time){
      best_time = perm_work_time;
      best_order.assign(main_list.begin(), main_list.end());
    }

    this->savePermResult(main_list, perm_work_time, file_destination);

    } while (std::next_permutation(main_list.begin(), main_list.end()));

  std::cout << "-------------------------Przegląd zupełny-------------------------" << std::endl;
  std::cout << "Optymalna kolejność wykonywania powyższych zadań jest dla ułożenia: ";
  for (Item& item : best_order) { 
    std::cout << item.get_id(); 
  }
  std::cout << std::endl << "Czas potrzebny na wykonanie zadania w powyższej kolejności to: " << best_time << std::endl << std::endl;

  main_list = original;
}

template<class Item>
void Problem<Item>::occurTimeSort(){
  std::vector<Item> original = main_list;
  std::sort(main_list.begin(), main_list.end(),[](const Item& a, const Item& b) {return a.compareByOccurTime(b);});

  int best_time = this->workTime();
  std::cout << "------------Algorytm heurystyczny - r (termin dostępności)--------" << std::endl;
  std::cout << "Optymalna kolejność wykonywania powyższych zadań jest dla ułożenia: ";
  for (Item& item : main_list) { 
    std::cout << item.get_id(); 
  }
  std::cout << std::endl << "Czas potrzebny na wykonanie zadania w powyższej kolejności to: " << best_time << std::endl << std::endl;

  main_list = original;
}

template<class Item>
void Problem<Item>::idleTimeSort(){
  std::vector<Item> original = main_list;
  std::sort(main_list.begin(), main_list.end(),[](const Item& a, const Item& b) {return a.compareByIdleTime(b);});

  int best_time = this->workTime();
  std::cout << "------------Algorytm heurystyczny - q (czas stygnięcia)-----------" << std::endl;
  std::cout << "Optymalna kolejność wykonywania powyższych zadań jest dla ułożenia: ";
  for (Item& item : main_list) { 
    std::cout << item.get_id(); 
  }
  std::cout << std::endl << "Czas potrzebny na wykonanie zadania w powyższej kolejności to: " << best_time << std::endl << std::endl;

  main_list = original;
}