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

std::string Table::getCreatingString() const
{
	std::string creatingString("");
	creatingString += "CREATE TABLE " + this->name + "(";

	for(size_t iC = 0; iC < this->columns.size(); iC++)
	{
		creatingString += this->columns[iC].getCreatingString();
		if(iC + 1 < this->columns.size())
		{
			creatingString += ",";
		}
	}

	creatingString += ");";
	return creatingString;
}


std::string Table::getInsertionString() const
{
	std::string buffer("");
	buffer += "INSERT INTO " + this->name + "(";

	for(size_t iC = 0; iC < this->columns.size(); iC++)
	{
		buffer += this->columns[iC].getHeader();
		if(iC + 1 < this->columns.size())
		{
			buffer += ",";
		}
	}

	buffer += ") VALUES (";

	std::string insertionString("");

	bool flag = true;
	size_t idX = 0;

	while(flag)
	{
		std::string current_values("");
		for(size_t iC = 0; iC < this->columns.size(); iC++)
		{
			Column current = this->columns[iC];
			if(current[idX] != NULL)
			{
				if(this->columns[iC].getType() == "TEXT")
					current_values += "'";
				current_values += (*current[idX]);
				if(this->columns[iC].getType() == "TEXT")
					current_values += "'";
				if(iC + 1 < this->columns.size())
				{
					current_values += ",";
				}
			}
			else
			{
				flag = false;
			}
		}
		if(flag)
		{
			idX++;
			insertionString += buffer + current_values;
		}
	}
	return insertionString;
}
