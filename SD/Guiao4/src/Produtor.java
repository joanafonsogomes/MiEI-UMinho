public class Produtor implements Runnable{
    private BoundedBuffer bb;
    private int n;

    public void run(){
        for(int i=0; i<this.n; i++){
            this.bb.put(i);
        }
    }

    public Produtor(BoundedBuffer bb, int n){
        this.bb = bb;
        this.n = n;
    }
}
