/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:35:56 by emimenza          #+#    #+#             */
/*   Updated: 2024/09/04 15:54:55 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTC_HPP
#define BTC_HPP

# include <iostream>
# include <fstream>
# include <map>
# include <algorithm>

class ArgumentsException : public std::exception {
public:
    const char* what() const throw() {
        return "Error: must have only 1 arg.";
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
        void isValidDate(const std::string& date) const;
        void isValidValue(const std::string& value) const;
        // double getExchangeRate(const std::string& date) const;

        std::map<std::string, double> historicalPrices;
};

#endif