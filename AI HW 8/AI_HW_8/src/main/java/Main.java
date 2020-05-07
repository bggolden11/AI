import java.io.IOException;
import java.util.*;

public class Main {



  static void extractPolicy(MDP mdp) {
    double rewardUp = Double.NEGATIVE_INFINITY;
    double rewardDown = Double.NEGATIVE_INFINITY;
    double rewardRight = Double.NEGATIVE_INFINITY;
    double rewardLeft = Double.NEGATIVE_INFINITY;
    System.out.println("Final Policy");
      List<List<Character>> extractPolicyGrid = new ArrayList<>();
      for(int x =0; x<mdp.sizeY;x++){
          extractPolicyGrid.add(new ArrayList<Character>());
          for(int y =0; y<mdp.sizeX;y++){
              extractPolicyGrid.get(x).add('0');
          }
      }


      for (int y = 0; y < mdp.sizeY; y++) {
      for (int x = 0; x < mdp.sizeX; x++) {
        MDP moveUpMdp = new MDP(mdp);
        MDP moveRightMdp = new MDP(mdp);
        MDP moveDown = new MDP(mdp);
        MDP moveLeft = new MDP(mdp);
        double gamma = mdp.epsilon;
        ArrayList<Moves> values = new ArrayList<>();

        Point currentP = new Point(x, y);
        if (mdp.grid.get(y).get(x).equals(" ")) {
          extractPolicyGrid.get(y).set(x,' ');

          continue;
        }
        if (mdp.isTerminalState(currentP)) {
          extractPolicyGrid.get(y).set(x,'T');

          continue;
        }

        double currentReward = mdp.getReward(currentP);
        if (moveDown.moveDown(currentP)) {
          currentP.y += 1;

          rewardDown = moveDown.getReward(currentP);
          rewardDown = (rewardDown * gamma);
          values.add(new Moves(rewardDown, 'N'));
          currentP.y += -1;
        } else {
          rewardDown = moveDown.getReward(currentP);
          rewardDown = (rewardDown * gamma);
          values.add(new Moves(rewardDown, 'N'));
        }
        if (moveRightMdp.moveRight(currentP)) {
          currentP.x += 1;
          rewardRight = moveRightMdp.getReward(currentP);

          rewardRight = (rewardRight * gamma);
          values.add(new Moves(rewardRight, 'E'));
          currentP.x += -1;
        } else {
          rewardRight = moveRightMdp.getReward(currentP);

          rewardRight = (rewardRight * gamma);
          values.add(new Moves(rewardRight, 'E'));
        }
        if (moveLeft.moveLeft(currentP)) {
          currentP.x += -1;
          rewardLeft = moveLeft.getReward(currentP);
          rewardLeft = (rewardLeft * gamma);
          values.add(new Moves(rewardLeft, 'W'));
          currentP.x += 1;
        } else {
          rewardLeft = moveLeft.getReward(currentP);
          rewardLeft = (rewardLeft * gamma);
          values.add(new Moves(rewardLeft, 'W'));
        }
        if (moveUpMdp.moveUp(currentP)) {
          currentP.y += -1;

          rewardUp = moveUpMdp.getReward(currentP);
          rewardUp = (rewardUp * gamma);
          values.add(new Moves(rewardUp, 'S'));
          currentP.y += 1;
        } else {
          rewardUp = moveUpMdp.getReward(currentP);
          rewardUp = (rewardUp * gamma);
          values.add(new Moves(rewardUp, 'S'));
        }
          values.sort(
                  new Comparator<Moves>() {
                      @Override
                      public int compare(Moves m1, Moves m2) {
                          return Double.compare(m1.value, m2.value);
                      }
                  });
          Collections.reverse(values);
        double finalAnsN = 0.0;
        double finalAnsW = 0.0;
        double finalAnsS = 0.0;
        double finalAnsE = 0.0;

          finalAnsN += firstDirectionNorth(values, mdp.transitionProbabilities);
          finalAnsW += firstDirectionWest(values, mdp.transitionProbabilities);
          finalAnsS += firstDirectionSouth(values, mdp.transitionProbabilities);
          finalAnsE += firstDirectionEast(values, mdp.transitionProbabilities);

        if(finalAnsN > finalAnsE && finalAnsN > finalAnsS && finalAnsN> finalAnsW)
        {
          extractPolicyGrid.get(y).set(x,'N');
        }
        else if(finalAnsE > finalAnsN && finalAnsE > finalAnsS && finalAnsE> finalAnsW)
        {
          extractPolicyGrid.get(y).set(x,'E');
        }
        else if(finalAnsW > finalAnsN && finalAnsW > finalAnsS && finalAnsW> finalAnsE)
        {
          extractPolicyGrid.get(y).set(x,'W');
        }else
          extractPolicyGrid.get(y).set(x,'S');
      }
    }
      for(int yt = extractPolicyGrid.size()-1;yt>=0;yt--){
          for(int xt =0;xt<extractPolicyGrid.get(0).size();xt++){
              System.out.print(String.format("%20s", extractPolicyGrid.get(yt).get(xt)));
          }
          System.out.println();

      }
  }

