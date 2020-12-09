public class BoundedBuffer {
    private int values[];
    private int poswrite;

    public BoundedBuffer(int size){
        this.values = new int[size];
        this.poswrite = 0;
    }

    public synchronized void put(int v){
        try {
            while (this.values.length == this.poswrite) {
                System.out.println("Array is full!");
                this.wait();
            }

            System.out.println("Escreveu: " + v + "\tPosição: " + this.poswrite);
            this.values[this.poswrite] = v;
            this.poswrite++;

            this.notifyAll();
        }
        catch(InterruptedException ie){};
    }

    public synchronized int get() throws InterruptedException {
        try {
            while (this.poswrite == 0) {
                System.out.println("Array is empty!");
                this.wait();
            }
        }
        catch(InterruptedException ie){};


        this.poswrite--;
        int r = this.values[this.poswrite];
        System.out.println("Leu: " + r + "\tPosição: " + this.poswrite);
        this.notifyAll();
        return r;

    }
}
