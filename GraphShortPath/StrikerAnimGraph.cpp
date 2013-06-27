#include "stdafx.h"

ActorAnimGraph* StrikerAnimGraph::FindAAG(const char* ActorName)
{
	for (std::vector<ActorAnimGraph*>::size_type i = 0; i < AAG.size(); i++) 
	{
		if (!AAG.at(i)->GetName().compare(ActorName))
		{
			return AAG.at(i);
			break;
		}
	}

	return NULL;
}

void StrikerAnimGraph::AddActor(const char* ActorName)
{
	AAG.push_back(new ActorAnimGraph(ActorName));
}

void StrikerAnimGraph::AddNode(const char* ActorName, const char* name, float duration)
{
	ActorAnimGraph* FindedAAG = FindAAG(ActorName);

	if (FindedAAG)
		FindedAAG->AddNode(name, duration);
}

void StrikerAnimGraph::AddEdge(const char* ActorName, const char* name_source, const char* name_dest)
{
	ActorAnimGraph* FindedAAG = FindAAG(ActorName);

	if (FindedAAG)
		FindedAAG->AddEdge(name_source, name_dest);
}

std::vector<std::string>* StrikerAnimGraph::GetPath(const char* ActorName, const char* name_source, const char* name_goal)
{  
	ActorAnimGraph* FindedAAG = FindAAG(ActorName);

	if (FindedAAG)
		return FindedAAG->GetPath(name_source, name_goal);
	
	return NULL;
}

StrikerAnimGraph::~StrikerAnimGraph(void)
{
	for (std::vector<ActorAnimGraph*>::size_type i = 0; i < AAG.size(); i++) 
	{
		delete AAG.at(i);
	}
}