//===----------------------------------------------------------------------===//
//                         DuckDB
//
// storage/mysql_schema_set.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "storage/mysql_catalog_set.hpp"
#include "storage/mysql_schema_entry.hpp"

namespace duckdb {
struct CreateSchemaInfo;

class MySQLSchemaSet : public MySQLCatalogSet {
public:
	MySQLSchemaSet(Catalog &catalog, string default_schema);

	void SetDefaultSchema(string new_default_schema);

	void SetDatabases(vector<string> databases);

public:
	optional_ptr<CatalogEntry> CreateSchema(ClientContext &context, CreateSchemaInfo &info);

protected:
	void LoadEntries(ClientContext &context) override;

private:
	string default_schema;
	vector<string> databases;
	vector<string> GetDatabasesToScan();
};

} // namespace duckdb
