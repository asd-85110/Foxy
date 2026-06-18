/*
*Game:Foxy
*Copyright (C) 2026~2028 asd-85110
*This program is free software: you can redistribute it and/or modify
*it under the terms of the GNU General Public License as published by
*the Free Software Foundation, either version 3 of the License, or
*(at your option) any later version.
*This program is distributed in the hope that it will be useful,
*but WITHOUT ANY WARRANTY; without even the implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*GNU General Public License for more details.
*You should have received a copy of the GNU General Public License
*along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include"include/sprite.hpp"
namespace sprite{
    player::player(Texture2D t,Vector2 p,std::uint8_t h){
        texture=t;
        position=p;
        health=h;
    }
    player::~player(){
        UnloadTexture(texture);
    }
    void player::animation(tags t){
        switch(t){
            case idle:
                Frame.x=1;
                break;
            case walk:
                timer+=GetFrameTime();
                if(timer>=FrameSpeed){
                    Frame.x+=1;
                    if(Frame.x>2){
                        Frame.x=0;
                    }
                    timer-=FrameSpeed;
                }
                break;
            default:
                break;
        }
        return;
    }
    void player::Draw(){
        DrawTexturePro(texture,Rectangle{Frame.x*48,Frame.y*64,48,64},Rectangle{position.x,position.y,48,64},Vector2{0,0},0,WHITE);
    }
    void player::UpdateDirection(std::uint16_t d){
        Frame.y=d;
    }
    item::item(Texture2D t,std::string n){
        texture=t;
    }
    item::~item(){
        UnloadTexture(texture);
    }
};