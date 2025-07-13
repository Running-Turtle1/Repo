package com.qust;

import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

import java.util.List;

import com.qust.Arrow;
import com.qust.IronBloodGame;

public class Shield implements MouseMotionListener {
    private int x, y; // 盾牌的位置
    private static final int WIDTH = 50, HEIGHT = 50; // 盾牌的大小
    private Image shieldImage; // 盾牌图片

    public Shield() {
        this.x = 400; // 初始化位置
        this.y = 300;
        loadShieldImage(); // 加载盾牌图片
    }

    // 加载盾牌图片
    private void loadShieldImage() {
        try {
            shieldImage = Toolkit.getDefaultToolkit().getImage("images\\shield.png");
        } catch (Exception e) {
            e.printStackTrace();
            shieldImage = null;
        }
    }

    // 绘制盾牌
    public void draw(Graphics g) {
        if (shieldImage != null) {
            g.drawImage(shieldImage, x, y, WIDTH, HEIGHT, null);
        } else {
            g.setColor(Color.BLUE);
            g.fillRect(x, y, WIDTH, HEIGHT); // 盾牌的默认绘制方式
        }
    }

    // 随鼠标移动更新盾牌位置
    @Override
    public void mouseMoved(MouseEvent e) {
        x = e.getX() - WIDTH / 2; // 使盾牌中心与鼠标对齐
        y = e.getY() - HEIGHT / 2;

        // 限制盾牌不超出边界
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x > 800 - WIDTH) x = 800 - WIDTH; // 假设窗口宽度为 800
        if (y > 600 - HEIGHT) y = 600 - HEIGHT; // 假设窗口高度为 600
    }

    @Override
    public void mouseDragged(MouseEvent e) {}

    // 检查盾牌与弓箭的碰撞
    public void checkCollisionWithArrow(List<Arrow> arrows, IronBloodGame game) {
        boolean flag = true;
        while (flag) {
            flag = false;
            for (int i = 0; i < arrows.size(); i++) {
                Arrow arrow = arrows.get(i);
                if (getBounds().intersects(arrow.getBounds())) {
                    arrows.remove(i); // 移除弓箭
                    flag = true;
                    break; // 只消除第一个碰撞的弓箭
                }
            }
        }

    }

    // 获取盾牌的边界矩形
    private Rectangle getBounds() {
        return new Rectangle(x, y, WIDTH, HEIGHT);
    }
}
