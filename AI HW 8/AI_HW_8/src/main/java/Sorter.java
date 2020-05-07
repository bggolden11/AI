public class Sorter implements Comparable<Moves> {
  public boolean compare(Moves o1, Moves o2) {
    return o1.value > o2.value;
  }

    @Override
    public int compareTo(Moves o) {
        return 0;
    }
}

