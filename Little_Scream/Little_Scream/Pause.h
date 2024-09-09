#pragma once

class CheckDevice;
class ControlSound;

class Pause
{
private:
    int select;             //�I��
    int pauseTextImg;       //�|�[�Y�e�L�X�g�摜
    bool pushFlg;           //�A���ŉ����Ȃ��悤�ɂ��邽�߂̃t���O
    bool pushEscapeKeyFlg;  //�G�X�P�[�v�L�[�����������ǂ���
    bool resetFlg;          //���Z�b�g���邩
public:
    Pause();
    ~Pause();
    void initialize();  //������
    void selectCommand(int& scene,CheckDevice checkDevice, ControlSound& sound);    //�I��������
    void controlPauseKey(int& scene, CheckDevice checkDevice, ControlSound& sound); //�|�[�Y�L�[�������ꂽ�Ƃ��̏���

    //�Q�b�^�[�֐�
    int getSelectCommand() { return select; }
    int getPauseText() { return pauseTextImg; }
    bool getResetFlg() { return resetFlg; }
};

