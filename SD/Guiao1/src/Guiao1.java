//VERSAO 1
/*public class Guiao1 implements Runnable {

    public void run(){
        System.out.println("Hello World!");
    }

    public static void main(String args[]){
        (new Thread(new Guiao1())).start();
    }

}*/

//VERSAO 2
/*public class  Guiao1 implements Runnable {
    int n;
    public void run() {
        System.out.println(n);
    }
    Guiao1(int a) {
        n=a;
    }
    public static void main(String args[]) {
        Guiao1 r222 = new Guiao1(222);
        Guiao1 r111 = new Guiao1(111);
        Thread t1=new Thread(r222);
        Thread t2=new Thread(r111);;
        System.out.println("Antes");
        t1.start();
        t2.start();
        System.out.println("Depois");
        try {
            t2.join();
            t1.join();
        } catch (InterruptedException e) {}
        System.out.println("Fim");
    }
}*/

//VERSAO 3
/*public class Guiao1 implements Runnable {
    int n;
    public void run() {
        System.out.println(n);
        this.set(111);
    }
    Guiao1(int a) {
        n=a;
    }
    public void set(int b) {
        n=b;
    }

    public static void main(String args[]) {
        Guiao1 r=new Guiao1(222);
        Thread t1=new Thread(r);
        Thread t2=new Thread(r);
        System.out.println("Antes");
        t1.start();
        t2.start();
        System.out.println("Depois");
        try {
            t2.join();
            t1.join();
        } catch (InterruptedException e) {}
    }
}*/

//EXERCICIO 1


