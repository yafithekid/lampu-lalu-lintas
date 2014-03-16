#pragma once

class Resource
{
public:
	static void LoadResource();

	//resource global
	static sf::Image backgroundimage;
	static sf::Image greenImage;
	static sf::Image greengogreenrightImage;
	static sf::Image greengoredpeopleImage;
	static sf::Image greengoredrightImage;
	static sf::Image redImage;
	static sf::Image redgogreenpeopleImage;
	static sf::Image redgoredpeopleImage;
	static sf::Image redgoredrightImage;
	static sf::Image redyellowImage;
	static sf::Image redyellowgoredpeopleImage;
	static sf::Image redyellowgoredrightImage;
	static sf::Image sebrangImage;
	static sf::Image tambahImage;
	static sf::Image kurangImage;
	static sf::Image sebranghoverImage;
	static sf::Image tambahhoverImage;
	static sf::Image kuranghoverImage;
	static sf::Image carImage;
	static sf::Image humanImage;
	static sf::Image closeImage;
	static sf::Image closehoverImage;

	static sf::Texture backgroundtexture;
	static sf::Texture greenTexture;
	static sf::Texture greengogreenrightTexture;
	static sf::Texture greengoredpeopleTexture;
	static sf::Texture greengoredrightTexture;
	static sf::Texture redTexture;
	static sf::Texture redgogreenpeopleTexture;
	static sf::Texture redgoredpeopleTexture;
	static sf::Texture redgoredrightTexture;
	static sf::Texture redyellowTexture;
	static sf::Texture redyellowgoredpeopleTexture;
	static sf::Texture redyellowgoredrightTexture;
	static sf::Texture sebrangTexture;
	static sf::Texture tambahTexture;
	static sf::Texture kurangTexture;
	static sf::Texture sebranghoverTexture;
	static sf::Texture tambahhoverTexture;
	static sf::Texture kuranghoverTexture;
	static sf::Texture carTexture;
	static sf::Texture humanTexture;
	static sf::Texture closeTexture;
	static sf::Texture closehoverTexture;

	static sf::Sprite background;
	static sf::Sprite greenwest;
	static sf::Sprite greengogreenright;
	static sf::Sprite greengoredpeoplenorth;
	static sf::Sprite greengoredright;
	static sf::Sprite greengoredpeoplesouth;
	static sf::Sprite redwest;
	static sf::Sprite redgogreenpeoplenorth;
	static sf::Sprite redgoredpeoplenorth;
	static sf::Sprite redgoredright;
	static sf::Sprite redgogreenpeoplesouth;
	static sf::Sprite redgoredpeoplesouth;
	static sf::Sprite redyellowwest;
	static sf::Sprite redyellowgoredpeoplenorth;
	static sf::Sprite redyellowgoredright;
	static sf::Sprite redyellowgoredpeoplesouth;
	static sf::Sprite sebrang;
	static sf::Sprite tambahnorth;
	static sf::Sprite kurangnorth;
	static sf::Sprite tambahsouth;
	static sf::Sprite kurangsouth;
	static sf::Sprite tambahwest;
	static sf::Sprite kurangwest;
	static sf::Sprite tambaheast;
	static sf::Sprite kurangeast;
	static sf::Sprite sebranghover;
	static sf::Sprite tambahnorthhover;
	static sf::Sprite kurangnorthhover;
	static sf::Sprite tambahsouthhover;
	static sf::Sprite kurangsouthhover;
	static sf::Sprite tambahwesthover;
	static sf::Sprite kurangwesthover;
	static sf::Sprite tambaheasthover;
	static sf::Sprite kurangeasthover;
	static sf::Sprite carnorth;
	static sf::Sprite carsouth;
	static sf::Sprite carwest;
	static sf::Sprite careast;
	static sf::Sprite humannorth;
	static sf::Sprite humansouth;
	static sf::Sprite close;
	static sf::Sprite closehover;

	static struct CarSprite
	{
		sf::Sprite sprite;
		sf::IntRect rect;
		bool IsMoveInSquare;
		bool IsRotate;
		bool IsMoveToNorth;
	};

	static std::vector<CarSprite> Arraycarnorth;
	static std::vector<CarSprite> Arraycarsouth;
	static std::vector<CarSprite> Arraycarwest;
	static std::vector<CarSprite> Arraycareast;

	//set rect for button
	static sf::IntRect sebrangRect;
	static sf::IntRect closeRect;

	static sf::IntRect tambahnorthRect;
	static sf::IntRect kurangnorthRect;
	static sf::IntRect tambahsouthRect;
	static sf::IntRect kurangsouthRect;
	static sf::IntRect tambahwestRect;
	static sf::IntRect kurangwestRect;
	static sf::IntRect tambaheastRect;
	static sf::IntRect kurangeastRect;

	//font
	static sf::Font SimulationFont;
};