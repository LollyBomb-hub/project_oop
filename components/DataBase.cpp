#include "include/DataBase"


#define checkNoNull(value, toAdd) if(this->value.length()) \
				  { \
					toAdd += this->value; \
				  } \
				  else \
				  { \
					toAdd += "Not set"; \
				  } \
				  toAdd += '\n';


bool DataBase::setUsername(std::string _username)
{
	bool flag = false;
	if(this->username.length())
	{
		flag = true;
	}
	this->username = _username;
	return flag;
}


bool DataBase::setPassword(std::string _password)
{
	bool flag = false;
	if(this->password.length())
	{
		flag = true;
	}
	this->password = _password;
	return flag;
}


bool DataBase::setAccessPoint(std::string _access_point)
{
	bool flag = false;
	if(this->access_point.length())
	{
		flag = true;
	}
	this->access_point = _access_point;
	return flag;
}


Table* DataBase::operator[](size_t idT)
{
	if(idT < this->tables.size())
		return &this->tables[idT];
	else
		return NULL;
}


std::vector<Table> DataBase::getAllTables() const
{
	return this->tables;
}


std::string DataBase::getUsername() const
{
	return this->username;
}

std::string DataBase::getPassword() const
{
	return this->password;
}

std::string DataBase::getAccessPoint() const
{
	return this->access_point;
}

void DataBase::addTable(Table* _table)
{
	this->tables.push_back(*_table);
}

std::string DataBase::log() const
{
	std::string log_info("[ INFO ]\n");

	log_info += "DATABASE - USERNAME: ";
	checkNoNull(username, log_info)

	log_info += "DATABASE - PASSWORD: ";
	checkNoNull(password, log_info)

	log_info += "DATABASE - ACCESS POINT: ";
	checkNoNull(access_point, log_info)

	for(size_t iT = 0; iT < this->tables.size(); iT++)
	{
		log_info += this->tables[iT].log();
	}
	return log_info;
}

std::string DataBase::getConnectionString() const
{
	std::string connectionString("postgresql://");
	connectionString += this->username;
	if(this->password.length() > 0)
		connectionString += ":" + this->password;
	connectionString += "@" + this->access_point;
	return connectionString;
}
