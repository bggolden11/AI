import java.util.ArrayList;
import java.util.List;

public class MDP {
    int sizeX;
    int sizeY;
    List<Point> walls;// = new ArrayList<>();
    List<TerminalState> terminalStates;// = new ArrayList<>();
    double rewardInNonTerminalStates;
    List<Double> transitionProbabilities;// = new ArrayList<>();
    double discountRate;
    double epsilon;
    List<List<String>> grid = new ArrayList<>();
    Point currentLocation;


    public MDP(MDP mdp){
        this.sizeX = mdp.sizeX;
        this.sizeY = mdp.sizeY;
        this.walls = mdp.walls;
        this.terminalStates = mdp.terminalStates;
        this.rewardInNonTerminalStates = mdp.rewardInNonTerminalStates;
        this.transitionProbabilities = mdp.transitionProbabilities;
        this.discountRate = mdp.discountRate;
        this.epsilon = mdp.epsilon;
        this.grid = new ArrayList<>();
        this.grid = setGrid(mdp.grid);
        this.currentLocation = mdp.currentLocation;
    }

    List<List<String>> setGrid(List<List<String>> given){
        List<List<String>> returnGrid = new ArrayList<>();
        for(int x =0; x<sizeY;x++){
            returnGrid.add(new ArrayList<String>());
            for(int y =0; y<sizeX;y++){
                returnGrid.get(x).add(given.get(x).get(y));
            }
        }
        return returnGrid;
        }


    public MDP(int sizeX, int sizeY, List<Point> walls, List<TerminalState> terminalStates, double rewardInNonTerminalStates, List<Double> transitionProbabilities, double discountRate, double epsilon) {
        this.sizeX = sizeX;
        this.sizeY = sizeY;
        this.walls = walls;

        this.terminalStates = terminalStates;
        this.rewardInNonTerminalStates = rewardInNonTerminalStates;
        this.transitionProbabilities = transitionProbabilities;
        this.discountRate = discountRate;
        this.epsilon = epsilon;
        currentLocation = new Point(0,0);


        System.out.println("Iteration: 0");
        for(int x =0; x<sizeY;x++){
            grid.add(new ArrayList<String>());
            for(int y =0; y<sizeX;y++){
                grid.get(x).add(String.valueOf(0));
            }
        }
        for(int y = grid.size()-1;y>=0;y--){
            for(int x =0;x<grid.get(0).size();x++){
                System.out.print(String.format("%20s", grid.get(y).get(x)));

            }
            System.out.println();
        }
        for(int y = grid.size()-1;y>=0;y--){
            for(int x =0;x<grid.get(0).size();x++){
                grid.get(y).set(x,String.valueOf(rewardInNonTerminalStates));

            }
            System.out.println();
        }

        for(Point p: walls){
            grid.get(p.y).set(p.x," ");
        }
        for(TerminalState terminalState:terminalStates){
            grid.get(terminalState.column).set(terminalState.row,String.valueOf(terminalState.reward));
        }


        System.out.println("Iteration: 1");
        printGrid();



    }

    public boolean setPoint(int x, int y, String c){
        try{
                grid.get(y).set(x, String.valueOf(c));
                return true;
            }
        catch(IndexOutOfBoundsException e){
            return false;
        }
    }

    public boolean setPoint(Point p, String c){
        try{
            grid.get(p.y).set(p.x, String.valueOf(c));
            return true;
        }
        catch(IndexOutOfBoundsException e){
            return false;
        }
    }

    public boolean isWall(Point p){
        try{
            return grid.get(p.y).get(p.x).equals(" ");
        }
        catch(IndexOutOfBoundsException e){
            return false;
        }
    }

    public boolean isWall(int x, int y){
        try{
            return grid.get(y).get(x).equals(" ");
        }
        catch(IndexOutOfBoundsException e){
            return false;
        }
    }

    public void printGrid(){
        for(int y = grid.size()-1;y>=0;y--){
            for(int x =0;x<grid.get(0).size();x++){
                System.out.print(String.format("%20s", grid.get(y).get(x)));

            }
            System.out.println();

        }
    }

    public boolean moveUp(Point currentLocation){
        if(currentLocation.y-1 >= 0 && !grid.get(currentLocation.y-1).get(currentLocation.x).equals(" ")){
//            currentLocation.y= currentLocation.y-1;
//            this.currentLocation.x = currentLocation.x;
//            this.currentLocation.y = currentLocation.y;
            return true;
        }
        else
            return false;
    }
    public boolean moveDown(Point currentLocation){
        if(currentLocation.y+1 <= sizeY-1 && !grid.get(currentLocation.y+1).get(currentLocation.x).equals(" ")){
//            currentLocation.y= currentLocation.y+1;
//            this.currentLocation.x = currentLocation.x;
//            this.currentLocation.y = currentLocation.y;

            return true;
        }
        else
            return false;
    }
//
    public boolean moveRight(Point currentLocation){
        if(currentLocation.x+1 <= sizeX-1 && !grid.get(currentLocation.y).get(currentLocation.x+1).equals(" ")){
//            currentLocation.x= currentLocation.x+1;
//            this.currentLocation.x = currentLocation.x;
//            this.currentLocation.y = currentLocation.y;
            return true;
        }
        else
            return false;
    }
    public boolean moveLeft(Point currentLocation){
        if(currentLocation.x-1 >= 0 && !grid.get(currentLocation.y).get(currentLocation.x-1).equals(" ")){
//            currentLocation.x= currentLocation.x-1;
//            this.currentLocation.x = currentLocation.x;
//            this.currentLocation.y = currentLocation.y;
            return true;
        }
        else
            return false;
    }

    public boolean isTerminalState(Point location){
        for (TerminalState terminalState : terminalStates) {
            if (location.y == terminalState.column && location.x == terminalState.row)
                return true;
        }
        return false;
    }

    public double getReward(Point currentLocation){
        for (TerminalState terminalState : terminalStates) {
            if (currentLocation.y == terminalState.column && currentLocation.x == terminalState.row)
                return terminalState.reward;
        }
        return Double.parseDouble(grid.get(currentLocation.y).get(currentLocation.x));
    }


    @Override
    public String toString() {
        return "MDP{" +
                "sizeX=" + sizeX +
                ", sizeY=" + sizeY +
                ", walls=" + walls +
                ", terminalStates=" + terminalStates +
                ", rewardInNonTerminalStates=" + rewardInNonTerminalStates +
                ", transitionProbabilities=" + transitionProbabilities +
                ", discountRate=" + discountRate +
                ", epsilon=" + epsilon +
                '}';
    }
}
