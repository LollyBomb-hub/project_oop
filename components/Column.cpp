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

Column::Column(std::string _header, std::string _type, std::string _ws)
{

	this->header = _header;
	this->type = _type;
	this->ws = _ws;

}

Column::Column(std::string _header, std::string _type, std::string _ws, std::string _source)
{

	this->header = _header;
	this->type = _type;
	this->ws = _ws;
	this->source = _source;

}

std::string* Column::operator[](size_t idV)
{
	if(idV < this->values.size())
		return new std::string(this->values[idV]);
	return NULL;
}

std::string Column::getHeader() const
{
	return this->header;
}

std::string Column::getType() const
{
	return this->type;
}

std::string Column::getCreatingString() const
{
	std::string creatingString("");
	creatingString += this->header + " ";
	creatingString += this->type;
	return creatingString;
}

void Column::readSource(XLDocument& xlsxFile)
{
	auto wks = xlsxFile.workbook().worksheet(this->ws);

	std::string beginCell;
	std::string endCell;

	size_t pos = 0;

	pos = this->source.find(":");

	beginCell = this->source.substr(0, pos);
	endCell = this->source.substr(pos + 1);

	auto rng = wks.range(XLCellReference(beginCell), XLCellReference(endCell));

	for(auto cell: rng)
	{
		if(this->type == "TEXT")
			this->values.push_back(cell.value());
		if(this->type == "INT")
			this->values.push_back(std::to_string(cell.value().get<int>()));
		if(this->type == "FLOAT")
			this->values.push_back(std::to_string(cell.value().get<float>()));
	}

	return;
}
