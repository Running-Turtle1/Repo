package com.qust;

import javax.imageio.ImageIO;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.util.Random;

public class Soldier implements Runnable {
    private int x, y; // 士兵的坐标
    private int speed; // 士兵移动速度
    private Image soldierImage;
    private boolean outOfBounds;
    private Component parent;

    public Soldier(int x, int y, Component parent) {
        this.x = x;
        this.y = y;
        this.parent = parent;
        this.speed = 2 + new Random().nextInt(3); // 随机速度 2~4

        loadRandomImage(); // 加载随机士兵图片
        this.outOfBounds = false;
    }

    /**
     * 加载随机士兵图片
     */
    private void loadRandomImage() {
        try {
            String imagePath = new Random().nextBoolean() ? "images/soldier1.png" : "images/soldier2.png";
            soldierImage = ImageIO.read(new File(imagePath));
        } catch (IOException e) {
            e.printStackTrace();
            soldierImage = null;
        }
    }

    /**
     * 绘制士兵
     */
    public void draw(Graphics g) {
        if (soldierImage != null) {
            g.drawImage(soldierImage, x, y, 50, 50, null); // 固定士兵宽高为 50x50
        } else {
            g.setColor(Color.BLUE);
            g.fillRect(x, y, 50, 50); // 如果图片加载失败，则用矩形代替
        }
    }

    /**
     * 士兵移动逻辑
     */
    private void move() {
        x += speed; // 向右移动
        if (x > parent.getWidth()) {
            outOfBounds = true; // 判断是否出界
        }
    }

    /**
     * 判断士兵是否出界
     */
    public boolean isOutOfBounds() {
        return outOfBounds;
    }

    /**
     * 返回士兵边界模型，用于碰撞检测
     * @return
     */
    public Rectangle getBounds() {
        return new Rectangle(x, y, 50, 50); // 这里假设你已经有了 x 和 y 坐标
    }

    @Override
    public void run() {
        while (!outOfBounds) {
            move();
            try {
                Thread.sleep(30); // 每 30 毫秒移动一次
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


}
