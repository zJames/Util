//------------------------------------------------------------------------------
//  Copyright : (c) 2022
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#pragma once

#include "Config_Base.h"
#include "../Text/RefString.h"

#include <map>
////////////////////////////////////////////////////////////////////////////////


namespace DomXML
{
class Node;
} //end namespace DomXML


namespace Config
{
//------------------------------------------------------------------------------
//	XML config file
//------------------------------------------------------------------------------
class XML : public Base
{
public:
	typedef std::map<RefString, RefString> StringMap;

	XML();
	XML(RefString file);
	XML(const DomXML::Node& head);

	const char* getRawOption(const char* name) const override;

	bool load(RefString file);
	bool load(const DomXML::Node& head);
	bool save(RefString file) const;
	bool save() const;

	void setOption(RefString name, RefString key);

private:
	RefString mLastFile;
	StringMap mStrings;
};

} //end namespace Config