  static double firstDirectionSouth(List<Moves> values, List<Double> prob) {
    double result = 0.0;
    int p = 0;
    for (Moves moves : values) {
      if (moves.d == 'S') {
        result += moves.value * prob.get(0);
        p++;
      }
    }
    for (Moves moves : values) {
      if (moves.d == 'E') {
        result += moves.value * prob.get(1);
        p++;
      }
    }
    for (Moves moves : values) {
      if (moves.d == 'W') {
        result += moves.value * prob.get(2);
        p++;
      }
    }
    for (Moves moves : values) {
      if (moves.d == 'N') {
        result += moves.value * prob.get(3);
        p++;
      }
    }

    return result;
  }

  static double firstDirectionEast(List<Moves> values, List<Double> prob) {
    double result = 0.0;
    int p = 0;
    double totalP = 0;

    for (Moves moves : values) {
      if (moves.d == 'E') {
        result += moves.value * prob.get(0);
        totalP += prob.get(0);
        p++;
      }
    }
    for (Moves moves : values) {
      if (moves.d == 'S') {
        result += moves.value * prob.get(1);
        totalP += prob.get(1);
        p++;
      }
    }
    for (Moves moves : values) {
      if (moves.d == 'N') {
        result += moves.value * prob.get(2);
        totalP += prob.get(2);
        p++;
      }
    }

    for (Moves moves : values) {
      if (moves.d == 'W') {
        result += moves.value * prob.get(3);
        totalP += prob.get(3);
        p++;
      }
    }

    return result;
  }

  static double firstDirectionNorth(List<Moves> values, List<Double> prob) {
    double result = 0.0;
    int p = 0;

    for (Moves moves : values) {
      if (moves.d == 'N') {
        result += moves.value * prob.get(0);
        p++;
      }
    }
    for (Moves moves : values) {
      if (moves.d == 'E') {
        result += moves.value * prob.get(1);
        p++;
      }
    }
    for (Moves moves : values) {
      if (moves.d == 'W') {
        result += moves.value * prob.get(2);
        p++;
      }
    }
    for (Moves moves : values) {
      if (moves.d == 'S') {
        result += moves.value * prob.get(3);
        p++;
      }
    }

    return result;
  }

  static double firstDirectionWest(List<Moves> values, List<Double> prob) {
    double result = 0.0;
    int p = 0;

    for (Moves moves : values) {
      if (moves.d == 'W') {
        result += moves.value * prob.get(0);
        p++;
      }
    }
    for (Moves moves : values) {
      if (moves.d == 'N') {
        result += moves.value * prob.get(1);
        p++;
      }
    }
    for (Moves moves : values) {
      if (moves.d == 'S') {
        result += moves.value * prob.get(2);
        p++;
      }
    }
    for (Moves moves : values) {
      if (moves.d == 'E') {
        result += moves.value * prob.get(3);
        p++;
      }
    }
    return result;
  }

