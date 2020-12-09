public class Main {
    public static void main(String args[]){
        BoundedBuffer bb = new BoundedBuffer(10);

        Produtor p = new Produtor(bb,20);
        Consumidor c = new Consumidor(bb,20);

        //criar as threads
        Thread t1 = new Thread(p);
        Thread t2 = new Thread(c);

        //iniciar as threads
        t1.start();
        t2.start();

        try{
            t1.join();
            t2.join();
        } catch (InterruptedException ie) { }
    }
}
