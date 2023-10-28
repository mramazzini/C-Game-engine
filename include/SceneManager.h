#pragma once
#include <string>

class Map;
class Manager;

class SceneManager
{
public:
    enum Scene
    {
        MainMenu,
        Game,
        Settings,
        Pause
    };

    SceneManager(Manager *mManager);
    ~SceneManager();
    void loadScene(Scene scene);
    Scene currentScene;
    std::string SceneName(Scene scene);
    void toggleSettings();

private:
    Manager *manager;
};