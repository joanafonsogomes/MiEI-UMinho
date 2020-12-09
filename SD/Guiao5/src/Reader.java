import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

public class Reader implements Runnable{
    private RWLock rwlock;

    public void run(){
        this.rwlock.readLock();
        System.out.println("Lock Read");
            try{
                Thread.sleep(1000);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        System.out.println("Unlock Read");
        this.rwlock.readUnlock();
    }

    public Reader(RWLock rwlock){
        this.rwlock = rwlock;
    }
}
