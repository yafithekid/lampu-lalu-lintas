#include "stdafx.h"
#include "Resource.h"

sf::Image Resource::backgroundimage;
sf::Image Resource::greenImage;
sf::Image Resource::greengogreenrightImage;
sf::Image Resource::greengoredpeopleImage;
sf::Image Resource::greengoredrightImage;
sf::Image Resource::redImage;
sf::Image Resource::redgogreenpeopleImage;
sf::Image Resource::redgoredpeopleImage;
sf::Image Resource::redgoredrightImage;
sf::Image Resource::redyellowImage;
sf::Image Resource::redyellowgoredpeopleImage;
sf::Image Resource::redyellowgoredrightImage;
sf::Image Resource::sebrangImage;
sf::Image Resource::tambahImage;
sf::Image Resource::kurangImage;
sf::Image Resource::sebranghoverImage;
sf::Image Resource::tambahhoverImage;
sf::Image Resource::kuranghoverImage;
sf::Image Resource::carImage;
sf::Image Resource::humanImage;
sf::Image Resource::closeImage;
sf::Image Resource::closehoverImage;

sf::Texture Resource::backgroundtexture;
sf::Texture Resource::greenTexture;
sf::Texture Resource::greengogreenrightTexture;
sf::Texture Resource::greengoredpeopleTexture;
sf::Texture Resource::greengoredrightTexture;
sf::Texture Resource::redTexture;
sf::Texture Resource::redgogreenpeopleTexture;
sf::Texture Resource::redgoredpeopleTexture;
sf::Texture Resource::redgoredrightTexture;
sf::Texture Resource::redyellowTexture;
sf::Texture Resource::redyellowgoredpeopleTexture;
sf::Texture Resource::redyellowgoredrightTexture;
sf::Texture Resource::sebrangTexture;
sf::Texture Resource::tambahTexture;
sf::Texture Resource::kurangTexture;
sf::Texture Resource::sebranghoverTexture;
sf::Texture Resource::tambahhoverTexture;
sf::Texture Resource::kuranghoverTexture;
sf::Texture Resource::carTexture;
sf::Texture Resource::humanTexture;
sf::Texture Resource::closeTexture;
sf::Texture Resource::closehoverTexture;

sf::Sprite Resource::background;
sf::Sprite Resource::greenwest;
sf::Sprite Resource::greengogreenright;
sf::Sprite Resource::greengoredpeoplenorth;
sf::Sprite Resource::greengoredpeoplesouth;
sf::Sprite Resource::greengoredright;
sf::Sprite Resource::redwest;
sf::Sprite Resource::redgogreenpeoplenorth;
sf::Sprite Resource::redgoredpeoplenorth;
sf::Sprite Resource::redgoredright;
sf::Sprite Resource::redgogreenpeoplesouth;
sf::Sprite Resource::redgoredpeoplesouth;
sf::Sprite Resource::redyellowwest;
sf::Sprite Resource::redyellowgoredpeoplenorth;
sf::Sprite Resource::redyellowgoredright;
sf::Sprite Resource::redyellowgoredpeoplesouth;
sf::Sprite Resource::sebrang;
sf::Sprite Resource::tambahnorth;
sf::Sprite Resource::kurangnorth;
sf::Sprite Resource::tambahsouth;
sf::Sprite Resource::kurangsouth;
sf::Sprite Resource::tambahwest;
sf::Sprite Resource::kurangwest;
sf::Sprite Resource::tambaheast;
sf::Sprite Resource::kurangeast;
sf::Sprite Resource::sebranghover;
sf::Sprite Resource::tambahnorthhover;
sf::Sprite Resource::kurangnorthhover;
sf::Sprite Resource::tambahsouthhover;
sf::Sprite Resource::kurangsouthhover;
sf::Sprite Resource::tambahwesthover;
sf::Sprite Resource::kurangwesthover;
sf::Sprite Resource::tambaheasthover;
sf::Sprite Resource::kurangeasthover;
sf::Sprite Resource::carnorth;
sf::Sprite Resource::carsouth;
sf::Sprite Resource::carwest;
sf::Sprite Resource::careast;
sf::Sprite Resource::humannorth;
sf::Sprite Resource::humansouth;
sf::Sprite Resource::close;
sf::Sprite Resource::closehover;

