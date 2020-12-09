import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String args[]){
        String[] items = new String[]{"Item1","Item2","Item3"};

        Warehouse wh = new Warehouse(items);

        Consumidor c = new Consumidor(wh,2,items);
        Produtor p = new Produtor(wh,1,items);

        //criar threads
        Thread t1 = new Thread(c);
        Thread t2 = new Thread(p);

        //iniciar threads
        t1.start();
        t2.start();

        try{
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
