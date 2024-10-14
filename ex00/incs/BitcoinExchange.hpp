/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:35:56 by emimenza          #+#    #+#             */
/*   Updated: 2024/10/14 16:38:54 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTC_HPP
#define BTC_HPP

# include <iostream>
# include <fstream>
# include <map>
# include <algorithm>
# include <cctype>  // For isdigit
# include <cstdlib> // For atof
# include <climits> // For INT_MIN, INT_MAX
# include <cfloat>  // For float/double limits
# include <sstream> // Para std::stringstream
# include <cstdio>
# include <ctime>

class ArgumentsException : public std::exception {
public:
    const char* what() const throw() {
        return "Error: must have 1 arg.";
    }
};

class FileException : public std::exception {
public:
    const char* what() const throw() {
        return "Error: could not open file.";
    }
};

class ParsingException : public std::exception {
public:
    const char* what() const throw() {
        return "Error: bad input.";
    }
};

class lowException : public std::exception {
public:
    const char* what() const throw() {
        return "Error: not a positive number";
    }
};

class largeException : public std::exception {
public:
    const char* what() const throw() {
        return "Error: to large a number.";
    }
};

class limitsException : public std::exception {
public:
    const char* what() const throw() {
        return "Error: The number is outside the limits of a float.";
    }
};

class processException : public std::exception {
public:
    const char* what() const throw() {
        return "Error: the csv table did not load correctly.";
    }
};

class BitcoinExchange {
    public:
        BitcoinExchange(const std::string& csvFilePath);
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void processInputFile(int argc, char **argv);

    private:
        void loadCSVData(const std::string& csvFilePath);
        void processLine(const std::string& line);

        bool isValidDate(const std::string& date) const;
        bool isValidValue(const std::string& value, int mode) const;
        
        void getExchangeRate(const std::string& date, const std::string &value) const;

        std::map<std::string, double> historicalPrices;
};

#endif