package org.example;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Pairwise {

    public static void main(String[] args) {
        // 定义每个输入点 的取值
        int[][] parameters = {
                {1, 2, 3, 4},    // 输入点 1: 4个取值
                {1, 2, 3},       // 输入点 2: 3个取值
                {1, 2, 3},       // 输入点 3: 3个取值
                {1, 2},          // 输入点 4: 2个取值
                {1, 2, 3, 4, 5}  // 输入点 5: 5个取值
        };

        List<int[]> testCases = generateMinimalPairwiseTestCases(parameters);
        int cnt=0;
        for (int[] testCase : testCases) {
            cnt++;
            System.out.print("测试用例 "+String.valueOf(cnt)+" : ");
            for (int value : testCase) {
                System.out.print(value + " ");
            }
            System.out.println();
        }
        System.out.println("总测试用例数" + testCases.size());
    }

    public static List<int[]> generateMinimalPairwiseTestCases(int[][] parameters) {
        List<int[]> testCases = new ArrayList<>();
        Set<String> coveredPairs = new HashSet<>();  //已经覆盖的组合  set自动去重

        /** 先求出 所有的组合 */
        List<int[]> allCombinations = new ArrayList<>();
        generateAllCombinations(0, new int[parameters.length], parameters, allCombinations);
//        System.out.println(">>>>"+allCombinations.size());


        /**  计算所有参数对的组合数 **/
        int sum= requiredPairsCount(parameters);
//        System.out.println("sum=="+sum);
        // 循环直到所有可能的对都被覆盖
        while (coveredPairs.size() < sum) { //保证所有 参数对的组合 都至少被覆盖一次
            int maxCovered = 0;
            int[] bestCombination = null;

            for (int[] combination : allCombinations) {
                int covered = countNewPairs(coveredPairs, combination, parameters);
                if (covered > maxCovered) { //找到能够 新覆盖最多的
                    maxCovered = covered;
                    bestCombination = combination;
                }
            }

            if (bestCombination != null) {  // 找到了新覆盖最多的 加入最终的测试集
                testCases.add(bestCombination);
                updateCoveredPairs(coveredPairs, bestCombination, parameters);  //更新已经覆盖的组合
            }
        }

        return testCases;
    }

    private static void generateAllCombinations(int depth, int[] current, int[][] parameters, List<int[]> results) {
        if (depth == parameters.length) {
            results.add(current.clone());
            return;
        }
        for (int value : parameters[depth]) {
            current[depth] = value;
            generateAllCombinations(depth + 1, current, parameters, results);
        }
    }

    private static int requiredPairsCount(int[][] parameters) {
        int count = 0;
        for (int i = 0; i < parameters.length; i++) {
            for (int j = i + 1; j < parameters.length; j++) {
                count += parameters[i].length * parameters[j].length;
            }
        }
        return count;
    }

    //计算可以新覆盖组合的个数
    private static int countNewPairs(Set<String> coveredPairs, int[] combination, int[][] parameters) {
        int count = 0;
        for (int i = 0; i < parameters.length; i++) {
            for (int j = i + 1; j < parameters.length; j++) {
                String pair = i + "-" + j + ":" + combination[i] + "-" + combination[j];
                if (!coveredPairs.contains(pair)) {
                    count++;
                }
            }
        }
        return count;
    }

    //更新已覆盖集合
    private static void updateCoveredPairs(Set<String> coveredPairs, int[] combination, int[][] parameters) {
        for (int i = 0; i < parameters.length; i++) {
            for (int j = i + 1; j < parameters.length; j++) {
                String pair = i + "-" + j + ":" + combination[i] + "-" + combination[j];
                coveredPairs.add(pair); //加入已经覆盖的集合中
            }
        }
    }
}
