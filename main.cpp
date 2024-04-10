#include <SFML/Graphics.hpp>
#include <iostream>
#include <bits/stdc++.h>
#include <Windows.h>
#include "Head.h"
using namespace sf;
using namespace std;

const int L = 400;
const int alignx = 300;
const int aligny = 300;
sf::RenderWindow window(sf::VideoMode(1920, 1080), "20729 project");

int p;
int amp = 200;
vector<Verticies> V;

set<pair<int,int>>Line;

void projection(){
    sf::CircleShape point;
    sf::VertexArray line(sf::Lines,2);
    for(auto i:Line){

        Verticies p1 = V[i.first];
        Verticies p2 = V[i.second];
        double x1,x2,y1,y2;
        x1 = p1.x*amp;
        y1 = p1.y*amp;
        x2 = p2.x*amp;
        y2 = p2.y*amp;

        line[0].position = sf::Vector2f(x1+alignx,y1+aligny);
        line[1].position = sf::Vector2f(x2+alignx,y2+aligny);
        window.draw(line);
    }
    for(auto vert:V){
        double x,y;
            x = vert.x*amp;
            y = vert.y*amp;
            point.setRadius(5);
            point.setPosition(sf::Vector2f(x+alignx-5,y+aligny-5));
            window.draw(point);

    }
}
/*
void initcube(){
    int idx = 0;
    for(int i = 0;i<2;i++){
        for(int j = 0;j<2;j++){
            for(int k = 0;k<2;k++){
                V[idx].x = i*L;
                V[idx].y = j*L;
                V[idx].z = k*L;
                idx++;
            }
        }
    }
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[0].push_back(4);
    adj[7].push_back(6);
    adj[7].push_back(5);
    adj[7].push_back(3);
    adj[3].push_back(2);
    adj[3].push_back(1);
    adj[6].push_back(2);
    adj[6].push_back(4);
    adj[5].push_back(1);
    adj[5].push_back(4);

}
*/
void rotatex(float angle){
    float radian = angle / 180 * 3.14;
    for(int i = 0;i<p;i++){
        V[i].y = cos(radian)*V[i].y + sin(radian)*V[i].z*-1;
        V[i].z =  sin(radian)*V[i].y+cos(radian)*V[i].z;
    }
}
void rotatey(float angle){
    float radian = angle / 180 * 3.1415926;
    for(int i = 0;i<p;i++){
        V[i].x = cos(radian)*V[i].x + sin(radian)*V[i].z;
        V[i].z =  sin(radian)*V[i].x*-1+cos(radian)*V[i].z;
    }
}
void rotatez(float angle){
    float radian = angle / 180 * 3.14;
    for(int i = 0;i<p;i++){
        V[i].x = cos(radian)*V[i].x + sin(radian)*V[i].y*-1;
        V[i].y =  sin(radian)*V[i].x+cos(radian)*V[i].y;
    }
}
int main()
{


    //SetCube();
    //SetTriangle();
    //SetFlat();
    //SetRandom(15);
    //Setico();

    Text text;
    Font font;
    font.loadFromFile("Fonts/Party Confetti.ttf");


    string ask;
    cin>>ask;
    cout<<ask;
    if(ask == "Cube"){
        SetCube();
    }
    else if(ask == "Triangle"){
        SetTriangle();
    }
    else if(ask == "ico"){
        Setico();
    }
    else{
        SetRandom(stoi(ask));
    }

    GenerateOutLine();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        rotatex(1);
        rotatey(1);
        rotatez(1);
        //point.setPosition(0,0);
        //point.setRadius(100);
        //window.draw(point);
        projection();
        window.display();
        Sleep(10);
    }//end while true

    return 0;
} // end main





