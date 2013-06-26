#pragma once

class StrikerAnimGraph : public StrikerAnimGraphInterface
{
private:
	std::vector<ActorAnimGraph*> AAG;

private:
	ActorAnimGraph* FindAAG(const char* ActorName);

public:
	virtual void AddActor(const char* ActorName);
	virtual void AddNode(const char* ActorName, const char* name, float duration);
	virtual void AddEdge(const char* ActorName, const char* name_source, const char* name_dest);
	virtual std::vector<std::string>* GetPath(const char* ActorName, const char* name_source, const char* name_goal);

	StrikerAnimGraph(void){};
	virtual ~StrikerAnimGraph(void);
};