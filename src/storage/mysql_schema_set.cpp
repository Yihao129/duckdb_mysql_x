#include "storage/mysql_schema_set.hpp"
#include "storage/mysql_catalog.hpp"
#include "storage/mysql_transaction.hpp"
#include "duckdb/parser/parsed_data/create_schema_info.hpp"

namespace duckdb {

static bool MySQLSchemaIsInternal(const string &name) {
	if (name == "information_schema" || name == "performance_schema" || name == "sys") {
		return true;
	}
	return false;
}

MySQLSchemaSet::MySQLSchemaSet(Catalog &catalog, string default_schema_p)
    : MySQLCatalogSet(catalog), default_schema(std::move(default_schema_p)) {
}

void MySQLSchemaSet::SetDefaultSchema(string new_default_schema) {
	default_schema = std::move(new_default_schema);
}

void MySQLSchemaSet::SetDatabases(vector<string> new_databases) {
	databases = std::move(new_databases);
}

vector<string> MySQLSchemaSet::GetDatabasesToScan() {
	// Return specified databases if set, otherwise fallback to default_schema, otherwise scan all.
	if (!databases.empty()) {
		return databases;
	}
	if (!default_schema.empty()) {
		return {default_schema};
	}
	return {};
}

void MySQLSchemaSet::LoadEntries(ClientContext &context) {
	auto databases_to_scan = GetDatabasesToScan();
	if (databases_to_scan.empty()) {
		auto query = R"(
SELECT schema_name
FROM information_schema.schemata;
)";
		auto &transaction = MySQLTransaction::Get(context, catalog);
		auto result = transaction.Query(query);
		while (result->Next()) {
			CreateSchemaInfo info;
			info.schema = result->GetString(0);
			info.internal = MySQLSchemaIsInternal(info.schema);
			auto schema = make_uniq<MySQLSchemaEntry>(catalog, info);
			CreateEntry(std::move(schema));
		}
	} else {
		// Filter schemas to only include the specified databases.
		unordered_set<string> database_set(databases_to_scan.begin(), databases_to_scan.end());
		auto query = R"(
SELECT schema_name
FROM information_schema.schemata;
)";
		auto &transaction = MySQLTransaction::Get(context, catalog);
		auto result = transaction.Query(query);
		while (result->Next()) {
			auto schema_name = result->GetString(0);
			if (database_set.find(schema_name) != database_set.end()) {
				CreateSchemaInfo info;
				info.schema = schema_name;
				info.internal = MySQLSchemaIsInternal(info.schema);
				auto schema = make_uniq<MySQLSchemaEntry>(catalog, info);
				CreateEntry(std::move(schema));
			}
		}
	}
}

optional_ptr<CatalogEntry> MySQLSchemaSet::CreateSchema(ClientContext &context, CreateSchemaInfo &info) {
	auto &transaction = MySQLTransaction::Get(context, catalog);

	string create_sql = "CREATE SCHEMA " + MySQLUtils::WriteIdentifier(info.schema);
	transaction.Query(create_sql);
	auto schema_entry = make_uniq<MySQLSchemaEntry>(catalog, info);
	return CreateEntry(std::move(schema_entry));
}

} // namespace duckdb
