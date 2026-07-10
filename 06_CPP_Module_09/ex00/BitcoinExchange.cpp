#include "BitcoinExchange.hpp"
#include <iomanip>

BitcoinExchange::BitcoinExchange() { _loadDatabase("data.csv"); }

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
  *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
  if (this != &other) {
    _database = other._database;
  }
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::_loadDatabase(const std::string &filename) {
  std::ifstream file(filename.c_str());
  if (!file.is_open()) {
    std::cerr << "Error: could not open database file." << std::endl;
    return;
  }

  std::string line;
  // Skip header
  if (std::getline(file, line)) {
    // Optional: check if header is valid "date,exchange_rate"
  }

  while (std::getline(file, line)) {
    if (line.empty())
      continue;
    size_t commaPos = line.find(',');
    if (commaPos != std::string::npos) {
      std::string date = line.substr(0, commaPos);
      std::string rateStr = line.substr(commaPos + 1);
      float rate = static_cast<float>(std::atof(rateStr.c_str()));
      _database[date] = rate;
    }
  }
  file.close();
}

bool BitcoinExchange::_validateDate(const std::string &date) const {
  if (date.length() != 10)
    return false;
  if (date[4] != '-' || date[7] != '-')
    return false;

  int year = std::atoi(date.substr(0, 4).c_str());
  int month = std::atoi(date.substr(5, 2).c_str());
  int day = std::atoi(date.substr(8, 2).c_str());

  if (year < 2009 || year > 2025)
    return false; // Basic range check
  if (month < 1 || month > 12)
    return false;

  int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    daysInMonth[2] = 29;

  if (day < 1 || day > daysInMonth[month])
    return false;
  return true;
}

bool BitcoinExchange::_validateValue(const std::string &valueStr,
                                     float &value) const {
  char *end;
  value = std::strtof(valueStr.c_str(), &end);
  if (*end != '\0' && *end != 'f')
    return false;
  // Basic check, might need stricter parsing if 'f' suffix is not allowed in
  // input but strtof handles it. Subject says: "float or a positive integer
  // between 0 and 1000"

  if (value < 0) {
    std::cerr << "Error: not a positive number." << std::endl;
    return false;
  }
  if (value > 1000) {
    std::cerr << "Error: too large a number." << std::endl;
    return false;
  }
  return true;
}

void BitcoinExchange::processInput(const std::string &filename) {
  std::ifstream file(filename.c_str());
  if (!file.is_open()) {
    std::cerr << "Error: could not open file." << std::endl;
    return;
  }

  std::string line;
  std::getline(file, line); // Skip header usually "date | value"

  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    size_t pipePos = line.find('|');
    if (pipePos == std::string::npos) {
      std::cerr << "Error: bad input => " << line << std::endl;
      continue;
    }

    std::string date = line.substr(0, pipePos);
    // Trim trailing space from date
    if (!date.empty() && date[date.length() - 1] == ' ')
      date.erase(date.length() - 1);

    if (!_validateDate(date)) {
      std::cerr << "Error: bad input => " << date << std::endl;
      continue;
    }

    std::string valueStr = line.substr(pipePos + 1);
    // Trim leading space from value
    if (!valueStr.empty() && valueStr[0] == ' ')
      valueStr.erase(0, 1);

    float value;
    if (!_validateValue(valueStr, value)) {
      // Error message printed in validateValue
      continue;
    }

    // Find exchange rate
    std::map<std::string, float>::const_iterator it =
        _database.lower_bound(date);
    if (it == _database.end() || it->first != date) {
      if (it == _database.begin()) {
        std::cerr << "Error: no data available for this date."
                  << std::endl; // Date before first record
        continue;
      }
      --it;
    }

    std::cout << date << " => " << value << " = " << (value * it->second)
              << std::endl;
  }
  file.close();
}
