#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class PmergeMe {
private:
  std::vector<int> _vec;
  std::deque<int> _deq;

  // Vector helpers
  void _sortVector(std::vector<int> &v);
  void _insertVector(std::vector<int> &main, std::vector<int> &pend);

  // Deque helpers
  void _sortDeque(std::deque<int> &d);
  void _insertDeque(std::deque<int> &main, std::deque<int> &pend);

public:
  PmergeMe();
  PmergeMe(const PmergeMe &other);
  PmergeMe &operator=(const PmergeMe &other);
  ~PmergeMe();

  void run(int argc, char **argv);
};

#endif
