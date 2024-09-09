#pragma once

class CheckDevice;
class ControlSound;

class Title
{
private:
    int select;         //�I����
    int titleImg;       //�^�C�g���摜
    int menuTextImg;    //���j���[��ʂ̃e�L�X�g�摜
    bool pushFlg;       //�A���ŉ����Ȃ��悤�ɂ��邽�߂̃t���O
public:
    Title();
    ~Title();
    void selectCommand(int& scene,CheckDevice checkDevice,ControlSound& sound);     //�I��������

    //�Q�b�^�[�֐�
    int getSelectCommand() { return select; }
    int getTitleImg() { return titleImg; }
    int getMenuTextImg() { return menuTextImg; }
};

