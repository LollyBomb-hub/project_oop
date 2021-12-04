#include <iostream>
#include <sstream>
#include <fstream>

#include <pqxx/pqxx>

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include "components/include/DataBase"
#include "components/include/Table"
#include "components/include/Column"


#define getProperty(node, prop) node->first_attribute(prop)->value()


using rapidxml::xml_document;
using rapidxml::xml_node;


int main(int argc, char** argv)
{
	if(argc < 2)
		return 0;

	xml_document<> xml_configuration;
	std::ifstream config_file(argv[1]);
	std::stringstream buffer;

	buffer << config_file.rdbuf();
	std::string config_content(buffer.str());
	xml_configuration.parse<0>(&config_content[0]);

	xml_node<> *rootNode = xml_configuration.first_node();

	DataBase db;

	db.setUsername(getProperty(rootNode, "username"));
	db.setPassword(getProperty(rootNode, "password"));
	db.setAccessPoint(getProperty(rootNode, "accesspoint"));

	for(xml_node<> *tableNode = rootNode->first_node("Table"); tableNode; tableNode = tableNode->next_sibling())
	{
		Table *currentTable = new Table(getProperty(tableNode, "name"));
		// Cycle {1}
		for(xml_node<> *columnNode = tableNode->first_node("Column"); columnNode; columnNode = columnNode->next_sibling())
		{
			Column *currentColumn = new Column(getProperty(columnNode, "name"), getProperty(columnNode, "type"));
			currentTable->addColumn(currentColumn);
		}
		db.addTable(currentTable);
	}

	std::cout << db.log();

	// Ok, we have specs of db
	// Next we must fullfill data in columns
	// It should be done in cycle {1}

	// Here is just connection to db and fullfilling it with given data

	try
	{
		// Open connection to postgresql
		pqxx::connection connection2DB(db.getConnectionString());
		if(connection2DB.is_open())
		{
			std::cout << "Connected to DATABASE successfully\n\0";
		}
		else
		{
			std::cerr << "Can't connect to DATABASE\n\0";
			return 1;
		}

		pqxx::work work(connection2DB);

		for(size_t iT = 0; iT < db.getAllTables().size(); iT++)
		{
			std::string sql_query = db[iT]->getCreatingString();
			std::cout << "Executing SQL query:\n" << sql_query << '\n';
			work.exec(sql_query);
		}

		work.commit();

		connection2DB.close();

		std::cout << "Connection closed!\n\0";
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}
