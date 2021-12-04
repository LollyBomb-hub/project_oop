#include "include/Column"


Column::Column(std::string _header)
{

	this->header = _header;

}

Column::Column(std::string _header, std::string _type)
{

	this->header = _header;
	this->type = _type;

}

Column::Column(std::string _header, std::string _type, std::string _source)
{

	this->header = _header;
	this->type = _type;
	this->source = _source;

}

Column::Column(std::string _header, std::string _type, std::vector<std::string> _values)
{

	this->header = _header;
	this->type = _type;
	this->values = _values;

}

std::string Column::getHeader() const
{
	return this->header;
}

std::string Column::getCreatingString() const
{
	std::string creatingString("");
	creatingString += this->header + " ";
	creatingString += this->type;
	return creatingString;
}
