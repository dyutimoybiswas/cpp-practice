#include "chapter11.hpp"

void wordTransform(std::ifstream& mapFile, std::ifstream& input) {
    auto transMap = buildMap(mapFile);  // convert mappings to key,value pairs
    std::string text;
    while (getline(input, text)) {      // read lines
        std::istringstream iss(text);
        std::string word;
        bool firstWord = true;
        while (iss >> word) {           // read words
            if (firstWord)
                firstWord = false;
            else
                std::cout << " ";       // print leading space if not first word
            std::cout << transform(word, transMap);     // returns transformed word
        }
        std::cout << std::endl;     // next line
    }
}

std::map<std::string, std::string> buildMap (std::ifstream& mapFile){
    
    std::map<std::string, std::string> tMap;
    std::string key, value;
    
    // read first word into key and rest of line into value.
    while (mapFile >> key && getline(mapFile, value)) {
        // std::clog << key << ", " << value << std::endl;     // debug
        if (value.size() > 1)            // check transformation exists
            tMap[key] = value.substr(1); // ignore leading space
        else
            throw std::runtime_error("no rule for " + key);
    }
    return tMap;
}

const std::string& transform(const std::string& s, const std::map<std::string, std::string>& m) {

    auto it = m.find(s);

    // use replacement word if transformation exists, else return the word.
    return it != m.cend() ? it->second : s;
}