//rect for button
sf::IntRect Resource::sebrangRect;
sf::IntRect Resource::closeRect;

sf::IntRect Resource::tambahnorthRect;
sf::IntRect Resource::kurangnorthRect;
sf::IntRect Resource::tambahsouthRect;
sf::IntRect Resource::kurangsouthRect;
sf::IntRect Resource::tambahwestRect;
sf::IntRect Resource::kurangwestRect;
sf::IntRect Resource::tambaheastRect;
sf::IntRect Resource::kurangeastRect;

//font
sf::Font Resource::SimulationFont;

//array of car
std::vector<Resource::CarSprite> Resource::Arraycarnorth;
std::vector<Resource::CarSprite> Resource::Arraycarsouth;
std::vector<Resource::CarSprite> Resource::Arraycarwest;
std::vector<Resource::CarSprite> Resource::Arraycareast;


void Resource::LoadResource()
{
	backgroundimage.loadFromFile("Resources/background.png");
	greenImage.loadFromFile("Resources/green.png");
	greengogreenrightImage.loadFromFile("Resources/greengogreenright.png");
	greengoredpeopleImage.loadFromFile("Resources/greengoredpeople.png");
	greengoredrightImage.loadFromFile("Resources/greengoredright.png");
	redImage.loadFromFile("Resources/red.png");
	redgogreenpeopleImage.loadFromFile("Resources/redgogreenpeople.png");
	redgoredpeopleImage.loadFromFile("Resources/redgoredpeople.png");
	redgoredrightImage.loadFromFile("Resources/redgoredright.png");
	redyellowImage.loadFromFile("Resources/redyellow.png");
	redyellowgoredpeopleImage.loadFromFile("Resources/redyellowgoredpeople.png");
	redyellowgoredrightImage.loadFromFile("Resources/redyellowgoredright.png");
	sebrangImage.loadFromFile("Resources/sebrang_button.png");
	tambahImage.loadFromFile("Resources/tambah_button.png");
	kurangImage.loadFromFile("Resources/kurang_button.png");
	sebranghoverImage.loadFromFile("Resources/sebrang_hover.png");
	tambahhoverImage.loadFromFile("Resources/tambah_hover.png");
	kuranghoverImage.loadFromFile("Resources/kurang_hover.png");
	carImage.loadFromFile("Resources/car.png");
	humanImage.loadFromFile("Resources/human.png");
	closeImage.loadFromFile("Resources/close_button.png");
	closehoverImage.loadFromFile("Resources/close_hover.png");

	backgroundtexture.loadFromImage(backgroundimage);
	greenTexture.loadFromImage(greenImage);
	greengogreenrightTexture.loadFromImage(greengogreenrightImage);
	greengoredpeopleTexture.loadFromImage(greengoredpeopleImage);
	greengoredrightTexture.loadFromImage(greengoredrightImage);
	redTexture.loadFromImage(redImage);
	redgogreenpeopleTexture.loadFromImage(redgogreenpeopleImage);
	redgoredpeopleTexture.loadFromImage(redgoredpeopleImage);
	redgoredrightTexture.loadFromImage(redgoredrightImage);
	redyellowTexture.loadFromImage(redyellowImage);
	redyellowgoredpeopleTexture.loadFromImage(redyellowgoredpeopleImage);
	redyellowgoredrightTexture.loadFromImage(redyellowgoredrightImage);
	sebrangTexture.loadFromImage(sebrangImage);
	tambahTexture.loadFromImage(tambahImage);
	kurangTexture.loadFromImage(kurangImage);
	sebranghoverTexture.loadFromImage(sebranghoverImage);
	tambahhoverTexture.loadFromImage(tambahhoverImage);
	kuranghoverTexture.loadFromImage(kuranghoverImage);
	carTexture.loadFromImage(carImage);
	humanTexture.loadFromImage(humanImage);
	closeTexture.loadFromImage(closeImage);
	closehoverTexture.loadFromImage(closehoverImage);

	//smoothing texture
	sebranghoverTexture.setSmooth(1);
	tambahhoverTexture.setSmooth(1);
	kuranghoverTexture.setSmooth(1);
	greenTexture.setSmooth(1);
	greengogreenrightTexture.setSmooth(1);
	greengoredpeopleTexture.setSmooth(1);
	greengoredrightTexture.setSmooth(1);
	redTexture.setSmooth(1);
	redgogreenpeopleTexture.setSmooth(1);
	redgoredpeopleTexture.setSmooth(1);
	redgoredrightTexture.setSmooth(1);
	redyellowTexture.setSmooth(1);
	redyellowgoredpeopleTexture.setSmooth(1);
	redyellowgoredrightTexture.setSmooth(1);
	carTexture.setSmooth(1);
	humanTexture.setSmooth(1);
	closeTexture.setSmooth(1);
	closehoverTexture.setSmooth(1);

	background.setTexture(backgroundtexture);
	greenwest.setTexture(greenTexture);
	greengogreenright.setTexture(greengogreenrightTexture);
	greengoredright.setTexture(greengoredrightTexture);
	greengoredpeoplenorth.setTexture(greengoredpeopleTexture);
	greengoredpeoplesouth.setTexture(greengoredpeopleTexture);
	redwest.setTexture(redTexture);
	redgogreenpeoplenorth.setTexture(redgogreenpeopleTexture);
	redgogreenpeoplesouth.setTexture(redgogreenpeopleTexture);
	redgoredpeoplenorth.setTexture(redgoredpeopleTexture);
	redgoredpeoplesouth.setTexture(redgoredpeopleTexture);
	redgoredright.setTexture(redgoredrightTexture);
	redyellowwest.setTexture(redyellowTexture);
	redyellowgoredpeoplenorth.setTexture(redyellowgoredpeopleTexture);
	redyellowgoredpeoplesouth.setTexture(redyellowgoredpeopleTexture);
	redyellowgoredright.setTexture(redyellowgoredrightTexture);
	sebrang.setTexture(sebrangTexture);
	tambahnorth.setTexture(tambahTexture);
	kurangnorth.setTexture(kurangTexture);
	tambahsouth.setTexture(tambahTexture);
	kurangsouth.setTexture(kurangTexture);
	tambahwest.setTexture(tambahTexture);
	kurangwest.setTexture(kurangTexture);
	tambaheast.setTexture(tambahTexture);
	kurangeast.setTexture(kurangTexture);
	sebranghover.setTexture(sebranghoverTexture);
	tambahnorthhover.setTexture(tambahhoverTexture);
	kurangnorthhover.setTexture(kuranghoverTexture);
	tambahsouthhover.setTexture(tambahhoverTexture);
	kurangsouthhover.setTexture(kuranghoverTexture);
	tambahwesthover.setTexture(tambahhoverTexture);
	kurangwesthover.setTexture(kuranghoverTexture);
	tambaheasthover.setTexture(tambahhoverTexture);
	kurangeasthover.setTexture(kuranghoverTexture);
	carnorth.setTexture(carTexture);
	carsouth.setTexture(carTexture);
	carwest.setTexture(carTexture);
	careast.setTexture(carTexture);
	humannorth.setTexture(humanTexture);
	humansouth.setTexture(humanTexture);
	close.setTexture(closeTexture);
	closehover.setTexture(closehoverTexture);

	//clipping the sprite
	sf::IntRect carnorthRect;
	sf::IntRect carsouthRect;
	sf::IntRect carwestRect;
	sf::IntRect careastRect;

	carnorthRect.height = 76;
	carnorthRect.width = 76;
	carnorthRect.left = 0;
	carnorthRect.top = 0;

	carsouthRect.height = 76;
	carsouthRect.width = 76;
	carsouthRect.top = 228;
	carsouthRect.left = 0;

	carwestRect.height = 76;
	carwestRect.width = 76;
	carwestRect.left = 0;
	carwestRect.top = 152;

	careastRect.height = 76;
	careastRect.width = 76;
	careastRect.left = 0;
	careastRect.top = 76;

	carnorth.setTextureRect(carnorthRect);
	carsouth.setTextureRect(carsouthRect);
	carwest.setTextureRect(carwestRect);
	careast.setTextureRect(careastRect);

	//rescaling the sprite
	sebranghover.setScale(1.15f,1.15f);
	closehover.setScale(1.15f,1.15f);
	tambahnorthhover.setScale(1.15f,1.15f);
	kurangnorthhover.setScale(1.15f,1.15f);
	tambahsouthhover.setScale(1.15f,1.15f);
	kurangsouthhover.setScale(1.15f,1.15f);
	tambahwesthover.setScale(1.15f,1.15f);
	kurangwesthover.setScale(1.15f,1.15f);
	tambaheasthover.setScale(1.15f,1.15f);
	kurangeasthover.setScale(1.15f,1.15f);
	greenwest.setScale(0.25f,0.25f);
	greengogreenright.setScale(0.25f,0.25f);
	greengoredright.setScale(0.25f,0.25f);
	greengoredpeoplenorth.setScale(0.25f,0.25f);
	greengoredpeoplesouth.setScale(0.25f,0.25f);
	redwest.setScale(0.25f,0.25f);
	redgogreenpeoplenorth.setScale(0.25f,0.25f);
	redgogreenpeoplesouth.setScale(0.25f,0.25f);
	redgoredpeoplenorth.setScale(0.25f,0.25f);
	redgoredpeoplesouth.setScale(0.25f,0.25f);
	redgoredright.setScale(0.25f,0.25f);
	redyellowwest.setScale(0.25f,0.25f);
	redyellowgoredpeoplenorth.setScale(0.25f,0.25f);
	redyellowgoredpeoplesouth.setScale(0.25f,0.25f);
	redyellowgoredright.setScale(0.25f,0.25f);
	carnorth.setScale(0.6f,0.6f);
	carsouth.setScale(0.6f,0.6f);
	carwest.setScale(0.6f,0.6f);
	careast.setScale(0.6f,0.6f);


	//rotating the sprite
	greenwest.rotate(90);
	greengogreenright.rotate(270);
	greengoredright.rotate(270);
	redwest.rotate(90);
	redgoredright.rotate(270);
	redyellowwest.rotate(90);
	redyellowgoredright.rotate(270);

	//font
	SimulationFont.loadFromFile("Resources/PAPYRUS.ttf");

	//set position for car
	carnorth.setPosition(395,0);
	carsouth.setPosition(355,600);
	carwest.setPosition(0,255);
	careast.setPosition(800,295);

	//isi array of car
	CarSprite carnorthSprite;
	CarSprite carsouthSprite;
	CarSprite carwestSprite;
	CarSprite careastSprite;

	carnorthSprite.sprite = carnorth;
	carnorthSprite.rect.height = 0;
	carnorthSprite.rect.width = 0;
	carnorthSprite.rect.left = 0;
	carnorthSprite.rect.top = 0;
	carnorthSprite.IsMoveInSquare = false;
	carnorthSprite.IsRotate = false;
	carnorthSprite.IsMoveToNorth = false;

	carsouthSprite.sprite = carsouth;
	carsouthSprite.rect.height = 0;
	carsouthSprite.rect.width = 0;
	carsouthSprite.rect.left = 0;
	carsouthSprite.rect.top = 0;
	carsouthSprite.IsMoveInSquare = false;
	carsouthSprite.IsRotate = false;
	carsouthSprite.IsMoveToNorth = false;

	carwestSprite.sprite = carwest;
	carwestSprite.rect.height = 0;
	carwestSprite.rect.width = 0;
	carwestSprite.rect.left = 0;
	carwestSprite.rect.top = 0;
	carwestSprite.IsMoveInSquare = false;
	carwestSprite.IsRotate = false;
	carwestSprite.IsMoveToNorth = false;

	careastSprite.sprite = careast;
	careastSprite.rect.height = 0;
	careastSprite.rect.width = 0;
	careastSprite.rect.left = 0;
	careastSprite.rect.top = 0;
	careastSprite.IsMoveInSquare = false;
	careastSprite.IsRotate = false;
	careastSprite.IsMoveToNorth = false;

	int i;
	for(i=0;i<=10;i++)
	{
		Arraycarnorth.push_back(carnorthSprite);
	}
	for(i=0;i<=10;i++)
	{
		Arraycarsouth.push_back(carsouthSprite);
	}
	for(i=0;i<=10;i++)
	{
		Arraycarwest.push_back(carwestSprite);
	}
	for(i=0;i<=10;i++)
	{
		Arraycareast.push_back(careastSprite);
	}
}