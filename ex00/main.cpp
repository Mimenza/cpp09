/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:34:50 by emimenza          #+#    #+#             */
/*   Updated: 2024/09/05 15:56:27 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/BitcoinExchange.hpp"

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