public class Consumidor implements Runnable {

    private BoundedBuffer bb;
    private int n;

    public void run(){
        for(int i=0; i<this.n; i++){
            try {
                this.bb.get();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public Consumidor(BoundedBuffer bb, int n){
        this.bb = bb;
        this.n = n;
    }
}
