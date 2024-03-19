#include "problem.h"

template<class Item>
Problem<Item>::Problem() : list_size(0) {}

template<class Item>
size_t Problem<Item>::getSize() { return list_size; }

template<class Item>
Item &Problem<Item>::getItem(size_t index) { return main_list[index]; }

template<class Item>
void Problem<Item>::loadFromFile(const std::string &file_name) {
    std::ifstream input_file(file_name);

    if (!input_file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku: " << file_name << "!\n";
        exit(EXIT_FAILURE);
    }

    std::string temp;

    if (!std::getline(input_file, temp)) {
        std::cerr << "Plik " << file_name << " jest pusty!\n";
        exit(EXIT_FAILURE);
    } else {
        list_size = std::stoi(temp);
    }

    Item new_item;
    int counter = 0, o_time, w_time, i_time;
    while (std::getline(input_file, temp)) {
        counter++;
        std::istringstream divide(temp);
        if (divide >> o_time >> w_time >> i_time) {
            new_item = Item(counter, o_time, w_time, i_time);
        } else {
            std::cerr << "Dane zostały źle podzielone!\n";
            exit(EXIT_FAILURE);
        }
        main_list.push_back(new_item);
    }
    if (counter != list_size) {
        std::cerr << "Liczba wczytanych zadań nie zgadza się z zadeklarowaną ilośćią!\n";
        exit(EXIT_FAILURE);
    }
    input_file.close();
}

template<class Item>
int Problem<Item>::workTime(bool count_idle_time) {
    int total_work_time = 0;
    std::vector<int> post_end_time;

    for (int i = 0; i < this->list_size; i++) {
        if (total_work_time < this->getItem(i).getOccurTime()) {
            total_work_time += (this->getItem(i).getOccurTime() - total_work_time);

        }
        total_work_time += this->getItem(i).getWorkTime();
        post_end_time.push_back(total_work_time + this->getItem(i).getIdleTime());
    }

    if(count_idle_time){
        int helper = 0;
        for (int i = 0; i < int(post_end_time.size()); i++){
            helper = post_end_time[i] - total_work_time;
            
            if(helper > 0){
                total_work_time += helper;
            }    
        }
    }

    return total_work_time;
}

template<class Item>
void Problem<Item>::createOrClearFile(const std::string file_name) {
    std::ofstream output_file(file_name);

    if (output_file.is_open()) {
        output_file.close();
        output_file.open(file_name, std::ios::out | std::ios::trunc);
    } else {
        std::ofstream file(file_name);
        if (!file.is_open()) {
            std::cout << "Plik nie został poprawnie utworzony!\n";
            exit(EXIT_FAILURE);
        }
    }
    output_file.close();
}

template<class Item>
void Problem<Item>::savePermResult(const std::vector<Item> best_order, int best_time, std::string result_file) {
    std::ofstream output_file(result_file, std::ios::app);

    if (!output_file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku do zapisu!" << std::endl;
        exit(EXIT_FAILURE);
    }

    for (const Item &item: best_order) {
        output_file << item.getId() << " ";
    }

    output_file << "  Czas: " << best_time << std::endl;
    output_file.close();
}

template<class Item>
void Problem<Item>::displayResult(std::vector<Item> order, int time){
    std::cout << "Optymalna kolejność wykonywania powyższych zadań jest dla ułożenia: ";
    for (Item &item: order) {
        std::cout << item.getId() << " ";
    }
    std::cout << std::endl << "Czas potrzebny na wykonanie zadania w powyższej kolejności to: " << time
              << std::endl << std::endl;
}

template<class Item>
void Problem<Item>::permutationSort() {
    std::string file_destination = ("./perm_result.txt"); // commented due to unittesting
    //std::vector<Item> original = main_list;
    int perm_work_time = 0;
    int best_time;
    std::vector<Item> best_order;
    bool first_iteration = true;

    do {
        perm_work_time = this->workTime(true);
        if (first_iteration == true) {
            best_time = perm_work_time;
            best_order.assign(main_list.begin(), main_list.end());
            this->createOrClearFile(file_destination); // commented due to unittesting
            first_iteration = false;
        }
        if (perm_work_time < best_time) {
            best_time = perm_work_time;
            best_order.assign(main_list.begin(), main_list.end());
        }

        this->savePermResult(main_list, perm_work_time, file_destination); // commented due to unittesting

    } while (std::next_permutation(main_list.begin(), main_list.end()));

    std::cout << "-------------------------Przegląd zupełny-------------------------" << std::endl;
    displayResult(best_order, best_time);

    //main_list = original;
}