  public static void valueIteration(MDP mdp) {
    int iteration = 2;

    MDP originalMdp = new MDP(mdp);
    List<Moves> values = new ArrayList<>();


    double rewardUp = Double.NEGATIVE_INFINITY;
    double rewardDown = Double.NEGATIVE_INFINITY;
    double rewardRight = Double.NEGATIVE_INFINITY;
    double rewardLeft = Double.NEGATIVE_INFINITY;

    boolean isComplete = false;
    double gamma = mdp.discountRate;
    double threshold;

    if (gamma == 1) threshold = mdp.epsilon;
    else threshold = mdp.epsilon * (1. - gamma) / gamma;

    for (; ; ) {
      MDP holdMdp = new MDP(mdp);
      double maxError = Double.MIN_VALUE;
      for (int y = 0; y < mdp.sizeY; y++) {
        for (int x = 0; x < mdp.sizeX; x++) {
          MDP moveUpMdp = new MDP(holdMdp);
          MDP moveRightMdp = new MDP(holdMdp);
          MDP moveDown = new MDP(holdMdp);
          MDP moveLeft = new MDP(holdMdp);
          Point currentP = new Point(x, y);
          values.clear();
          if (!mdp.isTerminalState(new Point(x, y)) && !mdp.isWall(new Point(x, y))) {

            double currentReward = originalMdp.getReward(currentP);
            if (moveDown.moveDown(currentP)) {
              currentP.y += 1;

              rewardDown = moveDown.getReward(currentP);
              rewardDown = (rewardDown * gamma);
              values.add(new Moves(rewardDown, 'N'));
              currentP.y += -1;
            } else {
              rewardDown = moveDown.getReward(currentP);
              rewardDown = (rewardDown * gamma);
              values.add(new Moves(rewardDown, 'N'));
            }
            if (moveRightMdp.moveRight(currentP)) {
              currentP.x += 1;
              rewardRight = moveRightMdp.getReward(currentP);

              rewardRight = (rewardRight * gamma);
              values.add(new Moves(rewardRight, 'E'));
              currentP.x += -1;
            } else {
              rewardRight = moveRightMdp.getReward(currentP);

              rewardRight = (rewardRight * gamma);
              values.add(new Moves(rewardRight, 'E'));
            }
            if (moveLeft.moveLeft(currentP)) {
              currentP.x += -1;
              rewardLeft = moveLeft.getReward(currentP);
              rewardLeft = (rewardLeft * gamma);
              values.add(new Moves(rewardLeft, 'W'));
              currentP.x += 1;
            } else {
              rewardLeft = moveLeft.getReward(currentP);
              rewardLeft = (rewardLeft * gamma);
              values.add(new Moves(rewardLeft, 'W'));
            }
            if (moveUpMdp.moveUp(currentP)) {
              currentP.y += -1;

              rewardUp = moveUpMdp.getReward(currentP);
              rewardUp = (rewardUp * gamma);
              values.add(new Moves(rewardUp, 'S'));
              currentP.y += 1;
            } else {
              rewardUp = moveUpMdp.getReward(currentP);
              rewardUp = (rewardUp * gamma);
              values.add(new Moves(rewardUp, 'S'));
            }

            double finalAns = currentReward;
            values.sort(
                new Comparator<Moves>() {
                  @Override
                  public int compare(Moves m1, Moves m2) {
                    return Double.compare(m1.value, m2.value);
                  }
                });
            Collections.reverse(values);
            if (values.size() == 1) finalAns += values.get(0).d;
            if (values.size() == 2) {
              Iterator<Moves> iter = values.iterator();

              Moves first = iter.next();
              Moves second = iter.next();
              System.out.println(values.get(0).d);
              System.out.println(mdp.transitionProbabilities.get(0) * (1 / .9));

              System.out.println(values.get(0).d * mdp.transitionProbabilities.get(0) * (1 / .9));
              finalAns += (first.value * mdp.transitionProbabilities.get(0) * (1 / .9));

              finalAns += (second.value * mdp.transitionProbabilities.get(1) * (1 / .9));
            } else {
              if (values.get(0).d == 'N')
                finalAns += firstDirectionNorth(values, mdp.transitionProbabilities);
              else if (values.get(0).d == 'W')
                finalAns += firstDirectionWest(values, mdp.transitionProbabilities);
              else if (values.get(0).d == 'S')
                finalAns += firstDirectionSouth(values, mdp.transitionProbabilities);
              else if (values.get(0).d == 'E')
                finalAns += firstDirectionEast(values, mdp.transitionProbabilities);
            }

            if (values.size() > 0 && !mdp.isTerminalState((new Point(x, y)))) {
              double currentError = Math.abs(finalAns - holdMdp.getReward(new Point(x, y)));
              if (currentError > maxError) maxError = currentError;
              mdp.setPoint(
                  new Point(x, y), String.valueOf(Math.round(finalAns * 1000000.0) / 1000000.0));
            }
          }
        }
      }

      if (maxError < threshold) break;
      System.out.println("iteration:" + iteration);
      mdp.printGrid();
      iteration++;
    }
    System.out.println("Final Value After Convergence");
    mdp.printGrid();
    extractPolicy(mdp);
  }

  public static void main(String[] test) {
    try {
      MDP initialMdp = (new Parser()).parse();
      valueIteration(initialMdp);

      System.out.println();
    } catch (IOException e) {
      System.out.println(
          "ERROR: Could not parse file properly, ensure proper format and that the file is in the right location.\n"
              + "ex: /src/resources");
    }
  }
}
