//
// Created by shiro on 02.08.19.
//

#include <fstream>
#include <regex>
#include "DataLoader.h"
#include "InvalidExpressionError.h"

DataLoader::DataLoader(const std::string &fileName) {

    try
    {
        readFromFile(fileName);
    } catch (InvalidExpressionError &error)
    {
        loaded=false;
        expressionString="";
        throw;
    }

}

const std::string &DataLoader::getExpressionString() const {
    return expressionString;
}

int DataLoader::getXValue() const {
    return xValue;
}

bool DataLoader::hasData() const {
    return loaded;
}

bool DataLoader::hasX() {
    return expressionString.find('x') != std::string::npos;
}

bool DataLoader::hasCorrectCharacters() {
    std::regex reg{R"([^+\-/*0-9 x]+)"};
    return !std::regex_search(expressionString, reg);
}

void DataLoader::readFromFile(const std::string &fileName) {

    std::ifstream file{fileName};

    if(!file)
    {
        throw InvalidExpressionError{"Could not loaded the file named: " + fileName};

    } else {
        getline(file,expressionString);
        if(!hasCorrectCharacters()) {
            file.close();
            throw InvalidExpressionError{"Invalid characters in input."};
        }
        if(hasX())
        {
            std::string tempX{};
            getline(file,tempX);
            try {
                xValue = stoi(tempX);
            } catch (std::invalid_argument &invalidArgumentException)
            {
                file.close();
                throw InvalidExpressionError{"X value is invalid."};
            }
        }
        loaded = true;

    }



}
