#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <map>

class ConfigManager
{
public:
    ConfigManager(const char* filePath);
    std::map<std::string, std::string> readConfig();
    void saveConfig(std::map<std::string, std::string>& configMap);
private:
    std::string m_filePath;
};

