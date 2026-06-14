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
    Texture2D bg=LoadTexture("../res/Texture/background.jpg");
    Music BGM=LoadMusicStream("../res/Sound/doodle_pop.ogg");
    Font F12=LoadFont("../res/Font/fusion-pixel-12px-monospaced-zh_hans.fnt");
    sprite::player Player(LoadTexture("../res/Texture/fox.png"),Vector2{400,300},1);
    bool moved;
    PlayMusicStream(BGM);
    GuiSetFont(F12);
    while (!WindowShouldClose())
    {
        UpdateMusicStream(BGM);
        moved=false;
        if(IsKeyDown(KEY_S)){
            Player.UpdateDirection(2);
            Player.animation(Player.walk);
            Player.position.y+=Player.speed*GetFrameTime()+1;
            moved=true;
        }
        if(IsKeyDown(KEY_W)){
            Player.UpdateDirection(0);
            Player.animation(Player.walk);
            Player.position.y-=Player.speed*GetFrameTime()+1;
            moved=true;
        }
        if(IsKeyDown(KEY_D)){
            Player.UpdateDirection(1);
            Player.animation(Player.walk);
            Player.position.x+=Player.speed*GetFrameTime()+1;
            moved=true;
        }
        if(IsKeyDown(KEY_A)){
            Player.UpdateDirection(3);
            Player.animation(Player.walk);
            Player.position.x-=Player.speed*GetFrameTime()+1;
            moved=true;
        }
        if(!moved){
            Player.animation(Player.idle);
        }
        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            switch(game_play_type){
                case 's':
                DrawTexture(bg,0,0,WHITE);
                    DrawText("Foxy",315,130,70,ORANGE);
                    if(GuiButton(Rectangle{350,250,100,50},gettext("Let's Play!"))){
                        game_play_type='r';
                    }
                    if(GuiButton(Rectangle{350,310,100,50},gettext("Settings"))){}
                    if(GuiButton(Rectangle{350,370,100,50},gettext("Credits"))){
                        game_play_type='a';
                    }
                    break;
                case 'r':
                    Player.Draw();
                    Event::DrawHealth(Vector2{10,10},Player.health);
                    break;
                case 'a':
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
    UnloadTexture(bg);
    UnloadFont(F12);
    Event::Quit();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}