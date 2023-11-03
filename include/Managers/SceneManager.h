#pragma once
#include <string>

class Map;
class Coordinator;

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

    SceneManager(Coordinator *coordinator);
    ~SceneManager();
    void loadScene(Scene scene);
    Scene currentScene;
    std::string SceneName(Scene scene);
    void toggleSettings();

private:
    Coordinator *coordinator;
};