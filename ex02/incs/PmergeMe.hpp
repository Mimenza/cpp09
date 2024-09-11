/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:57:47 by emimenza          #+#    #+#             */
/*   Updated: 2024/09/10 17:39:33 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

# include <iostream>
# include <cstdlib>
# include <climits>
# include <deque>
# include <vector>
# include <algorithm>
# include <ctime> 

class PmergeM
{
    public:
        static void process(char **argv) throw(std::invalid_argument, std::runtime_error);

    private:
        PmergeM(void);
        PmergeM(PmergeM const &);
        ~PmergeM(void);

        PmergeM operator=(PmergeM const &);
};


#endif