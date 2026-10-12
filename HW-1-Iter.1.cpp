#include <iostream>
class Fighter {
private:
    const char* name;
    int health;
    int maxHealth;
    int damage;
public:
    Fighter(const char* name, int health, int damage)
        : name(name), health(health), maxHealth(health), damage(damage) {}

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
};
void PrintFighter(const Fighter& fighter) {
    fighter.PrintStatus();
}
class Game {
private:
    Fighter player;
    Fighter enemy;
public:
    Game()
        : player("Hero", 30, 8),
          enemy("Enemy", 12, 3) {}
    void Run() {
        std::cout << "=== ARENA ===\n\n";
        while (true) {
            std::cout << "--- Fighters status ---\n";
            PrintFighter(player);
            PrintFighter(enemy);
            std::cout << "\n";
            std::cout << "Commands: 1 - attack, 0 - exit\n";
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
                player.Attack(enemy);
                if (!enemy.IsAlive()) {
                    std::cout << "\nEnemy defeated! You win!\n";
                    PrintFighter(enemy);
                    break;
                }
                enemy.Attack(player);
                if (!player.IsAlive()) {
                    std::cout << "\nYou died! Defeat.\n";
                    PrintFighter(player);
                    break;
                }
            } else {
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