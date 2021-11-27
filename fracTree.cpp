#include<SFML/Graphics.hpp>

#include<SFML/Window.hpp>

#include <random>

#include<iostream>

#include<vector>

#include<assert.h>

#define PI 3.141592




class Line {
private:
    sf::RectangleShape shape;
public:
    Line(sf::Vector2f start, float rot, float len, float thick, sf::Color color, sf::RenderWindow& window) {
        shape = sf::RectangleShape(sf::Vector2f(len, thick));
        shape.setOrigin(sf::Vector2f(0, thick / 2.));
        shape.setRotation(rot);
        shape.setPosition(start);
        shape.setFillColor(color);
        window.draw(shape);
    }

    sf::Vector2f getEnd() {
        sf::Vertex a = shape.getTransform().transformPoint(shape.getPoint(1));
        sf::Vertex b = shape.getTransform().transformPoint(shape.getPoint(2));
        return sf::Vector2f((a.position.x + b.position.x) / 2, (a.position.y + b.position.y) / 2);
    }

    sf::Vector2f getStart() {
        return shape.getOrigin();
    }

    float getRot() {
        return shape.getRotation();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
};

void treeRecA(int n, float length, sf::Vector2f origin, float baseRot, float thick, sf::RenderWindow& window) {


    if (n == 0) {
        Line l1(origin, baseRot - 30, length * (4. / 5.), thick * (4. / 5.), sf::Color::Green, window);
        window.display();
        l1.draw(window);

        Line l2(origin, baseRot + 30, length * (4. / 5.), thick * (4. / 5.), sf::Color::Green, window);
        window.display();
        l2.draw(window);
    }
    else {
        Line l1(origin, baseRot - 30, length * (4. / 5.), thick * (4. / 5.), sf::Color::Red, window);
        window.display();
        l1.draw(window);
        treeRecA(n - 1, length * (4. / 5.), l1.getEnd(), baseRot - 30, thick * (4. / 5.), window);

        Line l2(origin, baseRot + 30, length * (4. / 5.), thick * (4. / 5.), sf::Color::Red, window);
        window.display();
        l2.draw(window);
        treeRecA(n - 1, length * (4. / 5.), l2.getEnd(), baseRot + 30, thick * (4. / 5.), window);
    }
}

void treeRecB(int n, float length, std::vector<Line> couche, float thick, sf::RenderWindow& window) {
    float rFac = (4. / 5.);
    float rot = 30;

    std::vector<Line> newCouche;

    if (n == 0) {
        for (Line l : couche) {
            Line l1(l.getEnd(), l.getRot() - rot, length * rFac, thick * rFac, sf::Color::Green, window);
            window.display();
            l1.draw(window);

            Line l2(l.getEnd(), l.getRot() + rot, length * rFac, thick * rFac, sf::Color::Green, window);
            window.display();
            l2.draw(window);
        }
    }
    else {
        for (Line l : couche) {
            Line l1(l.getEnd(), l.getRot() - rot, length * rFac, thick * rFac, sf::Color::Red, window);
            window.display();
            l1.draw(window);
            newCouche.push_back(l1);

            Line l2(l.getEnd(), l.getRot() + rot, length * rFac, thick * rFac, sf::Color::Red, window);
            window.display();
            l2.draw(window);
            newCouche.push_back(l2);
        }

        treeRecB(n - 1, length * rFac, newCouche, thick * rFac, window);
    }
}





int main() {

    sf::Time deltaTime;
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "o.o");

    sf::Event ev;


    sf::Font arial;
    assert(arial.loadFromFile("font/arial.ttf"), "cant load font");

    sf::Text fps("FPS: 0", arial, 15);
    fps.setFillColor(sf::Color::White);
    window.clear(sf::Color::Black);

    Line trunk(sf::Vector2f(960, 1080), -90, 200, 17, sf::Color::Red, window);
    window.display();
    trunk.draw(window);
    //std::vector<Line> couche{trunk};

    clock.restart();
    treeRecA(12, 200 * (4. / 5.), trunk.getEnd(), -90, 17 * (4. / 5.), window);
    deltaTime = clock.restart();

    //treeRecB(15, 200*(4./5.), couche, 17*(4./5.), window);

    std::cout << deltaTime.asSeconds() << " s" << std::endl;
    std::cout << deltaTime.asMilliseconds() << " ms" << std::endl;

    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::EventType::Closed) {
                window.close();
            }
        }


    }

}