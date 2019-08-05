#include <utility>

//
// Created by shiro on 02.08.19.
//

#ifndef PREFIXNOTATIONPARSER_INVALIDEXPRESSIONERROR_H
#define PREFIXNOTATIONPARSER_INVALIDEXPRESSIONERROR_H


#include <string>
/**
 * Custom error class for PrefixExpression and DataLoader
 */
class InvalidExpressionError : public std::exception {
public:
    const char *what() const noexcept override {
        return errorMessage.c_str();
    }


    explicit InvalidExpressionError(std::string errorMessage) : errorMessage(std::move(errorMessage)) {}

private:
    std::string errorMessage;


};



#endif //PREFIXNOTATIONPARSER_INVALIDEXPRESSIONERROR_H
