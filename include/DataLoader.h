//
// Created by shiro on 02.08.19.
//

#ifndef PREFIXNOTATIONPARSER_DATALOADER_H
#define PREFIXNOTATIONPARSER_DATALOADER_H


#include <string>

class DataLoader {
private:

    bool hasX();
    bool hasCorrectCharacters();
    std::string expressionString{};
    int xValue{};
    bool loaded = false;
  //  friend class MockDataLoader;


public:
    bool hasData() const;


    explicit DataLoader(const std::string &fileName);

    int getXValue() const;
    const std::string &getExpressionString() const;

    void readFromFile(const std::string &fileName);

    DataLoader();
};


#endif //PREFIXNOTATIONPARSER_DATALOADER_H
