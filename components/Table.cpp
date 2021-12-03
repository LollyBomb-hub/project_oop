#include "include/Table"

Table::Table() {}

Table::Table(std::string _name)
{
	this->name = _name;
}

void Table::addColumn(Column *_toAdd)
{
	this->columns.push_back(*_toAdd);
}

std::string Table::log() const
{
	std::string log_info("[ INFO ]\n");

	log_info += "TABLE - NAME: ";

	if(this->name.length())
		log_info += this->name;
	else
		log_info += "NOT SET";

	log_info += '\n';

	log_info += "TABLE - COLUMNS: ";

	size_t countOfHeaders = this->columns.size();

	if(countOfHeaders == 0)
	{
		log_info += "NOT SET";
		return log_info;
	}

	log_info += '\n';

	size_t lengthOfHeader = 0;

	std::string head_buffer("+");
	std::string buffer("| ");
	for(size_t iC = 0; iC < countOfHeaders; iC++)
	{
		std::string header = this->columns[iC].getHeader();
		lengthOfHeader = header.length();
		for(size_t iK = 0; iK < lengthOfHeader + 2; iK++)
		{
			head_buffer += "-";
		}
		head_buffer += "+";
		buffer += header + " |";
		if(iC + 1 < countOfHeaders)
			buffer += " ";
	}

	log_info += head_buffer + '\n' + buffer + '\n' + head_buffer + '\n';
	return log_info;
}
