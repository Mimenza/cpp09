/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:09:17 by emimenza          #+#    #+#             */
/*   Updated: 2024/10/14 16:42:18 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/BitcoinExchange.hpp"
BitcoinExchange::BitcoinExchange(const std::string& csvFilePath)
{
    loadCSVData(csvFilePath);
    // for (std::map<std::string, double>::const_iterator it = historicalPrices.begin(); it != historicalPrices.end(); ++it) {
    //     std::cout << "Fecha: " << it->first << ", Precio: " << it->second << std::endl;
    // }
}

std::string currentDate()
{
    std::time_t t = std::time(NULL);
    std::tm* now = std::localtime(&t);

    char buffer[11];

    std::sprintf(buffer, "%04d-%02d-%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);

    return std::string(buffer);
}

bool checkDateExpiration(int year, int month, int day)
{
    const std::string date= currentDate();
    int cYear = std::atoi(date.substr(0, 4).c_str());
    int cMonth = std::atoi(date.substr(5, 2).c_str());
    int cDay = std::atoi(date.substr(8, 2).c_str());

    if (year > cYear)
    {
        return false;
    }
    else if (year == cYear)
        {
        if (month > cMonth)
        {
            return false;
        }
        else if (month == cMonth)
            {
            if (day > cDay)
            {
                return false;
            }
        }
    }
    return true;
}


void BitcoinExchange::loadCSVData(const std::string& csvFilePath)
{
    //check File and load the info into the map
    //(void)csvFilePath;
    std::ifstream file;
    
    file.open(csvFilePath.c_str());
    
    if (!file)
       throw FileException();
      
    std::string line;
    if (std::getline(file, line)){}

    while (std::getline(file, line))
    {
        std::string dateStr = line.substr(0, 10);
        std::string numberStr = line.substr(11);

        isValidDate(dateStr);
        isValidValue(numberStr, 0);
        
        //conver to double
        std::stringstream ss(numberStr);
        double number;
        char end;
        
        if (!(ss >> number) || ss.get(end))
        {
            throw processException();
        }
        //fill the map
        historicalPrices[dateStr] = number;
    }

    file.close();
}


void BitcoinExchange::processInputFile(int argc, char **argv)
{
    if (argc != 2)
        throw ArgumentsException();

    std::ifstream file(argv[1]);
    
    if (!file.is_open())
       throw FileException();
      
   
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
       processLine(line);
    }

    file.close();
}


void BitcoinExchange::processLine(const std::string& line)
{    
    size_t separatorPos = line.find(" | ");
    if (separatorPos == std::string::npos)
    {
        // Error: missing separator
        std::cout << "Error: bad input. '|' not found in line: " << line << std::endl;
        return;  // Continue with the next line
    }

    std::string dateStr = line.substr(0, separatorPos);
    std::string numberStr = line.substr(separatorPos + 3);

    if (!isValidDate(dateStr))
    {
        std::cout << "Error: invalid date: " << dateStr << std::endl;
        return;  // Continue with the next line
    }

    if (!isValidValue(numberStr, 1))
    {
        //std::cout << "Error: invalid value: " << numberStr << std::endl;
        return;  // Continue with the next line
    }
    
    getExchangeRate(dateStr, numberStr);
}


bool isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}


bool BitcoinExchange::isValidDate(const std::string& date) const
{
    if (date.size() != 10)
    {
        return false;
    }
    
    if (date[4] != '-' || date[7] != '-')
    {
        return false;
    }
    
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
    {
        return false;
    }
    
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && isLeapYear(year))
    {
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1])
    {
        return false;
    }
    
    if (!checkDateExpiration(year, month, day))
    {
        return false;
    }

    return true;
}


bool isNumeric(const std::string& str)
{
    bool hasDecimalPoint = false;
    std::size_t start = 0;

    // Check if the number starts with a negative sign
    if (str[0] == '-')
    {
        start = 1;
    }

    // String must have at least one digit after the negative sign (if present)
    if (str.size() == start)
    {
        return false;
    }

    for (std::size_t i = start; i < str.size(); ++i)
    {
        if (str[i] == '.')
        {
            // Only one decimal point is allowed
            if (hasDecimalPoint)
            {
                return false;
            }
            hasDecimalPoint = true;
        }
        else if (!isdigit(str[i]))
        {
            // If it's not a digit, it's not a valid number
            return false;
        }
    }

    // String cannot start or end with a decimal point
    if (str[start] == '.' || str[str.size() - 1] == '.')
    {
        return false;
    }

    return true;
}


bool BitcoinExchange::isValidValue(const std::string& value, int mode) const
{
    if (isNumeric(value))
    {
        float number = atof(value.c_str());

        if (number >= 1000 && mode == 1)
        {
            std::cout << "Error: value too large: " << value << std::endl;
            return false;
        } 
        else if (number < 0)
        {
            std::cout << "Error: value is not positive: " << value << std::endl;
            return false;
        }
    }
    else 
    {
        return false;
    }

    return true;
}


void BitcoinExchange::getExchangeRate(const std::string& date, const std::string& value) const {
    // Convertir value a double
    std::stringstream ss(value);
    double valueDouble;
    char end;

    if (!(ss >> valueDouble) || ss.get(end)) {
        std::cerr << "Error: Valor inválido para conversión: " << value << std::endl;
        return;
    }

    // Buscar la fecha exacta
    std::map<std::string, double>::const_iterator it = historicalPrices.find(date);

    if (it != historicalPrices.end()) {
        // Fecha exacta encontrada
        std::cout << it->first << " => " << it->second << " * " << value << " = " << it->second * valueDouble << std::endl;
    } else {
        // Fecha exacta no encontrada, buscar la fecha más cercana anterior
        it = historicalPrices.lower_bound(date);
        if (it != historicalPrices.begin())
        {
            --it;
            std::cout << it->first << " => " << it->second << " * " << value << " = " << it->second * valueDouble << std::endl;
        }
    }
}

//------------------------------------------------------------------

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    historicalPrices = other.historicalPrices;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        historicalPrices = other.historicalPrices;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}
