
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>

#define WINDOW_HEIGHT 25	//窗口高度
#define WINDOW_WIDTH 80		//窗口宽度
#define STAGE_HEIGHT 1308		//界面高度
#define STAGE_WIDTH 2000		//界面宽度
#define SCALE 0.6						//缩放倍数

using namespace sf;

const int height = STAGE_HEIGHT;
const int width = STAGE_WIDTH;

VideoMode mode = VideoMode::getDesktopMode();
Vector2i ViewPos;
sf::RenderWindow window(sf::VideoMode(width* SCALE, height* SCALE), L"好起来了？");
Texture tLoadingPic, tPlayButton_HighLight, tStopButton_HighLight;
Sprite spLoadingPic, spPlayButton_HighLight, spStopButton_HighLight;


Music LoadMusic;
SoundBuffer SouBufButPrs, SouBufButSlide;
Sound SoundButPrs, SoundButSlide;
/*
SouBufButPrs->SoundButPrs	按钮按下的音效
SouBufButSlide->SoundButSlide按钮划过的音效
*/

int Volume = 50;

Font font;
Text text;

Vector2i Loadposition;	//记录鼠标坐标

bool isOver;	//判断游戏是否退出
int inScene;//判断当前是否在主界面
bool isPlayBut_High, isPlayBut_Press, isSouPlay;	//鼠标移过按钮\按下按钮\判断移过音效是否播放
bool isStopBut_High, isStopBut_Press;	//功能同上，处理退出按钮事件

//SoundBuffer sbEat, sbDie;
//Sound soundEat, soundDie;
void initial() {
	ViewPos.x = (mode.width - STAGE_WIDTH * SCALE) / 2;
	ViewPos.y = (mode.height - STAGE_HEIGHT * SCALE) / 2;
	window.setPosition(ViewPos);
	//资源初始化


	if (!tLoadingPic.loadFromFile("./Assets/Meterials/bk.png")) {
		//主界面背景
		std::cout << "资源loading.png加载失败！" << std::endl;
	}
	spLoadingPic.setTexture(tLoadingPic);
	spLoadingPic.setScale(SCALE, SCALE);

	//资源初始化结束
	//布尔变量初始化
	isOver = false;
	inScene = 1;
	isPlayBut_High = false;
	isPlayBut_Press = false;
	isSouPlay = true;
}

void Loading_Logic() {		//起始界面代码（包括按钮逻辑和生成语句，触发在Input
	spLoadingPic.setPosition(0, 0);
	window.draw(spLoadingPic);
	if (isPlayBut_High == true) {	//鼠标划过开始游戏按钮时高亮,播放音频SoundButSlide
		spPlayButton_HighLight.setPosition(810 * SCALE, 540 * SCALE);
		window.draw(spPlayButton_HighLight);
		if (isSouPlay == true) {
			SoundButSlide.play();
			isSouPlay = false;
		}
	}
	if (isStopBut_High == true) {	//鼠标划过退出游戏按钮时高亮,播放音频SoundButSlide
		spStopButton_HighLight.setPosition(810 * SCALE, 855 * SCALE);
		window.draw(spStopButton_HighLight);
		if (isSouPlay == true) {
			SoundButSlide.play();
			isSouPlay = false;
		}
	}
	if (isPlayBut_Press == true) {	//鼠标抬起时播放音频SoundButPrs
		isPlayBut_Press = false;
		SoundButPrs.play();
		inScene = 2;
	}

	window.display();
}

void Loading_Input() {
	text.setCharacterSize(24);
	text.setFillColor(Color(0, 0, 0, 255));

	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
		}
	}
	if (event.type == Event::KeyReleased) {		//键盘抬起事件
		switch (event.key.code) {
		case Keyboard::Escape:		//Esc退出游戏
			window.close();
		default:
			break;
		}
	}
	Loadposition = Mouse::getPosition(window);		//鼠标移过事件
	//开始游戏按钮
	if ((Loadposition.x >= 810 * SCALE && Loadposition.x <= 1240 * SCALE) && (Loadposition.y >= 540 * SCALE && Loadposition.y <= 620 * SCALE)) {
		isPlayBut_High = true;
	}
	else {
		if (isPlayBut_High == true)isSouPlay = true;
		isPlayBut_High = false;
	}
	//退出游戏按钮
	if ((Loadposition.x >= 810 * SCALE && Loadposition.x <= 1240 * SCALE) && (Loadposition.y >= 855 * SCALE && Loadposition.y <= 935 * SCALE)) {
		isStopBut_High = true;
	}
	else {
		if (isStopBut_High == true) isSouPlay = true;
		isStopBut_High = false;
	}

	if (event.type == Event::MouseButtonReleased) {	//鼠标抬起事件
		//开始游戏按钮
		if ((Loadposition.x >= 810 * SCALE && Loadposition.x <= 1240 * SCALE) && (Loadposition.y >= 540 * SCALE && Loadposition.y <= 620 * SCALE)) {
			isPlayBut_Press = true;
		}
		else isPlayBut_Press = false;
		//退出游戏按钮
		if ((Loadposition.x >= 810 * SCALE && Loadposition.x <= 1240 * SCALE) && (Loadposition.y >= 855 * SCALE && Loadposition.y <= 935 * SCALE)) {
			//SoundButPrs.play();
			Sleep(300);
			window.close();
		}
	}
}

int main() {
	/*初始化
	while（游戏是否结束or是否重新开始）{
	场景绘制
	while（玩家是否结束回合or是否超时）{
	玩家操作
	逻辑判断
	}
	while（可执行操作是否完毕）{
	AI操作
	逻辑判断
	}
	}
	*/
	initial();

	while (window.isOpen() && isOver == false) {
		switch (inScene)
		{
		case 1://开始界面
			Loading_Logic();
			Loading_Input();
			break;
		case 2:
			Loading_Logic();
			Loading_Input();
			break;
		default:
			break;
		}
		Sleep(50);
	}
	return 0;
}