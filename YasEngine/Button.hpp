#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "GameObject.hpp"
#include<string>

class Button: public GameObject {
    public:
        enum ButtonId {

            RESTART_START,
            QUIT,
            NONE
        };

        std::string text;
        int buttonWidth;
        int buttonTextWidth;
        int buttonHeight;
        int verticalMargin;
        int horizontalMargin;

        ButtonId buttonId;

        Button(const ButtonId& buttonId, std::string text, const Vector4D<Uint8>& color);
        ~Button();

        void generate() override;
        void generateRegularPolygonVertices(float circumscribedCircleRadius, int numberOfVertices) override;
        void regeneratePolygon() override;
        void move(float deltaTime) override;

    void setPosition(float x, float y) {

        GameObject::setPosition(x, y);
    }

    void setPosition(const Vector2D<float>& position) {

        GameObject::setPosition(position);
    }
};

#endif //BUTTON_HPP
