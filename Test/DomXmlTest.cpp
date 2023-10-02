//------------------------------------------------------------------------------
//  Copyright : (c) 2015
//  Authors :
//	  JRP	James Prettyman
//------------------------------------------------------------------------------

#include "Test.h"

#include "../Util/Util_AllHeaders.h"

using namespace DomXML;
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
//	Local Data
//------------------------------------------------------------------------------
const char kTestXml[] =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\
<scene version=\"1\" size=\"1024,768\" color=\"{0, 0, 0, 255}\">\
<objects>\
	<image file=\"a.png\" />\
	<image file=\"b.png\" />\
	<image file=\"c.png\" />\
	<image file=\"d.png\" />\
</objects>\
<scene_objects>\
	<node name=\"emptyNode\" />\
	<sprite name=\"spriteA\" object=\"a.png\" />\
	<sprite name=\"spriteB\" object=\"b.png\" angle=\"30\" position=\"{40, 40}\">\
		<sprite name=\"spriteC\" object=\"c.png\" angle=\"30\" position=\"{40,40}\" color=\"{255,0,0}\">\
			<sprite name=\"spriteD\" object=\"d.png\" color=\"{0,255,0,128}\" />\
		</sprite>\
	</sprite>\
</scene_objects>\
<text_objects>\
	<text>Some Text</text>\
	<text>More Stuff</text>\
</text_objects>\
</scene>";


#define THROW_ON_FAIL(n) { if (!(n)) throw "Was false: " #n; }


//------------------------------------------------------------------------------
//	Local Functions
//------------------------------------------------------------------------------
void testSpriteB(const Node& spriteB)
{
	THROW_ON_FAIL(spriteB.size() == 1);
	
	const Node& spriteC = spriteB[0];

	THROW_ON_FAIL(spriteC.name() == "sprite");
	THROW_ON_FAIL(spriteC.attribute("name") == "spriteC");
	THROW_ON_FAIL(spriteC.size() == 1);

	const Node& spriteD = spriteC[0];

	THROW_ON_FAIL(spriteD.name() == "sprite");
	THROW_ON_FAIL(spriteD.attribute("name") == "spriteD");
	THROW_ON_FAIL(spriteD.size() == 0);
}

//------------------------------------------------------------------------------
//	DomXmlTest
//------------------------------------------------------------------------------
void testDomXml()
{
	{
		Node emptyTest;

		printf("Test for empty node: %s\n", !emptyTest.isValid() ? "passed" : "failed");
	}

	SharedArray<const char> xmlText(new char[ARRAY_LENGTH(kTestXml)]);

	memcpy(const_cast<char*>(xmlText.get()), kTestXml, ARRAY_LENGTH(kTestXml));

	const Node& scene = getFirstNode(xmlText);

	THROW_ON_FAIL(scene.name() == "scene");
	THROW_ON_FAIL(scene.size() == 3);
	
	//Testing attributes
	{
		const char* kTestObjects[] = {"a.png", "b.png", "c.png", "d.png"};
		const Node& objects = scene.getNode("objects");

		THROW_ON_FAIL(objects.size() == ARRAY_LENGTH(kTestObjects));

		for (size_t i = 0; i < ARRAY_LENGTH(kTestObjects); ++i)
		{
			const Node& node = objects[i];
			THROW_ON_FAIL(node.name() == "image");
			THROW_ON_FAIL(node.attribute("file") == kTestObjects[i]);
		}
	}

	//Testing nested objects
	{
		const Node& sceneObjects = scene.getNode("scene_objects");
		const char* kTestObjects[] = {"node", "sprite", "sprite"};
		const char* kTestObjectNames[] = {"emptyNode", "spriteA", "spriteB"};

		THROW_ON_FAIL(sceneObjects.size() == ARRAY_LENGTH(kTestObjects));

		for (size_t i = 0; i < ARRAY_LENGTH(kTestObjects); ++i)
		{
			const Node& node = sceneObjects[i];
			
			THROW_ON_FAIL(node.name() == kTestObjects[i]);
			THROW_ON_FAIL(node.attribute("name") == kTestObjectNames[i]);
		}

		testSpriteB(sceneObjects[2]);
	}

	//Testing inside text
	{
		Node scene2 = getFirstNode(xmlText);

		const Node& textObjects = scene2.getNode("text_objects");

		RefString text1 = textObjects.getNode(0).insideText();
		RefString text2 = textObjects.getNode(1).insideText();

		scene2 = Node();

		THROW_ON_FAIL(text1 == "Some Text");
		THROW_ON_FAIL(text2 == "More Stuff");
	}

	//Testing bug case: attribute corrupts after node release
	{
		RefString attrib;

		{
			SharedArray<const char> xmlText2(new char[ARRAY_LENGTH(kTestXml)]);
			
			memcpy(const_cast<char*>(xmlText2.get()), kTestXml, ARRAY_LENGTH(kTestXml));
			
			const Node& scene2 = getFirstNode(xmlText2);
			
			attrib = scene2.getNode("objects").getNode(1).attribute("file");
		}

		THROW_ON_FAIL(attrib == "b.png");
	}
}