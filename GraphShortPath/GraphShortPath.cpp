// GraphShortPath.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::auto_ptr<StrikerAnimGraph> SAG(new StrikerAnimGraph());
	SAG.get()->AddActor("ACTOR1");
	SAG.get()->AddActor("ACTOR2");

	SAG.get()->AddNode("ACTOR1", "NODE1", 3.0f);
	SAG.get()->AddNode("ACTOR1", "NODE2", 2.0f);
	SAG.get()->AddNode("ACTOR1", "NODE3", 1.0f);
	SAG.get()->AddNode("ACTOR1", "NODE4", 1.0f);

	SAG.get()->AddEdge("ACTOR1", "NODE1", "NODE2");
	SAG.get()->AddEdge("ACTOR1", "NODE2", "NODE3");
	SAG.get()->AddEdge("ACTOR1", "NODE3", "NODE1");
	SAG.get()->AddEdge("ACTOR1", "NODE3", "NODE4");
	
	SAG.get()->AddNode("ACTOR2", "NODE1", 3.0f);
	SAG.get()->AddNode("ACTOR2", "NODE2", 2.0f);
	SAG.get()->AddNode("ACTOR2", "NODE3", 1.0f);
	SAG.get()->AddNode("ACTOR2", "NODE4", 1.0f);

	SAG.get()->AddEdge("ACTOR2", "NODE1", "NODE3");
	SAG.get()->AddEdge("ACTOR2", "NODE1", "NODE4");
	SAG.get()->AddEdge("ACTOR2", "NODE3", "NODE2");
	
	std::auto_ptr<std::vector<std::string>> path1(SAG.get()->GetPath("ACTOR1", "NODE3", "NODE1"));
	std::auto_ptr<std::vector<std::string>> path2(SAG.get()->GetPath("ACTOR1", "NODE2", "NODE3"));
	std::auto_ptr<std::vector<std::string>> path3(SAG.get()->GetPath("ACTOR1", "NODE1", "NODE4"));

	std::auto_ptr<std::vector<std::string>> path4(SAG.get()->GetPath("ACTOR2", "NODE1", "NODE2"));

	_getch();
	//delete SAG;
	return 0;
}

