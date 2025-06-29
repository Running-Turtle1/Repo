package org.example;

import java.util.*;

public class LL1Parser {
    private static final Map<String, List<String[]>> grammar = new HashMap<>();
    private static final Map<String, Set<String>> first = new HashMap<>();
    private static final Map<String, Set<String>> follow = new HashMap<>();
    private static final Map<String, Map<String, String[]>> parsingTable = new HashMap<>();

    public static void main(String[] args) {
        initializeGrammar();
        computeFirstSets();
        computeFollowSets();
        constructParsingTable();

        // 指定输入字符串
        String[] input = {"i", "+", "i", "*", "i", "$"};

        parseInput(input);
    }

    private static void initializeGrammar() {
        grammar.put("E", Arrays.<String[]>asList(new String[]{"T", "E'"}));
        grammar.put("E'", Arrays.<String[]>asList(new String[]{"+", "T", "E'"}, new String[]{"ε"}));
        grammar.put("T", Arrays.<String[]>asList(new String[]{"F", "T'"}));
        grammar.put("T'", Arrays.<String[]>asList(new String[]{"*", "F", "T'"}, new String[]{"ε"}));
        grammar.put("F", Arrays.<String[]>asList(new String[]{"(", "E", ")"}, new String[]{"i"}));
    }

    private static void computeFirstSets() {
        for (String nonTerminal : grammar.keySet()) {
            first.put(nonTerminal, new HashSet<>());
        }

        boolean changed;
        do {
            changed = false;
            for (String nonTerminal : grammar.keySet()) {
                for (String[] production : grammar.get(nonTerminal)) {
                    int originalSize = first.get(nonTerminal).size();
                    Set<String> firstSet = computeFirstOfString(production);
                    first.get(nonTerminal).addAll(firstSet);
                    if (first.get(nonTerminal).size() > originalSize) {
                        changed = true;
                    }
                }
            }
        } while (changed);
    }

    private static Set<String> computeFirstOfString(String[] production) {
        Set<String> resultSet = new HashSet<>();
        for (String symbol : production) {
            if (!grammar.containsKey(symbol)) {
                resultSet.add(symbol);
                break;
            }
            Set<String> firstSet = first.get(symbol);
            resultSet.addAll(firstSet);
            if (!firstSet.contains("ε")) {
                break;
            }
        }
        return resultSet;
    }

    private static void computeFollowSets() {
        for (String nonTerminal : grammar.keySet()) {
            follow.put(nonTerminal, new HashSet<>());
        }
        follow.get("E").add("$");

        boolean changed;
        do {
            changed = false;
            for (String nonTerminal : grammar.keySet()) {
                for (String[] production : grammar.get(nonTerminal)) {
                    for (int i = 0; i < production.length; i++) {
                        String symbol = production[i];
                        if (!grammar.containsKey(symbol)) {
                            continue;
                        }
                        int originalSize = follow.get(symbol).size();
                        Set<String> followSet = computeFollowOfSymbol(nonTerminal, production, i);
                        follow.get(symbol).addAll(followSet);
                        if (follow.get(symbol).size() > originalSize) {
                            changed = true;
                        }
                    }
                }
            }
        } while (changed);
    }

    private static Set<String> computeFollowOfSymbol(String nonTerminal, String[] production, int index) {
        Set<String> resultSet = new HashSet<>();
        for (int i = index + 1; i < production.length; i++) {
            String symbol = production[i];
            if (!grammar.containsKey(symbol)) {
                resultSet.add(symbol);
                break;
            }
            Set<String> firstSet = first.get(symbol);
            resultSet.addAll(firstSet);
            if (!firstSet.contains("ε")) {
                resultSet.remove("ε");
                break;
            }
        }
        if (index == production.length - 1 || resultSet.contains("ε")) {
            resultSet.addAll(follow.get(nonTerminal));
        }
        resultSet.remove("ε");
        return resultSet;
    }

    private static void constructParsingTable() {
        for (String nonTerminal : grammar.keySet()) {
            parsingTable.put(nonTerminal, new HashMap<>());
            for (String[] production : grammar.get(nonTerminal)) {
                Set<String> firstSet = computeFirstOfString(production);
                for (String terminal : firstSet) {
                    if (!terminal.equals("ε")) {
                        parsingTable.get(nonTerminal).put(terminal, production);
                    }
                }
                if (firstSet.contains("ε")) {
                    Set<String> followSet = follow.get(nonTerminal);
                    for (String terminal : followSet) {
                        parsingTable.get(nonTerminal).put(terminal, production);
                    }
                }
            }
        }
    }

    private static void parseInput(String[] input) {
        Stack<String> stack = new Stack<>();
        stack.push("$");
        stack.push("E");

        int index = 0;
        int step = 1;

        System.out.printf("%-10s%-30s%-30s%-30s%n", "步骤", "分析栈", "剩余输入串", "推导所用产生式或匹配");

        while (!stack.isEmpty()) {
            String top = stack.peek();
            String current = input[index];

            System.out.printf("%-10d%-30s%-30s", step++, stack, Arrays.toString(Arrays.copyOfRange(input, index, input.length)));

            if (top.equals(current)) {
                stack.pop();
                index++;
                System.out.printf("%-30s%n", "匹配 " + current);
            } else if (grammar.containsKey(top)) {
                String[] production = parsingTable.get(top).get(current);
                if (production == null) {
                    System.out.println("Error: No production found for " + top + " with input " + current);
                    return;
                }
                stack.pop();
                for (int i = production.length - 1; i >= 0; i--) {
                    if (!production[i].equals("ε")) {
                        stack.push(production[i]);
                    }
                }
                System.out.printf("%-30s%n", top + " -> " + String.join(" ", production));
            } else {
                System.out.println("Error: Unexpected symbol " + current);
                return;
            }
        }

        if (index == input.length && stack.isEmpty()) {
            System.out.println("接受");
        } else {
            System.out.println("拒绝");
        }
    }
}
