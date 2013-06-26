// GraphShortPath.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	StrikerAnimGraph* SAG = new StrikerAnimGraph();
	SAG->AddActor("ACTOR1");
	SAG->AddActor("ACTOR2");

	SAG->AddNode("ACTOR1", "NODE1", 3.0f);
	SAG->AddNode("ACTOR1", "NODE2", 2.0f);
	SAG->AddNode("ACTOR1", "NODE3", 1.0f);
	SAG->AddNode("ACTOR1", "NODE4", 1.0f);

	SAG->AddEdge("ACTOR1", "NODE1", "NODE2");
	SAG->AddEdge("ACTOR1", "NODE2", "NODE3");
	SAG->AddEdge("ACTOR1", "NODE3", "NODE1");
	SAG->AddEdge("ACTOR1", "NODE3", "NODE4");
	
	SAG->AddNode("ACTOR2", "NODE1", 3.0f);
	SAG->AddNode("ACTOR2", "NODE2", 2.0f);
	SAG->AddNode("ACTOR2", "NODE3", 1.0f);
	SAG->AddNode("ACTOR2", "NODE4", 1.0f);

	SAG->AddEdge("ACTOR2", "NODE1", "NODE3");
	SAG->AddEdge("ACTOR2", "NODE1", "NODE4");
	SAG->AddEdge("ACTOR2", "NODE3", "NODE2");
	
	std::vector<std::string>* path1 = SAG->GetPath("ACTOR1", "NODE3", "NODE1");
	std::vector<std::string>* path2 = SAG->GetPath("ACTOR1", "NODE2", "NODE3");
	std::vector<std::string>* path3 = SAG->GetPath("ACTOR1", "NODE1", "NODE4");

	std::vector<std::string>* path4 = SAG->GetPath("ACTOR2", "NODE1", "NODE2");

	std::auto_ptr<std::vector<std::string>> sp(SAG->GetPath("ACTOR2", "NODE1", "NODE2"));
	_getch();
	delete SAG;
	return 0;
}

