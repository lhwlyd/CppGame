#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(){}
GameObjectManager::~GameObjectManager(){
    std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator() );
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject){
    _gameObjects.insert( std::pair<std::string, VisibleGameObject*>(name, gameObject) );
}

void GameObjectManager::Remove(std::string name){
    auto results = _gameObjects.find(name);
    if(results != _gameObjects.end() ){
        delete results->second;
        _gameObjects.erase(results);
    }
}

VisibleGameObject* GameObjectManager::Get(std::string name) const{
    auto results = _gameObjects.find(name);
    if( results == _gameObjects.end() ){
        return NULL;
    }

    return results->second;
}

int GameObjectManager::GetObjectCount() const {
    return _gameObjects.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow){
    auto it = _gameObjects.begin();
    while( it != _gameObjects.end() ){
        it->second->Draw(renderWindow);
        ++it;
    }
}