//------------------------------------------------------------------------------
//  Copyright : (c) 2015
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#pragma once

#include "../Pointers/SharedPtr.h"
#include "../Text/RefString.h"

#include <list>
#include <map>
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	XmlWrite
//------------------------------------------------------------------------------
namespace XmlWrite
{
	class Node;
	typedef SharedPtr<Node> NodePtr;

	class Node
	{
	public:
		typedef std::map<RefString, RefString> AttributeMap;
		typedef std::list<NodePtr> NodeList;

		RefString name;
		AttributeMap attributes;
		RefString insideText;
		NodeList subNodes;
	};

	NodePtr newNode();

	bool write(const char* fileName, const Node& root);
} //end namespace XmlWrite
