#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>
#include "DrawUIR.hpp"
#include "UIAlign.hpp"
#include "GameState.hpp"

#include <Windows.h>
#include <iomanip>  // std::hex, std::setw
#include <codecvt>  // wide → utf8 변환 (
#include <locale>
// 목록 (한글연습, 영어연습, 코딩연습, 타자대결)


std::string wstringToUtf8(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(wstr);
}

struct MenuButton {
    sf::RectangleShape box;
    sf::Text label;
    std::function<void()> onClick;


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

struct TajaMenuUI {
    std::vector<MenuButton> mainMenuButtons;
    MenuButton logoutButton;
    sf::Sprite profileSprite;
    sf::Text nicknameText;

    


    TajaMenuUI(const sf::Font& font, const sf::Texture& texture) : logoutButton(font), profileSprite(texture), nicknameText(font){}
};

void drawBtn(sf::RenderWindow& window, MenuButton& btn) {
    window.draw(btn.box);
    window.draw(btn.label);
}

// 호버효과
void menuHover(std::vector<MenuButton>& buttons, sf::Vector2f mousePos) {
    for (auto& btn : buttons) {
        if (btn.contains(mousePos)) {
            btn.box.setFillColor(sf::Color(60, 110, 60, 110));
            btn.label.setFillColor(sf::Color::White);
            //std::cout << "hover" << std::endl;
        }
        else {
            btn.box.setFillColor(sf::Color(46, 79, 46, 110));
            btn.label.setFillColor(sf::Color(208, 208, 208));
        }
    }   
}


void logoutHover(MenuButton& button, sf::Vector2f mousePos) {

    if (button.contains(mousePos)) {
        button.box.setFillColor(sf::Color(160, 10, 10));
        button.label.setFillColor(sf::Color(255, 255, 255));
    }
    else {
        button.box.setFillColor(sf::Color(139, 0, 0));
        button.label.setFillColor(sf::Color::White);
        
    }
}

void initTajaMenu(sf::RenderWindow& window, GameState& game, sf::Font& font, TajaMenuUI& ui) {
    sf::RectangleShape mFrame = makeRectangleR(window, 0.4f, 0.5f, sf::Color::Transparent, sf::Color::Transparent, 3.0f);
    sf::FloatRect frameBounds = mFrame.getGlobalBounds();
    sf::Vector2f frameSize = mFrame.getSize();

    sf::Vector2 framePos = getWindowCenterPosition(window, frameBounds); // 가운데 정렬
    mFrame.setPosition(framePos);

    std::vector<std::wstring> mainMenuLabels = { L"> 한글연습", L"> 영어연습", L"> 코딩연습", L"> 타자대결" };


    for (int i = 0; i < 4; i++) {
        MenuButton btn(font);
        btn.box = makeRectangleR(frameSize, 1.0f, 0.25f, sf::Color::Transparent, sf::Color::Transparent, 2.0f);
        btn.box.setPosition({ framePos.x, framePos.y + btn.box.getSize().y * i });
        btn.label.setString(mainMenuLabels[i]);

        btn.onClick = [&game, label = mainMenuLabels[i]]() {
            //std::wcout << label;
            //wprintf(L"[클릭됨] %ls\n", label.c_str());
            //std::cout << "[클릭됨] " << wstringToUtf8(label) << std::endl;
            std::wcout << L"[씬 이동] " << label << std::endl;
            game.currentScene = Scene::FILE_SELECT;
            };
        btn.setBtnPos(15.f);

        ui.mainMenuButtons.push_back(btn);
    }

    // 로그아웃 버튼 생성
    MenuButton logoutButton(font);
    logoutButton.box = makeRectangleR(frameSize, 0.3f, 0.15f);
    logoutButton.box.setFillColor(sf::Color(0, 0, 0, 0));
    logoutButton.label.setString(L"LOGOUT");
    logoutButton.onClick = []() {
        std::cout << "logout";
        };
    sf::Vector2f logoutBtnPos = getWindowCenterPosition(window, logoutButton.box.getGlobalBounds());
    sf::FloatRect lastBtnBounds = ui.mainMenuButtons.back().box.getGlobalBounds();  //  마지막 버튼 밑에 로그아웃을 위치 시키기 위해
    logoutButton.box.setPosition({ logoutBtnPos.x, lastBtnBounds.position.y + lastBtnBounds.size.y + 20.f });
    AlignTextCenter(logoutButton.label, logoutButton.box.getGlobalBounds());

    ui.logoutButton = logoutButton;
    // 랭킹 버튼 생성 // 아이콘만 있었나?
    //MenuButton rankingButton(font);

    // 프로필 버튼 생성
    sf::RectangleShape profileFrame = makeRectangleR(window, 0.25f, 0.18f, sf::Color::Transparent, sf::Color::Green, 3.0f);
    profileFrame.setPosition({ 20, 20 });   // padding
    sf::Vector2f profileFrameSize = profileFrame.getSize();
    sf::RectangleShape imgFrame({ profileFrameSize.y, profileFrameSize.y });
    imgFrame.setOutlineColor(sf::Color::Yellow);
    imgFrame.setOutlineThickness(3);
    imgFrame.setPosition({ 20, 20 });
    sf::Vector2f imgFrameSize = imgFrame.getSize();

    sf::RectangleShape nickFrame({ profileFrameSize.x - imgFrameSize.x, profileFrameSize.y / 3 });
    nickFrame.setPosition({ 20 + imgFrameSize.x, 20});
    sf::Texture profileTexture = game.user.profileTexture;
    sf::Vector2u profileTextureSize = profileTexture.getSize();

    // 스프라이트 프레임에 맞추는 작업
    float scaleX = imgFrameSize.x / profileTextureSize.x;
    float scaleY = imgFrameSize.y / profileTextureSize.y;
    ui.profileSprite.setTexture(game.user.profileTexture);
    ui.profileSprite.setScale({ scaleX, scaleY });
    ui.profileSprite.setPosition({20, 20});


    // 닉네임 추가
    sf::Text nickname(font, game.user.nickname, 30);
    AlignTextCenterY(nickname, nickFrame.getGlobalBounds(), {10, 0});
    //nickname.setPosition({ 20 + 10 + imgFrameSize.x, 20 });
    nickname.setFillColor(sf::Color::White);
    ui.nicknameText = nickname;

    

}

void tajaMenuHandeler(sf::RenderWindow& window, GameState& game, TajaMenuUI& ui, const std::optional<sf::Event>& event) {
    if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
        sf::Vector2f clickPos = window.mapPixelToCoords({ mouse->position.x, mouse->position.y });

        for (auto& btn : ui.mainMenuButtons) {
            if (btn.contains(clickPos)) {
                std::cout << "click" << std::endl;
                btn.onClick();
            }
        }

        if (ui.logoutButton.contains(clickPos)) ui.logoutButton.onClick();
        else if (ui.profileSprite.getGlobalBounds().contains(clickPos)) {
            std::wcout << L"[클릭] 프로필 클릭!" << std::endl;
            game.currentScene = Scene::PROFILE;
        }
    }
}

void renderTajaMenu(sf::RenderWindow& window, TajaMenuUI& ui) {
    for (auto& btn : ui.mainMenuButtons) {
        drawBtn(window, btn);
    }

    drawBtn(window, ui.logoutButton);

    window.draw(ui.profileSprite);
    window.draw(ui.nicknameText);

}

