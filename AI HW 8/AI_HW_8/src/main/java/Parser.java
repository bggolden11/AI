import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Parser {

    public MDP parse() throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("src/main/resources/mdp_input.txt"));
        String line;
        int sizeX = -1;
        int sizeY = -1;
        List<Point> walls = new ArrayList<>();
        List<TerminalState> terminalStates = new ArrayList<>();
        double rewardInNonTerminalStates = -1;
        List<Double> transitionProbabilities = new ArrayList<>();
        double discountRate = -1;;
        double epsilon = -1;

        while ((line = br.readLine()) != null) {

            if (!line.isEmpty() && line.charAt(0) != '#') {
                String leftSide = line.split(":")[0];
                String rightSide = line.split(":")[1];

                if (leftSide.contains("size")) {
                    List<String> parsed = Arrays.asList(rightSide.split(" "));
                    for (String x : parsed) {
                        if (x != null && !x.isEmpty()) {
                            if (sizeX == -1) sizeX = Integer.parseInt(x);
                            else if (sizeY == -1) {
                                sizeY = Integer.parseInt(x);
                            }
                        }
                    }
                } else if (leftSide.contains("walls")) {
                    List<String> splitByComma = Arrays.asList(rightSide.split(","));
                    for (String x : splitByComma) {
                        Point point = new Point();
                        List<String> parsed = Arrays.asList(x.split(" "));
                        for (String p : parsed) {
                            if (p != null && !p.isEmpty()) {
                                point.setPoint(Integer.parseInt(p));
                            }
                        }
                        walls.add(point);
                    }
                } else if (leftSide.contains("terminal_states")) {
                    List<String> splitByComma = Arrays.asList(rightSide.split(","));
                    for (String x : splitByComma) {
                        List<String> parsed = Arrays.asList(x.split(" "));
                        TerminalState states = new TerminalState();
                        states.setStates(parsed);
                        terminalStates.add(states);
                    }
                } else if (leftSide.contains("reward")) {
                    rewardInNonTerminalStates = Double.parseDouble(rightSide);
                } else if (leftSide.contains("transition_probabilities")) {
                    List<String> parsed = Arrays.asList(rightSide.split(" "));
                    for (String p : parsed) {
                        if (!p.isEmpty()) {
                            transitionProbabilities.add(Double.parseDouble(p));
                        }
                    }
                } else if (leftSide.contains("discount_rate")) {
                    discountRate = Double.parseDouble(rightSide);
                } else if (leftSide.contains("epsilon")) {
                    epsilon = Double.parseDouble(rightSide);
                }
            }
        }
        br.close();

        return new MDP(sizeX,sizeY,walls,terminalStates,rewardInNonTerminalStates, transitionProbabilities,discountRate,epsilon);
        }
    }

