public class Produtor implements Runnable{
    private Warehouse wh;
    private int nr;
    private String[] items;

    public void run(){
        for(int i=0; i<this.nr ; i++){
            try{
                for(String item : items){
                    this.wh.supply(item,2);
                    Thread.sleep(1000); //1s
                }
            }
            catch(InterruptedException ie) {
                ie.printStackTrace();
            } ;
        }
    }

    public Produtor(Warehouse wh, int nr, String[] items){
        this.wh = wh;
        this.nr = nr;
        this.items = items;
    }
}
