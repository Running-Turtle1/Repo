package com.qust;

import com.qust.IronBloodGame;
import com.qust.Soldier;

import javax.imageio.ImageIO;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class Arrow implements Runnable {
    private static final int SPEED = 5; // 弓箭移动速度
    private int x; // 弓箭的 x 坐标
    private int y; // 弓箭的 y 坐标
    private Image arrowImage; // 弓箭图片
    private IronBloodGame game; // 游戏主面板
    private boolean outOfBounds; // 是否超出边界
    private boolean stopped; // 弓箭是否被拦截

    public Arrow(IronBloodGame game, int startX, int startY) {
        this.game = game;
        this.x = startX;
        this.y = startY;
        this.outOfBounds = false;
        this.stopped = false;
        loadArrowImage();
    }

    /**
     * 加载弓箭图片
     */
    private void loadArrowImage() {
        try {
            arrowImage = ImageIO.read(new File("images\\arrow.png"));
        } catch (IOException e) {
            e.printStackTrace();
            arrowImage = null;
        }
    }

    /**
     * 绘制弓箭
     */
    public void draw(Graphics g) {
        if (arrowImage != null) {
            g.drawImage(arrowImage, x, y,null);
        }
    }

    /**
     * 弓箭移动逻辑
     */
    public void move() {
        if (!stopped) {
            x -= SPEED; // 向左移动
            y ++;

            if (x + getWidth() < 0) { // 判断是否超出屏幕左侧边界
                outOfBounds = true;
            }
        }
    }

    /**
     * 获取弓箭的边界矩形
     */
    public Rectangle getBounds() {
        return new Rectangle(x, y, getWidth(), getHeight());
    }

    public int getWidth() {
        return arrowImage != null ? arrowImage.getWidth(null) : 0;
    }

    public int getHeight() {
        return arrowImage != null ? arrowImage.getHeight(null) : 0;
    }

    public boolean isOutOfBounds() {
        return outOfBounds;
    }

    public void stop() {
        stopped = true;
    }

    @Override
    public void run() {
        while (!outOfBounds && !stopped) {
            move();
            checkCollision();
            try {
                Thread.sleep(30); // 控制移动速度
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 检查弓箭与士兵的碰撞
     */
    private boolean collided = false;
    private void checkCollision() {
        if (collided) return; // 如果已经碰撞，直接返回
        for (int i = 0; i < game.getSoldiers().size(); i++) {
            Soldier soldier = game.getSoldiers().get(i);
            if (getBounds().intersects(soldier.getBounds())) {
                game.soldierHit(soldier); // 士兵被击中
                game.getArrows().remove(this); // 移除弓箭
                collided = true; // 标记为已碰撞
                return;
            }
        }
    }
}