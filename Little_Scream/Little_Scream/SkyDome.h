#pragma once

class Player;

class SkyDome
{
private:
    int model;      //�X�J�C�h�[�����f��

public:
    SkyDome();
    ~SkyDome();
    void setPosition(Player player);    //���W���Z�b�g

    //�Q�b�^�[�֐�
    int getModel() { return model; }
};

