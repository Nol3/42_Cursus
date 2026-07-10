#include "PmergeMe.hpp"

// Utility to generate Jacobsthal numbers up to a limit
// J(n) = J(n-1) + 2*J(n-2)
static std::vector<size_t> generateJacobsthal(size_t n) {
  std::vector<size_t> jacob;
  jacob.push_back(0);
  jacob.push_back(1);
  size_t last = 1;
  size_t prev = 0;
  while (last < n) {
    size_t next = last + 2 * prev;
    jacob.push_back(next);
    prev = last;
    last = next;
  }
  return jacob;
}

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) { *this = other; }

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
  if (this != &other) {
    _vec = other._vec;
    _deq = other._deq;
  }
  return *this;
}

PmergeMe::~PmergeMe() {}

// ---------------- VECTOR IMPLEMENTATION ----------------

void PmergeMe::_sortVector(std::vector<int> &v) {
  if (v.size() <= 1)
    return;

  // FIX: Use typedef to avoid >> operator issues in C++98
  typedef std::pair<int, int> IntPair;
  std::vector<IntPair> pairs;

  int straggler = -1;
  bool hasStraggler = false;

  if (v.size() % 2 != 0) {
    straggler = v.back();
    hasStraggler = true;
    v.pop_back();
  }

  for (size_t i = 0; i < v.size(); i += 2) {
    if (v[i] > v[i + 1])
      pairs.push_back(std::make_pair(v[i], v[i + 1])); // larger, smaller
    else
      pairs.push_back(std::make_pair(v[i + 1], v[i]));
  }

  std::vector<int> mainChain;
  for (size_t i = 0; i < pairs.size(); ++i) {
    mainChain.push_back(pairs[i].first); // Push larger
  }

  _sortVector(mainChain);

  std::vector<int> pend;
  std::vector<int> mainWithPend = mainChain; // Will insert into this

  pend.resize(mainChain.size());
  for (size_t i = 0; i < mainChain.size(); ++i) {
    int largeVal = mainChain[i];
    for (size_t p = 0; p < pairs.size(); ++p) {
      if (pairs[p].first == largeVal) {
        pend[i] = pairs[p].second;
        break;
      }
    }
  }

  mainWithPend.insert(mainWithPend.begin(), pend[0]);

  std::vector<size_t> jacob = generateJacobsthal(pend.size());

  size_t insertedCount = 1;

  for (size_t k = 2; k < jacob.size(); ++k) {
    size_t right = jacob[k] - 1;
    size_t left = jacob[k - 1];

    if (right >= pend.size())
      right = pend.size() - 1;

    for (size_t i = right; i >= left; --i) {
      int val = pend[i];

      std::vector<int>::iterator boundIt = std::lower_bound(
          mainWithPend.begin(), mainWithPend.end(), mainChain[i]);

      std::vector<int>::iterator pos =
          std::lower_bound(mainWithPend.begin(), boundIt, val);
      mainWithPend.insert(pos, val);
      insertedCount++;
    }
    if (right == pend.size() - 1)
      break;
  }

  if (hasStraggler) {
    std::vector<int>::iterator pos =
        std::lower_bound(mainWithPend.begin(), mainWithPend.end(), straggler);
    mainWithPend.insert(pos, straggler);
  }
  v = mainWithPend;
}

// ---------------- DEQUE IMPLEMENTATION ----------------

void PmergeMe::_sortDeque(std::deque<int> &d) {
  if (d.size() <= 1)
    return;

  // FIX: Use typedef to avoid >> operator issues in C++98
  typedef std::pair<int, int> IntPair;
  std::deque<IntPair> pairs;

  int straggler = -1;
  bool hasStraggler = false;

  if (d.size() % 2 != 0) {
    straggler = d.back();
    hasStraggler = true;
    d.pop_back();
  }

  for (size_t i = 0; i < d.size(); i += 2) {
    if (d[i] > d[i + 1])
      pairs.push_back(std::make_pair(d[i], d[i + 1]));
    else
      pairs.push_back(std::make_pair(d[i + 1], d[i]));
  }

  std::deque<int> mainChain;
  for (size_t i = 0; i < pairs.size(); ++i) {
    mainChain.push_back(pairs[i].first); // Push larger
  }

  _sortDeque(mainChain);

  std::deque<int> pend;
  std::deque<int> mainWithPend = mainChain;

  pend.resize(mainChain.size());
  for (size_t i = 0; i < mainChain.size(); ++i) {
    int largeVal = mainChain[i];
    for (size_t p = 0; p < pairs.size(); ++p) {
      if (pairs[p].first == largeVal) {
        pend[i] = pairs[p].second;
        break;
      }
    }
  }

  mainWithPend.insert(mainWithPend.begin(), pend[0]);

  std::vector<size_t> jacob = generateJacobsthal(pend.size());

  size_t insertedCount = 1;

  for (size_t k = 2; k < jacob.size(); ++k) {
    size_t right = jacob[k] - 1;
    size_t left = jacob[k - 1];

    if (right >= pend.size())
      right = pend.size() - 1;

    for (size_t i = right; i >= left; --i) {
      int val = pend[i];
      std::deque<int>::iterator boundIt = std::lower_bound(
          mainWithPend.begin(), mainWithPend.end(), mainChain[i]);
      std::deque<int>::iterator pos =
          std::lower_bound(mainWithPend.begin(), boundIt, val);
      mainWithPend.insert(pos, val);
      insertedCount++;
    }
    if (right == pend.size() - 1)
      break;
  }

  if (hasStraggler) {
    std::deque<int>::iterator pos =
        std::lower_bound(mainWithPend.begin(), mainWithPend.end(), straggler);
    mainWithPend.insert(pos, straggler);
  }
  d = mainWithPend;
}

void PmergeMe::run(int argc, char **argv) {
  for (int i = 1; i < argc; ++i) {
    std::string s = argv[i];
    for (size_t j = 0; j < s.length(); ++j) {
      if (!isdigit(s[j])) {
        throw std::runtime_error("Error");
      }
    }
    long val = std::atol(s.c_str());
    if (val > INT_MAX || val < 0)
      throw std::runtime_error("Error");

    for (size_t k = 0; k < _vec.size(); ++k) {
      if (_vec[k] == (int)val)
        throw std::runtime_error("Error");
    }
    _vec.push_back((int)val);
    _deq.push_back((int)val);
  }

  std::cout << "Before: ";
  for (size_t i = 0; i < _vec.size(); ++i) {
    std::cout << _vec[i] << (i == _vec.size() - 1 ? "" : " ");
    if (i > 4 && _vec.size() > 5) {
      std::cout << "[...]";
      break;
    }
  }
  std::cout << std::endl;

  clock_t startVec = clock();
  _sortVector(_vec);
  clock_t endVec = clock();
  double timeVec =
      static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000;

  clock_t startDeq = clock();
  _sortDeque(_deq);
  clock_t endDeq = clock();
  double timeDeq =
      static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000;

  std::cout << "After:  ";
  for (size_t i = 0; i < _vec.size(); ++i) {
    std::cout << _vec[i] << (i == _vec.size() - 1 ? "" : " ");
    if (i > 4 && _vec.size() > 5) {
      std::cout << "[...]";
      break;
    }
  }
  std::cout << std::endl;

  std::cout << "Time to process a range of " << _vec.size()
            << " elements with std::vector : " << timeVec << " us" << std::endl;
  std::cout << "Time to process a range of " << _deq.size()
            << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}
