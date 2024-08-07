#include "configmanager.h"

ConfigManager::ConfigManager(const char* filePath)
    : m_filePath(filePath){}

std::map<std::string, std::string> ConfigManager::readConfig()
{
    std::ifstream configFile(m_filePath);
    std::map<std::string, std::string> configMap;

    if (configFile.is_open()) {
        std::string line;
        bool isEmpty = true;

        while (std::getline(configFile, line)) {
            if (!line.empty()) {
                isEmpty = false;
                std::istringstream lineStream(line);
                std::string key;
                if (std::getline(lineStream, key, '=')) {
                    std::string value;
                    if (std::getline(lineStream, value)) {
                        configMap[key] = value;
                    }
                }
            }
        }
        configFile.close();

        if (isEmpty) {
            configMap["username"] = "username";
            configMap["address"] = "localhost";
            configMap["port"] = "5555";
        }
    } else {
        configMap["username"] = "username";
        configMap["address"] = "localhost";
        configMap["port"] = "5555";
    }

    return configMap;
}

void ConfigManager::saveConfig(std::map<std::string, std::string> &configMap){
    std::ofstream configFile(m_filePath);
    if (configFile.is_open()) {
        for (const auto& pair : configMap) {
            configFile << pair.first << "=" << pair.second << std::endl;
        }
        configFile.close();
    }
}

