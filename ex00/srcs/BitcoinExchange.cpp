/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:09:17 by emimenza          #+#    #+#             */
/*   Updated: 2024/09/05 17:00:46 by emimenza         ###   ########.fr       */
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


void BitcoinExchange::loadCSVData(const std::string& csvFilePath)
{
    //check File and load the info into the map
    (void)csvFilePath;
    std::ifstream file;
    
    file.open("data.csv");
    
    if (!file)
       throw FileException();
      
    std::string line;
    if (std::getline(file, line)){}

    while (std::getline(file, line))
    {
        std::string dateStr = line.substr(0, 10);
        std::string numberStr = line.substr(11);

        isValidDate(dateStr);
        isValidValue(numberStr);
        
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
    size_t separatorPos = line.find(" | ");
    if (separatorPos == std::string::npos)
    {
        throw ParsingException();
    }

    std::string dateStr = line.substr(0, separatorPos);
    std::string numberStr = line.substr(separatorPos + 3);

    isValidDate(dateStr);
    isValidValue(numberStr);
    
    //std::cout << "date: " << dateStr << " value: " << numberStr << std::endl;
    
    getExchangeRate(dateStr, numberStr);
}


bool isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}


void BitcoinExchange::isValidDate(const std::string& date) const
{
    // Check if the string length is exactly 10 characters: YYYY-MM-DD
    if (date.size() != 10)
    {
        throw ParsingException();
    }

    // Check if the format is "XXXX-XX-XX", i.e., hyphens at positions 4 and 7
    if (date[4] != '-' || date[7] != '-')
    {
        throw ParsingException();
    }

    // Extract year, month, and day using substr and convert to integers
    int year = std::atoi(date.substr(0, 4).c_str());   // YYYY
    int month = std::atoi(date.substr(5, 2).c_str());  // MM
    int day = std::atoi(date.substr(8, 2).c_str());    // DD

    // Validate month and day ranges
    if (month < 1 || month > 12)
    {
        throw ParsingException();
    }

    // Array with the maximum number of days for each month
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Adjust February for leap years
    if (month == 2 && isLeapYear(year))
    {
        daysInMonth[1] = 29;
    }

    // Check if the day is within the allowed range for the given month
    if (day < 1 || day > daysInMonth[month - 1])
    {
        throw ParsingException();
    }
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


void BitcoinExchange::isValidValue(const std::string& value) const
{
    if (isNumeric(value))
    {
        // Convert string to double (to handle both integers and floats)
        double number = atof(value.c_str());

        // Check if the number is within float limits
        if (number >= FLT_MAX)
        {
            //large
            throw largeException();
        } 
        else if (number < 0)
        {
            //low
            throw lowException();
        }
    }
    else 
    {
        throw ParsingException();
    }
}



// void BitcoinExchange::getExchangeRate(const std::string& date, const std::string &value) const
// {
//     std::map<std::string, double>::const_iterator it = historicalPrices.find(date);
    
//     if (it != historicalPrices.end())
//     {
//         std::cout << it->first << " => " << it->second << " = " << value << std::endl;
//     }
//     else
//     {
//         it = historicalPrices.lower_bound(date);
//         if (it != historicalPrices.end())
//         {
//             std::cout << it->first << " => " << it->second << " = " << value << std::endl;
//         }
//     }
// }

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
