#include <iostream>
class Fighter {
private:
    const char* name;
    int health;
    int maxHealth;
    int damage;
public:
    Fighter(const char* name, int health, int damage)
        : name(name), health(health), maxHealth(health), damage(damage) {
    }
    void TakeDamage(int amount) {
        health -= amount;
        if (health < 0) {
            health = 0;
        }
    }
    void Attack(Fighter& target) const {
        std::cout << name << " attacks " << target.name << " and deals " << damage << " damage!\n";
        target.TakeDamage(damage);
    }

    bool IsAlive() const {
        return health > 0;
    }
    void PrintStatus() const {
        std::cout << name << " [HP: " << health << "/" << maxHealth << ", DMG: " << damage << "]";
        if (!IsAlive()) {
            std::cout << " (dead)";
        }
        std::cout << "\n";
    }
    const char* GetName() const {
        return name;
    }
};
void PrintFighter(const Fighter& fighter) {
    fighter.PrintStatus();
}
class Game {
private:
    Fighter player;
    Fighter enemies[3];
    Fighter* currentTarget;

    bool TrySelectTarget(int number, Fighter*& outTarget) {
        outTarget = nullptr;

        if (number < 1 || number > 3) {
            std::cout << "Invalid target number. Choose 1, 2 or 3.\n";
            return false;
        }

        if (!enemies[number - 1].IsAlive()) {
            std::cout << "This enemy is already dead. Choose another one.\n";
            return false;
        }

        outTarget = &enemies[number - 1];
        return true;
    }

    bool AllEnemiesDefeated() const {
        for (int i = 0; i < 3; ++i) {
            if (enemies[i].IsAlive()) {
                return false;
            }
        }
        return true;
    }

public:
    Game()
        : player("Hero", 30, 8),
        enemies{ {"Enemy 1", 12, 3},
                {"Enemy 2", 18, 4},
                {"Enemy 3", 24, 5} },
        currentTarget(nullptr) {
    }

    void Run() {
        std::cout << "=== ARENA ===\n\n";

        while (true) {
            std::cout << "--- Fighters status ---\n";
            PrintFighter(player);
            std::cout << "\nEnemies:\n";
            for (int i = 0; i < 3; ++i) {
                std::cout << "  " << (i + 1) << ". ";
                PrintFighter(enemies[i]);
            }
            std::cout << "\nCurrent target: ";
            if (currentTarget != nullptr) {
                std::cout << currentTarget->GetName() << "\n";
            }
            else {
                std::cout << "not selected\n";
            }
            std::cout << "\nCommands: 1 - select target, 2 - attack, 0 - exit\n";
            std::cout << "Your choice: ";

            int command;
            if (!(std::cin >> command)) {
                std::cout << "Input ended. Exiting game.\n";
                break;
            }
            if (command == 0) {
                std::cout << "You left the arena.\n";
                break;
            }
            if (command == 1) {
                std::cout << "Enter target number (1-3): ";
                int targetNum;
                if (!(std::cin >> targetNum)) {
                    std::cout << "Input ended. Exiting game.\n";
                    break;
                }

                if (TrySelectTarget(targetNum, currentTarget)) {
                    std::cout << "Target selected: " << currentTarget->GetName() << "\n";
                }
            }
            else if (command == 2) {
                if (currentTarget == nullptr) {
                    std::cout << "No target selected! Please select a target first.\n";
                }
                else {
                    player.Attack(*currentTarget);

                    if (!currentTarget->IsAlive()) {
                        std::cout << currentTarget->GetName() << " has been defeated!\n";
                        currentTarget = nullptr;

                        if (AllEnemiesDefeated()) {
                            std::cout << "\nAll enemies defeated! You win!\n";
                            PrintFighter(player);
                            break;
                        }
                    }
                    else {
                        currentTarget->Attack(player);

                        if (!player.IsAlive()) {
                            std::cout << "\nYou died! Defeat.\n";
                            PrintFighter(player);
                            break;
                        }
                    }
                }
            }
            else {
                std::cout << "Unknown command.\n";
            }

            std::cout << "\n";
        }
    }
};
int main() {
    Game game;
    game.Run();
    return 0;
}