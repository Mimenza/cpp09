/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:57:45 by emimenza          #+#    #+#             */
/*   Updated: 2024/09/10 18:05:39 by emimenza         ###   ########.fr       */
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

    // std::cout << "merge left content:" << std::endl;
    // std::deque<int>::const_iterator it;
    // for (it = left.begin(); it != left.end(); ++it)
    // {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;
    // std::cout << "merge right content:" << std::endl;
    // for (it = right.begin(); it != right.end(); ++it)
    // {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;
    // std::cout << std::endl;
    
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

    // std::cout << "after mergin" << std::endl;
    // for (it = result.begin(); it != result.end(); ++it)
    // {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;
    // std::cout << std::endl;
    
    return result;
}

void mergeInsertSort(std::deque<int> &deque)
{
    // Print
    //std::cout << "Start content:" << std::endl;
    std::deque<int>::iterator it;
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
        //sort 2 elements
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
    
	clock_t start = clock();
    while (*argv)
    {
        if (isValid((*argv)) == false)
                throw std::invalid_argument("Invalid arguments");
        
        long value = strtol(*argv, NULL, 10);
        nbrDeque.push_back(static_cast<int>(value));

        argv++;
    }

    
    std::cout << "Before ";
    for (std::deque<int>::iterator it = nbrDeque.begin(); it != nbrDeque.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    mergeInsertSort(nbrDeque);

    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "After  ";
    for (std::deque<int>::iterator it = nbrDeque.begin(); it != nbrDeque.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of " << nbrDeque.size()  << " elements with std::deque<int> :"  << elapsed * 10 << " us" << std::endl;
}