package com.qust.proxy_;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

/**
 * 类的作用 ：
 *  创建一个代理
 */


public class ProxyUtil {

    /**
     * 方法的作用 : 创建一个代理
     * @param bigStar
     * 返回值 :
     *  给 BigStar 创建的代理
     */
    public static Star createProxy(BigStar bigStar) {
        /**
         * java.lang.reflect.Proxy类 ：提供了为对象产生代理对象的方法
         * public static Object newProxyInstance(ClassLoader loader, Class<?>[] interfaces, InvocationHandler h)
         * 参数一 : 用于指定哪个类加载器
         * 参数二 : 指定接口，这些接口用于指定生成的代理长什么样，也就是有哪些方法
         * 参数三 ：指定生成的代理对象要干什么事情
         */
        Star star = (Star) Proxy.newProxyInstance(
                BigStar.class.getClassLoader(),
                new Class[]{Star.class},
                new InvocationHandler() {
                    @Override
                    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
                        if("sing".equals(method.getName())) {
                            System.out.println("准备话筒，收钱");
                        }
                        else if("dance".equals(method.getName())) {
                            System.out.println("准备场地，收钱");
                        }

                        return method.invoke(bigStar, args);

                    }
                }
        );

        return star;
    }

}
