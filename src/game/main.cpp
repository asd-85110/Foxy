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
#define RAYGUI_IMPLEMENTATION
#include<raylib.h>
#include<raygui.h>
#include<libintl.h>
#include<clocale>
#include"include/sprite.hpp"
#include"include/ev.hpp"
int main(void)
{
    ///\brief 初始化游戏模式
    char game_play_type='s';
    ///\brief 国际化配置
    setlocale(LC_ALL,"");
    bindtextdomain("game", "../locale");
    bind_textdomain_codeset("game", "UTF-8");
    textdomain("game");
    ///\brief 初始化游戏
    InitWindow(800, 600, "Foxy");
    InitAudioDevice();
    SetTargetFPS(60);
    Image icon=LoadImage("../res/Icon.png");
    SetWindowIcon(icon);
    Event::Init(LoadTexture("../res/Texture/UI_Lifebar_Border.png"),LoadTexture("../res/Texture/UI_Lifebar_Fill_02.png"),LoadTexture("../res/Texture/UI_Lifebar_Fill_01.png"));
    Music BGM=LoadMusicStream("../res/Sound/doodle_pop.ogg");
    Font F12=LoadFont("../res/Font/fusion-pixel-12px-monospaced-zh_hans.fnt");
    sprite::player Player(LoadTexture("../res/Texture/fox.png"),Vector2{376,268},255);
    sprite::BackGround bgs[2]={sprite::BackGround(LoadTexture("../res/Texture/background.jpg")),sprite::BackGround(LoadTexture("../res/Texture/FlowerSea.png"))};
    bool moved;
    PlayMusicStream(BGM);
    ///\brief GUI设置
    GuiSetStyle(DEFAULT,BASE_COLOR_FOCUSED,0xFFA100FF);
    GuiSetStyle(DEFAULT,BASE_COLOR_PRESSED,0xE62937FF);
    GuiSetStyle(DEFAULT,BORDER_COLOR_FOCUSED,0x7F5000FF);
    GuiSetStyle(DEFAULT,BORDER_COLOR_PRESSED,0x73141BFF);
    GuiSetFont(F12);
    while (!WindowShouldClose())
    {
        //更新游戏状态
        UpdateMusicStream(BGM);
        moved=false;
        if(game_play_type=='r'){
            if(IsKeyDown(KEY_S)&&!IsKeyDown(KEY_W)){
                Player.UpdateDirection(2);
                Player.animation(Player.walk);
                if(bgs[Event::scene].pos.y<=-(bgs[Event::scene].bg.height-600)){
                    bgs[Event::scene].pos.y=-(bgs[Event::scene].bg.height-600);
                    if(Player.position.y<(600-Player.h)){
                        Player.position.y+=Player.speed*GetFrameTime()+1;
                    }
                }else{
                    bgs[Event::scene].pos.y-=Player.speed*GetFrameTime()+1;;
                }
                moved=true;
            }
            if(IsKeyDown(KEY_W)&&!IsKeyDown(KEY_S)){
                Player.UpdateDirection(0);
                Player.animation(Player.walk);
                if(bgs[Event::scene].pos.y>=0){
                    bgs[Event::scene].pos.y=0;
                    if(Player.position.y>0){
                        Player.position.y-=Player.speed*GetFrameTime()+1;
                    }
                }else{
                    bgs[Event::scene].pos.y+=Player.speed*GetFrameTime()+1;;
                }
                moved=true;
            }
            if(IsKeyDown(KEY_D)&&!IsKeyDown(KEY_A)){
                Player.UpdateDirection(1);
                Player.animation(Player.walk);
                if(bgs[Event::scene].pos.x<=-(bgs[Event::scene].bg.width-800)){
                    bgs[Event::scene].pos.x=-(bgs[Event::scene].bg.width-800);
                    if(Player.position.x<800-Player.w){
                        Player.position.x+=Player.speed*GetFrameTime()+1;
                    }
                }else{
                    bgs[Event::scene].pos.x-=Player.speed*GetFrameTime()+1;;
                }
                moved=true;
            }
            if(IsKeyDown(KEY_A)&&!IsKeyDown(KEY_D)){
                Player.UpdateDirection(3);
                Player.animation(Player.walk);
                if(bgs[Event::scene].pos.x>=0){
                    bgs[Event::scene].pos.x=0;
                    if(Player.position.x>0){
                        Player.position.x-=Player.speed*GetFrameTime()+1;
                    }
                }else{
                    bgs[Event::scene].pos.x+=Player.speed*GetFrameTime()+1;;
                }
                moved=true;
            }
            if(!moved){
                Player.animation(Player.idle);
            }
            if(IsKeyDown(KEY_UP)&&Player.health<255){
                Player.health++;
            }
            if(IsKeyDown(KEY_DOWN)&&Player.health>0){
                Player.health--;
            }
        }
        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            switch(game_play_type){
                case 's':
                    DrawTexture(bgs[0].bg,0,0,WHITE);
                    DrawText("Foxy",315,130,70,ORANGE);
                    if(GuiButton(Rectangle{350,250,100,50},gettext("Let's Play!"))){
                        game_play_type='r';
                    }
                    if(GuiButton(Rectangle{350,310,100,50},gettext("Settings"))){
                        game_play_type='c';
                    }
                    if(GuiButton(Rectangle{350,370,100,50},gettext("Credits"))){
                        game_play_type='a';
                    }
                    DrawText("By asd-85110,made with Raylib",650,590,10,WHITE);
                    break;
                case 'r':
                    DrawTexture(bgs[Event::scene].bg,bgs[Event::scene].pos.x,bgs[Event::scene].pos.y,WHITE);
                    Player.Draw();
                    Event::DrawHealth(Vector2{10,10},Player.health);
                    break;
                case 'c':
                    DrawTexture(bgs[0].bg,0,0,WHITE);
                    break;
                case 'a':
                    DrawTexture(bgs[0].bg,0,0,WHITE);
                    DrawText("Fox.png - Stendhal",10,10,12,BLACK);
                    if(GuiButton(Rectangle{350,540,100,50},gettext("Back"))){
                        game_play_type='s';
                    }
                default:
                    break;
            }
            DrawText("v0.1.0",10,565,30,RAYWHITE);
        EndDrawing();
    }
    ///\brief 卸载并退出
    UnloadImage(icon);
    UnloadMusicStream(BGM);
    UnloadFont(F12);
    Event::Quit();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}