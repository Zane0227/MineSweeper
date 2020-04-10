
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>

#define WINDOW_HEIGHT 25	//���ڸ߶�
#define WINDOW_WIDTH 80		//���ڿ��
#define STAGE_HEIGHT 1308		//����߶�
#define STAGE_WIDTH 2000		//������
#define SCALE 0.6						//���ű���

using namespace sf;

const int height = STAGE_HEIGHT;
const int width = STAGE_WIDTH;

VideoMode mode = VideoMode::getDesktopMode();
Vector2i ViewPos;
sf::RenderWindow window(sf::VideoMode(width* SCALE, height* SCALE), L"�������ˣ�");
Texture tLoadingPic, tPlayButton_HighLight, tStopButton_HighLight;
Sprite spLoadingPic, spPlayButton_HighLight, spStopButton_HighLight;


Music LoadMusic;
SoundBuffer SouBufButPrs, SouBufButSlide;
Sound SoundButPrs, SoundButSlide;
/*
SouBufButPrs->SoundButPrs	��ť���µ���Ч
SouBufButSlide->SoundButSlide��ť��������Ч
*/

int Volume = 50;

Font font;
Text text;

Vector2i Loadposition;	//��¼�������

bool isOver;	//�ж���Ϸ�Ƿ��˳�
int inScene;//�жϵ�ǰ�Ƿ���������
bool isPlayBut_High, isPlayBut_Press, isSouPlay;	//����ƹ���ť\���°�ť\�ж��ƹ���Ч�Ƿ񲥷�
bool isStopBut_High, isStopBut_Press;	//����ͬ�ϣ������˳���ť�¼�

//SoundBuffer sbEat, sbDie;
//Sound soundEat, soundDie;
void initial() {
	ViewPos.x = (mode.width - STAGE_WIDTH * SCALE) / 2;
	ViewPos.y = (mode.height - STAGE_HEIGHT * SCALE) / 2;
	window.setPosition(ViewPos);
	//��Դ��ʼ��


	if (!tLoadingPic.loadFromFile("./Assets/Meterials/bk.png")) {
		//�����汳��
		std::cout << "��Դloading.png����ʧ�ܣ�" << std::endl;
	}
	spLoadingPic.setTexture(tLoadingPic);
	spLoadingPic.setScale(SCALE, SCALE);

	//��Դ��ʼ������
	//����������ʼ��
	isOver = false;
	inScene = 1;
	isPlayBut_High = false;
	isPlayBut_Press = false;
	isSouPlay = true;
}

void Loading_Logic() {		//��ʼ������루������ť�߼���������䣬������Input
	spLoadingPic.setPosition(0, 0);
	window.draw(spLoadingPic);
	if (isPlayBut_High == true) {	//��껮����ʼ��Ϸ��ťʱ����,������ƵSoundButSlide
		spPlayButton_HighLight.setPosition(810 * SCALE, 540 * SCALE);
		window.draw(spPlayButton_HighLight);
		if (isSouPlay == true) {
			SoundButSlide.play();
			isSouPlay = false;
		}
	}
	if (isStopBut_High == true) {	//��껮���˳���Ϸ��ťʱ����,������ƵSoundButSlide
		spStopButton_HighLight.setPosition(810 * SCALE, 855 * SCALE);
		window.draw(spStopButton_HighLight);
		if (isSouPlay == true) {
			SoundButSlide.play();
			isSouPlay = false;
		}
	}
	if (isPlayBut_Press == true) {	//���̧��ʱ������ƵSoundButPrs
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
	if (event.type == Event::KeyReleased) {		//����̧���¼�
		switch (event.key.code) {
		case Keyboard::Escape:		//Esc�˳���Ϸ
			window.close();
		default:
			break;
		}
	}
	Loadposition = Mouse::getPosition(window);		//����ƹ��¼�
	//��ʼ��Ϸ��ť
	if ((Loadposition.x >= 810 * SCALE && Loadposition.x <= 1240 * SCALE) && (Loadposition.y >= 540 * SCALE && Loadposition.y <= 620 * SCALE)) {
		isPlayBut_High = true;
	}
	else {
		if (isPlayBut_High == true)isSouPlay = true;
		isPlayBut_High = false;
	}
	//�˳���Ϸ��ť
	if ((Loadposition.x >= 810 * SCALE && Loadposition.x <= 1240 * SCALE) && (Loadposition.y >= 855 * SCALE && Loadposition.y <= 935 * SCALE)) {
		isStopBut_High = true;
	}
	else {
		if (isStopBut_High == true) isSouPlay = true;
		isStopBut_High = false;
	}

	if (event.type == Event::MouseButtonReleased) {	//���̧���¼�
		//��ʼ��Ϸ��ť
		if ((Loadposition.x >= 810 * SCALE && Loadposition.x <= 1240 * SCALE) && (Loadposition.y >= 540 * SCALE && Loadposition.y <= 620 * SCALE)) {
			isPlayBut_Press = true;
		}
		else isPlayBut_Press = false;
		//�˳���Ϸ��ť
		if ((Loadposition.x >= 810 * SCALE && Loadposition.x <= 1240 * SCALE) && (Loadposition.y >= 855 * SCALE && Loadposition.y <= 935 * SCALE)) {
			//SoundButPrs.play();
			Sleep(300);
			window.close();
		}
	}
}

int main() {
	/*��ʼ��
	while����Ϸ�Ƿ����or�Ƿ����¿�ʼ��{
	��������
	while������Ƿ�����غ�or�Ƿ�ʱ��{
	��Ҳ���
	�߼��ж�
	}
	while����ִ�в����Ƿ���ϣ�{
	AI����
	�߼��ж�
	}
	}
	*/
	initial();

	while (window.isOpen() && isOver == false) {
		switch (inScene)
		{
		case 1://��ʼ����
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