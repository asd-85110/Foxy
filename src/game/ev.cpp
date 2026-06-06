#include"include/ev.hpp"
namespace Event{
    Texture2D health_bar,health,health_fill;
    bool Init(Texture2D B,Texture2D H,Texture2D F){
        health_bar=B;
        health=H;
        health_fill=F;
        return true;
    }
    void Quit(){
        UnloadTexture(health_bar);
        UnloadTexture(health);
        UnloadTexture(health_fill);
    }
    void DrawHealth(Vector2 P){
        DrawTexture(health,P.x,P.y,WHITE);
        DrawTexture(health_fill,P.x,P.y,WHITE);
        DrawTexture(health_bar,P.x,P.y,WHITE);
    }
}