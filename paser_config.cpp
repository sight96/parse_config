#include "./inc/paesr_config.h"

namespace {
    const char COMMENT_CHARATER = '#';
    void  Split(const std::string &inString, std::vector<std::string> &outVector, const char delimiter)
    {
        std::stringstream ss(inString);
        std::string item;
        while (std::getline(ss, item, delimiter)) {
            outVector.push_back(item);
        }
    }
}

Result ConfigParser::ParseConfig(const std::string &filename)
{
    std::ifstream inFile(filename);
    char COMMENT_CHARATER = '#';
    if (!inFile.is_open())
    {
        std::cout << "cannot read setup.config file!" << std::endl;
        return FAILED;
    }
    std::string line, newLine;
    int startPos, endPos, pos;
    while (getline(inFile, line))
    {
        if (line.empty())
        {
            continue;
        }
        startPos = 0;
        endPos = line.size() - 1;
        pos = line.find(COMMENT_CHARATER);
        if (pos != -1)
        {
            if (pos == 0)
            {
                continue;
            }
            endPos = pos - 1;
        }
        newLine = line.substr(startPos, (endPos - startPos) + 1);
        pos = newLine.find('=');
        if (pos == -1)
        {
            continue;
        }
        std::string na = newLine.substr(0, pos);
        Trim(na);
        std::string value = newLine.substr(pos + 1, endPos + 1 - (pos + 1));
        Trim(value);
        configData_.insert(std::make_pair(na, value));
    }
    inFile.close();
    return SUCCESS;
}

inline void ConfigParser::Trim(std::string &str) const
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun(::isspace))));
    str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun(::isspace))).base(), str.end());
    return;
}

Result ConfigParser::GetStringValue(const std::string &name, std::string &value) const
{
    if (configData_.count(name) == 0)
    {
        return FAILED;
    }
    value = configData_.find(name)->second;
    return SUCCESS;
}

Result ConfigParser::GetIntValue(const std::string &name, int &value) const
{
    if (configData_.count(name) == 0)
    {
        return FAILED;
    }
    std::string str = configData_.find(name)->second;
    if (!(std::stringstream(str) >> value))
    {
        return FAILED;
    }
    return SUCCESS;
}

Result ConfigParser::GetFloatValue(const std::string &name, float &value) const
{
    if (configData_.count(name) == 0)
    {
        return FAILED;
    }
    std::string str = configData_.find(name)->second;
    if (!(std::stringstream(str) >> value))
    {
        return FAILED;
    }
    return SUCCESS;
}

Result ConfigParser::GetVectorStringValue(const std::string &name, std::vector<std:: string> &vector) const
{
    if (configData_.count(name) == 0) {
        return FAILED;
    }
    std::string str = configData_.find(name)->second;
    
    std::vector<std::string> splits;
    
    Split(str, splits, ',');

    std::string value ;
    
    std::stringstream ss;
    for (auto &it : splits) {

        if (!it.empty()) {
            std::stringstream ss(it);
            ss << it;
            ss >> value;
           
            vector.push_back(value);
        }
    }
    
    return SUCCESS;
}