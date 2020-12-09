import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

public class RWLock {
    private ReentrantLock lock;
    private int nReaders;
    private int nWriters;
    private Condition readerCondition;
    private Condition writerCondition;

    public RWLock(){
        this.lock = new ReentrantLock();
        this.readerCondition = this.lock.newCondition();
        this.writerCondition = this.lock.newCondition();
        this.nReaders = 0;
        this.nWriters = 0;
    }

    public void readLock(){
        this.lock.lock();
        while(this.nWriters>0){
            try{
                this.readerCondition.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        this.nReaders++;
        this.lock.unlock();
    }

    public void readUnlock(){
        this.lock.lock();
        this.nReaders--;
        if(this.nReaders==0){
            this.writerCondition.signal();
        }
        this.lock.unlock();
    }

    public void writeLock(){
        this.lock.lock();
            while(this.nReaders>0 || this.nWriters>0){
                try{
                    this.writerCondition.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        this.nWriters++;
        this.lock.unlock();
    }

    public void writeUnlock(){
        this.lock.lock();
        this.nWriters--;
        this.writerCondition.signal();
        this.readerCondition.signal();
        this.lock.unlock();
    }




}
