/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:57:45 by emimenza          #+#    #+#             */
/*   Updated: 2024/09/10 17:32:20 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/PmergeMe.hpp"

PmergeM::PmergeM(void) { return; }

PmergeM::PmergeM(PmergeM const &) { return; }

PmergeM::~PmergeM(void) { return; }

PmergeM PmergeM::operator=(PmergeM const &) { return (*this); }

bool isValid(char * str)
{
    if (str == NULL || *str == '\0')
        return false;

    char* endptr;
    long value = strtol(str, &endptr, 10);

    return (*endptr == '\0' && value >= 0 && value <= INT_MAX);
}

// void sortPairs(std::deque<int> *nbrDeque)
// {
//     for (std::deque<int>::iterator it = (*nbrDeque).begin(); it != (*nbrDeque).end(); )
//     {
//         std::deque<int>::iterator nextIt = it;
//         ++nextIt;
//         if (nextIt != (*nbrDeque).end())
//         {
//             if (*it > *nextIt)
//             {
//                 std::swap(*it, *nextIt);
//             }
//             it = nextIt;
//         }
//         ++it;
//     }
// }

void insertionSort(std::deque<int> &sublist)
{

    std::deque<int>::iterator it = sublist.begin();
    if (it != sublist.end())
    {
        std::deque<int>::iterator nextIt = it;
        ++nextIt;
        if (*it > *nextIt)
        {
            std::swap(*it, *nextIt);
        }
        it = nextIt;
    }
}

std::deque<int> merge(const std::deque<int> &left, const std::deque<int> &right)
{
    std::deque<int> result;
    std::deque<int>::const_iterator leftIt = left.begin();
    std::deque<int>::const_iterator rightIt = right.begin();

    while (leftIt != left.end() && rightIt != right.end())
    {
        if (*leftIt <= *rightIt)
        {
            result.push_back(*leftIt);
            ++leftIt;
        }
        else
        {
            result.push_back(*rightIt);
            ++rightIt;
        }
    }

    result.insert(result.end(), leftIt, left.end());
    result.insert(result.end(), rightIt, right.end());

    return result;
}

void mergeInsertSort(std::deque<int> &deque)
{
    // Print
    //std::cout << "Start content:" << std::endl;
    // std::deque<int>::iterator it;
    // for (it = deque.begin(); it != deque.end(); ++it)
    // {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;
    // std::cout << std::endl;
    
    if (deque.size() == 1){}
    else if(deque.size() == 2)
    {
        insertionSort(deque);
    }
    else
    {
        std::deque<int> left(deque.begin(), deque.begin() + 2);

        // std::cout << "left content:" << std::endl;
        // for (it = left.begin(); it != left.end(); ++it)
        // {
        //     std::cout << *it << " ";
        // }
        // std::cout << std::endl;

        std::deque<int> right(deque.begin() + 2, deque.end());
        // std::cout << "right content:" << std::endl;
        // for (it = right.begin(); it != right.end(); ++it)
        // {
        //     std::cout << *it << " ";
        // }
        // std::cout << std::endl;
        // std::cout << std::endl;

        mergeInsertSort(left);
        mergeInsertSort(right);

        deque = merge(left, right);
    }

    // std::cout << "End content:" << std::endl;
    // for (it = deque.begin(); it != deque.end(); ++it)
    // {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;
    // std::cout << std::endl;
}

void PmergeM::process(char **argv) throw(std::invalid_argument, std::runtime_error)
{
    std::deque<int> nbrDeque;

    while (*argv)
    {
        if (isValid((*argv)) == false)
                throw std::invalid_argument("Invalid arguments");
        
        long value = strtol(*argv, NULL, 10);
        nbrDeque.push_back(static_cast<int>(value));

        argv++;
    }

    //sortPairs(&nbrDeque);
    
    mergeInsertSort(nbrDeque);
    //Print
    for (std::deque<int>::iterator it = nbrDeque.begin(); it != nbrDeque.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    
}