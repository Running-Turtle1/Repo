package com.qust;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import com.qust.Shield;

public class IronBloodGame extends JPanel implements ActionListener, MouseMotionListener {
    private List<Soldier> soldiers;
    private List<Arrow> arrows; // 存储弓箭的列表
    private Timer gameTimer;
    private Timer soldierSpawnTimer;
    private Image backgroundImage;
    private int soldierCount; // 当前士兵数量
    private static final int MAX_SOLDIERS = 10; // 最大士兵数量
    private Shield shield; // 盾牌对象
    private boolean gameOver; // 游戏失败标志
    private boolean gameWon; // 游戏胜利标志
    private int spawnCount;
    private int wonCount = 0;


    public IronBloodGame() {
        soldiers = new ArrayList<>();
        arrows = new ArrayList<>(); // 初始化弓箭列表
        loadImages(); // 加载背景图片
        setFocusable(true);
        addMouseMotionListener(this);

        shield = new Shield(); // 创建盾牌

        // 游戏刷新定时器，每 16 毫秒刷新一次
        gameTimer = new Timer(16, this);
        gameTimer.start();

        // 士兵生成定时器，随机 1~3 秒生成一个士兵
        soldierSpawnTimer = new Timer(getRandomInterval(), e -> spawnSoldier());
        soldierSpawnTimer.start();

        spawnCount = 0;
        soldierCount = 0; // 初始化士兵数量为 0
        wonCount = 0; // 冲入敌营的士兵
        gameOver = false; // 初始化游戏为未结束
        gameWon = false; // 初始化游戏未胜利
    }

    /**
     * 加载背景图片
     */
    private void loadImages() {
        try {
            backgroundImage = ImageIO.read(new File("images/img.png"));
        } catch (IOException e) {
            e.printStackTrace();
            backgroundImage = null;
        }
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        if (backgroundImage != null) {
            g.drawImage(backgroundImage, 0, 0, getWidth(), getHeight(), null);
        }

        // 绘制士兵
        for (Soldier soldier : soldiers) {
            soldier.draw(g);
        }

        // 绘制弓箭
        for (Arrow arrow : arrows) {
            arrow.draw(g);
        }

        shield.draw(g); // 绘制盾牌
    }

    private void spawnSoldier() {
        if (soldierCount < MAX_SOLDIERS) {
            Soldier soldier = new Soldier(0, getHeight() / 2 + new Random().nextInt(100) - 50, this); // 士兵初始位置
            soldiers.add(soldier);
            soldierCount++;
            spawnCount ++;

            new Thread(soldier).start(); // 启动士兵线程
        } else {
            soldierSpawnTimer.stop(); // 停止生成士兵
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        // 更新士兵位置
        for (int i = 0; i < soldiers.size(); i++) {
            Soldier soldier = soldiers.get(i);
            if (soldier.isOutOfBounds()) {
                soldiers.remove(i);
                i--;
                wonCount ++;
            }
        }

        // 检查是否有超过 3 个士兵越过边界，触发游戏胜利
//        long soldiersOutOfBounds = soldiers.stream().filter(Soldier::isOutOfBounds).count();
        if (wonCount >= 3 && !gameWon) {
            gameWon = true;
            JOptionPane.showMessageDialog(this, "游戏胜利！", "胜利", JOptionPane.INFORMATION_MESSAGE);
        }

        // 检查是否所有士兵生成完毕且士兵数量为 0，触发游戏失败
        if (spawnCount == 10 && soldiers.isEmpty() && !gameOver) {
            gameOver = true;
            JOptionPane.showMessageDialog(this, "游戏失败！", "失败", JOptionPane.INFORMATION_MESSAGE);
        }

        // 更新弓箭的移动逻辑
        for (int i = 0; i < arrows.size(); i++) {
            Arrow arrow = arrows.get(i);
            arrow.move();
            if (arrow.isOutOfBounds()) {
                arrows.remove(i);
                i--;
            }
        }

        // 定时生成弓箭，从屏幕右侧发射
        if (Math.random() < 0.03) { // 控制箭生成的概率
            Arrow arrow = new Arrow(this, getWidth(), (int) (Math.random() * getHeight()));
            addArrow(arrow);
        }

        shield.checkCollisionWithArrow(arrows, this); // 检查盾牌与弓箭的碰撞

        repaint();
    }

    /**
     * 添加弓箭
     */
    public void addArrow(Arrow arrow) {
        arrows.add(arrow);
        new Thread(arrow).start(); // 启动弓箭线程
    }

    /**
     *
     * @return 返回 1~3 秒的随机间隔, 用于士兵生成
     */
    private int getRandomInterval() {
        return 1000 + new Random().nextInt(2000);
    }

    public List<Soldier> getSoldiers() {
        return soldiers;
    }

    public List<Arrow> getArrows() {
        return arrows;
    }

    public void soldierHit(Soldier soldier) {
        soldiers.remove(soldier); // 将士兵移除
        soldierCount--; // 更新士兵数量
    }



    @Override
    public void mouseDragged(MouseEvent e) {
    }

    @Override
    public void mouseMoved(MouseEvent e) {
        shield.mouseMoved(e); // 让盾牌跟随鼠标移动
    }


    public static void main(String[] args) {
        JFrame frame = new JFrame("Iron Blood Game");
        IronBloodGame gamePanel = new IronBloodGame();
        frame.add(gamePanel);
        frame.setSize(800, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}