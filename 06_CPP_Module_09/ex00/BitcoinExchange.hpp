#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <map>
# include <cstdlib>

class BitcoinExchange {
	private:
		std::map<std::string, float> _database;

		void	_loadDatabase(const std::string& filename);
		bool	_validateDate(const std::string& date) const;
		bool	_validateValue(const std::string& valueStr, float& value) const;
		
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void	processInput(const std::string& filename);
};

#endif
