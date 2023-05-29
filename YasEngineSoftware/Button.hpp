#include "GameObject.hpp"

#ifndef BUTTON_HPP
#define BUTTON_HPP

class Button: public GameObject
{
    public:
        enum ButtonId
        {
            RESTART_START,
            QUIT
        };

        std::string text;
        int buttonWidth;
        int buttonTextWidth;
        int buttonHeight;
        int verticalMargin;
        int horizontalMargin;

        ButtonId buttonId;

        Button(const ButtonId& buttonId, std::string text);

        void generate() override;
        void generateRegularPolygonVertices(float circumscribedCircleRadius, int numberOfVertices) override;
        void regeneratePolygon() override;
        void move(float deltaTime) override;
};

#endif //BUTTON_HPP
