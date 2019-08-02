//
// Created by shiro on 02.08.19.
//

#ifndef PREFIXNOTATIONPARSER_DATALOADER_H
#define PREFIXNOTATIONPARSER_DATALOADER_H


#include <string>

class DataLoader {
private:
    std::string expressionString{};
    int xValue{};
    bool open = false;


public:
    bool isOpen() const;


    explicit DataLoader(const std::string &fileName);

    int getXValue() const;
    const std::string &getExpressionString() const;
    bool hasX();
    bool hasCorrectCharacters();


};


#endif //PREFIXNOTATIONPARSER_DATALOADER_H
