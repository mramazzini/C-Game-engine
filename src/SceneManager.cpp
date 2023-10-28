#include "../include/SceneManager.h"
#include <iostream>

SceneManager::SceneManager(Manager *mManager)
{
    manager = mManager;
    loadScene(Scene::Game);
}

SceneManager::~SceneManager()
{
}

void SceneManager::loadScene(Scene scene)
{

    currentScene = scene;
    std::cout << "Loading scene: " << SceneName(scene) << std::endl;
}

std::string SceneManager::SceneName(Scene scene)
{
    switch (scene)
    {
    case Scene::MainMenu:
        return "MainMenu";
        break;
    case Scene::Game:
        return "Game";
        break;
    case Scene::Settings:
        return "Settings";
        break;
    case Scene::Pause:
        return "Pause";
        break;
    default:
        return "MainMenu";
        break;
    }
}

void SceneManager::toggleSettings()
{

    if (currentScene == Scene::Settings)
    {
        loadScene(Scene::Game);
    }
    else if (currentScene == Scene::Game)
    {
        loadScene(Scene::Settings);
    }
}