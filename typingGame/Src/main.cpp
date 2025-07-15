// 타자 게임 메인 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "GameState.hpp"
#include "Scene.hpp"
#include "UIAlign.hpp"
#include "DrawUI.hpp"
#include "FileLoader.hpp"
#include "TextUtil.hpp"
#include "TypingGame.hpp";
#include "ResultScreen.hpp"
#include "DrawUIR.hpp"
#include "FileSelectList.hpp"
#include "UserProfileUI.hpp"
#include "UserProfileSelectUI.hpp"
#include "TajaMainUI.hpp"
#include <locale>
#include <windows.h>


#include <iomanip>  // std::hex, std::setw
#include <codecvt>  // wide → utf8 변환 (선택)

// 디버그 확인용 함수
void debugPrintSentences(const std::vector<std::vector<std::wstring>>& sentences) {
    for (size_t i = 0; i < sentences.size(); ++i) {
        std::wcout << L"[문장 그룹 " << i << L"]\n";
        for (size_t j = 0; j < sentences[i].size(); ++j) {
            const std::wstring& line = sentences[i][j];
            std::wcout << L"  줄 " << j << L": \"" << line << L"\"\n";
            for (size_t k = 0; k < line.size(); ++k) {
                wchar_t ch = line[k];
                std::wstring type;
                if (ch == L' ')
                    type = L"공백";
                else if (ch == L'\t')
                    type = L"탭";
                else
                    type = L"일반";

                std::wcout << L"    [" << k << L"] '" << (ch == L' ' ? L'공백' : (ch == L'\t' ? L'tap' : ch))
                    << L"' (" << type << L")\n";
            }
        }
    }
}


