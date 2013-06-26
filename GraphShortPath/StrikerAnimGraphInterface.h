#ifndef _STRIKER_ANIM_GRAPH_INTERFACE_
#define _STRIKER_ANIM_GRAPH_INTERFACE_

class StrikerAnimGraphInterface
{
public:
	virtual void AddActor(const char* ActorName) = 0; 

	virtual void AddNode(const char* ActorName, const char* name, float duration) = 0; 
	virtual void AddEdge(const char* ActorName, const char* name_source, const char* name_dest) = 0; 

	virtual std::vector<std::string>* GetPath(const char* ActorName, const char* name_source, const char* name_goal) = 0; 

public:
	StrikerAnimGraphInterface(void){};
	virtual ~StrikerAnimGraphInterface(void){};
};

extern StrikerAnimGraphInterface* _stdcall CreateStrikerAnimGraph(void);
extern void _stdcall DeleteStrikerAnimGraph(StrikerAnimGraphInterface* SAG);

#endif