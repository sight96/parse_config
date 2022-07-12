#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include "acl/acl.h"
//#include "utils.h"
typedef enum Result
{
    SUCCESS = 0,
    FAILED = 1
} Result;
class ConfigParser
{
public : 
    Result ParseConfig(const std::string &fileName);

    inline void Trim(std::string &str) const;

    Result GetIntValue(const std::string &name, int &value) const;

    Result GetFloatValue(const std::string &name, float &value) const;

    Result GetStringValue(const std::string &name, std::string &value) const;

    Result GetVectorStringValue(const std::string &name, std::vector<std:: string> &vector) const;

private:
    std::map<std::string, std::string> configData_ = {};
};
