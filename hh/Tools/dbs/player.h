#pragma once

class MysqlStmt;
struct Stmt
struct StmtExData

class DBPlayer
{
public:
	DBPlayer();
	~DBPlayer();
	void registerMessage();
private:
	void processInsert(PackPtr& pPack);
	void processUpdate(PackPtr& pPack);
	void processDelete(PackPtr& pPack);
	void processRequest(PackPtr& pPack);
	void cbRequest(StmtExData* result, ConnectPtr& conn);
};
