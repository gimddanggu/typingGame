// ui 초기화 함수 initUI()
#include <SFML/Graphics.hpp>

// 결과창을 윈도우 비율에 맞게 만들기 위한 함수
sf::RectangleShape makeRectangle(sf::RenderWindow& window, float widthRatio, float heightRatio)
{
	// 현재 창 크기
	sf::Vector2u winSize = window.getSize();

	// 사각형 사이즈 조절
	sf::Vector2f rectSize(winSize.x * widthRatio, winSize.y * heightRatio);
	sf::RectangleShape rect(rectSize);
	rect.setFillColor(sf::Color::White);
	return rect;

}

// 컨테이너 생성용 함수 
sf::RectangleShape makeRectangle(sf::FloatRect& frameBounds, float widthRatio, float heightRatio, sf::Color color)
{
	// 현재 창 크기
	sf::Vector2f frameSize = frameBounds.size;

	// 사각형 사이즈 조절
	sf::Vector2f rectSize(frameSize.x * widthRatio, frameSize.y * heightRatio);
	sf::RectangleShape rect(rectSize);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(color);

	return rect;

}

// 가운데 정렬 - 윈도우 기준
sf::Vector2f getWindowCenterPosition(const sf::RenderWindow& window, const sf::FloatRect& targetBounds)
{
	float centerX = window.getSize().x / 2.f;
	float centerY = window.getSize().y / 2.f;

	float x = centerX - targetBounds.size.x / 2.f;
	float y = centerY - targetBounds.size.y / 2.f;

	return { x, y };
}

// 어떤 객체 기준 x 축 가운데 정렬
sf::Vector2f getCenterXPosition(sf::Vector2f targetSize,
	const sf::FloatRect& refBounds,
	float y)
{
	float x = refBounds.position.x + (refBounds.size.x - targetSize.x) / 2.f;
	return { x, y };
}

// 왼쪽 정렬
sf::Vector2f LeftInnerAlign(sf::FloatRect& refBounds, float x_margin = 0.f)
{
	return { refBounds.position.x + x_margin, refBounds.position.y };
}

// 오른쪽 정렬
sf::Vector2f RightInnerAlign(sf::Vector2f targetSize, sf::FloatRect& refBounds, float x_margin = 0.f)
{
	return { refBounds.position.x + refBounds.size.x - targetSize.x - x_margin, refBounds.position.y };
}

void initContainer(sf::RenderWindow& window)
{
	sf::RectangleShape profileBox_Frame = makeRectangle(window, 0.5f, 0.5f);

	// 기준 객체
	sf::FloatRect frameBound = profileBox_Frame.getGlobalBounds();
	profileBox_Frame.setPosition(getWindowCenterPosition(window, frameBound));			// 윈도우를 중심으로 중앙정렬
	frameBound = profileBox_Frame.getGlobalBounds();


	// 정렬을 위한 컨테이너 생성
	sf::RectangleShape profileBox_Title = makeRectangle(frameBound, 0.4f, 0.1f, sf::Color::Red);
	sf::RectangleShape profileBox_Image = makeRectangle(frameBound, 0.3f, 0.5f, sf::Color::Green);
	sf::RectangleShape profileBox_info = makeRectangle(frameBound, 0.5f, 0.6f, sf::Color::Yellow);
	sf::RectangleShape profileBox_info_label;
	sf::RectangleShape profileBox_info_value;


	// 제목 frame
	sf::Vector2f TitleSize = profileBox_Title.getSize();
	sf::FloatRect profileBox_Title_Bound = profileBox_Title.getGlobalBounds();
	sf::Vector2f titlePos = getCenterXPosition(TitleSize, frameBound, frameBound.position.y);	// 프로필 프래임 기준으로 중앙 정렬

	// 이미지 frame
	sf::Vector2f imgSize = profileBox_Image.getSize();
	sf::FloatRect profileBox_Image_Bound = profileBox_Image.getGlobalBounds();
	sf::Vector2f imgPos = LeftInnerAlign(frameBound, 30.f);										// 프로필 프래임 기준으로 왼쪽 정렬

	// 정보 입력 frame
	sf::Vector2f infoSize = profileBox_info.getSize();
	sf::FloatRect profileBox_info_Bound = profileBox_info.getGlobalBounds();
	sf::Vector2f infoPos = RightInnerAlign(infoSize, frameBound, 30.f);							// 프로필 프래임 기준으로 오른쪽 정렬

	// 위치 조정
	profileBox_Image.setPosition({ imgPos.x, imgPos.y + 90.0f });	// 왼쪽 정렬 됨
	profileBox_info.setPosition({ infoPos.x, infoPos.y + 90.0f });	// 오른쪽 정렬 됨
	profileBox_Title.setPosition(titlePos);
}