int main() {
    // 로그 출력용
    //SetConsoleOutputCP(CP_UTF8);               // 콘솔 UTF-8 설정
    std::wcout.imbue(std::locale(""));         // 유니코드 로케일 설정
    

    // 윈도우 생성 
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), L"타자연습 게임");
    
    // 게임상태 저장  구조체
    GameState game;
    // 메인 메뉴 초기화
    // 폰트 불러옴
    sf::Font font1;
    if (!font1.openFromFile("assets/fonts/DungGeunMo.ttf")) {
        std::wcerr << L"[ERROR] 폰트 로드 실패!" << std::endl;
        return 1;
    }


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


    
    // 메인 메뉴 초기화 끝

    // 테스트 용 임시 유저 정보
    game.user.id = L"test_user_001";
    game.user.nickname = L"인순이";
    game.user.profileImagePath = L"assets/profile_img/crok2.png";

    // 폰트 설정 d2
    sf::Font font;
    if (!font.openFromFile("assets/fonts/D2Coding.ttf")) {
        std::wcerr << L"[ERROR] 폰트 로드 실패!" << std::endl;
        return 1;
    }


    int fontSize = game.user.fontSize;

    // 기본 프로필 이미지 로드
    sf::Image img = loadImg(game.user.profileImagePath);
    game.user.profileTexture = sf::Texture(resizeImageKeepAspect(img));
    sf::Sprite userImage(game.user.profileTexture);

    std::vector<sf::Sprite> sprites;            // 이건 삭제 고민
    std::vector<ImageOption> imageOptions;      // 추가함 
    std::vector<FileOption> fileOptions;
    std::vector<std::wstring> typingFilePath;
    std::wstring selectMod = L"한글";

    //// 프로필 이미지 로딩
    //if (game.user.profileTexture.loadFromFile(game.user.profileImagePath)) {
    //    // 로딩 성공
    //}
    //else {
    //    std::wcout << L"프로필 이미지 로딩 실패!" << std::endl;
    //}

    game.selectPath = L"assets/hangleFile/애국가.txt";    

    // 게임 기록 - 일단 임의로 초기화
    game.user.point = 1234;
    game.user.bestWPM = 87.5f;
    game.user.bestAccuracy = 96.2f;
    game.user.totalPlayCount = 12;
    game.user.totalPlayTime = 983.7f;

    
    game.currentScene = Scene::MAIN_MENU; // 초기값 줬으므로 필요 x 나중에 복사용으로 남겨뒀음

    TajaMenuUI ui(font1, game.user.profileTexture);
    InitTajaMenu(window, game, font1, ui);


    // 목록확인 테스트용 
    typingFilePath = {
            L"C:/dev/typingGame/assets/typing/BOJ_2751.py",
            L"C:/dev/typingGame/assets/typing/BOJ_11050.py",
            L"C:/dev/typingGame/assets/typing/heap_study.py",
            L"C:/Source/IoT-python-2025/day04/py03_module.py",
            L"C:/Source/IoT-python-2025/day02/py02_datastruct.py",
            L"C://Users//Admin//Downloads//TypingTest_EnglishOnly.java",
            L"assets/typing/한글2.txt",
            L"assets/typing/english.txt",
            L"assets/typing/coding.cpp",
            L"assets/typing/coding.cpp",
            L"assets/typing/한글1.txt",

    };

    /*ypingFilePath = {
        L"C:\\Users\\Admin\\Documents\\카카오톡 받은 파일"
    };*/

    /* \t 확인용 코드 */
    //std::wstring content = loadText(typingFilePath[4]);
    //std::vector<std::wstring> lines = splitStrtoVector(content);
    ////std::cout << "[DEBUG] typingAreaWith: " << game.typingAreaWidth << '\n';
    //game.sentences = wrapAllLinesToPixelWidth(lines, font, game.user.fontSize, game.typingAreaWidth);
    // 
    // 프로필 선택 hover 효과
    sf::RectangleShape thumbnailHoverOutline;
    thumbnailHoverOutline.setSize({ 200, 200 }); // 썸네일 크기에 맞게
    thumbnailHoverOutline.setFillColor(sf::Color::Transparent);
    thumbnailHoverOutline.setOutlineColor(sf::Color::Red);
    thumbnailHoverOutline.setOutlineThickness(4.f);

    std::vector<sf::Text> profileTexts;

    debugPrintSentences(game.sentences);

    // 메인 while 루프
    while (window.isOpen()) 
    {
        //std::wcout << L"[DEBUG] 현재 Scene: ";
        //std::wcout << L"[DEBUG] 현재 Scene: " << static_cast<int>(game.currentScene) << std::endl;

        // hover 및 버튼 이벤트를 위해 마우스 위치 저장
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);


        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            switch (game.currentScene) {
            case Scene::MAIN_MENU: {
                TajaMenuHandeler(window, game, ui, event);
            }
            case Scene::PROFILE: {  // 프로필 창 이벤트
                if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()){
                    if (mouse->button == sf::Mouse::Button::Left) {
                        if (game.showImageOverlay) {
                            for (int i = 0; i < sprites.size(); ++i) {
                                if (sprites[i].getGlobalBounds().contains(worldPos)) {
                                    imageOptions[i].onClick();
                                    
                                }
                            }

                            // 불러오기 버튼 클릭 확인
                            if (game.btn.loadImgBtnBounds.contains(worldPos)) {
                                std::wcout << L"[불러오기 버튼 클릭됨]" << std::endl;
                                auto originalPath = std::filesystem::current_path();	// 현재 폴더 경로 저장
                                std::wstring selectedImagePath = openImageFileDialog();
                                std::filesystem::current_path(originalPath);  // 다시 원래 경로로 되돌림 - 선택된 폴더 경로로 바뀌는 거 방지
                                sf::Image image;
                                if (image.loadFromFile(selectedImagePath)) {
                                    // 성공 처리
                                    std::wcout << L"[이미지를 성공적으로 불러왔습니다]" << std::endl;
                                    std::wcout << selectedImagePath << std::endl;
                                    game.user.profileImagePath = selectedImagePath;
                                    updateProfileImage(selectedImagePath, game, userImage);
                                    game.showImageOverlay = false;
                                    game.currentScene = Scene::PROFILE;


                                }
                                else {
                                    std::wcout << L"[이미지를 불러오지 못했습니다]" << std::endl;
                                    return -1;
                                }

                            }   // HOVER 이벤트
                            
                        }
                        if (game.btn.selectImgBtnBounds.contains(worldPos)) {
                            game.showImageOverlay = true;
                            std::cout << 1 << std::endl;
                        }
                    }
                }

                else if (const auto* move = event->getIf<sf::Event::MouseMoved>()) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(move->position);
                    game.bHoveringThumbnail = false;

                    for (int i = 0; i < sprites.size(); ++i) {
                        if (sprites[i].getGlobalBounds().contains(mousePos)) {
                            /*thumbnailHoverOutline.setPosition(sprites[i].getPosition());
                            thumbnailHoverOutline.setScale(sprites[i].getScale());*/
                            sf::FloatRect bounds = sprites[i].getGlobalBounds();
                            thumbnailHoverOutline.setPosition(bounds.position);
                            thumbnailHoverOutline.setSize(bounds.size);
                            game.bHoveringThumbnail = true;
                            break;
                        }
                    }
                }
                break;

                
            }
            case Scene::FILE_SELECT: {
                handleFileClick(game, *event, worldPos, fileOptions, font);
                break;
            }
            case Scene::TYPING_GAME: {  // 기본타자연습 이벤트
                // Scene별 입력 처리
                handleInputGame(game, *event);
                break;
            }
            }
        }

        // HOVER 효과
        if (game.currentScene == Scene::FILE_SELECT) {
            hoverText(game, fileOptions, worldPos);
        }
        else if (game.currentScene == Scene::MAIN_MENU) {
            menuHover(ui.mainMenuButtons, worldPos);
            logoutHover(ui.logoutButton, worldPos);
        }
        
        /*if (game.currentScene == Scene::IMAGESELECT) {
            hoverImg(game, fileOptions, worldPos);
        }*/


        window.clear(sf::Color::White);

        // 렌더링
        switch (game.currentScene) {
        case Scene::MAIN_MENU: {
            window.draw(backgroundSprite);
            renderTajaMenu(window, ui);
            break;
        }
        case Scene::PROFILE: {
            renderProfile(window, game, font, fontSize, userImage, profileTexts);       
            // profileTexts 이거 나중에 프로필 기록 나타낼 때 일단 필요

            if (game.showImageOverlay) {
                renderSelectImage(window, game, font, imageOptions, sprites, userImage, thumbnailHoverOutline);  // 프로필 이미지 선택 화면 겹쳐서 그림
            }
            break;
        }

        case Scene::FILE_SELECT: {
            renderFileList(window, game, font, fontSize, typingFilePath, fileOptions, game.curMode);
            break;
        }
        case Scene::TYPING_GAME: {
            if (game.currentScene == Scene::TYPING_GAME && !game.started) {
                game.startTime = std::chrono::high_resolution_clock::now();     // 게임 시작 시간 저장
                game.started = true;                    // 한 번만 초기화 하도록
            }
            auto now = std::chrono::high_resolution_clock::now();
            float elapsed = std::chrono::duration<float>(now - game.startTime).count();
            game.elapsedSeconds = elapsed;

            if (game.readyToShowResult)
                //game.progress = 100.f;
                game.currentScene = Scene::RESULT;

            renderGame(window, game, font, fontSize);         // UI 렌더링
            updateTypingStats(game, elapsed);           // 실시간 통계 업데이트
            updateGame(game);
            break;
        }
        case Scene::RESULT: {
            //renderResult(window, game);
            std::wcout << L"[DEBUG] 렌더링 RESULT 로 변경합니다." << std::endl;

            bool bRstart = showResultWindow(game, font, fontSize, game.sentences);
            if (bRstart) {
                resetGameResult(game);  // 값 초기화
                game.currentScene = Scene::TYPING_GAME;
            }
            else {
                game.currentScene = Scene::FILE_SELECT;
            }

            break;
        }
        }

        window.display();
    }

    return 0;
}
