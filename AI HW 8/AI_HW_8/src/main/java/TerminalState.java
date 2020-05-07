import java.util.List;

public class TerminalState {
    public int row, column;
    public int reward;

    public TerminalState(){
        row = -1;
        column = -1;
        reward = -1;
    }
    public boolean setStates(List<String> l){
        if(l.size()==3){
            for(int i =0; i<l.size(); i++){
                if(i ==0)
                    row = Integer.parseInt(l.get(i));
                else if(i==1)
                    column =  Integer.parseInt(l.get(i));
                else reward =  Integer.parseInt(l.get(i));
            }
            return true;

        }
        if(l.size()==4){
            if(!l.get(0).isEmpty()){
                System.out.println("FAILED");
                return false;
                }
            for(int i =1; i<l.size(); i++){
                if(i ==1)
                    row = Integer.parseInt(l.get(i));
                else if(i==2)
                    column =  Integer.parseInt(l.get(i));
                else reward =  Integer.parseInt(l.get(i));
            }
            row+=-1;
            column+=-1;
            return true;

        }
        else{
            System.out.println("NOT PROPER SIZE!!!");
            return false;
        }
    }

    @Override
    public String toString() {
        return "TerminalStates{" +
                "row=" + row +
                ", column=" + column +
                ", reward=" + reward +
                '}';
    }
}
