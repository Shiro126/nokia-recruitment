#include <utility>

//
// Created by shiro on 02.08.19.
//

#ifndef PREFIXNOTATIONPARSER_INVALIDEXPRESSIONERROR_H
#define PREFIXNOTATIONPARSER_INVALIDEXPRESSIONERROR_H


#include <string>

class InvalidExpressionError {
public:
    const std::string &getErrorMessage() const {
        return errorMessage;
    }

    InvalidExpressionError(std::string errorMessage) : errorMessage(std::move(errorMessage)) {}

private:
    std::string errorMessage;


};



#endif //PREFIXNOTATIONPARSER_INVALIDEXPRESSIONERROR_H
