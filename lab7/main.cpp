#include "include/common.h"
#include "include/npc.h"
#include "include/bear.h"
#include "include/vup.h"
#include "include/vykhuhol.h"
#include "include/factory.h"
#include "include/visitor.h"
#include "include/observers.h"
#include "include/fight_manager.h"

#include <memory>
#include <set>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <shared_mutex>
#include <chrono>
#include <atomic>
#include <vector>

using namespace std::chrono_literals;

std::mutex print_mutex;
std::mutex cout_mutex;
std::shared_mutex npc_array_mutex;
std::atomic<bool> stop_game{false};

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;

std::pair<int, int> get_random_position() {
    return { std::rand() % MAP_WIDTH, std::rand() % MAP_HEIGHT };
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    set_t npc_array;

    {
        std::unique_lock<std::shared_mutex> lock(npc_array_mutex);
        for (size_t i = 0; i < 50; ++i) {
            NpcType type = static_cast<NpcType>(std::rand() % 3 + 1); // 1, 2 или 3
            auto [x, y] = get_random_position();
            npc_array.insert(factory(type, x, y));
        }
    }

    FightManager fight_manager;

    std::thread fight_thread([&fight_manager, &npc_array]() {
    while (!stop_game.load()) {
        std::optional<FightEvent> event = fight_manager.get_event();
        
        if (stop_game.load()) break; // Проверка на завершение

        if (!event) {
            std::this_thread::sleep_for(10ms); // Уменьшаем нагрузку
            continue;
        }

        auto attacker = event->attacker;
        auto defender = event->defender;

        {
            std::shared_lock<std::shared_mutex> lock(npc_array_mutex);
            if (!attacker->is_alive() || !defender->is_alive())
                continue;
        }

        int attack_roll = std::rand() % 6 + 1; 
        int defense_roll = std::rand() % 6 + 1; 

        bool win = attack_roll > defense_roll;

        {
            std::unique_lock<std::shared_mutex> lock(npc_array_mutex);
            if (win) {
                defender->die();
            }
        }

        attacker->fight_notify(defender, attack_roll, defense_roll, win);

        {
            std::lock_guard<std::mutex> cout_lock(cout_mutex);
            std::cout << "\nFight Details --------\n";
            std::cout << "Attacker:\n";
            attacker->print();
            std::cout << "Defender:\n";
            defender->print();
            std::cout << "Attack roll: " << attack_roll
                      << ", Defense roll: " << defense_roll << '\n';
            std::cout << (win ? "Defender died!\n\n" : "Defender survived.\n\n");
        }
    }
});


    std::thread movement_thread([&fight_manager, &npc_array]() {
    while (!stop_game.load()) {
        std::vector<std::shared_ptr<NPC>> npcs_copy;

        {
            std::shared_lock<std::shared_mutex> lock(npc_array_mutex);
            for (const auto& npc : npc_array) {
                if (npc->is_alive()) {
                    npcs_copy.push_back(npc);
                }
            }
        }
        
        

        for (auto& npc : npcs_copy) {
            if (stop_game.load()) break; // Проверка на завершение

            npc->move(); 

            {
                std::unique_lock<std::shared_mutex> lock(npc_array_mutex);
                auto [x, y] = npc->position();
                if (x < 0) x = 0;
                if (x >= MAP_WIDTH) x = MAP_WIDTH - 1;
                if (y < 0) y = 0;
                if (y >= MAP_HEIGHT) y = MAP_HEIGHT - 1;
            }
        }

        std::this_thread::sleep_for(100ms);
    }
});


    std::thread print_thread([&npc_array]() {
        while (!stop_game.load()) {
            std::this_thread::sleep_for(1s);
            std::vector<std::shared_ptr<NPC>> live_npcs;
            {
                std::shared_lock<std::shared_mutex> lock(npc_array_mutex);
                for (const auto& npc : npc_array) {
                    if (npc->is_alive()) {
                        live_npcs.push_back(npc);
                    }
                }
            }
            std::vector<std::vector<char>> map(MAP_HEIGHT, std::vector<char>(MAP_WIDTH, '.'));
            {
                std::shared_lock<std::shared_mutex> lock(npc_array_mutex);
                for (const auto& npc : live_npcs) {
                    auto [x, y] = npc->position();
                    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
                        char symbol = 'N'; 
                        switch (npc->get_type()) {
                            case BearType:
                                symbol = 'B';
                                break;
                            case VupType:
                                symbol = 'V';
                                break;
                            case VykhuholType:
                                symbol = 'Y';
                                break;
                            default:
                                symbol = 'N';
                                break;
                        }
                        map[y][x] = symbol;
                    }
                }
            }
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "\n=== Map ===\n";
                for (const auto& row : map) {
                    for (const auto& cell : row) {
                        std::cout << "[" << (cell != '.' ? cell : ' ') << "]";
                    }
                    std::cout << '\n';
                }
                std::cout << "===========\n";
            }
        }
    });

    std::this_thread::sleep_for(30s);
    stop_game.store(true);

    fight_manager.stop_processing();
    fight_thread.join();
    movement_thread.join();
    print_thread.join();

    {
        std::shared_lock<std::shared_mutex> lock(npc_array_mutex);
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        std::cout << "\n=== Survivors ===\n";
        for (const auto& npc : npc_array) {
            if (npc->is_alive()) {
                npc->print();
            }
        }
        std::cout << "==================\n";
    }

    return 0;
}
