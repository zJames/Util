//------------------------------------------------------------------------------
//  Copyright : (c) 2023
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Config_XML.h"

#include "..\domXML\domXML.h"
#include "..\XmlWrite\XmlWrite.h"
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
//	Local Const Data
//------------------------------------------------------------------------------
const RefString kConfigHeader = "config";


namespace Config
{
//------------------------------------------------------------------------------
// XML config file
//------------------------------------------------------------------------------
XML::XML()
{
}

XML::XML(RefString file)
{
	load(file);
}

XML::XML(const DomXML::Node& head)
{
	load(head);
}

const char* XML::getRawOption(const char* name) const
{
	RefString refName(name);
	StringMap::const_iterator obj = mStrings.find(refName);

	if (obj == mStrings.end())
	{
		return nullptr;
	}

	return obj->second;
}

bool XML::load(RefString file)
{
	mLastFile = file;

	auto head = DomXML::getFirstNode(file);

	return load(head.getNode(kConfigHeader));
}

bool XML::load(const DomXML::Node& head)
{
	if (!head.isValid() || head.name() != kConfigHeader)
	{
		return false;
	}

	for (auto& option : head.nodes())
	{
		mStrings[option.name()] = option.insideText().copy();
	}

	return true;
}

bool XML::save(RefString file) const
{
	XmlWrite::Node root;

	root.name = kConfigHeader;

	for (auto& option : mStrings)
	{
		XmlWrite::NodePtr toAdd(new XmlWrite::Node);

		if (option.second.empty())
		{
			continue;
		}

		toAdd->name = option.first;
		toAdd->insideText = option.second;

		root.subNodes.push_back(toAdd);
	}

	return XmlWrite::write(file, root);
}

bool XML::save() const
{
	if (mLastFile.empty())
	{
		return false;
	}

	return save(mLastFile);
}

void XML::setOption(RefString name, RefString key)
{
	mStrings[name] = key;
}

} //end namespace Config