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
#pragma once
#ifndef SPRITE_HPP
#define SPRITE_HPP
#include<raylib.h>
#include<vector>
#include<string>
#include<cstdint>
namespace sprite{
    struct item{
        Texture2D texture;/// \brief 纹理对象
        Rectangle bounds={0,0,16,16};/// \brief 纹理边界框
        std::string name;/// \brief 纹理名称
        /**
         * \param t 纹理对象
         * \param n 纹理名称
         * \brief 纹理对象构造函数
         * \note 纹理边界框默认为16x16大小，可根据实际情况修改。
        */
        item(Texture2D t,std::string n);
        ~item();
    };
    class player{
    private:
        //Frame w=48,h=64
        Vector2 Frame={0,0};// 纹理帧位置.[0]行,[1]列
        ///\brief 纹理对象
        Texture2D texture;
        /// \brief 纹理边界框
        Rectangle bounds={0,0,48,64};
        /// \brief 玩家经验值
        std::uint64_t xp;
        /// \brief 玩家携带物品列表
        std::vector<item> carry_things;
        /// \brief 帧率，用于控制动画速度
        const float FrameSpeed=0.125;
        /// \brief 计时器，用于控制动画帧率
        float timer=0;
    public:
        /// \brief 玩家属性
        std::uint8_t health,speed,damge;
        std::uint16_t h,w;
        /// \brief 玩家位置
        Vector2 position;
        enum tags{
            idle=0,// 枚举空闲标签
            walk=1,// 枚举行走标签(有动画)
            attack=2,// 枚举攻击标签(无动画)
            dead=3// 枚举玩家死亡标签
        };
        /**
         * \param t 状态枚举
         * \brief 玩家动画处理函数
         * \note 根据枚举标签进行动画处理
        */
        void animation(tags);
        /**
         * \param f 纹理帧位置
         * \brief 玩家绘制函数
         * \note 绘制玩家纹理，并根据纹理帧位置进行偏移。
        */
        void Draw();
        /**
         * \param d 玩家移动方向
         * \brief 玩家方向函数
        */
        void UpdateDirection(std::uint16_t);
        /**
         * \param t 纹理对象
         * \param p 玩家位置
         * \brief 玩家构造函数
        */
        player(Texture2D,Vector2,std::uint8_t);
        /**
         * \brief 玩家析构函数
         * \note 卸载纹理对象资源
         * \note 纹理对象资源卸载必须在玩家析构函数中进行，否则会造成内存泄漏。
        */
        ~player();
    };
    struct BackGround{
        ///\brief 背景纹理
        Texture2D bg;
        ///\brief 坐标状态
        Vector2 pos;
        BackGround(Texture2D);
        ~BackGround();
    };
}
#endif