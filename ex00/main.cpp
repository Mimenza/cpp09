/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:34:50 by emimenza          #+#    #+#             */
/*   Updated: 2024/09/04 15:23:04 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/BitcoinExchange.hpp"

// void checkData(std::string line)
// {
    
// }

// void readData(std::ifstream& file)
// {
//     std::string line;
//     while (std::getline(file, line))
//     {
//        checkData(line);
//     }
// }

// void checkInput(int argc, char **argv)
// {
//     std::ifstream file;
    
//     if (argc != 2)
//         throw ArgumentsException();

//     file.open(argv[1]);

//     if (!file)
//        throw FileException();
        
//     readData(file);

//     file.close();
// }

int main(int argc, char **argv)
{
    try
    {
        BitcoinExchange btcEx("data.csv");
        btcEx.processInputFile(argc, argv);
        
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}