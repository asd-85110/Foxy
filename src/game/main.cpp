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
#include"include/sprite.hpp"
#include<clocale>
int main(void)
{
    char game_play_type='s';
    setlocale(LC_ALL,"");
    bindtextdomain("game", "../locale");
    bind_textdomain_codeset("game", "UTF-8");
    textdomain("game");
    InitWindow(800, 600, "Foxy");
    InitAudioDevice();
    SetTargetFPS(60);
    Image icon=LoadImage("../res/Icon.png");
    SetWindowIcon(icon);
    Texture2D bg=LoadTexture("../res/Texture/background1.jpg");
    Music BGM=LoadMusicStream("../res/Sound/doodle_pop.ogg");
    Font F10=LoadFont("../res/Font/fusion-pixel-10px-monospaced-zh_hans.ttf"),
        F12=LoadFont("../res/Font/fusion-pixel-12px-monospaced-zh_hans.ttf");
    sprite::player Player(LoadTexture("../res/Texture/fox.png"),Vector2{400,300},1);
    bool moved;
    PlayMusicStream(BGM);
    GuiSetFont(F12);
    while (!WindowShouldClose())
    {
        UpdateMusicStream(BGM);
        moved=false;
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
        if(IsKeyDown(KEY_S)){
            Player.UpdateDirection(2);
            Player.animation(Player.walk);
            Player.position.y+=Player.speed*GetFrameTime()+1;
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
            DrawTexture(bg,0,0,WHITE);
            switch(game_play_type){
                case 's':
                    DrawText("Foxy",315,130,70,ORANGE);
                    if(GuiButton(Rectangle{350,250,100,50},gettext("Let's Play!"))){
                        game_play_type='r';
                    }
                    break;
                case 'r':
                    Player.Draw();
                    break;
                default:
                    break;
            }
            DrawText("v0.1.0",10,565,30,RAYWHITE);
        EndDrawing();
    }
    UnloadImage(icon);
    UnloadMusicStream(BGM);
    UnloadTexture(bg);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}