#include "API.h"

void API::init(CatalogManager *c, FakeRecordManager *r, IndexManager *ind,
               FileLogger *l) {
    catalogManager = c;
    recordManager = r;
    indexManager = ind;
    logger = l;
}

Records API::selectRecords(string tableName, vector<string> columns,
                           vector<Condition> conditions) {
    logger->log("API starting select record.");

    if (!catalogManager->isTableExist(tableName))
        throw SELECTING_TABLE_NOT_EXIST;

    Index *i = NULL;
    string valueForIndex = "";

    for (auto c : conditions) {
        i = this->catalogManager->getIndex(tableName, c.attributeName);
        if (i != NULL) {
            valueForIndex = c.value;
            logger->log("found index " + i->indexName + " can use!");
            break;
        }
    }

    int offset = 0;
    if (i != NULL) {
        offset = indexManager->search(i->indexName, valueForIndex);
        logger->log("the record is at block " + to_string(offset));
    }

    Records records = this->recordManager->selectRecord(tableName, conditions);

    if (columns.size() == 1 && columns[0] == "*") {
        return records;
    }

    Table t = this->catalogManager->getTable(tableName);

    vector<int> fieldIndex;

    for (auto col : columns) {
        int i = 0;
        bool found = false;
        for (auto attr : t.attributes) {
            if (attr.name == col) {
                fieldIndex.push_back(i);
                found = true;
                break;
            }
            i++;
        }
        if (!found) {
            logger->log("attribute " + col + " not in the table " + tableName);
            throw 1;
        }
    }

    Records recordsOnlySelectedCols;

    for (auto record : records) {
        vector<string> n;
        for (auto i : fieldIndex) {
            n.push_back(record[i]);
        }
        recordsOnlySelectedCols.push_back(n);
    }

    logger->log("API select record done, preparing response ...");

    return recordsOnlySelectedCols;
}

void API::createTable(string tableName, vector<Attribute> attrs) {
    logger->log("API creating table ...");
    Table t(tableName, attrs);
    catalogManager->createTable(t);

    // TODO: Call IndexManager to create Primary Key index

    recordManager->createTable(tableName);
}

void API::insertRecord(string tableName, vector<string> values) {
    logger->log("API starting insert record.");

    if (!catalogManager->isTableExist(tableName))
        throw INSERTING_TABLE_NOT_EXIST;

    logger->log("insert record request validated.");

    this->recordManager->insertRecord(tableName, values);
}

void API::createIndex(string indexName, string tableName,
                      vector<string> fields) {
    logger->log("API starting create index.");

    if (!catalogManager->isTableExist(tableName))
        throw CREATED_INDEX_TABLE_NOT_EXIST;

    if (catalogManager->isIndexExist(tableName)) throw INDEX_ALREADY_EXIST;

    logger->log("API validated create index request.");

    for (auto f : fields) {
        DataType dt;

        try {
            dt = catalogManager->getDataTypeOfAttribute(tableName, f);
        } catch (CatalogManager::CatalogManagerError error) {
            throw CREATED_INDEX_FIELD_NOT_EXIST;
        }

        Index *i = new Index();

        i->indexName = indexName;
        i->tableName = tableName;
        i->attributeName = f;
        i->dataType = dt;

        catalogManager->createIndex(*i);

        Table t = catalogManager->getTable(tableName);

        vector<string> attr;
        attr.push_back(f);

        auto attrIndex = recordManager->getAttrIndex(t.attributes, attr);

        indexManager->CreateOne(*i, attrIndex.at(0));
    }

    logger->log("API create index finished.");
}

int API::updateRecord(string tableName, vector<string> fields,
                      vector<string> values, vector<Condition> conditions) {
    if (!catalogManager->isTableExist(tableName))
        throw DELETING_TABLE_NOT_EXIST;

    return this->recordManager->updateRecord(tableName, fields, values,
                                             conditions);
}

int API::deleteRecord(string tableName, vector<Condition> conditions) {
    if (!catalogManager->isTableExist(tableName))
        throw DELETING_TABLE_NOT_EXIST;
    return this->recordManager->deleteRecord(tableName, conditions);
}

void API::dropIndex(string indexName) {
    if (!catalogManager->isIndexExist(indexName)) throw DROPING_INDEX_NOT_EXIST;

    catalogManager->dropIndex(indexName);

    this->indexManager->dropIndex(indexName);
}

void API::dropTable(string tableName) {
    logger->log("API starting drop table");

    if (!catalogManager->isTableExist(tableName)) throw DROPING_TABLE_NOT_EXIST;

    catalogManager->dropTable(tableName);

    recordManager->dropTable(tableName);

    logger->log("API drop table finished");
}