template<class Item>
void Problem<Item>::occurTimeSort() {
    //std::vector<Item> original = main_list;
    std::sort(main_list.begin(), main_list.end(), [](const Item &a, const Item &b) { return a.compareByOccurTime(b); });

    int best_time = this->workTime(true);
    std::cout << "------------Algorytm heurystyczny - r (termin dostępności)--------" << std::endl;
    displayResult(main_list, best_time);

    //main_list = original;
}

template<class Item>
void Problem<Item>::idleTimeSort() {
    //std::vector<Item> original = main_list;
    std::sort(main_list.begin(), main_list.end(), [](const Item &a, const Item &b) { return a.compareByIdleTime(b); });

    int best_time = this->workTime(true);
    std::cout << "------------Algorytm heurystyczny - q (czas stygnięcia)-----------" << std::endl;
    displayResult(main_list, best_time);

    //main_list = original;
}


template<class Item>
void Problem<Item>::eraseChosenElement(std::vector<Item>& list, int serial){
    auto it = list.begin();
    while (it != list.end()) {
        if (it->getId() == serial) {
            list.erase(it);
            break;
        } else {
            ++it; 
        }
    }
}

template<class Item>
void Problem<Item>::schrageAlgorithmV1() {
    std::vector<Item> helper, original = main_list;
    std::sort(original.begin(), original.end(), [](const Item &a, const Item &b) { return a.compareByOccurTime(b); });
    main_list.clear();
    main_list.push_back(original.front());
    list_size = 1;
    original.erase(original.begin());
    int current_work_time = this->workTime(false);

    while(!original.empty()){
        for(const auto& item : original) {
            if(item.getOccurTime() < current_work_time) {
                helper.push_back(item);
            }
        }

        if(!helper.empty()){
            std::sort(helper.begin(), helper.end(), [](const Item &a, const Item &b) { return a.compareByIdleTime(b); });
            main_list.push_back(helper.back());
            int num_to_erase = helper.back().getId();
            eraseChosenElement(original, num_to_erase);
        }
        else{
            main_list.push_back(original.front());
            original.erase(original.begin());
        }

        helper.clear();
        list_size++;
        current_work_time = this->workTime(false);
    }

    int total_work_time = this->workTime(true);
    std::cout << "----------------Algorytm Schrage - bez wywłaczszeń----------------" << std::endl;
    displayResult(main_list, total_work_time);
}

template<class Item>
void Problem<Item>::schrageAlgorithmV2() {
    std::vector<Item> ogrinal = main_list;

    std::priority_queue<Item, std::vector<Item>, std::function<bool(const Item&, const Item&)>> idleQueue(
        [](const Item &a, const Item &b) { return a.compareByIdleTime(b); });

    std::priority_queue<Item, std::vector<Item>, std::function<bool(const Item&, const Item&)>> helpQueue(
        [](const Item &a, const Item &b) { return a.compareByIdleTime(b); });

    std::priority_queue<Item, std::vector<Item>, std::function<bool(const Item&, const Item&)>> occurQueue(
        [](const Item &a, const Item &b) { return b.compareByOccurTime(a); });

    for (const auto &item : main_list) {
        occurQueue.push(item);
    }

    main_list.clear();
    list_size = 1;
    int current_time = 0;

    Item current_item = occurQueue.top();
    Item current_item_backup = current_item;

    while (!occurQueue.empty() || !idleQueue.empty()) {
        while (!occurQueue.empty() && occurQueue.top().getOccurTime() <= current_time) {
            idleQueue.push(occurQueue.top());
            occurQueue.pop(); 
        }

        current_time++; //nie wiem czy to tu ma być
        
        if (idleQueue.empty()) {
            current_time = occurQueue.top().getOccurTime();
        } 
        else{
            if (current_item.getWorkTime() > 0) {
                current_item.workTimeDecrement();
            }
            else { 
                main_list.push_back(current_item_backup);
                list_size++;
                
                while (!idleQueue.empty()) {
                    if (idleQueue.top().getId() == current_item_backup.getId()) {
                        idleQueue.pop();
                        break;
                    }
                    helpQueue.push(idleQueue.top());
                    idleQueue.pop();
                }

                while (!helpQueue.empty()) {
                    idleQueue.push(helpQueue.top());
                    helpQueue.pop();
                }

                current_item = idleQueue.top(); 
                current_item_backup = idleQueue.top();
                current_item.workTimeDecrement();
            }
        }
    }

    int total_work_time = this->workTime(true);
    std::cout << "----------------Algorytm Schrage - bez wywłaczszeń----------------" << std::endl;
    displayResult(main_list, total_work_time);
    main_list = ogrinal;
}

