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
#include"include/ev.hpp"
namespace Event{
    Texture2D health_bar,health,health_fill;
    Texture2D Recycles;
    const Rectangle Recycle[16]={
        {2,17,15,45},//矿泉水瓶
        {19,7,39,55},//大洗衣液桶
        {60,18,36,44},//小洗衣液桶
        {98,14,51,48},//纸箱
        {151,34,53,28},//报纸
        {206,16,35,46},//包装袋
        {243,12,17,50},//酒瓶
        {262,67,23,35},//玻璃罐
        {283,17,16,49},//玻璃瓶
        {305,32,23,30},//小罐头
        {330,22,21,40},//大罐头
        {353,28,18,34},//铝罐
        {373,17,28,45},//纸杯
        {403,32,60,30},//披萨盒
        {465,36,29,26},//破陶瓷杯
        {496,22,17,40}//喷漆瓶
    };
    int scene=S_FLOWER_SEA;
    bool Init(Texture2D B,Texture2D H,Texture2D F){
        if(IsTextureValid(B)&&IsTextureValid(H)&&IsTextureValid(F)){
            health_bar=B;
            health=H;
            health_fill=F;
        }else{
            return false;
        }
        Recycles=LoadTexture("../res/Texture/recycle_items.png");
        return IsTextureValid(Recycles);
    }
    void Quit(){
        UnloadTexture(health_bar);
        UnloadTexture(health);
        UnloadTexture(health_fill);
        UnloadTexture(Recycles);
    }
    void DrawHealth(Vector2 P,std::uint8_t H){
        DrawTexture(health,P.x,P.y,WHITE);
        DrawTextureRec(health_fill,Rectangle{0,0,(float)(((float)(H)/255*100)+5),32},P,WHITE);
        DrawTexture(health_bar,P.x,P.y,WHITE);
    }
}