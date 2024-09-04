/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:09:17 by emimenza          #+#    #+#             */
/*   Updated: 2024/09/04 17:02:33 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/BitcoinExchange.hpp"
BitcoinExchange::BitcoinExchange(const std::string& csvFilePath)
{
    loadCSVData(csvFilePath);
}

void BitcoinExchange::loadCSVData(const std::string& csvFilePath)
{
    //check File and load the info into the map
    (void)csvFilePath;
}

void BitcoinExchange::processInputFile(int argc, char **argv)
{
    std::ifstream file;
    
    if (argc != 2)
        throw ArgumentsException();

    file.open(argv[1]);

    if (!file)
       throw FileException();
      
        
    std::string line;
    while (std::getline(file, line))
    {
       processLine(line);
    }

    file.close();
}

void BitcoinExchange::processLine(const std::string& line)
{
    std::string date, value;
    
    size_t separatorPos = line.find(" | ");
    if (separatorPos == std::string::npos)
    {
        throw ParsingException();
    }

    // Dividir la cadena en la fecha y el número
    std::string dateStr = line.substr(0, separatorPos);
    std::string numberStr = line.substr(separatorPos + 3);

    isValidDate(dateStr);
    isValidValue(numberStr);
    
    std::cout << "date: " << dateStr << " value: " << numberStr << std::endl;
}

void BitcoinExchange::isValidDate(const std::string& date) const
{
    //Has no " "
    if (std::string::npos != date.find(" "))
        throw ParsingException();
    
    //Has 2 "-"
    if (2 != std::count(date.begin(), date.end(), '-'))
        throw ParsingException();
    
    //Has 10 size
    if (10 != date.size())
        throw ParsingException();
}

void BitcoinExchange::isValidValue(const std::string& value) const
{
    if (std::string::npos != value.find(" "))
        throw ParsingException();
}

// double BitcoinExchange::getExchangeRate(const std::string& date) const
// {
    
// }

//------------------------------------------------------------------
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    historicalPrices = other.historicalPrices;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        historicalPrices = other.historicalPrices;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}
