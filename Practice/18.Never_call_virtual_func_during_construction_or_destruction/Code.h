#pragma once 
#include <iostream>

class Game {
public:
    Game(){
        init();
    };

    void init() {
        Log();
    }

    ~Game(){
        std::cout << "~Game() Log()" << std::endl;
    };

    virtual void Log() const {
        std::cout << "Game Log()" << std::endl;
    }

};

class Kill : public Game {
public:
    virtual void Log() const override {
        std::cout << "Kill Log()" << std::endl;
    }
};

class BeKill : public Game {
public:
    virtual void Log() const override {
        std::cout << "BeKill Log()" << std::endl;
    }
};
