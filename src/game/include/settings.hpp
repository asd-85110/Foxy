#pragma once
#ifndef SETTINGS_HPP
#define SETTINGS_HPP
#define CONFIGURES_COUNT 2
#include<cstdint>
enum ConfigureFlags{
    DIFFCULTY=0,
    SPAWN_AMOUNT=1
};
extern std::uint8_t Configures[CONFIGURES_COUNT];
#endif