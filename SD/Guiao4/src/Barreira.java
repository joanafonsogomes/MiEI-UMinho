public class Barreira {

    private int N;
    private int locked;

    public Barreira(int N){
        this.N = N;
    }

    public synchronized void esperar(){
    try{
        while(this.N != this.locked){
            this.wait();
            this.locked++;
        }
    } catch (InterruptedException e) {
        e.printStackTrace();
    }
    this.notifyAll();
    this.locked=0;
    }
}
