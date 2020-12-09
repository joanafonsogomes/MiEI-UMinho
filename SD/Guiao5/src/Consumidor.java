public class Consumidor implements Runnable {

    private Warehouse wh;
    private int nr;
    private String[] items;

    public void run(){
        for(int i=0; i<this.nr; i++){
            try{
                this.wh.consume(items);
                Thread.sleep(1000);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }

    public Consumidor(Warehouse wh, int nr, String[] items){
        this.wh = wh;
        this.nr = nr;
        this.items = items;
    }
}
