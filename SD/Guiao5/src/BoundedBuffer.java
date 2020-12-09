import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

public class BoundedBuffer {
    private int values[];
    private int poswrite;
    private ReentrantLock lock;
    private Condition notEmpty;
    private Condition notFull;

    public BoundedBuffer(int size){
        this.values = new int[size];
        this.poswrite = 0;
        this.lock = new ReentrantLock();
        this.notEmpty = lock.newCondition();
        this.notFull = lock.newCondition();
    }

    public void put(int v){
        this.lock.lock();
        try {
            while (this.values.length == this.poswrite) {
                System.out.println("Array is full!");
                this.notFull.await();
            }

            System.out.println("Escreveu: " + v + "\tPosição: " + this.poswrite);
            this.values[this.poswrite] = v;
            this.poswrite++;

            this.notEmpty.signal();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }

    }

    public int get() throws InterruptedException {
        this.lock.lock();
        try {
            while (this.values.length == 0) {
                System.out.println("Array is empty!");
                this.notEmpty.await();
            }
            this.poswrite--;
            int r = this.values[this.poswrite];
            System.out.println("Leu: " + r + "\tPosição: " + this.poswrite);
            this.notFull.signal();
            return r;
        }
        finally{
            this.lock.unlock();
        }

    }
}
