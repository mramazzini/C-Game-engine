#include <string>
class Manager;
class LevelManager
{

public:
    LevelManager(Manager *manager);
    ~LevelManager();
    void loadLevel();
    void loadLevel(std::string level);
    void update();
    void render();
    void clean();

    static void setLevel(std::string level);
    static int getLevel();

private:
    Manager *manager;
};