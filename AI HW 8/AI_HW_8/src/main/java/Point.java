public class Point {
    int x;// = -1;
    int y;// = -1;

    public Point(){
         x = -1;
         y = -1;
    }

    public void setPoint(int input){
        if(x == -1){
            x = input-1;
        }
        else if(y == -1){
            y = input-1;
        }
    }
    public Point(int x, int y){
        this.x = x;
        this.y =y;
    }

    @Override
    public String toString() {
        return "Point{" +
                "x=" + x +
                ", y=" + y +
                '}';
    }
}
