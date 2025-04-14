#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>
#include "DrawUIR.hpp"
#include "UIAlign.hpp"

#include <Windows.h>
// 목록 (한글연습, 영어연습, 코딩연습, 타자대결)
struct MenuButton {
    sf::RectangleShape box;
    sf::Text label;
    std::function<void()> onClick;
    bool isHovered = false;


    // Text는 기본 생성자가 없으므로 : 초기화로 font 를 줘야 한다.
    MenuButton(const sf::Font& font) : label(font) {
   
    }

    bool contains(const sf::Vector2f& MousePoint) const {
        return box.getGlobalBounds().contains(MousePoint);
    }


    // 텍스트 버튼안에 정렬
    void setBtnPos(float padding) {
        sf::FloatRect textBounds = label.getGlobalBounds();
        sf::Vector2f boxPos = box.getPosition();
        //sf::Vector2f boxSize = box.getSize();
        label.setFillColor(sf::Color::Black);
        label.setCharacterSize(45);
        label.setPosition({ boxPos.x + padding, boxPos.y + padding });
    }

};

void drawBtn(sf::RenderWindow& window, MenuButton& btn) {
    window.draw(btn.box);
    window.draw(btn.label);
}

// 호버효과
void updateHover(std::vector<MenuButton>& buttons, sf::Vector2f mousePos) {
    for (auto& btn : buttons) {
        if (btn.contains(mousePos)) {
            btn.box.setFillColor(sf::Color(60, 110, 60, 110));
            btn.label.setFillColor(sf::Color::White);
            std::cout << "hover" << std::endl;
        }
        else {
            btn.box.setFillColor(sf::Color(46, 79, 46, 110));
            btn.label.setFillColor(sf::Color(208, 208, 208));
        }
    }   
}


int main() {
    // 디버그용 한글 출력되도록
    SetConsoleOutputCP(CP_UTF8);  // 콘솔 출력 UTF-8 설정
    std::wcout.imbue(std::locale(""));



    // 폰트 불러옴
    sf::Font font;
    if (!font.openFromFile("assets/fonts/DungGeunMo.ttf")) {
        std::wcerr << L"[ERROR] 폰트 로드 실패!" << std::endl;
        return 1;
    }

    // 윈도우 생성
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Typing Game");
    // 배경 이미지
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/resorce_img/background_sunset.png")) {
        std::wcerr << L"[ERROR] 폰트 로드 실패!" << std::endl;
        return 1;
    }

    sf::Sprite backgroundSprite(backgroundTexture);

    // 윈도우 크기 기준으로 스프라이트 크기 조정
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    backgroundSprite.setScale({ scaleX, scaleY });


    // 렌더링
    // 윈도우 비율에 맞게 사각형 생성
    sf::RectangleShape mFrame = makeRectangleR(window, 0.4f, 0.5f, sf::Color::Transparent, sf::Color::Transparent, 3.0f);
    sf::FloatRect frameBounds = mFrame.getGlobalBounds();
    sf::Vector2f frameSize = mFrame.getSize();

    sf::Vector2 framePos = getWindowCenterPosition(window, frameBounds); // 가운데 정렬
    mFrame.setPosition(framePos);

    std::vector<MenuButton> mainMenuButtons;
    std::vector<std::wstring> mainMenuLabels = { L"> 한글연습", L"> 영어연습", L"> 코딩연습", L"> 타자대결"};

    
    for (int i = 0; i < 4; i++) {
        MenuButton btn(font);
        btn.box = makeRectangleR(frameSize, 1.0f, 0.25f, sf::Color::Transparent, sf::Color::Transparent, 2.0f);
        btn.box.setPosition({ framePos.x, framePos.y + btn.box.getSize().y * i });
        btn.label.setString(mainMenuLabels[i]);
        
        btn.onClick = [label = mainMenuLabels[i]]() {
            std::cout << "click" << std::endl;
            };
        btn.setBtnPos(15.f);

        mainMenuButtons.push_back(btn);
    }

    // 로그아웃 버튼 생성
    MenuButton logoutButton(font);
    logoutButton.box = makeRectangleR(frameSize, 0.3f, 0.15f, sf::Color::Transparent, sf::Color::Blue, 2.f);
    logoutButton.box.setFillColor(sf::Color(0, 0, 0, 0));
    logoutButton.label.setString(L"LOGOUT");
    logoutButton.onClick = []() {
        std::cout << "logout";
        };
    sf::Vector2f logoutBtnPos = getWindowCenterPosition(window, logoutButton.box.getGlobalBounds());
    sf::FloatRect lastBtnBounds = mainMenuButtons.back().box.getGlobalBounds();  //  마지막 버튼 밑에 로그아웃을 위치 시키기 위해
    logoutButton.box.setPosition({ logoutBtnPos.x, lastBtnBounds.position.y + lastBtnBounds.size.y + 20.f });
    AlignTextCenter(logoutButton.label, logoutButton.box.getGlobalBounds());

    // 랭킹 버튼 생성 // 아이콘만 있었나?
    //MenuButton rankingButton(font);



    while (window.isOpen())
    {

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
        
        updateHover(mainMenuButtons, worldPos);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f clickPos = window.mapPixelToCoords({ mouse->position.x, mouse->position.y });

                for (auto& btn : mainMenuButtons) {
                    if (btn.contains(clickPos)) {
                        std::cout << "click" << std::endl;
                        btn.onClick();
                    }
                }

                if(logoutButton.contains(worldPos)) logoutButton.onClick();
            }
                


        }

        window.clear(sf::Color::White);
        window.draw(backgroundSprite);

        
        for (auto& btn : mainMenuButtons) {
            drawBtn(window, btn);
            //if (btn.contains(worldPos)) btn.onClick();
        }

        drawBtn(window, logoutButton);
        //if (logoutButton.contains(worldPos)) logoutButton.onClick();

        window.display();
    }

    return 0;
}

// 호버

// 버튼 이벤트 (한글, 영어, 코딩, 대결, 로그아웃, 랭킹)

