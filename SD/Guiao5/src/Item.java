import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

public class Item {
    private ReentrantLock lock;
    private Condition notFull;
    private Condition notEmpty;
    private int quant;
    private int maxQuant;

    public Item(){

    }

    public Item(int quant,int maxQuant){
        this.lock = new ReentrantLock();
        this.notFull = lock.newCondition();
        this.notEmpty = lock.newCondition();
        this.quant = quant;
        this.maxQuant = maxQuant;
    }

    public void supply(int add) throws InterruptedException {
        this.lock.lock();
       try {
           while (add > 0) {
               while (this.quant == this.maxQuant) {
                   this.notFull.await();
               }
            this.quant += add;
            this.notEmpty.signal();
           }
       }
       catch(InterruptedException ie){
           ie.printStackTrace();
       }
       finally{
           this.lock.unlock();
        }
    }

    public void consume() throws InterruptedException{
        this.lock.lock();
        try{
            while(this.quant == 0){
                this.notEmpty.await();
            }
        this.quant--;
        this.notFull.signal();
        }
        catch(InterruptedException ie){
            ie.printStackTrace();
        }
        finally {
            this.lock.unlock();
        }
    }

    public int getQuant() throws InterruptedException{
        this.lock.lock();
        try {
            return this.quant;
        } finally {
            lock.unlock();
        }
    }
}
