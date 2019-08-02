//
// Created by shiro on 02.08.19.
//

#include <fstream>
#include <regex>
#include "DataLoader.h"
#include "InvalidExpressionError.h"

DataLoader::DataLoader(const std::string &fileName) {

    std::ifstream file{fileName};

    if(!file)
    {

    } else {
        open = true;
        getline(file,expressionString);
        if(!hasCorrectCharacters()) {
            file.close();
            throw InvalidExpressionError{"Invalid characters in input"};
        }
        if(hasX())
        {
            std::string tempX{};
            getline(file,tempX);
            try {
                xValue = stoi(tempX);
            } catch (std::invalid_argument invalidArgumentException)
            {
                //TODO: Handle the error
                file.close();
            }
        }


    }


}

const std::string &DataLoader::getExpressionString() const {
    return expressionString;
}

int DataLoader::getXValue() const {
    return xValue;
}

bool DataLoader::isOpen() const {
    return open;
}

bool DataLoader::hasX() {
    return expressionString.find('x') != std::string::npos;
}

bool DataLoader::hasCorrectCharacters() {
    std::regex reg{"[^+\\-\\\\*0-9 x]+"};
    return !std::regex_search(expressionString, reg);
}