template<class Item>
void Problem<Item>::schrageAlgorithmWithExpropriation() {
    std::vector<Item> ogrinal = main_list;
    int orginal_size = list_size, last_item_id = 0, current_item_id = 0;

    std::priority_queue<Item, std::vector<Item>, std::function<bool(const Item&, const Item&)>> idleQueue(
        [](const Item &a, const Item &b) { return a.compareByIdleTime(b); });

    std::priority_queue<Item, std::vector<Item>, std::function<bool(const Item&, const Item&)>> helpQueue(
        [](const Item &a, const Item &b) { return a.compareByIdleTime(b); });

    std::priority_queue<Item, std::vector<Item>, std::function<bool(const Item&, const Item&)>> occurQueue(
        [](const Item &a, const Item &b) { return b.compareByOccurTime(a); });

    for (const auto &item : main_list) {
        occurQueue.push(item);
    }

    main_list.clear();
    list_size = 1;
    int current_time = 0;

    Item current_item = occurQueue.top();
    Item current_item_backup = current_item;

    while (!occurQueue.empty() || !idleQueue.empty()) {
        if (!idleQueue.empty()){
            last_item_id = idleQueue.top().getId();
        }
 
        while (!occurQueue.empty() && occurQueue.top().getOccurTime() <= current_time) {
            idleQueue.push(occurQueue.top());
            occurQueue.pop(); 
        }
        if (!idleQueue.empty()){
            current_item_id = idleQueue.top().getId();
        }
        current_time++; //nie wiem czy to tu ma być
        
        if (idleQueue.empty()) {
            current_time = occurQueue.top().getOccurTime();
        } 
        else{
            if (last_item_id != current_item_id && last_item_id != 0 && current_item_id != 0){
                Item top_item;
                while (!idleQueue.empty()) {
                    if (idleQueue.top().getId() == last_item_id) {
                        top_item = idleQueue.top();
                        idleQueue.pop();
                        break;
                    }
                    helpQueue.push(idleQueue.top());
                    idleQueue.pop();
                }

                top_item.setWorkTime(current_item.getWorkTime());
                idleQueue.push(top_item);

                while (!helpQueue.empty()) {
                    idleQueue.push(helpQueue.top());
                    helpQueue.pop();
                }

                current_item.setIdleTime(0);
                current_item.setWorkTime(current_item_backup.getWorkTime() - current_item.getWorkTime());
                main_list.push_back(current_item);
                list_size++;
                current_item = idleQueue.top(); 
                current_item_backup = idleQueue.top();
                current_item.workTimeDecrement();

            }
            else{
                if (current_item.getWorkTime() > 0) {
                    current_item.workTimeDecrement();


                }
                else { 
                    current_item.setWorkTime(idleQueue.top().getWorkTime());
                    main_list.push_back(current_item);
                    list_size++;
                    idleQueue.pop();
                    current_item = idleQueue.top(); 
                    current_item_backup = idleQueue.top();
                    current_item.workTimeDecrement();
                }
            }
        }
    }

    int total_work_time = this->workTime(true);
    std::cout << "----------------Algorytm Schrage - z wywłaczszeniami--------------" << std::endl;
    displayResult(main_list, total_work_time);

    list_size = orginal_size;
    main_list = ogrinal;
}

template class Problem<Item<int>>;